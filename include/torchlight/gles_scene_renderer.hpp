#pragma once

#include "torchlight/scene_geometry.hpp"

#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>

namespace torchlight {

class OgreMaterialCatalog;
class PakArchive;
struct OgreMeshPose;

struct GlesSceneRenderStats {
    std::size_t mesh_resources = 0;
    std::size_t instances = 0;
    std::size_t draw_batches = 0;
    std::size_t skipped_batches = 0;
    std::size_t texture_resources = 0;
    std::size_t textured_batches = 0;
    std::size_t fallback_batches = 0;
    std::uint64_t placed_triangles = 0;
};

class GlesSceneRenderer {
public:
    GlesSceneRenderer(const FixedSceneGeometry& geometry, const PakArchive& archive,
                      const OgreMaterialCatalog& materials);
    ~GlesSceneRenderer();

    GlesSceneRenderer(const GlesSceneRenderer&) = delete;
    GlesSceneRenderer& operator=(const GlesSceneRenderer&) = delete;

    void draw(int width, int height);
    void set_instance_position(std::size_t instance_index,
                               const std::array<float, 3>& position);
    void set_instance_angle(std::size_t instance_index, float angle_degrees);
    void set_instance_visible(std::size_t instance_index, bool visible);
    void set_mesh_pose(const OgreMeshPose& pose);
    void set_camera_target(const std::array<float, 3>& target,
                           float vertical_view_span = 80.0F);
    void clear_camera_target() noexcept;
    [[nodiscard]] std::array<float, 3> ground_position_at_pixel(
        int pixel_x, int pixel_y_from_bottom, int width, int height,
        float ground_height) const;
    [[nodiscard]] const GlesSceneRenderStats& stats() const noexcept;

private:
    class Implementation;
    std::unique_ptr<Implementation> implementation_;
};

} // namespace torchlight
