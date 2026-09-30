#pragma once
#include "torchlight/save_store.hpp"
#include "torchlight/settings.hpp"
#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_dropdown.hpp"
#include "torchlight/ui_dropdown_animation.hpp"
#include "torchlight/ui_pointer_event.hpp"
#include "torchlight/ui_pointer_timing.hpp"
#include "torchlight/ui_tooltip.hpp"
#include "torchlight/ui_combobox.hpp"
#include "torchlight/ui_skin.hpp"
#include "torchlight/ui_window_runtime.hpp"
#include "torchlight/ui_hud.hpp"
#include "torchlight/inventory_view.hpp"
#include "torchlight/cegui_menu.hpp"

namespace torchlight {
// Portable application policy. Original callback names are routed explicitly;
// this is not the original CGameStateController or an arbitrary script runner.
enum class FrontendPage { main, create, load, playing, pause, settings, quit };
enum class FrontendKey { previous, next, accept, back, backspace };
enum class FrontendCommand { create, load, save, save_and_menu, save_and_quit, remove,
                             apply_settings };
struct FrontendRequest {
    FrontendCommand command = FrontendCommand::create;
    std::int64_t class_guid = 0;
    std::string name, slot;
    DisplaySettings settings;
    FrontendRequest() = default;
    FrontendRequest(FrontendCommand command_in, std::int64_t class_guid_in, std::string name_in,
                    std::string slot_in, DisplaySettings settings_in = {})
        : command(command_in),
          class_guid(class_guid_in),
          name(std::move(name_in)),
          slot(std::move(slot_in)),
          settings(std::move(settings_in)) {
    }
};
struct FrontendClass {
    std::int64_t guid = 0;
    std::string name;
    // resource-derived UNIT DESCRIPTION for CharacterClassDescription. May be empty.
    std::string description;
    FrontendClass() = default;
    FrontendClass(std::int64_t guid_in, std::string name_in, std::string description_in = {})
        : guid(guid_in), name(std::move(name_in)), description(std::move(description_in)) {
    }
};
struct FrontendButton {
    FrontendPage owner = FrontendPage::main;
    std::string id, text;
    // Original skin references resolved from the looknfeel when available.
    std::string image, hover_image, font;
    UiRect rect;
    bool enabled = true, focused = false, selected = false;
    bool hovered = false, pressed = false;
    std::string pushed_image, disabled_image;
    bool supplemental = true;
    UiResolvedWidget widget;
};
struct FrontendListItem {
    UiSkinDraw draw;
    std::size_t paint_order = 0;
};
struct FrontendFrame {
    std::optional<CeguiMenuFrame> cegui;
    std::vector<FrontendListItem> list_items;
    std::map<std::string, UiSkinState> window_states;
    std::vector<UiDropdownMeshBatch> dropdown_meshes;
    std::string title;
    std::vector<UiResolvedWidget> decorations;
    std::vector<FrontendButton> buttons;
    std::vector<InventoryViewLine> notes;
    bool original_layout = false;
    std::vector<UiResolvedWidget> texts;
};
// One entry per window, ordered across images, controls and text. The button
// index retains the portable fallback/input adapter; widget contains live values.
struct FrontendPaintItem {
    UiResolvedWidget widget;
    std::optional<std::size_t> button;
    std::optional<UiSkinDraw> direct_draw = std::nullopt;
    UiSkinState state{};
};
[[nodiscard]] std::vector<FrontendPaintItem> frontend_paint_list(const FrontendFrame &frame);
// Original five-row visibility and highlight draw-list writes. The save list
// is supplied by the portable .otc adapter, not the original SVB producer.
[[nodiscard]] UiLayoutState continue_menu_layout_state(
    const UiLayout& layout, std::size_t count, std::size_t scroll,
    std::size_t selected, bool delete_confirmation);
class Frontend : private MainMenuActions {
  public:
    Frontend(UiResources &resources, std::vector<FrontendClass> classes);
    ~Frontend();
    [[nodiscard]] FrontendPage page() const noexcept {
        return page_;
    }
    void set_saves(std::vector<SaveSlotInfo> saves);
    void show_main();
    void pause();
    void entered_game();
    void error(std::string message);
    void saved(FrontendCommand command);
    void removed();
    void applied();
    // Pushes current settings data (no page change); the settings page opens
    // from activate("settings") and returns to the opening page.
    void sync_settings(DisplaySettings settings);
    void set_resolutions(std::vector<UiResolution> resolutions);
    [[nodiscard]] const DisplaySettings& audio_settings() const noexcept {
        return page_ == FrontendPage::settings ? settings_draft_ : settings_clean_;
    }
    void pointer(const UiPointerState& state);
    void pointer_event(const UiPointerEvent& event);
    void advance(float seconds);
    [[nodiscard]] bool has_closing_windows() const noexcept;
    [[nodiscard]] std::vector<DropdownSoundRequest> take_dropdown_sounds();
    void text(char ascii);
    void key(FrontendKey key);
    void click(float x, float y);
    [[nodiscard]] FrontendFrame frame(int width, int height);
    [[nodiscard]] std::optional<FrontendRequest> take_request();
    [[nodiscard]] const std::string &character_name() const noexcept {
        return name_;
    }
    [[nodiscard]] std::size_t frame_build_count() const noexcept { return frame_build_count_; }

  private:
    UiResources *resources_;
    std::vector<FrontendClass> classes_;
    std::vector<SaveSlotInfo> saves_;
    std::vector<FrontendButton> buttons_;
    std::optional<FrontendFrame> cached_frame_;
    int cached_width_ = 0, cached_height_ = 0;
    std::size_t frame_build_count_ = 0;
    FrontendPage page_ = FrontendPage::main;
    std::string name_ = "Hero", status_;
    std::size_t class_index_ = 0, save_index_ = 0, scroll_ = 0, focus_ = 0;
    std::optional<std::size_t> pending_delete_;
    bool show_credits_ = false, show_credits_b_ = false;
    struct ResourceWindows;
    std::unique_ptr<ResourceWindows> resource_windows_;
    std::unique_ptr<CeguiMenu> cegui_menu_;
    std::array<bool, 8> cegui_buttons_{};
    void sync_cegui_menu();
    UiWindowRuntime windows_;
    std::unique_ptr<UiTooltips> tooltips_;
    std::unique_ptr<UiSettingsComboboxes> comboboxes_;
    std::vector<UiResolution> resolutions_;
    std::map<UiSettingsComboKind, UiWindowId> bound_comboboxes_;
    UiPointerTiming pointer_timing_;
    double pointer_clock_ = 0;
    UiWindowId sheet_;
    std::unique_ptr<StaticDropdownState> main_dropdown_;
    bool main_open_ = false;
    std::map<FrontendPage, std::unique_ptr<StaticDropdownState>> dropdowns_;
    std::map<FrontendPage, const UiLayout*> bound_layouts_;
    std::unique_ptr<DropdownAnimation> options_animation_;
    bool options_animation_attempted_ = false;
    bool pending_options_exit_ = false;
    UiWindowSnapshot window_snapshot_;
    bool ordered_pointer_ = false;
    bool retargeting_ = false;
    std::size_t cached_revision_ = 0;
    std::map<UiWindowId, UiWindowId> slider_thumbs_;
    [[nodiscard]] StaticDropdownState& dropdown(FrontendPage);
    void sync_windows();
    void resolve_windows(int width, int height);
    void retarget_pointer();
    void dispatch_pointer_down(UiWindowId, const UiPointerEvent&, UiPointerDownDecision, bool bubble = true);
    void bind_settings_combos();
    [[nodiscard]] FrontendFrame build_frame(FrontendPage render_page, int width, int height);
    [[nodiscard]] FrontendFrame compose_frame(int width, int height);
    const UiLayout* main_layout_ = nullptr;
    std::vector<UiResolvedWidget> input_widgets_;
    UiPointerState pointer_;
    std::array<float, 2> last_pointer_position_{};
    std::string pressed_window_;
    std::string dragging_slider_;
    float slider_drag_offset_ = 0;
    [[nodiscard]] std::optional<std::size_t> button_at(float x, float y) const;
    [[nodiscard]] FrontendFrame pointer_frame(FrontendFrame frame) const;
    bool main_linux_credits_ = false, main_exit_requested_ = false;
    DisplaySettings settings_clean_, settings_draft_;
    FrontendPage settings_return_ = FrontendPage::main;
    void leave_settings();
    std::optional<FrontendRequest> request_;
    void activate(const std::string &id, std::optional<UiLayoutFunction> function = std::nullopt);
    bool main_can_load() const override;
    void main_request_state(int game_state, int menu) override;
    void main_set_open(bool) override;
    void main_request_exit() override;
    void main_close_all() override;
    void main_toggle_settings() override;
    bool main_has_linux_credits() const override;
    void main_show_credits(bool linux_panel, bool visible) override;
};
} // namespace torchlight
