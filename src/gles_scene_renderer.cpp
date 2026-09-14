#include "torchlight/gles_scene_renderer.hpp"

#include "torchlight/dds_texture.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/png_texture.hpp"

#include <GLES2/gl2.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace torchlight {
namespace {

constexpr float kDegreesToRadians = 0.01745329251994329577F;

class GlesSceneError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

GLuint compile_shader(GLenum type, const char* source) {
    const auto shader = glCreateShader(type);
    if (shader == 0) {
        throw GlesSceneError("glCreateShader failed");
    }
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::string log(static_cast<std::size_t>(std::max(0, length)), '\0');
        if (length > 0) {
            glGetShaderInfoLog(shader, length, nullptr, log.data());
        }
        glDeleteShader(shader);
        throw GlesSceneError("OpenGL ES shader compilation failed: " + log);
    }
    return shader;
}

GLuint create_program() {
    constexpr const char* vertex_source =
        "attribute vec3 position;"
        "attribute vec2 texcoord;"
        "uniform vec3 translation;"
        "uniform vec3 object_scale;"
        "uniform vec2 object_rotation;"
        "uniform vec4 projection;"
        "uniform vec2 depth_projection;"
        "varying vec2 vertex_texcoord;"
        "void main() {"
        "  vec3 local = vec3(position.x * object_scale.x,"
        "                    position.y * object_scale.y,"
        "                   -position.z * object_scale.z);"
        "  vec3 world = vec3(local.x * object_rotation.x + local.z * object_rotation.y,"
        "                    local.y,"
        "                   -local.x * object_rotation.y + local.z * object_rotation.x) +"
        "               translation;"
        "  float projected_x = world.x - 0.70 * world.z;"
        "  float projected_y = world.y + 0.35 * (world.x + 0.70 * world.z);"
        "  float depth = 0.25 * world.x + 0.50 * world.z - 0.10 * world.y;"
        "  gl_Position = vec4((projected_x - projection.x) * projection.z,"
        "                     (projected_y - projection.y) * projection.w,"
        "                     (depth - depth_projection.x) * depth_projection.y, 1.0);"
        "  vertex_texcoord = texcoord;"
        "}";
    constexpr const char* fragment_source =
        "precision mediump float;"
        "uniform sampler2D diffuse_texture;"
        "uniform vec3 draw_color;"
        "varying vec2 vertex_texcoord;"
        "void main() {"
        "  vec4 color = texture2D(diffuse_texture, vertex_texcoord) * vec4(draw_color, 1.0);"
        "  if (color.a < 0.10) discard;"
        "  gl_FragColor = color;"
        "}";
    const auto vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    const auto fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    const auto program = glCreateProgram();
    if (program == 0) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        throw GlesSceneError("glCreateProgram failed");
    }
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texcoord");
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string log(static_cast<std::size_t>(std::max(0, length)), '\0');
        if (length > 0) {
            glGetProgramInfoLog(program, length, nullptr, log.data());
        }
        glDeleteProgram(program);
        throw GlesSceneError("OpenGL ES program link failed: " + log);
    }
    return program;
}

GLsizei checked_count(std::size_t count) {
    if (count > static_cast<std::size_t>(std::numeric_limits<GLsizei>::max())) {
        throw GlesSceneError("OpenGL ES draw count exceeds GLsizei");
    }
    return static_cast<GLsizei>(count);
}

std::array<float, 3> material_color(const std::string& material) {
    std::uint32_t hash = 2166136261U;
    for (const auto character : material) {
        hash ^= static_cast<std::uint8_t>(character);
        hash *= 16777619U;
    }
    const auto channel = [hash](unsigned shift) {
        return 0.28F + static_cast<float>((hash >> shift) & 0xffU) / 850.0F;
    };
    return {channel(0), channel(8), channel(16)};
}

const OgreGeometry& geometry_for(const OgreMesh& mesh, const OgreSubmesh& submesh) {
    if (submesh.uses_shared_vertices) {
        if (!mesh.shared_geometry.has_value()) {
            throw GlesSceneError("Submesh has no shared geometry");
        }
        return *mesh.shared_geometry;
    }
    if (!submesh.geometry.has_value()) {
        throw GlesSceneError("Submesh has no local geometry");
    }
    return *submesh.geometry;
}

struct ProjectedPoint {
    float x = 0.0F;
    float y = 0.0F;
    float depth = 0.0F;
};

ProjectedPoint project(const std::array<float, 3>& point) {
    return {point[0] - 0.70F * point[2],
            point[1] + 0.35F * (point[0] + 0.70F * point[2]),
            0.25F * point[0] + 0.50F * point[2] - 0.10F * point[1]};
}

bool is_dds_path(const std::string& path) {
    if (path.size() < 4U) {
        return false;
    }
    std::array<char, 4> suffix{};
    for (std::size_t index = 0; index < suffix.size(); ++index) {
        const auto character = path[path.size() - suffix.size() + index];
        suffix[index] = character >= 'A' && character <= 'Z'
                            ? static_cast<char>(character - 'A' + 'a')
                            : character;
    }
    return suffix == std::array<char, 4>{'.', 'd', 'd', 's'};
}

bool is_png_path(const std::string& path) {
    if (path.size() < 4U) {
        return false;
    }
    std::string suffix = path.substr(path.size() - 4U);
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), [](const unsigned char value) {
        return value >= 'A' && value <= 'Z' ? static_cast<char>(value - 'A' + 'a')
                                            : static_cast<char>(value);
    });
    return suffix == ".png";
}

} // namespace

class GlesSceneRenderer::Implementation {
public:
    Implementation(const FixedSceneGeometry& geometry, const PakArchive& archive,
                   const OgreMaterialCatalog& materials)
        : instances_(geometry.instances), program_(create_program()) {
        stats_.mesh_resources = geometry.meshes.size();
        stats_.instances = geometry.instances.size();
        draws_by_mesh_.resize(geometry.meshes.size());
        struct GeometryBuffers {
            GLuint position = 0;
            GLuint texcoord = 0;
        };
        std::unordered_map<const OgreGeometry*, GeometryBuffers> vertex_buffers;
        std::unordered_map<std::string, GLuint> textures;
        const auto fallback_texture = upload_texture(1, 1, {255U, 255U, 255U, 255U});
        owned_textures_.push_back(fallback_texture);
        for (std::size_t mesh_index = 0; mesh_index < geometry.meshes.size(); ++mesh_index) {
            const auto& mesh = geometry.meshes[mesh_index].mesh;
            for (const auto& submesh : mesh.submeshes) {
                if (submesh.operation_type != 4 || submesh.indices.empty()) {
                    ++stats_.skipped_batches;
                    continue;
                }
                const auto& source_geometry = geometry_for(mesh, submesh);
                auto found_vertex_buffer = vertex_buffers.find(&source_geometry);
                GeometryBuffers buffers;
                if (found_vertex_buffer == vertex_buffers.end()) {
                    std::vector<float> positions;
                    positions.reserve(source_geometry.positions.size() * 3U);
                    for (const auto& position : source_geometry.positions) {
                        positions.insert(positions.end(), position.begin(), position.end());
                    }
                    glGenBuffers(1, &buffers.position);
                    glBindBuffer(GL_ARRAY_BUFFER, buffers.position);
                    glBufferData(GL_ARRAY_BUFFER,
                                 static_cast<GLsizeiptr>(positions.size() * sizeof(float)),
                                 positions.data(), GL_STATIC_DRAW);
                    std::vector<float> texcoords;
                    texcoords.reserve(source_geometry.positions.size() * 2U);
                    if (source_geometry.texcoords.size() == source_geometry.positions.size()) {
                        for (const auto& texcoord : source_geometry.texcoords) {
                            texcoords.insert(texcoords.end(), texcoord.begin(), texcoord.end());
                        }
                    } else {
                        texcoords.resize(source_geometry.positions.size() * 2U, 0.0F);
                    }
                    glGenBuffers(1, &buffers.texcoord);
                    glBindBuffer(GL_ARRAY_BUFFER, buffers.texcoord);
                    glBufferData(GL_ARRAY_BUFFER,
                                 static_cast<GLsizeiptr>(texcoords.size() * sizeof(float)),
                                 texcoords.data(), GL_STATIC_DRAW);
                    vertex_buffers.emplace(&source_geometry, buffers);
                    owned_vertex_buffers_.push_back(buffers.position);
                    owned_vertex_buffers_.push_back(buffers.texcoord);
                } else {
                    buffers = found_vertex_buffer->second;
                }

                std::vector<std::uint16_t> indices;
                indices.reserve(submesh.indices.size());
                for (const auto index : submesh.indices) {
                    if (index > std::numeric_limits<std::uint16_t>::max()) {
                        throw GlesSceneError("Scene mesh requires unsupported 32-bit indices");
                    }
                    indices.push_back(static_cast<std::uint16_t>(index));
                }
                GLuint index_buffer = 0;
                glGenBuffers(1, &index_buffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint16_t)),
                             indices.data(), GL_STATIC_DRAW);
                owned_index_buffers_.push_back(index_buffer);
                GLuint texture = fallback_texture;
                auto color = material_color(submesh.material);
                bool textured = false;
                bool alpha_blend = false;
                if (const auto* material = materials.find(submesh.material);
                    material != nullptr && !material->textures.empty()) {
                    alpha_blend = material->alpha_blend;
                    if (const auto* entry = resolve_material_texture(
                            archive, *material, material->textures.front())) {
                        if (is_dds_path(entry->name) || is_png_path(entry->name)) {
                            const auto found_texture = textures.find(entry->name);
                            if (found_texture != textures.end()) {
                                texture = found_texture->second;
                            } else {
                                const auto bytes = archive.read(*entry);
                                if (is_dds_path(entry->name)) {
                                    const auto image = decode_dds(bytes);
                                    texture = upload_texture(image.width, image.height, image.rgba);
                                } else {
                                    const auto image = decode_png(bytes);
                                    texture = upload_texture(image.width, image.height, image.rgba);
                                }
                                textures.emplace(entry->name, texture);
                                owned_textures_.push_back(texture);
                            }
                            color = {1.0F, 1.0F, 1.0F};
                            textured = true;
                        }
                    }
                }
                draws_by_mesh_[mesh_index].push_back(
                    Draw{buffers.position, buffers.texcoord, index_buffer,
                         checked_count(indices.size()), texture, color, alpha_blend});
                stats_.textured_batches += static_cast<std::size_t>(textured);
                stats_.fallback_batches += static_cast<std::size_t>(!textured);
                ++stats_.draw_batches;
            }
        }
        stats_.texture_resources = textures.size();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        if (glGetError() != GL_NO_ERROR) {
            throw GlesSceneError("OpenGL ES buffer upload failed");
        }
        calculate_bounds(geometry);
        for (const auto& instance : instances_) {
            for (const auto& draw : draws_by_mesh_.at(instance.mesh_index)) {
                stats_.placed_triangles += static_cast<std::uint64_t>(draw.index_count) / 3U;
            }
        }

        translation_location_ = glGetUniformLocation(program_, "translation");
        object_scale_location_ = glGetUniformLocation(program_, "object_scale");
        object_rotation_location_ = glGetUniformLocation(program_, "object_rotation");
        projection_location_ = glGetUniformLocation(program_, "projection");
        depth_projection_location_ = glGetUniformLocation(program_, "depth_projection");
        color_location_ = glGetUniformLocation(program_, "draw_color");
        texture_location_ = glGetUniformLocation(program_, "diffuse_texture");
        if (translation_location_ < 0 || object_scale_location_ < 0 ||
            object_rotation_location_ < 0 || projection_location_ < 0 ||
            depth_projection_location_ < 0 || color_location_ < 0 || texture_location_ < 0) {
            throw GlesSceneError("OpenGL ES scene shader has an inactive uniform");
        }
    }

    ~Implementation() {
        for (const auto buffer : owned_index_buffers_) {
            glDeleteBuffers(1, &buffer);
        }
        for (const auto buffer : owned_vertex_buffers_) {
            glDeleteBuffers(1, &buffer);
        }
        for (const auto texture : owned_textures_) {
            glDeleteTextures(1, &texture);
        }
        if (program_ != 0) {
            glDeleteProgram(program_);
        }
    }

    void draw(int width, int height) {
        if (width <= 0 || height <= 0) {
            throw GlesSceneError("OpenGL ES viewport dimensions must be positive");
        }
        const float aspect = static_cast<float>(width) / static_cast<float>(height);
        float center_x = (minimum_.x + maximum_.x) * 0.5F;
        float center_y = (minimum_.y + maximum_.y) * 0.5F;
        float scale_x = 0.0F;
        float scale_y = 0.0F;
        if (camera_target_.has_value()) {
            const auto projected_target = project(*camera_target_);
            center_x = projected_target.x;
            center_y = projected_target.y;
            scale_y = 1.90F / camera_vertical_span_;
            scale_x = scale_y / aspect;
        } else {
            const float extent_x = std::max(0.001F, maximum_.x - minimum_.x);
            const float extent_y = std::max(0.001F, maximum_.y - minimum_.y);
            scale_x = std::min(1.90F / extent_x, 1.90F / (extent_y * aspect));
            scale_y = scale_x * aspect;
        }
        last_width_ = width;
        last_height_ = height;
        last_center_x_ = center_x;
        last_center_y_ = center_y;
        last_scale_x_ = scale_x;
        last_scale_y_ = scale_y;
        const float depth_scale = 1.90F / std::max(0.001F, maximum_.depth - minimum_.depth);

        glViewport(0, 0, width, height);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClearColor(0.025F, 0.030F, 0.024F, 1.0F);
        glClearDepthf(1.0F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program_);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texture_location_, 0);
        glUniform4f(projection_location_, center_x, center_y, scale_x, scale_y);
        glUniform2f(depth_projection_location_, (minimum_.depth + maximum_.depth) * 0.5F,
                    depth_scale);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        for (const auto& instance : instances_) {
            if (!instance.visible) {
                continue;
            }
            glUniform3fv(translation_location_, 1, instance.transform.position.data());
            glUniform3fv(object_scale_location_, 1, instance.transform.scale.data());
            const float radians = instance.transform.angle * kDegreesToRadians;
            glUniform2f(object_rotation_location_, std::cos(radians), std::sin(radians));
            for (const auto& draw : draws_by_mesh_.at(instance.mesh_index)) {
                if (draw.alpha_blend) {
                    glEnable(GL_BLEND);
                    glDepthMask(GL_FALSE);
                } else {
                    glDisable(GL_BLEND);
                    glDepthMask(GL_TRUE);
                }
                glUniform3fv(color_location_, 1, draw.color.data());
                glBindBuffer(GL_ARRAY_BUFFER, draw.vertex_buffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ARRAY_BUFFER, draw.texcoord_buffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw.index_buffer);
                glBindTexture(GL_TEXTURE_2D, draw.texture);
                glDrawElements(GL_TRIANGLES, draw.index_count, GL_UNSIGNED_SHORT, nullptr);
            }
        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        if (glGetError() != GL_NO_ERROR) {
            throw GlesSceneError("OpenGL ES scene draw failed");
        }
    }

    [[nodiscard]] const GlesSceneRenderStats& stats() const noexcept { return stats_; }

    void set_instance_position(std::size_t instance_index,
                               const std::array<float, 3>& position) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        if (!std::all_of(position.begin(), position.end(),
                         [](float value) { return std::isfinite(value); })) {
            throw GlesSceneError("Scene instance position is not finite");
        }
        instances_[instance_index].transform.position = position;
    }

    void set_instance_visible(std::size_t instance_index, bool visible) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        instances_[instance_index].visible = visible;
    }

    void set_camera_target(const std::array<float, 3>& target, float vertical_view_span) {
        if (!std::all_of(target.begin(), target.end(),
                         [](float value) { return std::isfinite(value); }) ||
            !std::isfinite(vertical_view_span) || vertical_view_span <= 0.0F) {
            throw GlesSceneError("Camera target or view span is invalid");
        }
        camera_target_ = target;
        camera_vertical_span_ = vertical_view_span;
    }

    void clear_camera_target() noexcept { camera_target_.reset(); }

    [[nodiscard]] std::array<float, 3> ground_position_at_pixel(
        int pixel_x, int pixel_y_from_bottom, int width, int height,
        float ground_height) const {
        if (width <= 0 || height <= 0 || width != last_width_ || height != last_height_ ||
            !(last_scale_x_ > 0.0F) || !(last_scale_y_ > 0.0F) ||
            !std::isfinite(ground_height)) {
            throw GlesSceneError("Camera projection is not ready for screen conversion");
        }
        const float ndc_x = 2.0F * (static_cast<float>(pixel_x) + 0.5F) /
                                static_cast<float>(width) -
                            1.0F;
        const float ndc_y = 2.0F * (static_cast<float>(pixel_y_from_bottom) + 0.5F) /
                                static_cast<float>(height) -
                            1.0F;
        const float projected_x = last_center_x_ + ndc_x / last_scale_x_;
        const float projected_y = last_center_y_ + ndc_y / last_scale_y_;
        const float diagonal = (projected_y - ground_height) / 0.35F;
        return {(projected_x + diagonal) * 0.5F, ground_height,
                (diagonal - projected_x) / 1.4F};
    }

private:
    struct Draw {
        GLuint vertex_buffer = 0;
        GLuint texcoord_buffer = 0;
        GLuint index_buffer = 0;
        GLsizei index_count = 0;
        GLuint texture = 0;
        std::array<float, 3> color{};
        bool alpha_blend = false;
    };

    static GLuint upload_texture(std::uint32_t width, std::uint32_t height,
                                 const std::vector<std::uint8_t>& rgba) {
        if (width > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max()) ||
            height > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max())) {
            throw GlesSceneError("Texture dimensions exceed OpenGL ES limits");
        }
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // OGRE texture_unit defaults to wrap. Town roads, terrain and many
        // building atlases intentionally use UVs outside 0..1; clamping them
        // stretches one border texel across whole polygons.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width),
                     static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
        if (glGetError() != GL_NO_ERROR) {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
            throw GlesSceneError("OpenGL ES texture upload failed");
        }
        return texture;
    }

    void calculate_bounds(const FixedSceneGeometry& geometry) {
        minimum_ = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
                    std::numeric_limits<float>::max()};
        maximum_ = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(),
                    std::numeric_limits<float>::lowest()};
        for (const auto& instance : instances_) {
            const auto& mesh = geometry.meshes.at(instance.mesh_index).mesh;
            if (!mesh.bounds.has_value()) {
                throw GlesSceneError("Town mesh has no bounds");
            }
            for (unsigned corner = 0; corner < 8; ++corner) {
                std::array<float, 3> point{};
                for (unsigned axis = 0; axis < 3; ++axis) {
                    const float local = (corner & (1U << axis)) != 0
                                            ? mesh.bounds->maximum[axis]
                                            : mesh.bounds->minimum[axis];
                    point[axis] = instance.transform.scale[axis] * local;
                }
                point[2] = -point[2];
                const float radians = instance.transform.angle * kDegreesToRadians;
                const float cosine = std::cos(radians);
                const float sine = std::sin(radians);
                const float rotated_x = point[0] * cosine + point[2] * sine;
                const float rotated_z = -point[0] * sine + point[2] * cosine;
                point[0] = instance.transform.position[0] + rotated_x;
                point[1] += instance.transform.position[1];
                point[2] = instance.transform.position[2] + rotated_z;
                const auto projected = project(point);
                minimum_.x = std::min(minimum_.x, projected.x);
                minimum_.y = std::min(minimum_.y, projected.y);
                minimum_.depth = std::min(minimum_.depth, projected.depth);
                maximum_.x = std::max(maximum_.x, projected.x);
                maximum_.y = std::max(maximum_.y, projected.y);
                maximum_.depth = std::max(maximum_.depth, projected.depth);
            }
        }
        if (!std::isfinite(minimum_.x) || !std::isfinite(maximum_.x)) {
            throw GlesSceneError("Town scene has no finite geometry bounds");
        }
    }

    std::vector<SceneMeshInstance> instances_;
    std::vector<std::vector<Draw>> draws_by_mesh_;
    std::vector<GLuint> owned_vertex_buffers_;
    std::vector<GLuint> owned_index_buffers_;
    std::vector<GLuint> owned_textures_;
    GLuint program_ = 0;
    GLint translation_location_ = -1;
    GLint object_scale_location_ = -1;
    GLint object_rotation_location_ = -1;
    GLint projection_location_ = -1;
    GLint depth_projection_location_ = -1;
    GLint color_location_ = -1;
    GLint texture_location_ = -1;
    ProjectedPoint minimum_;
    ProjectedPoint maximum_;
    std::optional<std::array<float, 3>> camera_target_;
    float camera_vertical_span_ = 80.0F;
    int last_width_ = 0;
    int last_height_ = 0;
    float last_center_x_ = 0.0F;
    float last_center_y_ = 0.0F;
    float last_scale_x_ = 0.0F;
    float last_scale_y_ = 0.0F;
    GlesSceneRenderStats stats_;
};

GlesSceneRenderer::GlesSceneRenderer(const FixedSceneGeometry& geometry,
                                     const PakArchive& archive,
                                     const OgreMaterialCatalog& materials)
    : implementation_(std::make_unique<Implementation>(geometry, archive, materials)) {}

GlesSceneRenderer::~GlesSceneRenderer() = default;

void GlesSceneRenderer::draw(int width, int height) {
    implementation_->draw(width, height);
}

void GlesSceneRenderer::set_instance_position(std::size_t instance_index,
                                              const std::array<float, 3>& position) {
    implementation_->set_instance_position(instance_index, position);
}

void GlesSceneRenderer::set_instance_visible(std::size_t instance_index, bool visible) {
    implementation_->set_instance_visible(instance_index, visible);
}

void GlesSceneRenderer::set_camera_target(const std::array<float, 3>& target,
                                          float vertical_view_span) {
    implementation_->set_camera_target(target, vertical_view_span);
}

void GlesSceneRenderer::clear_camera_target() noexcept {
    implementation_->clear_camera_target();
}

std::array<float, 3> GlesSceneRenderer::ground_position_at_pixel(
    int pixel_x, int pixel_y_from_bottom, int width, int height,
    float ground_height) const {
    return implementation_->ground_position_at_pixel(pixel_x, pixel_y_from_bottom, width,
                                                     height, ground_height);
}

const GlesSceneRenderStats& GlesSceneRenderer::stats() const noexcept {
    return implementation_->stats();
}

} // namespace torchlight
