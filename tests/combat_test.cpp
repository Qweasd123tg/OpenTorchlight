#include "torchlight/scene_animation.hpp"
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
                    players.front().starting_weapon &&
                    players.front().starting_weapon->speed == 110 &&
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
        auto& spawned = world.entities().front();
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

        torchlight::AttackAnimationCatalog catalog(archive);
        torchlight::CombatController combat(players.front(), 31);
        combat.set_animation_resolver([&](std::string_view mesh, std::string_view prefix) {
            return catalog.resolve(mesh, prefix);
        });
        require(combat.maximum_damage() > 0 && combat.minimum_damage() ==
                    static_cast<std::int32_t>(std::ceil(combat.maximum_damage() * .5F)),
                "ordinary character damage was not derived from the selected weapon");
        require(combat.select_target(world, spawned.position, .5F), "target selection failed");
        auto far = spawned.position; far[0] += 100;
        require(combat.update(0, far, world).state == torchlight::CombatState::approaching,
                "out-of-range target did not request approach");
        std::size_t applied_hits = 0;
        for (int attempt = 0; attempt < 512 && spawned.alive; ++attempt) {
            const auto hp = spawned.health;
            const auto start = combat.update(0, spawned.position, world);
            if (start.state != torchlight::CombatState::attacking)
                throw std::runtime_error("original clip could not start: " + combat.last_attack_issue());
            require(spawned.health == hp, "start dealt damage without HIT");
            const auto& action = combat.action();
            require(action.clip() && action.clip()->bind_skeleton, "model/clip bind pose was lost");
            auto clip_name = action.clip()->animation_name;
            for (auto& c : clip_name) if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
            require(clip_name.find(action.description().animation_prefix) == 0,
                    "original clip does not match chosen attack family");
            require(combat.select_target(world, spawned.position, .5F) &&
                    combat.update(0, spawned.position, world).state == torchlight::CombatState::waiting,
                    "repeat selection bypassed active action");
            combat.clear_target();
            require(combat.select_target(world, spawned.position, .5F) &&
                    combat.update(0, spawned.position, world).state == torchlight::CombatState::waiting,
                    "clear/reselect bypassed active action");
            combat.advance_animation(action.clip()->duration / action.playback().playback_speed() + .01F);
            const auto events = action.playback().frame_events();
            for (const auto& event : events) {
                auto foreign = event; ++foreign.execution_id;
                require(combat.perform_attack(foreign, spawned.position, world, logic).damage == 0,
                        "foreign action applied damage");
                const auto result = combat.perform_attack(event, spawned.position, world, logic);
                if (result.damage > 0) ++applied_hits;
                require(combat.perform_attack(event, spawned.position, world, logic).damage == 0,
                        "duplicate event applied damage");
            }
            combat.finish_animation_frame();
            require(!combat.attack_in_progress(), "completed clip retained a second action gate");
        }
        require(applied_hits > 0 && !spawned.alive && spawned.health == 0 && combat.target_id() == 0,
                "resource-backed ordinary HIT chain did not kill/release target");
        const auto corpse_position = spawned.position;
        static_cast<void>(world.resolve_death_loot(logic));
        const auto events = logic.take_events();
        require(has_event(events, spawner, u"Monster Killed") &&
                has_event(events, spawner, u"All Monsters Dead"), "kill did not continue spawner logic");
        require(!combat.select_target(world, corpse_position, 1), "corpse remained selectable");
        std::cout << "PASS: selected, approached, damaged and killed an original monster\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
