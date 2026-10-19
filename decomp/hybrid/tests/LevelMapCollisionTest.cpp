#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,mcOldDec,(CLevel*,const Ogre::AxisAlignedBox&,CBaseUnit*),"_ZN6CLevel32decrementMapPassabilityCollisionERKN4Ogre14AxisAlignedBoxEP9CBaseUnit")
extern "C" void mcNewDec(CLevel*,const Ogre::AxisAlignedBox&,CBaseUnit*) __asm__("_ZN6CLevel32decrementMapPassabilityCollisionERKN4Ogre14AxisAlignedBoxEP9CBaseUnit");
TL_ORIGINAL(void,mcOldInc,(CLevel*,const Ogre::AxisAlignedBox&,CBaseUnit*),"_ZN6CLevel32incrementMapPassabilityCollisionERKN4Ogre14AxisAlignedBoxEP9CBaseUnit")
extern "C" void mcNewInc(CLevel*,const Ogre::AxisAlignedBox&,CBaseUnit*) __asm__("_ZN6CLevel32incrementMapPassabilityCollisionERKN4Ogre14AxisAlignedBoxEP9CBaseUnit");
TL_FUNCTION(mcRay,"_ZN9CBaseUnit12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*output;CLevel*level;CBaseUnit*actor;CCollisionList*collision;Ogre::SceneManager*scene;unsigned seed,calls;
void number(unsigned x){output->add(&x,4);}void vector(const Ogre::Vector3&v){output->add(&v,sizeof v);}
bool ray(CBaseUnit*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,bool flag){number(1);number(p==actor);vector(a);vector(b);number(&a!=&b);number(&hit!=&normal);number(flag);bool result=(seed+calls)%3!=0;++calls;hit=Ogre::Vector3(3,-4,5);normal=Ogre::Vector3(0,1,0);if((seed&32)&&calls==1)level->m_collisionList=level->m_collisionList?NULL:collision;number(result);return result;}
void execute(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;calls=0;output=&out;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=scene;finishlevel::Item item(&f.resources);actor=&item;CCollisionList native;collision=&native;level->m_collisionList=seed&1?collision:NULL;level->m_topLeftX=float(int(seed%7)-3)*.25f;level->m_topLeftY=float(int(seed%9)-4)*.125f;
 if(level->m_mapPassability||level->m_objectPassability)std::abort();level->m_passWidth=seed%10;level->m_passHeight=seed/10%10;level->m_mapPassability=new short*[level->m_passWidth];const short initial[]={0,1,-1,32767,-32768,51};for(unsigned x=0;x<level->m_passWidth;++x){level->m_mapPassability[x]=new short[level->m_passHeight];for(unsigned z=0;z<level->m_passHeight;++z)level->m_mapPassability[x][z]=initial[(x+z+seed)%6];}
 const float limits[]={-4,-.8f,-.40001f,-.4f,-.00001f,0,.39999f,.4f,.80001f,1.2f,2.4f,4};float x0=limits[seed%12],z0=limits[seed/12%12],x1=limits[seed/144%12],z1=limits[(seed/7+5)%12];if(x0>x1)std::swap(x0,x1);if(z0>z1)std::swap(z0,z1);Ogre::AxisAlignedBox box(Ogre::Vector3(x0,-9,z0),Ogre::Vector3(x1,11,z1));
 detour::Set hooks;TL_REDIRECT(hooks,mcRay,&ray);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLevel*,const Ogre::AxisAlignedBox&,CBaseUnit*);Fn fn=c.mode?(ours?mcNewInc:mcOldInc):(ours?mcNewDec:mcOldDec);if(!autotest::beginInvocation(out,fn))return;fn(level,box,actor);out.callCompleted=1;number(calls);number(level->m_collisionList!=NULL);for(unsigned x=0;x<level->m_passWidth;++x)out.add(level->m_mapPassability[x],level->m_passHeight*sizeof(short));level->m_collisionList=NULL;
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;for(unsigned mode=0;mode<2;++mode){autotest::Coverage coverage("level_map_collision",mode?(uintptr_t)&mcOldInc:(uintptr_t)&mcOldDec);for(unsigned i=0;i<1024;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    collision mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);}return 0;}
}
TL_TEST(level_map_collision){return systems_fixture::isolated(&run,host);}
