#pragma once

#if !defined(MEOJSON_MODULE)
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#endif

namespace json::_utils
{

inline std::string escape_string(const std::string& str)
{
    std::string result;
    auto cur = str.cbegin();
    auto end = str.cend();
    auto no_escape_beg = cur;
    char escape = 0;

    result.reserve(str.size());

    for (; cur != end; ++cur) {
        switch (*cur) {
        case '"':
            escape = '"';
            break;
        case '\\':
            escape = '\\';
            break;
        case '\b':
            escape = 'b';
            break;
        case '\f':
            escape = 'f';
            break;
        case '\n':
            escape = 'n';
            break;
        case '\r':
            escape = 'r';
            break;
        case '\t':
            escape = 't';
            break;
        default:
            break;
        }
        if (escape) {
            result.append(no_escape_beg, cur);
            result.push_back('\\');
            result.push_back(escape);
            no_escape_beg = cur + 1;
            escape = 0;
        }
    }
    result.append(no_escape_beg, cur);

    return result;
}

inline std::string_view true_string()
{
    return "true";
}

inline std::string_view false_string()
{
    return "false";
}

inline std::string_view null_string()
{
    return "null";
}

template <typename any_t>
inline std::string to_string(any_t arg)
{
#ifdef MEOJSON_KEEP_FLOATING_PRECISION
    using real_type = std::remove_reference_t<any_t>;
    if constexpr (std::is_floating_point_v<real_type>) {
        std::ostringstream oss;
        oss << std::setprecision(std::numeric_limits<real_type>::max_digits10) << arg;
        return oss.str();
    }
    else
#endif
    {
        return std::to_string(arg);
    }
}

}
