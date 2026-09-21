#pragma once
#include "torchlight/frontend.hpp"
#include "torchlight/ui_hud.hpp"
#include <memory>
namespace torchlight {
// Existing diagnostic inventory/HUD overlay, shared by window and headless runs.
void draw_inventory_overlay(const std::vector<InventoryViewLine>& lines,
                            bool inventory_open, int width, int height);
class GlesUiRenderer {
  public:
    GlesUiRenderer(const PakArchive &, UiResources &);
    ~GlesUiRenderer();
    GlesUiRenderer(const GlesUiRenderer &) = delete;
    GlesUiRenderer &operator=(const GlesUiRenderer &) = delete;
    void draw(const FrontendFrame &, int width, int height, bool clear_background = true);
    // Resource-derived HUD images and bars plus CEGUI-compatible font text.
    void draw_hud(const UiHudFrame &, int width, int height);
    // Same overlay content as draw_inventory_overlay, with font text when a
    // resource font is available. The box geometry remains prototype.
    void draw_overlay(const std::vector<InventoryViewLine> &lines, bool inventory_open,
                      int width, int height);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
