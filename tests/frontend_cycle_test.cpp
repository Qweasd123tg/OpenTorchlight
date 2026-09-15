#include "ai_cooldown_fixture.hpp"
#include "torchlight/frontend.hpp"
#include "torchlight/interaction.hpp"
#include "torchlight/ogre_mesh.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {
std::size_t checks = 0;
void require(bool ok, const char *what) {
    ++checks;
    if (!ok)
        throw std::runtime_error(what);
}
template <class F> void rejects(F f, const char *what) {
    bool rejected = false;
    try {
        f();
    } catch (const std::exception &) {
        rejected = true;
    }
    require(rejected, what);
}
AdmProperty text(std::u16string name, std::u16string value) {
    return {0, std::move(name), AdmValueType::string, std::move(value)};
}
AdmProperty integer(std::u16string name, std::int32_t value) {
    return {0, std::move(name), AdmValueType::integer, value};
}
LayoutManifest floor_layout(bool town) {
    auto layout = test_fixture::layout(town ? u"INNATE" : nullptr);
    if (town) {
        auto &npc = layout.objects.back();
        npc.name = u"Service inspection fixture";
        npc.position_x = 4.5F;
        npc.position_y = 0;
        npc.position_z = 3.5F;
        npc.properties.push_back({0, u"TARGETABLE", AdmValueType::boolean, false});
    }
    LayoutObject trigger;
    trigger.id = 100;
    trigger.descriptor = u"Unit Trigger";
    trigger.name = town ? u"Dungeon entrance" : u"Return to Town";
    trigger.position_x = 14.5F;
    trigger.position_y = 0;
    trigger.position_z = 4.5F;
    layout.objects.push_back(trigger);
    LayoutObject warper;
    warper.id = 101;
    warper.descriptor = u"Warper";
    warper.position_x = 22.5F;
    warper.position_y = 0;
    warper.position_z = 22.5F;
    warper.properties = {text(u"DUNGEON NAME", town ? u"Main" : u"Town"),
                         integer(u"LEVEL DELTA", town ? 1 : 0)};
    layout.objects.push_back(warper);
    LayoutObject group;
    group.id = 102;
    group.descriptor = u"Logic Group";
    layout.objects.push_back(group);
    layout.logic_groups.push_back(
        {102, {{0, 100, 0, 0, {{1, u"Triggered", u"Activate Warper"}}}, {1, 101, 0, 0, {}}}});
    LayoutObject timer;
    timer.id = 200;
    timer.descriptor = u"Timer";
    timer.properties = {{0, u"TIME", AdmValueType::floating, 2.0F},
                        {0, u"LOOPS FOREVER", AdmValueType::boolean, true}};
    layout.objects.push_back(timer);
    LayoutObject counter;
    counter.id = 201;
    counter.descriptor = u"Counter";
    counter.properties = {integer(u"STARTING VALUE", 0), integer(u"EQUALS VALUE", 100)};
    layout.objects.push_back(counter);
    return layout;
}
// Author-created Town/Main-shaped levels, not resources extracted from Torchlight.
struct Floor {
    PakArchive archive;
    AdmDocument document;
    MasterResourceIndex resources;
    UnitDefinitionLoader definitions;
    SpawnClassCatalog spawn_classes;
    UnitTypeHierarchy hierarchy;
    UnitTypeResourceIndex types;
    LayoutManifest layout;
    LogicRuntime logic;
    RuntimeEntityWorld world;
    EnemyController enemies;
    explicit Floor(const char *path, bool town)
        : archive(path), document(parse_adm(archive.read_normalized("media/master.adm"))),
          resources(document), definitions(archive), spawn_classes(archive), hierarchy(archive),
          types(archive, hierarchy, resources, definitions), layout(floor_layout(town)),
          logic(layout, 59), world(layout, resources, definitions, spawn_classes, types, 59, 1),
          enemies(67) {
    }
    std::uint64_t spawn(const char16_t *name, const char16_t *group) {
        const auto result = world.consume_spawn_requests({{42, name, group, 1}}, logic);
        require(result.entities_created == 1, "cycle fixture spawn failed");
        return world.entities().back().id;
    }
};
NavigationGrid navigation() {
    CollisionScene scene;
    const auto triangle = [&](std::array<float, 3> a, std::array<float, 3> b,
                              std::array<float, 3> c) { scene.triangles.push_back({{a, b, c}}); };
    triangle({0, 0, 0}, {24, 0, 24}, {24, 0, 0});
    triangle({0, 0, 0}, {0, 0, 24}, {24, 0, 24});
    triangle({10.5F, 0, 3}, {10.5F, 4, 3}, {10.5F, 4, 18});
    triangle({10.5F, 0, 3}, {10.5F, 4, 18}, {10.5F, 0, 18});
    return NavigationGrid::build(scene, 1, .45F);
}
void click(Frontend &ui, const std::string &id) {
    const auto frame = ui.frame(1024, 768);
    const auto it = std::find_if(frame.buttons.begin(), frame.buttons.end(),
                                 [&](const auto &b) { return b.id == id; });
    require(it != frame.buttons.end() && it->enabled, "cycle menu button not available");
    ui.click(it->rect.x + it->rect.width * .5F, it->rect.y + it->rect.height * .5F);
}
FloorCheckpoint snapshot(Floor &f, DungeonAddress address, const ActorMotion &motion) {
    FloorCheckpoint result;
    result.address = std::move(address);
    result.layout_identity = checkpoint_layout_identity(f.layout);
    result.player_position = motion.position();
    result.player_angle = 67;
    result.recovery_anchor = {2.5F, 0, 2.5F};
    result.recovery_angle = 19;
    result.world = CheckpointAccess::capture(f.world);
    result.logic = CheckpointAccess::capture(f.logic);
    result.enemies = CheckpointAccess::capture(f.enemies);
    return result;
}
PlayerPrototype chosen(Floor &f, std::int64_t guid) {
    const auto classes = load_playable_players(f.archive, f.resources, f.definitions);
    const auto it =
        std::find_if(classes.begin(), classes.end(), [&](const auto &p) { return p.guid == guid; });
    require(it != classes.end(), "saved selected class absent");
    return *it;
}
void walk(ActorMotion &actor, const NavigationGrid &nav, const std::array<float, 3> &target) {
    const auto route = nav.find_path(actor.position(), target);
    require(!route.empty(), "town walk has no route around wall");
    for (const auto &waypoint : route) {
        actor.set_destination(waypoint);
        for (int n = 0; actor.moving() && n < 500; ++n) {
            actor.advance(.02F);
            require(checkpoint_position_walkable(nav, actor.position(), 0),
                    "actor crossed blocked navigation cell");
        }
        require(!actor.moving(), "actor failed to reach waypoint");
    }
    require(std::hypot(actor.position()[0] - target[0], actor.position()[2] - target[2]) < 1,
            "town actor did not reach target");
    require(!checkpoint_position_walkable(nav, {10.5F, 0, 10}, 0),
            "wall accepted as load position");
    require(!checkpoint_position_walkable(nav, {2.5F, 20, 2.5F}, 0),
            "invalid saved height accepted");
}
void interaction_contracts(Floor &town, PlayerSession &player) {
    InteractionDispatcher dispatcher(town.layout, town.world, town.logic);
    require(!dispatcher.select({22.5F, 0, 22.5F}, .1F), "direct Warper click bypasses graph");
    auto npc = dispatcher.select({4.5F, 0, 3.5F}, .1F);
    require(npc && npc->kind == InteractionKind::character,
            "NPC cannot be selected for inspection");
    require(dispatcher.dispatch(*npc, {}, true, 1) == InteractionResult::approaching,
            "remote NPC interacted without approach");
    const auto gold = player.gold();
    const auto count = player.inventory().items().size();
    require(dispatcher.dispatch(*npc, npc->position, true, 1) ==
                InteractionResult::unsupported_service,
            "unimplemented merchant presented as working");
    require(player.gold() == gold && player.inventory().items().size() == count,
            "unsupported service changed inventory/wallet");
    require(dispatcher.dispatch(*npc, npc->position, true, 1) == InteractionResult::stale,
            "consumed interaction repeated");
    auto trigger = dispatcher.select({14.5F, 0, 4.5F}, 1);
    require(trigger.has_value(), "trigger selection failed");
    auto forged = *trigger;
    forged.object_id = 101;
    require(!dispatcher.resolve(forged), "interaction token can be retargeted to Warper");
    town.logic.invoke(100, u"Disable");
    require(dispatcher.dispatch(*trigger, trigger->position, true, 1) ==
                InteractionResult::unavailable,
            "object disabled during approach still activated");
    town.logic.invoke(100, u"Enable");
    trigger = dispatcher.select({14.5F, 0, 4.5F}, 1);
    require(dispatcher.dispatch(*trigger, trigger->position, false, 1) ==
                InteractionResult::player_dead,
            "dead player activated trigger");
    trigger = dispatcher.select({14.5F, 0, 4.5F}, 1);
    InteractionDispatcher new_floor(town.layout, town.world, town.logic);
    auto current = new_floor.select(trigger->position, 1);
    require(current && new_floor.dispatch(*trigger, trigger->position, true, 1) ==
                           InteractionResult::stale,
            "old generation interaction crossed floor/controller");
    new_floor.cancel();
    dispatcher.cancel();
    require(town.logic.take_warp_requests().empty(), "rejected interactions produced warp");
}
void write_phase(const char *pak, SaveStore &store) {
    Floor town(pak, true);
    const auto classes = load_playable_players(town.archive, town.resources, town.definitions);
    require(classes.size() >= 2, "fixture must exercise a non-first class");
    std::vector<FrontendClass> choices;
    for (const auto &p : classes)
        choices.push_back({p.guid, std::string(p.name.begin(), p.name.end())});
    UiResources resources(town.archive);
    Frontend frontend(resources, choices);
    click(frontend, "new");
    click(frontend, "class-1");
    for (int n = 0; n < 4; ++n)
        frontend.key(FrontendKey::backspace);
    for (const auto c : std::string("Town Hero"))
        frontend.text(c);
    click(frontend, "create");
    const auto request = frontend.take_request();
    require(request && request->command == FrontendCommand::create &&
                request->class_guid == classes[1].guid,
            "New Game discarded selected class");
    auto proto = chosen(town, request->class_guid);
    require(!parse_ogre_mesh(town.archive.read_normalized(proto.mesh_path)).submeshes.empty(),
            "selected authored hero model not loadable");
    PlayerSession session(proto, 123, &town.hierarchy);
    ActorMotion actor({2.5F, 0, 2.5F}, 5);
    const auto nav = navigation();
    walk(actor, nav, {14.5F, 0, 4.5F});
    for (const auto *name : {u"SWORD", u"MANA_CHEST"}) {
        const auto id = town.spawn(name, u"Items");
        const auto item = session.pick_up(town.world, id, town.logic);
        require(item && session.equip(item) == InventoryChange::changed, "town item cycle failed");
    }
    session.give_gold(77);
    TorchlightRandom random(41);
    static_cast<void>(session.health().apply_damage(7, 7, DamageType::physical, random));
    require(session.health().spend_mana(9), "cycle could not spend mana");
    town.logic.invoke(201, u"Add");
    town.logic.update(.75F);
    interaction_contracts(town, session);
    CampaignCheckpoint campaign;
    campaign.slot = "cycle-hero";
    campaign.seed = 123;
    campaign.character_name = request->name;
    campaign.class_guid = proto.guid;
    campaign.resource_identity = checkpoint_resource_identity(town.archive);
    campaign.player = CheckpointAccess::capture(session);
    remember_floor(campaign, snapshot(town, campaign.current, actor));
    frontend.entered_game();
    frontend.pause();
    click(frontend, "save-exit");
    const auto save = frontend.take_request();
    require(save && save->command == FrontendCommand::save_and_quit, "pause save/quit unavailable");
    campaign.revision = store.write(campaign);
    frontend.saved(save->command);
    require(frontend.page() == FrontendPage::quit, "did not quit after durable save");
    require(campaign.revision == 1 &&
                checkpoint_position_walkable(nav, campaign.floors.front().player_position, 0),
            "first save boundary invalid");
}
void load_and_travel(const char *pak, SaveStore &store) {
    Floor town(pak, true);
    const auto identity = checkpoint_resource_identity(town.archive);
    UiResources resources(town.archive);
    Frontend frontend(resources, {{1, "Placeholder"}});
    frontend.set_saves(store.list(identity));
    click(frontend, "loads");
    click(frontend, "load");
    const auto request = frontend.take_request();
    require(request && request->slot == "cycle-hero", "Load menu did not select save");
    auto campaign = store.read(request->slot, identity);
    require(campaign.character_name == "Town Hero" && campaign.seed == 123 &&
                campaign.revision == 1,
            "metadata lost across processes");
    const auto proto = chosen(town, campaign.class_guid);
    require(proto.guid ==
                load_playable_players(town.archive, town.resources, town.definitions)[1].guid,
            "class changed after new process");
    auto session =
        CheckpointAccess::restore_player(proto, campaign.player, campaign.seed, &town.hierarchy);
    auto transitions = CheckpointAccess::restore_transitions(campaign);
    const auto saved = *find_floor(campaign, {u"Town", 0});
    CheckpointAccess::restore_floor(saved, town.world, town.logic, town.enemies);
    require(CheckpointAccess::capture(session).inventory.slots == campaign.player.inventory.slots &&
                session.health().health() == campaign.player.health &&
                session.health().mana() == campaign.player.mana &&
                session.gold() == campaign.player.gold,
            "save/load changed selected item or vitals");
    require(town.logic.state(201)->counter == 1 &&
                town.world.entities().size() == saved.world.entities.size(),
            "Town world or logic was regenerated instead of restored");
    ActorMotion actor(saved.player_position, 5);
    require(checkpoint_position_walkable(navigation(), actor.position(), 0),
            "loaded position is invalid");
    InteractionDispatcher interactions(town.layout, town.world, town.logic);
    auto selection = interactions.select({14.5F, 0, 4.5F}, 1);
    require(selection && interactions.dispatch(*selection, actor.position(), true, 1) ==
                             InteractionResult::triggered,
            "Town entrance did not trigger graph");
    auto warps = town.logic.take_warp_requests();
    require(warps.size() == 1, "Town entrance produced wrong number of warps");
    const auto entry = transitions.resolve_entry(warps.front());
    require(same_dungeon_address(entry.destination, {u"Main", 1}), "wrong dungeon entry");
    remember_floor(campaign, snapshot(town, transitions.current(), actor));
    transitions.commit(entry.destination);
    session.enter_level();
    const auto before = CheckpointAccess::capture(session);
    Floor main(pak, false);
    const auto corpse = main.spawn(u"INNATE", u"Monsters");
    require(main.world.kill(corpse, main.logic), "Main kill failed");
    static_cast<void>(main.world.resolve_death_loot(main.logic));
    const auto loot = main.spawn(u"SWORD", u"Items");
    const auto main_count = main.world.entities().size();
    TorchlightRandom random(3);
    static_cast<void>(
        session.health().apply_damage(1000000, 1000000, DamageType::physical, random));
    const auto recovery = session.recover_at_entry(main.enemies, actor, {2.5F, 0, 2.5F});
    require(recovery.status == RecoveryStatus::recovered &&
                session.gold() == before.gold - before.gold / 10,
            "restart after disk load lost wallet policy");
    require(!main.world.find(corpse)->alive && main.world.find(loot)->alive &&
                main.world.entities().size() == main_count,
            "restart rebuilt corpse/ground loot");
    require(session.inventory().items().size() == before.inventory.items.size() &&
                CheckpointAccess::capture(session).inventory.slots == before.inventory.slots,
            "restart after load lost inventory instances");
    remember_floor(campaign, snapshot(main, transitions.current(), actor));
    InteractionDispatcher exit(main.layout, main.world, main.logic);
    selection = exit.select({14.5F, 0, 4.5F}, 1);
    walk(actor, navigation(), selection->position);
    require(exit.dispatch(*selection, actor.position(), true, 1) == InteractionResult::triggered,
            "Main return trigger failed");
    warps = main.logic.take_warp_requests();
    require(warps.size() == 1, "Main return produced duplicate warp");
    transitions.commit(transitions.resolve(warps.front()));
    require(same_dungeon_address(transitions.current(), {u"Town", 0}), "return did not enter Town");
    remember_floor(campaign, snapshot(main, {u"Main", 1}, actor));
    Floor again(pak, true);
    const auto cached = *find_floor(campaign, {u"Town", 0});
    CheckpointAccess::restore_floor(cached, again.world, again.logic, again.enemies);
    require(again.world.entities().size() == cached.world.entities.size() &&
                again.logic.state(201)->counter == 1,
            "return duplicated Town loot or reset counter");
    for (std::size_t n = 0; n < cached.world.entities.size(); ++n)
        require(again.world.entities()[n].alive == cached.world.entities[n].alive &&
                    again.world.entities()[n].health == cached.world.entities[n].health,
                "return changed saved entity state");
    // Restore rejection must not mutate the new world or logic halfway through.
    auto bad = cached;
    bad.layout_identity ^= 1;
    const auto before_world = CheckpointAccess::capture(again.world);
    rejects([&] { CheckpointAccess::restore_floor(bad, again.world, again.logic, again.enemies); },
            "wrong layout identity accepted");
    require(CheckpointAccess::capture(again.world).random_state == before_world.random_state &&
                again.world.entities().size() == before_world.entities.size(),
            "failed restore partially committed");
    campaign.current = transitions.current();
    campaign.last_dungeon = transitions.last_dungeon();
    campaign.player = CheckpointAccess::capture(session);
    remember_floor(campaign, snapshot(again, campaign.current, actor));
    campaign.revision = store.write(campaign);
    require(campaign.revision == 2, "second durable checkpoint revision wrong");
}
void verify_final(const char *pak, SaveStore &store) {
    PakArchive archive(pak);
    const auto c = store.read("cycle-hero", checkpoint_resource_identity(archive));
    require(c.revision == 2 && c.floors.size() == 2 &&
                same_dungeon_address(c.current, {u"Town", 0}),
            "third process lost revisited-floor campaign");
    const auto *main = find_floor(c, {u"Main", 1});
    require(main != nullptr, "visited Main absent");
    require(std::count_if(main->world.entities.begin(), main->world.entities.end(),
                          [](const auto &e) {
                              return e.kind == MasterResourceKind::monster && !e.alive;
                          }) == 1,
            "dead monster resurrected in saved Main");
    require(std::count_if(
                main->world.entities.begin(), main->world.entities.end(),
                [](const auto &e) { return e.kind == MasterResourceKind::item && e.alive; }) >= 1,
            "ground loot lost in saved Main");
}
} // namespace
int main(int argc, char **argv) {
    try {
        if (argc != 4)
            throw std::runtime_error(
                "usage: frontend_cycle_test authored_pak save_directory write|read|verify");
        SaveStore store(argv[2]);
        const std::string mode = argv[3];
        if (mode == "write")
            write_phase(argv[1], store);
        else if (mode == "read")
            load_and_travel(argv[1], store);
        else if (mode == "verify")
            verify_final(argv[1], store);
        else
            throw std::runtime_error("unknown cycle phase");
        std::cout << "frontend-cycle " << mode << ": " << checks
                  << " assertions (authored resources; not original Town/GUI parity)\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "frontend cycle failed: " << e.what() << '\n';
        return 1;
    }
}
