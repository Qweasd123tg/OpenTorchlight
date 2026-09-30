#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_combobox.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

UiWidget widget(std::string name, std::string type, std::string area) {
    UiWidget result;
    result.name = std::move(name);
    result.type = std::move(type);
    result.properties["UnifiedAreaRect"] = std::move(area);
    return result;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: ui_combobox_test /path/to/pak.zip");
        PakArchive archive(argv[1]);
        UiResources resources(archive);
        UiWindowRuntime runtime;
        const auto sheet = runtime.create(widget("sheet", "DefaultWindow",
            "{{0,0},{0,0},{1,0},{1,0}}"));
        const auto root = runtime.create(widget("settings", "DefaultWindow",
            "{{0,0},{0,0},{1,0},{1,0}}"));
        const auto resolution = runtime.create(widget("settings/ResolutionDropdown",
            "GuiLook/Combobox", "{{0,20},{0,20},{0,220},{0,150}}"));
        const auto shadow = runtime.create(widget("settings/ShadowDropdown",
            "GuiLook/Combobox", "{{0,260},{0,20},{0,460},{0,150}}"));
        const auto particle = runtime.create(widget("settings/ParticleDropdown",
            "GuiLook/Combobox", "{{0,260},{0,180},{0,460},{0,310}}"));
        runtime.add_child(sheet, root);
        runtime.add_child(root, resolution);
        runtime.add_child(root, shadow);
        runtime.add_child(root, particle);
        runtime.set_sheet(sheet);

        UiSettingsComboboxes combos(runtime, resources);
        const auto modes = UiSettingsComboboxes::resolution_options(
            {{1280, 720}, {1920, 1080}, {1280, 720}, {0, 0}});
        require(modes.size() == 2 && modes[0].text == "1280 x 720" &&
                    modes[1].resolution == UiResolution{1920, 1080},
                "resolution enumeration did not preserve host order/dedupe");
        const auto resolution_ids = combos.add(UiSettingsComboKind::resolution, resolution, modes);
        const auto shadow_ids = combos.add(UiSettingsComboKind::shadow, shadow,
            UiSettingsComboboxes::shadow_options());
        const auto particle_ids = combos.add(UiSettingsComboKind::particle, particle,
            UiSettingsComboboxes::particle_options());
        require(runtime.window(resolution_ids.editbox).name ==
                    "settings/ResolutionDropdown__auto_editbox__" &&
                    runtime.window(resolution_ids.droplist).parent ==
                        static_cast<std::int32_t>(resolution) &&
                    runtime.window(resolution_ids.horizontal_scrollbar).parent ==
                        static_cast<std::int32_t>(resolution_ids.droplist),
                "Falagard autochild names or ownership differ");
        require(combos.handles(shadow_ids.drop_button) &&
                    combos.handles(particle_ids.vertical_scrollbar) &&
                    combos.has(UiSettingsComboKind::resolution),
                "autochild routing is incomplete");

        DisplaySettings settings;
        settings.res_width = 1920;
        settings.res_height = 1080;
        settings.shadows_enabled = true;
        settings.shadows_detail = 4;
        settings.particle_fps = 40.0F;
        settings.particle_percent = 100.0F;
        combos.sync(settings);
        require(combos.selected(UiSettingsComboKind::resolution) == 1 &&
                    combos.selected(UiSettingsComboKind::shadow) == 4 &&
                    combos.selected(UiSettingsComboKind::particle) == 2 &&
                    runtime.window(resolution_ids.editbox).property("Text") == "1920 x 1080",
                "settings-to-combobox synchronization differs");

        auto frame = runtime.snapshot(800, 600);
        combos.layout(frame);
        frame = runtime.snapshot(800, 600);
        const auto button_index = frame.resolved_index_by_id[resolution_ids.drop_button];
        require(button_index && combos.pointer_down(resolution_ids.drop_button, frame,
                    frame.widgets[*button_index].rect.x + 1,
                    frame.widgets[*button_index].rect.y + 1) &&
                    runtime.capture() == resolution_ids.droplist,
                "drop-button base/callback order did not leave capture on droplist");
        static_cast<void>(combos.pointer_up(resolution_ids.drop_button, frame,
            frame.widgets[*button_index].rect.x + 1,
            frame.widgets[*button_index].rect.y + 1));
        combos.hide_all();
        frame = runtime.snapshot(800, 600);
        const auto edit_index = frame.resolved_index_by_id[resolution_ids.editbox];
        require(edit_index && combos.pointer_down(resolution_ids.editbox, frame,
                    frame.widgets[*edit_index].rect.x + 2, frame.widgets[*edit_index].rect.y + 2),
                "read-only editbox did not display popup");
        require(combos.popup_visible(UiSettingsComboKind::resolution) &&
                    runtime.capture() == resolution_ids.droplist,
                "popup did not activate and capture input");
        frame = runtime.snapshot(800, 600);
        const auto rows = combos.paint(frame);
        require(rows.size() >= 2 && rows[0].clip.width > 0 && rows[0].rect.height > 0 &&
                    rows[1].paint_order == rows[0].paint_order,
                "list item geometry did not use shared snapshot/clip");
        const float x = rows[0].rect.x + 1;
        const float y = rows[0].rect.y + 1;
        combos.pointer_move(frame, x, y, false);
        const auto accepted = combos.pointer_up(resolution_ids.droplist, frame, x, y);
        require(accepted && accepted->kind == UiSettingsComboKind::resolution &&
                    accepted->option.resolution == UiResolution{1280, 720} &&
                    !combos.popup_visible(UiSettingsComboKind::resolution) && !runtime.capture(),
                "selection acceptance/text/hide/capture order differs");
        UiSettingsComboboxes::apply(*accepted, settings);
        require(settings.res_width == 1280 && settings.res_height == 720,
                "resolution selection had no DisplaySettings consumer");

        const UiComboSelection shadow_choice{UiSettingsComboKind::shadow, 5,
            UiSettingsComboboxes::shadow_options()[5]};
        UiSettingsComboboxes::apply(shadow_choice, settings);
        require(settings.shadows_enabled && settings.shadows_detail == 5,
                "shadow selection had no exact DisplaySettings consumer");
        require(settings.lighting_enabled && settings.shadow_resolution == 1024,
                "shadow selection lost lighting/map-size effects");
        const UiComboSelection shadow_off{UiSettingsComboKind::shadow, 1,
            UiSettingsComboboxes::shadow_options()[1]};
        UiSettingsComboboxes::apply(shadow_off, settings);
        require(!settings.shadows_enabled && settings.shadows_detail == 1,
                "shadow-off mapping differs");
        require(settings.lighting_enabled,
                "shadow-off ID 1 incorrectly disabled lighting");
        require(settings.shadow_resolution == 128, "ID1 skipped the original 128 map-size write");
        settings.shadow_resolution = 1024;
        UiSettingsComboboxes::apply(
            {UiSettingsComboKind::shadow, 0, UiSettingsComboboxes::shadow_options()[0]},
            settings);
        require(settings.shadow_resolution == 128, "ID0 skipped the original 128 map-size write");
        require(!settings.lighting_enabled && !settings.shadows_enabled,
                "lighting-off ID 0 mapping differs");
        const auto particles = UiSettingsComboboxes::particle_options();
        require(particles.size() == 3 && particles[0].particle_fps == 20.0F &&
                    particles[1].particle_percent == 50.0F &&
                    particles[2].particle_fps == 40.0F && particles[2].particle_percent == 100.0F,
                "original particle FPS/PCT table differs");
        UiSettingsComboboxes::apply(
            {UiSettingsComboKind::particle, 0, particles[0]}, settings);
        require(settings.particle_fps == 20.0F && settings.particle_percent == 10.0F,
                "particle selection had no exact DisplaySettings consumer");
        combos.update_options(UiSettingsComboKind::resolution,
            UiSettingsComboboxes::resolution_options({{1024, 768}, {1920, 1080}}));
        combos.sync(settings);
        require(combos.options(UiSettingsComboKind::resolution).front().resolution ==
                    UiResolution{1024, 768},
                "hotplug resolution refresh did not replace typed options");

        frame = runtime.snapshot(800, 600);
        const auto shadow_edit = frame.resolved_index_by_id[shadow_ids.editbox];
        require(combos.pointer_down(shadow_ids.editbox, frame,
                    frame.widgets[*shadow_edit].rect.x + 1,
                    frame.widgets[*shadow_edit].rect.y + 1),
                "shadow editbox did not open popup");
        require(runtime.capture() == shadow_ids.droplist, "second popup did not capture");
        runtime.activate(particle_ids.editbox); // Window::activate loses foreign capture.
        combos.reconcile_capture();
        require(!combos.popup_visible(UiSettingsComboKind::shadow),
                "foreign capture loss did not hide the popup");

        UiLayoutState doubled;
        doubled.offset_ratio = 2.0F;
        auto doubled_frame = runtime.snapshot(1600, 1536, doubled);
        combos.layout(doubled_frame);
        doubled_frame = runtime.snapshot(1600, 1536, doubled);
        const auto doubled_edit = doubled_frame.resolved_index_by_id[resolution_ids.editbox];
        require(doubled_edit && frame.widgets[*edit_index].rect.height > 0.0F &&
                    doubled_frame.widgets[*doubled_edit].rect.height >
                        frame.widgets[*edit_index].rect.height * 1.9F,
                "AutoScaled font height was not applied exactly once at 2x offset ratio");
        require(combos.pointer_down(resolution_ids.editbox, doubled_frame,
                    doubled_frame.widgets[*doubled_edit].rect.x + 2,
                    doubled_frame.widgets[*doubled_edit].rect.y + 2),
                "scaled editbox did not open popup");
        doubled_frame = runtime.snapshot(1600, 1536, doubled);
        const auto doubled_rows = combos.paint(doubled_frame);
        const auto doubled_list = doubled_frame.resolved_index_by_id[resolution_ids.droplist];
        require(doubled_list && doubled_rows.size() == 2 &&
                    std::abs(doubled_frame.widgets[*doubled_edit].rect.height -
                             doubled_rows.front().rect.height * 1.5F) < 0.01F &&
                    doubled_rows.back().rect.y + doubled_rows.back().rect.height <=
                        doubled_frame.widgets[*doubled_list].rect.y +
                            doubled_frame.widgets[*doubled_list].rect.height + 0.01F,
                "scaled edit/list rows were double-scaled or did not fit the popup");
        combos.hide_all();

        std::cout << "PASS: settings Combobox autochildren, popup capture, item acceptance and "
                     "resolution/shadow/particle contracts\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
