// Compare the transition protocol, not actual level loading. Both executions
// call the same bounded spies; strings use the original process's libstdc++.
#include <climits>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Warper.h"
#include "GameClient.h"
#include "Player.h"
#include "Level.h"

TL_ORIGINAL(void, originalWarperActivate, (CWarper*), "_ZN7CWarper8activateEv")
extern "C" void recoveredWarperActivate(CWarper*) __asm__("_ZN7CWarper8activateEv");
TL_FUNCTION(warperAddWaypoint, "_ZN7CPlayer11addWaypointESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(warperWarpLevels, "_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b")

namespace {
struct Case { unsigned count, nullMask, mode, variant; bool waypoint, enabled, shared; };
CWarper* object;
CGameClient* clients[3];
CPlayer* players[2];
CResourceManager* resources[2];
CLevel* levels[2];
TArrayList<CGameClient*>* lists[2];
std::wstring* levelNames[2];
autotest::Capture* capture;
unsigned mode, callbackCount;
bool changed;

union Storage { long double alignment; char bytes[65536]; } storage;
unsigned used;
template<class T> T* raw() {
    unsigned at=(used+15u)&~15u; used=at+sizeof(T);
    if (used>sizeof(storage.bytes)) _exit(34);
    return reinterpret_cast<T*>(storage.bytes+at);
}
void pointer(void* p, unsigned offset, void* value) { std::memcpy(static_cast<char*>(p)+offset, &value, sizeof(value)); }
void number(void* p, unsigned offset, int value) { std::memcpy(static_cast<char*>(p)+offset, &value, sizeof(value)); }
void record(int n) { capture->add(&n, sizeof(n)); }
void recordString(const std::wstring& s) {
    record(static_cast<int>(s.size()));
    capture->add(s.data(), s.size()*sizeof(wchar_t));
}
int identity(void* p) {
    if (!p) return 0;
    for (int i=0;i<3;++i) if (p==clients[i]) return 10+i;
    for (int i=0;i<2;++i) {
        if (p==players[i]) return 20+i;
        if (p==resources[i]) return 30+i;
    }
    return -1;
}
void change() {
    if (changed) return;
    changed=true;
    // Every action is bounded, and happens only after the incoming arguments
    // were recorded. Subsequent iterations must observe the original policy.
    if (mode & 1) (*lists[0])[0]=clients[2];
    if (mode & 2) {
        object->m_sDungeon=L"changed dungeon";
        object->m_sWarpName=L"changed warp";
        object->m_iLevelDelta=-17;
        object->m_iLevelDepth=103;
        object->m_bWaypoint=!object->m_bWaypoint;
    }
    if (mode & 4) lists[0]->add(clients[2]);
    if (mode & 8) object->m_pResourceManager=resources[1];
    if (mode & 16) lists[0]->clear();
    if (mode & 32) {
        levelNames[0]->assign(L"changed level");
        number(levels[0],0x1a4,-109);
    }
}
bool waypointSpy(CPlayer* p, std::wstring dungeon, int depth) {
    if (++callbackCount>32) _exit(31);
    record(1); record(identity(p)); recordString(dungeon); record(depth);
    // mode 64 postpones mutation until warpLevels, exercising both call sites.
    if (!(mode & 64)) change();
    recordString(dungeon); // by-value argument must survive source mutation
    return false;
}
void warpSpy(CGameClient* c, std::wstring dungeon, int delta, int depth,
             bool waypoint, std::wstring name, bool flag) {
    if (++callbackCount>32) _exit(32);
    record(2); record(identity(c)); recordString(dungeon); record(delta);
    record(depth); record(waypoint); recordString(name); record(flag);
    change();
    recordString(dungeon); recordString(name);
}
void side(const Case& c, bool ours, autotest::Capture& out) {
    used=0; std::memset(storage.bytes,0,sizeof(storage.bytes));
    capture=&out; mode=c.mode; callbackCount=0; changed=false;
    object=raw<CWarper>();
    new (&object->m_sDungeon) std::wstring();
    new (&object->m_sWarpName) std::wstring();
    for (int i=0;i<2;++i) {
        resources[i]=raw<CResourceManager>(); levels[i]=raw<CLevel>(); players[i]=raw<CPlayer>();
        pointer(resources[i],0x18,levels[i]); pointer(players[i],0x68,resources[i]);
        lists[i]=new (reinterpret_cast<char*>(resources[i])+0x28) TArrayList<CGameClient*>(1);
        levelNames[i]=new (reinterpret_cast<char*>(levels[i])+0x280) std::wstring(i ? L"other level" : L"first level");
        number(levels[i],0x1a4,i ? -5 : 7);
    }
    for (unsigned i=0;i<3;++i) {
        clients[i]=raw<CGameClient>();
        pointer(clients[i],0x58,(c.nullMask & (1u<<i)) ? 0 : players[c.shared ? 0 : i%2]);
    }
    for (unsigned i=0;i<c.count;++i) lists[0]->add(clients[i]);
    lists[1]->add(clients[2]);
    object->m_pResourceManager=resources[0]; object->m_bEnabled=c.enabled;
    object->m_bWaypoint=c.waypoint;
    static const int deltas[]={0,1,-1,INT_MIN,INT_MAX};
    object->m_iLevelDelta=deltas[c.variant%5]; object->m_iLevelDepth=deltas[(c.variant+2)%5];
    if (c.variant) {
        object->m_sDungeon=std::wstring(L"A\0B\x416",4);
        object->m_sWarpName=std::wstring(80,L'W');
        levelNames[0]->assign(L"L\0V",3);
    }
    detour::Set patches;
    TL_REDIRECT(patches,warperAddWaypoint,&waypointSpy);
    TL_REDIRECT(patches,warperWarpLevels,&warpSpy);
    if (patches.failed()) _exit(33);
    if (ours) autotest::invoke(out,recoveredWarperActivate,object);
    else autotest::invoke(out,originalWarperActivate,object);
    record(3); record(callbackCount); record(identity(object->m_pResourceManager));
    record(object->m_bEnabled); record(object->m_bWaypoint);
    record(object->m_iLevelDelta); record(object->m_iLevelDepth);
    recordString(object->m_sDungeon); recordString(object->m_sWarpName);
    for (int i=0;i<2;++i) {
        record(lists[i]->size());
        for (unsigned j=0;j<lists[i]->size();++j) record(identity((*lists[i])[j]));
        recordString(*levelNames[i]);
    }
    patches.restore();
    typedef std::wstring Text;
    object->m_sDungeon.~Text(); object->m_sWarpName.~Text();
    for (int i=0;i<2;++i) { levelNames[i]->~Text(); lists[i]->~TArrayList<CGameClient*>(); }
}
void original(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),false,out); }
void recovered(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),true,out); }
}

TL_TEST(warper_activate_differential) {
    int failures=0;
    unsigned cases=0;
    autotest::Stats stats={0,0,0};
    autotest::Coverage coverage("warper_activate_differential",(uint64_t)(uintptr_t)&originalWarperActivate);
    // Stable cases cover all nullable-player combinations and both waypoint,
    // enabled and shared-player values. Enabled is deliberately ignored.
    for (unsigned n=0;n<=3;++n) for (unsigned mask=0;mask<(1u<<n);++mask)
    for (unsigned flags=0;flags<8;++flags) {
        Case c={n,mask,0,(n+mask+flags)%5, bool(flags&1),bool(flags&2),bool(flags&4)};
        bool ok=autotest::compareCase(original,recovered,&c,stats,host,"warper_activate_differential",cases,&coverage);
        TL_CHECK(failures,ok); ++cases;
    }
    // Clear only during warpLevels: clearing before the current client is
    // re-fetched makes the original dereference a null list, outside this test.
    const unsigned modes[]={1,2,4,8,32,1|2|4|8|32,64|1,64|2,64|4,64|8,64|16,64|32,64|1|2|4|8|32};
    for (unsigned m=0;m<sizeof(modes)/sizeof(modes[0]);++m) for (unsigned w=0;w<2;++w) {
        Case c={2,0,modes[m],m%5,bool(w),false,true};
        bool ok=autotest::compareCase(original,recovered,&c,stats,host,"warper_activate_differential",cases,&coverage);
        TL_CHECK(failures,ok); ++cases;
    }
    coverage.report(host);
    return failures + stats.incomplete + (coverage.completed<20 ? 1 : 0);
}
