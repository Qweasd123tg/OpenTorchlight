#include "torchlight/level_scene.hpp"
#include "torchlight/player.hpp"

#include <iomanip>
#include <iostream>
#include <string>

namespace {
template <std::size_t N> void array(const std::array<float, N>& values) {
    std::cout << '[';
    for (std::size_t i = 0; i < N; ++i) {
        if (i) std::cout << ',';
        std::cout << values[i];
    }
    std::cout << ']';
}
void text(std::u16string_view value) {
    std::cout << '"';
    for (const auto ch : value) {
        if (ch == u'"' || ch == u'\\') std::cout << '\\' << static_cast<char>(ch);
        else if (ch < 32 || ch >= 127)
            std::cout << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                      << static_cast<unsigned>(ch) << std::dec;
        else std::cout << static_cast<char>(ch);
    }
    std::cout << '"';
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: torchlight_scene_camera_dump /path/to/pak.zip\n";
        return 2;
    }
    try {
        const torchlight::PakArchive archive(argv[1]);
        const torchlight::LevelSceneLoader loader(archive);
        auto scene = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        const auto expansion = torchlight::expand_layout_links(loader, scene.layout);
        const auto transforms = torchlight::resolve_layout_world_transforms(scene.layout);
        const auto target = torchlight::layout_player_start(scene.layout);
        const auto pose = torchlight::game_camera_pose(target, 28.5F);
        const auto camera = torchlight::make_camera_projection(pose.position, pose.target, 16.0F / 9.0F);
        std::cout << std::setprecision(9) << "{\"scene\":\"town\",\"expanded_links\":"
                  << expansion.links_expanded << ",\"camera_target\":";
        array(pose.target);
        std::cout << ",\"camera_position\":"; array(pose.position);
        std::cout << ",\"view\":"; array(camera.view);
        std::cout << ",\"projection\":"; array(camera.projection);
        std::cout << ",\"objects\":[\n";
        for (std::size_t i = 0; i < scene.layout.objects.size(); ++i) {
            if (i) std::cout << ",\n";
            const auto& object = scene.layout.objects[i];
            const auto& world = transforms[i];
            std::cout << "{\"id\":\"" << object.id << "\",\"parent\":\"" << object.parent_id
                      << "\",\"name\":"; text(object.name);
            std::cout << ",\"descriptor\":"; text(object.descriptor);
            std::cout << ",\"authored_orientation\":" << (object.orientation ? "true" : "false");
            std::cout << ",\"local_position\":";
            array(torchlight::Vector3{object.position_x.value_or(0), object.position_y.value_or(0),
                                      object.position_z.value_or(0)});
            std::cout << ",\"local_rotation\":";
            array(object.orientation.value_or(torchlight::yaw_rotation(object.angle)));
            std::cout << ",\"local_scale\":";
            array(torchlight::Vector3{object.scale_x, object.scale_y, object.scale_z});
            std::cout << ",\"world_position\":"; array(world.position);
            std::cout << ",\"world_rotation\":"; array(world.orientation);
            std::cout << ",\"world_scale\":"; array(world.scale);
            std::cout << ",\"landmark_world\":";
            const auto landmark = torchlight::transform_point(world.position, world.orientation,
                                                               world.scale, {0.25F, 0.5F, 1.0F});
            array(landmark);
            std::cout << ",\"landmark_ndc\":";
            try { array(camera.project_ndc(landmark)); }
            catch (const std::invalid_argument&) { std::cout << "null"; }
            std::cout << '}';
        }
        std::cout << "\n]}\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
