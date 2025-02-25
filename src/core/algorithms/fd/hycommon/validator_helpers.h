#pragma once

#include <cstddef>      // for size_t
#include <string_view>  // for string_view
#include <vector>       // for vector

#include <boost/unordered/unordered_flat_map_fwd.hpp>  // for unordered_flat...
#include <boost/version.hpp>                           // for BOOST_VERSION
#include <easylogging++.h>                             // for Writer, CINFO

#include "types.h"  // for ClusterId, Row

#define UNORDERED_FLAT_MAP_AVAILABLE (BOOST_VERSION >= 108100)

#if UNORDERED_FLAT_MAP_AVAILABLE
#include <boost/unordered/unordered_flat_map.hpp>  // for unordered_flat...
#endif

namespace algos::hy {

// Builds a cluster's identifier of the agree set provided. Cluster's identifier is a vector
// of size_t value where ith value of the vector is an identifier of a cluster of ith set
// attribute of the agree set.
std::vector<ClusterId> BuildClustersIdentifier(Row const& compressed_record,
                                               std::vector<ClusterId> const& agree_set);

// Builds the next level of the prefix tree traversal
template <typename VertexAndAgreeSet>
std::vector<VertexAndAgreeSet> CollectCurrentChildren(
        std::vector<VertexAndAgreeSet> const& cur_level_vertices, size_t num_attributes);

template <typename VertexAndAgreeSet, typename InstanceValidations>
void LogLevel(std::vector<VertexAndAgreeSet> const& cur_level_vertices,
              InstanceValidations const& result, size_t candidates, size_t current_level_number,
              std::string_view primitive) {
    int const num_invalid_instances = result.InvalidInstances().size();
    int const num_valid_instances = result.CountValidations() - num_invalid_instances;

    LOG(INFO) << "LEVEL " << current_level_number << "(" << cur_level_vertices.size()
              << "): " << result.CountIntersections() << " intersections; "
              << result.CountValidations() << " validations; " << num_invalid_instances
              << " invalid; " << candidates << " new candidates; --> " << num_valid_instances << " "
              << primitive << "s";
}

template <typename T>
auto MakeClusterIdentifierToTMap(size_t bucket_size) {
    auto const hasher = [](std::vector<ClusterId> const& v) noexcept {
        size_t hash = 1;
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            hash = 31 * hash + *it;
        }
        return hash;
    };

#if UNORDERED_FLAT_MAP_AVAILABLE
    using UnorderedMap = boost::unordered_flat_map<std::vector<ClusterId>, T, decltype(hasher)>;
#else
    using UnorderedMap = std::unordered_map<std::vector<ClusterId>, T, decltype(hasher)>;
#endif
    return UnorderedMap(bucket_size, hasher);
}

#undef UNORDERED_FLAT_MAP_AVAILABLE

}  // namespace algos::hy
