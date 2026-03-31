#pragma once

#include "../array.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

inline bool array::empty() const noexcept
{
    return _data.empty();
}

inline size_t array::size() const noexcept
{
    return _data.size();
}

inline bool array::contains(size_t pos) const noexcept
{
    return pos < _data.size();
}

inline bool array::exists(size_t pos) const noexcept
{
    return pos < _data.size();
}

inline void array::clear() noexcept
{
    _data.clear();
}

inline void array::reserve(size_t capacity)
{
    _data.reserve(capacity);
}

inline size_t array::capacity() const noexcept
{
    return _data.capacity();
}

inline void array::push_back(const value_type& val)
{
    _data.push_back(val);
}

inline void array::push_back(value_type&& val)
{
    _data.push_back(std::move(val));
}

template <typename... args_t>
array::reference array::emplace_back(args_t&&... args)
{
    return _data.emplace_back(std::forward<args_t>(args)...);
}

inline bool array::erase(size_t pos)
{
    if (pos > size()) {
        return false;
    }
    return erase(_data.begin() + pos);
}

inline bool array::erase(iterator iter)
{
    return _data.erase(iter) != _data.end();
}

inline array::const_reference& array::at(size_t pos) const
{
    return _data.at(pos);
}

inline array::reference& array::at(size_t pos)
{
    return _data.at(pos);
}

inline array::const_reference& array::operator[](size_t pos) const
{
    return _data[pos];
}

inline array::reference& array::operator[](size_t pos)
{
    return _data[pos];
}

inline array::iterator array::begin() noexcept
{
    return _data.begin();
}

inline array::iterator array::end() noexcept
{
    return _data.end();
}

inline array::const_iterator array::begin() const noexcept
{
    return _data.begin();
}

inline array::const_iterator array::end() const noexcept
{
    return _data.end();
}

inline array::const_iterator array::cbegin() const noexcept
{
    return _data.cbegin();
}

inline array::const_iterator array::cend() const noexcept
{
    return _data.cend();
}

inline array::reverse_iterator array::rbegin() noexcept
{
    return _data.rbegin();
}

inline array::reverse_iterator array::rend() noexcept
{
    return _data.rend();
}

inline array::const_reverse_iterator array::rbegin() const noexcept
{
    return _data.rbegin();
}

inline array::const_reverse_iterator array::rend() const noexcept
{
    return _data.rend();
}

inline array::const_reverse_iterator array::crbegin() const noexcept
{
    return _data.crbegin();
}

inline array::const_reverse_iterator array::crend() const noexcept
{
    return _data.crend();
}

}
