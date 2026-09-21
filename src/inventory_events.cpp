#include "torchlight/inventory_events.hpp"

namespace torchlight {
void map_inventory_events(InventoryEventTree& tree, InventoryEventTree::Node root) {
    const auto count = tree.child_count(root);
    for (std::size_t i = 0; i < count; ++i)
        map_inventory_events(tree, tree.child(root, i));
    try {
        // One read; any nonempty value subscribes, including unknown or NUL.
        // Repeated mappings append subscriptions: no original deduplication.
        if (tree.has_click_property(root) && !tree.click_property(root).empty())
            tree.subscribe_mouse_down(root);
    } catch (...) {
        // b4f523..b4f530: swallow local failures; traversal is outside the try.
    }
}

bool dispatch_inventory_tab(bool open, int function, InventoryTabSink& sink) {
    if (!open || function < 14 || function > 16) return false;
    const auto selected = static_cast<std::size_t>(function - 14);
    for (std::size_t i = 0; i < 3; ++i) sink.select(i, i == selected);
    for (std::size_t i = 0; i < 3; ++i) sink.show(i, i == selected);
    sink.clear_alert(selected);
    sink.restore_unselected_image(selected);
    sink.update_layout();
    return true;
}
} // namespace torchlight
