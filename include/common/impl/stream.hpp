#pragma once

#if !defined(MEOJSON_MODULE)
#include <ostream>
#endif

#include "concepts.hpp"

namespace json
{

MEOJSON_EXPORT template <typename T>
requires _utils::same_as_one_of<T, value, array, object>
inline std::ostream& operator<<(std::ostream& out, const T& val)
{
    out << val.format();
    return out;
}

}
