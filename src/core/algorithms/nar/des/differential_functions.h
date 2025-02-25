#pragma once

#include <stddef.h>  // for size_t
#include <vector>    // for vector

#include "encoded_nar.h"  // for EncodedNAR
#include "enums.h"        // for DifferentialStrategy
#include "rng.h"          // for RNG

namespace algos::des {

struct DifferentialOptions {
    double differential_scale;
    double crossover_probability;
    DifferentialStrategy differential_strategy = DifferentialStrategy::best1Exp;
};

EncodedNAR Rand1Bin(std::vector<EncodedNAR> const& population, size_t candidate_index,
                    DifferentialOptions const& options, RNG& rng);

using MutationFunction = EncodedNAR (*)(std::vector<EncodedNAR> const& population,
                                        size_t candidate_index, DifferentialOptions const& options,
                                        RNG& rng);

MutationFunction EnumToMutationStrategy(DifferentialStrategy strategy);

}  // namespace algos::des
