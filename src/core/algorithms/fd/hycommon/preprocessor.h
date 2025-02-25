#pragma once

#include <stddef.h>  // for size_t
#include <tuple>     // for tuple
#include <vector>    // for vector

#include <boost/dynamic_bitset/dynamic_bitset.hpp>  // for dynamic_bitset

#include "types.h"  // for PLIs, ClusterId

class ColumnLayoutRelationData;

namespace algos::hy::util {

std::vector<ClusterId> SortAndGetMapping(PLIs& plis);
Columns BuildInvertedPlis(PLIs const& plis);
Rows BuildRecordRepresentation(Columns const& inverted_plis);
PLIs BuildPLIs(ColumnLayoutRelationData* relation);

}  // namespace algos::hy::util

namespace algos::hy {

std::tuple<PLIs, Rows, std::vector<ClusterId>> Preprocess(ColumnLayoutRelationData* relation);
boost::dynamic_bitset<> RestoreAgreeSet(boost::dynamic_bitset<> const& as,
                                        std::vector<ClusterId> const& og_mapping, size_t num_cols);

}  // namespace algos::hy
