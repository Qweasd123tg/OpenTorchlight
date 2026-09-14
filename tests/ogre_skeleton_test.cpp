#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {

bool ends_with_skeleton(std::string_view path) {
    constexpr std::string_view suffix = ".skeleton";
    if (path.size() < suffix.size()) {
        return false;
    }
    const auto tail = path.substr(path.size() - suffix.size());
    for (std::size_t index = 0; index < suffix.size(); ++index) {
        const auto character = tail[index];
        if ((character >= 'A' && character <= 'Z'
                 ? static_cast<char>(character - 'A' + 'a')
                 : character) != suffix[index]) {
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
            std::cerr << "usage: ogre_skeleton_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        std::size_t files = 0;
        std::size_t bones = 0;
        std::size_t animations = 0;
        std::size_t tracks = 0;
        std::size_t keyframes = 0;
        for (const auto& entry : archive.entries()) {
            if (!ends_with_skeleton(entry.name)) {
                continue;
            }
            const auto skeleton = torchlight::parse_ogre_skeleton(archive.read(entry));
            ++files;
            bones += skeleton.bones.size();
            animations += skeleton.animations.size();
            for (const auto& animation : skeleton.animations) {
                tracks += animation.tracks.size();
                for (const auto& track : animation.tracks) {
                    keyframes += track.keyframes.size();
                }
            }
        }
        require(files == 1612, "unexpected original skeleton file count");
        require(bones == 63043, "unexpected original bone count");
        require(animations == 1612, "unexpected original animation count");
        require(tracks == 38036, "unexpected original animation-track count");
        require(keyframes == 844506, "unexpected original keyframe count");
        std::cout << "PASS: parsed " << files << " OGRE skeletons, " << bones
                  << " bones, " << animations << " animations, " << tracks
                  << " tracks and " << keyframes << " keyframes\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
