#include "config/tabular_data/crud_operations/insert/option.h"

#include <variant>                          // for variant

#include "common_option.h"                  // for CommonOption
#include "config/names_and_descriptions.h"
#include "tabular_data/input_table_type.h"  // for InputTable

namespace config {
using names::kInsertStatements, descriptions::kDInsertStatements;
extern CommonOption<InputTable> const kInsertStatementsOpt = {kInsertStatements, kDInsertStatements,
                                                              InputTable{}};
}  // namespace config
