#include "session.hpp"

#include <common/exception.hpp>


namespace gl {

Session::Session(int version_major, int version_minor, int msaa) {
    if (int ok = glfwInit(); !ok) {
        throw utils::InitializationError("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_SAMPLES, msaa);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Session::~Session() {
    glfwTerminate();
}

std::unique_ptr<Window> Session::MakeWindow(int width, int height, const std::string& title) {
    std::unique_ptr<Window> w{new Window(width, height, title)};
    glfwMakeContextCurrent(w->GetPtr());
    if (GLenum res = glewInit(); res != GLEW_OK) {
        throw utils::InitializationError("Failed to initialize GLEW");
    }
    return w;
}

void Session::PollEvents() {
    glfwPollEvents();
}

}  // namespace gl
