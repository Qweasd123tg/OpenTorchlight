#include "torchlight/ui_function_bindings.hpp"

namespace torchlight {
namespace {
// KLayoutFunctionNames @0x14b7dc0; initializer 0xa850bd..0xa85a5b,
// read-only extraction: tools/audit_original.py::recover_commands.
// ELF SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
constexpr UiFunctionNames kNames{{
    "GUIEXITGAME",
    "GUIEXITAPPLICATION",
    "GUINEWGAME",
    "GUICONTINUEGAME",
    "GUINEWGAMEMENU",
    "GUICONTINUEGAMEMENU",
    "GUICLOSEMENU",
    "GUIBACK",
    "GUIDECLINE",
    "GUIACCEPT",
    "GUIOK",
    "GUIPAUSE",
    "GUISCROLLUP",
    "GUISCROLLDOWN",
    "GUISELECT1",
    "GUISELECT2",
    "GUISELECT3",
    "GUISELECT4",
    "GUISELECT5",
    "GUISELECT6",
    "GUISELECT7",
    "GUISELECT8",
    "GUISELECT9",
    "GUISELECT10",
    "GUISELECT11",
    "GUISELECT12",
    "GUISELECT13",
    "GUISELECT14",
    "GUISELECT15",
    "GUISELECT16",
    "GUISELECT17",
    "GUISELECT18",
    "GUISELECT19",
    "GUISELECT20",
    "GUISELECT21",
    "GUISELECT22",
    "GUISELECT23",
    "GUISELECT24",
    "GUISELECT25",
    "GUISELECT26",
    "GUISELECT27",
    "GUISELECT28",
    "GUISELECT29",
    "GUISELECT30",
    "GUISELECT31",
    "GUISELECT32",
    "GUISELECT33",
    "GUISELECT34",
    "GUISELECT35",
    "GUISELECT36",
    "GUISELECT37",
    "GUISELECT38",
    "GUISELECT39",
    "GUISELECT40",
    "GUISELECT41",
    "GUISELECT42",
    "GUISELECT43",
    "GUISELECT44",
    "GUISELECT45",
    "GUISELECT46",
    "GUISELECT47",
    "GUISELECT48",
    "GUISELECT49",
    "GUISELECT50",
    "GUISELECTA",
    "GUISELECTB",
    "GUISELECTC",
    "GUISELECTD",
    "GUIFEEDPET",
    "GUIPETPASSIVE",
    "GUIPETAGGRESSIVE",
    "GUIPETDEFENSIVE",
    "GUITOGGLEINVENTORY",
    "GUITOGGLEQUESTS",
    "GUITOGGLESTATS",
    "GUITOGGLESKILLS",
    "GUITOGGLEPERKS",
    "GUITOGGLEJOURNAL",
    "GUITOGGLEPET",
    "GUITOGGLEAUTOMAP",
    "GUITOGGLEOPTIONS",
    "GUITOGGLEITEMNAMES",
    "GUIAUTOMAPZOOMIN",
    "GUIAUTOMAPZOOMOUT",
    "GUILEVELUP",
    "GUISTATSUP",
    "GUISKILLUP",
    "GUIPET1",
    "GUIPET2",
    "GUIPET3",
    "GUIDELETE1",
    "GUIDELETE2",
    "GUIDELETE3",
    "GUIDELETE4",
    "GUISETTINGSMENU",
    "GUIPETSELL",
    "NONE",
}};
} // namespace

const UiFunctionNames &ui_function_names() noexcept { return kNames; }

std::string_view ui_function_name(UiLayoutFunction value) noexcept {
    const int index = static_cast<int>(value);
    return index >= 0 && index < static_cast<int>(kNames.size()) ? kNames[index] : std::string_view{};
}

void map_ui_functions(UiFunctionTree &tree, UiFunctionTree::Node root, const UiFunctionNames &names) {
    const auto count = tree.child_count(root);
    for (std::size_t i = 0; i < count; ++i)
        map_ui_functions(tree, tree.child(root, i), names);
    // Original recursion is outside the property try region (LSDA 0x119c4d0).
    try {
        if (!tree.has_click_property(root) || tree.click_property(root).empty()) {
            tree.set_function(root, UiLayoutFunction::none);
            return;
        }
        // The second read is intentional: original calls getProperty twice.
        auto command = tree.click_property(root);
        if (const auto nul = command.find('\0'); nul != std::string::npos)
            command.resize(nul); // std::string(char const*) after build_utf8_buff
        for (char &byte : command)
            if (byte >= 'a' && byte <= 'z')
                byte = static_cast<char>(byte - 'a' + 'A');
        for (std::size_t i = 0; i < names.size(); ++i)
            if (command == names[i])
                tree.set_function(root, static_cast<UiLayoutFunction>(i));
    } catch (...) {
        // Catch-all type entry = 0 at LSDA 0x119c524; native pad a9833c.
        tree.set_function(root, UiLayoutFunction::none);
    }
}
} // namespace torchlight
