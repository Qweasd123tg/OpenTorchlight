#pragma once
#include "torchlight/frontend.hpp"
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
    void draw(const FrontendFrame &, int width, int height);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
