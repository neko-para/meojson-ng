#pragma once

#if !defined(MEOJSON_MODULE)
#include <exception>
#include <format>
#endif

#include "../value.hpp"
#include "format.hpp"

namespace json
{

struct exception : public std::exception
{
    std::string _what;

    template <typename... args_t>
    requires std::is_constructible_v<std::string, args_t&&...>
    exception(args_t&&... args)
        : _what(std::forward<args_t>(args)...)
    {
    }

    exception(const exception&) = default;
    exception(exception&&) noexcept = default;

    virtual const char* what() const noexcept { return _what.c_str(); }
};

// inner type incorrect
struct type_error : public exception
{
    value::value_type expected;
    value::value_type actual;

    template <_utils::is_json_type T>
    type_error(std::string_view target, value::value_type exp, const T& curr)
        : exception(std::format("Type error: cannot convert to {}, expected={}, {}", target, exp, curr.value_info()))
        , expected(exp)
    {
        if constexpr (std::same_as<T, value>) {
            actual = curr.type();
        }
        else if constexpr (std::same_as<T, array>) {
            actual = value::value_type::array;
        }
        else if constexpr (std::same_as<T, object>) {
            actual = value::value_type::object;
        }
        else {
            static_assert(false);
        }
    }
};

// inner string value incorrect
struct value_error : public exception
{
};

}
