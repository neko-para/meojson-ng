#pragma once

#include "../value.hpp"
#include "extends.impl.hpp"

namespace json::ext
{

template <_utils::is_nullable T>
class jsonization<T>
{
public:
    using inner_type = _utils::nullable_value_t<T>;

    bool check_json(const value& val) const noexcept
    requires can_check_value<inner_type>
    {
        return val.is_null() || val.is<inner_type>();
    }

    value to_json(const T& t) const
    requires can_to_value<inner_type>
    {
        if (t) {
            return value { *t };
        }
        else {
            return { };
        }
    }

    bool from_json(const value& val, T& t) const
    requires(_utils::is_optional<T> || _utils::is_shared_ptr<T> || _utils::is_unique_ptr<T>) && can_from_value<inner_type>
    {
        if constexpr (_utils::is_optional<T>) {
            if (val.is_null()) {
                t = std::nullopt;
            }
            else {
                t = val.as<inner_type>();
            }
            return true;
        }
        else if constexpr (_utils::is_shared_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_shared<inner_type>(val.as<inner_type>());
            }
            return true;
        }
        else if constexpr (_utils::is_unique_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_unique<inner_type>(val.as<inner_type>());
            }
            return true;
        }
        else {
            static_assert(false);
        }
    }

    value to_json(T&& t) const
    requires can_to_value<inner_type>
    {
        if (t) {
            return value { std::move(*t) };
        }
        else {
            return { };
        }
    }

    bool from_json(value&& val, T& t) const
    requires(_utils::is_optional<T> || _utils::is_shared_ptr<T> || _utils::is_unique_ptr<T>) && can_from_value<inner_type>
    {
        if constexpr (_utils::is_optional<T>) {
            if (val.is_null()) {
                t = std::nullopt;
            }
            else {
                t = std::move(val).as<inner_type>();
            }
            return true;
        }
        else if constexpr (_utils::is_shared_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_shared<inner_type>(std::move(val).as<inner_type>());
            }
            return true;
        }
        else if constexpr (_utils::is_unique_ptr<T>) {
            if (val.is_null()) {
                t = nullptr;
            }
            else {
                t = std::make_unique<inner_type>(std::move(val).as<inner_type>());
            }
            return true;
        }
        else {
            static_assert(false);
        }
    }
};

}
