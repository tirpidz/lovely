#pragma once

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

template <typename T>
class listing {
public:
    listing() = default;
    ~listing() = default;

    listing(listing&) = delete;
    listing& operator=(const listing&) = delete;

    void enroll(const std::string& key)
    {
        auto it = _map.find(key);

        if (it != _map.cend()) {
            throw exception::is_already_enrolled();
        }

        auto unique_pointer = std::make_unique<T>();

        if (unique_pointer == nullptr) {
            throw exception::allocation_failed();
        }

        T* pointer = unique_pointer.get();
        _map.insert({key, pointer});
        _all.push_back(pointer);
        _pointers.push_back(std::move(unique_pointer));
    }

    const T& get(const std::string& key) const
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::key_not_found();
        }

        return *(it->second);
    }

    const std::vector<T const*>& all() const { return _all; }

protected:
    std::unordered_map<std::string, T const*> _map;
    std::vector<T const*> _all;
    std::vector<std::unique_ptr<T>> _pointers;
};

template <typename... types>
class registry final : public listing<types>... {
public:
    registry() {}
    ~registry() = default;

    registry(registry&) = delete;
    registry& operator=(const registry&) = delete;

    template <typename T>
    void enroll(const std::initializer_list<std::string>& keys)
    {
        for (const auto& key : keys) {
            listing<T>::enroll(key);
        }
    }

    template <typename T>
    const T& single(const std::string& key) const
    {
        return listing<T>::get(key);
    }

    template <typename... sub_types>
    const std::tuple<sub_types...>& many(const std::string& key) const
    {
        auto tuple = std::tuple<sub_types...>();
        std::apply([&](auto&&... args) { ((args = single<typeof(args)>(key)), ...); }, tuple);
        return std::move(tuple);
    }

    template <typename T>
    const std::vector<T const*>& all() const
    {
        return listing<T>::all();
    }
};

}  // namespace lovely
