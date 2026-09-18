#include <algorithm>
#include "ai_cooldown_fixture.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/scene_animation.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <zlib.h>
using namespace torchlight;
namespace {
std::size_t checks = 0;
void require(bool b, const char *s) {
    ++checks;
    if (!b)
        throw std::runtime_error(s);
}
template <class F> void rejects(F f, const char *text) {
    bool rejected = false;
    try {
        f();
    } catch (const std::exception &) {
        rejected = true;
    }
    require(rejected, text);
}
FloorCheckpoint floor_state(test_fixture::World &f, const EnemyController &enemies) {
    FloorCheckpoint s;
    s.address = {u"Town", 0};
    s.layout_identity = checkpoint_layout_identity(f.manifest);
    s.player_position = {3, 0, 4};
    s.player_angle = 137;
    s.recovery_anchor = {1, 0, 2};
    s.recovery_angle = 17;
    s.world = CheckpointAccess::capture(f.world);
    s.logic = CheckpointAccess::capture(f.logic);
    s.enemies = CheckpointAccess::capture(enemies);
    return s;
}
CampaignCheckpoint make_save(const char *pak) {
    test_fixture::World f(pak);
    f.spawn(u"ARMED");
    f.spawn(u"INNATE");
    auto proto = load_playable_players(f.archive, f.resources, f.definitions).front();
    PlayerSession session(proto, 73, &f.hierarchy);
    for (const auto *name : {u"SWORD", u"MANA_CHEST", u"SWORD"}) {
        const auto result = f.world.consume_spawn_requests({{42, name, u"Items", 1}}, f.logic);
        require(result.entities_created == 1, "cannot spawn save fixture item");
        const auto id = session.pick_up(f.world, f.world.entities().back().id, f.logic);
        require(id != 0, "cannot pick fixture item");
        if (id < 3)
            require(session.equip(id) == InventoryChange::changed, "cannot equip save fixture");
    }
    session.give_gold(1234);
    require(session.health().spend_mana(13), "fixture mana spend failed");
    TorchlightRandom random(71);
    static_cast<void>(session.health().apply_damage(11, 11, DamageType::physical, random));
    // Save a real in-progress enemy clock; actions deliberately do not survive.
    AttackAnimationCatalog clips(f.archive);
    EnemyController enemies(81);
    enemies.set_animation_resolver(
        [&](std::string_view m, std::string_view p) { return clips.resolve(m, p); });
    static_cast<void>(enemies.update(0, {}, session.health(), f.world));
    require(enemies.action(f.world.entities().front().id)->active(), "enemy action did not start");
    const auto dead = f.world.entities()[1].id;
    require(f.world.kill(dead, f.logic), "fixture kill failed");
    rejects([&] { static_cast<void>(CheckpointAccess::capture(f.world)); },
            "pending loot accepted for save");
    static_cast<void>(f.world.resolve_death_loot(f.logic));
    CampaignCheckpoint c;
    c.slot = "hero-test";
    c.character_name = "Saved Hero";
    c.seed = 73;
    c.class_guid = proto.guid;
    c.resource_identity = checkpoint_resource_identity(f.archive);
    c.player = CheckpointAccess::capture(session);
    remember_floor(c, floor_state(f, enemies));
    auto main = c.floors.front();
    main.address = {u"Main", 1};
    main.player_position = {7, 0, 8};
    remember_floor(c, main);
    c.last_dungeon = main.address;
    CheckpointAccess::validate(c);
    return c;
}
void check_restored(const char *pak, const CampaignCheckpoint &c) {
    test_fixture::World f(pak);
    const auto p = load_playable_players(f.archive, f.resources, f.definitions).front();
    auto session = CheckpointAccess::restore_player(p, c.player, 73, &f.hierarchy);
    require(session.gold() == 1343, "wallet did not persist");
    require(session.inventory().items().size() == 3, "inventory instances did not persist");
    require(session.inventory().items()[0].resource_guid ==
                    session.inventory().items()[2].resource_guid &&
                session.inventory().items()[0].id != session.inventory().items()[2].id,
            "same-GUID instances merged");
    require(session.inventory().equipped(InventorySlot::weapon)->id == 1 &&
                session.inventory().equipped(InventorySlot::chest)->id == 2,
            "slots lost");
    require(session.health().maximum_mana() == 36 && session.health().mana() == 18,
            "mana value/max lost");
    require(session.health().health() == c.player.health &&
                session.health().maximum_health() == c.player.maximum_health,
            "HP rerolled");
    require(!session.combat().attack_in_progress() && session.combat().target_id() == 0,
            "old action/target restored");
    EnemyController enemies(1);
    const auto &saved = *find_floor(c, c.current);
    CheckpointAccess::restore_floor(saved, f.world, f.logic, enemies);
    require(!f.world.entities()[1].alive, "dead monster resurrected on load");
    require(!f.world.entities()[2].alive, "picked world item resurrected on load");
    require(f.world.entities().size() == saved.world.entities.size(),
            "world identity/count changed");
    require(enemies.ai_cooldown_remaining(f.world.entities()[0].id) ==
                saved.enemies.entries[0].ai_cooldown,
            "AI timer reset");
    require(!enemies.action(f.world.entities()[0].id)->active(),
            "saved transient attack remained live");
    auto again = c;
    again.player = CheckpointAccess::capture(session);
    again.floors[0] = floor_state(f, enemies);
    auto canonical = c;
    // A legacy DTO gains its previously implicit pre-effect HP at recapture.
    if (!canonical.player.base_health) canonical.player.base_health = session.health().base_health();
    if (!canonical.player.skills) canonical.player.skills = session.skills();
    // Explicit v6 enrichment only in the restored floor: older DTOs lacked
    // weapon allocation metadata and monster MAGIC. Do not rewrite HP/RNG,
    // loot flags, clocks, or any other previously serialized field.
    for (auto& entity : canonical.floors[0].world.entities) {
        const auto enrich = [&](std::optional<AttackDescription>& attack) {
            if (!attack || attack->damage_allocation_known) return;
            const auto* record = f.resources.find(attack->source_guid);
            if (record) hydrate_attack_damage(*attack, *f.definitions.load(*record));
        };
        if (entity.weapon_item && !entity.weapon_item->prototype.damage_percent) {
            const auto* record=f.resources.find(entity.weapon_item->prototype.guid);
            if (record) hydrate_weapon_damage(*entity.weapon_item,*f.definitions.load(*record));
        }
        enrich(entity.attacks.right); enrich(entity.attacks.left);
        if (!entity.attack_character.magic_known && entity.kind==MasterResourceKind::monster) {
            const auto* record=f.resources.find(entity.resource_guid);
            if (record) { entity.attack_character.magic=load_attack_character_values(*f.definitions.load(*record),nullptr).magic;
                entity.attack_character.magic_known=true; }
        }
    }
    require(encode_checkpoint(canonical) == encode_checkpoint(again),
            "roundtrip changed canonical checkpoint beyond explicit legacy HP/skill/weapon-metadata/MAGIC migration");
    auto transitions = CheckpointAccess::restore_transitions(c);
    WarpRequest back;
    back.dungeon_name = u"LASTDUNGEON";
    require(same_dungeon_address(transitions.resolve(back), *c.last_dungeon), "LASTDUNGEON lost");
    // RNG and IDs continue from the saved state, not constructor seed.
    test_fixture::World other(pak);
    EnemyController other_ai(1);
    CheckpointAccess::restore_floor(saved, other.world, other.logic, other_ai);
    f.spawn(u"ARMED");
    other.spawn(u"ARMED");
    require(f.world.entities().back().id == other.world.entities().back().id &&
                f.world.entities().back().health == other.world.entities().back().health &&
                CheckpointAccess::capture(f.world).random_state ==
                    CheckpointAccess::capture(other.world).random_state,
            "saved world RNG/next ID not restored");
}
void malformed(const CampaignCheckpoint &good) {
    const auto bytes = encode_checkpoint(good);
    for (std::size_t n = 0; n < bytes.size(); n += std::max<std::size_t>(1, bytes.size() / 97)) {
        auto bad = bytes;
        bad.resize(n);
        rejects([&] { static_cast<void>(decode_checkpoint(bad)); }, "truncated save accepted");
    }
    for (std::size_t n = 20; n < bytes.size(); n += std::max<std::size_t>(1, bytes.size() / 113)) {
        auto bad = bytes;
        bad[n] ^= 0x40;
        rejects([&] { static_cast<void>(decode_checkpoint(bad)); }, "bad CRC accepted");
    }
    // Corruptions with a VALID CRC exercise bounded payload decoding, not just the checksum guard.
    for (std::size_t n = 20; n < bytes.size(); n += std::max<std::size_t>(1, bytes.size() / 320)) {
        auto altered = bytes;
        altered[n] ^= 0xff;
        const auto crc = static_cast<std::uint32_t>(
            crc32(0, altered.data() + 20, static_cast<uInt>(altered.size() - 20)));
        for (unsigned i = 0; i < 4; ++i)
            altered[16 + i] = static_cast<std::uint8_t>(crc >> (8 * i));
        try {
            const auto decoded = decode_checkpoint(altered);
            require(encode_checkpoint(decoded) == altered, "accepted payload is not canonical");
        } catch (const CheckpointError &) {
            ++checks;
        }
    }
    auto bad = bytes;
    bad[8] = 99;
    rejects([&] { static_cast<void>(decode_checkpoint(bad)); }, "unknown format accepted");
    const auto reject = [&](auto change) {
        auto c = good;
        change(c);
        rejects([&] { static_cast<void>(encode_checkpoint(c)); }, "invalid DTO accepted");
    };
    reject([](auto &c) { c.slot = "../escape"; });
    reject([](auto &c) { c.seed = 0; });
    reject([](auto &c) { c.player.health = std::numeric_limits<float>::infinity(); });
    reject([](auto &c) { c.player.health = c.player.maximum_health + 1; });
    reject([](auto &c) { c.player.inventory.items[1].id = c.player.inventory.items[0].id; });
    reject([](auto &c) { c.player.inventory.slots[0] = 999; });
    reject([](auto &c) { c.player.inventory.slots[1] = c.player.inventory.slots[0]; });
    reject([](auto &c) { c.floors[0].world.next_id = 1; });
    reject([](auto &c) { c.floors[0].world.entities[1].id = c.floors[0].world.entities[0].id; });
    reject([](auto &c) { c.floors[0].world.entities[0].spawner_id = 999; });
    reject([](auto &c) { c.floors[0].enemies.entries[0].id = 999; });
    reject([](auto &c) { c.current = {u"Elsewhere", 8}; });
    reject([](auto &c) { c.floors.push_back(c.floors[0]); });
}
} // namespace
int main(int argc, char **argv) {
    try {
        if (argc != 4)
            throw std::runtime_error(
                "usage: save_checkpoint_test fixture directory self|write|read");
        SaveStore store(argv[2]);
        const std::string mode = argv[3];
        if (mode == "crash-temp" || mode == "race-a" || mode == "race-b") {
            auto c = store.read("hero-test");
            if (mode == "crash-temp") {
                static_cast<void>(store.write(c, [] { std::_Exit(42); }));
                throw std::runtime_error("crash hook returned");
            }
            std::ofstream marker(std::filesystem::path(argv[2]) / (mode + ".ready"));
            marker << "ready";
            marker.close();
            const auto until = std::chrono::steady_clock::now() + std::chrono::seconds(20);
            while (!std::filesystem::exists(std::filesystem::path(argv[2]) / "go")) {
                if (std::chrono::steady_clock::now() > until)
                    throw std::runtime_error("writer barrier timeout");
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            try {
                c.revision = store.write(c);
                require(c.revision == 2, "racing writer produced wrong revision");
            } catch (const CheckpointError &e) {
                if (std::string(e.what()).find("another process") != std::string::npos) {
                    std::cout << "expected competing writer conflict\n";
                    return 3;
                }
                throw;
            }
        } else if (mode == "read" || mode == "read-revision-2") {
            PakArchive pak(argv[1]);
            const auto c = store.read("hero-test", checkpoint_resource_identity(pak));
            check_restored(argv[1], c);
            require(c.revision == (mode == "read" ? 1U : 2U), "unexpected fresh-process revision");
        } else {
            auto c = make_save(argv[1]);
            check_restored(argv[1], decode_checkpoint(encode_checkpoint(c)));
            malformed(c);
            if (mode == "self")
                std::filesystem::remove_all(argv[2]);
            require(store.list().empty(), "empty directory not empty");
            c.revision = store.write(c);
            require(c.revision == 1, "first revision wrong");
            require(store.list(c.resource_identity).size() == 1 &&
                        store.list(c.resource_identity)[0].loadable(),
                    "slot list lost save");
            rejects([&] { static_cast<void>(store.read(c.slot, c.resource_identity ^ 1)); },
                    "incompatible pak accepted");
            if (mode == "self") {
                const auto before = encode_checkpoint(store.read(c.slot));
                rejects(
                    [&] {
                        static_cast<void>(store.write(
                            c, [] { throw std::runtime_error("injected pre-rename failure"); }));
                    },
                    "failed write unexpectedly succeeded");
                require(encode_checkpoint(store.read(c.slot)) == before,
                        "failed save replaced old file");
                auto outdated = c;
                c.revision = store.write(c);
                require(c.revision == 2, "second revision wrong");
                rejects([&] { static_cast<void>(store.write(outdated)); },
                        "stale revision overwrote newer save");
                std::ofstream bad(std::filesystem::path(argv[2]) / "damaged.otc", std::ios::binary);
                bad << "broken";
                bad.close();
                const auto slots = store.list();
                require(slots.size() == 2, "corrupt slot was silently hidden");
                require(std::count_if(slots.begin(), slots.end(),
                                      [](const auto &s) { return !s.loadable(); }) == 1,
                        "corruption not reported");
                rejects([&] { static_cast<void>(store.read("../../bad")); },
                        "path traversal accepted");
                // original-code: deleteCharacter removes the file then reloads.
                require(store.remove(c.slot), "written save was not deleted");
                require(store.list().size() == 1, "deleted save still listed");
                require(!store.remove(c.slot), "absent delete reported removal");
                require(!store.remove("never-saved"), "absent slot reported removal");
                rejects([&] { static_cast<void>(store.remove("../../bad")); },
                        "delete traversal accepted");
                for (const auto &e : std::filesystem::directory_iterator(argv[2]))
                    require(e.path().filename().string().find(".checkpoint-") != 0,
                            "temporary file leaked after failure");
            }
        }
        std::cout << "save_checkpoint " << mode << ": " << checks
                  << " assertions passed (authored resources; not original save compatibility)\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "checkpoint test: " << e.what() << '\n';
        return 1;
    }
}
