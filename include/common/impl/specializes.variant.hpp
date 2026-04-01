#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.impl.hpp"

namespace json::ext
{

template <_utils::is_variant T>
class jsonization<T>
{
public:
    constexpr static size_t N = std::variant_size_v<T>;
    static_assert(N > 0);

    bool check_json(const value& val) const noexcept
    requires variant_can_check_value<T>
    {
        return [&]<size_t... Is>(std::index_sequence<Is...>) {
            return (val.is<std::variant_alternative_t<Is, T>>() || ...);
        }(std::make_index_sequence<N>());
    }

    value to_json(const T& t) const
    requires variant_can_to_value<T>
    {
        value val;
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            std::ignore = ((t.index() == Is ? (val = get<Is>(t), true) : false) || ...);
        }(std::make_index_sequence<N>());
        return val;
    }

    bool from_json(const value& val, T& t) const
    requires variant_can_from_value<T>
    {
        return [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            return ((val.is<std::variant_alternative_t<Is, T>>() ? (t = val.as<std::variant_alternative_t<Is, T>>(), true) : false) || ...);
        }(std::make_index_sequence<N>());
    }

    value to_json(T&& t) const
    requires variant_can_to_value<T>
    {
        value val;
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            std::ignore = ((t.index() == Is ? (val = get<Is>(std::move(t)), true) : false) || ...);
        }(std::make_index_sequence<N>());
        return val;
    }

    bool from_json(value&& val, T& t) const
    requires variant_can_from_value<T>
    {
        return [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            return (
                (val.is<std::variant_alternative_t<Is, T>>() ? (t = std::move(val).as<std::variant_alternative_t<Is, T>>(), true) : false)
                || ...);
        }(std::make_index_sequence<N>());
    }
};

}
