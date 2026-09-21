#pragma once

#include "torchlight/ui_window_runtime.hpp"

#include <cstdint>
#include <memory>
#include <optional>

namespace torchlight {

class UiResources;

enum class UiTooltipPhase : std::uint8_t {
    inactive = 0,
    active = 1,
    fade_in = 2,
    fade_out = 3,
};

// Production owner for the CEGUI Tooltip state consumed by the frontend.
// Window storage remains owned by UiWindowRuntime; custom tooltip windows are
// owned by their source window and are destroyed through release_owned().
class UiTooltips {
public:
    UiTooltips(UiWindowRuntime&, UiResources&);
    ~UiTooltips();
    UiTooltips(const UiTooltips&) = delete;
    UiTooltips& operator=(const UiTooltips&) = delete;

    [[nodiscard]] UiWindowId default_tooltip() const noexcept;
    [[nodiscard]] std::optional<UiWindowId> current_tooltip() const noexcept;
    [[nodiscard]] std::optional<UiWindowId> target(UiWindowId tooltip) const;
    [[nodiscard]] UiTooltipPhase phase(UiWindowId tooltip) const;

    void enter(UiWindowId target, const UiWindowSnapshot&, float x, float y);
    void move(float x, float y);
    void leave();
    void down();
    void advance(float dt, const UiWindowSnapshot&, float x, float y);

    // UiWindowLifecycle hooks. reset_target runs before release_owned during
    // Window::destroy, matching the original effective-tooltip ordering.
    void reset_target(UiWindowId);
    void release_owned(UiWindowId);
    void shutdown();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace torchlight
