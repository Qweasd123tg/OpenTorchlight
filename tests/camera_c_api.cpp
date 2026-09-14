#include "torchlight/scene_math.hpp"

#include <algorithm>

extern "C" bool recovered_game_camera(const float* target, float dolly, bool netbook,
                                       float multiplier, float* position, float* look_at) {
    try {
        const auto pose = torchlight::game_camera_pose(
            {target[0], target[1], target[2]}, dolly, netbook, multiplier);
        std::copy(pose.position.begin(), pose.position.end(), position);
        std::copy(pose.target.begin(), pose.target.end(), look_at);
        return true;
    } catch (...) { return false; }
}

extern "C" bool recovered_camera_projection(const float* position, const float* target,
    float aspect, float fov, float near_clip, float far_clip, float* view, float* projection) {
    try {
        const auto camera = torchlight::make_camera_projection(
            {position[0], position[1], position[2]}, {target[0], target[1], target[2]},
            aspect, fov, near_clip, far_clip);
        std::copy(camera.view.begin(), camera.view.end(), view);
        std::copy(camera.projection.begin(), camera.projection.end(), projection);
        return true;
    } catch (...) { return false; }
}

extern "C" bool recovered_camera_ground(const float* position, const float* target,
    float aspect, float fov, float x, float y, float height, float* output) {
    try {
        const auto point = torchlight::make_camera_projection(
            {position[0], position[1], position[2]}, {target[0], target[1], target[2]},
            aspect, fov).ground_at_ndc(x, y, height);
        std::copy(point.begin(), point.end(), output);
        return true;
    } catch (...) { return false; }
}
