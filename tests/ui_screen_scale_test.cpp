#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
// P1 differential test for CGameUI::convertToScreenScale @0xa83ed0
// (scaledX @0xa83ea0, scaledY @0xa83e70).
//
// Expected numbers are the output of the executed original instructions on the
// pinned ELF (SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88
// b5d41724b), re-run 2026-09-17 and stored at
// research/ui-scale-p1/original-ui-probes.rerun-2026-09-17.json: 400
// three-node trees, 1200 nodes / 9600 float fields bit-exact, children before
// parents, 390 -> 548.4375 at 1920x1080, repeat application -> 771.240234375.
// This test compares the port converter against those recorded literals, not
// against a second copy of its own formula.
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value)
        throw std::runtime_error(message);
}
UiLayout parse_xml(const std::string &text) {
    return UiLayout::parse(std::vector<std::uint8_t>(text.begin(), text.end()));
}
const UiResolvedWidget &named(const std::vector<UiResolvedWidget> &widgets, const char *name) {
    for (const auto &w : widgets)
        if (w.name == name)
            return w;
    throw std::runtime_error(std::string("widget missing: ") + name);
}
// Single-offset width widget: resolved width is exactly one float multiply,
// bit-comparable with the native probe literal f32(390 * ratio).
const char *kProbeLayout =
    "<GUILayout>"
    "<Window Name=\"Root\" Type=\"DefaultWindow\">"
    "<Property Name=\"UnifiedAreaRect\" Value=\"{{0,0},{0,0},{1,0},{1,0}}\"/>"
    "<Window Name=\"Probe\" Type=\"StaticImage\">"
    "<Property Name=\"UnifiedAreaRect\" Value=\"{{0,0},{0,0},{0,390},{0,28}}\"/>"
    "</Window>"
    "<Window Name=\"OffsetProbe\" Type=\"StaticImage\">"
    "<Property Name=\"UnifiedAreaRect\" Value=\"{{0,10},{0,20},{0,400},{0,48}}\"/>"
    "</Window>"
    "<Window Name=\"RoundProbe\" Type=\"StaticImage\">"
    "<Property Name=\"UnifiedAreaRect\" Value=\"{{0,-25.360240936279297},{0,0},{0,-2197.022705078125},{0,0}}\"/>"
    "</Window>"
    "</Window>"
    "</GUILayout>";
} // namespace
int main() {
    try {
        // Native YRATIO literals from the executed original (false branch).
        require(ui_screen_ratio(1024, 768, UiScreenScaleRatio::y_ratio) == 1.0F, "base ratio");
        require(ui_screen_ratio(1280, 720, UiScreenScaleRatio::y_ratio) == 0.9375F, "720p yratio");
        require(ui_screen_ratio(1920, 1080, UiScreenScaleRatio::y_ratio) == 1.40625F, "1080p yratio");
        require(ui_screen_ratio(2560, 1440, UiScreenScaleRatio::y_ratio) == 1.875F, "1440p yratio");
        require(ui_screen_ratio(1920, 1080, UiScreenScaleRatio::x_ratio) == 1.875F, "1080p xratio");
        require(ui_screen_ratio(1024, 768, UiScreenScaleRatio::x_ratio) == 1.0F, "base xratio");
        // Offsets scale, relative members survive.
        std::array<float, 8> area{0.5F, 10.0F, 0.25F, 20.0F, 0.5F, 400.0F, 0.25F, 48.0F};
        ui_scale_area_offsets(area, 1.40625F);
        require(area[0] == 0.5F && area[2] == 0.25F && area[4] == 0.5F && area[6] == 0.25F,
                "area scales preserved");
        require(area[1] == 14.0625F && area[5] == 562.5F, "area offsets scaled");
        std::array<float, 4> vec{0.0F, 100.0F, 1.0F, 50.0F};
        ui_scale_vector_offsets(vec, 1.40625F);
        require(vec[0] == 0.0F && vec[2] == 1.0F, "vector scales preserved");
        require(vec[1] == 140.625F && vec[3] == 70.3125F, "vector offsets scaled");
        // Layout-level comparison against native TopFrame literals (raw 390).
        const UiLayout layout = parse_xml(kProbeLayout);
        const auto check_viewport = [&](int w, int h, float native_width) {
            const float ratio = ui_screen_ratio(w, h, UiScreenScaleRatio::y_ratio);
            const auto resolved = layout.resolve(w, h, ratio);
            require(named(resolved, "Probe").rect.width == native_width, "native width mismatch");
        };
        check_viewport(1024, 768, 390.0F);
        check_viewport(1280, 720, 365.625F);
        check_viewport(1920, 1080, 548.4375F);
        check_viewport(2560, 1440, 731.25F);
        check_viewport(1023, 767, 389.4921875F);
        // Non-zero min offset at 1080p: (400 - 10) * 1.40625.
        const auto hd = layout.resolve(1920, 1080, 1.40625F);
        require(named(hd, "OffsetProbe").rect.width == 548.4375F, "offset-pair width mismatch");
        require(named(hd, "OffsetProbe").rect.x == 14.0625F, "offset-pair origin mismatch");
        // Rounding order (audit cross-check): the original scales the
        // getSize() difference, i.e. (max-min)*ratio with subss-then-mulss
        // (vendored Window::getSize @0x111bd0, live-verified), NOT
        // max*ratio-min*ratio. These differ by 1 ULP here.
        require(named(hd, "RoundProbe").rect.x == -35.662837982177734F, "round origin mismatch");
        require(named(hd, "RoundProbe").rect.width == -3053.900146484375F,
                "size must scale the offset difference");
        // Negative control: the legacy unscaled resolve keeps the old defect.
        const auto legacy = layout.resolve(1920, 1080);
        require(named(legacy, "Probe").rect.width == 390.0F, "legacy resolve changed");
        // No accumulation: re-resolving never feeds scaled values back.
        const auto again = layout.resolve(1920, 1080, 1.40625F);
        require(named(again, "Probe").rect.width == 548.4375F, "repeat resolve drifted");
        const auto base = layout.resolve(1024, 768, 1.0F);
        require(named(base, "Probe").rect.width == 390.0F, "resize back changed pristine");
        // Confirmed per-controller policy; unknown screens stay unscaled.
        require(ui_screen_scale_for_layout("media/UI/bottomhud.layout") ==
                    UiScreenScaleRatio::y_ratio,
                "bottomhud policy lost");
        require(ui_screen_scale_for_layout("media/UI/inventorymenu.layout") ==
                    UiScreenScaleRatio::y_ratio,
                "inventory policy lost");
        // Controller menus, verified per-menu in the shipped ELF (xor edx +
        // call convertToScreenScale in each createMenus, all false/YRATIO).
        for (const char *menu : {"media/UI/mainmenuframe.layout", "media/UI/charactercreate.layout",
                                 "media/UI/characterload.layout", "media/UI/optionsmenu.layout",
                                 "media/UI/settingsmenu.layout"}) {
            if (ui_screen_scale_for_layout(menu) != UiScreenScaleRatio::y_ratio)
                throw std::runtime_error(std::string("menu policy lost: ") + menu);
            ++checks;
        }
        require(!ui_screen_scale_for_layout("media/UI/mainmenu.layout").has_value(),
                "unknown screen invented a policy");
        require(!ui_screen_scale_for_layout("media/UI/characterselect.layout").has_value(),
                "unknown screen invented a policy");
        // UnifiedPosition/UnifiedSize path scales too.
        const UiLayout moved = parse_xml(
            "<GUILayout><Window Name=\"Solo\" Type=\"StaticImage\">"
            "<Property Name=\"UnifiedPosition\" Value=\"{{0,100},{0,50}}\"/>"
            "<Property Name=\"UnifiedSize\" Value=\"{{0,390},{0,28}}\"/>"
            "</Window></GUILayout>");
        const auto placed = moved.resolve(1920, 1080, 1.40625F);
        require(named(placed, "Solo").rect.x == 140.625F, "position offset unscaled");
        require(named(placed, "Solo").rect.width == 548.4375F, "size offset unscaled");
        bool threw = false;
        try {
            (void)layout.resolve(1920, 1080, 0.0F);
        } catch (const std::invalid_argument &) {
            threw = true;
        }
        require(threw, "zero ratio accepted");
        threw = false;
        try {
            (void)ui_screen_ratio(0, 768, UiScreenScaleRatio::y_ratio);
        } catch (const std::invalid_argument &) {
            threw = true;
        }
        require(threw, "zero viewport accepted");
        std::cout << "ui_screen_scale: " << checks
                  << " assertions; original-code CGameUI::convertToScreenScale, no "
                     "full-CEGUI geometry parity claim\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
