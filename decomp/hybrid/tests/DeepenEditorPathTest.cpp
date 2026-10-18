#include <string>
#include <vector>
#include "AutoTest.h"
#include "Path.h"
TL_ORIGINAL(void,dpOldAdd,(CPath*,const Ogre::Vector3&,float,float),"_ZN5CPath8AddPointERKN4Ogre7Vector3Eff")
extern "C" void dpNewAdd(CPath*,const Ogre::Vector3&,float,float) __asm__("_ZN5CPath8AddPointERKN4Ogre7Vector3Eff");
TL_ORIGINAL(void,dpOldCopy,(CPath*,CPath&),"_ZN5CPathC1ERS_")
extern "C" void dpNewCopy(CPath*,CPath&) __asm__("_ZN5CPathC1ERS_");
namespace {
struct Case{unsigned mode,seed;};void n(autotest::Capture&o,unsigned x){o.add(&x,4);}void captureFloats(autotest::Capture&o,const std::vector<float>&v){n(o,v.size());for(unsigned i=0;i<v.size();++i)o.add(&v[i],4);}
void snapshot(autotest::Capture&o,CPath&p){o.addText(p.m_sObjectName);o.addText(p.m_sName);o.add(&p.m_fPathLength,4);o.add(&p.m_vOrigin,12);o.add(&p.m_vMinimum,12);o.add(&p.m_vMaximum,12);o.add(&p.m_bClosedPath,1);n(o,p.m_lPoints.size());for(unsigned i=0;i<p.m_lPoints.size();++i)o.add(&p.m_lPoints[i],12);captureFloats(o,p.m_lRadiusLeft);captureFloats(o,p.m_lRadiusRight);captureFloats(o,p.m_lPointDistance);captureFloats(o,p.m_lSegmentAngle);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);unsigned seed=c.seed;CPath source(std::string(seed%3+1,'s'),seed&1,Ogre::Vector3(1.25f,-3.5f,17.75f));source.m_sObjectName=std::string(seed%5,'o');source.m_vMinimum=Ogre::Vector3(-1,-2,-3);source.m_vMaximum=Ogre::Vector3(1,2,3);if(seed&4){source.m_lPoints.reserve(16);source.m_lPointDistance.reserve(16);source.m_lSegmentAngle.reserve(16);source.m_lRadiusLeft.reserve(16);source.m_lRadiusRight.reserve(16);}for(unsigned i=0;i<seed%7;++i){Ogre::Vector3 p(i%3==0?0.0f:i*0.25f,(i*i)%3*0.5f,-float(i));if(seed%9==0&&i>0)p=source.m_lPoints.back();dpOldAdd(&source,p,-float(i)-0.5f,float(i)+0.25f);}
 if(c.mode==0){Ogre::Vector3 external(float(seed%3)-1.5f,float(seed%5)*0.125f,float(seed%7));if(seed%11==0)external=Ogre::Vector3(1e-10f,0,0);const Ogre::Vector3&point=(seed&2)&&!source.m_lPoints.empty()?source.m_lPoints[seed%source.m_lPoints.size()]:external;typedef void(*Fn)(CPath*,const Ogre::Vector3&,float,float);Fn fn=ours?dpNewAdd:dpOldAdd;if(!autotest::beginInvocation(out,fn))return;fn(&source,point,-float(seed)*0.25f,float(seed)*0.75f);out.callCompleted=1;snapshot(out,source);}
 else{if(seed%3==0&&!source.m_lRadiusLeft.empty())source.m_lRadiusLeft.pop_back();if(seed%5==0&&!source.m_lRadiusRight.empty())source.m_lRadiusRight.clear();uint64_t memory[(sizeof(CPath)+7)/8];CPath*p=reinterpret_cast<CPath*>(memory);typedef void(*Fn)(CPath*,CPath&);Fn fn=ours?dpNewCopy:dpOldCopy;if(!autotest::beginInvocation(out,fn))return;fn(p,source);out.callCompleted=1;snapshot(out,*p);snapshot(out,source);p->~CPath();}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<80;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    path mode%u seed%u issue%u/%u exit%d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_path_add){return run(host,0,"deepen_editor_path_add",(uintptr_t)&dpOldAdd);}
TL_TEST(deepen_editor_path_copy){return run(host,1,"deepen_editor_path_copy",(uintptr_t)&dpOldCopy);}
