#include "torchlight/menu_scene.hpp"

#include "torchlight/resource_fields.hpp"

#include <OgreMatrix3.h>
#include <OgreQuaternion.h>

#include <optional>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <unordered_map>

namespace torchlight {
namespace {
LayoutManifest runtime_menu_layout(const LayoutManifest& layout) {
    // original-code: PARENTID -> editor field +0x18 (setParentGuid
    // 0x59f070), while CLayout::editorObjectCreated @0x9df9d8 attaches
    // scene nodes to the owning CLayout through the separate +0x50 edge.
    // Group is CRandomGroup (ctor descriptor @0x6373b7): its GUID selects
    // children in rollGroup @0x74b330, not an OGRE transform parent.
    // Preserve real expanded Layout Link parents; flatten editor Groups.
    static_cast<void>(resolve_layout_world_transforms(layout));
    auto runtime = layout;
    std::unordered_map<std::int64_t, const LayoutObject*> ids;
    for (const auto& object : layout.objects) ids.emplace(object.id, &object);
    for (auto& object : runtime.objects) {
        while (object.parent_id != -1) {
            const auto* parent = ids.at(object.parent_id);
            if (parent->descriptor != u"Group") break;
            object.parent_id = parent->parent_id;
        }
    }
    return runtime;
}
} // namespace


MenuPlayerPlacement menu_player_placement(const LayoutManifest& layout) {
    // Reuse graph validation (IDs, missing parents, cycles) before resolving
    // the OGRE node values. Quaternion composition/normalisation uses the
    // pinned library rather than approximating _getDerivedOrientation.
    const auto runtime = runtime_menu_layout(layout);
    struct Node { Ogre::Quaternion orientation; Ogre::Vector3 position, scale; };
    std::unordered_map<std::int64_t, std::size_t> ids;
    for (std::size_t i = 0; i < runtime.objects.size(); ++i) ids.emplace(runtime.objects[i].id, i);
    std::vector<std::optional<Node>> nodes(runtime.objects.size());
    std::function<const Node&(std::size_t)> resolve = [&](std::size_t i) -> const Node& {
        if (nodes[i]) return *nodes[i];
        const auto& object = runtime.objects[i];
        const auto m = object.orientation.value_or(yaw_rotation(object.angle));
        Node node{Ogre::Quaternion(Ogre::Matrix3(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8])),
            Ogre::Vector3(object.position_x.value_or(0), object.position_y.value_or(0), object.position_z.value_or(0)),
            Ogre::Vector3(object.scale_x, object.scale_y, object.scale_z)};
        // library-derived: Node::setOrientation and updateFromParentImpl 1.6.5.
        node.orientation.normalise();
        if (object.parent_id != -1) {
            const auto& parent = resolve(ids.at(object.parent_id));
            node.position = parent.orientation * (parent.scale * node.position) + parent.position;
            node.scale = parent.scale * node.scale;
            node.orientation = parent.orientation * node.orientation;
        }
        nodes[i] = node;
        return *nodes[i];
    };
    std::optional<MenuPlayerPlacement> result;
    for (std::size_t i = 0; i < runtime.objects.size(); ++i) {
        const auto& object = runtime.objects[i];
        if (object.descriptor != u"Property Node") continue;
        // original-code: CPropertyNode ctor 0x9e862c initializes TYPE=1.
        std::u16string type = u"Player Start";
        if (const auto* property = object.find_property(u"TYPE")) {
            const auto* text = std::get_if<std::u16string>(&property->value);
            if (!text) throw std::invalid_argument("Menu Property Node TYPE is not text");
            type = *text;
        }
        if (type != u"Player Start" && type != u"Entrance") continue;
        const auto& node = resolve(i);
        auto direction = node.orientation.zAxis();
        direction.y = 0;
        // original-code: 0x960251..0x9602c2, double threshold @0xfa87a0.
        const float length = std::sqrt(direction.x * direction.x + direction.z * direction.z);
        if (length > 1e-8) { const float inverse = 1.0F / length; direction.x *= inverse; direction.z *= inverse; }
        const float angle = std::atan2(direction.x, direction.z);
        if (!std::isfinite(angle) || !std::isfinite(node.position.x) ||
            !std::isfinite(node.position.y) || !std::isfinite(node.position.z))
            throw std::invalid_argument("Menu player marker is not finite");
        // original-code: setToward 0x8126e0 -> matrixRotationY 0xc7a2a0,
        // atan2f(x,z) consumed directly in radians (no degrees round trip).
        const float c = std::cos(angle), s = std::sin(angle);
        result = MenuPlayerPlacement{{node.position.x, node.position.y, node.position.z},
            {direction.x, 0, direction.z}, {c, 0, s, 0, 1, 0, -s, 0, c}};
    }
    if (!result) throw std::invalid_argument("Menu layout lacks a player marker");
    return *result;
}

MenuSceneCamera menu_scene_camera(const LayoutManifest& layout, bool netbook_mode) {
    const auto runtime = runtime_menu_layout(layout);
    const auto transforms = resolve_layout_world_transforms(runtime);
    std::optional<Vector3> position;
    std::optional<Vector3> target;
    for (std::size_t i = 0; i < runtime.objects.size(); ++i) {
        const auto& object = runtime.objects[i];
        if (object.descriptor != u"Property Node") continue;
        const auto* property = object.find_property(u"TYPE");
        if (property == nullptr) continue;
        const auto* type = std::get_if<std::u16string>(&property->value);
        if (type == nullptr) throw std::invalid_argument("Menu camera node TYPE is not text");
        // original-code: type 10/11 assignments at 0x960868/0x960838.
        // The original traversal overwrites the destination for each marker.
        if (*type == u"Camera Position") position = transforms[i].position;
        if (*type == u"Camera Target") target = transforms[i].position;
    }
    if (!position || !target) throw std::invalid_argument("Menu layout lacks camera markers");
    MenuSceneCamera camera;
    camera.position = *position;
    camera.target = *target;
    camera.far_clip = netbook_mode ? 45.0F : 90.0F;
    // Validate the recovered pose without creating a graphics context.
    static_cast<void>(make_camera_projection(camera.position, camera.target, 1.0F,
        camera.fov_degrees, camera.near_clip, camera.far_clip));
    return camera;
}

MenuScene build_main_menu_scene(const PakArchive& archive, const LevelsetCatalog& levelsets,
                                bool netbook_mode) {
    const LevelSceneLoader loader(archive);
    MenuScene result;
    // original-code: setGameState 0x590c48 selects TOWN, depth 1 when no
    // saved player loads. This boundary does not select save-dependent themes.
    result.level.dungeon = loader.load_dungeon(u"media/dungeons/TOWN.DAT");
    const auto& first = result.level.dungeon.strata.front();
    if (first.floors < 1) throw std::invalid_argument("Town has no depth-one stratum");
    const auto town_rules = parse_adm(archive.read_normalized(compiled_adm_path(first.ruleset)));
    if (town_rules.root.name != u"LEVEL") throw std::invalid_argument("Town rules are not LEVEL");
    const auto menu_rules = resource_fields::text(town_rules.root, u"MAINMENURULES");
    if (menu_rules.empty()) throw std::invalid_argument("Town rules lack MAINMENURULES");
    result.level.rules = loader.load_rules(menu_rules);
    const auto& rules = result.level.rules;
    if (rules.randomized || rules.chunks.size() != 1)
        throw std::invalid_argument("Menu scene requires one fixed chunk");
    const auto& chunk = rules.chunks.front();
    if (chunk.x != 0.0F || chunk.y != 0.0F || chunk.z != 0.0F)
        throw std::invalid_argument("Menu fixed chunk has an unsupported placement offset");
    const auto candidates = loader.layout_candidates(rules, chunk.type);
    if (candidates.size() != 1)
        throw std::invalid_argument("Menu fixed chunk does not resolve to one layout");
    result.level.layout = loader.load_layout(candidates.front());
    static_cast<void>(expand_layout_links(loader, result.level.layout));
    result.camera = menu_scene_camera(result.level.layout, netbook_mode);
    auto render_level = result.level;
    render_level.layout = runtime_menu_layout(result.level.layout);
    result.geometry = build_room_piece_geometry(archive, levelsets, render_level);
    return result;
}

} // namespace torchlight
