#pragma once

#include <stdexcept>

namespace utils {

class IOException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InitializationError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FormatError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

}  // namespace utils
