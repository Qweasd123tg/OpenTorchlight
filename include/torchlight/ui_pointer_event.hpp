#pragma once
#include <cstdint>
#include <optional>

namespace torchlight {
// Host transport for ordered physical events. CEGUI dispatch/class effects
// belong to the window runtime, not to the platform callback.
enum class UiPointerEventKind { move, leave, button_down, button_up };
struct UiPointerEvent {
    UiPointerEventKind kind = UiPointerEventKind::move;
    float x = 0, y = 0;
    std::uint8_t button = 0; // CEGUI left=0, right=1, middle=2
    std::optional<double> time_seconds = std::nullopt;
};
} // namespace torchlight
