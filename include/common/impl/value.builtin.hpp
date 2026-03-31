#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "exception.hpp"
#include "utils.hpp"

namespace MEOJSON_NAMESPACE
{

inline value::value() = default;

inline value::value(const value& rhs)
    : _type(rhs._type)
    , _data(deep_copy(rhs._data))
{
}

inline value::value(value&& rhs) noexcept = default;

inline value::~value() = default;

inline value& value::operator=(const value& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    _type = rhs._type;
    _data = deep_copy(rhs._data);
    return *this;
}

inline value& value::operator=(value&& rhs) noexcept = default;

inline value::value(nullptr_t)
    : _type(value_type::null)
    , _data(std::string { _utils::null_string() })
{
}

inline value::value(std::monostate)
    : _type(value_type::null)
    , _data(std::string { _utils::null_string() })
{
}

inline value::value(bool b)
    : _type(value_type::boolean)
    , _data(std::string { b ? _utils::true_string() : _utils::false_string() })
{
}

template <std::integral T>
inline value::value(T num)
    : _type(value_type::number)
    , _data(_utils::to_string(num))
{
}

template <std::floating_point T>
inline value::value(T num)
    : _type(value_type::number)
    , _data(_utils::to_string(num))
{
}

inline value::value(const char* str)
    : _type(value_type::string)
    , _data(std::string { str })
{
}

inline value::value(std::string str)
    : _type(value_type::string)
    , _data(std::move(str))
{
}

inline value::value(std::string_view str)
    : _type(value_type::string)
    , _data(std::string { str })
{
}

inline value::value(const array& arr)
    : _type(value_type::array)
    , _data(std::make_unique<array>(arr))
{
}

inline value::value(array&& arr)
    : _type(value_type::array)
    , _data(std::make_unique<array>(std::move(arr)))
{
}

inline value::value(const object& obj)
    : _type(value_type::object)
    , _data(std::make_unique<object>(obj))
{
}

inline value::value(object&& obj)
    : _type(value_type::object)
    , _data(std::make_unique<object>(std::move(obj)))
{
}

inline value::value(std::initializer_list<typename raw_object::value_type> list)
    : _type(value_type::object)
    , _data(std::make_unique<object>(list))
{
}

template <typename enum_t>
requires std::is_enum_v<enum_t>
inline value::value(enum_t num)
    : value(static_cast<std::underlying_type_t<enum_t>>(num))
{
}

template <ext::has_to_json T>
inline value::value(T&& val)
    : value(ext::jsonization_wrapper<std::remove_cvref_t<T>>::to_json(std::forward<T>(val)))
{
}

inline raw_value value::deep_copy(const raw_value& src)
{
    raw_value dst;
    if (const auto string_ptr = std::get_if<std::string>(&src)) {
        dst = *string_ptr;
    }
    else if (const auto arr_ptr = std::get_if<array_ptr>(&src)) {
        dst = std::make_unique<array>(**arr_ptr);
    }
    else if (const auto obj_ptr = std::get_if<object_ptr>(&src)) {
        dst = std::make_unique<object>(**obj_ptr);
    }
    else {
        // maybe invalid_value
    }

    return dst;
}

inline void value::throw_type_error(value_type expected) const
{
    throw type_error { expected, _type };
}

inline const std::string& value::as_basic_type_str() const
{
    return std::get<std::string>(_data);
}

inline std::string& value::as_basic_type_str()
{
    return std::get<std::string>(_data);
}

inline const std::string& value::as_basic_type_str_unsafe() const noexcept
{
    return *std::get_if<std::string>(&_data);
}

inline std::string& value::as_basic_type_str_unsafe() noexcept
{
    return *std::get_if<std::string>(&_data);
}

}
