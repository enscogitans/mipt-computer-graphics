#pragma once

#include <filesystem>

#include <GL/glew.h>


namespace utils {

struct DdsInfo {
    int width;
    int height;
    GLenum format;  // E.g. GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
    std::vector<unsigned char> buffer;
};

std::vector<DdsInfo> LoadDdsMipmaps(const std::filesystem::path& image_path);

}  // namespace utils
