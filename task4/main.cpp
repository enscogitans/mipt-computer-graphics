#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <common/shader.hpp>
#include <common/defer.hpp>
#include <common/exception.hpp>

#include "dodecahedron.hpp"


glm::mat4 ComputeMvp(double time_now) {
    static const glm::mat4 projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    static const glm::mat4 model = glm::mat4(1.0f);  // An identity matrix (model will be at the origin)

    double radius = 6.0;
    double amplitude = 2;
    glm::vec3 camera_pos = {
            radius * sin(time_now),
            amplitude * sin(time_now),
            radius * cos(time_now),
    };

    glm::mat4 view = glm::lookAt(  // Camera matrix
            camera_pos,
            glm::vec3(0, 0, 0),  // It looks at the origin
            glm::vec3(0, 1, 0)   // Head is up
    );
    return projection * view * model;
}


int main() {
    if (int ok = glfwInit(); !ok) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }
    utils::Defer defer_1(glfwTerminate);  // Close (later) OpenGL window and terminate GLFW

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Task 4", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to open GLFW window. "
                     "If you have an Intel GPU, they are not 3.3 compatible. "
                     "Try the 2.1 version." << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true; // Global variable. Needed for core profile
    if (GLenum res = glewInit(); res != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return 1;
    }

    // Create VAO
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    utils::Defer defer_2 = [&]() { glDeleteVertexArrays(1, &vertex_array_id); };

    // Create and compile our GLSL program from the shaders
    GLuint program_id;
    try {
        program_id = utils::LoadShaders("vertex.shader", "fragment.shader");
    } catch (utils::IOException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    utils::Defer defer_3 = [&]() { glDeleteProgram(program_id); };

    // Initialize buffers
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dodecahedron::kTriangles), dodecahedron::kTriangles, GL_STATIC_DRAW);
    utils::Defer defer_4 = [&]() { glDeleteBuffers(1, &vertex_buffer); };

    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dodecahedron::kColors), dodecahedron::kColors, GL_STATIC_DRAW);
    utils::Defer defer_5 = [&]() { glDeleteBuffers(1, &color_buffer); };

    // Get a handle for our "mvp" uniform
    GLuint matrix_id = glGetUniformLocation(program_id, "mvp");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.5f, 0.9f, 1.0f, 0.0f);  // Light blue
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen

        glUseProgram(program_id);  // Use our shader

        // Send our transformation
        double time_now = glfwGetTime();
        glm::mat4 mvp = ComputeMvp(time_now);
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, glm::value_ptr(mvp));

        // Send our vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // Send our colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(dodecahedron::kTriangles));

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
