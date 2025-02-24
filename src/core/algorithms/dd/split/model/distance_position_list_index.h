#pragma once

#include <cstddef>                    // for size_t
#include <string>                     // for hash, string
#include <unordered_map>              // for unordered_map
#include <vector>                     // for vector

#include "model/table/tuple_index.h"  // for TupleIndex

namespace model { class TypedColumnData; }

namespace algos::dd {
using ClusterIndex = std::size_t;

struct ClusterInfo {
    model::TupleIndex first_tuple_index;
    std::size_t size;
};

class DistancePositionListIndex {
private:
    std::unordered_map<std::string, ClusterIndex> value_mapping_;
    std::vector<ClusterInfo> clusters_;
    std::vector<ClusterIndex> inverted_index_;

    model::TupleIndex cur_tuple_index_ = 0;
    ClusterIndex next_cluster_index_ = 0;

    template <typename T>
    void AddValue(T&& value);

public:
    DistancePositionListIndex() = default;
    DistancePositionListIndex(model::TypedColumnData const& column, model::TupleIndex num_rows = 0);

    std::vector<ClusterInfo> const& GetClusters() const {
        return clusters_;
    }

    std::vector<ClusterIndex> const& GetInvertedIndex() const {
        return inverted_index_;
    }
};
}  // namespace algos::dd
