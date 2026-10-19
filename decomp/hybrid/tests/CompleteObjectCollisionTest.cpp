#include "AutoTest.h"
#include <Ogre.h>
#define private public
#include "CollisionModel.h"
#undef private
#include "CollisionList.h"
#include "iCollision.h"
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "UtilitiesMath.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,coOldSnap,(CObjectControl3D*,CPositionableObject*,bool),"_ZN16CObjectControl3D18snapObjectToGroundEP19CPositionableObjectb")
extern "C" void coNewSnap(CObjectControl3D*,CPositionableObject*,bool) __asm__("_ZN16CObjectControl3D18snapObjectToGroundEP19CPositionableObjectb");
TL_ORIGINAL(CEditorBaseObject*,coOldPick,(CObjectControl3D*),"_ZN16CObjectControl3D19getObjectUnderMouseEv")
extern "C" CEditorBaseObject* coNewPick(CObjectControl3D*) __asm__("_ZN16CObjectControl3D19getObjectUnderMouseEv");
TL_FUNCTION(coMouse,"_ZN13CMouseHandler13MousePositionEv")
TL_FUNCTION(coRay,"_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")
namespace {
nativeeditor::Controls*owners;nativegame::Services*services;Ogre::Camera*camera;Ogre::MeshPtr mesh;autotest::Capture*output;unsigned seed,entityCount;bool picking;
struct Case{unsigned op,seed;};
void n(unsigned v){output->add(&v,4);}void vec(const Ogre::Vector3&v){output->add(v.ptr(),12);}
POINT mouse(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(11);POINT q={17+int(seed%5),23-int(seed%7)};return q;}
Ogre::Vector3 ray(Ogre::Camera*p,float x,float y,float width,float height){if(p!=camera)std::abort();n(12);output->add(&x,4);output->add(&y,4);output->add(&width,4);output->add(&height,4);return seed%7==0?Ogre::Vector3(1,0,0):Ogre::Vector3(seed%3==0?.125f:0.f,-1,seed%5==0?.25f:0.f);}
void entity(CPositionableObject*p,bool visible,unsigned flags){p->sceneNodeSetParent(services->scene->getRootSceneNode(),false);char name[50];std::sprintf(name,"collision-object-entity-%u",entityCount++);Ogre::Entity*e=services->scene->createEntity(name,mesh->getName());p->sceneNodeAttachEntity(e);e->setQueryFlags(flags);p->setVisible(visible);}
struct CollisionObject:CPositionableObject,iCollision{
 CCollisionModel collision;
 CollisionObject(unsigned index):CPositionableObject(owners->resources,services->scene),collision(services->scene,L""){
  setGuid(100+index);collision.m_pCollisionList=new CCollisionList;CCollisionList&list=*collision.m_pCollisionList;
  float slope=(seed+index)%3==0?2.f:0.f;Ogre::Vector3 v[]={Ogre::Vector3(-8,0,-8),Ogre::Vector3(8,0,-8),Ogre::Vector3(8,slope,8),Ogre::Vector3(-8,slope,8)};
  for(unsigned i=0;i<4;++i)list.addVertex(v[i],-1);
  if((seed+index)%11){if((seed+index)%5){list.addFace(0,2,1,21,-1);list.addFace(0,3,2,22,-1);}else{list.addFace(0,1,2,21,-1);list.addFace(0,2,3,22,-1);}}
  list.calculateNormals();list.calculateFaceBounds();
  if((seed+index)%13==0&&picking){delete collision.m_pCollisionList;collision.m_pCollisionList=NULL;}
 }
 virtual CCollisionModel*getCollisionMesh(){return &collision;}
};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;picking=c.op==1;output=&out;entityCount=0;CObjectControl3D*control=owners->control;
 CPositionableObject target(owners->resources,services->scene);target.setGuid(71);target.setPosition(Ogre::Vector3(seed%4==0?20.f:0.f,10.f,0.f));target.setOrientation(Ogre::Quaternion(Ogre::Degree(float(seed%3)*30),Ogre::Vector3::UNIT_Y));entity(&target,true,1);
 CEditorBaseObject plain;plain.setGuid(73);CPositionableObject noCollision(owners->resources,services->scene);noCollision.setGuid(79);noCollision.setPosition(Ogre::Vector3(30,0,0));entity(&noCollision,true,1);
 CEditorObjectManager::ObjectMap&objects=*owners->manager->getObjects();objects[0]=NULL;objects[1]=&plain;objects[2]=&noCollision;if(seed%3==0)objects[3]=&target;
 std::vector<CollisionObject*>models;unsigned count=seed/3%7;for(unsigned i=0;i<count;++i){CollisionObject*p=new CollisionObject(i);p->setPosition(Ogre::Vector3((seed+i)%9==0?30.f:0.f,float(i)*1.5f-2.f,0));if(seed/7%3)p->setOrientation(Ogre::Quaternion(Ogre::Degree(float((i+seed)%4)*30),Ogre::Vector3::UNIT_Y));entity(p,(seed+i)%4!=0,1u<<((seed+i)%3));objects[10+i]=p;models.push_back(p);}
 camera->setPosition(Ogre::Vector3(0,10,0));owners->editor->m_iFlags=0;owners->editor->m_iUnknown68=seed/5%8;owners->editor->m_pUnknown88=seed%17==0?NULL:camera;iEditorResourceManager*realResources=owners->editor->m_pEditorResourceManager;if(seed%19==0)owners->editor->m_pEditorResourceManager=NULL;
 services->scene->getRootSceneNode()->_update(true,false);control->m_snapToGroundBias=float(int(seed%5)-2)*.25f;
 detour::Set hooks;TL_REDIRECT(hooks,coMouse,&mouse);TL_REDIRECT(hooks,coRay,&ray);if(hooks.failed())std::abort();
 if(c.op==0){void(*fn)(CObjectControl3D*,CPositionableObject*,bool)=ours?coNewSnap:coOldSnap;if(autotest::beginInvocation(out,fn)){fn(control,seed%23==0?NULL:&target,seed%2);out.callCompleted=1;}vec(target.getPosition(false));Ogre::Quaternion q=target.getOrientationQuaternion();out.add(&q,sizeof q);Ogre::Matrix4 matrix=target.getOrientation();out.add(&matrix,sizeof matrix);}
 else {CEditorBaseObject*(*fn)(CObjectControl3D*)=ours?coNewPick:coOldPick;if(autotest::beginInvocation(out,fn)){CEditorBaseObject*result=fn(control);out.callCompleted=1;long long guid=result?result->getGuid():-1;out.add(&guid,8);}}
 hooks.restore();owners->editor->m_pEditorResourceManager=realResources;objects.clear();for(unsigned i=0;i<models.size();++i)delete models[i];
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client client(*CMasterResourceManager::getSingleton()->m_pSettings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);camera=client.camera->m_cameras[0];nativeeditor::Controls actual(native);owners=&actual;actual.game.game->m_sceneManager=native.scene;initialized(0x147fac8,true);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("object-collision-material","General");material->removeAllTechniques();mesh=Ogre::MeshManager::getSingleton().createManual("object-collision-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-8,-1,-8,8,3,8),false);mesh->createSubMesh()->setMaterialName(material->getName());autotest::Coverage snap("object_snap",reinterpret_cast<uintptr_t>(coOldSnap)),pick("object_under_mouse",reinterpret_cast<uintptr_t>(coOldPick));autotest::Coverage*all[]={&snap,&pick};unsigned hits[2]={0};for(unsigned op=0;op<2;++op)for(unsigned seed=0;seed<512;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(op==0&&a.capture.length>=12){float y;std::memcpy(&y,a.capture.data+4,4);if(y!=10.f)++hits[0];}if(op==1&&a.capture.length>=8){long long guid;std::memcpy(&guid,a.capture.data+a.capture.length-8,8);if(guid!=-1)++hits[1];}if(all[op]->observe(host,a,b)){host->log("    collision op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",op,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}all[op]->report(host);return 1;}}snap.report(host);pick.report(host);host->log("    collision actual hits snap%u pick%u\n",hits[0],hits[1]);if(!hits[0]||!hits[1])return 1;mesh.setNull();return snap.completed!=512||pick.completed!=512||snap.missing||pick.missing||snap.different||pick.different;}
}
TL_TEST(complete_object_collision){return systems_fixture::isolated(&worker,host);}
