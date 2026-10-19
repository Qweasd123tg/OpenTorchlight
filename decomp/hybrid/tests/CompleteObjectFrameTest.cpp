#include "AutoTest.h"
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include "tests/MenuModelGpuBoundary.h"
#include "tests/SystemsFixtureWorker.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include "UtilitiesMath.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,frameOld,(CObjectControl3D*,float),"_ZN16CObjectControl3D14updateControlsEf")
extern "C" void frameNew(CObjectControl3D*,float) __asm__("_ZN16CObjectControl3D14updateControlsEf");
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

unsigned windowCalls;
bool left(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(21);return seed<1536&&(seed%4==0||seed%4==3);}
bool right(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(22);return seed<1536&&seed%4>=2;}
bool window(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(23);++windowCalls;return seed>=1536?true:seed/4%4==0?false:seed/4%4==3?windowCalls%2:true;}
POINT position(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(24);POINT q={long(seed%13),long(seed%17)};return q;}
short key(unsigned k){if(k!=16&&k!=17)std::abort();n(25);n(k);return seed/9%2?short(0x8000):0;}
void entity(CPositionableObject&p,unsigned index){p.setGuid(100+index);p.sceneNodeSetParent(services->scene->getRootSceneNode(),false);char name[60];std::sprintf(name,"frame-object-%u",index);p.sceneNodeAttachEntity(services->scene->createEntity(name,meshes[seed%3]->getName()));p.getEntity()->setQueryFlags(1u<<index);p.setVisible((seed+index)%4!=0);p.setPosition(Ogre::Vector3(float(index)*5-5,seed%17==0?20000.f:0.f,float(index)*2));}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;recording=false;windowCalls=0;CObjectControl3D*c=owners->control;
 CPositionableObject a(owners->resources,services->scene),b(owners->resources,services->scene),d(owners->resources,services->scene);entity(a,0);entity(b,1);entity(d,2);CEditorBaseObject plain;plain.setGuid(99);CEditorObjectManager::ObjectMap&objects=*owners->manager->getObjects();objects[0]=NULL;objects[1]=&plain;objects[2]=&a;objects[3]=&b;objects[4]=&d;if(seed%2)owners->manager->EditorObjectSelected(&a);
 unsigned flags[]={0,8,16,32,64,128,136,160,2};owners->editor->m_iFlags=flags[seed/7%9];owners->editor->m_bRenderWindowHasFocus=seed/11%2;owners->editor->m_iUnknown68=seed/13%8;owners->editor->m_pUnknown88=seed/19%7==0?NULL:camera;
 c->m_flag58=seed/3%2;c->m_flag59=seed/5%2;c->m_boxSelecting=seed/2%2;c->m_dragType=seed/23%7;c->m_previousMouse.x=51;c->m_previousMouse.y=52;c->m_boxStart=Ogre::Vector3(11,12,13);c->m_boxEnd=Ogre::Vector3(14,15,16);c->m_dragPivot=Ogre::Vector3(1,2,3);c->m_dragMouse.x=71;c->m_dragMouse.y=72;c->m_selectedPivot=Ogre::Vector3(1,2,3);c->m_viewDelta=Ogre::Vector3(81,82,83);c->m_controlOffset=Ogre::Vector3(91,92,93);c->m_controlsNode->setScale(.01f,.02f,.03f);camera->setPosition(Ogre::Vector3(0,10,0));c->m_workingHeight=float(seed%5);c->m_planeScale=.1f;c->m_chunkCount=seed%11;c->m_chunkDepth=seed/17%2?4:0;c->m_chunkWidth=3;c->m_chunkSize=2;
 if(seed>=1536){owners->editor->m_iFlags=0;owners->editor->m_iUnknown68=7;owners->editor->m_pUnknown88=camera;c->m_flag58=false;c->m_flag59=true;c->m_boxSelecting=true;CPositionableObject*targets[]={&a,&b,&d};for(unsigned i=0;i<3;++i){targets[i]->setPosition(Ogre::Vector3::ZERO);targets[i]->setVisible(true);}c->m_models[7]->setPosition(Ogre::Vector3::ZERO);c->m_models[7]->setScale(100,100,100);}
 c->m_models[7]->setVisible(true);if(seed<1536)c->m_models[7]->setScale(3,1,3);services->scene->getRootSceneNode()->_update(true,false);for(unsigned i=0;i<c->m_models.size();++i)c->m_models[i]->getEntity()->getWorldBoundingBox(true);
 unsigned counts[]={0,1,6,19,20};unsigned count=seed>=1536?20:counts[seed/29%5];c->m_models.resize(count);if(seed<1536&&seed/31%11==0)c->m_mouseHandler=NULL;
 if(seed/37%5==0)Ogre::MaterialManager::getSingleton().remove("ControlOrange");
 detour::Set hooks;TL_REDIRECT(hooks,frameLeft,&left);TL_REDIRECT(hooks,frameRight,&right);TL_REDIRECT(hooks,frameWindow,&window);TL_REDIRECT(hooks,framePosition,&position);TL_REDIRECT(hooks,frameKey,&key);TL_REDIRECT(hooks,icRay,&ray);if(hooks.failed())std::abort();
 void(*fn)(CObjectControl3D*,float)=ours?frameNew:frameOld;if(autotest::beginInvocation(out,fn)){recording=true;fn(c,float(seed%3)*.25f);out.callCompleted=1;recording=false;}hooks.restore();
 n(c->m_flag58);n(c->m_flag59);n(c->m_boxSelecting);n(c->m_dragType);out.add(&c->m_previousMouse,sizeof c->m_previousMouse);out.add(&c->m_dragMouse,sizeof c->m_dragMouse);vec(c->m_boxStart);vec(c->m_boxEnd);vec(c->m_dragPivot);vec(c->m_viewDelta);vec(c->m_controlOffset);vec(c->m_controlsNode->getScale());out.add(&c->m_workingPlane,sizeof c->m_workingPlane);
 const char*materials[]={"WireframeYellow","WireframeBlue","ControlOrange"};for(unsigned i=0;i<3;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(materials[i]);n(!m.isNull());if(!m.isNull()){Ogre::Pass*p=m->getTechnique(0)->getPass(0);out.add(&p->getAmbient(),sizeof(Ogre::ColourValue));out.add(&p->getDiffuse(),sizeof(Ogre::ColourValue));out.add(&p->getSelfIllumination(),sizeof(Ogre::ColourValue));n(p->getSourceBlendFactor());n(p->getDestBlendFactor());}}
 for(unsigned i=0;i<c->m_models.size();++i){CGenericModel*p=c->m_models[i];n(p->getVisible());vec(p->getPosition(false));vec(p->getScale());text(p->getEntity()->getSubEntity(0)->getMaterialName());}
 TArrayList<CEditorBaseObject*>&selected=*owners->manager->getSelectedObjects();n(selected.size());for(unsigned i=0;i<selected.size();++i){long long g=selected[i]->getGuid();out.add(&g,8);}selected.clear();objects.clear();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
void initialized(uintptr_t address,bool wide,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring(value);else new(reinterpret_cast<void*>(address))std::string;}}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client client(*CMasterResourceManager::getSingleton()->m_pSettings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);camera=client.camera->m_cameras[0];nativeeditor::Controls actual(native);owners=&actual;actual.game.game->m_sceneManager=native.scene;menugui::ModelGpuBoundary gpu;
 uintptr_t strings[]={0x1482e00,0x1528e40,0x14e6860,0x14e6900};for(unsigned i=0;i<4;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}initialized(0x1469ba8,true);const wchar_t*names[]={L"SPHERE",L"BOX",L"PLANE",L"CYLINDER",L"CONE",L"ARROW"};for(unsigned i=0;i<6;++i)initialized(0x1482e20+i*8,true,names[i]);CFileSystem*previous=g_pFileSystem;void*storage=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(storage);CFileSystem*fs=new(storage)CFileSystem(false);
 const char*materials[]={"ControlBlue","ControlGreen","ControlRed","ControlWhite","ControlPurple","WireFrame","WireframeYellow","WireframeBlue","ControlOrange","ControlYellow","Wireframe"};for(unsigned i=0;i<11;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(materials[i]);if(m.isNull())m=Ogre::MaterialManager::getSingleton().create(materials[i],"General");m->removeAllTechniques();m->createTechnique()->createPass();}
 for(unsigned i=0;i<3;++i){char name[50];std::sprintf(name,"init-controls-mesh-%u",i);meshes[i]=Ogre::MeshManager::getSingleton().createManual(name,"General");meshes[i]->_setBounds(Ogre::AxisAlignedBox(-1,-2,-3,1,2,3),false);meshes[i]->_setBoundingSphereRadius(1.f+i*1.25f);meshes[i]->createSubMesh()->setMaterialName("ControlWhite");}
 {detour::Set setup;TL_REDIRECT(setup,icFiles,&files);TL_REDIRECT(setup,icRay,&ray);if(setup.failed())std::abort();seed=1;icOld(actual.control);}
 autotest::Coverage coverage("object_frame",reinterpret_cast<uintptr_t>(frameOld));for(unsigned seed=0;seed<1664;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    frame seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);for(unsigned j=0;j+4<=a.capture.length&&j<200;j+=4){float va,vb;std::memcpy(&va,a.capture.data+j,4);std::memcpy(&vb,b.capture.data+j,4);host->log("    offset%u %g/%g\n",j,double(va),double(vb));}break;}coverage.report(host);return 1;}}coverage.report(host);for(unsigned i=0;i<3;++i)meshes[i].setNull();fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;return coverage.completed!=1664||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_frame){return systems_fixture::isolated(&worker,host);}
