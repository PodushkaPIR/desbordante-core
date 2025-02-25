#pragma once

#include <limits>       // for numeric_limits
#include <string_view>  // for string_view

#include "config/common_option.h"                   // for CommonOption
#include "config/tabular_data/input_tables_type.h"  // for InputTables
#include "option.h"                                 // for Option
#include "tabular_data/input_tables/option.h"

namespace config {

struct InputTablesOption {
    using TableIndex = InputTables::size_type;

    InputTablesOption(std::string_view name, std::string_view description);

    [[nodiscard]] std::string_view GetName() const;

    /// Verify, that at least one table is passed and no more than the limit, if specified.
    [[nodiscard]] Option<InputTables> operator()(
            InputTables* value_ptr,
            TableIndex tables_limit = std::numeric_limits<TableIndex>::max()) const;

private:
    CommonOption<InputTables> const common_option_;
};

extern InputTablesOption const kTablesOpt;

}  // namespace config
