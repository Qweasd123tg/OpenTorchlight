#include "torchlight/adm_document.hpp"
#include "torchlight/combat.hpp"
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
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool has_event(const std::vector<torchlight::LogicEvent>& events,
               std::int64_t object_id, std::u16string_view output) {
    return std::any_of(events.begin(), events.end(), [&](const auto& event) {
        return event.object_id == object_id && event.output_name == output;
    });
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: combat_test --original /path/to/pak.zip\n";
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
        require(!players.empty() && players.front().name == u"Alchemist",
                "Alchemist combat prototype is missing");
        require(players.front().minimum_damage == 20 &&
                    players.front().maximum_damage == 20 &&
                    players.front().attack_speed == 80.0F &&
                    players.front().reach_bonus == 1.25F,
                "Alchemist base attack properties are wrong");

        constexpr std::int64_t spawner = 4789864784197325278LL;
        torchlight::LogicRuntime logic(layout, 31);
        torchlight::RuntimeEntityWorld world(
            layout, resources, definitions, spawn_classes, unit_types, 31, 10);
        const torchlight::SpawnRequest request{
            spawner, u"Skeletal Warrior", u"Monsters", 1};
        const auto stats = world.consume_spawn_requests({request}, logic);
        require(stats.entities_created == 1 && world.entities().size() == 1,
                "combat fixture monster was not spawned");
        const auto& spawned = world.entities().front();
        require(spawned.level == 10 && spawned.maximum_health >= 83.0F &&
                    spawned.maximum_health <= 118.0F &&
                    spawned.health == spawned.maximum_health &&
                    spawned.minimum_damage == 72 && spawned.maximum_damage == 107 &&
                    std::fabs(spawned.walking_speed - 1.3F) < 0.0001F &&
                    std::fabs(spawned.running_speed - 1.8F) < 0.0001F &&
                    spawned.attack_speed == 100.0F && spawned.sight_radius == 7.0F &&
                    spawned.reach_bonus == 0.75F &&
                    spawned.equipped_attack_name == u"Skeleton Sword" &&
                    std::fabs(spawned.weapon_range - 0.6F) < 0.0001F &&
                    std::fabs(spawned.attack_range - 1.55F) < 0.0001F &&
                    spawned.damage_defense.natural_armor == 40 &&
                    spawned.damage_defense.effective(
                        torchlight::DamageType::physical) == 40 &&
                    spawned.damage_defense.effective(
                        torchlight::DamageType::fire) == 40 &&
                    spawned.damage_defense.effective(
                        torchlight::DamageType::ice) == 20 &&
                    spawned.damage_defense.effective(
                        torchlight::DamageType::electric) == 32 &&
                    spawned.damage_defense.effective(
                        torchlight::DamageType::poison) == 32 &&
                    spawned.motion_radius == 4.5F && spawned.follow_radius == 18.0F,
                "monster level-scaled combat properties are wrong");
        static_cast<void>(logic.take_events());

        torchlight::CombatController combat(players.front(), 31);
        require(combat.attack_range() == 2.25F &&
                    std::fabs(combat.attack_interval() - 1.25F) < 0.0001F &&
                    combat.maximum_damage() >= 22 && combat.maximum_damage() <= 24 &&
                    combat.minimum_damage() == static_cast<std::int32_t>(
                        std::ceil(static_cast<float>(combat.maximum_damage()) * 0.5F)),
                "starting staff damage, reach or interval is wrong");
        require(combat.select_target(world, spawned.position, 0.5F) &&
                    combat.target_id() == spawned.id,
                "click selection did not choose the nearby monster");
        auto far_position = spawned.position;
        far_position[0] += 5.0F;
        require(combat.update(0.0F, far_position, world, logic).state ==
                    torchlight::CombatState::approaching,
                "out-of-range target did not request an approach");

        auto result = combat.update(0.0F, spawned.position, world, logic);
        require(result.state == torchlight::CombatState::attacked &&
                    result.damage == 1 &&
                    result.remaining_health == spawned.maximum_health - 1.0F,
                "level-ten monster armor did not absorb the starting attack");
        require(combat.update(0.0F, spawned.position, world, logic).state ==
                    torchlight::CombatState::waiting,
                "attack cooldown was ignored");
        for (int attack = 0;
             attack < 128 && result.state != torchlight::CombatState::killed;
             ++attack) {
            result = combat.update(combat.attack_interval(), spawned.position,
                                   world, logic);
        }
        require(result.state == torchlight::CombatState::killed &&
                    !world.entities().front().alive &&
                    world.entities().front().health == 0.0F &&
                    combat.target_id() == 0,
                "final attack did not kill and release the target");
        const auto events = logic.take_events();
        require(has_event(events, spawner, u"Monster Killed") &&
                    has_event(events, spawner, u"All Monsters Dead"),
                "combat kill did not continue the source spawner graph");
        require(!combat.select_target(world, spawned.position, 1.0F),
                "dead monster remained selectable");

        torchlight::WeaponItem replacement;
        replacement.minimum_damage = 7;
        replacement.maximum_damage = 14;
        replacement.prototype.range = 7.0F;
        combat.equip(replacement);
        require(combat.minimum_damage() == 7 && combat.maximum_damage() == 14 &&
                    combat.attack_range() == 8.45F,
                "picked-up weapon did not replace player combat properties");

        std::cout << "PASS: selected, approached, damaged and killed an original monster\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
