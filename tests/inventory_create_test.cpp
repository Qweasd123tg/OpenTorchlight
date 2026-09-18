// Differential/state tests for the portable createMenus pure logic.
// original-code: createMenus @0xb569e0, GetValueAsString @0xc91f60,
// uniqueName @0xc8ea50. Layout cross-check: media/UI/inventorymenu.layout
// (Slot1..Slot63) from pak.zip.
#include "torchlight/inventory_create.hpp"

#include <cstdio>
#include <string>
#include <vector>

namespace {
int failures = 0;
int assertions = 0;
void require(bool cond, const char* what) {
    ++assertions;
    if (!cond) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}
} // namespace

int main() {
    using namespace torchlight;

    // GetValueAsString == plain decimal (differential vs snprintf).
    for (unsigned v : {0u, 1u, 9u, 10u, 18u, 63u, 100u, 4294967295u}) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%u", v);
        require(original_uint_to_string(v) == buf, "decimal matches snprintf");
    }

    // Slot loop: 63 keys "Slot1".."Slot63".
    auto wirings = inventory_all_slot_wirings();
    require(wirings.size() == 63, "63 slot wirings");
    require(wirings.front().key == "Slot1", "first key Slot1");
    require(wirings.back().key == "Slot63", "last key Slot63");
    for (const auto& w : wirings) {
        require(w.key == "Slot" + std::to_string(w.counter), "key format");
        require(w.back_index == w.counter + 0x12, "back index = i + 0x12");
        require(w.slot_array_index == w.counter - 1, "array index = i - 1");
    }
    require(wirings.front().back_index == 19, "first back index 19");
    require(wirings.back().back_index == 81, "last back index 81");

    // Table loop bound.
    require(kInventoryTableLoopCount == 12, "table loop runs 12");

    // Static grabs: spot-check field targets from machine code.
    for (const auto& g : inventory_static_grabs()) {
        if (std::string(g.key) == "TopFrame")
            require(g.menu_field == 0x28, "TopFrame -> +0x28");
        if (std::string(g.key) == "BottomFrame")
            require(g.menu_field == 0x48, "BottomFrame -> +0x48");
        if (std::string(g.key) == "SlotGlow")
            require(g.menu_field == 0x1d00, "SlotGlow -> +0x1d00");
    }
    require(inventory_static_grabs().size() == 13, "13 static grabs");

    // Slot containers.
    require(inventory_slot_containers().size() == 3, "3 slot containers");
    require(inventory_slot_containers()[0].menu_field == 0x9108,
            "SlotsEquipment -> +0x9108");

    // Subscription table: handler ids are the original code addresses.
    auto handlers = inventory_slot_handlers();
    require(handlers.size() == 2, "two slot handlers");
    require(handlers[0] == InventorySlotHandler::item_click, "ItemClick first");
    require(static_cast<std::uint32_t>(handlers[0]) == 0xb45810,
            "ItemClick id = handle_ItemClick");
    require(static_cast<std::uint32_t>(handlers[1]) == 0xb4d590,
            "MouseOver id = handle_MouseOver");

    // uniqueName: prefix + '_' + decimal(++counter).
    UniqueNameState names;
    require(names.make("gui_") == "gui__1", "first unique name");
    require(names.make("gui_") == "gui__2", "counter increments");
    require(names.counter() == 2, "counter observable");
    UniqueNameState resumed(288);
    require(resumed.make("gui_") == "gui__289", "resumable counter");

    if (failures == 0)
        std::printf("inventory_create: %d assertions; slot keys/indices, "
                    "grabs, handlers, unique names\n",
                    assertions);
    return failures == 0 ? 0 : 1;
}
