#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

class type_mismatch final : public std::exception {
    virtual const char* what() const throw() { return "type mismatch"; }
};

}  // namespace exception

template <class T>
class listing {
public:
    listing() = default;
    ~listing() = default;

    listing(listing&) = delete;
    listing& operator=(const listing&) = delete;

    void enroll(const std::string& key)
    {
        auto unique_pointer = std::make_unique<T>();
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

template <class... Types>
class registry final : public listing<Types>... {
public:
    registry() {}
    ~registry() = default;

    registry(registry&) = delete;
    registry& operator=(const registry&) = delete;

    template <typename T>
    void enroll(const std::initializer_list<std::string>& keys)
    {
        for (auto key : keys) {
            listing<T>::enroll(key);
        }
    }

    template <class T>
    const T& get(const std::string& key) const
    {
        return listing<T>::get(key);
    }

    template <class T>
    const std::vector<T const*>& all() const
    {
        return listing<T>::all();
    }
};

}  // namespace lovely
