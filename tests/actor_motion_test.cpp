#include "torchlight/actor_motion.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}
}

int main() {
    try {
        torchlight::ActorMotion motion({1.0F, 3.0F, 2.0F}, 5.0F);
        motion.set_destination(4.0F, 6.0F);
        motion.advance(0.5F);
        require(motion.moving(), "actor reached a distant destination too early");
        require(std::abs(motion.position()[0] - 2.5F) < 0.00001F &&
                    std::abs(motion.position()[2] - 4.0F) < 0.00001F,
                "actor did not advance at its configured speed");
        require(motion.position()[1] == 3.0F, "horizontal motion changed actor height");
        motion.advance(1.0F);
        require(!motion.moving() && motion.position()[0] == 4.0F &&
                    motion.position()[2] == 6.0F,
                "actor did not stop exactly at the destination");
        motion.set_destination(10.0F, 10.0F);
        motion.advance(-1.0F);
        require(motion.position()[0] == 4.0F && motion.position()[2] == 6.0F,
                "negative frame time moved the actor");
        motion.stop();
        require(!motion.moving(), "actor did not stop");
        motion.set_destination({7.0F, 5.0F, 6.0F});
        motion.advance(0.3F);
        require(motion.position()[0] == 5.5F && motion.position()[1] == 4.0F,
                "actor did not interpolate waypoint height");
        std::cout << "PASS: actor motion advances by speed and stops at its destination\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
