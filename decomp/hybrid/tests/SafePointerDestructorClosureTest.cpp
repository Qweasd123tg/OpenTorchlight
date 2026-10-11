// Direct evidence for two weak template closures emitted by GameUI lifetimes.
// The pointees here are genuinely constructed RegistryOwner:CRunicCore objects,
// NOT constructed CCharacter/CEquipment instances. Typed safe references use
// only the proven offset-zero inherited base registry, exactly as both original
// destructor bodies do. No gameplay or derived-class operation is exercised.
#include <cstdlib>
#include <cstring>
#include <new>
#include "Character.h"
#include "Equipment.h"
#include "SafePointer.h"
#include "RunicCore.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalCharacterSafeD1,(void*),"_ZN12TSafePointerI10CCharacterED1Ev")
TL_ORIGINAL(void, originalCharacterSafeD2,(void*),"_ZN12TSafePointerI10CCharacterED2Ev")
TL_ORIGINAL(void, originalEquipmentSafeD1,(void*),"_ZN12TSafePointerI10CEquipmentED1Ev")
TL_ORIGINAL(void, originalEquipmentSafeD2,(void*),"_ZN12TSafePointerI10CEquipmentED2Ev")
extern "C" void candidateCharacterSafeD1(void*) __asm__("_ZN12TSafePointerI10CCharacterED1Ev");
extern "C" void candidateCharacterSafeD2(void*) __asm__("_ZN12TSafePointerI10CCharacterED2Ev");
extern "C" void candidateEquipmentSafeD1(void*) __asm__("_ZN12TSafePointerI10CEquipmentED1Ev");
extern "C" void candidateEquipmentSafeD2(void*) __asm__("_ZN12TSafePointerI10CEquipmentED2Ev");
TL_FUNCTION(unregisterSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" char safeScalarNew[] __asm__("_Znwm");
extern "C" char safeArrayNew[] __asm__("_Znam");
extern "C" char safeScalarDelete[] __asm__("_ZdlPv");
extern "C" char safeArrayDelete[] __asm__("_ZdaPv");
extern "C" char safeOgreAllocate[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char safeOgreFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace safe_pointer_closure {
struct RegistryOwner:CRunicCore { unsigned long long cookie;RegistryOwner():CRunicCore(),cookie(0x3179bdf2468aceULL){} };
struct Slot { unsigned long long storage[4]; };
struct Case { unsigned kind,mode,poison,alias,fault; };
struct Stop {};
typedef TSafePointer<CCharacter> CharacterRef;
typedef TSafePointer<CEquipment> EquipmentRef;
typedef TArrayList<TSafePointer<void*>*> Registry;
static Slot slots[8];
static unsigned long long ownerStorage[2][8];
static RegistryOwner* owners[2];
static bool ownerAlive[2];
static unsigned registryIDs[2][8],registryCount[2],initialCount[2],refOwner[8],refIndex[8];
static void* originalRegistry[2];
static void* originalData[2];
static unsigned originalCapacity[2],originalGrow[2];
static unsigned target,errors,removeCalls,allocatorCalls;
static bool removed;
static Case current;
static autotest::Capture* capture;
static detour::Set *removePatch,*allocatorPatch;
static void n(unsigned v){capture->add(&v,sizeof(v));}
static void need(bool ok,unsigned code){if(!ok){++errors;n(0xe5000000u+code);}}
static void* ref(unsigned id){return reinterpret_cast<unsigned char*>(&slots[id])+8;}
template<class T>static T read(void* p,unsigned off){T v;std::memcpy(&v,static_cast<unsigned char*>(p)+off,sizeof(v));return v;}
static TSafePointer<void*>** entries(Registry* p){return read<TSafePointer<void*>**>(p,0);}
static unsigned count(Registry* p){return read<unsigned>(p,8);}
static unsigned capacity(Registry* p){return read<unsigned>(p,12);}
static unsigned grow(Registry* p){return read<unsigned>(p,16);}
static Registry*& registry(unsigned id){return *reinterpret_cast<Registry**>(reinterpret_cast<unsigned char*>(owners[id])+8);}
static unsigned identity(void* p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(p==ref(i))return i+1;return 99;}
static unsigned ownerIdentity(void* p){if(!p)return 0;for(unsigned i=0;i<2;++i)if(p==static_cast<CRunicCore*>(owners[i]))return i+1;return 99;}
static void construct(unsigned id){if(current.kind)::new(ref(id)) EquipmentRef;else ::new(ref(id)) CharacterRef;refOwner[id]=0;refIndex[id]=~0u;}
static void bind(unsigned id,unsigned ownerID){
    if(current.kind)static_cast<EquipmentRef*>(ref(id))->setObject(reinterpret_cast<CEquipment*>(owners[ownerID]));
    else static_cast<CharacterRef*>(ref(id))->setObject(reinterpret_cast<CCharacter*>(owners[ownerID]));
    refOwner[id]=ownerID+1;refIndex[id]=registryCount[ownerID];registryIDs[ownerID][registryCount[ownerID]++]=id;
}
static void setIndex(unsigned id,unsigned index){if(current.kind)static_cast<EquipmentRef*>(ref(id))->setIndex(index);else static_cast<CharacterRef*>(ref(id))->setIndex(index);refIndex[id]=index;}
static void destroyRef(unsigned id){if(current.kind)static_cast<EquipmentRef*>(ref(id))->~EquipmentRef();else static_cast<CharacterRef*>(ref(id))->~CharacterRef();}
static void guard(unsigned id){
    unsigned char* p=reinterpret_cast<unsigned char*>(&slots[id]);unsigned char poison=current.poison?0x5a:0xa5;
    for(unsigned i=0;i<32;++i)if(i<8||i>=20)need(p[i]==poison,10+id);
}
static void snapshot(){
    for(unsigned i=0;i<8;++i){
        void* p=read<void*>(ref(i),0);unsigned index=read<unsigned>(ref(i),8);
        need(ownerIdentity(p)==refOwner[i],30+i);need(index==refIndex[i],40+i);guard(i);
        n(ownerIdentity(p));n(index);capture->add(reinterpret_cast<unsigned char*>(&slots[i])+20,12);
    }
    for(unsigned k=0;k<2;++k){
        n(ownerAlive[k]);if(!ownerAlive[k])continue;
        need(owners[k]->cookie==0x3179bdf2468aceULL,50+k);
        need(registry(k)==originalRegistry[k],52+k);Registry* list=registry(k);
        need(list&&entries(list)==originalData[k],54+k);if(!list)continue;
        need(count(list)==registryCount[k],56+k);need(capacity(list)==originalCapacity[k],58+k);need(grow(list)==originalGrow[k],60+k);
        n(count(list));n(capacity(list));n(grow(list));
        // removeAt preserves its old trailing cell, including a last-cell
        // removal; verify every originally initialized entry, not only size.
        for(unsigned i=0;i<initialCount[k];++i){unsigned id=identity(entries(list)[i]);n(id);need(id==registryIDs[k][i]+1,70+k*8+i);}
    }
}
static void modelRemove(unsigned ownerID,unsigned index){
    if(index==~0u||index>=registryCount[ownerID])return;
    unsigned count=--registryCount[ownerID];unsigned moved=registryIDs[ownerID][count];registryIDs[ownerID][index]=moved;
    if(index<count)refIndex[moved]=index;removed=true;
}
static void remove(CRunicCore* p,TSafePointer<void*>* pointer,unsigned index){
    ++removeCalls;n(100);n(ownerIdentity(p));n(identity(pointer));n(index);
    need(pointer==ref(target),100);need(ownerIdentity(p)==refOwner[target],101);need(index==refIndex[target],102);
    // The destructor must not clear its object/index before calling out.
    snapshot();if(current.fault==1)throw Stop();
    unsigned ownerID=ownerIdentity(p)-1;
    removePatch->restore();reinterpret_cast<void(*)(CRunicCore*,TSafePointer<void*>*,unsigned)>(unregisterSafe_original)(p,pointer,index);
    TL_REDIRECT(*removePatch,unregisterSafe,&remove);if(removePatch->failed())_exit(86);
    modelRemove(ownerID,index);snapshot();if(current.fault==2)throw Stop();
}
static void installAllocators();
static void* scalarNew(size_t size){++allocatorCalls;allocatorPatch->restore();void* p=reinterpret_cast<void*(*)(size_t)>(safeScalarNew)(size);installAllocators();return p;}
static void* arrayNew(size_t size){++allocatorCalls;allocatorPatch->restore();void* p=reinterpret_cast<void*(*)(size_t)>(safeArrayNew)(size);installAllocators();return p;}
static void scalarDelete(void* p){++allocatorCalls;allocatorPatch->restore();reinterpret_cast<void(*)(void*)>(safeScalarDelete)(p);installAllocators();}
static void arrayDelete(void* p){++allocatorCalls;allocatorPatch->restore();reinterpret_cast<void(*)(void*)>(safeArrayDelete)(p);installAllocators();}
static void* ogreAllocate(size_t size,const char* file,int line,const char* function){++allocatorCalls;allocatorPatch->restore();void* p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(safeOgreAllocate)(size,file,line,function);installAllocators();return p;}
static void ogreFree(void* p){++allocatorCalls;allocatorPatch->restore();reinterpret_cast<void(*)(void*)>(safeOgreFree)(p);installAllocators();}
static void installAllocators(){
    allocatorPatch->redirect(safeScalarNew,safeScalarNew,&scalarNew);allocatorPatch->redirect(safeArrayNew,safeArrayNew,&arrayNew);
    allocatorPatch->redirect(safeScalarDelete,safeScalarDelete,&scalarDelete);allocatorPatch->redirect(safeArrayDelete,safeArrayDelete,&arrayDelete);
    allocatorPatch->redirect(safeOgreAllocate,safeOgreAllocate,&ogreAllocate);allocatorPatch->redirect(safeOgreFree,safeOgreFree,&ogreFree);
    if(allocatorPatch->failed())_exit(87);
}
static void setup(){
    std::memset(slots,current.poison?0x5a:0xa5,sizeof(slots));std::memset(ownerStorage,current.poison?0x5a:0xa5,sizeof(ownerStorage));
    std::memset(registryCount,0,sizeof(registryCount));removed=false;errors=removeCalls=allocatorCalls=0;
    for(unsigned k=0;k<2;++k){owners[k]=::new(ownerStorage[k])RegistryOwner;ownerAlive[k]=true;}
    // These static base conversions assert the actual declarations' zero offset.
    need(reinterpret_cast<uintptr_t>(static_cast<CRunicCore*>(reinterpret_cast<CCharacter*>(owners[0])))==reinterpret_cast<uintptr_t>(owners[0]),110);
    need(reinterpret_cast<uintptr_t>(static_cast<CRunicCore*>(reinterpret_cast<CEquipment*>(owners[1])))==reinterpret_cast<uintptr_t>(owners[1]),111);
    for(unsigned i=0;i<8;++i)construct(i);
    target=current.mode==5||current.mode>=7?2:current.mode==6?4:0;
    for(unsigned i=0;i<8;++i){
        if(current.mode<3&&i==target)continue;
        bind(i,current.mode==3?(i==target?0:1):(i<5?0:1));
    }
    if(current.mode==1)setIndex(target,0);
    if(current.mode==2)setIndex(target,0x81234567u);
    if(current.mode==7)setIndex(target,~0u);
    if(current.mode==8)setIndex(target,registryCount[0]);
    if(current.mode==9)setIndex(target,0x80000001u);
    for(unsigned k=0;k<2;++k){
        originalRegistry[k]=registry(k);originalData[k]=entries(registry(k));originalCapacity[k]=capacity(registry(k));originalGrow[k]=grow(registry(k));initialCount[k]=registryCount[k];
    }
    if(current.mode==10){
        owners[0]->~RegistryOwner();ownerAlive[0]=false;
        for(unsigned i=0;i<8;++i)if(refOwner[i]==1){refOwner[i]=0;refIndex[i]=~0u;}
    }
    snapshot();
}
static void side(const Case& c,bool ours,autotest::Capture& out){
    typedef char character_ref_size[sizeof(CharacterRef)==16?1:-1];typedef char equipment_ref_size[sizeof(EquipmentRef)==16?1:-1];
    current=c;capture=&out;setup();
    detour::Set removal,allocation;removePatch=&removal;allocatorPatch=&allocation;
    TL_REDIRECT(removal,unregisterSafe,&remove);installAllocators();if(removal.failed())_exit(88);
    unsigned beforeOwner=refOwner[target],beforeIndex=refIndex[target];bool threw=false;
    void(*fn)(void*)=c.kind?(ours?(c.alias?candidateEquipmentSafeD2:candidateEquipmentSafeD1):(c.alias?originalEquipmentSafeD2:originalEquipmentSafeD1)):(ours?(c.alias?candidateCharacterSafeD2:candidateCharacterSafeD1):(c.alias?originalCharacterSafeD2:originalCharacterSafeD1));
    try{autotest::invoke(out,fn,ref(target));}catch(const Stop&){threw=true;}catch(...){_exit(89);}
    need(threw==(c.fault!=0),120);need(removeCalls==(beforeOwner?1u:0u),121);need(allocatorCalls==0,122);
    if(!threw){refOwner[target]=0;refIndex[target]=~0u;}
    else {need(refOwner[target]==beforeOwner&&refIndex[target]==beforeIndex,123);}
    n(101);n(threw);n(removeCalls);n(allocatorCalls);n(removed);snapshot();
    removal.restore();allocation.restore();
    // A throwing destructor has ended the reference lifetime too. If the
    // collaborator did not unlink it, remove its address from the real registry
    // before owner invalidation; never invoke the ended destructor a second time.
    for(unsigned k=0;k<2;++k)if(ownerAlive[k]){
        Registry* list=registry(k);
        for(unsigned i=0;i<count(list);++i)if(entries(list)[i]==ref(target)){
            reinterpret_cast<void(*)(CRunicCore*,TSafePointer<void*>*,unsigned)>(unregisterSafe_original)(owners[k],reinterpret_cast<TSafePointer<void*>*>(ref(target)),i);break;
        }
        owners[k]->~RegistryOwner();ownerAlive[k]=false;
    }
    for(unsigned i=0;i<8;++i)if(i!=target){need(read<void*>(ref(i),0)==0&&read<unsigned>(ref(i),8)==~0u,130+i);guard(i);destroyRef(i);}
    guard(target);n(0x5afe0012u);n(errors);
}
static void original(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void candidate(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
static bool clean(const autotest::Capture& c){if(c.length<8)return false;unsigned last[2];std::memcpy(last,c.data+c.length-8,8);return last[0]==0x5afe0012u&&last[1]==0;}
static bool valid(const autotest::Outcome& a,const autotest::Outcome& b,bool exception){return a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.callStarted&&b.capture.callStarted&&bool(a.capture.callCompleted)==!exception&&bool(b.capture.callCompleted)==!exception&&!a.capture.issue&&!b.capture.issue&&clean(a.capture)&&clean(b.capture)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
static void report(const tlhybrid_host* host,const Case& c,const autotest::Outcome& a,const autotest::Outcome& b){
    host->log("    safe closure kind%u mode%u poison%u alias%u fault%u exits%d/%d issue%u/%u length%lu/%lu\n",c.kind,c.mode,c.poison,c.alias,c.fault,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
    for(unsigned side=0;side<2;++side){const autotest::Capture& q=side?b.capture:a.capture;for(size_t i=0;i+4<=q.length;++i){unsigned code;std::memcpy(&code,q.data+i,4);if(code>=0xe5000000u&&code<0xe5000100u)host->log("    safe oracle side%u error%u\n",side,code-0xe5000000u);}}
}
static int normal(const tlhybrid_host* host,unsigned kind,const char* name){
    autotest::Coverage coverage(name,reinterpret_cast<uintptr_t>(kind?&originalEquipmentSafeD1:&originalCharacterSafeD1));
    for(unsigned mode=0;mode<11;++mode)for(unsigned pattern=0;pattern<4;++pattern){
        Case c={kind,mode,pattern&1,pattern>>1,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        int difference=coverage.observe(host,a,b);if(difference||!valid(a,b,false)){report(host,c,a,b);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    safe closure:44 completed pairs; D1/D2 share one original address; null/registered/stale-index/owner-first states\n");return 0;
}
}
TL_TEST(safe_pointer_character_destructor_closure){return safe_pointer_closure::normal(host,0,"safe_pointer_character_destructor_closure");}
TL_TEST(safe_pointer_equipment_destructor_closure){return safe_pointer_closure::normal(host,1,"safe_pointer_equipment_destructor_closure");}
TL_TEST(safe_pointer_destructor_closure_expected_exceptions){
    using namespace safe_pointer_closure;unsigned count=0;
    for(unsigned kind=0;kind<2;++kind)for(unsigned fault=1;fault<=2;++fault)for(unsigned mode=4;mode<=6;++mode)for(unsigned pattern=0;pattern<4;++pattern){
        Case c={kind,mode,pattern&1,pattern>>1,fault};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++count;
        if(!valid(a,b,true)){report(host,c,a,b);return 1;}
    }
    host->log("    EXPECTED SAFE-REFERENCE EXCEPTIONS:%u before/after-unregister witnesses; no completed-call coverage\n",count);return 0;
}
