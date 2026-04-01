// IWYU pragma: private, include <meojson/json.hpp>

#pragma once

#if !defined(MEOJSON_MODULE)
#include <string>
#include <type_traits>
#include <utility>
#endif

#include "../common/types.hpp"

namespace json::_jsonization_helper
{
struct next_is_optional_t
{
};

struct next_override_key_t
{
    const char* key;
};

struct next_state_t
{
    bool is_optional = false;
    const char* override_key = nullptr;
};

struct va_arg_end
{
};

template <typename tag_t>
struct is_tag_t : public std::false_type
{
};

template <>
struct is_tag_t<next_is_optional_t> : public std::true_type
{
};

template <>
struct is_tag_t<next_override_key_t> : public std::true_type
{
};

struct dumper
{
    void _to_json(object&, va_arg_end) const { }

    template <typename... rest_t>
    void _to_json(object& result, const char* key, rest_t&&... rest) const
    {
        _to_json(result, next_state_t { }, key, std::forward<rest_t>(rest)...);
    }

    template <typename var_t, typename... rest_t, typename _ = std::enable_if_t<!is_tag_t<var_t>::value, void>>
    void _to_json(object& result, next_state_t state, const char* key, const var_t& var, rest_t&&... rest) const
    {
        if (state.override_key) {
            key = state.override_key;
        }

        result.emplace(key, var);

        _to_json(result, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    void _to_json(object& result, next_state_t state, const char*, next_is_optional_t, rest_t&&... rest) const
    {
        state.is_optional = true;
        _to_json(result, state, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    void _to_json(object& result, next_state_t state, const char*, next_override_key_t override_key, rest_t&&... rest) const
    {
        state.override_key = override_key.key;
        _to_json(result, state, std::forward<rest_t>(rest)...);
    }
};

struct checker
{
    bool _check_json(const value&, std::string&, va_arg_end) const noexcept { return true; }

    template <typename... rest_t>
    bool _check_json(const value& in, std::string& error_key, const char* key, rest_t&&... rest) const noexcept
    {
        return _check_json(in, error_key, next_state_t { }, key, std::forward<rest_t>(rest)...);
    }

    template <typename var_t, typename... rest_t, typename _ = std::enable_if_t<!is_tag_t<var_t>::value, void>>
    bool _check_json(const value& in, std::string& error_key, next_state_t state, const char* key, const var_t&, rest_t&&... rest)
        const noexcept
    {
        if (state.override_key) {
            key = state.override_key;
        }
        auto opt = in.find(key);

        if (opt) {
            if (!opt->is<var_t>()) {
                error_key = key;
                return false;
            }
        }
        else if (state.is_optional) {
            // is_optional, ignore key not found
        }
        else {
            error_key = key;
            return false;
        }

        return _check_json(in, error_key, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    bool _check_json(const value& in, std::string& error_key, next_state_t state, const char*, next_is_optional_t, rest_t&&... rest)
        const noexcept
    {
        state.is_optional = true;
        return _check_json(in, error_key, state, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    bool _check_json(
        const value& in,
        std::string& error_key,
        next_state_t state,
        const char*,
        next_override_key_t override_key,
        rest_t&&... rest) const noexcept
    {
        state.override_key = override_key.key;
        return _check_json(in, error_key, state, std::forward<rest_t>(rest)...);
    }
};

struct loader
{
    bool _from_json(const value&, std::string&, va_arg_end) const { return true; }

    template <typename... rest_t>
    bool _from_json(const value& in, std::string& error_key, const char* key, rest_t&&... rest)
    {
        return _from_json(in, error_key, next_state_t { }, key, std::forward<rest_t>(rest)...);
    }

    template <typename var_t, typename... rest_t, typename _ = std::enable_if_t<!is_tag_t<var_t>::value, void>>
    bool _from_json(const value& in, std::string& error_key, next_state_t state, const char* key, var_t& var, rest_t&&... rest)
    {
        if (state.override_key) {
            key = state.override_key;
        }
        auto opt = in.find(key);
        if (opt) {
            if (opt->is<var_t>()) {
                var = std::move(opt)->as<var_t>();
            }
            else {
                error_key = key;
                return false;
            }
        }
        else if (state.is_optional) {
            // is_optional, ignore key not found
        }
        else {
            error_key = key;
            return false;
        }

        return _from_json(in, error_key, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    bool _from_json(const value& in, std::string& error_key, next_state_t state, const char*, next_is_optional_t, rest_t&&... rest)
    {
        state.is_optional = true;
        return _from_json(in, error_key, state, std::forward<rest_t>(rest)...);
    }

    template <typename... rest_t>
    bool _from_json(
        const value& in,
        std::string& error_key,
        next_state_t state,
        const char*,
        next_override_key_t override_key,
        rest_t&&... rest)
    {
        state.override_key = override_key.key;
        return _from_json(in, error_key, state, std::forward<rest_t>(rest)...);
    }
};
} // namespace json::_jsonization_helper
