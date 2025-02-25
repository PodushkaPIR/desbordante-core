#include "algorithms/fd/fd_verifier/fd_verifier.h"

#include <bits/chrono.h>  // for duration_cast
#include <functional>     // for function
#include <memory>         // for shared_ptr, uni...
#include <stdexcept>      // for runtime_error

#include <boost/type_index/type_index_facade.hpp>  // for operator==

#include "algorithm.h"                  // for Algorithm
#include "common_option.h"              // for CommonOption
#include "config/equal_nulls/option.h"  // for kEqualNullsOpt
#include "config/indices/option.h"      // for IndicesOption
#include "config/names_and_descriptions.h"
#include "config/option_using.h"                      // for DESBORDANTE_OPT...
#include "config/tabular_data/input_table/option.h"   // for kTableOpt
#include "fd/fd_verifier/stats_calculator.h"          // for StatsCalculator
#include "indices/type.h"                             // for IndicesType
#include "table/column_data.h"                        // for ColumnData
#include "table/column_layout_relation_data.h"        // for ColumnLayoutRel...
#include "table/column_layout_typed_relation_data.h"  // for ColumnLayoutTyp...
#include "table/idataset_stream.h"                    // for IDatasetStream
#include "table/relational_schema.h"                  // for RelationalSchema

namespace algos::fd_verifier {

FDVerifier::FDVerifier() : Algorithm({}) {
    RegisterOptions();
    MakeOptionsAvailable({config::kTableOpt.GetName(), config::kEqualNullsOpt.GetName()});
}

void FDVerifier::RegisterOptions() {
    DESBORDANTE_OPTION_USING;

    auto get_schema_cols = [this]() { return relation_->GetSchema()->GetNumColumns(); };

    RegisterOption(config::kTableOpt(&input_table_));
    RegisterOption(config::kEqualNullsOpt(&is_null_equal_null_));
    RegisterOption(config::kLhsIndicesOpt(&lhs_indices_, get_schema_cols));
    RegisterOption(config::kRhsIndicesOpt(&rhs_indices_, get_schema_cols));
}

void FDVerifier::MakeExecuteOptsAvailable() {
    using namespace config::names;

    MakeOptionsAvailable({config::kLhsIndicesOpt.GetName(), config::kRhsIndicesOpt.GetName()});
}

void FDVerifier::LoadDataInternal() {
    relation_ = ColumnLayoutRelationData::CreateFrom(*input_table_, is_null_equal_null_);
    input_table_->Reset();
    if (relation_->GetColumnData().empty()) {
        throw std::runtime_error("Got an empty dataset: FD verifying is meaningless.");
    }
    typed_relation_ =
            model::ColumnLayoutTypedRelationData::CreateFrom(*input_table_, is_null_equal_null_);
}

unsigned long long FDVerifier::ExecuteInternal() {
    auto start_time = std::chrono::system_clock::now();

    stats_calculator_ = std::make_unique<StatsCalculator>(relation_, typed_relation_, lhs_indices_,
                                                          rhs_indices_);

    VerifyFD();
    SortHighlightsByProportionDescending();
    stats_calculator_->PrintStatistics();

    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
    return elapsed_milliseconds.count();
}

void FDVerifier::VerifyFD() const {
    std::shared_ptr<model::PLI const> lhs_pli = CalculatePLI(lhs_indices_);
    std::shared_ptr<model::PLI const> rhs_pli = CalculatePLI(rhs_indices_);

    std::unique_ptr<model::PLI const> intersection_pli = lhs_pli->Intersect(rhs_pli.get());
    if (lhs_pli->GetNumCluster() == intersection_pli->GetNumCluster()) {
        return;
    }

    stats_calculator_->CalculateStatistics(lhs_pli.get(), rhs_pli.get());
}

std::shared_ptr<model::PLI const> FDVerifier::CalculatePLI(
        config::IndicesType const& indices) const {
    std::shared_ptr<model::PLI const> pli = relation_->GetColumnData(indices[0]).GetPliOwnership();

    for (size_t i = 1; i < indices.size(); ++i) {
        pli = pli->Intersect(relation_->GetColumnData(indices[i]).GetPositionListIndex());
    }
    return pli;
}

void FDVerifier::SortHighlightsByProportionAscending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsByProportionAscending());
}

void FDVerifier::SortHighlightsByProportionDescending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsByProportionDescending());
}

void FDVerifier::SortHighlightsByNumAscending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsByNumAscending());
}

void FDVerifier::SortHighlightsByNumDescending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsByNumDescending());
}

void FDVerifier::SortHighlightsBySizeAscending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsBySizeAscending());
}

void FDVerifier::SortHighlightsBySizeDescending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(StatsCalculator::CompareHighlightsBySizeDescending());
}

void FDVerifier::SortHighlightsByLhsAscending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(stats_calculator_->CompareHighlightsByLhsAscending());
}

void FDVerifier::SortHighlightsByLhsDescending() const {
    assert(stats_calculator_);
    stats_calculator_->SortHighlights(stats_calculator_->CompareHighlightsByLhsDescending());
}

}  // namespace algos::fd_verifier
