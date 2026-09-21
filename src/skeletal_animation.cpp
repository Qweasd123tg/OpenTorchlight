#include "torchlight/skeletal_animation.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace torchlight {
namespace {

struct Transform {
    std::array<float, 3> position{};
    std::array<float, 4> rotation{1.0F, 0.0F, 0.0F, 0.0F};
    std::array<float, 3> scale{1.0F, 1.0F, 1.0F};
};

std::array<float, 4> normalize_quaternion(std::array<float, 4> value) {
    const float length = std::sqrt(value[0] * value[0] + value[1] * value[1] +
                                   value[2] * value[2] + value[3] * value[3]);
    if (!(length > 0.000001F) || !std::isfinite(length)) {
        throw OgreSkeletonError("OGRE animation contains an invalid quaternion");
    }
    for (auto& component : value) {
        component /= length;
    }
    return value;
}

std::array<float, 4> multiply_quaternion(const std::array<float, 4>& left,
                                         const std::array<float, 4>& right) {
    return normalize_quaternion({
        left[0] * right[0] - left[1] * right[1] - left[2] * right[2] - left[3] * right[3],
        left[0] * right[1] + left[1] * right[0] + left[2] * right[3] - left[3] * right[2],
        left[0] * right[2] - left[1] * right[3] + left[2] * right[0] + left[3] * right[1],
        left[0] * right[3] + left[1] * right[2] - left[2] * right[1] + left[3] * right[0]});
}

std::array<float, 3> rotate_vector(const std::array<float, 4>& rotation,
                                   const std::array<float, 3>& vector) {
    const std::array<float, 3> axis{rotation[1], rotation[2], rotation[3]};
    const std::array<float, 3> twice_cross{
        2.0F * (axis[1] * vector[2] - axis[2] * vector[1]),
        2.0F * (axis[2] * vector[0] - axis[0] * vector[2]),
        2.0F * (axis[0] * vector[1] - axis[1] * vector[0])};
    return {vector[0] + rotation[0] * twice_cross[0] +
                            axis[1] * twice_cross[2] - axis[2] * twice_cross[1],
            vector[1] + rotation[0] * twice_cross[1] +
                            axis[2] * twice_cross[0] - axis[0] * twice_cross[2],
            vector[2] + rotation[0] * twice_cross[2] +
                            axis[0] * twice_cross[1] - axis[1] * twice_cross[0]};
}

std::array<float, 4> interpolate_quaternion(std::array<float, 4> left,
                                            std::array<float, 4> right, float amount) {
    left = normalize_quaternion(left);
    right = normalize_quaternion(right);
    const float dot = left[0] * right[0] + left[1] * right[1] +
                      left[2] * right[2] + left[3] * right[3];
    if (dot < 0.0F) {
        for (auto& component : right) {
            component = -component;
        }
    }
    std::array<float, 4> result{};
    for (std::size_t index = 0; index < result.size(); ++index) {
        result[index] = left[index] + (right[index] - left[index]) * amount;
    }
    return normalize_quaternion(result);
}

Transform combine(const Transform& parent, const Transform& child) {
    Transform result;
    result.rotation = multiply_quaternion(parent.rotation, child.rotation);
    for (std::size_t index = 0; index < 3; ++index) {
        result.scale[index] = parent.scale[index] * child.scale[index];
    }
    const std::array<float, 3> scaled_child{
        parent.scale[0] * child.position[0], parent.scale[1] * child.position[1],
        parent.scale[2] * child.position[2]};
    const auto rotated_child = rotate_vector(parent.rotation, scaled_child);
    for (std::size_t index = 0; index < 3; ++index) {
        result.position[index] = parent.position[index] + rotated_child[index];
    }
    return result;
}

Transform sample_track(const OgreSkeletonTrack& track, float time, float length,
                       AnimationPlaybackMode playback_mode) {
    if (track.keyframes.empty()) {
        return {};
    }
    const auto* left = &track.keyframes.front();
    const auto* right = left;
    float amount = 0.0F;
    const auto found = std::upper_bound(
        track.keyframes.begin(), track.keyframes.end(), time,
        [](float value, const OgreSkeletonKeyframe& keyframe) { return value < keyframe.time; });
    if (found == track.keyframes.begin()) {
        right = &track.keyframes.front();
        left = right;
    } else if (found == track.keyframes.end()) {
        left = &track.keyframes.back();
        if (playback_mode == AnimationPlaybackMode::loop) {
            right = &track.keyframes.front();
            const float span = right->time + length - left->time;
            amount = span > 0.000001F ? (time - left->time) / span : 0.0F;
        } else {
            right = left;
        }
    } else {
        left = &*(found - 1);
        right = &*found;
        const float span = right->time - left->time;
        amount = span > 0.000001F ? (time - left->time) / span : 0.0F;
    }
    amount = std::clamp(amount, 0.0F, 1.0F);
    Transform result;
    result.rotation = interpolate_quaternion(left->rotation, right->rotation, amount);
    for (std::size_t index = 0; index < 3; ++index) {
        result.position[index] =
            left->translation[index] + (right->translation[index] - left->translation[index]) * amount;
        result.scale[index] =
            left->scale[index] + (right->scale[index] - left->scale[index]) * amount;
    }
    return result;
}

std::vector<Transform> global_transforms(const OgreSkeleton& skeleton,
                                         const std::vector<Transform>& local) {
    std::unordered_map<std::uint16_t, std::size_t> by_handle;
    for (std::size_t index = 0; index < skeleton.bones.size(); ++index) {
        if (!by_handle.emplace(skeleton.bones[index].handle, index).second) {
            throw OgreSkeletonError("OGRE skeleton has duplicate bone handles");
        }
    }
    std::vector<Transform> global(skeleton.bones.size());
    std::vector<std::uint8_t> state(skeleton.bones.size(), 0U);
    std::function<void(std::size_t)> resolve = [&](std::size_t index) {
        if (state[index] == 2U) {
            return;
        }
        if (state[index] == 1U) {
            throw OgreSkeletonError("OGRE skeleton contains a parent cycle");
        }
        state[index] = 1U;
        if (skeleton.bones[index].parent_handle) {
            const auto parent = by_handle.find(*skeleton.bones[index].parent_handle);
            if (parent == by_handle.end()) {
                throw OgreSkeletonError("OGRE skeleton parent handle is absent");
            }
            resolve(parent->second);
            global[index] = combine(global[parent->second], local[index]);
        } else {
            global[index] = local[index];
        }
        state[index] = 2U;
    };
    for (std::size_t index = 0; index < skeleton.bones.size(); ++index) {
        resolve(index);
    }
    return global;
}

std::array<float, 3> skin_position(const std::array<float, 3>& position,
                                   const Transform& bind, const Transform& pose) {
    const std::array<float, 4> inverse_rotation{
        bind.rotation[0], -bind.rotation[1], -bind.rotation[2], -bind.rotation[3]};
    const std::array<float, 3> displaced{
        position[0] - bind.position[0], position[1] - bind.position[1],
        position[2] - bind.position[2]};
    auto local = rotate_vector(inverse_rotation, displaced);
    for (std::size_t index = 0; index < 3; ++index) {
        if (std::abs(bind.scale[index]) < 0.000001F) {
            throw OgreSkeletonError("OGRE bind-pose bone has zero scale");
        }
        local[index] = local[index] / bind.scale[index] * pose.scale[index];
    }
    const auto rotated = rotate_vector(pose.rotation, local);
    return {pose.position[0] + rotated[0], pose.position[1] + rotated[1],
            pose.position[2] + rotated[2]};
}

std::array<float, 3> skin_normal(const std::array<float, 3>& normal,
                                 const Transform& bind, const Transform& pose) {
    const std::array<float, 4> inverse_rotation{
        bind.rotation[0], -bind.rotation[1], -bind.rotation[2], -bind.rotation[3]};
    return rotate_vector(pose.rotation, rotate_vector(inverse_rotation, normal));
}

OgreGeometryPose skin_geometry(const OgreGeometry& geometry,
                               const std::vector<OgreBoneAssignment>& assignments,
                               const std::unordered_map<std::uint16_t, std::size_t>& by_handle,
                               const std::vector<Transform>& bind,
                               const std::vector<Transform>& pose) {
    OgreGeometryPose result;
    result.source = &geometry;
    result.positions.resize(geometry.positions.size(), {0.0F, 0.0F, 0.0F});
    result.normals.resize(geometry.normals.size(), {0.0F, 0.0F, 0.0F});
    std::vector<float> weights(geometry.positions.size(), 0.0F);
    for (const auto& assignment : assignments) {
        if (assignment.vertex_index >= geometry.positions.size() ||
            !std::isfinite(assignment.weight) || assignment.weight < 0.0F) {
            throw OgreSkeletonError("Invalid OGRE vertex bone assignment");
        }
        const auto bone = by_handle.find(assignment.bone_index);
        if (bone == by_handle.end()) {
            throw OgreSkeletonError("OGRE vertex assignment references an absent bone");
        }
        const auto transformed = skin_position(
            geometry.positions[assignment.vertex_index], bind[bone->second], pose[bone->second]);
        for (std::size_t axis = 0; axis < 3; ++axis) {
            result.positions[assignment.vertex_index][axis] += transformed[axis] * assignment.weight;
        }
        if (assignment.vertex_index < geometry.normals.size()) {
            const auto transformed_normal = skin_normal(
                geometry.normals[assignment.vertex_index], bind[bone->second], pose[bone->second]);
            for (std::size_t axis = 0; axis < 3; ++axis) {
                result.normals[assignment.vertex_index][axis] +=
                    transformed_normal[axis] * assignment.weight;
            }
        }
        weights[assignment.vertex_index] += assignment.weight;
    }
    for (std::size_t index = 0; index < weights.size(); ++index) {
        if (weights[index] < 0.000001F) {
            result.positions[index] = geometry.positions[index];
            if (index < geometry.normals.size()) {
                result.normals[index] = geometry.normals[index];
            }
            continue;
        }
        if (std::abs(weights[index] - 1.0F) > 0.0001F) {
            for (auto& component : result.positions[index]) {
                component /= weights[index];
            }
        }
        if (index < result.normals.size()) {
            const auto& normal = result.normals[index];
            const float length = std::hypot(normal[0], std::hypot(normal[1], normal[2]));
            if (length > 0.000001F) {
                for (auto& component : result.normals[index]) {
                    component /= length;
                }
            }
        }
    }
    return result;
}

struct AnimationLayer {
    const OgreSkeleton* skeleton = nullptr;
    std::string_view name;
    float time = 0.0F;
    float weight = 1.0F;
    AnimationPlaybackMode playback_mode = AnimationPlaybackMode::loop;
};

void apply_animation_layer(
    const AnimationLayer& layer,
    const std::unordered_map<std::string, std::size_t>& bind_by_name,
    const std::vector<Transform>& bind_local,
    std::vector<Transform>& pose_local) {
    if (layer.skeleton == nullptr || !std::isfinite(layer.time) ||
        !std::isfinite(layer.weight)) {
        throw OgreSkeletonError("OGRE animation layer is invalid");
    }
    // Ogre::AnimationState::setWeight stores an unclamped float. Negative
    // weights are reachable during interrupted CGenericModel blends and OGRE
    // passes them through NodeAnimationTrack::applyToNode.
    const float weight = layer.weight;
    if (weight == 0.0F) {
        return;
    }
    const auto animation = std::find_if(
        layer.skeleton->animations.begin(), layer.skeleton->animations.end(),
        [&layer](const auto& candidate) { return candidate.name == layer.name; });
    if (animation == layer.skeleton->animations.end() || !(animation->length > 0.0F)) {
        throw OgreSkeletonError("Requested OGRE animation is absent or empty");
    }
    float time = layer.time;
    if (layer.playback_mode == AnimationPlaybackMode::loop) {
        time = std::fmod(time, animation->length);
        if (time < 0.0F) {
            time += animation->length;
        }
    } else {
        time = std::clamp(time, 0.0F, animation->length);
    }
    std::unordered_map<std::uint16_t, const OgreSkeletonTrack*> tracks;
    for (const auto& track : animation->tracks) {
        if (!tracks.emplace(track.bone_handle, &track).second) {
            throw OgreSkeletonError("OGRE animation has duplicate tracks for a bone");
        }
    }
    for (const auto& animation_bone : layer.skeleton->bones) {
        const auto bind_bone = bind_by_name.find(animation_bone.name);
        if (bind_bone == bind_by_name.end()) {
            continue;
        }
        const auto track = tracks.find(animation_bone.handle);
        auto delta = track == tracks.end()
                         ? Transform{}
                         : sample_track(*track->second, time, animation->length,
                                        layer.playback_mode);

        // Torchlight imports each sibling animation skeleton through OGRE 1.6's
        // Skeleton::_mergeSkeletonAnimations. The clip skeletons have different
        // local bind poses, so OGRE adjusts every key (and creates a static track
        // for bones without keys) before applying it to the model skeleton:
        //   destKey = inverse(destBind) * sourceBind * sourceKey
        const auto& destination_bone = bind_local[bind_bone->second];
        for (std::size_t axis = 0; axis < 3; ++axis) {
            if (std::abs(destination_bone.scale[axis]) < 0.000001F) {
                throw OgreSkeletonError("OGRE destination bind-pose bone has zero scale");
            }
            delta.position[axis] +=
                animation_bone.position[axis] - destination_bone.position[axis];
            delta.scale[axis] *=
                animation_bone.scale[axis] / destination_bone.scale[axis];
        }
        const auto inverse_destination_rotation = std::array<float, 4>{
            destination_bone.rotation[0], -destination_bone.rotation[1],
            -destination_bone.rotation[2], -destination_bone.rotation[3]};
        delta.rotation = multiply_quaternion(
            multiply_quaternion(inverse_destination_rotation,
                                normalize_quaternion(animation_bone.orientation)),
            delta.rotation);

        auto& local = pose_local[bind_bone->second];
        for (std::size_t axis = 0; axis < 3; ++axis) {
            local.position[axis] += delta.position[axis] * weight;
            // OGRE 1.6 applies track scale directly; the AnimationState weight
            // affects translation and rotation, but not this scale value.
            local.scale[axis] *= delta.scale[axis];
        }
        local.rotation = multiply_quaternion(
            local.rotation,
            interpolate_quaternion({1.0F, 0.0F, 0.0F, 0.0F},
                                   delta.rotation, weight));
    }
}

OgreMeshPose sample_layers(const OgreMesh& mesh,
                           const OgreSkeleton& bind_skeleton,
                           const std::vector<AnimationLayer>& layers) {
    std::unordered_map<std::uint16_t, std::size_t> bind_by_handle;
    std::unordered_map<std::string, std::size_t> bind_by_name;
    for (std::size_t index = 0; index < bind_skeleton.bones.size(); ++index) {
        bind_by_handle.emplace(bind_skeleton.bones[index].handle, index);
        bind_by_name.emplace(bind_skeleton.bones[index].name, index);
    }

    std::vector<Transform> bind_local;
    bind_local.reserve(bind_skeleton.bones.size());
    for (const auto& bone : bind_skeleton.bones) {
        bind_local.push_back(
            Transform{bone.position, normalize_quaternion(bone.orientation), bone.scale});
    }
    auto pose_local = bind_local;
    for (const auto& layer : layers) {
        apply_animation_layer(layer, bind_by_name, bind_local, pose_local);
    }
    const auto bind_global = global_transforms(bind_skeleton, bind_local);
    const auto pose_global = global_transforms(bind_skeleton, pose_local);

    OgreMeshPose result;
    result.bones.reserve(bind_skeleton.bones.size());
    for (std::size_t index = 0; index < bind_skeleton.bones.size(); ++index) {
        result.bones.push_back(
            {bind_skeleton.bones[index].name, bind_skeleton.bones[index].handle,
             pose_global[index].position, pose_global[index].rotation,
             pose_global[index].scale});
    }
    if (mesh.shared_geometry) {
        result.geometries.push_back(skin_geometry(
            *mesh.shared_geometry, mesh.shared_bone_assignments, bind_by_handle,
            bind_global, pose_global));
    }
    for (const auto& submesh : mesh.submeshes) {
        if (submesh.geometry) {
            result.geometries.push_back(skin_geometry(
                *submesh.geometry, submesh.bone_assignments, bind_by_handle,
                bind_global, pose_global));
        }
    }
    return result;
}

} // namespace

OgreMeshPose sample_ogre_mesh_animation(const OgreMesh& mesh,
                                        const OgreSkeleton& bind_skeleton,
                                        const OgreSkeleton& animation_skeleton,
                                        std::string_view animation_name,
                                        float time_seconds,
                                        AnimationPlaybackMode playback_mode) {
    return sample_layers(mesh, bind_skeleton,
                         {{&animation_skeleton, animation_name, time_seconds, 1.0F,
                           playback_mode}});
}

OgreMeshPose sample_ogre_mesh_animation_layers(
    const OgreMesh& mesh, const OgreSkeleton& bind_skeleton,
    const std::vector<OgreAnimationLayer>& layers) {
    std::vector<AnimationLayer> internal;
    internal.reserve(layers.size());
    for (const auto& layer : layers) {
        if (layer.skeleton == nullptr) {
            throw OgreSkeletonError("OGRE animation layer has no skeleton");
        }
        internal.push_back({layer.skeleton, layer.animation_name, layer.time_seconds,
                            layer.weight, layer.playback_mode});
    }
    return sample_layers(mesh, bind_skeleton, internal);
}

OgreMeshPose sample_ogre_mesh_animation_blend(
    const OgreMesh& mesh, const OgreSkeleton& bind_skeleton,
    const OgreSkeleton& first_animation_skeleton,
    std::string_view first_animation_name, float first_time_seconds,
    float first_weight, const OgreSkeleton& second_animation_skeleton,
    std::string_view second_animation_name, float second_time_seconds,
    float second_weight, AnimationPlaybackMode first_playback_mode,
    AnimationPlaybackMode second_playback_mode) {
    return sample_layers(
        mesh, bind_skeleton,
        {{&first_animation_skeleton, first_animation_name, first_time_seconds,
          first_weight, first_playback_mode},
         {&second_animation_skeleton, second_animation_name, second_time_seconds,
          second_weight, second_playback_mode}});
}

OgreMeshPose blend_ogre_mesh_poses(const OgreMeshPose& first,
                                   const OgreMeshPose& second,
                                   float second_weight) {
    if (!std::isfinite(second_weight)) {
        throw OgreSkeletonError("OGRE pose blend weight is not finite");
    }
    const float amount = std::clamp(second_weight, 0.0F, 1.0F);
    if (first.geometries.size() != second.geometries.size()) {
        throw OgreSkeletonError("OGRE poses have different geometry counts");
    }
    OgreMeshPose result;
    if (first.bones.size() == second.bones.size()) {
        result.bones.reserve(first.bones.size());
        for (std::size_t index = 0; index < first.bones.size(); ++index) {
            if (first.bones[index].handle != second.bones[index].handle ||
                first.bones[index].name != second.bones[index].name) {
                result.bones.clear();
                break;
            }
            OgreBonePose bone = first.bones[index];
            bone.orientation = interpolate_quaternion(
                first.bones[index].orientation, second.bones[index].orientation,
                amount);
            for (std::size_t axis = 0; axis < 3; ++axis) {
                bone.position[axis] +=
                    (second.bones[index].position[axis] - bone.position[axis]) * amount;
                bone.scale[axis] +=
                    (second.bones[index].scale[axis] - bone.scale[axis]) * amount;
            }
            result.bones.push_back(std::move(bone));
        }
    }
    result.geometries.reserve(first.geometries.size());
    for (std::size_t geometry_index = 0;
         geometry_index < first.geometries.size(); ++geometry_index) {
        const auto& left = first.geometries[geometry_index];
        const auto& right = second.geometries[geometry_index];
        if (left.source == nullptr || left.source != right.source ||
            left.positions.size() != right.positions.size() ||
            left.normals.size() != right.normals.size()) {
            throw OgreSkeletonError("OGRE poses do not describe the same mesh");
        }
        OgreGeometryPose blended;
        blended.source = left.source;
        blended.positions.resize(left.positions.size());
        blended.normals.resize(left.normals.size());
        for (std::size_t vertex = 0; vertex < left.positions.size(); ++vertex) {
            for (std::size_t axis = 0; axis < 3; ++axis) {
                blended.positions[vertex][axis] =
                    left.positions[vertex][axis] +
                    (right.positions[vertex][axis] - left.positions[vertex][axis]) * amount;
            }
        }
        for (std::size_t vertex = 0; vertex < left.normals.size(); ++vertex) {
            for (std::size_t axis = 0; axis < 3; ++axis) {
                blended.normals[vertex][axis] =
                    left.normals[vertex][axis] +
                    (right.normals[vertex][axis] - left.normals[vertex][axis]) * amount;
            }
            const auto& normal = blended.normals[vertex];
            const float length = std::hypot(normal[0], std::hypot(normal[1], normal[2]));
            if (length > 0.000001F) {
                for (auto& component : blended.normals[vertex]) {
                    component /= length;
                }
            }
        }
        result.geometries.push_back(std::move(blended));
    }
    return result;
}

} // namespace torchlight
