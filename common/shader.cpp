#include "shader.hpp"

#include <fstream>
#include <iostream>

#include "defer.hpp"
#include "exception.hpp"


namespace {

std::string ReadShaderContents(const std::filesystem::path& file_path) {
    std::ifstream stream(file_path.string());
    if (!stream) {
        throw utils::IOException("Can't open shader \"" + file_path.string() + "\"");
    }
    return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
}

}  // namespace


namespace utils {

GLuint LoadShaders(const std::filesystem::path& vertex_shader_path,
                   const std::filesystem::path& fragment_shader_path) {
    std::string vertex_shader_code = ReadShaderContents(vertex_shader_path);
    std::string fragment_shader_code = ReadShaderContents(fragment_shader_path);

    // Create shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    Defer defer_1 = [&]() {
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    };

    // Compile shaders
    for (auto& [shader_id, shader_code, shader_name] : {
            std::tuple{vertex_shader_id, vertex_shader_code, vertex_shader_path.filename()},
            {fragment_shader_id, fragment_shader_code, fragment_shader_path.filename()}
    }) {
        // Compile
        char const* shader_code_ptr = shader_code.c_str();
        glShaderSource(shader_id, 1, &shader_code_ptr, nullptr);
        glCompileShader(shader_id);

        // Check
        GLint compile_status;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
        if (compile_status != GL_TRUE) {
            GLsizei buf_size;
            GLsizei log_length;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &buf_size);
            std::unique_ptr<char[]> info_log(new char[buf_size]);
            glGetShaderInfoLog(shader_id, buf_size, &log_length, info_log.get());

            std::cerr << "Couldn't compile shader " << shader_name << ": ";
            std::cerr.write(info_log.get(), log_length).write("\n", 1);
        }
    }

    // Link the program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    Defer defer_2 = [&]() {
        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);
    };
    glLinkProgram(program_id);

    // Check the program
    GLint link_status;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        GLsizei buf_size;
        GLsizei log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &buf_size);
        std::unique_ptr<char[]> info_log(new char[buf_size]);
        glGetProgramInfoLog(program_id, buf_size, &log_length, info_log.get());

        std::cerr << "Couldn't link program: ";
        std::cerr.write(info_log.get(), log_length).write("\n", 1);
    }

    return program_id;
}

}  // namespace utils
