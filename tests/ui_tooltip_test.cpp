#include "torchlight/ui_tooltip.hpp"

#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_layout.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace torchlight;
namespace {

unsigned checks = 0;
void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}

UiWidget widget(std::string name, std::string type = "DefaultWindow") {
    UiWidget result;
    result.name = std::move(name);
    result.type = std::move(type);
    result.properties["UnifiedAreaRect"] = "{{0,0},{0,0},{1,0},{1,0}}";
    return result;
}

float property_float(const UiWindowRuntime& windows, UiWindowId id, const char* key) {
    return std::stof(windows.window(id).property(key));
}

} // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 2, "usage: ui_tooltip_test original-pak.zip");
        PakArchive archive(argv[1]);
        UiResources resources(archive);
        UiWindowRuntime windows;
        const auto sheet = windows.create(widget("sheet"));
        windows.set_sheet(sheet);
        windows.activate(sheet);
        UiTooltips tooltips(windows, resources);
        UiWindowLifecycle lifecycle;
        lifecycle.reset_tooltip_target = [&](UiWindowId id) { tooltips.reset_target(id); };
        lifecycle.release_tooltip = [&](UiWindowId id) { tooltips.release_owned(id); };
        windows.set_lifecycle(std::move(lifecycle));

        auto parent_widget = widget("parent");
        parent_widget.properties["Tooltip"] = "Inherited tooltip";
        const auto parent = windows.create(std::move(parent_widget));
        auto child_widget = widget("child");
        child_widget.properties["UnifiedAreaRect"] = "{{0,20},{0,20},{0,120},{0,80}}";
        child_widget.properties["InheritsTooltipText"] = "True";
        // Explicit cursor image validates the resource-sized offset. CGameUI's
        // normal hardware cursor leaves this absent and therefore offsets zero.
        child_widget.properties["MouseCursorImage"] = "set:WindowsLook image:MouseArrow";
        const auto child = windows.create(std::move(child_widget));
        windows.add_child(sheet, parent);
        windows.add_child(parent, child);
        auto frame = windows.snapshot(1024, 768);

        const auto default_id = tooltips.default_tooltip();
        require(windows.window(default_id).type == "GuiLook/Tooltip" &&
                    windows.window(default_id).property("Font") == "Serif" &&
                    windows.window(default_id).property("MousePassThroughEnabled") == "True",
                "CGameUI default tooltip construction differs");
        tooltips.enter(child, frame, 100, 150);
        require(tooltips.current_tooltip() == default_id && tooltips.target(default_id) == child,
                "inherited target did not bind the default tooltip");
        frame = windows.snapshot(1024, 768);
        const auto tooltip_index = frame.resolved_index_by_id.at(default_id);
        require(tooltip_index && frame.widgets[*tooltip_index].text == "Inherited tooltip" &&
                    frame.widgets[*tooltip_index].rect.x == 110.0F &&
                    frame.widgets[*tooltip_index].rect.y == 169.0F &&
                    frame.widgets[*tooltip_index].rect.width > 0.0F &&
                    frame.widgets[*tooltip_index].rect.height > 0.0F,
                "tooltip text, NamedArea sizing, or cursor resource offset differs");

        tooltips.advance(0.1F, frame, 100, 150);
        require(tooltips.phase(default_id) == UiTooltipPhase::fade_in &&
                    windows.window(default_id).property("Visible") == "True" &&
                    property_float(windows, default_id, "Alpha") == 0.0F,
                "inactive update carried dt into fade-in");
        frame = windows.snapshot(1024, 768);
        tooltips.advance(0.165F, frame, 200, 250);
        require(tooltips.phase(default_id) == UiTooltipPhase::fade_in &&
                    std::abs(property_float(windows, default_id, "Alpha") - 0.5F) < 0.001F,
                "fade-in alpha differs");
        tooltips.move(200, 250); // Fade timers are deliberately not reset.
        tooltips.advance(0.165F, frame, 200, 250);
        require(tooltips.phase(default_id) == UiTooltipPhase::active &&
                    property_float(windows, default_id, "Alpha") == 1.0F,
                "fade timer reset or active transition differs");
        tooltips.leave();
        require(windows.window(default_id).property("Visible") == "True" &&
                    windows.window(default_id).parent == static_cast<std::int32_t>(sheet),
                "leave hid the tooltip before its next update");
        tooltips.advance(0.0F, frame, 200, 250);
        require(tooltips.phase(default_id) == UiTooltipPhase::inactive &&
                    windows.window(default_id).property("Visible") == "False" &&
                    windows.window(default_id).parent < 0,
                "missing target did not perform inactive detach");

        auto custom_widget = widget("custom-owner");
        custom_widget.properties["Tooltip"] = "custom";
        custom_widget.properties["CustomTooltipType"] = "GuiLook/Tooltip";
        const auto owner = windows.create(std::move(custom_widget));
        windows.add_child(sheet, owner);
        frame = windows.snapshot(1024, 768);
        tooltips.enter(owner, frame, 5, 7);
        require(tooltips.current_tooltip() && *tooltips.current_tooltip() != default_id,
                "CustomTooltipType did not create an owned tooltip");
        const auto custom = *tooltips.current_tooltip();
        tooltips.advance(0.1F, frame, 5, 7);
        require(tooltips.phase(custom) == UiTooltipPhase::inactive &&
                    windows.window(custom).property("Visible") == "False",
                "custom tooltip lost the library 0.4 second hover default");
        windows.destroy(owner);
        require(!windows.alive(owner) && !windows.alive(custom) && !tooltips.current_tooltip(),
                "owner teardown retained custom tooltip or target");
        windows.clean_dead_pool();

        auto failed_widget = widget("failed-owner");
        failed_widget.properties["Tooltip"] = "fallback";
        failed_widget.properties["CustomTooltipType"] = "GuiLook/Tooltip";
        const auto failed_owner = windows.create(std::move(failed_widget));
        const auto collision = windows.create(widget(
            "failed-owner__auto_tooltip__", "GuiLook/Tooltip"));
        windows.add_child(sheet, failed_owner);
        frame = windows.snapshot(1024, 768);
        tooltips.enter(failed_owner, frame, 1, 2);
        require(tooltips.current_tooltip() == default_id && windows.alive(collision),
                "failed custom factory left an invalid owned tooltip instead of System fallback");
        windows.destroy(failed_owner);
        windows.destroy(collision);
        windows.clean_dead_pool();

        tooltips.shutdown();
        require(!windows.alive(default_id), "System-owned default tooltip survived shutdown");
        windows.clean_dead_pool();
        std::cout << "PASS " << checks
                  << " tooltip lifecycle checks; pinned state/resource boundary\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL " << error.what() << '\n';
        return 1;
    }
}
