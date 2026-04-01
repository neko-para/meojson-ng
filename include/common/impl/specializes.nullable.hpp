#pragma once

#include "../array.hpp"
#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

template <_utils::is_nullable T>
class jsonization<T>
{
public:
    bool check_json(const value& val) const noexcept { return val.is_null() || val.is<_utils::nullable_value_t<T>>(); }

    value to_json(const T& t) const
    {
        if (t) {
            return value { *t };
        }
        else {
            return { };
        }
    }

    bool from_json(const value& val, T& t) const
    requires _utils::is_optional<T> || _utils::is_shared_ptr<T> || _utils::is_unique_ptr<T>
    {
        if constexpr (_utils::is_optional<T>) {
            if (val.is_null()) {
                t = std::nullopt;
            }
            else {
                t = val.as<T>();
            }
            return true;
        }
        else if constexpr (_utils::is_shared_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_shared<T>(val.as<T>());
            }
            return true;
        }
        else if constexpr (_utils::is_unique_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_unique<T>(val.as<T>());
            }
            return true;
        }
        else {
            static_assert(false);
        }
    }

    value to_json(T&& t) const
    {
        if (t) {
            return value { std::move(*t) };
        }
        else {
            return { };
        }
    }

    bool from_json(value&& val, T& t) const
    requires _utils::is_optional<T> || _utils::is_shared_ptr<T> || _utils::is_unique_ptr<T>
    {
        if constexpr (_utils::is_optional<T>) {
            if (val.is_null()) {
                t = std::nullopt;
            }
            else {
                t = std::move(val).as<T>();
            }
            return true;
        }
        else if constexpr (_utils::is_shared_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_shared<T>(std::move(val).as<T>());
            }
            return true;
        }
        else if constexpr (_utils::is_unique_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_unique<T>(std::move(val).as<T>());
            }
            return true;
        }
        else {
            static_assert(false);
        }
    }
};

}
