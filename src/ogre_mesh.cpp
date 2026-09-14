#include "torchlight/ogre_mesh.hpp"

#include <algorithm>
#include <cstring>
#include <string>
#include <utility>

namespace torchlight {
namespace {

constexpr std::uint16_t kHeader = 0x1000;
constexpr std::uint16_t kMesh = 0x3000;
constexpr std::uint16_t kSubmesh = 0x4000;
constexpr std::uint16_t kSubmeshOperation = 0x4010;
constexpr std::uint16_t kSubmeshBoneAssignment = 0x4100;
constexpr std::uint16_t kGeometry = 0x5000;
constexpr std::uint16_t kVertexDeclaration = 0x5100;
constexpr std::uint16_t kVertexElement = 0x5110;
constexpr std::uint16_t kVertexBuffer = 0x5200;
constexpr std::uint16_t kVertexBufferData = 0x5210;
constexpr std::uint16_t kSkeletonLink = 0x6000;
constexpr std::uint16_t kMeshBoneAssignment = 0x7000;
constexpr std::uint16_t kBounds = 0x9000;
constexpr std::uint16_t kPositionSemantic = 1;
constexpr std::uint16_t kNormalSemantic = 4;
constexpr std::uint16_t kTextureCoordinateSemantic = 7;
constexpr std::uint16_t kFloat2Type = 1;
constexpr std::uint16_t kFloat3Type = 2;

struct Chunk {
    std::uint16_t id = 0;
    std::size_t end = 0;
};

class Reader {
public:
    explicit Reader(const std::vector<std::uint8_t>& bytes) : bytes_(bytes) {}

    [[nodiscard]] std::size_t position() const noexcept { return position_; }
    [[nodiscard]] std::size_t size() const noexcept { return bytes_.size(); }
    [[nodiscard]] bool can_read(std::size_t count, std::size_t end) const noexcept {
        return end <= bytes_.size() && position_ <= end && count <= end - position_;
    }

    [[nodiscard]] std::uint16_t peek_u16(std::size_t end) const {
        require(2, end, "OGRE chunk ID");
        return static_cast<std::uint16_t>(bytes_[position_]) |
               (static_cast<std::uint16_t>(bytes_[position_ + 1]) << 8U);
    }

    std::uint8_t read_u8(std::size_t end, const char* description) {
        require(1, end, description);
        return bytes_[position_++];
    }

    std::uint16_t read_u16(std::size_t end, const char* description) {
        require(2, end, description);
        const auto result = static_cast<std::uint16_t>(bytes_[position_]) |
                            (static_cast<std::uint16_t>(bytes_[position_ + 1]) << 8U);
        position_ += 2;
        return result;
    }

    std::uint32_t read_u32(std::size_t end, const char* description) {
        require(4, end, description);
        const auto result = static_cast<std::uint32_t>(bytes_[position_]) |
                            (static_cast<std::uint32_t>(bytes_[position_ + 1]) << 8U) |
                            (static_cast<std::uint32_t>(bytes_[position_ + 2]) << 16U) |
                            (static_cast<std::uint32_t>(bytes_[position_ + 3]) << 24U);
        position_ += 4;
        return result;
    }

    float read_float(std::size_t end, const char* description) {
        const auto bits = read_u32(end, description);
        float result = 0.0F;
        static_assert(sizeof(result) == sizeof(bits));
        std::memcpy(&result, &bits, sizeof(result));
        return result;
    }

    std::string read_line(std::size_t end, const char* description) {
        const auto begin = position_;
        while (position_ < end && bytes_[position_] != static_cast<std::uint8_t>('\n')) {
            ++position_;
        }
        if (position_ == end) {
            throw OgreMeshError(std::string(description) + " has no newline terminator");
        }
        std::string result(bytes_.begin() + static_cast<std::ptrdiff_t>(begin),
                           bytes_.begin() + static_cast<std::ptrdiff_t>(position_));
        ++position_;
        return result;
    }

    std::vector<std::uint8_t> read_bytes(std::size_t count, std::size_t end,
                                         const char* description) {
        require(count, end, description);
        std::vector<std::uint8_t> result(
            bytes_.begin() + static_cast<std::ptrdiff_t>(position_),
            bytes_.begin() + static_cast<std::ptrdiff_t>(position_ + count));
        position_ += count;
        return result;
    }

    Chunk read_chunk(std::size_t container_end) {
        const auto id = read_u16(container_end, "OGRE chunk ID");
        const auto length = read_u32(container_end, "OGRE chunk length");
        if (length < 6U) {
            throw OgreMeshError("OGRE chunk is shorter than its header");
        }
        const auto payload_size = static_cast<std::size_t>(length - 6U);
        if (payload_size > bytes_.size() - position_) {
            if (container_end == bytes_.size()) {
                return Chunk{id, container_end};
            }
            throw OgreMeshError("OGRE chunk " + std::to_string(id) + " at " +
                                std::to_string(position_ - 6U) + " with length " +
                                std::to_string(length) + " exceeds the input");
        }
        return Chunk{id, position_ + payload_size};
    }

    Chunk read_root_chunk() {
        const auto id = read_u16(bytes_.size(), "OGRE root chunk ID");
        const auto length = read_u32(bytes_.size(), "OGRE root chunk length");
        if (length < 6U) {
            throw OgreMeshError("OGRE root chunk is shorter than its header");
        }
        return Chunk{id, bytes_.size()};
    }

    void seek(std::size_t position) {
        if (position > bytes_.size()) {
            throw OgreMeshError("OGRE seek exceeds the input");
        }
        position_ = position;
    }

private:
    void require(std::size_t count, std::size_t end, const char* description) const {
        if (end > bytes_.size() || position_ > end || count > end - position_) {
            throw OgreMeshError(std::string("Truncated ") + description);
        }
    }

    const std::vector<std::uint8_t>& bytes_;
    std::size_t position_ = 0;
};

std::size_t vertex_element_size(std::uint16_t type) {
    switch (type) {
    case 0: return 4;
    case 1: return 8;
    case 2: return 12;
    case 3: return 16;
    case 4: return 4;
    case 5: return 2;
    case 6: return 4;
    case 7: return 6;
    case 8: return 8;
    case 9:
    case 10:
    case 11: return 4;
    case 12: return 8;
    case 13: return 16;
    case 14: return 24;
    case 15: return 32;
    case 16: return 2;
    case 17: return 4;
    case 18: return 6;
    case 19: return 8;
    case 20:
    case 24: return 4;
    case 21:
    case 25: return 8;
    case 22:
    case 26: return 12;
    case 23:
    case 27: return 16;
    case 28:
    case 29:
    case 30: return 4;
    case 31:
    case 33: return 4;
    case 32:
    case 34: return 8;
    default: throw OgreMeshError("Unsupported OGRE vertex element type");
    }
}

const OgreVertexBuffer* find_buffer(const OgreGeometry& geometry, std::uint16_t binding) {
    const auto found = std::find_if(geometry.buffers.begin(), geometry.buffers.end(),
                                    [binding](const auto& buffer) {
                                        return buffer.binding == binding;
                                    });
    return found == geometry.buffers.end() ? nullptr : &*found;
}

float read_buffer_float(const std::vector<std::uint8_t>& data, std::size_t offset) {
    if (offset > data.size() || sizeof(std::uint32_t) > data.size() - offset) {
        throw OgreMeshError("OGRE position exceeds its vertex buffer");
    }
    const auto bits = static_cast<std::uint32_t>(data[offset]) |
                      (static_cast<std::uint32_t>(data[offset + 1]) << 8U) |
                      (static_cast<std::uint32_t>(data[offset + 2]) << 16U) |
                      (static_cast<std::uint32_t>(data[offset + 3]) << 24U);
    float result = 0.0F;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}

void finish_geometry(OgreGeometry& geometry) {
    for (const auto& element : geometry.elements) {
        const auto* buffer = find_buffer(geometry, element.source);
        if (buffer == nullptr) {
            throw OgreMeshError("OGRE vertex declaration references an absent buffer");
        }
        const auto size = vertex_element_size(element.type);
        if (element.offset > buffer->stride) {
            throw OgreMeshError("OGRE vertex element exceeds its stride");
        }
        const auto available = static_cast<std::size_t>(buffer->stride - element.offset);
        if (size > available) {
            throw OgreMeshError("OGRE vertex element exceeds its stride");
        }
    }
    const auto position = std::find_if(geometry.elements.begin(), geometry.elements.end(),
                                       [](const auto& element) {
                                           return element.semantic == kPositionSemantic;
                                       });
    if (geometry.vertex_count == 0) {
        return;
    }
    if (position == geometry.elements.end() || position->type != kFloat3Type) {
        throw OgreMeshError("OGRE geometry has no FLOAT3 position element");
    }
    const auto* buffer = find_buffer(geometry, position->source);
    if (buffer == nullptr) {
        throw OgreMeshError("OGRE position buffer is absent");
    }
    geometry.positions.reserve(geometry.vertex_count);
    for (std::uint32_t index = 0; index < geometry.vertex_count; ++index) {
        const auto offset = static_cast<std::size_t>(index) * buffer->stride + position->offset;
        geometry.positions.push_back({read_buffer_float(buffer->data, offset),
                                      read_buffer_float(buffer->data, offset + 4U),
                                      read_buffer_float(buffer->data, offset + 8U)});
    }

    const auto normal = std::find_if(geometry.elements.begin(), geometry.elements.end(),
                                     [](const auto& element) {
                                         return element.semantic == kNormalSemantic &&
                                                element.index == 0;
                                     });
    if (normal != geometry.elements.end()) {
        if (normal->type != kFloat3Type) {
            throw OgreMeshError("OGRE primary normal is not FLOAT3");
        }
        const auto* normal_buffer = find_buffer(geometry, normal->source);
        if (normal_buffer == nullptr) {
            throw OgreMeshError("OGRE normal buffer is absent");
        }
        geometry.normals.reserve(geometry.vertex_count);
        for (std::uint32_t index = 0; index < geometry.vertex_count; ++index) {
            const auto offset = static_cast<std::size_t>(index) * normal_buffer->stride +
                                normal->offset;
            geometry.normals.push_back({
                read_buffer_float(normal_buffer->data, offset),
                read_buffer_float(normal_buffer->data, offset + 4U),
                read_buffer_float(normal_buffer->data, offset + 8U)});
        }
    }

    const auto texcoord = std::find_if(geometry.elements.begin(), geometry.elements.end(),
                                       [](const auto& element) {
                                           return element.semantic == kTextureCoordinateSemantic &&
                                                  element.index == 0;
                                       });
    if (texcoord == geometry.elements.end()) {
        return;
    }
    if (texcoord->type != kFloat2Type) {
        throw OgreMeshError("OGRE primary texture coordinate is not FLOAT2");
    }
    const auto* texcoord_buffer = find_buffer(geometry, texcoord->source);
    if (texcoord_buffer == nullptr) {
        throw OgreMeshError("OGRE texture-coordinate buffer is absent");
    }
    geometry.texcoords.reserve(geometry.vertex_count);
    for (std::uint32_t index = 0; index < geometry.vertex_count; ++index) {
        const auto offset = static_cast<std::size_t>(index) * texcoord_buffer->stride +
                            texcoord->offset;
        geometry.texcoords.push_back({read_buffer_float(texcoord_buffer->data, offset),
                                      read_buffer_float(texcoord_buffer->data, offset + 4U)});
    }
}

OgreGeometry parse_geometry(Reader& reader, const Chunk& chunk) {
    OgreGeometry geometry;
    geometry.vertex_count = reader.read_u32(chunk.end, "OGRE geometry vertex count");
    while (reader.can_read(6, chunk.end) &&
           (reader.peek_u16(chunk.end) == kVertexDeclaration ||
            reader.peek_u16(chunk.end) == kVertexBuffer)) {
        const auto child = reader.read_chunk(chunk.end);
        if (child.id == kVertexDeclaration) {
            while (reader.can_read(6, child.end) &&
                   reader.peek_u16(child.end) == kVertexElement) {
                const auto element_chunk = reader.read_chunk(child.end);
                OgreVertexElement element;
                element.source = reader.read_u16(element_chunk.end, "vertex source");
                element.type = reader.read_u16(element_chunk.end, "vertex type");
                element.semantic = reader.read_u16(element_chunk.end, "vertex semantic");
                element.offset = reader.read_u16(element_chunk.end, "vertex offset");
                element.index = reader.read_u16(element_chunk.end, "vertex semantic index");
                geometry.elements.push_back(element);
                reader.seek(element_chunk.end);
            }
        } else if (child.id == kVertexBuffer) {
            OgreVertexBuffer buffer;
            buffer.binding = reader.read_u16(child.end, "vertex buffer binding");
            buffer.stride = reader.read_u16(child.end, "vertex buffer stride");
            const auto data_chunk = reader.read_chunk(child.end);
            if (data_chunk.id != kVertexBufferData) {
                throw OgreMeshError("OGRE vertex buffer has no data chunk");
            }
            const auto byte_count = static_cast<std::size_t>(geometry.vertex_count) * buffer.stride;
            if (buffer.stride != 0 && byte_count / buffer.stride != geometry.vertex_count) {
                throw OgreMeshError("OGRE vertex buffer size overflows");
            }
            buffer.data = reader.read_bytes(byte_count, data_chunk.end, "vertex buffer data");
            if (reader.position() != data_chunk.end) {
                throw OgreMeshError("OGRE vertex buffer data has an unexpected size");
            }
            if (find_buffer(geometry, buffer.binding) != nullptr) {
                throw OgreMeshError("Duplicate OGRE vertex buffer binding");
            }
            geometry.buffers.push_back(std::move(buffer));
        }
        reader.seek(child.end);
    }
    finish_geometry(geometry);
    return geometry;
}

OgreSubmesh parse_submesh(Reader& reader, const Chunk& chunk) {
    OgreSubmesh submesh;
    submesh.material = reader.read_line(chunk.end, "OGRE material name");
    submesh.uses_shared_vertices = reader.read_u8(chunk.end, "shared-vertices flag") != 0;
    const auto index_count = reader.read_u32(chunk.end, "OGRE index count");
    submesh.indexes_32bit = reader.read_u8(chunk.end, "32-bit-index flag") != 0;
    const auto index_size = submesh.indexes_32bit ? 4U : 2U;
    if (index_count > (chunk.end - reader.position()) / index_size) {
        throw OgreMeshError("OGRE index buffer exceeds its submesh");
    }
    submesh.indices.reserve(index_count);
    for (std::uint32_t index = 0; index < index_count; ++index) {
        submesh.indices.push_back(submesh.indexes_32bit
                                      ? reader.read_u32(chunk.end, "32-bit mesh index")
                                      : reader.read_u16(chunk.end, "16-bit mesh index"));
    }
    if (!submesh.uses_shared_vertices) {
        const auto geometry_chunk = reader.read_chunk(chunk.end);
        if (geometry_chunk.id != kGeometry) {
            throw OgreMeshError("OGRE submesh has no local geometry");
        }
        submesh.geometry = parse_geometry(reader, geometry_chunk);
    }
    while (reader.can_read(6, chunk.end)) {
        const auto next_id = reader.peek_u16(chunk.end);
        if (next_id != kSubmeshOperation && next_id != kSubmeshBoneAssignment &&
            next_id != 0x4200) {
            break;
        }
        const auto child = reader.read_chunk(chunk.end);
        if (child.id == kSubmeshOperation) {
            submesh.operation_type = reader.read_u16(child.end, "submesh operation");
        } else if (child.id == kSubmeshBoneAssignment) {
            OgreBoneAssignment assignment;
            assignment.vertex_index =
                reader.read_u32(child.end, "submesh bone-assignment vertex index");
            assignment.bone_index =
                reader.read_u16(child.end, "submesh bone-assignment bone index");
            assignment.weight =
                reader.read_float(child.end, "submesh bone-assignment weight");
            submesh.bone_assignments.push_back(assignment);
        }
        reader.seek(child.end);
    }
    return submesh;
}

void validate_mesh(const OgreMesh& mesh) {
    for (const auto& submesh : mesh.submeshes) {
        const OgreGeometry* geometry = nullptr;
        if (submesh.uses_shared_vertices) {
            if (!mesh.shared_geometry.has_value()) {
                throw OgreMeshError("OGRE submesh requests absent shared geometry");
            }
            geometry = &*mesh.shared_geometry;
        } else if (submesh.geometry.has_value()) {
            geometry = &*submesh.geometry;
        }
        if (geometry == nullptr && !submesh.indices.empty()) {
            throw OgreMeshError("Indexed OGRE submesh has no geometry");
        }
        if (geometry != nullptr) {
            for (const auto index : submesh.indices) {
                if (index >= geometry->vertex_count) {
                    throw OgreMeshError("OGRE submesh index exceeds its geometry");
                }
            }
            for (const auto& assignment : submesh.bone_assignments) {
                if (assignment.vertex_index >= geometry->vertex_count) {
                    throw OgreMeshError("OGRE submesh bone assignment exceeds its geometry");
                }
            }
        }
    }
    if (!mesh.shared_bone_assignments.empty() && !mesh.shared_geometry) {
        throw OgreMeshError("OGRE shared bone assignment has no shared geometry");
    }
    for (const auto& assignment : mesh.shared_bone_assignments) {
        if (assignment.vertex_index >= mesh.shared_geometry->vertex_count) {
            throw OgreMeshError("OGRE shared bone assignment exceeds its geometry");
        }
    }
}

} // namespace

OgreMesh parse_ogre_mesh(const std::vector<std::uint8_t>& bytes) {
    Reader reader(bytes);
    if (reader.read_u16(reader.size(), "OGRE file header") != kHeader) {
        throw OgreMeshError("OGRE mesh has the wrong header");
    }
    OgreMesh mesh;
    mesh.serializer_version = reader.read_line(reader.size(), "OGRE serializer version");
    if (mesh.serializer_version != "[MeshSerializer_v1.40]") {
        throw OgreMeshError("Unsupported OGRE mesh serializer version");
    }
    const auto mesh_chunk = reader.read_root_chunk();
    if (mesh_chunk.id != kMesh) {
        throw OgreMeshError("OGRE file has no mesh chunk");
    }
    mesh.skeletally_animated = reader.read_u8(mesh_chunk.end, "skeletal-animation flag") != 0;
    while (reader.can_read(6, mesh_chunk.end)) {
        const auto child = reader.read_chunk(mesh_chunk.end);
        bool consumed_by_parser = false;
        switch (child.id) {
        case kGeometry:
            if (mesh.shared_geometry.has_value()) {
                throw OgreMeshError("OGRE mesh contains duplicate shared geometry");
            }
            mesh.shared_geometry = parse_geometry(reader, child);
            consumed_by_parser = true;
            break;
        case kSubmesh:
            mesh.submeshes.push_back(parse_submesh(reader, child));
            consumed_by_parser = true;
            break;
        case kSkeletonLink:
            mesh.skeleton_file = reader.read_line(child.end, "OGRE skeleton link");
            break;
        case kMeshBoneAssignment: {
            OgreBoneAssignment assignment;
            assignment.vertex_index =
                reader.read_u32(child.end, "shared bone-assignment vertex index");
            assignment.bone_index =
                reader.read_u16(child.end, "shared bone-assignment bone index");
            assignment.weight = reader.read_float(child.end, "shared bone-assignment weight");
            mesh.shared_bone_assignments.push_back(assignment);
            break;
        }
        case kBounds: {
            OgreMeshBounds bounds;
            for (auto& coordinate : bounds.minimum) {
                coordinate = reader.read_float(child.end, "OGRE minimum bound");
            }
            for (auto& coordinate : bounds.maximum) {
                coordinate = reader.read_float(child.end, "OGRE maximum bound");
            }
            bounds.radius = reader.read_float(child.end, "OGRE bounding radius");
            mesh.bounds = bounds;
            break;
        }
        default: break;
        }
        if (!consumed_by_parser) {
            reader.seek(child.end);
        }
    }
    if (mesh_chunk.end != reader.size()) {
        throw OgreMeshError("OGRE mesh has trailing data");
    }
    validate_mesh(mesh);
    return mesh;
}

} // namespace torchlight
