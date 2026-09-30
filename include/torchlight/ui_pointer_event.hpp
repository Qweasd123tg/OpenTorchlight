#pragma once
#include <cstdint>
#include <optional>
#include <string>

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
// Backend transport: physical key values use application_keys/Linux evdev;
// text is committed UTF-8 supplied by the host layout/compose implementation.
// Native CEGUI owns editing, validation, selection, caret and text limits.
enum class UiKeyboardEventKind { key_down, key_up, text, leave };
struct UiKeyboardEvent {
    UiKeyboardEventKind kind = UiKeyboardEventKind::key_down;
    std::uint32_t key = 0;
    std::string text;
    std::optional<double> time_seconds = std::nullopt;
};
} // namespace torchlight
