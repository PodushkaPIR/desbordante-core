#pragma once

#include <memory>         // for unique_ptr
#include <unordered_map>  // for unordered...
#include <vector>         // for vector

#include "algorithms/algorithm.h"                           // for Algorithm
#include "config/tabular_data/input_table_type.h"           // for InputTable
#include "dependency_checker.h"                             // for ValidityType
#include "list_lattice.h"                                   // for ListLattice
#include "model/table/column_layout_typed_relation_data.h"  // for ColumnLay...
#include "order_utility.h"                                  // for Attribute...
#include "sorted_partitions.h"                              // for SortedPar...

namespace algos::order {

class Order : public Algorithm {
public:
    using SortedPartitions = std::unordered_map<Node, SortedPartition, ListHash>;
    using TypedRelation = model::ColumnLayoutTypedRelationData;

    config::InputTable input_table_;
    std::unique_ptr<TypedRelation> typed_relation_;
    SortedPartitions sorted_partitions_;
    std::vector<AttributeList> single_attributes_;
    CandidateSets previous_candidate_sets_;
    CandidateSets candidate_sets_;
    OrderDependencies valid_;
    OrderDependencies merge_invalidated_;
    std::unique_ptr<ListLattice> lattice_;

    void RegisterOptions();
    void LoadDataInternal() override;
    void ResetState() override;
    void PruneSingleEqClassPartitions();
    void CreateSingleColumnSortedPartitions();
    void CreateSortedPartitionsFromSingletons(AttributeList const& attr_list);
    bool HasValidPrefix(AttributeList const& lhs, AttributeList const& rhs) const;
    ValidityType CheckCandidateValidity(AttributeList const& lhs, AttributeList const& rhs);
    void ComputeDependencies(ListLattice::LatticeLevel const& lattice_level);
    std::vector<AttributeList> Extend(AttributeList const& lhs, AttributeList const& rhs) const;
    bool IsMinimal(AttributeList const& a) const;
    bool ExtendedRhsIsPrunable(AttributeList const& lhs, AttributeList const& extended_rhs) const;
    void UpdateCandidateSets();
    void MergePrune();
    void PrintValidOD();
    unsigned long long ExecuteInternal() final;

public:
    OrderDependencies const& GetValidODs() const {
        return valid_;
    }

    Order();
};

}  // namespace algos::order
