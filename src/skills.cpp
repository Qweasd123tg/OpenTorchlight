#include "torchlight/skills.hpp"
#include "torchlight/resource_fields.hpp"
#include "torchlight/original_combat_inputs.hpp"
#include "torchlight/scene_animation.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
namespace torchlight {
namespace {
namespace rf = resource_fields;
AdmGroup merged(AdmGroup previous,const AdmGroup& next) {
    previous.name = next.name;
    for (const auto& p : next.properties) {
        auto it=std::find_if(previous.properties.begin(),previous.properties.end(),[&](const auto& q){return rf::upper(q.name)==rf::upper(p.name);});
        if(it==previous.properties.end()) previous.properties.push_back(p); else *it=p;
    }
    // An explicitly specified event replaces that event's inherited definition.
    // The strict executable subset below only accepts one explicit TRIGGER and
    // no inherited/chained event containers.
    for(const auto& g:next.groups) {
        previous.groups.erase(std::remove_if(previous.groups.begin(),previous.groups.end(),[&](const auto& q){return rf::upper(q.name)==rf::upper(g.name);}),previous.groups.end());
        previous.groups.push_back(g);
    }
    return previous;
}
float finite_float(double n) {
    if(!std::isfinite(n)||std::abs(n)>std::numeric_limits<float>::max()) throw std::invalid_argument("skill float overflow");
    return static_cast<float>(n);
}
std::int32_t cost(const AdmGroup& g) {
    const auto n=finite_float(rf::number(g,u"MANACOST",0));
    if(n<0||static_cast<double>(n)>std::numeric_limits<std::int32_t>::max()) throw std::invalid_argument("invalid skill mana cost");
    return static_cast<std::int32_t>(n); // original cvttss2si, not ceil
}
void supported_properties(const AdmGroup& g,const std::set<std::u16string>& allowed) {
    for(const auto& p:g.properties) if(!allowed.count(rf::upper(p.name)))
        throw std::invalid_argument("unsupported self-buff field: "+rf::ascii(p.name));
}
SelfBuffProgram compile_self_buff(const AdmGroup& rank,const AdmGroup& explicit_rank,
    const std::unordered_map<std::u16string,AdmGroup>& affixes,const AttackEffectCatalog& catalog,
    const AdmDocument& effects,std::int64_t guid) {
    if(rf::upper(rf::text(rank,u"ACTIVATION_TYPE"))!=u"NORMAL"||rf::upper(rf::text(rank,u"TARGET_TYPE"))!=u"SELF")
        throw std::invalid_argument("not a finite self-targeted NORMAL buff");
    supported_properties(rank,{u"NAME",u"DISPLAYNAME",u"DESCRIPTION",u"SKILL_ICON",u"SKILL_ICON_INACTIVE",u"ACTIVATION_TYPE",
        u"TARGET_ALIGNMENT",u"TARGET_TYPE",u"ANIMATION",u"MAX_INVEST_LEVEL",u"MAXLEVEL",u"UNIQUE_GUID",u"MANACOST",
        u"LEVEL_REQUIRED",u"COOLDOWNMS",u"MONSTERCOOLDOWNMS",u"SPEED"});
    if(rf::upper(rf::text(rank,u"TARGET_ALIGNMENT"))!=u"GOOD") throw std::invalid_argument("unsupported self-buff alignment");
    const auto* event=rf::child(explicit_rank,u"EVENT_TRIGGER");
    if(!event||rank.groups.size()!=1||explicit_rank.groups.size()!=1) throw std::invalid_argument("nontrivial skill event chain is not implemented");
    if(!event->properties.empty()) throw std::invalid_argument("skill event layout/conditions are not implemented");
    SelfBuffProgram result;
    for(const auto& list:event->groups) {
        if(rf::upper(list.name)!=u"AFFIXES") throw std::invalid_argument("unsupported skill event group");
        supported_properties(list,{u"AFFIXLEVEL",u"TARGET",u"AFFIX"});
        if(!list.groups.empty()||rf::upper(rf::text(list,u"TARGET"))!=u"SELF") throw std::invalid_argument("affix target must be SELF");
        for(const auto& prop:list.properties) if(rf::upper(prop.name)==u"AFFIX") {
            const auto* name=std::get_if<std::u16string>(&prop.value);
            if(!name) throw std::invalid_argument("invalid affix name");
            const auto found=affixes.find(rf::upper(*name));
            if(found==affixes.end()) throw std::invalid_argument("missing skill affix: "+rf::ascii(*name));
            const auto& a=found->second;
            supported_properties(a,{u"NAME",u"RANK",u"MIN_SPAWN_RANGE",u"MAX_SPAWN_RANGE",u"DURATION",u"WEIGHT",u"SLOTS_OCCUPY"});
            for(const auto& e:a.groups) {
                if(rf::upper(e.name)==u"UNITTYPES") {
                    bool player=e.properties.empty();
                    for(const auto& p:e.properties) {
                        const auto* value=std::get_if<std::u16string>(&p.value);
                        if(!value) throw std::invalid_argument("invalid affix unit restriction");
                        player|=rf::upper(*value)==u"PLAYER"||rf::upper(*value)==u"ANY";
                    }
                    if(!player) throw std::invalid_argument("affix disallows PLAYER");
                    continue;
                }
                if(rf::upper(e.name)!=u"EFFECT"||!e.groups.empty()) throw std::invalid_argument("conditional affix is not implemented");
                supported_properties(e,{u"NAME",u"TYPE",u"ACTIVATION",u"DURATION",u"UNITTHEME",u"DAMAGE_TYPE",u"EXCLUSIVE",u"MIN",u"MAX",u"VALUE"});
                if(rf::upper(rf::text(e,u"ACTIVATION",u"DYNAMIC"))!=u"DYNAMIC") throw std::invalid_argument("buff effect is not DYNAMIC");
                TimedSkillEffect value;
                const auto type=catalog.find(rf::text(e,u"TYPE"));
                if(!type) throw std::invalid_argument("unknown buff effect TYPE");
                value.type=*type; value.name=rf::upper(rf::text(e,u"NAME")); value.source_skill=guid;
                value.exclusive=rf::flag(e,u"EXCLUSIVE");
                value.duration=finite_float(rf::number(e,u"DURATION",rf::number(a,u"DURATION",0)));
                if(!(value.duration>0)||value.duration>86400) throw std::invalid_argument("buff is not finite");
                value.remaining=value.duration;
                const auto channel=rf::upper(rf::text(e,u"DAMAGE_TYPE"));
                if(channel.empty()) value.damage_type=7;
                else if(channel==u"ALL") value.damage_type=6;
                else throw std::invalid_argument("typed temporary damage modifier is not implemented");
                if(rf::upper(rf::text(e,u"TYPE"))==u"UNIT THEME") {
                    value.unit_theme=rf::text(e,u"UNITTHEME");
                    if(value.unit_theme.empty()) throw std::invalid_argument("empty UNIT THEME");
                    result.visual_effects_pending=true;
                } else {
                    // These have live consumers already recovered in attack_action.cpp.
                    if(value.type!=0x0f&&value.type!=0x10&&value.type!=0x16&&value.type!=0x1d)
                        throw std::invalid_argument("temporary effect has no implemented consumer");
                    const auto& meta=effects.root.groups.at(value.type);
                    if(!rf::text(meta,u"GRAPH1").empty()||!rf::text(meta,u"GRAPH2").empty())
                        throw std::invalid_argument("graphed buff modifier requires a separate evaluator");
                    value.value=finite_float(rf::number(e,u"MIN",0));
                    const auto maximum=finite_float(rf::number(e,u"MAX",value.value));
                    if(maximum!=0&&maximum!=value.value) throw std::invalid_argument("random buff magnitude is not implemented");
                }
                result.effects.push_back(std::move(value));
            }
        }
    }
    if(result.effects.empty()) throw std::invalid_argument("empty self-buff program");
    validate_skill_checkpoint({{},result.effects});
    return result;
}
}
std::vector<SkillGrant> load_class_skills(const UnitDefinition& d) {
    std::vector<SkillGrant> result; std::set<std::u16string> seen;
    for(const auto& g:d.root.groups) if(rf::upper(g.name)==u"SKILL") {
        SkillGrant v{rf::upper(rf::text(g,u"NAME")),rf::integer(g,u"LEVEL",0),rf::integer(g,u"LEVEL_REQUIRED",0)};
        if(v.name.empty()||v.rank<0||v.rank>1000||v.level_required<0||!seen.insert(v.name).second)
            throw std::invalid_argument("invalid or duplicate class skill grant");
        result.push_back(std::move(v));
    }
    return result;
}
const SkillRank* SkillDefinition::rank(std::int32_t n) const noexcept {
    return n>0&&static_cast<std::size_t>(n)<=ranks.size()?&ranks[static_cast<std::size_t>(n-1)]:nullptr;
}
SkillCatalog::SkillCatalog(const PakArchive& pak) {
    const auto effects=parse_adm(pak.read_normalized(original_combat_inputs::effect_catalog_compiled_path));
    const AttackEffectCatalog catalog(effects);
    std::unordered_map<std::u16string,AdmGroup> affixes;
    std::vector<const PakArchive::Entry*> skills;
    for(const auto& entry:pak.entries()) {
        auto path=entry.name; for(auto& c:path) {if(c>='A'&&c<='Z')c+='a'-'A'; if(c=='\\')c='/';}
        if(path.size()<8||path.substr(path.size()-8)!=".dat.adm")continue;
        if(path.rfind("media/affixes/",0)==0) {
            auto doc=parse_adm(pak.read(entry)); auto name=rf::upper(rf::text(doc.root,u"NAME"));
            // Identical names elsewhere are ambiguous, never choose an arbitrary file.
            if(!name.empty()&&!affixes.emplace(name,std::move(doc.root)).second)
                affixes.at(name)=AdmGroup{};
        } else if(path.rfind("media/skills/",0)==0) skills.push_back(&entry);
    }
    for(const auto* entry:skills) {
        const auto doc=parse_adm(pak.read(*entry)); const auto& root=doc.root;
        SkillDefinition def; def.name=rf::upper(rf::text(root,u"NAME"));
        if(def.name.empty())continue;
        def.display_name=rf::text(root,u"DISPLAYNAME",rf::text(root,u"NAME")); def.source_path=entry->name;
        if(rf::field(root,u"UNIQUE_GUID"))def.guid=rf::guid(root,u"UNIQUE_GUID");
        def.animation=rf::ascii(rf::text(root,u"ANIMATION"));
        def.maximum_investment=rf::integer(root,u"MAX_INVEST_LEVEL",0);
        AdmGroup previous=root; previous.groups.clear();
        for(std::int32_t n=1;n<=1024;++n) {
            const auto digits=std::to_string(n); const auto key=u"LEVEL"+std::u16string(digits.begin(),digits.end());
            const auto* raw=rf::child(root,key); if(!raw)break;
            auto evaluated=merged(previous,*raw);
            SkillRank r; r.resource=evaluated; r.level_required=rf::integer(evaluated,u"LEVEL_REQUIRED",0);
            r.mana_cost=cost(evaluated);
            r.cooldown=static_cast<float>(rf::integer(evaluated,u"COOLDOWNMS",0))/1000.0F;
            r.monster_cooldown=static_cast<float>(rf::integer(evaluated,u"MONSTERCOOLDOWNMS",0))/1000.0F;
            r.speed=finite_float(rf::number(evaluated,u"SPEED",1));
            try {
                if(r.cooldown<0 || r.monster_cooldown<0 || !(r.speed>0) || r.mana_cost<0)
                    throw std::invalid_argument("invalid cast cost/cooldown/speed");
                r.self_buff=compile_self_buff(evaluated,*raw,affixes,catalog,effects,def.guid);
            }
            catch(const std::exception& e) { r.unavailable_reason=e.what(); }
            def.ranks.push_back(std::move(r));previous=std::move(evaluated);
        }
        if(!by_name_.emplace(def.name,definitions_.size()).second)throw std::invalid_argument("duplicate skill NAME");
        definitions_.push_back(std::move(def));
    }
}
const SkillDefinition* SkillCatalog::find(std::u16string_view name) const {
    const auto it=by_name_.find(rf::upper(std::u16string(name)));
    return it==by_name_.end()?nullptr:&definitions_[it->second];
}
float original_cast_speed(float pct,float resistance,float mult) {
    if(!std::isfinite(pct)||!std::isfinite(resistance)||!std::isfinite(mult)||mult<=0)throw std::invalid_argument("invalid cast speed input");
    if(pct<0)pct*=1.0F-std::clamp(resistance/100.0F,0.0F,1.0F);
    const auto speed=(pct/100.0F+1.0F)*mult;
    if(!std::isfinite(speed))throw std::invalid_argument("cast speed overflow");
    return std::max(0.2F,speed);
}
void validate_skill_checkpoint(const SkillCheckpoint& s) {
    if(s.skills.size()>1024||s.effects.size()>1024)throw std::invalid_argument("skill checkpoint exceeds limits");
    std::set<std::u16string> names;
    for(const auto& p:s.skills) {
        if(p.name.empty()||p.name.size()>1024||p.invested<0||p.invested>1024||!std::isfinite(p.cooldown)||p.cooldown<0||p.cooldown>86400||!names.insert(rf::upper(p.name)).second)
            throw std::invalid_argument("invalid skill progress");
    }
    for(const auto& e:s.effects) {
        if(e.name.size()>1024||e.unit_theme.size()>4096||e.type>=0x91||e.damage_type>7||!std::isfinite(e.value)||std::abs(e.value)>1e6F||
           !std::isfinite(e.duration)||e.duration<=0||e.duration>86400||!std::isfinite(e.remaining)||e.remaining<=0||e.remaining>e.duration)
            throw std::invalid_argument("invalid timed skill effect");
        if(e.unit_theme.empty()&&e.type!=0x0f&&e.type!=0x10&&e.type!=0x16&&e.type!=0x1d)
            throw std::invalid_argument("unsupported saved timed modifier");
    }
}
void add_timed_skill_effects(std::vector<TimedSkillEffect>& active,const std::vector<TimedSkillEffect>& incoming) {
    validate_skill_checkpoint({{},incoming});auto staged=active;
    for(auto effect:incoming) {
        if(effect.exclusive)staged.erase(std::remove_if(staged.begin(),staged.end(),[&](const auto& old){return old.name==effect.name&&old.type==effect.type;}),staged.end());
        effect.remaining=effect.duration;staged.push_back(std::move(effect));
    }
    validate_skill_checkpoint({{},staged});active.swap(staged);
}
AttackEffects skill_attack_effects(const std::vector<TimedSkillEffect>& active) {
    AttackEffects r;for(const auto& e:active)if(e.unit_theme.empty())r.add(e.type,e.value,e.damage_type);return r;
}
bool advance_timed_skill_effects(std::vector<TimedSkillEffect>& active,float seconds) {
    if(!std::isfinite(seconds)||seconds<0)throw std::invalid_argument("invalid buff clock");
    const auto before=active.size();
    for(auto& e:active)e.remaining=std::max(0.0F,e.remaining-seconds);
    active.erase(std::remove_if(active.begin(),active.end(),[](const auto& e){return e.remaining==0;}),active.end());
    return active.size()!=before;
}
void SelfBuffCast::start(std::uint64_t execution,std::u16string name,SelfBuffProgram program,AttackClip clip,float speed) {
    if(!clip||clip->event_keys.empty())throw std::invalid_argument("skill animation has no event keys");
    if(std::none_of(clip->event_keys.begin(),clip->event_keys.end(),[](const auto& k){return k.name=="HIT";}))throw std::invalid_argument("skill animation has no HIT");
    validate_skill_checkpoint({{},program.effects});
    AnimationEventPlayback next;next.start(execution,clip->skeleton_path,clip->duration,speed,clip->event_keys);
    std::vector<bool> consumed(clip->event_keys.size(),false);
    name_=std::move(name);program_=std::move(program);clip_=std::move(clip);playback_=std::move(next);consumed_=std::move(consumed);active_=true;
}
void SelfBuffCast::advance(float seconds){if(active_)playback_.advance(seconds);}
bool SelfBuffCast::consume(const AnimationEventOccurrence& event) {
    if(!active_||event.key.name!="HIT"||event.key_index>=consumed_.size()||consumed_[event.key_index])return false;
    const auto& issued=playback_.frame_events();
    const auto match=std::find_if(issued.begin(),issued.end(),[&](const auto& k){return k.execution_id==event.execution_id&&k.playback_generation==event.playback_generation&&
        k.source_clip==event.source_clip&&k.key_index==event.key_index&&k.key.name==event.key.name&&k.key.frame==event.key.frame&&k.clip_time_seconds==event.clip_time_seconds;});
    if(match==issued.end())return false;
    consumed_[event.key_index]=true;return true;
}
void SelfBuffCast::finish_frame() noexcept {if(active_&&playback_.finished())active_=false;}
void SelfBuffCast::cancel() noexcept {playback_.stop();active_=false;}
const char* skill_use_message(SkillUse s) noexcept {
    switch(s) {
    case SkillUse::started:return "CAST STARTED";case SkillUse::learned:return "SKILL RANK INCREASED";
    case SkillUse::unknown:return "UNKNOWN CLASS SKILL";case SkillUse::unsupported:return "UNSUPPORTED SKILL: NO POINTS OR MANA SPENT";
    case SkillUse::unlearned:return "SKILL NOT LEARNED";case SkillUse::maximum_rank:return "MAXIMUM INVESTMENT";
    case SkillUse::level_required:return "PLAYER LEVEL TOO LOW";case SkillUse::no_points:return "NO SKILL POINTS";
    case SkillUse::no_mana:return "NOT ENOUGH MANA";case SkillUse::dead:return "PLAYER IS DEAD";
    case SkillUse::busy:return "ACTION IN PROGRESS";case SkillUse::cooldown:return "SKILL COOLING DOWN";
    case SkillUse::missing_animation:return "ORIGINAL CAST ANIMATION UNAVAILABLE";
    }return "UNKNOWN SKILL RESULT";
}
} // namespace torchlight
