#include "torchlight/ui_pause.hpp"
#include <array>
#include <iostream>
using namespace torchlight;
int main() {
    UiPauseInputs state; unsigned mask;
    while (std::cin >> state.forced >> state.ui_present >> state.console_open >> state.console_no_pause >>
                      state.modal_partial >> state.explicit_pause >> mask) {
        if (mask > 15) return 2;
        // Original isRight getters: Inventory/Quest/Skill=1, Merchant=0.
        const std::array<UiPausePanel,4> panels{{
            {true,(mask&1)!=0},{false,(mask&2)!=0},{true,(mask&4)!=0},{true,(mask&8)!=0}}};
        std::cout << ui_game_is_paused(state,panels.data(),panels.size()) << '\n';
    }
    return std::cin.eof()?0:2;
}
