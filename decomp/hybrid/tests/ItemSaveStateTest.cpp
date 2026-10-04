#include <cstring>
#include <map>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "Item.h"
#include "ItemSaveState.h"
#include "EditorScene.h"
#include "Descriptor.h"
#include "UnitSpawner.h"
#include "SafePointer.h"

TL_ORIGINAL(void, originalItemApply, (CItem*,CItemSaveState&), "_ZN5CItem14applySaveStateER14CItemSaveState")
extern "C" void* saveItemTable[] __asm__("_ZTV5CItem");
extern "C" void* saveSpawnerTable[] __asm__("_ZTV12CUnitSpawner");
extern "C" void* saveEditorObjectTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case { unsigned int seed; };
void pointerAt(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void int64At(void* p,size_t offset,long long value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
struct DescriptorManagerView {
    void* vptr;void* safe;
    std::map<std::wstring,unsigned int> ids;
    std::vector<CDescriptor*> descriptors;
    CEditorScene* owner;
    DescriptorManagerView():vptr(NULL),safe(NULL),owner(NULL) {}
};
void side(Case& c,bool ours,autotest::Capture& out) {
    long long item[0x230/8],manager[0x48/8],level[0x2f0/8],scenes[2][0x190/8],descriptors[2][sizeof(CDescriptor)/8],spawners[2][0x240/8],other[0x58/8];
    std::memset(item,0,sizeof(item));std::memset(manager,0,sizeof(manager));std::memset(level,0,sizeof(level));
    std::memset(scenes,0,sizeof(scenes));std::memset(descriptors,0,sizeof(descriptors));std::memset(spawners,0,sizeof(spawners));std::memset(other,0,sizeof(other));
    char* self=reinterpret_cast<char*>(item);pointerAt(item,0,saveItemTable+2);pointerAt(other,0,saveEditorObjectTable+2);
    int64At(item,0x10,900+c.seed);int64At(item,0x20,700+c.seed);int64At(item,0x180,555);
    new(self+0x210)std::wstring(L"before");
    CItemSaveState state;
    state.m_sItemName=c.seed%2?L"restored α":L"";
    state.m_vLocalPosition=Ogre::Vector3(1+c.seed,2,3);
    state.m_mOrientation=Ogre::Matrix4::IDENTITY;state.m_mOrientation.setTrans(Ogre::Vector3(91,92,93));
    state.m_mOrientation[0][0]=2;state.m_mOrientation[1][1]=3;state.m_mOrientation[2][2]=4;
    state.m_bEnabled=c.seed&1;state.m_bItemFlag17C=(c.seed>>1)&1;state.m_bBlocksPath=(c.seed>>2)&1;
    state.m_iQuestGuid=123456+c.seed;state.m_iQuestState=int(c.seed)-25;state.m_iRoomIndex=int(c.seed%5)-1;
    const long long guids[]={0xffffffffLL,-1,0,123,124,999,123,123};state.m_iSpawnerGuid=guids[c.seed%8];
    DescriptorManagerView managers[2];
    TArrayList<CEditorBaseObject*>* objects[2];
    TArrayList<TSafePointer<CBaseUnit*>*>* spawned[2];
    for(unsigned int i=0;i<2;++i) {
        pointerAt(spawners[i],0,saveSpawnerTable+2);
        int64At(spawners[i],0x20,c.seed%8==6?123:c.seed%8==1?-1:123+i);
        spawned[i]=new(reinterpret_cast<char*>(spawners[i])+0x1e8)TArrayList<TSafePointer<CBaseUnit*>*>(10);
        objects[i]=new(reinterpret_cast<char*>(descriptors[i])+0xe0)TArrayList<CEditorBaseObject*>(10);
        if(c.seed&1)objects[i]->add(reinterpret_cast<CEditorBaseObject*>(spawners[0]));
        objects[i]->add(NULL);objects[i]->add(reinterpret_cast<CEditorBaseObject*>(other));
        if(c.seed%3!=0||i)objects[i]->add(reinterpret_cast<CEditorBaseObject*>(spawners[0]));
        objects[i]->add(reinterpret_cast<CEditorBaseObject*>(spawners[1]));
        if(c.seed%8==7)objects[i]->add(reinterpret_cast<CEditorBaseObject*>(spawners[0]));
        if(c.seed%5!=0||i)managers[i].ids[L"Unit Spawner"]=0;
        managers[i].descriptors.push_back(reinterpret_cast<CDescriptor*>(descriptors[i]));
        pointerAt(scenes[i],0x100,&managers[i]);
    }
    TArrayList<CEditorScene*>* rooms=new(reinterpret_cast<char*>(level)+0x10)TArrayList<CEditorScene*>(4);
    for(unsigned int i=0;i<c.seed%3;++i)rooms->add(reinterpret_cast<CEditorScene*>(scenes[i]));
    typedef std::map<long long,TArrayList<iUnitObserver*>*> Listeners;
    Listeners* listeners=new(reinterpret_cast<char*>(level)+0x2a8)Listeners;
    if(c.seed%13)pointerAt(item,0x68,manager);
    if(c.seed%11)pointerAt(manager,0x18,level);
    CItem* object=reinterpret_cast<CItem*>(item);
    if(ours)object->CItem::applySaveState(state);else originalItemApply(object,state);
    out.add(self+0x80,0x1d8-0x80);out.add(self+0x1f2,1);out.addText(*reinterpret_cast<std::wstring*>(self+0x210));out.add(self+0x20,8);
    TArrayList<TSafePointer<void*>*>* safe=*reinterpret_cast<TArrayList<TSafePointer<void*>*>**>(self+8);
    unsigned int safeCount=safe?safe->size():0;out.add(&safeCount,sizeof(safeCount));
    for(int i=0;i<2;++i) {
        unsigned int count=spawned[i]->size();out.add(&count,sizeof(count));if(count>32)_exit(4);
        for(unsigned int j=0;j<count;++j) {
            struct SafeView {void* object;unsigned int index;};
            SafeView& value=*reinterpret_cast<SafeView*>((*spawned[i])[j]);
            bool pointsToItem=value.object==item;out.add(&pointsToItem,sizeof(pointsToItem));out.add(&value.index,sizeof(value.index));
        }
    }
    size_t n=listeners->size();out.add(&n,sizeof(n));
    for(Listeners::const_iterator i=listeners->begin();i!=listeners->end();++i) {
        out.add(&i->first,sizeof(i->first));unsigned int count=i->second->size();out.add(&count,sizeof(count));
        for(unsigned int j=0;j<count;++j) {
            void* observer=(*i->second)[j];int id=observer==reinterpret_cast<char*>(spawners[0])+0x170?1:observer==reinterpret_cast<char*>(spawners[1])+0x170?2:99;out.add(&id,sizeof(id));
        }
    }
    // The child owns this synthetic world; OS teardown reclaims its registered
    // safe pointers and observers after the capture, without invoking fake vtables.
    reinterpret_cast<std::wstring*>(self+0x210)->~basic_string();
    for(int i=0;i<2;++i) {objects[i]->~TArrayList<CEditorBaseObject*>();spawned[i]->~TArrayList<TSafePointer<CBaseUnit*>*>();}
    rooms->~TArrayList<CEditorScene*>();listeners->~Listeners();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(item_restore_and_spawner_binding) {
    int failures=0;
    for(unsigned int seed=0;seed<96;++seed) {
        Case c={seed};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    item restore seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
