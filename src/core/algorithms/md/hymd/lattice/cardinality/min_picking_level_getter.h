#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#include <boost/dynamic_bitset/dynamic_bitset.hpp>

#include "algorithms/md/hymd/lattice/cardinality/one_by_one_min_picker.h"
#include "algorithms/md/hymd/lattice/level_getter.h"
#include "algorithms/md/hymd/lattice/md_lattice.h"
#include "algorithms/md/hymd/md_lhs.h"
#include "md/hymd/lattice/validation_info.h"

namespace algos::hymd::lattice::cardinality {

class MinPickingLevelGetter final : public LevelGetter {
private:
    using MinPickerType = OneByOnePicker;
    std::size_t const column_matches_number_;
    MinPickerType min_picker_;
    std::unordered_map<MdLhs, boost::dynamic_bitset<>> picked_;

    std::vector<ValidationInfo> GetPendingGroupedMinimalLhsMds(
            std::vector<MdLattice::MdVerificationMessenger>& level_lattice_info) final;

    // false simulates Metanome, true is faster, but the order changes may lead to
    // unpredictable effects on runtime
    static constexpr bool kEraseEmptyKeepOrder = false;

public:
    MinPickingLevelGetter(MdLattice* lattice)
        : LevelGetter(lattice),
          column_matches_number_(lattice->GetColMatchNumber()),
          min_picker_() {}
};

}  // namespace algos::hymd::lattice::cardinality
