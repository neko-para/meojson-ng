#pragma once

#include "forward.hpp"

#include <optional>
#include <string>
#include <variant>

#include "impl/concepts.hpp"
#include "impl/extends.hpp"

namespace MEOJSON_NAMESPACE
{

class value
{
    friend class array;
    friend class object;

    template <typename T>
    requires(!_utils::is_initializer_list<T>)
    friend struct ext::jsonization_wrapper;

public:
    using raw_value = raw_value;
    using var_t = raw_value;

    enum class value_type : std::uint8_t
    {
        invalid,
        null,
        boolean,
        number,
        string,
        array,
        object
    };

#pragma mark - Builtin
public:
    value();
    value(const value& rhs);
    value(value&& rhs) noexcept;
    ~value();

    value& operator=(const value& rhs);
    value& operator=(value&& rhs) noexcept;

    value(nullptr_t);
    value(std::monostate);

    value(bool b);

    template <std::integral var_t>
    value(var_t num);

    template <std::floating_point var_t>
    value(var_t num);

    value(const char* str);
    value(std::string str);
    value(std::string_view str);

    value(const array& arr);
    value(array&& arr);

    value(const object& obj);
    value(object&& obj);

    value(std::initializer_list<typename raw_object::value_type> list);

    template <typename enum_t>
    requires std::is_enum_v<enum_t>
    value(enum_t num);

    value(char) = delete;
    value(wchar_t) = delete;
    value(char16_t) = delete;
    value(char32_t) = delete;

    template <ext::has_to_json T>
    value(T&& val);

    // Constructed from raw data
    template <typename... args_t>
    requires std::is_constructible_v<raw_value, args_t...>
    value(value_type type, args_t&&... args);

#pragma mark - Checker
public:
    bool valid() const noexcept;
    bool empty() const noexcept;
    value_type type() const noexcept;

    bool is_null() const noexcept;
    bool is_boolean() const noexcept;
    bool is_number() const noexcept;
    bool is_string() const noexcept;
    bool is_array() const noexcept;
    bool is_object() const noexcept;

    template <typename T>
    bool is() const noexcept;

    template <typename T>
    bool all() const noexcept;

    bool operator==(const value& rhs) const;
    bool operator!=(const value& rhs) const;

#pragma mark - Converter
public:
    explicit operator std::nullptr_t() const;
    explicit operator std::monostate() const;

    bool as_boolean() const;
    explicit operator bool() const;

    int as_integer() const;
    unsigned as_unsigned() const;
    long as_long() const;
    unsigned long as_unsigned_long() const;
    long long as_long_long() const;
    unsigned long long as_unsigned_long_long() const;
    float as_float() const;
    double as_double() const;
    long double as_long_double() const;
    explicit operator int() const;
    explicit operator unsigned() const;
    explicit operator long() const;
    explicit operator unsigned long() const;
    explicit operator long long() const;
    explicit operator unsigned long long() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;

    const std::string& as_string() const&;
    std::string& as_string() &;
    std::string as_string() &&;
    explicit operator std::string() const&;
    explicit operator std::string() &&;

    std::string_view as_string_view() const&;
    std::string_view as_string_view() const&& = delete;
    explicit operator std::string_view() const&;
    explicit operator std::string_view() const&& = delete;

    const array& as_array() const&;
    array& as_array() &;
    array as_array() &&;
    const array& as_array_unsafe() const& noexcept;
    array& as_array_unsafe() & noexcept;
    array as_array_unsafe() && noexcept;
    explicit operator array() const&;
    explicit operator array() &&;

    const object& as_object() const&;
    object& as_object() &;
    object as_object() &&;
    const object& as_object_unsafe() const& noexcept;
    object& as_object_unsafe() & noexcept;
    object as_object_unsafe() && noexcept;
    explicit operator object() const&;
    explicit operator object() &&;

    template <typename enum_t>
    requires std::is_enum_v<enum_t>
    explicit operator enum_t() const;

    template <typename T>
    requires(!_utils::support_as_ref<T>)
    T as() const&;
    template <_utils::support_as_ref T>
    const T& as() const&;
    template <_utils::support_as_ref T>
    T& as() &;
    template <typename T>
    T as() &&;

    template <typename T>
    explicit operator T() const&;
    template <typename T>
    requires(!_utils::is_builtin_primitive_without_string<T>)
    explicit operator T() &&;

#pragma mark - Container
public:
    bool contains(size_t pos) const noexcept;
    bool exists(size_t pos) const noexcept;

    template <all_object_key K>
    bool contains(const K& key) const;
    template <all_object_key K>
    bool exists(const K& key) const;

    // actually set to null
    void clear() noexcept;
    template <typename V>
    requires std::is_constructible_v<value, V&&>
    auto emplace(V&& val);
    template <all_object_key K, typename V>
    requires std::is_constructible_v<value, V&&>
    auto emplace(K&& key, V&& val);
    bool erase(size_t pos);
    template <all_object_key K>
    bool erase(const K& pos);
    const value& at(size_t pos) const;
    value& at(size_t pos);
    template <all_object_key K>
    const value& at(const K& key) const;
    template <all_object_key K>
    value& at(const K& key);

    const value& operator[](size_t pos) const;
    value& operator[](size_t pos);
    value& operator[](const raw_object::key_type& key);
    value& operator[](raw_object::key_type&& key);

#pragma mark - Manipulate
public:
    template <typename T = value>
    std::optional<T> find(size_t pos) const&;
    template <typename T = value>
    std::optional<T> find(size_t pos) &&;

    template <typename T = value, all_object_key K = raw_object::key_type>
    std::optional<T> find(const K& key) const&;
    template <typename T = value, all_object_key K = raw_object::key_type>
    std::optional<T> find(const K& key) &&;

    template <typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(Ks&&... keys) const&;
    template <typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(Ks&&... keys) &&;

    value operator+(const array& rhs) const&;
    value operator+(array&& rhs) const&;
    value operator+(const array& rhs) &&;
    value operator+(array&& rhs) &&;

    value& operator+=(const array& rhs);
    value& operator+=(array&& rhs);

    value operator|(const object& rhs) const&;
    value operator|(object&& rhs) const&;
    value operator|(const object& rhs) &&;
    value operator|(object&& rhs) &&;

    value& operator|=(const object& rhs);
    value& operator|=(object&& rhs);

private:
    template <typename Ret, typename K, typename... Ks>
    _utils::wrap_string_t<std::decay_t<Ret>> get_helper(Ret&& def, K&& key, Ks&&... keys) const&;
    template <typename Ret, typename K, typename... Ks>
    _utils::wrap_string_t<std::decay_t<Ret>> get_helper(Ret&& def, K&& key, Ks&&... keys) &&;
    template <typename Ret>
    _utils::wrap_string_t<std::decay_t<Ret>> get_helper(Ret&& def) const&;
    template <typename Ret>
    _utils::wrap_string_t<std::decay_t<Ret>> get_helper(Ret&& def) &&;

#pragma mark - Stringify
public:
    std::string to_string() const;
    std::string format(size_t indent = 4) const;
    std::string dumps(std::optional<size_t> indent = std::nullopt) const;

private:
    std::string format(size_t indent, size_t indent_times) const;

private:
    static raw_value deep_copy(const raw_value& src);

    [[noreturn]] void throw_type_error(value_type expected) const;

    const std::string& as_basic_type_str() const;
    std::string& as_basic_type_str();
    const std::string& as_basic_type_str_unsafe() const noexcept;
    std::string& as_basic_type_str_unsafe() noexcept;

    value_type _type = value_type::null;
    raw_value _data;
};

}
