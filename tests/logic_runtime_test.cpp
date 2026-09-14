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
    runtime.notify_monster_killed(spawner);
    const auto invocations = runtime.take_invocations();
    require(std::any_of(invocations.begin(), invocations.end(), [](const auto& invocation) {
                return invocation.source_object_id == spawner && invocation.input_name == u"Play";
            }),
            "original all-monsters-dead link did not reach its timeline");
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: logic_runtime_test --original /path/to/pak.zip\n";
            return 2;
        }
        test_stateful_graph();
        test_original_logic_layout(argv[2]);
        std::cout << "PASS: parsed and executed Torchlight layout logic graphs\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
