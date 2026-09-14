#include "torchlight/animation_events.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main() {
    try {
        std::vector<torchlight::AnimationEventKey> keys(3);
        keys[0].name = "HIT";
        keys[0].frame = 6.0F;
        keys[1].name = "FOOTSTEP";
        keys[1].frame = 12.0F;
        keys[2].name = "HIT";
        keys[2].frame = 18.0F;

        torchlight::AnimationEventPlayback playback;
        playback.start(17, "attack/test", 1.2F, 0.5F, keys);
        playback.advance(0.39F);
        require(playback.frame_events().empty(),
                "animation event fired before its speed-scaled time");
        playback.advance(0.02F);
        require(playback.frame_events().size() == 1 &&
                    playback.frame_events()[0].execution_id == 17 &&
                    playback.frame_events()[0].source_clip == "attack/test" &&
                    playback.frame_events()[0].key.name == "HIT" &&
                    playback.frame_events()[0].key_index == 0 &&
                    std::fabs(playback.frame_events()[0].clip_time_seconds - 0.2F) <
                        0.0001F,
                "first HIT lost its execution, source clip, or scaled timing");
        const auto* retained_events = &playback.frame_events();
        require(retained_events->size() == 1 && playback.frame_events().size() == 1,
                "reading animation events consumed the shared frame list");

        playback.advance(0.38F);
        require(playback.frame_events().empty(),
                "FOOTSTEP fired before its speed-scaled time");
        playback.advance(0.02F);
        require(playback.frame_events().size() == 1 &&
                    playback.frame_events()[0].key.name == "FOOTSTEP",
                "non-HIT event was not retained for another consumer");
        playback.advance(0.38F);
        require(playback.frame_events().empty(),
                "second HIT fired before its speed-scaled time");
        playback.advance(0.02F);
        require(playback.frame_events().size() == 1 &&
                    playback.frame_events()[0].key.name == "HIT" &&
                    playback.frame_events()[0].key_index == 2,
                "second HIT did not fire at 1.2 wall seconds");
        playback.advance(1.2F);
        require(playback.frame_events().empty() && playback.finished() &&
                    !playback.active() &&
                    std::fabs(playback.time_seconds() - 1.2F) < 0.0001F,
                "animation playback did not finish at duration divided by speed");

        std::vector<torchlight::AnimationEventKey> simultaneous(2);
        simultaneous[0].name = "HIT";
        simultaneous[0].frame = 3.0F;
        simultaneous[1].name = "HIT";
        simultaneous[1].frame = 5.0F;
        playback.start(18, "attack/multi", 0.5F, 1.0F, simultaneous);
        playback.advance(0.2F);
        require(playback.frame_events().size() == 2 &&
                    playback.frame_events()[0].key_index == 0 &&
                    playback.frame_events()[1].key_index == 1,
                "one update lost or reordered multiple HIT events");
        playback.advance(0.0F);
        require(playback.frame_events().empty(),
                "zero-time update duplicated previously emitted events");

        std::cout << "PASS: retained ordered animation events with clip timing\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
