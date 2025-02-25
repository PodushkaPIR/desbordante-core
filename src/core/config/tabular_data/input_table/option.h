// This option is meant for the common case where an algorithm accepts only one
// table.

#pragma once

#include "config/tabular_data/input_table_type.h"  // for InputTable

namespace config {
template <typename T>
class CommonOption;
}

namespace config {
extern CommonOption<InputTable> const kTableOpt;
}  // namespace config
