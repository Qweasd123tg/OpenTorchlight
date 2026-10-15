#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "RoomPiece.h"
#include "RandomGroup.h"
TL_ORIGINAL(void, oldRoomParent, (CRoomPiece*,long long), "_ZN10CRoomPiece13setParentGuidEx")
extern "C" void newRoomParent(CRoomPiece*,long long) __asm__("_ZN10CRoomPiece13setParentGuidEx");
extern "C" void* randomGroupTable[] __asm__("_ZTV12CRandomGroup");
extern "C" void* editorBaseTable[] __asm__("_ZTV17CEditorBaseObject");
TL_FUNCTION(sceneObjectTarget, "_ZN12CEditorScene16GetObjectInSceneEx")
namespace {
struct Case { unsigned shape, initial, scene, guid; };
autotest::Capture* capture;
void* expectedScene;
CEditorBaseObject* nodes[3];
long long ids[3];
unsigned calls;
CEditorBaseObject* sceneObject(void* receiver,long long guid) {
    if(receiver!=expectedScene || calls>3)capture->issue=autotest::Capture::InvalidReport;
    ++calls; capture->add(&guid,sizeof(guid));
    for(unsigned i=0;i<3;++i)if(guid==ids[i])return nodes[i];
    return 0;
}
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);
    uint64_t roomMemory[(sizeof(CRoomPiece)+7)/8], groupMemory[3][(sizeof(CRandomGroup)+7)/8], scene[8];
    std::memset(roomMemory,0xa5,sizeof(roomMemory));std::memset(groupMemory,0x3c,sizeof(groupMemory));std::memset(scene,0x69,sizeof(scene));
    CRoomPiece* room=reinterpret_cast<CRoomPiece*>(roomMemory);
    const long long starts[]={0,0x1122334455667788LL,-1,777};long long start=starts[c.guid];
    ids[0]=c.guid==1?starts[1]:0;ids[1]=17;ids[2]=-29;
    unsigned length=c.shape==0?0:c.shape==1||c.shape==2?1:3;
    for(unsigned i=0;i<3;++i){
        nodes[i]=i<length?reinterpret_cast<CEditorBaseObject*>(groupMemory[i]):0;
        void* table=(c.shape==1 || (c.shape==3&&i==0) || (c.shape==4&&i==2))?static_cast<void*>(editorBaseTable+2):static_cast<void*>(randomGroupTable+2);
        std::memcpy(groupMemory[i],&table,sizeof(table));
        long long next=i+1<length?ids[i+1]:-1;
        std::memcpy(reinterpret_cast<char*>(groupMemory[i])+0x18,&next,sizeof(next));
        CRandomGroup* group=reinterpret_cast<CRandomGroup*>(groupMemory[i]);
        group->m_iRandomType=c.shape==2?1:c.shape==3&&i==2?0xffffffffu:0;
    }
    expectedScene=c.scene?scene:0;std::memcpy(reinterpret_cast<char*>(room)+0x48,&expectedScene,sizeof(expectedScene));
    room->m_bUnknown15D=c.initial!=0;
    unsigned char expectedRoom[sizeof(roomMemory)],expectedGroups[sizeof(groupMemory)];
    std::memcpy(expectedRoom,roomMemory,sizeof(roomMemory));std::memcpy(expectedGroups,groupMemory,sizeof(groupMemory));
    std::memcpy(expectedRoom+0x18,&start,sizeof(start));
    bool traversing=c.scene && c.guid<2;
    bool found=traversing&&(c.shape==2||c.shape==3);
    bool expectedFlag=c.initial||found;std::memcpy(expectedRoom+0x15d,&expectedFlag,1);
    unsigned expectedCalls=traversing?(c.shape==0?1:c.shape==1?2:c.shape==2?1:c.shape==3?3:4):(c.scene&&c.guid==3?1:0);
    capture=&out;calls=0;detour::Set d;TL_REDIRECT(d,sceneObjectTarget,&sceneObject);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    typedef void(*Fn)(CRoomPiece*,long long);Fn fn=ours?newRoomParent:oldRoomParent;
    if(!autotest::beginInvocation(out,fn))return;
    fn(room,start);out.callCompleted=1;
    if(calls!=expectedCalls||std::memcmp(roomMemory,expectedRoom,sizeof(roomMemory))||std::memcmp(groupMemory,expectedGroups,sizeof(groupMemory)))out.issue=autotest::Capture::InvalidReport;
    out.add(&calls,4);out.add(&room->m_bUnknown15D,1);out.add(&start,sizeof(start));out.add(scene,sizeof(scene));
}
void original(void* p,autotest::Capture&out){side(p,out,false);}void candidate(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(room_piece_parent_guid) {
    autotest::Coverage coverage("room_piece_parent_guid",reinterpret_cast<uintptr_t>(&oldRoomParent));
    for(unsigned shape=0;shape<5;++shape)for(unsigned initial=0;initial<2;++initial)for(unsigned scene=0;scene<2;++scene)for(unsigned guid=0;guid<4;++guid){
        Case c={shape,initial,scene,guid};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)){host->log("    room-parent shape %u initial %u scene %u guid %u exits %d/%d\n",shape,initial,scene,guid,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
