#include "torchlight/menu_scene.hpp"
#include "torchlight/menu_player.hpp"
#include "torchlight/checkpoint.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
bool near(const torchlight::Vector3& a, const torchlight::Vector3& b) {
    for (std::size_t i = 0; i < a.size(); ++i) if (std::abs(a[i] - b[i]) > 1e-5F) return false;
    return true;
}
template<class Function> void rejects(Function&& function, const char* message) {
    try { function(); }
    catch (const std::invalid_argument&) { return; }
    throw std::runtime_error(message);
}
torchlight::LayoutObject marker(std::int64_t id, const std::u16string& type,
                                torchlight::Vector3 position) {
    torchlight::LayoutObject object;
    object.id = id;
    object.parent_id = 1;
    object.descriptor = u"Property Node";
    object.position_x = position[0];
    object.position_y = position[1];
    object.position_z = position[2];
    torchlight::AdmProperty property;
    property.name = u"TYPE";
    property.type = torchlight::AdmValueType::string;
    property.value = type;
    object.properties.push_back(property);
    return object;
}
void authored_contract() {
    using namespace torchlight;
    LayoutManifest layout;
    LayoutObject parent;
    parent.id = 1;
    parent.descriptor = u"Layout Link";
    parent.position_x = 10;
    parent.position_y = 20;
    parent.position_z = 30;
    parent.scale_x = 2;
    parent.scale_y = 3;
    parent.scale_z = 4;
    parent.orientation = Matrix3{0, 0, 1, 0, 1, 0, -1, 0, 0};
    layout.objects = {parent, marker(2, u"Camera Position", {1, 2, 3}),
                      marker(3, u"Camera Target", {0, 0, 0})};
    const auto camera = menu_scene_camera(layout);
    require(camera.position == Vector3{22, 26, 28}, "camera lost parent rotation/scale/translation");
    require(camera.target == Vector3{10, 20, 30}, "camera target lost parent translation");
    require(camera.fov_degrees == 35 && camera.near_clip == 1 && camera.far_clip == 90,
            "menu creation projection parameters differ from ELF");
    require(menu_scene_camera(layout, true).far_clip == 45, "netbook far clip branch lost");
    const auto projection = make_camera_projection(camera.position, camera.target, 16.0F / 9.0F,
        camera.fov_degrees, camera.near_clip, camera.far_clip);
    const auto target_ndc = projection.project_ndc(camera.target);
    require(std::abs(target_ndc[0]) < 1e-6F && std::abs(target_ndc[1]) < 1e-6F,
            "explicit camera does not look at its resource target");
    layout.objects.push_back(marker(4, u"Camera Position", {2, 2, 3}));
    require(menu_scene_camera(layout).position == Vector3{22, 26, 26},
            "last camera marker must replace earlier assignment");
    layout.objects.pop_back();
    layout.objects[1].position_x = std::numeric_limits<float>::quiet_NaN();
    rejects([&] { static_cast<void>(menu_scene_camera(layout)); }, "nonfinite camera accepted");
    layout.objects[1].position_x = 1;
    layout.objects.pop_back();
    rejects([&] { static_cast<void>(menu_scene_camera(layout)); }, "missing target silently fitted");

    layout.objects = {parent, marker(2, u"Player Start", {1, 2, 3})};
    layout.objects[1].properties.clear(); // ctor default TYPE=1, not Point of Interest.
    auto player = menu_player_placement(layout);
    require(near(player.position, Vector3{22, 26, 28}), "player marker lost parent transform");
    require(std::abs(player.toward[0] - 1) < 1e-6F && std::abs(player.toward[2]) < 1e-6F,
            "derived quaternion zAxis must be the player's toward vector");
    layout.objects.push_back(marker(3, u"Entrance", {2, 2, 3}));
    require(near(menu_player_placement(layout).position, Vector3{22, 26, 26}), "menu Entrance must overwrite Player Start");
    layout.objects.push_back(marker(4, u"Exit", {9, 9, 9}));
    require(near(menu_player_placement(layout).position, Vector3{22, 26, 26}), "non-menu Exit replaced player spawn");
    layout.objects[0].descriptor = u"Group";
    require(menu_player_placement(layout).position == Vector3{2, 2, 3}, "editor Group pivot applied to player node");
    layout.objects = {parent, marker(2, u"Camera Position", {1, 2, 3}), marker(3, u"Camera Target", {0, 0, 0})};
    layout.objects[0].descriptor = u"Group";
    require(menu_scene_camera(layout).position == Vector3{1, 2, 3}, "editor Group pivot applied to camera node");
    AdmProperty choice;
    choice.name = u"CHOICE"; choice.type = AdmValueType::string; choice.value = std::u16string(u"Weight");
    layout.objects[0].properties.push_back(choice);
    require(menu_scene_camera(layout).position == Vector3{1, 2, 3}, "direct marker was treated as a child-Group alternative");
    auto child_group = parent; child_group.id = 5; child_group.parent_id = 1; child_group.descriptor = u"Group";
    layout.objects.push_back(child_group);
    layout.objects[1].parent_id = 5; layout.objects[2].parent_id = 5;
    rejects([&] { static_cast<void>(menu_scene_camera(layout)); }, "random camera alternatives displayed together");
    layout.objects[0].properties[0].value = std::u16string(u"ALL");
    require(menu_scene_camera(layout).position == Vector3{1, 2, 3}, "ALL camera Group was treated as random");
    layout.objects = {parent};
    rejects([&] { static_cast<void>(menu_player_placement(layout)); }, "missing player marker silently invented");
}
void original_resources(const char* pak_path) {
    using namespace torchlight;
    const PakArchive archive(pak_path);
    const LevelsetCatalog levelsets(archive);
    const auto menu = build_main_menu_scene(archive, levelsets);
    require(menu.level.dungeon.name == u"Town", "no-save scene is not Town");
    require(menu.level.rules.name == u"MainMenuTown", "gameplay rules used as menu scene");
    require(menu.level.layout.source_path.find("MAINMENU_TOWN.LAYOUT") != std::string::npos,
            "Town menu rules resolve to another layout");
    // External marker coordinates; editor Group pivot (69,0,14) is not an OGRE parent.
    const Vector3 position{73.345703125F, 2.5F, 10.848299980163574F};
    const Vector3 target{65.12799835205078F, 1.0199999809265137F,
                         9.146269798278809F};
    require(menu.camera.position == position && menu.camera.target == target,
            "Town camera marker world coordinates changed");
    require(!menu.geometry.instances.empty() && !menu.geometry.meshes.empty() &&
            menu.geometry.unique_index_count > 0, "menu contains no room-piece geometry");
    const auto placement = menu_player_placement(menu.level.layout);
    require(placement.position == Vector3{66.27629852294922F, 1.215000033378601F,
                                         9.377470016479492F}, "Town player spawn differs from external layout");
    require(std::abs(placement.toward[0] - 0.891007F) < 2e-6F &&
            std::abs(placement.toward[2] - 0.453989F) < 2e-6F,
            "Town player direction differs from authored forward axis");
    const MasterResourceIndex resources(parse_adm(archive.read("media/MASTERRESOURCEUNITS.DAT.ADM")));
    UnitDefinitionLoader definitions(archive);
    const auto players = load_playable_players(archive, resources, definitions);
    require(players.size() == 3, "supported class family changed");
    struct Theme {
        std::int32_t first, last;
        const char* layout;
        Vector3 camera, target, player;
    };
    // resource-derived: MAIN.DAT strata -> gameplay rules MAINMENURULES ->
    // expanded source layout. These are OTC depths, not the original save ABI.
    const Theme themes[] = {
        {1, 4, "MAINMENU_MINES.LAYOUT", {5.66000986F,3.5150001F,-6.13999987F}, {1.25F,0.829999983F,1}, {1.86000001F,1.83000004F,0}},
        {5, 8, "MAINMENU_CRYPT.LAYOUT", {5.66000986F,3.5150001F,-6.13999987F}, {1.25F,0.829999983F,1}, {1.86000001F,1.83000004F,0}},
        {9, 16, "MAINMENU_SUNKENTEMPLE.LAYOUT", {5.61003017F,3.5150001F,-7.15001011F}, {1.20000005F,0.829999983F,-0.00999784004F}, {1.80999994F,1.83000004F,-1.00999999F}},
        {21, 24, "MAINMENU_LAVA.LAYOUT", {5.66000986F,3.5150001F,-6.13999987F}, {1.25F,0.829999983F,1}, {1.86000001F,1.83000004F,0}},
        {25, 29, "MAINMENU_FORTRESS.LAYOUT", {5.66000986F,3.5150001F,-6.13999987F}, {1.25F,0.829999983F,1}, {1.86000001F,1.83000004F,0}},
        {30, 35, "MAINMENU_PALACE.LAYOUT", {-1.63998997F,3.5150001F,-0.490007997F}, {-6.05000019F,0.829999983F,6.64999008F}, {-5.44000006F,1.83000004F,5.64999008F}},
    };
    for (const auto& theme : themes) {
        for (const auto depth : {theme.first, theme.last}) {
            const auto saved_menu = build_saved_menu_scene(archive, levelsets, {u"Main", depth});
            require(saved_menu.level.layout.source_path.find(theme.layout) != std::string::npos,
                    "saved floor resolved to the wrong menu theme at stratum boundary");
            require(near(saved_menu.camera.position, theme.camera) && near(saved_menu.camera.target, theme.target),
                    "saved theme camera differs from source markers");
            require(!saved_menu.geometry.instances.empty(), "saved theme has no geometry consumer");
            const auto saved_preview = build_menu_player_preview(archive, saved_menu, players.front());
            require(near(saved_preview.geometry.instances[saved_preview.body_instance].transform.position, theme.player),
                    "actor retained the previous theme's player marker");
            require(sample_menu_player_preview(saved_preview, 0).weapon.has_value(), "theme replacement lost weapon hand consumer");
            if (theme.first == 1)
                require(saved_menu.omitted_random_room_pieces > 0, "Mine random alternatives were silently drawn together");
            std::cout << "Saved menu depth " << depth << ": " << saved_menu.level.layout.source_path
                      << ", " << saved_menu.geometry.instances.size() << " instances, "
                      << saved_menu.omitted_random_room_pieces << " random props omitted\n";
        }
    }
    for (const auto depth : {17, 20})
        rejects([&] { static_cast<void>(build_saved_menu_scene(archive, levelsets, {u"Main", depth})); },
                "random Caves menu silently substituted a fixed theme");
    const auto saved_town = build_saved_menu_scene(archive, levelsets, {u"Town", 0});
    require(saved_town.camera.position == position && saved_town.camera.target == target &&
            saved_town.omitted_random_room_pieces == 0, "saved Town changed the existing no-save route");
    for (const auto& prototype : players) {
        const auto preview = build_menu_player_preview(archive, menu, prototype);
        require(preview.geometry.instances.size() == menu.geometry.instances.size() + 2 && preview.weapon_instance,
                "body and actual starting weapon are not connected to menu geometry");
        const auto& instance = preview.geometry.instances[preview.body_instance];
        require(instance.transform.position == placement.position && instance.transform.orientation == placement.orientation,
                "preview ignores source placement/toward consumer");
        require(preview.geometry.meshes[instance.mesh_index].texture_layers == prototype.wardrobe_texture_layers,
                "preview lost the gameplay wardrobe consumer");
        const auto first = sample_menu_player_preview(preview, 0);
        const auto later = sample_menu_player_preview(preview, preview.idle.duration * 0.37F);
        require(first.weapon && later.weapon && !first.body.geometries.empty(), "model/hand tag have no pose consumer");
        require(first.body.geometries[0].positions != later.body.geometries[0].positions, "IDLE did not animate player vertices");
        const auto loop = sample_menu_player_preview(preview, preview.idle.duration);
        require(first.body.geometries[0].positions == loop.body.geometries[0].positions, "menu IDLE is not looping");
        auto unarmed = prototype; unarmed.starting_weapon.reset();
        const auto unarmed_preview = build_menu_player_preview(archive, menu, unarmed);
        require(!unarmed_preview.weapon_instance && !sample_menu_player_preview(unarmed_preview, 0).weapon,
                "saved unequipped weapon was replaced by starting equipment");

        PlayerSession session(prototype, 77);
        const auto before = CheckpointAccess::capture(session);
        const auto initial_visual = menu_player_visual(prototype, session);
        const auto after = CheckpointAccess::capture(session);
        require(initial_visual && initial_visual->starting_weapon &&
                before.combat_random == after.combat_random && before.health == after.health &&
                before.gold == after.gold && before.inventory.slots == after.inventory.slots,
                "preview snapshot consumed live simulation state/RNG");
        const auto weapon_id = session.weapon()->id;
        require(session.unequip(weapon_id) == InventoryChange::changed, "fixture weapon did not unequip");
        const auto current = menu_player_visual(prototype, session);
        require(current && !current->starting_weapon && initial_visual->starting_weapon,
                "current preview retained starting weapon or mutated earlier snapshot");
        const auto returned = build_menu_player_preview(archive, menu, *current);
        require(returned.geometry.instances.size() == menu.geometry.instances.size() + 1 &&
                !returned.weapon_instance && !sample_menu_player_preview(returned, 0).weapon,
                "return-to-menu current snapshot has a stale weapon consumer");
        require(session.equip(weapon_id) == InventoryChange::changed, "fixture weapon did not re-equip");
        const auto equipped = menu_player_visual(prototype, session);
        require(equipped && equipped->starting_weapon &&
                equipped->starting_weapon->guid == initial_visual->starting_weapon->guid,
                "re-equipped live instance has no preview producer");

        // Real rolled inventory from another supported resource class, restored
        // through the same OTC DTO consumer as Load (no fabricated weapon mesh).
        const auto donor_index = static_cast<std::size_t>(&prototype - players.data() + 1) % players.size();
        PlayerSession donor(players[donor_index], 91);
        auto state = CheckpointAccess::capture(session);
        state.inventory = CheckpointAccess::capture(donor).inventory;
        const auto restored = CheckpointAccess::restore_player(prototype, state, 77);
        const auto changed = menu_player_visual(prototype, restored);
        require(changed && changed->starting_weapon &&
                changed->starting_weapon->guid == donor.weapon()->weapon->prototype.guid &&
                changed->starting_weapon->guid != prototype.starting_weapon->guid,
                "restored preview replaced equipped item with class starting equipment");
        const auto changed_preview = build_menu_player_preview(archive, menu, *changed);
        require(changed_preview.weapon_instance &&
                changed_preview.geometry.meshes[changed_preview.geometry.instances[*changed_preview.weapon_instance].mesh_index].guid ==
                    donor.weapon()->resource_guid && sample_menu_player_preview(changed_preview, 0).weapon,
                "changed equipped instance did not reach actual mesh/hand consumer");
        state.health = 0;
        const auto dead = CheckpointAccess::restore_player(prototype, state, 77);
        require(!menu_player_visual(prototype, dead), "dead current player was replaced by a living menu actor");
    }
    std::cout << "Town menu: " << menu.geometry.instances.size() << " instances, "
              << menu.geometry.meshes.size() << " meshes; camera=" << position[0] << ','
              << position[1] << ',' << position[2] << '\n';
}
} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 1 && (argc != 3 || std::string(argv[1]) != "--original")) {
            std::cerr << "usage: menu_scene_test [--original /path/to/pak.zip]\n";
            return 2;
        }
        authored_contract();
        if (argc == 3) original_resources(argv[2]);
        std::cout << "PASS: menu scene data/camera/actor contract (no graphics or original execution)\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
