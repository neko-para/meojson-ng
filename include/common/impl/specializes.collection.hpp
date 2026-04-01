#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.hpp"
#include "extends.impl.hpp"

namespace json::ext
{

template <_utils::is_collection T>
class jsonization<T>
{
public:
    using inner_type = T::value_type;

    bool check_json(const array& arr) const noexcept
    requires can_check_value<inner_type>
    {
        for (const auto& val : arr) {
            if (!val.is<inner_type>()) {
                return false;
            }
        }
        return true;
    }

    array to_json(const T& t) const
    requires can_to_value<inner_type>
    {
        array arr;
        if constexpr (_utils::has_size<T>) {
            arr.reserve(t.size());
        }
        for (const auto& val : t) {
            arr.push_back(static_cast<value>(val));
        }
        return arr;
    }

    bool from_json(const array& arr, T& t) const
    requires can_from_value<inner_type>
    {
        if constexpr (_utils::has_clear<T>) {
            t.clear();
        }
        else {
            T empty { };
            std::swap(t, empty);
        }
        if constexpr (_utils::has_reserve<T>) {
            t.reserve(arr.size());
        }
        for (const auto& val : arr) {
            if constexpr (_utils::has_push_back<T>) {
                t.push_back(val.as<inner_type>());
            }
            else if constexpr (_utils::has_insert<T>) {
                t.insert(val.as<inner_type>());
            }
            else if constexpr (_utils::has_push<T>) {
                t.push(val.as<inner_type>());
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }

    array to_json(T&& t) const
    requires can_to_value<inner_type>
    {
        array arr;
        if constexpr (_utils::has_size<T>) {
            arr.reserve(t.size());
        }
        for (auto& val : t) {
            arr.push_back(static_cast<value>(std::move(val)));
        }
        return arr;
    }

    bool from_json(array&& arr, T& t) const
    requires can_from_value<inner_type>
    {
        if constexpr (_utils::has_clear<T>) {
            t.clear();
        }
        else {
            T empty { };
            std::swap(t, empty);
        }
        if constexpr (_utils::has_reserve<T>) {
            t.reserve(arr.size());
        }
        for (auto& val : arr) {
            if constexpr (_utils::has_push_back<T>) {
                t.push_back(std::move(val).as<inner_type>());
            }
            else if constexpr (_utils::has_insert<T>) {
                t.insert(std::move(val).as<inner_type>());
            }
            else if constexpr (_utils::has_push<T>) {
                t.push(std::move(val).as<inner_type>());
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }
};

}
