#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Inventory.h"
#include "SkillManager.h"
#include "Skill.h"
#include "Affix.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldProcs,(CCharacter*,EEFFECT_TYPE,CBaseUnit*),"_ZN10CCharacter12executeProcsE12EEFFECT_TYPEP9CBaseUnit")
extern "C" void newProcs(CCharacter*,EEFFECT_TYPE,CBaseUnit*) __asm__("_ZN10CCharacter12executeProcsE12EEFFECT_TYPEP9CBaseUnit");
TL_ORIGINAL(void,oldDamageEffects,(CCharacter*,CCharacter*,float,int(*)[2],unsigned,bool),"_ZN10CCharacter18applyDamageEffectsEPS_fPA2_ijb")
extern "C" void newDamageEffects(CCharacter*,CCharacter*,float,int(*)[2],unsigned,bool) __asm__("_ZN10CCharacter18applyDamageEffectsEPS_fPA2_ijb");
TL_FUNCTION(cp_has,"_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(cp_randint,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(cp_value,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(cp_skill,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(cp_execute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(cp_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cp_inventory,"_ZN10CInventory12executeProcsE12EEFFECT_TYPEP9CBaseUnit")
TL_FUNCTION(cp_random,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(cp_player,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(cp_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(cp_affix,"_ZN14CEffectManager8getAffixERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cp_addaffix,"_ZN9CBaseUnit8addAffixERKSbIwSt11char_traitsIwESaIwEEjPS_f")
namespace {
void initStrings(){
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476068),8);if(!p)new(reinterpret_cast<void*>(0x1476068))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476060),8);if(!p)new(reinterpret_cast<void*>(0x1476060))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14781e8),8);if(!p)new(reinterpret_cast<void*>(0x14781e8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14781e0),8);if(!p)new(reinterpret_cast<void*>(0x14781e0))std::string;}
}
struct Case{unsigned op,index;};struct State{Case c;autotest::Capture*out;CCharacter*self,*target;CEffect*effects[8];CEffectManager*manager;CSkillManager*skills;CSkill*skill;CInventory*inventory;Ogre::SceneNode*node;Ogre::Quaternion orientation;CAffix*affixes[2];unsigned rng;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float n){active->out->add(&n,4);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned effectId(CEffect*e){for(unsigned i=0;i<8;++i)if(active->effects[i]==e)return i;return 99;}unsigned id(CBaseUnit*p){return p==active->self?1:p==active->target?2:p==NULL?0:99;}
bool has(CBaseUnit*p,EEFFECT_TYPE t){num(1);num(id(p));num(t);return hash(1)%3!=0;}int randInt(int a,int b){num(2);num(a);num(b);unsigned v=hash(100+active->rng++)%101;num(v);return v;}float value(CEffect*e,EEFFECT_VALUES n){num(3);unsigned i=effectId(e);num(i);num(n);const float chances[]={-1,0,25,50,75,100,101,std::numeric_limits<float>::quiet_NaN()};return chances[hash(10+i)%8];}CSkill*getSkill(CSkillManager*p,const std::wstring&s,int level){num(4);num(p==active->skills);wide(s);num(level);return hash(200+active->rng)%3?active->skill:NULL;}CSkill*execute(CSkillManager*p,CSkill*sk,CBaseUnit*caster,ESKILL_ACTIVATION_TYPE activation,const Ogre::Vector3&from,const Ogre::Quaternion&q,const Ogre::Vector3&to,CBaseUnit*target){num(5);num(p==active->skills);num(sk==active->skill);num(id(caster));num(activation);vec(from);fp(q.w);fp(q.x);fp(q.y);fp(q.z);vec(to);num(id(target));return sk;}Ogre::Vector3 position(CPositionableObject*p,bool abs){num(6);num(id(static_cast<CBaseUnit*>(p)));num(abs);return Ogre::Vector3(float(active->rng++),id(static_cast<CBaseUnit*>(p))*.25f,-3.f);}const Ogre::Quaternion&orientation(Ogre::SceneNode*p){num(7);num(p==active->node);return active->orientation;}void inventory(CInventory*p,EEFFECT_TYPE t,CBaseUnit*target){num(8);num(p==active->inventory);num(t);num(id(target));}float random(float a,float b){num(9);fp(a);fp(b);float v=a+(b-a)*float(hash(300+active->rng++)%11)*.1f;fp(v);return v;}bool player(CBaseUnit*p){num(10);num(id(p));return hash(400+active->rng++)&1;}bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(11);num(id(p));num(t);return hash(410)&1;}CAffix*affix(CEffectManager*p,const std::wstring&s){num(12);num(p==active->manager);wide(s);return hash(411)%3?active->affixes[0]:NULL;}CAffix*addAffix(CBaseUnit*p,const std::wstring&s,unsigned level,CBaseUnit*source,float scale){num(13);num(id(p));wide(s);num(level);num(id(source));fp(scale);return hash(412)%3?active->affixes[1]:NULL;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initStrings();s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.target=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.inventory=static_cast<CInventory*>(autotest::allocate(sizeof(CInventory)));s.skills=static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager)));s.skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.orientation=Ogre::Quaternion(.5,.25,-.25,.75);void**vt=static_cast<void**>(autotest::allocate(0x100));vt[0xc8/8]=reinterpret_cast<void*>(&orientation);*reinterpret_cast<void***>(s.node)=vt;s.self->m_pSceneNode=s.node;s.manager=new CEffectManager(NULL);s.self->m_pEffectManager=s.manager;s.self->m_pSkillManager=hash(2)%4?s.skills:NULL;s.self->m_pInventory=hash(3)%4?s.inventory:NULL;s.self->m_procTime=-17;const int types[]={74,75,76,81,105,73,77,0,145};EEFFECT_TYPE type=static_cast<EEFFECT_TYPE>(types[c.index%9]);for(unsigned i=0;i<8;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(hash(20+i)&1?int(type):105),false,EFFECT_ACTIVATION_PASSIVE,0,0,0,false);s.effects[i]=e;e->m_iLevel=hash(30+i)%6;e->m_sName=i&1?L"ProcSkill Ж":L"";}for(unsigned g=0;g<2;++g)for(unsigned i=0;i<hash(40+g)%7;++i)s.manager->m_Effects[g].add(s.effects[(i+g)%8]);
if(c.op==0){typedef void(*F)(CCharacter*,EEFFECT_TYPE,CBaseUnit*);F f=ours?newProcs:oldProcs;if(!autotest::beginInvocation(out,f))return;f(s.self,type,hash(50)&1?s.target:NULL);out.callCompleted=1;fp(s.self->m_procTime);}
else{for(unsigned i=0;i<2;++i){s.affixes[i]=static_cast<CAffix*>(autotest::allocate(sizeof(CAffix)));s.affixes[i]->m_fDuration=-100-i;}if(hash(51)%3==0)s.self->m_pEffectManager=NULL;s.target->m_iUnitLevel=hash(52);int damage[9][2];unsigned count=hash(53)%10;for(unsigned i=0;i<count;++i){damage[i][0]=hash(60+i)%7;damage[i][1]=int(hash(70+i)%401)-100;}for(unsigned i=0;i<7;++i)s.self->m_damageDefense[i]=int(hash(80+i)%200)-100;const float totals[]={-1,0,1,25,std::numeric_limits<float>::quiet_NaN()};typedef void(*F)(CCharacter*,CCharacter*,float,int(*)[2],unsigned,bool);F f=ours?newDamageEffects:oldDamageEffects;if(!autotest::beginInvocation(out,f))return;f(s.self,hash(54)%9?s.target:NULL,totals[hash(55)%5],damage,count,hash(56)&1);out.callCompleted=1;for(unsigned i=0;i<2;++i)fp(s.affixes[i]->m_fDuration);}
s.manager->m_Effects[0].clear();s.manager->m_Effects[1].clear();for(unsigned i=0;i<8;++i)delete s.effects[i];delete s.manager;}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address){detour::Set h;TL_REDIRECT(h,cp_has,&has);TL_REDIRECT(h,cp_randint,&randInt);TL_REDIRECT(h,cp_value,&value);TL_REDIRECT(h,cp_skill,&getSkill);TL_REDIRECT(h,cp_execute,&execute);TL_REDIRECT(h,cp_position,&position);TL_REDIRECT(h,cp_inventory,&inventory);TL_REDIRECT(h,cp_random,&random);TL_REDIRECT(h,cp_player,&player);TL_REDIRECT(h,cp_isa,&isa);TL_REDIRECT(h,cp_affix,&affix);TL_REDIRECT(h,cp_addaffix,&addAffix);if(h.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<8192;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    procdamage op%u seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",op,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=8192||coverage.different||coverage.missing;}
}
TL_TEST(character_combat_procs){return run(host,0,"character_combat_procs",0x810730);}
TL_TEST(character_combat_damage_effects){return run(host,1,"character_combat_damage_effects",0x810b30);}
