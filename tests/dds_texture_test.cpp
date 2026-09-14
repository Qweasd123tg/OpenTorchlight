#include "torchlight/dds_texture.hpp"
#include "torchlight/pak_archive.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool ends_with_dds(const std::string& path) {
    if (path.size() < 4) {
        return false;
    }
    std::string suffix = path.substr(path.size() - 4);
    for (auto& character : suffix) {
        if (character >= 'A' && character <= 'Z') {
            character = static_cast<char>(character - 'A' + 'a');
        }
    }
    return suffix == ".dds";
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: dds_texture_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        std::size_t file_count = 0;
        std::array<std::size_t, 5> format_counts{};
        std::uint64_t decoded_pixels = 0;
        std::uint64_t rgba_checksum = 0;
        for (const auto& entry : archive.entries()) {
            if (!ends_with_dds(entry.name)) {
                continue;
            }
            torchlight::DdsImage image;
            try {
                image = torchlight::decode_dds(archive.read(entry));
            } catch (const std::exception& error) {
                throw std::runtime_error(entry.name + ": " + error.what());
            }
            require(image.width != 0 && image.height != 0, "DDS dimensions are empty");
            require(image.rgba.size() ==
                        static_cast<std::size_t>(image.width) * image.height * 4U,
                    "DDS RGBA output has the wrong size");
            require(image.additional_mipmaps.size() + 1U == image.mip_count,
                    "DDS authored mip chain has the wrong level count");
            ++file_count;
            ++format_counts[static_cast<std::size_t>(image.format)];
            decoded_pixels += static_cast<std::uint64_t>(image.width) * image.height;
            for (const auto byte : image.rgba) {
                rgba_checksum = (rgba_checksum * 1099511628211ULL) ^ byte;
            }
        }
        require(file_count == 2776, "unexpected DDS file count");
        require(format_counts[static_cast<std::size_t>(torchlight::DdsFormat::dxt1)] == 2044,
                "unexpected DXT1 file count");
        require(format_counts[static_cast<std::size_t>(torchlight::DdsFormat::dxt3)] == 624,
                "unexpected DXT3 file count");
        require(format_counts[static_cast<std::size_t>(torchlight::DdsFormat::dxt5)] == 92,
                "unexpected DXT5 file count");
        require(format_counts[static_cast<std::size_t>(torchlight::DdsFormat::rgb24)] == 8,
                "unexpected RGB24 file count");
        require(format_counts[static_cast<std::size_t>(torchlight::DdsFormat::rgba32)] == 8,
                "unexpected RGBA32 file count");
        require(decoded_pixels == 231484880ULL, "unexpected decoded DDS pixel count");
        require(rgba_checksum == 5218436249286343524ULL,
                "decoded DDS content checksum changed");
        std::cout << "PASS: decoded 2776 DDS textures and 231484880 top-level pixels\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
