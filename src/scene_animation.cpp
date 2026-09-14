#include "torchlight/scene_animation.hpp"

#include <algorithm>
#include <cctype>
#include <limits>
#include <string_view>

namespace torchlight {
namespace {

bool ascii_equal_case_insensitive(std::string_view left, std::string_view right) {
    if (left.size() != right.size()) {
        return false;
    }
    for (std::size_t index = 0; index < left.size(); ++index) {
        const auto left_character = static_cast<unsigned char>(left[index]);
        const auto right_character = static_cast<unsigned char>(right[index]);
        if (std::tolower(left_character) != std::tolower(right_character)) {
            return false;
        }
    }
    return true;
}

const PakArchive::Entry* sibling_entry(const PakArchive& archive,
                                       std::string_view mesh_path,
                                       std::string_view sibling_name) {
    const auto slash = mesh_path.find_last_of("/\\");
    const auto directory = slash == std::string_view::npos
                               ? std::string{}
                               : std::string(mesh_path.substr(0, slash + 1U));
    return archive.find_normalized(directory + std::string(sibling_name));
}

std::string ascii_lower(std::string_view value) {
    std::string result;
    result.reserve(value.size());
    for (const auto character : value) {
        result.push_back(static_cast<char>(
            std::tolower(static_cast<unsigned char>(character))));
    }
    return result;
}

std::vector<const PakArchive::Entry*> sibling_idle_entries(
    const PakArchive& archive, std::string_view mesh_path) {
    const auto slash = mesh_path.find_last_of("/\\");
    const auto directory = slash == std::string_view::npos
                               ? std::string{}
                               : ascii_lower(mesh_path.substr(0, slash + 1U));
    const auto mesh_name = ascii_lower(
        slash == std::string_view::npos ? mesh_path : mesh_path.substr(slash + 1U));
    const bool unarmed_mesh = mesh_name.find("unarmed") != std::string::npos;

    struct Candidate {
        const PakArchive::Entry* entry = nullptr;
        int priority = std::numeric_limits<int>::max();
        std::string normalized_name;
    };
    std::vector<Candidate> candidates;
    for (const auto& entry : archive.entries()) {
        const auto normalized = ascii_lower(entry.name);
        if (normalized.size() <= directory.size() ||
            normalized.compare(0, directory.size(), directory) != 0 ||
            normalized.find('/', directory.size()) != std::string::npos) {
            continue;
        }
        const auto filename = normalized.substr(directory.size());
        if (filename.rfind("idle", 0) != 0 ||
            filename.size() < 9U ||
            filename.compare(filename.size() - 9U, 9U, ".skeleton") != 0) {
            continue;
        }
        int priority = 3;
        if (filename == "idle.skeleton") {
            priority = 0;
        } else if ((unarmed_mesh && filename == "idle_unarmed.skeleton") ||
                   (!unarmed_mesh && filename == "idle_armed.skeleton")) {
            priority = 1;
        } else if (filename == "idle_unarmed.skeleton" ||
                   filename == "idle_armed.skeleton") {
            priority = 2;
        }
        candidates.push_back(Candidate{&entry, priority, normalized});
    }
    std::sort(candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
        return left.priority != right.priority ? left.priority < right.priority
                                               : left.normalized_name < right.normalized_name;
    });
    std::vector<const PakArchive::Entry*> result;
    result.reserve(candidates.size());
    for (const auto& candidate : candidates) {
        result.push_back(candidate.entry);
    }
    return result;
}

} // namespace

std::vector<SceneMeshAnimation> load_scene_idle_animations(
    const PakArchive& archive, const FixedSceneGeometry& geometry,
    std::optional<std::size_t> excluded_mesh_index) {
    std::vector<SceneMeshAnimation> result;
    for (std::size_t mesh_index = 0; mesh_index < geometry.meshes.size(); ++mesh_index) {
        if (excluded_mesh_index && mesh_index == *excluded_mesh_index) {
            continue;
        }
        const auto& resource = geometry.meshes[mesh_index];
        const auto& mesh = resource.mesh;
        if (!mesh.skeletally_animated || mesh.skeleton_file.empty()) {
            continue;
        }
        const auto* bind_entry = sibling_entry(
            archive, resource.source_path, mesh.skeleton_file);
        if (bind_entry == nullptr) {
            continue;
        }
        auto idle_entries = sibling_idle_entries(archive, resource.source_path);
        if (idle_entries.empty()) {
            continue;
        }
        OgreSkeleton animation_skeleton;
        std::string animation_name;
        float animation_duration = 0.0F;
        for (const auto* idle_entry : idle_entries) {
            auto candidate = parse_ogre_skeleton(archive.read(*idle_entry));
            auto candidate_clip = std::find_if(
                candidate.animations.begin(), candidate.animations.end(),
                [](const auto& animation) {
                    return ascii_equal_case_insensitive(animation.name, "Idle") &&
                           animation.length > 0.0F;
                });
            if (candidate_clip == candidate.animations.end()) {
                candidate_clip = std::find_if(
                    candidate.animations.begin(), candidate.animations.end(),
                    [](const auto& animation) { return animation.length > 0.0F; });
            }
            if (candidate_clip != candidate.animations.end()) {
                animation_name = candidate_clip->name;
                animation_duration = candidate_clip->length;
                animation_skeleton = std::move(candidate);
                break;
            }
        }
        if (animation_name.empty()) {
            continue;
        }
        SceneMeshAnimation animation;
        animation.mesh_index = mesh_index;
        animation.bind_skeleton = parse_ogre_skeleton(archive.read(*bind_entry));
        animation.animation_name = std::move(animation_name);
        animation.duration = animation_duration;
        animation.animation_skeleton = std::move(animation_skeleton);
        result.push_back(std::move(animation));
    }
    return result;
}

OgreMeshPose sample_scene_mesh_animation(const FixedSceneGeometry& geometry,
                                         const SceneMeshAnimation& animation,
                                         float time_seconds) {
    return sample_ogre_mesh_animation(
        geometry.meshes.at(animation.mesh_index).mesh, animation.bind_skeleton,
        animation.animation_skeleton, animation.animation_name, time_seconds);
}

} // namespace torchlight
