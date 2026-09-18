// original-code: CEGUI::Image render offsets (XOffset/YOffset) with
// per-imageset autoscale (upstream v0-6-2 CEGUIImageset.cpp/CEGUIImage.cpp,
// vendored alignment CEGUI::Image::setHorzScaling @0xe59e0 in the shipped
// libCEGUIBase.so.1). Research: research/ui-imageset-offsets.md.
// Expected values are hand-computed from the shipped hud.imageset /
// WindowsLook.imageset bytes through the original formulas, not from a
// second copy of the port code.
#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_layout.hpp"
#include <cmath>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <string>
namespace {
unsigned checks = 0;
void require(bool b, const char* what) {
    ++checks;
    if (!b)
        throw std::runtime_error(what);
}
void require_same(float actual, float expected, const char* what) {
    ++checks;
    if (actual != expected)
        throw std::runtime_error(what);
}
} // namespace
int main(int argc, char** argv) {
    try {
        // Pure alignment unit first (vendored round-half-away-from-zero).
        require_same(torchlight::pixel_align_ui(7.5F), 8.0F, "align +7.5");
        require_same(torchlight::pixel_align_ui(2.5F), 3.0F, "align +2.5");
        require_same(torchlight::pixel_align_ui(0.49F), 0.0F, "align +0.49");
        require_same(torchlight::pixel_align_ui(-9.375F), -9.0F, "align -9.375");
        require_same(torchlight::pixel_align_ui(-8.0F), -8.0F, "align -8");
        require_same(torchlight::pixel_align_ui(-2.5F), -3.0F, "align -2.5");
        require_same(torchlight::pixel_align_ui(-0.49F), -0.0F, "align -0.49");
        require_same(torchlight::pixel_align_ui(std::numeric_limits<float>::quiet_NaN()),
                     -2147483648.0F, "align NaN");
        require_same(torchlight::pixel_align_ui(std::numeric_limits<float>::infinity()),
                     -2147483648.0F, "align inf");
        if (argc != 3 || std::string(argv[1]) != "--original")
            throw std::runtime_error("usage: ui_imageset_test --original /path/to/pak.zip");
        const torchlight::PakArchive archive(argv[2]);
        torchlight::UiResources resources(archive);
        const auto lookup = [&](const char* reference) {
            const auto image = resources.image(reference);
            if (!image)
                throw std::runtime_error(std::string("image missing: ") + reference);
            return *image;
        };
        const auto left = lookup("set:GuiLook image:WindowLeftEdge");
        require(left.offset_x == 4.0F && left.offset_y == 0.0F, "hud left edge offsets");
        require(left.native_horz == 1024.0F && left.native_vert == 768.0F, "hud native res");
        require(left.auto_scaled, "hud autoscale flag");
        const auto brush = lookup("set:GuiLook image:ClientBrush");
        require(brush.offset_x == 0.0F && brush.offset_y == 0.0F, "brush offsets default");
        const auto target = lookup("set:GuiLook image:MouseTarget");
        require(target.offset_x == -8.0F && target.offset_y == -8.0F, "cursor offsets");
        const auto cursor = lookup("set:WindowsLook image:MouseMoveCursor");
        require(!cursor.auto_scaled, "windowslook autoscale flag");
        require(cursor.offset_x == -10.0F && cursor.offset_y == -10.0F, "cursor offsets 2");
        const auto shift = [&](const torchlight::UiImage& image, float w, float h) {
            return torchlight::ui_image_render_offset(image, w, h);
        };
        // 4 * 1024/1024 = 4; 4 * 1920/1024 = 7.5 -> 8.
        require_same(shift(left, 1024, 768)[0], 4.0F, "left edge dx native");
        require_same(shift(left, 1024, 768)[1], 0.0F, "left edge dy native");
        require_same(shift(left, 1920, 1080)[0], 8.0F, "left edge dx 1080p");
        require_same(shift(left, 1920, 1080)[1], 0.0F, "left edge dy 1080p");
        // -8 at factor 1 -> -8; -5 * 1.875 = -9.375 -> -9.
        require_same(shift(target, 1024, 768)[0], -8.0F, "cursor dx native");
        require_same(shift(target, 1024, 768)[1], -8.0F, "cursor dy native");
        const auto right = lookup("set:GuiLook image:WindowRightEdge");
        require_same(shift(right, 1920, 1080)[0], -9.0F, "right edge dx 1080p");
        // Non-autoscaled: raw offsets at any resolution.
        require_same(shift(cursor, 1920, 1080)[0], -10.0F, "fixed dx 1080p");
        require_same(shift(cursor, 1920, 1080)[1], -10.0F, "fixed dy 1080p");
        // Zero offsets stay zero through alignment at any resolution.
        require_same(shift(brush, 1920, 1080)[0], 0.0F, "brush dx 1080p");
        require_same(shift(brush, 1920, 1080)[1], 0.0F, "brush dy 1080p");
        std::printf("PASS: %u imageset offset/scale checks on real pak data\n", checks);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
