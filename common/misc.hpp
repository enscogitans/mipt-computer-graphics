#pragma once

#include <string>
#include <filesystem>


namespace utils {

std::string ReadFileContents(const std::filesystem::path& file_path, std::ios::openmode mode = std::ios::in);

}  // namespace utils
