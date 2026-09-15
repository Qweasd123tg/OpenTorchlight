#pragma once
#include "torchlight/frontend.hpp"
#include <memory>
namespace torchlight {
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
