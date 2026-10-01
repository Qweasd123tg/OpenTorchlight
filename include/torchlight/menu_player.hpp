#pragma once

#include "torchlight/menu_scene.hpp"
#include "torchlight/player.hpp"
#include "torchlight/scene_animation.hpp"

namespace torchlight {

class PlayerSession;

// Read-only current-player snapshot for alive Load/return-to-menu previews.
// Dead models remain unsupported; no living replacement is supplied.
[[nodiscard]] std::optional<PlayerPrototype> menu_player_visual(
    const PlayerPrototype&, const PlayerSession&);

// Connected menu actor slice. Shares the gameplay mesh, wardrobe-layer,
// skeleton sampler and hand-tag consumers; not a second character simulation.
struct MenuPlayerPreview {
    FixedSceneGeometry geometry;
    PlayerPrototype prototype;
    std::size_t body_instance = 0;
    std::optional<std::size_t> weapon_instance;
    ModelAnimationClip idle;
};
struct MenuPlayerPose {
    OgreMeshPose body;
    std::optional<LayoutWorldTransform> weapon;
};
[[nodiscard]] MenuPlayerPreview build_menu_player_preview(
    const PakArchive&, const MenuScene&, const PlayerPrototype&);
[[nodiscard]] MenuPlayerPose sample_menu_player_preview(const MenuPlayerPreview&, float seconds);

} // namespace torchlight
