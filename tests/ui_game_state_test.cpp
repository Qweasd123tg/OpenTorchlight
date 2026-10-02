#include "torchlight/ui_game_state.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

int main(int argc, char**) {
    using namespace torchlight;
    if (argc != 1) return 2;
    try {
        UiGameStateRequest owner;
        if (owner.state != 6 || owner.menu != 6 || owner.pending())
            throw std::runtime_error("UI request initializer drifted");
        for (const auto state : {UINT32_C(0), UINT32_C(2), UINT32_C(6), UINT32_C(0x80000000), UINT32_MAX})
            for (const auto menu : {UINT32_C(0), UINT32_C(1), UINT32_C(3), UINT32_C(6), UINT32_MAX}) {
                ui_request_game_state(owner, state, menu);
                if (owner.state != state || owner.menu != menu || owner.pending() != (state != 6))
                    throw std::runtime_error("generated request did not feed owned state");
                ui_clear_game_state_request(owner);
                if (owner.state != 6 || owner.menu != 6 || owner.pending())
                    throw std::runtime_error("generated clear left pending state");
            }
        std::cout << "UI state: initializer and 25 request/clear pairs; generated production bodies\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
