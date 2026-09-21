#include "torchlight/ui_window_runtime.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace torchlight;
namespace {

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

UiWidget widget(std::string name, std::string type = "DefaultWindow",
                std::string area = "{{0,0},{0,0},{1,0},{1,0}}") {
    UiWidget value;
    value.name = std::move(name);
    value.type = std::move(type);
    value.properties["UnifiedAreaRect"] = std::move(area);
    return value;
}

void ownership_and_draw_contract() {
    UiWindowRuntime runtime;
    const auto sheet = runtime.create(widget("sheet"));
    const auto root = runtime.create(widget("root"));
    auto ordinary_widget = widget("ordinary", "DefaultWindow", "{{0,0},{0,0},{0,80},{0,80}}");
    const auto ordinary = runtime.create(std::move(ordinary_widget));
    auto top_widget = widget("top", "DefaultWindow", "{{0,0},{0,0},{0,80},{0,80}}");
    top_widget.properties["AlwaysOnTop"] = "True";
    const auto top = runtime.create(std::move(top_widget));
    runtime.add_child(sheet, root);
    runtime.add_child(root, top);
    runtime.add_child(root, ordinary);
    runtime.set_sheet(sheet);
    bool duplicate_rejected = false;
    try { (void)runtime.create(widget("sheet")); }
    catch (const std::invalid_argument&) { duplicate_rejected = true; }
    require(duplicate_rejected, "live WindowManager name collision was accepted");

    auto frame = runtime.snapshot(100, 100);
    require(frame.source_ids.size() == 4 &&
                frame.widgets[*frame.resolved_index_by_id[ordinary]].paint_order <
                    frame.widgets[*frame.resolved_index_by_id[top]].paint_order,
            "draw list did not partition ordinary before AlwaysOnTop");
    require(runtime.target_at_position(frame, 20, 20) == top,
            "topmost runtime target differs");

    runtime.move_to_back(top);
    frame = runtime.snapshot(100, 100);
    require(frame.widgets[*frame.resolved_index_by_id[ordinary]].paint_order <
                frame.widgets[*frame.resolved_index_by_id[top]].paint_order,
            "move_to_back crossed the AlwaysOnTop partition");
    runtime.move_to_front(ordinary);
    frame = runtime.snapshot(100, 100);
    require(frame.widgets[*frame.resolved_index_by_id[ordinary]].paint_order <
                frame.widgets[*frame.resolved_index_by_id[top]].paint_order,
            "move_to_front crossed the sibling Z group");

    const auto revision = runtime.revision();
    runtime.set_property(ordinary, "UnifiedAreaRect", "{{0,7},{0,9},{0,87},{0,89}}");
    frame = runtime.snapshot(100, 100);
    require(runtime.revision() > revision && frame.resolved_index_by_id[ordinary] &&
                frame.widgets[*frame.resolved_index_by_id[ordinary]].rect.x == 7,
            "property mutation did not invalidate and resolve");
    require(runtime.find("ordinary") == ordinary && runtime.window(ordinary).parent ==
                static_cast<std::int32_t>(root),
            "registry lookup or ID parent edge differs");
}

void capture_modal_and_detach_contract() {
    UiWindowRuntime runtime;
    const auto sheet = runtime.create(widget("sheet"));
    const auto parent = runtime.create(widget("parent", "DefaultWindow",
        "{{0,10},{0,10},{0,90},{0,90}}"));
    const auto child = runtime.create(widget("child", "DefaultWindow",
        "{{0,5},{0,5},{0,25},{0,25}}"));
    const auto modal = runtime.create(widget("modal", "DefaultWindow",
        "{{0,60},{0,60},{0,90},{0,90}}"));
    runtime.add_child(sheet, parent);
    runtime.add_child(parent, child);
    runtime.add_child(sheet, modal);
    runtime.set_zero_position(parent, true);
    runtime.set_sheet(sheet);
    runtime.activate(child);
    require(runtime.is_active(parent) && runtime.is_active(child),
            "parent-first activation chain differs");
    require(runtime.capture_input(parent), "active parent failed to capture");
    runtime.set_restore_capture(child, true);
    require(runtime.capture_input(child) && runtime.capture() == child,
            "restore capture did not replace global owner");
    runtime.release_input(child);
    require(runtime.capture() == parent,
            "release did not restore the previous capture owner");

    runtime.remove_child(sheet, parent);
    auto frame = runtime.snapshot(100, 100);
    require(runtime.capture() == parent && runtime.target_at_position(frame, 99, 99) == parent,
            "detach cleared or geometrically clipped capture");
    runtime.set_distributes_captured_inputs(parent, true);
    require(runtime.target_at_position(frame, 6, 6) == child,
            "detached distributed capture did not resolve descendant geometry");
    runtime.release_input(parent);

    runtime.set_modal(modal, true);
    frame = runtime.snapshot(100, 100);
    require(runtime.target_at_position(frame, 1, 1) == modal &&
                runtime.dispatch_path(modal) == std::vector<UiWindowId>{modal},
            "modal did not clamp target and ancestor dispatch");
    runtime.set_modal(parent, false);
    require(runtime.modal() == modal, "non-current modal cleared current modal");
    runtime.set_modal(modal, false);

    runtime.set_visible(sheet, false);
    frame = runtime.snapshot(100, 100);
    runtime.activate(parent);
    require(!runtime.target_at_position(frame, 6, 6),
            "hidden sheet failed to gate capture/modal targeting");
}

void events_buttons_and_dead_pool_contract() {
    UiWindowRuntime runtime;
    const auto sheet = runtime.create(widget("sheet"));
    const auto button = runtime.create(widget("button", "Torchlight/StandardButton",
        "{{0,10},{0,10},{0,50},{0,50}}"));
    runtime.add_child(sheet, button);
    runtime.set_sheet(sheet);
    runtime.activate(button);
    auto frame = runtime.snapshot(100, 100);
    runtime.set_mouse_target(button);

    std::vector<std::string> order;
    bool expect_pushed_during_lost = true;
    runtime.set_event_listener([&](const UiWindowEvent& event) {
        if (event.window == button && event.type == UiWindowEventType::capture_gained)
            order.push_back("gained");
        if (event.window == button && event.type == UiWindowEventType::mouse_retarget_requested)
            order.push_back("retarget");
        if (event.window == button && event.type == UiWindowEventType::capture_lost) {
            require(!expect_pushed_during_lost || runtime.button_pushed(button),
                    "ButtonBase pushed cleared before Window capture-lost event");
            order.push_back("lost");
        }
        if (event.window == button && event.type == UiWindowEventType::destruction_started)
            order.push_back("destroy");
    });
    const auto handled = runtime.button_mouse_down(button, frame, 20, 20,
        [&](UiWindowId) {
            require(!runtime.capture() && !runtime.button_pushed(button),
                    "ButtonBase state changed before Window/game callback");
            order.push_back("base");
        });
    require(handled && runtime.capture() == button && runtime.button_pushed(button) &&
                runtime.button_hovering(button) &&
                order == std::vector<std::string>({"base", "gained"}),
            "button down ordering/state differs");
    runtime.set_enabled(button, false);
    runtime.button_mouse_move(button, frame, 20, 20);
    require(runtime.capture() == button && !runtime.button_hovering(button),
            "disabled captured button remained hit or released capture");
    runtime.set_enabled(button, true);
    runtime.button_mouse_move(button, frame, 20, 20);
    require(runtime.button_hovering(button), "re-enabled captured button did not restore hover");
    bool clicked = false;
    require(runtime.button_mouse_up(button, frame, 20, 20,
        [&](UiWindowId) { clicked = true; order.push_back("derived"); }),
        "button mouse-up was not handled");
    require(clicked && !runtime.capture() && !runtime.button_pushed(button) &&
                order == std::vector<std::string>(
                    {"base", "gained", "derived", "retarget", "lost", "retarget"}),
            "button up effect/release ordering differs");

    require(runtime.capture_input(button), "button recapture failed");
    expect_pushed_during_lost = false;
    // A listener may query stable ID state and mutate the registry reentrantly.
    runtime.destroy(button);
    require(!runtime.alive(button) && !runtime.capture() &&
                order[order.size() - 4] == "retarget" &&
                order[order.size() - 3] == "lost" &&
                order[order.size() - 2] == "retarget" && order.back() == "destroy",
            "destroy did not release capture before destruction event");
    runtime.clean_dead_pool();
    const auto later = runtime.create(widget("later"));
    require(later > button, "tombstoned UI window ID was reused");

    auto retained_widget = widget("retained");
    retained_widget.properties["DestroyedByParent"] = "False";
    const auto owner = runtime.create(widget("owner"));
    const auto retained = runtime.create(std::move(retained_widget));
    runtime.add_child(owner, retained);
    runtime.destroy(owner);
    require(runtime.alive(retained) && runtime.window(retained).parent == -1,
            "DestroyedByParent=False child did not survive detached");

    const auto slider = runtime.create(widget("slider", "Falagard/Slider",
        "{{0,0},{0,0},{0,100},{0,20}}"));
    const auto thumb = runtime.create(widget("__auto_thumb__", "GuiLook/SliderThumb",
        "{{0,0},{0,0},{0,10},{0,20}}"));
    runtime.add_child(sheet, slider);
    runtime.add_child(slider, thumb);
    runtime.activate(thumb);
    frame = runtime.snapshot(100, 100);
    require(runtime.is_thumb(thumb) && runtime.thumb_mouse_down(thumb, frame, 3, 5),
            "typed Thumb did not enter ButtonBase capture");
    float moved_left = -1;
    runtime.thumb_mouse_move(thumb, frame, 98, 5,
        [&](UiWindowId moved, float left) { require(moved == thumb, "wrong thumb move owner");
                                           moved_left = left; });
    require(moved_left == 90 && runtime.thumb_mouse_up(thumb, frame, 98, 5),
            "thumb drag did not preserve offset/clamp/release");

    const auto checkbox = runtime.create(widget("checkbox", "GuiLook/Checkbox",
        "{{0,0},{0,30},{0,20},{0,50}}"));
    const auto radio = runtime.create(widget("radio", "GuiLook/RadioTab",
        "{{0,30},{0,30},{0,50},{0,50}}"));
    const auto radio_peer = runtime.create(widget("radio-peer", "GuiLook/RadioTab",
        "{{0,50},{0,30},{0,70},{0,50}}"));
    auto other_group_widget = widget("radio-other-group", "GuiLook/RadioTab",
        "{{0,70},{0,30},{0,90},{0,50}}");
    other_group_widget.properties["GroupID"] = "1";
    const auto radio_other_group = runtime.create(std::move(other_group_widget));
    runtime.add_child(sheet, checkbox);
    runtime.add_child(sheet, radio);
    runtime.add_child(sheet, radio_peer);
    runtime.add_child(sheet, radio_other_group);
    runtime.set_button_selected(radio_other_group, true);
    std::vector<UiWindowId> selection_order;
    runtime.set_event_listener([&](const UiWindowEvent& event) {
        if (event.type == UiWindowEventType::selection_changed)
            selection_order.push_back(event.window);
    });
    runtime.activate(checkbox);
    frame = runtime.snapshot(100, 100);
    require(runtime.button_mouse_down(checkbox, frame, 5, 35) &&
                runtime.button_mouse_up(checkbox, frame, 5, 35) &&
                runtime.button_selected(checkbox),
            "Checkbox did not toggle selection before ButtonBase release");
    selection_order.clear();
    runtime.activate(radio);
    frame = runtime.snapshot(100, 100);
    require(runtime.button_mouse_down(radio, frame, 35, 35) &&
                runtime.button_mouse_up(radio, frame, 35, 35) &&
                runtime.button_selected(radio),
            "RadioButton did not select on accepted release");
    require(selection_order == std::vector<UiWindowId>{radio},
            "initial RadioButton selection event differs");
    selection_order.clear();
    runtime.activate(radio_peer);
    frame = runtime.snapshot(100, 100);
    require(runtime.button_mouse_down(radio_peer, frame, 55, 35) &&
                runtime.button_mouse_up(radio_peer, frame, 55, 35) &&
                runtime.button_selected(radio_peer) && !runtime.button_selected(radio) &&
                runtime.button_selected(radio_other_group),
            "same-type/default-GroupID radio sibling was not deselected");
    require(selection_order == std::vector<UiWindowId>({radio, radio_peer}),
            "radio sibling deselection event did not precede selected event");
}

} // namespace

int main() {
    try {
        ownership_and_draw_contract();
        capture_modal_and_detach_contract();
        events_buttons_and_dead_pool_contract();
        std::cout << "ui window runtime tests passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
