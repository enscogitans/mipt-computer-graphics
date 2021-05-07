#include "bmp_loader.hpp"

#include "exception.hpp"
#include "misc.hpp"


namespace utils {

BmpInfo LoadBmpData(const std::filesystem::path& image_path) {
    static const int kHeaderSize = 54;
    static const int kChannelsCount = 3;

	std::string data = ReadFileContents(image_path, std::ios::binary);

	if (data.size() < kHeaderSize
        || data.substr(0, 2) != "BM"
        || *reinterpret_cast<int*>(&data[0x1C]) != 24
        || *reinterpret_cast<int*>(&data[0x1E]) != 0  // Make sure this is a 24bpp file
    ) {
	    throw FormatError("Invalid BMP file " + image_path.string());
	}

	auto data_pos = *reinterpret_cast<int*>(&data[0x0A]);
    auto width = *reinterpret_cast<int*>(&data[0x12]);
    auto height = *reinterpret_cast<int*>(&data[0x16]);
    auto image_size = *reinterpret_cast<int*>(&data[0x22]);

    // Some BMP files are misformatted, guess missing information
	if (image_size == 0) {
        image_size = width * height * kChannelsCount;
    }
	if (data_pos == 0) {
        data_pos = 54;  // The BMP header is done that way
    }

    return BmpInfo{
        .width = width,
	    .height = height,
	    .buffer = {data.begin() + data_pos, data.begin() + data_pos + image_size}
	};
}

}  // namespace utils
