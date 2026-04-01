#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "enum_reflection.hpp"
#include "extends.hpp"

namespace json
{

inline bool value::valid() const noexcept
{
    return _type != value_type::invalid;
}

inline bool value::empty() const noexcept
{
    switch (_type) {
    case value_type::null:
        return true;
    case value_type::string:
        return std::get<std::string>(_data).empty();
    case value_type::array:
        return std::get<array_ptr>(_data)->empty();
    case value_type::object:
        return std::get<object_ptr>(_data)->empty();
    default:
        return false;
    }
}

inline value::value_type value::type() const noexcept
{
    return _type;
}

inline bool value::is_null() const noexcept
{
    return _type == value_type::null;
}

inline bool value::is_boolean() const noexcept
{
    return _type == value_type::boolean;
}

inline bool value::is_number() const noexcept
{
    return _type == value_type::number;
}

inline bool value::is_string() const noexcept
{
    return _type == value_type::string;
}

inline bool value::is_array() const noexcept
{
    return _type == value_type::array;
}

inline bool value::is_object() const noexcept
{
    return _type == value_type::object;
}

template <typename T>
inline bool value::is() const noexcept
{
    if constexpr (std::is_same_v<T, value>) {
        return true;
    }
    else if constexpr (std::is_same_v<T, array>) {
        return is_array();
    }
    else if constexpr (std::is_same_v<T, object>) {
        return is_object();
    }
    else if constexpr (std::is_same_v<T, nullptr_t> || std::is_same_v<T, std::monostate>) {
        return is_null();
    }
    else if constexpr (std::is_same_v<T, bool>) {
        return is_boolean();
    }
    else if constexpr (std::integral<T> || std::floating_point<T>) {
        return is_number();
    }
    else if constexpr (std::is_enum_v<T>) {
        if (is_string()) {
            return _reflection::string_to_enum<T>(as_string_view()).has_value();
        }
        return is_number();
    }
    else if constexpr (std::is_constructible_v<std::string, T>) {
        return is_string();
    }
    else if constexpr (ext::has_check_json<T>) {
        return ext::jsonization_wrapper<T>::check_json(*this);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
inline bool value::all() const noexcept
{
    if (is_array()) {
        return as_array_unsafe().all<T>();
    }
    else if (is_object()) {
        return as_object_unsafe().all<T>();
    }
    else {
        return false;
    }
}

inline bool value::operator==(const value& rhs) const
{
    if (_type != rhs._type) {
        return false;
    }

    switch (_type) {
    case value_type::null:
        return rhs.is_null();
    case value_type::boolean:
    case value_type::number:
    case value_type::string:
        return as_basic_type_str_unsafe() == rhs.as_basic_type_str_unsafe();
    case value_type::array:
        return as_array_unsafe() == rhs.as_array_unsafe();
    case value_type::object:
        return as_object_unsafe() == rhs.as_object_unsafe();
    default:
        return false;
    }
}

inline bool value::operator!=(const value& rhs) const
{
    return !(*this == rhs);
}

}
