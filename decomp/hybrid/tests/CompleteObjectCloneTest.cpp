#include "AutoTest.h"
#include <Ogre.h>
#define private public
#include "EditorBaseObject.h"
#undef private
#include "tests/NativeEditorControls.h"
#include "Descriptor.h"
#include "EditorScene.h"
#include "Undo.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,clOld,(CObjectControl3D*,TArrayList<CEditorBaseObject*>&),"_ZN16CObjectControl3D20cloneObjectsIfNeedBeER10TArrayListIP17CEditorBaseObjectE")
extern "C" void clNew(CObjectControl3D*,TArrayList<CEditorBaseObject*>&) __asm__("_ZN16CObjectControl3D20cloneObjectsIfNeedBeER10TArrayListIP17CEditorBaseObjectE");
TL_FUNCTION(clShift,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(clMouse,"_ZN13CMouseHandler19MouseLeftButtonDownEv")
namespace {
nativeeditor::Controls*owners;autotest::Capture*output;unsigned seed,factories,shiftCalls;
void n(unsigned v){output->add(&v,4);}void identity(CEditorBaseObject*p){long long id=p?p->getGuid():-1;output->add(&id,8);}
short shift(unsigned key){if(key!=16)std::abort();n(11);++shiftCalls;return seed%3==0?0:short(0x8000);}
bool left(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(12);return seed/3%2;}
struct Descriptor:CDescriptor{Descriptor(unsigned flags):CDescriptor(0){m_iFlags=flags;}virtual CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}};
struct Scene:CEditorScene{
 std::vector<CEditorBaseObject*>made;
 Scene():CEditorScene(L"clone actual scene"){}
 virtual CEditorBaseObject*CreateObjectByDescriptor(CDescriptor*d,CEditorBaseObject*source,CEditorBaseObject*owner,bool load){
  n(31);identity(source);n(d==source->getDescriptor());n(owner==NULL);n(load);++factories;
  if((seed/7+factories)%4==0)return NULL;
  CEditorBaseObject*q=new CEditorBaseObject;q->setGuid(1000+factories);q->setParentGuid(source->getGuid());q->SetName(source->getName());
  q->m_pDescriptor=(seed/13+factories)%5?d:NULL;q->SetSceneOwner((seed/17+factories)%5?this:NULL);made.push_back(q);return q;
 }
 ~Scene(){for(unsigned i=0;i<made.size();++i)delete made[i];}
};
void undo(CUndo*p){n(p!=NULL);if(!p)return;n(p->m_undoData.size());for(unsigned i=0;i<p->m_undoData.size();++i){CUndo::CUndoData*d=p->m_undoData[i];identity(d->m_object);n(d->m_action);n(d->m_property);output->add(&d->m_objectGuid,8);n(d->m_data==NULL);n(d->m_count);}}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;factories=shiftCalls=0;
 Scene scene;Descriptor yes(8),no(0);std::vector<CEditorBaseObject*> originals;TArrayList<CEditorBaseObject*>local(10);TArrayList<CEditorBaseObject*>&objects=seed/5%2?*owners->manager->getSelectedObjects():local;
 unsigned counts[]={0,1,2,5,11,17,25};unsigned count=counts[seed/11%7];
 for(unsigned i=0;i<count;++i){CEditorBaseObject*p=new CEditorBaseObject;p->setGuid(100+i);p->setParentGuid(900+i);p->SetName(i%2?L"\u043e\u0431\u044a\u0435\u043a\u0442":L"");p->m_pDescriptor=(seed/19+i)%3?&yes:&no;p->SetSceneOwner(&scene);originals.push_back(p);objects.add(p);}
 CObjectControl3D*c=owners->control;c->m_dragType=seed/2%10;c->m_previousLeftDown=seed/4%2;c->m_keys.flushAll();c->m_keys.capture();unsigned keys[]={37,39,38,40};for(unsigned i=0;i<4;++i)c->m_keys.m_pressed[keys[i]]=((seed/23)&(1u<<i))?1:0;
 c->m_undo=seed/6%2?new CUndo:NULL;owners->editor->m_iMaxUndos=100;owners->editor->m_Redos.push_back(new CUndo);
 detour::Set hooks;TL_REDIRECT(hooks,clShift,&shift);TL_REDIRECT(hooks,clMouse,&left);if(hooks.failed())std::abort();
 void(*fn)(CObjectControl3D*,TArrayList<CEditorBaseObject*>&)=ours?clNew:clOld;if(autotest::beginInvocation(out,fn)){fn(c,objects);out.callCompleted=1;}hooks.restore();
 n(factories);n(shiftCalls);undo(c->m_undo);n(objects.size());for(unsigned i=0;i<objects.size();++i)identity(objects[i]);n(owners->manager->getCreatedObjects().size());for(unsigned i=0;i<owners->manager->getCreatedObjects().size();++i)identity(owners->manager->getCreatedObjects()[i]);
 n(owners->editor->m_Undos.size());for(std::list<CUndo*>::iterator i=owners->editor->m_Undos.begin();i!=owners->editor->m_Undos.end();++i)undo(*i);n(owners->editor->m_Redos.size());for(std::list<CUndo*>::iterator i=owners->editor->m_Redos.begin();i!=owners->editor->m_Redos.end();++i)n(*i!=NULL);
 delete c->m_undo;c->m_undo=NULL;owners->editor->deleteAllUndos();for(std::list<CUndo*>::iterator i=owners->editor->m_Redos.begin();i!=owners->editor->m_Redos.end();++i)delete *i;owners->editor->m_Redos.clear();owners->manager->getSelectedObjects()->clear();owners->manager->getCreatedObjects().clear();owners->manager->getObjects()->clear();for(unsigned i=0;i<originals.size();++i)delete originals[i];
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls actual(services);owners=&actual;autotest::Coverage coverage("object_clone",reinterpret_cast<uintptr_t>(clOld));for(unsigned seed=0;seed<2048;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    clone seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_clone){return systems_fixture::isolated(&worker,host);}
