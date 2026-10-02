#include "torchlight/ui_game_state.hpp"
#include <cstdint>
#include <iostream>

int main() {
    torchlight::UiGameStateRequest owner;
    std::uint32_t state = 0, menu = 0;
    while (std::cin >> owner.state >> owner.menu >> state >> menu) {
        torchlight::ui_request_game_state(owner, state, menu);
        std::cout << owner.state << ' ' << owner.menu << ' ';
        torchlight::ui_clear_game_state_request(owner);
        std::cout << owner.state << ' ' << owner.menu << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}
