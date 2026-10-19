#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "SettingsVariables.h"
#include "GameClientUiOwner.h"
#define private public
#include "Skill.h"
#undef private
#include "SkillManager.h"
TL_ORIGINAL(bool,gcrightOld,(CGameClient*,long long,bool,bool),"_ZN11CGameClient10clickRightExbb")
extern "C" bool gcrightNew(CGameClient*,long long,bool,bool) __asm__("_ZN11CGameClient10clickRightExbb");
TL_FUNCTION(gcrightPaused,"_ZN11CGameClient11getIsPausedEv")
TL_FUNCTION(gcrightAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(gcrightSkillLoose,"_ZN10CCharacter20performingSkillLooseEv")
TL_FUNCTION(gcrightAttackLoose,"_ZN10CCharacter21performingAttackLooseEv")
TL_FUNCTION(gcrightSkill,"_ZN10CCharacter15performingSkillEv")
TL_FUNCTION(gcrightEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(gcrightRange,"_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
TL_FUNCTION(gcrightISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(gcrightTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(gcrightItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(gcrightAI,"_ZN7CPlayer10setAIStateE8EAIState")
TL_FUNCTION(gcrightHunt,"_ZN10CCharacter6huntAIEfR6CLevel")
TL_FUNCTION(gcrightGetItem,"_ZN10CCharacter9getItemAIEfR6CLevel")
TL_FUNCTION(gcrightStop,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(gcrightAttack,"_ZN10CCharacter6attackEv")
TL_FUNCTION(gcrightPet,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(gcrightKey,"_ZN11CKeyManager7keyHeldEj")
TL_FUNCTION(gcrightMove,"_ZN11CGameClient11moveToMouseEb")
TL_FUNCTION(gcrightDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(gcrightLookup,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(gcrightType,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(gcrightAnimation,"_ZN6CSkill17getAnimationIndexEv")
TL_FUNCTION(gcrightTooltip,"_ZN7CGameUI23equipmentTooltipVisibleEv")
TL_FUNCTION(gcrightButton,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(gcrightCursor,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(gcrightFlush,"_ZN7CGameUI10flushInputEv")
TL_FUNCTION(gcrightPressed,"_ZN7CGameUI21setRightButtonPressedEv")
TL_FUNCTION(gcrightWorld,"_ZN11CGameClient17findWorldLocationERN4Ogre7Vector3Eb")
TL_FUNCTION(gcrightCast,"_ZN10CCharacter9castSkillEx")
TL_FUNCTION(gcrightSkillRange,"_ZN10CCharacter12inSkillRangeExb")
TL_FUNCTION(gcrightApproach,"_ZN10CCharacter15skillApproachAIEfR6CLevelx")
TL_FUNCTION(gcrightDirection,"_ZN10CCharacter18setTargetDirectionEff")
namespace {
#include "tests/CharacterEmptyGlobals.h"
CGameClient*client;CPlayer*actors[4];CItem*item;CLevel*level;CSkill*skills[2];CGameUI*ui;unsigned seed,skillCalls,castCalls;autotest::Capture*cap;
void num(unsigned n){cap->add(&n,4);}void fp(float f){cap->add(&f,4);}unsigned id(const void*p){if(!p)return 0;if(p==item)return 5;for(unsigned i=0;i<4;++i)if(p==actors[i])return i+1;if(p==skills[0])return 6;if(p==skills[1])return 7;if(p==actors[0]->getSkillManager())return 8;return 99;}
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
CSkill*lookup(CSkillManager*p,long long guid){num(197);num(id(p));cap->add(&guid,8);if(guid==100)return seed%5==0?NULL:skills[0];if(guid==200)return seed%7==0?NULL:skills[1];return seed%3?skills[0]:NULL;}
int type(CSkill*p){num(199);num(id(p));const int types[]={0,1,3,7,8,9,10};return types[(seed/3+(p==skills[1]?2:0))%7];}
unsigned animation(CSkill*p){num(211);num(id(p));return seed&16?~0u:9;}
bool tooltip(CGameUI*p){num(223);num(p==ui);return seed&32;}
bool button(CMouseManager*p,EMouseButton b){num(227);num(p==&client->m_mouseManager);num(b);return seed&64;}
void cursor(CGameUI*p,ECursorState v){num(229);num(p==ui);num(v);p->m_cursorState=v;}
void flush(CGameUI*p){num(233);num(p==ui);}
void pressed(CGameUI*p){num(239);num(p==ui);}
bool world(CGameClient*p,Ogre::Vector3&v,bool b){num(241);num(p==client);num(b);v=Ogre::Vector3(11+seed*.125f,7,-3);return seed%17!=3;}
bool cast(CCharacter*p,long long guid){num(251);num(id(p));cap->add(&guid,8);num(castCalls);bool result=(seed+castCalls++)%3==1;if(seed%13==5)p->m_eAIState=static_cast<EAIState>(13);return result;}
int skillRange(CCharacter*p,long long guid,bool b){num(257);num(id(p));cap->add(&guid,8);num(b);return int(seed/11%3)-1;}
void approach(CCharacter*p,float elapsed,CLevel&w,long long guid){num(263);num(id(p));fp(elapsed);num(&w==level);cap->add(&guid,8);p->m_isPathing=seed&128;}
void direction(CCharacter*p,float x,float z){num(269);num(id(p));fp(x);fp(z);}
struct Case{unsigned seed;unsigned variant;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;skillCalls=0;castCalls=0;client->m_pGameUI=ui;ui->m_cursorState=static_cast<ECursorState>(seed%6);ui->m_guidB0=777;client->m_pPlayer=actors[0];client->m_level=level;client->m_leftHeld=seed&1;client->m_rightHeld=seed&2;client->m_inputConsumed=seed&4;actors[0]->m_pathGraceTime=-3;actors[0]->m_moveInputHeld=seed&8;actors[0]->m_Padding4D0[0]=seed&16;actors[0]->m_Padding4D0[1]=seed&32;actors[0]->m_bEnabled=seed%23!=1;actors[0]->m_eAIState=static_cast<EAIState>(seed%19==1?34:seed%17==1?20:0);
 for(unsigned i=1;i<4;++i){actors[i]->m_bVisible=seed/5%4!=1;actors[i]->m_bEnabled=seed/7%4!=1;actors[i]->m_vPosition=Ogre::Vector3(seed*.25f,3,-float(i*11));actors[i]->m_eAIState=static_cast<EAIState>(seed/11%3==0?42:seed/11%3==1?41:0);}
 actors[0]->m_Followers.clear();switch(seed/3%4){case 1:actors[0]->m_Followers.push_back(NULL);break;case 2:case 3:actors[0]->m_Followers.push_back(actors[3]);break;}
 unsigned selection=seed/2%8;client->m_targetCharacter.setObject(selection==3||selection==5?actors[1]:NULL);client->m_selectedCharacter.setObject(selection>=4?actors[2]:NULL);client->m_targetItem.setObject(selection==1||selection==7?item:NULL);client->m_selectedItem.setObject(selection==2||selection==6?item:NULL);
 item->m_bRangeEnabled=seed%5!=1;item->m_bEnabled=seed%7!=1;actors[0]->m_targetCharacter.setObject(seed&64?actors[1]:NULL);actors[0]->m_targetItem.setObject(seed&128?item:NULL);actors[3]->m_targetItem.setObject(seed&256?item:NULL);client->m_settings->SetInt(KSETTINGS_KEYMAP_HOLDPOS,seed%511);
 actors[0]->m_activeSkill=seed%4==0?skills[0]:seed%4==1?skills[1]:NULL;actors[0]->m_activeSkillGuid=200;skills[0]->m_stopsPathingOnCompletion=seed&256;skills[1]->m_stopsPathingOnCompletion=seed&512;for(unsigned k=0;k<10;++k)actors[0]->m_skillMap[k]=seed/7%11==k?300+k:-1;
 // Independent selection/held inputs specifically exercise target promotion.
 unsigned variant=static_cast<Case*>(raw)->variant;
 client->m_leftHeld=variant==3;client->m_rightHeld=false;
 client->m_selectedCharacter.setObject(NULL);client->m_targetCharacter.setObject(actors[1]);
 client->m_selectedItem.setObject(NULL);client->m_targetItem.setObject(NULL);
 actors[0]->m_activeSkill=variant==1?skills[1]:skills[0];
 for(unsigned k=0;k<10;++k)actors[0]->m_skillMap[k]=-1;
 actors[0]->m_skillMap[2]=variant==2?200:100;
 detour::Set hooks;TL_REDIRECT(hooks,gcrightLookup,&lookup);TL_REDIRECT(hooks,gcrightType,&type);TL_REDIRECT(hooks,gcrightAnimation,&animation);TL_REDIRECT(hooks,gcrightTooltip,&tooltip);TL_REDIRECT(hooks,gcrightButton,&button);TL_REDIRECT(hooks,gcrightCursor,&cursor);TL_REDIRECT(hooks,gcrightFlush,&flush);TL_REDIRECT(hooks,gcrightPressed,&pressed);TL_REDIRECT(hooks,gcrightWorld,&world);TL_REDIRECT(hooks,gcrightCast,&cast);TL_REDIRECT(hooks,gcrightSkillRange,&skillRange);TL_REDIRECT(hooks,gcrightApproach,&approach);TL_REDIRECT(hooks,gcrightDirection,&direction);TL_REDIRECT(hooks,gcrightPaused,&paused);TL_REDIRECT(hooks,gcrightAlive,&alive);TL_REDIRECT(hooks,gcrightSkillLoose,&skillLoose);TL_REDIRECT(hooks,gcrightAttackLoose,&attackLoose);TL_REDIRECT(hooks,gcrightSkill,&skill);TL_REDIRECT(hooks,gcrightEnemy,&enemy);TL_REDIRECT(hooks,gcrightRange,&range);TL_REDIRECT(hooks,gcrightISA,&isa);TL_REDIRECT(hooks,gcrightTarget,&target);TL_REDIRECT(hooks,gcrightItem,&targetItem);TL_REDIRECT(hooks,gcrightAI,&ai);TL_REDIRECT(hooks,gcrightHunt,&hunt);TL_REDIRECT(hooks,gcrightGetItem,&getItem);TL_REDIRECT(hooks,gcrightStop,&stop);TL_REDIRECT(hooks,gcrightAttack,&attack);TL_REDIRECT(hooks,gcrightPet,&pet);TL_REDIRECT(hooks,gcrightKey,&key);TL_REDIRECT(hooks,gcrightMove,&move);TL_REDIRECT(hooks,gcrightDestination,&destination);if(hooks.failed())_exit(64);
 typedef bool(*F)(CGameClient*,long long,bool,bool);F fn=ours?gcrightNew:gcrightOld;if(autotest::beginInvocation(out,fn)){bool result=fn(client,100,(seed&1024)!=0,(seed&2048)!=0);out.callCompleted=1;num(result);}num(ui->m_cursorState);cap->add(&ui->m_guidB0,8);num(id(client->m_selectedCharacter.getObject()));num(id(client->m_selectedItem.getObject()));num(client->m_inputConsumed);fp(actors[0]->m_pathGraceTime);num(actors[0]->m_Padding4D0[0]);num(actors[0]->m_Padding4D0[1]);for(unsigned i=0;i<4;++i){num(actors[i]->m_eAIState);num(actors[i]->m_isPathing);num(id(actors[i]->m_targetCharacter.getObject()));num(id(actors[i]->m_targetItem.getObject()));}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){tlheadless::Environment environment;environment.loadGameSkin();initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;finishlevel::Fixture world;level=&world.level;for(unsigned i=0;i<4;++i)actors[i]=nativegame::createPlayer(client->m_gameResources);item=new finishlevel::Item(client->m_gameResources);for(unsigned i=0;i<2;++i)skills[i]=new CSkill(client->m_gameResources,NULL);if(!actors[0]->getSkillManager())actors[0]->m_pSkillManager=new CSkillManager(client->m_gameResources,actors[0]);gameclient_fixture::UiOwner uiOwner(*native.settings,*client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);ui=uiOwner.ui;autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_click_right_audit",(uintptr_t)gcrightOld);int failures=0;const unsigned auditSeeds[]={26,78,130,182,234,286,338,390};for(unsigned i=0;i<32;++i){Case c={auditSeeds[i/4],i%4};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_click_right_audit",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);for(unsigned i=0;i<4;++i)actors[i]->m_activeSkill=NULL;for(unsigned i=0;i<2;++i)delete skills[i];delete item;for(unsigned i=0;i<4;++i)nativegame::destroyPlayer(actors[i]);return failures+stats.incomplete+(coverage.completed!=32);}
}
TL_TEST(gameclient_click_right_audit){return systems_fixture::isolated(&worker,host);}
