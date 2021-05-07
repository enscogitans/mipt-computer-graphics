#include "instancing_model.hpp"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <common/exception.hpp>
#include <common/shader.hpp>
#include <common/bmp_loader.hpp>


namespace {

template <typename T>
size_t GetSizeOfVectorContent(const std::vector<T>& v) {
    return v.size() * sizeof(T);
}

}  // namespace


namespace model {

InstancingModel::InstancingModel(std::vector<float> vertices, const std::vector<float>& colors,
                                 const std::filesystem::path& vertex_shader, const std::filesystem::path& fragment_shader,
                                 float model_scale)
        : use_color_(true)
{
    if (vertices.size() != colors.size()) {
        throw std::invalid_argument("Sizes of vertices and colors must be the same");
    }
    n_vertices_ = static_cast<GLsizei>(vertices.size());
    std::for_each(vertices.begin(), vertices.end(), [=](float& f) { f *= model_scale; });

    // Might throw an exception
    program_ = utils::LoadShaders(vertex_shader, fragment_shader);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    vp_matrix_location_ = glGetUniformLocation(program_, kVpName);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, GetSizeOfVectorContent(vertices), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, GetSizeOfVectorContent(colors), colors.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &model_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, model_buffer_);
    glBufferData(GL_ARRAY_BUFFER, kMaxInstances * sizeof(glm::mat4), nullptr, GL_STREAM_DRAW);  // Reserve space

    glBindVertexArray(0);  // Unbind current VAO
}

InstancingModel::InstancingModel(const std::filesystem::path& model_path, const std::filesystem::path& texture_path,
                                 const std::filesystem::path& vertex_shader, const std::filesystem::path& fragment_shader,
                                 float model_scale)
        : use_color_(false)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uv_coords;
    std::vector<GLuint> indices;

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(model_path.string(), aiProcess_Triangulate);
    aiMesh* pMesh = scene->mMeshes[0];
    float max_norm = 0.0f;
    for (size_t i = 0; i < pMesh->mNumVertices; ++i) {
        glm::vec3 vec = {
                pMesh->mVertices[i].x,
                pMesh->mVertices[i].y,
                pMesh->mVertices[i].z
        };
        vertices.emplace_back(vec.x);
        vertices.emplace_back(vec.y);
        vertices.emplace_back(vec.z);
        if (glm::length(vec) > max_norm) {
            max_norm = glm::length(vec);
        }

        uv_coords.push_back(pMesh->mTextureCoords[0][i].x);
        uv_coords.push_back(pMesh->mTextureCoords[0][i].y);
    }
    for (size_t i = 0; i < pMesh->mNumFaces; ++i) {
        indices.emplace_back(pMesh->mFaces[i].mIndices[0]);
        indices.emplace_back(pMesh->mFaces[i].mIndices[1]);
        indices.emplace_back(pMesh->mFaces[i].mIndices[2]);
    }

//    aiMaterial* material = scene->mMaterials[pMesh->mMaterialIndex];
//    aiString texture_path;
//    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) != AI_SUCCESS) {
//        throw utils::InitializationError("Can't get texture for " + model_path.string());
//    }
//    utils::BmpInfo texture = utils::LoadBmpData(model_path.parent_path() / texture_path.C_Str());
    utils::BmpInfo texture = utils::LoadBmpData(texture_path);

    n_vertices_ = static_cast<GLsizei>(vertices.size());
    n_indices_ = static_cast<GLsizei>(indices.size());
    if (max_norm > 0.0f) {
        model_scale /= max_norm;
    }
    std::for_each(vertices.begin(), vertices.end(), [=](float& f) { f *= model_scale; });

    // Might throw an exception
    program_ = utils::LoadShaders(vertex_shader, fragment_shader);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    vp_matrix_location_ = glGetUniformLocation(program_, kVpName);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, GetSizeOfVectorContent(vertices), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &uv_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glBufferData(GL_ARRAY_BUFFER, GetSizeOfVectorContent(uv_coords), uv_coords.data(), GL_STATIC_DRAW);

    glGenTextures(1, &texture_buffer_);
    glBindTexture(GL_TEXTURE_2D, texture_buffer_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.buffer.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenBuffers(1, &element_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSizeOfVectorContent(indices), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &model_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, model_buffer_);
    glBufferData(GL_ARRAY_BUFFER, kMaxInstances * sizeof(glm::mat4), nullptr, GL_STREAM_DRAW);  // Reserve space

    glBindVertexArray(0);  // Unbind current VAO
}

InstancingModel::~InstancingModel() {
    if (use_color_) {
        glDeleteBuffers(1, &color_buffer_);
    } else {
        glDeleteTextures(1, &texture_buffer_);
        glDeleteBuffers(1, &uv_buffer_);
        glDeleteBuffers(1, &element_buffer_);
    }
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &model_buffer_);
    glDeleteProgram(program_);
    glDeleteVertexArrays(1, &vao_);
}

void InstancingModel::DrawInstances(const glm::mat4& vp_matrix, const std::vector<glm::mat4>& model_matrices) const {
    auto n_instances = static_cast<GLsizei>(model_matrices.size());
    if (n_instances > kMaxInstances) {
        std::cerr << "Too many instances to draw: " << n_instances
                  << " while limit is " << kMaxInstances << "."
                  << " Will draw only first " << kMaxInstances << " elements.\n";
        n_instances = kMaxInstances;
    }

    glBindVertexArray(vao_);
    glUseProgram(program_);

    glUniformMatrix4fv(vp_matrix_location_, 1, GL_FALSE, glm::value_ptr(vp_matrix));

    glEnableVertexAttribArray(Locations::kPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glVertexAttribPointer(Locations::kPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (use_color_) {
        glEnableVertexAttribArray(Locations::kColor);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
        glVertexAttribPointer(Locations::kColor, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    } else {
        glBindTexture(GL_TEXTURE_2D, texture_buffer_);
        glEnableVertexAttribArray(Locations::kUv);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
        glVertexAttribPointer(Locations::kUv, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    // Use instancing for our model matrices
    const GLuint kMatrixSize = 4;  // 4x4
    glBindBuffer(GL_ARRAY_BUFFER, model_buffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, GetSizeOfVectorContent(model_matrices), model_matrices.data());
    for (GLuint i = 0; i < kMatrixSize; ++i) {
        GLuint loc = i + Locations::kModelMatrix;
        size_t shift = i * sizeof(glm::vec4);
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, kMatrixSize, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(shift));
        glVertexAttribDivisor(loc, 1);
    }

    if (use_color_) {
        glDrawArraysInstanced(GL_TRIANGLES, 0, n_vertices_ * sizeof(GLfloat), n_instances);
    } else {
        glDrawElementsInstanced(GL_TRIANGLES, n_indices_ * sizeof(GLuint), GL_UNSIGNED_INT, nullptr, n_instances);
    }

    glBindVertexArray(0);  // Unbind current VAO
}

}  // namespace model
