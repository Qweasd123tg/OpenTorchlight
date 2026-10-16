#include "ParentPairs.h"
#include "Detour.h"
#define private public
#include "Undo.h"
#undef private
TL_ORIGINAL(void,parentUndoOld,(CUndo*,CUndo*),"_ZN5CUndo23resetPropertiesOnObjectEPS_")
extern "C" void parentUndoNew(CUndo*,CUndo*) __asm__("_ZN5CUndo23resetPropertiesOnObjectEPS_");
TL_FUNCTION(parentUndoProperty,"_ZN5CUndo16DoUndoOnPropertyEPNS_9CUndoDataEPS_")
TL_FUNCTION(parentUndoUndelete,"_ZN5CUndo14DoUndoUndeleteEPNS_9CUndoDataEPS_")
TL_FUNCTION(parentUndoCreate,"_ZN5CUndo12DoUndoCreateEPNS_9CUndoDataEPS_")
namespace {
autotest::Capture* cap;CUndo* receiver;CUndo* inverse;CUndo::CUndoData* entries;unsigned seed,calls;
void dispatch(CUndo* self,CUndo::CUndoData* data,CUndo* redo,unsigned kind)
{
    bool valid=self==receiver&&redo==inverse;parentpairs::scalar(*cap,valid);
    int index=-1;for(unsigned i=0;i<8;++i)if(data==entries+i)index=i;
    parentpairs::scalar(*cap,index);parentpairs::scalar(*cap,kind);
    if(!valid||index<0||data->m_action!=int(kind))cap->issue=autotest::Capture::InvalidReport;
    ++calls;data->m_property+=13+kind;
    // A collaborator can change the live list; the original re-reads its count.
    if(calls==1&&seed%7==1)receiver->m_undoData.add(entries+7);
    if(calls==1&&seed%7==2&&receiver->m_undoData.size()>1)receiver->m_undoData.removeAt(1);
}
void property(CUndo*a,CUndo::CUndoData*b,CUndo*c){dispatch(a,b,c,0);}
void undelete(CUndo*a,CUndo::CUndoData*b,CUndo*c){dispatch(a,b,c,1);}
void create(CUndo*a,CUndo::CUndoData*b,CUndo*c){dispatch(a,b,c,2);}
void side(void* raw,autotest::Capture& out,bool ours)
{
    seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;calls=0;
    CUndo undo,redo;receiver=&undo;inverse=seed%5?&redo:NULL;
    CUndo::CUndoData data[8];entries=data;
    const int actions[]={-1,0,1,2,3,0x7fffffff,int(0x80000000u)};
    for(unsigned i=0;i<8;++i){data[i].m_object=NULL;data[i].m_data=NULL;data[i].m_count=0;data[i].m_property=seed*17+i;data[i].m_action=actions[(seed/8+i)%7];}
    data[7].m_action=seed%3;
    for(unsigned i=0;i<seed%8;++i)undo.m_undoData.add(data+i);
    detour::Set patches;TL_REDIRECT(patches,parentUndoProperty,&property);TL_REDIRECT(patches,parentUndoUndelete,&undelete);TL_REDIRECT(patches,parentUndoCreate,&create);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    typedef void(*Fn)(CUndo*,CUndo*);Fn fn=ours?parentUndoNew:parentUndoOld;
    autotest::invoke(out,fn,&undo,inverse);
    parentpairs::scalar(out,calls);parentpairs::scalar(out,undo.m_undoData.size());
    for(unsigned i=0;i<8;++i)parentpairs::scalar(out,data[i].m_property);
    for(unsigned i=0;i<undo.m_undoData.size();++i){int id=undo.m_undoData[i]-entries;parentpairs::scalar(out,id);}
    // The fixture owns these stack entries; CUndo normally owns heap entries.
    undo.m_undoData.clear();
}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(parent_undo_dispatch){return parentpairs::run(host,"parent_undo_dispatch",(uintptr_t)parentUndoOld,112,a,b);}
