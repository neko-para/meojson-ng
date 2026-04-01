#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

template <_utils::is_tuple_like T>
class jsonization<T>
{
public:
    constexpr static size_t N = std::tuple_size_v<T>;
    static_assert(N > 0);

    bool check_json(const array& arr) const noexcept
    {
        if (arr.size() != N) {
            return false;
        }
        return [&]<size_t... Is>(std::index_sequence<Is...>) {
            return (arr[Is].is<std::tuple_element_t<Is, T>>() && ...);
        }(std::make_index_sequence<N>());
    }

    array to_json(const T& t) const
    {
        array arr;
        arr.reserve(N);
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            ((arr.push_back(get<Is>(t))), ...);
        }(std::make_index_sequence<N>());
        return arr;
    }

    bool from_json(const array& arr, T& t) const
    {
        if (arr.size() != N) {
            return false;
        }
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            ((get<Is>(t) = arr[Is].as<std::tuple_element_t<Is, T>>()), ...);
        }(std::make_index_sequence<N>());
        return true;
    }

    array to_json(T&& t) const
    {
        array arr;
        arr.reserve(N);
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            ((arr.push_back(get<Is>(std::move(t)))), ...);
        }(std::make_index_sequence<N>());
        return arr;
    }

    bool from_json(array&& arr, T& t) const
    {
        if (arr.size() != N) {
            return false;
        }
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            using std::get;
            ((get<Is>(t) = std::move(arr[Is]).as<std::tuple_element_t<Is, T>>()), ...);
        }(std::make_index_sequence<N>());
        return true;
    }
};

}
