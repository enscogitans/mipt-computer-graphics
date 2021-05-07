#pragma once

#include <string>
#include <memory>

#include "window.hpp"


namespace gl {

class Session {
public:
    Session(int version_major, int version_minor, int msaa);

    ~Session();

    std::unique_ptr<Window> MakeWindow(int width, int height, const std::string& title);

    void PollEvents();

public:
    Session(Session&&) = delete;
    Session& operator=(Session&&) = delete;
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
};

}  // namespace gl
