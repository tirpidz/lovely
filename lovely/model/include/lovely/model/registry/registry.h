#pragma once

#include <lovely/model/exceptions.h>
#include <lovely/model/registry/listing.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lovely {

template <typename... types>
class registry : private listing<types>... {
public:
    registry() = default;
    virtual ~registry() = default;

    registry(const registry&) = delete;
    registry& operator=(const registry&) = delete;

    template <typename type>
    void enroll(std::initializer_list<std::pair<std::string, type>> pairs)
    {
        for (const auto& pair : pairs) {
            listing<type>::enroll(pair.first, pair.second);
        }
    }

    template <typename... sub_types>
    void cget(const std::string& key, sub_types const*&... value) const
    {
        (..., listing<sub_types>::cget(key, value));
    }

    template <typename... sub_types>
    void get(const std::string& key, sub_types*&... value)
    {
        (..., listing<sub_types>::get(key, value));
    }

    template <typename... sub_types>
    void set(const std::string& key, const sub_types&... value)
    {
        (..., listing<sub_types>::set(key, value));
    }

    template <typename type>
    void call(std::vector<type const*>& all) const
    {
        listing<type>::call(all);
    }

    template <typename type>
    void all(std::vector<type*>& all)
    {
        listing<type>::all(all);
    }
};

}  // namespace lovely
