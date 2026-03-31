#pragma once

#include "../array.hpp"
#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

template <ext::has_check_json_array T>
inline bool array::is() const noexcept
{
    return ext::jsonization_wrapper<T>::check_json(*this);
}

template <typename T>
inline bool array::all() const noexcept
{
    for (const auto& val : *this) {
        if (!val.is<T>()) {
            return false;
        }
    }
    return true;
}

inline bool array::operator==(const array& rhs) const
{
    return _data == rhs._data;
}

inline bool array::operator!=(const array& rhs) const
{
    return _data != rhs._data;
}

}
