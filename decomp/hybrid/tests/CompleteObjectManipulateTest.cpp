#include "AutoTest.h"
#include <Ogre.h>
#define private public
#include "EditorBaseObject.h"
#undef private
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include "tests/MenuModelGpuBoundary.h"
#include "tests/SystemsFixtureWorker.h"
#include "GenericModel.h"
#include "FileSystem.h"
#define private public
#define protected public
#include "EditorBaseObject.h"
#include "Descriptor.h"
#undef protected
#undef private
#include "RoomPiece.h"
#include "UtilitiesMath.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,manOld,(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&),"_ZN16CObjectControl3D23manipulateSelectedItemsEfR10TArrayListIP17CEditorBaseObjectE")
extern "C" void manNew(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&) __asm__("_ZN16CObjectControl3D23manipulateSelectedItemsEfR10TArrayListIP17CEditorBaseObjectE");
TL_FUNCTION(manSnap,"_ZN16CObjectControl3D18snapObjectToGroundEP19CPositionableObjectb")
TL_FUNCTION(manRemoveCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
TL_ORIGINAL(void,icOld,(CObjectControl3D*),"_ZN16CObjectControl3D12InitControlsEv")
TL_FUNCTION(icFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(icRay,"_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")
TL_FUNCTION(frameLeft,"_ZN13CMouseHandler19MouseLeftButtonDownEv")
TL_FUNCTION(frameRight,"_ZN13CMouseHandler20MouseRightButtonDownEv")
TL_FUNCTION(frameWindow,"_ZN13CMouseHandler15MouseIsInWindowEv")
TL_FUNCTION(framePosition,"_ZN13CMouseHandler13MousePositionEv")
TL_FUNCTION(frameKey,"_Z16GetAsyncKeyStatej")
namespace {
nativeeditor::Controls*owners;nativegame::Services*services;Ogre::Camera*camera;Ogre::MeshPtr meshes[3];autotest::Capture*output;unsigned seed,entities;bool recording;
void n(unsigned v){output->add(&v,4);}void vec(const Ogre::Vector3&v){output->add(v.ptr(),12);}void text(const std::string&s){n(s.size());if(s.size())output->add(s.data(),s.size());}
void files(CFileSystem*p,const std::wstring&path,CFileInfo&info,bool a,bool b,bool c){if(p!=g_pFileSystem)std::abort();if(recording){n(11);output->addText(path);n(a);n(b);n(c);}info.m_bExists=path.find(L".animation")==std::wstring::npos;info.m_sResourceName=meshes[seed%3]->getName();}
Ogre::Vector3 ray(Ogre::Camera*p,float x,float y,float width,float height){if(p!=camera)std::abort();if(recording){n(12);output->add(&x,4);output->add(&y,4);output->add(&width,4);output->add(&height,4);}return seed%7==0?Ogre::Vector3(1,0,0):Ogre::Vector3(float(int(seed%5)-2)*.1f,-1,float(int(seed%3)-1)*.1f);}


struct Descriptor:CDescriptor {Descriptor(unsigned flags):CDescriptor(0){m_iFlags=flags;}virtual CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}};
short key(unsigned k){if(k!=17)std::abort();n(25);return seed/7%2?short(0x8000):0;}
POINT position(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(24);POINT q={long(seed%13),long(seed%17)};return q;}
void snap(CObjectControl3D*p,CPositionableObject*object,bool orient){if(p!=owners->control||!object)std::abort();n(26);long long guid=object->getGuid();output->add(&guid,8);n(orient);object->setY(2.f+seed%3);}
void removeCollision(CMasterResourceManager*,CCollisionModel*p){if(p)std::abort();}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;recording=false;CObjectControl3D*c=owners->control;
 detour::Set teardown;TL_REDIRECT(teardown,manRemoveCollision,&removeCollision);if(teardown.failed())std::abort();
 Descriptor descriptor((seed/11%2?0x400:0)|(seed/13%2?0x800:0)|(seed/17%3==0?0x200:0));CPositionableObject a(owners->resources,services->scene),b(owners->resources,services->scene);CEditorBaseObject plain;plain.setGuid(90);a.setGuid(100);b.setGuid(101);a.m_pDescriptor=b.m_pDescriptor=&descriptor;
 CRoomPiece room(owners->resources);room.setGuid(102);room.m_pDescriptor=&descriptor;room.setResourceManager(owners->resources);CRoomPieceDataInformation::CRoomPieceCoreData core;core.m_scalable=seed/19%2;room.m_pRoomPieceData->m_coreData=seed/23%3?&core:NULL;
 CPositionableObject*models[]={&a,&b,&room};for(unsigned i=0;i<3;++i){models[i]->sceneNodeSetParent(services->scene->getRootSceneNode(),false);models[i]->setPosition(Ogre::Vector3(float(i)*3-2,float(i)-1,float(i)*2-1));models[i]->setScale(.25f+float((seed+i)%5)*.5f);models[i]->setOrientation(Ogre::Quaternion(Ogre::Degree(float((seed+i)%7)*13),Ogre::Vector3::UNIT_Y));}
 TArrayList<CEditorBaseObject*>objects(10);CEditorBaseObject*items[]={&a,NULL,&plain,&b,&room,&a};for(unsigned i=0;i<seed%7;++i)objects.add(items[i]);
 c->m_keys.flushAll();for(unsigned i=0;i<4;++i)c->m_keys.m_pressed[37+i]=((seed/3)&(1u<<i))!=0;c->m_keys.m_pressed[36]=seed/5%2;c->m_keys.m_pressed[78]=seed%2;c->m_keys.m_pressed[110]=seed/2%2;
 unsigned flags[]={0,8,16,32,64,24,40,56};owners->editor->m_iFlags=flags[seed/29%8];owners->editor->m_pUnknown88=seed/31%13==0?NULL:camera;owners->manager->m_bUnknown79=false;c->m_selectedPivot=Ogre::Vector3(1,2,3);c->m_dragType=seed/2%9;c->m_dragPlane=seed/37%5==0?Ogre::Plane():Ogre::Plane(Ogre::Vector3::UNIT_Y,float(int(seed%5)-2));c->m_dragDirection=Ogre::Vector3(.1f,-.2f,.3f);c->m_controlOffset=Ogre::Vector3(.25f,.5f,.75f);c->m_planeScale=.25f+float(seed%4)*.25f;c->m_positionVerticalSnap=.125f+float(seed%3)*.125f;c->m_orientationSnap=.125f*float(seed%5+1);camera->setPosition(Ogre::Vector3(3,10,5));
 detour::Set hooks;TL_REDIRECT(hooks,framePosition,&position);TL_REDIRECT(hooks,frameKey,&key);TL_REDIRECT(hooks,icRay,&ray);TL_REDIRECT(hooks,manSnap,&snap);if(hooks.failed())std::abort();void(*fn)(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&)=ours?manNew:manOld;recording=true;if(autotest::beginInvocation(out,fn)){fn(c,float(seed%3)*.25f,objects);out.callCompleted=1;}recording=false;hooks.restore();
 for(unsigned i=0;i<3;++i){vec(models[i]->getPosition(false));vec(models[i]->getScale());Ogre::Quaternion q=models[i]->getOrientationQuaternion();out.add(&q,sizeof q);q=models[i]->getSceneNode()->getOrientation();out.add(&q,sizeof q);vec(models[i]->getSceneNode()->getPosition());vec(models[i]->getSceneNode()->getScale());}vec(c->m_selectedPivot);vec(c->m_controlOffset);n(owners->manager->m_bUnknown79);room.m_pRoomPieceData->m_coreData=NULL;
 room.clearCollisionData();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
void initialized(uintptr_t address,bool wide,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring(value);else new(reinterpret_cast<void*>(address))std::string;}}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client client(*CMasterResourceManager::getSingleton()->m_pSettings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);camera=client.camera->m_cameras[0];nativeeditor::Controls actual(native);owners=&actual;actual.game.game->m_sceneManager=native.scene;menugui::ModelGpuBoundary gpu;
 uintptr_t strings[]={0x1482e00,0x1528e40,0x14e6860,0x14e6900};for(unsigned i=0;i<4;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}initialized(0x1469ba8,true);initialized(0x14a9de8,true);const wchar_t*names[]={L"SPHERE",L"BOX",L"PLANE",L"CYLINDER",L"CONE",L"ARROW"};for(unsigned i=0;i<6;++i)initialized(0x1482e20+i*8,true,names[i]);CFileSystem*previous=g_pFileSystem;void*storage=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(storage);CFileSystem*fs=new(storage)CFileSystem(false);
 const char*materials[]={"ControlBlue","ControlGreen","ControlRed","ControlWhite","ControlPurple","WireFrame","WireframeYellow","WireframeBlue","ControlOrange","ControlYellow","Wireframe"};for(unsigned i=0;i<11;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(materials[i]);if(m.isNull())m=Ogre::MaterialManager::getSingleton().create(materials[i],"General");m->removeAllTechniques();m->createTechnique()->createPass();}
 for(unsigned i=0;i<3;++i){char name[50];std::sprintf(name,"init-controls-mesh-%u",i);meshes[i]=Ogre::MeshManager::getSingleton().createManual(name,"General");meshes[i]->_setBounds(Ogre::AxisAlignedBox(-1,-2,-3,1,2,3),false);meshes[i]->_setBoundingSphereRadius(1.f+i*1.25f);meshes[i]->createSubMesh()->setMaterialName("ControlWhite");}
 {detour::Set setup;TL_REDIRECT(setup,icFiles,&files);TL_REDIRECT(setup,icRay,&ray);if(setup.failed())std::abort();seed=1;icOld(actual.control);}
 autotest::Coverage coverage("object_manipulate",reinterpret_cast<uintptr_t>(manOld));for(unsigned seed=0;seed<4096;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    frame seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);for(unsigned j=0;j+4<=a.capture.length&&j<200;j+=4){float va,vb;std::memcpy(&va,a.capture.data+j,4);std::memcpy(&vb,b.capture.data+j,4);host->log("    offset%u %g/%g\n",j,double(va),double(vb));}break;}coverage.report(host);return 1;}}coverage.report(host);for(unsigned i=0;i<3;++i)meshes[i].setNull();fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;return coverage.completed!=4096||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_manipulate){return systems_fixture::isolated(&worker,host,300);}
