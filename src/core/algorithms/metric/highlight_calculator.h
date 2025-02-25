#pragma once

#include <cstddef>  // for byte
#include <memory>   // for shared_ptr
#include <utility>  // for move
#include <vector>   // for vector

#include "algorithms/metric/highlight.h"  // for Highlight
#include "config/indices/type.h"          // for IndicesType
#include "metric/aliases.h"               // for DistanceFunction, IndexedOn...

namespace algos {
namespace metric {
template <typename T>
struct IndexedPoint;
}
}  // namespace algos

namespace model {
class ColumnLayoutTypedRelationData;
}

namespace algos::metric {

class HighlightCalculator {
private:
    std::vector<std::vector<Highlight>> highlights_;
    std::shared_ptr<model::ColumnLayoutTypedRelationData> typed_relation_;
    config::IndicesType rhs_indices_;

    template <typename Compare>
    void SortHighlights(Compare compare) {
        for (auto& cluster_highlight : highlights_) {
            std::sort(cluster_highlight.begin(), cluster_highlight.end(), compare);
        }
    }

    template <typename T>
    void BruteCalculateHighlights(std::vector<IndexedPoint<T>> const& indexed_points,
                                  std::vector<Highlight>&& cluster_highlights,
                                  DistanceFunction<T> const& dist_func);

public:
    void CalculateOneDimensionalHighlights(
            std::vector<IndexedOneDimensionalPoint> const& indexed_points,
            std::vector<Highlight>&& cluster_highlights);

    void CalculateHighlightsForStrings(
            std::vector<IndexedPoint<std::byte const*>> const& indexed_points,
            std::vector<Highlight>&& cluster_highlights,
            DistanceFunction<std::byte const*> const& dist_func);

    void CalculateMultidimensionalHighlights(
            std::vector<IndexedPoint<std::vector<long double>>> const& indexed_points,
            std::vector<Highlight>&& cluster_highlights);

    void SortHighlightsByDistanceAscending();
    void SortHighlightsByDistanceDescending();
    void SortHighlightsByFurthestIndexAscending();
    void SortHighlightsByFurthestIndexDescending();
    void SortHighlightsByIndexAscending();
    void SortHighlightsByIndexDescending();

    std::vector<std::vector<Highlight>> const& GetHighlights() const {
        return highlights_;
    }

    explicit HighlightCalculator(
            std::shared_ptr<model::ColumnLayoutTypedRelationData> typed_relation,
            config::IndicesType rhs_indices)
        : typed_relation_(std::move(typed_relation)), rhs_indices_(std::move(rhs_indices)) {};
};

}  // namespace algos::metric
