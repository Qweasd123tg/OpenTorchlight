// Real RTTI and string conversion, with only the room's mesh-count query observed.
#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,oldIndexString,(void*,void*,unsigned,void*),"_ZN20CRoomPieceDescriptor33GetRoomPieceVisualIndexStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(unsigned,oldStringIndex,(void*,void*,const std::wstring&,void*),"_ZN20CRoomPieceDescriptor33GetRoomPieceVisualIndexIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" std::wstring newIndexString(void*,void*,unsigned,void*) __asm__("_ZN20CRoomPieceDescriptor33GetRoomPieceVisualIndexStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" unsigned newStringIndex(void*,void*,const std::wstring&,void*) __asm__("_ZN20CRoomPieceDescriptor33GetRoomPieceVisualIndexIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
extern "C" void* roomTable[] __asm__("_ZTV10CRoomPiece");
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
TL_FUNCTION(meshCountTarget,"_ZN10CRoomPiece29getVisualMeshCountInRoomPieceEv")
namespace {
struct Case {unsigned operation,kind,count,index;const wchar_t* text;};
const Case* input;autotest::Capture* capture;void* object;unsigned calls;
void invalid(){capture->issue=autotest::Capture::InvalidReport;}
int meshCount(void* p){bool correct=p==object;capture->add(&correct,1);if(!correct)invalid();++calls;return static_cast<int>(input->count);}
void side(Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;calls=0;uint64_t memory[128]={0},scene[4]={0},user[4]={0};object=memory;
    *reinterpret_cast<void**>(memory)=c.kind==1?static_cast<void*>(baseTable+2):static_cast<void*>(roomTable+2);
    std::wstring text(c.text);detour::Set d;TL_REDIRECT(d,meshCountTarget,&meshCount);if(d.failed()){invalid();return;}
    void* receiver=c.kind?object:0;
    if(c.operation==0){
        typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?newIndexString:oldIndexString;
        if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(scene,receiver,c.index,user);out.callCompleted=1;out.addText(result);
        std::wstring expected;
        if(c.kind==2){if(c.index<c.count&&c.index!=0xffffffffu){
            // These bounded indices have known decimal strings, independent of conversion code.
            if(c.index==0)expected=L"0";else if(c.index==1)expected=L"1";else if(c.index==3)expected=L"3";else expected=L"4";
        }else expected=L"RANDOM";}
        if(result!=expected)invalid();
        if(calls!=(c.kind==2?1u:0u))invalid();
    }else{
        typedef unsigned(*Fn)(void*,void*,const std::wstring&,void*);Fn fn=ours?newStringIndex:oldStringIndex;
        if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(scene,receiver,text,user);out.callCompleted=1;out.add(&result,4);
        if(calls!=((c.kind==2&&text!=L"RANDOM")?1u:0u))invalid();
        if((c.kind!=2||text==L"RANDOM")&&result!=0xffffffffu)invalid();
    }
    out.add(&calls,4);out.addText(text);if(*reinterpret_cast<void**>(memory)!=(c.kind==1?static_cast<void*>(baseTable+2):static_cast<void*>(roomTable+2)))invalid();*reinterpret_cast<void**>(memory)=0;out.add(memory,sizeof(memory));out.add(scene,sizeof(scene));out.add(user,sizeof(user));
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
    autotest::Coverage coverage(name,address);const unsigned counts[]={0,1,4,0xffffffffu};const unsigned indices[]={0,1,3,4,0xffffffffu};
    const wchar_t* texts[]={L"",L"RANDOM",L"0",L"1",L"-1",L"4294967295",L"3",L"garbage",L" 2 "};
    for(unsigned kind=0;kind<3;++kind)for(unsigned count=0;count<4;++count)for(unsigned i=0;i<(operation?9u:5u);++i){
        Case c={operation,kind,counts[count],indices[i%5],texts[i%9]};autotest::Outcome x,y;autotest::runChild(before,&c,x);autotest::runChild(after,&c,y);
        if(coverage.observe(host,x,y)){host->log("    room-index op %u kind %u count %u input %u exits %d/%d\n",operation,kind,c.count,i,x.childStatus,y.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(room_piece_descriptor_index_string){return run(host,0,"room_piece_descriptor_index_string",reinterpret_cast<uintptr_t>(&oldIndexString));}
TL_TEST(room_piece_descriptor_string_index){return run(host,1,"room_piece_descriptor_string_index",reinterpret_cast<uintptr_t>(&oldStringIndex));}
