#include "torchlight/inventory_view.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace torchlight {
namespace {
std::string display_name(const InventoryItem& item) {
    std::string result;
    const auto& text = item.display_name.empty() ? item.name : item.display_name;
    for (const auto c : text) result += c >= 32 && c <= 126 ? static_cast<char>(c) : '?';
    return result.empty() ? "UNNAMED ITEM" : result;
}
}
void InventoryView::move(int direction, const PlayerInventory& inventory) noexcept {
    const auto size = inventory.items().size();
    if (size == 0) { selected_ = 0; return; }
    selected_ = std::min(selected_, size - 1);
    if (direction < 0 && selected_ > 0) --selected_;
    if (direction > 0 && selected_ < size - 1) ++selected_;
}
InventoryId InventoryView::selected_id(const PlayerInventory& inventory) const noexcept {
    if (inventory.items().empty()) return 0;
    return inventory.items()[std::min(selected_, inventory.items().size() - 1)].id;
}
std::vector<InventoryViewLine> InventoryView::lines(const PlayerSession& session,
                                                 std::size_t visible_items) const {
    const auto& inventory = session.inventory();
    std::vector<InventoryViewLine> result;
    std::ostringstream stats;
    stats << "HP " << std::fixed << std::setprecision(0) << session.health().health()
          << '/' << session.health().maximum_health() << "  ARMOR "
          << session.health().armor_class() << "  DAMAGE " << session.combat().minimum_damage()
          << '-' << session.combat().maximum_damage() << "  ITEMS " << inventory.items().size();
    stats << "  GOLD " << session.gold();
    if (session.health().mana()) stats << "  MANA " << *session.health().mana()
        << '/' << *session.health().maximum_mana();
    else stats << "  MANA ?";
    result.push_back({stats.str(), false});
    result.push_back({"INVENTORY - PAUSED", false});
    result.push_back({"UP/DOWN SELECT | ENTER EQUIP | U UNEQUIP | I/ESC CLOSE", false});
    if (inventory.items().empty()) result.push_back({"BAG IS EMPTY. PICK UP EQUIPMENT IN THE WORLD.", false});
    const auto selected = inventory.items().empty() ? 0 : std::min(selected_, inventory.items().size() - 1);
    visible_items = std::max<std::size_t>(1, visible_items);
    const auto first = selected >= visible_items ? selected - visible_items + 1 : 0;
    for (auto i = first; i < inventory.items().size() && i - first < visible_items; ++i) {
        const auto& item = inventory.items()[i];
        const auto slot = inventory.equipped_slot(item.id);
        const auto supported_slot = PlayerInventory::slot_for(item);
        std::ostringstream row;
        row << (i == selected ? "> " : "  ") << '#' << item.id << ' '
            << (slot ? "[ON] " : "[BAG] ") << display_name(item).substr(0, 28) << "  "
            << (supported_slot ? inventory_slot_name(*supported_slot) : "VIEW ONLY");
        result.push_back({row.str(), i == selected});
    }
    if (const auto* item = inventory.find(selected_id(inventory))) {
        std::ostringstream detail;
        if (item->weapon) {
            const auto& w = *item->weapon;
            detail << "STORED DAMAGE " << w.minimum_damage << '-' << w.maximum_damage
                   << "  SPEED " << w.prototype.speed << "  RANGE " << w.prototype.range;
            if (item->two_handed) detail << "  TWO HANDS";
        } else if (item->armor) detail << "STORED ARMOR " << item->armor->armor;
        else detail << "ITEM RETAINED. ITS USE/EFFECTS ARE NOT IMPLEMENTED.";
        result.push_back({detail.str(), false});
    }
    if (!status.empty()) result.push_back({status, false});
    result.push_back({"REPLACED GEAR STAYS IN THE BAG. ESC CLOSES; ESC AGAIN OPENS SAVE MENU.", false});
    return result;
}
const char* inventory_change_message(InventoryChange change) noexcept {
    switch (change) {
    case InventoryChange::changed: return "EQUIPMENT UPDATED. PREVIOUS ITEM KEPT.";
    case InventoryChange::unchanged: return "NO CHANGE.";
    case InventoryChange::not_found: return "NO ITEM SELECTED.";
    case InventoryChange::unsupported: return "THIS ITEM'S SLOT OR EFFECT IS NOT IMPLEMENTED.";
    case InventoryChange::busy: return "ATTACK IN PROGRESS. CLOSE INVENTORY AND LET IT FINISH.";
    case InventoryChange::dead: return "PLAYER IS DEAD.";
    }
    return "UNKNOWN INVENTORY RESULT.";
}
std::array<unsigned char, 7> inventory_glyph(char c) noexcept {
    if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
    switch (c) {
    case 'A': return {14,17,17,31,17,17,17}; case 'B': return {30,17,17,30,17,17,30};
    case 'C': return {14,17,16,16,16,17,14}; case 'D': return {30,17,17,17,17,17,30};
    case 'E': return {31,16,16,30,16,16,31}; case 'F': return {31,16,16,30,16,16,16};
    case 'G': return {14,17,16,23,17,17,15}; case 'H': return {17,17,17,31,17,17,17};
    case 'I': return {14,4,4,4,4,4,14}; case 'J': return {7,2,2,2,2,18,12};
    case 'K': return {17,18,20,24,20,18,17}; case 'L': return {16,16,16,16,16,16,31};
    case 'M': return {17,27,21,21,17,17,17}; case 'N': return {17,25,21,19,17,17,17};
    case 'O': return {14,17,17,17,17,17,14}; case 'P': return {30,17,17,30,16,16,16};
    case 'Q': return {14,17,17,17,21,18,13}; case 'R': return {30,17,17,30,20,18,17};
    case 'S': return {15,16,16,14,1,1,30}; case 'T': return {31,4,4,4,4,4,4};
    case 'U': return {17,17,17,17,17,17,14}; case 'V': return {17,17,17,17,17,10,4};
    case 'W': return {17,17,17,21,21,21,10}; case 'X': return {17,17,10,4,10,17,17};
    case 'Y': return {17,17,10,4,4,4,4}; case 'Z': return {31,1,2,4,8,16,31};
    case '0': return {14,17,19,21,25,17,14}; case '1': return {4,12,4,4,4,4,14};
    case '2': return {14,17,1,2,4,8,31}; case '3': return {30,1,1,14,1,1,30};
    case '4': return {2,6,10,18,31,2,2}; case '5': return {31,16,16,30,1,1,30};
    case '6': return {14,16,16,30,17,17,14}; case '7': return {31,1,2,4,8,8,8};
    case '8': return {14,17,17,14,17,17,14}; case '9': return {14,17,17,15,1,1,14};
    case ' ': return {}; case '-': return {0,0,0,31,0,0,0};
    case '_': return {0,0,0,0,0,0,31}; case '.': return {0,0,0,0,0,12,12};
    case ':': return {0,12,12,0,12,12,0}; case '/': return {1,2,2,4,8,8,16};
    case '[': return {14,8,8,8,8,8,14}; case ']': return {14,2,2,2,2,2,14};
    case '>': return {0,16,8,4,8,16,0}; case '|': return {4,4,4,4,4,4,4};
    case '#': return {10,10,31,10,31,10,10}; case '\'': return {4,4,0,0,0,0,0};
    case '=': return {0,0,31,0,31,0,0}; case '+': return {0,4,4,31,4,4,0};
    default: return {14,17,1,2,4,0,4};
    }
}
} // namespace torchlight
