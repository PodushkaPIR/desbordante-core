#pragma once

// see ../algorithms/cfd/LICENSE

#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>
#include <bitset>
#include <iostream>
#include <map>

std::vector<int> Range(int, int, int = 1);
std::vector<int> Iota(int);

template <typename T>
typename T::value_type product(const T& items) {
    typename T::value_type prod{};
    for (const typename T::value_type& i : items) {
        prod *= i;
    }
    return prod;
}

template<typename T>
bool IsSubsetOf(const T& sub, const T& super) {
    return std::includes(super.begin(), super.end(), sub.begin(), sub.end());
}

template<typename T>
T Subset(const T& items, const typename T::value_type leave_out) {
    if (items.size() == 1) return T();
    T sub;
    sub.reserve(items.size() - 1);
    for (unsigned mi = 0; mi < items.size(); mi++) {
        if (items[mi] != leave_out) {
            sub.push_back(items[mi]);
        }
    }
    return sub;
}

template<typename T>
void InsertSorted(const T& in, const typename T::value_type item, T& out) {
    auto it = in.begin();
    while (it != in.end() && *it < item) { it++; }
    if (it != in.begin()) {
        out.insert(out.begin(), in.begin(), it);
    }
    int offset = (int)(it - in.begin());
    out.insert(out.begin() + offset, item);
    if (in.size() && it != in.end()) {
        out.insert(out.begin() + offset + 1, it, in.end());
    }
}

template<typename T>
T Intersection(const T& lhs, const T& rhs) {
    T isect(std::min(lhs.size(), rhs.size()));
    auto it = std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), isect.begin());
    isect.resize((int)(it - isect.begin()));
    return isect;
}

template<typename T>
T SetDiff(const T& lhs, const T& rhs) {
    T res;
    std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(res, res.begin()));
    return res;
}

template<typename T>
T* Join(const T* lhs, const T* rhs) {
    T* uni = new T(lhs->size() + rhs->size());
    auto it = std::set_union(lhs->begin(), lhs->end(), rhs->begin(), rhs->end(), uni->begin());
    uni->resize((int)(it - uni->begin()));
    return uni;
}

template<typename T>
T Join(const T& lhs, const T& rhs) {
    T uni(lhs.size() + rhs.size());
    auto it = std::set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), uni.begin());
    uni.resize((int)(it - uni.begin()));
    return uni;
}

template<typename T>
T Join(const T& lhs, const typename T::value_type& rhs) {
    T res;
    res.reserve(lhs.size() + 1);
    InsertSorted(lhs, rhs, res);
    return res;
}

template<typename T>
T* Join(const T* lhs, const typename T::value_type& rhs_item) {
    T* res = new T();
    res->reserve(lhs->size() + 1);
    InsertSorted(*lhs, rhs_item, *res);
    return res;
}

template<typename T>
T Remove(const T& lhs, const typename T::value_type& rhs_item) {
    T res;
    res.reserve(lhs.size() - 1);
    const auto& lower = std::lower_bound(lhs.begin(), lhs.end(), rhs_item);
    res.insert(res.begin(), lhs.begin(), lower);
    res.insert(res.begin() + (lower - lhs.begin()), lower + 1, lhs.end());
    return res;
}

template <typename T>
bool Contains(const T& collection, const typename T::value_type& item) {
    return std::find(collection.begin(), collection.end(), item) != collection.end();
}

template <typename T, typename S>
T Projection(const T& collection, const S& indices) {
    T res;
    for (int i : indices) {
        res.push_back(collection[i]);
    }
    return res;
}

template<typename T>
std::vector<T> Split(const T& collection, const typename T::value_type& spl) {
    std::vector<T> res(1);
    for (int i : collection) {
        if (i == spl) {
            res.push_back(T());
        }
        else {
            res.back().push_back(i);
        }
    }
    res.pop_back();
    return res;
}

template <typename T>
T GetMaxElem(const std::vector<std::pair<T, int> >& collection) {
    int max = -1;
    size_t maxI = 0;
    for (size_t i = 0; i < collection.size(); i++) {
        const auto& elem = collection[i];
        if (elem.second > max) {
            max = elem.second;
            maxI = i;
        }
    }
    return collection[maxI].first;
}

template <typename T>
void Shuffle(T& collection) {
    std::mt19937 gen(time(0));
    std::shuffle(collection.begin(), collection.end(), gen);
}