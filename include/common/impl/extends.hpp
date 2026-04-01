#pragma once

#include "../forward.hpp"
#include "concepts.hpp"

namespace json::ext
{

template <typename T>
class jsonization
{
public:
    // bool check_json(const value&) const noexcept = delete;

    // value to_json(const T&) const = delete;
    // bool from_json(const value&, T&) const = delete;

    // value to_json(T&&) const = delete;
    // bool from_json(value&&, T&) const = delete;
};

#pragma mark - check_json

template <typename T>
concept has_check_json_value_in_member = requires(T t, value v) {
    { t.check_json(v) } noexcept -> std::same_as<bool>;
};

template <typename T>
concept has_check_json_array_in_member = requires(T t, array v) {
    { t.check_json(v) } noexcept -> std::same_as<bool>;
} && !has_check_json_value_in_member<T>;

template <typename T>
concept has_check_json_object_in_member = requires(T t, object v) {
    { t.check_json(v) } noexcept -> std::same_as<bool>;
} && !has_check_json_value_in_member<T>;

template <typename T>
concept has_check_json_value_in_spec = requires(jsonization<T> j, value v) {
    { j.check_json(v) } noexcept -> std::same_as<bool>;
};

template <typename T>
concept has_check_json_array_in_spec = requires(jsonization<T> j, array v) {
    { j.check_json(v) } noexcept -> std::same_as<bool>;
} && !has_check_json_value_in_spec<T>;

template <typename T>
concept has_check_json_object_in_spec = requires(jsonization<T> j, object v) {
    { j.check_json(v) } noexcept -> std::same_as<bool>;
} && !has_check_json_value_in_spec<T>;

#pragma mark - to_json

template <typename T>
concept has_to_json_in_member = requires(T t) {
    { t.to_json() } -> _utils::same_as_one_of<value, array, object>;
};

template <typename T>
concept has_to_json_in_spec = requires(jsonization<T> j, T t) {
    { j.to_json(t) } -> _utils::same_as_one_of<value, array, object>;
};

#pragma mark - from_json

template <typename T>
concept has_from_json_value_in_member = requires(T t, value v) {
    { t.from_json(v) } -> std::same_as<bool>;
};

template <typename T>
concept has_from_json_array_in_member = requires(T t, array v) {
    { t.from_json(v) } -> std::same_as<bool>;
} && !has_from_json_value_in_member<T>;

template <typename T>
concept has_from_json_object_in_member = requires(T t, object v) {
    { t.from_json(v) } -> std::same_as<bool>;
} && !has_from_json_value_in_member<T>;

template <typename T>
concept has_from_json_value_in_spec = requires(jsonization<T> j, value v, T t) {
    { j.from_json(v, t) } -> std::same_as<bool>;
};

template <typename T>
concept has_from_json_array_in_spec = requires(jsonization<T> j, array v, T t) {
    { j.from_json(v, t) } -> std::same_as<bool>;
} && !has_from_json_value_in_spec<T>;

template <typename T>
concept has_from_json_object_in_spec = requires(jsonization<T> j, object v, T t) {
    { j.from_json(v, t) } -> std::same_as<bool>;
} && !has_from_json_value_in_spec<T>;

#pragma mark - jsonization_wrapper

template <typename T>
requires(!_utils::is_initializer_list<T>)
struct jsonization_wrapper
{
    static bool check_json(const value& val) noexcept
    requires has_check_json_value_in_member<T> || has_check_json_array_in_member<T> || has_check_json_object_in_member<T>
             || has_check_json_value_in_spec<T> || has_check_json_array_in_spec<T> || has_check_json_object_in_spec<T>;

    static bool check_json(const array& val) noexcept
    requires has_check_json_array_in_member<T> || has_check_json_array_in_spec<T>;

    static bool check_json(const object& val) noexcept
    requires has_check_json_object_in_member<T> || has_check_json_object_in_spec<T>;

    template <typename U>
    requires std::is_same_v<std::remove_cvref_t<U>, T>
    static auto to_json(U&& val)
    requires has_to_json_in_member<T> || has_to_json_in_spec<T>;

    template <typename U>
    requires std::is_same_v<std::remove_cvref_t<U>, value>
    static bool from_json(U&& val, T& t)
    requires has_from_json_value_in_member<T> || has_from_json_array_in_member<T> || has_from_json_object_in_member<T>
             || has_from_json_value_in_spec<T> || has_from_json_array_in_spec<T> || has_from_json_object_in_spec<T>;

    template <typename U>
    requires std::is_same_v<std::remove_cvref_t<U>, array>
    static bool from_json(U&& val, T& t)
    requires has_from_json_array_in_member<T> || has_from_json_array_in_spec<T>;

    template <typename U>
    requires std::is_same_v<std::remove_cvref_t<U>, object>
    static bool from_json(U&& val, T& t)
    requires has_from_json_object_in_member<T> || has_from_json_object_in_spec<T>;
};

#pragma mark - concepts

template <typename T>
concept has_check_json = requires(const value& v) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::check_json(v) } noexcept -> std::same_as<bool>;
};

template <typename T>
concept has_check_json_array = requires(const array& v) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::check_json(v) } noexcept -> std::same_as<bool>;
};

template <typename T>
concept has_check_json_object = requires(const object& v) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::check_json(v) } noexcept -> std::same_as<bool>;
};

template <typename T>
concept has_to_json = requires(T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::to_json(t) } -> _utils::same_as_one_of<value, array, object>;
};

template <typename T>
concept has_to_json_array = requires(T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::to_json(t) } -> std::same_as<array>;
};

template <typename T>
concept has_to_json_object = requires(T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::to_json(t) } -> std::same_as<object>;
};

template <typename T>
concept has_from_json_value = requires(const value& v, T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::from_json(v, t) } -> std::same_as<bool>;
};

template <typename T>
concept has_from_json_array = requires(const array& v, T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::from_json(v, t) } -> std::same_as<bool>;
};

template <typename T>
concept has_from_json_object = requires(const object& v, T t) {
    { jsonization_wrapper<std::remove_cvref_t<T>>::from_json(v, t) } -> std::same_as<bool>;
};

template <typename T>
concept has_from_json = has_from_json_value<T> || has_from_json_array<T> || has_from_json_object<T>;

}
