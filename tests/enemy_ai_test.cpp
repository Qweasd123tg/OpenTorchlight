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

#include <cmath>
#include <iostream>
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
        const auto attack = enemies.update(
            0.0F, player_position, player, world);
        require(attack.size() == 1 &&
                    attack.front().state == torchlight::EnemyAiState::attacked &&
                    attack.front().damage >= 51 && attack.front().damage <= 106 &&
                    attack.front().player_health == player.health() && player.alive(),
                "monster did not apply its level-scaled damage");

        torchlight::ArmorItem chest;
        chest.slot = torchlight::ArmorSlot::chest;
        chest.damage_defense.natural_armor = 10;
        player.equip(chest);
        require(player.armor_class() == 32,
                "equipped armor was not added to passive armor");
        chest.damage_defense.natural_armor = 20;
        player.equip(chest);
        require(player.armor_class() == 42,
                "new armor did not replace the same equipment slot");
        const auto waiting = enemies.update(
            0.0F, player_position, player, world);
        require(waiting.size() == 1 &&
                    waiting.front().state == torchlight::EnemyAiState::waiting &&
                    waiting.front().damage == 0,
                "monster ignored its attack cooldown");

        for (int frame = 0; frame < 40 && player.alive(); ++frame) {
            static_cast<void>(
                enemies.update(0.1F, player_position, player, world));
        }
        require(!player.alive() && player.health() == 0.0F,
                "repeated monster attacks did not kill the player");

        std::cout << "PASS: monster detected, chased and attacked a level-one player\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
