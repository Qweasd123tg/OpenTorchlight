#pragma once
#include "torchlight/ui_pointer_event.hpp"
#include "torchlight/frontend.hpp"
#include "torchlight/settings.hpp"
#include "torchlight/gles_scene_renderer.hpp"
#include "torchlight/gles_ui_renderer.hpp"
#include "torchlight/ui_hud.hpp"
#include "torchlight/ui_combobox.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/player_session.hpp"
#include <filesystem>
#include <optional>

namespace torchlight {
// Port-native orchestration shared by the real window and deterministic scenarios.
// No window API, wall clock or random_device is owned by this component.
struct ApplicationOptions {
    std::filesystem::path game_directory;
    std::uint64_t frame_limit = 0; // Explicit legacy preview mode, NOT menu acceptance.
    std::optional<std::size_t> main_stratum;
    std::uint32_t seed = 42;
    std::optional<std::filesystem::path> save_directory;
    std::optional<std::filesystem::path> settings_directory;
    // PORT diagnostic header. Does not disable inventory, services or death UI.
    bool debug_ui = false;
    // Explicit resource/event preview, not recovered animated inventory UI.
    bool inventory_ui_preview = false;
    // Menu/world music (plain OGG next to the game). Off unless the host
    // opts in, so scenario tests stay hermetic and silent.
    bool music_enabled = false;
    std::filesystem::path music_directory;
    float music_volume = 1.0F;
    bool music_mute = false;
    DisplaySettings settings;
};
struct ApplicationView {
    // Borrowed read-only values, valid ONLY during observe_game(). No pointer is
    // an object identity and nothing here may be retained past the callback.
    const char* phase = "before_input";
    FrontendPage page = FrontendPage::main;
    std::uint64_t frame = 0, level_frame = 0, revision = 0;
    std::uint32_t seed = 0;
    std::int64_t class_guid = 0;
    std::string character_name, slot;
    DungeonAddress address;
    Vector3 player_position{}, recovery_anchor{};
    float player_angle = 0, floor_offset = 0;
    std::size_t player_instance = 0;
    std::optional<std::size_t> weapon_instance;
    bool inventory_open = false, moving = false;
    int inventory_tab = 14;
    const PlayerSession* session = nullptr;
    const RuntimeEntityWorld* world = nullptr;
    const LogicRuntime* logic = nullptr;
    const QuestCheckpoint* quests = nullptr;
    const EnemyController* enemies = nullptr;
    const NavigationGrid* navigation = nullptr;
    const LayoutManifest* layout = nullptr;
    const FixedSceneGeometry* geometry = nullptr;
    const GlesSceneRenderer* renderer = nullptr;
    const OgreMeshPose* player_pose = nullptr;
};
class ApplicationHost {
public:
    virtual ~ApplicationHost() = default;
    virtual bool process_events() = 0;
    virtual std::optional<std::array<int, 2>> take_left_click() = 0;
    // Optional UI release channel, separate from press-to-move world input.
    // Old scenario hosts remain valid and report no physical pointer state.
    virtual std::optional<UiPointerClick> take_ui_click() { return std::nullopt; }
    virtual UiPointerState ui_pointer_state() const noexcept { return {}; }
    virtual bool has_ui_pointer_events() const noexcept { return false; }
    virtual std::vector<UiPointerEvent> take_ui_pointer_events() { return {}; }
    // Backend-neutral physical US scan-code contract; see application_keys.hpp.
    virtual std::vector<std::uint32_t> take_key_presses() = 0;
    virtual int width() const noexcept = 0;
    virtual int height() const noexcept = 0;
    // Physical modes exposed by the host. Deterministic/minimal hosts retain
    // their current viewport as the sole real resolution.
    virtual std::vector<UiResolution> display_resolutions() const {
        return {{width(), height()}};
    }
    virtual double clock_seconds() = 0;
    virtual std::uint32_t new_campaign_seed() = 0;
    virtual void draw_menu_frame(GlesUiRenderer&, const FrontendFrame&) = 0;
    // Hosts without a scene presenter retain their existing resource-only
    // menu path. The desktop draws the original scene before the UI overlay.
    virtual void draw_menu_scene(GlesSceneRenderer&, GlesUiRenderer& ui,
                                 const FrontendFrame& frame) { draw_menu_frame(ui, frame); }
    virtual void draw_scene_frame(GlesSceneRenderer&, GlesUiRenderer&,
                                  const std::vector<InventoryViewLine>&, bool,
                                  const UiHudFrame&) = 0;
    virtual void observe_frontend(FrontendPage, const FrontendFrame&, const std::string&) {}
    virtual void observe_game(const ApplicationView&) {}
    virtual void notice(std::string_view, std::string_view) {}
};
// Preserves the existing application policy and update ordering; not a recovered
// original scheduler. A scripted fixed clock is explicitly a prototype driver.
int run_application(const ApplicationOptions& options, ApplicationHost& host);
} // namespace torchlight
