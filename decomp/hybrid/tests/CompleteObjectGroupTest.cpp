#include "AutoTest.h"
#include "NativeEditorControls.h"
#include "PositionableObject.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(Ogre::Vector3,ogOld,(CObjectControl3D*,TArrayList<CEditorBaseObject*>&),"_ZN16CObjectControl3D21getGroupRotationPointER10TArrayListIP17CEditorBaseObjectE")
extern "C" Ogre::Vector3 ogNew(CObjectControl3D*,TArrayList<CEditorBaseObject*>&) __asm__("_ZN16CObjectControl3D21getGroupRotationPointER10TArrayListIP17CEditorBaseObjectE");
namespace {
nativeeditor::Controls*owners;Ogre::SceneManager*scene;
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);float values[]={-200.f,-5.75f,-1.5f,-.5f,0.f,.5f,.75f,1.5f,5.75f,200.f};float steps[]={.5f,1.f,2.f,.1f};CObjectControl3D*control=owners->control;control->m_planeScale=steps[seed/2%4];control->m_selectedPivot=Ogre::Vector3(values[seed%10],float(int(seed/7%5)-2),values[seed/3%10]);
 CPositionableObject a(owners->resources,scene),b(owners->resources,scene),c(owners->resources,scene);CEditorBaseObject foreign;a.setPosition(Ogre::Vector3(values[seed/11%10],-2.f,values[seed/5%10]));b.setPosition(Ogre::Vector3(values[seed/13%10],7.f,values[seed/17%10]));c.setPosition(Ogre::Vector3(values[seed/19%10],0.f,values[seed/23%10]));
 Ogre::SceneNode*parent=scene->getRootSceneNode()->createChildSceneNode();parent->setPosition(Ogre::Vector3(seed%3,seed%2,-float(seed%5)));if(seed%3)a.sceneNodeSetParent(parent,false);if(seed%5==0)b.sceneNodeSetParent(parent,false);a.setVisible(true);b.setVisible(true);c.setVisible(true);
 TArrayList<CEditorBaseObject*>objects(8);CEditorBaseObject*items[]={NULL,&foreign,&a,&b,&c,&a};for(unsigned i=0;i<seed/32%7;++i)objects.add(items[(i+seed/7)%6]);typedef Ogre::Vector3(*Fn)(CObjectControl3D*,TArrayList<CEditorBaseObject*>&);Fn fn=ours?ogNew:ogOld;Ogre::Vector3 result;if(autotest::beginInvocation(out,fn)){result=fn(control,objects);out.callCompleted=1;}out.add(&result,sizeof result);out.add(&control->m_selectedPivot,sizeof(Ogre::Vector3));unsigned n=objects.size();out.add(&n,4);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls actual(services);owners=&actual;scene=services.scene;autotest::Coverage coverage("object_group_point",reinterpret_cast<uintptr_t>(ogOld));for(unsigned seed=0;seed<1024;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    group seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=1024||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_group){return systems_fixture::isolated(&worker,host);}
