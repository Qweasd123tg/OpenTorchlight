#include <cstring>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "GenericModel.h"
#include "Path.h"
#include "DataGroup.h"
#include "TRepository.h"
#undef private
#undef protected
#include "NativeMenuServices.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(bool,cjOld,(CCharacter*),"_ZN10CCharacter15attemptJumpDownEv")
extern "C" bool cjNew(CCharacter*) __asm__("_ZN10CCharacter15attemptJumpDownEv");
TL_FUNCTION(cjExists,"_ZNK13CGenericModel15animationExistsERKSs")
TL_FUNCTION(cjSight,"_ZN10CCharacter10sightRangeEv")
TL_FUNCTION(cjSphere,"_ZN6CLevel15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_RjS4_")
TL_FUNCTION(cjOpen,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(cjRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_FUNCTION(cjRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(cjLength,"_ZNK13CGenericModel25getAnimationLengthSecondsERKSs")
TL_FUNCTION(cjBlend,"_ZN10CCharacter14blendAnimationERKSsbfff")
TL_FUNCTION(cjQueue,"_ZN10CCharacter19queueBlendAnimationERKSsbff")
TL_FUNCTION(cjAllow,"_ZN10CCharacter16setAllowJumpDownEb")
namespace {
struct Case{unsigned seed,control;};unsigned seed,mode,variant,phase;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;finishlevel::Fixture*world;CCharacter*self,*target;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-jump-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void narrow(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setAIState(EAIState state){num(101);num(state);m_eAIState=state;}};
bool exists(CGenericModel*p,const std::string&name){num(103);num(p==self->m_pUnitModel);narrow(name);return mode!=1;}
float sight(CCharacter*p){num(107);num(p==self);return mode==2?.01f:100;}
bool sphere(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float radius,Ogre::Vector3&position,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&material,Ogre::Vector3&other){num(109);num(p==&world->level);vec(a);vec(b);fp(radius);return mode==3;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&v,float radius,bool flag){num(113);num(p==&world->level);vec(v);fp(radius);num(flag);return mode==4?v:v+Ogre::Vector3(1,0,2);}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&material,Ogre::Vector3&other,bool flag){num(127);num(p==&world->level);vec(a);vec(b);num(flag);float drops[]={.5f,.8f,6.5f,7,2,4};float drop=mode==6?drops[variant%4]:drops[4+variant%2];hit=Ogre::Vector3(a.x,self->m_vPosition.y-drop,a.z);normal=Ogre::Vector3(0,mode==8?(variant%2?.8f:.5f):1,0);material=mode==7?100:3;other=Ogre::Vector3::ZERO;return mode!=5;}
float random(float minimum,float maximum){num(131);fp(minimum);fp(maximum);return minimum+(maximum-minimum)*float(variant%5)*.25f;}
float length(CGenericModel*p,const std::string&name){num(137);num(p==self->m_pUnitModel);narrow(name);return .5f+float(variant%5);}
void blend(CCharacter*p,const std::string&name,bool loop,float amount,float speed,float length){num(139);num(p==self);narrow(name);num(loop);fp(amount);fp(speed);fp(length);}
void queue(CCharacter*p,const std::string&name,bool loop,float amount,float speed){num(149);num(p==self);narrow(name);num(loop);fp(amount);fp(speed);}
void allow(CCharacter*p,bool flag){num(151);num(p==self);num(flag);p->m_allowJumpDown=flag;}
void path(CPath*p){num(p!=NULL);if(!p)return;num(p->m_lPoints.size());fp(p->m_fPathLength);for(unsigned i=0;i<p->m_lPoints.size();++i)vec(p->m_lPoints[i]);num(p->m_lRadiusLeft.size());for(unsigned i=0;i<p->m_lRadiusLeft.size();++i)fp(p->m_lRadiusLeft[i]);num(p->m_lRadiusRight.size());for(unsigned i=0;i<p->m_lRadiusRight.size();++i)fp(p->m_lRadiusRight[i]);num(p->m_lSegmentAngle.size());for(unsigned i=0;i<p->m_lSegmentAngle.size();++i)fp(p->m_lSegmentAngle[i]);num(p->m_lPointDistance.size());for(unsigned i=0;i<p->m_lPointDistance.size();++i)fp(p->m_lPointDistance[i]);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%16;variant=seed/16;phase=1;oursSide=ours;armed=false;out=&capture;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);self=new Actor;target=new CCharacter(NULL);self->m_pResourceManager=&world->resources;self->m_pUnitModel=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));self->m_targetCharacter.setObject(mode==0?NULL:target);self->m_vPosition=Ogre::Vector3(1,10,-2);target->m_vPosition=Ogre::Vector3(variant%7+1,20,variant%5-2.0f);self->m_fBaseUnitValue194=.25f*float(variant%5);self->m_isPathing=variant&1;self->m_pathGraceTime=-3;self->m_pathDestination=Ogre::Vector3(-4,-5,-6);self->m_allowJumpDown=true;self->m_deathPathActive=false;self->m_deathPathSilent=variant&2;self->m_deathPathDistance=12;self->m_deathPathSpeed=13;self->m_pDataGroup=new CDataGroup(L"jump",NULL,4,4,new TRepository<std::wstring>(L""));if(variant%3)self->m_pDataGroup->AddDataValue(L"JUMP_SPEED",float(variant%4)*.5f);if(variant&4){self->m_deathPath=new CPath("old",false,Ogre::Vector3::ZERO);self->m_deathPath->AddPoint(Ogre::Vector3(2,3,4),-1,1);self->m_deathPath->AddPoint(Ogre::Vector3(5,6,7),-1,1);}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,cj##name,&fn)
 P(Exists,exists);P(Sight,sight);P(Sphere,sphere);P(Open,open);P(Ray,ray);P(Random,random);P(Length,length);P(Blend,blend);P(Queue,queue);P(Allow,allow);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef bool(*F)(CCharacter*);F fn=ours?cjNew:cjOld;if(!autotest::beginInvocation(capture,fn))return;bool result=fn(self);capture.callCompleted=1;phase=101;if(ours&&c.control)result=!result;num(result);num(self->m_isPathing);num(self->m_allowJumpDown);num(self->m_deathPathActive);num(self->m_deathPathSilent);num(self->m_eAIState);fp(self->m_pathGraceTime);fp(self->m_deathPathDistance);fp(self->m_deathPathSpeed);vec(self->m_pathDestination);path(self->m_deathPath);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_jump_runtime){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_jump_runtime",(uintptr_t)&cjOld);for(unsigned i=0;i<512;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    jump seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length&&j<400;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    jump negative detected%u\n",unsigned(caught));return failures;}
