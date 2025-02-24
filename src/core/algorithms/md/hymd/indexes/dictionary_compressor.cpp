#include "algorithms/md/hymd/indexes/dictionary_compressor.h"

#include <cstddef>                                      // for size_t
#include <utility>                                      // for move

#include "md/hymd/compressed_record.h"                  // for CompressedRecord
#include "md/hymd/indexes/keyed_position_list_index.h"  // for KeyedPosition...
#include "model/index.h"                                // for Index
#include "util/desbordante_assume.h"                    // for DESBORDANTE_A...

namespace algos::hymd::indexes {

DictionaryCompressor::DictionaryCompressor(std::size_t attribute_num) : plis_(attribute_num) {}

void DictionaryCompressor::AddRecord(std::vector<GlobalValueIdentifier> const& record) {
    std::size_t const record_size = record.size();
    DESBORDANTE_ASSUME(record_size == plis_.size());
    ++records_processed_;
    CompressedRecord rec;
    rec.reserve(record_size);
    for (model::Index i = 0; i != record_size; ++i) {
        rec.push_back(plis_[i].AddNextValue(record[i]));
    }
    records_.push_back(std::move(rec));
}

}  // namespace algos::hymd::indexes
