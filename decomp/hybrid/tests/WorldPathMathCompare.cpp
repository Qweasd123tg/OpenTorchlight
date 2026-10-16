#include <string>
#include <new>
#include <cmath>
#include "AutoTest.h"
#include "Path.h"
TL_ORIGINAL(Ogre::Vector3, splineOriginal,(void*,float),"_ZN5CPath27GetSplinePositionAtDistanceEf")
extern "C" Ogre::Vector3 splineCandidate(void*,float) __asm__("_ZN5CPath27GetSplinePositionAtDistanceEf");
TL_ORIGINAL(bool, nearestOriginal,(void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,float&,float),"_ZN5CPath16FindNearestPointERKN4Ogre7Vector3ERS1_S4_RjRff")
extern "C" bool nearestCandidate(void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,float&,float) __asm__("_ZN5CPath16FindNearestPointERKN4Ogre7Vector3ERS1_S4_RjRff");
TL_ORIGINAL(void, pathCtorOriginal,(void*,const std::string&,bool,const Ogre::Vector3&),"_ZN5CPathC1ESsbRKN4Ogre7Vector3E")
TL_ORIGINAL(void, pathDtorOriginal,(void*),"_ZN5CPathD1Ev")
namespace {
struct Case{unsigned op,index;};
float bits(unsigned u){float v;std::memcpy(&v,&u,4);return v;}
void body(Case& c,bool ours,autotest::Capture& out){autotest::g_arenaUsed=0;CPath* p=static_cast<CPath*>(autotest::allocate(sizeof(CPath)));Ogre::Vector3 origin(float(c.index%3)-1,-3,4);std::string name="math path";bool closed=c.index%2;pathCtorOriginal(p,name,closed,origin);unsigned n=c.index%7;float length=0;
 for(unsigned i=0;i<n;++i){Ogre::Vector3 point(float(i)*1.25f,float((i*i)%5)*0.5f,-float(i%3)*0.75f);if(c.index%9==0&&i==1)point=p->m_lPoints[0];if(i)length+=(point-p->m_lPoints[i-1]).length();p->m_lPoints.push_back(point);p->m_lPointDistance.push_back(length);p->m_lRadiusLeft.push_back(-2);p->m_lRadiusRight.push_back(2);p->m_lSegmentAngle.push_back(0);}
 if(closed&&n>1)length+=(p->m_lPoints[n-1]-p->m_lPoints[0]).length();p->m_fPathLength=length;
 if(c.op==0){const float fractions[]={-2.25f,-0.25f,0,0.125f,0.25f,0.5f,0.75f,1,1.25f,2.25f};float distance=length*fractions[c.index/7%10];if(c.index%29==0&&closed)distance=bits(0x7fc12345);if(c.index%31==0&&closed)distance=bits(0x7f800000);Ogre::Vector3(*fn)(void*,float)=ours?splineCandidate:splineOriginal;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 value=fn(p,distance);out.callCompleted=1;out.add(&value,sizeof(value));}
 else{Ogre::Vector3 target(float(c.index%11)*0.75f-2,float(c.index%5)-1,float(c.index%7)*0.5f-3);target+=origin;if(c.index%17==0)target.x=1000000;if(c.index%23==0)target.z=bits(0x7fc12345);const float limits[]={-2,0,0.25f,0.5f,1,1.5f,2};float minimum=length*limits[c.index/7%7];if(c.index%19==0)minimum=bits(0x7fc12345);if(c.index%37==0)minimum=bits(0x7f800000);Ogre::Vector3 point(-17,18,-19),offset(21,-22,23);unsigned index=0xdeadbeef;float distance=-44.5f;bool(*fn)(void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,float&,float)=ours?nearestCandidate:nearestOriginal;if(!autotest::beginInvocation(out,fn))return;bool result=fn(p,target,point,offset,index,distance,minimum);out.callCompleted=1;out.add(&result,sizeof(result));out.add(&point,sizeof(point));out.add(&offset,sizeof(offset));out.add(&index,sizeof(index));out.add(&distance,sizeof(distance));}
 pathDtorOriginal(p);}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<280;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("world path math op %u case %u child %d/%d issue %u/%u\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=280||coverage.different||coverage.missing;}
}
TL_TEST(world_path_spline_position){return run(host,0,"world_path_spline_position",(uintptr_t)&splineOriginal);}
TL_TEST(world_path_nearest_point){return run(host,1,"world_path_nearest_point",(uintptr_t)&nearestOriginal);}
