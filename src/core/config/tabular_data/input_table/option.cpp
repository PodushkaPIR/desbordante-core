#include "config/tabular_data/input_table/option.h"

#include <memory>                           // for operator==
#include <optional>                         // for nullopt
#include <variant>                          // for variant

#include "common_option.h"                  // for CommonOption
#include "config/names_and_descriptions.h"
#include "exceptions.h"                     // for ConfigurationError
#include "tabular_data/input_table_type.h"  // for InputTable

namespace config {
using names::kTable, descriptions::kDTable;
extern CommonOption<InputTable> const kTableOpt = {
        kTable, kDTable, std::nullopt, nullptr, [](InputTable const& table) {
            // Shouldn't happen normally.
            if (table == nullptr) throw ConfigurationError("Table must be a valid pointer!");
        }};
}  // namespace config
