#pragma once

#include "../object.hpp"
#include "../value.hpp"
#include "utils.hpp"

namespace json
{

inline std::string object::to_string() const
{
    std::string str { '{' };
    for (auto iter = _data.cbegin(); iter != _data.cend();) {
        const auto& [key, val] = *iter;
        str += '"' + _utils::escape_string(key) + std::string { '\"', ':' } + val.to_string();
        if (++iter != _data.cend()) {
            str += ',';
        }
    }
    str += '}';
    return str;
}

inline std::string object::format(size_t indent) const
{
    return format(indent, 0);
}

inline std::string object::dumps(std::optional<size_t> indent) const
{
    return indent ? format(*indent) : to_string();
}

inline std::string object::format(size_t indent, size_t indent_times) const
{
    const std::string tail_indent(indent * indent_times, ' ');
    const std::string body_indent(indent * (indent_times + 1), ' ');

    std::string str { '{', '\n' };
    for (auto iter = _data.cbegin(); iter != _data.cend();) {
        const auto& [key, val] = *iter;
        str += body_indent + '"' + _utils::escape_string(key) + std::string { '\"', ':', ' ' } + val.format(indent, indent_times + 1);
        if (++iter != _data.cend()) {
            str += ',';
        }
        str += '\n';
    }
    str += tail_indent + '}';
    return str;
}

}
