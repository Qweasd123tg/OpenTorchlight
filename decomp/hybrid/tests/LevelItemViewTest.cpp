#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "Hierarchy.h"
#include <limits>
TL_ORIGINAL(CItem*,ivOld,(CLevel*,const Ogre::Matrix4&,float,float),"_ZN6CLevel18findItemWithinViewERKN4Ogre7Matrix4Eff")
extern "C" CItem*ivNew(CLevel*,const Ogre::Matrix4&,float,float) __asm__("_ZN6CLevel18findItemWithinViewERKN4Ogre7Matrix4Eff");
TL_FUNCTION(ivSight,"_ZN6CLevel17sightUnobstructedERKN4Ogre7Vector3ES3_b")
namespace {
autotest::Capture*output;CLevel*level;Ogre::SceneManager*scene;unsigned seed,calls;
void number(unsigned x){output->add(&x,4);}void vector(const Ogre::Vector3&v){output->add(&v,sizeof v);}
struct Item:finishlevel::Item{unsigned index;Item(CResourceManager*r,unsigned i):finishlevel::Item(r),index(i){}virtual bool getEnabled(){number(1);number(index);number(m_bEnabled);return m_bEnabled;}};
bool sight(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,bool flag){number(2);number(p==level);vector(a);vector(b);number(flag);bool visible=(seed+calls++)%3!=0;number(visible);return visible;}
void execute(void*raw,autotest::Capture&out,bool ours){output=&out;seed=*static_cast<unsigned*>(raw);calls=0;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=scene;f.resources.m_pHierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;for(unsigned t=29;t<31;++t){f.resources.m_pHierarchy->m_parentTypes[t].clear();f.resources.m_pHierarchy->m_parentTypes[t].push_back(t);}
 Ogre::Matrix4 transform=Ogre::Matrix4::IDENTITY;float phase=float(seed%9)*.25f,c=::cosf(phase),s=::sinf(phase);float sx=seed%47?float(seed%3+1)*.5f:0.0f,sz=float(seed%4+1)*.25f;transform[0][0]=c*sx;transform[0][2]=s*sz;transform[2][0]=-s*sx;transform[2][2]=c*sz;transform[1][1]=.5f+float(seed%5);transform[0][3]=float(int(seed%7)-3);transform[1][3]=float(int(seed%11)-5)*.25f;transform[2][3]=float(int(seed%13)-6)*.5f;if(seed&64){transform[3][0]=.03125f;transform[3][2]=-.0625f;}
 const Ogre::Vector3 positions[]={Ogre::Vector3(0,0,0),Ogre::Vector3(0,9,1),Ogre::Vector3(1,0,0),Ogre::Vector3(-1,-9,1),Ogre::Vector3(1,100,-1),Ogre::Vector3(.5f,-100,.5f),Ogre::Vector3(.00001f,0,1),Ogre::Vector3(-.00001f,7,1)};
 Item*items[5];for(unsigned i=0;i<5;++i){items[i]=new Item(&f.resources,i);items[i]->m_bItemFlag1F0=(seed+i)%5!=0;items[i]->m_bInActiveRange=(seed/3+i)%4!=0;items[i]->setEnabled((seed/5+i)%3!=0);items[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>((seed/7+i)%4?29:30);items[i]->setPosition(transform*positions[(seed/11+i)%8]);}
 for(unsigned i=0;i<seed%9;++i)finishlevel::prepend(level->m_items,static_cast<CItem*>(items[(i+seed/9)%5]));
 float nan=std::numeric_limits<float>::quiet_NaN();const float angles[]={-1,0,15,45,89.999f,90,180,360,nan};const float ranges[]={-1,0,.5f,1,5,100,std::numeric_limits<float>::infinity(),nan};
 detour::Set hooks;TL_REDIRECT(hooks,ivSight,&sight);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef CItem*(*Fn)(CLevel*,const Ogre::Matrix4&,float,float);Fn fn=ours?ivNew:ivOld;if(!autotest::beginInvocation(out,fn))return;CItem*result=fn(level,transform,angles[seed%9],ranges[seed/9%8]);out.callCompleted=1;unsigned id=result?99:0;for(unsigned i=0;i<5;++i)if(result==items[i])id=i+1;number(id);number(calls);for(unsigned i=0;i<5;++i)delete items[i];
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;autotest::Coverage coverage("level_item_view",(uintptr_t)&ivOld);for(unsigned i=0;i<2304;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    item view seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_item_view){return systems_fixture::isolated(&run,host);}
