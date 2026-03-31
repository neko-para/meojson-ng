#pragma once

#include <algorithm>
#include <iterator>

#include "../array.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

template <typename T>
inline std::optional<T> array::find(size_t pos) const&
{
    if (!contains(pos)) {
        return std::nullopt;
    }
    if (_data[pos].is<T>()) {
        return _data[pos].as<T>();
    }
    else {
        return std::nullopt;
    }
}

template <typename T>
inline std::optional<T> array::find(size_t pos) &&
{
    if (!contains(pos)) {
        return std::nullopt;
    }
    if (_data[pos].is<T>()) {
        return std::move(_data[pos]).as<T>();
    }
    else {
        return std::nullopt;
    }
}

inline array array::operator+(const array& rhs) const&
{
    array arr;
    arr.reserve(size() + rhs.size());
    std::copy(begin(), end(), std::back_insert_iterator<array>(arr));
    std::copy(rhs.begin(), rhs.end(), std::back_insert_iterator<array>(arr));
    return arr;
}

inline array array::operator+(array&& rhs) const&
{
    array arr;
    arr.reserve(size() + rhs.size());
    std::copy(begin(), end(), std::back_insert_iterator<array>(arr));
    std::move(rhs.begin(), rhs.end(), std::back_insert_iterator<array>(arr));
    return arr;
}

inline array array::operator+(const array& rhs) &&
{
    *this += rhs;
    return std::move(*this);
}

inline array array::operator+(array&& rhs) &&
{
    *this += std::move(rhs);
    return std::move(*this);
}

inline array& array::operator+=(const array& rhs)
{
    reserve(size() + rhs.size());
    std::copy(rhs.begin(), rhs.end(), std::back_insert_iterator<array>(*this));
    return *this;
}

inline array& array::operator+=(array&& rhs)
{
    reserve(size() + rhs.size());
    std::move(rhs.begin(), rhs.end(), std::back_insert_iterator<array>(*this));
    return *this;
}

}
