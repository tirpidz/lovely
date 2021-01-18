#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace lovely {

namespace exception {

class key_not_found final : public std::exception {
    virtual const char* what() const throw() { return "key is not found"; }
};

class is_already_enrolled final : public std::exception {
    virtual const char* what() const throw() { return "key is already enrolled"; }
};

class allocation_failed final : public std::exception {
    virtual const char* what() const throw() { return "allocation failed"; }
};

}  // namespace exception

template <typename type>
class listing {
public:
    listing() = default;
    ~listing() = default;

    listing(listing&) = delete;
    listing& operator=(const listing&) = delete;

    void enroll(const std::string& key, const type& value)
    {
        auto it = _map.find(key);

        if (it != _map.cend()) {
            throw exception::is_already_enrolled();
        }

        auto unique_pointer = std::make_unique<type>(value);

        if (unique_pointer == nullptr) {
            throw exception::allocation_failed();
        }

        type* pointer = unique_pointer.get();
        _map.insert({key, pointer});
        _all.push_back(*pointer);
        _pointers.push_back(std::move(unique_pointer));
    }

    const type& get(const std::string& key) const
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::key_not_found();
        }

        return *(it->second);
    }

    void set(const std::string& key, const type& value)
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::key_not_found();
        }

        *(it->second) = value;
    }

    const std::vector<std::reference_wrapper<type>>& all() const { return _all; }

protected:
    std::unordered_map<std::string, type*> _map;
    std::vector<std::reference_wrapper<type>> _all;
    std::vector<std::unique_ptr<type>> _pointers;
};

template <typename... types>
class registry final : public listing<types>... {
public:
    registry() {}
    ~registry() = default;

    registry(registry&) = delete;
    registry& operator=(const registry&) = delete;

    template <typename type>
    void enroll(std::initializer_list<std::pair<std::string, type>> pairs)
    {
        for (const auto& pair : pairs) {
            listing<type>::enroll(pair.first, pair.second);
        }
    }

    template <typename type>
    const type& single(const std::string& key) const
    {
        return listing<type>::get(key);
    }

    template <typename type>
    void set_single(const std::string& key, const type& value)
    {
        listing<type>::set(key, value);
    }

    template <typename... sub_types>
    std::tuple<const sub_types...> many(const std::string& key) const
    {
        auto tuple = std::tuple<sub_types...>();
        std::apply([&](auto&&... args) { ((args = single<typeof(args)>(key)), ...); }, tuple);
        return tuple;
    }

    template <typename... sub_types>
    void set_many(const std::string& key, const sub_types&... value)
    {
        (..., set_single(key, value));
    }

    template <typename type>
    const std::vector<std::reference_wrapper<type>>& all() const
    {
        return listing<type>::all();
    }
};

}  // namespace lovely
