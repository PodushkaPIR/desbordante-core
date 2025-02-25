/** \file
 * \brief Mind algorithm
 *
 * Mind algorithm class definition
 */
#pragma once

#include <memory>         // for unique_ptr
#include <optional>       // for optional
#include <stddef.h>       // for size_t
#include <string_view>    // for string_view
#include <typeindex>      // for type_index
#include <unordered_set>  // for unordered_set

#include "algorithms/ind/ind_algorithm.h"  // for INDAlgorithm
#include "config/error/type.h"             // for ErrorType
#include "config/max_arity/type.h"         // for MaxArityType
#include "raw_ind.h"                       // for RawIND

namespace boost {
class any;
}

namespace algos {

///
/// \brief in-memory nary approximate inclusion dependency mining algorithm
///
class Mind final : public INDAlgorithm {
public:
    /// timing information for algorithm stages
    struct StageTimings {
        size_t load;          /**< time taken for the data loading */
        size_t compute_uinds; /**< time taken for the unary inds computing */
        size_t compute_ninds; /**< time taken for the n-ary inds computing */
    };

private:
    using RawIND = mind::RawIND;

    /* configuration stage fields */
    config::ErrorType max_ind_error_ = 0;
    config::MaxArityType max_arity_;

    /* execution stage fields */
    std::unique_ptr<INDAlgorithm> auind_algo_; /*< algorithm for mining unary approximate INDs*/
    StageTimings timings_{};                   /*< timings info */

    void MakeLoadOptsAvailable();
    void MakeExecuteOptsAvailable() override;
    void AddSpecificNeededOptions(
            std::unordered_set<std::string_view>& previous_options) const override;
    bool SetExternalOption(std::string_view option_name, boost::any const& value) override;
    std::type_index GetExternalTypeIndex(std::string_view option_name) const override;

    void LoadINDAlgorithmDataInternal() override;

    ///
    /// Test a given IND candidate to determine if it should be registered.
    ///
    /// \return `std::nullopt` if the candidate should not be registered,
    ///         otherwise return the error threshold at which AIND holds.
    ///
    std::optional<config::ErrorType> TestCandidate(RawIND const& raw_ind);

    void MineUnaryINDs();
    void MineNaryINDs();
    unsigned long long ExecuteInternal() override;
    void ResetINDAlgorithmState() override;

public:
    explicit Mind();

    /// get information about stage timings
    StageTimings const& GetStageTimings() const noexcept {
        return timings_;
    }
};

}  // namespace algos
