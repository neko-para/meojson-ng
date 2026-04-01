#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "enum_reflection.hpp"
#include "exception.hpp"
#include "extends.hpp"
#include "utils.hpp"

namespace MEOJSON_NAMESPACE
{

inline value::operator std::nullptr_t() const
{
    if (!is_null()) {
        throw_type_error(value_type::null);
    }
    return { };
}

inline value::operator std::monostate() const
{
    if (!is_null()) {
        throw_type_error(value_type::null);
    }
    return { };
}

inline bool value::as_boolean() const
{
    if (!is_boolean()) {
        throw_type_error(value_type::boolean);
    }
    const auto& str = as_basic_type_str();
    if (str == _utils::true_string()) {
        return true;
    }
    else if (str == _utils::false_string()) {
        return false;
    }
    else {
        throw value_error { };
    }
}

inline value::operator bool() const
{
    return as_boolean();
}

inline int value::as_integer() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stoi(as_basic_type_str());
}

inline unsigned value::as_unsigned() const
{
    return static_cast<unsigned>(as_unsigned_long());
}

inline long value::as_long() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stol(as_basic_type_str());
}

inline unsigned long value::as_unsigned_long() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stoul(as_basic_type_str());
}

inline long long value::as_long_long() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stoll(as_basic_type_str());
}

inline unsigned long long value::as_unsigned_long_long() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stoull(as_basic_type_str());
}

inline float value::as_float() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stof(as_basic_type_str());
}

inline double value::as_double() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stod(as_basic_type_str());
}

inline long double value::as_long_double() const
{
    if (!is_number()) {
        throw_type_error(value_type::number);
    }
    return std::stold(as_basic_type_str());
}

inline value::operator int() const
{
    return as_integer();
}

inline value::operator unsigned() const
{
    return as_unsigned();
}

inline value::operator long() const
{
    return as_long();
}

inline value::operator unsigned long() const
{
    return as_unsigned_long();
}

inline value::operator long long() const
{
    return as_long_long();
}

inline value::operator unsigned long long() const
{
    return as_unsigned_long_long();
}

inline value::operator float() const
{
    return as_float();
}

inline value::operator double() const
{
    return as_double();
}

inline value::operator long double() const
{
    return as_long_double();
}

inline const std::string& value::as_string() const&
{
    if (!is_string()) {
        throw_type_error(value_type::string);
    }
    return as_basic_type_str();
}

inline std::string& value::as_string() &
{
    if (!is_string()) {
        throw_type_error(value_type::string);
    }
    return as_basic_type_str();
}

inline std::string value::as_string() &&
{
    if (!is_string()) {
        throw_type_error(value_type::string);
    }
    return std::move(as_basic_type_str());
}

inline const std::string& value::as_string_unsafe() const& noexcept
{
    return as_basic_type_str_unsafe();
}

inline std::string& value::as_string_unsafe() & noexcept
{
    return as_basic_type_str_unsafe();
}

inline std::string value::as_string_unsafe() && noexcept
{
    return std::move(as_basic_type_str_unsafe());
}

inline value::operator std::string() const&
{
    return as_string();
}

inline value::operator std::string() &&
{
    return std::move(as_string());
}

inline std::string_view value::as_string_view() const&
{
    if (!is_string()) {
        throw_type_error(value_type::string);
    }
    return as_basic_type_str();
}

inline value::operator std::string_view() const&
{
    return as_string_view();
}

inline const array& value::as_array() const&
{
    if (!is_array()) {
        throw_type_error(value_type::array);
    }
    return *std::get<array_ptr>(_data);
}

inline array& value::as_array() &
{
    if (empty()) {
        _type = value_type::array;
        _data = std::make_unique<array>();
        return as_array_unsafe();
    }
    if (!is_array()) {
        throw_type_error(value_type::array);
    }
    return *std::get<array_ptr>(_data);
}

inline array value::as_array() &&
{
    if (!is_array()) {
        throw_type_error(value_type::array);
    }
    return std::move(*std::get<array_ptr>(_data));
}

inline const array& value::as_array_unsafe() const& noexcept
{
    return **std::get_if<array_ptr>(&_data);
}

inline array& value::as_array_unsafe() & noexcept
{
    return **std::get_if<array_ptr>(&_data);
}

inline array value::as_array_unsafe() && noexcept
{
    return std::move(**std::get_if<array_ptr>(&_data));
}

inline value::operator array() const&
{
    return as_array();
}

inline value::operator array() &&
{
    return std::move(as_array());
}

inline const object& value::as_object() const&
{
    if (!is_object()) {
        throw_type_error(value_type::object);
    }
    return *std::get<object_ptr>(_data);
}

inline object& value::as_object() &
{
    if (empty()) {
        _type = value_type::object;
        _data = std::make_unique<object>();
        return as_object_unsafe();
    }
    if (!is_object()) {
        throw_type_error(value_type::object);
    }
    return *std::get<object_ptr>(_data);
}

inline object value::as_object() &&
{
    if (!is_object()) {
        throw_type_error(value_type::object);
    }
    return std::move(*std::get<object_ptr>(_data));
}

inline const object& value::as_object_unsafe() const& noexcept
{
    return **std::get_if<object_ptr>(&_data);
}

inline object& value::as_object_unsafe() & noexcept
{
    return **std::get_if<object_ptr>(&_data);
}

inline object value::as_object_unsafe() && noexcept
{
    return std::move(**std::get_if<object_ptr>(&_data));
}

inline value::operator object() const&
{
    return as_object();
}

inline value::operator object() &&
{
    return std::move(as_object());
}

template <typename enum_t>
requires std::is_enum_v<enum_t>
inline value::operator enum_t() const
{
    if (is_string()) {
        if (auto enum_opt = _reflection::string_to_enum<enum_t>(as_string_unsafe()); enum_opt) {
            return *enum_opt;
        }
        else {
            throw exception { };
        }
    }
    else if (is_number()) {
        return static_cast<enum_t>(static_cast<std::underlying_type_t<enum_t>>(*this));
    }
    else {
        throw_type_error(value_type::number);
    }
}

template <typename T>
requires(!_utils::support_as_ref<T>)
inline T value::as() const&
{
    if constexpr (_utils::is_builtin_primitive<T>) {
        return static_cast<T>(*this);
    }
    else if constexpr (ext::has_from_json<T>) {
        T t { };
        if (!ext::jsonization_wrapper<T>::from_json(*this, t)) {
            throw exception { };
        }
        return t;
    }
    else {
        static_assert(false);
    }
}

template <_utils::support_as_ref T>
inline const T& value::as() const&
{
    if constexpr (std::is_same_v<T, value>) {
        return *this;
    }
    else if constexpr (std::is_same_v<T, array>) {
        return as_array();
    }
    else if constexpr (std::is_same_v<T, object>) {
        return as_object();
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        return as_basic_type_str();
    }
    else {
        static_assert(false);
    }
}

template <_utils::support_as_ref T>
inline T& value::as() &
{
    if constexpr (std::is_same_v<T, value>) {
        return *this;
    }
    else if constexpr (std::is_same_v<T, array>) {
        return as_array();
    }
    else if constexpr (std::is_same_v<T, object>) {
        return as_object();
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        return as_basic_type_str();
    }
    else {
        static_assert(false);
    }
}

template <typename T>
inline T value::as() &&
{
    if constexpr (std::is_same_v<T, value>) {
        return static_cast<T>(std::move(*this));
    }
    else if constexpr (std::is_same_v<T, array>) {
        return static_cast<T>(std::move(*this));
    }
    else if constexpr (std::is_same_v<T, object>) {
        return static_cast<T>(std::move(*this));
    }
    else if constexpr (_utils::is_builtin_primitive<T>) {
        return static_cast<T>(std::move(*this));
    }
    else if constexpr (ext::has_from_json<T>) {
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
inline value::operator T() const&
{
    return as<T>();
}

template <typename T>
requires(!_utils::is_builtin_primitive_without_string<T>)
inline value::operator T() &&
{
    return std::move(*this).as<T>();
}

}
