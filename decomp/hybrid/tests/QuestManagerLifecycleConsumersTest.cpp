// Genuine lifecycle -> definition loader -> accepted query/controller edges.
// The original Quest constructor, definition parser, NPC helper and deleting
// destructor all execute. Original CDataGroup::LoadFile consumes real cached
// CDataGroups built through original constructors/setters. Only filesystem
// enumeration/cache lookup, absent sound samples, and global environment
// access are controlled boundaries. This is not .adm decoding, GameClient,
// renderer/world, or EditorReloadAllAssets execution coverage.
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

#define QLC_PAIR(R,N,A,S) TL_ORIGINAL(R,qlcOld##N,A,S) extern "C" R qlcNew##N A __asm__(S);
QLC_PAIR(void,Ctor,(void*,void*),"_ZN13CQuestManagerC1EP16CResourceManager")
QLC_PAIR(void,Reload,(void*),"_ZN13CQuestManager12reloadQuestsEv")
QLC_PAIR(void,Dtor,(void*),"_ZN13CQuestManagerD1Ev")
QLC_PAIR(void*,Lookup,(void*,const std::wstring&),"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(bool,Active,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(char,Complete,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
QLC_PAIR(void,Names,(void*,TArrayList<std::wstring>&),"_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
QLC_PAIR(void,ControllerInit,(void*),"_ZN16CQuestController19initQuestControllerEv")
extern "C" void qlcNewLoad(void*) __asm__("_ZN13CQuestManager10loadQuestsEv");
TL_ORIGINAL(void,qlcConsole,(),"_Z12reloadQuestsv")
TL_ORIGINAL(void,qlcResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qlcResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qlcControllerCtor,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
TL_ORIGINAL(void,qlcControllerDtor,(void*),"_ZN16CQuestControllerD1Ev")
TL_ORIGINAL(void,qlcQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qlcQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qlcQuestNPCs,(void*,TArrayList<CDataGroup*>&),"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
TL_ORIGINAL(void,qlcGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qlcGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*,qlcAddWide,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(void*,qlcAddGuid,(void*,const std::wstring&,long long),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEx")
TL_FUNCTION(qlcMasterBoundary,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qlcFilesSingletonBoundary,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(qlcFilesBoundary,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(qlcCacheBoundary,"_ZN11CFileSystem12getDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qlcSoundBoundary,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qlcQuestCtorBoundary,"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_FUNCTION(qlcQuestDtorBoundary,"_ZN6CQuestD1Ev")
TL_FUNCTION(qlcNPCBoundary,"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
TL_FUNCTION(qlcReloadBoundary,"_ZN13CQuestManager12reloadQuestsEv")
TL_FUNCTION(qlcUIBoundary,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qlcSaveBoundary,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qlcGuidBoundary,"_ZN9UTILITIES16createUniqueGuidEv")

namespace quest_lifecycle_consumers {
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
struct Case { unsigned entry, initialCount, consoleGate; };
static const Case* current;
static autotest::Capture* capture;
static bool candidate, masterAvailable;
static unsigned errors, phase, filesCalls, cacheCalls, soundCalls;
static unsigned questCtors, questDtors, npcCalls, saveCalls;
static void *manager,*resource,*controller,*master,*files,*soundOwner,*soundInfo;
static CDataGroup* groups[3];
static detour::Set *ctorObservation,*dtorObservation,*npcObservation;
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
static void observedQuestCtor(void* self,void* r,void* m) {
    need(r==resource && m==manager && singleton()==manager,10);
    ++questCtors;
    ctorObservation->restore();
    qlcQuestCtor(self,r,m);
    TL_REDIRECT(*ctorObservation,qlcQuestCtorBoundary,&observedQuestCtor);
    need(!ctorObservation->failed(),11);
    need(at<void*>(self,0x1d0)==manager && at<void*>(self,0x1d8)==resource,12);
    need(at<void*>(self,0x1e0)!=0 && at<Wide>(self,0x50).empty(),13);
}
static void observedNPCs(void* self,TArrayList<CDataGroup*>& list) {
    need(at<void*>(self,0x1d0)==manager && at<void*>(self,0x1d8)==resource,14);
    need(at<int>(self,0x1a8)==0 && at<int>(self,0x1ac)==0,15);
    need(at<void*>(self,0x128)!=0 && at<void*>(self,0x1e0)!=0,16);
    need(at<unsigned>(&list,16)==100 && list.size()==0,17);
    capture->addText(at<Wide>(self,0x50));
    ++npcCalls;
    npcObservation->restore();
    qlcQuestNPCs(self,list);
    TL_REDIRECT(*npcObservation,qlcNPCBoundary,&observedNPCs);
    need(!npcObservation->failed() && list.size()==0,18);
}
static void observedQuestDtor(void* self) {
    // The original D0 invokes this original D1, which really destroys rewards,
    // requirements, listeners, containers, strings and base safe pointers.
    capture->addText(at<Wide>(self,0x50)); ++questDtors;
    dtorObservation->restore(); qlcQuestDtor(self);
    TL_REDIRECT(*dtorObservation,qlcQuestDtorBoundary,&observedQuestDtor);
    need(!dtorObservation->failed(),19);
}
static void* lookup(const Wide& n) {
    return candidate?qlcNewLookup(manager,n):qlcOldLookup(manager,n);
}
static bool active(const Wide& n) {
    return candidate?qlcNewActive(manager,n):qlcOldActive(manager,n);
}
static char complete(const Wide& n) {
    return candidate?qlcNewComplete(manager,n):qlcOldComplete(manager,n);
}
static void bindController(const Wide& name) {
    at<Wide>(controller,0xa8)=name;
    if (candidate) qlcNewControllerInit(controller);
    else qlcOldControllerInit(controller);
    void* q=lookup(name);
    need(q && at<void*>(controller,0x98)==q,20);
    need(at<bool>(controller,0xb0) && !at<bool>(controller,0xb1),21);
    need(at<unsigned>(q,0x1b8)==1,22);
    void* listener=at<void**>(q,0x1b0)[0];
    need(listener && at<void*>(listener,0)==controller,23);
}
static void checkLoaded(unsigned first,unsigned count) {
    TArrayList<Wide> actual(3);
    if (candidate) qlcNewNames(manager,actual); else qlcOldNames(manager,actual);
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
        0x151d408,0x151ab48,0x151c128};
    for (unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)
        new(reinterpret_cast<void*>(cells[i])) Wide();
    new(reinterpret_cast<void*>(0x14dd9c0)) std::string();
    const wchar_t* typeNames[]={L"",L"FIND",L"KILL NUM",L"KILL BOSS"};
    for (unsigned i=0;i<4;++i)
        new(reinterpret_cast<void*>(0x14fa000+i*8)) Wide(typeNames[i]);
    // The original loader requests DIALOG before reading this table, and this
    // minimal valid fixture has none. Initialize it anyway as the original
    // does so its untouched state is meaningful to adjacent real code.
    const wchar_t* dialogNames[]={L"ERROR",L"INTRO",L"RETURN",L"COMPLETE",L"PASSIVE",L"DETAILS"};
    for (unsigned i=0;i<6;++i)
        new(reinterpret_cast<void*>(0x14fa020+i*8)) Wide(dialogNames[i]);
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
    detour::Set environment,ctorWatch,dtorWatch,npcWatch,route;
    ctorObservation=&ctorWatch; dtorObservation=&dtorWatch; npcObservation=&npcWatch;
    TL_REDIRECT(environment,qlcMasterBoundary,&masterBoundary);
    TL_REDIRECT(environment,qlcFilesSingletonBoundary,&filesBoundary);
    TL_REDIRECT(environment,qlcFilesBoundary,&fileList);
    TL_REDIRECT(environment,qlcCacheBoundary,&cachedGroup);
    TL_REDIRECT(environment,qlcSoundBoundary,&absentSound);
    TL_REDIRECT(environment,qlcUIBoundary,&noUI);
    // Cached fixtures have explicit GUIDs. Never permit original resource writes.
    saveCalls=0;
    TL_REDIRECT(environment,qlcSaveBoundary,&rejectSave);
    TL_REDIRECT(environment,qlcGuidBoundary,&stableGuid);
    TL_REDIRECT(ctorWatch,qlcQuestCtorBoundary,&observedQuestCtor);
    TL_REDIRECT(dtorWatch,qlcQuestDtorBoundary,&observedQuestDtor);
    TL_REDIRECT(npcWatch,qlcNPCBoundary,&observedNPCs);
    if (environment.failed()||ctorWatch.failed()||dtorWatch.failed()||npcWatch.failed()) {
        out.issue=autotest::Capture::InvalidReport; return;
    }
    qlcResourceCtor(resource,0);
    need(!at<void*>(resource,0x28) && !at<unsigned>(resource,0x30),34);
    qlcControllerCtor(controller,resource);
    const wchar_t* mixedNames[]={L"First",L"Second",L"Third"};
    for (unsigned i=0;i<3;++i) {
        groups[i]=static_cast<CDataGroup*>(storage(0x60));
        qlcGroupCtor(groups[i],Wide(L"QUEST"),0,20,10,
                     reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));
        qlcAddWide(groups[i],Wide(L"NAME"),Wide(mixedNames[i]),false);
        qlcAddWide(groups[i],Wide(L"DISPLAYNAME"),Wide(L"Lifecycle \u0416\u732b"),false);
        qlcAddGuid(groups[i],Wide(L"QUEST_GUID"),0x12131400+i);
    }
    masterAvailable=true;
    typedef void(*Ctor)(void*,void*); Ctor ctor=candidate?&qlcNewCtor:&qlcOldCtor;
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
        if (current->entry==1) {
            typedef void(*Reload)(void*); Reload reload=candidate?&qlcNewReload:&qlcOldReload;
            if (!autotest::beginInvocation(out,reload)) return;
            reload(manager); out.callCompleted=1;
        } else {
            // Genuine original Console wrapper. Its two guards only inspect
            // these fields; +58 is a presence token and is never dereferenced.
            void* editor=storage(0x60); std::memset(editor,0,0x60);
            at<bool>(editor,0x49)=current->consoleGate==1;
            at<void*>(editor,0x58)=current->consoleGate==2?0:resource;
            void*& slot=*reinterpret_cast<void**>(0x145c6e0);
            void* savedEditor=slot; slot=editor;
            if (candidate)
                route.redirect(qlcReloadBoundary_original,qlcReloadBoundary_original,&qlcNewReload);
            if (route.failed()) { out.issue=autotest::Capture::InvalidReport; return; }
            if (!autotest::beginInvocation(out,&qlcConsole)) return;
            qlcConsole(); out.callCompleted=1; slot=savedEditor; route.restore();
        }
        if (current->entry==1 || !current->consoleGate) {
            need(filesCalls==2 && questDtors==current->initialCount,39);
            need(!at<void*>(controller,0x98),40); // Original CRunicCore invalidation.
            need(!lookup(L"FIRST") && !active(L"FIRST") && !complete(L"FIRST"),41);
            checkLoaded(1,2); bindController(Wide(L"SECOND"));
        } else {
            need(filesCalls==1 && !questDtors && at<void*>(controller,0x98)==first,42);
            need(active(L"FIRST") && complete(L"FIRST"),43);
        }
        need(at<void*>(manager,0x30)==sound && at<void*>(manager,0x38)==resource,44);
        need(singleton()==manager && soundCalls==2,45);
    }
    // Leave the actual controller bound while the actual manager destroys its
    // loaded Quest: this exercises cross-object listener and safe-pointer life.
    if (candidate) qlcNewDtor(manager); else qlcOldDtor(manager);
    need(!singleton() && !at<void*>(controller,0x98),46);
    need(questDtors==questCtors && npcCalls==questCtors && cacheCalls==questCtors,47);
    qlcControllerDtor(controller); qlcResourceDtor(resource); singleton()=savedManager;
    for (unsigned i=0;i<3;++i) qlcGroupDtor(groups[i]);
    reinterpret_cast<TRepository<Wide>*>(0x14dd9e0)->~TRepository<Wide>();
    number(filesCalls); number(cacheCalls); number(soundCalls);
    number(questCtors); number(questDtors); number(npcCalls);
    need(saveCalls==0,51); number(saveCalls);
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
static bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case& c) {
    // Refuse an accidentally imported original at any credited candidate edge.
    // Manager-to-loader relocation binding is additionally checked by the
    // production object/link closure; no detour manufactures that edge here.
    if (!host->comparison_pair(0xd31410,(uint64_t)&qlcNewLoad) ||
        !host->comparison_pair(0xd32300,(uint64_t)&qlcNewCtor) ||
        !host->comparison_pair(0xd2e930,(uint64_t)&qlcNewDtor) ||
        !host->comparison_pair(0xd2dda0,(uint64_t)&qlcNewLookup) ||
        !host->comparison_pair(0xd2d8e0,(uint64_t)&qlcNewActive) ||
        !host->comparison_pair(0xd2dca0,(uint64_t)&qlcNewComplete) ||
        !host->comparison_pair(0xd2e700,(uint64_t)&qlcNewNames) ||
        !host->comparison_pair(0xdee380,(uint64_t)&qlcNewControllerInit)) {
        host->log(" lifecycle consumer candidate method binding is missing\n");
        return false;
    }
    autotest::Outcome a,b;
    autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
    bool same=good(a)&&good(b)&&a.capture.length==b.capture.length&&
              !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    if (c.entry==2) {
        same=same&&a.capture.callStarted&&b.capture.callStarted&&
            a.capture.callCompleted&&b.capture.callCompleted&&
            a.capture.callTarget==0x724580&&b.capture.callTarget==0x724580;
    } else if (cv.observe(host,a,b)) same=false;
    if (!same) {
        host->log(" lifecycle consumer entry=%u count=%u gate=%u good=%u/%u status=%d/%d\n",
            c.entry,c.initialCount,c.consoleGate,good(a),good(b),a.childStatus,b.childStatus);
        for (unsigned s=0;s<2;++s) {
            const autotest::Capture& z=s?b.capture:a.capture;
            for (size_t i=0;i+4<=z.length;i+=4) {
                unsigned v; std::memcpy(&v,z.data+i,4);
                if ((v&0xffff0000u)==0xf1000000u)
                    host->log(" side %u oracle %u\n",s,v-0xf1000000u);
            }
        }
    }
    return same;
}
}
TL_TEST(questmanager_constructor_definition_consumers) {
    using namespace quest_lifecycle_consumers;
    autotest::Coverage cv("questmanager_constructor_definition_consumers",0xd32300);
    for (unsigned n=1;n<=2;++n) { Case c={0,n,0}; if (!pair(host,cv,c)) {cv.report(host);return 1;} }
    cv.report(host); return cv.completed!=2||cv.different||cv.missing;
}
TL_TEST(questmanager_reload_definition_consumers) {
    using namespace quest_lifecycle_consumers;
    autotest::Coverage cv("questmanager_reload_definition_consumers",0xd321f0);
    for (unsigned n=1;n<=2;++n) { Case c={1,n,0}; if (!pair(host,cv,c)) {cv.report(host);return 1;} }
    cv.report(host); return cv.completed!=2||cv.different||cv.missing;
}
TL_TEST(questmanager_console_reload_consumer) {
    using namespace quest_lifecycle_consumers;
    if (!host->comparison_pair(0xd321f0,(uint64_t)&qlcNewReload)) return 1;
    autotest::Coverage cv("Console consumer only; no direct method credit",0xd321f0);
    for (unsigned n=1;n<=2;++n) for (unsigned g=0;g<3;++g) {
        Case c={2,n,g}; if (!pair(host,cv,c)) return 1;
    }
    host->log(" original Console guards/reload, original Quest cached-definition parser/lifetime, accepted query/controller binding; .adm decoding, GameClient/world and EditorReloadAllAssets not executed\n");
    return 0;
}
