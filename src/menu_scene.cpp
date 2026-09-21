#include "torchlight/menu_scene.hpp"

#include "torchlight/resource_fields.hpp"

#include <optional>
#include <stdexcept>

namespace torchlight {

MenuSceneCamera menu_scene_camera(const LayoutManifest& layout, bool netbook_mode) {
    const auto transforms = resolve_layout_world_transforms(layout);
    std::optional<Vector3> position;
    std::optional<Vector3> target;
    for (std::size_t i = 0; i < layout.objects.size(); ++i) {
        const auto& object = layout.objects[i];
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
    result.geometry = build_room_piece_geometry(archive, levelsets, result.level);
    return result;
}

} // namespace torchlight
