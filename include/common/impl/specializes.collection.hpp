#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.hpp"

namespace json::ext
{

template <_utils::is_collection T>
class jsonization<T>
{
public:
    bool check_json(const array& arr) const noexcept
    {
        for (const auto& val : arr) {
            if (!val.is<typename T::value_type>()) {
                return false;
            }
        }
        return true;
    }

    array to_json(const T& t) const
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
                t.push_back(val.as<typename T::value_type>());
            }
            else if constexpr (_utils::has_insert<T>) {
                t.insert(val.as<typename T::value_type>());
            }
            else if constexpr (_utils::has_push<T>) {
                t.push(val.as<typename T::value_type>());
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }

    array to_json(T&& t) const
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
                t.push_back(std::move(val).as<typename T::value_type>());
            }
            else if constexpr (_utils::has_insert<T>) {
                t.insert(std::move(val).as<typename T::value_type>());
            }
            else if constexpr (_utils::has_push<T>) {
                t.push(std::move(val).as<typename T::value_type>());
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }
};

}
