#include <climits>
#include <cstring>
#include <new>
#include <CEGUI.h>
#include "GameUI.h"
#include "Character.h"
#include "SkillMenu.h"
#include "Settings.h"
#include "AutoTest.h"
#include "Detour.h"

// The CEGUI member-slot consumer reads AL. These five callbacks return bool.
#define CALLBACK(N, S) \
    TL_ORIGINAL(bool, original##N, (CGameUI*, const CEGUI::EventArgs*), S) \
    extern "C" bool candidate##N(CGameUI*, const CEGUI::EventArgs*) __asm__(S);
CALLBACK(Click, "_ZN7CGameUI14handle_onClickERKN5CEGUI9EventArgsE")
CALLBACK(Skill, "_ZN7CGameUI21handle_SkillMouseOverERKN5CEGUI9EventArgsE")
CALLBACK(Names, "_ZN7CGameUI22handle_ToggleItemNamesERKN5CEGUI9EventArgsE")
CALLBACK(Hover, "_ZN7CGameUI16handle_MouseOverERKN5CEGUI9EventArgsE")
CALLBACK(Through, "_ZN7CGameUI19handle_MouseThroughERKN5CEGUI9EventArgsE")
#undef CALLBACK
TL_FUNCTION(baseClickFn, "_ZN7CGameUI7onClickE15ELayoutFunction")
TL_FUNCTION(lookupFn, "_ZN16CResourceManager17getUnitDataByGuidEx")
TL_FUNCTION(getIntFn, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(setIntFn, "_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(clearFn, "_ZN10CSkillMenu17clearSkillTooltipEv")
#define SDK(N, S) extern "C" char N[] __asm__(S)
SDK(childFn, "_ZNK5CEGUI6Window7isChildEPKS0_");
SDK(addFn, "_ZN5CEGUI6Window14addChildWindowEPS0_");
SDK(positionFn, "_ZNK5CEGUI6Window11getPositionEv");
SDK(sizeFn, "_ZNK5CEGUI6Window7getSizeEv");
SDK(setPositionFn, "_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
SDK(setSizeFn, "_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
SDK(backFn, "_ZN5CEGUI6Window10moveToBackEv");
SDK(frontFn, "_ZN5CEGUI6Window11moveToFrontEv");
#undef SDK

namespace {
enum Target { Click, Skill, Names, Hover, Through };
enum Trace { Dispatch = 1, WrongVirtual, BaseDispatch, Lookup, GetInt, SetInt,
             IsChild, AddChild, GetPosition, SetPosition, GetSize, SetSize,
             MoveBack, MoveFront, ClearTooltip, NestedReturn };
typedef bool (*Handler)(CGameUI*, const CEGUI::EventArgs*);

struct Case {
    Target target;
    int action, button, setting;
    unsigned flags, id, guid, profile, at, geometry, sequence, repeat, fault;
    bool present, character, hit, result, handled, child, menu, realClear;
    Case(Target t)
        : target(t), action(81), button(0), setting(0), flags(21), id(1000),
          guid(2), profile(0), at(0), geometry(0), sequence(0), repeat(1), fault(0),
          present(true), character(true), hit(true), result(true),
          handled(false), child(false), menu(true), realClear(false) {}
};
struct CallbackFailure { unsigned boundary; explicit CallbackFailure(unsigned b) : boundary(b) {} };
struct Block { unsigned char* start; unsigned size; };
struct PointerField { void* base; unsigned offset; };
Block blocks[40];
PointerField pointerFields[100];
unsigned blockCount, pointerCount, calls[20], depth, step;
bool ours, mutated;
const Case* cs;
autotest::Capture* cap;
void* ui;
void* actors[2];
void* managers[3];
void* settings[2];
void* menus[2];
void* resultObject;
CEGUI::Window* windows[8]; // input A/B, glow A/B, parent A/B, spare glow, spare
CEGUI::UVector2* positions;
CEGUI::UVector2* sizes;
CEGUI::MouseEventArgs* mouseEvent;
CEGUI::EventArgs* plainEvent;
void* eventVtables[2];
void** table;
long long* guids;
int* actions;
const unsigned hoverOffsets[] = {0x1640, 0x1641, 0x1642, 0x1643, 0x1660};
const unsigned guidOffsets[] = {0x1648, 0x1650, 0x1658, 0x1668};
const long long guidValues[] = {0LL, -1LL, 0x1234567887654321LL,
                               (-9223372036854775807LL - 1LL)};

bool dispatch(CGameUI*, ELayoutFunction);
bool wrongVirtual(CGameUI*, ELayoutFunction);
bool baseDispatch(CGameUI*, ELayoutFunction);

template<class T> T& field(void* p, unsigned offset)
{
    return *reinterpret_cast<T*>(static_cast<char*>(p) + offset);
}
void n(unsigned x) { cap->add(&x, sizeof(x)); }
void integer(int x) { cap->add(&x, sizeof(x)); }
void wide(long long x) { cap->add(&x, sizeof(x)); }
void invalid(unsigned code)
{
    n(0xbad00000u | code);
    cap->issue = autotest::Capture::InvalidReport;
}
void* object(unsigned bytes)
{
    if (blockCount == 40 || bytes > 0x4000) _exit(70);
    unsigned char* p = static_cast<unsigned char*>(autotest::allocate(bytes + 32));
    if (!p) _exit(71);
    std::memset(p, 0xd3, 16);
    std::memset(p + 16, 0xa5, bytes);
    std::memset(p + 16 + bytes, 0x6c, 16);
    blocks[blockCount].start = p;
    blocks[blockCount++].size = bytes;
    return p + 16;
}
void pointerField(void* p, unsigned offset, void* value)
{
    if (pointerCount == 100) _exit(72);
    field<void*>(p, offset) = value;
    pointerFields[pointerCount].base = p;
    pointerFields[pointerCount++].offset = offset;
}
uintptr_t token(const void* p)
{
    if (!p) return 0;
    if (p == reinterpret_cast<void*>(1)) return 1; // suppressed-path poison
    for (unsigned i = 0; i < blockCount; ++i) {
        uintptr_t at = reinterpret_cast<uintptr_t>(p);
        uintptr_t start = reinterpret_cast<uintptr_t>(blocks[i].start + 16);
        if (at >= start && at - start < blocks[i].size)
            return 0x10000u + (uintptr_t(i) << 16) + at - start;
    }
    if (p == eventVtables[0]) return 0x100;
    if (p == eventVtables[1]) return 0x101;
    if (p == reinterpret_cast<void*>(&dispatch)) return 0x102;
    if (p == reinterpret_cast<void*>(&wrongVirtual)) return 0x103;
    if (p == reinterpret_cast<void*>(&baseDispatch)) return 0x104;
    cap->issue = autotest::Capture::UnsupportedPointer;
    return 0;
}
void ptr(const void* p) { uintptr_t value = token(p); cap->add(&value, sizeof(value)); }
unsigned windowIndex(const CEGUI::Window* p)
{
    for (unsigned i = 0; i < 8; ++i) if (p == windows[i]) return i;
    cap->issue = autotest::Capture::UnsupportedPointer;
    return 7;
}
void setFlags(unsigned bits)
{
    for (unsigned i = 0; i < 5; ++i) field<bool>(ui, hoverOffsets[i]) = (bits & (1u << i)) != 0;
}
void trace(unsigned code, const void* self)
{
    ++calls[code]; n(code); n(step); n(depth); ptr(self);
    for (unsigned i = 0; i < 5; ++i) n(field<bool>(ui, hoverOffsets[i]));
    for (unsigned i = 0; i < 4; ++i) wide(field<long long>(ui, guidOffsets[i]));
    ptr(field<void*>(ui, 0x38)); ptr(field<void*>(ui, 0x78));
    ptr(field<void*>(ui, 0x558)); ptr(field<void*>(ui, 0x1318));
    ptr(mouseEvent->window); ptr(field<void*>(windows[0], 0xb0));
    n(KSETTINGS_TOGGLE_ITEM_NAME);
}
Handler handler(Target t)
{
    if (ours) {
        switch (t) {
        case Click: return &candidateClick;
        case Skill: return &candidateSkill;
        case Names: return &candidateNames;
        case Hover: return &candidateHover;
        case Through: return &candidateThrough;
        }
    }
    switch (t) {
    case Click: return &originalClick;
    case Skill: return &originalSkill;
    case Names: return &originalNames;
    case Hover: return &originalHover;
    case Through: return &originalThrough;
    }
    return 0;
}
bool nested(Target t, const CEGUI::EventArgs* event)
{
    ++depth;
    bool result = handler(t)(reinterpret_cast<CGameUI*>(ui), event);
    --depth;
    n(NestedReturn); n(t); n(result);
    return result;
}

bool dispatch(CGameUI* self, ELayoutFunction action)
{
    trace(Dispatch, self); integer(static_cast<int>(action));
    field<unsigned>(ui, 0x1900) = static_cast<unsigned>(action) ^ (0x51238000u + depth);
    field<bool>(ui, 0x1640) = !cs->result;
    bool result = depth ? !cs->result : cs->result;
    if (cs->profile && !depth) {
        mouseEvent->window = windows[1];
        mouseEvent->button = static_cast<CEGUI::MouseButton>(cs->profile == 1 ? 6 : 0);
        nested(Click, mouseEvent);
    }
    return result;
}
bool wrongVirtual(CGameUI* self, ELayoutFunction action)
{
    trace(WrongVirtual, self); integer(static_cast<int>(action)); return !cs->result;
}
bool baseDispatch(CGameUI* self, ELayoutFunction action)
{
    // A mistaken qualified base call is a complete differing report, not a crash
    // or an accidental execution of the large gameplay dispatcher.
    trace(BaseDispatch, self); integer(static_cast<int>(action)); return !cs->result;
}
void* lookup(void* self, long long guid)
{
    trace(Lookup, self); wide(guid);
    ptr(field<void*>(actors[0], 0x68)); ptr(field<void*>(ui, 0x1308));
    bool hit = cs->sequence == 1 ? step == 0 : cs->hit;
    if (cs->profile == 1 || cs->profile == 5) mouseEvent->window = windows[1];
    if (cs->profile == 2 || cs->profile == 5) guids[0] = 0x7766554433221100LL;
    if (cs->profile == 3 || cs->profile == 5) {
        field<void*>(ui, 0x38) = actors[1];
        field<void*>(actors[0], 0x68) = managers[1];
    }
    if (cs->profile == 4 || cs->profile == 5) {
        setFlags(cs->handled ? 31 : 0);
        field<long long>(ui, 0x1650) = 0x6a5a4a3a2a1a0908LL;
        field<long long>(ui, 0x1648) = -246813579LL;
    }
    if (cs->profile == 6 && !depth) {
        mouseEvent->window = windows[1]; // alternate non-item skill hover
        nested(Skill, mouseEvent);
    }
    return hit ? resultObject : 0;
}
int getInt(void* self, unsigned key)
{
    trace(GetInt, self); n(key);
    if (cs->profile & 1) field<void*>(ui, 0x78) = settings[1];
    if (cs->profile & 2) KSETTINGS_TOGGLE_ITEM_NAME = 0xfedcba98u;
    return cs->setting;
}
void setInt(void* self, unsigned key, int value)
{
    trace(SetInt, self); n(key); integer(value);
    field<int>(self, 0x10) = value;
    field<unsigned>(ui, 0x1900) = 0x81624357u;
    field<bool>(ui, 0x1640) = cs->handled;
}
void maybeThrow(unsigned code)
{
    if (cs->fault == code) throw CallbackFailure(code);
}
void changeHover(unsigned code)
{
    if (mutated || !cs->profile || cs->at != code) return;
    mutated = true;
    if (cs->profile == 1) field<void*>(ui, 0x1318) = windows[3];
    if (cs->profile == 2) mouseEvent->window = windows[1];
    if (cs->profile == 3) field<void*>(windows[0], 0xb0) = windows[5];
}
bool isChild(const CEGUI::Window* self, const CEGUI::Window* child)
{
    trace(IsChild, self); ptr(child);
    // Observe the relationship before the reentrant mutation, like an ordinary
    // collaborator returning its already-computed answer.
    bool result = field<void*>(const_cast<CEGUI::Window*>(child), 0xb0) == self;
    n(result); changeHover(IsChild); maybeThrow(IsChild); return result;
}
void addChild(CEGUI::Window* self, CEGUI::Window* child)
{
    trace(AddChild, self); ptr(child);
    field<void*>(child, 0xb0) = self;
    changeHover(AddChild); maybeThrow(AddChild);
}
const CEGUI::UVector2& position(const CEGUI::Window* self)
{
    trace(GetPosition, self);
    unsigned i = windowIndex(self);
    cap->add(&positions[i], sizeof(positions[i]));
    changeHover(GetPosition); maybeThrow(GetPosition);
    return positions[i];
}
void setPosition(CEGUI::Window* self, const CEGUI::UVector2& value)
{
    trace(SetPosition, self);
    cap->add(&value, sizeof(value));
    // getPosition is reference-returning: retain its exact source identity.
    unsigned reference = 99;
    for (unsigned i = 0; i < 8; ++i) if (&value == &positions[i]) reference = i;
    n(reference);
    positions[windowIndex(self)] = value;
    changeHover(SetPosition); maybeThrow(SetPosition);
}
CEGUI::UVector2 size(const CEGUI::Window* self)
{
    // Deliberately the SDK's real by-value class ABI (hidden return storage),
    // never a UVector2 reference or a hand-written two-register substitute.
    trace(GetSize, self);
    CEGUI::UVector2 result(sizes[windowIndex(self)]);
    cap->add(&result, sizeof(result));
    changeHover(GetSize); maybeThrow(GetSize);
    return result;
}
void setSize(CEGUI::Window* self, const CEGUI::UVector2& value)
{
    trace(SetSize, self);
    cap->add(&value, sizeof(value));
    bool aliasesSource = false;
    for (unsigned i = 0; i < 8; ++i) aliasesSource = aliasesSource || &value == &sizes[i];
    n(aliasesSource);
    sizes[windowIndex(self)] = value;
    changeHover(SetSize); maybeThrow(SetSize);
}
void back(CEGUI::Window* self)
{
    trace(MoveBack, self); changeHover(MoveBack); maybeThrow(MoveBack);
    field<unsigned>(self, 0x180) = 0x12340000u + calls[MoveBack];
    // The handler must write true after this callback, even on repeated hover.
    field<bool>(ui, 0x1640) = false;
}
void front(CEGUI::Window* self) { trace(MoveFront, self); }
void clear(void* self)
{
    trace(ClearTooltip, self);
    field<bool>(self, 0x3b) = false;
    field<long long>(self, 0x40) = -1;
    if (cs->profile == 2 || cs->profile == 3) field<void*>(ui, 0x558) = menus[1];
    if (cs->profile == 4 && !depth) {
        field<void*>(ui, 0x558) = 0;
        nested(Through, plainEvent);
        field<void*>(ui, 0x558) = menus[1];
    }
    if (cs->profile == 1 || cs->profile == 3 || cs->profile == 4) {
        setFlags((cs->flags ^ 31u) | 1u);
        field<long long>(ui, 0x1648) = 0x1122334455667788LL;
        field<long long>(ui, 0x1650) = -772233445566LL;
    }
}

void geometry(unsigned kind, unsigned index, CEGUI::UVector2& result)
{
    // Four independently distinguishable components, including raw quiet NaN
    // payloads, infinities, signed zero, and fractional/negative offsets.
    static const uint32_t bits[4][4] = {
        {0x3f000000u, 0xc1200000u, 0xbe800000u, 0x418a0000u},
        {0x80000000u, 0x00000000u, 0x3e000000u, 0xc0200000u},
        {0x7f800000u, 0xff800000u, 0x7fc12345u, 0x7fc54321u},
        {0xbf400000u, 0x3f600000u, 0x40200000u, 0xc0900000u}
    };
    uint32_t value[4];
    for (unsigned i = 0; i < 4; ++i) value[i] = bits[kind % 4][(i + index) % 4];
    // UVector2 is four SDK float components; no floating-point comparisons or
    // arithmetic can erase a signed zero or NaN payload in the observation.
    typedef char vector_has_four_floats[sizeof(CEGUI::UVector2) == 16 ? 1 : -1];
    (void)sizeof(vector_has_four_floats);
    std::memcpy(&result, value, sizeof(value));
}
void initialize()
{
    autotest::g_arenaUsed = 0;
    blockCount = pointerCount = depth = step = 0;
    mutated = false;
    eventVtables[0] = eventVtables[1] = 0;
    std::memset(calls, 0, sizeof(calls));
    ui = object(sizeof(CGameUI));
    for (unsigned i = 0; i < 2; ++i) {
        actors[i] = object(sizeof(CCharacter));
        settings[i] = object(0x40);
        menus[i] = object(sizeof(CSkillMenu));
    }
    for (unsigned i = 0; i < 3; ++i) managers[i] = object(0x40);
    resultObject = object(0x40);
    for (unsigned i = 0; i < 8; ++i) windows[i] = static_cast<CEGUI::Window*>(object(sizeof(CEGUI::Window)));
    positions = static_cast<CEGUI::UVector2*>(object(8 * sizeof(CEGUI::UVector2)));
    sizes = static_cast<CEGUI::UVector2*>(object(8 * sizeof(CEGUI::UVector2)));
    table = static_cast<void**>(object(16 * sizeof(void*)));
    actions = static_cast<int*>(object(2 * sizeof(int)));
    guids = static_cast<long long*>(object(2 * sizeof(long long)));
    mouseEvent = new(object(sizeof(CEGUI::MouseEventArgs))) CEGUI::MouseEventArgs(cs->present ? windows[0] : 0);
    plainEvent = new(object(sizeof(CEGUI::EventArgs))) CEGUI::EventArgs();
    eventVtables[0] = field<void*>(mouseEvent, 0);
    eventVtables[1] = field<void*>(plainEvent, 0);
    pointerField(mouseEvent, 0, eventVtables[0]);
    pointerField(plainEvent, 0, eventVtables[1]);
    pointerField(mouseEvent, 0x10, cs->present ? windows[0] : 0);
    mouseEvent->handled = plainEvent->handled = cs->handled;
    mouseEvent->button = static_cast<CEGUI::MouseButton>(cs->button);
    mouseEvent->position = CEGUI::Point(-7.5f, 2.25f);
    mouseEvent->moveDelta = CEGUI::Point(3.75f, -4.125f);
    mouseEvent->sysKeys = 0x31415;
    mouseEvent->wheelChange = -6.5f;
    mouseEvent->clickCount = 3;
    actions[0] = cs->action; actions[1] = -1234567;
    guids[0] = guidValues[cs->guid]; guids[1] = 0x76543210abcdef01LL;
    for (unsigned i = 0; i < 16; ++i)
        pointerField(table, i * sizeof(void*), reinterpret_cast<void*>(i == 2 ? &dispatch : &wrongVirtual));
    pointerField(ui, 0, table);
    pointerField(ui, 0x38, cs->character ? actors[0] : 0);
    pointerField(ui, 0x78, settings[0]);
    pointerField(ui, 0x558, cs->menu ? menus[0] : 0);
    pointerField(ui, 0x1308, managers[2]); // intentionally not the actor manager
    pointerField(ui, 0x1318, windows[2]);
    for (unsigned i = 0; i < 2; ++i) {
        pointerField(actors[i], 0x68, managers[i]);
        field<int>(settings[i], 0x10) = -76543 - i;
        field<bool>(menus[i], 0x3b) = true;
        field<long long>(menus[i], 0x40) = 0x1234000056780000LL + i;
    }
    for (unsigned i = 0; i < 8; ++i) {
        void* parent = i == 0 ? windows[4] : windows[5];
        if (i == 1 && (cs->flags & 2)) parent = windows[4];
        if (i == 2) parent = cs->child ? windows[4] : windows[5];
        pointerField(windows[i], 0xb0, parent);
        pointerField(windows[i], 0x1d8, i == 1 ? static_cast<void*>(guids + 1) : static_cast<void*>(guids));
        field<unsigned>(windows[i], 0x170) = i == 0 ? cs->id : 999;
        new(&positions[i]) CEGUI::UVector2();
        new(&sizes[i]) CEGUI::UVector2();
        geometry(cs->geometry, i, positions[i]);
        geometry(cs->geometry + 1, i + 1, sizes[i]);
    }
    if (cs->target == Click) {
        field<void*>(windows[0], 0x1d8) = cs->button || !cs->present ? reinterpret_cast<void*>(1) : actions;
        field<void*>(windows[1], 0x1d8) = actions + 1;
    }
    if (cs->target == Skill && (!cs->present || (cs->id == 1000 && !cs->character)))
        field<void*>(windows[0], 0x1d8) = reinterpret_cast<void*>(1);
    setFlags(cs->flags);
    for (unsigned i = 0; i < 4; ++i)
        field<long long>(ui, guidOffsets[i]) = 0x1020304050607080LL + 0x100000001LL * i;
    field<bool>(ui, 0x12fb) = cs->handled;
    field<int>(ui, 0x12fc) = 13;
    field<bool>(ui, 0x1670) = !cs->handled;
    field<int>(ui, 0x1674) = -9876;
    field<int>(ui, 0x1678) = 7777;
    field<int>(ui, 0x167c) = -3333;
    field<unsigned>(ui, 0x1900) = 0xdead2468u;
    field<bool>(ui, 0x1998) = cs->handled;
    field<bool>(ui, 0x1999) = !cs->handled;
    KSETTINGS_TOGGLE_ITEM_NAME = cs->handled ? 0x80001000u : 0x13572468u;
}
void redirect(detour::Set& d)
{
    TL_REDIRECT(d, baseClickFn, &baseDispatch);
    TL_REDIRECT(d, lookupFn, &lookup);
    TL_REDIRECT(d, getIntFn, &getInt);
    TL_REDIRECT(d, setIntFn, &setInt);
    if (!cs->realClear) TL_REDIRECT(d, clearFn, &clear);
    d.redirect(childFn, childFn, &isChild);
    d.redirect(addFn, addFn, &addChild);
    d.redirect(positionFn, positionFn, &position);
    d.redirect(sizeFn, sizeFn, &size);
    d.redirect(setPositionFn, setPositionFn, &setPosition);
    d.redirect(setSizeFn, setSizeFn, &setSize);
    d.redirect(backFn, backFn, &back);
    d.redirect(frontFn, frontFn, &front);
}
void snapshot()
{
    n(blockCount);
    unsigned char bytes[0x4000];
    for (unsigned i = 0; i < blockCount; ++i) {
        Block& b = blocks[i];
        for (unsigned j = 0; j < 16; ++j) {
            if (b.start[j] != 0xd3 || b.start[16 + b.size + j] != 0x6c) invalid(100 + i);
        }
        std::memcpy(bytes, b.start + 16, b.size);
        for (unsigned j = 0; j < pointerCount; ++j) if (pointerFields[j].base == b.start + 16) {
            unsigned offset = pointerFields[j].offset;
            uintptr_t value = token(field<void*>(b.start + 16, offset));
            std::memcpy(bytes + offset, &value, sizeof(value));
        }
        n(b.size); cap->add(bytes, b.size);
        cap->add(b.start, 16); cap->add(b.start + 16 + b.size, 16);
    }
    n(KSETTINGS_TOGGLE_ITEM_NAME);
    for (unsigned i = 1; i <= NestedReturn; ++i) n(calls[i]);
    n(mutated); n(depth);
}
Target prepareStep(unsigned which)
{
    if (cs->sequence == 1) {
        // Item hit, then item miss: never reset UI flags or GUIDs between calls.
        mouseEvent->window = windows[0];
        guids[0] = guidValues[(cs->guid + which) % 4];
        return Skill;
    }
    if (cs->sequence == 2) return which ? Through : Skill;
    if (cs->sequence == 3) {
        if (which < 2) { mouseEvent->window = windows[which]; return Hover; }
        return Through;
    }
    if (cs->sequence == 4) {
        // A skill hover followed by an item miss preserves the old item GUID.
        mouseEvent->window = windows[0];
        field<unsigned>(windows[0], 0x170) = which ? 1000 : 999;
        guids[0] = guidValues[(cs->guid + which) % 4];
        return Skill;
    }
    return cs->target;
}
void side(void* context, autotest::Capture& out, bool candidate)
{
    cs = static_cast<Case*>(context); ours = candidate; cap = &out;
    initialize();
    detour::Set d; redirect(d);
    if (d.failed()) { out.issue = autotest::Capture::UnsupportedPointer; return; }
    autotest::Capture invocation;
    for (step = 0; step < cs->repeat; ++step) {
        Target target = prepareStep(step);
        const CEGUI::EventArgs* event = target == Names || target == Through ? plainEvent : mouseEvent;
        invocation.reset(); cap = &invocation; n(step); n(target);
        // Exceptional witnesses are a separate, uncounted suite. The normal
        // receipt remains incomplete if any invocation throws or fails.
        bool caught = false;
        try {
            autotest::invoke(invocation, handler(target), reinterpret_cast<CGameUI*>(ui), event);
        } catch (const CallbackFailure& failure) {
            caught = true; n(failure.boundary);
            if (!cs->fault || failure.boundary != cs->fault) invalid(3);
        } catch (...) { invalid(4); }
        n(caught);
        if (caught != (cs->fault != 0)) invalid(5);
        snapshot();
        cap = &out;
        if (!step) {
            out.callTarget = invocation.callTarget;
            out.callStarted = invocation.callStarted;
            out.callCompleted = invocation.callCompleted;
        } else {
            if (invocation.callStarted != 1 || invocation.callCompleted != 1) invalid(2);
            out.callCompleted = out.callCompleted && invocation.callCompleted;
        }
        if (invocation.issue) out.issue = invocation.issue;
        out.add(invocation.data, invocation.length);
    }
}
void oldSide(void* context, autotest::Capture& out) { side(context, out, false); }
void newSide(void* context, autotest::Capture& out) { side(context, out, true); }
bool pair(const tlhybrid_host* host, autotest::Coverage& coverage, Case& c, unsigned& count)
{
    autotest::Outcome a, b;
    autotest::runChild(oldSide, &c, a);
    autotest::runChild(newSide, &c, b);
    ++count;
    int receipt = coverage.observe(host, a, b);
    if (!receipt && a.reportValid && b.reportValid && !a.childStatus && !b.childStatus &&
        a.capture.callCompleted == 1 && b.capture.callCompleted == 1 &&
        !a.capture.issue && !b.capture.issue && a.capture.length == b.capture.length &&
        !std::memcmp(a.capture.data, b.capture.data, a.capture.length)) return true;
    size_t first = 0;
    while (first < a.capture.length && first < b.capture.length && a.capture.data[first] == b.capture.data[first]) ++first;
    host->log("    event #%u target=%u action=%d button=%d flags=%u id=%u guid=%u profile=%u at=%u "
              "geometry=%u sequence=%u repeat=%u present=%u actor=%u hit=%u result=%u handled=%u "
              "child=%u menu=%u real=%u exits=%d/%d valid=%u/%u issues=%u/%u complete=%u/%u "
              "bytes=%lu/%lu first=%lu\n",
              count, unsigned(c.target), c.action, c.button, c.flags, c.id, c.guid, c.profile, c.at,
              c.geometry, c.sequence, c.repeat, unsigned(c.present), unsigned(c.character), unsigned(c.hit),
              unsigned(c.result), unsigned(c.handled), unsigned(c.child), unsigned(c.menu), unsigned(c.realClear),
              a.childStatus, b.childStatus, unsigned(a.reportValid), unsigned(b.reportValid),
              a.capture.issue, b.capture.issue, a.capture.callCompleted, b.capture.callCompleted,
              (unsigned long)a.capture.length, (unsigned long)b.capture.length, (unsigned long)first);
    coverage.report(host); return false;
}
bool exceptionPair(const tlhybrid_host* host, Case& c)
{
    autotest::Outcome a, b;
    autotest::runChild(oldSide, &c, a);
    autotest::runChild(newSide, &c, b);
    bool clean = a.reportValid && b.reportValid && !a.childStatus && !b.childStatus &&
        !a.capture.issue && !b.capture.issue && a.capture.callStarted == 1 && b.capture.callStarted == 1 &&
        a.capture.callCompleted == 0 && b.capture.callCompleted == 0 &&
        a.capture.callTarget == (uint64_t)(uintptr_t)&originalHover &&
        host->comparison_pair && host->comparison_pair(a.capture.callTarget, b.capture.callTarget) &&
        a.capture.length == b.capture.length &&
        !std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    if (!clean) host->log("    event exception boundary=%u exits=%d/%d valid=%u/%u issues=%u/%u complete=%u/%u\n",
                         c.fault, a.childStatus, b.childStatus, unsigned(a.reportValid), unsigned(b.reportValid),
                         a.capture.issue, b.capture.issue, a.capture.callCompleted, b.capture.callCompleted);
    // Never call Coverage::observe here: an exception is not a completed pair.
    return clean;
}
int finish(const tlhybrid_host* host, autotest::Coverage& coverage, unsigned count, unsigned expected)
{
    coverage.report(host);
    return count != expected || coverage.completed != expected || coverage.completed < 20 ||
           coverage.different || coverage.missing;
}
} // namespace

TL_TEST(gameui_event_click_dispatch)
{
    autotest::Coverage coverage("gameui_event_click_dispatch", (uint64_t)(uintptr_t)&originalClick);
    unsigned count = 0;
    // 64 guard/result/handled cases, including all named buttons and -1.
    for (unsigned button = 0; button < 8; ++button)
        for (unsigned bits = 0; bits < 8; ++bits) {
            Case c(Click); c.button = button == 7 ? -1 : int(button);
            c.present = bits & 1; c.result = bits & 2; c.handled = bits & 4;
            c.action = -987654321; c.id = 12345 + button; c.flags = bits * 4;
            if (!pair(host, coverage, c, count)) return 1;
        }
    const int actionsToTest[] = {-1, 0, 11, 81, 95, INT_MIN, INT_MAX};
    for (unsigned i = 0; i < 7; ++i) for (unsigned bits = 0; bits < 4; ++bits) {
        Case c(Click); c.action = actionsToTest[i]; c.id = i + 4000;
        c.result = bits & 1; c.handled = bits & 2;
        if (!pair(host, coverage, c, count)) return 1;
    }
    for (unsigned i = 0; i < 4; ++i) {
        Case c(Click); c.profile = i / 2 + 1; c.result = i & 1;
        c.action = i & 1 ? INT_MIN : INT_MAX;
        if (!pair(host, coverage, c, count)) return 1;
    }
    return finish(host, coverage, count, 96);
}
TL_TEST(gameui_event_skill_hover)
{
    autotest::Coverage coverage("gameui_event_skill_hover", (uint64_t)(uintptr_t)&originalSkill);
    unsigned count = 0;
    for (unsigned i = 0; i < 8; ++i) {
        Case c(Skill); c.present = false; c.character = i & 1; c.flags = i * 4; c.handled = i & 2;
        if (!pair(host, coverage, c, count)) return 1;
        c.present = true; c.character = false;
        if (!pair(host, coverage, c, count)) return 1;
    }
    const unsigned ids[] = {0, 999, 1001, UINT_MAX};
    for (unsigned i = 0; i < 4; ++i) for (unsigned guid = 0; guid < 4; ++guid)
        for (unsigned handled = 0; handled < 2; ++handled) {
            Case c(Skill); c.id = ids[i]; c.guid = guid; c.handled = handled;
            c.character = !handled; c.flags = (i * 7 + guid * 3) % 32;
            if (!pair(host, coverage, c, count)) return 1;
        }
    // Every lookup profile runs for hit and miss, with prior item flag both
    // false and true, using all four 64-bit boundary GUIDs.
    for (unsigned guid = 0; guid < 4; ++guid) for (unsigned hit = 0; hit < 2; ++hit)
        for (unsigned profile = 0; profile < 7; ++profile) for (unsigned old = 0; old < 2; ++old) {
            Case c(Skill); c.guid = guid; c.hit = hit; c.profile = profile;
            c.flags = old ? 31 : 21; c.handled = old;
            if (!pair(host, coverage, c, count)) return 1;
        }
    for (unsigned i = 0; i < 8; ++i) {
        Case c(Skill); c.sequence = i < 4 ? 1 : (i < 6 ? 4 : 2); c.repeat = 2;
        c.guid = i % 4; c.flags = 31; c.hit = c.sequence == 2;
        if (!pair(host, coverage, c, count)) return 1;
    }
    return finish(host, coverage, count, 168);
}
TL_TEST(gameui_event_item_names)
{
    autotest::Coverage coverage("gameui_event_item_names", (uint64_t)(uintptr_t)&originalNames);
    unsigned count = 0;
    const int values[] = {0, 1, -1, 2, INT_MIN, INT_MAX};
    for (unsigned i = 0; i < 6; ++i) for (unsigned profile = 0; profile < 4; ++profile)
        for (unsigned handled = 0; handled < 2; ++handled) {
            Case c(Names); c.setting = values[i]; c.profile = profile; c.handled = handled;
            c.present = false; c.flags = (i * 5 + profile) % 32;
            if (!pair(host, coverage, c, count)) return 1;
        }
    return finish(host, coverage, count, 48);
}
TL_TEST(gameui_event_slot_hover)
{
    autotest::Coverage coverage("gameui_event_slot_hover", (uint64_t)(uintptr_t)&originalHover);
    unsigned count = 0;
    const unsigned boundaries[] = {IsChild, AddChild, GetPosition, SetPosition, GetSize, SetSize, MoveBack};
    for (unsigned at = 0; at < 7; ++at) for (unsigned profile = 1; profile <= 3; ++profile)
        for (unsigned child = 0; child < 2; ++child) for (unsigned geometry = 0; geometry < 4; ++geometry) {
            Case c(Hover); c.at = boundaries[at]; c.profile = profile;
            c.child = child; c.geometry = geometry; c.flags = geometry * 8; c.handled = geometry & 1;
            if (!pair(host, coverage, c, count)) return 1;
        }
    for (unsigned geometry = 0; geometry < 4; ++geometry) for (unsigned child = 0; child < 2; ++child)
        for (unsigned repeated = 0; repeated < 2; ++repeated) {
            Case c(Hover); c.geometry = geometry; c.child = child; c.repeat = repeated + 1;
            c.flags = 31 - geometry * 8;
            if (!pair(host, coverage, c, count)) return 1;
        }
    for (unsigned i = 0; i < 8; ++i) {
        Case c(Hover); c.present = false; c.flags = i * 4; c.handled = i & 1;
        if (!pair(host, coverage, c, count)) return 1;
    }
    for (unsigned i = 0; i < 4; ++i) {
        Case c(Hover); c.sequence = 3; c.repeat = 3; c.geometry = i;
        c.flags = i & 1 ? 31 : 0; c.child = i & 2;
        if (!pair(host, coverage, c, count)) return 1;
    }
    if (finish(host, coverage, count, 196)) return 1;
    for (unsigned i = 0; i < 7; ++i) {
        Case c(Hover); c.fault = boundaries[i]; c.geometry = i % 4;
        if (!exceptionPair(host, c)) return 1;
    }
    host->log("    gameui_event_slot_hover exception propagation 7 matched (excluded from normal receipts)\n");
    return 0;
}
TL_TEST(gameui_event_mouse_through)
{
    autotest::Coverage coverage("gameui_event_mouse_through", (uint64_t)(uintptr_t)&originalThrough);
    unsigned count = 0;
    for (unsigned flags = 0; flags < 32; ++flags) for (unsigned menu = 0; menu < 2; ++menu) {
        Case c(Through); c.flags = flags; c.menu = menu; c.handled = flags & 1;
        if (!pair(host, coverage, c, count)) return 1;
    }
    for (unsigned profile = 1; profile <= 4; ++profile) for (unsigned i = 0; i < 4; ++i) {
        Case c(Through); c.profile = profile; c.flags = i * 10; c.handled = i & 1;
        if (!pair(host, coverage, c, count)) return 1;
    }
    for (unsigned i = 0; i < 4; ++i) {
        // The first call remains MouseThrough for this target's exact receipt.
        Case c(Through); c.repeat = 2; c.profile = 3; c.flags = i * 10;
        if (!pair(host, coverage, c, count)) return 1;
        c.repeat = 1; c.profile = 0; c.realClear = true; c.flags = 31 - i * 10;
        if (!pair(host, coverage, c, count)) return 1;
    }
    return finish(host, coverage, count, 88);
}
