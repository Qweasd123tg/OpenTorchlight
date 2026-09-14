#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_animation.hpp"
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
        const auto polearms = torchlight::load_model_animations_by_prefix(
            archive, mesh_entry->name, mesh.skeleton_file, "POLEARM");
        require(polearms.size() == 3 && polearms[0].animation_name == "Polearm1" &&
                    polearms[1].animation_name == "Polearm2" &&
                    polearms[2].animation_name == "Polearm3",
                "Alchemist staff attacks did not resolve in manifest order");
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
        const auto blended = torchlight::blend_ogre_mesh_poses(first, second, 0.5F);
        require(blended.geometries.size() == first.geometries.size(),
                "Alchemist blended pose has the wrong geometry count");
        const auto& blended_position = blended.geometries.front().positions.front();
        const auto& first_position = first.geometries.front().positions.front();
        const auto& second_position = second.geometries.front().positions.front();
        for (std::size_t axis = 0; axis < 3; ++axis) {
            require(std::abs(blended_position[axis] -
                             (first_position[axis] + second_position[axis]) * 0.5F) <
                        0.00001F,
                    "Alchemist blended pose is not halfway between its sources");
        }
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
        const auto skeletal_blend = torchlight::sample_ogre_mesh_animation_blend(
            mesh, bind, run, "Run", 0.0F, 0.5F,
            attack, "Attack1", 0.0F, 0.5F);
        require(skeletal_blend.geometries.size() == first.geometries.size(),
                "Alchemist AnimationState blend has the wrong geometry count");

        torchlight::OgreMesh rotation_mesh;
        rotation_mesh.skeletally_animated = true;
        rotation_mesh.shared_geometry.emplace();
        rotation_mesh.shared_geometry->vertex_count = 1;
        rotation_mesh.shared_geometry->positions.push_back({1.0F, 0.0F, 0.0F});
        rotation_mesh.shared_bone_assignments.push_back({0, 0, 1.0F});
        torchlight::OgreSkeleton rotation_bind;
        rotation_bind.bones.push_back(
            {"root", 0, {0.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F, 0.0F}});
        torchlight::OgreSkeleton rotation_first;
        rotation_first.bones = rotation_bind.bones;
        torchlight::OgreSkeletonTrack rotation_first_track;
        rotation_first_track.bone_handle = 0;
        rotation_first_track.keyframes.push_back(
            {0.0F, {1.0F, 0.0F, 0.0F, 0.0F}, {0.0F, 0.0F, 0.0F}});
        rotation_first.animations.push_back(
            {"First", 1.0F, {std::move(rotation_first_track)}});
        torchlight::OgreSkeleton rotation_second;
        rotation_second.bones = rotation_bind.bones;
        torchlight::OgreSkeletonTrack rotation_second_track;
        rotation_second_track.bone_handle = 0;
        rotation_second_track.keyframes.push_back(
            {0.0F, {0.0F, 0.0F, 0.0F, 1.0F}, {0.0F, 0.0F, 0.0F}});
        rotation_second.animations.push_back(
            {"Second", 1.0F, {std::move(rotation_second_track)}});
        const auto rotation_blend = torchlight::sample_ogre_mesh_animation_blend(
            rotation_mesh, rotation_bind,
            rotation_first, "First", 0.0F, 0.5F,
            rotation_second, "Second", 0.0F, 0.5F);
        const auto& rotation_position =
            rotation_blend.geometries.front().positions.front();
        require(std::abs(rotation_position[0]) < 0.0001F &&
                    std::abs(rotation_position[1] - 1.0F) < 0.0001F,
                "OGRE weighted bone rotation was not applied before skinning");

        torchlight::OgreMesh delayed_mesh;
        delayed_mesh.skeletally_animated = true;
        delayed_mesh.shared_geometry.emplace();
        delayed_mesh.shared_geometry->vertex_count = 1;
        delayed_mesh.shared_geometry->positions.push_back({0.0F, 0.0F, 0.0F});
        delayed_mesh.shared_bone_assignments.push_back({0, 0, 1.0F});
        torchlight::OgreSkeleton delayed_bind;
        delayed_bind.bones.push_back(
            {"root", 0, {0.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F, 0.0F}});
        torchlight::OgreSkeleton delayed_animation;
        delayed_animation.bones = delayed_bind.bones;
        torchlight::OgreSkeletonTrack delayed_track;
        delayed_track.bone_handle = 0;
        delayed_track.keyframes.push_back(
            {0.25F, {1.0F, 0.0F, 0.0F, 0.0F}, {10.0F, 0.0F, 0.0F}});
        delayed_track.keyframes.push_back(
            {0.75F, {1.0F, 0.0F, 0.0F, 0.0F}, {20.0F, 0.0F, 0.0F}});
        delayed_animation.animations.push_back(
            {"Delayed", 1.0F, {std::move(delayed_track)}});
        const auto before_first = torchlight::sample_ogre_mesh_animation(
            delayed_mesh, delayed_bind, delayed_animation, "Delayed", 0.0F);
        require(std::abs(before_first.geometries.front().positions.front()[0] - 10.0F) <
                    0.00001F,
                "animation did not hold OGRE's first key before its timestamp");

        torchlight::OgreMesh merged_mesh;
        merged_mesh.skeletally_animated = true;
        merged_mesh.shared_geometry.emplace();
        merged_mesh.shared_geometry->vertex_count = 1;
        merged_mesh.shared_geometry->positions.push_back({10.0F, 0.0F, 0.0F});
        merged_mesh.shared_bone_assignments.push_back({0, 0, 1.0F});
        torchlight::OgreSkeleton merged_bind;
        merged_bind.bones.push_back(
            {"root", 0, {10.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F, 0.0F}});
        torchlight::OgreSkeleton merged_animation;
        merged_animation.bones.push_back(
            {"root", 0, {12.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F, 0.0F}});
        torchlight::OgreSkeletonTrack merged_track;
        merged_track.bone_handle = 0;
        merged_track.keyframes.push_back(
            {0.0F, {1.0F, 0.0F, 0.0F, 0.0F}, {3.0F, 0.0F, 0.0F}});
        merged_animation.animations.push_back(
            {"Merged", 1.0F, {std::move(merged_track)}});
        const auto merged_pose = torchlight::sample_ogre_mesh_animation(
            merged_mesh, merged_bind, merged_animation, "Merged", 0.0F);
        require(std::abs(merged_pose.geometries.front().positions.front()[0] - 15.0F) <
                    0.00001F,
                "animation skeleton bind pose was not merged like OGRE 1.6");
        std::cout << "PASS: sampled original Alchemist Run and Attack1 animations across "
                  << vertices << " vertices; run_changed=" << changed
                  << " attack_changed=" << attack_changed << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
