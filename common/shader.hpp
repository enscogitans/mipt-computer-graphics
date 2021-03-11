#pragma once

#include <filesystem>
#include <GL/glew.h>

namespace utils {

GLuint LoadShaders(const std::filesystem::path& vertex_shader_path,
                   const std::filesystem::path& fragment_shader_path);

} // namespace utils
