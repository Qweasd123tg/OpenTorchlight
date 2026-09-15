#include "torchlight/player_session.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/inventory_view.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace torchlight;
namespace {
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
LayoutManifest layout() {
    LayoutManifest value;
    LayoutObject object; object.id=42; object.descriptor=u"Unit Spawner";
    value.objects.push_back(object);
    return value;
}
}
// This is a resource-backed PORT integration test, NOT execution of the original
// engine. It also runs against a wholly synthetic PAK to check the harness itself.
int main(int argc, char** argv) {
    try {
        if (argc!=3 || (std::string(argv[1])!="--pak" && std::string(argv[1])!="--original")) {
            std::cerr<<"usage: item_cycle_resource_test --pak|--original /path/to/pak.zip\n";return 2;
        }
        const PakArchive archive(argv[2]);
        const auto master=parse_adm(archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const MasterResourceIndex resources(master);
        UnitDefinitionLoader definitions(archive);
        const SpawnClassCatalog spawn_classes(archive);
        const UnitTypeHierarchy hierarchy(archive);
        const UnitTypeResourceIndex types(archive,hierarchy,resources,definitions);
        const auto manifest=layout();
        LogicRuntime logic(manifest,42);
        RuntimeEntityWorld world(manifest,resources,definitions,spawn_classes,types,42,1);
        PlayerPrototype prototype;prototype.minimum_health=prototype.maximum_health=1000;
        prototype.minimum_damage=prototype.maximum_damage=1;
        PlayerSession session(prototype,42,&hierarchy);
        FixedSceneGeometry geometry;
        std::size_t deaths=0, dropped_equipment=0, models=0;
        for (const auto& resource:resources.records()) {
            if(resource.kind!=MasterResourceKind::monster || resource.do_not_create || resource.unit_type!=u"MONSTER") continue;
            const auto before=world.entities().size();
            const auto created=world.consume_spawn_requests({{42,resource.name,u"Monsters",1}},logic);
            if(created.entities_created!=1) continue;
            const auto source=world.entities()[before].id;
            require(world.kill(source,logic),"resource monster could not enter ordinary death path");
            const auto drop_start=world.entities().size();
            const auto loot=world.resolve_death_loot(logic);
            require(loot.deaths==1,"ordinary death lost its one-shot treasure request");
            ++deaths;
            for(auto i=drop_start;i<world.entities().size();++i) {
                const auto id=world.entities()[i].id;
                if(world.entities()[i].kind!=MasterResourceKind::item || !world.entities()[i].inventory_eligible)continue;
                const auto instance=append_runtime_entity_geometry(archive,resources,definitions,world.entities()[i],geometry);
                if(!instance)continue;
                ++models;
                require(session.pick_up(world,id,logic)!=0,"real-resource dropped instance did not enter bag");
                ++dropped_equipment;
            }
            if(dropped_equipment || deaths>=32)break;
        }
        require(deaths>0 && dropped_equipment>0,"no model-backed equipment generated in 32 supported resource deaths; inspect treasure/rank eligibility");
        std::vector<InventoryId> weapons, chests;
        for(const auto& resource:resources.records()) {
            if(resource.kind!=MasterResourceKind::item || resource.do_not_create)continue;
            const auto slot=armor_slot_for_unit_type(resource.unit_type);
            const bool chest=slot && *slot==ArmorSlot::chest && chests.size()<2;
            const bool weapon=(hierarchy.is_a(resource.unit_type,u"SWORD") || hierarchy.is_a(resource.unit_type,u"STAFF")) && weapons.size()<2;
            if(!chest && !weapon)continue;
            const auto before=world.entities().size();
            const auto created=world.consume_spawn_requests({{42,resource.name,u"Items",1}},logic);
            if(created.entities_created!=1)continue;
            const auto& item=world.entities()[before];
            if(!item.inventory_eligible || (chest && !item.armor_item) || (weapon && !item.weapon_item))continue;
            const auto& chosen = chest ? chests : weapons;
            bool duplicate_resource = false;
            for (const auto owned : chosen)
                if (session.inventory().find(owned)->resource_guid == item.resource_guid) duplicate_resource = true;
            if (duplicate_resource) continue;
            const auto instance=append_runtime_entity_geometry(archive,resources,definitions,item,geometry);
            if(!instance)continue;
            ++models;
            const auto id=session.pick_up(world,item.id,logic);
            require(id!=0,"resource item pickup failed");
            if(chest)chests.push_back(id);else weapons.push_back(id);
            if(weapons.size()==2 && chests.size()==2)break;
        }
        require(weapons.size()==2 && chests.size()==2,"need two model-backed weapons and two chest armors in supplied PAK");
        const auto count=session.inventory().items().size();
        for(const auto id:weapons) {
            const auto expected=*session.inventory().find(id)->weapon;
            require(session.equip(id)==InventoryChange::changed,"weapon equip failed");
            require(session.combat().minimum_damage()==expected.minimum_damage && session.combat().maximum_damage()==expected.maximum_damage,"equip rerolled or ignored resource weapon damage");
            auto visual=prototype;visual.starting_weapon=expected.prototype;
            require(append_player_weapon_geometry(archive,visual,{0,0,0},geometry).has_value(),"resource weapon cannot be attached");
        }
        for(const auto id:chests) {
            const auto expected=*session.inventory().find(id)->armor;
            require(session.equip(id)==InventoryChange::changed,"chest equip failed");
            require(session.health().armor_class()==expected.damage_defense.natural_armor,"resource chest replacement stacked old armor");
        }
        TorchlightRandom incoming(7);
        static_cast<void>(session.health().apply_damage(100,100,DamageType::physical,incoming));
        const auto hp=session.health().health();
        const auto damage=session.combat().maximum_damage();
        const auto armor=session.health().armor_class();
        session.enter_level();
        require(session.health().health()==hp && session.combat().maximum_damage()==damage && session.health().armor_class()==armor,"floor change reset player or equipment");
        require(session.inventory().items().size()==count && session.weapon()->id==weapons.back(),"floor change lost owned instances or slot");
        require(session.inventory().find(weapons.front()) && session.inventory().find(chests.front()),"replacement destroyed displaced instance");
        InventoryView view;view.open=true;
        require(!view.lines(session).empty(),"inventory inspection missing");
        std::cout<<"resource_cycle deaths="<<deaths<<" dropped_equipment="<<dropped_equipment
                 <<" models="<<models<<" stored="<<count<<" weapons_checked=2 chest_armors_checked=2\n";
        return 0;
    } catch(const std::exception& error) {std::cerr<<"item_cycle_resource: "<<error.what()<<'\n';return 1;}
}
