#include "des.h"

#include <algorithm>                               // for generate_n, __sort_fn
#include <cstddef>                                 // for size_t
#include <iterator>                                // for back_insert_iterator
#include <memory>                                  // for shared_ptr, unique...
#include <string_view>                             // for basic_string_view
#include <utility>                                 // for move
#include <vector>                                  // for vector

#include <bits/chrono.h>                           // for duration_cast, ope...
#include <boost/type_index/type_index_facade.hpp>  // for operator==

#include "algorithms/nar/value_range.h"            // for CreateValueRange
#include "config/names_and_descriptions.h"                   // for DESBORDANTE_OPTION...
#include "config/option_using.h"                   // for DESBORDANTE_OPTION...
#include "nar/des/differential_functions.h"        // for DifferentialOptions
#include "nar/des/encoded_nar.h"                   // for EncodedNAR, NAR
#include "nar/des/enums.h"                         // for DifferentialStrategy
#include "nar/des/rng.h"                           // for RNG
#include "nar/nar.h"                               // for NAR, NARQualities
#include "nar/nar_algorithm.h"                     // for NARAlgorithm
#include "option.h"                                // for Option

namespace algos::des {
using model::ValueRange;

DES::DES() : NARAlgorithm({}) {
    RegisterOptions();
}

void DES::RegisterOptions() {
    DESBORDANTE_OPTION_USING;

    DifferentialStrategy default_strategy = DifferentialStrategy::rand1Bin;
    RegisterOption(Option{&seed_, kSeed, kDSeed, 2ul});
    RegisterOption(Option{&population_size_, kPopulationSize, kDPopulationSize, 100u});
    RegisterOption(
            Option{&num_evaluations_, kMaxFitnessEvaluations, kDMaxFitnessEvaluations, 1000u});
    RegisterOption(Option{&differential_options_.differential_scale, kDifferentialScale,
                          kDDifferentialScale, 0.5});
    RegisterOption(Option{&differential_options_.crossover_probability, kCrossoverProbability,
                          kDCrossoverProbability, 0.9});
    RegisterOption(Option{&differential_options_.differential_strategy, kDifferentialStrategy,
                          kDDifferentialStrategy, default_strategy});
}

void DES::MakeExecuteOptsAvailable() {
    NARAlgorithm::MakeExecuteOptsAvailable();
    using namespace config::names;
    MakeOptionsAvailable({kSeed, kPopulationSize, kMaxFitnessEvaluations, kDifferentialScale,
                          kCrossoverProbability, kDifferentialStrategy});
}

FeatureDomains DES::FindFeatureDomains(TypedRelation const* typed_relation) {
    std::vector<std::shared_ptr<ValueRange>> feature_domains;
    feature_domains.reserve(typed_relation->GetNumColumns());
    std::ranges::transform(typed_relation->GetColumnData(), std::back_inserter(feature_domains),
                           model::CreateValueRange);
    return feature_domains;
}

std::vector<EncodedNAR> DES::GetRandomPopulationInDomains(FeatureDomains const& domains,
                                                          RNG& rng) const {
    std::vector<EncodedNAR> population;
    population.reserve(population_size_);
    std::generate_n(std::back_inserter(population), population_size_,
                    [&]() { return EncodedNAR(domains, typed_relation_.get(), rng); });
    auto compare_by_fitness = [](EncodedNAR const& a, EncodedNAR const& b) {
        return a.GetQualities().fitness > b.GetQualities().fitness;
    };
    std::ranges::stable_sort(population, compare_by_fitness);
    return population;
}

EncodedNAR DES::MutatedIndividual(std::vector<EncodedNAR> const& population, size_t at,
                                  RNG& rng) const {
    MutationFunction diff_func =
            EnumToMutationStrategy(differential_options_.differential_strategy);
    return (*diff_func)(population, at, differential_options_, rng);
}

unsigned long long DES::ExecuteInternal() {
    rng_.SetSeed(seed_);
    auto const start_time = std::chrono::system_clock::now();

    FeatureDomains feature_domains = FindFeatureDomains(typed_relation_.get());
    std::vector<EncodedNAR> population = GetRandomPopulationInDomains(feature_domains, rng_);

    for (unsigned i = 0; i < num_evaluations_; ++i) {
        size_t candidate_i = i % population_size_;
        EncodedNAR mutant = MutatedIndividual(population, candidate_i, rng_);
        NAR mutant_decoded = mutant.SetQualities(feature_domains, typed_relation_.get(), rng_);
        double candidate_fitness = population[candidate_i].GetQualities().fitness;
        auto mutant_qualities = mutant_decoded.GetQualities();
        if (mutant_qualities.fitness > candidate_fitness) {
            population[candidate_i] = std::move(mutant);
            if (mutant_qualities.support > minsup_ && mutant_qualities.confidence > minconf_) {
                nar_collection_.emplace_back(std::move(mutant_decoded));
            }
        }
    }

    auto compare_by_fitness = [](const NAR& a, const NAR& b) -> bool {
        return a.GetQualities().fitness > b.GetQualities().fitness;
    };
    std::ranges::sort(nar_collection_, compare_by_fitness);

    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
    return elapsed_milliseconds.count();
}

}  // namespace algos::des
