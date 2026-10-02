#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include <algorithm>
#include <limits>
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
 // Own sale stock on an actual resource-spawned NPC, not on the catalog GUID.
 require(world.consume_spawn_requests({{42,npc->name,u"Monsters",1}},logic).entities_created==1,"merchant spawn failed");
 const auto merchant_id=world.entities().back().id;
 auto* owner=world.find(merchant_id);require(owner&&owner->resource_guid==m->guid,"wrong merchant owner");
 const auto full=std::find_if(restored.inventory().items().begin(),restored.inventory().items().end(),
     [&](const auto& item){return item.resource_guid==low[0]->item.resource_guid&&item.consumable->count==20;});
 require(full!=restored.inventory().items().end(),"full purchased stack absent");
 const auto full_id=full->id;
 const auto sale_price=equipment_sell_price(low[0]->prices,20,true,restored.barter_percent());
 const auto before_sale=restored.gold();
 const auto sold=restored.sell_potion(catalog,*owner,full_id);
 require(sold.status==SaleStatus::sold&&sold.price==sale_price&&restored.gold()==before_sale+sale_price,"whole stack sale wallet");
 require(!restored.inventory().find(full_id)&&count(restored,low[0]->item.resource_guid)==3&&
         owner->merchant_buyback.size()==1&&owner->merchant_buyback[0].id==full_id&&
         owner->merchant_buyback[0].consumable->count==20,"sale did not transfer whole owned stack");
 const auto resource_identity=checkpoint_resource_identity(pak);
 EnemyController enemies(31);
 const auto capture_trade=[&](const PlayerSession& player){
     CampaignCheckpoint c;c.slot="merchant";c.revision=1;c.resource_identity=resource_identity;
     c.seed=31;c.class_guid=proto.guid;c.character_name="merchant";c.player=CheckpointAccess::capture(player);
     FloorCheckpoint floor;floor.address=c.current;floor.layout_identity=checkpoint_layout_identity(manifest);
     floor.world=CheckpointAccess::capture(world);floor.logic=CheckpointAccess::capture(logic);
     floor.enemies=CheckpointAccess::capture(enemies);c.floors.push_back(std::move(floor));return c;
 };
 restored.give_gold(-std::numeric_limits<std::int32_t>::max());
 const auto denied_state=encode_checkpoint(capture_trade(restored));
 require(restored.buy_back_potion(catalog,*owner,full_id).status==PurchaseStatus::insufficient_gold&&
         denied_state==encode_checkpoint(capture_trade(restored)),"failed buyback changed money/ownership");
 restored.give_gold(100000);
 const auto rebuy_price=equipment_buy_price(low[0]->prices,20,true,restored.barter_percent());
 const auto before_rebuy=restored.gold();const auto bought=restored.buy_back_potion(catalog,*owner,full_id);
 require(bought.status==PurchaseStatus::purchased&&bought.paid==rebuy_price&&
         restored.gold()==before_rebuy-rebuy_price&&count(restored,low[0]->item.resource_guid)==23&&
         owner->merchant_buyback.empty(),"finite stack was cloned or bought one bottle at a time");
 require(restored.inventory().find(bought.item)->consumable->count==20,"buyback split across the remaining 3-stack");
 require(restored.buy_back_potion(catalog,*owner,full_id).status==PurchaseStatus::unavailable,"finite stock sold twice");
 PlayerSession single(proto,88,&types);single.give_gold(10000);
 const auto bottle=single.buy_potion(catalog,m->guid,low[0]->item.resource_guid);
 require(single.inventory().find(bottle.item)->consumable->count==1,"single bottle fixture");
 require(single.sell_potion(catalog,*owner,bottle.item).status==SaleStatus::sold,"single sale failed");
 require(single.buy_back_potion(catalog,*owner,bottle.item).status==PurchaseStatus::purchased&&
         single.buy_back_potion(catalog,*owner,bottle.item).status==PurchaseStatus::purchased&&
         count(single,low[0]->item.resource_guid)==2&&owner->merchant_buyback.size()==1&&
         owner->merchant_buyback[0].consumable->count==1,"original single MERCHANTINFINITE clone branch lost");
 const auto trade=decode_checkpoint(encode_checkpoint(capture_trade(single)));
 require(trade.floors[0].world.entities.back().merchant_buyback.size()==1&&
         encode_checkpoint(trade)==encode_checkpoint(capture_trade(single)),"v7 buyback codec not canonical");
 LogicRuntime restored_logic(manifest);RuntimeEntityWorld restored_world(manifest,index,loader,spawn,type_index,31,1);
 EnemyController restored_enemies(31);
 CheckpointAccess::restore_floor(trade.floors[0],restored_world,restored_logic,restored_enemies);
 require(restored_world.find(merchant_id)->merchant_buyback[0].id==bottle.item,"floor restore lost merchant instance");
 auto malformed=trade.floors[0];malformed.world.entities.back().merchant_buyback[0].consumable->effects[0].value+=1;
 rejects([&]{CheckpointAccess::restore_floor(malformed,restored_world,restored_logic,restored_enemies);},"changed buyback effects restored");
 require(restored_world.find(merchant_id)->merchant_buyback[0].consumable->effects[0].value==
         owner->merchant_buyback[0].consumable->effects[0].value,"failed restore committed merchant data");
 malformed=trade.floors[0];malformed.world.entities.back().merchant_buyback.push_back(malformed.world.entities.back().merchant_buyback.front());
 rejects([&]{CheckpointAccess::validate(malformed);},"duplicate merchant owned ID accepted");
 auto unsupported=owner->merchant_buyback.front();unsupported.consumable->effects[0].value+=1;
 require(!catalog.trade_offer(m->guid,unsupported),"unknown rolled potion accepted for trade");
 RuntimeEntity stranger=*owner;stranger.merchant_buyback.clear();
 require(single.buy_back_potion(catalog,stranger,bottle.item).status==PurchaseStatus::unavailable,"buyback leaked to another same-GUID NPC");
 stranger.alive=false;
 require(single.sell_potion(catalog,stranger,single.inventory().items().back().id).status==SaleStatus::unavailable,"dead merchant accepted sale");
 single.give_gold(std::numeric_limits<std::int32_t>::max());
 const auto remaining=std::find_if(single.inventory().items().begin(),single.inventory().items().end(),
     [&](const auto& item){return item.resource_guid==low[0]->item.resource_guid;});
 require(single.sell_potion(catalog,*owner,remaining->id).status==SaleStatus::sold&&
         single.gold()==std::numeric_limits<std::int32_t>::max(),"sale wallet did not use original saturation");
 std::cout<<"Tarn potions="<<m->potions.size()<<" unsupported="<<m->unsupported_entries.size()<<" first_price="<<price<<'\n';
}
}
int main(int argc,char**argv){try{core();if(argc==2)real(argv[1]);std::cout<<"PASS merchant checks="<<checks<<'\n';return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
