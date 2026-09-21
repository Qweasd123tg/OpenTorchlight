#include "torchlight/frontend.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
const UiResolvedWidget& named(const std::vector<UiResolvedWidget>& widgets, const std::string& name) {
    const auto found = std::find_if(widgets.begin(), widgets.end(), [&](const auto& w) {
        return w.name == name;
    });
    if (found == widgets.end()) throw std::runtime_error("missing window: " + name);
    return *found;
}
void check(const UiLayout& layout) {
    const auto resolve = [&](std::size_t count, std::size_t scroll, std::size_t selected, bool prompt) {
        return layout.resolve(1024, 768, continue_menu_layout_state(layout, count, scroll, selected, prompt));
    };
    auto widgets = resolve(0, 0, 0, false);
    for (int row = 1; row <= 5; ++row) {
        const auto n = std::to_string(row);
        require(!named(widgets, "Player" + n).visible, "empty slot visible");
        require(!named(widgets, "Player" + n + "Name").visible, "empty name visible");
        require(!named(widgets, "Player" + n + "Desc").visible, "empty description visible");
        require(!named(widgets, "PlayerHighlight" + n).visible, "empty highlight visible");
    }
    require(!named(widgets, "DeleteConfirm").visible, "prompt visible without pending deletion");
    require(!named(widgets, "DeleteConfirmButton").visible, "hidden parent did not hide accept");
    require(!named(widgets, "Continue").visible && !named(widgets, "Delete").visible, "empty list actions visible");
    widgets = resolve(7, 1, 3, true);
    require(named(widgets, "DeleteConfirmButton").visible, "runtime show did not reach accept child");
    require(named(widgets, "ScrollUp").visible && named(widgets, "ScrollDown").visible, "scroll visibility");
    require(!named(widgets, "CharacterModsWarning").visible, "portable saves invent mod mismatch");
    for (int row = 1; row <= 5; ++row) {
        const auto n = std::to_string(row);
        const auto& highlight = named(widgets, "PlayerHighlight" + n);
        require(named(widgets, "Player" + n).visible, "occupied row hidden");
        require(highlight.visible == (row == 3), "selected index did not include scroll offset");
        require(highlight.paint_order > named(widgets, "Player" + n).paint_order, "highlight not raised above slot");
    }
    widgets = resolve(7, 6, 6, false);
    require(named(widgets, "Player1").visible && !named(widgets, "Player2").visible, "last partial page");
    require(!named(widgets, "ScrollDown").visible, "end-of-list scroll down visible");
}
}
int main(int argc, char** argv) {
    try {
        if (argc == 2) {
            PakArchive archive(argv[1]);
            UiResources resources(archive);
            const auto* layout = resources.layout("media/UI/characterload.layout");
            require(layout != nullptr, "missing original character load layout");
            check(*layout);
        } else if (argc == 1) {
            std::string xml = "<GUILayout><Window Name='root'>";
            for (int row = 1; row <= 5; ++row) {
                const auto n = std::to_string(row);
                // Deliberately put highlights BEFORE opaque row windows.
                xml += "<Window Name='PlayerHighlight" + n + "'/>";
                for (const std::string& suffix : {std::string{}, std::string{"Name"}, std::string{"Desc"}})
                    xml += "<Window Name='Player" + n + suffix + "'/>";
            }
            for (const char* name : {"ScrollUp", "ScrollDown", "Continue", "Delete", "CharacterModsWarning"})
                xml += std::string{"<Window Name='"} + name + "'/>";
            xml += "<Window Name='DeleteConfirm'><Property Name='Visible' Value='False'/>"
                   "<Window Name='DeleteConfirmButton'/></Window></Window></GUILayout>";
            check(UiLayout::parse({xml.begin(), xml.end()}));
        } else throw std::runtime_error("usage: ui_menu_state_test [pak.zip]");
        std::cout << "PASS character-list presentation contracts (no event injection or rendering)\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
