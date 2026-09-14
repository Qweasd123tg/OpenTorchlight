#include "torchlight/collision_scene.hpp"

#include "torchlight/ogre_mesh.hpp"

#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace torchlight {
namespace {


class CollisionSceneError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::string ascii_path(std::u16string_view path) {
    std::string result;
    result.reserve(path.size());
    for (const auto character : path) {
        if (character > 0x7fU) {
            throw CollisionSceneError("Collision mesh path contains a non-ASCII character");
        }
        result.push_back(static_cast<char>(character));
    }
    return result;
}

const OgreGeometry& geometry_for(const OgreMesh& mesh, const OgreSubmesh& submesh) {
    if (submesh.uses_shared_vertices) {
        if (!mesh.shared_geometry) {
            throw CollisionSceneError("Collision submesh has no shared geometry");
        }
        return *mesh.shared_geometry;
    }
    if (!submesh.geometry) {
        throw CollisionSceneError("Collision submesh has no local geometry");
    }
    return *submesh.geometry;
}

std::array<float, 3> transformed(const std::array<float, 3>& point,
                                 const LayoutWorldTransform& transform,
                                 const std::array<float, 3>& chunk_offset) {
    auto result = transform_point(transform.position, transform.orientation,
                                  transform.scale, point);
    for (std::size_t axis = 0; axis < 3; ++axis) result[axis] += chunk_offset[axis];
    return result;
}

bool degenerate(const CollisionTriangle& triangle) {
    const auto& a = triangle.vertices[0];
    const auto& b = triangle.vertices[1];
    const auto& c = triangle.vertices[2];
    const float ab_x = b[0] - a[0];
    const float ab_y = b[1] - a[1];
    const float ab_z = b[2] - a[2];
    const float ac_x = c[0] - a[0];
    const float ac_y = c[1] - a[1];
    const float ac_z = c[2] - a[2];
    const float normal_x = ab_y * ac_z - ab_z * ac_y;
    const float normal_y = ab_z * ac_x - ab_x * ac_z;
    const float normal_z = ab_x * ac_y - ab_y * ac_x;
    return normal_x * normal_x + normal_y * normal_y + normal_z * normal_z <= 1.0e-12F;
}

void append_layout_collision(const PakArchive& archive, const LevelsetCatalog& levelsets,
                             const LayoutManifest& layout,
                             const std::array<float, 3>& offset, CollisionScene& result,
                             std::unordered_map<std::string, OgreMesh>& meshes) {
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t object_index = 0; object_index < layout.objects.size(); ++object_index) {
        const auto& object = layout.objects[object_index];
        if (object.descriptor != u"Room Piece" || !object.piece_guid) {
            continue;
        }
        const auto* piece = levelsets.find(*object.piece_guid);
        if (piece == nullptr) {
            throw CollisionSceneError("Collision room-piece GUID is absent from levelsets");
        }
        if (piece->collision_file.empty()) {
            continue;
        }
        const auto requested_path = ascii_path(piece->collision_file);
        const auto* entry = archive.find_normalized(requested_path);
        if (entry == nullptr) {
            ++result.missing_instances;
            continue;
        }
        auto found = meshes.find(entry->name);
        if (found == meshes.end()) {
            found = meshes.emplace(entry->name, parse_ogre_mesh(archive.read(*entry))).first;
        }
        ++result.instances;
        const auto& mesh = found->second;
        for (const auto& submesh : mesh.submeshes) {
            if (submesh.operation_type != 4 || submesh.indices.size() % 3U != 0U) {
                continue;
            }
            const auto& geometry = geometry_for(mesh, submesh);
            for (std::size_t index = 0; index < submesh.indices.size(); index += 3U) {
                CollisionTriangle triangle;
                for (std::size_t corner = 0; corner < 3U; ++corner) {
                    const auto vertex_index = submesh.indices[index + corner];
                    if (vertex_index >= geometry.positions.size()) {
                        throw CollisionSceneError("Collision triangle index is out of range");
                    }
                    triangle.vertices[corner] = transformed(
                        geometry.positions[vertex_index], transforms[object_index], offset);
                }
                result.degenerate_triangles += static_cast<std::size_t>(degenerate(triangle));
                result.triangles.push_back(std::move(triangle));
            }
        }
    }
}

} // namespace

CollisionScene build_generated_level_collision(const PakArchive& archive,
                                                const LevelsetCatalog& levelsets,
                                                const LevelSceneLoader& loader,
                                                const GeneratedLevel& level) {
    CollisionScene result;
    std::unordered_map<std::string, OgreMesh> meshes;
    for (std::size_t layout_index = 0; layout_index < level.chunks.size(); ++layout_index) {
        const auto& chunk = level.chunks[layout_index];
        const auto layout = loader.load_layout(chunk.layout_path);
        append_layout_collision(archive, levelsets, layout, chunk.position, result, meshes);
    }
    result.source_meshes = meshes.size();
    return result;
}

CollisionScene build_fixed_level_collision(const PakArchive& archive,
                                           const LevelsetCatalog& levelsets,
                                           const FixedLevelScene& scene) {
    CollisionScene result;
    std::unordered_map<std::string, OgreMesh> meshes;
    append_layout_collision(archive, levelsets, scene.layout, {0.0F, 0.0F, 0.0F}, result,
                            meshes);
    result.source_meshes = meshes.size();
    return result;
}

} // namespace torchlight
