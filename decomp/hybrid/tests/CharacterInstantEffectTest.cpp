#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#include <CEGUIcolour.h>
#include <OgreSceneManager.h>
#define private public
#define protected public
#include "Character.h"
#include "Player.h"
#include "Equipment.h"
#include "Effect.h"
#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Console.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "StringTranslate.h"
#include "FileSystem.h"
#include "DynamicLine.h"
#include "Skill.h"
#include "SkillManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldInstant,(CCharacter*,CEffect*),"_ZN10CCharacter18applyInstantEffectEP7CEffect")
extern "C" void newInstant(CCharacter*,CEffect*) __asm__("_ZN10CCharacter18applyInstantEffectEP7CEffect");
TL_FUNCTION(ci_hp,"_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(ci_blocked,"_ZN10CCharacter7blockedEv")
TL_FUNCTION(ci_effectvalue,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(ci_critical,"_ZN10CCharacter12rollCriticalEPS_")
TL_FUNCTION(ci_randint,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(ci_interrupt,"_ZN10CCharacter9interruptEb")
TL_FUNCTION(ci_mitigate,"_ZN10CCharacter12modifyDamageEi13EDAMAGE_TYPESif")
TL_FUNCTION(ci_value,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(ci_random,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(ci_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(ci_damage,"_ZN10CCharacter11applyDamageER6CLevelRKN4Ogre7Vector3EfS5_fPS_bbbbj")
TL_FUNCTION(ci_damageeffects,"_ZN10CCharacter18applyDamageEffectsEPS_fPA2_ijb")
TL_FUNCTION(ci_strike,"_ZN10CCharacter18playStrikeParticleERKN4Ogre7Vector3ES3_fbb")
TL_FUNCTION(ci_sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(ci_trigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
TL_FUNCTION(ci_transform,"_ZN10CCharacter18transformCharacterESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(ci_canlearn,"_ZN10CCharacter13canLearnSpellESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(ci_player,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(ci_queue,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(ci_learn,"_ZN10CCharacter10learnSpellESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(ci_ui,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(ci_tip,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(ci_pet,"_ZN10CCharacter9removePetESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ci_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ci_gearprocs,"_ZN10CEquipment12executeProcsEP10CCharacter12EEFFECT_TYPEP9CBaseUnit")
TL_FUNCTION(ci_procs,"_ZN10CCharacter12executeProcsE12EEFFECT_TYPEP9CBaseUnit")
TL_FUNCTION(ci_visible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(ci_warp,"_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b")
TL_FUNCTION(ci_stop,"_ZN13CSkillManager16stopSkillsByNameESbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(ci_setpos,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(ci_reset,"_ZN7CPlayer11resetSkillsEv")
TL_FUNCTION(ci_text,"_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
TL_FUNCTION(ci_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(ci_setting,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(ci_console,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ci_translator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(ci_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(ci_line,"_ZN12CDynamicLineC1EN4Ogre15RenderOperation13OperationTypeE")
TL_FUNCTION(ci_point,"_ZN12CDynamicLine8addPointEfff")
TL_FUNCTION(ci_align,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(ci_unique,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(ci_files,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(ci_mods,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
namespace {
void initStrings(){
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476068),8);if(!p)new(reinterpret_cast<void*>(0x1476068))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1476060),8);if(!p)new(reinterpret_cast<void*>(0x1476060))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479460),8);if(!p)new(reinterpret_cast<void*>(0x1479460))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479468),8);if(!p)new(reinterpret_cast<void*>(0x1479468))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c348),8);if(!p)new(reinterpret_cast<void*>(0x147c348))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c340),8);if(!p)new(reinterpret_cast<void*>(0x147c340))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1480a48),8);if(!p)new(reinterpret_cast<void*>(0x1480a48))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1480a40),8);if(!p)new(reinterpret_cast<void*>(0x1480a40))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1484120),8);if(!p)new(reinterpret_cast<void*>(0x1484120))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1484128),8);if(!p)new(reinterpret_cast<void*>(0x1484128))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a300),8);if(!p)new(reinterpret_cast<void*>(0x148a300))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a308),8);if(!p)new(reinterpret_cast<void*>(0x148a308))std::wstring;}
}
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;bool observing,actualPlayer;CCharacter*self,*other,*follower;CEquipment*gear;CEffect*effect;CLevel*level;CResourceManager*resources;CGameClient*client;CGameUI*ui;CConsole*console;CMasterResourceManager*master;CSettings*settings;CSoundBank*sound;CSkill*skill;unsigned rng;Ogre::Quaternion q;Ogre::SceneManager*scene;Ogre::SceneNode*root,*base,*lineNode,*node;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){if(active->observing)active->out->add(&n,4);}void fp(float n){if(active->observing)active->out->add(&n,4);}void wide(const std::wstring&s){num(s.size());if(active->observing)active->out->add(s.data(),s.size()*4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(CBaseUnit*p){return p==active->self?1:p==active->other?2:p==active->follower?3:p==active->gear?4:p==NULL?0:99;}void quat(const Ogre::Quaternion&q){fp(q.w);fp(q.x);fp(q.y);fp(q.z);}float scalar(unsigned n){const float values[]={-100,-1,-.25f,-0.0f,0,.5f,1,5,20,100,std::numeric_limits<float>::quiet_NaN()};return values[hash(n)%11];}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual void openPortal(CLevel&l){num(1);num(&l==active->level);}virtual void openMapPortal(std::wstring n,CLevel&l){num(2);wide(n);num(&l==active->level);}virtual void die(CCharacter*p,const Ogre::Vector3*d,float f,bool b){num(3);num(id(p));num(d==NULL);fp(f);num(b);}virtual void reactToDamage(CCharacter*p,bool b){num(4);num(id(p));num(b);}virtual void BroadcastEvent(unsigned n){num(5);num(n);}virtual Ogre::Quaternion getOrientationQuaternion(){num(6);num(id(this));return active->q;}virtual void setOrientation(const Ogre::Quaternion&q){num(7);num(id(this));quat(q);}};
void hp(CCharacter*p,float value){num(8);num(id(p));fp(value);p->m_fHPFloat=value;}bool blocked(CCharacter*){num(9);return hash(1)&1;}float effectValue(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES d){num(10);num(id(p));num(t);num(d);return scalar(100+unsigned(t));}bool critical(CCharacter*p,CCharacter*t){num(11);num(id(p));num(id(t));return hash(2)&1;}int rngInt(int a,int b){num(12);num(a);num(b);unsigned x=hash(200+active->rng++)%unsigned(b-a+1)+a;num(x);return x;}void interrupt(CCharacter*p,bool b){num(13);num(id(p));num(b);}int mitigate(CCharacter*p,int damage,EDAMAGE_TYPES t,int total,float f){num(14);num(id(p));num(damage);num(t);num(total);fp(f);return int(hash(3)%11)-5;}float value(CEffect*p,EEFFECT_VALUES n){num(15);num(p==active->effect);num(n);return scalar(10+unsigned(n));}float rngFloat(float a,float b){num(16);fp(a);fp(b);return a+(b-a)*.25f;}Ogre::Vector3 position(CPositionableObject*p,bool b){num(17);num(id(static_cast<CBaseUnit*>(p)));num(b);return p->m_vPosition;}
void damage(CCharacter*p,CLevel&l,const Ogre::Vector3&from,float amount,const Ogre::Vector3&direction,float force,CCharacter*k,bool a,bool b,bool c,bool d,unsigned flags){num(18);num(id(p));num(&l==active->level);vec(from);fp(amount);vec(direction);fp(force);num(id(k));num(a);num(b);num(c);num(d);num(flags);p->m_fHPFloat=hash(4)&1?0:1;}
void damageEffects(CCharacter*p,CCharacter*t,float n,int(*damages)[2],unsigned count,bool b){num(19);num(id(p));num(id(t));fp(n);num(count);num(b);for(unsigned i=0;i<count;++i){num(damages[i][0]);num(damages[i][1]);}}void strike(CCharacter*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float r,bool c,bool d){num(20);num(id(p));vec(a);vec(b);fp(r);num(c);num(d);}int sound(CSoundBank*p,int i,Ogre::SceneNode*n,float a,float b,bool c){num(21);num(p==active->sound);num(i);num(n==active->node);fp(a);fp(b);num(c);return 0;}bool trigger(CSkill*p,ESKILL_EVENT_TYPE e,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*position){num(22);num(p==active->skill);num(e);vec(v);quat(q);num(id(t));num(position==NULL);return true;}void transform(CCharacter*p,std::wstring name,float f){num(23);num(id(p));wide(name);fp(f);}bool canlearn(CCharacter*p,std::wstring n,int level){num(24);num(id(p));wide(n);num(level);return hash(5)&1;}bool player(CBaseUnit*p){num(25);num(id(p));return active->actualPlayer||bool(hash(6)&1);}void queue(CSoundBank*p,int i,float a,float b){num(26);num(p==active->sound);num(i);fp(a);fp(b);}bool learn(CCharacter*p,std::wstring n,int level){num(27);num(id(p));wide(n);num(level);return true;}CGameUI*ui(CResourceManager*p){num(28);num(p==active->resources);return active->ui;}void tip(CGameUI*p,EContextTip t){num(29);num(p==active->ui);num(t);}void pet(CCharacter*p,std::wstring n){num(30);num(id(p));wide(n);}bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(31);num(id(p));num(t);return p==active->gear;}void gearprocs(CEquipment*p,CCharacter*c,EEFFECT_TYPE t,CBaseUnit*b){num(32);num(id(p));num(id(c));num(t);num(id(b));}void procs(CCharacter*p,EEFFECT_TYPE t,CBaseUnit*b){num(33);num(id(p));num(t);num(id(b));}void visible(CCharacter*p,bool a,bool b){num(34);num(id(p));num(a);num(b);num(p->m_forcedHidden);}void warp(CGameClient*p,std::wstring n,int a,int b,bool c,std::wstring w,bool d){num(35);num(p==active->client);wide(n);num(a);num(b);num(c);wide(w);num(d);}void stop(CSkillManager*,std::wstring n,bool b){num(36);wide(n);num(b);}void setpos(CPositionableObject*p,const Ogre::Vector3&v){num(37);num(id(static_cast<CBaseUnit*>(p)));vec(v);p->m_vPosition=v;}void reset(CPlayer*p){num(38);num(p==active->self);}void text(CGameUI*p,const Ogre::Vector3&v,const std::string&s,float a,float b,CEGUI::colour first,CEGUI::colour second){num(39);num(p==active->ui);vec(v);num(s.size());if(active->observing)active->out->add(s.data(),s.size());fp(a);fp(b);fp(first.getRed());fp(first.getGreen());fp(first.getBlue());fp(first.getAlpha());fp(second.getRed());fp(second.getGreen());fp(second.getBlue());fp(second.getAlpha());}CMasterResourceManager*master(){num(40);return active->master;}int setting(CDynamicPropertyFile*p,unsigned k){num(41);num(p==active->settings);num(k);return hash(7)%3-1;}void console(CConsole*p,std::wstring s){num(42);num(p==active->console);wide(s);}CStringTranslate*translator(){num(43);return reinterpret_cast<CStringTranslate*>(0x12345000);}std::wstring translate(CStringTranslate*,const wchar_t*s){num(44);wide(s);return hash(8)%3?std::wstring(s)+L" Ж":L"";}const Ogre::Quaternion&nodeOrientation(Ogre::SceneNode*){num(45);return active->q;}
// Renderer and filesystem boundaries for a genuine native Player construction.
Ogre::SceneNode*create(Ogre::SceneManager*){return active->base;}Ogre::SceneNode*root(Ogre::SceneManager*){return active->root;}Ogre::SceneNode*child(Ogre::SceneNode*,const std::string&,const Ogre::Vector3&,const Ogre::Quaternion&){return active->lineNode;}void attach(Ogre::SceneNode*,Ogre::MovableObject*){}void nodeVisible(Ogre::SceneNode*,bool,bool){}void line(CDynamicLine*p,Ogre::RenderOperation::OperationType){new(&p->m_points)std::vector<Ogre::Vector3>;p->m_dirty=false;}void point(CDynamicLine*p,float x,float y,float z){p->m_points.push_back(Ogre::Vector3(x,y,z));p->m_dirty=true;}void align(CCharacter*p,EAlignment a){p->m_alignment=a;}std::string unique(const std::string&s){return s+"17";}CFileSystem*files(){return reinterpret_cast<CFileSystem*>(0x12344000);}void mods(CFileSystem*,TArrayList<std::wstring>*){}
void setupPlayer(){State&s=*active;s.scene=static_cast<Ogre::SceneManager*>(autotest::allocate(sizeof(Ogre::SceneManager)));s.root=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.base=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.lineNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.resources->m_pSceneManager=s.scene;void**sm=static_cast<void**>(autotest::allocate(0x400));sm[0x230/8]=reinterpret_cast<void*>(&create);sm[0x250/8]=reinterpret_cast<void*>(&root);*reinterpret_cast<void***>(s.scene)=sm;void**nv=static_cast<void**>(autotest::allocate(0x400));nv[0x328/8]=reinterpret_cast<void*>(&child);nv[0x278/8]=reinterpret_cast<void*>(&attach);nv[0x378/8]=reinterpret_cast<void*>(&nodeVisible);*reinterpret_cast<void***>(s.root)=nv;*reinterpret_cast<void***>(s.lineNode)=nv;*reinterpret_cast<void***>(s.base)=nv;s.self=new CPlayer(s.resources);}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initStrings();const int types[]={7,52,124,45,56,57,65,67,73,74,110,111,112,113,114,115,116,117,118,119,120,127,141,142,143,0,6,144};int type=types[c.index%28];s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.actualPlayer=type==143&&(hash(50)&1);if(s.actualPlayer)setupPlayer();else s.self=new Character;s.other=new Character;s.follower=new Character;s.gear=new CEquipment(NULL);s.effect=new CEffect(static_cast<EEFFECT_TYPE>(type),false,EFFECT_ACTIVATION_PASSIVE,0,0,0,false);CBaseUnit*owners[]={s.other,s.gear,s.follower,NULL};CBaseUnit*owner=owners[hash(51)%4];if(type==74&&!owner)owner=s.other;s.effect->m_Owner.setObject(owner);s.effect->m_eDamageType=static_cast<EDAMAGE_TYPES>(hash(52)%8);s.effect->m_fValueC0=scalar(53);s.effect->m_direction=Ogre::Vector3(1,0,-1);s.effect->m_sName=hash(54)&1?L"EffectName Ж":L"";s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.console=static_cast<CConsole*>(autotest::allocate(sizeof(CConsole)));s.sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.master=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.settings=static_cast<CSettings*>(autotest::allocate(sizeof(CSettings)));s.skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));s.master->m_pSettings=s.settings;s.ui->m_console=s.console;s.level->m_pGameClient=s.client;s.client->m_pGameUI=s.ui;s.resources->m_pLevel=s.level;new(&s.resources->m_GameClients)TArrayList<CGameClient*>(2);s.resources->m_GameClients.add(s.client);s.self->m_pResourceManager=s.resources;s.self->m_levelSound=hash(55)&1?s.sound:NULL;s.self->m_pSkillManager=hash(56)&1?static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager))):NULL;s.self->m_attack=reinterpret_cast<CAttackDescription*>(0x12345000);s.self->m_alwaysActive=hash(57)&1;s.self->m_champion=hash(58)&1;s.self->m_forcedHidden=hash(59)&1;s.self->m_iMeleeStat=9;s.self->m_rangedStat=10;s.self->m_magicStat=11;s.self->m_maxHPBonus=12;s.self->m_defenseStat=13;s.self->m_maxManaBonus=14.25;s.self->m_iUnusedStatPoints=15;s.self->m_fBaseUnitValue194=7.25;s.self->m_vPosition=Ogre::Vector3(1,2,3);s.other->m_vPosition=Ogre::Vector3(-1,2,-3);s.follower->m_vPosition=Ogre::Vector3(7,8,9);if(hash(60)%3)s.self->m_Followers.push_back(hash(61)&1?s.follower:NULL);s.q=Ogre::Quaternion(.5,.25,-.25,.75);s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));void**nv=static_cast<void**>(autotest::allocate(0x100));nv[0xc8/8]=reinterpret_cast<void*>(&nodeOrientation);*reinterpret_cast<void***>(s.node)=nv;s.self->m_pSceneNode=s.node;s.effect->m_pSkillOwner.m_pObject=hash(62)&1?s.skill:NULL;
typedef void(*F)(CCharacter*,CEffect*);F f=ours?newInstant:oldInstant;if(!autotest::beginInvocation(out,f))return;s.observing=true;f(s.self,s.effect);f(s.self,s.effect);out.callCompleted=1;num(s.self->m_attack==NULL);num(s.self->m_forcedHidden);num(s.self->m_iMeleeStat);num(s.self->m_rangedStat);num(s.self->m_magicStat);num(s.self->m_maxHPBonus);num(s.self->m_defenseStat);fp(s.self->m_maxManaBonus);num(s.self->m_iUnusedStatPoints);fp(s.self->m_fHPFloat);vec(s.self->m_vPosition);vec(s.follower->m_vPosition);s.observing=false;s.effect->m_pSkillOwner.invalidate();delete s.effect;}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(character_combat_instant_effect){detour::Set h;TL_REDIRECT(h,ci_hp,&hp);TL_REDIRECT(h,ci_blocked,&blocked);TL_REDIRECT(h,ci_effectvalue,&effectValue);TL_REDIRECT(h,ci_critical,&critical);TL_REDIRECT(h,ci_randint,&rngInt);TL_REDIRECT(h,ci_interrupt,&interrupt);TL_REDIRECT(h,ci_mitigate,&mitigate);TL_REDIRECT(h,ci_value,&value);TL_REDIRECT(h,ci_random,&rngFloat);TL_REDIRECT(h,ci_position,&position);TL_REDIRECT(h,ci_damage,&damage);TL_REDIRECT(h,ci_damageeffects,&damageEffects);TL_REDIRECT(h,ci_strike,&strike);TL_REDIRECT(h,ci_sound,&sound);TL_REDIRECT(h,ci_trigger,&trigger);TL_REDIRECT(h,ci_transform,&transform);TL_REDIRECT(h,ci_canlearn,&canlearn);TL_REDIRECT(h,ci_player,&player);TL_REDIRECT(h,ci_queue,&queue);TL_REDIRECT(h,ci_learn,&learn);TL_REDIRECT(h,ci_ui,&ui);TL_REDIRECT(h,ci_tip,&tip);TL_REDIRECT(h,ci_pet,&pet);TL_REDIRECT(h,ci_isa,&isa);TL_REDIRECT(h,ci_gearprocs,&gearprocs);TL_REDIRECT(h,ci_procs,&procs);TL_REDIRECT(h,ci_visible,&visible);TL_REDIRECT(h,ci_warp,&warp);TL_REDIRECT(h,ci_stop,&stop);TL_REDIRECT(h,ci_setpos,&setpos);TL_REDIRECT(h,ci_reset,&reset);TL_REDIRECT(h,ci_text,&text);TL_REDIRECT(h,ci_master,&master);TL_REDIRECT(h,ci_setting,&setting);TL_REDIRECT(h,ci_console,&console);TL_REDIRECT(h,ci_translator,&translator);TL_REDIRECT(h,ci_translate,&translate);TL_REDIRECT(h,ci_line,&line);TL_REDIRECT(h,ci_point,&point);TL_REDIRECT(h,ci_align,&align);TL_REDIRECT(h,ci_unique,&unique);TL_REDIRECT(h,ci_files,&files);TL_REDIRECT(h,ci_mods,&mods);if(h.failed())return 1;autotest::Coverage coverage("character_combat_instant_effect",0x8424a0);for(unsigned i=0;i<8192;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    instantEffect seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=8192||coverage.different||coverage.missing;}
