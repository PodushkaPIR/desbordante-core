//
// Created by Ilya Vologin
// https://github.com/cupertank
//

#pragma once

#include <memory>    // for unique_ptr
#include <stddef.h>  // for size_t
#include <vector>    // for vector

#include "column_data.h"    // for ColumnData
#include "relation_data.h"  // for RelationData

class RelationalSchema;

namespace model {
class IDatasetStream;
}

class ColumnLayoutRelationData final : public RelationData {
public:
    static constexpr int kNullValueId = -1;

    using RelationData::AbstractRelationData;

    [[nodiscard]] size_t GetNumRows() const final {
        if (column_data_.empty()) {
            return 0;
        }
        return column_data_[0].GetProbingTable().size();
    }

    [[nodiscard]] std::vector<int> GetTuple(int tuple_index) const;

    static std::unique_ptr<ColumnLayoutRelationData> CreateFrom(model::IDatasetStream& data_stream,
                                                                bool is_null_eq_null);
};
