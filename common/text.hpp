#pragma once

#include <string_view>
#include <filesystem>

#include <GL/glew.h>


namespace utils {

class TextDrawer {
public:
    TextDrawer(const std::filesystem::path& font_image,
               const std::filesystem::path& vertex_shader,
               const std::filesystem::path& fragment_shader);

    ~TextDrawer();

    void DrawText(std::string_view text, int x, int y, int size, int window_width, int window_height) const;

private:
    const std::string kTextureSamplerName = "texture_sampler";
    enum Locations {
        kPosition = 0,
        kUv = 1,
    };

private:
    GLuint vao_;
    GLuint program_;
    GLuint texture_buffer_;
    GLuint vertex_buffer_;
    GLuint uv_buffer_;
    GLint texture_sampler_location_;
};

}  // namespace utils
