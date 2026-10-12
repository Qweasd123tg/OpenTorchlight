// Independent original-ELF lifecycle oracle. C++98 / GCC 4.4 COW ABI.
// Manager bodies, list operations and all map helpers remain real. Sound and
// Quest construction/destruction are forwarded to the original implementations;
// master lookup, sample registration, definition loading and injected failures
// are explicit dependency boundaries. Definition parsing/binding is covered by
// the separate consumer fixture, not by this loadQuests boundary double.
//
// Original LSDA, decoded directly from .gcc_except_table:
// C1: 11df129; sound allocation/master -> d324e7, sound C1 -> d325e7,
// string constructors -> d325e2/d32592, lookups -> d325d5/d32582,
// addSample/loadQuests -> d324e7. D1: 11dee2e; [d2e9bf,d2ead1)
// (quest/sound virtual destruction) -> d2eb5a. Reload and D0 have no LSDA.
// Never throw from delete[]/deallocation or through an omitted LSDA region.
#include <cstddef>
#include <cstring>
#include <cwchar>
#include <map>
#include <new>
#include <string>
#include "QuestManager.h"
#include "Quest.h"
#include "AutoTest.h"
#include "Detour.h"

#define QML_PAIR(N,A,S) TL_ORIGINAL(void,qmlOld##N,A,S) extern "C" void qmlNew##N A __asm__(S);
QML_PAIR(C1,(void*,void*),"_ZN13CQuestManagerC1EP16CResourceManager")
QML_PAIR(C2,(void*,void*),"_ZN13CQuestManagerC2EP16CResourceManager")
QML_PAIR(Reload,(void*),"_ZN13CQuestManager12reloadQuestsEv")
QML_PAIR(D1,(void*),"_ZN13CQuestManagerD1Ev")
QML_PAIR(D2,(void*),"_ZN13CQuestManagerD2Ev")
QML_PAIR(D0,(void*),"_ZN13CQuestManagerD0Ev")
#undef QML_PAIR
TL_ORIGINAL(void,qmlQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qmlQuestD1,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qmlSoundD1,(void*),"_ZN10CSoundBankD1Ev")
TL_ORIGINAL(unsigned,qmlAddSafe,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qmlMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qmlSoundCtor,"_ZN10CSoundBankC1ER13CSoundManagerb")
TL_FUNCTION(qmlLookup,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qmlSample,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(qmlLoad,"_ZN13CQuestManager10loadQuestsEv")
TL_FUNCTION(qmlQuestDelete,"_ZN6CQuestD0Ev")
TL_FUNCTION(qmlSoundDelete,"_ZN10CSoundBankD0Ev")
TL_FUNCTION(qmlCoreDelete,"_ZN10CRunicCoreD1Ev")
extern "C" char qmlAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qmlFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qmlScalarDelete[] __asm__("_ZdlPv");
extern "C" char qmlArrayDelete[] __asm__("_ZdaPv");
extern "C" char qmlWideCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");

namespace quest_manager_lifetime {
typedef std::wstring Wide;
typedef TArrayList<CQuest*> List;
typedef std::map<Wide,CQuest*> Names;
typedef std::map<Wide,bool> Completion;
typedef std::map<CDataGroup*,List*> NPCs;
typedef char ABI[sizeof(CQuestManager)==0xd0 && sizeof(Wide)==8 &&
                 sizeof(List)==24 && sizeof(Names)==48 &&
                 sizeof(Completion)==48 && sizeof(NPCs)==48 ? 1 : -1];
template<class T> T& at(void* p,unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);
}
struct Stop { unsigned site; explicit Stop(unsigned s):site(s){} };
// kind: 0 constructor, 1 reload, 2 destructor. alias: C1/C2 or D1/D2/D0.
// Constructor shape is existing-singleton; sample is the two-bit sample mask.
// Teardown shape: empty, null-only, mixed+active, mixed+empty-active.
// fault C1: 1 first master, 2 allocation, 3 sound C1, 4 second master,
// 5 first string, 6 first lookup, 7 first add, 8 second string,
// 9 second lookup, 10 second add, 11 load after observable partial effects.
// fault teardown: 21/22/23 first/second/third Quest D0, 24 sound D0,
// 25 reload load after clearing. Every injected fault precedes dependency work.
struct Case { unsigned kind,alias,shape,sample,singleton,text,fault; };
struct Node { void* p; unsigned family,id; bool freed; };
struct Weak { void* p; unsigned index,padding; };
static const Case* cs;
static const tlhybrid_host* hostContext;
static autotest::Capture* cap;
static void *owner,*resource,*player,*foreign,*master[2],*soundManager;
static void *info[2],*data[2],*bank,*activeBuffer,*initialSingleton;
static CQuest* quests[3];
static List* buckets[2];
static void* bucketBuffer[2];
static Wide *keys[4],*lookupKeeper[2];
static Wide* mapKeeper[2][4];
static const wchar_t* mapRep[2][4];
static int sourceRefs[4];
static Weak* witness;
static Node nodes[10];
static unsigned errors,nodeCount,nodeFrees[4],bucketFrees[2],bucketBufferFrees[2];
static unsigned events[128],eventCount,masterCalls,allocCalls,soundCtorCalls;
static unsigned stringCalls,lookupCalls,sampleCalls,loadCalls,baseCalls;
static unsigned questCalls,soundCalls,ownerFrees,scalarOwnerFrees,bankFrees;
static unsigned faultHits,activeFrees;
static bool tracking,awaitingSound,bankConstructed,bankDeleted,questDeleted[3];
static bool seeded,weakRegistered;
static detour::Set *allocPatch,*freePatch,*scalarPatch,*arrayPatch,*widePatch;
static detour::Set *soundCtorPatch,*questPatch,*soundPatch,*corePatch;

static void number(unsigned value) { cap->add(&value,sizeof(value)); }
static void need(bool value,unsigned site) {
    if(!value) { ++errors; number(0xf2000000u+site); }
}
static void event(unsigned value) {
    need(eventCount<128,1);
    if(eventCount<128) events[eventCount++]=value;
    number(value);
}
static void fault(unsigned site) {
    if(tracking && cs->fault==site) { ++faultHits; throw Stop(site); }
}
static void* raw(unsigned size,unsigned poison=0xa5) {
    void* p=autotest::allocate(size);
    if(!p) _exit(71);
    std::memset(p,poison,size);
    return p;
}
static void*& singleton() { return *reinterpret_cast<void**>(0x14fc6e0); }
static Names& names() { return at<Names>(owner,0x40); }
static Completion& completion() { return at<Completion>(owner,0x70); }
static NPCs& npcs() { return at<NPCs>(owner,0xa0); }
static List& active() { return at<List>(owner,0x18); }
static int cowRefs(const Wide& s) {
    return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);
}
static bool mapped(uintptr_t oldAddress,uintptr_t replacement) {
    return oldAddress==replacement || (hostContext->comparison_pair &&
           hostContext->comparison_pair(oldAddress,replacement));
}
static void managerVtable(bool candidate) {
    uintptr_t* actual=at<uintptr_t*>(owner,0);
    const uintptr_t* original=reinterpret_cast<const uintptr_t*>(0xff7790);
    need(actual && reinterpret_cast<std::ptrdiff_t*>(actual)[-2]==0,2);
    if(!actual)return;
    for(unsigned i=0;i<2;++i)
        need(candidate?mapped(original[i],actual[i]):actual[i]==original[i],3+i);
}
static void emptyState() {
    need(!at<void*>(owner,0x10) && at<void*>(owner,0x38)==resource,5);
    need(!at<void*>(owner,0x18) && !at<unsigned>(owner,0x20) &&
         !at<unsigned>(owner,0x24) && at<unsigned>(owner,0x28)==10,6);
    need(names().empty() && completion().empty() && npcs().empty(),7);
    const unsigned offsets[]={0x40,0x70,0xa0};
    for(unsigned i=0;i<3;++i) {
        unsigned o=offsets[i];
        need(at<unsigned>(owner,o+8)==0 && !at<void*>(owner,o+16),8+i);
        need(at<void*>(owner,o+24)==static_cast<char*>(owner)+o+8 &&
             at<void*>(owner,o+32)==static_cast<char*>(owner)+o+8 &&
             !at<size_t>(owner,o+40),11+i);
    }
}
static void registerWeak() {
    if(weakRegistered)return;
    witness->p=owner;
    witness->index=qmlAddSafe(owner,witness);
    weakRegistered=true;
    need(witness->index==0,14);
}
static void rememberNode(void* p,unsigned family,unsigned id) {
    need(nodeCount<10,15);
    if(nodeCount<10) {
        nodes[nodeCount].p=p; nodes[nodeCount].family=family;
        nodes[nodeCount].id=id; nodes[nodeCount++].freed=false;
    }
}
static void checkKeys(bool mapsAlive,unsigned site) {
    for(unsigned i=0;i<4;++i)if(keys[i]) {
        // operator[] in the long/embedded-NUL input intentionally produces a
        // leaked source rep (-1). Copies into map keys then own different reps.
        // Ordinary inputs share one rep between source and both maps. Count
        // known live owners by saved rep identity, never by a fixed refcount.
        const wchar_t* source=keys[i]->c_str();
        if(sourceRefs[i]==-1) {
            need(cowRefs(*keys[i])==-1,site+i);
            need(mapRep[0][i]!=source && mapRep[1][i]!=source,site+4+i);
        } else {
            unsigned owners=1;
            for(unsigned m=0;m<2;++m) {
                owners+=mapKeeper[m][i]->c_str()==source;
                if(mapsAlive)owners+=mapRep[m][i]==source;
            }
            need(cowRefs(*keys[i])==static_cast<int>(owners-1),site+i);
        }
        // Each real map key has an independent retained witness. A missed key
        // destructor is detected even when a leaked source forced a deep copy.
        for(unsigned m=0;m<2;++m) {
            const wchar_t* rep=mapKeeper[m][i]->c_str();
            need(rep==mapRep[m][i],site+8+m*4+i);
            unsigned owners=source==rep;
            for(unsigned j=0;j<2;++j) {
                owners+=mapKeeper[j][i]->c_str()==rep;
                if(mapsAlive)owners+=mapRep[j][i]==rep;
            }
            need(owners && cowRefs(*mapKeeper[m][i])==static_cast<int>(owners-1),site+16+m*4+i);
        }
    }
}
static Wide key(unsigned i) {
    // Fixed first characters make sorted order independent of suffix encoding.
    wchar_t lead=wchar_t(L'A'+i);
    Wide result(1,lead);
    if(cs->text==0)result+=L" quest lifecycle key";
    else if(cs->text==1) {
        const wchar_t suffix[]={L'\u0416',0,L'\u732b',L'\u03a9'};
        result.append(suffix,4);
    } else { result.append(180+i*17,L'q'); result[17]=0; }
    return result;
}
static void seed(unsigned shape) {
    seeded=true;
    unsigned count=shape==0?0:shape==1?1:4;
    for(unsigned i=0;i<count;++i) {
        keys[i]=new(raw(sizeof(Wide)))Wide(key(i));
        sourceRefs[i]=cowRefs(*keys[i]);
        need(sourceRefs[i]==0 || sourceRefs[i]==-1,150+i);
        CQuest* q=0;
        if(shape>=2 && i!=1) {
            unsigned index=i==0?0:i-1;
            quests[index]=static_cast<CQuest*>(raw(0x218));
            qmlQuestCtor(quests[index],0,0);
            q=quests[index];
        }
        Names::iterator n=names().insert(Names::value_type(*keys[i],q)).first;
        Completion::iterator c=completion().insert(Completion::value_type(*keys[i],i%2!=0)).first;
        rememberNode(n._M_node,1,i); rememberNode(c._M_node,3,i);
        mapRep[0][i]=n->first.c_str(); mapRep[1][i]=c->first.c_str();
        mapKeeper[0][i]=new(raw(sizeof(Wide)))Wide(n->first);
        mapKeeper[1][i]=new(raw(sizeof(Wide)))Wide(c->first);
    }
    if(shape>=2) {
        for(unsigned i=0;i<2;++i) {
            buckets[i]=new List(2);
            buckets[i]->add(quests[i]); buckets[i]->add(quests[2]);
            bucketBuffer[i]=at<void*>(buckets[i],0);
            CDataGroup* npc=reinterpret_cast<CDataGroup*>(data[i]);
            NPCs::iterator n=npcs().insert(NPCs::value_type(npc,buckets[i])).first;
            rememberNode(n._M_node,2,i);
        }
    }
    if(shape==1)active().add(0);
    if(shape==2) {
        active().add(quests[2]); active().add(quests[0]); active().add(quests[2]);
    }
    activeBuffer=at<void*>(owner,0x18);
    checkKeys(true,160);
}
static void checkBuckets() {
    for(unsigned i=0;i<2;++i)if(buckets[i]) {
        need(!bucketFrees[i] && !bucketBufferFrees[i],16+i);
        // Skip dereferencing a lifetime that an incorrect candidate destroyed.
        if(bucketFrees[i] || bucketBufferFrees[i])continue;
        need(at<void*>(buckets[i],0)==bucketBuffer[i] && buckets[i]->size()==2 &&
             at<unsigned>(buckets[i],12)==2 && at<unsigned>(buckets[i],16)==2,18+i);
        need((*buckets[i])[0]==quests[i] && (*buckets[i])[1]==quests[2],20+i);
    }
}
static void* allocate(size_t size,const char* file,int line,const char* function) {
    bool sound=tracking && cs->kind==0 && awaitingSound && size==0xd0;
    if(sound) {
        ++allocCalls; event(20); need(singleton()==owner,22);
        need(!file && !line && !function,23); fault(2);
    }
    allocPatch->restore();
    void* p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qmlAlloc)(size,file,line,function);
    allocPatch->redirect(qmlAlloc,qmlAlloc,&allocate); need(!allocPatch->failed(),24);
    if(sound)bank=p;
    return p;
}
static void release(void* p) {
    if(p==owner) {
        if(tracking) { ++ownerFrees; event(130); need(baseCalls==1,25);
            need(!witness->p && witness->index==~0u,26); }
        return; // Explicit allocator observer owns the arena-backed owner.
    }
    for(unsigned i=0;i<3;++i)if(p==quests[i] && p)return;
    for(unsigned i=0;i<2;++i)if(p==buckets[i] && p && tracking) {
        ++bucketFrees[i]; event(140+i); return;
    }
    if(p==bank && p && tracking) { ++bankFrees; event(135); }
    freePatch->restore(); reinterpret_cast<void(*)(void*)>(qmlFree)(p);
    freePatch->redirect(qmlFree,qmlFree,&release); need(!freePatch->failed(),27);
}
static void scalarRelease(void* p) {
    if(p==owner) { if(tracking){++scalarOwnerFrees;event(139);need(false,28);} return; }
    if(tracking)for(unsigned i=0;i<nodeCount;++i)if(p==nodes[i].p) {
        need(!nodes[i].freed,29); nodes[i].freed=true;
        unsigned f=nodes[i].family; ++nodeFrees[f]; event(100+f); number(nodes[i].id);
        // clear() resets the preceding container's header before the next
        // family is erased. Do not traverse a currently erasing tree.
        bool bodyOrder=cs->kind==1 || (cs->kind==2 && cs->fault<21);
        if(bodyOrder && f==2)need(names().empty(),30);
        if(bodyOrder && f==3)need(names().empty() && npcs().empty(),31);
        break;
    }
    scalarPatch->restore(); reinterpret_cast<void(*)(void*)>(qmlScalarDelete)(p);
    scalarPatch->redirect(qmlScalarDelete,qmlScalarDelete,&scalarRelease);
    need(!scalarPatch->failed(),32);
}
static void arrayRelease(void* p) {
    if(tracking && p==activeBuffer && p) {
        ++activeFrees; event(80);
        if(cs->kind!=0)need(!at<unsigned>(owner,0x20) && !at<unsigned>(owner,0x24),33);
        need(at<void*>(owner,0x18)==p,34); // pointer is nulled after delete[] returns
    }
    for(unsigned i=0;i<2;++i)if(tracking && p && p==bucketBuffer[i]) {
        ++bucketBufferFrees[i]; event(145+i); return;
    }
    arrayPatch->restore(); reinterpret_cast<void(*)(void*)>(qmlArrayDelete)(p);
    arrayPatch->redirect(qmlArrayDelete,qmlArrayDelete,&arrayRelease);
    need(!arrayPatch->failed(),35);
}
static void coreDelete(void* self) {
    bool observed=tracking && self==owner;
    if(observed) {
        ++baseCalls; event(120);
        need(!at<void*>(owner,0x18),36);
        for(unsigned i=0;i<nodeCount;++i)need(nodes[i].freed,37);
        checkKeys(false,190);
        need(witness->p==owner && witness->index==0,42);
        if(cs->kind==0)need(singleton()==owner,43);
        else need(singleton()==(cs->fault?initialSingleton:0),44);
    }
    corePatch->restore();
    reinterpret_cast<void(*)(void*)>(qmlCoreDelete_original)(self);
    TL_REDIRECT(*corePatch,qmlCoreDelete,&coreDelete); need(!corePatch->failed(),45);
    if(observed)need(!witness->p && witness->index==~0u && !at<void*>(owner,8),46);
}
static void* masterLookup() {
    ++masterCalls; event(9+masterCalls);
    need(masterCalls<=2 && singleton()==owner,47); emptyState(); registerWeak();
    fault(masterCalls==1?1:4);
    if(masterCalls==1)awaitingSound=true;
    return master[masterCalls==1?0:1];
}
static void soundConstructor(void* self,void* sound,bool option) {
    if(tracking) {
        ++soundCtorCalls; event(30); awaitingSound=false;
        need(self==bank && sound==soundManager && !option && singleton()==owner,48);
        uintptr_t poison=cs->text&1?0x5a5a5a5a5a5a5a5aULL:0xa5a5a5a5a5a5a5a5ULL;
        need(at<uintptr_t>(owner,0x30)==poison,49); fault(3);
    }
    soundCtorPatch->restore();
    reinterpret_cast<void(*)(void*,void*,bool)>(qmlSoundCtor_original)(self,sound,option);
    TL_REDIRECT(*soundCtorPatch,qmlSoundCtor,&soundConstructor); need(!soundCtorPatch->failed(),50);
    bankConstructed=true;
}
static void wideConstructor(Wide* self,const wchar_t* text,const std::allocator<wchar_t>& allocator) {
    bool sample=tracking && cs->kind==0 &&
        (!std::wcscmp(text,L"QUESTRECEIVED") || !std::wcscmp(text,L"QUESTCOMPLETED"));
    if(sample) {
        ++stringCalls; event(39+stringCalls);
        need(stringCalls<=2 && singleton()==owner && at<void*>(owner,0x30)==bank,51);
        fault(stringCalls==1?5:8);
    }
    widePatch->restore();
    reinterpret_cast<void(*)(Wide*,const wchar_t*,const std::allocator<wchar_t>&)>(qmlWideCtor)(self,text,allocator);
    widePatch->redirect(qmlWideCtor,qmlWideCtor,&wideConstructor); need(!widePatch->failed(),52);
}
static void* sampleLookup(void* self,const Wide& name) {
    unsigned i=lookupCalls++; event(50+i);
    need(i<2 && self==info[0] && singleton()==owner,53);
    need(name==(i==0?L"QUESTRECEIVED":L"QUESTCOMPLETED"),54);
    cap->addText(name);
    if(i<2)lookupKeeper[i]=new(raw(sizeof(Wide)))Wide(name);
    // Both names use the information pointer cached after the SECOND master
    // lookup. A fresh master/member load for sample two must be observable.
    at<void*>(master[1],0x100)=info[1];
    fault(i==0?6:9);
    return i<2 && (cs->sample&(1u<<i))?data[i]:0;
}
static void addSample(void* self,int id,long long guid) {
    unsigned i=id==31?0:1; ++sampleCalls; event(60+i);
    need(id==31 || id==32,55);
    need(self==bank && singleton()==owner && (cs->sample&(1u<<i)),56);
    need(guid==at<long long>(data[i],0x20),57);
    need(lookupKeeper[i] && cowRefs(*lookupKeeper[i])==0,58);
    fault(i==0?7:10);
    // Explicit sample boundary: no audio backend or sample resource parsing.
}
static void loadBoundary(void* self) {
    ++loadCalls; event(70); need(self==owner,59);
    need(names().empty() && completion().empty() && npcs().empty(),60);
    need(!at<void*>(owner,0x18) && !at<unsigned>(owner,0x20) &&
         !at<unsigned>(owner,0x24) && at<unsigned>(owner,0x28)==10,61);
    if(cs->kind==0) {
        need(singleton()==owner && at<void*>(owner,0x30)==bank,62);
        if(cs->fault==11) { seed(2); fault(11); }
    } else {
        need(singleton()==initialSingleton && at<void*>(owner,0x30)==bank &&
             at<void*>(owner,0x10)==player && at<void*>(owner,0x38)==resource,63);
        checkBuckets(); fault(25);
    }
}
static unsigned questIndex(void* self) {
    for(unsigned i=0;i<3;++i)if(self==quests[i])return i;
    need(false,64); return 0;
}
static void questDelete(void* self) {
    unsigned i=questIndex(self);
    if(tracking) {
        ++questCalls; event(90+i);
        need(!questDeleted[i] && questCalls==i+1,65);
        need(!at<void*>(owner,0x18) && !at<unsigned>(owner,0x20) && !at<unsigned>(owner,0x24),66);
        unsigned k=i==0?0:i+1;
        need(names().find(*keys[k])->second==self,67);
        for(unsigned j=0;j<i;++j) {
            unsigned p=j==0?0:j+1;
            need(!names().find(*keys[p])->second,68);
        }
        need(nodeFrees[1]==0 && nodeFrees[2]==0 && nodeFrees[3]==0,69);
        need(singleton()==initialSingleton && at<void*>(owner,0x30)==bank,70);
        fault(21+i);
    }
    questPatch->restore();
    reinterpret_cast<void(*)(void*)>(qmlQuestDelete_original)(self);
    TL_REDIRECT(*questPatch,qmlQuestDelete,&questDelete); need(!questPatch->failed(),71);
    questDeleted[i]=true;
}
static void soundDelete(void* self) {
    if(tracking) {
        ++soundCalls; event(110);
        need(self==bank && at<void*>(owner,0x30)==bank && !bankDeleted,72);
        need(names().empty() && completion().empty() && npcs().empty(),73);
        need(singleton()==initialSingleton,74); checkBuckets(); fault(24);
    }
    soundPatch->restore();
    reinterpret_cast<void(*)(void*)>(qmlSoundDelete_original)(self);
    TL_REDIRECT(*soundPatch,qmlSoundDelete,&soundDelete); need(!soundPatch->failed(),75);
    bankDeleted=true;
}

static void initialize() {
    errors=nodeCount=eventCount=masterCalls=allocCalls=soundCtorCalls=0;
    stringCalls=lookupCalls=sampleCalls=loadCalls=baseCalls=questCalls=soundCalls=0;
    ownerFrees=scalarOwnerFrees=bankFrees=faultHits=activeFrees=0;
    tracking=awaitingSound=bankConstructed=bankDeleted=seeded=weakRegistered=false;
    std::memset(nodes,0,sizeof(nodes)); std::memset(nodeFrees,0,sizeof(nodeFrees));
    std::memset(quests,0,sizeof(quests)); std::memset(questDeleted,0,sizeof(questDeleted));
    std::memset(buckets,0,sizeof(buckets)); std::memset(bucketBuffer,0,sizeof(bucketBuffer));
    std::memset(bucketFrees,0,sizeof(bucketFrees)); std::memset(bucketBufferFrees,0,sizeof(bucketBufferFrees));
    std::memset(keys,0,sizeof(keys)); std::memset(lookupKeeper,0,sizeof(lookupKeeper));
    std::memset(mapKeeper,0,sizeof(mapKeeper)); std::memset(mapRep,0,sizeof(mapRep));
    std::memset(sourceRefs,0,sizeof(sourceRefs));
    autotest::g_arenaUsed=0; bank=activeBuffer=0;
    owner=raw(0xd0,cs->text&1?0x5a:0xa5); resource=raw(16); player=raw(16); foreign=raw(16);
    witness=new(raw(sizeof(Weak)))Weak; witness->p=0; witness->index=~0u;
    master[0]=raw(0x108); master[1]=raw(0x108); soundManager=raw(16);
    info[0]=raw(16); info[1]=raw(16); data[0]=raw(0x28); data[1]=raw(0x28);
    at<void*>(master[0],0x98)=soundManager;
    at<void*>(master[0],0x100)=info[1];
    at<void*>(master[1],0x98)=foreign;
    at<void*>(master[1],0x100)=info[0];
    at<long long>(data[0],0x20)=0x123456789abcdef0LL;
    at<long long>(data[1],0x20)=-0x1234567890abcdeLL;
    // The original Quest constructor copies this original TU empty string;
    // the self-test runs before the game's static initialization.
    new(reinterpret_cast<void*>(0x14f9fe8))Wide();
}
static void sequenceOracle() {
    unsigned want[80],count=0;
    if(cs->kind==0 && !cs->shape) {
        // The site list is independent of the callback implementation. A throw
        // occurs after its boundary event but before that dependency's effects.
        const unsigned trace[]={10,20,30,11,40,50,60,41,51,61,70};
        for(unsigned i=0;i<11;++i) {
            if((i==6 && !(cs->sample&1)) || (i==9 && !(cs->sample&2)))continue;
            want[count++]=trace[i];
            if(cs->fault==i+1)break;
        }
        if(cs->fault==3)want[count++]=135;
        if(cs->fault==11) {
            for(unsigned i=0;i<2;++i)want[count++]=102;
            for(unsigned i=0;i<4;++i)want[count++]=103;
            for(unsigned i=0;i<4;++i)want[count++]=101;
            want[count++]=80;
        }
        if(cs->fault)want[count++]=120;
    } else if(cs->kind!=0) {
        unsigned namesCount=cs->shape==0?0:cs->shape==1?1:4;
        unsigned npcCount=cs->shape>=2?2:0;
        if(activeBuffer)want[count++]=80;
        bool questFault=cs->fault>=21 && cs->fault<=23;
        if(cs->shape>=2)for(unsigned i=0;i<3;++i) {
            want[count++]=90+i;
            if(cs->fault==21+i)break;
        }
        if(!questFault) {
            for(unsigned i=0;i<namesCount;++i)want[count++]=101;
            for(unsigned i=0;i<npcCount;++i)want[count++]=102;
            for(unsigned i=0;i<namesCount;++i)want[count++]=103;
            if(cs->kind==1)want[count++]=70;
            else if(cs->sample) {
                want[count++]=110;
                if(cs->fault!=24)want[count++]=135;
            }
        } else if(cs->kind==2) {
            // Member destruction is reverse declaration order on unwind;
            // the body clear order is name, NPC, completion instead.
            for(unsigned i=0;i<npcCount;++i)want[count++]=102;
            for(unsigned i=0;i<namesCount;++i)want[count++]=103;
            for(unsigned i=0;i<namesCount;++i)want[count++]=101;
        }
        if(cs->kind==2) {
            want[count++]=120;
            if(!cs->fault && cs->alias==2)want[count++]=130;
        }
    }
    need(eventCount==count,118);
    for(unsigned i=0;i<count && i<eventCount;++i)need(events[i]==want[i],119+i);
}
static void finishChecks(bool caught,bool candidate) {
    need(caught==(cs->fault!=0) && faultHits==(cs->fault?1u:0u),76);
    need(!scalarOwnerFrees,77); checkBuckets();
    if(cs->kind==0) {
        need(!ownerFrees && !soundCalls && !questCalls,78);
        need(baseCalls==(caught?1u:0u),79);
        need(singleton()==(cs->shape?foreign:owner),80);
        uintptr_t poison=cs->text&1?0x5a5a5a5a5a5a5a5aULL:0xa5a5a5a5a5a5a5a5ULL;
        if(cs->shape || (caught && cs->fault<=3))need(at<uintptr_t>(owner,0x30)==poison,81);
        else need(at<void*>(owner,0x30)==bank,82);
        if(cs->shape)need(!masterCalls && !allocCalls && !soundCtorCalls && !lookupCalls && !loadCalls,83);
        if(!caught) { emptyState(); managerVtable(candidate); }
        need(bankFrees==(cs->fault==3?1u:0u),84);
        if(!cs->shape && !caught)need(masterCalls==2 && allocCalls==1 && soundCtorCalls==1 &&
            stringCalls==2 && lookupCalls==2 && sampleCalls==((cs->sample&1)!=0)+((cs->sample&2)!=0) && loadCalls==1,85);
        for(unsigned i=0;i<2;++i)if(lookupKeeper[i])need(cowRefs(*lookupKeeper[i])==0,86+i);
        if(caught)need(!witness->p && witness->index==~0u,88);
    } else {
        need(!at<void*>(owner,0x18) && !at<unsigned>(owner,0x20) &&
             !at<unsigned>(owner,0x24) && at<unsigned>(owner,0x28)==10,89);
        need(activeFrees==(activeBuffer?1u:0u),90);
        need(at<void*>(owner,0x10)==player && at<void*>(owner,0x38)==resource,91);
        unsigned expectedQuest=cs->shape>=2?(cs->fault>=21 && cs->fault<=23?cs->fault-20:3):0;
        need(questCalls==expectedQuest,92);
        if(cs->kind==1) {
            need(!baseCalls && !ownerFrees && !soundCalls && !bankFrees,93);
            need(singleton()==initialSingleton && at<void*>(owner,0x30)==bank,94);
            need(witness->p==owner && witness->index==0,95);
            need(loadCalls==(cs->fault>=21 && cs->fault<=23?0u:1u),96);
            if(cs->fault>=21 && cs->fault<=23) {
                need(names().size()==4 && completion().size()==4 && npcs().size()==2,97);
                for(unsigned i=0;i<3;++i) {
                    unsigned k=i==0?0:i+1;
                    need(names().find(*keys[k])->second==(i<cs->fault-21?0:quests[i]),98+i);
                }
                need(!nodeFrees[1] && !nodeFrees[2] && !nodeFrees[3],101);
            } else need(names().empty() && completion().empty() && npcs().empty(),102);
        } else {
            need(baseCalls==1 && !witness->p && witness->index==~0u,103);
            need(ownerFrees==(!caught && cs->alias==2?1u:0u),104);
            need(soundCalls==(cs->sample && !(cs->fault>=21 && cs->fault<=23)?1u:0u),105);
            need(at<void*>(owner,0x30)==(caught?bank:0),106);
            need(singleton()==(caught?initialSingleton:0),107);
            need(!loadCalls,108);
        }
        if(!(cs->kind==1 && cs->fault>=21 && cs->fault<=23))
            for(unsigned i=0;i<nodeCount;++i)need(nodes[i].freed,109);
        checkKeys(cs->kind==1 && cs->fault>=21 && cs->fault<=23,220);
    }
    sequenceOracle();
    // Stable semantic tokens, never raw addresses of child heap allocations.
    number(masterCalls); number(allocCalls); number(soundCtorCalls); number(stringCalls);
    number(lookupCalls); number(sampleCalls); number(loadCalls); number(questCalls);
    number(soundCalls); number(baseCalls); number(ownerFrees); number(bankFrees);
    number(activeFrees); number(nodeFrees[1]); number(nodeFrees[2]); number(nodeFrees[3]);
    for(unsigned i=0;i<3;++i)number(questDeleted[i]);
    number(caught); number(witness->p==owner); number(witness->index);
    number(singleton()==owner?1:singleton()==foreign?2:singleton()==0?0:3);
}
static void cleanup(bool caught) {
    // Cleanup occurs only after all observations. It is not credited as manager
    // behavior. In particular it reclaims the original's surviving NPC buckets.
    tracking=false;
    bool managerAlive=cs->kind==1 || (cs->kind==0 && !caught);
    if(managerAlive) {
        // Remove already-destroyed Quest values after a partially failed reload.
        names().clear(); completion().clear(); npcs().clear(); active().clear();
        // The secondary-constructor sound field is poisoned by design. Never
        // call any destructor with that poison: explicitly detach it here.
        at<void*>(owner,0x30)=0;
        qmlOldD1(owner);
    }
    for(unsigned i=0;i<3;++i)if(quests[i] && !questDeleted[i])qmlQuestD1(quests[i]);
    if(bankConstructed && !bankDeleted) {
        qmlSoundD1(bank);
        reinterpret_cast<void(*)(void*)>(qmlFree)(bank);
    }
    for(unsigned i=0;i<2;++i)if(buckets[i] && !bucketFrees[i] && !bucketBufferFrees[i])delete buckets[i];
    for(unsigned i=0;i<4;++i)if(keys[i])keys[i]->~Wide();
    for(unsigned m=0;m<2;++m)for(unsigned i=0;i<4;++i)if(mapKeeper[m][i])mapKeeper[m][i]->~Wide();
    for(unsigned i=0;i<2;++i)if(lookupKeeper[i])lookupKeeper[i]->~Wide();
    singleton()=0;
}
static void side(void* input,autotest::Capture& output,bool candidate) {
    cs=static_cast<Case*>(input); cap=&output; initialize();
    detour::Set allocators,frees,scalars,arrays,wide,constructor,questDestructor,soundDestructor,core,dependencies;
    allocPatch=&allocators; freePatch=&frees; scalarPatch=&scalars; arrayPatch=&arrays;
    widePatch=&wide; soundCtorPatch=&constructor; questPatch=&questDestructor;
    soundPatch=&soundDestructor; corePatch=&core;
    allocators.redirect(qmlAlloc,qmlAlloc,&allocate); frees.redirect(qmlFree,qmlFree,&release);
    scalars.redirect(qmlScalarDelete,qmlScalarDelete,&scalarRelease);
    arrays.redirect(qmlArrayDelete,qmlArrayDelete,&arrayRelease);
    wide.redirect(qmlWideCtor,qmlWideCtor,&wideConstructor);
    TL_REDIRECT(constructor,qmlSoundCtor,&soundConstructor);
    TL_REDIRECT(questDestructor,qmlQuestDelete,&questDelete);
    TL_REDIRECT(soundDestructor,qmlSoundDelete,&soundDelete);
    TL_REDIRECT(core,qmlCoreDelete,&coreDelete);
    TL_REDIRECT(dependencies,qmlMaster,&masterLookup);
    TL_REDIRECT(dependencies,qmlLookup,&sampleLookup);
    TL_REDIRECT(dependencies,qmlSample,&addSample);
    TL_REDIRECT(dependencies,qmlLoad,&loadBoundary);
    if(allocators.failed() || frees.failed() || scalars.failed() || arrays.failed() ||
       wide.failed() || constructor.failed() || questDestructor.failed() ||
       soundDestructor.failed() || core.failed() || dependencies.failed()) {
        output.issue=autotest::Capture::InvalidReport; return;
    }
    bool caught=false;
    if(cs->kind==0) {
        singleton()=cs->shape?foreign:0; initialSingleton=singleton();
        need(reinterpret_cast<uintptr_t>(&qmlOldC1)==reinterpret_cast<uintptr_t>(&qmlOldC2),114);
        typedef void(*Fn)(void*,void*);
        Fn fn=candidate?(cs->alias?&qmlNewC2:&qmlNewC1):(cs->alias?&qmlOldC2:&qmlOldC1);
        tracking=true;
        if(!autotest::beginInvocation(output,fn))return;
        try { fn(owner,resource); output.callCompleted=1; }
        catch(const Stop& s) { caught=true; need(s.site==cs->fault,115); }
    } else {
        // Safe complete original manager lifetime, not placement-only headers.
        singleton()=foreign; qmlOldC1(owner,resource); at<void*>(owner,0x30)=0;
        at<void*>(owner,0x10)=player; registerWeak(); seed(cs->shape);
        if(cs->sample) {
            bank=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qmlAlloc)(0xd0,0,0,0);
            soundConstructor(bank,soundManager,false); at<void*>(owner,0x30)=bank;
        }
        singleton()=cs->singleton==0?owner:cs->singleton==1?0:foreign;
        initialSingleton=singleton();
        need(reinterpret_cast<uintptr_t>(&qmlOldD1)==reinterpret_cast<uintptr_t>(&qmlOldD2),116);
        typedef void(*Fn)(void*);
        Fn oldFunctions[]={&qmlOldD1,&qmlOldD2,&qmlOldD0};
        Fn newFunctions[]={&qmlNewD1,&qmlNewD2,&qmlNewD0};
        Fn fn=cs->kind==1?(candidate?&qmlNewReload:&qmlOldReload):
            (candidate?newFunctions[cs->alias]:oldFunctions[cs->alias]);
        tracking=true;
        if(!autotest::beginInvocation(output,fn))return;
        try { fn(owner); output.callCompleted=1; }
        catch(const Stop& s) { caught=true; need(s.site==cs->fault,117); }
    }
    finishChecks(caught,candidate);
    cleanup(caught);
    number(0x514d4c46u); number(errors);
}
static void original(void* p,autotest::Capture& out) { side(p,out,false); }
static void replacement(void* p,autotest::Capture& out) { side(p,out,true); }
static bool good(const autotest::Outcome& out) {
    unsigned footer[2]={0,1};
    if(out.capture.length>=8)std::memcpy(footer,out.capture.data+out.capture.length-8,8);
    return out.reportValid && !out.childStatus && !out.capture.issue &&
           footer[0]==0x514d4c46u && !footer[1];
}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c) {
    hostContext=host; autotest::Outcome a,b;
    autotest::runChild(original,&c,a); autotest::runChild(replacement,&c,b);
    bool ok=good(a) && good(b) && a.capture.length==b.capture.length &&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    if(!c.fault) { if(coverage.observe(host,a,b))ok=false; }
    else ok=ok && a.capture.callStarted && b.capture.callStarted &&
        !a.capture.callCompleted && !b.capture.callCompleted &&
        a.capture.callTarget==coverage.original && host->comparison_pair &&
        host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
    if(!ok) {
        host->log("    questmanager lifecycle kind=%u alias=%u shape=%u sample=%u singleton=%u text=%u fault=%u status=%d/%d good=%u/%u bytes=%lu/%lu\n",
            c.kind,c.alias,c.shape,c.sample,c.singleton,c.text,c.fault,
            a.childStatus,b.childStatus,good(a),good(b),
            (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        for(unsigned side=0;side<2;++side) {
            const autotest::Capture& out=side?b.capture:a.capture;
            for(size_t i=0;i+4<=out.length;i+=4) {
                unsigned word; std::memcpy(&word,out.data+i,4);
                if((word&0xffff0000u)==0xf2000000u)
                    host->log("    lifecycle side=%u oracle=%u word=%lu\n",side,word-0xf2000000u,(unsigned long)(i/4));
            }
        }
    }
    return ok;
}
}

TL_TEST(questmanager_lifecycle_constructor) {
    using namespace quest_manager_lifetime;
    autotest::Coverage cv("questmanager_lifecycle_constructor",0xd32300);
    unsigned completed=0;
    for(unsigned alias=0;alias<2;++alias)for(unsigned existing=0;existing<2;++existing)
    for(unsigned samples=0;samples<4;++samples)for(unsigned poison=0;poison<2;++poison) {
        Case c={0,alias,existing,samples,0,poison,0};
        if(!pair(host,cv,c)){cv.report(host);return 1;} ++completed;
    }
    cv.report(host); return cv.completed!=completed || cv.different || cv.missing;
}
TL_TEST(questmanager_lifecycle_constructor_unwind) {
    using namespace quest_manager_lifetime;
    autotest::Coverage cv("constructor expected unwinds, no completed credit",0xd32300);
    unsigned witnesses=0;
    for(unsigned alias=0;alias<2;++alias)for(unsigned site=1;site<=11;++site)
    for(unsigned text=0;text<3;++text) {
        Case c={0,alias,0,3,0,text,site}; if(!pair(host,cv,c))return 1; ++witnesses;
    }
    host->log("    questmanager constructor: %u LSDA-supported expected unwinds, separate from completed coverage\n",witnesses);
    return 0;
}
TL_TEST(questmanager_lifecycle_reload) {
    using namespace quest_manager_lifetime;
    autotest::Coverage cv("questmanager_lifecycle_reload",0xd321f0); unsigned completed=0;
    for(unsigned shape=0;shape<4;++shape)for(unsigned sound=0;sound<2;++sound)
    for(unsigned single=0;single<3;++single)for(unsigned text=0;text<3;++text) {
        Case c={1,0,shape,sound,single,text,0};
        if(!pair(host,cv,c)){cv.report(host);return 1;} ++completed;
    }
    cv.report(host); return cv.completed!=completed || cv.different || cv.missing;
}
TL_TEST(questmanager_lifecycle_reload_unwind) {
    using namespace quest_manager_lifetime;
    autotest::Coverage cv("reload expected propagation, no completed credit",0xd321f0);
    const unsigned sites[]={21,22,23,25}; unsigned witnesses=0;
    for(unsigned i=0;i<4;++i)for(unsigned single=0;single<3;++single)
    for(unsigned text=0;text<3;++text) {
        Case c={1,0,2,1,single,text,sites[i]}; if(!pair(host,cv,c))return 1; ++witnesses;
    }
    host->log("    questmanager reload: %u expected propagated exceptions preserve observed partial state\n",witnesses);
    return 0;
}
TL_TEST(questmanager_lifecycle_destructor) {
    using namespace quest_manager_lifetime;
    for(unsigned alias=0;alias<3;++alias) {
        autotest::Coverage cv("questmanager_lifecycle_destructor",alias==2?0xd2ebf0:0xd2e930);
        unsigned completed=0;
        for(unsigned shape=0;shape<4;++shape)for(unsigned sound=0;sound<2;++sound)
        for(unsigned single=0;single<3;++single)for(unsigned text=0;text<3;++text) {
            Case c={2,alias,shape,sound,single,text,0};
            if(!pair(host,cv,c)){cv.report(host);return 1;} ++completed;
        }
        cv.report(host); if(cv.completed!=completed || cv.different || cv.missing)return 1;
    }
    return 0;
}
TL_TEST(questmanager_lifecycle_destructor_unwind) {
    using namespace quest_manager_lifetime;
    unsigned witnesses=0;
    for(unsigned alias=0;alias<3;++alias) {
        autotest::Coverage cv("destructor expected unwinds, no completed credit",alias==2?0xd2ebf0:0xd2e930);
        for(unsigned site=21;site<=24;++site)for(unsigned single=0;single<3;++single)
        for(unsigned text=0;text<3;++text) {
            Case c={2,alias,2,1,single,text,site}; if(!pair(host,cv,c))return 1; ++witnesses;
        }
    }
    host->log("    questmanager D1/D2/D0: %u supported virtual-deletion unwinds; D0 does not free owner after D1 throws\n",witnesses);
    return 0;
}
