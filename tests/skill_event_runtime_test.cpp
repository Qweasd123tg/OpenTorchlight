// Skill event runtime: startSkill guards, triggerEvent dispatch, spawner
// Missiles branch, fire-sink launches, MISSILEHIT/MISSILEDIE callbacks.
// original-code: startSkill @0xca9150, triggerEvent @0xca5950, startEvent
// @0xcc4300, spawnUnitByIndex Missiles branch @0xa167a0, createAndFireMissile
// @0xa0adc0, missileApplyingEffects @0xcb8360, missileDieing @0xcb7670;
// research/skill-effect-dispatch.md.
//
// Mechanics run without assets. The SEEKING section is resource-backed: it
// loads the real SEEKING.LAYOUT.adm when TORCHLIGHT_GAME_DIR is set, else
// SKIP. The skill chain under test never calls the missile runtime: launch
// records are produced only by the chain, and only the application-role fire
// sink (the documented createAndFireMissile seam) forwards them into a real
// MissileRuntime, which starts empty. The test never spawns a missile except
// through a chain-produced record, and never substitutes the event handler.
#include "torchlight/skill_event_runtime.hpp"

#include "torchlight/missile_runtime.hpp"
#include "torchlight/pak_archive.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace {
int failures = 0;
int assertions = 0;
void require(bool cond, const char* what) {
    ++assertions;
    if (!cond) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}

torchlight::AdmProperty text_property(std::u16string name, std::u16string value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::string;
    result.value = std::move(value);
    return result;
}

torchlight::AdmProperty bool_property(std::u16string name, bool value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::boolean;
    result.value = value;
    return result;
}

torchlight::LayoutManifest spawner_scene(std::u16string group, std::u16string resource) {
    torchlight::LayoutManifest scene;
    scene.source_path = "synthetic";
    torchlight::LayoutObject object;
    object.descriptor = u"Unit Spawner";
    object.name = u"Unit Spawner0";
    object.id = 5;
    object.properties.push_back(bool_property(u"SPAWN ON CREATE", true));
    object.properties.push_back(text_property(u"GROUP", std::move(group)));
    object.properties.push_back(text_property(u"RESOURCE", std::move(resource)));
    scene.objects.push_back(std::move(object));
    return scene;
}

torchlight::SkillCastContext live_cast() {
    torchlight::SkillCastContext context;
    context.caster_id = 7;
    context.origin = {1.0F, 2.0F, 3.0F};
    context.direction = {1.0F, 0.0F, 0.0F};
    return context;
}
} // namespace

int main() {
    using torchlight::SkillEventType;

    require(torchlight::skill_event_type_name(SkillEventType::start) == u"EVENT_START",
            "event name 0 is EVENT_START");
    require(torchlight::skill_event_type_name(SkillEventType::missile_hit) == u"EVENT_MISSILEHIT",
            "event name 6 is EVENT_MISSILEHIT");
    require(torchlight::skill_event_type_name(SkillEventType::missile_die) == u"EVENT_MISSILEDIE",
            "event name 7 is EVENT_MISSILEDIE");
    require(torchlight::skill_event_type_name(SkillEventType::unit_create) == u"EVENT_UNIT_CREATE",
            "event name 10 is EVENT_UNIT_CREATE");

    {
        // Guard matrix in original order: scene, caster, alive, chance, cooldown.
        torchlight::SkillEventRuntime empty("EMPTY", torchlight::LayoutManifest{});
        auto refused = empty.start_skill(live_cast());
        require(!refused.started && refused.issue == "no_skill_scene", "empty scene refuses");
        require(!empty.has_event(SkillEventType::start), "empty scene has no START");

        torchlight::SkillEventRuntime runtime("TEST", spawner_scene(u"Missiles", u"SHOT"));
        torchlight::SkillCastContext context = live_cast();
        context.caster_id = 0;
        auto no_caster = runtime.start_skill(context);
        require(!no_caster.started && no_caster.issue == "no_caster", "null caster refuses");
        context = live_cast();
        context.caster_alive = false;
        auto down = runtime.start_skill(context);
        require(!down.started && down.issue == "caster_down", "dead caster refuses");
        context = live_cast();
        context.chance_passed = false;
        auto chance = runtime.start_skill(context);
        require(!chance.started && chance.issue == "chance", "failed chance refuses");
        context = live_cast();
        context.cooldown_remaining = 1.0F;
        auto cooling = runtime.start_skill(context);
        require(!cooling.started && cooling.issue == "cooldown", "cooldown refuses");
        context = live_cast();
        context.cooldown_seconds = 2.0F;
        auto first = runtime.start_skill(context);
        require(first.started && first.issue.empty(), "live cast starts");
        auto second = runtime.start_skill(live_cast());
        require(!second.started && second.issue == "cooldown", "armed cooldown refuses");
        runtime.advance(2.0F);
        auto third = runtime.start_skill(live_cast());
        require(third.started, "cooldown advance releases");
        require(!runtime.trigger(SkillEventType::end), "unsupported event triggers nothing");
        require(!runtime.has_event(SkillEventType::end), "unsupported event boundary is explicit");
        require(!runtime.notify_missile_impact(4242, 9, false, false),
                "unknown missile id posts nothing");
    }

    {
        // Timeline routing: t=0 points fire through the scene (Spawn Units on
        // the spawner launches a second time); late and dangling points are
        // retained, never fired.
        torchlight::LayoutManifest scene = spawner_scene(u"Missiles", u"SHOT");
        scene.timeline_points.push_back({1, 5, u"Spawn Units", 0.0F});
        scene.timeline_points.push_back({1, 5, u"Spawn Units", 0.5F});
        scene.timeline_points.push_back({1, 9999, u"Spawn Units", 0.0F});
        torchlight::SkillEventRuntime timeline("TEST", std::move(scene));
        require(timeline.start_skill(live_cast()).started, "timeline scene starts");
        require(timeline.take_missile_launches().size() == 2,
                "t=0 timeline point fires Spawn Units through the scene");
        auto deferred = timeline.take_deferred_timeline_points();
        require(deferred.size() == 2, "late and dangling points stay deferred");
    }

    {
        // Non-missile spawn groups are retained, never acted on.
        torchlight::SkillEventRuntime runtime("TEST", spawner_scene(u"Particle", u"FOO"));
        auto started = runtime.start_skill(live_cast());
        require(started.started, "particle scene starts");
        require(runtime.take_missile_launches().empty(), "particle scene launches nothing");
        require(!runtime.has_event(SkillEventType::missile_hit),
                "no missile path without a Missiles launch");
        auto unsupported = runtime.take_unsupported_spawns();
        require(unsupported.size() == 1 && unsupported.front().group == "Particle",
                "particle spawn retained as boundary");
    }

    {
        // Ladder gate and the no-data / open-leg paths (no pak).
        torchlight::SkillTriggerLevel rung;
        rung.weapon_damage_pct = 40.0F;
        rung.soak_scale_pct = 60.0F;
        rung.present = true;
        torchlight::SkillEventRuntime leveled("TEST", spawner_scene(u"Missiles", u"SHOT"),
                                              {rung});
        torchlight::SkillCastContext high = live_cast();
        high.skill_level = 2;
        auto refused_level = leveled.start_skill(high);
        require(!refused_level.started && refused_level.issue == "level",
                "rung outside the ladder refuses");
        require(leveled.start_skill(live_cast()).started, "rung 1 starts");
        leveled.drain_launches([](const torchlight::SkillMissileLaunch& launch) {
            require(launch.skill_level == 1, "launch binds the cast rung");
            return torchlight::SkillMissileFireOutcome{11, ""};
        });
        require(leveled.notify_missile_impact(11, 5, false, false, true), "leveled hit dispatches");
        auto damage = leveled.take_weapon_damage_requests();
        require(damage.size() == 1 && damage.front().weapon_damage_pct == 40.0F &&
                    damage.front().soak_scale_pct == 60.0F && damage.front().scalars_present &&
                    damage.front().skill_level == 1 && damage.front().victim_id == 5 &&
                    damage.front().caster_id == 7,
                "weapon leg carries rung scalars and binding");
        bool saw_unit_hit = false;
        bool saw_unit_die = false;
        for (const auto& event : leveled.take_skill_events()) {
            if (event.type == SkillEventType::unit_hit && event.victim_id == 5) saw_unit_hit = true;
            if (event.type == SkillEventType::unit_die && event.victim_id == 5) saw_unit_die = true;
        }
        require(saw_unit_hit, "UNITHIT poster observed");
        require(saw_unit_die, "UNITDIE poster observed on the death fact");
        require(leveled.take_open_effect_legs().empty(), "zero entries stay a silent no-op");

        torchlight::SkillTriggerLevel rich = rung;
        rich.effect_entries = 2;
        torchlight::SkillEventRuntime legged("TEST", spawner_scene(u"Missiles", u"SHOT"), {rich});
        require(legged.start_skill(live_cast()).started, "rich scene starts");
        legged.drain_launches([](const torchlight::SkillMissileLaunch&) {
            return torchlight::SkillMissileFireOutcome{12, ""};
        });
        require(legged.notify_missile_impact(12, 5, false, false), "rich hit dispatches");
        auto open = legged.take_open_effect_legs();
        require(open.size() == 1 && open.front().entry_count == 2, "entries stay open, never run");

        torchlight::SkillEventRuntime dataless("TEST", spawner_scene(u"Missiles", u"SHOT"));
        require(dataless.start_skill(live_cast()).started, "dataless scene starts");
        dataless.drain_launches([](const torchlight::SkillMissileLaunch&) {
            return torchlight::SkillMissileFireOutcome{13, ""};
        });
        require(dataless.notify_missile_impact(13, 5, false, false), "dataless hit dispatches");
        auto open_damage = dataless.take_weapon_damage_requests();
        require(open_damage.size() == 1 && !open_damage.front().scalars_present,
                "missing ladder marks scalars open, never defaults");
    }

    {
        // Sink refusals ride explicit codes, never guessed missiles.
        torchlight::SkillEventRuntime runtime("TEST", spawner_scene(u"Missiles", u"SHOT"));
        require(runtime.start_skill(live_cast()).started, "missile scene starts");
        require(runtime.take_missile_launches().size() == 1, "one launch produced");
        torchlight::SkillEventRuntime missing("TEST", spawner_scene(u"Missiles", u"SHOT"));
        require(missing.start_skill(live_cast()).started, "second scene starts");
        missing.drain_launches([](const torchlight::SkillMissileLaunch&) {
            return torchlight::SkillMissileFireOutcome{0, "template_missing"};
        });
        auto refused = missing.take_refused_launches();
        require(refused.size() == 1 && refused.front().issue == "template_missing" &&
                    refused.front().missile_resource == "SHOT",
                "template refusal carries resource and code");
    }

    if (const char* game_dir = std::getenv("TORCHLIGHT_GAME_DIR")) {
        try {
            const std::string pak = std::string(game_dir) + "/pak.zip";
            const torchlight::PakArchive archive(pak);
            const torchlight::LevelSceneLoader loader(archive);
            auto scene = loader.load_layout("media/skills/vanquisher/seeking/SEEKING.LAYOUT.adm");
            const auto trigger_levels = torchlight::load_skill_trigger_levels(
                archive, "media/skills/vanquisher/seeking/SEEKING.DAT.adm");
            require(trigger_levels.has_value() && trigger_levels->size() == 12,
                    "SEEKING trigger ladder loads 12 rungs");
            if (!trigger_levels.has_value()) return failures == 0 ? 0 : 1;
            require((*trigger_levels)[0].present &&
                        (*trigger_levels)[0].weapon_damage_pct == 40.0F &&
                        (*trigger_levels)[0].soak_scale_pct == 60.0F &&
                        (*trigger_levels)[0].effect_entries == 0,
                    "SEEKING rung 1 is 40/60 with no effect entries");
            require(!torchlight::load_skill_trigger_levels(archive, "media/skills/NOPE.DAT.adm")
                         .has_value(),
                    "missing skill DAT refuses");
            torchlight::SkillEventRuntime seeking("SEEKING", std::move(scene), *trigger_levels);
            require(seeking.has_event(SkillEventType::start), "SEEKING has START");
            require(!seeking.has_event(SkillEventType::missile_hit),
                    "SEEKING has no missile path before the cast");
            auto cast = seeking.start_skill(live_cast());
            require(cast.started, "SEEKING cast starts through the event chain");
            const auto missile_template =
                torchlight::load_missile_template(archive, "SEEKINGSHOT");
            require(missile_template.has_value(), "SEEKINGSHOT template loads from real pak");
            if (!missile_template.has_value()) return failures == 0 ? 0 : 1;
            std::printf("template SEEKINGSHOT: dist=%.3f vel=%.3f radius=%.3f aoe_r=%.3f\n",
                        missile_template->max_distance, missile_template->max_velocity,
                        missile_template->radius, missile_template->aoe_radius);
            require(std::isfinite(missile_template->max_velocity) &&
                        missile_template->max_velocity > 0.0F,
                    "SEEKINGSHOT velocity sane");

            // Application-role fire sink: the only place the missile runtime
            // is touched, fed exclusively by chain-produced launch records.
            // The sink records every launch it receives, so the record
            // content below is asserted on chain output, not test input.
            torchlight::MissileRuntime missiles;
            require(missiles.empty(), "missile runtime starts empty");
            std::size_t sink_calls = 0;
            std::vector<torchlight::SkillMissileLaunch> fired_launches;
            const auto sink = [&](const torchlight::SkillMissileLaunch& launch) {
                ++sink_calls;
                fired_launches.push_back(launch);
                torchlight::MissileSpawn spawn;
                spawn.origin = launch.origin;
                spawn.direction = launch.direction;
                spawn.owner_id = launch.caster_id;
                const auto id = missiles.spawn(*missile_template, spawn);
                return torchlight::SkillMissileFireOutcome{id, id == 0 ? "spawn_refused" : ""};
            };
            seeking.drain_launches(sink);
            require(sink_calls == 1, "fire sink ran once for the chain launch");
            require(fired_launches.size() == 1, "SEEKING produces one launch");
            if (fired_launches.size() == 1) {
                require(fired_launches.front().missile_resource == "SEEKINGSHOT",
                        "SEEKING launch names SEEKINGSHOT");
                require(fired_launches.front().origin == live_cast().origin,
                        "launch keeps cast origin");
                require(fired_launches.front().direction == live_cast().direction,
                        "launch keeps cast direction");
                require(fired_launches.front().caster_id == 7, "launch keeps caster");
                // SEEKING spawner COUNT is 3 in the resource: multi-launch
                // semantics stay open, exactly one launch is produced.
                require(fired_launches.front().spawner_count == 3 &&
                            fired_launches.front().repeated_count_open,
                        "SEEKING count 3 recorded as open repetition");
            }
            require(!missiles.empty(), "chain launch reached the missile runtime");
            require(seeking.has_event(SkillEventType::missile_hit),
                    "missile callbacks dispatch after the launch");
            require(seeking.take_refused_launches().empty(), "SEEKING launch not refused");
            require(seeking.take_deferred_timeline_points().empty(),
                    "SEEKING timeline points all fire at t=0");

            {
                // HIT: a live target on the flight line, impact re-enters
                // through the missile hook equivalent.
                torchlight::MissileCollider target;
                target.id = 99;
                target.position = {live_cast().origin[0] + missile_template->max_velocity * 0.5F,
                                   live_cast().origin[1], live_cast().origin[2]};
                target.radius = 1.0F;
                target.live_target = true;
                const torchlight::CollisionScene empty_scene{};
                std::uint64_t hit_missile = 0;
                std::uint64_t hit_victim = 0;
                for (int step = 0; step < 600 && hit_missile == 0; ++step) {
                    missiles.step(1.0F / 60.0F, {target}, empty_scene);
                    for (const auto& impact : missiles.take_impacts()) {
                        if (impact.victim_id != 0) {
                            hit_missile = impact.missile_id;
                            hit_victim = impact.victim_id;
                        }
                    }
                }
                require(hit_missile != 0 && hit_victim == 99, "SEEKINGSHOT hits the target");
                require(seeking.notify_missile_impact(hit_missile, hit_victim, false, false),
                        "hit impact dispatches");
                auto events = seeking.take_skill_events();
                bool saw_start = false;
                bool saw_hit = false;
                bool saw_unit_hit = false;
                for (const auto& event : events) {
                    if (event.type == SkillEventType::start) saw_start = true;
                    if (event.type == SkillEventType::missile_hit &&
                        event.missile_id == hit_missile && event.victim_id == 99 &&
                        event.damage_application_open)
                        saw_hit = true;
                    if (event.type == SkillEventType::unit_hit && event.victim_id == 99)
                        saw_unit_hit = true;
                }
                require(saw_start, "START event observed on the chain");
                require(saw_hit, "MISSILEHIT callback observed with open damage");
                require(saw_unit_hit, "UNITHIT poster observed on the SEEKING chain");
                auto weapon_hits = seeking.take_weapon_damage_requests();
                require(weapon_hits.size() == 1 && weapon_hits.front().victim_id == 99 &&
                            weapon_hits.front().weapon_damage_pct == 40.0F &&
                            weapon_hits.front().soak_scale_pct == 60.0F &&
                            weapon_hits.front().scalars_present &&
                            weapon_hits.front().skill_level == 1 &&
                            weapon_hits.front().caster_id == 7,
                        "weapon leg carries the SEEKING rung 40/60 contract");
                require(seeking.take_open_effect_legs().empty(),
                        "SEEKING effects leg is a proven no-op");
            }

            {
                // DIE: a second cast flies unobstructed to expiry, the
                // victimless end posts MISSILEDIE.
                require(seeking.start_skill(live_cast()).started, "second SEEKING cast starts");
                const std::size_t calls_before = sink_calls;
                fired_launches.clear();
                seeking.drain_launches(sink);
                require(sink_calls == calls_before + 1 && fired_launches.size() == 1,
                        "second cast launches again");
                const torchlight::CollisionScene empty_scene{};
                std::uint64_t dead_missile = 0;
                bool saw_expired = false;
                for (int step = 0; step < 3600 && dead_missile == 0; ++step) {
                    missiles.step(1.0F / 60.0F, {}, empty_scene);
                    for (const auto& impact : missiles.take_impacts()) {
                        if (impact.victim_id == 0) {
                            dead_missile = impact.missile_id;
                            saw_expired = saw_expired || impact.expired;
                        }
                    }
                }
                require(dead_missile != 0 && saw_expired, "SEEKINGSHOT expires unobstructed");
                require(seeking.notify_missile_impact(dead_missile, 0, false, true),
                        "expiry dispatches");
                bool saw_die = false;
                for (const auto& event : seeking.take_skill_events()) {
                    if (event.type == SkillEventType::missile_die &&
                        event.missile_id == dead_missile && event.expired)
                        saw_die = true;
                }
                require(saw_die, "MISSILEDIE callback observed");
            }
            require(!seeking.has_event(SkillEventType::end), "effect engine still bounded");
        } catch (const std::exception& e) {
            std::printf("FAIL: SEEKING chain threw: %s\n", e.what());
            ++failures;
        }
    } else {
        std::printf("SKIP: TORCHLIGHT_GAME_DIR unset, SEEKING chain skipped\n");
    }

    std::printf("skill_event_runtime: %d assertions, %d failures\n", assertions, failures);
    return failures == 0 ? 0 : 1;
}
