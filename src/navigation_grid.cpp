#include "torchlight/navigation_grid.hpp"

#include "torchlight/pathfinder_rules.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <stdexcept>

namespace torchlight {
namespace {

class NavigationError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct TriangleProjection {
    float normal_x = 0.0F;
    float normal_y = 0.0F;
    float normal_z = 0.0F;
    float length = 0.0F;
};

TriangleProjection triangle_normal(const CollisionTriangle& triangle) {
    const auto& a = triangle.vertices[0];
    const auto& b = triangle.vertices[1];
    const auto& c = triangle.vertices[2];
    const float ab_x = b[0] - a[0];
    const float ab_y = b[1] - a[1];
    const float ab_z = b[2] - a[2];
    const float ac_x = c[0] - a[0];
    const float ac_y = c[1] - a[1];
    const float ac_z = c[2] - a[2];
    TriangleProjection result;
    result.normal_x = ab_y * ac_z - ab_z * ac_y;
    result.normal_y = ab_z * ac_x - ab_x * ac_z;
    result.normal_z = ab_x * ac_y - ab_y * ac_x;
    result.length = std::sqrt(result.normal_x * result.normal_x +
                              result.normal_y * result.normal_y +
                              result.normal_z * result.normal_z);
    return result;
}

float signed_area(float ax, float az, float bx, float bz, float px, float pz) {
    return (px - bx) * (az - bz) - (ax - bx) * (pz - bz);
}

bool point_in_triangle_xz(const CollisionTriangle& triangle, float x, float z) {
    const auto& a = triangle.vertices[0];
    const auto& b = triangle.vertices[1];
    const auto& c = triangle.vertices[2];
    const float d1 = signed_area(a[0], a[2], b[0], b[2], x, z);
    const float d2 = signed_area(b[0], b[2], c[0], c[2], x, z);
    const float d3 = signed_area(c[0], c[2], a[0], a[2], x, z);
    const bool negative = d1 < -1.0e-5F || d2 < -1.0e-5F || d3 < -1.0e-5F;
    const bool positive = d1 > 1.0e-5F || d2 > 1.0e-5F || d3 > 1.0e-5F;
    return !(negative && positive);
}

float height_on_triangle(const CollisionTriangle& triangle, const TriangleProjection& normal,
                         float x, float z) {
    const auto& a = triangle.vertices[0];
    return a[1] - (normal.normal_x * (x - a[0]) + normal.normal_z * (z - a[2])) /
                      normal.normal_y;
}

float distance_to_segment(float px, float pz, float ax, float az, float bx, float bz) {
    const float dx = bx - ax;
    const float dz = bz - az;
    const float squared = dx * dx + dz * dz;
    if (squared <= 1.0e-12F) {
        return std::hypot(px - ax, pz - az);
    }
    const float t = std::clamp(((px - ax) * dx + (pz - az) * dz) / squared, 0.0F, 1.0F);
    return std::hypot(px - (ax + t * dx), pz - (az + t * dz));
}

} // namespace

NavigationGrid NavigationGrid::build(const CollisionScene& collision, float cell_size,
                                     float actor_radius) {
    if (collision.triangles.empty() || !std::isfinite(cell_size) || cell_size <= 0.0F ||
        !std::isfinite(actor_radius) || actor_radius < 0.0F) {
        throw NavigationError("Collision scene or navigation dimensions are invalid");
    }
    float minimum_x = std::numeric_limits<float>::max();
    float minimum_z = std::numeric_limits<float>::max();
    float maximum_x = std::numeric_limits<float>::lowest();
    float maximum_z = std::numeric_limits<float>::lowest();
    for (const auto& triangle : collision.triangles) {
        for (const auto& vertex : triangle.vertices) {
            minimum_x = std::min(minimum_x, vertex[0]);
            minimum_z = std::min(minimum_z, vertex[2]);
            maximum_x = std::max(maximum_x, vertex[0]);
            maximum_z = std::max(maximum_z, vertex[2]);
        }
    }
    NavigationGrid result;
    result.cell_size_ = cell_size;
    result.origin_x_ = std::floor(minimum_x / cell_size) * cell_size;
    result.origin_z_ = std::floor(minimum_z / cell_size) * cell_size;
    result.width_ = static_cast<std::size_t>(
                        std::ceil((maximum_x - result.origin_x_) / cell_size)) +
                    1U;
    result.height_ = static_cast<std::size_t>(
                         std::ceil((maximum_z - result.origin_z_) / cell_size)) +
                     1U;
    if (result.width_ == 0 || result.height_ == 0 ||
        result.width_ > 8192U || result.height_ > 8192U ||
        result.width_ > 16000000U / result.height_) {
        throw NavigationError("Navigation grid dimensions are excessive");
    }
    result.cells_.resize(result.width_ * result.height_);

    const auto cell_range = [&](float low, float high, float origin, std::size_t count) {
        const auto first = static_cast<long>(std::floor((low - origin) / cell_size));
        const auto last = static_cast<long>(std::ceil((high - origin) / cell_size));
        return std::array<std::size_t, 2>{
            static_cast<std::size_t>(std::clamp(first, 0L, static_cast<long>(count - 1U))),
            static_cast<std::size_t>(std::clamp(last, 0L, static_cast<long>(count - 1U)))};
    };

    for (const auto& triangle : collision.triangles) {
        const auto normal = triangle_normal(triangle);
        if (normal.length <= 0.0F || std::abs(normal.normal_y) / normal.length < 0.7F) {
            continue;
        }
        float low_x = std::numeric_limits<float>::max();
        float low_z = std::numeric_limits<float>::max();
        float high_x = std::numeric_limits<float>::lowest();
        float high_z = std::numeric_limits<float>::lowest();
        for (const auto& vertex : triangle.vertices) {
            low_x = std::min(low_x, vertex[0]);
            low_z = std::min(low_z, vertex[2]);
            high_x = std::max(high_x, vertex[0]);
            high_z = std::max(high_z, vertex[2]);
        }
        const auto x_range = cell_range(low_x, high_x, result.origin_x_, result.width_);
        const auto z_range = cell_range(low_z, high_z, result.origin_z_, result.height_);
        for (std::size_t z = z_range[0]; z <= z_range[1]; ++z) {
            for (std::size_t x = x_range[0]; x <= x_range[1]; ++x) {
                const float world_x = result.origin_x_ + (static_cast<float>(x) + 0.5F) * cell_size;
                const float world_z = result.origin_z_ + (static_cast<float>(z) + 0.5F) * cell_size;
                if (!point_in_triangle_xz(triangle, world_x, world_z)) {
                    continue;
                }
                auto& cell = result.cells_[z * result.width_ + x];
                const float floor_height = height_on_triangle(triangle, normal, world_x, world_z);
                if (!cell.walkable || floor_height > cell.height) {
                    cell.height = floor_height;
                    cell.walkable = true;
                }
            }
        }
    }

    for (const auto& triangle : collision.triangles) {
        const auto normal = triangle_normal(triangle);
        if (normal.length <= 0.0F || std::abs(normal.normal_y) / normal.length > 0.3F) {
            continue;
        }
        float low_x = std::numeric_limits<float>::max();
        float low_z = std::numeric_limits<float>::max();
        float high_x = std::numeric_limits<float>::lowest();
        float high_z = std::numeric_limits<float>::lowest();
        for (const auto& vertex : triangle.vertices) {
            low_x = std::min(low_x, vertex[0]);
            low_z = std::min(low_z, vertex[2]);
            high_x = std::max(high_x, vertex[0]);
            high_z = std::max(high_z, vertex[2]);
        }
        const auto x_range =
            cell_range(low_x - actor_radius, high_x + actor_radius, result.origin_x_, result.width_);
        const auto z_range =
            cell_range(low_z - actor_radius, high_z + actor_radius, result.origin_z_, result.height_);
        for (std::size_t z = z_range[0]; z <= z_range[1]; ++z) {
            for (std::size_t x = x_range[0]; x <= x_range[1]; ++x) {
                auto& cell = result.cells_[z * result.width_ + x];
                if (!cell.walkable) {
                    continue;
                }
                const float world_x = result.origin_x_ + (static_cast<float>(x) + 0.5F) * cell_size;
                const float world_z = result.origin_z_ + (static_cast<float>(z) + 0.5F) * cell_size;
                bool blocked = point_in_triangle_xz(triangle, world_x, world_z);
                for (std::size_t edge = 0; edge < 3U && !blocked; ++edge) {
                    const auto& a = triangle.vertices[edge];
                    const auto& b = triangle.vertices[(edge + 1U) % 3U];
                    blocked = distance_to_segment(world_x, world_z, a[0], a[2], b[0], b[2]) <=
                              actor_radius;
                }
                if (blocked) {
                    cell.walkable = false;
                }
            }
        }
    }
    return result;
}

std::size_t NavigationGrid::walkable_cell_count() const noexcept {
    return static_cast<std::size_t>(std::count_if(cells_.begin(), cells_.end(),
                                                  [](const NavigationCell& cell) {
                                                      return cell.walkable;
                                                  }));
}

const NavigationCell& NavigationGrid::cell(std::size_t x, std::size_t z) const {
    if (x >= width_ || z >= height_) {
        throw NavigationError("Navigation cell is out of range");
    }
    return cells_[z * width_ + x];
}

std::array<float, 3> NavigationGrid::cell_center(std::size_t x, std::size_t z) const {
    const auto& selected = cell(x, z);
    return {origin_x_ + (static_cast<float>(x) + 0.5F) * cell_size_, selected.height,
            origin_z_ + (static_cast<float>(z) + 0.5F) * cell_size_};
}

std::optional<std::array<std::size_t, 2>> NavigationGrid::nearest_walkable(
    const std::array<float, 3>& position, std::size_t maximum_radius) const {
    const long center_x = static_cast<long>(std::floor((position[0] - origin_x_) / cell_size_));
    const long center_z = static_cast<long>(std::floor((position[2] - origin_z_) / cell_size_));
    float best_distance = std::numeric_limits<float>::max();
    std::optional<std::array<std::size_t, 2>> best;
    for (long dz = -static_cast<long>(maximum_radius); dz <= static_cast<long>(maximum_radius); ++dz) {
        for (long dx = -static_cast<long>(maximum_radius); dx <= static_cast<long>(maximum_radius); ++dx) {
            const long x = center_x + dx;
            const long z = center_z + dz;
            if (x < 0 || z < 0 || x >= static_cast<long>(width_) ||
                z >= static_cast<long>(height_)) {
                continue;
            }
            const auto& candidate = cells_[static_cast<std::size_t>(z) * width_ +
                                           static_cast<std::size_t>(x)];
            if (!candidate.walkable) {
                continue;
            }
            const auto world = cell_center(static_cast<std::size_t>(x), static_cast<std::size_t>(z));
            const float distance = std::hypot(world[0] - position[0], world[2] - position[2]);
            if (distance < best_distance) {
                best_distance = distance;
                best = std::array<std::size_t, 2>{static_cast<std::size_t>(x),
                                                  static_cast<std::size_t>(z)};
            }
        }
    }
    return best;
}

std::vector<std::array<float, 3>> NavigationGrid::find_path(
    const std::array<float, 3>& start, const std::array<float, 3>& destination,
    float maximum_step_height) const {
    const auto first = nearest_walkable(start);
    const auto last = nearest_walkable(destination);
    if (!first || !last || !std::isfinite(maximum_step_height) || maximum_step_height < 0.0F) {
        return {};
    }
    const std::size_t start_index = (*first)[1] * width_ + (*first)[0];
    const std::size_t goal_index = (*last)[1] * width_ + (*last)[0];
    struct QueueNode {
        float score;
        std::size_t index;
        bool operator<(const QueueNode& other) const noexcept { return score > other.score; }
    };
    std::priority_queue<QueueNode> open;
    std::vector<float> cost(cells_.size(), std::numeric_limits<float>::infinity());
    std::vector<std::size_t> previous(cells_.size(), cells_.size());
    std::vector<bool> closed(cells_.size(), false);
    cost[start_index] = 0.0F;
    const auto start_x = static_cast<std::uint32_t>((*first)[0]);
    const auto start_z = static_cast<std::uint32_t>((*first)[1]);
    const auto goal_x = static_cast<std::uint32_t>((*last)[0]);
    const auto goal_z = static_cast<std::uint32_t>((*last)[1]);
    open.push({path_node_priority(-1.0F, start_x, start_z, goal_x, goal_z), start_index});
    constexpr std::array<std::array<int, 2>, 8> directions{{
        {{-1, 0}}, {{1, 0}}, {{0, -1}}, {{0, 1}},
        {{-1, -1}}, {{1, -1}}, {{-1, 1}}, {{1, 1}},
    }};
    std::size_t expanded = 0;
    constexpr std::size_t kMaximumExpandedNodes = 150;
    while (!open.empty()) {
        const auto current = open.top();
        open.pop();
        if (closed[current.index]) {
            continue;
        }
        closed[current.index] = true;
        if (current.index == goal_index) {
            break;
        }
        if (expanded++ > kMaximumExpandedNodes) {
            break;
        }
        const std::size_t x = current.index % width_;
        const std::size_t z = current.index / width_;
        for (const auto& direction : directions) {
            const long next_x = static_cast<long>(x) + direction[0];
            const long next_z = static_cast<long>(z) + direction[1];
            if (next_x < 0 || next_z < 0 || next_x >= static_cast<long>(width_) ||
                next_z >= static_cast<long>(height_)) {
                continue;
            }
            const std::size_t nx = static_cast<std::size_t>(next_x);
            const std::size_t nz = static_cast<std::size_t>(next_z);
            const std::size_t next_index = nz * width_ + nx;
            if (!cells_[next_index].walkable ||
                std::abs(cells_[next_index].height - cells_[current.index].height) >
                    maximum_step_height) {
                continue;
            }
            const bool diagonal = direction[0] != 0 && direction[1] != 0;
            if (diagonal &&
                (!cells_[z * width_ + nx].walkable || !cells_[nz * width_ + x].walkable)) {
                continue;
            }
            const float next_cost = cost[current.index] + 1.0F;
            if (next_cost >= cost[next_index]) {
                continue;
            }
            cost[next_index] = next_cost;
            previous[next_index] = current.index;
            open.push({path_node_priority(cost[current.index], static_cast<std::uint32_t>(nx),
                                          static_cast<std::uint32_t>(nz), goal_x, goal_z),
                       next_index});
        }
    }
    if (goal_index != start_index && previous[goal_index] == cells_.size()) {
        return {};
    }
    std::vector<std::array<float, 3>> path;
    for (std::size_t index = goal_index;; index = previous[index]) {
        path.push_back(cell_center(index % width_, index / width_));
        if (index == start_index) {
            break;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace torchlight
