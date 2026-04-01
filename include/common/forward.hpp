#pragma once

#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#ifndef MEOJSON_NAMESPACE
#define MEOJSON_NAMESPACE json
#endif

namespace MEOJSON_NAMESPACE
{

class value;
class array;
class object;

using array_ptr = std::unique_ptr<array>;
using object_ptr = std::unique_ptr<object>;
using raw_value = std::variant<std::string, array_ptr, object_ptr>;
using raw_array = std::vector<value>;
using raw_object = std::map<std::string, value>;

template <typename T>
concept all_object_key = requires(T t, raw_object o) { o.find(t); };

}
