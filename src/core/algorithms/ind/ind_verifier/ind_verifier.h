/** \file
 * \brief INDVerifier algorithm
 *
 * Algorithm for veryfing AIND.
 */
#pragma once

#include <vector>                            // for vector

#include <stddef.h>                          // for size_t

#include "algorithms/algorithm.h"            // for Algorithm
#include "config/indices/type.h"             // for IndicesType
#include "error/type.h"                      // for ErrorType
#include "table/tuple_index.h"               // for TupleIndex
#include "tabular_data/input_tables_type.h"  // for InputTables

namespace algos {

///
/// \brief Algorithm for verifying AIND.
///
/// \todo Add special handling of empty values and nulls.
///
class INDVerifier final : public Algorithm {
public:
    struct RawIND {
        config::IndicesType lhs;
        config::IndicesType rhs;
    };

    using Cluster = std::vector<model::TupleIndex>;
    using Error = config::ErrorType;

private:
    /* configuration stage fields */
    config::InputTables input_tables_;
    RawIND ind_;

    /* execution stage fields */
    std::vector<Cluster> violating_clusters_;
    model::TupleIndex violating_rows_;
    Error error_;

    void RegisterOptions();
    void MakeExecuteOptsAvailable() final;
    void ResetState() final;

    void LoadDataInternal() final;

    void VerifyIND();

    unsigned long long ExecuteInternal() final;

public:
    explicit INDVerifier();

    ///
    /// Check if exact IND holds.
    ///
    bool Holds() const noexcept {
        return GetError() == 0.0;
    }

    ///
    /// Get the error threshold at which AIND holds.
    ///
    Error GetError() const noexcept {
        return error_;
    }

    ///
    /// Get the total number of table rows that violate the IND.
    ///
    size_t GetViolatingRowsCount() const noexcept {
        return violating_rows_;
    }

    ///
    /// Get the number of clusters where the IND is violated, that is, the number
    /// of unique rows in the specified columns that need to be removed.
    ///
    size_t GetViolatingClustersCount() const noexcept {
        return GetViolatingClusters().size();
    }

    ///
    /// Get clusters where the IND is violated, that is, sets of rows where each set consists of
    /// rows equal to each other in the specified columns.
    ///
    std::vector<Cluster> const& GetViolatingClusters() const noexcept {
        return violating_clusters_;
    }
};

}  // namespace algos
