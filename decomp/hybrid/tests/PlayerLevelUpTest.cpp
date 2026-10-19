#include <string>
#include <vector>
#include <map>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "Particle.h"
#include "SoundBank.h"
#include "Inventory.h"
#include "GameUI.h"
#include "StringTranslate.h"
#include "ResourceManager.h"
#include "Achievements.h"
#include "Achievement.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerLevelUp,(CPlayer*),"_ZN7CPlayer7levelUpEv")
extern "C" void newPlayerLevelUp(CPlayer*) __asm__("_ZN7CPlayer7levelUpEv");
TL_FUNCTION(plu_base,"_ZN10CCharacter7levelUpEv")
TL_FUNCTION(plu_playing,"_ZN10CSoundBank11bankPlayingEi")
TL_FUNCTION(plu_play,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(plu_global,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(plu_start,"_ZN9CParticle5StartEv")
TL_FUNCTION(plu_translateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(plu_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(plu_ui,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(plu_big,"_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(plu_small,"_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(plu_tip,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(plu_refresh,"_ZN10CInventory15refreshEquippedEv")
TL_FUNCTION(plu_recalc,"_ZN10CInventory34forceRecalculationOfEquipmentStatsEv")
TL_FUNCTION(plu_armor,"_ZN7CPlayer21calculateNaturalArmorEv")
TL_FUNCTION(plu_hp,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(plu_mana,"_ZN10CCharacter7maxManaEv")
TL_FUNCTION(plu_achievements,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(plu_get,"_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(plu_complete,"_ZN12CAchievement13forceCompleteEv")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CParticle*particle;Ogre::SceneNode*selfNode,*particleNode,*parent;CGameUI*ui;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float f){active->out->add(&f,4);}void wide(const std::wstring&w){num(w.size());active->out->add(w.data(),w.size()*4);}
void base(CCharacter*p){num(1);num(p==active->self);++p->m_iUnitLevel;}bool playing(CSoundBank*,int i){num(2);num(i);return hash(1)&1;}int play(CSoundBank*,int i,Ogre::SceneNode*n,float a,float b,bool flag){num(3);num(i);num(n==active->selfNode);fp(a);fp(b);num(flag);return 7;}void global(CSoundBank*,int i,float a,float b){num(4);num(i);fp(a);fp(b);}void start(CParticle*p){num(5);num(p==active->particle);}Ogre::Node*parent(Ogre::SceneNode*p){num(6);num(p==active->particleNode);return p->mParent;}Ogre::Node*remove(Ogre::SceneNode*p,Ogre::Node*n){num(7);num(p==active->parent);num(n==active->particleNode);return n;}void add(Ogre::SceneNode*p,Ogre::Node*n){num(8);num(p==active->selfNode);num(n==active->particleNode);}void position(CParticle*p,float x,float y,float z){num(9);num(p==active->particle);fp(x);fp(y);fp(z);p->m_vPosition=Ogre::Vector3(x,y,z);}
CStringTranslate*translator(){num(10);return reinterpret_cast<CStringTranslate*>(0x11223300);}std::wstring translate(CStringTranslate*,const wchar_t*p){num(11);std::wstring s(p);wide(s);return hash(2)%7?s+L" переведено":L"";}CGameUI*ui(CResourceManager*){num(12);return active->ui;}void big(CGameUI*,std::wstring s,float dt){num(13);wide(s);fp(dt);}void small(CGameUI*,std::wstring s,float dt){num(14);wide(s);fp(dt);}void tip(CGameUI*,EContextTip t){num(15);num(t);}void refresh(CInventory*){num(16);}void recalc(CInventory*){num(17);}void hpCalc(CCharacter*p){num(18);p->m_maxHPBase=123;}void manaCalc(CCharacter*p){num(19);p->m_maxManaBase=37;}void armor(CPlayer*p){num(20);p->m_naturalArmor=5;}int hp(CCharacter*p){num(21);return p->m_maxHPBase+int(hash(3)%10);}int mana(CCharacter*p){num(22);return p->m_maxManaBase+int(hash(4)%10);}CAchievements*achievements(){num(23);return reinterpret_cast<CAchievements*>(0x11224400);}CAchievement*get(CAchievements*,EACHIEVEMENTS t){num(24);num(t);return reinterpret_cast<CAchievement*>(uintptr_t(t)+0x11225500);}void complete(CAchievement*p){num(25);num(uintptr_t(p)-0x11225500);}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.particle=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));s.selfNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.particleNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.parent=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));CPlayer&p=*s.self;p.m_levelUpParticle=hash(5)%3?s.particle:NULL;p.m_levelSound=hash(6)%3?static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank))):NULL;p.m_pInventory=hash(7)%3?static_cast<CInventory*>(autotest::allocate(sizeof(CInventory))):NULL;p.m_pResourceManager=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));p.m_pSceneNode=s.selfNode;s.particle->m_pSceneNode=s.particleNode;s.particleNode->mParent=hash(8)&1?s.parent:NULL;p.m_fBaseUnitValue194=float(hash(9)%50)*.125f;const unsigned levels[]={0,1,63,64,65,98,99,100,0xffffffff};p.m_iUnitLevel=levels[c.index%9];void**v=static_cast<void**>(autotest::allocate(0x440));v[0x410/8]=reinterpret_cast<void*>(&manaCalc);v[0x418/8]=reinterpret_cast<void*>(&hpCalc);*reinterpret_cast<void***>(&p)=v;void**pv=static_cast<void**>(autotest::allocate(0x100));pv[0x58/8]=reinterpret_cast<void*>(&position);*reinterpret_cast<void***>(s.particle)=pv;void**nv=static_cast<void**>(autotest::allocate(0x200));nv[0xc0/8]=reinterpret_cast<void*>(&parent);nv[0x1e0/8]=reinterpret_cast<void*>(&remove);nv[0x1a8/8]=reinterpret_cast<void*>(&add);*reinterpret_cast<void***>(s.particleNode)=nv;*reinterpret_cast<void***>(s.parent)=nv;*reinterpret_cast<void***>(s.selfNode)=nv;typedef void(*F)(CPlayer*);F f=ours?newPlayerLevelUp:oldPlayerLevelUp;if(!autotest::beginInvocation(out,f))return;f(&p);f(&p);out.callCompleted=1;num(p.m_iUnitLevel);fp(p.m_fHPFloat);fp(p.m_fManaFloat);num(p.m_maxHPBase);num(p.m_maxManaBase);num(p.m_naturalArmor);}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_level_up){detour::Set h;TL_REDIRECT(h,plu_base,&base);TL_REDIRECT(h,plu_playing,&playing);TL_REDIRECT(h,plu_play,&play);TL_REDIRECT(h,plu_global,&global);TL_REDIRECT(h,plu_start,&start);TL_REDIRECT(h,plu_translateSingleton,&translator);TL_REDIRECT(h,plu_translate,&translate);TL_REDIRECT(h,plu_ui,&ui);TL_REDIRECT(h,plu_big,&big);TL_REDIRECT(h,plu_small,&small);TL_REDIRECT(h,plu_tip,&tip);TL_REDIRECT(h,plu_refresh,&refresh);TL_REDIRECT(h,plu_recalc,&recalc);TL_REDIRECT(h,plu_armor,&armor);TL_REDIRECT(h,plu_hp,&hp);TL_REDIRECT(h,plu_mana,&mana);TL_REDIRECT(h,plu_achievements,&achievements);TL_REDIRECT(h,plu_get,&get);TL_REDIRECT(h,plu_complete,&complete);if(h.failed())return 1;autotest::Coverage coverage("all_player_level_up",0x8f9ad0);for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player levelup seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
