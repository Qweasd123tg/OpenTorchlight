#pragma once
#include <array>
#include <cstddef>
#include <string>
#include <string_view>

namespace torchlight {
// original-code: CGameUI::mapToFunctions @0xa980e0; see
// research/ui-function-bindings.md. These are enum values, not CEGUI pointers.
// Select2..Select49 have the contiguous original values 15..62.
enum class UiLayoutFunction : int {
    exit_game = 0, exit_application = 1, new_game = 2, continue_game = 3,
    new_game_menu = 4, continue_game_menu = 5, close_menu = 6, back = 7,
    decline = 8, accept = 9, ok = 10, pause = 11, scroll_up = 12, scroll_down = 13,
    select1 = 14, select50 = 63, select_a = 64, select_b = 65, select_c = 66, select_d = 67,
    feed_pet = 68, pet_passive = 69, pet_aggressive = 70, pet_defensive = 71,
    toggle_inventory = 72, toggle_quests = 73, toggle_stats = 74, toggle_skills = 75,
    toggle_perks = 76, toggle_journal = 77, toggle_pet = 78, toggle_automap = 79,
    toggle_options = 80, toggle_item_names = 81, automap_zoom_in = 82, automap_zoom_out = 83,
    level_up = 84, stats_up = 85, skill_up = 86, pet1 = 87, pet2 = 88, pet3 = 89,
    delete1 = 90, delete2 = 91, delete3 = 92, delete4 = 93, settings_menu = 94,
    pet_sell = 95, none = 96
};
using UiFunctionNames = std::array<std::string_view, 97>;
[[nodiscard]] const UiFunctionNames &ui_function_names() noexcept;
[[nodiscard]] std::string_view ui_function_name(UiLayoutFunction value) noexcept;

// Narrow window-tree adapter, not a CEGUI replacement. Children and properties
// remain owned by the caller. set_function is a nonthrowing field write.
// Unknown nonempty properties do not call set_function at all: existing user
// data (including non-command data in a future runtime) must be preserved.
class UiFunctionTree {
public:
    using Node = std::size_t;
    virtual ~UiFunctionTree() = default;
    [[nodiscard]] virtual std::size_t child_count(Node) const = 0;
    [[nodiscard]] virtual Node child(Node, std::size_t) const = 0;
    [[nodiscard]] virtual bool has_click_property(Node) const = 0;
    [[nodiscard]] virtual std::string click_property(Node) const = 0;
    virtual void set_function(Node, UiLayoutFunction) noexcept = 0;
};

// Child-first order; property failures become NONE only on the current node.
// C-locale byte casing of ASCII command names; no Unicode/other-locale claim.
// The optional table argument permits testing the original last-match rule;
// production always uses the pinned 97 names.
void map_ui_functions(UiFunctionTree &tree, UiFunctionTree::Node root,
                      const UiFunctionNames &names = ui_function_names());
} // namespace torchlight
