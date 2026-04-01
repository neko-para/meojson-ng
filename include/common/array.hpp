#pragma once

#if !defined(MEOJSON_MODULE)
#include <optional>
#include <vector>
#endif

#include "forward.hpp"
#include "impl/extends.hpp"

namespace json
{

MEOJSON_EXPORT class array
{
    friend class value;
    friend class object;

public:
    using raw_array = raw_array;

    using value_type = typename raw_array::value_type;
    using reference = typename raw_array::reference;
    using const_reference = typename raw_array::const_reference;
    using size_type = typename raw_array::size_type;
    using difference_type = typename raw_array::difference_type;
    using pointer = typename raw_array::pointer;
    using const_pointer = typename raw_array::const_pointer;

    using iterator = typename raw_array::iterator;
    using const_iterator = typename raw_array::const_iterator;
    using reverse_iterator = typename raw_array::reverse_iterator;
    using const_reverse_iterator = typename raw_array::const_reverse_iterator;

#pragma mark - Builtin
public:
    array();
    array(const array& rhs);
    array(array&& rhs) noexcept;
    ~array();

    array& operator=(const array& rhs);
    array& operator=(array&& rhs) noexcept;

    array(size_type size);

    array(std::initializer_list<value_type> list);

    template <ext::has_to_json_array T>
    array(T&& val);

    array(raw_array&& args);

#pragma mark - Checker
public:
    template <ext::has_check_json_array T>
    bool is() const noexcept;

    template <typename T>
    bool all() const noexcept;

    bool operator==(const array& rhs) const;
    bool operator!=(const array& rhs) const;

#pragma mark - Converter
public:
    template <ext::has_from_json_array T>
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
    explicit operator T() &&;

#pragma mark - Container
public:
    bool empty() const noexcept;
    size_t size() const noexcept;
    bool contains(size_t pos) const noexcept;
    bool exists(size_t pos) const noexcept;

    void clear() noexcept;
    void reserve(size_t capacity);
    size_t capacity() const noexcept;
    void push_back(const value_type& val);
    void push_back(value_type&& val);
    template <typename... args_t>
    reference emplace_back(args_t&&... args);
    bool erase(size_t pos);
    bool erase(iterator iter);
    const_reference& at(size_t pos) const;
    reference& at(size_t pos);

    const_reference& operator[](size_t pos) const;
    reference& operator[](size_t pos);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

#pragma mark - Manipulate
public:
    template <typename T = value>
    std::optional<T> find(size_t pos) const&;
    template <typename T = value>
    std::optional<T> find(size_t pos) &&;

    template <std::integral K, typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(const K& key, Ks&&... keys) const&;
    template <std::integral K, typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(const K& key, Ks&&... keys) &&;

    array operator+(const array& rhs) const&;
    array operator+(array&& rhs) const&;
    array operator+(const array& rhs) &&;
    array operator+(array&& rhs) &&;

    array& operator+=(const array& rhs);
    array& operator+=(array&& rhs);

#pragma mark - Stringify
public:
    std::string to_string() const;
    std::string format(size_t indent = 4) const;
    std::string dumps(std::optional<size_t> indent = std::nullopt) const;

private:
    std::string format(size_t indent, size_t indent_times) const;

private:
    raw_array _data;
};

}
