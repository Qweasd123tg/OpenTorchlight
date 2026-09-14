#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/unit_definition.hpp"

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
}

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: player_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const auto players =
            torchlight::load_playable_players(archive, resources, definitions);
        require(players.size() == 3, "unexpected playable player count");
        require(players[0].name == u"Alchemist" && players[1].name == u"Destroyer" &&
                    players[2].name == u"Vanquisher",
                "playable player order or names changed");
        require(players[0].guid == -8268919844649954850LL,
                "Alchemist GUID changed");
        require(players[0].walking_speed == 2.5F && players[0].running_speed == 6.25F,
                "Alchemist movement speeds changed");
        require(players[0].minimum_health == 200.0F &&
                    players[0].maximum_health == 200.0F &&
                    players[1].maximum_health == 300.0F &&
                    players[2].maximum_health == 200.0F,
                "playable player health graphs changed");
        require(players[0].strength == 6 && players[0].dexterity == 7 &&
                    players[0].magic == 10 && players[0].defense == 5,
                "Alchemist starting stats changed");
        require(players[0].damage_defense.natural_armor == 0 &&
                    players[0].damage_defense.effective(
                        torchlight::DamageType::physical) == 0,
                "unequipped Alchemist unexpectedly has armor");
        require(players[0].minimum_armor_bonus == 20 &&
                    players[0].maximum_armor_bonus == 20 &&
                    players[1].minimum_armor_bonus == 20 &&
                    players[2].minimum_armor_bonus == 20,
                "playable passive armor effects changed");
        require(players[0].starting_weapon &&
                    players[0].starting_weapon->name == u"Moldy Staff" &&
                    players[0].starting_weapon->guid == 5521717854978183646LL &&
                    players[0].starting_weapon->level == 1 &&
                    players[0].starting_weapon->minimum_damage_percent == 110 &&
                    players[0].starting_weapon->maximum_damage_percent == 120 &&
                    players[0].starting_weapon->rarity_damage_modifier == 80 &&
                    players[0].starting_weapon->speed_damage_modifier == 115 &&
                    players[0].starting_weapon->base_weapon_damage == 21.0F &&
                    std::fabs(players[0].starting_weapon->range - 0.8F) < 0.0001F,
                "Alchemist starting staff combat data changed");
        require(players[1].starting_weapon &&
                    players[1].starting_weapon->name == u"Rusty Blade" &&
                    players[2].starting_weapon &&
                    players[2].starting_weapon->name == u"Loose Shortbow" &&
                    players[2].starting_weapon->display_name == u"Practice Bow" &&
                    players[2].starting_weapon->range == 7.0F,
                "playable player starting equipment changed");
        torchlight::FixedSceneGeometry geometry;
        torchlight::append_player_geometry(archive, players[0], {0.0F, 0.0F, 50.0F}, geometry);
        require(geometry.meshes.size() == 1 && geometry.instances.size() == 1,
                "player geometry was not appended once");
        require(geometry.unique_vertex_count > 0 && geometry.unique_index_count > 0,
                "player mesh has no geometry");
        const torchlight::LevelSceneLoader scene_loader(archive);
        const auto main = scene_loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        const auto rules = scene_loader.load_rules(main.strata.front().ruleset);
        const torchlight::RandomLevelGenerator generator(scene_loader);
        const auto level = generator.generate(rules, 42U);
        const auto start = torchlight::generated_player_start(scene_loader, level);
        require(std::isfinite(start[0]) && std::isfinite(start[1]) &&
                    std::isfinite(start[2]),
                "generated player start is not finite");
        std::cout << "PASS: loaded 3 playable players and appended Alchemist mesh, vertices="
                  << geometry.unique_vertex_count << " indices=" << geometry.unique_index_count
                  << " start=" << start[0] << ',' << start[1] << ',' << start[2] << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
