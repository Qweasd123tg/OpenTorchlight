#pragma once

#include <array>

namespace torchlight {

using Vector3 = std::array<float, 3>;
// Row-major matrices acting on column vectors, as in OGRE 1.6.
using Matrix3 = std::array<float, 9>;
using Matrix4 = std::array<float, 16>;
inline constexpr Matrix3 kIdentityRotation{1, 0, 0, 0, 1, 0, 0, 0, 1};

[[nodiscard]] Matrix3 yaw_rotation(float degrees);
[[nodiscard]] Matrix3 quaternion_rotation(const std::array<float, 4>& quaternion);
[[nodiscard]] Matrix3 compose_rotation(const Matrix3& parent, const Matrix3& local);
[[nodiscard]] Vector3 rotate_vector(const Matrix3& rotation, const Vector3& vector);
[[nodiscard]] Vector3 inverse_rotate_vector(const Matrix3& rotation, const Vector3& vector);
[[nodiscard]] Vector3 transform_point(const Vector3& position, const Matrix3& rotation,
                                    const Vector3& scale, const Vector3& point);

struct CameraProjection {
    Vector3 position{};
    Vector3 right{};
    Vector3 up{};
    Vector3 forward{};
    float tangent_half_fov = 0;
    float aspect = 1;
    float near_clip = 0.1F;
    float far_clip = 500;
    Matrix4 view{};
    Matrix4 projection{};

    [[nodiscard]] Vector3 project_ndc(const Vector3& world) const;
    [[nodiscard]] Vector3 ground_at_ndc(float x, float y, float height) const;
};

[[nodiscard]] CameraProjection make_camera_projection(
    const Vector3& position, const Vector3& target, float aspect,
    float fov_degrees = 45, float near_clip = 0.1F, float far_clip = 500);

// Stationary normal gameplay branch of CCameraControl::updateGameCamera.
// Dolly is the controller parameter, not the Euclidean distance to the target.
// Shake, collision, cinematic/pause states and temporal smoothing are separate.
struct GameCameraPose { Vector3 position; Vector3 target; };
[[nodiscard]] GameCameraPose game_camera_pose(const Vector3& target, float dolly,
                                             bool netbook_mode = true,
                                             float distance_multiplier = 1);

} // namespace torchlight
