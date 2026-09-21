#pragma once
#include <cstddef>
#include <string>

namespace torchlight {
// original-code: CInventoryMenu::mapEventHandlers @0xb4f1b0.
// This is the inventory catch-all contract, NOT CGameUI's Ogre-only catch.
class InventoryEventTree {
public:
    using Node = std::size_t;
    virtual ~InventoryEventTree() = default;
    virtual std::size_t child_count(Node) const = 0;
    virtual Node child(Node, std::size_t) const = 0;
    virtual bool has_click_property(Node) const = 0;
    virtual std::string click_property(Node) const = 0;
    virtual void subscribe_mouse_down(Node) = 0;
};
void map_inventory_events(InventoryEventTree&, InventoryEventTree::Node);

// original-code: onClick @0xb4f570, callbacks stand at the CEGUI boundary.
// update_layout is the call boundary, not a claim that updateLayout is ported.
class InventoryTabSink {
public:
    virtual ~InventoryTabSink() = default;
    virtual void select(std::size_t, bool) = 0;
    virtual void show(std::size_t, bool) = 0;
    virtual void clear_alert(std::size_t) = 0;
    virtual void restore_unselected_image(std::size_t) = 0;
    virtual void update_layout() = 0;
};
// Returns whether a tab branch ran; original event handled result is always 1.
// Exceptions propagate (original onClick only cleans up, unlike the mapper).
bool dispatch_inventory_tab(bool open, int function, InventoryTabSink&);
} // namespace torchlight
