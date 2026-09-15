#include "torchlight/scene_animation.hpp"
#include "torchlight/adm_document.hpp"
#include "torchlight/enemy_ai.hpp"
#include "torchlight/entity_world.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_definition.hpp"
#include "torchlight/unit_type.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: enemy_ai_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const torchlight::SpawnClassCatalog spawn_classes(archive);
        const torchlight::UnitTypeHierarchy hierarchy(archive);
        const torchlight::UnitTypeResourceIndex unit_types(
            archive, hierarchy, resources, definitions);
        const torchlight::LevelSceneLoader scene_loader(archive);
        const auto layout = scene_loader.load_layout(
            "media/layouts/test/LOGICTEST.LAYOUT.adm");
        const auto players = torchlight::load_playable_players(
            archive, resources, definitions);
        require(players.front().minimum_health == 200.0F &&
                    players.front().maximum_health == 200.0F,
                "Alchemist level-one health graph is wrong");

        constexpr std::int64_t spawner = 4789864784197325278LL;
        torchlight::LogicRuntime logic(layout, 71);
        torchlight::RuntimeEntityWorld world(
            layout, resources, definitions, spawn_classes, unit_types, 71, 10);
        const torchlight::SpawnRequest request{
            spawner, u"Skeletal Warrior", u"Monsters", 1};
        require(world.consume_spawn_requests({request}, logic).entities_created == 1,
                "enemy fixture did not spawn");
        const auto start = world.entities().front().position;
        auto player_position = start;
        player_position[0] += 5.0F;
        torchlight::PlayerCombatState player(players.front(), 71);
        require(player.armor_class() == 21,
                "Alchemist passive armor bonus was not applied");
        torchlight::EnemyController enemies(71);
        torchlight::AttackAnimationCatalog catalog(archive);
        enemies.set_animation_resolver([&](std::string_view mesh, std::string_view prefix) {
            return catalog.resolve(mesh, prefix);
        });

        const auto chase = enemies.update(
            0.1F, player_position, player, world);
        require(chase.size() == 1 &&
                    chase.front().state == torchlight::EnemyAiState::chasing &&
                    chase.front().position_changed && enemies.alerted_count() == 1 &&
                    std::fabs(world.entities().front().position[0] -
                              (start[0] + 0.18F)) < 0.001F,
                "monster did not detect and chase the player at its running speed");

        player_position = world.entities().front().position;
        player_position[0] += 1.54F;
        player_position = world.entities().front().position;
        const auto hp_before = player.health();
        const auto attack = enemies.update(0, player_position, player, world);
        if (attack.size() != 1 || attack[0].state != torchlight::EnemyAiState::attacking)
            throw std::runtime_error("original enemy clip could not start: " +
                enemies.last_attack_issue(world.entities().front().id));
        require(player.health() == hp_before, "enemy damage occurred at action start");
        const auto id = world.entities().front().id;
        const auto* action = enemies.action(id);
        require(action && action->clip() && action->clip()->bind_skeleton,
                "enemy action has no resource-backed model/clip");
        torchlight::ArmorItem chest; chest.slot = torchlight::ArmorSlot::chest;
        chest.damage_defense.natural_armor = 10; player.equip(chest);
        require(player.armor_class() == 32, "equipped armor did not add to passive bonus");
        chest.damage_defense.natural_armor = 20; player.equip(chest);
        require(player.armor_class() == 42, "armor did not replace same slot");
        const auto waiting = enemies.update(0, player_position, player, world);
        require(waiting.size() == 1 && waiting[0].state == torchlight::EnemyAiState::waiting,
                "running action was overwritten");
        std::size_t applied_hits = 0;
        for (int frame = 0; frame < 100000 && player.alive(); ++frame) {
            constexpr float dt = .0625F;
            enemies.advance_animations(dt, world, player);
            action = enemies.action(id);
            if (action) {
                const auto events = action->playback().frame_events();
                for (const auto& event : events) {
                    const auto result = enemies.perform_attack(id, event, player_position, player, world);
                    if (result.damage > 0) ++applied_hits;
                    require(enemies.perform_attack(id, event, player_position, player, world).damage == 0,
                            "enemy HIT repeated damage");
                }
            }
            enemies.finish_animation_frame();
            static_cast<void>(enemies.update(dt, player_position, player, world));
        }
        require(applied_hits > 0 && !player.alive() && player.health() == 0,
                "resource-backed enemy HIT did not finish death chain within bounded window");
        require(!enemies.action(id)->active(), "target death left an attacking action alive");
        std::cout << "PASS: monster detected, chased and attacked a level-one player\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
