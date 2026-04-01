#pragma once

#include "../object.hpp"
#include "exception.hpp"

namespace json
{

template <ext::has_from_json_object T>
requires(!_utils::support_as_ref<T>)
inline T object::as() const&
{
    T t { };
    if (!ext::jsonization_wrapper<T>::from_json(*this, t)) {
        throw exception { };
    }
    return t;
}

template <_utils::support_as_ref T>
inline const T& object::as() const&
{
    if constexpr (std::is_same_v<T, object>) {
        return *this;
    }
    else {
        static_assert(false);
    }
}

template <_utils::support_as_ref T>
inline T& object::as() &
{
    if constexpr (std::is_same_v<T, object>) {
        return *this;
    }
    else {
        static_assert(false);
    }
}

template <typename T>
inline T object::as() &&
{
    if constexpr (std::is_same_v<T, object>) {
        return std::move(*this);
    }
    else if constexpr (ext::has_from_json_object<T>) {
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
inline object::operator T() const&
{
    return as<T>();
}

template <typename T>
inline object::operator T() &&
{
    return std::move(*this).as<T>();
}

}
