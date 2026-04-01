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

template <typename... Ks>
requires(sizeof...(Ks) > 0)
inline std::decay_t<_utils::last_of_t<Ks...>> value::get(Ks&&... keys) const&
{
    constexpr size_t count = sizeof...(Ks);
    auto&& args = std::forward_as_tuple(std::forward<Ks>(keys)...);

    return [&]<size_t... Is>(std::index_sequence<Is...>) {
        return get_helper(std::move(std::get<count - 1>(args)), std::move(std::get<Is>(args))...);
    }(std::make_index_sequence<count - 1>());
}

template <typename... Ks>
requires(sizeof...(Ks) > 0)
inline std::decay_t<_utils::last_of_t<Ks...>> value::get(Ks&&... keys) &&
{
    constexpr size_t count = sizeof...(Ks);
    auto&& args = std::forward_as_tuple(std::forward<Ks>(keys)...);

    return [&]<size_t... Is>(std::index_sequence<Is...>) {
        return std::move(*this).get_helper(std::move(std::get<count - 1>(args)), std::move(std::get<Is>(args))...);
    }(std::make_index_sequence<count - 1>());
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

template <typename Ret, typename K, typename... Ks>
inline std::decay_t<Ret> value::get_helper(Ret&& def, K&& key, Ks&&... keys) const&
{
    if constexpr (std::is_constructible_v<std::string, K>) {
        if (!is_object()) {
            return std::forward<Ret>(def);
        }
        if (auto it = as_object_unsafe().find_(key); it != as_object_unsafe().end()) {
            return it->second.get_helper(std::forward<Ret>(def), std::forward<Ks>(keys)...);
        }
        else {
            return std::forward<Ret>(def);
        }
    }
    else if constexpr (std::integral<std::decay_t<K>>) {
        if (!is_array()) {
            return std::forward<Ret>(def);
        }
        if (as_array_unsafe().contains(key)) {
            return as_array_unsafe()[key].get_helper(std::forward<Ret>(def), std::forward<Ks>(keys)...);
        }
        else {
            return std::forward<Ret>(def);
        }
    }
    else {
        static_assert(false);
    }
}

template <typename Ret, typename K, typename... Ks>
inline std::decay_t<Ret> value::get_helper(Ret&& def, K&& key, Ks&&... keys) &&
{
    if constexpr (std::is_constructible_v<std::string, K>) {
        if (!is_object()) {
            return std::forward<Ret>(def);
        }
        if (auto it = as_object_unsafe().find_(key); it != as_object_unsafe().end()) {
            return std::move(it->second).get_helper(std::forward<Ret>(def), std::forward<Ks>(keys)...);
        }
        else {
            return std::forward<Ret>(def);
        }
    }
    else if constexpr (std::integral<std::decay_t<K>>) {
        if (!is_array()) {
            return std::forward<Ret>(def);
        }
        if (as_array_unsafe().contains(key)) {
            return std::move(as_array_unsafe()[key]).get_helper(std::forward<Ret>(def), std::forward<Ks>(keys)...);
        }
        else {
            return std::forward<Ret>(def);
        }
    }
    else {
        static_assert(false);
    }
}

template <typename Ret>
inline std::decay_t<Ret> value::get_helper(Ret&& def) const&
{
    using final_t = std::decay_t<Ret>;
    return is<final_t>() ? as<final_t>() : std::forward<Ret>(def);
}

template <typename Ret>
inline std::decay_t<Ret> value::get_helper(Ret&& def) &&
{
    using final_t = std::decay_t<Ret>;
    return is<final_t>() ? std::move(*this).as<final_t>() : std::forward<Ret>(def);
}

}
