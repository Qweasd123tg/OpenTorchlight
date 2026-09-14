#include "torchlight/animation_manifest.hpp"
#include "torchlight/pak_archive.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace {

bool ends_with_animation(std::string_view path) {
    constexpr std::string_view suffix = ".animation";
    if (path.size() < suffix.size()) {
        return false;
    }
    const auto tail = path.substr(path.size() - suffix.size());
    for (std::size_t index = 0; index < suffix.size(); ++index) {
        const auto character = tail[index];
        const auto lower = character >= 'A' && character <= 'Z'
                               ? static_cast<char>(character - 'A' + 'a')
                               : character;
        if (lower != suffix[index]) {
            return false;
        }
    }
    return true;
}

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: animation_manifest_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        std::size_t files = 0;
        std::size_t clips = 0;
        std::size_t keys = 0;
        std::size_t bone_offsets = 0;
        std::size_t hit_keys = 0;
        for (const auto& entry : archive.entries()) {
            if (!ends_with_animation(entry.name)) {
                continue;
            }
            const auto manifest = torchlight::parse_animation_manifest(archive.read(entry));
            ++files;
            clips += manifest.clips.size();
            for (const auto& clip : manifest.clips) {
                require(!clip.file.empty(), "animation manifest contains an empty FILE");
                keys += clip.keys.size();
                for (const auto& key : clip.keys) {
                    bone_offsets += static_cast<std::size_t>(key.bone_offset.has_value());
                    hit_keys += static_cast<std::size_t>(key.name == "HIT");
                }
            }
        }
        require(files == 182, "unexpected original animation manifest count");
        require(clips == 1514, "unexpected original animation clip count");
        require(keys == 2650, "unexpected original animation key count");
        require(bone_offsets == 252, "unexpected animation bone-offset count");
        require(hit_keys > 250, "too few original HIT timeline keys");
        std::cout << "PASS: parsed " << files << " original animation manifests, "
                  << clips << " clips, " << keys << " event keys and "
                  << bone_offsets << " bone offsets\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
