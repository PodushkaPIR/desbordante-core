#include "algorithms/fd/pfd_verifier/pfd_verifier.h"

#include <bits/chrono.h>  // for duration_cast
#include <functional>     // for function
#include <memory>         // for shared_ptr, __sh...
#include <stdexcept>      // for runtime_error

#include "algorithms/algorithm.h"                    // for Algorithm
#include "common_option.h"                           // for CommonOption
#include "config/equal_nulls/option.h"               // for kEqualNullsOpt
#include "config/error_measure/option.h"             // for kPfdErrorMeasureOpt
#include "config/indices/option.h"                   // for IndicesOption
#include "config/names.h"                            // for kEqualNulls, kLh...
#include "config/tabular_data/input_table/option.h"  // for kTableOpt
#include "fd/pfd_verifier/pfd_stats_calculator.h"    // for PFDStatsCalculator
#include "fd/tane/enums.h"                           // for PfdErrorMeasure
#include "indices/type.h"                            // for IndicesType
#include "table/column_data.h"                       // for ColumnData
#include "table/column_layout_relation_data.h"       // for ColumnLayoutRela...
#include "table/relational_schema.h"                 // for RelationalSchema

namespace algos {

void PFDVerifier::RegisterOptions() {
    auto get_schema_cols = [this]() { return relation_->GetSchema()->GetNumColumns(); };
    RegisterOption(config::kTableOpt(&input_table_));
    RegisterOption(config::kEqualNullsOpt(&is_null_equal_null_));
    RegisterOption(config::kLhsIndicesOpt(&lhs_indices_, get_schema_cols));
    RegisterOption(config::kRhsIndicesOpt(&rhs_indices_, get_schema_cols));
    RegisterOption(config::kPfdErrorMeasureOpt(&error_measure_));
}

void PFDVerifier::MakeExecuteOptsAvailable() {
    using namespace config::names;
    MakeOptionsAvailable({kLhsIndices, kRhsIndices, kPfdErrorMeasure});
}

void PFDVerifier::LoadDataInternal() {
    relation_ = ColumnLayoutRelationData::CreateFrom(*input_table_, is_null_equal_null_);
    if (relation_->GetColumnData().empty()) {
        throw std::runtime_error("Got an empty dataset: pFD verifying is meaningless.");
    }
}

unsigned long long PFDVerifier::ExecuteInternal() {
    auto start_time = std::chrono::system_clock::now();
    stats_calculator_ = std::make_unique<PFDStatsCalculator>(relation_, error_measure_);
    VerifyPFD();
    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
    return elapsed_milliseconds.count();
}

void PFDVerifier::VerifyPFD() const {
    std::shared_ptr<model::PLI const> lhs_pli = CalculatePLI(lhs_indices_);
    std::shared_ptr<model::PLI const> rhs_pli = CalculatePLI(rhs_indices_);
    std::unique_ptr<model::PLI const> intersection_pli = lhs_pli->Intersect(rhs_pli.get());
    stats_calculator_->CalculateStatistics(lhs_pli.get(), intersection_pli.get());
}

std::shared_ptr<model::PLI const> PFDVerifier::CalculatePLI(
        config::IndicesType const& indices) const {
    std::shared_ptr<model::PLI const> pli = relation_->GetColumnData(indices[0]).GetPliOwnership();
    for (size_t i = 1; i < indices.size(); ++i) {
        pli = pli->Intersect(relation_->GetColumnData(indices[i]).GetPositionListIndex());
    }
    return pli;
}

PFDVerifier::PFDVerifier() : Algorithm({}) {
    using namespace config::names;
    RegisterOptions();
    MakeOptionsAvailable({kTable, kEqualNulls});
}

}  // namespace algos
