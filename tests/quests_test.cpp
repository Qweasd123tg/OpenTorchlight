#include "torchlight/quests.hpp"
#include "torchlight/save_store.hpp"
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool a,const char*b){++checks;if(!a)throw std::runtime_error(b);}
template<class F>void rejects(F f,const char*name){bool rejected=false;try{f();}catch(const std::exception&){rejected=true;}require(rejected,name);}
void core(){
 QuestDefinition d;d.name=u"SELF";QuestCheckpoint state;QuestRequirementContext c;
 c.player_present=false;require(quest_requirements_met(d,state,c),"absent requirements require player");
 d.requirements.present=true;require(!quest_requirements_met(d,state,c),"present requirements missing player");
 c.player_present=true;c.maximum_depth=[](auto n)->std::optional<std::int32_t>{return n==u"MAIN"?std::optional<std::int32_t>(4):std::nullopt;};
 c.template_name=[](auto,std::int32_t n)->std::optional<std::u16string>{return n==5?std::optional<std::u16string>(u"MINE"):std::nullopt;};
 require(quest_requirements_met(d,state,c),"default MAIN max depth + 1");
 d.requirements.minimum_depth=5;d.requirements.maximum_depth=5;require(quest_requirements_met(d,state,c),"inclusive quest depth");
 d.requirements.maximum_depth=4;require(!quest_requirements_met(d,state,c),"wrong max depth");d.requirements.minimum_depth=-1;require(quest_requirements_met(d,state,c),"sentinel did not bypass both depth bounds");
 d.requirements.ruleset=u"CRYPT";require(!quest_requirements_met(d,state,c),"ruleset mismatch");d.requirements.ruleset=u"MINE";
 d.requirements.minimum_level=2;d.requirements.maximum_level=-1;require(!quest_requirements_met(d,state,c),"minimum player level");c.player_level=2;require(quest_requirements_met(d,state,c),"unsigned max level sentinel");
 d.requirements.complete={u"SELF"};d.requirements.not_complete={u"SELF"};require(quest_requirements_met(d,state,c),"self dependency exception");
 d.requirements.active={u"SELF"};require(!quest_requirements_met(d,state,c),"self active exception invented");state.flags.push_back({u"SELF",true,false,false});require(quest_requirements_met(d,state,c),"self active missing");
 state.flags[0].complete=true;require(!quest_requirements_met(d,state,c),"complete quest offered again");
 state.flags.push_back(state.flags[0]);rejects([&]{validate_quest_checkpoint(state);},"duplicate flags");
}
AdmProperty text(std::u16string name,std::u16string value){return {0,std::move(name),AdmValueType::string,std::move(value)};}
const QuestFlags* row(const QuestCheckpoint&s,std::u16string_view name){for(const auto&r:s.flags)if(r.name==name)return &r;return nullptr;}
void real(const char*path){PakArchive p(path);QuestCatalog catalog(p);require(catalog.definitions().size()==111,"quest catalog count");
 for(const auto&d:catalog.definitions())if(d.name==u"INTROTOGAMEPT1"&&!d.flag_only())throw std::runtime_error(d.unavailable_reason);
 require(catalog.find(u"IntroToGamePT1")&&catalog.find(u"INTROTOGAMEPT1")->flag_only(),"intro pure flags blocked");
 require(catalog.find(u"INTROTOGAMEPT3")&&!catalog.find(u"INTROTOGAMEPT3")->flag_only(),"population quest incorrectly executable");
 QuestCheckpoint state;LayoutManifest layout;
 for(const auto&n:{u"INTROTOGAMEPT1",u"RANDOMMINERS",u"INTROTOGAMEPT3"}){LayoutObject o;o.id=static_cast<std::int64_t>(layout.objects.size()+1);o.descriptor=u"Quest Controller";o.properties.push_back(text(u"QUEST",n));layout.objects.push_back(o);}
 LogicRuntime logic(layout);QuestControllerRuntime runtime(catalog,state,layout,logic);
 logic.invoke(1,u"Force Accept");require(row(state,u"INTROTOGAMEPT1")&&row(state,u"INTROTOGAMEPT1")->active,"force accept");require(row(state,u"INTROTOGAMEPT1")->accept_dialog,"accept dialog state");
 auto events=logic.take_events();require(events.size()==1&&events[0].output_name==u"Quest Active","accepted output");
 logic.invoke(1,u"Force Complete");require(row(state,u"INTROTOGAMEPT1")->complete&&!row(state,u"INTROTOGAMEPT1")->active&&!row(state,u"INTROTOGAMEPT1")->accept_dialog,"complete flags");
 require(row(state,u"RANDOMMINERS")&&row(state,u"RANDOMMINERS")->active&&!row(state,u"RANDOMMINERS")->accept_dialog,"chained quest grant");
 events=logic.take_events();require(events.size()==2&&events[0].object_id==2&&events[0].output_name==u"Quest Active"&&events[1].object_id==1&&events[1].output_name==u"Quest Complete","completion event order");
 require(state.completed_count==1,"completion statistic");logic.invoke(1,u"Force Complete");require(logic.take_events().empty()&&state.completed_count==1,"repeated complete replay");
 logic.invoke(2,u"Force Not Accepted");events=logic.take_events();require(events.size()==1&&events[0].output_name==u"Quest Not Active","forced unaccept invented abandon");
 const auto size=state.flags.size();logic.invoke(3,u"Force Complete");require(!runtime.diagnostics().empty()&&state.flags.size()==size&&!row(state,u"INTROTOGAMEPT3"),"unsupported quest partially complete");
 logic.invoke(1,u"Force Not Complete");require(!row(state,u"INTROTOGAMEPT1")->complete&&!row(state,u"INTROTOGAMEPT1")->active,"reset accepts quest");
 require(state.completed_count==1,"reset decremented journal");catalog.validate(state);
 // Multiple listeners must keep resource order, including nested actions.
 LayoutObject duplicate=layout.objects[0];duplicate.id=4;layout.objects.push_back(duplicate);
 QuestCheckpoint multi;LogicRuntime multi_logic(layout);QuestControllerRuntime multi_runtime(catalog,multi,layout,multi_logic);
 multi_logic.invoke(1,u"Force Accept");events=multi_logic.take_events();
 require(events.size()==2&&events[0].object_id==1&&events[1].object_id==4,"listener order reversed by LIFO queue");
 multi_logic.invoke(1,u"Force Complete");events=multi_logic.take_events();
 require(events.size()==3&&events[0].object_id==2&&events[1].object_id==1&&events[2].object_id==4,"chained/duplicate listener ordering");
 // Controller states survive the actual campaign codec without broadcasting
 // completion or reissuing chained grants on restore.
 CampaignCheckpoint campaign;campaign.slot="quests";campaign.character_name="Quest regression";campaign.resource_identity=1;campaign.class_guid=1;
 FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;campaign.floors.push_back(floor);
 campaign.player.maximum_health=100;campaign.player.health=100;campaign.player.base_health=100;
 campaign.quests=multi;auto restored=decode_checkpoint(encode_checkpoint(campaign)).quests;
 require(restored.completed_count==1&&row(restored,u"INTROTOGAMEPT1")->complete&&row(restored,u"RANDOMMINERS")->active,"quest save codec loses flags");
 LogicRuntime restored_logic(layout);QuestControllerRuntime restored_runtime(catalog,restored,layout,restored_logic);
 require(restored_logic.take_events().empty(),"binding loaded state replays events");
 restored_logic.invoke(1,u"Force Complete");require(restored.completed_count==1&&restored_logic.take_events().empty(),"load repeats completion");
 std::size_t pure=0;for(const auto&d:catalog.definitions())pure+=d.flag_only();std::cout<<"quests="<<catalog.definitions().size()<<" flag_only="<<pure<<'\n';
}
}
int main(int argc,char**argv){try{core();if(argc==2)real(argv[1]);std::cout<<"PASS quest checks="<<checks<<'\n';return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
