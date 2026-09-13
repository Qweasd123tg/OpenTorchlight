#pragma once

#include "torchlight/collision_scene.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace torchlight {

struct NavigationCell {
    float height = 0.0F;
    bool walkable = false;
};

class NavigationGrid {
public:
    static NavigationGrid build(const CollisionScene& collision, float cell_size = 1.0F,
                                float actor_radius = 0.45F);

    [[nodiscard]] std::size_t width() const noexcept { return width_; }
    [[nodiscard]] std::size_t height() const noexcept { return height_; }
    [[nodiscard]] float cell_size() const noexcept { return cell_size_; }
    [[nodiscard]] std::size_t walkable_cell_count() const noexcept;
    [[nodiscard]] const NavigationCell& cell(std::size_t x, std::size_t z) const;
    [[nodiscard]] std::array<float, 3> cell_center(std::size_t x, std::size_t z) const;
    [[nodiscard]] std::optional<std::array<std::size_t, 2>> nearest_walkable(
        const std::array<float, 3>& position, std::size_t maximum_radius = 16) const;
    [[nodiscard]] std::vector<std::array<float, 3>> find_path(
        const std::array<float, 3>& start, const std::array<float, 3>& destination,
        float maximum_step_height = 1.5F) const;

private:
    float origin_x_ = 0.0F;
    float origin_z_ = 0.0F;
    float cell_size_ = 1.0F;
    std::size_t width_ = 0;
    std::size_t height_ = 0;
    std::vector<NavigationCell> cells_;
};

} // namespace torchlight
