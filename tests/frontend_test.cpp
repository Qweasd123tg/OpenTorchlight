#include "torchlight/frontend.hpp"
#include "torchlight/png_texture.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool b, const char *s) {
    ++checks;
    if (!b)
        throw std::runtime_error(s);
}
std::vector<std::uint8_t> bytes(const std::string &s) {
    return {s.begin(), s.end()};
}
template <class F> void rejects(F f) {
    bool hit = false;
    try {
        f();
    } catch (const std::exception &) {
        hit = true;
    }
    require(hit, "invalid XML accepted");
}
FrontendButton button(Frontend &ui, const std::string &id, int w = 1024, int h = 768) {
    const auto f = ui.frame(w, h);
    const auto it =
        std::find_if(f.buttons.begin(), f.buttons.end(), [&](const auto &b) { return b.id == id; });
    if (it == f.buttons.end())
        throw std::runtime_error("button absent: " + id);
    return *it;
}
void click(Frontend &ui, const std::string &id, int w = 1024, int h = 768) {
    const auto b = button(ui, id, w, h);
    ui.click(b.rect.x + b.rect.width * .5F, b.rect.y + b.rect.height * .5F);
}
void parsing() {
    const auto p = UiLayout::parse(bytes(
        "<GUILayout><Window Name='root' Type='Default'><Window Name='child'><Property Name='Text' "
        "Value='A &amp; B &#x3a0;'/><Property Name='onClick' Value='guiExitApplication'/><Property "
        "Name='onClick' Value='guiScrollDown'/><Property Name='UnifiedPosition' "
        "Value='{{0.5,-100},{0,40}}'/><Property Name='UnifiedSize' "
        "Value='{{0,200},{0,50}}'/><Property name='AlwaysOnTop' value='True'/></Window></Window>"
        "</GUILayout>"));
    const auto f = p.resolve(1024, 768);
    require(f.size() == 2 && f[1].callback == "guiScrollDown", "property last-write rule lost");
    require(f[1].text == "A & B \xCE\xA0", "XML character entities lost");
    require(p.widgets()[1].property("AlwaysOnTop").empty(),
            "lowercase malformed Property was not ignored");
    require(f[1].rect.x == 412 && f[1].rect.y == 40 && f[1].rect.width == 200,
            "unified coordinates wrong");
    const auto small = p.resolve(512, 384);
    require(small[1].rect.x == 206 && small[1].rect.width == 100, "small window mapping wrong");
    const auto lowercase = UiLayout::parse(bytes(
        "<GUILayout><Window Name='Player1Name'><Property Name='Text' Value='before'/>"
        "<Property name='Text' value='after'/></Window></GUILayout>"));
    require(lowercase.widgets()[0].property("Text") == "before",
            "lowercase malformed Property changed an uppercase property");
    for (const auto *s :
         {"<Window Name='x'>", "<Window Name='a'></Thing>", "<!DOCTYPE x><Window Name='a'/>",
          "<Window Name='x'><Property Name='Text' Value='&unknown;'/></Window>",
          "<Window Name='a' Name='b'/>",
          "<Window Name='x'><Property Name='UnifiedSize' Value='nan'/></Window>"})
        rejects([&] { static_cast<void>(UiLayout::parse(bytes(s)).resolve(1024, 768)); });
    auto deep = std::string{};
    for (int i = 0; i < 70; ++i)
        deep += "<Window Name='n'>";
    for (int i = 0; i < 70; ++i)
        deep += "</Window>";
    rejects([&] { static_cast<void>(UiLayout::parse(bytes(deep))); });
}
} // namespace
int main(int argc, char **argv) {
    try {
        if (argc != 2)
            throw std::runtime_error("expected authored frontend fixture");
        parsing();
        PakArchive archive(argv[1]);
        UiResources resources(archive);
        Frontend ui(resources, {{1, "DESTROYER"}, {2, "VANQUISHER"}, {3, "ALCHEMIST"}});
        const auto f = ui.frame(1024, 768);
        require(f.original_layout && f.decorations.size() == 1,
                "original-shaped layout/images not used");
        require(button(ui, "new").rect.x == 100 && button(ui, "new").rect.y == 250,
                "button did not use resource coordinates");
        auto image = resources.image(f.decorations[0].image);
        require(image && image->width == 2, "imageset crop absent");
        const auto png = decode_png(archive.read_normalized(image->texture_path));
        require(png.width == 2 && png.height == 2, "authored PNG not loaded");
        require(!button(ui, "loads").enabled && !button(ui, "continue").enabled,
                "empty save buttons active");
        click(ui, "new", 512, 384);
        require(ui.page() == FrontendPage::create, "scaled click did not open new game");
        for (std::size_t i = 0; i < 4; ++i)
            ui.key(FrontendKey::backspace);
        for (const auto c : std::string("Alice-7"))
            ui.text(c);
        click(ui, "class-2");
        click(ui, "create");
        const auto request = ui.take_request();
        require(request && request->class_guid == 3 && request->name == "Alice-7" &&
                    request->command == FrontendCommand::create,
                "selected hero/name lost");
        require(!ui.take_request(), "frontend command duplicated");
        ui.entered_game();
        ui.pause();
        require(ui.page() == FrontendPage::pause, "pause not reached");
        click(ui, "save-menu");
        auto save = ui.take_request();
        require(save && save->command == FrontendCommand::save_and_menu,
                "save-and-menu command wrong");
        ui.error("DISK FULL");
        require(ui.page() == FrontendPage::pause, "failed save left gameplay");
        click(ui, "save-menu");
        save = ui.take_request();
        ui.saved(save->command);
        require(ui.page() == FrontendPage::main, "successful save did not return to menu");
        std::vector<SaveSlotInfo> slots;
        for (int i = 0; i < 8; ++i) {
            SaveSlotInfo slot;
            slot.slot = "slot-" + std::to_string(i);
            slot.name = "Hero " + std::to_string(i);
            slot.class_guid = i % 3 + 1;
            if (i == 0)
                slot.error = "bad CRC";
            slots.push_back(slot);
        }
        ui.set_saves(slots);
        click(ui, "loads");
        require(ui.page() == FrontendPage::load, "load page absent");
        require(!button(ui, "load").enabled, "damaged slot can be loaded");
        click(ui, "slot-2");
        click(ui, "load");
        auto load = ui.take_request();
        require(load && load->slot == "slot-2", "selected slot not loaded");
        click(ui, "scroll-down");
        require(ui.page() == FrontendPage::load, "overridden ScrollDown exit callback executed");
        require(button(ui, "slot-5").enabled, "load list did not scroll");
        ui.key(FrontendKey::back);
        click(ui, "continue");
        load = ui.take_request();
        require(load && load->slot == "slot-1", "continue selected corrupted newest save");
        ui.error("class unavailable");
        ui.show_main();
        static_cast<void>(ui.frame(1024, 768));
        ui.key(FrontendKey::accept);
        require(ui.page() == FrontendPage::create, "keyboard menu entry failed");
        for (int i = 0; i < 50; ++i)
            ui.text('x');
        require(ui.character_name().size() == 32, "name input unbounded");
        ui.key(FrontendKey::back);
        click(ui, "exit");
        require(ui.page() == FrontendPage::quit, "exit command failed");
        std::cout << "frontend: " << checks
                  << " assertions; authored CEGUI/PNG fixture, no original skin equivalence\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
