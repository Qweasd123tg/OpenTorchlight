#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#include <CEGUIcolour.h>
#define private public
#define protected public
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Console.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "StringTranslate.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(int,oldMitigation,(CCharacter*,int,EDAMAGE_TYPES,int,float),"_ZN10CCharacter12modifyDamageEi13EDAMAGE_TYPESif")
extern "C" int newMitigation(CCharacter*,int,EDAMAGE_TYPES,int,float) __asm__("_ZN10CCharacter12modifyDamageEi13EDAMAGE_TYPESif");
TL_FUNCTION(cm_ac,"_ZN10CCharacter2ACEv")
TL_FUNCTION(cm_minac,"_ZN10CCharacter9minimumACEv")
TL_FUNCTION(cm_defense,"_ZN10CCharacter13damageDefenseE13EDAMAGE_TYPES")
TL_FUNCTION(cm_percent,"_ZN10CCharacter20damageDefensePercentE13EDAMAGE_TYPES")
TL_FUNCTION(cm_rand,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(cm_has,"_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(cm_value,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(cm_calculate,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
TL_FUNCTION(cm_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cm_text,"_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
TL_FUNCTION(cm_sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(cm_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(cm_setting,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(cm_console,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cm_translator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(cm_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
namespace {
void initStrings(){
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476068),8);if(!p)new(reinterpret_cast<void*>(0x1476068))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476060),8);if(!p)new(reinterpret_cast<void*>(0x1476060))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14781e8),8);if(!p)new(reinterpret_cast<void*>(0x14781e8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14781e0),8);if(!p)new(reinterpret_cast<void*>(0x14781e0))std::string;}
}
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CCharacter*self;CEffect*effects[8];CEffectManager*manager;CGameUI*ui;Ogre::SceneNode*node;CSoundBank*sound;CMasterResourceManager*master;CSettings*settings;CConsole*console;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float n){active->out->add(&n,4);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(CEffect*e){for(unsigned i=0;i<8;++i)if(active->effects[i]==e)return i;return 99;}float scalar(unsigned n){const float v[]={-1000,-900,-1,0,.5f,1,5,20,100,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};return v[hash(n)%11];}
int ac(CCharacter*){num(1);return int(hash(1)%300)-50;}int minimum(CCharacter*){num(2);return int(hash(2)%100)-50;}int defense(CCharacter*,EDAMAGE_TYPES t){num(3);num(t);return int(hash(3)%300)-150;}int percent(CCharacter*,EDAMAGE_TYPES t){num(4);num(t);return int(hash(4)%401)-200;}int rngInt(int a,int b){num(5);num(a);num(b);return a+int(hash(5)%11)*(b-a)/10;}bool has(CBaseUnit*,EEFFECT_TYPE t){num(6);num(t);return hash(6)%3!=0;}float value(CEffect*e,EEFFECT_VALUES v){num(7);num(id(e));num(v);return e->m_fValueC4;}float calculate(CEffect*e,CEffect::ECALCULATETYPES t){num(8);num(id(e));num(t);fp(e->m_fValueC4);e->m_fValueC0=e->m_fValueC4;return e->m_fValueC0;}Ogre::Vector3 position(CPositionableObject*,bool abs){num(9);num(abs);return Ogre::Vector3(2,-1,.25f);}void text(CGameUI*p,const Ogre::Vector3&v,const std::string&s,float a,float b,CEGUI::colour first,CEGUI::colour second){num(10);num(p==active->ui);vec(v);num(s.size());active->out->add(s.data(),s.size());fp(a);fp(b);fp(first.getRed());fp(first.getGreen());fp(first.getBlue());fp(first.getAlpha());fp(second.getRed());fp(second.getGreen());fp(second.getBlue());fp(second.getAlpha());}int playSound(CSoundBank*p,int index,Ogre::SceneNode*n,float a,float b,bool flag){num(11);num(p==active->sound);num(index);num(n==active->node);fp(a);fp(b);num(flag);return 0;}CMasterResourceManager*master(){num(12);return active->master;}int setting(CDynamicPropertyFile*p,unsigned key){num(13);num(p==active->settings);num(key);return hash(7)%3-1;}void console(CConsole*p,std::wstring s){num(14);num(p==active->console);wide(s);}CStringTranslate*translator(){num(15);return reinterpret_cast<CStringTranslate*>(0x12345600);}std::wstring translate(CStringTranslate*,const wchar_t*s){num(16);wide(s);return hash(8)%5?std::wstring(s)+L" Ж":L"";}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initStrings();s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.master=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.settings=static_cast<CSettings*>(autotest::allocate(sizeof(CSettings)));s.console=static_cast<CConsole*>(autotest::allocate(sizeof(CConsole)));s.master->m_pSettings=s.settings;s.ui->m_console=s.console;CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));CLevel*l=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));CGameClient*g=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));r->m_pLevel=l;l->m_pGameClient=g;g->m_pGameUI=s.ui;s.self->m_pResourceManager=r;s.self->m_pSceneNode=s.node;s.self->m_levelSound=hash(9)&1?s.sound:NULL;s.manager=new CEffectManager(NULL);s.self->m_pEffectManager=s.manager;
for(unsigned i=0;i<8;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(hash(20+i)%3?122:1),false,EFFECT_ACTIVATION_PASSIVE,0,0,0,false);s.effects[i]=e;e->m_eDamageType=static_cast<EDAMAGE_TYPES>(hash(30+i)%8);e->m_bDead=hash(40+i)%5==0;e->m_fValue24=scalar(50+i);e->m_fRemainingDuration=scalar(60+i);e->m_fValueC4=scalar(70+i);e->m_fValueC0=scalar(80+i);}for(unsigned g=0;g<2;++g)for(unsigned i=0;i<hash(90+g)%7;++i)s.manager->m_Effects[g].add(s.effects[(i+g*3)%8]);int damages[]={-100,-1,0,1,5,20,100,500};int damage=damages[hash(10)%8];int total=damages[hash(11)%8];EDAMAGE_TYPES type=static_cast<EDAMAGE_TYPES>(hash(12)%8);float scale=scalar(13);typedef int(*F)(CCharacter*,int,EDAMAGE_TYPES,int,float);F f=ours?newMitigation:oldMitigation;if(!autotest::beginInvocation(out,f))return;num(f(s.self,damage,type,total,scale));num(f(s.self,damage,type,total,scale));out.callCompleted=1;for(unsigned i=0;i<8;++i){CEffect*e=s.effects[i];fp(e->m_fValueC4);fp(e->m_fValueC0);fp(e->m_fRemainingDuration);num(e->m_bDead);}s.manager->m_Effects[0].clear();s.manager->m_Effects[1].clear();for(unsigned i=0;i<8;++i)delete s.effects[i];delete s.manager;}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(character_combat_modify_damage){detour::Set h;TL_REDIRECT(h,cm_ac,&ac);TL_REDIRECT(h,cm_minac,&minimum);TL_REDIRECT(h,cm_defense,&defense);TL_REDIRECT(h,cm_percent,&percent);TL_REDIRECT(h,cm_rand,&rngInt);TL_REDIRECT(h,cm_has,&has);TL_REDIRECT(h,cm_value,&value);TL_REDIRECT(h,cm_calculate,&calculate);TL_REDIRECT(h,cm_position,&position);TL_REDIRECT(h,cm_text,&text);TL_REDIRECT(h,cm_sound,&playSound);TL_REDIRECT(h,cm_master,&master);TL_REDIRECT(h,cm_setting,&setting);TL_REDIRECT(h,cm_console,&console);TL_REDIRECT(h,cm_translator,&translator);TL_REDIRECT(h,cm_translate,&translate);if(h.failed())return 1;autotest::Coverage coverage("character_combat_modify_damage",0x837c00);for(unsigned i=0;i<16384;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    mitigation seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=16384||coverage.different||coverage.missing;}
