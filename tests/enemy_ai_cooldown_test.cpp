#include "ai_cooldown_fixture.hpp"
#include "attack_fixture.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
std::size_t assertions = 0;

void require(bool condition, const char* message) {
    ++assertions;
    if (!condition) throw std::runtime_error(message);
}

torchlight::PlayerPrototype player_prototype(float health = 10000.0F) {
    torchlight::PlayerPrototype result;
    result.minimum_health = result.maximum_health = health;
    return result;
}

struct Session {
    test_fixture::World fixture;
    torchlight::PlayerCombatState player{player_prototype(), 1};
    torchlight::EnemyController enemies{1};

    Session(const char* pak, const char16_t* name, float action_duration = 1.0F)
        : fixture(pak) {
        fixture.spawn(name);
        auto& loadout = fixture.world.entities().front().attacks;
        for (auto& attack : loadout.innate) attack.speed_denominator = 1;
        if (loadout.right) loadout.right->speed_denominator = 1;
        if (loadout.left) loadout.left->speed_denominator = 1;
        enemies.set_animation_resolver(test_fixture::clips(action_duration));
    }

    torchlight::EnemyAiUpdate step(float seconds,
                                  const std::array<float, 3>& position = {}) {
        // A completed action's final HIT is delivered before the next decision.
        const auto dt = std::isfinite(seconds) && seconds >= 0 ? seconds : 0;
        enemies.advance_animations(dt, fixture.world, player);
        const auto id = fixture.world.entities().front().id;
        if (const auto* action = enemies.action(id)) {
            const auto events = action->playback().frame_events();
            for (const auto& event : events)
                static_cast<void>(enemies.perform_attack(id, event, position, player, fixture.world));
        }
        enemies.finish_animation_frame();
        const auto updates = enemies.update(seconds, position, player, fixture.world);
        require(updates.size() == 1, "single-enemy update count changed");
        return updates.front();
    }
};

void check_next_attack(const char* pak, const char16_t* name,
                       float action_duration, int expected_ticks) {
    Session session(pak, name, action_duration);
    require(session.step(0).state == torchlight::EnemyAiState::attacking,
            "first attack must not wait for an unstarted AI cooldown");
    require(session.player.health() == 10000, "start must not deal damage");
    for (int tick = 1; tick < expected_ticks; ++tick) {
        const auto update = session.step(0.0625F);
        require(update.state == torchlight::EnemyAiState::waiting && update.damage == 0,
                "attack restarted before both independent gates expired");
        // A prior action may issue its terminal HIT while its AI cooldown is still waiting.
    }
    require(session.step(0.0625F).state == torchlight::EnemyAiState::attacking,
            "attack did not restart when both gates expired (serial timers?)");
}

void check_loading(const char* pak) {
    struct Case { const char16_t* name; float unit; std::optional<float> weapon; };
    const Case cases[] = {
        {u"DEFAULT", 0, std::nullopt}, {u"FAST", 0, std::nullopt},
        {u"SLOW", 2, std::nullopt}, {u"INHERITED", 2, std::nullopt},
        {u"OVERRIDE", 0.5F, std::nullopt}, {u"ARMED", 1.5F, 0.5F},
        {u"LEFT_ARMED", 1.5F, 0.5F}, {u"SPAWN_ARMED", 1.5F, 0.5F},
        {u"DEFAULT_WEAPON", 0, 0.0F}, {u"NEGATIVE_WEAPON", 0.5F, -3.0F},
        {u"NEGATIVE_UNIT", -0.25F, 0.5F},
    };
    for (const auto& entry : cases) {
        test_fixture::World fixture(pak);
        fixture.spawn(entry.name);
        const auto& entity = fixture.world.entities().front();
        require(entity.ai_attack_cooldown == entry.unit,
                "UNIT AI_ATTACKCOOLDOWN/default/inheritance was not loaded");
        require(entity.equipped_ai_attack_cooldown == entry.weapon,
                "weapon AI_ATTACKCOOLDOWN/default/selection was not loaded");
        test_fixture::World placed(pak, entry.name);
        require(placed.world.entities().size() == 1, "placed fixture did not import");
        const auto& imported = placed.world.entities().front();
        require(imported.ai_attack_cooldown == entity.ai_attack_cooldown &&
                    imported.equipped_ai_attack_cooldown == entity.equipped_ai_attack_cooldown,
                "placed and spawned cooldown loading diverged");
    }
    for (const auto* name : {u"NAN_UNIT", u"INF_UNIT", u"NAN_WEAPON", u"INF_WEAPON"}) {
        test_fixture::World fixture(pak);
        bool rejected = false;
        try { fixture.spawn(name); }
        catch (const std::runtime_error& error) {
            rejected = std::string(error.what()).find("AI attack cooldown") != std::string::npos;
        }
        require(rejected && fixture.world.entities().empty(),
                "non-finite cooldown was accepted or produced a partial entity");
    }
}

void check_scalar() {
    torchlight::MonsterAiCooldown timer;
    require(!timer.blocks_attack(), "default AI cooldown is not ready");
    timer.attack_started(1.5F, 0.5F);
    require(timer.remaining == 2 && timer.blocks_attack(), "cooldown contributions not added");
    timer.update(3);
    require(timer.remaining == -1 && !timer.blocks_attack(), "signed remainder was clamped");
    timer.attack_started(1.5F, 0.5F);
    require(timer.remaining == 2, "overshoot shortened a fresh cooldown");
    timer.remaining = -100;
    timer.attack_started(0.5F, -3.0F);
    require(timer.remaining == 0.5F, "negative weapon must be clamped BEFORE adding UNIT");
    timer.remaining = 1;
    timer.attack_started(0.25F, 0.5F);
    require(timer.remaining == 1.75F, "positive existing timer was discarded");
    timer.remaining = -1;
    timer.attack_started(-0.25F, std::nullopt);
    require(timer.remaining == -0.25F, "UNIT contribution was incorrectly clamped afterward");
    timer.remaining = 0;
    timer.attack_started(-0.25F, 0.5F);
    require(timer.remaining == 0.25F, "weapon and negative UNIT order is wrong");
    timer.update(0.25F);
    require(timer.remaining == 0 && !timer.blocks_attack(), "zero boundary must permit attack");
}

void check_state_paths(const char* pak) {
    Session lost(pak, u"SLOW");
    require(lost.step(0).state == torchlight::EnemyAiState::attacking, "missing initial attack");
    for (int i = 0; i < 24; ++i) {
        require(lost.step(0.0625F, {100, 0, 0}).state == torchlight::EnemyAiState::idle,
                "follow radius should drop the target");
    }
    require(lost.step(0).state == torchlight::EnemyAiState::waiting,
            "reacquiring a target reset AI cooldown");
    for (int i = 0; i < 7; ++i)
        require(lost.step(0.0625F).state == torchlight::EnemyAiState::waiting,
                "AI timer expired too early after target reacquisition");
    require(lost.step(0.0625F).state == torchlight::EnemyAiState::attacking,
            "AI timer stopped advancing while there was no target");

    Session denied(pak, u"SLOW");
    denied.enemies.set_animation_resolver({});
    for (int i = 0; i < 16; ++i)
        require(denied.step(0.0625F).state == torchlight::EnemyAiState::unavailable,
                "invalid attack must not start");
    denied.enemies.set_animation_resolver(test_fixture::clips());
    require(denied.step(0).state == torchlight::EnemyAiState::attacking,
            "failed attack incorrectly armed AI cooldown");
    for (float delta : {0.0F, -1.0F, std::numeric_limits<float>::infinity(),
                        std::numeric_limits<float>::quiet_NaN()})
        require(denied.step(delta).state == torchlight::EnemyAiState::waiting,
                "invalid elapsed time must not bypass active cooldown");
    for (int i = 0; i < 31; ++i)
        require(denied.step(0.0625F).state == torchlight::EnemyAiState::waiting,
                "waiting update rewrote cooldown");
    require(denied.step(0.0625F).state == torchlight::EnemyAiState::attacking,
            "waiting updates kept rearming cooldown");

    Session disabled(pak, u"SLOW");
    disabled.fixture.world.entities().front().enabled = false;
    require(disabled.enemies.update(0.0625F, {}, disabled.player, disabled.fixture.world).empty(),
            "disabled entity acquired an AI action");
    require(disabled.player.health() == 10000.0F, "disabled entity dealt damage");
}

void check_independent(const char* pak) {
    Session fast(pak, u"FAST"), slow(pak, u"SLOW");
    int counts[2] = {0,0};
    for (int frame=0; frame<=32; ++frame) {
        const float dt = frame ? .0625F : 0;
        if (fast.step(dt).state == torchlight::EnemyAiState::attacking) ++counts[0];
        if (slow.step(dt).state == torchlight::EnemyAiState::attacking) ++counts[1];
    }
    require(counts[0] == 3 && counts[1] == 2, "independent action/AI clocks diverged");
    std::cout << "Starts over [0,2]: AI=0 -> " << counts[0] << "; AI=2 -> " << counts[1] << '\n';
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 2) { std::cerr << "usage: enemy_ai_cooldown_test synthetic-pak.zip\n"; return 2; }
        check_scalar();
        check_loading(argv[1]);
        check_next_attack(argv[1], u"DEFAULT", 1, 16);
        check_next_attack(argv[1], u"FAST", 1, 16);
        check_next_attack(argv[1], u"SLOW", 1, 32);
        check_next_attack(argv[1], u"INHERITED", 1, 32);
        check_next_attack(argv[1], u"ARMED", 1, 32);
        check_next_attack(argv[1], u"SLOW", 4, 64);
        check_next_attack(argv[1], u"WEAPON_ONLY", 0.25F, 8);
        check_next_attack(argv[1], u"NEGATIVE_WEAPON", 0.25F, 8);
        check_next_attack(argv[1], u"NEGATIVE_UNIT", 0.125F, 4);
        check_state_paths(argv[1]);
        check_independent(argv[1]);
        std::cout << "PASS: " << assertions << " AI cooldown assertions; synthetic resources only\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL after " << assertions << " assertions: " << error.what() << '\n';
        return 1;
    }
}
