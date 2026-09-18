// An unchanged large-15 application produced the v5 input. This executable
// never forges a version byte and never rerolls saved weapon characteristics.
#include "torchlight/save_store.hpp"
#include "torchlight/typed_damage.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool condition,const char* message) {
    ++checks;if(!condition)throw std::runtime_error(message);
}
std::vector<std::uint8_t> read(const char* path) {
    std::ifstream stream(path,std::ios::binary);
    if(!stream)throw std::runtime_error("cannot read checkpoint");
    return {std::istreambuf_iterator<char>(stream),std::istreambuf_iterator<char>()};
}
}
int main(int argc,char**argv) {
    try {
        if(argc!=5)throw std::invalid_argument("typed_migration_test PAK INPUT OUTPUT EXPECTED_INPUT_VERSION");
        const auto bytes=read(argv[2]);
        require(bytes.size()>20 && bytes[8]==std::stoul(argv[4]),"wrong genuine input version");
        auto before=decode_checkpoint(bytes);
        PakArchive pak(argv[1]);
        MasterResourceIndex resources(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));
        UnitDefinitionLoader definitions(pak);UnitTypeHierarchy hierarchy(pak);
        require(before.resource_identity==checkpoint_resource_identity(pak),"fixture pak mismatch");
        const auto players=load_playable_players(pak,resources,definitions);
        const auto found=std::find_if(players.begin(),players.end(),[&](const auto& p){return p.guid==before.class_guid;});
        require(found!=players.end(),"saved class not found");
        const auto item=std::find_if(before.player.inventory.items.begin(),before.player.inventory.items.end(),[](const auto& i){return i.resource_guid==INT64_C(5521717854978183646);});
        require(item!=before.player.inventory.items.end() && item->weapon,"genuine Moldy Staff missing");
        if(bytes[8]==5) require(!item->weapon->prototype.damage_percent && item->weapon->prototype.delivery==WeaponDelivery::unsupported_damage,
            "legacy input was already rewritten with typed metadata");
        const auto graph_roll=item->weapon->prototype.damage_percent ? item->weapon->damage_bonus[5] : item->weapon->maximum_damage;
        const auto item_id=item->id;
        auto session=CheckpointAccess::restore_player(*found,before.player,before.seed,&hierarchy);
        session.hydrate_consumables(definitions,resources);
        const auto after=CheckpointAccess::capture(session);
        const auto* stored=session.inventory().find(item_id);
        require(stored && stored->weapon,"saved staff ID lost");
        // Hydration swaps the bag transactionally; retain a value, not a dangling
        // reference across the second hydration below.
        const auto weapon=*stored->weapon;
        require(weapon.prototype.delivery==WeaponDelivery::direct_typed && weapon.prototype.damage_percent &&
            (*weapon.prototype.damage_percent)[0]==0 && (*weapon.prototype.damage_percent)[5]==100,
            "migration did not use exact staff resource percentages");
        require(weapon.maximum_damage==0 && weapon.minimum_damage==0 && weapon.damage_bonus[5]==graph_roll,
            "legacy graph roll was rerolled, double-split, or left physical");
        const auto& combat=session.combat();
        require(combat.attack_loadout().right && ordinary_delivery_supported(*combat.attack_loadout().right) &&
            combat.attack_loadout().right->damage_bonus[5]==graph_roll,"live attack not rebound to hydrated item");
        require(combat.attack_character().magic==session.attributes()[2],"saved attributes do not reach MAGIC");
        require(after.combat_random==before.player.combat_random,"migration consumed combat RNG");
        require(after.health==before.player.health && after.mana==before.player.mana && after.gold==before.player.gold,
            "migration healed, spent mana or changed wallet");
        auto canonical=before;
        for(auto& current:canonical.player.inventory.items) if(current.weapon && !current.weapon->prototype.damage_percent) {
            const auto* record=resources.find(current.resource_guid);
            require(record!=nullptr,"legacy weapon source not found");
            hydrate_weapon_damage(*current.weapon,*definitions.load(*record));
        }
        auto actual=before;actual.player=after;
        require(encode_checkpoint(actual)==encode_checkpoint(canonical),"unrelated checkpoint state changed during migration");
        session.hydrate_consumables(definitions,resources);
        actual.player=CheckpointAccess::capture(session);
        require(encode_checkpoint(actual)==encode_checkpoint(canonical),"repeat hydration changed checkpoint");
        const auto encoded=encode_checkpoint(actual);
        require(encoded[8]==kCheckpointFormatVersion && encode_checkpoint(decode_checkpoint(encoded))==encoded,"v6 codec is not canonical");
        require(!std::filesystem::exists(argv[3]),"refusing to overwrite output");
        std::ofstream out(argv[3],std::ios::binary);out.write(reinterpret_cast<const char*>(encoded.data()),static_cast<std::streamsize>(encoded.size()));
        out.close();require(bool(out),"checkpoint output failed");
        std::cout<<"PASS "<<checks<<" legacy/typed checks; input=v"<<unsigned(bytes[8])<<" saved_graph_roll="<<graph_roll
            <<" physical=0 poison="<<weapon.damage_bonus[5]<<" magic="<<combat.attack_character().magic
            <<" rng="<<after.combat_random<<'\n';
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
