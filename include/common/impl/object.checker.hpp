#pragma once

#include "../object.hpp"
#include "../value.hpp"

namespace json
{

template <ext::has_check_json_object T>
inline bool object::is() const noexcept
{
    return ext::jsonization_wrapper<T>::check_json(*this);
}

template <typename T>
inline bool object::all() const noexcept
{
    for (const auto& [_, val] : *this) {
        if (!val.is<T>()) {
            return false;
        }
    }
    return true;
}

inline bool object::operator==(const object& rhs) const
{
    return _data == rhs._data;
}

inline bool object::operator!=(const object& rhs) const
{
    return _data != rhs._data;
}

}
