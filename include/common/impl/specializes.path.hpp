#pragma once

#include <filesystem>

#include "../value.hpp"
#include "extends.hpp"

namespace MEOJSON_NAMESPACE::ext
{

#if defined(MEOJSON_FS_PATH_EXTENSION)

template <>
class jsonization<std::filesystem::path>
{
public:
    bool check_json(const value& val) const noexcept { return val.is_string(); }

    value to_json(const std::filesystem::path& t) const { return t.string(); }

    bool from_json(const value& val, std::filesystem::path& t) const
    {
        if (val.is_string()) {
            t = val.as_string_unsafe();
            return true;
        }
        else {
            return false;
        }
    }

    value to_json(std::filesystem::path&& t) const { return t.string(); }

    bool from_json(value&& val, std::filesystem::path& t) const
    {
        if (val.is_string()) {
            t = std::move(val).as_string_unsafe();
            return true;
        }
        else {
            return false;
        }
    }
};

#endif

}
