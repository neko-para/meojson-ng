#pragma once

#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

template <typename T>
requires(!_utils::is_initializer_list<T>)
inline bool jsonization_wrapper<T>::check_json(const value& val) noexcept
requires has_check_json_value_in_member<T> || has_check_json_array_in_member<T> || has_check_json_object_in_member<T>
         || has_check_json_value_in_spec<T> || has_check_json_array_in_spec<T> || has_check_json_object_in_spec<T>
{
    if constexpr (has_check_json_array_in_member<T>) {
        static_assert(std::is_default_constructible_v<T>);
        return val.is_array() && T { }.check_json(val.as_array_unsafe());
    }
    else if constexpr (has_check_json_object_in_member<T>) {
        static_assert(std::is_default_constructible_v<T>);
        return val.is_object() && T { }.check_json(val.as_object_unsafe());
    }
    else if constexpr (has_check_json_value_in_member<T>) {
        static_assert(std::is_default_constructible_v<T>);
        return T { }.check_json(val);
    }
    else if constexpr (has_check_json_array_in_spec<T>) {
        return val.is_array() && jsonization<T> { }.check_json(val.as_array_unsafe());
    }
    else if constexpr (has_check_json_object_in_spec<T>) {
        return val.is_object() && jsonization<T> { }.check_json(val.as_object_unsafe());
    }
    else if constexpr (has_check_json_value_in_spec<T>) {
        return jsonization<T> { }.check_json(val);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
inline bool jsonization_wrapper<T>::check_json(const array& val) noexcept
requires has_check_json_array_in_member<T> || has_check_json_array_in_spec<T>
{
    if constexpr (has_check_json_array_in_member<T>) {
        static_assert(std::is_default_constructible_v<T>);
        return T { }.check_json(val);
    }
    else if constexpr (has_check_json_array_in_spec<T>) {
        return jsonization<T> { }.check_json(val);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
inline bool jsonization_wrapper<T>::check_json(const object& val) noexcept
requires has_check_json_object_in_member<T> || has_check_json_object_in_spec<T>
{
    if constexpr (has_check_json_object_in_member<T>) {
        static_assert(std::is_default_constructible_v<T>);
        return T { }.check_json(val);
    }
    else if constexpr (has_check_json_object_in_spec<T>) {
        return jsonization<T> { }.check_json(val);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
template <typename U>
requires std::is_same_v<std::remove_cvref_t<U>, T>
inline auto jsonization_wrapper<T>::to_json(U&& val)
requires has_to_json_in_member<T> || has_to_json_in_spec<T>
{
    if constexpr (has_to_json_in_member<T>) {
        return std::forward<U>(val).to_json();
    }
    else if constexpr (has_to_json_in_spec<T>) {
        return jsonization<T> { }.to_json(std::forward<U>(val));
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
template <typename U>
requires std::is_same_v<std::remove_cvref_t<U>, value>
inline bool jsonization_wrapper<T>::from_json(U&& val, T& t)
requires has_from_json_value_in_member<T> || has_from_json_array_in_member<T> || has_from_json_object_in_member<T>
         || has_from_json_value_in_spec<T> || has_from_json_array_in_spec<T> || has_from_json_object_in_spec<T>
{
    if constexpr (has_from_json_array_in_member<T>) {
        if (!val.is_array()) {
            val.throw_type_error(value::value_type::array);
        }
        return t.from_json(std::forward<U>(val).as_array_unsafe());
    }
    else if constexpr (has_from_json_object_in_member<T>) {
        if (!val.is_object()) {
            val.throw_type_error(value::value_type::object);
        }
        return t.from_json(std::forward<U>(val).as_object_unsafe());
    }
    else if constexpr (has_from_json_value_in_member<T>) {
        return t.from_json(std::forward<U>(val));
    }
    else if constexpr (has_from_json_array_in_spec<T>) {
        if (!val.is_array()) {
            val.throw_type_error(value::value_type::array);
        }
        return jsonization<T> { }.from_json(std::forward<U>(val).as_array_unsafe(), t);
    }
    else if constexpr (has_from_json_object_in_spec<T>) {
        if (!val.is_object()) {
            val.throw_type_error(value::value_type::object);
        }
        return jsonization<T> { }.from_json(std::forward<U>(val).as_object_unsafe(), t);
    }
    else if constexpr (has_from_json_value_in_spec<T>) {
        return jsonization<T> { }.from_json(std::forward<U>(val), t);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
template <typename U>
requires std::is_same_v<std::remove_cvref_t<U>, array>
inline bool jsonization_wrapper<T>::from_json(U&& val, T& t)
requires has_from_json_array_in_member<T> || has_from_json_array_in_spec<T>
{
    if constexpr (has_from_json_array_in_member<T>) {
        return t.from_json(std::forward<U>(val));
    }
    else if constexpr (has_from_json_array_in_spec<T>) {
        return jsonization<T> { }.from_json(std::forward<U>(val), t);
    }
    else {
        static_assert(false);
    }
}

template <typename T>
requires(!_utils::is_initializer_list<T>)
template <typename U>
requires std::is_same_v<std::remove_cvref_t<U>, object>
inline bool jsonization_wrapper<T>::from_json(U&& val, T& t)
requires has_from_json_object_in_member<T> || has_from_json_object_in_spec<T>
{
    if constexpr (has_from_json_object_in_member<T>) {
        return t.from_json(std::forward<U>(val));
    }
    else if constexpr (has_from_json_object_in_spec<T>) {
        return jsonization<T> { }.from_json(std::forward<U>(val), t);
    }
    else {
        static_assert(false);
    }
}

}
