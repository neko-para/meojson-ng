#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "exception.hpp"
#include "extends.impl.hpp"

namespace json::ext
{

template <_utils::is_fixed_array T>
class jsonization<T>
{
public:
    constexpr static size_t N = _utils::fixed_array_size<T>;
    using inner_type = T::value_type;

    bool check_json(const array& arr) const noexcept
    requires can_check_value<inner_type>
    {
        if (arr.size() != N) {
            return false;
        }
        for (const auto& val : arr) {
            if (!val.is<inner_type>()) {
                return false;
            }
        }
        return true;
    }

    array to_json(const T& t) const
    requires can_to_value<inner_type>
    {
        array arr;
        arr.reserve(N);
        for (size_t i = 0; i < N; i++) {
            arr.push_back(t.at(i));
        }
        return arr;
    }

    bool from_json(const array& arr, T& t) const
    requires can_from_value<inner_type>
    {
        if (arr.size() != N) {
            throw type_error { _reflection::type_name<T>(), value::value_type::array, arr };
        }
        for (size_t i = 0; i < N; i++) {
            t.at(i) = arr[i].as<inner_type>();
        }
        return true;
    }

    array to_json(T&& t) const
    requires can_to_value<inner_type>
    {
        array arr;
        arr.reserve(N);
        for (size_t i = 0; i < N; i++) {
            arr.push_back(std::move(t.at(i)));
        }
        return arr;
    }

    bool from_json(array&& arr, T& t) const
    requires can_from_value<inner_type>
    {
        if (arr.size() != N) {
            throw type_error { _reflection::type_name<T>(), value::value_type::array, arr };
        }
        for (size_t i = 0; i < N; i++) {
            t.at(i) = std::move(arr[i]).as<inner_type>();
        }
        return true;
    }
};

}
