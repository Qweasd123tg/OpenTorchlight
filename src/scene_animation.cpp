#include "torchlight/scene_animation.hpp"

#include <algorithm>
#include <cctype>
#include <limits>
#include <optional>
#include <stdexcept>
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

std::string_view filename(std::string_view path) {
    const auto slash = path.find_last_of("/\\");
    return slash == std::string_view::npos ? path : path.substr(slash + 1U);
}

std::string filename_stem(std::string_view path) {
    const auto name = filename(path);
    const auto dot = name.find_last_of('.');
    return ascii_lower(dot == std::string_view::npos ? name : name.substr(0U, dot));
}

bool has_suffix(std::string_view value, std::string_view suffix) {
    return value.size() >= suffix.size() &&
           value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
}

struct ManifestResource {
    const PakArchive::Entry* entry = nullptr;
    AnimationManifest manifest;
};

std::optional<ManifestResource> model_animation_manifest(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view bind_skeleton_file, bool strict = false) {
    const auto slash = mesh_path.find_last_of("/\\");
    const auto directory = slash == std::string_view::npos
                               ? std::string{}
                               : ascii_lower(mesh_path.substr(0, slash + 1U));
    const auto mesh_stem = filename_stem(mesh_path);

    struct Candidate {
        const PakArchive::Entry* entry = nullptr;
        int priority = std::numeric_limits<int>::max();
        std::string normalized_name;
        AnimationManifest manifest;
    };
    std::vector<Candidate> candidates;
    for (const auto& entry : archive.entries()) {
        const auto normalized = ascii_lower(entry.name);
        if (normalized.size() <= directory.size() ||
            normalized.compare(0, directory.size(), directory) != 0 ||
            normalized.find('/', directory.size()) != std::string::npos) {
            continue;
        }
        const auto sibling_name = normalized.substr(directory.size());
        if (!has_suffix(sibling_name, ".animation")) {
            continue;
        }
        auto manifest = parse_animation_manifest(archive.read(entry));
        int priority = filename_stem(sibling_name) == mesh_stem ? 0 : 2;
        const bool binds_mesh_skeleton = std::any_of(
            manifest.clips.begin(), manifest.clips.end(), [&](const auto& clip) {
                return ascii_equal_case_insensitive(clip.file, bind_skeleton_file);
            });
        if (priority != 0 && binds_mesh_skeleton) {
            priority = 1;
        }
        candidates.push_back(
            Candidate{&entry, priority, normalized, std::move(manifest)});
    }
    if (candidates.empty()) {
        return std::nullopt;
    }
    std::sort(candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
        return left.priority != right.priority ? left.priority < right.priority
                                               : left.normalized_name < right.normalized_name;
    });
    if ((strict && candidates.front().priority == 2) ||
        (candidates.front().priority == 2 && candidates.size() != 1U) ||
        (candidates.size() > 1U &&
         candidates[1].priority == candidates.front().priority)) {
        return std::nullopt;
    }
    return ManifestResource{candidates.front().entry,
                            std::move(candidates.front().manifest)};
}

bool clip_has_event(const AnimationManifestClip& clip, std::string_view name) {
    return std::any_of(clip.keys.begin(), clip.keys.end(), [&](const auto& key) {
        return ascii_equal_case_insensitive(key.name, name);
    });
}

bool clip_starts_with(const AnimationManifestClip& clip, std::string_view prefix) {
    return filename_stem(clip.file).rfind(ascii_lower(prefix), 0U) == 0U;
}

std::vector<const AnimationManifestClip*> matching_clips(
    const AnimationManifest& manifest, SceneAnimationKind kind) {
    std::vector<const AnimationManifestClip*> result;
    const auto append_prefix = [&](std::string_view prefix) {
        for (const auto& clip : manifest.clips) {
            if (clip_starts_with(clip, prefix)) {
                result.push_back(&clip);
            }
        }
    };
    switch (kind) {
    case SceneAnimationKind::idle:
        append_prefix("idle");
        break;
    case SceneAnimationKind::run:
        append_prefix("run");
        break;
    case SceneAnimationKind::attack:
        append_prefix("attack");
        for (const auto& clip : manifest.clips) {
            if (clip_has_event(clip, "HIT") &&
                std::find(result.begin(), result.end(), &clip) == result.end()) {
                result.push_back(&clip);
            }
        }
        break;
    case SceneAnimationKind::hit:
        append_prefix("hit");
        break;
    case SceneAnimationKind::death:
        append_prefix("die");
        append_prefix("death");
        break;
    }
    return result;
}

std::optional<ModelAnimationClip> load_manifest_clip(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view manifest_path, const AnimationManifestClip& clip, bool strict = false) {
    const auto* entry = sibling_entry(archive, mesh_path, clip.file);
    if (entry == nullptr) {
        return std::nullopt;
    }
    auto skeleton = parse_ogre_skeleton(archive.read(*entry));
    const auto stem = filename_stem(clip.file);
    auto animation = std::find_if(
        skeleton.animations.begin(), skeleton.animations.end(),
        [&](const auto& candidate) {
            return ascii_equal_case_insensitive(candidate.name, stem) &&
                   candidate.length > 0.0F;
        });
    if (!strict && animation == skeleton.animations.end()) {
        animation = std::find_if(
            skeleton.animations.begin(), skeleton.animations.end(),
            [](const auto& candidate) { return candidate.length > 0.0F; });
    }
    if (animation == skeleton.animations.end()) {
        return std::nullopt;
    }
    ModelAnimationClip result;
    result.animation_name = animation->name;
    result.duration = animation->length;
    result.animation_skeleton = std::move(skeleton);
    result.manifest_path = std::string(manifest_path);
    result.skeleton_path = entry->name;
    result.event_keys = clip.keys;
    return result;
}

} // namespace

std::optional<ModelAnimationClip> load_model_animation(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view bind_skeleton_file, SceneAnimationKind kind) {
    auto manifest_resource =
        model_animation_manifest(archive, mesh_path, bind_skeleton_file);
    if (!manifest_resource) {
        return std::nullopt;
    }
    const auto candidates = matching_clips(manifest_resource->manifest, kind);
    for (const auto* clip : candidates) {
        if (auto result = load_manifest_clip(
                archive, mesh_path, manifest_resource->entry->name, *clip)) {
            return result;
        }
    }
    return std::nullopt;
}

std::vector<ModelAnimationClip> load_model_animations_by_prefix(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view bind_skeleton_file, std::string_view prefix) {
    auto manifest_resource =
        model_animation_manifest(archive, mesh_path, bind_skeleton_file, true);
    if (!manifest_resource) {
        return {};
    }
    std::vector<ModelAnimationClip> result;
    for (const auto& clip : manifest_resource->manifest.clips) {
        if (!clip_starts_with(clip, prefix)) {
            continue;
        }
        if (auto loaded = load_manifest_clip(
                archive, mesh_path, manifest_resource->entry->name, clip, true)) {
            result.push_back(std::move(*loaded));
        }
    }
    return result;
}

std::size_t select_original_random_animation(
    std::size_t clip_count, TorchlightRandom& random) {
    if (clip_count == 0U) {
        throw std::invalid_argument("Cannot select an animation from an empty list");
    }
    std::size_t selected = 0U;
    for (std::size_t index = 1U; index < clip_count; ++index) {
        if (random.between(0.0F, 1000.0F) < 500.0F) {
            selected = index;
        }
    }
    return selected;
}

std::vector<SceneMeshAnimation> load_scene_idle_animations(
    const PakArchive& archive, const FixedSceneGeometry& geometry,
    std::optional<std::size_t> excluded_mesh_index) {
    return load_scene_animations(
        archive, geometry, SceneAnimationKind::idle, excluded_mesh_index);
}

std::vector<SceneMeshAnimation> load_scene_animations(
    const PakArchive& archive, const FixedSceneGeometry& geometry,
    SceneAnimationKind kind,
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
        auto clip = load_model_animation(
            archive, resource.source_path, mesh.skeleton_file, kind);
        if (!clip) {
            continue;
        }
        SceneMeshAnimation animation;
        animation.mesh_index = mesh_index;
        animation.kind = kind;
        animation.bind_skeleton = parse_ogre_skeleton(archive.read(*bind_entry));
        animation.animation_name = std::move(clip->animation_name);
        animation.manifest_path = std::move(clip->manifest_path);
        animation.skeleton_path = std::move(clip->skeleton_path);
        animation.event_keys = std::move(clip->event_keys);
        animation.duration = clip->duration;
        animation.animation_skeleton = std::move(clip->animation_skeleton);
        result.push_back(std::move(animation));
    }
    return result;
}

OgreMeshPose sample_scene_mesh_animation(const FixedSceneGeometry& geometry,
                                         const SceneMeshAnimation& animation,
                                         float time_seconds) {
    return sample_ogre_mesh_animation(
        geometry.meshes.at(animation.mesh_index).mesh, animation.bind_skeleton,
        animation.animation_skeleton, animation.animation_name, time_seconds,
        animation.kind == SceneAnimationKind::idle ||
                animation.kind == SceneAnimationKind::run
            ? AnimationPlaybackMode::loop
            : AnimationPlaybackMode::clamp);
}

} // namespace torchlight
