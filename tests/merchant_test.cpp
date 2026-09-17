#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include <iostream>
using namespace torchlight;
namespace {
unsigned checks=0;void require(bool v,const char*s){++checks;if(!v)throw std::runtime_error(s);}
template<class F>void rejects(F f,const char*s){bool caught=false;try{f();}catch(const std::exception&){caught=true;}require(caught,s);}
void core(){EquipmentPrices p{51,7,23,3};require(equipment_buy_price(p,2,true,10)==92,"buy barter truncation");require(equipment_sell_price(p,2,true,10)==15,"sell barter truncation");require(equipment_buy_price(p,0,false,90)==23,"unidentified/default count");require(equipment_buy_price(p,1,true,125)==1,"buy minimum");require(equipment_base_price(101,50)==51,"ceil base price");require(equipment_base_price(999,0)==1,"zero VALUE");rejects([&]{(void)equipment_buy_price(p,2147483647,true,0);},"overflow");rejects([&]{(void)equipment_base_price(-1,100);},"negative graph");}
std::uint32_t count(const PlayerSession&p,std::int64_t guid){std::uint32_t n=0;for(const auto&i:p.inventory().items())if(i.resource_guid==guid&&i.consumable)n+=i.consumable->count;return n;}
void real(const char*path){PakArchive pak(path);MasterResourceIndex index(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));UnitDefinitionLoader loader(pak);SpawnClassCatalog spawn(pak);UnitTypeHierarchy types(pak);PotionMerchantCatalog catalog(pak,index,loader,spawn,types);
 const auto* npc=index.find_case_insensitive(MasterResourceKind::monster,u"Tarn the Merchant");require(npc,"Tarn absent");const auto*m=catalog.find(npc->guid);require(m&&m->potions.size()==8&&m->unsupported_entries.size()==3,"Tarn catalog/unsupported entries");
 auto low=catalog.offers(m->guid,1);require(low.size()==2,"level1 potion pair");const auto* low_record=index.find(low[0]->item.resource_guid);
 require(low_record && low[0]->item.mesh_path==pak.find_normalized(unit_model_path(*loader.load(*low_record)))->name,"merchant lost canonical item mesh");
 auto high=catalog.offers(m->guid,7);require(high.size()==2&&high[0]->item.resource_guid!=low[0]->item.resource_guid,"level7 potion tier");require(catalog.offers(m->guid,6)[0]==low[0],"range upper inclusive");
 auto players=load_playable_players(pak,index,loader);require(!players.empty(),"real player absent");auto proto=players.front();PlayerSession p(proto,72,&types);p.give_gold(-2147483647);
 const auto gold=p.gold();const auto items=p.inventory().items().size();auto r=p.buy_potion(catalog,m->guid,low[0]->item.resource_guid);require(r.status==PurchaseStatus::insufficient_gold&&p.gold()==gold&&p.inventory().items().size()==items,"failed purchase mutates state");
 p.give_gold(100000);const auto before=p.gold();const auto price=equipment_buy_price(low[0]->prices,1,true,p.barter_percent());
 for(unsigned i=0;i<21;++i){r=p.buy_potion(catalog,m->guid,low[0]->item.resource_guid);require(r.status==PurchaseStatus::purchased&&r.paid==price,"infinite purchase");}
 require(count(p,low[0]->item.resource_guid)==21&&p.gold()==before-price*21,"purchase count/gold");std::size_t stacks=0;for(const auto&i:p.inventory().items())if(i.resource_guid==low[0]->item.resource_guid)++stacks;require(stacks==2,"MAXSTACKSIZE split");
 // Reconstruct the same descriptor as a world pickup; bought and found items
 // must merge rather than splitting by a missing merchant-only mesh path.
 auto bag=p.inventory();auto found=low[0]->item;found.mesh_path=pak.find_normalized(unit_model_path(*loader.load(*low_record)))->name;
 const auto stack_count=bag.items().size();(void)bag.store(found);require(bag.items().size()==stack_count,"found/bought descriptors do not stack");
 const auto balance=p.gold();require(p.buy_potion(catalog,m->guid,high[0]->item.resource_guid).status==PurchaseStatus::unavailable&&p.gold()==balance,"higher tier bought early");
 auto saved=CheckpointAccess::capture(p);auto restored=CheckpointAccess::restore_player(proto,saved,72,&types);require(count(restored,low[0]->item.resource_guid)==21&&restored.gold()==p.gold(),"purchase save/load");
 require(restored.buy_potion(catalog,m->guid,low[0]->item.resource_guid).status==PurchaseStatus::purchased&&count(restored,low[0]->item.resource_guid)==22,"infinite stock after restore");
 // Actual resource spawn -> pickup must share the purchased stack.
 UnitTypeResourceIndex type_index(pak,types,index,loader);
 LayoutManifest manifest;LayoutObject spawner;spawner.id=42;spawner.descriptor=u"Unit Spawner";manifest.objects.push_back(spawner);
 LogicRuntime logic(manifest);RuntimeEntityWorld world(manifest,index,loader,spawn,type_index,31,1);
 const auto spawned=world.consume_spawn_requests({{42,low[0]->item.name,u"Items",1}},logic);
 require(spawned.entities_created==1,"real potion spawn failed");
 const auto before_pickup=restored.inventory().items().size();
 require(restored.pick_up(world,world.entities().back().id,logic)!=0,"real potion pickup failed");
 require(restored.inventory().items().size()==before_pickup&&count(restored,low[0]->item.resource_guid)==23,"picked/bought real potion did not merge");
 std::cout<<"Tarn potions="<<m->potions.size()<<" unsupported="<<m->unsupported_entries.size()<<" first_price="<<price<<'\n';
}
}
int main(int argc,char**argv){try{core();if(argc==2)real(argv[1]);std::cout<<"PASS merchant checks="<<checks<<'\n';return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
