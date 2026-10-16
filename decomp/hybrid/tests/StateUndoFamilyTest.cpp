#include "AutoTest.h"
#include "Detour.h"
#include "Undo.h"
#include "Editor.h"
#include "EditorScene.h"
#include "Descriptor.h"
#include "PositionableObject.h"
#include "FileUtilities.h"

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(void, old795550, (CUndo*, CUndo::CUndoData*, CUndo*), "_ZN5CUndo14DoUndoUndeleteEPNS_9CUndoDataEPS_")
extern "C" void new795550(CUndo*, CUndo::CUndoData*, CUndo*) __asm__("_ZN5CUndo14DoUndoUndeleteEPNS_9CUndoDataEPS_");
TL_ORIGINAL(void, old7957d0, (CUndo*, CUndo::CUndoData*, CUndo*), "_ZN5CUndo12DoUndoCreateEPNS_9CUndoDataEPS_")
extern "C" void new7957d0(CUndo*, CUndo::CUndoData*, CUndo*) __asm__("_ZN5CUndo12DoUndoCreateEPNS_9CUndoDataEPS_");
TL_ORIGINAL(void, old795a30, (CUndo*), "_ZN5CUndo8DoAsUndoEv")
extern "C" void new795a30(CUndo*) __asm__("_ZN5CUndo8DoAsUndoEv");
TL_ORIGINAL(void, old795ae0, (CUndo*, CEditorBaseObject*, const wchar_t*), "_ZN5CUndo15AddUndoPropertyEP17CEditorBaseObjectPKw")
extern "C" void new795ae0(CUndo*, CEditorBaseObject*, const wchar_t*) __asm__("_ZN5CUndo15AddUndoPropertyEP17CEditorBaseObjectPKw");
TL_ORIGINAL(void, old78baa0, (CUndo*, CEditorBaseObject*, unsigned), "_ZN5CUndo15AddUndoPropertyEP17CEditorBaseObjectj")
extern "C" void new78baa0(CUndo*, CEditorBaseObject*, unsigned) __asm__("_ZN5CUndo15AddUndoPropertyEP17CEditorBaseObjectj");
TL_ORIGINAL(void,editorCtor,(CEditor*),"_ZN7CEditorC1Ev")
TL_FUNCTION(appDirectory,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(copyFile,"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
TL_FUNCTION(objectCreated,"_ZN20CEditorObjectManager19EditorObjectCreatedEP17CEditorBaseObject")
TL_FUNCTION(addDeleted,"_ZN5CUndo16AddObjectDeletedEP17CEditorBaseObject")
TL_FUNCTION(resetUndo,"_ZN5CUndo23resetPropertiesOnObjectEPS_")
TL_FUNCTION(addFlag,"_ZN17CEditorBaseObject17AddBaseObjectFlagE18EEDITOROBJECT_FLAG")
TL_FUNCTION(removeFlag,"_ZN17CEditorBaseObject20RemoveBaseObjectFlagE18EEDITOROBJECT_FLAG")
TL_FUNCTION(addRedo,"_ZN7CEditor7addRedoEP5CUndo")
namespace {
struct Descriptor: CDescriptor {Descriptor():CDescriptor(0){} virtual CEditorBaseObject* CreateObject(CEditorScene*){return NULL;}void property(CDescriptorProp* p){m_Properties.add(p);m_PropertyIDs[L"value"]=0;}};
autotest::Capture* capture;unsigned setupWrites,calls,seed;CEditorBaseObject* expectedObject;CUndo* receiver;CEditor* editor;
unsigned operation,flagCalls,createdCalls,deletedCalls,visibleCalls;
void trace(unsigned event,CEditorBaseObject* object,unsigned argument)
{
    bool valid=object==expectedObject;
    capture->add(&event,4);capture->add(&valid,1);capture->add(&argument,4);
    if(!valid)capture->issue=autotest::Capture::InvalidReport;
}
void flags(CEditorBaseObject* object,EEDITOROBJECT_FLAG flag,unsigned kind)
{
    const unsigned expected[]={1,2,8};
    trace(kind,object,static_cast<unsigned>(flag));
    if(flagCalls>=3||static_cast<unsigned>(flag)!=expected[flagCalls]||
       (operation==0?(kind!=2||createdCalls!=1):(kind!=3||deletedCalls!=1)))
        capture->issue=autotest::Capture::InvalidReport;
    ++flagCalls;++calls;
}
void add(CEditorBaseObject* object,EEDITOROBJECT_FLAG flag){flags(object,flag,3);}
void remove(CEditorBaseObject* object,EEDITOROBJECT_FLAG flag){flags(object,flag,2);}
struct ObservedPositionable: CPositionableObject {
    ObservedPositionable():CPositionableObject(NULL,NULL){}
    virtual void setVisible(bool visible)
    {
        trace(4,this,visible?1:0);
        if(operation==0?(flagCalls!=3||createdCalls!=1||!visible):
           (flagCalls!=0||deletedCalls!=0||visible))
            capture->issue=autotest::Capture::InvalidReport;
        ++visibleCalls;++calls;
        CSceneNodeObject::setVisible(visible);
    }
};
struct ObservedSceneNode: CSceneNodeObject {
    ObservedSceneNode():CSceneNodeObject(NULL,NULL){}
    virtual void setVisible(bool visible)
    {
        trace(4,this,visible?1:0);
        if(operation==0?(flagCalls!=3||createdCalls!=1||!visible):
           (flagCalls!=0||deletedCalls!=0||visible))
            capture->issue=autotest::Capture::InvalidReport;
        ++visibleCalls;++calls;
        CSceneNodeObject::setVisible(visible);
    }
};
bool directory(const std::wstring& path){++setupWrites;capture->addText(path);return true;}
void copy(const std::wstring& from,const std::wstring& to){++setupWrites;capture->addText(from);capture->addText(to);}
void created(CEditorObjectManager* p,CEditorBaseObject* object){++calls;++createdCalls;trace(1,object,0);if(flagCalls||visibleCalls)capture->issue=autotest::Capture::InvalidReport;bool valid=object==expectedObject;capture->add(&valid,1);bool managerNull=p==NULL;capture->add(&managerNull,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;}
void deleted(CUndo* undo,CEditorBaseObject* object){++calls;++deletedCalls;trace(5,object,0);if(flagCalls)capture->issue=autotest::Capture::InvalidReport;bool valid=undo==receiver&&object==expectedObject;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;}
void reset(CUndo* object,CUndo* inverse){++calls;bool valid=object==receiver&&inverse!=receiver;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;if(seed%2){CUndo::CUndoData* data=new CUndo::CUndoData;data->m_object=NULL;data->m_data=NULL;data->m_count=0;inverse->m_undoData.add(data);}}
void redo(CEditor* object,CUndo* inverse){++calls;bool valid=object==editor&&inverse->m_undoData.size()==1;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;}
void side(void* raw,autotest::Capture& out,bool ours)
{
 Case c=*static_cast<Case*>(raw);capture=&out;seed=c.index;calls=0;setupWrites=0;operation=c.op;flagCalls=createdCalls=deletedCalls=visibleCalls=0;
 editor=static_cast<CEditor*>(autotest::allocate(sizeof(CEditor)));
 {detour::Set setup;TL_REDIRECT(setup,appDirectory,&directory);TL_REDIRECT(setup,copyFile,&copy);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}editorCtor(editor);}
 out.add(&setupWrites,4);gEditor=editor;
 CEditorScene scene(L"undo-test");Descriptor descriptor;
 CDescriptorProp* property=new CDescriptorProp(L"category",L"value",L"description",NULL,NULL,VARIABLE_TYPE_INTEGER,0);
 for(unsigned i=0;i<c.index%4;++i){UNIONDATA32BIT value;value.m_uValue=0xffffff00u+i;property->m_DefaultValue.add(value);}descriptor.property(property);
 CEditorBaseObject object;ObservedPositionable positionable;ObservedSceneNode sceneNode;
 expectedObject=c.index%3==0?&object:c.index%3==1?static_cast<CEditorBaseObject*>(&positionable):static_cast<CEditorBaseObject*>(&sceneNode);
 expectedObject->CEditorBaseObject::SetSceneOwner(c.index%7==0?NULL:&scene);
 // The class has no public descriptor setter. The +0x38 slot is proved by
 // EditorBaseObject's frozen declaration and all original guards under test.
 CDescriptor* selected=c.index%5==0?NULL:&descriptor;std::memcpy(reinterpret_cast<char*>(expectedObject)+0x38,&selected,sizeof(selected));
 expectedObject->setGuid(0x100000007LL);expectedObject->setParentGuid(0x200000009LL);
 CUndo undo,inverse;receiver=&inverse;
 CUndo::CUndoData* data=new CUndo::CUndoData;data->m_object=expectedObject;data->m_data=NULL;data->m_count=0;data->m_property=~0u;data->m_action=2;
 if(c.op==0||c.op==1){detour::Set patches;TL_REDIRECT(patches,objectCreated,&created);TL_REDIRECT(patches,addDeleted,&deleted);TL_REDIRECT(patches,addFlag,&add);TL_REDIRECT(patches,removeFlag,&remove);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(c.index%11==0)data->m_object=NULL;typedef void(*Fn)(CUndo*,CUndo::CUndoData*,CUndo*);Fn fn=c.op==0?(ours?new795550:old795550):(ours?new7957d0:old7957d0);
  if(!autotest::beginInvocation(out,fn))return;fn(&undo,c.index%13==0?NULL:data,&inverse);out.callCompleted=1;
  bool performed=c.index%13!=0&&c.index%11!=0&&expectedObject->getSceneOwner()!=NULL;
  if(flagCalls!=(performed?3u:0u)||visibleCalls!=(performed&&c.index%3!=0?1u:0u))out.issue=autotest::Capture::InvalidReport;
  out.add(&flagCalls,4);out.add(&createdCalls,4);out.add(&deletedCalls,4);out.add(&visibleCalls,4);
  bool released=data->m_object==NULL;out.add(&released,1);
  bool visible=positionable.getVisible();out.add(&visible,1);visible=sceneNode.getVisible();out.add(&visible,1);
  bool enabled=positionable.getEnabled();out.add(&enabled,1);enabled=sceneNode.getEnabled();out.add(&enabled,1);bool changed;std::memcpy(&changed,reinterpret_cast<char*>(editor)+0x164,1);out.add(&changed,1);
 } else if(c.op==2) {
  receiver=&undo;for(unsigned i=0;i<c.index%3;++i)undo.m_undoData.add(NULL);
  detour::Set patches;TL_REDIRECT(patches,resetUndo,&reset);TL_REDIRECT(patches,addRedo,&redo);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CUndo*);Fn fn=ours?new795a30:old795a30;if(!autotest::beginInvocation(out,fn))return;fn(&undo);out.callCompleted=1;
 } else if(c.op==3) {
  typedef void(*Fn)(CUndo*,CEditorBaseObject*,const wchar_t*);Fn fn=ours?new795ae0:old795ae0;if(!autotest::beginInvocation(out,fn))return;fn(&undo,c.index%11==0?NULL:expectedObject,c.index%3?L"value":L"missing");out.callCompleted=1;
 } else {
  typedef void(*Fn)(CUndo*,CEditorBaseObject*,unsigned);Fn fn=ours?new78baa0:old78baa0;if(!autotest::beginInvocation(out,fn))return;fn(&undo,c.index%11==0?NULL:expectedObject,c.index%3==0?~0u:c.index%3==1?0:2);out.callCompleted=1;
 }
 out.add(&calls,4);unsigned n=inverse.m_undoData.size();out.add(&n,4);n=undo.m_undoData.size();out.add(&n,4);
 if(c.op>=3)for(unsigned i=0;i<n;++i){CUndo::CUndoData* v=undo.m_undoData[i];out.add(&v->m_action,4);out.add(&v->m_property,4);out.add(&v->m_sceneID,4);out.add(&v->m_parentGuid,8);out.add(&v->m_objectGuid,8);out.add(&v->m_count,4);out.add(v->m_data,v->m_count*4);}
 data->m_object=NULL;delete data;
 // Keep the real editor alive until the child exits: its application teardown
 // is outside these entrypoint comparisons and the setup global is child-local.
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_undo_795550) {return runCases(host,0,84,"state_undo_795550",(uint64_t)(uintptr_t)old795550,original,candidate);}
TL_TEST(state_undo_7957d0) {return runCases(host,1,84,"state_undo_7957d0",(uint64_t)(uintptr_t)old7957d0,original,candidate);}
TL_TEST(state_undo_795a30) {return runCases(host,2,84,"state_undo_795a30",(uint64_t)(uintptr_t)old795a30,original,candidate);}
TL_TEST(state_undo_795ae0) {return runCases(host,3,84,"state_undo_795ae0",(uint64_t)(uintptr_t)old795ae0,original,candidate);}
TL_TEST(state_undo_78baa0) {return runCases(host,4,84,"state_undo_78baa0",(uint64_t)(uintptr_t)old78baa0,original,candidate);}
