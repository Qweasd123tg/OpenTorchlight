#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include <new>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Layout.h"
#include "Timeline.h"
#include "ParticleTechWrapper.h"
#include "SoundObject.h"
#include "CameraShake.h"
#include "CameraControl.h"
#undef private
#undef protected
TL_ORIGINAL(void,aeOldLayoutCreated,(CLayout*,CEditorBaseObject*),"_ZN7CLayout19editorObjectCreatedEP17CEditorBaseObject")
extern "C" void aeNewLayoutCreated(CLayout*,CEditorBaseObject*) __asm__("_ZN7CLayout19editorObjectCreatedEP17CEditorBaseObject");
TL_ORIGINAL(void,aeOldLayoutCall,(CLayout*,unsigned,bool),"_ZN7CLayout21callFunctionOnObjectsENS_22ELAYOUT_FUNCTION_TYPESEb")
extern "C" void aeNewLayoutCall(CLayout*,unsigned,bool) __asm__("_ZN7CLayout21callFunctionOnObjectsENS_22ELAYOUT_FUNCTION_TYPESEb");
#define FN(n,s) TL_FUNCTION(n,s)
FN(aePStart,"_ZN9CParticle5StartEv") FN(aePStop,"_ZN9CParticle4StopEb") FN(aePPause,"_ZN9CParticle5PauseEv") FN(aePResume,"_ZN9CParticle6ResumeEv")
FN(aeUPause,"_ZN16ParticleUniverse14ParticleSystem5pauseEv") FN(aeUResume,"_ZN16ParticleUniverse14ParticleSystem6resumeEv")
FN(aeSPlay,"_ZN12CSoundObject4playEv") FN(aeSStop,"_ZN12CSoundObject4stopEv") FN(aeSPause,"_ZN12CSoundObject5pauseEv") FN(aeSResume,"_ZN12CSoundObject6resumeEv") FN(aeSLoop,"_ZN12CSoundObject9isLoopingEv")
FN(aeTPlay,"_ZN9CTimeline4PlayEb") FN(aeTStop,"_ZN9CTimeline4StopEv") FN(aeTPause,"_ZN9CTimeline5PauseEv") FN(aeTBack,"_ZN9CTimeline14Play_BackwardsEv") FN(aeTReset,"_ZN9CTimeline18Reset_To_BeginningEv") FN(aeTEnd,"_ZN9CTimeline12Reset_To_EndEv") FN(aeTEnabled,"_ZN9CTimeline10SetEnabledEb")
FN(aeLayoutPosition,"_ZN19CPositionableObject11getPositionEb") FN(aeLayoutCamera,"_ZN16CResourceManager16getCameraControlEv") FN(aeLayoutSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
extern "C" char aeLayoutAllocate[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char aeLBaseTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" char aeLTechTable[] __asm__("_ZTV20CParticleTechWrapper");
extern "C" char aeLSoundTable[] __asm__("_ZTV12CSoundObject");
extern "C" char aeLShakeTable[] __asm__("_ZTV12CCameraShake");
extern "C" char aeLTimeTable[] __asm__("_ZTV9CTimeline");
namespace {
struct Case{unsigned op,kind,type,variant,function;};autotest::Capture*output;Case input;CLayout*layout;CEditorBaseObject*object;void*particle;void*universe;CCameraControl*camera;void*resources;void*owner;uint64_t safeMemory[4];unsigned calls;
void number(unsigned x){output->add(&x,4);}void check(bool x){number(x);if(!x)output->issue=autotest::Capture::InvalidReport;}
void event(unsigned code,void*p){number(code);check(p==object||p==particle||p==universe||p==layout);++calls;if(input.variant==5&&calls==1)layout->m_Unknown1D0.clear();}
void parent(void*p,CPositionableObject*q){event(1,p);check(q==layout);if(input.variant==4)layout->m_Unknown1B8=static_cast<ELAYOUT_TYPES>(2);}
void broadcast(void*p,unsigned e){event(2,p);number(e);}void activated(void*p,bool x){event(3,p);number(x);}
void pstart(void*p){event(4,p);}void pstop(void*p,bool x){event(5,p);number(x);}void ppause(void*p){event(6,p);}void presume(void*p){event(7,p);}
void upause(void*p){event(8,p);}void uresume(void*p){event(9,p);}void splay(void*p){event(10,p);}void sstop(void*p){event(11,p);}void spause(void*p){event(12,p);}void sresume(void*p){event(13,p);}bool sloop(void*p){event(14,p);return input.variant&1;}
void tplay(void*p,bool x){event(15,p);number(x);}void tstop(void*p){event(16,p);}void tpause(void*p){event(17,p);}void tback(void*p){event(18,p);}void treset(void*p){event(19,p);}void tend(void*p){event(20,p);}void tenabled(void*p,bool x){event(21,p);number(x);}
Ogre::Vector3 position(void*p,bool absolute){event(22,p);number(absolute);return Ogre::Vector3(3.25f,-5.5f,7.75f);}
void*getCamera(void*p){number(23);check(p==resources);return camera;}
void*allocate(size_t size,const char*file,int line,const char*function){number(24);output->add(&size,sizeof(size));check(!file&&!line&&!function);std::memset(safeMemory,0x5a,sizeof(safeMemory));return safeMemory;}
unsigned safe(void*p,void*ref){event(25,p);check(ref==safeMemory);TSafePointer<CCameraShake>*s=static_cast<TSafePointer<CCameraShake>*>(ref);check(!s->getObject());number(s->m_nIndex);return 0x12340000u+input.variant;}
void side(void*raw,autotest::Capture&out,bool ours){input=*static_cast<Case*>(raw);output=&out;calls=0;uint64_t l[(sizeof(CLayout)+7)/8]={0},o[256]={0},cam[(sizeof(CCameraControl)+7)/8]={0},res[16]={0},own[128]={0},part[128]={0},pu[16]={0};layout=reinterpret_cast<CLayout*>(l);object=reinterpret_cast<CEditorBaseObject*>(o);camera=reinterpret_cast<CCameraControl*>(cam);resources=res;owner=own;particle=part;universe=pu;
 void*ltable[80]={0};ltable[6]=reinterpret_cast<void*>(&broadcast);*reinterpret_cast<void**>(layout)=ltable;
 char*table=input.kind==0?aeLBaseTable:input.kind==1?aeLTechTable:input.kind==2?aeLSoundTable:input.kind==3?aeLShakeTable:aeLTimeTable;
 void*otable[80]={0};unsigned entries=input.kind==0||input.kind==3||input.kind==4?10:80;std::memcpy(otable,table,entries*8);otable[2+2]=reinterpret_cast<void*>(&parent);otable[2+0x218/8]=reinterpret_cast<void*>(&activated);*reinterpret_cast<void**>(object)=otable+2;
 object->m_pParentPositionableObject=input.variant%3==0?NULL:input.variant%3==1?reinterpret_cast<CPositionableObject*>(owner):reinterpret_cast<CPositionableObject*>(part);layout->m_pSceneOwner=reinterpret_cast<CEditorScene*>(owner);layout->m_pResourceManager=reinterpret_cast<CResourceManager*>(resources);layout->m_Unknown1B8=static_cast<ELAYOUT_TYPES>(input.type);
 new(&layout->m_Unknown1D0)TArrayList<CEditorBaseObject*>(2);if(input.variant&1){layout->m_Unknown1D0.add(NULL);layout->m_Unknown1D0.add(object);}else if(input.variant==2)layout->m_Unknown1D0.add(NULL);
 if(input.op==1){layout->m_Unknown1D0.clear();if(input.variant!=0){layout->m_Unknown1D0.add(object);layout->m_Unknown1D0.add(NULL);}layout->m_pParticle=input.variant==6?reinterpret_cast<CParticle*>(particle):NULL;}
 if(input.op==1&&input.variant==4)layout->m_Unknown1D0.m_nCapacity=0;
 if(input.kind==1)reinterpret_cast<CParticleTechWrapper*>(object)->m_pParticleSystem=input.variant&1?reinterpret_cast<ParticleUniverse::ParticleSystem*>(universe):NULL;
 if(input.kind==2)reinterpret_cast<CSoundObject*>(object)->m_bSoundStartsOnActivated=input.variant&1;
 if(input.kind==4)reinterpret_cast<CTimeline*>(object)->m_bLayoutCanControl=input.variant&1;
 new(&camera->m_cameraShakesSecondary)TArrayList<TSafePointer<CCameraShake>*>(2);for(unsigned i=0;i<input.variant%3;++i)camera->m_cameraShakesSecondary.add(NULL);
 detour::Set d;TL_REDIRECT(d,aePStart,&pstart);TL_REDIRECT(d,aePStop,&pstop);TL_REDIRECT(d,aePPause,&ppause);TL_REDIRECT(d,aePResume,&presume);TL_REDIRECT(d,aeUPause,&upause);TL_REDIRECT(d,aeUResume,&uresume);TL_REDIRECT(d,aeSPlay,&splay);TL_REDIRECT(d,aeSStop,&sstop);TL_REDIRECT(d,aeSPause,&spause);TL_REDIRECT(d,aeSResume,&sresume);TL_REDIRECT(d,aeSLoop,&sloop);TL_REDIRECT(d,aeTPlay,&tplay);TL_REDIRECT(d,aeTStop,&tstop);TL_REDIRECT(d,aeTPause,&tpause);TL_REDIRECT(d,aeTBack,&tback);TL_REDIRECT(d,aeTReset,&treset);TL_REDIRECT(d,aeTEnd,&tend);TL_REDIRECT(d,aeTEnabled,&tenabled);TL_REDIRECT(d,aeLayoutPosition,&position);TL_REDIRECT(d,aeLayoutCamera,&getCamera);TL_REDIRECT(d,aeLayoutSafe,&safe);d.redirect(aeLayoutAllocate,aeLayoutAllocate,&allocate);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(input.op==0)autotest::invoke(out,ours?aeNewLayoutCreated:aeOldLayoutCreated,layout,object);else autotest::invoke(out,ours?aeNewLayoutCall:aeOldLayoutCall,layout,input.function,(input.variant&2)!=0);
 number(layout->m_Unknown1D0.size());number(layout->m_Unknown1D0.m_nCapacity);number(layout->m_Unknown1D0.m_nGrowBy);for(unsigned i=0;i<layout->m_Unknown1D0.size();++i)number(layout->m_Unknown1D0[i]==object?1:0);
 if(input.kind==4)number(reinterpret_cast<CTimeline*>(object)->m_bManualUpdate);
 if(input.kind==3){CCameraShake*shake=reinterpret_cast<CCameraShake*>(object);out.add(&shake->m_fCameraPositionX,12);number(shake->m_bCameraShakeActive);}
 number(camera->m_cameraShakesSecondary.size());number(camera->m_cameraShakesSecondary.m_nCapacity);number(camera->m_cameraShakesSecondary.m_nGrowBy);for(unsigned i=0;i<camera->m_cameraShakesSecondary.size();++i){TSafePointer<CCameraShake>*safe=camera->m_cameraShakesSecondary[i];number(safe!=NULL);if(safe){check(safe==reinterpret_cast<TSafePointer<CCameraShake>*>(safeMemory));check(safe->getObject()==object);number(safe->m_nIndex);}}
 camera->m_cameraShakesSecondary.~TArrayList<TSafePointer<CCameraShake>*>();layout->m_Unknown1D0.~TArrayList<CEditorBaseObject*>();
}
void old(void*p,autotest::Capture&c){side(p,c,false);}void newer(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uint64_t address){autotest::Coverage coverage(name,address);const unsigned functions[]={0,1,2,3,4,5,0xffffffffu};for(unsigned kind=0;kind<5;++kind)for(unsigned type=0;type<4;++type)for(unsigned variant=0;variant<7;++variant)for(unsigned f=0;f<(op?7u:1u);++f){Case c={op,kind,type,variant,functions[f]};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);if(coverage.observe(host,a,b)){host->log("    advance layout op%u kind%u type%u variant%u fn%u status%d/%d bytes%lu/%lu\n",op,kind,type,variant,c.function,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(advance_editor_layout_created){return run(host,0,"advance_editor_layout_created",(uint64_t)(uintptr_t)aeOldLayoutCreated);}
