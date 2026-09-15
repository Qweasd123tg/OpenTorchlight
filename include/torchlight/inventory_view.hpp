#pragma once
#include "torchlight/player_session.hpp"
#include <array>
#include <string>
#include <vector>

namespace torchlight {
struct InventoryViewLine { std::string text; bool selected = false; };
// Minimal desktop UI, not a recreation of CInventoryMenu. Uses session instance
// IDs and stored rolls. Keyboard navigation is independent of Wayland/GL.
class InventoryView {
public:
    bool open = false;
    std::string status;
    void move(int direction, const PlayerInventory& inventory) noexcept;
    [[nodiscard]] InventoryId selected_id(const PlayerInventory& inventory) const noexcept;
    [[nodiscard]] std::vector<InventoryViewLine> lines(const PlayerSession& session,
                                                      std::size_t visible_items = 12) const;
private:
    std::size_t selected_ = 0;
};
[[nodiscard]] const char* inventory_change_message(InventoryChange change) noexcept;
// Original small bitmap glyphs for an ASCII diagnostic overlay; no game fonts.
[[nodiscard]] std::array<unsigned char, 7> inventory_glyph(char character) noexcept;
} // namespace torchlight
