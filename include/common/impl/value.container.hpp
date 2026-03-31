#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

inline bool value::contains(size_t pos) const noexcept
{
    return is_array() && as_array_unsafe().contains(pos);
}

inline bool value::exists(size_t pos) const noexcept
{
    return is_array() && as_array_unsafe().contains(pos);
}

template <all_object_key K>
inline bool value::contains(const K& key) const
{
    return is_object() && as_object_unsafe().contains(key);
}

template <all_object_key K>
inline bool value::exists(const K& key) const
{
    return is_object() && as_object_unsafe().contains(key);
}

inline void value::clear() noexcept
{
    *this = value { };
}

template <typename V>
requires std::is_constructible_v<value, V&&>
inline auto value::emplace(V&& val)
{
    return as_array().emplace_back(std::forward<V>(val));
}

template <all_object_key K, typename V>
requires std::is_constructible_v<value, V&&>
inline auto value::emplace(K&& key, V&& val)
{
    return as_object().emplace(std::forward<K>(key), std::forward<V>(val));
}

inline bool value::erase(size_t pos)
{
    return as_array().erase(pos);
}

template <all_object_key K>
inline bool value::erase(const K& pos)
{
    return as_object().erase(pos);
}

inline const value& value::at(size_t pos) const
{
    return as_array().at(pos);
}

inline value& value::at(size_t pos)
{
    return as_array().at(pos);
}

template <all_object_key K>
inline const value& value::at(const K& key) const
{
    return as_object().at(key);
}

template <all_object_key K>
inline value& value::at(const K& key)
{
    return as_object().at(key);
}

inline const value& value::operator[](size_t pos) const
{
    return as_array()[pos];
}

inline value& value::operator[](size_t pos)
{
    return as_array()[pos];
}

inline value& value::operator[](const raw_object::key_type& key)
{
    return as_object()[key];
}

inline value& value::operator[](raw_object::key_type&& key)
{
    return as_object()[std::move(key)];
}

}
