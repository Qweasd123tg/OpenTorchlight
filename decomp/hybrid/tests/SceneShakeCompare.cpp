#include "SmallMassCompare.h"
#include "CameraShake.h"
#include "CameraControl.h"
#include "Graph.h"
#include "SafePointer.h"
#include <new>
TL_ORIGINAL(void, ctorOriginal,(void*,const std::wstring&,Ogre::Vector3,float),"_ZN12CCameraShakeC1ERKSbIwSt11char_traitsIwESaIwEEN4Ogre7Vector3Ef")
extern "C" void ctorCandidate(void*,const std::wstring&,Ogre::Vector3,float) __asm__("_ZN12CCameraShakeC1ERKSbIwSt11char_traitsIwESaIwEEN4Ogre7Vector3Ef");
TL_ORIGINAL(void, defaultOriginal,(void*),"_ZN12CCameraShakeC1Ev")
extern "C" void defaultCandidate(void*) __asm__("_ZN12CCameraShakeC1Ev");
TL_ORIGINAL(void, dtorOriginal,(void*),"_ZN12CCameraShakeD1Ev")
extern "C" void dtorCandidate(void*) __asm__("_ZN12CCameraShakeD1Ev");
TL_ORIGINAL(void, startOriginal,(void*,const Ogre::Vector3&,bool),"_ZN12CCameraShake16startCameraShakeERKN4Ogre7Vector3Eb")
extern "C" void startCandidate(void*,const Ogre::Vector3&,bool) __asm__("_ZN12CCameraShake16startCameraShakeERKN4Ogre7Vector3Eb");
TL_ORIGINAL(void, graphCtorOriginal,(void*,int,std::wstring,unsigned),"_ZN6CGraphC1E12EGRAPH_TYPESSbIwSt11char_traitsIwESaIwEEj")
TL_ORIGINAL(void, graphDtorOriginal,(void*),"_ZN6CGraphD1Ev")
TL_FUNCTION(cameraSingleton,"_ZN14CCameraControl12getSingletonEv")
TL_FUNCTION(graphSingleton,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(getGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
namespace {
using namespace smallmass;CCameraControl* camera;CGraph* graph;void* manager;unsigned calls;
void* cameraInstance(){event(1,camera);++calls;return camera;}
void* graphInstance(){event(2,manager);++calls;return manager;}
CGraph* get(void* p,const std::wstring& name){event(3,p);text(name);++calls;return input->index%5?graph:NULL;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;CCameraShake* self=static_cast<CCameraShake*>(object(sizeof(CCameraShake)));camera=static_cast<CCameraControl*>(object(sizeof(CCameraControl)));graph=static_cast<CGraph*>(object(sizeof(CGraph)));manager=object(0x20);graphCtorOriginal(graph,0,L"test",0);new(&camera->m_cameraShakes)TArrayList<TSafePointer<CCameraShake>*>(2);new(&camera->m_cameraShakesSecondary)TArrayList<TSafePointer<CCameraShake>*>(3);
 detour::Set p;TL_REDIRECT(p,cameraSingleton,&cameraInstance);TL_REDIRECT(p,graphSingleton,&graphInstance);TL_REDIRECT(p,getGraph,&get);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 int before=g_iTotalCountOfObjects;
 if(c.op==0){std::wstring name=c.index%3?L"CameraTest":L"";Ogre::Vector3 direction(c.index*.125f,-1,3);autotest::invoke(out,ours?ctorCandidate:ctorOriginal,self,name,direction,c.index*.25f);floating(self->m_fDuration);floating(self->m_fElapsedTime);floating(self->m_fMagnitudeMultiplier);floating(self->m_fDirectionX);floating(self->m_fDirectionY);floating(self->m_fDirectionZ);number(self->m_graph.getObject()==graph);text(self->m_strCameraShakeName);number(self->m_nDirectionOrientation);floating(self->m_fCameraPositionX);floating(self->m_fCameraPositionY);floating(self->m_fCameraPositionZ);number(self->m_bCameraShakeActive);number(self->m_bCameraFallsOffWithDistance);number(g_iTotalCountOfObjects-before);if(g_iTotalCountOfObjects!=before+1)out.issue=autotest::Capture::InvalidReport;}
 else if(c.op==3){autotest::invoke(out,ours?defaultCandidate:defaultOriginal,self);floating(self->m_fDuration);floating(self->m_fElapsedTime);floating(self->m_fMagnitudeMultiplier);floating(self->m_fDirectionX);floating(self->m_fDirectionY);floating(self->m_fDirectionZ);number(self->m_graph.getObject()==NULL);text(self->m_strCameraShakeName);number(self->m_nDirectionOrientation);floating(self->m_fCameraPositionX);floating(self->m_fCameraPositionY);floating(self->m_fCameraPositionZ);number(self->m_bCameraShakeActive);number(self->m_bCameraFallsOffWithDistance);number(g_iTotalCountOfObjects-before);}
 else {defaultOriginal(self);if(c.index%3)self->m_graph.setObject(graph);self->m_strCameraShakeName=c.index%2?L"A nonempty shake name":L"";}
 TSafePointer<CCameraShake> reference;reference.setObject(self);
 if(c.op==2){unsigned n=c.index%4;for(unsigned i=0;i<n;++i){TSafePointer<CCameraShake>* r=OGRE_NEW_T(TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL)();r->setObject(self);camera->m_cameraShakes.add(r);}Ogre::Vector3 position(c.index,-2,4);autotest::invoke(out,ours?startCandidate:startOriginal,self,position,bool(c.index&1));floating(self->m_fCameraPositionX);floating(self->m_fCameraPositionY);floating(self->m_fCameraPositionZ);number(self->m_bCameraShakeActive);number(camera->m_cameraShakes.size());number(camera->m_cameraShakesSecondary.size());for(unsigned i=0;i<camera->m_cameraShakes.size();++i)number(camera->m_cameraShakes[i]->getObject()==self);for(unsigned i=0;i<camera->m_cameraShakesSecondary.size();++i)number(camera->m_cameraShakesSecondary[i]->getObject()==self);}
 int constructed=g_iTotalCountOfObjects;
 if(c.op==1)autotest::invoke(out,ours?dtorCandidate:dtorOriginal,self);else dtorOriginal(self);
 number(reference.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);for(unsigned i=0;i<camera->m_cameraShakes.size();++i){number(camera->m_cameraShakes[i]->getObject()==NULL);OGRE_DELETE_T(camera->m_cameraShakes[i],TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL);}for(unsigned i=0;i<camera->m_cameraShakesSecondary.size();++i){number(camera->m_cameraShakesSecondary[i]->getObject()==NULL);OGRE_DELETE_T(camera->m_cameraShakesSecondary[i],TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL);}if(reference.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;
 camera->m_cameraShakes.~TArrayList();camera->m_cameraShakesSecondary.~TArrayList();graphDtorOriginal(graph);number(calls);out.addHeapInUse();
}
}
TL_TEST(scene_shake_construct){return smallmass::run(host,0,"scene_shake_construct",(uintptr_t)ctorOriginal,execute,24);}
TL_TEST(scene_shake_destroy){return smallmass::run(host,1,"scene_shake_destroy",(uintptr_t)dtorOriginal,execute,24);}
TL_TEST(scene_shake_start){return smallmass::run(host,2,"scene_shake_start",(uintptr_t)startOriginal,execute,32);}

TL_TEST(scene_shake_default){return smallmass::run(host,3,"scene_shake_default",(uintptr_t)defaultOriginal,execute,24);}
