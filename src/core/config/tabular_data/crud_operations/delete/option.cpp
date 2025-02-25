#include "config/tabular_data/crud_operations/delete/option.h"

#include <variant>  // for variant

#include "common_option.h"  // for CommonOption
#include "config/names_and_descriptions.h"

namespace config {
using names::kDeleteStatements, descriptions::kDDeleteStatements;
extern CommonOption<std::unordered_set<size_t>> const kDeleteStatementsOpt = {
        kDeleteStatements, kDDeleteStatements, std::unordered_set<size_t>()};
}  // namespace config
