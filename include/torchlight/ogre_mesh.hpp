#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace torchlight {

class OgreMeshError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct OgreVertexElement {
    std::uint16_t source = 0;
    std::uint16_t type = 0;
    std::uint16_t semantic = 0;
    std::uint16_t offset = 0;
    std::uint16_t index = 0;
};

struct OgreVertexBuffer {
    std::uint16_t binding = 0;
    std::uint16_t stride = 0;
    std::vector<std::uint8_t> data;
};

struct OgreBoneAssignment {
    std::uint32_t vertex_index = 0;
    std::uint16_t bone_index = 0;
    float weight = 0.0F;
};

struct OgreGeometry {
    std::uint32_t vertex_count = 0;
    std::vector<OgreVertexElement> elements;
    std::vector<OgreVertexBuffer> buffers;
    std::vector<std::array<float, 3>> positions;
    std::vector<std::array<float, 3>> normals;
    std::vector<std::array<float, 2>> texcoords;
};

struct OgreSubmesh {
    std::string material;
    bool uses_shared_vertices = false;
    bool indexes_32bit = false;
    std::uint16_t operation_type = 4;
    std::vector<std::uint32_t> indices;
    std::vector<OgreBoneAssignment> bone_assignments;
    std::optional<OgreGeometry> geometry;
};

struct OgreMeshBounds {
    std::array<float, 3> minimum{};
    std::array<float, 3> maximum{};
    float radius = 0.0F;
};

struct OgreMesh {
    std::string serializer_version;
    bool skeletally_animated = false;
    std::optional<OgreGeometry> shared_geometry;
    std::vector<OgreSubmesh> submeshes;
    std::vector<OgreBoneAssignment> shared_bone_assignments;
    std::string skeleton_file;
    std::optional<OgreMeshBounds> bounds;
};

[[nodiscard]] OgreMesh parse_ogre_mesh(const std::vector<std::uint8_t>& bytes);

} // namespace torchlight
