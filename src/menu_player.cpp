#include "torchlight/menu_player.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace torchlight {

MenuPlayerPreview build_menu_player_preview(const PakArchive& archive,
                                           const MenuScene& scene,
                                           const PlayerPrototype& prototype) {
    MenuPlayerPreview result;
    result.geometry = scene.geometry;
    result.prototype = prototype;
    const auto placement = menu_player_placement(scene.level.layout);
    result.body_instance = result.geometry.instances.size();
    append_player_geometry(archive, prototype, placement.position, result.geometry);
    result.geometry.instances[result.body_instance].transform.orientation = placement.orientation;
    result.weapon_instance = append_player_weapon_geometry(archive, prototype, placement.position, result.geometry);
    const auto mesh_index = result.geometry.instances[result.body_instance].mesh_index;
    const auto& mesh = result.geometry.meshes[mesh_index];
    auto idle = load_model_animations_by_prefix(archive, prototype.mesh_path,
        result.geometry.meshes[mesh_index].mesh.skeleton_file, "IDLE");
    // original-code: CCharacter::updateAnimation IDLE branch @0x84a6c3 /
    // 0x84b13c. resource-derived: each supported player has one IDLE match.
    // Multiple variants require the original selection/RNG chain, not first().
    if (idle.size() != 1)
        throw std::invalid_argument("Menu preview requires one resolved player IDLE clip");
    result.idle = std::move(idle.front());
    const auto slash = mesh.source_path.find_last_of("/\\");
    const auto directory = slash == std::string::npos ? std::string{} : mesh.source_path.substr(0, slash + 1);
    const auto* bind = archive.find_normalized(directory + mesh.mesh.skeleton_file);
    if (!bind || mesh.mesh.skeleton_file.empty())
        throw std::invalid_argument("Menu player mesh lacks its bind skeleton");
    result.idle.bind_skeleton = std::make_shared<OgreSkeleton>(parse_ogre_skeleton(archive.read(*bind)));
    return result;
}

MenuPlayerPose sample_menu_player_preview(const MenuPlayerPreview& preview, float seconds) {
    if (!std::isfinite(seconds) || seconds < 0)
        throw std::invalid_argument("Invalid menu preview animation time");
    const auto& body = preview.geometry.instances.at(preview.body_instance);
    MenuPlayerPose result;
    result.body = sample_ogre_mesh_animation(preview.geometry.meshes.at(body.mesh_index).mesh,
        *preview.idle.bind_skeleton, preview.idle.animation_skeleton,
        preview.idle.animation_name, seconds, AnimationPlaybackMode::loop);
    if (preview.weapon_instance) {
        const bool left = preview.prototype.starting_weapon &&
            preview.prototype.starting_weapon->attack_hand == AttackHand::left;
        const auto tag = std::find_if(result.body.bones.begin(), result.body.bones.end(),
            [&](const auto& bone) { return bone.name == (left ? "tag_lefthand" : "tag_righthand"); });
        if (tag == result.body.bones.end())
            throw std::invalid_argument("Menu player lacks selected equipment hand tag");
        LayoutWorldTransform transform;
        transform.position = transform_point(body.transform.position, body.transform.orientation,
                                            body.transform.scale, tag->position);
        transform.orientation = compose_rotation(body.transform.orientation, quaternion_rotation(tag->orientation));
        for (std::size_t axis = 0; axis < 3; ++axis)
            transform.scale[axis] = body.transform.scale[axis] * tag->scale[axis] * preview.prototype.weapon_scale;
        result.weapon = transform;
    }
    return result;
}

} // namespace torchlight
