// Populated original definition parser -> accepted manager/controller -> Quest A.
// Only Quest A (ctor, D1/D0, listeners) varies between sides. B/C remain
// actual original parser/reset/persistence boundaries and receive no credit.
// Original CDataGroup cached definitions, child constructors/parsers/destructors
// execute; filesystem/cache, absent sounds/UI and unit resource lookup are
// explicitly controlled boundaries. No input-resource writes are permitted.
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "TArrayList.h"

#define QLC_PAIR(R,N,A,S) TL_ORIGINAL(R,qpcOld##N,A,S) extern "C" R qpcNew##N A __asm__(S);
QLC_PAIR(void,Ctor,(void*,void*),"_ZN13CQuestManagerC1EP16CResourceManager")
QLC_PAIR(void,Reload,(void*),"_ZN13CQuestManager12reloadQuestsEv")
QLC_PAIR(void,Dtor,(void*),"_ZN13CQuestManagerD1Ev")
QLC_PAIR(void*,Lookup,(void*,const std::wstring&),"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(bool,Active,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(char,Complete,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(void,Names,(void*,TArrayList<std::wstring>&),"_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
QLC_PAIR(void,ControllerInit,(void*),"_ZN16CQuestController19initQuestControllerEv")
extern "C" void qpcNewLoad(void*) __asm__("_ZN13CQuestManager10loadQuestsEv");
TL_ORIGINAL(void,qpcResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qpcResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qpcControllerCtor,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
TL_ORIGINAL(void,qpcControllerDtor,(void*),"_ZN16CQuestControllerD1Ev")
TL_ORIGINAL(void,qpcQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qpcQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qpcQuestDelete,(void*),"_ZN6CQuestD0Ev")
extern "C" void qpcCandidateCtor(void*,void*,void*) __asm__("_ZN6CQuestC1EP16CResourceManagerP13CQuestManager");
extern "C" void qpcCandidateDtor(void*) __asm__("_ZN6CQuestD1Ev");
extern "C" void qpcCandidateDelete(void*) __asm__("_ZN6CQuestD0Ev");
TL_ORIGINAL(void,qpcOriginalAdd,(void*,void*),"_ZN6CQuest27addQuestControllerListernerEP16CQuestController")
TL_ORIGINAL(void,qpcOriginalRemove,(void*,void*),"_ZN6CQuest30removeQuestControllerListernerEP16CQuestController")
extern "C" void qpcCandidateAdd(void*,void*) __asm__("_ZN6CQuest27addQuestControllerListernerEP16CQuestController");
extern "C" void qpcCandidateRemove(void*,void*) __asm__("_ZN6CQuest30removeQuestControllerListernerEP16CQuestController");
TL_FUNCTION(qpcAddBoundary,"_ZN6CQuest27addQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qpcRemoveBoundary,"_ZN6CQuest30removeQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qpcDeleteBoundary,"_ZN6CQuestD0Ev")
TL_FUNCTION(qpcUnitsSingleton,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(qpcUnitLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_ORIGINAL(CDataGroup*,qpcAddGroup,(void*,const std::wstring&),"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char qpcFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qpcArrayFree[] __asm__("_ZdaPv");
TL_ORIGINAL(void,qpcQuestNPCs,(void*,TArrayList<CDataGroup*>&),"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
TL_ORIGINAL(void,qpcGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qpcGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*,qpcAddWide,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(void*,qpcAddGuid,(void*,const std::wstring&,long long),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEx")
TL_FUNCTION(qpcMasterBoundary,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qpcFilesSingletonBoundary,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(qpcFilesBoundary,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(qpcCacheBoundary,"_ZN11CFileSystem12getDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qpcSoundBoundary,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qpcQuestCtorBoundary,"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_FUNCTION(qpcQuestDtorBoundary,"_ZN6CQuestD1Ev")
TL_FUNCTION(qpcNPCBoundary,"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
TL_FUNCTION(qpcUIBoundary,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qpcSaveBoundary,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qpcGuidBoundary,"_ZN9UTILITIES16createUniqueGuidEv")

#define QPC_CHILD_DECL(N,S) \
 TL_ORIGINAL(void,qpc##N##D1,(void*),"_ZN" S "D1Ev") \
 TL_ORIGINAL(void,qpc##N##D0,(void*),"_ZN" S "D0Ev") \
 TL_FUNCTION(qpc##N##Complete,"_ZN" S "D1Ev") \
 TL_FUNCTION(qpc##N##Delete,"_ZN" S "D0Ev")
QPC_CHILD_DECL(Dialog,"12CQuestDialog")
QPC_CHILD_DECL(Rewards,"13CQuestRewards")
QPC_CHILD_DECL(Requirements,"18CQuestRequirements")
QPC_CHILD_DECL(Unit,"14CQuestUnitData")
#undef QPC_CHILD_DECL
TL_ORIGINAL(unsigned,qpcRegister,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_ORIGINAL(void,qpcUnregister,(void*,void*,unsigned),"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qpcRegisterBoundary,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qpcUnregisterBoundary,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")

namespace quest_populated_consumers {
typedef std::wstring Wide;
typedef std::map<Wide,void*> QuestMap;
typedef std::map<Wide,bool> CompleteMap;
typedef std::map<CDataGroup*,void*> NPCMap;
typedef char WideABI[sizeof(Wide)==8?1:-1];
typedef char MapABI[sizeof(QuestMap)==48?1:-1];
typedef char RepositoryABI[sizeof(TRepository<Wide>)==0xa0?1:-1];
template<class T> T& at(void* p,unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);
}
struct Case { unsigned entry, initialCount, detachController; };
static const Case* current;
static autotest::Capture* capture;
static bool candidate, masterAvailable;
static unsigned errors, phase, filesCalls, cacheCalls, soundCalls;
static unsigned questCtors, questDtors, npcCalls, saveCalls, unitLookups;
static void *manager,*resource,*controller,*master,*files,*soundOwner,*soundInfo;
static CDataGroup* groups[3];
static CDataGroup* itemGroup;
static detour::Set *ctorObservation,*dtorObservation,*deleteObservation,*npcObservation;
static const wchar_t* const paths[] = {
    L"media/quests/lifecycle_first.dat",L"media/quests/lifecycle_second.dat",
    L"media/quests/lifecycle_third.dat"
};
static const wchar_t* const names[] = {L"FIRST",L"SECOND",L"THIRD"};
static void number(unsigned n) { capture->add(&n,sizeof(n)); }
static void need(bool b,unsigned site) {
    if (!b) { ++errors; number(0xf1000000u+site); }
}
static void* storage(unsigned n) {
    void* p=autotest::allocate(n); if (!p) _exit(71);
    std::memset(p,0xa5,n); return p;
}
static void*& singleton() { return *reinterpret_cast<void**>(0x14fc6e0); }
static void* masterBoundary() { return masterAvailable?master:0; }
static void* filesBoundary() { return files; }
static void* noUI() { return 0; }
static void rejectSave(void*, const Wide&) { ++saveCalls; need(false,50); }
static unsigned long long stableGuid() { return 0x81726354ULL; }
static unsigned fileList(void* self,const Wide& path,TArrayList<Wide>& list,
                         Wide pattern,bool a,bool b,bool c,bool d) {
    need(self==files && path==L"media/quests/" && pattern==L"*.dat",1);
    need(a&&b&&!c&&!d && list.size()==0 && at<unsigned>(&list,16)==10,2);
    need(singleton()==manager && at<void*>(manager,0x38)==resource,3);
    need(at<QuestMap>(manager,0x40).empty() &&
         at<CompleteMap>(manager,0x70).empty() &&
         at<NPCMap>(manager,0xa0).empty(),4);
    need(!at<void*>(manager,0x18) && !at<unsigned>(manager,0x20),5);
    ++filesCalls; number(100+phase);
    if (!phase) {
        // Deliberately not map order: loaded-map consumers must expose FIRST,
        // SECOND even when the filesystem reports SECOND before FIRST.
        if (current->initialCount==2) list.add(Wide(paths[1]));
        list.add(Wide(paths[0]));
    } else {
        list.add(Wide(paths[2])); list.add(Wide(paths[1]));
    }
    return list.size();
}
static CDataGroup* cachedGroup(void* self,const Wide& path) {
    need(self==files,6); ++cacheCalls;
    for (unsigned i=0;i<3;++i) if (path==paths[i]) {
        number(200+i); return groups[i];
    }
    need(false,7); return 0;
}
static void* absentSound(void* self,const Wide& name) {
    need(self==soundInfo && singleton()==manager,8);
    need(name==(soundCalls?L"QUESTCOMPLETED":L"QUESTRECEIVED"),9);
    ++soundCalls; number(300+soundCalls); return 0;
}
// Reachability and lifetime are distinct observations: snapshot each real
// parser-produced object, then require the original child D0, D1 and allocator
// release for that exact object. No synthetic vtables or child lifetimes.
struct Owned {void* pointer;unsigned kind,d0,d1,freed;};
static Owned owned[64]; static unsigned ownedCount;
static bool observingGraph;
static detour::Set *freeObservation,*arrayFreeObservation,*childD0Observation,*childD1Observation;
static detour::Set *addObservation,*removeObservation,*registerObservation,*unregisterObservation;
static unsigned addCalls,removeCalls,registered,unregistered,listenerFreed;
static void* liveListener;
static unsigned registryCount(void* core,void* weak) {
    void* list=at<void*>(core,8); unsigned count=0;
    if(list) for(unsigned i=0;i<at<unsigned>(list,8);++i)
        if(at<void**>(list,0)[i]==weak) ++count;
    return count;
}
static void remember(void* p,unsigned kind) {
    need(p!=0 && ownedCount<64,60); if(!p||ownedCount>=64) return;
    for(unsigned i=0;i<ownedCount;++i) need(owned[i].pointer!=p,61);
    Owned x={p,kind,0,0,0}; owned[ownedCount++]=x;
}
static void childEvent(void* p,unsigned kind,bool deleting) {
    if(!observingGraph) return;
    bool found=false;
    for(unsigned i=0;i<ownedCount;++i) if(owned[i].pointer==p) {
        found=true; need(owned[i].kind==kind,62);
        if(deleting) ++owned[i].d0; else ++owned[i].d1;
        number((deleting?1000:1100)+kind); break;
    }
    need(found,63);
}
static void installChildD0(); static void installChildD1();
#define QPC_CHILD_WATCH(N,K) \
 static void observed##N##D0(void* p) { \
  childEvent(p,K,true); childD0Observation->restore(); qpc##N##D0(p); installChildD0(); } \
 static void observed##N##D1(void* p) { \
  childEvent(p,K,false); childD1Observation->restore(); qpc##N##D1(p); installChildD1(); }
QPC_CHILD_WATCH(Dialog,1)
QPC_CHILD_WATCH(Rewards,2)
QPC_CHILD_WATCH(Requirements,3)
QPC_CHILD_WATCH(Unit,4)
#undef QPC_CHILD_WATCH
static void installChildD0() {
    TL_REDIRECT(*childD0Observation,qpcDialogDelete,&observedDialogD0);
    TL_REDIRECT(*childD0Observation,qpcRewardsDelete,&observedRewardsD0);
    TL_REDIRECT(*childD0Observation,qpcRequirementsDelete,&observedRequirementsD0);
    TL_REDIRECT(*childD0Observation,qpcUnitDelete,&observedUnitD0);
}
static void installChildD1() {
    TL_REDIRECT(*childD1Observation,qpcDialogComplete,&observedDialogD1);
    TL_REDIRECT(*childD1Observation,qpcRewardsComplete,&observedRewardsD1);
    TL_REDIRECT(*childD1Observation,qpcRequirementsComplete,&observedRequirementsD1);
    TL_REDIRECT(*childD1Observation,qpcUnitComplete,&observedUnitD1);
}
static void freeEvent(void* p) {
    if(p && p==liveListener) { ++listenerFreed; liveListener=0; }
    if(observingGraph) for(unsigned i=0;i<ownedCount;++i)
        if(owned[i].pointer==p) {++owned[i].freed;number(1200+owned[i].kind);}
}
static void release(void* p) {
    freeEvent(p); freeObservation->restore();
    reinterpret_cast<void(*)(void*)>(qpcFree)(p);
    freeObservation->redirect(qpcFree,qpcFree,&release);
}
static void releaseArray(void* p) {
    freeEvent(p); arrayFreeObservation->restore();
    reinterpret_cast<void(*)(void*)>(qpcArrayFree)(p);
    arrayFreeObservation->redirect(qpcArrayFree,qpcArrayFree,&releaseArray);
}
static unsigned registerWeak(void* core,void* weak) {
    registerObservation->restore(); unsigned index=qpcRegister(core,weak);
    TL_REDIRECT(*registerObservation,qpcRegisterBoundary,&registerWeak);
    if(core==controller) { ++registered; need(registryCount(core,weak)==1,64); }
    return index;
}
static void unregisterWeak(void* core,void* weak,unsigned index) {
    if(core==controller) {++unregistered;need(registryCount(core,weak)==1,65);}
    unregisterObservation->restore(); qpcUnregister(core,weak,index);
    TL_REDIRECT(*unregisterObservation,qpcUnregisterBoundary,&unregisterWeak);
    if(core==controller) need(registryCount(core,weak)==0,66);
}
static void selectedAdd(void* quest,void* ctrl) {
    ++addCalls; addObservation->restore();
    if(candidate) qpcCandidateAdd(quest,ctrl); else qpcOriginalAdd(quest,ctrl);
    TL_REDIRECT(*addObservation,qpcAddBoundary,&selectedAdd);
}
static void selectedRemove(void* quest,void* ctrl) {
    ++removeCalls; removeObservation->restore();
    if(candidate) qpcCandidateRemove(quest,ctrl); else qpcOriginalRemove(quest,ctrl);
    TL_REDIRECT(*removeObservation,qpcRemoveBoundary,&selectedRemove);
}
static void* unitSingleton() {return itemGroup;}
static CDataGroup* unitLookup(void* self,const Wide& category,const Wide& name) {
    need(self==itemGroup && category==L"ITEMS" && name==L"fixture-item",67);
    ++unitLookups;return itemGroup;
}
static void populateDefinition(CDataGroup* group) {
    CDataGroup* dialogs=qpcAddGroup(group,Wide(L"DIALOG"));
    const wchar_t* tags[]={L"INTRO",L"RETURN",L"COMPLETE",L"PASSIVE",L"DETAILS"};
    for(unsigned i=0;i<5;++i) {
        CDataGroup* d=qpcAddGroup(dialogs,Wide(tags[i]));
        qpcAddWide(d,Wide(L"DIALOG"),Wide(L"Populated lifecycle dialog"),false);
    }
    const wchar_t* families[]={L"DEFEAT",L"ACQUIRE",L"POPULATE"};
    for(unsigned i=0;i<3;++i) {
        CDataGroup* family=qpcAddGroup(group,Wide(families[i]));
        CDataGroup* unit=qpcAddGroup(family,Wide(L"UNIT"));
        qpcAddWide(unit,Wide(L"ITEM"),Wide(L"fixture-item"),false);
    }
}
static void checkGraph(void* quest,bool record) {
    const unsigned lists[]={0x60,0x78,0x90,0xa8};
    for(unsigned i=0;i<4;++i) {
        TArrayList<void*>& list=at<TArrayList<void*> >(quest,lists[i]);
        need(list.size()==1,70+i);
        if(list.size()!=1) continue;
        void* dialog=list[0];need(dialog && at<void*>(dialog,0x10)==quest,74);
        need(!at<void*>(dialog,0x68) && at<unsigned>(dialog,0x20)==1,75);
        if(record) {remember(dialog,1);remember(at<void*>(&list,0),6);}
    }
    void* primary=at<void*>(quest,0xc0);
    need(primary && at<void*>(primary,0x10)==quest && at<unsigned>(primary,0x20)==1,76);
    if(record) {remember(primary,1);remember(at<void*>(quest,0x128),2);remember(at<void*>(quest,0x1e0),3);}
    const unsigned families[]={0x160,0x178,0x190};
    for(unsigned i=0;i<3;++i) {
        TArrayList<TArrayList<void*>*>& outer=at<TArrayList<TArrayList<void*>*> >(quest,families[i]);
        need(outer.size()==1,77+i);
        if(outer.size()!=1) continue;
        TArrayList<void*>* inner=outer[0];need(inner && inner->size()==1,80);
        if(!inner||inner->size()!=1) continue;
        void* unit=(*inner)[0];
        need(unit && at<void*>(unit,0x18)==quest && at<void*>(unit,0x20)==itemGroup,81);
        need(at<Wide>(unit,0x80)==L"fixture-item" && at<long long>(unit,0x30)==12345,82);
        if(record) {remember(unit,4);remember(inner,5);remember(at<void*>(inner,0),6);remember(at<void*>(&outer,0),6);}
    }
}
static void observeOwnedGraph(void* quest) {
    need(!observingGraph,83);ownedCount=0;checkGraph(quest,true);remember(quest,7);
    observingGraph=true;
}
static void verifyOwnedGraph() {
    unsigned kinds[8]={0,0,0,0,0,0,0,0};
    for(unsigned i=0;i<ownedCount;++i) {
        Owned& p=owned[i];++kinds[p.kind];if(p.freed!=1) {number(2000+p.kind);number(p.freed);}need(p.freed==1,84);
        if(p.kind<=4) {if(p.d0!=1||p.d1!=1) {number(2100+p.kind);number(p.d0);number(p.d1);}need(p.d0==1 && p.d1==1,85);}
    }
    need(kinds[1]==5 && kinds[2]==1 && kinds[3]==1 && kinds[4]==3 && kinds[5]==3 && kinds[6]==10 && kinds[7]==1,86);
    for(unsigned i=1;i<8;++i) number(kinds[i]);observingGraph=false;
}
static void observedQuestCtor(void* self,void* r,void* m) {
    need(r==resource && m==manager && singleton()==manager,10);
    ++questCtors;
    ctorObservation->restore();
    if(candidate) qpcCandidateCtor(self,r,m); else qpcQuestCtor(self,r,m);
    TL_REDIRECT(*ctorObservation,qpcQuestCtorBoundary,&observedQuestCtor);
    need(!ctorObservation->failed(),11);
    need(at<void*>(self,0x1d0)==manager && at<void*>(self,0x1d8)==resource,12);
    need(at<void*>(self,0x1e0)!=0 && at<Wide>(self,0x50).empty(),13);
}
static void observedNPCs(void* self,TArrayList<CDataGroup*>& list) {
    need(at<void*>(self,0x1d0)==manager && at<void*>(self,0x1d8)==resource,14);
    // Present DEFEAT/ACQUIRE tags default MINCREATE/MAXCREATE to zero.
    // Original d19ade..d19b09 clamps both to one; its returned minimum is
    // stored by loadQuestData at d1be96 (+1a8) and d1befb (+1ac).
    need(at<int>(self,0x1a8)==1 && at<int>(self,0x1ac)==1,15);
    need(at<void*>(self,0x128)!=0 && at<void*>(self,0x1e0)!=0,16);
    need(at<unsigned>(&list,16)==100 && list.size()==0,17);
    capture->addText(at<Wide>(self,0x50));
    ++npcCalls;
    npcObservation->restore();
    qpcQuestNPCs(self,list);
    TL_REDIRECT(*npcObservation,qpcNPCBoundary,&observedNPCs);
    need(!npcObservation->failed() && list.size()==0,18);
}
static void observedQuestDtor(void* self) {
    dtorObservation->restore();
    if(candidate) qpcCandidateDtor(self); else qpcQuestDtor(self);
    TL_REDIRECT(*dtorObservation,qpcQuestDtorBoundary,&observedQuestDtor);
    need(!dtorObservation->failed(),19);
}
static void observeOwnedGraph(void*);
static void verifyOwnedGraph();
static void observedQuestDelete(void* self) {
    capture->addText(at<Wide>(self,0x50)); ++questDtors;
    observeOwnedGraph(self);
    deleteObservation->restore();
    if(candidate) qpcCandidateDelete(self); else qpcQuestDelete(self);
    TL_REDIRECT(*deleteObservation,qpcDeleteBoundary,&observedQuestDelete);
    need(!deleteObservation->failed(),52);
    verifyOwnedGraph();
}
static void* lookup(const Wide& n) {
    return qpcNewLookup(manager,n);
}
static bool active(const Wide& n) {
    return qpcNewActive(manager,n);
}
static char complete(const Wide& n) {
    return qpcNewComplete(manager,n);
}
static void bindController(const Wide& name) {
    at<Wide>(controller,0xa8)=name;
    qpcNewControllerInit(controller);
    void* q=lookup(name);
    need(q && at<void*>(controller,0x98)==q,20);
    need(at<bool>(controller,0xb0) && !at<bool>(controller,0xb1),21);
    need(at<unsigned>(q,0x1b8)==1,22);
    void* listener=at<void**>(q,0x1b0)[0];
    need(listener && at<void*>(listener,0)==controller,23);
    need(registryCount(controller,listener)==1,87);liveListener=listener;
}
static void checkLoaded(unsigned first,unsigned count) {
    TArrayList<Wide> actual(3);
    qpcNewNames(manager,actual);
    need(actual.size()==count && at<QuestMap>(manager,0x40).size()==count,24);
    need(at<CompleteMap>(manager,0x70).size()==count && at<NPCMap>(manager,0xa0).empty(),25);
    for (unsigned i=0;i<count;++i) {
        Wide n(names[first+i]);
        need(i<actual.size() && actual[i]==n,26);
        void* q=lookup(n); need(q!=0,27);
        if (!q) continue;
        need(at<Wide>(q,0x50)==n && at<Wide>(q,0x58)==L"Lifecycle \u0416\u732b",28);
        need(at<long long>(q,0x1c8)==static_cast<long long>(0x12131400+first+i),29);
        need(at<Wide>(q,0x48)==paths[first+i],30);
        need(!at<bool>(q,0x26) && !active(n) && !complete(n),31);
        checkGraph(q,false);
        capture->addText(n); capture->addText(at<Wide>(q,0x58));
    }
    need(!lookup(L"first") && !lookup(L"MISSING") && !complete(L"MISSING"),32);
    need(!at<void*>(manager,0x18) && !at<unsigned>(manager,0x20),33);
}
static void initializeOriginalStatics() {
    // Tests run before game static initialization. Only cells used by these
    // real original constructors/parser paths are initialized, per their ELF
    // static initializer stores. Do not invoke whole game TU initializers.
    const unsigned cells[]={0x14f9fe8,0x14dd9c8,0x14dd9d8,0x14dda88,
        0x151d408,0x151ab48,0x151c128,0x14fb488,0x14ff1a8,0x1509e88};
    for (unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)
        new(reinterpret_cast<void*>(cells[i])) Wide();
    new(reinterpret_cast<void*>(0x14dd9c0)) std::string();
    const wchar_t* typeNames[]={L"",L"FIND",L"KILL NUM",L"KILL BOSS"};
    for (unsigned i=0;i<4;++i)
        new(reinterpret_cast<void*>(0x14fa000+i*8)) Wide(typeNames[i]);
    // Both Quest and QuestDialog own their original tag tables.
    const wchar_t* dialogNames[]={L"ERROR",L"INTRO",L"RETURN",L"COMPLETE",L"PASSIVE",L"DETAILS"};
    for (unsigned i=0;i<6;++i)
        new(reinterpret_cast<void*>(0x14fa020+i*8)) Wide(dialogNames[i]);
    for(unsigned i=0;i<6;++i) new(reinterpret_cast<void*>(0x14fb4c0+i*8)) Wide(dialogNames[i]);
    new(reinterpret_cast<void*>(0x14fb4f0)) Wide(L"GIVEITEM");
    new(reinterpret_cast<void*>(0x14fb4f8)) Wide(L"TAKEITEM");
    new(reinterpret_cast<void*>(0x14ff260)) Wide(L"ITEMS");
    *reinterpret_cast<unsigned*>(0x1500730)=0;
    new(reinterpret_cast<void*>(0x14fa050)) Wide(L"COMPLETE_ON_QUEST_ACCEPT");
    new(reinterpret_cast<void*>(0x14fa058)) Wide(L"COMPLETE_ON_QUEST_COMPLETE");
    ::new(reinterpret_cast<void*>(0x14dd9e0)) TRepository<Wide>(Wide());
}
static void side(void* context,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(context); capture=&out; candidate=ours;
    errors=phase=filesCalls=cacheCalls=soundCalls=questCtors=questDtors=npcCalls=0;
    masterAvailable=false; autotest::g_arenaUsed=0; initializeOriginalStatics();
    manager=storage(0xd0); resource=storage(0x48); controller=storage(0xb8);
    master=storage(0x190); files=storage(8); soundOwner=storage(8); soundInfo=storage(8);
    std::memset(master,0,0x190); at<void*>(master,0x98)=soundOwner; at<void*>(master,0x100)=soundInfo;
    void* savedManager=singleton(); singleton()=0;
    detour::Set environment,ctorWatch,dtorWatch,deleteWatch,npcWatch,addWatch,removeWatch,freeWatch,arrayFreeWatch,childD0Watch,childD1Watch,registerWatch,unregisterWatch;
    ctorObservation=&ctorWatch; dtorObservation=&dtorWatch; deleteObservation=&deleteWatch; npcObservation=&npcWatch;
    TL_REDIRECT(environment,qpcMasterBoundary,&masterBoundary);
    TL_REDIRECT(environment,qpcFilesSingletonBoundary,&filesBoundary);
    TL_REDIRECT(environment,qpcFilesBoundary,&fileList);
    TL_REDIRECT(environment,qpcCacheBoundary,&cachedGroup);
    TL_REDIRECT(environment,qpcSoundBoundary,&absentSound);
    TL_REDIRECT(environment,qpcUIBoundary,&noUI);
    // Cached fixtures have explicit GUIDs. Never permit original resource writes.
    saveCalls=unitLookups=0;
    TL_REDIRECT(environment,qpcSaveBoundary,&rejectSave);
    TL_REDIRECT(environment,qpcGuidBoundary,&stableGuid);
    TL_REDIRECT(ctorWatch,qpcQuestCtorBoundary,&observedQuestCtor);
    TL_REDIRECT(dtorWatch,qpcQuestDtorBoundary,&observedQuestDtor);
    TL_REDIRECT(deleteWatch,qpcDeleteBoundary,&observedQuestDelete);
    TL_REDIRECT(npcWatch,qpcNPCBoundary,&observedNPCs);
    if (environment.failed()||ctorWatch.failed()||dtorWatch.failed()||deleteWatch.failed()||npcWatch.failed()) {
        out.issue=autotest::Capture::InvalidReport; return;
    }
    addObservation=&addWatch;removeObservation=&removeWatch;
    registerObservation=&registerWatch;unregisterObservation=&unregisterWatch;
    freeObservation=&freeWatch;arrayFreeObservation=&arrayFreeWatch;
    childD0Observation=&childD0Watch;childD1Observation=&childD1Watch;
    addCalls=removeCalls=registered=unregistered=listenerFreed=ownedCount=0;
    liveListener=0;observingGraph=false;
    TL_REDIRECT(addWatch,qpcAddBoundary,&selectedAdd);
    TL_REDIRECT(removeWatch,qpcRemoveBoundary,&selectedRemove);
    TL_REDIRECT(registerWatch,qpcRegisterBoundary,&registerWeak);
    TL_REDIRECT(unregisterWatch,qpcUnregisterBoundary,&unregisterWeak);
    TL_REDIRECT(environment,qpcUnitsSingleton,&unitSingleton);
    TL_REDIRECT(environment,qpcUnitLookup,&unitLookup);
    freeWatch.redirect(qpcFree,qpcFree,&release);
    arrayFreeWatch.redirect(qpcArrayFree,qpcArrayFree,&releaseArray);
    installChildD0();installChildD1();
    if(addWatch.failed()||removeWatch.failed()||registerWatch.failed()||unregisterWatch.failed()||
       environment.failed()||freeWatch.failed()||arrayFreeWatch.failed()||childD0Watch.failed()||childD1Watch.failed()) {
        out.issue=autotest::Capture::InvalidReport;return;
    }
    qpcResourceCtor(resource,0);
    need(!at<void*>(resource,0x28) && !at<unsigned>(resource,0x30),34);
    qpcControllerCtor(controller,resource);
    itemGroup=static_cast<CDataGroup*>(storage(0x60));
    qpcGroupCtor(itemGroup,Wide(L"UNIT"),0,20,10,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));
    qpcAddWide(itemGroup,Wide(L"UNIT_GUID"),Wide(L"12345"),false);
    const wchar_t* mixedNames[]={L"First",L"Second",L"Third"};
    for (unsigned i=0;i<3;++i) {
        groups[i]=static_cast<CDataGroup*>(storage(0x60));
        qpcGroupCtor(groups[i],Wide(L"QUEST"),0,20,10,
                     reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));
        qpcAddWide(groups[i],Wide(L"NAME"),Wide(mixedNames[i]),false);
        qpcAddWide(groups[i],Wide(L"DISPLAYNAME"),Wide(L"Lifecycle \u0416\u732b"),false);
        qpcAddGuid(groups[i],Wide(L"QUEST_GUID"),0x12131400+i);
        populateDefinition(groups[i]);
    }
    masterAvailable=true;
    typedef void(*Ctor)(void*,void*); Ctor ctor=&qpcNewCtor;
    if (!current->entry && !autotest::beginInvocation(out,ctor)) return;
    // Intentionally NO detour of loadQuests. Both callers must invoke their
    // actual selected definition loader, not a fake or an observation shim.
    ctor(manager,resource);
    if (!current->entry) out.callCompleted=1;
    need(singleton()==manager && filesCalls==1 && soundCalls==2,35);
    need(questCtors==current->initialCount && npcCalls==current->initialCount && !questDtors,36);
    void* sound=at<void*>(manager,0x30);
    need(sound && at<void*>(sound,0x10)==soundOwner,37);
    checkLoaded(0,current->initialCount); bindController(Wide(L"FIRST"));
    if (current->entry) {
        void* first=lookup(L"FIRST");
        at<TArrayList<void*> >(manager,0x18).add(first);
        at<CompleteMap>(manager,0x70)[L"FIRST"]=true;
        need(active(L"FIRST") && complete(L"FIRST"),38);
        phase=1;
        typedef void(*Reload)(void*); Reload reload=&qpcNewReload;
        if (!autotest::beginInvocation(out,reload)) return;
        reload(manager); out.callCompleted=1;
        need(filesCalls==2 && questDtors==current->initialCount,39);
        need(!at<void*>(controller,0x98),40); // Original CRunicCore invalidation.
        need(!lookup(L"FIRST") && !active(L"FIRST") && !complete(L"FIRST"),41);
        checkLoaded(1,2); bindController(Wide(L"SECOND"));
        need(at<void*>(manager,0x30)==sound && at<void*>(manager,0x38)==resource,44);
        need(singleton()==manager && soundCalls==2,45);
    }
    // Both real controller-first removal and manager-first invalidation paths.
    if(current->detachController) {
        qpcControllerDtor(controller);need(!liveListener,88);
    }
    qpcNewDtor(manager);
    need(!singleton() && (current->detachController || !at<void*>(controller,0x98)),46);
    need(questDtors==questCtors && npcCalls==questCtors && cacheCalls==questCtors,47);
    if(!current->detachController) qpcControllerDtor(controller);
    need(addCalls==1+current->entry && registered==addCalls && unregistered==registered && listenerFreed==registered,89);
    need(removeCalls==(current->detachController?1u:0u),90);
    number(addCalls);number(removeCalls);number(registered);number(unregistered);number(listenerFreed);
    qpcResourceDtor(resource); singleton()=savedManager;
    for (unsigned i=0;i<3;++i) qpcGroupDtor(groups[i]);
    qpcGroupDtor(itemGroup);
    reinterpret_cast<TRepository<Wide>*>(0x14dd9e0)->~TRepository<Wide>();
    number(filesCalls); number(cacheCalls); number(soundCalls);
    number(questCtors); number(questDtors); number(npcCalls);
    need(unitLookups>=questCtors*3,53); number(unitLookups);
    need(saveCalls==0,51); number(saveCalls);
    need(!environment.failed()&&!ctorWatch.failed()&&!dtorWatch.failed()&&!deleteWatch.failed()&&
         !npcWatch.failed()&&!addWatch.failed()&&!removeWatch.failed()&&!registerWatch.failed()&&
         !unregisterWatch.failed()&&!freeWatch.failed()&&!arrayFreeWatch.failed()&&
         !childD0Watch.failed()&&!childD1Watch.failed(),91);
    number(0x514c434eu); number(errors);
}
static void original(void* c,autotest::Capture& out) { side(c,out,false); }
static void recovered(void* c,autotest::Capture& out) { side(c,out,true); }
static bool good(const autotest::Outcome& o) {
    unsigned footer[2]={0,1};
    if (o.capture.length>=8) std::memcpy(footer,o.capture.data+o.capture.length-8,8);
    return o.reportValid && !o.childStatus && !o.capture.issue &&
           footer[0]==0x514c434eu && !footer[1];
}
static bool pair(const tlhybrid_host* host,Case& c) {
    // Refuse an accidentally imported original at any credited candidate edge.
    // Manager-to-loader relocation binding is additionally checked by the
    // production object/link closure; no detour manufactures that edge here.
    host->log("tlhybrid: populated consumer entry=%u count=%u detach=%u binding check\n",c.entry,c.initialCount,c.detachController);
    if (!host->comparison_pair(0xd16280,(uint64_t)&qpcCandidateCtor) ||
        !host->comparison_pair(0xd1a390,(uint64_t)&qpcCandidateDtor) ||
        !host->comparison_pair(0xd1b5c0,(uint64_t)&qpcCandidateDelete) ||
        !host->comparison_pair(0xd14860,(uint64_t)&qpcCandidateAdd) ||
        !host->comparison_pair(0xd14b30,(uint64_t)&qpcCandidateRemove) ||
        !host->comparison_pair(0xd31410,(uint64_t)&qpcNewLoad) ||
        !host->comparison_pair(0xd32300,(uint64_t)&qpcNewCtor) ||
        !host->comparison_pair(0xd2e930,(uint64_t)&qpcNewDtor) ||
        !host->comparison_pair(0xd2dda0,(uint64_t)&qpcNewLookup) ||
        !host->comparison_pair(0xd2d8e0,(uint64_t)&qpcNewActive) ||
        !host->comparison_pair(0xd2dca0,(uint64_t)&qpcNewComplete) ||
        !host->comparison_pair(0xd2e700,(uint64_t)&qpcNewNames) ||
        !host->comparison_pair(0xdee380,(uint64_t)&qpcNewControllerInit)) {
        host->log("tlhybrid: lifecycle consumer candidate method binding is missing\n");
        return false;
    }
    autotest::Outcome a,b;
    host->log("tlhybrid: populated consumer bindings verified; original side\n");
    autotest::runChild(original,&c,a);
    host->log("tlhybrid: populated consumer original status=%d valid=%u issue=%u bytes=%lu target=%llx started=%u completed=%u; candidate side\n",a.childStatus,a.reportValid,a.capture.issue,(unsigned long)a.capture.length,(unsigned long long)a.capture.callTarget,a.capture.callStarted,a.capture.callCompleted);
    autotest::runChild(recovered,&c,b);
    host->log("tlhybrid: populated consumer candidate status=%d valid=%u issue=%u bytes=%lu target=%llx started=%u completed=%u\n",b.childStatus,b.reportValid,b.capture.issue,(unsigned long)b.capture.length,(unsigned long long)b.capture.callTarget,b.capture.callStarted,b.capture.callCompleted);
    bool same=good(a)&&good(b)&&a.capture.length==b.capture.length&&
              !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    same=same&&a.capture.callStarted&&b.capture.callStarted&&
        a.capture.callCompleted&&b.capture.callCompleted;
    if (!same) {
        host->log("tlhybrid: lifecycle consumer entry=%u count=%u gate=%u good=%u/%u status=%d/%d\n",
            c.entry,c.initialCount,c.detachController,good(a),good(b),a.childStatus,b.childStatus);
        for (unsigned s=0;s<2;++s) {
            const autotest::Capture& z=s?b.capture:a.capture;
            for (size_t i=0;i+4<=z.length;i+=4) {
                unsigned v; std::memcpy(&v,z.data+i,4);
                if ((v&0xffff0000u)==0xf1000000u)
                    host->log("tlhybrid: side %u oracle %u\n",s,v-0xf1000000u);
            }
        }
    }
    return same;
}
}
TL_TEST(quest_populated_original_parser_consumers) {
    using namespace quest_populated_consumers;
    for(unsigned reload=0;reload<2;++reload) for(unsigned count=1;count<=2;++count) for(unsigned detach=0;detach<2;++detach) {
        Case c={reload,count,detach}; if(!pair(host,c)) return 1;
    }
    host->log("tlhybrid: populated original Quest parser / accepted manager and controller / selected Quest A teardown; no B/C, GameClient/world or resource-file decoding credit\n");
    return 0;
}
