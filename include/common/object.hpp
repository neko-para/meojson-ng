#pragma once

#include <map>
#include <optional>
#include <string>

#include "forward.hpp"
#include "impl/extends.hpp"

namespace MEOJSON_NAMESPACE
{

class object
{
    friend class value;
    friend class array;

public:
    using raw_object = raw_object;

    using key_type = typename raw_object::key_type;
    using mapped_type = typename raw_object::mapped_type;
    using value_type = typename raw_object::value_type;
    using reference = typename raw_object::reference;
    using const_reference = typename raw_object::const_reference;
    using size_type = typename raw_object::size_type;
    using difference_type = typename raw_object::difference_type;
    using pointer = typename raw_object::pointer;
    using const_pointer = typename raw_object::const_pointer;

    using iterator = typename raw_object::iterator;
    using const_iterator = typename raw_object::const_iterator;
    using reverse_iterator = typename raw_object::reverse_iterator;
    using const_reverse_iterator = typename raw_object::const_reverse_iterator;

#pragma mark - Builtin
public:
    object();
    object(const object& rhs);
    object(object&& rhs) noexcept;
    ~object();

    object& operator=(const object& rhs);
    object& operator=(object&& rhs) noexcept;

    object(std::initializer_list<typename raw_object::value_type> list);

    template <ext::has_to_json_object T>
    object(T&& val);

#pragma mark - Checker
public:
    template <ext::has_check_json_object T>
    bool is() const noexcept;

    template <typename T>
    bool all() const noexcept;

    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const;

#pragma mark - Converter
public:
    template <ext::has_from_json_object T>
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
    template <all_object_key K>
    bool contains(const K& key) const;
    template <all_object_key K>
    bool exists(const K& key) const;

    void clear() noexcept;
    template <all_object_key K, typename V>
    requires std::is_constructible_v<object::mapped_type, V&&>
    std::pair<object::iterator, bool> insert(K&& key, V&& val);
    template <all_object_key K, typename V>
    requires std::is_constructible_v<object::mapped_type, V&&>
    std::pair<object::iterator, bool> emplace(K&& key, V&& val);
    template <all_object_key K>
    bool erase(const K& pos);
    bool erase(iterator iter);
    template <all_object_key K>
    iterator find_(const K& pos);
    template <all_object_key K>
    const_iterator find_(const K& pos) const;
    template <all_object_key K>
    const mapped_type& at(const K& key) const;
    template <all_object_key K>
    mapped_type& at(const K& key);

    mapped_type& operator[](const key_type& key);
    mapped_type& operator[](key_type&& key);

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
    template <typename T = value, all_object_key K = key_type>
    std::optional<T> find(const K& key) const&;
    template <typename T = value, all_object_key K = key_type>
    std::optional<T> find(const K& key) &&;

    template <all_object_key K, typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(const K& key, Ks&&... keys) const&;
    template <all_object_key K, typename... Ks>
    requires(sizeof...(Ks) > 0)
    _utils::get_access_t<Ks...> get(const K& key, Ks&&... keys) &&;

    object operator|(const object& rhs) const&;
    object operator|(object&& rhs) const&;
    object operator|(const object& rhs) &&;
    object operator|(object&& rhs) &&;

    object& operator|=(const object& rhs);
    object& operator|=(object&& rhs);

#pragma mark - Stringify
public:
    std::string to_string() const;
    std::string format(size_t indent = 4) const;
    std::string dumps(std::optional<size_t> indent = std::nullopt) const;

private:
    std::string format(size_t indent, size_t indent_times) const;

private:
    raw_object _data;
};

}
