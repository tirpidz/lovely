#pragma once

#include <stdexcept>

namespace lovely {
namespace exception {
namespace controller {

class callback_cannot_be_null final : public std::exception {
    virtual const char* what() const throw() { return "callback cannot be null"; }
};

}  // namespace controller
}  // namespace exception
}  // namespace lovely