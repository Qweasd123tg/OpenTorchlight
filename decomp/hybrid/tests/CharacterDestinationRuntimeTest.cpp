#include <cstring>
#include <clocale>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Skill.h"
#include "Path.h"
#include "AstarPathfinder.h"
#include "AttackDescription.h"
#include "SettingsVariables.h"
#undef private
#undef protected
#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,cdOld,(CCharacter*,CLevel&,float,float),"_ZN10CCharacter14setDestinationER6CLevelff")
extern "C" void cdNew(CCharacter*,CLevel&,float,float) __asm__("_ZN10CCharacter14setDestinationER6CLevelff");
TL_FUNCTION(cdWalk,"_ZN10CCharacter12walkingSpeedEv")
TL_FUNCTION(cdRun,"_ZN10CCharacter12runningSpeedEv")
TL_FUNCTION(cdAttack,"_ZN10CCharacter6attackEv")
TL_FUNCTION(cdFind,"_ZN16CAstarPathfinder8findPathEffff")
TL_FUNCTION(cdReached,"_ZN16CAstarPathfinder11reachedGoalEv")
TL_FUNCTION(cdAdvance,"_ZN16CAstarPathfinder15advanceNextNodeEv")
TL_FUNCTION(cdNodeX,"_ZN16CAstarPathfinder8getNodeXEv")
TL_FUNCTION(cdNodeY,"_ZN16CAstarPathfinder8getNodeYEv")
TL_FUNCTION(cdPass,"_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b")
TL_FUNCTION(cdPosition,"_ZN6CLevel16positionPassableERKN4Ogre7Vector3E")
TL_FUNCTION(cdDisplay,"_ZN10CCharacter11displayPathEv")
TL_FUNCTION(cdUI,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(cdCinematic,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(cdSetting,"_ZN20CDynamicPropertyFile6GetIntEj")
namespace {
struct Case{unsigned seed,control;};unsigned seed,mode,variant,phase,node,passCalls;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;menugui::Fixture*menu;finishlevel::Fixture*world;CCharacter*self;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-destination-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setAIState(EAIState state){num(101);num(state);m_eAIState=state;}virtual void removeFromAvoidanceMap(CLevel&level){num(103);num(&level==&world->level);num(m_bBaseUnitFlag19B);m_bBaseUnitFlag19B=false;}virtual void addToAvoidanceMap(CLevel&level){num(107);num(&level==&world->level);num(m_bBaseUnitFlag19B);m_bBaseUnitFlag19B=true;}};
float walk(CCharacter*p){num(109);num(p==self);return mode==4?0:float(variant%3);}
float run(CCharacter*p){num(113);num(p==self);return mode==4?0:2;}
void attack(CCharacter*p){num(127);num(p==self);}
bool find(CAstarPathfinder*p,float a,float b,float c,float d){num(131);num(p==self->m_pathfinder);fp(a);fp(b);fp(c);fp(d);num(p->m_bIgnoreOccupancy);return mode!=11;}
bool reached(CAstarPathfinder*p){num(137);num(p==self->m_pathfinder);num(node);return node>=variant%6;}
void advance(CAstarPathfinder*p){num(139);num(p==self->m_pathfinder);++node;}
float nodeX(CAstarPathfinder*p){num(149);num(p==self->m_pathfinder);return 1+node*.4f;}
float nodeY(CAstarPathfinder*p){num(151);num(p==self->m_pathfinder);return 3+node*.6f;}
bool pass(CLevel*p,Ogre::Vector3 a,const Ogre::Vector3&b,bool flag){num(157);num(p==&world->level);vec(a);vec(b);num(flag);return(variant+passCalls++)%3!=0;}
bool position(CLevel*p,const Ogre::Vector3&v){num(163);num(p==&world->level);vec(v);return variant%3!=0;}
void display(CCharacter*p){num(167);num(p==self);}
CGameUI*ui(CResourceManager*p){num(173);num(p==&world->resources);return variant%3==0?NULL:menu->ui;}
bool cinematic(CGameUI*p){num(179);num(p==menu->ui);return variant%3==1;}
int setting(CDynamicPropertyFile*p,unsigned key){num(181);num(p==static_cast<CDynamicPropertyFile*>(services->master->m_pSettings));num(key);return variant&4;}
void floats(const std::vector<float>&v){num(v.size());for(unsigned i=0;i<v.size();++i)fp(v[i]);}
void path(CPath*p){num(p->m_lPoints.size());fp(p->m_fPathLength);for(unsigned i=0;i<p->m_lPoints.size();++i)vec(p->m_lPoints[i]);floats(p->m_lRadiusLeft);floats(p->m_lRadiusRight);floats(p->m_lSegmentAngle);floats(p->m_lPointDistance);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%24;variant=seed/24;phase=1;oursSide=ours;armed=false;out=&capture;node=passCalls=0;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);self=new Actor;self->m_pResourceManager=&world->resources;self->m_pathfinder=mode==0?NULL:new CAstarPathfinder(0,0,0,0,NULL,NULL,1);if(self->m_pathfinder)self->m_pathfinder->m_bIgnoreOccupancy=variant&8;self->m_movementPath=new CPath("move",false,Ogre::Vector3::ZERO);if(variant&16){self->m_movementPath->AddPoint(Ogre::Vector3(2,0,3),-1,1);self->m_movementPath->AddPoint(Ogre::Vector3(5,0,6),-1,1);}self->m_eAIState=static_cast<EAIState>(mode==1?5:mode==2?6:mode==3?12:mode>=20?32+mode%3:2);self->m_vPosition=Ogre::Vector3(1,2,3);self->m_targetPosition=Ogre::Vector3(-4,-5,-6);self->m_pathDestination=Ogre::Vector3(-7,-8,-9);self->m_pathGraceTime=-2;self->m_moveInputHeld=mode==5||mode==6;self->m_isPathing=variant&1;self->m_skillLooping=variant&2;self->m_skillTime=variant&4?1:0;self->m_skillInterrupted=variant&8;self->m_bBaseUnitFlag19B=variant&16;
 if(mode==6||mode==8||mode==9||mode==10){self->m_activeSkill=new CSkill(NULL,NULL);self->m_activeSkill->m_animationID=variant%2?-1:4;self->m_activeSkill->m_interruptible=variant&1;self->m_activeSkill->m_stopsPathingOnCompletion=mode!=9;}
 if(mode==7||mode==8){self->m_attack=new CAttackDescription("destination",false,1,2,3,4,5,6);self->m_attackTime=.3f;}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,cd##name,&fn)
 P(Walk,walk);P(Run,run);P(Attack,attack);P(Find,find);P(Reached,reached);P(Advance,advance);P(NodeX,nodeX);P(NodeY,nodeY);P(Pass,pass);P(Position,position);P(Display,display);P(UI,ui);P(Cinematic,cinematic);P(Setting,setting);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef void(*F)(CCharacter*,CLevel&,float,float);F fn=ours?cdNew:cdOld;if(!autotest::beginInvocation(capture,fn))return;float x=variant%2?1.1f:8,z=variant%2?3.2f:9;fn(self,world->level,x,z);capture.callCompleted=1;phase=101;if(ours&&c.control)self->m_isPathing=!self->m_isPathing;num(self->m_eAIState);num(self->m_isPathing);fp(self->m_pathGraceTime);vec(self->m_targetPosition);vec(self->m_pathDestination);num(self->m_bBaseUnitFlag19B);num(self->m_pathfinder?self->m_pathfinder->m_bIgnoreOccupancy:0);path(self->m_movementPath);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_destination_runtime){initEmptyGlobals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);CStringTranslate translate(L"");menugui::Fixture gui(*native.settings,native.scene);menu=&gui;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_destination_runtime",(uintptr_t)&cdOld);for(unsigned i=0;i<768;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    destination seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length&&j<400;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    destination negative detected%u\n",unsigned(caught));return failures;}
