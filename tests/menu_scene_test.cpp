#include "torchlight/menu_scene.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
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
    parent.descriptor = u"Group";
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
    // External marker coordinates plus their Properties parent (69,0,14).
    const Vector3 position{73.345703125F + 69.0F, 2.5F, 10.848299980163574F + 14.0F};
    const Vector3 target{65.12799835205078F + 69.0F, 1.0199999809265137F,
                         9.146269798278809F + 14.0F};
    require(menu.camera.position == position && menu.camera.target == target,
            "Town camera marker world coordinates changed");
    require(!menu.geometry.instances.empty() && !menu.geometry.meshes.empty() &&
            menu.geometry.unique_index_count > 0, "menu contains no room-piece geometry");
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
