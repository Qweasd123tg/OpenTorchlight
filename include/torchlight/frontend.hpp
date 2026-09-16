#pragma once
#include "torchlight/save_store.hpp"
#include "torchlight/ui_layout.hpp"
#include "torchlight/inventory_view.hpp"

namespace torchlight {
// Portable application policy. Original callback names are routed explicitly;
// this is not the original CGameStateController or an arbitrary script runner.
enum class FrontendPage { main, create, load, playing, pause, quit };
enum class FrontendKey { previous, next, accept, back, backspace };
enum class FrontendCommand { create, load, save, save_and_menu, save_and_quit };
struct FrontendRequest {
    FrontendCommand command = FrontendCommand::create;
    std::int64_t class_guid = 0;
    std::string name, slot;
};
struct FrontendClass {
    std::int64_t guid = 0;
    std::string name;
};
struct FrontendButton {
    std::string id, text;
    // Original skin references resolved from the looknfeel when available.
    std::string image, hover_image, font;
    UiRect rect;
    bool enabled = true, focused = false, selected = false;
};
struct FrontendFrame {
    std::string title;
    std::vector<UiResolvedWidget> decorations;
    std::vector<FrontendButton> buttons;
    std::vector<InventoryViewLine> notes;
    bool original_layout = false;
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
    std::optional<FrontendRequest> request_;
    void activate(const std::string &id);
};
} // namespace torchlight
