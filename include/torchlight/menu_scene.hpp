#pragma once

#include "torchlight/scene_geometry.hpp"

namespace torchlight {

struct MenuSceneCamera {
    Vector3 position{};
    Vector3 target{};
    // original-code: CGame::createCamera, research/menu-scene.md.
    float fov_degrees = 35.0F;
    float near_clip = 1.0F;
    float far_clip = 90.0F;
};

struct MenuScene {
    FixedLevelScene level;
    FixedSceneGeometry geometry;
    MenuSceneCamera camera;
};

// CLevel::loadRoomLayout's Property Node camera markers, in world space.
// No GL calls; missing markers fail instead of choosing a fitted camera.
[[nodiscard]] MenuSceneCamera menu_scene_camera(const LayoutManifest& layout,
                                               bool netbook_mode = false);

// No-save branch only: setGameState -> TOWN depth 1 -> MAINMENURULES.
// Room-piece geometry only; skybox/particles/menu actors remain open.
[[nodiscard]] MenuScene build_main_menu_scene(const PakArchive& archive,
                                             const LevelsetCatalog& levelsets,
                                             bool netbook_mode = false);

} // namespace torchlight
