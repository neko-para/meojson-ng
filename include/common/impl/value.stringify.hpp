#pragma once

#include "../array.hpp"
#include "../object.hpp"
#include "../value.hpp"
#include "exception.hpp"
#include "utils.hpp"

namespace json
{

inline std::string value::to_string() const
{
    switch (_type) {
    case value_type::null:
        return std::string(_utils::null_string());
    case value_type::boolean:
    case value_type::number:
        return as_basic_type_str();
    case value_type::string:
        return '"' + _utils::escape_string(as_basic_type_str()) + '"';
    case value_type::array:
        return as_array().to_string();
    case value_type::object:
        return as_object().to_string();
    default:
        throw exception { };
    }
}

inline std::string value::format(size_t indent) const
{
    return format(indent, 0);
}

inline std::string value::dumps(std::optional<size_t> indent) const
{
    return indent ? format(*indent) : to_string();
}

inline std::string value::format(size_t indent, size_t indent_times) const
{
    switch (_type) {
    case value_type::null:
    case value_type::boolean:
    case value_type::number:
    case value_type::string:
        return to_string();
    case value_type::array:
        return as_array().format(indent, indent_times);
    case value_type::object:
        return as_object().format(indent, indent_times);
    default:
        throw exception { };
    }
}

}
