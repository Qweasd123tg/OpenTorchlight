#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "Level.h"
#include "Player.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Effect.h"
#include "EffectManager.h"
#include "SoundBank.h"
#include "GameClient.h"
#include "GameUI.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "GameClientUiOwner.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(bool,taOld,(CTriggerUnit*,CCharacter*),"_ZN12CTriggerUnit7triggerEP10CCharacter")
extern "C" bool taNew(CTriggerUnit*,CCharacter*) __asm__("_ZN12CTriggerUnit7triggerEP10CCharacter");
TL_FUNCTION(taState,"_ZN12CTriggerUnit15setTriggerStateE15ETRIGGER_STATESbbb")
TL_FUNCTION(taItem,"_ZN5CItem8interactEP10CCharacter")
TL_FUNCTION(taSelect,"_ZN9CBaseUnit17selectRandomSkillEv")
TL_FUNCTION(taExecute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(taJournal,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(taQueue,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(taSpawn,"_ZN12CTriggerUnit18spawnTreasureClassEP10CCharacterRKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(taRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(taWarp,"_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b")
TL_FUNCTION(taWaypoint,"_ZN7CGameUI18toggleWaypointMenuEv")
namespace {
nativegame::Services*services;menugui::Client*clients[3];autotest::Capture*output;CTriggerUnit*unit;CCharacter*actor;CGameUI*ui;unsigned seed;
void n(unsigned x){output->add(&x,4);}void f(float x){output->add(&x,4);}void text(const std::wstring&s){output->addText(s);}
void state(CTriggerUnit*p,ETRIGGER_STATES s,bool a,bool b,bool c){n(1);n(p==unit);n(s);n(a);n(b);n(c);p->m_state=s;}
bool item(CItem*p,CCharacter*a){n(2);n(p==unit);n(a==actor);return seed%2;}
int select(CBaseUnit*p){n(3);n(p==unit);return seed/5%4==0?-1:int(seed/5%4)-1;}
CSkill*execute(CSkillManager*p,CSkill*s,CBaseUnit*caster,ESKILL_ACTIVATION_TYPE activation,const Ogre::Vector3&position,const Ogre::Quaternion&orientation,const Ogre::Vector3&target,CBaseUnit*a){n(4);n(p==unit->m_pSkillManager);n(s==p->m_OtherSkills[0]?1:s==p->m_OtherSkills[1]?2:0);n(caster==unit);n(activation);output->add(&position,sizeof position);output->add(&orientation,sizeof orientation);output->add(&target,sizeof target);n(a==actor);if(seed/31%2)unit->m_cycleMode=3;return seed/7%3?s:NULL;}
void journal(CCharacter*p,EJournalStatistic which,int amount){n(5);n(p==actor);n(which);n(amount);}
void queue(CSoundBank*p,int which,float a,float b){n(6);n(actor&&p==actor->m_levelSound);n(which);f(a);f(b);}
void spawn(CTriggerUnit*p,CCharacter*a,const std::wstring&name,unsigned count){n(7);n(p==unit);n(a==actor);text(name);n(count);}
unsigned random(int minimum,int maximum){n(8);n(minimum);n(maximum);return static_cast<unsigned>(minimum+(maximum-minimum)/2);}
void warp(CGameClient*p,std::wstring name,int depth,int unknown,bool a,std::wstring extra,bool b){n(9);n(p==clients[0]->client?1:p==clients[1]->client?2:p==clients[2]->client?3:0);text(name);n(depth);n(unknown);n(a);text(extra);n(b);}
void waypoint(CGameUI*p){n(10);n(p==ui);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;nativetrigger::LevelFixture fixture(*services);CTriggerUnit u(&fixture.resources);unit=&u;u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.setPosition(1.25f,-.5f,float(seed%7));u.setOrientation(Ogre::Quaternion(Ogre::Degree(23.f),Ogre::Vector3::UNIT_Y));u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);u.m_bItemFlag1F0=seed%13!=0;u.m_minState=int(seed/3%3)-1;u.m_maxState=u.m_minState+int(seed/5%4)+1;u.m_state=int(seed%8)-2;u.m_cycleDirection=seed/7%4;u.m_cycleMode=seed/11%4;u.m_fBaseUnitValue194=.125f*(1+seed%5);u.m_treasureClass=seed/13%2?L"GOLD":L"";u.m_minTreasure=int(seed/17%3);u.m_maxTreasure=u.m_minTreasure+int(seed/19%4);u.m_bEnabled=seed/23%2;
 CDataGroup data(L"trigger",NULL,10,10,NULL);u.m_pDataGroup=&data;data.SetDataValue(L"DESTROY_ON_DEATH",bool(seed/29%2));CPlayer*player=nativegame::createPlayer(&fixture.resources);player->m_eUnitType=UNITTYPES::PLAYER;player->sceneNodeSetParent(services->scene->getRootSceneNode(),false);player->setPosition(2.5f,3.75f,-4.5f);if(seed/7%2)player->m_levelSound=new CSoundBank(*services->master->m_pSoundManager,false);CCharacter other(&fixture.resources);other.m_eUnitType=UNITTYPES::MONSTER;other.setPosition(-.5f,2.25f,3.5f);actor=seed/3%3==0?NULL:seed/3%3==1?static_cast<CCharacter*>(player):&other;
 const unsigned types[]={32,43,173,171};u.m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(types[seed/5%4]);if(c.op==1){u.m_pSkillManager=new CSkillManager(&fixture.resources,&u);for(unsigned i=0;i<2;++i){CSkill*s=new CSkill(NULL,NULL);s->m_skillType=(seed+i)%3;u.m_pSkillManager->m_OtherSkills.add(s);}}
 if(seed/17%3){u.m_pEffectManager=new CEffectManager(&u);for(unsigned i=0;i<3;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(i==seed%3?0x71:2),false,static_cast<EEFFECT_ACTIVATION>(0),-900,1,1,false);e->m_sName=seed/19%2?L"VAULT":L"";u.m_pEffectManager->getActiveEffects(seed/23%3==0?1:0).add(e);}}
 gameclient_fixture::UiOwner uiOwner(*services->settings,*clients[0]->client,clients[0]->camera->m_cameras[0],clients[0]->scenes[0],clients[0]->scenes[1],clients[0]->scenes[2],clients[0]->resources);ui=uiOwner.ui;for(unsigned i=0;i<3;++i){clients[i]->client->m_pPlayer=(seed+i)%3?player:NULL;fixture.resources.m_GameClients.add(clients[i]->client);}
 detour::Set hooks;TL_REDIRECT(hooks,taState,&state);TL_REDIRECT(hooks,taItem,&item);if(c.op==1){TL_REDIRECT(hooks,taSelect,&select);}else{u.m_pSkillManager=new CSkillManager(&fixture.resources,&u);}TL_REDIRECT(hooks,taExecute,&execute);TL_REDIRECT(hooks,taJournal,&journal);TL_REDIRECT(hooks,taQueue,&queue);TL_REDIRECT(hooks,taSpawn,&spawn);TL_REDIRECT(hooks,taRandom,&random);TL_REDIRECT(hooks,taWarp,&warp);TL_REDIRECT(hooks,taWaypoint,&waypoint);if(hooks.failed())std::abort();autotest::invoke(out,ours?taNew:taOld,&u,actor);hooks.restore();n(u.m_state);n(u.m_cycleDirection);n(u.m_cycleMode);n(u.m_bItemFlag1F0);n(u.m_bEnabled);n(u.m_bBaseUnitFlag190);for(unsigned i=0;i<3;++i)clients[i]->client->m_pPlayer=NULL;nativegame::destroyPlayer(player);
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
 menugui::Client first(*native.settings,native.master,*native.master->m_pSoundManager);menugui::Client second(*native.settings,native.master,*native.master->m_pSoundManager);menugui::Client third(*native.settings,native.master,*native.master->m_pSoundManager);clients[0]=&first;clients[1]=&second;clients[2]=&third;
 if(smallmass::run(host,0,"trigger_action_modes_native",0x908c10,&side,384))return 1;return smallmass::run(host,1,"trigger_action_skills_native",0x908c10,&side,768);
}
}
TL_TEST(complete_trigger_action){return systems_fixture::isolated(&worker,host);}
