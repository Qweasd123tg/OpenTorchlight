#include "torchlight/ui_dropdown_animation.hpp"

#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_animation.hpp"

#include <algorithm>
#include <cmath>
#include <deque>
#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace torchlight {
namespace {

constexpr std::string_view kMeshPath = "media/ui/models/dropdown/dropdown.mesh";
constexpr float kBlendSeconds = 0.1F;

std::string sibling_path(std::string_view path, std::string_view leaf) {
    const auto slash = path.find_last_of("/\\");
    return std::string(path.substr(0, slash == std::string_view::npos ? 0 : slash + 1)) +
           std::string(leaf);
}

const OgreBonePose& dropdown_top(const OgreMeshPose& pose) {
    const auto found = std::find_if(pose.bones.begin(), pose.bones.end(), [](const auto& bone) {
        return bone.name == "tag_dropdowntop";
    });
    if (found == pose.bones.end()) {
        throw std::runtime_error("dropdown skeleton has no tag_dropdowntop");
    }
    return *found;
}

} // namespace

struct DropdownAnimation::Impl {
    struct Assets {
        OgreMesh mesh;
        OgreSkeleton bind;
        std::array<ModelAnimationClip, 3> clips; // idle, open, close: manifest order
        OgreMaterial material;
        std::string texture;
    };
    struct Layer {
        std::size_t clip = 0;
        float length = 0.0F;
        float time = 0.0F;
        float remaining_blend = 0.0F;
        float initial_blend = 0.0F;
        float inverse_weight = 0.0F;
        float speed = 1.0F;
        bool loop = false;
        bool active = false;
        bool queued = false;
        bool wrapped = false;
        bool remove = false;
        bool blend_complete = false;
        bool touched = false;
    };
    struct SharedState {
        float time = 0.0F;
        float weight = 1.0F;
        bool enabled = false;
    };

    std::shared_ptr<const Assets> assets;
    std::deque<Layer> layers;
    std::array<SharedState, 3> states{};
    std::vector<std::size_t> enabled_order;
    OgreMeshPose sampled_pose;
    std::vector<DropdownSoundRequest> sounds;
    bool is_open = false;
    bool is_closed = true;
    bool is_visible = false;

    explicit Impl(const PakArchive& archive) {
        static std::mutex cache_mutex;
        static std::unordered_map<std::string, std::weak_ptr<const Assets>> cache;
        const auto cache_key = archive.path().lexically_normal().string();
        const std::lock_guard<std::mutex> lock(cache_mutex);
        if (const auto found = cache.find(cache_key); found != cache.end()) {
            assets = found->second.lock();
        }
        if (assets) {
            sampled_pose = sample_ogre_mesh_animation(
                assets->mesh, assets->bind, assets->clips[0].animation_skeleton,
                assets->clips[0].animation_name, 0.0F, AnimationPlaybackMode::loop);
            return;
        }
        auto loaded = std::make_shared<Assets>();
        const auto* mesh_entry = archive.find_normalized(kMeshPath);
        if (mesh_entry == nullptr) {
            throw std::runtime_error("original dropdown.mesh is absent");
        }
        loaded->mesh = parse_ogre_mesh(archive.read(*mesh_entry));
        if (!loaded->mesh.shared_geometry || loaded->mesh.submeshes.empty() ||
            loaded->mesh.skeleton_file.empty()) {
            throw std::runtime_error("dropdown.mesh has an unsupported geometry contract");
        }
        const auto* bind_entry = archive.find_normalized(
            sibling_path(mesh_entry->name, loaded->mesh.skeleton_file));
        if (bind_entry == nullptr) {
            throw std::runtime_error("dropdown bind skeleton is absent");
        }
        loaded->bind = parse_ogre_skeleton(archive.read(*bind_entry));
        const auto load_clip = [&](std::string_view prefix) {
            auto found = load_model_animations_by_prefix(
                archive, mesh_entry->name, loaded->mesh.skeleton_file, prefix);
            if (found.size() != 1U) {
                throw std::runtime_error("dropdown animation prefix is not unique: " +
                                         std::string(prefix));
            }
            return std::move(found.front());
        };
        loaded->clips[0] = load_clip("IDLE");
        loaded->clips[1] = load_clip("OPEN");
        loaded->clips[2] = load_clip("CLOSE");

        const OgreMaterialCatalog materials(archive);
        const auto* material = materials.find(loaded->mesh.submeshes.front().material);
        if (material == nullptr || material->textures.empty()) {
            throw std::runtime_error("Dropdown_ material or texture is absent");
        }
        loaded->material = *material;
        const auto texture_name = material->primary_texture.empty()
                                      ? material->textures.front()
                                      : material->primary_texture;
        const auto* texture = resolve_material_texture(archive, *material, texture_name);
        if (texture == nullptr) {
            throw std::runtime_error("dropdown material texture is absent");
        }
        loaded->texture = texture->name;
        assets = std::move(loaded);
        cache[cache_key] = assets;
        sampled_pose = sample_ogre_mesh_animation(
            assets->mesh, assets->bind, assets->clips[0].animation_skeleton,
            assets->clips[0].animation_name, 0.0F, AnimationPlaybackMode::loop);
    }

    void notify_enabled(std::size_t clip, bool enabled) {
        enabled_order.erase(
            std::remove(enabled_order.begin(), enabled_order.end(), clip), enabled_order.end());
        states[clip].enabled = enabled;
        if (enabled) {
            enabled_order.push_back(clip);
        }
    }

    void clear_animations() {
        for (auto clip : enabled_order) {
            states[clip].enabled = false;
        }
        enabled_order.clear();
        layers.clear();
    }

    void clear_queued() {
        layers.erase(std::remove_if(layers.begin(), layers.end(),
                                    [](const auto& layer) { return layer.queued; }),
                     layers.end());
    }

    void play(std::size_t clip, bool loop, float speed) {
        clear_animations();
        const float length = assets->clips[clip].duration;
        layers.push_front(Layer{clip, length, 0.0F, 0.0F, 0.0F, 0.0F, speed,
                                loop, true, false});
        notify_enabled(clip, true);
    }

    void blend(std::size_t clip, bool loop, float requested_blend, float speed) {
        const float length = assets->clips[clip].duration;
        if (!(length != 0.0F) || !(requested_blend != 0.0F)) {
            play(clip, loop, speed);
            return;
        }
        clear_queued();
        const float blend_time = std::min(requested_blend, length);
        layers.push_front(Layer{clip, length, 0.0F, blend_time, blend_time, 1.0F,
                                speed, loop, true, false});
        notify_enabled(clip, true);
        const bool older_same = std::any_of(std::next(layers.begin()), layers.end(),
                                            [&](const auto& layer) {
                                                return layer.clip == clip;
                                            });
        if (!older_same) {
            states[clip].weight = 0.0F;
        }
    }

    void queue(std::size_t clip, bool loop, float requested_blend, float speed) {
        const float length = assets->clips[clip].duration;
        const float blend_time = std::min(requested_blend, length);
        layers.push_front(Layer{clip, length, 0.0F, blend_time, blend_time, 1.0F,
                                speed, loop, false, true});
    }

    bool playing(std::size_t clip) const {
        return std::any_of(layers.begin(), layers.end(), [&](const auto& layer) {
            return layer.clip == clip && layer.active;
        });
    }

    bool queued(std::size_t clip) const {
        return std::any_of(layers.begin(), layers.end(), [&](const auto& layer) {
            return layer.clip == clip && layer.queued;
        });
    }

    void update(float dt) {
        if (layers.empty() || dt == 0.0F) {
            return;
        }
        bool latch = false;
        bool prior_removal_latch = false;
        float cumulative = 0.0F;
        std::vector<std::pair<std::size_t, float>> deferred;

        for (std::size_t index = 0; index < layers.size(); ++index) {
            auto& layer = layers[index];
            bool skip = false;
            bool wait_for_predecessor = false;
            if (layer.queued) {
                if (index + 1U < layers.size() && layers[index + 1U].queued) {
                    skip = true;
                } else if (index + 1U == layers.size() || !layers[index + 1U].active) {
                    layer.active = true;
                    layer.queued = false;
                    layer.inverse_weight = 0.0F;
                    notify_enabled(layer.clip, true);
                    states[layer.clip].time = layer.time;
                } else {
                    const auto& predecessor = layers[index + 1U];
                    const float remaining = predecessor.wrapped
                                                ? 0.0F
                                                : predecessor.length - predecessor.time;
                    if (remaining / predecessor.speed - dt > layer.initial_blend) {
                        wait_for_predecessor = true;
                    } else {
                        layer.active = true;
                        layer.queued = false;
                        layer.inverse_weight = 0.0F;
                        notify_enabled(layer.clip, true);
                        states[layer.clip].time = layer.time;
                    }
                }
            }
            if (wait_for_predecessor) {
                continue;
            }
            if (index != 0U && !skip) {
                layer.touched = true;
            }
            const float old_time = layer.time;
            const bool was_active = layer.active;
            layer.wrapped = false;
            if (layer.active) {
                if (layer.remaining_blend > 0.0F) {
                    layer.remaining_blend -= dt;
                    layer.inverse_weight = 1.0F;
                    if (layer.initial_blend != 0.0F && layer.remaining_blend > 0.0F) {
                        layer.inverse_weight = std::min(
                            layer.remaining_blend / layer.initial_blend, 1.0F);
                    }
                    if (layer.remaining_blend <= 0.0F) {
                        layer.blend_complete = true;
                        layer.inverse_weight = 0.0F;
                        layer.remaining_blend = 0.0F;
                    }
                }
                layer.time += dt * layer.speed;
                if (layer.length == 0.0F) {
                    if (layer.loop) {
                        layer.wrapped = true;
                        layer.time = 0.0F;
                    } else {
                        layer.time = 0.0F;
                        layer.active = false;
                        layer.remove = true;
                        layer.blend_complete = true;
                    }
                } else if (layer.time > layer.length) {
                    layer.time -= layer.length;
                    if (layer.loop) {
                        while (layer.time > layer.length) {
                            layer.time -= layer.length;
                        }
                        layer.wrapped = true;
                    } else {
                        layer.time = layer.length;
                        layer.active = false;
                        layer.remove = true;
                        layer.blend_complete = true;
                    }
                }
            }

            const float raw = 1.0F - layer.inverse_weight;
            const bool time_changed = old_time != layer.time;
            if (raw != 0.0F && (layer.active || was_active || time_changed)) {
                states[layer.clip].time = layer.time;
            }
            const float delta = raw - cumulative;
            cumulative += delta;
            if (delta != 0.0F) {
                if (!latch && time_changed) {
                    deferred.emplace_back(layer.clip, delta);
                } else if (layer.active && time_changed) {
                    states[layer.clip].weight = delta;
                }
            }
            if (delta == 1.0F && layer.touched) {
                latch = true;
            }
            if (prior_removal_latch) {
                layer.remove = true;
            }
            if (layer.blend_complete) {
                prior_removal_latch = true;
            }
        }

        const float deferred_factor = cumulative >= 1.0F || cumulative == 0.0F
                                          ? 2.0F
                                          : 1.0F - cumulative;
        for (const auto [clip, weight] : deferred) {
            states[clip].weight = weight * deferred_factor;
        }

        for (std::size_t index = 1U; index < layers.size();) {
            if (!layers[index].remove) {
                ++index;
                continue;
            }
            const auto clip = layers[index].clip;
            const bool preceding_same = std::any_of(
                layers.begin(), layers.begin() + static_cast<std::ptrdiff_t>(index),
                [&](const auto& layer) { return layer.clip == clip; });
            if (!preceding_same) {
                notify_enabled(clip, false);
            }
            layers[index] = std::move(layers.back());
            layers.pop_back();
        }
        sample_pose();
    }

    void sample_pose() {
        struct WeightedClip { std::size_t clip; float weight; };
        std::vector<WeightedClip> enabled;
        float sum = 0.0F;
        for (const auto clip : enabled_order) {
            if (!states[clip].enabled || states[clip].weight == 0.0F) {
                continue;
            }
            enabled.push_back({clip, states[clip].weight});
            sum += states[clip].weight;
        }
        if (enabled.empty()) {
            return;
        }
        if (sum > 1.0F) {
            for (auto& item : enabled) {
                item.weight /= sum;
            }
        }
        const auto mode = [&](std::size_t clip) {
            return clip == 0U ? AnimationPlaybackMode::loop : AnimationPlaybackMode::clamp;
        };
        std::vector<OgreAnimationLayer> sampled_layers;
        sampled_layers.reserve(enabled.size());
        for (const auto item : enabled) {
            const auto& clip = assets->clips[item.clip];
            sampled_layers.push_back({&clip.animation_skeleton, clip.animation_name,
                                      states[item.clip].time, item.weight, mode(item.clip)});
        }
        sampled_pose = sample_ogre_mesh_animation_layers(
            assets->mesh, assets->bind, sampled_layers);
    }
};

DropdownAnimation::DropdownAnimation(const PakArchive& archive)
    : impl_(std::make_unique<Impl>(archive)) {}
DropdownAnimation::~DropdownAnimation() = default;
DropdownAnimation::DropdownAnimation(DropdownAnimation&&) noexcept = default;
DropdownAnimation& DropdownAnimation::operator=(DropdownAnimation&&) noexcept = default;

void DropdownAnimation::set_open(bool value) {
    if (value == impl_->is_open) {
        impl_->is_open = value;
        return;
    }
    if (value) {
        impl_->sounds.push_back(DropdownSoundRequest::open);
        impl_->is_visible = true;
        if (impl_->playing(2U)) {
            impl_->blend(1U, false, kBlendSeconds, 2.0F);
        } else {
            impl_->play(1U, false, 2.0F);
        }
        impl_->queue(0U, true, kBlendSeconds, 1.0F);
    } else {
        impl_->sounds.push_back(DropdownSoundRequest::close);
        impl_->blend(2U, false, kBlendSeconds, 2.0F);
        impl_->is_closed = false;
    }
    impl_->is_open = value;
    impl_->sample_pose();
}

void DropdownAnimation::advance(float dt_seconds) {
    if (!std::isfinite(dt_seconds) || dt_seconds < 0.0F) {
        throw std::invalid_argument("dropdown animation dt must be finite and non-negative");
    }
    if (!impl_->is_open && impl_->is_closed) {
        return;
    }
    impl_->update(dt_seconds);
    if (!impl_->is_open && !impl_->is_closed && !impl_->playing(2U) && !impl_->queued(2U)) {
        impl_->is_visible = false;
        impl_->is_closed = true;
    }
}

bool DropdownAnimation::open() const noexcept { return impl_->is_open; }
bool DropdownAnimation::closed() const noexcept { return impl_->is_closed; }
bool DropdownAnimation::visible() const noexcept { return impl_->is_visible; }
bool DropdownAnimation::close_transition_complete() const noexcept {
    return !impl_->is_open && impl_->is_closed;
}

std::array<float, 2> DropdownAnimation::content_position(int width, int height) const {
    const auto& tag = dropdown_top(impl_->sampled_pose);
    const float scale = static_cast<float>(height) / 768.0F;
    return {static_cast<float>(width) * 0.5F + tag.position[0] * scale,
            static_cast<float>(height) * 0.5F - tag.position[1] * scale};
}

std::vector<UiDropdownMeshBatch> DropdownAnimation::draws(int width, int height) const {
    if (!impl_->is_visible) {
        return {};
    }
    std::vector<UiDropdownMeshBatch> result;
    std::size_t geometry_index = 0U;
    for (const auto& submesh : impl_->assets->mesh.submeshes) {
        const OgreGeometry* geometry = submesh.uses_shared_vertices
                                           ? &*impl_->assets->mesh.shared_geometry
                                           : &*submesh.geometry;
        const auto& posed = impl_->sampled_pose.geometries.at(geometry_index++);
        UiDropdownMeshBatch batch;
        batch.texture = impl_->assets->texture;
        batch.scene_blend = impl_->assets->material.scene_blend;
        batch.alpha_compare = impl_->assets->material.alpha_compare;
        batch.alpha_rejection = impl_->assets->material.alpha_rejection_value;
        batch.depth_write = impl_->assets->material.depth_write;
        batch.depth_check = impl_->assets->material.depth_check;
        batch.vertices.reserve(submesh.indices.size());
        const float scale = static_cast<float>(height) / 768.0F;
        for (const auto source_index : submesh.indices) {
            const auto& position = posed.positions.at(source_index);
            const auto& uv = geometry->texcoords.at(source_index);
            batch.vertices.push_back(
                {static_cast<float>(width) * 0.5F + position[0] * scale,
                 static_cast<float>(height) * 0.5F - position[1] * scale,
                 uv[0], uv[1], {1.0F, 1.0F, 1.0F, 1.0F}});
        }
        result.push_back(std::move(batch));
    }
    return result;
}

const OgreMeshPose& DropdownAnimation::pose() const noexcept { return impl_->sampled_pose; }

std::vector<DropdownAnimationLayerState> DropdownAnimation::layers() const {
    std::vector<DropdownAnimationLayerState> result;
    result.reserve(impl_->layers.size());
    for (const auto& layer : impl_->layers) {
        const auto clip = layer.clip == 0U ? DropdownAnimationClip::idle
                          : layer.clip == 1U ? DropdownAnimationClip::open
                                             : DropdownAnimationClip::close;
        const float weight = impl_->states[layer.clip].enabled
                                 ? impl_->states[layer.clip].weight : 0.0F;
        result.push_back({clip, layer.time, layer.length, weight, layer.speed,
                          layer.active, layer.queued});
    }
    return result;
}

std::vector<DropdownSoundRequest> DropdownAnimation::consume_sound_requests() {
    return std::exchange(impl_->sounds, {});
}

} // namespace torchlight
