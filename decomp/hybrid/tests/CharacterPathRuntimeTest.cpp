#include <cstring>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Path.h"
#include "PathController.h"
#include "AIManager.h"
#undef private
#undef protected
#include "tests/NativeGameServices.h"
#include "tests/FinishLevelFixture.h"
TL_ORIGINAL(void,pathOldUpdate,(CCharacter*,float),"_ZN10CCharacter13updatePathingEf")
TL_ORIGINAL(void,pathOldFollow,(CCharacter*,bool),"_ZN10CCharacter19updatePathFollowingEb")
extern "C" void pathNewUpdate(CCharacter*,float) __asm__("_ZN10CCharacter13updatePathingEf");
extern "C" void pathNewFollow(CCharacter*,bool) __asm__("_ZN10CCharacter19updatePathFollowingEb");
TL_FUNCTION(pathTurn,"_ZN10CCharacter10turnTowardERKN4Ogre7Vector3Ef")
TL_FUNCTION(pathNext,"_ZN15CPathController21getNextPointAtPercentEfP9CBaseUnitb")
TL_FUNCTION(pathClosest,"_ZN15CPathController19getClosestPctOfPathERKN4Ogre7Vector3E")
TL_FUNCTION(pathDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(pathISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(pathFlag,"_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
namespace {
struct Case{unsigned op,seed,control;};unsigned seed;bool armed;autotest::Capture*out;finishlevel::Fixture*level;CCharacter*self;CPathController*followed;unsigned nextCalls;
void num(unsigned v){if(armed)out->add(&v,4);}void fp(float v){if(armed)out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}
void initEmptyGlobals(){
 const uintptr_t a[]={0x14286f0,0x1428720,0x1429ea0,0x1476060,0x14781e0,0x1479460,0x147c340,0x147e8e0,0x147fac0,0x1480a40,0x1482e00,0x1484120,0x14872e0,0x148e500,0x148f960,0x14afec0,0x14b3300,0x14b5868,0x14b58e8,0x14e68b0,0x14ee340,0x14f2668,0x1500740,0x1500820,0x15019a0,0x150b428,0x150c8a0,0x150c980};
 for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i){void*p;std::memcpy(&p,(void*)a[i],sizeof(p));if(!p)new((void*)a[i])std::string;}
 const uintptr_t b[]={0x14286f8,0x1428728,0x1429ea8,0x1476068,0x14781e8,0x1479468,0x147c348,0x147e8e8,0x147fac8,0x1480a48,0x1482e08,0x1484128,0x14872e8,0x148e508,0x148f968,0x14afec8,0x14b3308,0x14b5870,0x14b58f0,0x14e68b8,0x14ee348,0x14f2670,0x1500748,0x1500828,0x15019a8,0x150b430,0x150c8a8,0x150c988};
 for(unsigned i=0;i<sizeof(b)/sizeof(b[0]);++i){void*p;std::memcpy(&p,(void*)b[i],sizeof(p));if(!p)new((void*)b[i])std::wstring;}
}

void turn(CCharacter*p,const Ogre::Vector3&v,float elapsed){num(101);vec(v);fp(elapsed);p->m_targetDirection=v;}
Ogre::Vector3 next(CPathController*p,float percent,CBaseUnit*unit,bool forward){num(103);num(p==followed);fp(percent);num(unit==self);num(forward);++nextCalls;const float d[]={0,.5f,1,1.4142135f,1.4142137f,2,4};return self->m_vPosition+Ogre::Vector3(d[(seed/3)%7],-37,d[(seed/7)%7]);}
float closest(CPathController*p,const Ogre::Vector3&v){num(107);num(p==followed);vec(v);const float pct[]={-.1f,0,.01f,.05f,.9f,.95f,1,1.1f};return pct[(seed/5)%8];}
void destination(CCharacter*p,CLevel&l,float x,float z){num(109);num(&l==&level->level);fp(x);fp(z);p->m_pathDestination=Ogre::Vector3(x,0,z);p->m_isPathing=seed%5!=0;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(113);num(p==self);num(type);return type==28&&seed%7==0;}
bool flag(CAIManager*,EAIFLAG_TYPES type){num(127);num(type);return seed%3==0;}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual bool getEnabled(){num(131);return seed%5!=0;}virtual void setPathToFollow(CPathController*p){num(137);num(p==followed);CCharacter::setPathToFollow(p);}};
class Controller:public CPathController{public:Controller():CPathController(NULL){}virtual void BroadcastEvent(unsigned int event){num(139);num(event);}};
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;out=&capture;armed=false;nextCalls=0;self=new Character;self->m_pResourceManager=&level->resources;self->m_vPosition=Ogre::Vector3(float(int(seed%9)-4),float(seed%3),float(int(seed%11)-5));self->m_isPathing=seed%4!=0;self->m_pathGraceTime=-7;self->m_pathDestination=Ogre::Vector3(5,6,7);self->m_targetDirection=Ogre::Vector3(8,9,10);const float vertical[]={-10,-1,0,1,10};self->m_movement=Ogre::Vector3(17,vertical[seed%5],19);self->m_returningToTown=seed&1;self->m_groundFlag=seed%3!=0;self->m_walkingSpeed=seed%3+1;self->m_runningSpeed=seed%7-2.0f;const float scales[]={0,.5f,1,2};float scale=scales[(seed/5)%4];std::memcpy(self->m_Padding25C,&scale,sizeof(scale));Ogre::Vector3 normal=seed%3==0?Ogre::Vector3(0,1,0):seed%3==1?Ogre::Vector3(.6f,.8f,0):Ogre::Vector3(0,.8f,.6f);std::memcpy(self->m_Padding6D4+4,&normal,sizeof(normal));self->m_pAIManager=seed%4?new CAIManager(self):NULL;
 followed=new Controller;followed->m_bUnknown136=(seed/3)%2;followed->m_bUnitRunsOnPath=seed%3==0;self->m_pathToFollow.setObject(seed%11?followed:NULL);const float pct[]={-.1f,0,.01f,.05f,.9f,.95f,1,1.1f};self->m_pathTime=pct[(seed/7)%8];self->m_Padding770=(seed/2)%2;self->m_keepPathWhenAIChanges=seed&1;
 delete self->m_movementPath;self->m_movementPath=new CPath("fixture path",seed%3==0,Ogre::Vector3(0,0,0));float length=seed%8==0?.4f:float(seed%9+1);self->m_movementPath->AddPoint(Ogre::Vector3(0,0,0),1,1);self->m_movementPath->AddPoint(Ogre::Vector3(length,0,length),1,1);if(seed&1)self->m_movementPath->AddPoint(Ogre::Vector3(length*2,0,0),1,1);self->m_pathToFollow.getObject();
 detour::Set patches;TL_REDIRECT(patches,pathTurn,&turn);TL_REDIRECT(patches,pathDestination,&destination);TL_REDIRECT(patches,pathISA,&isa);TL_REDIRECT(patches,pathFlag,&flag);TL_REDIRECT(patches,pathNext,&next);TL_REDIRECT(patches,pathClosest,&closest);if(patches.failed())_exit(43);armed=true;
 if(c.op==0){const float times[]={0,.016f,.25f,1,5};typedef void(*F)(CCharacter*,float);F fn=ours?pathNewUpdate:pathOldUpdate;autotest::invoke(capture,fn,self,times[(seed/3)%5]);}
 else{typedef void(*F)(CCharacter*,bool);F fn=ours?pathNewFollow:pathOldFollow;autotest::invoke(capture,fn,self,(seed/13)%2!=0);}
 if(ours&&c.control)self->m_isPathing=!self->m_isPathing;num(self->m_isPathing);vec(self->m_pathDestination);vec(self->m_movement);vec(self->m_targetDirection);fp(self->m_pathGraceTime);fp(self->m_pathTime);num(self->m_Padding770);num(self->m_returningToTown);num(self->m_pathToFollow.getObject()==followed);num(followed->m_bUnknown136);num(nextCalls);armed=false;}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op){int failures=0;const uintptr_t address[]={(uintptr_t)&pathOldUpdate,(uintptr_t)&pathOldFollow};autotest::Coverage coverage("character_path_runtime",address[op]);for(unsigned i=0;i<4096;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    path op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    path op%u negative detected%u\n",op,unsigned(caught));return failures;}
}
TL_TEST(character_path_runtime){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;finishlevel::Fixture ownedLevel;ownedLevel.resources.m_pSceneManager=native.scene;ownedLevel.resources.m_pLevel=&ownedLevel.level;level=&ownedLevel;int failures=run(host,0);if(!failures)failures+=run(host,1);return failures;}
