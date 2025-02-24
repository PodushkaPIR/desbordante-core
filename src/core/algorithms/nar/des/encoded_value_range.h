#pragma once

#include <memory>                        // for shared_ptr

#include <stddef.h>                      // for size_t

#include "algorithms/nar/value_range.h"  // for ValueRange

namespace algos { namespace des { class RNG; } }

namespace algos::des {

class EncodedValueRange {
public:
    static size_t constexpr kFieldCount = 4;
    double permutation;
    double threshold;
    double bound1;
    double bound2;

    double& operator[](size_t index);
    double const& operator[](size_t index) const;

    template <typename T, typename RangeT>
    std::shared_ptr<RangeT> DecodeTypedValueRange(
            std::shared_ptr<model::ValueRange> const& domain) const;

    std::shared_ptr<model::ValueRange> Decode(
            std::shared_ptr<model::ValueRange> const& domain) const;

    explicit EncodedValueRange(RNG& rng);
};

}  // namespace algos::des
