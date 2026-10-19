#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "SettingsVariables.h"
TL_ORIGINAL(void,gcclickOld,(CGameClient*),"_ZN11CGameClient9clickLeftEv")
extern "C" void gcclickNew(CGameClient*) __asm__("_ZN11CGameClient9clickLeftEv");
TL_FUNCTION(gcclickPaused,"_ZN11CGameClient11getIsPausedEv")
TL_FUNCTION(gcclickAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(gcclickSkillLoose,"_ZN10CCharacter20performingSkillLooseEv")
TL_FUNCTION(gcclickAttackLoose,"_ZN10CCharacter21performingAttackLooseEv")
TL_FUNCTION(gcclickSkill,"_ZN10CCharacter15performingSkillEv")
TL_FUNCTION(gcclickEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(gcclickRange,"_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
TL_FUNCTION(gcclickISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(gcclickTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(gcclickItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(gcclickAI,"_ZN7CPlayer10setAIStateE8EAIState")
TL_FUNCTION(gcclickHunt,"_ZN10CCharacter6huntAIEfR6CLevel")
TL_FUNCTION(gcclickGetItem,"_ZN10CCharacter9getItemAIEfR6CLevel")
TL_FUNCTION(gcclickStop,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(gcclickAttack,"_ZN10CCharacter6attackEv")
TL_FUNCTION(gcclickPet,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(gcclickKey,"_ZN11CKeyManager7keyHeldEj")
TL_FUNCTION(gcclickMove,"_ZN11CGameClient11moveToMouseEb")
TL_FUNCTION(gcclickDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
namespace {
#include "tests/CharacterEmptyGlobals.h"
CGameClient*client;CPlayer*actors[4];CItem*item;CLevel*level;unsigned seed,skillCalls;autotest::Capture*cap;
void num(unsigned n){cap->add(&n,4);}void fp(float f){cap->add(&f,4);}unsigned id(const void*p){if(!p)return 0;if(p==item)return 5;for(unsigned i=0;i<4;++i)if(p==actors[i])return i+1;return 99;}
bool paused(CGameClient*p){num(101);num(p==client);return seed%31==1;}
bool alive(CCharacter*p){num(103);num(id(p));return p==actors[0]?seed%29!=1:p==actors[2]?seed%3!=0:seed%11!=1;}
bool skillLoose(CCharacter*p){num(107);num(id(p));num(skillCalls);return seed%13==skillCalls++;}
bool attackLoose(CCharacter*p){num(109);num(id(p));return seed/3%3==1;}
bool skill(CCharacter*p){num(113);num(id(p));return seed/7%3==1;}
bool enemy(CCharacter*p,CCharacter*c){num(127);num(id(p));num(id(c));return seed/5%3==1;}
bool range(CCharacter*p,EATTACK_RANGE_TYPE t){num(131);num(id(p));num(t);return seed/11%3==1;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(137);num(id(p));num(t);return p==item?seed/7%3==1:seed/13%3==1;}
void target(CCharacter*p,CCharacter*c){num(139);num(id(p));num(id(c));p->m_targetCharacter.setObject(c);}
void targetItem(CCharacter*p,CItem*i){num(149);num(id(p));num(id(i));p->m_targetItem.setObject(i);}
void ai(CPlayer*p,EAIState s){num(151);num(id(p));num(s);p->m_eAIState=s;}
void hunt(CCharacter*p,float elapsed,CLevel&w){num(157);num(id(p));fp(elapsed);num(&w==level);p->m_eAIState=static_cast<EAIState>(seed%3==1?3:4);p->m_isPathing=seed/3%2;}
void getItem(CCharacter*p,float elapsed,CLevel&w){num(163);num(id(p));fp(elapsed);num(&w==level);}
void stop(CCharacter*p){num(167);num(id(p));p->m_isPathing=false;}
bool attack(CCharacter*p){num(173);num(id(p));return true;}
bool pet(CCharacter*p){num(179);num(id(p));return seed/9%3==1;}
bool key(CKeyManager*p,unsigned k){num(181);num(p==client->getKeyManager());num(k);return seed&2;}
void move(CGameClient*p,bool flag){num(191);num(p==client);num(flag);}
void destination(CCharacter*p,CLevel&w,float x,float z){num(193);num(id(p));num(&w==level);fp(x);fp(z);}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;skillCalls=0;client->m_pPlayer=actors[0];client->m_level=level;client->m_leftHeld=seed&1;client->m_inputConsumed=seed&4;actors[0]->m_pathGraceTime=-3;actors[0]->m_moveInputHeld=seed&8;actors[0]->m_Padding4D0[0]=seed&16;actors[0]->m_Padding4D0[1]=seed&32;actors[0]->m_bEnabled=seed%23!=1;actors[0]->m_eAIState=static_cast<EAIState>(seed%19==1?34:seed%17==1?20:0);
 for(unsigned i=1;i<4;++i){actors[i]->m_bVisible=seed/5%4!=1;actors[i]->m_bEnabled=seed/7%4!=1;actors[i]->m_vPosition=Ogre::Vector3(seed*.25f,3,-float(i*11));actors[i]->m_eAIState=static_cast<EAIState>(seed/11%3==0?42:seed/11%3==1?41:0);}
 actors[0]->m_Followers.clear();switch(seed/3%4){case 1:actors[0]->m_Followers.push_back(NULL);break;case 2:case 3:actors[0]->m_Followers.push_back(actors[3]);break;}
 unsigned selection=seed/2%8;client->m_targetCharacter.setObject(selection==3||selection==5?actors[1]:NULL);client->m_selectedCharacter.setObject(selection>=4?actors[2]:NULL);client->m_targetItem.setObject(selection==1||selection==7?item:NULL);client->m_selectedItem.setObject(selection==2||selection==6?item:NULL);
 item->m_bRangeEnabled=seed%5!=1;item->m_bEnabled=seed%7!=1;actors[0]->m_targetCharacter.setObject(seed&64?actors[1]:NULL);actors[0]->m_targetItem.setObject(seed&128?item:NULL);actors[3]->m_targetItem.setObject(seed&256?item:NULL);client->m_settings->SetInt(KSETTINGS_KEYMAP_HOLDPOS,seed%511);
 detour::Set hooks;TL_REDIRECT(hooks,gcclickPaused,&paused);TL_REDIRECT(hooks,gcclickAlive,&alive);TL_REDIRECT(hooks,gcclickSkillLoose,&skillLoose);TL_REDIRECT(hooks,gcclickAttackLoose,&attackLoose);TL_REDIRECT(hooks,gcclickSkill,&skill);TL_REDIRECT(hooks,gcclickEnemy,&enemy);TL_REDIRECT(hooks,gcclickRange,&range);TL_REDIRECT(hooks,gcclickISA,&isa);TL_REDIRECT(hooks,gcclickTarget,&target);TL_REDIRECT(hooks,gcclickItem,&targetItem);TL_REDIRECT(hooks,gcclickAI,&ai);TL_REDIRECT(hooks,gcclickHunt,&hunt);TL_REDIRECT(hooks,gcclickGetItem,&getItem);TL_REDIRECT(hooks,gcclickStop,&stop);TL_REDIRECT(hooks,gcclickAttack,&attack);TL_REDIRECT(hooks,gcclickPet,&pet);TL_REDIRECT(hooks,gcclickKey,&key);TL_REDIRECT(hooks,gcclickMove,&move);TL_REDIRECT(hooks,gcclickDestination,&destination);if(hooks.failed())_exit(64);
 typedef void(*F)(CGameClient*);F fn=ours?gcclickNew:gcclickOld;autotest::invoke(out,fn,client);num(id(client->m_selectedCharacter.getObject()));num(id(client->m_selectedItem.getObject()));num(client->m_inputConsumed);fp(actors[0]->m_pathGraceTime);num(actors[0]->m_Padding4D0[0]);num(actors[0]->m_Padding4D0[1]);for(unsigned i=0;i<4;++i){num(actors[i]->m_eAIState);num(actors[i]->m_isPathing);num(id(actors[i]->m_targetCharacter.getObject()));num(id(actors[i]->m_targetItem.getObject()));}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;finishlevel::Fixture world;level=&world.level;for(unsigned i=0;i<4;++i)actors[i]=nativegame::createPlayer(client->m_gameResources);item=new finishlevel::Item(client->m_gameResources);autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_click_left",(uintptr_t)gcclickOld);int failures=0;for(unsigned i=0;i<1024;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_click_left",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);delete item;for(unsigned i=0;i<4;++i)nativegame::destroyPlayer(actors[i]);return failures+stats.incomplete+(coverage.completed!=1024);}
}
TL_TEST(gameclient_click_left){return systems_fixture::isolated(&worker,host);}
