#pragma once

#include "../array.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

inline std::string array::to_string() const
{
    std::string str { '[' };
    for (auto iter = _data.cbegin(); iter != _data.cend();) {
        str += iter->to_string();
        if (++iter != _data.cend()) {
            str += ',';
        }
    }
    str += ']';
    return str;
}

inline std::string array::format(size_t indent) const
{
    return format(indent, 0);
}

inline std::string array::dumps(std::optional<size_t> indent) const
{
    return indent ? format(*indent) : to_string();
}

inline std::string array::format(size_t indent, size_t indent_times) const
{
    const std::string tail_indent(indent * indent_times, ' ');
    const std::string body_indent(indent * (indent_times + 1), ' ');

    std::string str { '[', '\n' };
    for (auto iter = _data.cbegin(); iter != _data.cend();) {
        str += body_indent + iter->format(indent, indent_times + 1);
        if (++iter != _data.cend()) {
            str += ',';
        }
        str += '\n';
    }
    str += tail_indent + ']';
    return str;
}

}
