#include <iostream>
#include <forward_list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <common/shader.hpp>
#include <common/defer.hpp>
#include <common/exception.hpp>


glm::mat4 ComputeMvp(double time_now) {
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    static const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    static const glm::mat4 model = glm::mat4(1.0f);  // Model matrix: an identity matrix (model will be at the origin)

    const double radius = 4;
    glm::vec3 camera_pos = {
            radius * sin(time_now),
            0,
            radius * cos(time_now),
    };

    glm::mat4 view = glm::lookAt(  // Camera matrix
            camera_pos,  // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0),  // and looks at the origin
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
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Task 3", nullptr, nullptr);
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
    GLuint program_id_1;
    GLuint program_id_2;
    std::forward_list<utils::Defer> defer_3;
    try {
        program_id_1 = utils::LoadShaders("vertex.shader", "fragment_1.shader");
        defer_3.emplace_front([&]() { glDeleteProgram(program_id_1); });
        program_id_2 = utils::LoadShaders("vertex.shader", "fragment_2.shader");
        defer_3.emplace_front([&]() { glDeleteProgram(program_id_2); });
    } catch (utils::IOException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Initialize triangles' coordinates
    const int kCoordsArraySize = 9;
    const GLfloat kTriangleCoords1[kCoordsArraySize] = {
            -0.75f, -0.5f, -0.5f,
            0.25f, -0.5f, -0.5f,
            -0.25f, 0.866f, -0.5f,
    };
    const GLfloat kTriangleCoords2[kCoordsArraySize] = {
            -0.25f, -0.7f, 0.5f,
            0.75f, -0.7f, 0.5f,
            0.25f, 0.666f, 0.5f,
    };

    GLuint vertex_buffer_1;
    GLuint vertex_buffer_2;
    for (auto& [vertex_buffer, triangle_coords] : std::initializer_list<std::pair<GLuint&, const GLfloat*>>{
            {vertex_buffer_1, kTriangleCoords1},
            {vertex_buffer_2, kTriangleCoords2}
    }) {
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_coords[0]) * kCoordsArraySize, triangle_coords, GL_STATIC_DRAW);
    }
    utils::Defer defer_4 = [&]() {
        glDeleteBuffers(1, &vertex_buffer_1);
        glDeleteBuffers(1, &vertex_buffer_2);
    };

    // Get a handle for our "mvp" uniform
    GLuint matrix_id_1 = glGetUniformLocation(program_id_1, "mvp");
    GLuint matrix_id_2 = glGetUniformLocation(program_id_2, "mvp");

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.6f, 0.4f, 0.0f);  // Sort of green for background
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

        for (auto& [program_id, vertex_buffer, matrix_id] : std::initializer_list<std::tuple<GLuint&, GLuint&, GLuint&>>{
                {program_id_1, vertex_buffer_1, matrix_id_1},
                {program_id_2, vertex_buffer_2, matrix_id_2}
        }) {
            glUseProgram(program_id);  // Use our shader

            double time_now = glfwGetTime();
            glm::mat4 mvp = ComputeMvp(time_now);
            glUniformMatrix4fv(matrix_id, 1, GL_FALSE, glm::value_ptr(mvp));  // Send our transformation

            glEnableVertexAttribArray(0);  // 1st attribute buffer : vertices
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
