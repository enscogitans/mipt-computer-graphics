#include "dds_loader.hpp"

#include "exception.hpp"
#include "misc.hpp"


namespace {

enum FourCC {
    kDtx1 = 0x31545844,
    kDtx3 = 0x33545844,
    kDtx5 = 0x35545844,
};

}  // namespace


namespace utils {

std::vector<DdsInfo> LoadDdsMipmaps(const std::filesystem::path& image_path) {
    static const size_t kHeaderSize = 128;

	std::string file_content = ReadFileContents(image_path, std::ios::binary);

    if (file_content.size() < kHeaderSize || file_content.substr(0, 4) != "DDS ") {
	    throw FormatError("Invalid DDS file " + image_path.string());
	}

    auto height = *reinterpret_cast<int*>(&file_content[12]);
    auto width = *reinterpret_cast<int*>(&file_content[16]);
//    auto linearSize = *reinterpret_cast<int*>(&file_content[20]);
    auto mipmap_count = *reinterpret_cast<int*>(&file_content[28]);
    auto four_cc = *reinterpret_cast<int*>(&file_content[84]);

    std::vector<unsigned char> data{file_content.begin() + kHeaderSize, file_content.end()};

    int blockSize;
//    int components;
    if (four_cc == FourCC::kDtx1) {
        blockSize = 8;
//        components = 3;
    } else {
        blockSize = 16;
//        components = 4;
    }

    GLenum format;
    switch(four_cc) {
        case FourCC::kDtx1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FourCC::kDtx3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FourCC::kDtx5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            throw FormatError(
                    "Can't recognize dds' FourCC format "
                    + std::to_string(four_cc)
                    + " of file " + image_path.string()
            );
    }

    std::vector<DdsInfo> mipmaps;
    auto offset = data.begin();
    for (int i = 0; i < mipmap_count; ++i) {
        int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

        mipmaps.push_back(DdsInfo{
            .width = width,
            .height = height,
            .format = format,
            .buffer = {offset, offset + size}
        });
        offset += size;

        width = std::max(1, width / 2);
        height = std::max(1, height / 2);
    }

    return mipmaps;
}

}  // namespace utils
