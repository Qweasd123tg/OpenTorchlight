#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace torchlight {

// State transitions recovered from CKeyManager. The platform adapter supplies
// messages and the physical Caps Lock key state; no SDL ABI is assumed here.
class KeyManager {
public:
    static constexpr std::size_t key_count = 512;
    static constexpr std::uint32_t key_down = 0x100;
    static constexpr std::uint32_t key_up = 0x101;
    static constexpr std::uint32_t system_key_down = 0x104;
    static constexpr std::uint32_t system_key_up = 0x105;

    void key_event(std::uint32_t message, std::uint32_t key, bool caps_key_down) noexcept;
    void capture() noexcept;
    void flush() noexcept;
    void flush_all() noexcept;

    [[nodiscard]] bool key_pressed(std::uint32_t key) const noexcept;
    [[nodiscard]] bool key_held(std::uint32_t key) const noexcept;
    [[nodiscard]] bool key_released(std::uint32_t key) const noexcept;
    [[nodiscard]] bool caps_key_down() const noexcept { return caps_key_down_; }

private:
    using Keys = std::array<std::uint8_t, key_count>;
    Keys pressed_{};
    Keys held_{};
    Keys released_{};
    Keys pending_pressed_{};
    Keys pending_held_{};
    Keys pending_released_{};
    bool caps_key_down_ = false;
};

} // namespace torchlight
