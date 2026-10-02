#include "torchlight/inventory.hpp"
#include <iostream>
using namespace torchlight;
namespace {
InventoryItem potion(std::uint32_t count, std::uint32_t maximum, std::int64_t guid) {
    InventoryItem item; item.resource_guid = guid;
    ConsumableItem definition; definition.count = count; definition.maximum_stack = maximum;
    definition.unavailable_reason = "raw selector fixture"; item.consumable = definition;
    return item;
}
}
int main() {
    std::uint32_t count, maximum, size;
    while (std::cin >> count >> maximum >> size) {
        if (!count || count > maximum || maximum > 100000 || size > 64) return 2;
        std::vector<InventoryItem> items;
        for (std::uint32_t i = 0; i < size; ++i) {
            std::uint32_t existing; std::int64_t guid;
            if (!(std::cin >> existing >> guid) || !existing || existing > maximum) return 2;
            items.push_back(potion(existing, maximum, guid));
        }
        const auto result = inventory_pickup_stack(items, potion(count, maximum, 9));
        std::cout << result.value_or(size) << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}
