#pragma once

#include <bit>          // for rotl
#include <cstddef>      // for size_t
#include <functional>   // for equal_to
#include <memory>       // for shared_ptr, __shared_ptr_access
#include <string_view>  // for hash
#include <utility>      // for move

#include "simple_cc.h"                 // for SimpleCC, hash
#include "table/arity_index.h"         // for ArityIndex
#include "table/column_combination.h"  // for ColumnCombination

namespace algos::faida {

class SimpleIND {
private:
    std::shared_ptr<SimpleCC> const left_;
    std::shared_ptr<SimpleCC> const right_;

public:
    SimpleIND(std::shared_ptr<SimpleCC> left, std::shared_ptr<SimpleCC> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    bool operator==(SimpleIND const& other) const {
        return *(this->left_) == *(other.left_) && *(this->right_) == *(other.right_);
    }

    bool operator!=(SimpleIND const& other) const {
        return !(*this == other);
    }

    bool operator<(SimpleIND const& other) const;

    bool StartsWith(SimpleIND const& other) const {
        return this->left_->StartsWith(*other.left_) && this->right_->StartsWith(*other.right_);
    }

    std::shared_ptr<SimpleCC> const& Left() const {
        return left_;
    }

    std::shared_ptr<SimpleCC> const& Right() const {
        return right_;
    }

    model::ArityIndex GetArity() const {
        return left_->GetArity();
    }
};

}  // namespace algos::faida

template <>
struct std::hash<algos::faida::SimpleIND> {
    size_t operator()(algos::faida::SimpleIND const& ind) const {
        size_t seed = 0;
        seed ^= reinterpret_cast<size_t>(ind.Left().get());
        seed = std::rotl(seed, 11) ^ reinterpret_cast<size_t>(ind.Right().get());
        return seed;
    }
};

template <>
struct std::hash<algos::faida::SimpleIND const*> {
    size_t operator()(algos::faida::SimpleIND const* ind) const {
        size_t seed = 0;
        seed ^= std::hash<algos::faida::SimpleCC>{}(*(ind->Left()));
        seed = std::rotl(seed, 11) ^ std::hash<algos::faida::SimpleCC>{}(*(ind->Right()));
        return seed;
    }
};

template <>
struct std::equal_to<algos::faida::SimpleIND const*> {
    bool operator()(algos::faida::SimpleIND const* a, algos::faida::SimpleIND const* b) const {
        return *a == *b;
    }
};
