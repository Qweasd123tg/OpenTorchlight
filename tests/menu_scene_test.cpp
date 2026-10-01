#include "torchlight/menu_scene.hpp"
#include "torchlight/menu_player.hpp"

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
        std::cout << "PASS: menu scene data/camera contract (no graphics or original execution)\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
