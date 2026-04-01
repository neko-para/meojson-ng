#pragma once

#include "../object.hpp"
#include "../value.hpp"
#include "exception.hpp"

namespace json
{

inline bool object::empty() const noexcept
{
    return _data.empty();
}

inline size_t object::size() const noexcept
{
    return _data.size();
}

template <all_object_key K>
inline bool object::contains(const K& key) const
{
    return _data.contains(key);
}

template <all_object_key K>
inline bool object::exists(const K& key) const
{
    return _data.contains(key);
}

inline void object::clear() noexcept
{
    _data.clear();
}

template <all_object_key K, typename V>
requires std::is_constructible_v<object::mapped_type, V&&>
inline std::pair<object::iterator, bool> object::insert(K&& key, V&& val)
{
    return _data.insert_or_assign(std::forward<K>(key), std::forward<V>(val));
}

template <all_object_key K, typename V>
requires std::is_constructible_v<object::mapped_type, V&&>
inline std::pair<object::iterator, bool> object::emplace(K&& key, V&& val)
{
    return _data.insert_or_assign(std::forward<K>(key), std::forward<V>(val));
}

template <all_object_key K>
inline bool object::erase(const K& pos)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<K>, key_type>) {
        return _data.erase(pos) > 0;
    }
    else {
        if (auto it = _data.find(pos); it != _data.end()) {
            _data.erase(it);
            return true;
        }
        else {
            return false;
        }
    }
}

inline bool object::erase(iterator iter)
{
    return _data.erase(iter) != _data.end();
}

template <all_object_key K>
object::iterator object::find_(const K& pos)
{
    return _data.find(pos);
}

template <all_object_key K>
object::const_iterator object::find_(const K& pos) const
{
    return _data.find(pos);
}

template <all_object_key K>
inline const object::mapped_type& object::at(const K& key) const
{
    if constexpr (std::is_same_v<std::remove_cvref_t<K>, key_type>) {
        return _data.at(key);
    }
    else {
        if (auto it = find_(key); it != end()) {
            return it->second;
        }
        throw exception { };
    }
}

template <all_object_key K>
inline object::mapped_type& object::at(const K& key)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<K>, key_type>) {
        return _data.at(key);
    }
    else {
        if (auto it = find_(key); it != end()) {
            return it->second;
        }
        throw exception { };
    }
}

inline object::mapped_type& object::operator[](const key_type& key)
{
    return _data[key];
}

inline object::mapped_type& object::operator[](key_type&& key)
{
    return _data[std::move(key)];
}

inline object::iterator object::begin() noexcept
{
    return _data.begin();
}

inline object::iterator object::end() noexcept
{
    return _data.end();
}

inline object::const_iterator object::begin() const noexcept
{
    return _data.begin();
}

inline object::const_iterator object::end() const noexcept
{
    return _data.end();
}

inline object::const_iterator object::cbegin() const noexcept
{
    return _data.cbegin();
}

inline object::const_iterator object::cend() const noexcept
{
    return _data.cend();
}

inline object::reverse_iterator object::rbegin() noexcept
{
    return _data.rbegin();
}

inline object::reverse_iterator object::rend() noexcept
{
    return _data.rend();
}

inline object::const_reverse_iterator object::rbegin() const noexcept
{
    return _data.rbegin();
}

inline object::const_reverse_iterator object::rend() const noexcept
{
    return _data.rend();
}

inline object::const_reverse_iterator object::crbegin() const noexcept
{
    return _data.crbegin();
}

inline object::const_reverse_iterator object::crend() const noexcept
{
    return _data.crend();
}

}
