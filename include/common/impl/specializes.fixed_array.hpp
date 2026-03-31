#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

template <_utils::is_fixed_array T>
class jsonization<T>
{
public:
    constexpr static size_t N = _utils::fixed_array_size<T>;

    bool check_json(const array& arr) const noexcept
    {
        if (arr.size() != N) {
            return false;
        }
        for (const auto& val : arr) {
            if (!val.is<typename T::value_type>()) {
                return false;
            }
        }
        return true;
    }

    array to_json(const T& t) const
    {
        array arr;
        arr.reserve(N);
        for (size_t i = 0; i < N; i++) {
            arr.push_back(t.at(i));
        }
        return arr;
    }

    bool from_json(const array& arr, T& t) const
    {
        if (arr.size() != N) {
            return false;
        }
        for (size_t i = 0; i < N; i++) {
            t.at(i) = arr[i].as<typename T::value_type>();
        }
        return true;
    }

    array to_json(T&& t) const
    {
        array arr;
        arr.reserve(N);
        for (size_t i = 0; i < N; i++) {
            arr.push_back(std::move(t.at(i)));
        }
        return arr;
    }

    bool from_json(array&& arr, T& t) const
    {
        if (arr.size() != N) {
            return false;
        }
        for (size_t i = 0; i < N; i++) {
            t.at(i) = std::move(arr[i]).as<typename T::value_type>();
        }
        return true;
    }
};

}
