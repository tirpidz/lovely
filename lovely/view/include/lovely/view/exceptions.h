#pragma once

#include <stdexcept>

namespace lovely::exception::view {

class model_not_initialized final : public std::exception {
    virtual const char* what() const throw() { return "model not initialized"; }
};

}  // namespace lovely::exception::view