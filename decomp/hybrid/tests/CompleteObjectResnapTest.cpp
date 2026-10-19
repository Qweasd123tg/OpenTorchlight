#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "Editor.h"
#include "EditorObjectManager.h"
#include "ObjectControl3D.h"
#include "ResourceManager.h"
#undef protected
#undef private
#include "PositionableObject.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsNativeGame.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,rsOld,(CObjectControl3D*,TArrayList<CEditorBaseObject*>&,bool),"_ZN16CObjectControl3D13resnapObjectsER10TArrayListIP17CEditorBaseObjectEb")
extern "C" void rsNew(CObjectControl3D*,TArrayList<CEditorBaseObject*>&,bool) __asm__("_ZN16CObjectControl3D13resnapObjectsER10TArrayListIP17CEditorBaseObjectEb");
#include "NativeEditorControls.h"
namespace {
CObjectControl3D*control;CEditorObjectManager*manager;
void integer(autotest::Capture&o,unsigned n){o.add(&n,4);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);float values[]={-2.75f,-1.5f,-.5f,-.25f,0.f,.25f,.5f,.75f,1.5f,2.75f};float steps[]={.5f,1.f,2.f,.1f};control->m_planeScale=steps[(seed/2)%4];control->m_positionVerticalSnap=steps[(seed/8)%4];manager->clearChanged();
 CPositionableObject a(NULL,NULL),b(NULL,NULL);CEditorBaseObject foreign;Ogre::Vector3 v(values[seed%10],values[(seed/3)%10],values[(seed/7)%10]);a.setPosition(v);b.setPosition(-v);a.setOrientation(Ogre::Quaternion(Ogre::Degree(37),Ogre::Vector3(0,1,0)));b.setOrientation(Ogre::Quaternion(Ogre::Degree(-21),Ogre::Vector3(1,0,0)));TArrayList<CEditorBaseObject*>objects(5);unsigned count=(seed/32)%6;for(unsigned i=0;i<count;++i){CEditorBaseObject*p=i%4==0?NULL:i%4==1?&foreign:i%4==2?static_cast<CEditorBaseObject*>(&a):static_cast<CEditorBaseObject*>(&b);objects.add(p);}
 typedef void(*Fn)(CObjectControl3D*,TArrayList<CEditorBaseObject*>&,bool);Fn fn=ours?rsNew:rsOld;if(autotest::beginInvocation(out,fn)){fn(control,objects,seed%2);out.callCompleted=1;}
 integer(out,manager->getChanged());integer(out,objects.size());Ogre::Vector3 position=a.getPosition(false);out.add(&position,sizeof position);position=b.getPosition(false);out.add(&position,sizeof position);Ogre::Quaternion qa=a.getOrientationQuaternion(),qb=b.getOrientationQuaternion();out.add(&qa,sizeof qa);out.add(&qb,sizeof qb);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls actual(services);control=actual.control;manager=actual.manager;
 autotest::Coverage coverage("object_resnap",reinterpret_cast<uintptr_t>(rsOld));for(unsigned seed=0;seed<768;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    resnap seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);
 return 0;
}
}
TL_TEST(complete_object_resnap){return systems_fixture::isolated(&worker,host);}
