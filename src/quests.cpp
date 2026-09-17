#include "torchlight/quests.hpp"
#include "torchlight/resource_fields.hpp"
#include <algorithm>
#include <cctype>
#include <limits>
#include <set>
namespace torchlight {
namespace { namespace rf=resource_fields;
const QuestFlags* find_flags(const QuestCheckpoint& s,std::u16string_view n){const auto name=rf::upper(std::u16string(n));for(const auto& f:s.flags)if(f.name==name)return &f;return nullptr;}
bool completed(const QuestCheckpoint& s,std::u16string_view n){const auto* f=find_flags(s,n);return f&&f->complete;}
bool active(const QuestCheckpoint& s,std::u16string_view n){const auto* f=find_flags(s,n);return f&&f->active;}
std::vector<std::u16string> names(const AdmGroup* g){std::vector<std::u16string> result;if(!g)return result;
 if(!g->groups.empty())throw std::invalid_argument("unexpected quest list subgroup");
 for(const auto&p:g->properties){if(rf::upper(p.name)!=u"QUEST")throw std::invalid_argument("unsupported quest list key");const auto* n=std::get_if<std::u16string>(&p.value);if(!n||n->empty())throw std::invalid_argument("invalid quest reference");result.push_back(rf::upper(*n));}return result;}
QuestRequirements requirements(const AdmGroup& g){QuestRequirements r;const auto* a=rf::child(g,u"REQUIREMENTS");if(!a)return r;r.present=true;
 r.minimum_level=rf::integer(*a,u"MINPLAYERLEVEL",-1);r.maximum_level=rf::integer(*a,u"MAXPLAYERLEVEL",-1);r.minimum_depth=rf::integer(*a,u"MINDUNGEONDEPTH",-1);r.maximum_depth=rf::integer(*a,u"MAXDUNGEONDEPTH",-1);r.ruleset=rf::upper(rf::text(*a,u"RULESET"));
 for(const auto&p:a->properties)if(p.name!=u"MINPLAYERLEVEL"&&p.name!=u"MAXPLAYERLEVEL"&&p.name!=u"MINDUNGEONDEPTH"&&p.name!=u"MAXDUNGEONDEPTH"&&p.name!=u"RULESET")throw std::invalid_argument("unknown quest requirement property");
 for(const auto&c:a->groups)if(c.name!=u"QUESTSCOMPLETE"&&c.name!=u"QUESTSNOTCOMPLETE"&&c.name!=u"QUESTSACTIVE")throw std::invalid_argument("unknown quest requirement group");
 r.complete=names(rf::child(*a,u"QUESTSCOMPLETE"));r.not_complete=names(rf::child(*a,u"QUESTSNOTCOMPLETE"));r.active=names(rf::child(*a,u"QUESTSACTIVE"));return r;}
void check_pure(const QuestDefinition& d){if(!d.controller_completes)throw std::invalid_argument("automatic quest completion/objectives are not implemented");
 const std::set<std::u16string> root={u"NAME",u"DISPLAYNAME",u"DESCRIPTION",u"DUNGEON",u"FORCEACCEPT",u"QUESTCONTROLLERCOMPLETES",u"QUEST_GUID",u"SHOWQUESTCOMPLETE"};
 const std::set<std::u16string> dialog={u"UNITNAME",u"DIALOG",u"SOUND",u"ICONABOVEHEAD",u"FLOATYTEXT",u"LOOK_AT_PLAYER",u"COMPLETE",u"DETAILS"};
 for(const auto&p:d.resource.properties)if(!root.count(rf::upper(p.name)))throw std::invalid_argument("unimplemented quest field: "+rf::ascii(p.name));
 for(const auto&g:d.resource.groups){const auto name=rf::upper(g.name);if(name==u"REQUIREMENTS"||name==u"GIVE_QUESTS_ON_COMPLETE")continue;
  if(name!=u"DIALOG")throw std::invalid_argument("unimplemented quest action/group: "+rf::ascii(g.name));
  if(!g.properties.empty())throw std::invalid_argument("unimplemented dialog root property");
  for(const auto&part:g.groups){if(!part.groups.empty())throw std::invalid_argument("nested dialog action");for(const auto&p:part.properties)if(!dialog.count(rf::upper(p.name)))throw std::invalid_argument("unimplemented dialog side effect: "+rf::ascii(p.name));}
 }
}
AdmGroup property_group(const LayoutObject&o){AdmGroup g;g.properties=o.properties;return g;}
}
void validate_quest_checkpoint(const QuestCheckpoint& s){if(s.flags.size()>4096||s.completed_count>1000000000U)throw std::invalid_argument("quest checkpoint bounds");std::set<std::u16string> seen;for(const auto&f:s.flags){if(f.name.empty()||f.name.size()>256||rf::upper(f.name)!=f.name||!seen.insert(f.name).second)throw std::invalid_argument("invalid/duplicate quest state");}}
bool quest_requirements_met(const QuestDefinition&d,const QuestCheckpoint&s,const QuestRequirementContext&c){
 if(completed(s,d.name))return false;
 const auto&r=d.requirements;
 if(!r.present)return true;
 if(!c.player_present||!c.manager_present)return false;
 if(r.minimum_level!=-1&&(c.player_level<static_cast<std::uint32_t>(r.minimum_level)||c.player_level>static_cast<std::uint32_t>(r.maximum_level)))return false;
 for(const auto&n:r.complete)if(n!=d.name&&!completed(s,n))return false;
 for(const auto&n:r.not_complete)if(n!=d.name&&completed(s,n))return false;
 for(const auto&n:r.active)if(!active(s,n))return false;
 if(!c.maximum_depth||!c.template_name)return false;
 const auto dungeon=d.dungeon.empty()?std::u16string(u"MAIN"):d.dungeon;
 const auto maximum=c.maximum_depth(dungeon);if(!maximum||*maximum==std::numeric_limits<std::int32_t>::max())return false;
 const auto depth=std::max(0,*maximum+1);const auto name=c.template_name(dungeon,depth);if(!name)return false;
 if(!r.ruleset.empty()&&rf::upper(*name)!=r.ruleset)return false;
 return r.minimum_depth==-1||(depth>=r.minimum_depth&&depth<=r.maximum_depth);
}
QuestCatalog::QuestCatalog(const PakArchive&p){for(const auto&e:p.entries()){auto path=e.name;std::transform(path.begin(),path.end(),path.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});if(e.is_directory()||path.rfind("media/quests/",0)!=0||path.size()<8||path.substr(path.size()-8)!=".dat.adm")continue;
 QuestDefinition d;d.resource=parse_adm(p.read(e)).root;d.source_path=e.name;d.name=rf::upper(rf::text(d.resource,u"NAME"));d.display_name=rf::text(d.resource,u"DISPLAYNAME",d.name);d.guid=rf::guid(d.resource,u"QUEST_GUID");d.dungeon=rf::upper(rf::text(d.resource,u"DUNGEON"));d.force_accept=rf::flag(d.resource,u"FORCEACCEPT");d.controller_completes=rf::flag(d.resource,u"QUESTCONTROLLERCOMPLETES");d.requirements=requirements(d.resource);d.on_complete=names(rf::child(d.resource,u"GIVE_QUESTS_ON_COMPLETE"));
 try{check_pure(d);}catch(const std::exception&x){d.unavailable_reason=x.what();}
 if(d.name.empty()||!by_name_.emplace(d.name,definitions_.size()).second)throw std::invalid_argument("duplicate or empty quest name");
 definitions_.push_back(std::move(d));}
 // A pure parent cannot complete partially if a chained quest has side effects.
 bool changed=true;while(changed){changed=false;for(auto&d:definitions_)if(d.flag_only())for(const auto&n:d.on_complete){const auto*q=find(n);if(!q||!q->flag_only()){d.unavailable_reason="unsupported chained quest: "+rf::ascii(n);changed=true;break;}}}
 // Cycles do not recurse on acceptance (only completion starts successors).
}
const QuestDefinition* QuestCatalog::find(std::u16string_view n)const{const auto it=by_name_.find(rf::upper(std::u16string(n)));return it==by_name_.end()?nullptr:&definitions_[it->second];}
void QuestCatalog::validate(const QuestCheckpoint&s)const{validate_quest_checkpoint(s);for(const auto&f:s.flags){const auto*d=find(f.name);if(!d||!d->flag_only())throw std::invalid_argument("checkpoint quest has unimplemented side effects");}}
QuestControllerRuntime::QuestControllerRuntime(const QuestCatalog&c,QuestCheckpoint&s,const LayoutManifest&l,LogicRuntime&r):catalog_(&c),state_(&s),layout_(&l),logic_(&r){c.validate(s);r.set_subsystem_input([this](const auto&o,auto input){return this->input(o,input);});}
QuestControllerRuntime::~QuestControllerRuntime(){logic_->set_subsystem_input({});}
QuestFlags& QuestControllerRuntime::flags(std::u16string_view name){for(auto&f:state_->flags)if(f.name==name)return f;state_->flags.push_back({std::u16string(name),false,false,false});return state_->flags.back();}
void QuestControllerRuntime::broadcast(std::u16string_view name, std::u16string_view output) {
    broadcast_from(std::u16string(name), std::u16string(output), 0);
}
void QuestControllerRuntime::broadcast_from(std::u16string name, std::u16string output, std::size_t index) {
    // Original quest listeners are synchronous and visited in registration order.
    // The shared logic queue is LIFO: finish this listener and its descendants
    // BEFORE visiting the next listener, rather than enqueueing the whole list.
    for (; index < layout_->objects.size(); ++index) {
        const auto& object = layout_->objects[index];
        if (object.descriptor != u"Quest Controller" ||
            rf::upper(rf::text(property_group(object), u"QUEST")) != name) continue;
        logic_->after_current_event([this, name, output, index] {
            broadcast_from(name, output, index + 1);
        });
        logic_->emit(object.id, output);
        return;
    }
}
void QuestControllerRuntime::accept(const QuestDefinition& d, bool dialog) {
    auto& f = flags(d.name);
    if (f.active) return;
    f.active = true;
    if (dialog) logic_->after_current_event([this, &d] { flags(d.name).accept_dialog = true; });
    broadcast(d.name, u"Quest Active");
}
void QuestControllerRuntime::complete(const QuestDefinition& d) {
    if (completed(*state_, d.name)) return;
    if (!active(*state_, d.name)) {
        logic_->after_current_event([this, &d] { complete_after_accept(d); });
        accept(d, false);
        return;
    }
    complete_after_accept(d);
}
void QuestControllerRuntime::complete_after_accept(const QuestDefinition& d) {
    // setQuestComplete(true) accepts once, then continues even if a synchronous
    // acceptance listener removed it (de6b20 -> d32600). Never re-accept in a loop.
    if (state_->completed_count == 1000000000U) throw std::invalid_argument("quest count overflow");
    ++state_->completed_count;
    complete_successors(d, 0);
}
void QuestControllerRuntime::complete_successors(const QuestDefinition& d, std::size_t index) {
    if (index < d.on_complete.size()) {
        const auto* next = catalog_->find(d.on_complete[index]);
        logic_->after_current_event([this, &d, index] { complete_successors(d, index + 1); });
        // Chained giveQuest(false) does not mark the accept dialog interacted.
        if (!active(*state_, next->name)) accept(*next, false);
        return;
    }
    auto& f = flags(d.name);
    f.active = false;
    f.accept_dialog = false;
    f.complete = true;
    broadcast(d.name, u"Quest Complete");
}
bool QuestControllerRuntime::input(const LayoutObject&o,std::u16string_view in){if(o.descriptor!=u"Quest Controller")return false;
 if(in!=u"Force Accept"&&in!=u"Force Not Accepted"&&in!=u"Force Complete"&&in!=u"Force Not Complete")return false;
 const auto name=rf::upper(rf::text(property_group(o),u"QUEST"));const auto*d=catalog_->find(name);
 if(!d||!d->flag_only()){if(diagnostics_.size()<4096)diagnostics_.push_back(rf::ascii(name)+": "+(d?d->unavailable_reason:"missing quest"));return true;}
 // Original forced inputs bypass offer requirements (giveQuest 0xd33150).
 if(in==u"Force Accept")accept(*d,true);
 else if(in==u"Force Complete")complete(*d);
 else if(in==u"Force Not Accepted"){auto&f=flags(d->name);if(f.active){f.active=false;f.accept_dialog=false;broadcast(d->name,u"Quest Not Active");}}
 else{flags(d->name).complete=false;broadcast(d->name,u"Quest Not Complete");}
 return true;
}
void QuestControllerRuntime::initialize(){for(const auto&o:layout_->objects)if(o.descriptor==u"Quest Controller"){
 const auto g=property_group(o);if(!rf::flag(g,u"BROADCAST ON LOAD"))continue;const auto n=rf::upper(rf::text(g,u"QUEST"));const auto*d=catalog_->find(n);
 // Unknown legacy/unsupported quest flags are not treated as authoritative false.
 if(!d||!d->flag_only())continue;
 logic_->emit(o.id,active(*state_,n)?u"Quest Active":u"Quest Not Active");logic_->emit(o.id,completed(*state_,n)?u"Quest Complete":u"Quest Not Complete");}}
} // namespace torchlight
