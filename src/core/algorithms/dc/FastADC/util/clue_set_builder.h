#pragma once

#include <vector>                                     // for vector

#include "dc/FastADC/util/common_clue_set_builder.h"  // for ClueSet

namespace algos { namespace fastadc { class PliShard; } }
namespace algos { namespace fastadc { struct PredicatePacks; } }

namespace algos::fastadc {

ClueSet BuildClueSet(std::vector<PliShard> const& pliShards, PredicatePacks const& packs);

}  // namespace algos::fastadc
