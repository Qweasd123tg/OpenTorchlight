#pragma once

#include "torchlight/animation_manifest.hpp"

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace torchlight {

class AnimationEventPlaybackError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct AnimationEventOccurrence {
    std::uint64_t execution_id = 0;
    std::string source_clip;
    std::size_t key_index = 0;
    AnimationEventKey key;
    float clip_time_seconds = 0.0F;
    // Inferred ownership guard: disambiguates controllers/floors reusing numeric IDs.
    std::uint64_t playback_generation = 0;
};

// Advances one non-looping animation and publishes every manifest key crossed
// during the current update. The frame list is retained for multiple consumers
// until the next advance instead of being destructively taken by the first one.
class AnimationEventPlayback {
public:
    void start(std::uint64_t execution_id, std::string_view source_clip,
               float duration_seconds, float playback_speed,
               const std::vector<AnimationEventKey>& keys);
    void advance(float elapsed_seconds);
    void stop() noexcept;

    [[nodiscard]] bool active() const noexcept { return active_; }
    [[nodiscard]] bool finished() const noexcept { return finished_; }
    [[nodiscard]] std::uint64_t execution_id() const noexcept {
        return execution_id_;
    }
    [[nodiscard]] float time_seconds() const noexcept { return time_seconds_; }
    [[nodiscard]] float duration_seconds() const noexcept {
        return duration_seconds_;
    }
    [[nodiscard]] float playback_speed() const noexcept {
        return playback_speed_;
    }
    [[nodiscard]] const std::vector<AnimationEventOccurrence>& frame_events()
        const noexcept {
        return frame_events_;
    }

private:
    std::uint64_t execution_id_ = 0;
    std::uint64_t playback_generation_ = 0;
    std::string source_clip_;
    std::vector<AnimationEventKey> keys_;
    std::vector<bool> emitted_;
    std::vector<AnimationEventOccurrence> frame_events_;
    float time_seconds_ = 0.0F;
    float duration_seconds_ = 0.0F;
    float playback_speed_ = 1.0F;
    bool active_ = false;
    bool finished_ = false;
};

} // namespace torchlight
