#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace gl {

class Window {
private:
    friend class Session;
    Window(int width, int height, const std::string& title);

public:
    ~Window();

    [[nodiscard]] GLFWwindow* GetPtr() const;

    [[nodiscard]] bool ShouldClose() const;

    void SetShouldClose(bool flag);

    void SetCursorPos(double x, double y);

    void SetKeyCallback(GLFWkeyfun callback);

    void SetCursorPosCallback(GLFWcursorposfun callback);

    void SetMouseButtonCallback(GLFWmousebuttonfun callback);

    void SetCursorRawInputMode(bool on);

    void SwapBuffers();

    template<typename T>
    void SetContext(T* ctx) {
        glfwSetWindowUserPointer(window_, static_cast<void*>(ctx));
    }

    template<typename T>
    static T* GetContext(GLFWwindow* window) {
        void* ctx = glfwGetWindowUserPointer(window);
        return static_cast<T*>(ctx);
    }

public:
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

private:
    GLFWwindow* window_;
};

}  // namespace gl
