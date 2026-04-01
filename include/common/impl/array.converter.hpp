#pragma once

#include "../array.hpp"
#include "exception.hpp"

namespace json
{

template <ext::has_from_json_array T>
requires(!_utils::support_as_ref<T>)
inline T array::as() const&
{
    T t { };
    if (!ext::jsonization_wrapper<T>::from_json(*this, t)) {
        throw exception { };
    }
    return t;
}

template <_utils::support_as_ref T>
inline const T& array::as() const&
{
    if constexpr (std::is_same_v<T, array>) {
        return *this;
    }
    else {
        static_assert(false);
    }
}

template <_utils::support_as_ref T>
inline T& array::as() &
{
    if constexpr (std::is_same_v<T, array>) {
        return *this;
    }
    else {
        static_assert(false);
    }
}

template <typename T>
inline T array::as() &&
{
    if constexpr (std::is_same_v<T, array>) {
        return std::move(*this);
    }
    else if constexpr (ext::has_from_json_array<T>) {
        T t { };
        if (!ext::jsonization_wrapper<T>::from_json(std::move(*this), t)) {
            throw exception { };
        }
        return t;
    }
    else {
        static_assert(false);
    }
}

template <typename T>
inline array::operator T() const&
{
    return as<T>();
}

template <typename T>
inline array::operator T() &&
{
    return std::move(*this).as<T>();
}

}
