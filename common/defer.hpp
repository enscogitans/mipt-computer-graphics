#pragma once

#include <functional>

namespace utils {

class Defer {
    std::function<void()> func_;
public:
    template <class F>
    Defer(F&& f) : func_(std::forward<F>(f)) {}

    ~Defer() {
        func_();
    }
};

}  // namespace utils
