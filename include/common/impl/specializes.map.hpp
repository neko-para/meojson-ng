#pragma once

#include "../object.hpp"
#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

template <_utils::is_map T>
class jsonization<T>
{
public:
    bool check_json(const object& obj) const noexcept
    {
        for (const auto& [_, val] : obj) {
            if (!val.is<typename T::mapped_type>()) {
                return false;
            }
        }
        return true;
    }

    object to_json(const T& t) const
    {
        object obj;
        for (const auto& [key, val] : t) {
            obj.insert(key, val);
        }
        return obj;
    }

    bool from_json(const object& obj, T& t) const
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
    {
        object obj;
        for (auto& [key, val] : t) {
            obj.insert(key, std::move(val));
        }
        return obj;
    }

    bool from_json(object&& obj, T& t) const
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
