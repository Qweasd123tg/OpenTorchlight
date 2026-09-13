#include "torchlight/key_manager.hpp"

namespace torchlight {

void KeyManager::key_event(std::uint32_t message, std::uint32_t key, bool caps_key_down) noexcept {
    if (key < key_count) {
        if (message == key_down || message == system_key_down) {
            if (!pending_held_[key]) {
                pending_pressed_[key] = 1;
            }
            pending_held_[key] = 1;
        } else if (message == key_up || message == system_key_up) {
            if (pending_held_[key]) {
                pending_released_[key] = 1;
            }
            pending_held_[key] = 0;
        }
    }
    // The original polls SDL even for messages it does not otherwise handle.
    caps_key_down_ = caps_key_down;
}

void KeyManager::capture() noexcept {
    pressed_ = pending_pressed_;
    released_ = pending_released_;
    held_ = pending_held_;
    flush();
}

void KeyManager::flush() noexcept {
    pending_pressed_.fill(0);
    pending_released_.fill(0);
}

void KeyManager::flush_all() noexcept {
    pending_held_.fill(0);
    flush();
    // Published frame state remains unchanged until capture(), as in the game.
}

bool KeyManager::key_pressed(std::uint32_t key) const noexcept {
    return key < key_count && pressed_[key] == 1;
}

bool KeyManager::key_held(std::uint32_t key) const noexcept {
    // A press and release between captures still counts as held for one frame.
    return key < key_count && (held_[key] == 1 || pressed_[key] == 1);
}

bool KeyManager::key_released(std::uint32_t key) const noexcept {
    return key < key_count && released_[key] == 1;
}

} // namespace torchlight
