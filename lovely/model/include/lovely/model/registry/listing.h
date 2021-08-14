#pragma one

#include <lovely/model/exceptions.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace lovely {

template <typename type>
class listing {
public:
    listing() = default;
    virtual ~listing() = default;

    listing(const listing&) = delete;
    listing& operator=(const listing&) = delete;

    void enroll(const std::string& key, const type& value)
    {
        auto it = _map.find(key);

        if (it != _map.cend()) {
            throw exception::model::is_already_enrolled();
        }

        auto unique_pointer = std::make_unique<type>(value);

        if (unique_pointer == nullptr) {
            throw exception::model::allocation_failed();
        }

        type* pointer = unique_pointer.get();

        if (pointer == nullptr) {
            throw exception::model::allocation_failed();
        }

        _map.insert({key, pointer});
        _call.push_back(pointer);
        _all.push_back(pointer);
        _pointers.push_back(std::move(unique_pointer));
    }

    void cget(const std::string& key, type const*& value) const
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::model::key_not_found();
        }

        value = it->second;
    }

    void get(const std::string& key, type*& value)
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::model::key_not_found();
        }

        value = it->second;
    }

    void set(const std::string& key, const type& value)
    {
        const auto it = _map.find(key);

        if (it == _map.cend()) {
            throw exception::model::key_not_found();
        }

        *(it->second) = value;
    }

    void call(std::vector<type const*>& all) const { all = _call; }
    void all(std::vector<type*>& all) { all = _all; }

protected:
    std::unordered_map<std::string, type*> _map;
    std::vector<type const*> _call;
    std::vector<type*> _all;
    std::vector<std::unique_ptr<type>> _pointers;
};

}