#pragma once

#ifndef MEOJSON_MODULE
#include <format>
#endif

#include "../value.hpp"
#include "enum_reflection.hpp"

MEOJSON_EXPORT template <>
struct std::formatter<json::value::value_type, char> : public std::formatter<std::string_view>
{
    template <class FmtContext>
    FmtContext::iterator format(json::value::value_type type, FmtContext& ctx) const
    {
        std::string_view name = json::_reflection::enum_to_string(type);
        if (name.empty()) {
            name = "unknown";
        }
        return std::formatter<std::string_view, char>::format(name, ctx);
    }
};

MEOJSON_EXPORT template <>
struct std::formatter<json::value, char> : public std::formatter<std::string>
{
    template <class FmtContext>
    FmtContext::iterator format(json::value value, FmtContext& ctx) const
    {
        return std::formatter<std::string, char>::format(value.dumps(), ctx);
    }
};
