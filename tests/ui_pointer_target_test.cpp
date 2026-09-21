#include "torchlight/ui_dropdown.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string_view>

using namespace torchlight;
namespace {
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
UiLayout tree(std::string_view children, std::string_view root_properties = {}) {
    const auto xml = std::string("<GUILayout><Window Name='root'>") +
        "<Property Name='MousePassThroughEnabled' Value='True'/>" +
        std::string(root_properties) + std::string(children) + "</Window></GUILayout>";
    return UiLayout::parse({xml.begin(), xml.end()});
}
std::string name(const std::vector<UiResolvedWidget>& widgets, std::optional<std::size_t> index) {
    return index ? widgets.at(*index).name : "";
}
void target(const UiLayout& layout, const char* expected, float x = 50, float y = 50) {
    const auto widgets = layout.resolve(100, 100);
    require(name(widgets, ui_target_at_position(widgets, x, y)) == expected,
            "topmost resource window differs");
}
void receiver(const UiLayout& layout, const char* expected) {
    const auto widgets = layout.resolve(100, 100);
    require(name(widgets, dropdown_mouse_down_receiver(
        widgets, dropdown_subscriptions(layout), 50, 50)) == expected,
        "MouseButtonDown subscription route differs");
}
void contracts() {
    // Values are geometry / subscription queries; no event injection or renderer.
    const auto siblings = tree("<Window Name='a'/><Window Name='b'/>");
    target(siblings, "b");
    target(tree("<Window Name='a'><Property Name='AlwaysOnTop' Value='True'/></Window>"
                "<Window Name='b'/>"), "a");
    target(tree("<Window Name='a'><Property Name='AlwaysOnTop' Value='True'/></Window>"
                "<Window Name='b'><Property Name='AlwaysOnTop' Value='True'/></Window>"), "b");
    target(tree("<Window Name='a'><Window Name='nested'>"
                "<Property Name='AlwaysOnTop' Value='True'/></Window></Window>"
                "<Window Name='b'/>"), "b");
    target(tree("<Window Name='a'><Window Name='nested'/></Window>"), "nested");

    const auto blocked = tree(
        "<Window Name='button'><Property Name='onClick' Value='guiNewGameMenu'/></Window>"
        "<Window Name='overlay'/>");
    target(blocked, "overlay");
    receiver(blocked, ""); // Unsubscribed overlay blocks its lower sibling.
    const auto passing = tree(
        "<Window Name='button'><Property Name='onClick' Value='guiNewGameMenu'/></Window>"
        "<Window Name='overlay'><Property Name='MousePassThroughEnabled' Value='True'/>"
        "<Property Name='onClick' Value='guiExitApplication'/></Window>");
    target(passing, "button");
    receiver(passing, "button"); // Pass-through also applies to subscribed windows.
    target(tree("<Window Name='parent'><Property Name='MousePassThroughEnabled' Value='True'/>"
                "<Window Name='child'/></Window>"), "child");
    const auto ancestor = tree(
        "<Window Name='parent'><Property Name='onClick' Value='guiNewGameMenu'/>"
        "<Property Name='MousePassThroughEnabled' Value='True'/>"
        "<Window Name='child'/></Window>");
    target(ancestor, "child");
    receiver(ancestor, "parent");
    receiver(tree("<Window Name='parent'><Property Name='onClick' Value='guiNewGameMenu'/>"
                  "<Window Name='child'><Property Name='onClick' Value='guiExitApplication'/>"
                  "</Window></Window>"), "child");
    receiver(tree("<Window Name='a'><Property Name='onClick' Value='guiSelectB'/></Window>"
                  "<Window Name='b'><Property Name='onClick' Value='guiSelectB'/></Window>"), "b");
    receiver(tree("<Window Name='a'><Property Name='onClick' Value='guiNewGameMenu'/></Window>"
                  "<Window Name='unknown'><Property Name='onClick' Value='unmapped-command'/>"
                  "</Window>"), "unknown");

    for (const auto* property : {"Visible' Value='False", "Disabled' Value='True"}) {
        const auto xml = std::string("<Window Name='bottom'/><Window Name='parent'>") +
            "<Property Name='" + property + "'/><Window Name='child'/></Window>";
        target(tree(xml), "bottom");
    }
    target(tree("<Window Name='transparent'><Property Name='Alpha' Value='0'/></Window>"),
           "transparent"); // isHit does not inspect alpha.
    const auto outside = [](bool clipped) {
        return tree(std::string("<Window Name='parent'>") +
            "<Property Name='UnifiedSize' Value='{{0,20},{0,20}}'/>"
            "<Window Name='outside'><Property Name='UnifiedPosition' Value='{{0,30},{0,30}}'/>"
            "<Property Name='UnifiedSize' Value='{{0,20},{0,20}}'/>" +
            (clipped ? "" : "<Property Name='ClippedByParent' Value='False'/>") +
            "</Window></Window>");
    };
    target(outside(true), "", 35, 35);
    target(outside(false), "outside", 35, 35);
    target(siblings, "b", 0, 0);
    target(siblings, "", 100, 50);
    target(siblings, "", 50, 100);
    target(siblings, "", -1, 50);
    target(tree("<Window Name='zero'><Property Name='UnifiedSize' Value='{{0,0},{0,10}}'/>"
                "</Window>"), "", 0, 0);
    require(!ui_target_at_position({}, 0, 0), "empty target tree");

    // Port-native validation of malformed API inputs, not a CEGUI claim.
    auto widgets = siblings.resolve(100, 100);
    bool rejected = false;
    try { (void)dropdown_mouse_down_receiver(widgets, {}, 50, 50); }
    catch (const std::invalid_argument&) { rejected = true; }
    require(rejected, "mismatched subscription tree accepted");
    widgets.back().parent = static_cast<std::int32_t>(widgets.size() - 1);
    rejected = false;
    try { (void)dropdown_mouse_down_receiver(widgets, dropdown_subscriptions(siblings), 50, 50); }
    catch (const std::invalid_argument&) { rejected = true; }
    require(rejected, "cyclic unsubscribed parent chain accepted");
}
void resources(const char* path) {
    PakArchive pak(path);
    UiResources resources(pak);
    const auto* layout = resources.layout("media/UI/mainmenuframe.layout");
    require(layout != nullptr, "missing original main menu");
    const auto subscriptions = dropdown_subscriptions(*layout);
    for (const auto size : {std::pair{1024, 768}, std::pair{1920, 1080}}) {
        UiLayoutState state;
        state.screen_scale = UiScreenScale::height;
        state.visibility = {{"DemoVersion", false}, {"CharacterModsWarning", false},
                            {"ContinueLast", true}, {"CreditFrame", false}, {"CreditFrameB", false}};
        auto widgets = layout->resolve(size.first, size.second, state);
        for (const auto* control : {"NewGame", "ContinueGame", "ContinueLast", "Settings",
                                    "ExitGame", "TabA", "TabB"}) {
            const auto it = std::find_if(widgets.begin(), widgets.end(), [&](const auto& w) {
                return w.name == control;
            });
            require(it != widgets.end(), "missing original control");
            const auto x = it->rect.x + it->rect.width * 0.5F;
            const auto y = it->rect.y + it->rect.height * 0.5F;
            require(name(widgets, ui_target_at_position(widgets, x, y)) == control,
                    "original control obscured despite layout pass-through");
            require(name(widgets, dropdown_mouse_down_receiver(widgets, subscriptions, x, y)) == control,
                    "original control subscription not selected");
        }
        // Direct property overrides only: no controller click/state scenario.
        for (const auto* backing : {"CreditFrame", "CreditFrameB"}) {
            state.visibility["CreditFrame"] = false;
            state.visibility["CreditFrameB"] = false;
            state.visibility[backing] = true;
            widgets = layout->resolve(size.first, size.second, state);
            for (const auto point : {std::pair{1.0F, 1.0F},
                                    std::pair{size.first * 0.5F, size.second * 0.5F}}) {
                require(name(widgets, ui_target_at_position(widgets, point.first, point.second)) == backing,
                        "pass-through Credits child intercepted backing target");
                require(name(widgets, dropdown_mouse_down_receiver(
                    widgets, subscriptions, point.first, point.second)) == backing,
                    "credits backing subscription not selected");
            }
        }
    }
}
} // namespace
int main(int argc, char** argv) {
    try {
        require(argc == 1 || argc == 2, "usage: ui_pointer_target_test [external pak.zip]");
        contracts();
        if (argc == 2) resources(argv[1]);
        std::cout << "PASS: resource target order, occlusion, pass-through and ancestor subscriptions\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
