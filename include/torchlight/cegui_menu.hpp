#pragma once
#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_pointer_event.hpp"
#include "torchlight/settings.hpp"
#include "torchlight/ui_combobox.hpp"
#include <functional>
#include <memory>

namespace torchlight {
[[nodiscard]] std::string main_menu_credit_text();
// Renderer transport only. Window state, clipping, text layout and Falagard
// imagery are produced by the pinned CEGUI library, not reconstructed here.
struct CeguiTextureData {
    std::uint32_t width = 0, height = 0;
    std::uint64_t revision = 0;
    std::vector<std::uint8_t> rgba;
};
struct CeguiQuad {
    UiRect destination, uv;
    std::array<std::array<float, 4>, 4> colours{}; // TL, TR, BL, BR
    std::shared_ptr<const CeguiTextureData> texture;
    float z = 0;
    bool bottom_left_to_top_right = false;
};
enum class CeguiPage { main, options, settings, create };
struct CeguiWidget : UiResolvedWidget {
    CeguiPage page = CeguiPage::main;
};
struct CeguiMenuFrame {
    std::vector<CeguiQuad> quads;
    std::vector<CeguiWidget> widgets;
};
class CeguiMenu {
  public:
    using Action = std::function<void(CeguiPage, const std::string&, UiLayoutFunction)>;
    CeguiMenu(const PakArchive&, Action);
    ~CeguiMenu();
    CeguiMenu(const CeguiMenu&) = delete;
    CeguiMenu& operator=(const CeguiMenu&) = delete;
    static bool available(const PakArchive&);
    void state(bool open, bool can_continue, bool credits, bool linux_credits);
    void settings_state(bool open, const DisplaySettings&, const std::vector<UiResolution>&);
    [[nodiscard]] DisplaySettings settings_values(DisplaySettings base, bool applying = false) const;
    void options_state(bool attached, const std::array<float, 2>& content_position);
    void focus(CeguiPage, const std::string& window_name);
    void creation_state(bool open, const std::string& class_name,
        const std::string& display_name, const std::string& description);
    [[nodiscard]] std::string creation_name() const;
    void keyboard_event(const UiKeyboardEvent&);
    void resize(int width, int height);
    void pointer_event(const UiPointerEvent&);
    void advance(float seconds);
    [[nodiscard]] CeguiMenuFrame frame(int width, int height);
    [[nodiscard]] bool has_linux_credits() const;
  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
