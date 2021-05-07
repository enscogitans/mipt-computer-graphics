#pragma once

#include <filesystem>


namespace utils {

struct BmpInfo {
    int width;
    int height;
    std::vector<unsigned char> buffer;
};

BmpInfo LoadBmpData(const std::filesystem::path& image_path);

}  // namespace utils
