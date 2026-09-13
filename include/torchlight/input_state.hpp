#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace torchlight {

// Explicit widths preserve the inspected Linux LP64 build on Android ARM64.
struct Point {
    std::int64_t x = 0;
    std::int64_t y = 0;
};

// Recovered legacy state only. Touch routing and game commands are separate.
// Calls are serialized by the input loop; this class is not thread-safe.
class InputState {
public:
    static constexpr std::size_t key_count = 256;

    void update_cursor_position(std::int64_t x, std::int64_t y) noexcept;
    [[nodiscard]] int get_cursor_position(Point& point) const noexcept;
    [[nodiscard]] int set_cursor_position(std::int32_t x, std::int32_t y) noexcept;

    // Original behavior is defined here for 0..255. Out-of-range keys are
    // rejected, rather than reproducing the original unchecked memory access.
    [[nodiscard]] bool update_key_state(std::uint32_t key, bool down) noexcept;
    [[nodiscard]] std::int16_t get_key_state(std::uint32_t key) const noexcept;
    [[nodiscard]] std::int16_t get_async_key_state(std::uint32_t key) const noexcept;
    void clear_key_state() noexcept;

private:
    std::array<std::uint8_t, key_count> keys_{};
    Point cursor_{};
};

} // namespace torchlight
