#include "AutoTest.h"
#include <Ogre.h>
#define private public
#include "EditorBaseObject.h"
#undef private
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include "Descriptor.h"
#include "EditorScene.h"
#include "GenericModel.h"
#include "Undo.h"
TL_ORIGINAL(void,upOld,(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&,bool),"_ZN16CObjectControl3D6updateEfR10TArrayListIP17CEditorBaseObjectEb")
extern "C" void upNew(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&,bool) __asm__("_ZN16CObjectControl3D6updateEfR10TArrayListIP17CEditorBaseObjectEb");
TL_ORIGINAL(void,upModelCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_FUNCTION(upLeft,"_ZN13CMouseHandler19MouseLeftButtonDownEv")
TL_FUNCTION(upCenter,"_ZN13CMouseHandler21MouseCenterButtonDownEv")
TL_FUNCTION(upBounds,"_ZN16CObjectControl3D17updateBoundingBoxER10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(upClone,"_ZN16CObjectControl3D20cloneObjectsIfNeedBeER10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(upManipulate,"_ZN16CObjectControl3D23manipulateSelectedItemsEfR10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(upShow,"_ZN16CObjectControl3D12showControlsEb")
namespace {
nativeeditor::Controls*owners;nativegame::Services*services;autotest::Capture*output;TArrayList<CEditorBaseObject*>*selection;unsigned seed,leftCalls;
void n(unsigned v){output->add(&v,4);}void list(TArrayList<CEditorBaseObject*>&objects){if(&objects!=selection)std::abort();n(objects.size());for(unsigned i=0;i<objects.size();++i){long long guid=objects[i]?objects[i]->getGuid():-1;output->add(&guid,8);}}
void receiver(CObjectControl3D*p,unsigned event){if(p!=owners->control)std::abort();n(event);}
bool left(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(11);unsigned call=leftCalls++;return seed/5%4==0?call%2:seed/5%2;}
bool center(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(12);return seed%2;}
void bounds(CObjectControl3D*p,TArrayList<CEditorBaseObject*>&objects){receiver(p,21);list(objects);p->m_selectionCount=seed/3%3;p->m_selectedPivot=Ogre::Vector3(9,8,7);}
void clone(CObjectControl3D*p,TArrayList<CEditorBaseObject*>&objects){receiver(p,22);list(objects);if(seed/11%2&&objects.size())objects.removeAt(objects.size()-1);if(seed/13%2)owners->editor->m_iFlags^=2;}
void manipulate(CObjectControl3D*p,float elapsed,TArrayList<CEditorBaseObject*>&objects){receiver(p,23);output->add(&elapsed,4);list(objects);}
void show(CObjectControl3D*p,bool visible){receiver(p,24);n(visible);}
struct Descriptor:CDescriptor{Descriptor():CDescriptor(0){}virtual CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}};
void undo(CUndo*p){n(p!=NULL);if(!p)return;n(p->m_undoData.size());for(unsigned i=0;i<p->m_undoData.size();++i){CUndo::CUndoData*d=p->m_undoData[i];n(d->m_action);n(d->m_property);n(d->m_object!=NULL);}}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;leftCalls=0;CObjectControl3D*c=owners->control;CEditorScene scene(L"update real scene");Descriptor descriptor;CPositionableObject a(owners->resources,services->scene),b(owners->resources,services->scene);a.setGuid(71);b.setGuid(73);a.m_pDescriptor=&descriptor;b.m_pDescriptor=&descriptor;a.SetSceneOwner(&scene);b.SetSceneOwner(&scene);a.setPosition(Ogre::Vector3(-1,2,3));b.setPosition(Ogre::Vector3(5,-2,7));CEditorBaseObject plain;plain.setGuid(79);plain.m_pDescriptor=&descriptor;TArrayList<CEditorBaseObject*>objects(10);selection=&objects;CEditorBaseObject*values[]={&a,&b,NULL,&plain,&a};for(unsigned i=0;i<seed%6;++i)objects.add(values[i]);
 c->m_keys.flushAll();for(unsigned i=0;i<4;++i)c->m_keys.m_currentPressed[37+i]=((seed/7)&(1u<<i))?1:0;for(unsigned i=0;i<3;++i){c->m_mouse.m_PendingPressed[i]=(seed+i)%2;c->m_mouse.m_PendingHeld[i]=(seed/2+i)%2;c->m_mouse.m_PendingDoubleClick[i]=(seed/3+i)%2;}c->m_mouse.m_iPendingWheelDelta=int(seed%7)-3;
 owners->editor->m_bRenderWindowHasFocus=seed/2%2;owners->editor->m_iFlags=seed/3%2?2:0;owners->editor->m_iMaxUndos=100;c->m_editorEnabled=seed/4%2;c->m_previousLeftDown=seed/5%2;c->m_selectionCount=0xbad;c->m_selectedPivot=Ogre::Vector3(81,82,83);c->m_undo=seed/17%3?new CUndo:NULL;if(c->m_undo&&seed/17%3==2)c->m_undo->AddNewObject(&a);
 CGenericModel*box=NULL;if(seed/19%2){box=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));upModelCtor(box,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_BOX);box->setResourceManager(owners->resources);box->setVisible(seed%2);}c->m_boxModel=box;
 detour::Set hooks;TL_REDIRECT(hooks,upLeft,&left);TL_REDIRECT(hooks,upCenter,&center);TL_REDIRECT(hooks,upBounds,&bounds);TL_REDIRECT(hooks,upClone,&clone);TL_REDIRECT(hooks,upManipulate,&manipulate);TL_REDIRECT(hooks,upShow,&show);if(hooks.failed())std::abort();float elapsed=float(int(seed%11)-5)*.125f;void(*fn)(CObjectControl3D*,float,TArrayList<CEditorBaseObject*>&,bool)=ours?upNew:upOld;if(autotest::beginInvocation(out,fn)){fn(c,elapsed,objects,seed/23%2);out.callCompleted=1;}hooks.restore();
 n(leftCalls);n(c->m_previousLeftDown);n(c->m_selectionCount);output->add(c->m_selectedPivot.ptr(),12);list(objects);undo(c->m_undo);n(owners->editor->m_Undos.size());for(std::list<CUndo*>::iterator i=owners->editor->m_Undos.begin();i!=owners->editor->m_Undos.end();++i)undo(*i);n(owners->editor->m_iFlags);n(box!=NULL);if(box)n(box->getVisible());output->add(c->m_keys.m_pressed,512);output->add(c->m_keys.m_currentPressed,512);output->add(c->m_mouse.m_Pressed,18);output->add(&c->m_mouse.m_iWheelDelta,8);
 delete c->m_undo;c->m_undo=NULL;owners->editor->deleteAllUndos();delete box;c->m_boxModel=NULL;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;nativeeditor::Controls actual(native);owners=&actual;uintptr_t strings[]={0x1482e00,0x1482e08};for(unsigned i=0;i<2;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(strings[i]),8);if(!p){if(i)new(reinterpret_cast<void*>(strings[i]))std::wstring;else new(reinterpret_cast<void*>(strings[i]))std::string;}}const wchar_t*names[]={L"SPHERE",L"BOX",L"PLANE",L"CYLINDER",L"CONE",L"ARROW"};for(unsigned i=0;i<6;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1482e20+i*8),8);if(!p)new(reinterpret_cast<void*>(0x1482e20+i*8))std::wstring(names[i]);}autotest::Coverage coverage("object_update",reinterpret_cast<uintptr_t>(upOld));for(unsigned seed=0;seed<2048;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    update seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_update){return systems_fixture::isolated(&worker,host);}
