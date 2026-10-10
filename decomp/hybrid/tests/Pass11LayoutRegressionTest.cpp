// Receipt-bearing pass11 preservation checks. No target is detoured.
// Original ELF: CLevelState C1/C2 0x968ef0, CQuestRewards::destroyIcons 0xd34aa0.
// CLevelState's first four collections are original three-pointer vectors;
// capture all of their initialized bytes, including the third pointer's high
// half, even if the recovered header currently calls those bytes padding.
#include <climits>
#include <cstddef>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "LevelState.h"
#include "QuestRewards.h"
#include "BaseUnit.h"
#include "Equipment.h"

TL_ORIGINAL(void, p11LayoutOldC1, (CLevelState*, int), "_ZN11CLevelStateC1Ei")
TL_ORIGINAL(void, p11LayoutOldC2, (CLevelState*, int), "_ZN11CLevelStateC2Ei")
TL_ORIGINAL(void, p11LayoutOldD1, (CLevelState*), "_ZN11CLevelStateD1Ev")
TL_ORIGINAL(void, p11LayoutOldIcons, (CQuestRewards*), "_ZN13CQuestRewards12destroyIconsEv")
extern "C" void p11LayoutNewC1(CLevelState*, int) __asm__("_ZN11CLevelStateC1Ei");
extern "C" void p11LayoutNewC2(CLevelState*, int) __asm__("_ZN11CLevelStateC2Ei");
extern "C" void p11LayoutNewIcons(CQuestRewards*) __asm__("_ZN13CQuestRewards12destroyIconsEv");
TL_FUNCTION(p11LayoutCoreC1, "_ZN10CRunicCoreC1Ev")
TL_FUNCTION(p11LayoutCoreC2, "_ZN10CRunicCoreC2Ev")
TL_FUNCTION(p11LayoutCoreD1, "_ZN10CRunicCoreD1Ev")
TL_FUNCTION(p11LayoutCoreD2, "_ZN10CRunicCoreD2Ev")
TL_FUNCTION(p11LayoutDestroyIcon, "_ZN10CEquipment11destroyIconEv")
extern "C" void* p11LayoutLevelTable[] __asm__("_ZTV11CLevelState");
extern "C" void* p11LayoutQuestTable[] __asm__("_ZTV13CQuestRewards");
extern "C" void* p11LayoutBaseTable[] __asm__("_ZTV9CBaseUnit");
extern "C" void* p11LayoutEquipmentTable[] __asm__("_ZTV10CEquipment");

namespace {
#define P11_OFFSET(C,F,N) typedef char offset_##C##_##F[__builtin_offsetof(C,F)==N ? 1:-1]
P11_OFFSET(CLevelState,m_iLevelId,0x10);
P11_OFFSET(CLevelState,m_sLevelName,0x18);
P11_OFFSET(CLevelState,m_lCharacters,0x20);
P11_OFFSET(CLevelState,m_lItems,0x38);
P11_OFFSET(CLevelState,m_lLogicStates,0x50);
P11_OFFSET(CLevelState,m_lLevelStrings,0x68);
P11_OFFSET(CLevelState,m_lFormations,0x80);
P11_OFFSET(CLevelState,m_iStateVersion,0x98);
P11_OFFSET(CLevelState,m_iAutomapWidth,0x9c);
P11_OFFSET(CLevelState,m_iAutomapHeight,0xa0);
P11_OFFSET(CLevelState,m_pAutomapData,0xa8);
P11_OFFSET(CLevelState,m_bUnknownB0,0xb0);
P11_OFFSET(CLevelState,m_bUnknownB1,0xb1);
P11_OFFSET(CQuestRewards,m_rewardItems,0x60);
P11_OFFSET(CEquipment,m_iUnknown238,0x238);
P11_OFFSET(CEquipment,m_pIconWindow,0x2c8);
#undef P11_OFFSET
typedef char level_size[sizeof(CLevelState)==0xb8 ? 1:-1];
typedef char quest_size[sizeof(CQuestRewards)==0x78 ? 1:-1];
typedef char equipment_size[sizeof(CEquipment)==0x438 ? 1:-1];
struct ListView { CBaseUnit** data; unsigned count,capacity,growBy; };
typedef char list_size[sizeof(ListView)==sizeof(TArrayList<CBaseUnit*>) ? 1:-1];

template<class T> struct Guarded {
    uint64_t before[2];
    uint64_t storage[(sizeof(T)+7)/8];
    uint64_t after[2];
    T* get() { return reinterpret_cast<T*>(storage); }
    void fill(unsigned seed) {
        unsigned char* p=reinterpret_cast<unsigned char*>(this);
        for(size_t i=0;i<sizeof(*this);++i)
            p[i]=static_cast<unsigned char>(0x35u+seed*37u+i*19u);
    }
    void captureGuards(autotest::Capture& out) {
        out.add(before,sizeof(before)); out.add(after,sizeof(after));
    }
};
struct Case { unsigned mode,seed,mutation; };
autotest::Capture* active;
CLevelState* levelTarget;
unsigned coreConstructed,coreDestroyed;
void number(unsigned n) { active->add(&n,sizeof(n)); }
void setPointer(void* p,size_t at,void* value) {
    std::memcpy(static_cast<char*>(p)+at,&value,sizeof(value));
}

// CRunicCore's unrelated process-global object counter is isolated. Both
// original and linked base entries are redirected; the real target still
// initializes its vtable, string, collections and every scalar itself.
void coreCtor(CRunicCore* p) {
    if(reinterpret_cast<void*>(p)!=reinterpret_cast<void*>(levelTarget)) _exit(71);
    ++coreConstructed;
    setPointer(p,0,NULL); setPointer(p,8,NULL);
}
void coreDtor(CRunicCore* p) {
    if(reinterpret_cast<void*>(p)!=reinterpret_cast<void*>(levelTarget)) _exit(72);
    void* safe=NULL; std::memcpy(&safe,reinterpret_cast<char*>(p)+8,sizeof(safe));
    if(safe) _exit(73);
    ++coreDestroyed; setPointer(p,0,NULL);
}

int levelId(unsigned seed) {
    static const int edges[]={INT_MIN,INT_MIN+1,-65536,-1024,-2,-1,0,1,
        2,3,7,255,256,65535,INT_MAX-1,INT_MAX};
    if(seed<16) return edges[seed];
    // All arithmetic stays representable; the rest are distinct signed IDs.
    return (seed&1) ? int(seed)*104729 : -int(seed)*13007;
}
void levelSide(const Case& c,autotest::Capture& out,bool ours) {
    Guarded<CLevelState> raw; raw.fill(c.seed);
    levelTarget=raw.get(); coreConstructed=coreDestroyed=0;
    detour::Set patches;
    TL_REDIRECT(patches,p11LayoutCoreC1,&coreCtor);
    TL_REDIRECT(patches,p11LayoutCoreC2,&coreCtor);
    TL_REDIRECT(patches,p11LayoutCoreD1,&coreDtor);
    TL_REDIRECT(patches,p11LayoutCoreD2,&coreDtor);
    if(patches.failed()) _exit(70);
    {
        out.addHeapInUse();
        typedef void(*Ctor)(CLevelState*,int);
        Ctor fn=c.mode==0 ? (ours?&p11LayoutNewC1:&p11LayoutOldC1)
                             : (ours?&p11LayoutNewC2:&p11LayoutOldC2);
        const int id=levelId(c.seed);
        out.add(&id,sizeof(id));
        autotest::invoke(out,fn,levelTarget,id);
        const unsigned char* bytes=reinterpret_cast<const unsigned char*>(levelTarget);
        // The base vptr must be the exact LevelState vtable, not merely nonnull.
        void** actualTable=NULL; std::memcpy(&actualTable,bytes,sizeof(actualTable));
        number(actualTable==p11LayoutLevelTable+2);
        out.add(bytes,0x10);                     // Exact vptr and safe-pointer state.
        out.add(bytes+0x10,4);                  // Signed level ID.
        out.addText(levelTarget->m_sLevelName);
        out.add(bytes+0x20,0x60);               // Four original std::vector triples.
        out.add(bytes+0x80,0x14);               // Formation array, including growBy=10.
        out.add(bytes+0x98,0x0c);               // Exact version float bits and map dimensions.
        out.add(bytes+0xa8,0x0a);               // Map pointer and both flags.
        raw.captureGuards(out); number(coreConstructed); number(coreDestroyed);
        // The initialized string must support real COW copy, append and cleanup.
        std::wstring peer=levelTarget->m_sLevelName;
        levelTarget->m_sLevelName.append(1+c.seed%33,wchar_t(L'A'+c.seed%26));
        levelTarget->m_sLevelName+=L" \x3b1\x416";
        out.addText(peer); out.addText(levelTarget->m_sLevelName);
        p11LayoutOldD1(levelTarget);
        number(coreConstructed); number(coreDestroyed);
        raw.captureGuards(out); out.addText(peer);
    }
    out.addHeapInUse(); levelTarget=NULL;
}

struct QuestWorld {
    Guarded<CQuestRewards> quest;
    // Full Equipment-sized storage for every stand-in. The last three use
    // the real BaseUnit vtable/RTTI and must fail the Equipment dynamic_cast.
    Guarded<CEquipment> units[8];
    uint64_t icons[8];
    unsigned hits[8];
    unsigned calls,allocatedSlots;
    bool changed;
    QuestWorld(unsigned seed):calls(0),allocatedSlots(0),changed(false) {
        quest.fill(seed+17); setPointer(quest.get(),0,p11LayoutQuestTable+2);
        new(&quest.get()->m_rewardItems) TArrayList<CBaseUnit*>(1+seed%5);
        for(unsigned i=0;i<8;++i) {
            units[i].fill(seed*11+i);
            setPointer(units[i].get(),0,i<5?p11LayoutEquipmentTable+2:p11LayoutBaseTable+2);
            icons[i]=0x1122334400000000ULL+seed*16+i;
            units[i].get()->m_pIconWindow=((seed+i)%4==0)?NULL:
                reinterpret_cast<CEGUI::Window*>(&icons[i]);
            units[i].get()->m_iUnknown238=int(seed)*17+int(i)-128;
            hits[i]=0;
        }
    }
    ~QuestWorld() { quest.get()->m_rewardItems.~TArrayList<CBaseUnit*>(); }
    TArrayList<CBaseUnit*>& list() { return quest.get()->m_rewardItems; }
    ListView& view() { return *reinterpret_cast<ListView*>(&list()); }
    CBaseUnit* unit(unsigned i) { return reinterpret_cast<CBaseUnit*>(units[i].get()); }
    unsigned id(const CBaseUnit* p) {
        if(!p) return 0;
        for(unsigned i=0;i<8;++i) if(p==unit(i)) return i+1;
        _exit(74); return 99;
    }
    unsigned iconId(const CEGUI::Window* p) {
        if(!p) return 0;
        for(unsigned i=0;i<8;++i)
            if(p==reinterpret_cast<CEGUI::Window*>(&icons[i])) return i+1;
        _exit(75); return 99;
    }
    void add(CBaseUnit* p) {
        list().add(p); allocatedSlots=view().capacity;
        // Spare allocated slots are defined sentinels, never indeterminate data.
        for(unsigned i=view().count;i<allocatedSlots;++i) view().data[i]=unit(7);
    }
    void clear() { list().clear(); allocatedSlots=0; }
    void captureList() {
        const ListView& v=view();
        number(v.data!=NULL); number(v.count); number(v.capacity); number(v.growBy);
        number(allocatedSlots);
        if(allocatedSlots>128 || v.count>allocatedSlots || v.capacity>allocatedSlots ||
           ((v.data==NULL)!=(allocatedSlots==0))) _exit(76);
        // Capture the whole allocated array, including slots outside count and
        // capacity when the defined operator[] fallback is being exercised.
        for(unsigned i=0;i<allocatedSlots;++i) number(id(v.data[i]));
    }
    void capture() {
        uint64_t state[(sizeof(CQuestRewards)+7)/8];
        std::memcpy(state,quest.get(),sizeof(state));
        const uintptr_t present=view().data?1:0;
        std::memcpy(reinterpret_cast<char*>(state)+0x60,&present,sizeof(present));
        active->add(state,sizeof(state)); quest.captureGuards(*active);
        captureList(); number(calls); number(changed);
        for(unsigned i=0;i<8;++i) {
            uint64_t item[(sizeof(CEquipment)+7)/8];
            std::memcpy(item,units[i].get(),sizeof(item));
            const uintptr_t icon=iconId(units[i].get()->m_pIconWindow);
            std::memcpy(reinterpret_cast<char*>(item)+0x2c8,&icon,sizeof(icon));
            active->add(item,sizeof(item)); units[i].captureGuards(*active);
            number(hits[i]); active->add(&icons[i],sizeof(icons[i]));
        }
    }
};
QuestWorld* world;
const Case* input;

void destroyIcon(CEquipment* p) {
    const unsigned token=world->id(reinterpret_cast<CBaseUnit*>(p));
    if(token==0 || token>5 || world->calls>=128) _exit(77);
    const unsigned i=token-1;
    // Order, identity, repeated callbacks, and already-absent icons are visible.
    number(0xd357); number(token); number(world->calls);
    number(world->iconId(p->m_pIconWindow));
    active->add(&p->m_iUnknown238,sizeof(p->m_iUnknown238));
    world->captureList();
    ++world->calls; ++world->hits[i];
    p->m_pIconWindow=NULL; ++p->m_iUnknown238;
    if(world->changed || input->mutation==0) return;
    world->changed=true;
    switch(input->mutation) {
    case 1: // Append across capacity boundaries, with mixed RTTI and a duplicate.
        world->add(world->unit(4)); world->add(NULL); world->add(world->unit(6));
        world->add(world->unit(2)); world->add(world->unit(4));
        break;
    case 2: // A callback can destroy the whole backing allocation and terminate.
        world->clear();
        break;
    case 3: // Unordered removal moves the last entry into the current slot.
        world->list().removeAt(0);
        break;
    case 4: // Later slots must be reread rather than using a prefetched item list.
        if(world->view().count>1) world->view().data[1]=world->unit(3);
        if(world->view().count>2) world->view().data[2]=NULL;
        if(world->view().count>3) world->view().data[3]=world->unit(7);
        if(world->view().count>4) world->view().data[4]=world->unit(3);
        break;
    case 5: // Loop termination must reread count after the collaborator returns.
        world->view().count=1;
        break;
    case 6: // Replacement allocation tests both data and count reloads.
        world->clear(); world->list().setGrowBy(2);
        world->add(world->unit(4)); world->add(world->unit(1));
        world->add(NULL); world->add(world->unit(6)); world->add(world->unit(1));
        break;
    case 7: // Capacity metadata below count: original operator[] uses slot zero.
        // Physical storage remains intact; no out-of-allocation read is needed.
        world->view().capacity=input->seed%3;
        if(input->seed&1) world->view().data[0]=NULL;
        break;
    default: _exit(78);
    }
    world->captureList();
}

CBaseUnit* initialItem(QuestWorld& w,unsigned seed,unsigned index) {
    switch(seed%8) {
    case 0: return NULL;
    case 1: return w.unit(5+index%3);
    case 2: return w.unit((index+seed)%5);
    case 3: return w.unit(seed%5); // Every entry aliases the same Equipment.
    case 4: return index%3==0?NULL:index%3==1?w.unit(index%5):w.unit(5+index%3);
    case 5: return index%4==0?w.unit(0):index%4==1?w.unit(6):NULL;
    case 6: return index%2?w.unit(4):w.unit(index%5);
    default: return index%5==0?NULL:w.unit((index*3+seed)%8);
    }
}
void questSide(const Case& c,autotest::Capture& out,bool ours) {
    input=&c;
    detour::Set patches;
    TL_REDIRECT(patches,p11LayoutDestroyIcon,&destroyIcon);
    if(patches.failed()) _exit(79);
    {
        QuestWorld w(c.seed); world=&w;
        static const unsigned sizes[]={0,1,2,3,4,7,8,9,15,16,17,25};
        unsigned n=c.mutation ? 3+c.seed%23 : sizes[(c.seed/8)%12];
        for(unsigned i=0;i<n;++i) w.add(initialItem(w,c.seed,i));
        if(c.mutation) {
            w.view().data[0]=w.unit(c.seed%5); // Every mutation case reaches its callback.
            w.view().data[1]=w.unit((c.seed+1)%5);
            w.view().data[2]=w.unit(5+c.seed%3);
        }
        // Empty, allocated-but-empty arrays exercise the early exit too.
        if(!c.mutation && n==0 && (c.seed&4)) {
            w.add(w.unit(2)); w.view().count=0;
        }
        w.capture(); out.addHeapInUse();
        autotest::invoke(out,ours?&p11LayoutNewIcons:&p11LayoutOldIcons,w.quest.get());
        w.capture(); out.addHeapInUse();
        // Repeat on the resulting live state: duplicate callbacks must remain
        // visible even after the fake collaborator has cleared every icon.
        if(ours) p11LayoutNewIcons(w.quest.get()); else p11LayoutOldIcons(w.quest.get());
        w.capture(); out.addHeapInUse();
        if(c.mutation && !w.changed) _exit(80);
    }
    out.addHeapInUse(); world=NULL; input=NULL;
}
void side(void* p,autotest::Capture& out,bool ours) {
    active=&out; const Case& c=*static_cast<Case*>(p);
    if(c.mode<2) levelSide(c,out,ours); else questSide(c,out,ours);
    active=NULL;
}
void original(void* p,autotest::Capture& out) { side(p,out,false); }
void recovered(void* p,autotest::Capture& out) { side(p,out,true); }
int run(const tlhybrid_host* host,unsigned mode) {
    const char* names[]={"pass11_levelstate_ctor_c1","pass11_levelstate_ctor_c2",
                         "pass11_quest_destroy_icons"};
    void* originals[]={reinterpret_cast<void*>(&p11LayoutOldC1),
        reinterpret_cast<void*>(&p11LayoutOldC2),reinterpret_cast<void*>(&p11LayoutOldIcons)};
    autotest::Coverage coverage(names[mode],(uint64_t)(uintptr_t)originals[mode]);
    int failures=0;
    const unsigned cases=mode<2?64:96;
    const unsigned mutations=mode<2?1:8;
    for(unsigned mutation=0;mutation<mutations;++mutation)
        for(unsigned seed=0;seed<cases;++seed) {
            Case c={mode,seed,mutation}; autotest::Outcome a,b;
            autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
            const int result=coverage.observe(host,a,b);
            if(result) {
                ++failures;
                if(failures<=12) {
                    size_t first=0;
                    while(first<a.capture.length && first<b.capture.length &&
                          a.capture.data[first]==b.capture.data[first]) ++first;
                    host->log("    %s seed %u mutation %u result %d status %d/%d bytes %lu/%lu first %lu\n",
                        names[mode],seed,mutation,result,a.childStatus,b.childStatus,
                        (unsigned long)a.capture.length,(unsigned long)b.capture.length,
                        (unsigned long)first);
                }
            }
        }
    coverage.report(host);
    // Every planned pair must finish; identical faults, exceptions, timeouts,
    // and missing/wrong target receipts cannot satisfy preservation coverage.
    if(coverage.completed!=cases*mutations || coverage.completed<20) ++failures;
    return failures;
}
}
TL_TEST(pass11_levelstate_ctor_c1) { return run(host,0); }
TL_TEST(pass11_levelstate_ctor_c2) { return run(host,1); }
TL_TEST(pass11_quest_destroy_icons) { return run(host,2); }
