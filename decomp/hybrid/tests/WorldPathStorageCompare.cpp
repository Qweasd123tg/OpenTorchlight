#include <string>
#include <stdexcept>
#include "AutoTest.h"
#include "Detour.h"
#include "Path.h"
TL_ORIGINAL(void, clearOriginal,(void*),"_ZN5CPath5ClearEv")
extern "C" void clearCandidate(void*) __asm__("_ZN5CPath5ClearEv");
TL_ORIGINAL(void, reverseOriginal,(void*),"_ZN5CPath7ReverseEv")
extern "C" void reverseCandidate(void*) __asm__("_ZN5CPath7ReverseEv");
TL_ORIGINAL(void, resizeOriginal,(void*,unsigned),"_ZN5CPath6ResizeEj")
extern "C" void resizeCandidate(void*,unsigned) __asm__("_ZN5CPath6ResizeEj");
TL_ORIGINAL(void, widthOriginal,(void*,CPath&,CPath&),"_ZN5CPath18CalculatePathWidthERS_S0_")
extern "C" void widthCandidate(void*,CPath&,CPath&) __asm__("_ZN5CPath18CalculatePathWidthERS_S0_");
TL_ORIGINAL(void, pathCtorOriginal,(void*,const std::string&,bool,const Ogre::Vector3&),"_ZN5CPathC1ESsbRKN4Ogre7Vector3E")
TL_ORIGINAL(void, pathDtorOriginal,(void*),"_ZN5CPathD1Ev")
TL_FUNCTION(addPointTarget,"_ZN5CPath8AddPointERKN4Ogre7Vector3Eff")
TL_FUNCTION(closeTarget,"_ZN5CPath9ClosePathEv")
TL_FUNCTION(nearestTarget,"_ZN5CPath16FindNearestPointERKN4Ogre7Vector3ERS1_S4_RjRff")
namespace {
struct Case{unsigned op,index;};Case* input;autotest::Capture* output;CPath* self;CPath* left;CPath* right;unsigned calls;
void invalid(){output->issue=autotest::Capture::InvalidReport;}void number(unsigned n){output->add(&n,sizeof(n));}void vector(const Ogre::Vector3& v){output->add(&v,sizeof(v));}
void add(void* p,const Ogre::Vector3& v,float a,float b){if(p!=self)invalid();number(1);vector(v);output->add(&a,4);output->add(&b,4);++calls;if(input->index%11==0&&calls==2)throw std::runtime_error("path rebuild");self->m_lPoints.push_back(v);self->m_lRadiusLeft.push_back(a);self->m_lRadiusRight.push_back(b);self->m_lPointDistance.push_back(calls*0.5f);self->m_lSegmentAngle.push_back(calls*0.25f);self->m_fPathLength+=0.5f;}
void close(void* p){number(2);if(p!=self)invalid();number(self->m_lPoints.size());++calls;self->m_fPathLength+=1.25f;}
bool nearest(void* p,const Ogre::Vector3& point,Ogre::Vector3& nearestPoint,Ogre::Vector3& offset,unsigned& index,float& distance,float maximum){number(3);number(p==left?0:1);vector(point);output->add(&maximum,4);++calls;if(p!=left&&p!=right)invalid();unsigned mode=(input->index+(p==right?2:0))%7;if(mode==0)return false;nearestPoint=point+Ogre::Vector3(mode%2?-3.0f:2.0f,99,mode%3?-1.0f:4.0f);offset=mode==1?Ogre::Vector3(0,0,0):mode==2?Ogre::Vector3(1e-15f,0,0):Ogre::Vector3(mode%2?-2.0f:3.0f,4,mode%3?-1.0f:2.0f);index=2;distance=0.5f;return true;}
void state(){number(self->m_lPoints.size());for(unsigned i=0;i<self->m_lPoints.size();++i)vector(self->m_lPoints[i]);const std::vector<float>* lists[]={&self->m_lRadiusLeft,&self->m_lRadiusRight,&self->m_lPointDistance,&self->m_lSegmentAngle};for(unsigned k=0;k<4;++k){number(lists[k]->size());for(unsigned i=0;i<lists[k]->size();++i)output->add(&(*lists[k])[i],4);}vector(self->m_vOrigin);output->add(&self->m_fPathLength,4);number(self->m_bClosedPath);number(calls);}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=static_cast<CPath*>(autotest::allocate(sizeof(CPath)));left=static_cast<CPath*>(autotest::allocate(sizeof(CPath)));right=static_cast<CPath*>(autotest::allocate(sizeof(CPath)));std::string name="path storage";Ogre::Vector3 origin(3,-4,2);pathCtorOriginal(self,name,c.index%2!=0,origin);pathCtorOriginal(left,name,false,origin);pathCtorOriginal(right,name,false,origin);unsigned n=c.index%8;for(unsigned i=0;i<n;++i){self->m_lPoints.push_back(Ogre::Vector3(float(i),float(i*i),-float(i)*0.125f));self->m_lRadiusLeft.push_back(-3-i);self->m_lRadiusRight.push_back(4+i);self->m_lPointDistance.push_back(i*1.5f);self->m_lSegmentAngle.push_back(i*0.25f);}self->m_fPathLength=12.5f;
 detour::Set patches;TL_REDIRECT(patches,addPointTarget,&add);TL_REDIRECT(patches,closeTarget,&close);TL_REDIRECT(patches,nearestTarget,&nearest);if(patches.failed()){invalid();return;}
 bool threw=false;
 if(c.op==0){void(*fn)(void*)=ours?clearCandidate:clearOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;}
 else if(c.op==1){void(*fn)(void*)=ours?reverseCandidate:reverseOriginal;if(!autotest::beginInvocation(out,fn))return;try{fn(self);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;}
 else if(c.op==2){unsigned count=c.index/8%10;void(*fn)(void*,unsigned)=ours?resizeCandidate:resizeOriginal;if(!autotest::beginInvocation(out,fn))return;try{fn(self,count);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;}
 else{void(*fn)(void*,CPath&,CPath&)=ours?widthCandidate:widthOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,*left,*right);out.callCompleted=1;}
 number(threw);state();patches.restore();pathDtorOriginal(self);pathDtorOriginal(left);pathDtorOriginal(right);}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<96;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("world path storage op %u case %u child %d/%d issue %u/%u\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=96||coverage.different||coverage.missing;}
}
TL_TEST(world_path_clear){return run(host,0,"world_path_clear",(uintptr_t)&clearOriginal);}
TL_TEST(world_path_reverse){return run(host,1,"world_path_reverse",(uintptr_t)&reverseOriginal);}
TL_TEST(world_path_resize){return run(host,2,"world_path_resize",(uintptr_t)&resizeOriginal);}
TL_TEST(world_path_width){return run(host,3,"world_path_width",(uintptr_t)&widthOriginal);}
