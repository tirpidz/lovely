#pragma once

#include <stdexcept>

namespace lovely::exception::model {

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

}  // namespace lovely::exception::model