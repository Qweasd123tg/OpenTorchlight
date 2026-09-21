#include "torchlight/ui_function_bindings.hpp"
#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_hud.hpp"
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace torchlight;
namespace {
using Function = UiLayoutFunction;
struct Entry {
    int parent = -1;
    int value = -1;
    std::optional<std::string> property;
    std::optional<std::string> second;
    int fail = 0; // 1=presence, 2=first get, 3=second get
    mutable unsigned reads = 0;
};
struct Tree final : UiFunctionTree {
    explicit Tree(std::vector<Entry> entries) : rows(std::move(entries)) {}
    std::vector<Entry> rows;
    mutable std::vector<std::pair<std::string, std::size_t>> events;
    bool fail_children = false;
    std::size_t child_count(Node n) const override {
        if (fail_children) throw std::runtime_error("structural failure");
        std::size_t count = 0;
        for (const auto &row : rows) if (row.parent == static_cast<int>(n)) ++count;
        return count;
    }
    Node child(Node n, std::size_t index) const override {
        for (std::size_t i = 0; i < rows.size(); ++i)
            if (rows[i].parent == static_cast<int>(n) && index-- == 0) return i;
        throw std::runtime_error("missing child");
    }
    bool has_click_property(Node n) const override {
        events.emplace_back("present", n);
        if (rows[n].fail == 1) throw std::runtime_error("property presence failed");
        return rows[n].property.has_value();
    }
    std::string click_property(Node n) const override {
        events.emplace_back("get", n);
        const auto read = ++rows[n].reads;
        if ((rows[n].fail == 2 && read == 1) || (rows[n].fail == 3 && read == 2))
            throw std::runtime_error("property get failed");
        return read == 2 && rows[n].second ? *rows[n].second : rows[n].property.value();
    }
    void set_function(Node n, Function value) noexcept override { rows[n].value = static_cast<int>(value); }
    void run(const UiFunctionNames &names = ui_function_names()) {
        for (std::size_t i = 0; i < rows.size(); ++i)
            if (rows[i].parent == -1) map_ui_functions(*this, i, names);
    }
};
void require(bool condition, const char *message) {
    if (!condition) throw std::runtime_error(message);
}
Entry row(int parent, int prior, std::optional<std::string> prop) {
    Entry entry;
    entry.parent = parent; entry.value = prior; entry.property = std::move(prop);
    return entry;
}
void self_test() {
    Tree tree({row(-1, 7, "guiPause"), row(0, 14, "unknown"), row(0, 15, ""),
               row(1, -1, "guiSelect1"), row(-1, 8, std::nullopt),
               row(-1, 9, std::string("\0guiPause", 9)), row(-1, 10, "guiPause ")});
    tree.run();
    require(tree.rows[0].value == 11 && tree.rows[1].value == 14 && tree.rows[2].value == 96 &&
            tree.rows[3].value == 14 && tree.rows[4].value == 96 && tree.rows[5].value == 9 &&
            tree.rows[6].value == 10, "missing/empty/unknown/NUL command behavior changed");
    std::vector<std::size_t> order;
    for (const auto &event : tree.events) if (event.first == "present") order.push_back(event.second);
    require(order == std::vector<std::size_t>({3, 1, 2, 0, 4, 5, 6}), "not child-first sibling order");
    Tree changing({row(-1, 7, "guiPause")});
    changing.rows[0].second = "guiSelect2";
    changing.run();
    require(changing.rows[0].value == 15 && changing.rows[0].reads == 2, "second property read omitted");
    Tree becomes_empty({row(-1, 7, "guiPause")});
    becomes_empty.rows[0].second = "";
    becomes_empty.run();
    require(becomes_empty.rows[0].value == 7, "empty second read must lookup/preserve, not take first-read NONE branch");
    auto duplicates = ui_function_names();
    duplicates[95] = "GUIPAUSE";
    Tree duplicate({row(-1, -1, "guiPause")}); duplicate.run(duplicates);
    require(duplicate.rows[0].value == 95, "lookup must keep last duplicate, not first");
    for (int fail = 1; fail <= 3; ++fail) {
        Tree broken({row(-1, 7, "guiPause"), row(0, 8, "guiSelect1")});
        broken.rows[0].fail = fail;
        broken.run();
        require(broken.rows[0].value == 96 && broken.rows[1].value == 14,
                "property exception must set current NONE without rolling back child");
        Tree broken_child({row(-1, 7, "guiPause"), row(0, 8, "guiSelect1")});
        broken_child.rows[1].fail = fail;
        broken_child.run();
        require(broken_child.rows[0].value == 11 && broken_child.rows[1].value == 96,
                "child property failure must not prevent parent mapping");
    }
    Tree structural({row(-1, 7, "guiPause")}); structural.fail_children = true;
    bool threw = false;
    try { structural.run(); } catch (const std::runtime_error &) { threw = true; }
    require(threw && structural.rows[0].value == 7, "structural errors swallowed by property catch");
    Tree remap({row(-1, 7, "guiPause")}); remap.run();
    remap.rows[0].property = "unknown"; remap.run();
    require(remap.rows[0].value == 11, "unknown remap cleared prior binding");
    remap.rows[0].property = ""; remap.run();
    require(remap.rows[0].value == 96, "empty remap did not clear to NONE");
    const std::string xml = "<GUILayout><Window Name='Root' Type='DefaultWindow'>"
        "<Window Name='Tab' Type='Button'><Property Name='onClick' Value='guiExitGame'/>"
        "<Property Name='onClick' Value='gUiSeLeCt1'/></Window>"
        "<Window Name='Bad' Type='Button'><Property Name='onClick' Value='unknown'/></Window>"
        "<Window Name='WrongCase' Type='Button'><Property Name='onclick' Value='guiPause'/></Window>"
        "</Window></GUILayout>";
    const auto layout = UiLayout::parse({xml.begin(), xml.end()});
    require(layout.widgets()[1].layout_function == Function::select1, "load did not bind last XML property");
    for (const auto width : {640, 1280, 1920}) {
        const auto widgets = layout.resolve(width, 720);
        require(widgets[0].layout_function == Function::none && widgets[1].layout_function == Function::select1 &&
                !widgets[2].layout_function && widgets[3].layout_function == Function::none,
                "resolve lost or invented a command binding");
        require(widgets[1].callback == "gUiSeLeCt1", "raw callback must remain diagnostic data");
    }
    // The production HUD sink uses the bound ID, not the spelling of its
    // nonempty callback. Empty callback still means no subscribed target.
    UiHudFrame frame;
    UiResolvedWidget button;
    button.rect = {0, 0, 10, 10}; button.callback = "gUiToGgLeInVeNtOrY";
    button.layout_function = Function::toggle_inventory; frame.buttons.push_back(button);
    require(hud_press_function(frame, 5, 5) == Function::toggle_inventory, "HUD did not consume bound ID");
    frame.buttons[0].enabled = false;
    require(!hud_press_function(frame, 5, 5), "disabled command delivered");
    require(ui_function_names().size() == 97 && ui_function_name(Function::none) == "NONE", "table boundary");
    require(ui_function_name(static_cast<Function>(-1)).empty(), "invalid ID accessed table");
    std::cout << "ui_function_bindings: traversal, all property branches, remap, catch, XML and HUD sinks passed\n";
}
void resource_test(const char *path) {
    PakArchive archive(path); UiResources resources(archive);
    const auto *inventory = resources.layout("media/UI/inventorymenu.layout");
    require(inventory != nullptr, "inventory layout unavailable");
    unsigned found = 0;
    for (const auto &widget : inventory->resolve(1280, 720))
        for (const auto &[name, id] : std::vector<std::pair<std::string, int>>{{"TabBackpack", 14}, {"TabSpell", 15}, {"TabFish", 16}})
            if (widget.name == name) {
                require(widget.layout_function == static_cast<Function>(id), "shipped inventory tab binding differs");
                ++found;
            }
    require(found == 3, "missing inventory tab");
    const auto hud = UiHud(resources).frame(1280, 720, {});
    found = 0;
    for (const auto &widget : hud.buttons)
        if (widget.name == "InventoryButton") {
            require(widget.layout_function == Function::toggle_inventory, "shipped HUD binding differs");
            require(hud_press_function(hud, widget.clip.x + widget.clip.width / 2,
                                      widget.clip.y + widget.clip.height / 2) == Function::toggle_inventory,
                    "shipped HUD press lost binding");
            ++found;
        }
    require(found == 1, "missing HUD inventory button");
    std::cout << "original inventory layout -> enum 14/15/16; HUD -> enum 72 -> press sink passed\n";
}
std::string unhex(const std::string &hex) {
    if (hex == "-") return {};
    if (hex.size() % 2) throw std::runtime_error("odd hex");
    std::string value;
    for (std::size_t i = 0; i < hex.size(); i += 2)
        value.push_back(static_cast<char>(std::stoul(hex.substr(i, 2), nullptr, 16)));
    return value;
}
void probe() {
    std::size_t size;
    while (std::cin >> size) {
        if (size > 10000) throw std::runtime_error("fixture too large");
        std::vector<Entry> rows;
        for (std::size_t i = 0; i < size; ++i) {
            int parent, prior; std::string hex;
            if (!(std::cin >> parent >> prior >> hex) || parent < -1 || parent >= static_cast<int>(i))
                throw std::runtime_error("invalid tree fixture");
            rows.push_back(row(parent, prior, hex == "_" ? std::nullopt : std::optional<std::string>(unhex(hex))));
        }
        Tree tree(std::move(rows)); tree.run();
        std::cout << "{\"bindings\":[";
        for (std::size_t i = 0; i < size; ++i) std::cout << (i ? "," : "") << tree.rows[i].value;
        std::cout << "],\"events\":[";
        for (std::size_t i = 0; i < tree.events.size(); ++i)
            std::cout << (i ? "," : "") << "[\"" << tree.events[i].first << "\"," << tree.events[i].second << "]";
        std::cout << "]}\n";
    }
}
} // namespace
int main(int argc, char **argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--self-test") self_test();
        else if (argc == 3 && std::string(argv[1]) == "--pak") resource_test(argv[2]);
        else if (argc == 1) probe();
        else throw std::runtime_error("expected --self-test, --pak FILE or stdin fixtures");
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
