#include "torchlight/diagnostic_json.hpp"
#include "torchlight/gles_scene_renderer.hpp"

#include "torchlight/dds_texture.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/png_texture.hpp"
#include "torchlight/skeletal_animation.hpp"

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

constexpr float kOriginalCameraNearClip = 0.1F;
constexpr float kOriginalCameraFarClip = 500.0F;

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
        "attribute vec3 normal;"
        "attribute vec2 texcoord;"
        "attribute vec4 vertex_color;"
        "uniform vec3 translation;"
        "uniform vec3 object_scale;"
        "uniform mat3 object_rotation;"
        "uniform vec4 projection;"
        "uniform vec2 depth_projection;"
        "uniform vec3 camera_position;"
        "uniform vec3 camera_right;"
        "uniform vec3 camera_up;"
        "uniform vec3 camera_forward;"
        "uniform vec4 camera_projection;"
        "uniform float perspective_camera;"
        "varying vec2 vertex_texcoord;"
        "varying vec4 vertex_diffuse;"
        "varying float vertex_light;"
        "void main() {"
        "  vec3 world = object_rotation * (position * object_scale) + translation;"
        "  float projected_x = world.x - 0.70 * world.z;"
        "  float projected_y = world.y + 0.35 * (world.x + 0.70 * world.z);"
        "  float depth = 0.25 * world.x + 0.50 * world.z - 0.10 * world.y;"
        "  vec3 local_normal = normalize(vec3(normal.x / max(abs(object_scale.x), 0.0001),"
        "                                           normal.y / max(abs(object_scale.y), 0.0001),"
        "                                           normal.z / max(abs(object_scale.z), 0.0001)));"
        "  vec3 world_normal = normalize(object_rotation * local_normal);"
        "  vec3 light_direction = normalize(vec3(-0.35, 0.80, -0.45));"
        "  vertex_light = max(dot(world_normal, light_direction), 0.0);"
        "  if (perspective_camera > 0.5) {"
        "    vec3 camera_relative = world - camera_position;"
        "    float camera_depth = dot(camera_relative, camera_forward);"
        "    float clip_depth = ((camera_projection.w + camera_projection.z) /"
        "                        (camera_projection.w - camera_projection.z)) * camera_depth -"
        "                       (2.0 * camera_projection.w * camera_projection.z) /"
        "                        (camera_projection.w - camera_projection.z);"
        "    gl_Position = vec4(dot(camera_relative, camera_right) /"
        "                           (camera_projection.x * camera_projection.y),"
        "                       dot(camera_relative, camera_up) / camera_projection.x,"
        "                       clip_depth, camera_depth);"
        "  } else {"
        "    gl_Position = vec4((projected_x - projection.x) * projection.z,"
        "                       (projected_y - projection.y) * projection.w,"
        "                       (depth - depth_projection.x) * depth_projection.y, 1.0);"
        "  }"
        "  vertex_texcoord = texcoord;"
        "  vertex_diffuse = vertex_color;"
        "}";
    constexpr const char* fragment_source =
        "precision mediump float;"
        "uniform sampler2D diffuse_texture;"
        "uniform vec3 draw_color;"
        "uniform vec3 material_ambient;"
        "uniform vec3 material_emissive;"
        "uniform float use_vertex_color;"
        "uniform float use_lighting;"
        "uniform float texture_add;"
        "uniform float alpha_reject_reference;"
        "uniform float alpha_reject_inclusive;"
        "varying vec2 vertex_texcoord;"
        "varying vec4 vertex_diffuse;"
        "varying float vertex_light;"
        "void main() {"
        "  vec4 texel = texture2D(diffuse_texture, vertex_texcoord);"
        "  vec3 diffuse_color = mix(draw_color, vertex_diffuse.rgb, use_vertex_color);"
        "  float alpha = texel.a * mix(1.0, vertex_diffuse.a, use_vertex_color);"
        "  if (alpha_reject_reference >= 0.0 &&"
        "      (alpha_reject_inclusive > 0.5"
        "           ? alpha < alpha_reject_reference"
        "           : alpha <= alpha_reject_reference)) discard;"
        "  vec3 lit = material_emissive + 0.55 * material_ambient +"
        "             (0.35 + 0.55 * vertex_light) * diffuse_color;"
        "  vec3 current = mix(diffuse_color, lit, use_lighting);"
        "  vec3 modulated = texel.rgb * current;"
        "  vec3 added = min(texel.rgb + current, vec3(1.0));"
        "  gl_FragColor = vec4(mix(modulated, added, texture_add), alpha);"
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
    glBindAttribLocation(program, 2, "normal");
    glBindAttribLocation(program, 3, "vertex_color");
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

void upload_rotation(GLint location, const Matrix3& rotation) {
    // GLES requires column-major storage and transpose=GL_FALSE.
    const Matrix3 columns{rotation[0], rotation[3], rotation[6],
                          rotation[1], rotation[4], rotation[7],
                          rotation[2], rotation[5], rotation[8]};
    glUniformMatrix3fv(location, 1, GL_FALSE, columns.data());
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
        : instances_(geometry.instances),
          instance_pose_buffers_(geometry.instances.size()), program_(create_program()) {
        stats_.mesh_resources = geometry.meshes.size();
        stats_.instances = geometry.instances.size();
        draws_by_mesh_.resize(geometry.meshes.size());
        animated_meshes_.resize(geometry.meshes.size(), false);
        shadow_radius_by_mesh_.resize(geometry.meshes.size(), 0.0F);
        std::unordered_map<std::string, GLuint> textures;
        const auto fallback_texture = upload_texture(1, 1, {255U, 255U, 255U, 255U});
        shadow_texture_ = fallback_texture;
        owned_textures_.push_back(fallback_texture);
        for (std::size_t mesh_index = 0; mesh_index < geometry.meshes.size(); ++mesh_index) {
            const auto& mesh_resource = geometry.meshes[mesh_index];
            const auto& mesh = mesh_resource.mesh;
            GLuint mesh_texture_override = 0;
            if (!mesh_resource.texture_layers.empty()) {
                std::string texture_key = "layers";
                std::vector<PngImage> layers;
                layers.reserve(mesh_resource.texture_layers.size());
                for (const auto& layer_path : mesh_resource.texture_layers) {
                    texture_key += "|" + layer_path;
                    const auto* layer_entry = archive.find_normalized(layer_path);
                    if (layer_entry == nullptr || !is_png_path(layer_entry->name)) {
                        throw GlesSceneError(
                            "Scene texture layer is absent or is not PNG: " + layer_path);
                    }
                    layers.push_back(decode_png(archive.read(*layer_entry)));
                }
                const auto found_texture = textures.find(texture_key);
                if (found_texture != textures.end()) {
                    mesh_texture_override = found_texture->second;
                } else {
                    const auto image = compose_png_layers(layers);
                    mesh_texture_override = upload_texture(
                        image.width, image.height, image.rgba, false, true);
                    textures.emplace(std::move(texture_key), mesh_texture_override);
                    owned_textures_.push_back(mesh_texture_override);
                }
            }
            animated_meshes_[mesh_index] = mesh.skeletally_animated;
            if (mesh.skeletally_animated && mesh.bounds) {
                const float width = mesh.bounds->maximum[0] - mesh.bounds->minimum[0];
                const float depth = mesh.bounds->maximum[2] - mesh.bounds->minimum[2];
                shadow_radius_by_mesh_[mesh_index] =
                    std::clamp(std::max(width, depth) * 0.38F, 0.35F, 3.5F);
            }
            for (const auto& submesh : mesh.submeshes) {
                if (submesh.operation_type != 4 || submesh.indices.empty()) {
                    ++stats_.skipped_batches;
                    continue;
                }
                const auto& source_geometry = geometry_for(mesh, submesh);
                auto found_vertex_buffer = vertex_buffers_.find(&source_geometry);
                GeometryBuffers buffers;
                if (found_vertex_buffer == vertex_buffers_.end()) {
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
                    std::vector<float> normals;
                    normals.reserve(source_geometry.positions.size() * 3U);
                    if (source_geometry.normals.size() == source_geometry.positions.size()) {
                        for (const auto& normal : source_geometry.normals) {
                            normals.insert(normals.end(), normal.begin(), normal.end());
                        }
                    } else {
                        for (std::size_t index = 0;
                             index < source_geometry.positions.size(); ++index) {
                            normals.insert(normals.end(), {0.0F, 1.0F, 0.0F});
                        }
                    }
                    glGenBuffers(1, &buffers.normal);
                    glBindBuffer(GL_ARRAY_BUFFER, buffers.normal);
                    glBufferData(GL_ARRAY_BUFFER,
                                 static_cast<GLsizeiptr>(normals.size() * sizeof(float)),
                                 normals.data(), GL_STATIC_DRAW);
                    std::vector<float> colors;
                    colors.reserve(source_geometry.positions.size() * 4U);
                    if (source_geometry.colors.size() == source_geometry.positions.size()) {
                        for (const auto& color : source_geometry.colors) {
                            colors.insert(colors.end(), color.begin(), color.end());
                        }
                    } else {
                        for (std::size_t index = 0;
                             index < source_geometry.positions.size(); ++index) {
                            colors.insert(colors.end(), {1.0F, 1.0F, 1.0F, 1.0F});
                        }
                    }
                    glGenBuffers(1, &buffers.color);
                    glBindBuffer(GL_ARRAY_BUFFER, buffers.color);
                    glBufferData(GL_ARRAY_BUFFER,
                                 static_cast<GLsizeiptr>(colors.size() * sizeof(float)),
                                 colors.data(), GL_STATIC_DRAW);
                    vertex_buffers_.emplace(&source_geometry, buffers);
                    owned_vertex_buffers_.push_back(buffers.position);
                    owned_vertex_buffers_.push_back(buffers.texcoord);
                    owned_vertex_buffers_.push_back(buffers.normal);
                    owned_vertex_buffers_.push_back(buffers.color);
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
                std::array<float, 3> ambient{};
                std::array<float, 3> emissive{};
                bool textured = false;
                std::string texture_source = "fallback:white";
                bool use_vertex_color = false;
                OgreSceneBlend scene_blend = OgreSceneBlend::replace;
                OgreAlphaCompare alpha_compare = OgreAlphaCompare::always;
                std::uint8_t alpha_rejection_value = 0;
                OgreTextureColorOperation texture_color_operation =
                    OgreTextureColorOperation::modulate;
                bool depth_write = true;
                bool lighting = true;
                bool texture_clamp = false;
                bool texture_filter_linear = true;
                if (const auto* material = materials.find(submesh.material);
                    material != nullptr) {
                    color = material->diffuse;
                    ambient = material->ambient;
                    emissive = material->emissive;
                    use_vertex_color = material->diffuse_vertex_color;
                    scene_blend = material->scene_blend;
                    alpha_compare = material->alpha_compare;
                    alpha_rejection_value = material->alpha_rejection_value;
                    texture_color_operation = material->texture_color_operation;
                    depth_write = material->depth_write;
                    lighting = material->lighting;
                    texture_clamp = material->texture_clamp;
                    texture_filter_linear = material->texture_filter_linear;
                    if (mesh_texture_override != 0) {
                        texture = mesh_texture_override;
                        texture_source = "layers";
                        for (const auto& layer : mesh_resource.texture_layers) texture_source += "|" + layer;
                        textured = true;
                    } else if (!material->primary_texture.empty()) {
                        if (const auto* entry = resolve_material_texture(
                                archive, *material, material->primary_texture)) {
                            if (is_dds_path(entry->name) || is_png_path(entry->name)) {
                                texture_source = entry->name;
                                const auto texture_key =
                                    entry->name + (texture_clamp ? "|clamp" : "|wrap") +
                                    (texture_filter_linear ? "|linear" : "|nearest");
                                const auto found_texture = textures.find(texture_key);
                                if (found_texture != textures.end()) {
                                    texture = found_texture->second;
                                } else {
                                    const auto bytes = archive.read(*entry);
                                    if (is_dds_path(entry->name)) {
                                        const auto image = decode_dds(bytes);
                                        texture = upload_dds_texture(
                                            image, texture_clamp,
                                            texture_filter_linear);
                                    } else {
                                        const auto image = decode_png(bytes);
                                        texture = upload_texture(
                                            image.width, image.height, image.rgba,
                                            texture_clamp, texture_filter_linear);
                                    }
                                    textures.emplace(texture_key, texture);
                                    owned_textures_.push_back(texture);
                                }
                                textured = true;
                            }
                        }
                    }
                }
                Draw draw;
                draw.material_name = submesh.material;
                draw.texture_source = std::move(texture_source);
                draw.textured = textured;
                draw.source = &source_geometry;
                draw.vertex_buffer = buffers.position;
                draw.texcoord_buffer = buffers.texcoord;
                draw.normal_buffer = buffers.normal;
                draw.color_buffer = buffers.color;
                draw.index_buffer = index_buffer;
                draw.index_count = checked_count(indices.size());
                draw.texture = texture;
                draw.color = color;
                draw.ambient = ambient;
                draw.emissive = emissive;
                draw.scene_blend = scene_blend;
                draw.alpha_compare = alpha_compare;
                draw.alpha_rejection_value = alpha_rejection_value;
                draw.texture_color_operation = texture_color_operation;
                draw.depth_write = depth_write;
                draw.lighting = lighting;
                draw.use_vertex_color = use_vertex_color;
                draws_by_mesh_[mesh_index].push_back(std::move(draw));
                stats_.textured_batches += static_cast<std::size_t>(textured);
                stats_.fallback_batches += static_cast<std::size_t>(!textured);
                ++stats_.draw_batches;
            }
        }
        stats_.texture_resources = textures.size();
        initialize_shadow_buffers();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        if (glGetError() != GL_NO_ERROR) {
            throw GlesSceneError("OpenGL ES buffer upload failed");
        }
        calculate_bounds(geometry);
        for (const auto& instance : instances_) {
            stats_.shadow_instances += static_cast<std::size_t>(
                instance.visible && animated_meshes_.at(instance.mesh_index));
            for (const auto& draw : draws_by_mesh_.at(instance.mesh_index)) {
                stats_.placed_triangles += static_cast<std::uint64_t>(draw.index_count) / 3U;
            }
        }

        translation_location_ = glGetUniformLocation(program_, "translation");
        object_scale_location_ = glGetUniformLocation(program_, "object_scale");
        object_rotation_location_ = glGetUniformLocation(program_, "object_rotation");
        projection_location_ = glGetUniformLocation(program_, "projection");
        depth_projection_location_ = glGetUniformLocation(program_, "depth_projection");
        camera_position_location_ = glGetUniformLocation(program_, "camera_position");
        camera_right_location_ = glGetUniformLocation(program_, "camera_right");
        camera_up_location_ = glGetUniformLocation(program_, "camera_up");
        camera_forward_location_ = glGetUniformLocation(program_, "camera_forward");
        camera_projection_location_ = glGetUniformLocation(program_, "camera_projection");
        perspective_camera_location_ = glGetUniformLocation(program_, "perspective_camera");
        color_location_ = glGetUniformLocation(program_, "draw_color");
        ambient_location_ = glGetUniformLocation(program_, "material_ambient");
        emissive_location_ = glGetUniformLocation(program_, "material_emissive");
        texture_location_ = glGetUniformLocation(program_, "diffuse_texture");
        vertex_color_location_ = glGetUniformLocation(program_, "use_vertex_color");
        lighting_location_ = glGetUniformLocation(program_, "use_lighting");
        texture_add_location_ = glGetUniformLocation(program_, "texture_add");
        alpha_reject_reference_location_ =
            glGetUniformLocation(program_, "alpha_reject_reference");
        alpha_reject_inclusive_location_ =
            glGetUniformLocation(program_, "alpha_reject_inclusive");
        if (translation_location_ < 0 || object_scale_location_ < 0 ||
            object_rotation_location_ < 0 || projection_location_ < 0 ||
            depth_projection_location_ < 0 || camera_position_location_ < 0 ||
            camera_right_location_ < 0 || camera_up_location_ < 0 ||
            camera_forward_location_ < 0 || camera_projection_location_ < 0 ||
            perspective_camera_location_ < 0 || color_location_ < 0 ||
            ambient_location_ < 0 || emissive_location_ < 0 ||
            texture_location_ < 0 || vertex_color_location_ < 0 ||
            lighting_location_ < 0 || texture_add_location_ < 0 ||
            alpha_reject_reference_location_ < 0 ||
            alpha_reject_inclusive_location_ < 0) {
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
            const auto pose = game_camera_pose(*camera_target_, camera_distance_);
            last_camera_ = make_camera_projection(
                pose.position, pose.target,
                aspect, 45.0F, kOriginalCameraNearClip, kOriginalCameraFarClip);
            last_perspective_ready_ = true;
        } else {
            const float extent_x = std::max(0.001F, maximum_.x - minimum_.x);
            const float extent_y = std::max(0.001F, maximum_.y - minimum_.y);
            scale_x = std::min(1.90F / extent_x, 1.90F / (extent_y * aspect));
            scale_y = scale_x * aspect;
            last_perspective_ready_ = false;
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
        glUniform3fv(camera_position_location_, 1, last_camera_.position.data());
        glUniform3fv(camera_right_location_, 1, last_camera_.right.data());
        glUniform3fv(camera_up_location_, 1, last_camera_.up.data());
        glUniform3fv(camera_forward_location_, 1, last_camera_.forward.data());
        glUniform4f(camera_projection_location_, last_camera_.tangent_half_fov, aspect,
                    kOriginalCameraNearClip, kOriginalCameraFarClip);
        glUniform1f(perspective_camera_location_, camera_target_.has_value() ? 1.0F : 0.0F);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        for (std::size_t instance_index = 0;
             instance_index < instances_.size(); ++instance_index) {
            const auto& instance = instances_[instance_index];
            if (!instance.visible) {
                continue;
            }
            glUniform3fv(translation_location_, 1, instance.transform.position.data());
            glUniform3fv(object_scale_location_, 1, instance.transform.scale.data());
            upload_rotation(object_rotation_location_, instance.transform.orientation);
            for (const auto& draw : draws_by_mesh_.at(instance.mesh_index)) {
                auto vertex_buffer = draw.vertex_buffer;
                auto normal_buffer = draw.normal_buffer;
                const auto pose_buffers =
                    instance_pose_buffers_[instance_index].find(draw.source);
                if (pose_buffers != instance_pose_buffers_[instance_index].end()) {
                    vertex_buffer = pose_buffers->second.position;
                    normal_buffer = pose_buffers->second.normal;
                }
                if (draw.scene_blend == OgreSceneBlend::replace) {
                    glDisable(GL_BLEND);
                } else {
                    glEnable(GL_BLEND);
                    if (draw.scene_blend == OgreSceneBlend::alpha) {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    } else if (draw.scene_blend == OgreSceneBlend::add) {
                        glBlendFunc(GL_ONE, GL_ONE);
                    } else {
                        glBlendFunc(GL_DST_COLOR, GL_ZERO);
                    }
                }
                glDepthMask(draw.depth_write ? GL_TRUE : GL_FALSE);
                const auto* draw_color = draw.color.data();
                const auto* material_ambient = draw.ambient.data();
                if (instance.material_color_override.has_value()) {
                    draw_color = instance.material_color_override->data();
                    material_ambient = instance.material_color_override->data();
                }
                glUniform3fv(color_location_, 1, draw_color);
                glUniform3fv(ambient_location_, 1, material_ambient);
                glUniform3fv(emissive_location_, 1, draw.emissive.data());
                glUniform1f(vertex_color_location_, draw.use_vertex_color ? 1.0F : 0.0F);
                glUniform1f(lighting_location_, draw.lighting ? 1.0F : 0.0F);
                glUniform1f(texture_add_location_,
                            draw.texture_color_operation ==
                                    OgreTextureColorOperation::add
                                ? 1.0F
                                : 0.0F);
                const float alpha_reference =
                    draw.alpha_compare == OgreAlphaCompare::always
                        ? -1.0F
                        : static_cast<float>(draw.alpha_rejection_value) / 255.0F;
                glUniform1f(alpha_reject_reference_location_, alpha_reference);
                glUniform1f(alpha_reject_inclusive_location_,
                            draw.alpha_compare == OgreAlphaCompare::greater_equal
                                ? 1.0F
                                : 0.0F);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ARRAY_BUFFER, draw.texcoord_buffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ARRAY_BUFFER, draw.color_buffer);
                glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw.index_buffer);
                glBindTexture(GL_TEXTURE_2D, draw.texture);
                glDrawElements(GL_TRIANGLES, draw.index_count, GL_UNSIGNED_SHORT, nullptr);
            }
        }
        draw_character_shadows();
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
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

    void set_instance_angle(std::size_t instance_index, float angle_degrees) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        if (!std::isfinite(angle_degrees)) {
            throw GlesSceneError("Scene instance angle is not finite");
        }
        instances_[instance_index].transform.orientation = yaw_rotation(angle_degrees);
    }

    void set_instance_transform(std::size_t instance_index,
                                const LayoutWorldTransform& transform) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        const auto finite = [](const auto& values) {
            return std::all_of(values.begin(), values.end(),
                               [](float value) { return std::isfinite(value); });
        };
        if (!finite(transform.position) || !finite(transform.orientation) ||
            !finite(transform.scale)) {
            throw GlesSceneError("Scene instance transform is not finite");
        }
        instances_[instance_index].transform = transform;
    }

    void set_instance_visible(std::size_t instance_index, bool visible) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        instances_[instance_index].visible = visible;
    }

    void set_mesh_pose(const OgreMeshPose& pose) {
        for (const auto& geometry : pose.geometries) {
            if (geometry.source == nullptr ||
                geometry.positions.size() != geometry.source->positions.size() ||
                geometry.normals.size() != geometry.source->normals.size()) {
                throw GlesSceneError("Skeletal pose geometry does not match its source mesh");
            }
            const auto buffers = vertex_buffers_.find(geometry.source);
            if (buffers == vertex_buffers_.end()) {
                throw GlesSceneError("Skeletal pose source mesh is absent from the renderer");
            }
            std::vector<float> positions;
            positions.reserve(geometry.positions.size() * 3U);
            for (const auto& position : geometry.positions) {
                positions.insert(positions.end(), position.begin(), position.end());
            }
            std::vector<float> normals;
            normals.reserve(geometry.normals.size() * 3U);
            for (const auto& normal : geometry.normals) {
                normals.insert(normals.end(), normal.begin(), normal.end());
            }
            glBindBuffer(GL_ARRAY_BUFFER, buffers->second.position);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            static_cast<GLsizeiptr>(positions.size() * sizeof(float)),
                            positions.data());
            glBindBuffer(GL_ARRAY_BUFFER, buffers->second.normal);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            static_cast<GLsizeiptr>(normals.size() * sizeof(float)),
                            normals.data());
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if (glGetError() != GL_NO_ERROR) {
            throw GlesSceneError("OpenGL ES skeletal pose upload failed");
        }
    }

    void set_instance_pose(std::size_t instance_index, const OgreMeshPose& pose) {
        if (instance_index >= instances_.size()) {
            throw GlesSceneError("Scene instance index is out of range");
        }
        const auto& mesh_draws = draws_by_mesh_.at(instances_[instance_index].mesh_index);
        auto& instance_buffers = instance_pose_buffers_[instance_index];
        for (const auto& geometry : pose.geometries) {
            if (geometry.source == nullptr ||
                geometry.positions.size() != geometry.source->positions.size() ||
                geometry.normals.size() != geometry.source->normals.size()) {
                throw GlesSceneError("Skeletal pose geometry does not match its source mesh");
            }
            if (std::none_of(mesh_draws.begin(), mesh_draws.end(), [&](const auto& draw) {
                    return draw.source == geometry.source;
                })) {
                throw GlesSceneError("Skeletal pose does not belong to the scene instance");
            }
            auto found = instance_buffers.find(geometry.source);
            if (found == instance_buffers.end()) {
                GeometryBuffers buffers;
                glGenBuffers(1, &buffers.position);
                glBindBuffer(GL_ARRAY_BUFFER, buffers.position);
                glBufferData(GL_ARRAY_BUFFER,
                             static_cast<GLsizeiptr>(geometry.positions.size() *
                                                    3U * sizeof(float)),
                             nullptr, GL_DYNAMIC_DRAW);
                glGenBuffers(1, &buffers.normal);
                glBindBuffer(GL_ARRAY_BUFFER, buffers.normal);
                glBufferData(GL_ARRAY_BUFFER,
                             static_cast<GLsizeiptr>(geometry.normals.size() *
                                                    3U * sizeof(float)),
                             nullptr, GL_DYNAMIC_DRAW);
                owned_vertex_buffers_.push_back(buffers.position);
                owned_vertex_buffers_.push_back(buffers.normal);
                found = instance_buffers.emplace(geometry.source, buffers).first;
            }
            std::vector<float> positions;
            positions.reserve(geometry.positions.size() * 3U);
            for (const auto& position : geometry.positions) {
                positions.insert(positions.end(), position.begin(), position.end());
            }
            std::vector<float> normals;
            normals.reserve(geometry.normals.size() * 3U);
            for (const auto& normal : geometry.normals) {
                normals.insert(normals.end(), normal.begin(), normal.end());
            }
            glBindBuffer(GL_ARRAY_BUFFER, found->second.position);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            static_cast<GLsizeiptr>(positions.size() * sizeof(float)),
                            positions.data());
            glBindBuffer(GL_ARRAY_BUFFER, found->second.normal);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            static_cast<GLsizeiptr>(normals.size() * sizeof(float)),
                            normals.data());
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if (glGetError() != GL_NO_ERROR) {
            throw GlesSceneError("OpenGL ES instance skeletal pose upload failed");
        }
    }

    void set_camera_target(const std::array<float, 3>& target, float camera_distance) {
        if (!std::all_of(target.begin(), target.end(),
                         [](float value) { return std::isfinite(value); }) ||
            !std::isfinite(camera_distance) || camera_distance <= 0.0F) {
            throw GlesSceneError("Camera target or distance is invalid");
        }
        camera_target_ = target;
        camera_distance_ = camera_distance;
    }

    void clear_camera_target() noexcept { camera_target_.reset(); }

    [[nodiscard]] std::array<float, 3> ground_position_at_pixel(
        int pixel_x, int pixel_y_from_bottom, int width, int height,
        float ground_height) const {
        if (width <= 0 || height <= 0 || width != last_width_ || height != last_height_ ||
            !std::isfinite(ground_height)) {
            throw GlesSceneError("Camera projection is not ready for screen conversion");
        }
        const float ndc_x = 2.0F * (static_cast<float>(pixel_x) + 0.5F) /
                                static_cast<float>(width) -
                            1.0F;
        const float ndc_y = 2.0F * (static_cast<float>(pixel_y_from_bottom) + 0.5F) /
                                static_cast<float>(height) -
                            1.0F;
        if (last_perspective_ready_) {
            return last_camera_.ground_at_ndc(ndc_x, ndc_y, ground_height);
        }
        if (!(last_scale_x_ > 0.0F) || !(last_scale_y_ > 0.0F)) {
            throw GlesSceneError("Orthographic camera projection is not ready");
        }
        const float projected_x = last_center_x_ + ndc_x / last_scale_x_;
        const float projected_y = last_center_y_ + ndc_y / last_scale_y_;
        const float diagonal = (projected_y - ground_height) / 0.35F;
        return {(projected_x + diagonal) * 0.5F, ground_height,
                (diagonal - projected_x) / 1.4F};
    }

    std::array<float, 2> pixel_position_of_world(const Vector3& world) const {
        if (!last_perspective_ready_ || last_width_ <= 0 || last_height_ <= 0)
            throw GlesSceneError("Perspective camera has not rendered a frame");
        const auto ndc = last_camera_.project_ndc(world);
        return {(ndc[0] + 1) * 0.5F * last_width_ - 0.5F,
                (1 - ndc[1]) * 0.5F * last_height_ - 0.5F};
    }
    bool instance_visible(std::size_t index) const { return instances_.at(index).visible; }

    void write_diagnostics(std::ostream& out) const {
        using namespace diagnostic;
        out << "{\"schema\":1,\"evidence\":\"port-regression-not-original\","
            << "\"viewport\":[" << last_width_ << ',' << last_height_ << "],\"camera\":{";
        out << "\"view\":"; array(out, last_camera_.view);
        out << ",\"projection\":"; array(out, last_camera_.projection);
        out << ",\"position\":"; array(out, last_camera_.position);
        out << "},\"pipeline\":{\"depth_test\":true,\"depth_func\":\"LEQUAL\","
            << "\"cull\":false,\"shadow_pass\":\"prototype-contact-shadow-after-meshes\"},"
            << "\"light\":{\"direction\":[-0.35,0.8,-0.45],\"status\":\"prototype-shader\"},\"instances\":[";
        for (std::size_t i = 0; i < instances_.size(); ++i) {
            if (i) out << ',';
            const auto& item = instances_[i];
            out << "{\"index\":" << i << ",\"mesh\":" << item.mesh_index
                << ",\"visible\":" << (item.visible ? "true" : "false")
                << ",\"entity\":" << item.runtime_entity_id << ",\"position\":";
            array(out, item.transform.position);
            out << ",\"rotation\":"; array(out, item.transform.orientation);
            out << ",\"scale\":"; array(out, item.transform.scale);
            out << ",\"passes\":[";
            bool comma = false;
            for (const auto& draw : draws_by_mesh_.at(item.mesh_index)) {
                if (comma) out << ',';
                comma = true;
                out << "{\"material\":"; string(out, draw.material_name);
                out << ",\"texture\":"; string(out, draw.texture_source);
                out << ",\"fallback\":" << (!draw.textured ? "true" : "false")
                    << ",\"index_count\":" << draw.index_count
                    << ",\"blend\":" << static_cast<int>(draw.scene_blend)
                    << ",\"depth_write\":" << (draw.depth_write ? "true" : "false")
                    << ",\"lighting\":" << (draw.lighting ? "true" : "false")
                    << ",\"vertex_color\":" << (draw.use_vertex_color ? "true" : "false")
                    << ",\"texture_op\":" << static_cast<int>(draw.texture_color_operation)
                    << ",\"alpha_compare\":" << static_cast<int>(draw.alpha_compare)
                    << ",\"alpha_value\":" << static_cast<unsigned>(draw.alpha_rejection_value)
                    << ",\"diffuse\":";
                if (item.material_color_override) {
                    const auto& rgba = *item.material_color_override;
                    array(out, std::array<float, 3>{rgba[0], rgba[1], rgba[2]});
                }
                else array(out, draw.color);
                out << ",\"ambient\":";
                if (item.material_color_override) {
                    const auto& rgba = *item.material_color_override;
                    array(out, std::array<float, 3>{rgba[0], rgba[1], rgba[2]});
                }
                else array(out, draw.ambient);
                out << ",\"emissive\":"; array(out, draw.emissive);
                out << '}';
            }
            out << "]}";
        }
        out << "]}";
    }

private:
    struct GeometryBuffers {
        GLuint position = 0;
        GLuint texcoord = 0;
        GLuint normal = 0;
        GLuint color = 0;
    };

    struct Draw {
        std::string material_name, texture_source;
        bool textured = false;
        const OgreGeometry* source = nullptr;
        GLuint vertex_buffer = 0;
        GLuint texcoord_buffer = 0;
        GLuint normal_buffer = 0;
        GLuint color_buffer = 0;
        GLuint index_buffer = 0;
        GLsizei index_count = 0;
        GLuint texture = 0;
        std::array<float, 3> color{};
        std::array<float, 3> ambient{};
        std::array<float, 3> emissive{};
        OgreSceneBlend scene_blend = OgreSceneBlend::replace;
        OgreAlphaCompare alpha_compare = OgreAlphaCompare::always;
        std::uint8_t alpha_rejection_value = 0;
        OgreTextureColorOperation texture_color_operation =
            OgreTextureColorOperation::modulate;
        bool depth_write = true;
        bool lighting = true;
        bool use_vertex_color = false;
    };

    void initialize_shadow_buffers() {
        constexpr std::size_t kSegments = 20U;
        constexpr float kPi = 3.14159265358979323846F;
        std::vector<float> positions{0.0F, 0.0F, 0.0F};
        std::vector<float> texcoords{0.5F, 0.5F};
        std::vector<float> normals{0.0F, 1.0F, 0.0F};
        std::vector<float> colors{0.0F, 0.0F, 0.0F, 0.34F};
        for (std::size_t segment = 0; segment <= kSegments; ++segment) {
            const float angle = 2.0F * kPi * static_cast<float>(segment) /
                                static_cast<float>(kSegments);
            positions.insert(positions.end(), {std::cos(angle), 0.0F, std::sin(angle)});
            texcoords.insert(texcoords.end(), {0.0F, 0.0F});
            normals.insert(normals.end(), {0.0F, 1.0F, 0.0F});
            colors.insert(colors.end(), {0.0F, 0.0F, 0.0F, 0.0F});
        }
        shadow_vertex_count_ = checked_count(kSegments + 2U);
        const auto upload = [&](GLuint& buffer, const std::vector<float>& values) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER,
                         static_cast<GLsizeiptr>(values.size() * sizeof(float)),
                         values.data(), GL_STATIC_DRAW);
            owned_vertex_buffers_.push_back(buffer);
        };
        upload(shadow_buffers_.position, positions);
        upload(shadow_buffers_.texcoord, texcoords);
        upload(shadow_buffers_.normal, normals);
        upload(shadow_buffers_.color, colors);
    }

    void draw_character_shadows() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        const std::array<float, 3> black{};
        glUniform3fv(color_location_, 1, black.data());
        glUniform3fv(ambient_location_, 1, black.data());
        glUniform3fv(emissive_location_, 1, black.data());
        glUniform1f(vertex_color_location_, 1.0F);
        glUniform1f(lighting_location_, 0.0F);
        glUniform1f(texture_add_location_, 0.0F);
        glUniform1f(alpha_reject_reference_location_, -1.0F);
        glUniform1f(alpha_reject_inclusive_location_, 0.0F);
        glBindBuffer(GL_ARRAY_BUFFER, shadow_buffers_.position);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, shadow_buffers_.texcoord);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, shadow_buffers_.normal);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, shadow_buffers_.color);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindTexture(GL_TEXTURE_2D, shadow_texture_);
        for (std::size_t instance_index = 0;
             instance_index < instances_.size(); ++instance_index) {
            const auto& instance = instances_[instance_index];
            if (!instance.visible ||
                !animated_meshes_.at(instance.mesh_index)) {
                continue;
            }
            auto position = instance.transform.position;
            position[1] += 0.025F;
            const float radius = shadow_radius_by_mesh_.at(instance.mesh_index) *
                                 std::max(std::abs(instance.transform.scale[0]),
                                          std::abs(instance.transform.scale[2]));
            const std::array<float, 3> scale{radius, 1.0F, radius * 0.72F};
            glUniform3fv(translation_location_, 1, position.data());
            glUniform3fv(object_scale_location_, 1, scale.data());
            upload_rotation(object_rotation_location_, kIdentityRotation);
            glDrawArrays(GL_TRIANGLE_FAN, 0, shadow_vertex_count_);
        }
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }

    static GLuint upload_texture(std::uint32_t width, std::uint32_t height,
                                 const std::vector<std::uint8_t>& rgba,
                                 bool clamp = false, bool linear_filter = true) {
        if (width > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max()) ||
            height > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max())) {
            throw GlesSceneError("Texture dimensions exceed OpenGL ES limits");
        }
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const auto mag_filter = linear_filter ? GL_LINEAR : GL_NEAREST;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        // OGRE texture_unit defaults to wrap. Town roads, terrain and many
        // building atlases intentionally use UVs outside 0..1; clamping them
        // stretches one border texel across whole polygons.
        const auto address_mode = clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, address_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, address_mode);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width),
                     static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
        if (linear_filter && (width > 1U || height > 1U)) {
            glGenerateMipmap(GL_TEXTURE_2D);
            // OGRE 1.6's default TFO_BILINEAR uses linear texel filtering and
            // selects the nearest authored/generated mip level.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR_MIPMAP_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag_filter);
        }
        if (glGetError() != GL_NO_ERROR) {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
            throw GlesSceneError("OpenGL ES texture upload failed");
        }
        return texture;
    }

    static GLuint upload_dds_texture(const DdsImage& image, bool clamp,
                                     bool linear_filter) {
        if (image.width > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max()) ||
            image.height > static_cast<std::uint32_t>(std::numeric_limits<GLsizei>::max())) {
            throw GlesSceneError("Texture dimensions exceed OpenGL ES limits");
        }
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const auto mag_filter = linear_filter ? GL_LINEAR : GL_NEAREST;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        const auto address_mode = clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, address_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, address_mode);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     static_cast<GLsizei>(image.width),
                     static_cast<GLsizei>(image.height), 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image.rgba.data());
        for (std::size_t index = 0; index < image.additional_mipmaps.size(); ++index) {
            const auto& level = image.additional_mipmaps[index];
            glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(index + 1U), GL_RGBA,
                         static_cast<GLsizei>(level.width),
                         static_cast<GLsizei>(level.height), 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, level.rgba.data());
        }
        if (linear_filter && !image.additional_mipmaps.empty()) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR_MIPMAP_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag_filter);
        }
        if (glGetError() != GL_NO_ERROR) {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
            throw GlesSceneError("OpenGL ES DDS texture upload failed");
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
                    point[axis] = local;
                }
                point = transform_point(instance.transform.position,
                    instance.transform.orientation, instance.transform.scale, point);
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
    std::unordered_map<const OgreGeometry*, GeometryBuffers> vertex_buffers_;
    std::vector<std::unordered_map<const OgreGeometry*, GeometryBuffers>>
        instance_pose_buffers_;
    std::vector<bool> animated_meshes_;
    std::vector<float> shadow_radius_by_mesh_;
    GeometryBuffers shadow_buffers_;
    GLsizei shadow_vertex_count_ = 0;
    GLuint shadow_texture_ = 0;
    std::vector<GLuint> owned_vertex_buffers_;
    std::vector<GLuint> owned_index_buffers_;
    std::vector<GLuint> owned_textures_;
    GLuint program_ = 0;
    GLint translation_location_ = -1;
    GLint object_scale_location_ = -1;
    GLint object_rotation_location_ = -1;
    GLint projection_location_ = -1;
    GLint depth_projection_location_ = -1;
    GLint camera_position_location_ = -1;
    GLint camera_right_location_ = -1;
    GLint camera_up_location_ = -1;
    GLint camera_forward_location_ = -1;
    GLint camera_projection_location_ = -1;
    GLint perspective_camera_location_ = -1;
    GLint color_location_ = -1;
    GLint ambient_location_ = -1;
    GLint emissive_location_ = -1;
    GLint texture_location_ = -1;
    GLint vertex_color_location_ = -1;
    GLint lighting_location_ = -1;
    GLint texture_add_location_ = -1;
    GLint alpha_reject_reference_location_ = -1;
    GLint alpha_reject_inclusive_location_ = -1;
    ProjectedPoint minimum_;
    ProjectedPoint maximum_;
    std::optional<std::array<float, 3>> camera_target_;
    float camera_distance_ = 28.5F;
    int last_width_ = 0;
    int last_height_ = 0;
    float last_center_x_ = 0.0F;
    float last_center_y_ = 0.0F;
    float last_scale_x_ = 0.0F;
    float last_scale_y_ = 0.0F;
    CameraProjection last_camera_{};
    bool last_perspective_ready_ = false;
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

void GlesSceneRenderer::set_instance_angle(std::size_t instance_index,
                                           float angle_degrees) {
    implementation_->set_instance_angle(instance_index, angle_degrees);
}

void GlesSceneRenderer::set_instance_transform(
    std::size_t instance_index, const LayoutWorldTransform& transform) {
    implementation_->set_instance_transform(instance_index, transform);
}

void GlesSceneRenderer::set_instance_visible(std::size_t instance_index, bool visible) {
    implementation_->set_instance_visible(instance_index, visible);
}

bool GlesSceneRenderer::instance_visible(std::size_t instance_index) const {
    return implementation_->instance_visible(instance_index);
}

void GlesSceneRenderer::set_mesh_pose(const OgreMeshPose& pose) {
    implementation_->set_mesh_pose(pose);
}

void GlesSceneRenderer::set_instance_pose(std::size_t instance_index,
                                          const OgreMeshPose& pose) {
    implementation_->set_instance_pose(instance_index, pose);
}

void GlesSceneRenderer::set_camera_target(const std::array<float, 3>& target,
                                          float camera_distance) {
    implementation_->set_camera_target(target, camera_distance);
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

std::array<float, 2> GlesSceneRenderer::pixel_position_of_world(const Vector3& world) const {
    return implementation_->pixel_position_of_world(world);
}
void GlesSceneRenderer::write_diagnostics(std::ostream& out) const {
    implementation_->write_diagnostics(out);
}

} // namespace torchlight
