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
#include "Level.h"
#include "SoundBank.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(bool,oldApplyEffect,(CCharacter*,CCharacter*,CBaseUnit*,CEffect*),"_ZN10CCharacter17applyEffectOnUnitEPS_P9CBaseUnitP7CEffect")
extern "C" bool newApplyEffect(CCharacter*,CCharacter*,CBaseUnit*,CEffect*) __asm__("_ZN10CCharacter17applyEffectOnUnitEPS_P9CBaseUnitP7CEffect");
TL_FUNCTION(ca_instant,"_ZN10CCharacter18applyInstantEffectEP7CEffect")
TL_FUNCTION(ca_randint,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(ca_value,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(ca_copy,"_ZN9CBaseUnit10copyEffectEPS_P7CEffect")
TL_FUNCTION(ca_effectvalue,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(ca_random,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(ca_interrupt,"_ZN10CCharacter9interruptEb")
TL_FUNCTION(ca_player,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(ca_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(ca_sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(ca_destination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(ca_enemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(ca_area,"_ZN6CLevel17reactToAreaDamageEP10CCharacterS1_")
TL_FUNCTION(ca_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ca_calculate,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
namespace {
void initStrings(){
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476068),8);if(!p)new(reinterpret_cast<void*>(0x1476068))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476060),8);if(!p)new(reinterpret_cast<void*>(0x1476060))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479460),8);if(!p)new(reinterpret_cast<void*>(0x1479460))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479468),8);if(!p)new(reinterpret_cast<void*>(0x1479468))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c348),8);if(!p)new(reinterpret_cast<void*>(0x147c348))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c340),8);if(!p)new(reinterpret_cast<void*>(0x147c340))std::string;}
}
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;bool observing;CCharacter*self,*source,*target,*owner;CEffect*effect,*copied;CLevel*level;CSoundBank*sound;unsigned rng;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){if(active->observing)active->out->add(&n,4);}void fp(float n){if(active->observing)active->out->add(&n,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(CBaseUnit*p){return p==active->self?1:p==active->source?2:p==active->target?3:p==active->owner?4:p==NULL?0:99;}float scalar(unsigned n){const float vs[]={-1000,-900,-1,0,.25f,.5f,1,20,50,100,101,std::numeric_limits<float>::quiet_NaN()};return vs[hash(n)%12];}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual bool isEffectValidForUnit(CCharacter*s,CBaseUnit*t,CEffect*e){num(1);num(id(s));num(id(t));num(e==active->effect);return hash(1)%5!=0;}virtual void reactToDamage(CCharacter*p,bool b){num(2);num(id(p));num(b);if(hash(2)%3==0)m_eAIState=static_cast<EAIState>(hash(3)%3);}virtual void setAIState(EAIState s){num(3);num(s);m_eAIState=s;}virtual void die(CCharacter*k,const Ogre::Vector3*d,float f,bool b){num(4);num(id(k));num(d==NULL);fp(f);num(b);m_eAIState=static_cast<EAIState>(6);}};
void instant(CCharacter*,CEffect*p){num(5);num(p==active->effect);p->m_fValueC0=-33;}int rngInt(int a,int b){num(6);num(a);num(b);unsigned x=hash(100+active->rng++)%unsigned(b-a+1)+a;num(x);return x;}float value(CEffect*p,EEFFECT_VALUES n){num(7);num(p==active->effect);num(n);return scalar(4);}CEffect*copy(CBaseUnit*p,CBaseUnit*source,CEffect*e){num(8);num(id(p));num(id(source));num(e==active->effect);return hash(5)%4?active->copied:NULL;}float effectValue(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES d){num(9);num(id(p));num(t);num(d);return scalar(6+unsigned(t));}float rngFloat(float a,float b){num(10);fp(a);fp(b);float v=a+(b-a)*float(hash(200+active->rng++)%11)*.1f;fp(v);return v;}void interrupt(CCharacter*,bool b){num(11);num(b);}bool player(CBaseUnit*){num(12);return hash(7)&1;}Ogre::Vector3 position(CPositionableObject*p,bool b){num(13);num(id(static_cast<CBaseUnit*>(p)));num(b);return p->m_vPosition;}int sound(CSoundBank*p,int n,Ogre::SceneNode*,float a,float b,bool c){num(14);num(p==active->sound);num(n);fp(a);fp(b);num(c);return 0;}void destination(CCharacter*,CLevel&l,float x,float z){num(15);num(&l==active->level);fp(x);fp(z);}bool enemy(CCharacter*,CCharacter*p){num(16);num(id(p));return hash(8)&1;}void area(CLevel*p,CCharacter*a,CCharacter*b){num(17);num(p==active->level);num(id(a));num(id(b));}bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(18);num(id(p));num(t);return hash(9)&1;}float calculate(CEffect*p,CEffect::ECALCULATETYPES t){num(19);num(p==active->copied);num(t);return p->m_fValueC0;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initStrings();s.self=new Character;s.source=new CCharacter(NULL);s.target=new CCharacter(NULL);s.owner=new CCharacter(NULL);s.sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));r->m_pLevel=hash(10)%5?s.level:NULL;s.self->m_pResourceManager=hash(11)%5?r:NULL;s.self->m_levelSound=hash(12)&1?s.sound:NULL;const int types[]={7,8,47,56,63,64,79,80,106,107,108,109,110,124,128,144,65};s.effect=new CEffect(static_cast<EEFFECT_TYPE>(types[c.index%17]),false,static_cast<EEFFECT_ACTIVATION>(hash(13)%5),0,0,0,false);s.effect->m_fValue24=scalar(14);s.effect->m_fValueC0=scalar(15);s.effect->m_Owner.setObject(hash(16)%4?s.owner:NULL);s.copied=new CEffect(s.effect);for(unsigned i=0;i<4;++i)s.copied->m_values[i]=scalar(20+i);s.copied->m_modifierFlag32=hash(25)&1;s.self->m_eAIState=static_cast<EAIState>(hash(26)%5==0?40:hash(27)%11);s.self->m_alwaysActive=hash(28)&1;s.self->m_champion=hash(29)&1;s.self->m_value6D0=hash(30);for(unsigned i=0;i<8;++i)s.self->m_damageDefense[i]=int(hash(31+i));s.self->m_pathGraceTime=scalar(40);s.self->m_movement=Ogre::Vector3(4,5,6);s.self->m_vPosition=Ogre::Vector3(float(hash(41)%8),2,-3);s.owner->m_vPosition=hash(42)&1?s.self->m_vPosition:Ogre::Vector3(-1,2,3);
typedef bool(*F)(CCharacter*,CCharacter*,CBaseUnit*,CEffect*);F f=ours?newApplyEffect:oldApplyEffect;if(!autotest::beginInvocation(out,f))return;s.observing=true;num(f(s.self,s.source,hash(43)%4?s.target:NULL,hash(44)%13?s.effect:NULL));out.callCompleted=1;num(s.self->m_eAIState);vec(s.self->m_movement);fp(s.effect->m_fValue24);fp(s.effect->m_fValueC0);for(unsigned i=0;i<4;++i)fp(s.copied->m_values[i]);num(s.copied->m_modifierFlag32);fp(s.copied->m_fValueC0);s.observing=false;delete s.copied;delete s.effect;}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(character_combat_apply_effect){detour::Set h;TL_REDIRECT(h,ca_instant,&instant);TL_REDIRECT(h,ca_randint,&rngInt);TL_REDIRECT(h,ca_value,&value);TL_REDIRECT(h,ca_copy,&copy);TL_REDIRECT(h,ca_effectvalue,&effectValue);TL_REDIRECT(h,ca_random,&rngFloat);TL_REDIRECT(h,ca_interrupt,&interrupt);TL_REDIRECT(h,ca_player,&player);TL_REDIRECT(h,ca_position,&position);TL_REDIRECT(h,ca_sound,&sound);TL_REDIRECT(h,ca_destination,&destination);TL_REDIRECT(h,ca_enemy,&enemy);TL_REDIRECT(h,ca_area,&area);TL_REDIRECT(h,ca_isa,&isa);TL_REDIRECT(h,ca_calculate,&calculate);if(h.failed())return 1;autotest::Coverage coverage("character_combat_apply_effect",0x8435c0);for(unsigned i=0;i<16384;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    applyEffect seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=16384||coverage.different||coverage.missing;}
