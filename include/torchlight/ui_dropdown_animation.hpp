#pragma once

#include "torchlight/ogre_material.hpp"
#include "torchlight/skeletal_animation.hpp"
#include "torchlight/ui_skin.hpp"

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace torchlight {

class PakArchive;

enum class DropdownAnimationClip { open, close, idle };
enum class DropdownSoundRequest : std::uint8_t { open = 22, close = 66 };

struct DropdownAnimationLayerState {
    DropdownAnimationClip clip = DropdownAnimationClip::idle;
    float time = 0.0F;
    float length = 0.0F;
    float weight = 0.0F;
    float speed = 1.0F;
    bool active = false;
    bool queued = false;
};

struct UiDropdownMeshBatch {
    std::string texture;
    std::vector<UiSkinVertex> vertices;
    OgreSceneBlend scene_blend = OgreSceneBlend::replace;
    OgreAlphaCompare alpha_compare = OgreAlphaCompare::always;
    std::uint8_t alpha_rejection = 0;
    bool depth_write = true;
    bool depth_check = true;
};

// Resource-backed model-enabled CDropdownMenu branch consumed by Options.
// CSettingsMenu overrides setOpen and leaves its flags=0 model hidden. This
// object owns per-menu animation state; parsed assets are shared and immutable.
class DropdownAnimation {
public:
    explicit DropdownAnimation(const PakArchive& archive);
    ~DropdownAnimation();
    DropdownAnimation(DropdownAnimation&&) noexcept;
    DropdownAnimation& operator=(DropdownAnimation&&) noexcept;
    DropdownAnimation(const DropdownAnimation&) = delete;
    DropdownAnimation& operator=(const DropdownAnimation&) = delete;

    void set_open(bool open);
    void advance(float dt_seconds);

    [[nodiscard]] bool open() const noexcept;
    [[nodiscard]] bool closed() const noexcept;
    [[nodiscard]] bool visible() const noexcept;
    [[nodiscard]] bool close_transition_complete() const noexcept;
    [[nodiscard]] std::array<float, 2> content_position(int width, int height) const;
    [[nodiscard]] std::vector<UiDropdownMeshBatch> draws(int width, int height) const;
    [[nodiscard]] const OgreMeshPose& pose() const noexcept;
    [[nodiscard]] std::vector<DropdownAnimationLayerState> layers() const;
    [[nodiscard]] std::vector<DropdownSoundRequest> consume_sound_requests();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace torchlight
