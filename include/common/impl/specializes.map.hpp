#pragma once

#include "../object.hpp"
#include "../value.hpp"
#include "extends.impl.hpp"

namespace json::ext
{

template <_utils::is_map T>
class jsonization<T>
{
public:
    using inner_type = T::mapped_type;

    bool check_json(const object& obj) const noexcept
    requires can_check_value<inner_type>
    {
        for (const auto& [_, val] : obj) {
            if (!val.is<inner_type>()) {
                return false;
            }
        }
        return true;
    }

    object to_json(const T& t) const
    requires can_to_value<inner_type>
    {
        object obj;
        for (const auto& [key, val] : t) {
            obj.insert(key, val);
        }
        return obj;
    }

    bool from_json(const object& obj, T& t) const
    requires can_from_value<inner_type>
    {
        if constexpr (_utils::has_clear<T>) {
            t.clear();
        }
        else {
            T empty { };
            std::swap(t, empty);
        }
        for (const auto& [key, val] : obj) {
            if constexpr (_utils::has_emplace<T>) {
                t.emplace(key, val);
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }

    object to_json(T&& t) const
    requires can_to_value<inner_type>
    {
        object obj;
        for (auto& [key, val] : t) {
            obj.insert(key, std::move(val));
        }
        return obj;
    }

    bool from_json(object&& obj, T& t) const
    requires can_from_value<inner_type>
    {
        if constexpr (_utils::has_clear<T>) {
            t.clear();
        }
        else {
            T empty { };
            std::swap(t, empty);
        }
        for (auto& [key, val] : obj) {
            if constexpr (_utils::has_emplace<T>) {
                t.emplace(key, std::move(val));
            }
            else {
                static_assert(false);
            }
        }
        return true;
    }
};

}
