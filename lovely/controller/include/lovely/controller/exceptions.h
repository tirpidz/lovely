#pragma once

#include <stdexcept>

namespace lovely {
namespace exception {
namespace controller {

class model_is_not_initialized final : public std::exception {
    virtual const char* what() const throw() { return "model is not initialized"; }
};

class callback_cannot_be_null final : public std::exception {
    virtual const char* what() const throw() { return "callback cannot be null"; }
};

}  // namespace controller
}  // namespace exception
}  // namespace lovely