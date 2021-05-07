#include "text.hpp"

#include <glm/vec2.hpp>

#include "dds_loader.hpp"
#include "shader.hpp"


namespace utils {

TextDrawer::TextDrawer(const std::filesystem::path& font_image,
                       const std::filesystem::path& vertex_shader,
                       const std::filesystem::path& fragment_shader) {
    program_ = LoadShaders(vertex_shader, fragment_shader);
    std::vector<DdsInfo> mipmaps = LoadDdsMipmaps(font_image);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenTextures(1, &texture_buffer_);
    glBindTexture(GL_TEXTURE_2D, texture_buffer_);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (int i = 0; i < mipmaps.size(); ++i) {
        glCompressedTexImage2D(
                GL_TEXTURE_2D,
                i,
                mipmaps[i].format,
                mipmaps[i].width, mipmaps[i].height,
                0,
                mipmaps[i].buffer.size(), mipmaps[i].buffer.data()
        );
    }

    glGenBuffers(1, &vertex_buffer_);
    glGenBuffers(1, &uv_buffer_);

    texture_sampler_location_ = glGetUniformLocation(program_, kTextureSamplerName.c_str());

    glBindVertexArray(0);
}

TextDrawer::~TextDrawer() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &uv_buffer_);
    glDeleteTextures(1, &texture_buffer_);
    glDeleteProgram(program_);
    glDeleteVertexArrays(1, &vao_);
}

void TextDrawer::DrawText(std::string_view text, int x, int y, int size, int window_width, int window_height) const {
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> uvs;
    for (int i = 0; i < text.size(); ++i) {
        glm::vec2 vertex_up_left(x + i * size, y + size);
        glm::vec2 vertex_up_right(x + (i + 1) * size, y + size);
        glm::vec2 vertex_down_right(x + (i + 1) * size, y);
        glm::vec2 vertex_down_left(x + i * size, y);

        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        float uv_x = (text[i] % 16) / 16.0f;
        float uv_y = (text[i] / 16) / 16.0f;

        glm::vec2 uv_up_left(uv_x, uv_y);
        glm::vec2 uv_up_right(uv_x + 1.0f / 16.0f, uv_y);
        glm::vec2 uv_down_right(uv_x + 1.0f / 16.0f, uv_y + 1.0f / 16.0f);
        glm::vec2 uv_down_left(uv_x, uv_y + 1.0f / 16.0f);

        uvs.push_back(uv_up_left);
        uvs.push_back(uv_down_left);
        uvs.push_back(uv_up_right);

        uvs.push_back(uv_down_right);
        uvs.push_back(uv_up_right);
        uvs.push_back(uv_down_left);
    }

    // Output position of the vertex, in clip space. Map to [-1..1][-1..1]
    glm::vec2 window_mid = glm::vec2{window_width, window_height} / 2.0f;
    std::for_each(vertices.begin(), vertices.end(), [=](glm::vec2& vec) {
        vec = (vec - window_mid) / window_mid;
    });

    glBindVertexArray(vao_);
    glUseProgram(program_);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_buffer_);
    glUniform1i(texture_sampler_location_, 0);  // Set our "myTextureSampler" sampler to use Texture Unit 0

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(Locations::kPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glVertexAttribPointer(Locations::kPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(Locations::kUv);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glVertexAttribPointer(Locations::kUv, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisable(GL_BLEND);

    glBindVertexArray(0);
}

}  // namespace utils
