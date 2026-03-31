#pragma once

#include "../object.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

template <typename T, all_object_key K>
inline std::optional<T> object::find(const K& key) const&
{
    auto it = find_(key);
    if (it == end()) {
        return std::nullopt;
    }
    if (it->second.template is<T>()) {
        return it->second.template as<T>();
    }
    else {
        return std::nullopt;
    }
}

template <typename T, all_object_key K>
inline std::optional<T> object::find(const K& key) &&
{
    auto it = find_(key);
    if (it == end()) {
        return std::nullopt;
    }
    if (it->second.template is<T>()) {
        return std::move(it->second).template as<T>();
    }
    else {
        return std::nullopt;
    }
}

inline object object::operator|(const object& rhs) const&
{
    object obj = *this;
    for (const auto& [key, val] : rhs) {
        obj.insert(key, val);
    }
    return obj;
}

inline object object::operator|(object&& rhs) const&
{
    object obj = *this;
    while (!rhs.empty()) {
        auto node = rhs._data.extract(rhs.begin());
        obj.insert(std::move(node.key()), std::move(node.mapped()));
    }
    return obj;
}

inline object object::operator|(const object& rhs) &&
{
    *this |= rhs;
    return std::move(*this);
}

inline object object::operator|(object&& rhs) &&
{
    *this |= std::move(rhs);
    return std::move(*this);
}

inline object& object::operator|=(const object& rhs)
{
    for (auto& [key, val] : rhs) {
        insert(key, val);
    }
    return *this;
}

inline object& object::operator|=(object&& rhs)
{
    while (!rhs.empty()) {
        auto node = rhs._data.extract(rhs.begin());
        insert(std::move(node.key()), std::move(node.mapped()));
    }
    return *this;
}

}
