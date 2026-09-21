#pragma once

#include "torchlight/settings.hpp"
#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_window_runtime.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {

class UiResources;
class UiFont;

struct UiResolution {
    int width = 0;
    int height = 0;
    friend bool operator==(const UiResolution& a, const UiResolution& b) noexcept {
        return a.width == b.width && a.height == b.height;
    }
};

enum class UiSettingsComboKind { resolution, shadow, particle };

struct UiComboOption {
    std::string text;
    // Original ListboxTextItem::d_ID.  Resolution uses the supplied host
    // index; shadow uses 0..5; particle uses 0..2.
    std::size_t id = 0;
    UiResolution resolution{};
    float particle_fps = 0.0F;
    float particle_percent = 0.0F;
};

struct UiComboSelection {
    UiSettingsComboKind kind{};
    std::size_t index = 0;
    UiComboOption option;
};

struct UiComboboxIds {
    UiWindowId combobox = 0;
    UiWindowId editbox = 0;
    UiWindowId droplist = 0;
    UiWindowId drop_button = 0;
    UiWindowId horizontal_scrollbar = 0;
    UiWindowId vertical_scrollbar = 0;
};

// Render-only list rows.  The autochildren themselves remain ordinary
// UiWindowRuntime nodes in the shared immutable snapshot.
struct UiComboPaintRow {
    UiWindowId droplist = 0;
    std::size_t option = 0;
    std::string text;
    UiRect rect;
    UiRect clip;
    bool selected = false;
    bool highlighted = false;
    std::size_t paint_order = 0;
};

class UiSettingsComboboxes {
public:
    UiSettingsComboboxes(UiWindowRuntime&, UiResources&);
    ~UiSettingsComboboxes();
    UiSettingsComboboxes(const UiSettingsComboboxes&) = delete;
    UiSettingsComboboxes& operator=(const UiSettingsComboboxes&) = delete;

    [[nodiscard]] static std::vector<UiComboOption> resolution_options(
        const std::vector<UiResolution>&);
    [[nodiscard]] static std::vector<UiComboOption> shadow_options();
    [[nodiscard]] static std::vector<UiComboOption> particle_options();

    // The combobox is an existing settingsmenu.layout window.  add creates
    // the Falagard autochildren and may be called once per kind.
    const UiComboboxIds& add(UiSettingsComboKind, UiWindowId combobox,
                             std::vector<UiComboOption>);
    void update_options(UiSettingsComboKind, std::vector<UiComboOption>);
    void sync(const DisplaySettings&);
    // Re-evaluates FontDim metrics for the current viewport and writes the
    // resulting autochild geometry to the shared runtime.
    void layout(const UiWindowSnapshot&);

    [[nodiscard]] bool has(UiSettingsComboKind) const noexcept;
    [[nodiscard]] bool handles(UiWindowId) const noexcept;
    [[nodiscard]] bool pointer_down(UiWindowId, const UiWindowSnapshot&, float x, float y);
    void pointer_move(const UiWindowSnapshot&, float x, float y, bool left_down);
    [[nodiscard]] std::optional<UiComboSelection> pointer_up(
        UiWindowId, const UiWindowSnapshot&, float x, float y);
    void hide_all();
    void reconcile_capture();

    [[nodiscard]] bool popup_visible(UiSettingsComboKind) const;
    [[nodiscard]] const UiComboboxIds& ids(UiSettingsComboKind) const;
    [[nodiscard]] const std::vector<UiComboOption>& options(UiSettingsComboKind) const;
    [[nodiscard]] std::size_t selected(UiSettingsComboKind) const;
    [[nodiscard]] std::vector<UiComboPaintRow> paint(const UiWindowSnapshot&) const;

    // Applies fields that DisplaySettings actually owns.  The exact original
    // particle FPS/PCT pair remains in UiComboSelection for the particle
    // runtime consumer; MAX_PARTICLES is a separate setting and is untouched.
    static void apply(const UiComboSelection&, DisplaySettings&);

private:
    struct Entry;
    UiWindowRuntime* runtime_;
    UiResources* resources_;
    std::unique_ptr<UiFont> font_;
    float line_height_ = 16.0F;
    std::vector<Entry> entries_;

    Entry& entry(UiSettingsComboKind);
    const Entry& entry(UiSettingsComboKind) const;
    Entry* owner(UiWindowId) noexcept;
    const Entry* owner(UiWindowId) const noexcept;
    void show(Entry&);
    void hide(Entry&, bool restore_selection);
    [[nodiscard]] std::optional<std::size_t> item_at(
        const Entry&, const UiWindowSnapshot&, float x, float y) const;
    [[nodiscard]] float line_height(int width, int height) const;
    void layout_entry(Entry&, float line_height, float offset_ratio,
                      float vertical_frame_margin);
};

} // namespace torchlight
