#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "extends.impl.hpp"

namespace MEOJSON_NAMESPACE
{

inline array::array() = default;

inline array::array(const array& rhs) = default;

inline array::array(array&& rhs) noexcept = default;

inline array::~array() = default;

inline array& array::operator=(const array& rhs) = default;

inline array& array::operator=(array&& rhs) noexcept = default;

inline array::array(size_type size)
    : _data(size)
{
}

inline array::array(std::initializer_list<value_type> list)
    : _data(list)
{
}

template <ext::has_to_json_array T>
inline array::array(T&& val)
    : array(ext::jsonization_wrapper<std::remove_cvref_t<T>>::to_json(std::forward<T>(val)))
{
}

}
