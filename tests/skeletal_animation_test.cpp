#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/skeletal_animation.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: skeletal_animation_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto* mesh_entry =
            archive.find_normalized("media/models/alchemist/alchemist.mesh");
        const auto* bind_entry =
            archive.find_normalized("media/models/alchemist/alchemist.skeleton");
        const auto* run_entry =
            archive.find_normalized("media/models/alchemist/run.skeleton");
        const auto* attack_entry =
            archive.find_normalized("media/models/alchemist/attack1.skeleton");
        require(mesh_entry && bind_entry && run_entry && attack_entry,
                "Alchemist animation resources are absent");
        const auto mesh = torchlight::parse_ogre_mesh(archive.read(*mesh_entry));
        const auto bind = torchlight::parse_ogre_skeleton(archive.read(*bind_entry));
        const auto run = torchlight::parse_ogre_skeleton(archive.read(*run_entry));
        const auto attack = torchlight::parse_ogre_skeleton(archive.read(*attack_entry));
        const auto first = torchlight::sample_ogre_mesh_animation(mesh, bind, run, "Run", 0.0F);
        const auto second = torchlight::sample_ogre_mesh_animation(mesh, bind, run, "Run", 0.4F);
        require(first.geometries.size() == 4 && second.geometries.size() == 4,
                "Alchemist pose has the wrong geometry count");
        std::size_t vertices = 0;
        std::size_t changed = 0;
        for (std::size_t geometry = 0; geometry < first.geometries.size(); ++geometry) {
            require(first.geometries[geometry].positions.size() ==
                        second.geometries[geometry].positions.size(),
                    "Alchemist pose vertex counts differ");
            vertices += first.geometries[geometry].positions.size();
            for (std::size_t vertex = 0;
                 vertex < first.geometries[geometry].positions.size(); ++vertex) {
                const auto& left = first.geometries[geometry].positions[vertex];
                const auto& right = second.geometries[geometry].positions[vertex];
                for (std::size_t axis = 0; axis < 3; ++axis) {
                    require(std::isfinite(left[axis]) && std::isfinite(right[axis]),
                            "Alchemist pose contains a non-finite position");
                }
                const float distance = std::hypot(left[0] - right[0],
                    std::hypot(left[1] - right[1], left[2] - right[2]));
                changed += static_cast<std::size_t>(distance > 0.001F);
            }
        }
        require(vertices == 1524, "Alchemist pose has the wrong vertex count");
        require(changed > 1000, "Alchemist run animation moves too few vertices");
        const auto attack_first = torchlight::sample_ogre_mesh_animation(
            mesh, bind, attack, "Attack1", 0.0F);
        const auto attack_second = torchlight::sample_ogre_mesh_animation(
            mesh, bind, attack, "Attack1", 0.4F);
        std::size_t attack_changed = 0;
        for (std::size_t geometry = 0; geometry < attack_first.geometries.size(); ++geometry) {
            for (std::size_t vertex = 0;
                 vertex < attack_first.geometries[geometry].positions.size(); ++vertex) {
                const auto& left = attack_first.geometries[geometry].positions[vertex];
                const auto& right = attack_second.geometries[geometry].positions[vertex];
                attack_changed += static_cast<std::size_t>(
                    std::hypot(left[0] - right[0],
                               std::hypot(left[1] - right[1], left[2] - right[2])) > 0.001F);
            }
        }
        require(attack_changed > 1000,
                "Alchemist attack animation moves too few vertices");
        std::cout << "PASS: sampled original Alchemist Run and Attack1 animations across "
                  << vertices << " vertices; run_changed=" << changed
                  << " attack_changed=" << attack_changed << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
