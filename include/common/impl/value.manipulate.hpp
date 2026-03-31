#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

template <typename T>
inline std::optional<T> value::find(size_t pos) const&
{
    if (!is_array()) {
        return std::nullopt;
    }
    return as_array_unsafe().find(pos);
}

template <typename T>
inline std::optional<T> value::find(size_t pos) &&
{
    if (!is_array()) {
        return std::nullopt;
    }
    return std::move(*this).as_array_unsafe().find(pos);
}

template <typename T, all_object_key K>
inline std::optional<T> value::find(const K& key) const&
{
    if (!is_object()) {
        return std::nullopt;
    }
    return as_object_unsafe().find(key);
}

template <typename T, all_object_key K>
inline std::optional<T> value::find(const K& key) &&
{
    if (!is_object()) {
        return std::nullopt;
    }
    return std::move(*this).as_object_unsafe().find(key);
}

inline value value::operator+(const array& rhs) const&
{
    return as_array() + rhs;
}

inline value value::operator+(array&& rhs) const&
{
    return as_array() + std::move(rhs);
}

inline value value::operator+(const array& rhs) &&
{
    return std::move(*this).as_array() + rhs;
}

inline value value::operator+(array&& rhs) &&
{
    return std::move(*this).as_array() + std::move(rhs);
}

inline value& value::operator+=(const array& rhs)
{
    as_array() += rhs;
    return *this;
}

inline value& value::operator+=(array&& rhs)
{
    as_array() += std::move(rhs);
    return *this;
}

inline value value::operator|(const object& rhs) const&
{
    return as_object() | rhs;
}

inline value value::operator|(object&& rhs) const&
{
    return as_object() | std::move(rhs);
}

inline value value::operator|(const object& rhs) &&
{
    return std::move(*this).as_object() | rhs;
}

inline value value::operator|(object&& rhs) &&
{
    return std::move(*this).as_object() | std::move(rhs);
}

inline value& value::operator|=(const object& rhs)
{
    as_object() |= rhs;
    return *this;
}

inline value& value::operator|=(object&& rhs)
{
    as_object() |= std::move(rhs);
    return *this;
}

}
