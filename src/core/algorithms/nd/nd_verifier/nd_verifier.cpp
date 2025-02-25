#include "algorithms/nd/nd_verifier/nd_verifier.h"

#include <bits/chrono.h>  // for durati...
#include <cstddef>        // for size_t
#include <functional>     // for function
#include <stdexcept>      // for runtim...
#include <string>         // for to_string
#include <string_view>    // for basic_...
#include <unordered_set>  // for unorde...
#include <vector>         // for vector

#include <easylogging++.h>  // for Writer

#include "algorithm.h"                                         // for Algorithm
#include "algorithms/nd/nd_verifier/util/stats_calculator.h"   // for StatsC...
#include "algorithms/nd/nd_verifier/util/value_combination.h"  // for ValueC...
#include "algorithms/nd/nd_verifier/util/vector_to_string.h"   // for Vector...
#include "common_option.h"                                     // for Common...
#include "config/descriptions.h"                               // for kDNDWe...
#include "config/equal_nulls/option.h"                         // for kEqual...
#include "config/indices/option.h"                             // for Indice...
#include "config/names.h"                                      // for kWeight
#include "config/option.h"                                     // for Option
#include "config/option_using.h"                               // for DESBOR...
#include "config/tabular_data/input_table/option.h"            // for kTableOpt
#include "indices/type.h"                                      // for Indice...
#include "model/table/column_layout_typed_relation_data.h"     // for Column...
#include "model/table/typed_column_data.h"                     // for TypedC...
#include "model/types/builtin.h"                               // for TypeId
#include "nd/nd.h"                                             // for Weight...
#include "table/idataset_stream.h"                             // for IDatas...
#include "table/relational_schema.h"                           // for Relati...
#include "util/timed_invoke.h"                                 // for TimedI...

namespace algos {
namespace nd_verifier {
namespace util {
class Highlight;
}
}  // namespace nd_verifier
}  // namespace algos

namespace algos::nd_verifier {

NDVerifier::NDVerifier() : Algorithm({}) {
    RegisterOptions();
    MakeOptionsAvailable({config::kTableOpt.GetName(), config::kEqualNullsOpt.GetName()});
}

void NDVerifier::RegisterOptions() {
    DESBORDANTE_OPTION_USING;

    auto get_schema_cols = [this]() { return typed_relation_->GetSchema()->GetNumColumns(); };

    RegisterOption(config::kTableOpt(&input_table_));
    RegisterOption(config::kEqualNullsOpt(&is_null_equal_null_));
    RegisterOption(config::kLhsIndicesOpt(&lhs_indices_, get_schema_cols));
    RegisterOption(config::kRhsIndicesOpt(&rhs_indices_, get_schema_cols));
    RegisterOption(Option<model::WeightType>(&weight_, kWeight, kDNDWeight, 1));
}

void NDVerifier::LoadDataInternal() {
    typed_relation_ =
            model::ColumnLayoutTypedRelationData::CreateFrom(*input_table_, is_null_equal_null_);
    input_table_->Reset();
    if (typed_relation_->GetColumnData().empty()) {
        throw std::runtime_error("Got an empty dataset: ND verifying is meaningless.");
    }
}

void NDVerifier::MakeExecuteOptsAvailable() {
    MakeOptionsAvailable({config::kLhsIndicesOpt.GetName(), config::kRhsIndicesOpt.GetName(),
                          config::names::kWeight});
}

unsigned long long NDVerifier::ExecuteInternal() {
    LOG(INFO) << "Parameters of NDVerifier:";
    LOG(INFO) << "\tInput table: " << input_table_->GetRelationName();
    LOG(INFO) << "\tNull equals null: " << is_null_equal_null_;
    LOG(INFO) << "\tLhs indices: " << util::VectorToString(lhs_indices_);
    LOG(INFO) << "\tRhs indices: " << util::VectorToString(rhs_indices_);
    LOG(INFO) << "\tWeight: " << weight_;

    auto verification_time = ::util::TimedInvoke(&NDVerifier::VerifyND, this);

    LOG(DEBUG) << "ND verification took " << std::to_string(verification_time) << "ms";

    auto stats_calculation_time = ::util::TimedInvoke(&NDVerifier::CalculateStats, this);

    LOG(DEBUG) << "Statistics calculation took " << std::to_string(stats_calculation_time) << "ms";

    return verification_time + stats_calculation_time;
}

bool NDVerifier::NDHolds() const {
    return stats_calculator_.GetRealWeight() <= weight_;
}

void NDVerifier::ResetState() {
    stats_calculator_ = util::StatsCalculator{};
}

void NDVerifier::AddVCToValues(
        std::shared_ptr<std::vector<util::ValueCombination>> values,
        std::shared_ptr<std::vector<size_t>> row,
        std::vector<std::pair<model::TypeId, std::byte const*>> const& typed_data,
        bool is_null) const {
    util::ValueCombination vc{typed_data};

    size_t index{values->size()};
    if (is_null && !is_null_equal_null_) {
        // If not null_eq_null, every value with null will be unique
        values->push_back(vc);
    } else {
        for (size_t i{0}; i < values->size(); ++i) {
            if ((*values)[i] == vc) {
                index = i;
                break;
            }
        }

        if (index == values->size()) {  // wasn`t in values
            values->push_back(vc);
        }
    }
    row->push_back(index);
}

NDVerifier::CombinedValuesType NDVerifier::CombineValues(
        config::IndicesType const& col_idxs) const {
    auto values = std::make_shared<std::vector<util::ValueCombination>>();
    auto row = std::make_shared<std::vector<size_t>>();

    for (size_t row_idx{0}; row_idx < typed_relation_->GetNumRows(); ++row_idx) {
        std::vector<std::pair<model::TypeId, std::byte const*>> typed_data;
        bool was_null = false;
        for (auto col_idx_pt{col_idxs.begin()}; col_idx_pt != col_idxs.end(); ++col_idx_pt) {
            model::TypedColumnData const& col_data = typed_relation_->GetColumnData(*col_idx_pt);
            std::vector<std::byte const*> const& byte_data = col_data.GetData();
            auto type_id = col_data.GetTypeId();

            std::byte const* bytes_ptr = byte_data[row_idx];
            if (bytes_ptr == nullptr) {
                LOG(INFO) << "WARNING: Cell (" << *col_idx_pt << ", " << row_idx << ") is empty";
                was_null = true;
            }

            typed_data.emplace_back(std::move(type_id), bytes_ptr);
        }

        AddVCToValues(values, row, typed_data, was_null);
    }
    return std::make_pair(std::move(values), std::move(row));
}

void NDVerifier::VerifyND() {
    auto local_start_time = std::chrono::system_clock::now();
    auto [lhs_values, combined_lhs] = CombineValues(lhs_indices_);
    auto [rhs_values, combined_rhs] = CombineValues(rhs_indices_);

    LOG(DEBUG) << "Values combination took "
               << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                                         std::chrono::system_clock::now() - local_start_time)
                                         .count())
               << "ms";

    local_start_time = std::chrono::system_clock::now();
    std::unordered_map<size_t, std::unordered_set<size_t>> value_deps{};

    for (size_t i{0}; i < combined_lhs->size(); ++i) {
        auto lhs_code = (*combined_lhs)[i];
        auto rhs_code = (*combined_rhs)[i];

        if (value_deps.find(lhs_code) == value_deps.end()) {
            value_deps.emplace(lhs_code, std::unordered_set<size_t>({rhs_code}));
        } else {
            value_deps[lhs_code].insert(rhs_code);
        }
    }
    LOG(DEBUG) << "Value deps calculation took "
               << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                                         std::chrono::system_clock::now() - local_start_time)
                                         .count())
               << "ms";

    stats_calculator_ = util::StatsCalculator(std::move(value_deps), std::move(lhs_values),
                                              std::move(rhs_values), std::move(combined_lhs),
                                              std::move(combined_rhs));
}

[[nodiscard]] std::vector<util::Highlight> const& NDVerifier::GetHighlights() const {
    return stats_calculator_.GetHighlights();
}

[[nodiscard]] model::WeightType NDVerifier::GetGlobalMinWeight() const {
    return stats_calculator_.GetGlobalMinWeight();
}

[[nodiscard]] model::WeightType NDVerifier::GetRealWeight() const {
    return stats_calculator_.GetRealWeight();
}

[[nodiscard]] std::unordered_map<std::string, size_t> NDVerifier::GetLhsFrequencies() const {
    return stats_calculator_.GetLhsFrequencies();
}

[[nodiscard]] std::unordered_map<std::string, size_t> NDVerifier::GetRhsFrequencies() const {
    return stats_calculator_.GetRhsFrequencies();
}

}  // namespace algos::nd_verifier
