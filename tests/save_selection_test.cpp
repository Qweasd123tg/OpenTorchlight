#include "torchlight/save_store.hpp"
#include "torchlight/frontend.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
SaveSlotInfo slot(std::string id, float health, std::string error = {}) {
    SaveSlotInfo row;
    row.slot = std::move(id);
    row.health = health;
    row.error = std::move(error);
    return row;
}
float float_bits(std::uint32_t bits) {
    float value = 0;
    static_assert(sizeof(value) == sizeof(bits));
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}
void pure_selection() {
    const std::vector<SaveSlotInfo> empty;
    require(selected_continue_save(empty, 0) == nullptr, "empty save list continued");
    const std::vector<SaveSlotInfo> rows = {
        slot("dead", 0.0F), slot("live", 23.0F), slot("damaged", 7.0F, "CRC"),
        slot("negative", -2.0F), slot("nan", std::numeric_limits<float>::quiet_NaN())};
    require(selected_continue_save(rows, rows.size()) == nullptr, "past-end selection continued");
    require(selected_continue_save(rows, std::numeric_limits<std::size_t>::max()) == nullptr,
            "large selection continued");
    require(selected_continue_save(rows, 0) == nullptr, "dead selected row fell through to live row");
    require(selected_continue_save(rows, 1) == &rows[1], "selected live row identity lost");
    require(selected_continue_save(rows, 2) == nullptr, "unreadable OTC row continued");
    require(selected_continue_save(rows, 3) == nullptr, "negative health continued");
    require(selected_continue_save(rows, 4) == nullptr, "NaN health continued");
    auto tiny = slot("tiny", float_bits(1));
    require(selected_continue_save(std::vector<SaveSlotInfo>{tiny}, 0) != nullptr,
            "positive subnormal rejected");
}
void main_entry_selection() {
    const std::vector<SaveSlotInfo> rows = {
        slot("dead", 0), slot("visible-first", 12), slot("live", 23),
        slot("corrupt", 17, "CRC"), slot("negative", -2),
        slot("nan", std::numeric_limits<float>::quiet_NaN())};
    for (const auto source : {FrontendPage::load, FrontendPage::create}) {
        require(main_entry_save_selection(source, rows, 2, 1) == 1,
                "genuine Main entry lost current-scroll first row");
        require(main_entry_save_selection(source, rows, 2, 0) == 0,
                "Main entry did not force dead first row after live prior selection");
        for (const auto invalid : {std::size_t{0}, std::size_t{3}, std::size_t{4},
                                   std::size_t{5}, rows.size()})
            require(main_entry_save_selection(source, rows, invalid, 1) == invalid,
                    "non-continuable prior selection was replaced on Main entry");
        require(main_entry_save_selection(source, {}, 0, 1) == 0,
                "empty Main entry invented a selection");
        const auto missing = main_entry_save_selection(source, rows, 2, rows.size());
        require(missing == rows.size() && selected_continue_save(rows, missing) == nullptr,
                "out-of-range first visible row was clamped to a substitute save");
        const auto huge = main_entry_save_selection(source, rows, 2,
                                                   std::numeric_limits<std::size_t>::max());
        require(selected_continue_save(rows, huge) == nullptr,
                "large scroll reached an unrelated save");
    }
    for (const auto source : {FrontendPage::main, FrontendPage::settings,
                              FrontendPage::playing, FrontendPage::pause, FrontendPage::quit})
        require(main_entry_save_selection(source, rows, 2, 1) == 2,
                "same Main page, settings overlay or gameplay producer changed selection");
}
void frontend_selection(const char* pak_path) {
    PakArchive archive(pak_path);
    UiResources resources(archive);
    Frontend ui(resources, {{1, "Destroyer"}});
    auto live = slot("stable-live", 18.0F);
    auto other = slot("other-live", 30.0F);
    auto dead = slot("dead", 0.0F);
    auto corrupt = slot("corrupt", 90.0F, "CRC");

    ui.set_saves({other, live}, "stable-live");
    require(ui.selected_save() && ui.selected_save()->slot == "stable-live" &&
            ui.continue_save() == ui.selected_save(), "explicit slot identity not selected");
    ui.set_saves({live, other}, "stable-live");
    require(ui.selected_save() && ui.selected_save()->slot == "stable-live" &&
            ui.continue_save() == ui.selected_save(), "sort changed explicit slot identity");
    ui.set_saves({other, live}, "stable-live");
    ui.show_main();
    require(ui.continue_save() && ui.continue_save()->slot == "stable-live",
            "main page erased Continue identity");
    ui.entered_game();
    ui.saved(FrontendCommand::save_and_menu);
    require(ui.page() == FrontendPage::main && ui.continue_save() &&
            ui.continue_save()->slot == "stable-live", "Save & Menu lost selected identity");

    ui.set_saves({other, live}, "missing");
    require(ui.selected_save() == nullptr && ui.continue_save() == nullptr,
            "missing committed slot silently chose another character");
    ui.set_saves({other, dead}, "dead");
    require(ui.selected_save() && ui.selected_save()->slot == "dead" &&
            ui.continue_save() == nullptr, "dead selected row fell through to live row");
    ui.set_saves({corrupt, other}, "corrupt");
    require(ui.selected_save() && ui.selected_save()->slot == "corrupt" &&
            ui.continue_save() == nullptr, "damaged selected row continued");
}
} // namespace
int main(int argc, char** argv) {
    try {
        if (argc > 2) throw std::runtime_error("expected optional authored pak path");
        pure_selection();
        main_entry_selection();
        if (argc == 2) frontend_selection(argv[1]);
        std::cout << "save selection: " << checks << " assertions; no window/input/game process\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
