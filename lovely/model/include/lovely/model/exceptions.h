#pragma once

#include <stdexcept>

namespace lovely {
namespace exception {
namespace model {

class key_not_found final : public std::exception {
    virtual const char* what() const throw() { return "key is not found"; }
};

class is_already_enrolled final : public std::exception {
    virtual const char* what() const throw() { return "key is already enrolled"; }
};

class allocation_failed final : public std::exception {
    virtual const char* what() const throw() { return "allocation failed"; }
};

class already_has_been_initialized final : public std::exception {
    virtual const char* what() const throw() { return "already has been initialized"; }
};

class callback_cannot_be_null final : public std::exception {
    virtual const char* what() const throw() { return "callback cannot be null"; }
};

}  // namespace model
}  // namespace exception
}  // namespace lovely