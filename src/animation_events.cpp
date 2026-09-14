#include "torchlight/animation_events.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {

void AnimationEventPlayback::start(
    std::uint64_t execution_id, std::string_view source_clip,
    float duration_seconds, float playback_speed,
    const std::vector<AnimationEventKey>& keys) {
    if (execution_id == 0) {
        throw AnimationEventPlaybackError(
            "Animation event playback requires a non-zero execution ID");
    }
    if (!std::isfinite(duration_seconds) || duration_seconds < 0.0F ||
        !std::isfinite(playback_speed) || playback_speed <= 0.0F) {
        throw AnimationEventPlaybackError(
            "Animation event playback has an invalid duration or speed");
    }
    for (const auto& key : keys) {
        if (!std::isfinite(key.frame) || key.frame < 0.0F) {
            throw AnimationEventPlaybackError(
                "Animation event playback has an invalid key frame");
        }
    }

    execution_id_ = execution_id;
    source_clip_ = source_clip;
    keys_ = keys;
    emitted_.assign(keys_.size(), false);
    frame_events_.clear();
    time_seconds_ = 0.0F;
    duration_seconds_ = duration_seconds;
    playback_speed_ = playback_speed;
    active_ = duration_seconds_ > 0.0F;
    finished_ = !active_;
}

void AnimationEventPlayback::advance(float elapsed_seconds) {
    frame_events_.clear();
    if (!std::isfinite(elapsed_seconds) || elapsed_seconds < 0.0F) {
        throw AnimationEventPlaybackError(
            "Animation event playback requires a finite non-negative time step");
    }
    if (!active_ || elapsed_seconds == 0.0F) {
        return;
    }

    const float previous_time = time_seconds_;
    time_seconds_ = std::min(
        duration_seconds_, time_seconds_ + elapsed_seconds * playback_speed_);
    for (std::size_t index = 0; index < keys_.size(); ++index) {
        const float key_time = keys_[index].frame / 30.0F;
        if (!emitted_[index] && key_time >= previous_time &&
            key_time <= time_seconds_) {
            emitted_[index] = true;
            frame_events_.push_back({execution_id_, source_clip_, index,
                                     keys_[index], key_time});
        }
    }
    if (time_seconds_ >= duration_seconds_) {
        active_ = false;
        finished_ = true;
    }
}

void AnimationEventPlayback::stop() noexcept {
    execution_id_ = 0;
    source_clip_.clear();
    keys_.clear();
    emitted_.clear();
    frame_events_.clear();
    time_seconds_ = 0.0F;
    duration_seconds_ = 0.0F;
    playback_speed_ = 1.0F;
    active_ = false;
    finished_ = false;
}

} // namespace torchlight
