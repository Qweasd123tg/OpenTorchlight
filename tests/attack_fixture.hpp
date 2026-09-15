#pragma once
#include "torchlight/scene_animation.hpp"
#include "torchlight/attack_action.hpp"
#include <memory>
#include <string>

namespace test_fixture {
// Authored event data, not an original-game clip. One HIT at the terminal key.
inline torchlight::AttackClip clip(std::string prefix, float duration = 1.0F) {
    auto result = std::make_shared<torchlight::ModelAnimationClip>();
    result->animation_name = prefix + "_SYNTHETIC";
    result->skeleton_path = "synthetic/" + result->animation_name + ".skeleton";
    result->duration = duration;
    torchlight::AnimationEventKey hit; hit.name = "HIT"; hit.frame = duration * 30.0F;
    result->event_keys.push_back(hit);
    return result;
}
inline torchlight::AttackClipResolver clips(float duration = 1.0F) {
    return [duration](std::string_view, std::string_view prefix) {
        return torchlight::AttackClips{clip(std::string(prefix), duration)};
    };
}
}
