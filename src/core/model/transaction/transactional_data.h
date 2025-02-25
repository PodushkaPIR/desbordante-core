#pragma once

#include <memory>         // for unique_ptr
#include <stddef.h>       // for size_t
#include <string>         // for string
#include <unordered_map>  // for unordered_map
#include <utility>        // for move
#include <vector>         // for vector

#include "itemset.h"  // for Itemset

namespace model {
class IDatasetStream;
}

namespace model {

class TransactionalData {
private:
    std::vector<std::string> item_universe_;
    std::unordered_map<size_t, Itemset> transactions_;

    TransactionalData(std::vector<std::string> item_universe,
                      std::unordered_map<size_t, Itemset> transactions)
        : item_universe_(std::move(item_universe)), transactions_(std::move(transactions)) {}

public:
    TransactionalData() = delete;

    TransactionalData(TransactionalData const&) = delete;
    TransactionalData& operator=(TransactionalData const&) = delete;

    TransactionalData(TransactionalData&& other) = default;
    TransactionalData& operator=(TransactionalData&& other) = default;

    std::vector<std::string> const& GetItemUniverse() const noexcept {
        return item_universe_;
    }

    std::unordered_map<size_t, Itemset> const& GetTransactions() const noexcept {
        return transactions_;
    }

    size_t GetUniverseSize() const noexcept {
        return item_universe_.size();
    }

    size_t GetNumTransactions() const noexcept {
        return transactions_.size();
    }

    static std::unique_ptr<TransactionalData> CreateFromSingular(IDatasetStream& data_stream,
                                                                 size_t tid_col_index = 0,
                                                                 size_t item_col_index = 1);

    static std::unique_ptr<TransactionalData> CreateFromTabular(IDatasetStream& data_stream,
                                                                bool has_tid);
};

}  // namespace model
