#include "order.h"

#include <algorithm>

#include "config/names_and_descriptions.h"
#include "config/tabular_data/input_table/option.h"
#include "model/types/types.h"

namespace algos::order {

Order::Order() : Algorithm({}) {
    RegisterOptions();
    MakeOptionsAvailable({config::kTableOpt.GetName()});
}

void Order::RegisterOptions() {
    using namespace config::names;
    using namespace config::descriptions;
    using config::Option;

    RegisterOption(config::kTableOpt(&input_table_));
}

void Order::LoadDataInternal() {
    typed_relation_ = model::ColumnLayoutTypedRelationData::CreateFrom(*input_table_, false);
}

void Order::ResetState() {}

void Order::CreateSortedPartitions() {
    std::vector<model::TypedColumnData> const& data = typed_relation_->GetColumnData();
    for (unsigned int i = 0; i < data.size(); ++i) {
        if (!model::Type::IsOrdered(data[i].GetTypeId())) {
            continue;
        }
        std::vector<std::pair<unsigned long, std::byte const*>> indexed_byte_data;
        indexed_byte_data.reserve(data[i].GetNumRows());
        std::vector<std::byte const*> const& byte_data = data[i].GetData();
        for (size_t k = 0; k < byte_data.size(); ++k) {
            indexed_byte_data.emplace_back(k, byte_data[k]);
        }
        model::Type const& type = data[i].GetType();
        auto less = [&type](std::pair<unsigned long, std::byte const*> l,
                            std::pair<unsigned long, std::byte const*> r) {
            return type.Compare(l.second, r.second) == model::CompareResult::kLess;
        };
        std::sort(indexed_byte_data.begin(), indexed_byte_data.end(), less);
        std::vector<std::unordered_set<unsigned long>> equivalence_classes;
        equivalence_classes.push_back({indexed_byte_data.front().first});
        auto equal = [&type](std::pair<unsigned long, std::byte const*> l,
                             std::pair<unsigned long, std::byte const*> r) {
            return type.Compare(l.second, r.second) == model::CompareResult::kEqual;
        };
        for (size_t k = 1; k < indexed_byte_data.size(); ++k) {
            if (equal(indexed_byte_data[k - 1], indexed_byte_data[k])) {
                equivalence_classes.back().insert(indexed_byte_data[k].first);
            } else {
                equivalence_classes.push_back({indexed_byte_data[k].first});
            }
        }
        sorted_partitions_[{i}] = SortedPartition(std::move(equivalence_classes));
    }
}

bool SubsetSetDifference(std::unordered_set<unsigned long>& a,
                                                        std::unordered_set<unsigned long>& b) {
    auto const not_found = b.end();
    for (auto const& element: a)
        if (b.find(element) == not_found) {
            return false;
        } else {
            b.erase(element);
        }
    return true;
}

ValidityType Order::CheckForSwap(SortedPartition const& l, SortedPartition const& r) {
    ValidityType res = ValidityType::valid;
    size_t l_i = 0, r_i = 0;
    bool next_l = true, next_r = true;
    std::unordered_set<unsigned long> l_eq_class;
    std::unordered_set<unsigned long> r_eq_class;
    while (l_i < l.sorted_partition.size() && r_i < r.sorted_partition.size()) {
        if (next_l) {
            l_eq_class = l.sorted_partition[l_i];
        }    
        if (next_r) {
            r_eq_class = r.sorted_partition[r_i];
        }
        if (l_eq_class.size() < r_eq_class.size()) {
            if(!SubsetSetDifference(l_eq_class, r_eq_class)) {
                return ValidityType::swap;
            } else {
                res = ValidityType::merge;
                ++l_i;
                next_l = true;
                next_r = false;
            }
        } else {
            if (!SubsetSetDifference(r_eq_class, l_eq_class)) {
                return ValidityType::swap;
            } else {
                ++r_i;
                next_r = true;
                if (l_eq_class.empty()) {
                    ++l_i;
                    next_l = true;
                } else {
                    next_l = false;
                }
            }
        }
    }
    return res;
}

unsigned long long Order::ExecuteInternal() {}

}  // namespace algos::order