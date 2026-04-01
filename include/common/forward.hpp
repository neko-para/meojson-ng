#pragma once

#if !defined(MEOJSON_MODULE)
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#endif

#ifndef MEOJSON_EXPORT
#define MEOJSON_EXPORT
#endif

namespace json
{

MEOJSON_EXPORT class value;
MEOJSON_EXPORT class array;
MEOJSON_EXPORT class object;

using array_ptr = std::unique_ptr<array>;
using object_ptr = std::unique_ptr<object>;
using raw_value = std::variant<std::string, array_ptr, object_ptr>;
using raw_array = std::vector<value>;
using raw_object = std::map<std::string, value>;

template <typename T>
concept all_object_key = requires(T t, raw_object o) { o.find(t); };

}
