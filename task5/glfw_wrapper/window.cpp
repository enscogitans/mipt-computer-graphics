#include "window.hpp"

#include <common/exception.hpp>
#include <iostream>


namespace gl {

Window::Window(int width, int height, const std::string& title) {
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        throw utils::InitializationError("Failed to open GLFW window");
    }
}

Window::~Window() {
    glfwDestroyWindow(window_);
}

GLFWwindow* Window::GetPtr() const {
    return window_;
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window_) == GLFW_TRUE;
}

void Window::SetShouldClose(bool flag) {
    glfwSetWindowShouldClose(window_, flag ? GLFW_TRUE : GLFW_FALSE);
}

void Window::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window_, callback);
}

void Window::SetCursorPos(double x, double y) {
    glfwSetCursorPos(window_, x, y);
}

void Window::SetCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(window_, callback);
}

void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
    glfwSetMouseButtonCallback(window_, callback);
}

void Window::SetCursorRawInputMode(bool on) {
    int value = on ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(window_, GLFW_CURSOR, value);

    if (glfwRawMouseMotionSupported()) {
        value = on ? GLFW_TRUE : GLFW_FALSE;
        glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, value);
    } else if (on) {
        std::cerr << "GLFW raw mouse motion is not supported.\n";
    }
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window_);
}

}  // namespace gl
