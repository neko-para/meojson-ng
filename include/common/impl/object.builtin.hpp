#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "extends.impl.hpp"

namespace MEOJSON_NAMESPACE
{

inline object::object() = default;

inline object::object(const object& rhs) = default;

inline object::object(object&& rhs) noexcept = default;

inline object::~object() = default;

inline object& object::operator=(const object& rhs) = default;

inline object& object::operator=(object&& rhs) noexcept = default;

inline object::object(std::initializer_list<typename raw_object::value_type> list)
    : _data(list)
{
}

template <ext::has_to_json_object T>
inline object::object(T&& val)
    : object(ext::jsonization_wrapper<std::remove_cvref_t<T>>::to_json(std::forward<T>(val)))
{
}

}
