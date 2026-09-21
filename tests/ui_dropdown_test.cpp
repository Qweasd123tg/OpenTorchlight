#include "torchlight/ui_dropdown.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {
void require(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
struct Actions final : MainMenuActions {
    mutable std::vector<std::string> log;
    bool load = false, linux_present = true, throw_request = false;
    bool main_can_load() const override { log.push_back("canLoad"); return load; }
    void main_request_state(int state, int menu) override {
        log.push_back("request:" + std::to_string(state) + ":" + std::to_string(menu));
        if (throw_request) throw std::runtime_error("request failure");
    }
    void main_set_open(bool open) override { log.push_back(open ? "open" : "close"); }
    void main_request_exit() override { log.push_back("exitFlag"); }
    void main_close_all() override { log.push_back("closeAll"); }
    void main_toggle_settings() override { log.push_back("settings"); }
    bool main_has_linux_credits() const override { return linux_present; }
    void main_show_credits(bool linux_panel, bool visible) override {
        log.push_back(std::string(linux_panel ? "linux:" : "runic:") + (visible ? "show" : "hide"));
    }
};
void dispatch_contract() {
    // Expected calls transcribed from complete c4ae80..c4aff1, including
    // unknown enum values and all four open/closed flag combinations.
    for (const bool open : {false, true}) for (const bool closed : {false, true})
        for (const bool load : {false, true}) for (const bool linux_panel : {false, true})
            for (int command = -2; command < 100; ++command) {
                Actions actions; actions.load = load; actions.linux_present = linux_panel;
                std::vector<std::string> expected;
                if (open || !closed) {
                    switch (command) {
                    case 1: expected = {"exitFlag", "closeAll"}; break;
                    case 3: expected = {"request:2:0", "close"}; break;
                    case 4: expected = {"request:0:1", "close"}; break;
                    case 5: expected = {"canLoad", load ? "request:0:3" : "request:0:1", "close"}; break;
                    case 64: expected = {"runic:show"}; break;
                    case 65: expected = {"runic:hide"}; break;
                    case 66: if (linux_panel) expected = {"linux:show"}; break;
                    case 67: if (linux_panel) expected = {"linux:hide"}; break;
                    case 94: expected = {"settings"}; break;
                    }
                }
                require(dispatch_main_menu(open, closed, static_cast<UiLayoutFunction>(command), actions),
                        "original handled return differs");
                require(actions.log == expected, "main dispatch sequence differs");
            }
    Actions throwing; throwing.throw_request = true;
    bool caught = false;
    try { dispatch_main_menu(true, true, UiLayoutFunction::new_game_menu, throwing); }
    catch (const std::runtime_error&) { caught = true; }
    require(caught && throwing.log == std::vector<std::string>{"request:0:1"},
            "dispatch swallowed error or closed after failed call");
    StaticDropdownState state;
    require(!state.open() && state.closed() && !state.attached(), "constructor flags differ");
    state.set_open(false);
    state.set_open(true);
    require(state.open() && state.closed() && state.attached(), "static opening must retain closed flag");
    state.set_open(true);
    require(state.attached(), "repeat open detached root");
    state.set_open(false);
    require(!state.open() && state.closed() && !state.attached(), "static close flags differ");
    state.set_open(true);
    require(state.attached(), "reopen failed");
}

struct Tree final : DropdownEventTree {
    mutable std::vector<std::string> log;
    std::vector<std::vector<Node>> children{{1,2}, {}, {}};
    std::vector<std::string> values{"root", "unknown-command", ""};
    std::string fail;
    void call(const std::string& op, Node n) const {
        const auto entry = op + std::to_string(n);
        log.push_back(entry);
        if (fail == entry) throw std::runtime_error("injected contract error");
    }
    std::size_t child_count(Node n) const override { call("count", n); return children.at(n).size(); }
    Node child(Node n, std::size_t i) const override { call("child", n); return children.at(n).at(i); }
    bool has_click_property(Node n) const override { call("has", n); return true; }
    std::string click_property(Node n) const override { call("get", n); return values.at(n); }
    void want_multi_click(Node n) override { call("multi", n); }
    void subscribe_mouse_down(Node n) override { call("down", n); }
    void subscribe_double_click(Node n) override { call("double", n); }
};
void subscription_contract() {
    Tree tree;
    map_dropdown_events(tree, 0);
    const std::vector<std::string> order{
        "count0","child0","count1","has1","get1","multi1","down1","double1",
        "child0","count2","has2","get2","has0","get0","multi0","down0","double0"};
    require(tree.log == order, "child-first subscription order differs");
    map_dropdown_events(tree, 0);
    require(std::count(tree.log.begin(), tree.log.end(), "down1") == 2, "mapping was deduplicated");
    tree = Tree{}; tree.fail = "down1";
    map_dropdown_events(tree, 0);
    require(std::find(tree.log.begin(), tree.log.end(), "multi1") != tree.log.end() &&
            std::find(tree.log.begin(), tree.log.end(), "double1") == tree.log.end() &&
            tree.log.back() == "double0", "failure did not retain prior effects/continue parent");
    tree = Tree{}; tree.fail = "get1";
    map_dropdown_events(tree, 0);
    require(std::find(tree.log.begin(), tree.log.end(), "multi1") == tree.log.end() &&
            tree.log.back() == "double0", "property failure boundary differs");
    tree = Tree{}; tree.fail = "child0";
    bool caught = false;
    try { map_dropdown_events(tree, 0); } catch (const std::runtime_error&) { caught = true; }
    require(caught, "child traversal failure was swallowed");
    tree = Tree{}; tree.values[1] = std::string(1, '\0');
    map_dropdown_events(tree, 0);
    require(std::find(tree.log.begin(), tree.log.end(), "down1") != tree.log.end(),
            "nonempty CEGUI string mistaken for zero-length C string");

    const std::string xml = "<GUILayout><Window Name='root'><Window Name='empty'/>"
        "<Window Name='known'><Property Name='onClick' Value='guiNewGameMenu'/></Window>"
        "<Window Name='unknown'><Property Name='onClick'>unknown-command</Property></Window>"
        "</Window></GUILayout>";
    const auto layout = UiLayout::parse({xml.begin(), xml.end()});
    const auto bindings = dropdown_subscriptions(layout);
    require(bindings.size() == 4 && bindings[0].mouse_down == 0 && bindings[1].mouse_down == 0,
            "absent property subscribed");
    for (const auto n : {2,3}) require(bindings[n].multi_click && bindings[n].mouse_down == 1 &&
                                     bindings[n].double_click == 1, "layout subscription lost");
    require(layout.widgets()[2].layout_function == UiLayoutFunction::new_game_menu &&
            !layout.widgets()[3].layout_function, "binding and event registration were conflated");
}
void runtime_tree_contract() {
    const std::string xml =
        "<GUILayout><Window Name='__opentorchlight/dropdown/root'>"
        "<Property Name='UnifiedAreaRect' Value='{{0,30},{0,40},{0,230},{0,140}}'/>"
        "<Property Name='MousePassThroughEnabled' Value='True'/>"
        "<Window Name='command'><Property Name='WantsMultiClickEvents' Value='False'/>"
        "<Property Name='UnifiedPosition' Value='{{0,10},{0,20}}'/>"
        "<Property Name='UnifiedSize' Value='{{0,30},{0,20}}'/>"
        "<Property Name='onClick' Value='guiNewGameMenu'/></Window>"
        "</Window></GUILayout>";
    const auto layout = UiLayout::parse({xml.begin(), xml.end()});
    StaticDropdownState open_before_bind;
    open_before_bind.set_open(true);
    open_before_bind.bind_layout(layout);
    require(open_before_bind.manager().window(open_before_bind.resource_ids().at(1))
                .property("WantsMultiClickEvents") == "True",
            "mapEventHandlers did not enable multi-clicks on the live receiver");
    require(open_before_bind.attached() &&
            open_before_bind.resolve(640, 480).widgets.size() == 6,
            "bind replaced the already-open root attachment edge");
    StaticDropdownState state;
    state.bind_layout(layout);
    auto closed = state.resolve(640, 480);
    require(closed.sheet == 0 && closed.widgets.size() == 1 && closed.subscriptions.size() == 1,
            "closed tree exposed retained dropdown subtree");
    require(closed.target_at_position(900, 900) == closed.sheet,
            "system sheet fallback applied isHit to sheet");
    closed.widgets[0].visible = false;
    require(!closed.target_at_position(1, 1), "hidden sheet exposed a child/fallback target");
    closed.sheet = 99;
    require(!closed.target_at_position(1, 1), "invalid sheet exposed a child/fallback target");

    state.set_open(true);
    auto frame = state.resolve(640, 480);
    require(state.attached() && frame.widgets.size() == 6 && frame.subscriptions.size() == 6,
            "open tree size or edge differs");
    require(frame.widgets[0].parent == -1 && frame.widgets[1].parent == 0 &&
            frame.widgets[2].parent == 1 && frame.widgets[3].parent == 1 &&
            frame.widgets[4].parent == 1 && frame.widgets[5].parent == 4,
            "runtime parent graph differs");
    require(frame.widgets[0].type == "DefaultWindow" &&
            frame.widgets[1].type == "DefaultWindow" &&
            frame.widgets[2].type == "DefaultWindow" &&
            frame.widgets[3].type == "DefaultWindow", "service window types differ");
    require(frame.widgets[1].property("MousePassThroughEnabled") == "False" &&
            frame.widgets[2].property("MousePassThroughEnabled") == "False" &&
            frame.widgets[3].property("MousePassThroughEnabled") == "True",
            "service pass-through properties differ");
    for (const auto index : {std::size_t{1}, std::size_t{2}, std::size_t{3}})
        require(frame.widgets[index].property("RiseOnClick") == "False" &&
                frame.widgets[index].property("ZOrderingEnabled") == "False" &&
                frame.widgets[index].property("DestroyedByParent") == "True",
                "service ownership/Z properties differ");
    require(frame.widgets[1].paint_order == 1 && frame.widgets[2].paint_order == 2 &&
            frame.widgets[3].paint_order == 3 && frame.widgets[4].paint_order == 4,
            "root/back/content/resource insertion order differs");
    require(frame.widgets[1].name != frame.widgets[4].name,
            "reserved service name collided with resource name");
    require(frame.widgets[4].rect.x == 0 && frame.widgets[4].rect.y == 0 &&
            frame.widgets[4].rect.width == 200 && frame.widgets[4].rect.height == 100 &&
            frame.widgets[5].rect.x == 10 && frame.widgets[5].rect.y == 20,
            "CMain resource-root position reset differs");
    require(frame.target_at_position(15, 25) == std::optional<std::size_t>{5} &&
            frame.mouse_down_receiver(15, 25) == std::optional<std::size_t>{5},
            "resource target/subscription remap differs");
    auto hidden_sheet = frame;
    hidden_sheet.widgets[*hidden_sheet.sheet].visible = false;
    require(!hidden_sheet.target_at_position(15, 25) &&
            !hidden_sheet.mouse_down_receiver(15, 25),
            "hidden sheet did not gate an otherwise hittable child");
    hidden_sheet = frame;
    hidden_sheet.sheet.reset();
    require(!hidden_sheet.target_at_position(15, 25),
            "missing sheet exposed an otherwise hittable child");
    require(frame.target_at_position(300, 300) == std::optional<std::size_t>{2},
            "empty dropdown area did not target back window");
    frame.widgets[2].properties["MousePassThroughEnabled"] = "True";
    require(frame.target_at_position(300, 300) == std::optional<std::size_t>{1},
            "root fallback was not retained behind pass-through children");

    UiLayoutState scaled;
    scaled.offset_ratio = 0.5F;
    frame = state.resolve(640, 480, scaled);
    require(frame.widgets[4].rect.x == 0 && frame.widgets[4].rect.y == 0 &&
            frame.widgets[4].rect.width == 100 && frame.widgets[4].rect.height == 50 &&
            frame.widgets[5].rect.x == 5 && frame.widgets[5].rect.y == 10,
            "scaled resize compounded or lost root-position reset");

    const auto retained_name = frame.widgets[5].name;
    state.set_open(false);
    require(!state.attached() && state.resolve(640, 480).widgets.size() == 1,
            "close did not detach root edge");
    state.set_open(false);
    state.set_open(true);
    const auto reopened = state.resolve(640, 480);
    require(reopened.widgets[5].name == retained_name && reopened.subscriptions[5].mouse_down == 1,
            "reopen did not retain owned resource data");

    DropdownWindowFrame surviving;
    {
        StaticDropdownState owner;
        owner.bind_layout(layout);
        owner.set_open(true);
        surviving = owner.resolve(640, 480);
    }
    require(surviving.widgets.size() == 6 && surviving.mouse_down_receiver(15, 25) == 5,
            "port owner teardown left borrowed runtime data");

    const std::string hidden_xml =
        "<GUILayout><Window Name='hidden'><Property Name='Visible' Value='False'/>"
        "</Window></GUILayout>";
    const auto hidden = UiLayout::parse({hidden_xml.begin(), hidden_xml.end()});
    state.bind_layout(hidden);
    frame = state.resolve(640, 480);
    require(!frame.widgets[4].visible && frame.target_at_position(1, 1) == 2,
            "bound resource root ignored explicit visibility");

    const std::string aligned_xml =
        "<GUILayout><Window Name='aligned'><Property Name='UnifiedAreaRect' "
        "Value='{{0,30},{0,40},{0,230},{0,140}}'/><Property Name='HorizontalAlignment' "
        "Value='Right'/><Property Name='VerticalAlignment' Value='Bottom'/></Window></GUILayout>";
    const auto aligned = UiLayout::parse({aligned_xml.begin(), aligned_xml.end()});
    state.bind_layout(aligned);
    frame = state.resolve(640, 480);
    require(frame.widgets[4].rect.x == 440 && frame.widgets[4].rect.y == 380 &&
            frame.widgets[4].rect.width == 200 && frame.widgets[4].rect.height == 100,
            "root UDim reset incorrectly erased alignment");
}
void shared_runtime_contract() {
    UiWindowRuntime manager;
    UiWidget sheet_widget;
    sheet_widget.name = "shared-sheet";
    sheet_widget.type = "DefaultWindow";
    sheet_widget.properties["UnifiedSize"] = "{{1,0},{1,0}}";
    const auto sheet = manager.create(std::move(sheet_widget));
    manager.set_sheet(sheet);
    const std::string xml =
        "<GUILayout><Window Name='page'><Window Name='command'>"
        "<Property Name='UnifiedSize' Value='{{0,20},{0,20}}'/>"
        "<Property Name='onClick' Value='guiNewGameMenu'/></Window></Window></GUILayout>";
    const auto layout = UiLayout::parse({xml.begin(), xml.end()});
    StaticDropdownState first(manager, sheet, "shared/first");
    StaticDropdownState second(manager, sheet, "shared/second", true);
    first.bind_layout(layout);
    second.bind_layout(layout);
    first.set_open(true);
    second.set_open(true);
    require(first.attached() && second.attached() && first.root() != second.root(),
            "shared dropdown roots did not attach independently");
    require(manager.window(second.resource_roots().front()).parent ==
                static_cast<std::int32_t>(second.content()),
            "content_parent did not own resource root");
    const auto command = first.resource_ids().at(1);
    require(first.subscription(command).mouse_down == 1 &&
                first.subscription(second.resource_ids().at(1)).mouse_down == 0,
            "stable-ID subscription lookup crossed menu owners");
    const auto retained = second.resource_ids();
    second.set_settings_open(false);
    require(!second.attached() && !second.closed() && manager.alive(retained.front()) &&
                second.resource_ids() == retained,
            "shared close destroyed or renumbered retained resource windows");
    second.set_settings_open(true);
    require(second.resource_ids() == retained && !second.closed() &&
                manager.window(second.content()).property("UnifiedPosition") == "{{0,0},{0,0}}",
            "shared reopen did not retain stable resource IDs");
}
void resource_contract(const char* path) {
    PakArchive archive(path); UiResources resources(archive);
    const auto* layout = resources.layout("media/UI/mainmenuframe.layout");
    require(layout != nullptr, "main menu resource absent");
    const auto bindings = dropdown_subscriptions(*layout);
    bool load = false, runic = false, linux_panel = false;
    for (std::size_t n = 0; n < layout->widgets().size(); ++n) {
        const auto& w = layout->widgets()[n];
        const auto expected = !w.property("onClick").empty();
        require(bindings[n].multi_click == expected && bindings[n].mouse_down == unsigned(expected) &&
                bindings[n].double_click == unsigned(expected), "resource subscription differs");
        if (w.layout_function == UiLayoutFunction::continue_game_menu) load = expected;
        if (w.layout_function == UiLayoutFunction::select_a) runic = expected;
        if (w.layout_function == UiLayoutFunction::select_c) linux_panel = expected;
    }
    require(load && runic && linux_panel, "original main commands absent");

    StaticDropdownState runtime;
    runtime.bind_layout(*layout);
    runtime.set_open(true);
    for (const auto size : {std::pair{1024, 768}, std::pair{1920, 1080}}) {
        UiLayoutState state;
        state.screen_scale = UiScreenScale::height;
        const auto direct = layout->resolve(size.first, size.second, state);
        const auto frame = runtime.resolve(size.first, size.second, state);
        require(frame.widgets.size() == direct.size() + 4 &&
                frame.subscriptions.size() == bindings.size() + 4,
                "original runtime remap size differs");
        for (std::size_t i = 0; i < direct.size(); ++i) {
            const auto& wrapped = frame.widgets[i + 4];
            require(wrapped.rect.x == direct[i].rect.x && wrapped.rect.y == direct[i].rect.y &&
                    wrapped.rect.width == direct[i].rect.width &&
                    wrapped.rect.height == direct[i].rect.height,
                    "original runtime geometry differs after parent remap");
            require(wrapped.parent == (direct[i].parent < 0 ? 1 : direct[i].parent + 4),
                    "original runtime parent remap differs");
            require(frame.subscriptions[i + 4].mouse_down == bindings[i].mouse_down &&
                    frame.subscriptions[i + 4].double_click == bindings[i].double_click,
                    "original runtime subscriptions differ after remap");
        }
    }
}
}
int main(int argc, char** argv) { try {
    dispatch_contract(); subscription_contract(); runtime_tree_contract(); shared_runtime_contract();
    if (argc == 2) resource_contract(argv[1]);
    else require(argc == 1, "usage: ui_dropdown_test [pak.zip]");
    std::cout << "PASS: main dispatch, subscriptions and owned dropdown runtime tree\n";
    return 0;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; } }
