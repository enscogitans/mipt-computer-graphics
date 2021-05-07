#pragma once

#include <vector>
#include <filesystem>

#include <GL/glew.h>

#include "instance_interface.hpp"


namespace model {

/*
 * This model is preferred if one wants to draw many identical objects located in different positions.
 * However, it has a limit of how many objects it may draw.
 *
 * One should be careful with shaders, because some locations and variable names are hardcoded here.
 * The class also has some assumptions about which variables the shader has:
 *     - coordinates
 *     - colors or uv-coords
 *     - model matrix
 *     - view-projection matrix
 */
class InstancingModel {
public:
    InstancingModel(std::vector<float> vertices, const std::vector<float>& colors,
                    const std::filesystem::path& vertex_shader, const std::filesystem::path& fragment_shader,
                    float model_scale = 1.0f);

    /* Has a very limited support of model loading */
    InstancingModel(const std::filesystem::path& model_path, const std::filesystem::path& texture_path,
                    const std::filesystem::path& vertex_shader, const std::filesystem::path& fragment_shader,
                    float model_scale = 1.0f);

    ~InstancingModel();

    void DrawInstances(const glm::mat4& vp_matrix, const std::vector<glm::mat4>& model_matrices) const;

public:
    InstancingModel(InstancingModel&&) = delete;
    InstancingModel& operator=(InstancingModel&&) = delete;
    InstancingModel(const InstancingModel&) = delete;
    InstancingModel& operator=(const InstancingModel&) = delete;

private:
    static const size_t kMaxInstances = 200;

    GLuint vao_;
    GLuint program_;
    GLint vp_matrix_location_;  // Uniform variable vp = projection * view

    GLuint vertex_buffer_;
    GLsizei n_vertices_;  // Size of vertex buffer
    GLsizei n_indices_;  // Size of index buffer

    const bool use_color_;  // Use either color or uv
    GLuint color_buffer_;
    GLuint uv_buffer_;
    GLuint texture_buffer_;
    GLuint element_buffer_;

    GLuint model_buffer_;  // Buffer of model matrices

private:  // Constants used (hardcoded) in vertex shader
    static constexpr char kVpName[] = "vp";
    enum Locations {
        kPosition = 0,
        kColor = 1,
        kUv = 2,
        kModelMatrix = 3,  // Actually, it utilizes locations 3,4,5,6
    };
};

}  // namespace model
