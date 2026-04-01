#pragma once

#include <ostream>

#include "concepts.hpp"

namespace MEOJSON_NAMESPACE
{

template <typename T>
requires _utils::same_as_one_of<T, value, array, object>
inline std::ostream& operator<<(std::ostream& out, const T& val)
{
    out << val.format();
    return out;
}

}
