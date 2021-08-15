#pragma once

#include <stdexcept>

namespace lovely {
namespace exception {
namespace view {

class model_not_initialized final : public std::exception {
    virtual const char* what() const throw() { return "model not initialized"; }
};

}  // namespace view
}  // namespace exception
}  // namespace lovely