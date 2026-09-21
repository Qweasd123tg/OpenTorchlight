#include "torchlight/ui_layout.hpp"
#include <iostream>
#include <stdexcept>
#include <string_view>
using namespace torchlight;
namespace {
void require(bool value, const char *message) {
    if (!value) throw std::runtime_error(message);
}
UiLayout parse(std::string_view xml) { return UiLayout::parse({xml.begin(), xml.end()}); }
void value(const char *properties, const char *expected) {
    const auto document = parse(std::string("<GUILayout><Window Name='root'>") + properties + "</Window></GUILayout>");
    require(document.widgets()[0].property("Text") == expected, "Property value contract differs");
    require(document.resolve(1024,768)[0].text == expected, "resolve lost the parsed value");
}
}
int main(int argc, char **argv) { try {
    // Reviewed elementPropertyStart/text/End contract, independent of renderer/input.
    value("<Property Name='Text' Value='attribute'/>", "attribute");
    value("<Property Name='Text'>body</Property>", "body");
    value("<Property Name='Text' Value=''>body</Property>", "body");
    value("<Property Name='Text' Value='attribute'>ignored body</Property>", "attribute");
    value("<Property Name='Text' Value=' '/>", " ");
    value("<Property Name='Text'> first \n last </Property>", " first \n last ");
    value("<Property Name='Text'>A &amp; B\r\n<!--split SAX text-->\rC &#x3a0;&#13;</Property>",
          "A & B\n\nC \xCE\xA0\r");
    value("<Property Name='Text' Value='old'/><Property Name='Text'>new</Property>", "new");
    value("<Property Name='Text'>old</Property><Property Name='Text'/>", "");
    value("<Property Name='Text' Value='old'/><Property name='Text'>ignored</Property>", "old");
    const auto commands = parse("<GUILayout><Window Name='root'><Property Name='onClick' Value=''>guiSelectC</Property></Window></GUILayout>");
    require(commands.widgets()[0].layout_function.has_value(), "body callback was not bound");
    require(ui_function_name(*commands.widgets()[0].layout_function)=="GUISELECTC", "body callback bound incorrectly");
    if (argc == 2) {
        PakArchive pak(argv[1]); UiResources resources(pak);
        const auto *layout=resources.layout("media/UI/mainmenuframe.layout");
        require(layout!=nullptr,"main menu layout absent");
        bool found=false;
        for (const auto &w : layout->widgets()) if (w.name=="CreditsB") {
            const auto text=w.property("Text");
            require(text.find("|cFFFFBA00Linux Platform\nOutOfOrder Games|u")!=text.npos,
                    "original Property body lost its header");
            require(text.find("Edward Rudd\nhttp://www.outoforder.cc/")!=text.npos,
                    "original Property body lost its content");
            found=true;
        }
        require(found,"CreditsB not found");
    } else require(argc==1,"usage: ui_layout_property_test [external pak.zip]");
    std::cout << "PASS: Property Value/body selection, text fragments/entities, resolve and binding consumers\n";
    return 0;
} catch(const std::exception &e) { std::cerr << e.what() << '\n'; return 1; } }
