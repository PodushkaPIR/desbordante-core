#pragma once

#include <optional>             // for optional, nullopt, nullopt_t

#include "config/error/type.h"  // for ErrorType
#include "enums.h"              // for PfdErrorMeasure, operator+
#include "tane_common.h"        // for TaneCommon

class ColumnData;
namespace model { class PositionListIndex; }

namespace algos {

/** Class for pFD mining with TANE algorithm */
class PFDTane : public tane::TaneCommon {
private:
    PfdErrorMeasure pfd_error_measure_ = +PfdErrorMeasure::per_tuple;
    void RegisterOptions();
    void MakeExecuteOptsAvailableFDInternal() final;
    config::ErrorType CalculateZeroAryFdError(ColumnData const* rhs) override;
    config::ErrorType CalculateFdError(model::PositionListIndex const* lhs_pli,
                                       model::PositionListIndex const* rhs_pli,
                                       model::PositionListIndex const* joint_pli) override;

public:
    PFDTane(std::optional<ColumnLayoutRelationDataManager> relation_manager = std::nullopt);
    static config::ErrorType CalculateZeroAryPFDError(ColumnData const* rhs);
    static config::ErrorType CalculatePFDError(model::PositionListIndex const* x_pli,
                                               model::PositionListIndex const* xa_pli,
                                               PfdErrorMeasure error_measure);
};

}  // namespace algos
