#include "torchlight/adm_document.hpp"
#include "torchlight/entity_world.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"
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
            std::cerr << "usage: entity_world_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        const torchlight::SpawnClassCatalog spawn_classes(archive);
        torchlight::UnitDefinitionLoader definitions(archive);
        const torchlight::UnitTypeHierarchy unit_type_hierarchy(archive);
        const torchlight::UnitTypeResourceIndex unit_types(
            archive, unit_type_hierarchy, resources, definitions);
        const torchlight::LevelSceneLoader loader(archive);
        const auto layout = loader.load_layout(
            "media/layouts/test/LOGICTEST.LAYOUT.adm");

        constexpr std::int64_t lever = 4789864698297979358LL;
        constexpr std::int64_t spawner = 4789864784197325278LL;
        torchlight::LogicRuntime logic(layout, 42);
        torchlight::RuntimeEntityWorld world(
            layout, resources, definitions, spawn_classes, unit_types, 42);
        logic.trigger(lever);
        const auto requests = logic.take_spawn_requests();
        require(requests.size() == 1, "original lever did not request one spawn");
        const auto stats = world.consume_spawn_requests(requests, logic);
        require(stats.requests == 1 && stats.entities_created == 1 &&
                    stats.resolved_unit_types == 0 &&
                    stats.unresolved_unit_types == 0 && stats.missing_resources == 0,
                "original spawn request did not create one resolved entity");
        require(world.entities().size() == 1 &&
                    world.entities()[0].name == u"Skeletal Warrior" &&
                    world.entities()[0].kind == torchlight::MasterResourceKind::monster &&
                    world.entities()[0].spawner_id == spawner,
                "spawned entity has the wrong original resource identity");
        const auto transforms = torchlight::resolve_layout_world_transforms(layout);
        const auto spawner_object = std::find_if(
            layout.objects.begin(), layout.objects.end(), [](const auto& object) {
                return object.id == spawner;
            });
        require(spawner_object != layout.objects.end(), "logic test has no requested spawner");
        const auto spawner_index = static_cast<std::size_t>(
            spawner_object - layout.objects.begin());
        for (std::size_t axis = 0; axis < 3; ++axis) {
            require(std::fabs(world.entities()[0].position[axis] -
                              transforms[spawner_index].position[axis]) < 0.001F,
                    "spawned entity is not at its spawner");
        }
        require(has_event(logic.take_events(), spawner, u"All Units Spawned"),
                "entity creation did not complete the spawner");
        torchlight::FixedSceneGeometry runtime_geometry;
        const auto runtime_instance = torchlight::append_runtime_entity_geometry(
            archive, resources, definitions, world.entities()[0], runtime_geometry);
        require(runtime_instance == 0 && runtime_geometry.instances.size() == 1 &&
                    runtime_geometry.instances[0].runtime_entity_id == world.entities()[0].id &&
                    runtime_geometry.meshes.size() == 1,
                "spawned monster did not resolve to visible runtime geometry");
        auto second_entity = world.entities()[0];
        second_entity.id = 2;
        second_entity.position[0] += 2.0F;
        const auto second_instance = torchlight::append_runtime_entity_geometry(
            archive, resources, definitions, second_entity, runtime_geometry);
        require(second_instance == 1 && runtime_geometry.instances.size() == 2 &&
                    runtime_geometry.meshes.size() == 1,
                "repeated runtime monster did not reuse its original mesh");
        require(world.kill(world.entities()[0].id, logic),
                "live monster could not be killed");
        require(!world.kill(world.entities()[0].id, logic),
                "dead monster was killed twice");
        const auto death_events = logic.take_events();
        require(has_event(death_events, spawner, u"Monster Killed") &&
                    has_event(death_events, spawner, u"All Monsters Dead"),
                "monster death did not notify its source spawner");
        const auto invocations = logic.take_invocations();
        require(std::any_of(invocations.begin(), invocations.end(),
                            [spawner](const auto& invocation) {
                                return invocation.source_object_id == spawner &&
                                       invocation.input_name == u"Play";
                            }),
                "all-monsters-dead did not continue the original timeline");

        torchlight::LogicRuntime class_logic(layout, 7);
        torchlight::RuntimeEntityWorld class_world(
            layout, resources, definitions, spawn_classes, unit_types, 7);
        const torchlight::SpawnRequest class_request{
            spawner, u"SKELETONS", u"Spawn Class", 2};
        const auto class_stats =
            class_world.consume_spawn_requests({class_request, class_request}, class_logic);
        require(class_stats.entities_created == 4 &&
                    class_stats.resolved_unit_types == 0 &&
                    class_stats.unresolved_unit_types == 0 &&
                    class_stats.missing_resources == 0,
                "SKELETONS request did not create four concrete monsters");
        require(std::all_of(class_world.entities().begin(), class_world.entities().end(),
                            [](const auto& entity) {
                                return entity.kind == torchlight::MasterResourceKind::monster;
                            }),
                "SKELETONS request created a non-monster entity");
        static_cast<void>(class_logic.take_events());
        for (std::size_t index = 0; index + 1U < class_world.entities().size(); ++index) {
            require(class_world.kill(class_world.entities()[index].id, class_logic),
                    "monster from repeated spawn request could not be killed");
        }
        require(!has_event(class_logic.take_events(), spawner, u"All Monsters Dead"),
                "repeated spawn requests overwrote the active monster count");
        require(class_world.kill(class_world.entities().back().id, class_logic),
                "last monster from repeated spawn request could not be killed");
        require(has_event(class_logic.take_events(), spawner, u"All Monsters Dead"),
                "last monster did not complete repeated spawn requests");

        torchlight::LogicRuntime item_logic(layout, 11);
        torchlight::RuntimeEntityWorld item_world(
            layout, resources, definitions, spawn_classes, unit_types, 11, 1);
        const torchlight::SpawnRequest item_request{
            spawner, u"FISH_SPAWN", u"Spawn Class", 1};
        const auto item_stats =
            item_world.consume_spawn_requests({item_request}, item_logic);
        require(item_stats.entities_created == 1 &&
                    item_stats.resolved_unit_types == 1 &&
                    item_stats.unresolved_unit_types == 0 &&
                    item_world.entities().size() == 1 &&
                    item_world.entities()[0].kind ==
                        torchlight::MasterResourceKind::item,
                "FISH UNITTYPE did not create one concrete item");
        static_cast<void>(item_logic.take_events());
        require(item_world.pick_up(item_world.entities()[0].id, item_logic),
                "UNITTYPE item could not be picked up");
        require(has_event(item_logic.take_events(), spawner, u"Item Picked Up"),
                "UNITTYPE item pickup did not notify its source spawner");

        std::cout << "PASS: resolved original spawns into runtime entities and routed death\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
