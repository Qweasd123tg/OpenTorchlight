#include "torchlight/scene_math.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr float kDegreesToRadians = 0.01745329251994329577F;
float dot(const Vector3& a, const Vector3& b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
Vector3 cross(const Vector3& a, const Vector3& b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}
Vector3 normalized(Vector3 v) {
    const float length = std::sqrt(dot(v, v));
    if (!std::isfinite(length) || length <= 0) {
        throw std::invalid_argument("Camera basis is degenerate");
    }
    for (auto& value : v) value /= length;
    return v;
}
bool finite(const Vector3& v) {
    return std::all_of(v.begin(), v.end(), [](float f) { return std::isfinite(f); });
}
} // namespace

Matrix3 yaw_rotation(float degrees) {
    const float c = std::cos(degrees * kDegreesToRadians);
    const float s = std::sin(degrees * kDegreesToRadians);
    return {c, 0, s, 0, 1, 0, -s, 0, c};
}

Matrix3 quaternion_rotation(const std::array<float, 4>& quaternion) {
    const float length = std::sqrt(
        quaternion[0] * quaternion[0] + quaternion[1] * quaternion[1] +
        quaternion[2] * quaternion[2] + quaternion[3] * quaternion[3]);
    if (!std::isfinite(length) || length <= 0.000001F) {
        throw std::invalid_argument("Quaternion rotation is invalid");
    }
    const float w = quaternion[0] / length;
    const float x = quaternion[1] / length;
    const float y = quaternion[2] / length;
    const float z = quaternion[3] / length;
    return {1.0F - 2.0F * (y * y + z * z), 2.0F * (x * y - z * w),
            2.0F * (x * z + y * w), 2.0F * (x * y + z * w),
            1.0F - 2.0F * (x * x + z * z), 2.0F * (y * z - x * w),
            2.0F * (x * z - y * w), 2.0F * (y * z + x * w),
            1.0F - 2.0F * (x * x + y * y)};
}

Matrix3 compose_rotation(const Matrix3& parent, const Matrix3& local) {
    Matrix3 result{};
    for (unsigned r = 0; r < 3; ++r)
        for (unsigned c = 0; c < 3; ++c)
            for (unsigned k = 0; k < 3; ++k)
                result[r * 3 + c] += parent[r * 3 + k] * local[k * 3 + c];
    return result;
}

Vector3 rotate_vector(const Matrix3& rotation, const Vector3& vector) {
    Vector3 result{};
    for (unsigned r = 0; r < 3; ++r)
        for (unsigned c = 0; c < 3; ++c)
            result[r] += rotation[r * 3 + c] * vector[c];
    return result;
}

Vector3 inverse_rotate_vector(const Matrix3& rotation, const Vector3& vector) {
    Vector3 result{};
    for (unsigned r = 0; r < 3; ++r)
        for (unsigned c = 0; c < 3; ++c)
            result[r] += rotation[c * 3 + r] * vector[c];
    return result;
}

Vector3 transform_point(const Vector3& position, const Matrix3& rotation,
                        const Vector3& scale, const Vector3& point) {
    auto result = rotate_vector(rotation, {point[0] * scale[0], point[1] * scale[1],
                                          point[2] * scale[2]});
    for (unsigned axis = 0; axis < 3; ++axis) result[axis] += position[axis];
    return result;
}

GameCameraPose game_camera_pose(const Vector3& target, float dolly, bool netbook_mode,
                                float distance_multiplier) {
    if (!finite(target) || !std::isfinite(dolly) || dolly <= 0 ||
        !std::isfinite(distance_multiplier) || distance_multiplier <= 14.0F / 28.5F) {
        throw std::invalid_argument("Invalid game camera parameters");
    }
    const float fraction = (dolly - 14.0F) / (28.5F * distance_multiplier - 14.0F);
    const float vertical = (1.0F + (1.0F - fraction) * -0.5F) * 0.75F;
    const float mode_scale = netbook_mode ? 0.8F : 1.0F;
    GameCameraPose pose{{target[0] + 0.5F * dolly * mode_scale,
                          target[1] + vertical * dolly * mode_scale,
                          target[2] - 0.5F * dolly * mode_scale}, target};
    const Vector3 delta{pose.position[0] - target[0], pose.position[1] - target[1],
                         pose.position[2] - target[2]};
    const float distance = std::sqrt(dot(delta, delta));
    const float minimum = 14.0F * distance_multiplier;
    if (distance < minimum) pose.target[1] += 1.0F - distance / minimum;
    pose.position[1] = std::max(pose.target[1] + 0.1F, pose.position[1]);
    return pose;
}

CameraProjection make_camera_projection(const Vector3& position, const Vector3& target,
                                        float aspect, float fov_degrees,
                                        float near_clip, float far_clip) {
    if (!finite(position) || !finite(target) || !std::isfinite(aspect) || aspect <= 0 ||
        !std::isfinite(fov_degrees) || fov_degrees <= 0 || fov_degrees >= 180 ||
        !std::isfinite(near_clip) || near_clip <= 0 ||
        !std::isfinite(far_clip) || far_clip <= near_clip) {
        throw std::invalid_argument("Invalid camera projection");
    }
    CameraProjection camera;
    camera.position = position;
    camera.forward = normalized({target[0] - position[0], target[1] - position[1],
                                 target[2] - position[2]});
    camera.right = normalized(cross(camera.forward, {0, 1, 0}));
    camera.up = cross(camera.right, camera.forward);
    camera.tangent_half_fov = std::tan(fov_degrees * kDegreesToRadians * 0.5F);
    camera.aspect = aspect;
    camera.near_clip = near_clip;
    camera.far_clip = far_clip;
    const auto& r = camera.right;
    const auto& u = camera.up;
    const auto& f = camera.forward;
    camera.view = {r[0], r[1], r[2], -dot(r, position),
                   u[0], u[1], u[2], -dot(u, position),
                   -f[0], -f[1], -f[2], dot(f, position), 0, 0, 0, 1};
    const float reciprocal = 1.0F / camera.tangent_half_fov;
    const float depth = far_clip - near_clip;
    camera.projection = {reciprocal / aspect, 0, 0, 0, 0, reciprocal, 0, 0,
                          0, 0, -(far_clip + near_clip) / depth,
                          -2.0F * far_clip * near_clip / depth, 0, 0, -1, 0};
    return camera;
}

Vector3 CameraProjection::project_ndc(const Vector3& world) const {
    const Vector3 relative{world[0] - position[0], world[1] - position[1],
                           world[2] - position[2]};
    const float depth = dot(relative, forward);
    if (!finite(world) || !std::isfinite(depth) || depth <= 0) {
        throw std::invalid_argument("Point is not in front of the camera");
    }
    return {dot(relative, right) / (depth * tangent_half_fov * aspect),
            dot(relative, up) / (depth * tangent_half_fov),
            (far_clip + near_clip) / (far_clip - near_clip) -
                2.0F * far_clip * near_clip / ((far_clip - near_clip) * depth)};
}

Vector3 CameraProjection::ground_at_ndc(float x, float y, float height) const {
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(height)) {
        throw std::invalid_argument("Invalid camera ray");
    }
    Vector3 direction{};
    for (unsigned axis = 0; axis < 3; ++axis)
        direction[axis] = forward[axis] + right[axis] * x * tangent_half_fov * aspect +
                          up[axis] * y * tangent_half_fov;
    if (std::abs(direction[1]) < 0.00001F) {
        throw std::invalid_argument("Camera ray is parallel to the ground");
    }
    const float distance = (height - position[1]) / direction[1];
    if (distance < 0) throw std::invalid_argument("Ground is behind the camera ray");
    return {position[0] + direction[0] * distance, height,
            position[2] + direction[2] * distance};
}
} // namespace torchlight
