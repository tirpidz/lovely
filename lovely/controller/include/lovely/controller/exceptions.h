#pragma once

#include <stdexcept>

namespace lovely::exception::controller {

class model_not_initialized final : public std::exception {
    virtual const char* what() const throw() { return "model not initialized"; }
};

class base_class_not_executor final : public std::exception {
    virtual const char* what() const throw() { return "base class not executor"; }
};

}  // namespace lovely::exception::controller