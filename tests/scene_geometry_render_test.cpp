#include "torchlight/adm_document.hpp"
#include "torchlight/entity_world.hpp"
#include "torchlight/gles_scene_renderer.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/unit_definition.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

constexpr int kWidth = 256;
constexpr int kHeight = 192;

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

class HeadlessContext {
public:
    HeadlessContext() {
        display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        require(display_ != EGL_NO_DISPLAY, "eglGetDisplay failed");
        require(eglInitialize(display_, nullptr, nullptr) == EGL_TRUE, "eglInitialize failed");
        require(eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE, "eglBindAPI failed");
        const EGLint config_attributes[] = {
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE,
        };
        EGLConfig config = nullptr;
        EGLint count = 0;
        require(eglChooseConfig(display_, config_attributes, &config, 1, &count) == EGL_TRUE &&
                    count == 1,
                "eglChooseConfig failed");
        const EGLint surface_attributes[] = {
            EGL_WIDTH, kWidth,
            EGL_HEIGHT, kHeight,
            EGL_NONE,
        };
        surface_ = eglCreatePbufferSurface(display_, config, surface_attributes);
        require(surface_ != EGL_NO_SURFACE, "eglCreatePbufferSurface failed");
        const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, context_attributes);
        require(context_ != EGL_NO_CONTEXT, "eglCreateContext failed");
        require(eglMakeCurrent(display_, surface_, surface_, context_) == EGL_TRUE,
                "eglMakeCurrent failed");
    }

    HeadlessContext(const HeadlessContext&) = delete;
    HeadlessContext& operator=(const HeadlessContext&) = delete;

    ~HeadlessContext() {
        if (display_ != EGL_NO_DISPLAY) {
            eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (context_ != EGL_NO_CONTEXT) {
                eglDestroyContext(display_, context_);
            }
            if (surface_ != EGL_NO_SURFACE) {
                eglDestroySurface(display_, surface_);
            }
            eglTerminate(display_);
        }
    }

private:
    EGLDisplay display_ = EGL_NO_DISPLAY;
    EGLSurface surface_ = EGL_NO_SURFACE;
    EGLContext context_ = EGL_NO_CONTEXT;
};

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: scene_geometry_render_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader loader(archive);
        const auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        const auto geometry = torchlight::build_room_piece_geometry(archive, levelsets, town);
        const torchlight::OgreMaterialCatalog materials(archive);

        HeadlessContext context;
        torchlight::GlesSceneRenderer renderer(geometry, archive, materials);
        renderer.draw(kWidth, kHeight);
        const auto& stats = renderer.stats();
        require(stats.mesh_resources == 303, "renderer has the wrong mesh count");
        require(stats.instances == 352, "renderer has the wrong instance count");
        require(stats.draw_batches > 0, "renderer has no draw batches");
        require(stats.placed_triangles > 100000, "renderer submitted too few town triangles");
        require(stats.texture_resources == 101, "renderer has the wrong texture count");
        require(stats.textured_batches == 525, "renderer has untextured town batches");
        require(stats.fallback_batches == 0, "renderer used a fallback town texture");

        std::array<std::uint8_t, kWidth * kHeight * 4> pixels{};
        glReadPixels(0, 0, kWidth, kHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        require(glGetError() == GL_NO_ERROR, "town framebuffer readback failed");
        std::size_t colored_pixels = 0;
        for (std::size_t offset = 0; offset < pixels.size(); offset += 4U) {
            if (pixels[offset] > 30U || pixels[offset + 1] > 30U || pixels[offset + 2] > 30U) {
                ++colored_pixels;
            }
        }
        require(colored_pixels > 1000, "town render produced no visible geometry");
        std::cout << "PASS: rendered full town geometry, batches=" << stats.draw_batches
                  << " placed_triangles=" << stats.placed_triangles
                  << " textures=" << stats.texture_resources
                  << " colored_pixels=" << colored_pixels << '\n';

        const auto main = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        const auto mine_rules = loader.load_rules(main.strata.front().ruleset);
        const torchlight::RandomLevelGenerator generator(loader);
        const auto generated = generator.generate(mine_rules, 42U);
        auto mine_geometry = torchlight::build_generated_level_geometry(
            archive, levelsets, loader, mine_rules, generated);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const auto players =
            torchlight::load_playable_players(archive, resources, definitions);
        require(!players.empty(), "no playable player prototype was loaded");
        const auto player_start = torchlight::generated_player_start(loader, generated);
        torchlight::append_player_geometry(archive, players.front(), player_start, mine_geometry);
        const auto* skeleton = resources.find_case_insensitive(
            torchlight::MasterResourceKind::monster, u"Skeletal Warrior");
        require(skeleton != nullptr, "Skeletal Warrior master resource is absent");
        torchlight::RuntimeEntity runtime_monster;
        runtime_monster.id = 1;
        runtime_monster.resource_guid = skeleton->guid;
        runtime_monster.kind = skeleton->kind;
        runtime_monster.name = skeleton->name;
        runtime_monster.position = player_start;
        runtime_monster.position[0] += 3.0F;
        const auto runtime_instance = torchlight::append_runtime_entity_geometry(
            archive, resources, definitions, runtime_monster, mine_geometry);
        require(runtime_instance.has_value() &&
                    mine_geometry.instances[*runtime_instance].runtime_entity_id == 1,
                "runtime monster was not appended to generated geometry");
        torchlight::GlesSceneRenderer mine_renderer(mine_geometry, archive, materials);
        mine_renderer.set_camera_target(player_start);
        mine_renderer.draw(kWidth, kHeight);
        const auto center_ground = mine_renderer.ground_position_at_pixel(
            kWidth / 2, kHeight / 2, kWidth, kHeight, player_start[1]);
        require(std::hypot(center_ground[0] - player_start[0],
                           center_ground[2] - player_start[2]) < 1.0F,
                "camera center does not project back near the player");
        const auto& mine_stats = mine_renderer.stats();
        require(mine_stats.instances == mine_geometry.instances.size(),
                "generated mine renderer has the wrong instance count");
        require(mine_stats.textured_batches > 0, "generated mine has no textured batches");
        require(mine_stats.fallback_batches == 0,
                "generated mine or player used a fallback texture");
        pixels.fill(0U);
        glReadPixels(0, 0, kWidth, kHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        require(glGetError() == GL_NO_ERROR, "generated mine framebuffer readback failed");
        std::size_t mine_colored_pixels = 0;
        for (std::size_t offset = 0; offset < pixels.size(); offset += 4U) {
            if (pixels[offset] > 30U || pixels[offset + 1] > 30U || pixels[offset + 2] > 30U) {
                ++mine_colored_pixels;
            }
        }
        require(mine_colored_pixels > 1000, "generated mine render produced no visible geometry");
        std::cout << "PASS: rendered generated mine with Alchemist, chunks="
                  << generated.chunks.size()
                  << " instances=" << mine_stats.instances
                  << " placed_triangles=" << mine_stats.placed_triangles
                  << " textures=" << mine_stats.texture_resources
                  << " colored_pixels=" << mine_colored_pixels << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
