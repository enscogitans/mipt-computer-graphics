#include "misc.hpp"

#include <fstream>

#include "exception.hpp"


namespace utils {

std::string ReadFileContents(const std::filesystem::path& file_path, std::ios::openmode mode) {
    std::ifstream stream(file_path.string(), mode);
    if (!stream) {
        throw utils::IOException("Can't open file \"" + file_path.string() + "\"");
    }
    return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
}

}  // namespace utils
