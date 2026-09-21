#pragma once

#include "torchlight/ui_layout.hpp"
#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <string_view>
#include <vector>

namespace torchlight {

using UiWindowId = std::size_t;

enum class UiWindowEventType {
    activated,
    deactivated,
    capture_gained,
    capture_lost,
    mouse_retarget_requested,
    child_added,
    child_removed,
    parent_sized,
    z_changed,
    shown,
    hidden,
    enabled,
    disabled,
    selection_changed,
    destruction_started,
};

struct UiWindowEvent {
    UiWindowEventType type;
    UiWindowId window;
    std::optional<UiWindowId> related;
};

struct UiWindowSnapshot {
    std::vector<UiResolvedWidget> widgets;
    std::vector<UiWindowId> source_ids;
    std::vector<std::optional<std::size_t>> resolved_index_by_id;
    std::optional<std::size_t> sheet;
    int width = 0;
    int height = 0;
    UiLayoutState layout_state;
};

// WindowManager/Window lifetime dependencies. The production owner binds
// these to tooltip windows, renderer instances and per-window render caches.
// Callback exceptions propagate at the original call boundary.
struct UiWindowLifecycle {
    std::function<void(UiWindowId, const UiWidget&)> initialize;
    std::function<void(UiWindowId)> reset_tooltip_target;
    std::function<void(UiWindowId)> release_tooltip;
    std::function<void(UiWindowId, const UiWidget&)> detach_renderer;
    std::function<void(UiWindowId, const UiWidget&)> destroy_renderer;
    std::function<void(UiWindowId, const UiWidget&)> destroy_factory_object;
    std::function<void(UiWindowId)> mouse_down;
};

// Persistent owner for the subset of the shipped CEGUI Window/System state
// consumed by the frontend. IDs are never reused; destroy makes an ID a
// tombstone immediately and clean_dead_pool performs the deferred release.
class UiWindowRuntime {
public:
    using EventListener = std::function<void(const UiWindowEvent&)>;
    using ButtonCallback = std::function<void(UiWindowId)>;
    using ThumbMoveCallback = std::function<void(UiWindowId, float)>;
    using RepeatCallback = std::function<void(UiWindowId, std::uint8_t)>;

    UiWindowRuntime();
    ~UiWindowRuntime();
    UiWindowRuntime(UiWindowRuntime&&) noexcept;
    UiWindowRuntime& operator=(UiWindowRuntime&&) noexcept;
    UiWindowRuntime(const UiWindowRuntime&) = delete;
    UiWindowRuntime& operator=(const UiWindowRuntime&) = delete;

    [[nodiscard]] UiWindowId create(
        UiWidget widget, std::optional<UiLayoutFunction> binding = std::nullopt);
    [[nodiscard]] std::vector<UiWindowId> create(const UiLayout& layout);
    void add_child(UiWindowId parent, UiWindowId child);
    void remove_child(UiWindowId parent, UiWindowId child);
    void destroy(UiWindowId);
    void clean_dead_pool();

    [[nodiscard]] bool alive(UiWindowId) const noexcept;
    [[nodiscard]] const UiWidget& window(UiWindowId) const;
    [[nodiscard]] const std::vector<UiWindowId>& children(UiWindowId) const;
    [[nodiscard]] std::optional<UiWindowId> find(std::string_view name) const;

    void set_sheet(std::optional<UiWindowId>);
    void set_mouse_target(std::optional<UiWindowId>);
    void set_modal(UiWindowId, bool);
    [[nodiscard]] bool capture_input(UiWindowId);
    void release_input(UiWindowId);
    void set_restore_capture(UiWindowId, bool);
    void set_distributes_captured_inputs(UiWindowId, bool);
    void activate(UiWindowId);
    void deactivate(UiWindowId);
    void set_visible(UiWindowId, bool);
    void set_enabled(UiWindowId, bool);
    void set_zero_position(UiWindowId, bool);
    void move_to_front(UiWindowId);
    void move_to_back(UiWindowId);
    void set_property(UiWindowId, std::string key, std::string value);

    [[nodiscard]] std::optional<UiWindowId> sheet() const noexcept;
    [[nodiscard]] std::optional<UiWindowId> mouse_target() const noexcept;
    [[nodiscard]] std::optional<UiWindowId> modal() const noexcept;
    [[nodiscard]] std::optional<UiWindowId> capture() const noexcept;
    [[nodiscard]] bool is_active(UiWindowId) const;
    [[nodiscard]] std::size_t revision() const noexcept;

    [[nodiscard]] UiWindowSnapshot snapshot(
        int width, int height, const UiLayoutState& state = {}) const;
    [[nodiscard]] std::optional<UiWindowId> target_at_position(
        const UiWindowSnapshot&, float x, float y) const;
    [[nodiscard]] std::vector<UiWindowId> dispatch_path(
        std::optional<UiWindowId> target) const;

    // Only the three resource widget classes backed by CEGUI ButtonBase are
    // accepted. The base callback runs after rise/activation and before
    // ButtonBase capture/pushed, matching the shipped virtual call order.
    [[nodiscard]] bool is_button(UiWindowId) const;
    bool window_mouse_down(UiWindowId, std::uint8_t, const ButtonCallback& = {});
    void window_mouse_up(UiWindowId);
    void advance(float seconds, const RepeatCallback&);
    [[nodiscard]] bool button_mouse_down(UiWindowId, const UiWindowSnapshot&,
                                         float x, float y,
                                         const ButtonCallback& base_callback = {});
    [[nodiscard]] bool button_mouse_up(UiWindowId, const UiWindowSnapshot&,
                                       float x, float y, const ButtonCallback& derived_effect = {});
    void button_mouse_move(UiWindowId, const UiWindowSnapshot&, float x, float y);
    void button_mouse_leave(UiWindowId);
    [[nodiscard]] bool button_pushed(UiWindowId) const;
    [[nodiscard]] bool button_hovering(UiWindowId) const;
    [[nodiscard]] bool button_selected(UiWindowId) const;
    void set_button_selected(UiWindowId, bool);
    [[nodiscard]] bool is_thumb(UiWindowId) const;
    [[nodiscard]] bool thumb_mouse_down(UiWindowId, const UiWindowSnapshot&,
                                        float x, float y, const ButtonCallback& base_callback = {});
    void thumb_mouse_move(UiWindowId, const UiWindowSnapshot&, float x, float y,
                          const ThumbMoveCallback&);
    [[nodiscard]] bool thumb_mouse_up(UiWindowId, const UiWindowSnapshot&, float x, float y);

    void set_event_listener(EventListener);
    void set_lifecycle(UiWindowLifecycle);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace torchlight
