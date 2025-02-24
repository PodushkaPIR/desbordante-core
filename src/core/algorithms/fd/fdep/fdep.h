#pragma once

#include <memory>                                  // for unique_ptr, shared...
#include <string>                                  // for string
#include <vector>                                  // for vector

#include <stddef.h>                                // for size_t

#include "algorithms/fd/fd_algorithm.h"            // for FDAlgorithm
#include "algorithms/fd/fdep/fd_tree_element.h"    // for FDTreeElement
#include "config/tabular_data/input_table_type.h"  // for InputTable
#include "model/types/bitset.h"                    // for Bitset

class RelationalSchema;

namespace algos {

class FDep : public FDAlgorithm {
public:
    FDep();

    ~FDep() override = default;

private:
    config::InputTable input_table_;

    std::shared_ptr<RelationalSchema> schema_{};

    std::vector<std::string> column_names_;
    size_t number_attributes_{};

    std::unique_ptr<FDTreeElement> neg_cover_tree_{};
    std::unique_ptr<FDTreeElement> pos_cover_tree_{};

    std::vector<std::vector<size_t>> tuples_;

    void RegisterOptions();

    void LoadDataInternal() final;

    void ResetStateFd() final;
    unsigned long long ExecuteInternal() final;

    // Building negative cover via violated dependencies
    void BuildNegativeCover();

    // Iterating over all pairs t1 and t2 of the relation
    // Adding violated FDs to negative cover tree.
    void AddViolatedFDs(std::vector<size_t> const& t1, std::vector<size_t> const& t2);

    // Converting negative cover tree into positive cover tree
    void CalculatePositiveCover(FDTreeElement const& neg_cover_subtree,
                                model::Bitset<FDTreeElement::kMaxAttrNum>& active_path);

    // Specializing general dependencies for not to be followed from violated dependencies of
    // negative cover tree.
    void SpecializePositiveCover(model::Bitset<FDTreeElement::kMaxAttrNum> const& lhs,
                                 size_t const& a);
};

}  // namespace algos
