#include "AutoTest.h"
#include "NativeEditorControls.h"
#include "Descriptor.h"
#include "DescriptorProp.h"
#include "Undo.h"
#include "EditorScene.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,ouOld,(CObjectControl3D*,TArrayList<CEditorBaseObject*>&),"_ZN16CObjectControl3D10createUndoER10TArrayListIP17CEditorBaseObjectE")
extern "C" void ouNew(CObjectControl3D*,TArrayList<CEditorBaseObject*>&) __asm__("_ZN16CObjectControl3D10createUndoER10TArrayListIP17CEditorBaseObjectE");
namespace {
nativeeditor::Controls*owners;const wchar_t*names[]={L"FORWARD",L"RIGHT",L"UP",L"POSITION",L"SCALE X",L"SCALE Y",L"SCALE Z"};
struct Descriptor:CDescriptor{Descriptor(unsigned mask,unsigned seed):CDescriptor(0){for(unsigned i=0;i<7;++i)if(mask&(1u<<i)){CDescriptorProp*p=new CDescriptorProp(L"transform",names[i],L"",NULL,NULL,VARIABLE_TYPE_FLOAT,0);for(unsigned j=0;j<(seed+i)%4;++j){UNIONDATA32BIT value;value.m_fValue=float(seed+i*7+j)*.125f;p->m_DefaultValue.add(value);}m_PropertyIDs[names[i]]=m_Properties.size();m_Properties.add(p);}}virtual CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}};
void number(autotest::Capture&o,unsigned n){o.add(&n,4);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);CObjectControl3D*control=owners->control;CEditorScene scene(L"object-undo-scene");Descriptor first(seed%128,seed),second((seed*73+17)%128,seed+1);CEditorBaseObject a,b;CDescriptor*pa=&first,*pb=&second;std::memcpy(reinterpret_cast<char*>(&a)+0x38,&pa,sizeof pa);std::memcpy(reinterpret_cast<char*>(&b)+0x38,&pb,sizeof pb);if(a.getDescriptor()!=&first||b.getDescriptor()!=&second)std::abort();a.SetSceneOwner(seed/16%3?&scene:NULL);b.SetSceneOwner(seed/32%3?&scene:NULL);a.setGuid(0x100000007LL);b.setGuid(0x20000000bLL);a.setParentGuid(41);b.setParentGuid(43);TArrayList<CEditorBaseObject*>objects(8);CEditorBaseObject*items[]={NULL,&a,&b,&a,&b};for(unsigned i=0;i<seed/128%6;++i)objects.add(items[(seed/7+i)%5]);CUndo*before=seed/64%2?new CUndo:NULL;control->m_undo=before;void(*fn)(CObjectControl3D*,TArrayList<CEditorBaseObject*>&)=ours?ouNew:ouOld;if(autotest::beginInvocation(out,fn)){fn(control,objects);out.callCompleted=1;}CUndo*undo=control->m_undo;number(out,undo!=NULL);number(out,undo==before);number(out,undo->m_undoData.size());for(unsigned i=0;i<undo->m_undoData.size();++i){CUndo::CUndoData*d=undo->m_undoData[i];number(out,d->m_object==NULL);number(out,d->m_action);number(out,d->m_property);number(out,d->m_sceneID);out.add(&d->m_parentGuid,8);out.add(&d->m_objectGuid,8);number(out,d->m_count);out.add(d->m_data,d->m_count*4);}delete undo;if(before&&before!=undo)delete before;control->m_undo=NULL;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls actual(services);owners=&actual;autotest::Coverage coverage("object_create_undo",reinterpret_cast<uintptr_t>(ouOld));for(unsigned seed=0;seed<1024;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    undo seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=1024||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_undo){return systems_fixture::isolated(&worker,host);}
