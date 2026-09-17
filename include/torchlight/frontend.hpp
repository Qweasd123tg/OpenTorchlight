#pragma once
#include "torchlight/save_store.hpp"
#include "torchlight/settings.hpp"
#include "torchlight/ui_layout.hpp"
#include "torchlight/inventory_view.hpp"

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
    std::string id, text;
    // Original skin references resolved from the looknfeel when available.
    std::string image, hover_image, font;
    UiRect rect;
    bool enabled = true, focused = false, selected = false;
    std::string pushed_image, disabled_image;
    bool supplemental = true;
    UiResolvedWidget widget;
};
struct FrontendFrame {
    std::string title;
    std::vector<UiResolvedWidget> decorations;
    std::vector<FrontendButton> buttons;
    std::vector<InventoryViewLine> notes;
    bool original_layout = false;
    std::vector<UiResolvedWidget> texts;
};
class Frontend {
  public:
    Frontend(UiResources &resources, std::vector<FrontendClass> classes);
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
    void text(char ascii);
    void key(FrontendKey key);
    void click(float x, float y);
    [[nodiscard]] FrontendFrame frame(int width, int height);
    [[nodiscard]] std::optional<FrontendRequest> take_request();
    [[nodiscard]] const std::string &character_name() const noexcept {
        return name_;
    }

  private:
    UiResources *resources_;
    std::vector<FrontendClass> classes_;
    std::vector<SaveSlotInfo> saves_;
    std::vector<FrontendButton> buttons_;
    FrontendPage page_ = FrontendPage::main;
    std::string name_ = "Hero", status_;
    std::size_t class_index_ = 0, save_index_ = 0, scroll_ = 0, focus_ = 0;
    std::optional<std::size_t> pending_delete_;
    bool show_credits_ = false, show_credits_b_ = false;
    DisplaySettings settings_clean_, settings_draft_;
    FrontendPage settings_return_ = FrontendPage::main;
    void leave_settings();
    std::optional<FrontendRequest> request_;
    void activate(const std::string &id);
};
} // namespace torchlight
