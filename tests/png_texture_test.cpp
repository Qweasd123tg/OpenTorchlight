#include "torchlight/pak_archive.hpp"
#include "torchlight/png_texture.hpp"

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

bool ends_with_png(const std::string& path) {
    if (path.size() < 4U) {
        return false;
    }
    std::string suffix = path.substr(path.size() - 4U);
    for (auto& character : suffix) {
        if (character >= 'A' && character <= 'Z') {
            character = static_cast<char>(character - 'A' + 'a');
        }
    }
    return suffix == ".png";
}
}

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: png_texture_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        std::size_t images = 0;
        std::uint64_t pixels = 0;
        std::uint64_t checksum = 1469598103934665603ULL;
        for (const auto& entry : archive.entries()) {
            if (!ends_with_png(entry.name)) {
                continue;
            }
            const auto image = torchlight::decode_png(archive.read(entry));
            require(image.width > 0 && image.height > 0, "PNG has empty dimensions");
            require(image.rgba.size() == static_cast<std::size_t>(image.width) * image.height * 4U,
                    "PNG RGBA size does not match its dimensions");
            pixels += static_cast<std::uint64_t>(image.width) * image.height;
            for (const auto byte : image.rgba) {
                checksum ^= byte;
                checksum *= 1099511628211ULL;
            }
            ++images;
        }
        require(images == 188, "unexpected original PNG count");
        std::cout << "PASS: decoded " << images << " PNG textures and " << pixels
                  << " pixels, checksum=" << checksum << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
