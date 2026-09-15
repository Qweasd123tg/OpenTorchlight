#include "torchlight/frontend.hpp"
#include "torchlight/interaction.hpp"
#include "torchlight/ogre_mesh.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
std::uint32_t seed = 491;
} // namespace
// External original resources are read-only; save_directory is a fresh test directory.
// This tests the new port's resource-backed persistence, NOT original save parity.
int main(int argc, char **argv) {
    try {
        if (argc != 4)
            throw std::runtime_error(
                "usage: frontend_resource_test original_pak temporary_save_directory write|read");
        const bool writing = std::string(argv[3]) == "write";
        if (!writing && std::string(argv[3]) != "read")
            throw std::runtime_error("invalid test mode");
        PakArchive archive(argv[1]);
        SaveStore store(argv[2]);
        UiResources ui(archive);
        const auto identity = checkpoint_resource_identity(archive);
        const auto master = parse_adm(archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM"));
        MasterResourceIndex resources(master);
        UnitDefinitionLoader definitions(archive);
        SpawnClassCatalog spawn_classes(archive);
        UnitTypeHierarchy hierarchy(archive);
        UnitTypeResourceIndex types(archive, hierarchy, resources, definitions);
        const auto players = load_playable_players(archive, resources, definitions);
        require(players.size() == 3,
                "original playable class count differs from established resource boundary");
        std::vector<FrontendClass> classes;
        for (const auto &p : players)
            classes.push_back({p.guid, std::string(p.name.begin(), p.name.end())});
        Frontend frontend(ui, classes);
        const auto main = frontend.frame(1024, 768);
        require(main.original_layout, "original main menu was not parsed");
        for (const auto *path : {"media/UI/mainmenuframe.layout", "media/UI/charactercreate.layout",
                                 "media/UI/characterload.layout"}) {
            const auto *layout = ui.layout(path);
            require(layout && !layout->resolve(1024, 768).empty(), "original UI layout missing");
        }
        const auto &load_widgets = ui.layout("media/UI/characterload.layout")->widgets();
        const auto player_name = std::find_if(load_widgets.begin(), load_widgets.end(),
                                              [](const auto &w) { return w.name == "Player1Name"; });
        require(player_name != load_widgets.end() &&
                    player_name->property("AlwaysOnTop").empty(),
                "lowercase malformed original Property was not ignored");
        const auto callback_present = [&](const char *path, const std::string &command) {
            const auto widgets = ui.layout(path)->resolve(1024, 768);
            return std::any_of(widgets.begin(), widgets.end(),
                               [&](const auto &w) { return w.callback == command; });
        };
        require(callback_present("media/UI/mainmenuframe.layout", "guiNewGameMenu"),
                "original New Game binding changed");
        require(callback_present("media/UI/charactercreate.layout", "guiNewGame"),
                "original Create binding changed");
        LevelSceneLoader loader(archive);
        LevelsetCatalog levelsets(archive);
        auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        static_cast<void>(expand_layout_links(loader, town.layout));
        const auto nav =
            NavigationGrid::build(build_fixed_level_collision(archive, levelsets, town));
        auto position = layout_player_start(town.layout);
        const auto cell = nav.nearest_walkable(position);
        require(cell.has_value(), "Town entry has no walkable cell");
        position = nav.cell_center((*cell)[0], (*cell)[1]);
        require(checkpoint_position_walkable(nav, position, 0), "Town save position invalid");
        for (std::size_t n = 0; n < players.size(); ++n) {
            LogicRuntime logic(town.layout, seed);
            RuntimeEntityWorld world(town.layout, resources, definitions, spawn_classes, types,
                                     seed, 1);
            EnemyController enemies(seed);
            const auto slot = "original-test-" + std::to_string(n);
            const auto &proto = players[n];
            require(!parse_ogre_mesh(archive.read_normalized(proto.mesh_path)).submeshes.empty(),
                    "selected original class model empty");
            if (writing) {
                PlayerSession session(proto, seed, &hierarchy);
                session.give_gold(7);
                CampaignCheckpoint c;
                c.slot = slot;
                c.seed = seed;
                c.class_guid = proto.guid;
                c.character_name = "Resource Hero " + std::to_string(n);
                c.resource_identity = identity;
                c.player = CheckpointAccess::capture(session);
                FloorCheckpoint f;
                f.address = {u"Town", 0};
                f.layout_identity = checkpoint_layout_identity(town.layout);
                f.player_position = position;
                f.recovery_anchor = position;
                f.world = CheckpointAccess::capture(world);
                f.logic = CheckpointAccess::capture(logic);
                f.enemies = CheckpointAccess::capture(enemies);
                remember_floor(c, std::move(f));
                c.revision = store.write(c);
            } else {
                const auto c = store.read(slot, identity);
                require(c.class_guid == proto.guid, "saved original class mismatch");
                auto session = CheckpointAccess::restore_player(proto, c.player, seed, &hierarchy);
                const auto *floor = find_floor(c, {u"Town", 0});
                require(floor, "saved Town absent");
                CheckpointAccess::restore_floor(*floor, world, logic, enemies);
                require(session.gold() == proto.starting_gold + 7 &&
                            session.health().health() == c.player.health &&
                            session.health().mana() == c.player.mana,
                        "original-resource checkpoint vitals mismatch");
                require(world.entities().size() == floor->world.entities.size() &&
                            CheckpointAccess::capture(session).inventory.slots ==
                                c.player.inventory.slots,
                        "original-resource entities/slots changed");
            }
        }
        std::cout << "Original-resource frontend/checkpoint " << (writing ? "write" : "read")
                  << " passed for three classes; not original SVB or Wayland parity\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "original frontend resources: " << e.what() << '\n';
        return 1;
    }
}
