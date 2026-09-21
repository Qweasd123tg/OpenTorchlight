#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_skin.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {

unsigned checks = 0;
void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
void equal(float actual, float expected, const char* message) {
    require(std::abs(actual - expected) < 0.001F, message);
}
UiResolvedWidget widget(std::string name, std::string type, UiRect rect) {
    UiResolvedWidget result;
    result.name = std::move(name);
    result.type = std::move(type);
    result.rect = rect;
    result.clip = {0, 0, 800, 600};
    result.has_clip = true;
    return result;
}

} // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 2, "usage: ui_combobox_skin_test original-pak.zip");
        PakArchive archive(argv[1]);
        UiResources resources(archive);
        auto& skin = resources.skin();

        auto combo = widget("combo", "GuiLook/Combobox", {20, 30, 240, 120});
        auto frame = skin.compile(resources, combo, {}, 800, 600);
        require(frame.handled && frame.diagnostics.empty() && frame.draws.empty() &&
                    frame.states == std::vector<std::string>{"Enabled"},
                "Falagard/Default combobox parent manufactured imagery or rejected real autochildren");

        auto edit = widget("combo__auto_editbox__", "GuiLook/ComboEditbox",
                           {20, 30, 210, 30});
        edit.text = "1920 x 1080";
        edit.properties["ReadOnly"] = "True";
        frame = skin.compile(resources, edit, {}, 800, 600);
        require(frame.handled && frame.diagnostics.empty() &&
                    frame.states == std::vector<std::string>{"ReadOnly"} &&
                    frame.draws.size() == 3 &&
                    frame.draws[0].kind == UiSkinDraw::Kind::image &&
                    frame.draws[1].kind == UiSkinDraw::Kind::image &&
                    frame.draws[2].kind == UiSkinDraw::Kind::text,
                "read-only Falagard/Editbox state or image-before-text order differs");
        const auto& text = frame.draws.back();
        require(text.text == "1920 x 1080" && text.font == "Serif" &&
                    text.text_style.vertical == UiTextVertical::centre,
                "ComboEditbox did not consume runtime Text/default font");
        equal(text.destination.x, 30.0F, "ComboEditbox TextArea left differs");
        equal(text.destination.y, 35.0F, "ComboEditbox TextArea top differs");
        equal(text.destination.width, 185.0F, "ComboEditbox TextArea width differs");
        equal(text.destination.height, 20.0F, "ComboEditbox TextArea height differs");

        auto list = widget("combo__auto_droplist__", "GuiLook/ComboDropList",
                           {20, 60, 240, 90});
        frame = skin.compile(resources, list, {}, 800, 600);
        require(frame.handled && frame.diagnostics.empty() &&
                    frame.states == std::vector<std::string>{"Enabled"} &&
                    frame.draws.size() == 9,
                "ComboDropList frame or real scrollbar-autochild admission differs");
        const auto item_area = skin.named_area(resources, list, "ItemRenderingArea", 800, 600);
        require(item_area && item_area->x > list.rect.x && item_area->y > list.rect.y &&
                    item_area->width < list.rect.width && item_area->height < list.rect.height,
                "ComboDropList ItemRenderingArea did not consume edge resources");

        const auto row = skin.combobox_text_item("Shadows 512",
            {item_area->x, item_area->y, item_area->width, 18}, list.clip, 0.5F);
        require(row.kind == UiSkinDraw::Kind::text && row.font == "Serif" &&
                    row.section == "ListboxTextItem" &&
                    row.text_style.vertical == UiTextVertical::centre &&
                    row.colours[0][0] == 1.0F && row.colours[0][1] == 1.0F &&
                    row.colours[0][2] == 1.0F && row.colours[0][3] == 0.5F,
                "ListboxTextItem white text/alpha consumer differs");
        require(row.texture.empty(),
                "null ListboxTextItem selection brush became invented highlight imagery");

        std::cout << "PASS " << checks
                  << " combobox skin checks; Falagard edit/list resource boundary\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL " << error.what() << '\n';
        return 1;
    }
}
