#include "torchlight/logic_runtime.hpp"
#include "torchlight/pak_archive.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

torchlight::AdmProperty text_property(std::u16string name, std::u16string value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::string;
    result.value = std::move(value);
    return result;
}

torchlight::AdmProperty int_property(std::u16string name, std::int32_t value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::integer;
    result.value = value;
    return result;
}

torchlight::AdmProperty uint_property(std::u16string name, std::uint32_t value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::unsigned_integer;
    result.value = value;
    return result;
}

torchlight::AdmProperty float_property(std::u16string name, float value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::floating;
    result.value = value;
    return result;
}

torchlight::AdmProperty bool_property(std::u16string name, bool value) {
    torchlight::AdmProperty result;
    result.name = std::move(name);
    result.type = torchlight::AdmValueType::boolean;
    result.value = value;
    return result;
}

torchlight::LayoutObject object(std::int64_t id, std::u16string descriptor,
                                std::vector<torchlight::AdmProperty> properties = {}) {
    torchlight::LayoutObject result;
    result.id = id;
    result.descriptor = std::move(descriptor);
    result.properties = std::move(properties);
    return result;
}

torchlight::LayoutLogicNode node(
    std::uint32_t id, std::int64_t object_id,
    std::vector<torchlight::LayoutLogicLink> links = {}) {
    return {id, object_id, 0.0F, 0.0F, std::move(links)};
}

bool has_event(const std::vector<torchlight::LogicEvent>& events, std::int64_t object_id,
               std::u16string_view output) {
    return std::any_of(events.begin(), events.end(), [&](const auto& event) {
        return event.object_id == object_id && event.output_name == output;
    });
}

torchlight::LayoutManifest synthetic_layout() {
    torchlight::LayoutManifest layout;

    auto sphere = object(1, u"Player Sphere Trigger",
                         {float_property(u"RADIUS", 2.0F)});
    sphere.position_x = 0.0F;
    sphere.position_y = 0.0F;
    sphere.position_z = 0.0F;
    layout.objects.push_back(std::move(sphere));
    layout.objects.push_back(object(2, u"Counter",
                                    {int_property(u"EQUALS VALUE", 2),
                                     int_property(u"STARTING VALUE", 0),
                                     text_property(u"LOGIC", u"Activate only once")}));
    layout.objects.push_back(object(3, u"Unit Spawner",
                                    {uint_property(u"COUNT", 2),
                                     text_property(u"RESOURCE", u"Skeletal Warrior"),
                                     text_property(u"GROUP", u"Monsters")}));
    layout.objects.push_back(object(4, u"Warper",
                                    {text_property(u"DUNGEON NAME", u"Main"),
                                     int_property(u"LEVEL DELTA", 1)}));
    layout.objects.push_back(object(5, u"Timer",
                                    {bool_property(u"ENABLED", false),
                                     float_property(u"TIME", 0.5F)}));
    auto box = object(6, u"Player Box Trigger",
                      {float_property(u"DIMENSIONSX", 4.0F),
                       float_property(u"DIMENSIONSY", 4.0F),
                       float_property(u"DIMENSIONSZ", 4.0F)});
    box.position_x = 20.0F;
    box.position_y = 0.0F;
    box.position_z = 0.0F;
    layout.objects.push_back(std::move(box));
    layout.objects.push_back(object(7, u"Logic Group"));

    torchlight::LayoutLogicGroup graph;
    graph.object_id = 7;
    graph.nodes.push_back(node(0, 1, {{1, u"Triggered First Time", u"Add"},
                                      {1, u"Triggered", u"Add"}}));
    graph.nodes.push_back(node(1, 2, {{2, u"Activated", u"Spawn Units"}}));
    graph.nodes.push_back(node(2, 3, {{3, u"All Monsters Dead", u"Activate Warper"}}));
    graph.nodes.push_back(node(3, 4));
    graph.nodes.push_back(node(4, 5, {{2, u"Activated", u"Spawn Units"}}));
    layout.logic_groups.push_back(std::move(graph));
    return layout;
}

void test_stateful_graph() {
    const auto layout = synthetic_layout();
    torchlight::LogicRuntime runtime(layout, 42);

    runtime.update_player_position({10.0F, 0.0F, 0.0F});
    require(runtime.take_events().empty(), "a player outside the trigger emitted an event");
    runtime.update_player_position({0.0F, 0.0F, 0.0F});
    const auto entered = runtime.take_events();
    require(entered.size() == 3, "first trigger entry produced the wrong event count");
    require(entered[0].output_name == u"Triggered First Time" &&
                entered[1].output_name == u"Triggered" &&
                entered[2].output_name == u"Activated",
            "first trigger entry used the wrong original event order");
    auto spawns = runtime.take_spawn_requests();
    require(spawns.size() == 1 && spawns[0].count == 2 &&
                spawns[0].resource == u"Skeletal Warrior",
            "trigger-counter-spawner chain produced the wrong spawn request");
    require(runtime.state(2) != nullptr && !runtime.state(2)->enabled,
            "activate-once counter remained enabled");
    runtime.mark_spawn_complete(3, 2);
    static_cast<void>(runtime.take_events());

    runtime.update_player_position({10.0F, 0.0F, 0.0F});
    const auto left = runtime.take_events();
    require(left.size() == 2 && left[0].output_name == u"Deactivated First Time" &&
                left[1].output_name == u"Deactivated",
            "trigger exit used the wrong event order");
    runtime.update_player_position({0.0F, 0.0F, 0.0F});
    const auto reentered = runtime.take_events();
    require(reentered.size() == 1 && reentered[0].output_name == u"Triggered",
            "re-entering a trigger repeated its first-time output");

    runtime.notify_monster_killed(3);
    require(runtime.take_warp_requests().empty(), "warper activated before all monsters died");
    runtime.notify_monster_killed(3);
    const auto warps = runtime.take_warp_requests();
    require(warps.size() == 1 && warps[0].dungeon_name == u"Main" &&
                warps[0].level_delta == 1,
            "all-monsters-dead did not activate the linked warper");

    runtime.invoke(5, u"Enable");
    static_cast<void>(runtime.take_events());
    runtime.update(0.25F);
    require(runtime.take_spawn_requests().empty(), "timer fired too early");
    runtime.update(0.25F);
    spawns = runtime.take_spawn_requests();
    require(spawns.size() == 1 && spawns[0].count == 2,
            "timer did not forward Activated into Spawn Units");

    runtime.update_player_position({20.0F, 0.0F, 0.0F});
    require(has_event(runtime.take_events(), 6, u"Triggered First Time"),
            "box trigger did not detect the player");
}

void test_spawner_controls() {
    const auto layout = synthetic_layout();

    torchlight::LogicRuntime hide_runtime(layout, 42);
    hide_runtime.mark_spawn_complete(3, 2);
    static_cast<void>(hide_runtime.take_events());
    hide_runtime.invoke(3, u"Hide And Disable Spawned Units");
    const auto hidden = hide_runtime.take_spawn_requests();
    require(hidden.size() == 1 &&
                hidden.front().action == torchlight::SpawnAction::hide_and_disable,
            "spawner hide input did not retain a world control request");
    require(hide_runtime.state(3) != nullptr &&
                hide_runtime.state(3)->enabled &&
                hide_runtime.state(3)->active_spawned_units == 2,
            "spawner hide input changed its owner state or unit count");
    require(hide_runtime.take_events().empty(),
            "spawner hide input fabricated a monster-death output");
    hide_runtime.invoke(3, u"Spawn Units");
    const auto respawned = hide_runtime.take_spawn_requests();
    require(respawned.size() == 1 &&
                respawned.front().action == torchlight::SpawnAction::spawn &&
                respawned.front().count == 2,
            "spawner owner could not spawn again after hiding its children");

    torchlight::LogicRuntime destroy_runtime(layout, 42);
    destroy_runtime.mark_spawn_complete(3, 2);
    static_cast<void>(destroy_runtime.take_events());
    destroy_runtime.invoke(3, u"Destroy Spawned Units");
    const auto destroyed = destroy_runtime.take_spawn_requests();
    require(destroyed.size() == 1 &&
                destroyed.front().action == torchlight::SpawnAction::destroy,
            "spawner destroy input did not retain a world control request");
    require(destroy_runtime.state(3) != nullptr &&
                destroy_runtime.state(3)->active_spawned_units == 2,
            "spawner destroy input cleared ownership before the world handled it");
    require(destroy_runtime.take_events().empty(),
            "spawner destroy input fabricated a monster-death output");
}

void test_original_timer_update_semantics() {
    torchlight::LayoutManifest layout;
    layout.objects.push_back(object(10, u"Timer",
                                    {float_property(u"TIME", 0.25F),
                                     bool_property(u"LOOPS FOREVER", true)}));
    layout.objects.push_back(object(11, u"Timer",
                                    {float_property(u"TIME", 0.0F),
                                     bool_property(u"LOOPS FOREVER", true)}));
    layout.objects.push_back(object(12, u"Timer",
                                    {float_property(u"TIME", 0.5F),
                                     int_property(u"LOOP COUNT", 3)}));

    torchlight::LogicRuntime runtime(layout, 42);
    runtime.update(1.0F);
    const auto first_update = runtime.take_events();
    require(first_update.size() == 3,
            "a timer update emitted catch-up events or skipped another timer");
    require(runtime.state(10)->timer_remaining == 0.25F,
            "timer carried overshoot instead of resetting its full period");
    require(runtime.state(11)->timer_remaining == 0.0F,
            "zero-period timer did not return after one activation");

    runtime.update(0.0F);
    const auto zero_update = runtime.take_events();
    require(zero_update.size() == 1 && zero_update.front().object_id == 11,
            "zero-period timer emitted more than once per update");

    runtime.update(0.5F);
    static_cast<void>(runtime.take_events());
    runtime.update(0.5F);
    static_cast<void>(runtime.take_events());
    require(runtime.state(12)->timer_loops_remaining == 0,
            "finite timer did not exhaust its original repeat count");
    runtime.invoke(12, u"Enable");
    require(runtime.state(12)->timer_loops_remaining == 1,
            "enabling an exhausted timer restored more than one repeat");
    require(runtime.state(12)->timer_remaining == 0.5F,
            "enabling a timer did not reset its period");
    runtime.update(0.2F);
    runtime.invoke(12, u"Disable");
    require(runtime.state(12)->timer_remaining == 0.5F,
            "disabling a timer did not reset its period before Disabled");

    torchlight::LayoutManifest callback_layout;
    callback_layout.objects.push_back(object(13, u"Timer",
                                             {float_property(u"TIME", 0.1F),
                                              int_property(u"LOOP COUNT", 3)}));
    callback_layout.objects.push_back(object(14, u"Logic Group"));
    callback_layout.objects.push_back(object(15, u"Timer",
                                             {float_property(u"TIME", 0.1F),
                                              int_property(u"LOOP COUNT", 3)}));
    torchlight::LayoutLogicGroup callback_graph;
    callback_graph.object_id = 14;
    callback_graph.nodes.push_back(node(0, 13, {{0, u"Activated", u"Reset"}}));
    callback_graph.nodes.push_back(node(1, 15, {{1, u"Enabled", u"Reset"}}));
    callback_layout.logic_groups.push_back(std::move(callback_graph));

    torchlight::LogicRuntime callback_runtime(callback_layout, 42);
    callback_runtime.update(0.1F);
    require(callback_runtime.state(13)->timer_loops_remaining == 2,
            "timer update cached its repeat count across Activated callback");
    callback_runtime.update(0.1F);
    callback_runtime.update(0.1F);
    require(callback_runtime.state(13)->timer_loops_remaining == 2,
            "Activated callback no longer reset the timer before decrement");

    callback_runtime.update(0.1F);
    callback_runtime.update(0.1F);
    callback_runtime.update(0.1F);
    require(callback_runtime.state(15)->timer_loops_remaining == 0,
            "callback test timer did not reach its exhausted state");
    callback_runtime.invoke(15, u"Enable");
    require(callback_runtime.state(15)->timer_loops_remaining == 3,
            "Enable cached an exhausted count before its synchronous callback");
}

torchlight::LayoutManifest nested_dispatch_layout(bool reverse_root_links) {
    torchlight::LayoutManifest layout;
    layout.objects.push_back(object(20, u"Logic Group"));
    layout.objects.push_back(object(21, u"Timer", {bool_property(u"ENABLED", false)}));
    layout.objects.push_back(object(22, u"Timer", {bool_property(u"ENABLED", false)}));

    torchlight::LayoutLogicGroup graph;
    graph.object_id = 20;
    std::vector<torchlight::LayoutLogicLink> root_links{
        {1, u"Activated", u"Enable"}, {2, u"Activated", u"Enable"}};
    if (reverse_root_links) {
        std::reverse(root_links.begin(), root_links.end());
    }
    graph.nodes.push_back(node(0, 20, std::move(root_links)));
    graph.nodes.push_back(node(1, 21, {{2, u"Enabled", u"Disable"}}));
    graph.nodes.push_back(node(2, 22));
    layout.logic_groups.push_back(std::move(graph));
    return layout;
}

void test_nested_dispatch_order() {
    const auto layout = nested_dispatch_layout(false);
    torchlight::LogicRuntime runtime(layout, 42);
    runtime.emit(20, u"Activated");
    const auto invocations = runtime.take_invocations();
    require(invocations.size() == 3 && invocations[0].target_object_id == 21 &&
                invocations[0].input_name == u"Enable" &&
                invocations[1].target_object_id == 22 &&
                invocations[1].input_name == u"Disable" &&
                invocations[2].target_object_id == 22 &&
                invocations[2].input_name == u"Enable",
            "nested logic output did not finish before the next sibling link");
    require(runtime.state(22)->enabled,
            "depth-first dispatch produced the wrong final target state");

    const auto reversed_layout = nested_dispatch_layout(true);
    torchlight::LogicRuntime reversed(reversed_layout, 42);
    reversed.emit(20, u"Activated");
    require(!reversed.state(22)->enabled,
            "reversing sibling links did not preserve their original order");
}

void test_dispatch_cycle_limit() {
    torchlight::LayoutManifest layout;
    layout.objects.push_back(object(30, u"Logic Group"));
    layout.objects.push_back(object(31, u"Logic Group"));
    torchlight::LayoutLogicGroup graph;
    graph.object_id = 30;
    graph.nodes.push_back(node(0, 30, {{1, u"Start", u"Start"}}));
    graph.nodes.push_back(node(1, 31, {{0, u"Start", u"Start"}}));
    layout.logic_groups.push_back(std::move(graph));

    torchlight::LogicRuntime runtime(layout, 42);
    bool rejected = false;
    try {
        runtime.invoke(30, u"Start");
    } catch (const std::runtime_error&) {
        rejected = true;
    }
    require(rejected, "cyclic logic graph bypassed the root dispatch limit");
}

void test_original_logic_layout(const std::string& pak_path) {
    const torchlight::PakArchive archive(pak_path);
    const torchlight::LevelSceneLoader loader(archive);
    const auto layout = loader.load_layout("media/layouts/test/LOGICTEST.LAYOUT.adm");
    require(layout.objects.size() == 159, "logic test has the wrong object count");
    require(layout.logic_groups.size() == 1, "logic test has the wrong graph count");
    require(layout.logic_groups[0].nodes.size() == 28,
            "logic test has the wrong node count");
    std::size_t link_count = 0;
    for (const auto& item : layout.logic_groups[0].nodes) {
        link_count += item.links.size();
    }
    require(link_count == 26, "logic test has the wrong link count");

    torchlight::LogicRuntime runtime(layout, 42);
    constexpr std::int64_t lever = 4789864698297979358LL;
    constexpr std::int64_t spawner = 4789864784197325278LL;
    runtime.trigger(lever);
    const auto requests = runtime.take_spawn_requests();
    require(requests.size() == 1 && requests[0].spawner_id == spawner &&
                requests[0].resource == u"Skeletal Warrior" && requests[0].count == 1,
            "original lever-to-spawner graph was not executed");
    runtime.mark_spawn_complete(spawner, 1);
    runtime.notify_monster_killed(spawner);
    const auto invocations = runtime.take_invocations();
    require(std::any_of(invocations.begin(), invocations.end(), [](const auto& invocation) {
                return invocation.source_object_id == spawner && invocation.input_name == u"Play";
            }),
            "original all-monsters-dead link did not reach its timeline");

    const auto shipped_with_dangling_links = loader.load_layout(
        "media/layouts/SunkenTemple/1X1SINGLE_ROOM_HUB/1X1_HUB_LM_A.LAYOUT.adm");
    const torchlight::LogicRuntime tolerant_runtime(shipped_with_dangling_links, 42);
    require(tolerant_runtime.dangling_link_count() == 2,
            "shipped dangling editor links were not isolated");
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: logic_runtime_test --original /path/to/pak.zip\n";
            return 2;
        }
        test_stateful_graph();
        test_spawner_controls();
        test_original_timer_update_semantics();
        test_nested_dispatch_order();
        test_dispatch_cycle_limit();
        test_original_logic_layout(argv[2]);
        std::cout << "PASS: parsed and executed Torchlight layout logic graphs\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
