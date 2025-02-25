#pragma once

#include <cstddef>  // for byte

#include "algorithms/od/fastod/storage/data_frame.h"  // for DataFrame
#include "mixed_type.h"                               // for MixedType
#include "model/types/builtin.h"                      // for TypeId, Compare...
#include "table/typed_column_data.h"                  // for TypedColumnData
#include "type.h"                                     // for Type

namespace algos::fastod {

bool IsUnorderedType(model::TypeId type_id);

model::CompareResult CompareDataAsStrings(std::byte const* left, std::byte const* right,
                                          model::MixedType const* mixed_type);

template <bool IsColumnMixed>
model::CompareResult CompareData(DataFrame::DataAndIndex const& left,
                                 DataFrame::DataAndIndex const& right,
                                 model::TypedColumnData const& column) {
    model::TypeId const left_type_id = column.GetValueTypeId(left.second);
    model::TypeId const right_type_id = column.GetValueTypeId(right.second);

    bool const is_both_types_unordered =
            IsUnorderedType(left_type_id) && IsUnorderedType(right_type_id);

    bool const is_one_type_unordered =
            IsUnorderedType(left_type_id) || IsUnorderedType(right_type_id);

    if (is_both_types_unordered) {
        return model::CompareResult::kEqual;
    }

    if (is_one_type_unordered) {
        return IsUnorderedType(left_type_id) ? model::CompareResult::kLess
                                             : model::CompareResult::kGreater;
    }

    if constexpr (IsColumnMixed) {
        model::MixedType const* mixed_type = column.GetIfMixed();

        return left_type_id == right_type_id
                       ? mixed_type->Compare(left.first, right.first)
                       : CompareDataAsStrings(left.first, right.first, mixed_type);
    } else {
        model::Type const& type = column.GetType();
        return type.Compare(left.first, right.first);
    }
}

}  // namespace algos::fastod
