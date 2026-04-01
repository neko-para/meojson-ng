#pragma once

#include <string>
#include <type_traits>

#include "../forward.hpp"

namespace MEOJSON_NAMESPACE::_utils
{

template <typename T>
using iterator_t = decltype(std::declval<T&>().begin());
template <typename T>
using iter_value_t = typename std::iterator_traits<std::decay_t<T>>::value_type;
template <typename R>
using range_value_t = iter_value_t<iterator_t<R>>;

template <typename T>
concept is_string = requires {
    typename T::traits_type;
    typename T::value_type;
    requires std::is_same_v<typename T::traits_type, std::char_traits<typename T::value_type>>;
};

template <typename T>
concept is_container = requires {
    typename T::value_type;
    typename range_value_t<T>;
    requires std::is_same_v<typename T::value_type, range_value_t<T>>;
    requires !is_string<T>;
};

template <typename T>
concept is_map = requires(T t) {
    typename T::key_type;
    typename T::mapped_type;
    requires is_container<T>;
    requires std::is_same_v<typename T::key_type, std::string>;
};

template <typename T, typename = void>
constexpr bool is_fixed_array_v = false;
template <template <typename, size_t> typename arr_t, typename value_t, size_t size>
constexpr bool is_fixed_array_v<arr_t<value_t, size>> = true;
template <typename T>
concept is_fixed_array = is_fixed_array_v<T> && requires(T t, size_t i) {
    typename T::value_type;
    { t.at(i) } -> std::same_as<typename T::value_type&>;
};

template <is_fixed_array T>
constexpr size_t fixed_array_size = 0;
template <template <typename, size_t> typename arr_t, typename value_t, size_t size>
constexpr size_t fixed_array_size<arr_t<value_t, size>> = size;

template <typename T>
concept is_collection = is_container<T> && !is_map<T> && !is_fixed_array<T>;

template <typename T>
concept is_tuple_like = requires { std::tuple_size<T>::value; } && !is_fixed_array<T>;

template <typename T>
constexpr bool is_variant_v = false;
template <typename... T>
constexpr bool is_variant_v<std::variant<T...>> = true;

template <typename T>
concept is_variant = is_variant_v<T>;

template <typename T>
concept is_nullable = !std::is_pointer_v<std::decay_t<T>> && requires(T t) {
    { static_cast<bool>(t) };
    { *t };
};

template <is_nullable T>
using nullable_value_t = std::decay_t<decltype(*std::declval<T>())>;

template <typename T>
constexpr bool is_optional_v = false;
template <typename T>
constexpr bool is_optional_v<std::optional<T>> = true;

template <typename T>
concept is_optional = is_optional_v<T>;

template <typename T>
constexpr bool is_shared_ptr_v = false;
template <typename T>
constexpr bool is_shared_ptr_v<std::shared_ptr<T>> = true;

template <typename T>
concept is_shared_ptr = is_shared_ptr_v<T>;

template <typename T>
constexpr bool is_unique_ptr_v = false;
template <typename T>
constexpr bool is_unique_ptr_v<std::unique_ptr<T>> = true;

template <typename T>
concept is_unique_ptr = is_unique_ptr_v<T>;

template <typename T>
constexpr bool is_initializer_list_v = false;
template <typename T>
constexpr bool is_initializer_list_v<std::initializer_list<T>> = true;

template <typename T>
concept is_initializer_list = is_initializer_list_v<T>;

template <typename T>
concept has_push_back = requires(T t, typename T::value_type v) { t.push_back(v); };

template <typename T>
concept has_insert = requires(T t, typename T::value_type v) { t.insert(v); };

template <typename T>
concept has_emplace = requires(T t, raw_object::key_type k, raw_object::value_type v) { t.emplace(k, v); };

template <typename T>
concept has_push = requires(T t, typename T::value_type v) { t.push(v); };

template <typename T>
concept has_clear = requires(T t, size_t n) { t.clear(); };

template <typename T>
concept has_size = requires(T t) {
    { t.size() } noexcept -> std::same_as<size_t>;
};

template <typename T>
concept has_reserve = requires(T t, size_t n) { t.reserve(n); };

template <typename T>
concept support_as_ref =
    std::is_same_v<T, value> || std::is_same_v<T, array> || std::is_same_v<T, object> || std::is_same_v<T, std::string>;

template <typename T>
concept is_builtin_primitive_without_string = std::is_same_v<T, nullptr_t> || std::is_same_v<T, std::monostate> || std::is_same_v<T, bool>
                                              || std::integral<T> || std::floating_point<T> || std::is_enum_v<T>;

template <typename T>
concept is_builtin_primitive = is_builtin_primitive_without_string<T> || std::is_constructible_v<std::string, T>;

template <typename T, typename... Us>
concept same_as_one_of = (std::same_as<T, Us> || ...);

template <typename... Ts>
using last_of_t = std::tuple_element_t<sizeof...(Ts) - 1, std::tuple<Ts...>>;

template <typename T>
using wrap_string_t = std::conditional_t<std::is_constructible_v<std::string, T>, std::string, T>;

template <typename... Ts>
using get_access_t = wrap_string_t<std::decay_t<last_of_t<Ts...>>>;

}
