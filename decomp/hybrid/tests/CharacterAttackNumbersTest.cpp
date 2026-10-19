#include <string>
#include <vector>
#include <new>
#include <limits>
#include <CEGUIcolour.h>
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "AttackDescription.h"
#include "Inventory.h"
#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "SoundBank.h"
#include "StringTranslate.h"
#include "MasterResourceManager.h"
#include "CameraControl.h"
#include "CameraShake.h"
#include "Graph.h"
#include "GraphManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(int,originalMax,(CCharacter*,CAttackDescription*,CCharacter*),"_ZN10CCharacter9maxDamageEP18CAttackDescriptionPS_")
extern "C" int candidateMax(CCharacter*,CAttackDescription*,CCharacter*) __asm__("_ZN10CCharacter9maxDamageEP18CAttackDescriptionPS_");
TL_ORIGINAL(bool,originalCritical,(CCharacter*,CCharacter*),"_ZN10CCharacter12rollCriticalEPS_")
extern "C" bool candidateCritical(CCharacter*,CCharacter*) __asm__("_ZN10CCharacter12rollCriticalEPS_");
TL_ORIGINAL(void,originalFame,(CCharacter*,CLevel&,CCharacter*,int,bool),"_ZN10CCharacter9awardFameER6CLevelPS_ib")
extern "C" void candidateFame(CCharacter*,CLevel&,CCharacter*,int,bool) __asm__("_ZN10CCharacter9awardFameER6CLevelPS_ib");
TL_FUNCTION(an_effect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(an_equipmentEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE16EEQUIP_LOCATIONS13EDAMAGE_TYPES")
TL_FUNCTION(an_strength,"_ZN10CCharacter8strengthEv")
TL_FUNCTION(an_dexterity,"_ZN10CCharacter9dexterityEv")
TL_FUNCTION(an_select,"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(an_equipped,"_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(an_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(an_alignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(an_random,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(an_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(an_text,"_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
TL_FUNCTION(an_sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(an_translator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(an_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(an_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(an_gate,"_ZN22CMasterResourceManager8fameGateEi")
TL_FUNCTION(an_maxfame,"_ZN22CMasterResourceManager15getMaxFameLevelEv")
TL_FUNCTION(an_camera,"_ZN16CResourceManager16getCameraControlEv")
TL_FUNCTION(an_graphManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(an_graph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case {unsigned op,index;};struct State{Case c;autotest::Capture*out;bool observing;CCharacter*self,*master,*grand,*target;CEquipment*gear[2];CAttackDescription*attacks[2];CInventory*inventory;CResourceManager*resources;CLevel*level;CGameClient*client;CGameUI*ui;CSoundBank*sound;CCameraControl*camera;CMasterResourceManager*manager;CGraph*graph;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){if(active->observing)active->out->add(&n,4);}void fp(float n){if(active->observing)active->out->add(&n,4);}void wide(const std::wstring&s){num(s.size());if(active->observing)active->out->add(s.data(),s.size()*4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(CBaseUnit*p){return p==active->self?1:p==active->master?2:p==active->grand?3:p==active->target?4:p==active->gear[0]?5:p==active->gear[1]?6:p==NULL?0:99;}float scalar(unsigned n){const float a[]={-100,-10,-1,-.01f,0,.01f,.5f,1,20,100,std::numeric_limits<float>::quiet_NaN()};return a[hash(n)%11];}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual void fameUp(){num(1);num(id(this));++m_fameLevel;}};
void initStrings(){const unsigned long a[]={0x1479460,0x147c340,0x1480a40,0x1484120,0x145dd00,0x14e5948,0x14f6ec0};for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(a[i]),8);if(!p)new(reinterpret_cast<void*>(a[i]))std::string;}const unsigned long b[]={0x1479468,0x147c348,0x1480a48,0x1484128,0x145dd08,0x14e5950,0x14f6ec8};for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(b[i]),8);if(!p)new(reinterpret_cast<void*>(b[i]))std::wstring;}}
float effect(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES d){num(2);num(id(p));num(t);num(d);return scalar(unsigned(t)+id(p)*10);}
float equipmentEffect(CCharacter*p,EEFFECT_TYPE t,EEQUIP_LOCATIONS l,EDAMAGE_TYPES d){num(3);num(id(p));num(t);num(l);num(d);return scalar(100+unsigned(t));}
int strength(CCharacter*p){num(4);num(id(p));return int(hash(1)%200)-20;}int dexterity(CCharacter*p){num(5);num(id(p));return int(hash(2)%200)-20;}
void select(CCharacter*p,EATTACK_RANGE_TYPE t){num(6);num(id(p));num(t);p->m_attack=hash(3)%3?active->attacks[0]:NULL;}
CEquipment*equipped(CInventory*p,EEQUIP_LOCATIONS l){num(7);num(p==active->inventory);num(l);return hash(10+unsigned(l))%3?active->gear[unsigned(l)&1]:NULL;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(8);num(id(p));num(t);return bool(hash(30+unsigned(t)+id(p)*7)&1);}
EAlignment alignment(CCharacter*p){num(9);num(id(p));return static_cast<EAlignment>(hash(4)%4);}
float random(float a,float b){num(10);fp(a);fp(b);const float v[]={1,20,95,96,96.01f,96.99f,97,98,100,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()};return v[hash(5)%12];}
Ogre::Vector3 position(CPositionableObject*p,bool b){num(11);num(id(static_cast<CBaseUnit*>(p)));num(b);return p->m_vPosition;}
void text(CGameUI*p,const Ogre::Vector3&v,const std::string&s,float a,float b,CEGUI::colour first,CEGUI::colour second){num(12);num(p==active->ui);vec(v);num(s.size());if(active->observing)active->out->add(s.data(),s.size());fp(a);fp(b);fp(first.getRed());fp(first.getGreen());fp(first.getBlue());fp(first.getAlpha());fp(second.getRed());fp(second.getGreen());fp(second.getBlue());fp(second.getAlpha());}
int sound(CSoundBank*p,int n,Ogre::SceneNode*node,float a,float b,bool c){num(13);num(p==active->sound);num(n);num(node==active->self->m_pSceneNode);fp(a);fp(b);num(c);return 0;}
CStringTranslate*translator(){num(14);return reinterpret_cast<CStringTranslate*>(0x12345000);}std::wstring translate(CStringTranslate*,const wchar_t*s){num(15);wide(s);return hash(6)%3?std::wstring(s)+L" Ж":L"";}
CMasterResourceManager*manager(){num(16);return active->manager;}int gate(CMasterResourceManager*p,int l){num(17);num(p==active->manager);num(l);return (l+1)*100+int(hash(7)%5);}int maxFame(CMasterResourceManager*p){num(18);num(p==active->manager);return 5;}
CCameraControl*camera(CResourceManager*p){num(19);num(p==active->resources);return active->camera;}CGraphManager*graphManager(){num(20);return reinterpret_cast<CGraphManager*>(0x12346000);}CGraph*graph(CGraphManager*p,const std::wstring&s){num(21);num(p==reinterpret_cast<CGraphManager*>(0x12346000));wide(s);return hash(8)&1?active->graph:NULL;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initStrings();s.self=new Character;s.master=new Character;s.grand=new Character;s.target=new Character;s.gear[0]=new CEquipment(NULL);s.gear[1]=new CEquipment(NULL);s.attacks[0]=new CAttackDescription("Attack0",false,1,2,3,4,5,6);s.attacks[1]=new CAttackDescription("Attack1",true,2,3,4,5,6,7);s.inventory=static_cast<CInventory*>(autotest::allocate(sizeof(CInventory)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.camera=static_cast<CCameraControl*>(autotest::allocate(sizeof(CCameraControl)));new(&s.camera->m_cameraShakes)TArrayList<TSafePointer<CCameraShake>*>(2);s.graph=new CGraph(GRAPH_LINEAR,L"Fixture",0);s.manager=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.resources->m_pLevel=s.level;s.level->m_pGameClient=s.client;s.client->m_pGameUI=s.ui;s.self->m_pResourceManager=s.master->m_pResourceManager=s.grand->m_pResourceManager=s.resources;s.self->m_pInventory=s.inventory;s.self->m_attackItem=hash(9)%3==0?NULL:hash(9)%3==1?s.gear[0]:s.gear[1];s.self->m_bCharacterFlag4A0=hash(11)&1;s.self->m_attack=hash(12)&1?s.attacks[0]:NULL;s.self->m_attacks.push_back(s.attacks[1]);s.attacks[0]->m_DamageMaximums[0]=hash(13)%200;s.attacks[1]->m_DamageMaximums[0]=hash(14)%200;s.attacks[0]->m_iUnknown78=hash(15)%8;s.attacks[1]->m_iUnknown78=hash(16)%8;s.self->m_CharacterValue720=scalar(17);s.self->m_flag700=hash(18)&1;s.self->m_levelSound=hash(19)&1?s.sound:NULL;s.self->m_vPosition=Ogre::Vector3(1,2,3);s.target->m_vPosition=Ogre::Vector3(-1,-2,-3);s.self->m_vRight=Ogre::Vector3(.5,-.25,1);s.self->m_vForward=Ogre::Vector3(.75,.5,-.75);s.self->m_pMaster=hash(20)%3?s.master:NULL;s.master->m_pMaster=hash(21)%3?s.grand:NULL;const unsigned fame[]={0,1,50,99,100,500,1000,0x7fffffffU,0x80000000U,0xffffffffU};CCharacter*actors[]={s.self,s.master,s.grand};for(unsigned i=0;i<3;++i){actors[i]->m_fame=fame[hash(22+i)%10];actors[i]->m_fameLevel=int(hash(25+i)%9)-1;}s.self->m_pSceneNode=reinterpret_cast<Ogre::SceneNode*>(0x12347000);
if(c.op==0){typedef int(*F)(CCharacter*,CAttackDescription*,CCharacter*);F f=ours?candidateMax:originalMax;CAttackDescription*attack=hash(42)%3?s.attacks[0]:NULL;CCharacter*target=hash(43)&1?s.target:NULL;if(!autotest::beginInvocation(out,f))return;s.observing=true;num(f(s.self,attack,target));num(f(s.self,attack,target));}
else if(c.op==1){typedef bool(*F)(CCharacter*,CCharacter*);F f=ours?candidateCritical:originalCritical;if(!autotest::beginInvocation(out,f))return;s.observing=true;num(f(s.self,s.target));num(f(s.self,s.target));num(s.camera->m_cameraShakes.size());for(unsigned i=0;i<s.camera->m_cameraShakes.size();++i){CCameraShake*p=s.camera->m_cameraShakes[i]->getObject();num(p!=NULL);fp(p->m_fDuration);fp(p->m_fElapsedTime);fp(p->m_fMagnitudeMultiplier);fp(p->m_fDirectionX);fp(p->m_fDirectionY);fp(p->m_fDirectionZ);wide(p->m_strCameraShakeName);fp(p->m_fCameraPositionX);fp(p->m_fCameraPositionY);fp(p->m_fCameraPositionZ);num(p->m_bCameraShakeActive);num(p->m_bCameraFallsOffWithDistance);num(p->m_graph.getObject()==s.graph);}}
else{typedef void(*F)(CCharacter*,CLevel&,CCharacter*,int,bool);F f=ours?candidateFame:originalFame;const int a[]={-2147483647-1,-1000,-100,-1,0,1,50,100,1000,2147483647};int amount=a[hash(44)%10];bool bonus=hash(45)&1;if(!autotest::beginInvocation(out,f))return;s.observing=true;f(s.self,*s.level,s.target,amount,bonus);f(s.self,*s.level,s.target,amount,bonus);for(unsigned i=0;i<3;++i){num(actors[i]->m_fame);num(actors[i]->m_fameLevel);}}
out.callCompleted=1;s.observing=false;for(unsigned i=0;i<s.camera->m_cameraShakes.size();++i){TSafePointer<CCameraShake>*p=s.camera->m_cameraShakes[i];CCameraShake*shake=p->getObject();OGRE_DELETE_T(p, TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL);delete shake;}s.camera->m_cameraShakes.~TArrayList();delete s.graph;delete s.attacks[0];delete s.attacks[1];}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){detour::Set h;TL_REDIRECT(h,an_effect,&effect);TL_REDIRECT(h,an_equipmentEffect,&equipmentEffect);TL_REDIRECT(h,an_strength,&strength);TL_REDIRECT(h,an_dexterity,&dexterity);TL_REDIRECT(h,an_select,&select);TL_REDIRECT(h,an_equipped,&equipped);TL_REDIRECT(h,an_isa,&isa);TL_REDIRECT(h,an_alignment,&alignment);TL_REDIRECT(h,an_random,&random);TL_REDIRECT(h,an_position,&position);TL_REDIRECT(h,an_text,&text);TL_REDIRECT(h,an_sound,&sound);TL_REDIRECT(h,an_translator,&translator);TL_REDIRECT(h,an_translate,&translate);TL_REDIRECT(h,an_master,&manager);TL_REDIRECT(h,an_gate,&gate);TL_REDIRECT(h,an_maxfame,&maxFame);TL_REDIRECT(h,an_camera,&camera);TL_REDIRECT(h,an_graphManager,&graphManager);TL_REDIRECT(h,an_graph,&graph);if(h.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<8192;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    attackNumbers op%u seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",op,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=8192||coverage.different||coverage.missing;}
}
TL_TEST(character_attack_max_damage){return run(host,0,"character_attack_max_damage",0x815d40);}
TL_TEST(character_attack_critical){return run(host,1,"character_attack_critical",0x838410);}
TL_TEST(character_attack_fame){return run(host,2,"character_attack_fame",0x83c9c0);}
