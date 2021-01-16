#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>

namespace lovely {

template <class M>
class registry final {
public:
    Registry() = default;
    virtual ~Registry() = default;

    template <class T>
    T* get(const std::string& key) const
    {
        const std::size_t hash = getHash<T>();

        auto it = classes_.constFind(hash);

        if (it == classes_.cend()) {
            return nullptr;
        }

        return static_cast<T*>(*it);
    }

    template <class T>
    QString getName(const T*) const
    {
        return getName<T>();
    }

    template <class T>
    bool enroll(const std::string& key)
    {
        Class manager = std::make_unique<T>(*this);
        M* ptr = manager.get();

        if (ptr == nullptr) {
            LH_WARN("manager allocation failed");
            return false;
        }

        const std::size_t hash = getHash<T>();

        if (classes_.contains(hash)) {
            LH_WARN("manager(" << getName<T>() << ") with hash(" << hash << ") already registered : skipping... ");
            return false;
        }

        classes_.insert(hash, ptr);
        pointers_.insert(std::move(manager));
        return true;
    }

private:
    template <class T>
    constexpr std::size_t get_hash() const
    {
        return typeid(T).hash_code();
    }

    template <class T>
    constexpr std::string get_name() const
    {
        return typeid(T).name();
    }
};

}  // namespace lovely
