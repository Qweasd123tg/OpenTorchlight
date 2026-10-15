// Descriptor traversal pairs retain original RTTI and real array indexing.
// Only direct object operations and the editor-mode query are redirected.
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(void, original0, (void*, float), "_ZN26CAnimationPlayerDescriptor6updateEf")
extern "C" void candidate0(void*, float) __asm__("_ZN26CAnimationPlayerDescriptor6updateEf");
TL_ORIGINAL(void, original1, (void*, float), "_ZN30CGameStateControllerDescriptor6updateEf")
extern "C" void candidate1(void*, float) __asm__("_ZN30CGameStateControllerDescriptor6updateEf");
TL_ORIGINAL(void, original2, (void*, void*), "_ZN30CGameStateControllerDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate2(void*, void*) __asm__("_ZN30CGameStateControllerDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original3, (void*, float), "_ZN26CSkillControllerDescriptor6updateEf")
extern "C" void candidate3(void*, float) __asm__("_ZN26CSkillControllerDescriptor6updateEf");
TL_ORIGINAL(void, original4, (void*, void*), "_ZN26CSkillControllerDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate4(void*, void*) __asm__("_ZN26CSkillControllerDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original5, (void*, float), "_ZN22CSoundObjectDescriptor6updateEf")
extern "C" void candidate5(void*, float) __asm__("_ZN22CSoundObjectDescriptor6updateEf");
TL_ORIGINAL(void, original6, (void*, void*), "_ZN22CSoundObjectDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate6(void*, void*) __asm__("_ZN22CSoundObjectDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original7, (void*, void*), "_ZN22CRandomGroupDescriptor21descriptorSceneLoadedEP12CEditorScene")
extern "C" void candidate7(void*, void*) __asm__("_ZN22CRandomGroupDescriptor21descriptorSceneLoadedEP12CEditorScene");
extern "C" void* tableCAnimationPlayer[] __asm__("_ZTV16CAnimationPlayer");
extern "C" void* tableCGameStateController[] __asm__("_ZTV20CGameStateController");
extern "C" void* tableCRandomGroup[] __asm__("_ZTV12CRandomGroup");
extern "C" void* tableCSkillController[] __asm__("_ZTV16CSkillController");
extern "C" void* tableCSoundObject[] __asm__("_ZTV12CSoundObject");
TL_FUNCTION(target0, "_ZN16CAnimationPlayer6updateEf")
TL_FUNCTION(target1, "_ZN20CGameStateController6updateEf")
TL_FUNCTION(target2, "_ZN20CGameStateController14setInitializedEv")
TL_FUNCTION(target3, "_ZN16CSkillController6updateEf")
TL_FUNCTION(target4, "_ZN16CSkillController19initSkillControllerEv")
TL_FUNCTION(target5, "_ZN12CSoundObject12updateSoundsEf")
TL_FUNCTION(target6, "_ZN12CSoundObject4playEv")
TL_FUNCTION(target7, "_ZN12CRandomGroup17calculateChildrenEv")
TL_FUNCTION(editorTarget, "_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
struct Case { unsigned operation, layout, editor, mutation; float elapsed; };
const Case* input; autotest::Capture* capture;
void* descriptor; void* objects[4]; void* resource; unsigned calls, queries;
void pointerAt(void* p, unsigned offset, void* value) { std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value)); }
void number(unsigned value) { capture->add(&value,sizeof(value)); }
void invalid() { capture->issue=autotest::Capture::InvalidReport; }
void expectPointer(void* p,unsigned offset,void* expected) {
    void* actual=0;std::memcpy(&actual,static_cast<char*>(p)+offset,sizeof(actual));
    if(actual!=expected) invalid();
}
unsigned identity(void* p) { for(unsigned i=0;i<4;++i) if(p==objects[i]) return i+1; return 99; }
void changeTraversal() {
    if(input->mutation==1 && calls==1) {
        unsigned count=0;
        std::memcpy(static_cast<char*>(descriptor)+0xe8,&count,4);
    }
}
void objectCall(void* p) {
    unsigned id=identity(p); if(id==99) invalid();
    number(1); number(id); ++calls;
    // Model a direct collaborator writing its receiver without touching RTTI.
    static_cast<unsigned char*>(p)[0x180] ^= static_cast<unsigned char>(calls);
    changeTraversal();
}
void updateCall(void* p,float value) {
    objectCall(p); capture->add(&value,sizeof(value));
    if(std::memcmp(&value,&input->elapsed,sizeof(value))) invalid();
}
bool editorCall(void* p) {
    if(p!=resource) invalid();
    number(2); ++queries;
    bool running=input->editor!=0 || (input->mutation==2 && queries>1);
    number(running); return running;
}
void visibleCall(void* p,bool value) {
    number(3); number(identity(p)); number(value); if(!value) invalid();
    static_cast<unsigned char*>(p)[0x181]=value;
}
void enabledCall(void* p,bool value) {
    number(4); number(identity(p)); number(value); if(!value) invalid();
    static_cast<unsigned char*>(p)[0x182]=value;
}
void* originalTable(unsigned operation) {
    switch(operation) {
    case 0:return tableCAnimationPlayer;
    case 1:case 2:return tableCGameStateController;
    case 3:case 4:return tableCSkillController;
    case 5:case 6:return tableCSoundObject;
    default:return tableCRandomGroup;
    }
}
void side(Case& c,bool ours,autotest::Capture& out) {
    input=&c; capture=&out; calls=queries=0;
    uint64_t descriptorBytes[40]={0}, objectBytes[4][64]={{0}}, sceneBytes[20]={0}, resourceBytes[8]={0};
    void* array[6]={0}; void* vtable[18]={0};
    descriptor=descriptorBytes;resource=resourceBytes;
    // Preserve offset-to-top and typeinfo for the actual __dynamic_cast.
    std::memcpy(vtable,originalTable(c.operation),sizeof(vtable));
    vtable[2+0x50/8]=reinterpret_cast<void*>(&visibleCall);
    vtable[2+0x40/8]=reinterpret_cast<void*>(&enabledCall);
    for(unsigned i=0;i<4;++i) {
        objects[i]=objectBytes[i];
        pointerAt(objects[i],0,i==3?baseTable+2:vtable+2);
        pointerAt(objects[i],0x100,resource);
        static_cast<unsigned char*>(objects[i])[0x120]=(i!=1);
        static_cast<unsigned char*>(objects[i])[0x150]=(i!=1);
    }
    unsigned count=0,capacity=6;
    switch(c.layout) {
    case 0: break;
    case 1: count=1;array[0]=objects[0];break;
    case 2: count=1;break;
    case 3: count=1;array[0]=objects[3];break;
    case 4: count=6;array[0]=objects[0];array[1]=0;array[2]=objects[3];array[3]=objects[1];array[4]=objects[2];array[5]=objects[0];break;
    case 5: count=4;capacity=2;array[0]=objects[0];array[1]=objects[1];break;
    case 6: count=4;capacity=0;array[0]=objects[2];break;
    case 7: count=6;array[0]=objects[1];array[1]=objects[2];array[2]=objects[0];array[3]=objects[2];array[4]=objects[1];array[5]=objects[0];break;
    }
    // Skill update is an original static cast; unrelated RTTI is relevant only to its dynamic activation.
    if(c.operation==3) for(unsigned i=0;i<6;++i) if(array[i]==objects[3]) array[i]=0;
    unsigned expectedCalls=0,expectedQueries=0,expectedCount=count;
    for(unsigned i=0;i<expectedCount;++i) {
        void* p=array[i<capacity?i:0];
        if(!p || p==objects[3]) continue;
        if(c.operation==2 || c.operation==3 || c.operation==4 || c.operation==7) {
            ++expectedQueries;
            if(c.editor || (c.mutation==2 && expectedQueries>1)) continue;
        }
        if((c.operation==6 || c.operation==7) && p==objects[1]) continue;
        ++expectedCalls;
        if(c.mutation==1 && expectedCalls==1) expectedCount=0;
    }
    pointerAt(descriptor,0xe0,array);
    std::memcpy(static_cast<char*>(descriptor)+0xe8,&count,4);
    std::memcpy(static_cast<char*>(descriptor)+0xec,&capacity,4);
    pointerAt(sceneBytes,0x68,resource);
    detour::Set d;
    TL_REDIRECT(d,editorTarget,&editorCall);
    switch(c.operation) {
    case 0: TL_REDIRECT(d,target0,&updateCall); break;
    case 1: TL_REDIRECT(d,target1,&updateCall); break;
    case 2: TL_REDIRECT(d,target2,&objectCall); break;
    case 3: TL_REDIRECT(d,target3,&updateCall); break;
    case 4: TL_REDIRECT(d,target4,&objectCall); break;
    case 5: TL_REDIRECT(d,target5,&updateCall); break;
    case 6: TL_REDIRECT(d,target6,&objectCall); break;
    case 7: TL_REDIRECT(d,target7,&objectCall); break;
    }
    if(d.failed()) { invalid(); return; }
    switch(c.operation) {
    case 0: autotest::invoke(out,ours?candidate0:original0,descriptor,c.elapsed); break;
    case 1: autotest::invoke(out,ours?candidate1:original1,descriptor,c.elapsed); break;
    case 2: autotest::invoke(out,ours?candidate2:original2,descriptor,static_cast<void*>(sceneBytes)); break;
    case 3: autotest::invoke(out,ours?candidate3:original3,descriptor,c.elapsed); break;
    case 4: autotest::invoke(out,ours?candidate4:original4,descriptor,static_cast<void*>(sceneBytes)); break;
    case 5: autotest::invoke(out,ours?candidate5:original5,descriptor,c.elapsed); break;
    case 6: autotest::invoke(out,ours?candidate6:original6,descriptor,static_cast<void*>(sceneBytes)); break;
    case 7: autotest::invoke(out,ours?candidate7:original7,descriptor,static_cast<void*>(sceneBytes)); break;
    }
    if(calls!=expectedCalls || queries!=expectedQueries) invalid();
    number(calls);number(queries);
    // Verify pointer identity before removing process-local addresses from snapshots.
    expectPointer(descriptor,0xe0,array);
    pointerAt(descriptor,0xe0,0); out.add(descriptor,sizeof(descriptorBytes));
    for(unsigned i=0;i<4;++i) {
        expectPointer(objects[i],0,i==3?baseTable+2:vtable+2);
        expectPointer(objects[i],0x100,resource);
        pointerAt(objects[i],0,0);pointerAt(objects[i],0x100,0);
        out.add(objects[i],sizeof(objectBytes[i]));
    }
    for(unsigned i=0;i<6;++i) number(array[i]?identity(array[i]):0);
    expectPointer(sceneBytes,0x68,resource);
    pointerAt(sceneBytes,0x68,0);out.add(sceneBytes,sizeof(sceneBytes));out.add(resource,sizeof(resourceBytes));
}
void before(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),false,out); }
void after(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),true,out); }
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address) {
    autotest::Coverage coverage(name,address);
    const uint32_t times[]={0x00000000,0x3c888889,0xbf800000,0x7fc12345};
    for(unsigned layout=0;layout<8;++layout) for(unsigned editor=0;editor<2;++editor) for(unsigned mutation=0;mutation<3;++mutation) {
        Case c={operation,layout,editor,mutation,0};std::memcpy(&c.elapsed,&times[(layout+editor+mutation)%4],4);
        autotest::Outcome x,y;autotest::runChild(before,&c,x);autotest::runChild(after,&c,y);
        if(coverage.observe(host,x,y)) {
            host->log("    descriptor %u layout %u editor %u mutation %u exits %d/%d\n",operation,layout,editor,mutation,x.childStatus,y.childStatus);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return 0;
}
}
TL_TEST(animation_descriptor_update) { return run(host,0,"animation_descriptor_update",reinterpret_cast<uintptr_t>(&original0)); }
TL_TEST(game_state_descriptor_update) { return run(host,1,"game_state_descriptor_update",reinterpret_cast<uintptr_t>(&original1)); }
TL_TEST(game_state_descriptor_activation) { return run(host,2,"game_state_descriptor_activation",reinterpret_cast<uintptr_t>(&original2)); }
TL_TEST(skill_descriptor_update) { return run(host,3,"skill_descriptor_update",reinterpret_cast<uintptr_t>(&original3)); }
TL_TEST(skill_descriptor_activation) { return run(host,4,"skill_descriptor_activation",reinterpret_cast<uintptr_t>(&original4)); }
TL_TEST(sound_descriptor_update) { return run(host,5,"sound_descriptor_update",reinterpret_cast<uintptr_t>(&original5)); }
TL_TEST(sound_descriptor_activation) { return run(host,6,"sound_descriptor_activation",reinterpret_cast<uintptr_t>(&original6)); }
TL_TEST(random_group_descriptor_loaded) { return run(host,7,"random_group_descriptor_loaded",reinterpret_cast<uintptr_t>(&original7)); }
