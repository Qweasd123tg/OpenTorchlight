#include <climits>
#include <cstring>
#include <cwchar>
#include <string>
#include "GameUI.h"
#include "Settings.h"
#include "AutoTest.h"
#include "Detour.h"

// Original callback adapter/consumer use AL: this is a bool, not a guessed
// 64-bit return. Only collaborators are detoured; both target entries run.
TL_ORIGINAL(bool, originalClick, (CGameUI*, ELayoutFunction),
            "_ZN7CGameUI7onClickE15ELayoutFunction")
extern "C" bool recoveredClick(CGameUI*, ELayoutFunction)
    __asm__("_ZN7CGameUI7onClickE15ELayoutFunction");

TL_FUNCTION(pauseCall, "_ZN7CGameUI11togglePauseEv")
TL_FUNCTION(inventoryCall, "_ZN7CGameUI15toggleInventoryEv")
TL_FUNCTION(questCall, "_ZN7CGameUI11toggleQuestEv")
TL_FUNCTION(statsCall, "_ZN7CGameUI11toggleStatsEv")
TL_FUNCTION(skillCall, "_ZN7CGameUI11toggleSkillEv")
TL_FUNCTION(journalCall, "_ZN7CGameUI13toggleJournalEv")
TL_FUNCTION(petCall, "_ZN7CGameUI9togglePetEv")
TL_FUNCTION(optionsCall, "_ZN7CGameUI13toggleOptionsEv")
TL_FUNCTION(automapCall, "_ZN6CLevel13toggleAutomapEv")
TL_FUNCTION(zoomCall, "_ZN6CLevel11zoomAutomapEf")
TL_FUNCTION(getIntCall, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(setIntCall, "_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(targetCall, "_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(usableCall, "_ZN5CItem9isUseableEv")
TL_FUNCTION(itemUseCall, "_ZN7CGameUI14performItemUseER6CLevelP10CEquipmentP10CCharacterS5_S5_")
TL_FUNCTION(returnDragCall, "_ZN7CGameUI17returnDraggedItemEv")
TL_FUNCTION(playCall, "_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(queueCall, "_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(modalPartialCall, "_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(closeLeftCall, "_ZN7CGameUI9closeLeftEv")
TL_FUNCTION(closeRightCall, "_ZN7CGameUI10closeRightEv")
TL_FUNCTION(nearDeathCall, "_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(aliveCall, "_ZN10CCharacter5aliveEv")
TL_FUNCTION(sendTownCall, "_ZN10CCharacter10sendToTownER6CLevel")
TL_FUNCTION(translatorCall, "_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateCall, "_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(modalCall, "_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
extern "C" char moveFrontLinked[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");

namespace {

enum Flags {
    NullLevel = 1, Paused = 2, ModalOpen = 4, AlreadyConsumed = 8,
    DepartureAllowed = 16, PortalAllowed = 32, Town = 64, NoActorSound = 128
};

enum Mutation {
    Unchanged,
    ToggleCreatesFirstDrag, ToggleCreatesSecondDrag,
    UsableClearsFollowers, UsableReplacesFollower, UsableSwapsActor,
    UsableSwapsToEmptyActor, UsableReplacesDrag, UsableClearsDrag,
    UsableSwapsLevel, UsableBlocksCachedPet, UsableBlocksNewPet,
    PlayClearsDrag, PlayReplacesDrag, PlaySwapsActor,
    PlaySwapsToSilentActor, QueueClearsDrag, QueueReplacesDrag,
    QueueSwapsLevel, ModalSwapsMenus, PartialSwapsMenus, CloseSwapsMenus,
    SetSwapsToPositiveActor, SetSwapsToZeroActor, SetOpensOtherMenu,
    SetClosesOtherMenu, SetSwapsOtherMenu, GetSwapsSettings, GetChangesKey,
    NearSwapsActor, NearReplacesFollower, NearBlocksPet, AliveBlocksPet,
    AliveSwapsLevel, TargetRewritesModes, PerformChangesIcon,
    ReturnChangesIcon, PlayChangesIcon, QueueChangesIcon,
    PartialChangesPoints, SetMakesPointsNegative, UsableNullsCurrentFollower
};

struct Case {
    int event, petState, statPoints, skillPoints, setting;
    unsigned flags, followers, dragged, mutation, performed, returned;
    unsigned translation, repeat, sequence, fault;
    bool usable, nearDeath, alive;
    unsigned menuStates;
    Case(int id = 0)
        : event(id), petState(40), statPoints(1), skillPoints(1), setting(0),
          flags(DepartureAllowed), followers(2), dragged(0), mutation(Unchanged),
          performed(0), returned(0), translation(0), repeat(1), sequence(0),
          fault(0), usable(true), nearDeath(false), alive(true), menuStates(0) {}
};

enum Trace {
    Pause = 1, Inventory, Quest, Stats, Skills, Journal, Pet, Options,
    Automap, Zoom, GetInt, SetInt, Target, Usable, Perform, ReturnDrag,
    Play, Queue, ModalPartial, CloseLeft, CloseRight, PartialSlot5,
    SetOpenSlot8, NearDeath, Alive, SendTown, Translator, Translate,
    Modal, MoveFront
};

struct Stop {};
struct Block { unsigned char* start; unsigned size; };
Block blocks[48];
unsigned blockCount, calls[32], translations[2], iteration;
bool faultFired;
const Case* current;
autotest::Capture* capture;
void* ui;
void* actors[2];
void* pets[2];
void* levels[2];
void* templates[2];
void* settings[2];
void* equipment[2];
void* icons[3];
void* sounds[3];
void* nodes[2];
void* menus[4]; // stats, skills, alternate stats, alternate skills
void* translatorObject;
void** followerArrays[2];
void* menuVtable[16];

template<class T> T& field(void* object, unsigned offset)
{
    return *reinterpret_cast<T*>(static_cast<char*>(object) + offset);
}

void number(int value) { capture->add(&value, sizeof(value)); }
void scalar(float value) { capture->add(&value, sizeof(value)); }
void pointer(const void* value) { capture->addPointer(value); }

void require(bool condition, unsigned reason)
{
    if (!condition) {
        number(0x6bad0000 | reason);
        capture->issue = autotest::Capture::InvalidReport;
    }
}

void* object(unsigned bytes)
{
    if (blockCount == sizeof(blocks) / sizeof(blocks[0])) _exit(70);
    unsigned char* p = static_cast<unsigned char*>(autotest::allocate(bytes + 32));
    if (!p) _exit(71);
    std::memset(p, 0xd3, 16);
    std::memset(p + 16, 0xa5, bytes);
    std::memset(p + 16 + bytes, 0x6c, 16);
    blocks[blockCount].start = p;
    blocks[blockCount++].size = bytes;
    return p + 16;
}

void guards()
{
    for (unsigned i = 0; i < blockCount; ++i)
        for (unsigned j = 0; j < 16; ++j) {
            require(blocks[i].start[j] == 0xd3, 100 + i);
            require(blocks[i].start[16 + blocks[i].size + j] == 0x6c, 200 + i);
        }
}

void trace(unsigned code, void* self)
{
    ++calls[code];
    number(code);
    pointer(self);
    // This also proves consumption is stored before any callback.
    number(field<bool>(ui, 0x1998));
}

void drag(void* item) { field<void*>(ui, 0xb8) = item; }

void followers(unsigned actor, unsigned kind)
{
    void** data = followerArrays[actor];
    data[0] = kind == 3 ? 0 : pets[actor];
    data[1] = pets[1 - actor];
    unsigned count = kind == 3 ? 2 : kind;
    field<void**>(actors[actor], 0x648) = count ? data : 0;
    field<void**>(actors[actor], 0x650) = count ? data + count : 0;
    field<void**>(actors[actor], 0x658) = count ? data + 2 : 0;
}

void changeDrag(unsigned mode)
{
    if (mode == 1) drag(0);
    if (mode == 2) drag(equipment[1]);
}

unsigned menuIndex(void* p)
{
    for (unsigned i = 0; i < 4; ++i) if (menus[i] == p) return i;
    _exit(72);
}

bool& menuOpen(void* p)
{
    return field<bool>(p, (menuIndex(p) & 1) ? 0x38 : 0x68);
}

void unexpectedSlot(void*) { _exit(73); }
void pause(void* p) { trace(Pause, p); }
void inventory(void* p) { trace(Inventory, p); }
void quest(void* p) { trace(Quest, p); }
void stats(void* p) { trace(Stats, p); }
void skills(void* p) { trace(Skills, p); }
void journal(void* p) { trace(Journal, p); }
void options(void* p) { trace(Options, p); }

void pet(void* p)
{
    trace(Pet, p);
    if (current->mutation == ToggleCreatesFirstDrag) drag(equipment[0]);
    if (current->mutation == ToggleCreatesSecondDrag) drag(equipment[1]);
}

void automap(void* p) { trace(Automap, p); }
void zoom(void* p, float amount) { trace(Zoom, p); scalar(amount); }

int getInt(void* p, unsigned key)
{
    trace(GetInt, p); number(key);
    if (current->mutation == GetSwapsSettings) field<void*>(ui, 0x78) = settings[1];
    if (current->mutation == GetChangesKey) KSETTINGS_TOGGLE_ITEM_NAME = 0x8192u;
    return current->setting;
}

void setInt(void* p, unsigned key, int value)
{
    trace(SetInt, p); number(key); number(value);
    field<int>(p, 0x10) = value;
}

void setTarget(void* p, void* target)
{
    trace(Target, p); pointer(target);
    number(field<int>(ui, 0x16c8)); number(field<int>(p, 0x710));
    require(target == 0, 1);
    require(field<int>(ui, 0x16c8) == current->event - 69, 2);
    require(field<int>(p, 0x710) == current->event - 69, 3);
    if (current->mutation == TargetRewritesModes) {
        field<int>(ui, 0x16c8) = -123;
        field<int>(p, 0x710) = 876;
        followers(0, 0);
    }
}

bool usable(void* p)
{
    trace(Usable, p);
    switch (current->mutation) {
    case UsableClearsFollowers: followers(0, 0); break;
    case UsableReplacesFollower: followerArrays[0][0] = pets[1]; break;
    case UsableSwapsActor: field<void*>(ui, 0x38) = actors[1]; break;
    case UsableSwapsToEmptyActor:
        followers(1, 0); field<void*>(ui, 0x38) = actors[1]; break;
    case UsableReplacesDrag: drag(equipment[1]); break;
    case UsableClearsDrag: drag(0); break;
    case UsableSwapsLevel: field<void*>(ui, 0x40) = levels[1]; break;
    case UsableBlocksCachedPet: field<int>(pets[0], 0x330) = 41; break;
    case UsableBlocksNewPet:
        followerArrays[0][0] = pets[1]; field<int>(pets[1], 0x330) = 42; break;
    case UsableNullsCurrentFollower: followerArrays[0][0] = 0; break;
    default: break;
    }
    return current->usable;
}

void perform(void* p, void* level, void* item, void* source, void* owner, void* target)
{
    trace(Perform, p); pointer(level); pointer(item);
    pointer(source); pointer(owner); pointer(target);
    require(source == field<void*>(ui, 0x38), 4);
    require(owner == source, 5);
    require(item == field<void*>(ui, 0xb8), 6);
    require(level == field<void*>(ui, 0x40), 7);
    require(target == *field<void**>(source, 0x648), 8);
    changeDrag(current->performed);
    if (current->mutation == PerformChangesIcon)
        field<void*>(equipment[0], 0x2c8) = icons[2];
}

void returnDragged(void* p)
{
    trace(ReturnDrag, p); pointer(field<void*>(ui, 0xb8));
    changeDrag(current->returned);
    if (current->mutation == ReturnChangesIcon)
        field<void*>(equipment[0], 0x2c8) = icons[2];
}

void play(void* p, int sample, void* node, float a, float b, bool flag)
{
    trace(Play, p); number(sample); pointer(node); scalar(a); scalar(b); number(flag);
    require(sample == 24 && a == 0.f && b == 0.f && !flag, 9);
    if (current->mutation == PlayClearsDrag) drag(0);
    if (current->mutation == PlayReplacesDrag) drag(equipment[1]);
    if (current->mutation == PlaySwapsActor || current->mutation == PlaySwapsToSilentActor)
        field<void*>(ui, 0x38) = actors[1];
    if (current->mutation == PlaySwapsToSilentActor) field<void*>(actors[1], 0x298) = 0;
    if (current->mutation == PlayChangesIcon)
        field<void*>(equipment[0], 0x2c8) = icons[2];
}

void queue(void* p, int sample, float a, float b)
{
    trace(Queue, p); number(sample); scalar(a); scalar(b);
    require(sample == (current->event == 95 ? 43 : 49), 10);
    require(a == 0.f && b == 0.1f, 11);
    if (current->mutation == QueueClearsDrag) drag(0);
    if (current->mutation == QueueReplacesDrag) drag(equipment[1]);
    if (current->mutation == QueueSwapsLevel) {
        field<void*>(ui, 0x40) = levels[1];
        followerArrays[0][0] = pets[1];
    }
    if (current->mutation == QueueChangesIcon)
        field<void*>(equipment[0], 0x2c8) = icons[2];
}

bool modalPartial(void* p)
{
    trace(ModalPartial, p);
    if (current->mutation == ModalSwapsMenus) {
        field<void*>(ui, 0x4e0) = menus[2];
        field<void*>(ui, 0x558) = menus[3];
    }
    return (current->flags & ModalOpen) != 0;
}

bool partial(void* p)
{
    trace(PartialSlot5, p);
    bool result = menuOpen(p);
    number(result);
    if (current->mutation == PartialSwapsMenus) {
        field<void*>(ui, 0x4e0) = menus[2];
        field<void*>(ui, 0x558) = menus[3];
    }
    if (current->mutation == PartialChangesPoints) {
        field<int>(actors[0], 0x45c) = 1;
        field<int>(actors[0], 0x460) = 1;
    }
    return result;
}

void closeLeft(void* p)
{
    trace(CloseLeft, p);
    if (current->mutation == CloseSwapsMenus) field<void*>(ui, 0x4e0) = menus[2];
}

void closeRight(void* p)
{
    trace(CloseRight, p);
    if (current->mutation == CloseSwapsMenus) field<void*>(ui, 0x558) = menus[3];
}

void setOpen(void* p, bool value)
{
    trace(SetOpenSlot8, p); number(value);
    require(value, 12);
    menuOpen(p) = value;
    unsigned other = (menuIndex(p) & 1) ? 0 : 1;
    if (current->mutation == SetSwapsToPositiveActor || current->mutation == SetSwapsToZeroActor) {
        int points = current->mutation == SetSwapsToPositiveActor ? 3 : 0;
        field<int>(actors[1], 0x45c) = points;
        field<int>(actors[1], 0x460) = points;
        field<void*>(ui, 0x38) = actors[1];
    }
    if (current->mutation == SetOpensOtherMenu) menuOpen(menus[other]) = true;
    if (current->mutation == SetClosesOtherMenu) menuOpen(menus[other]) = false;
    if (current->mutation == SetSwapsOtherMenu)
        field<void*>(ui, other ? 0x558 : 0x4e0) = menus[other + 2];
    if (current->mutation == SetMakesPointsNegative) {
        field<int>(actors[0], 0x45c) = -1;
        field<int>(actors[0], 0x460) = -1;
    }
}

bool nearDeath(void* p)
{
    trace(NearDeath, p);
    if (current->mutation == NearSwapsActor) field<void*>(ui, 0x38) = actors[1];
    if (current->mutation == NearReplacesFollower) followerArrays[0][0] = pets[1];
    if (current->mutation == NearBlocksPet) field<int>(p, 0x330) = 42;
    return current->nearDeath;
}

bool alive(void* p)
{
    trace(Alive, p);
    if (current->mutation == AliveBlocksPet) field<int>(p, 0x330) = 41;
    if (current->mutation == AliveSwapsLevel) field<void*>(ui, 0x40) = levels[1];
    return current->alive;
}

void sendTown(void* p, void* level)
{
    trace(SendTown, p); pointer(level);
    require(p == pets[0], 13);
    require(level == field<void*>(ui, 0x40), 14);
    field<int>(p, 0x330) = 42;
}

void* translator()
{
    trace(Translator, translatorObject);
    return translatorObject;
}

std::wstring translationValue(unsigned which, unsigned count)
{
    unsigned mode = current->translation;
    bool empty = (mode == 1 && which == 0 && count == 1) ||
                 (mode == 2 && which == 1 && count == 1) ||
                 (mode == 3 && count == 1) ||
                 (mode == 4 && which == 0) || (mode == 5 && which == 1) || mode == 6;
    if (empty) return L"";
    if (mode == 7)
        return which ? std::wstring(L"body\0\x96ea\x1f63a", 7)
                     : std::wstring(L"pet\0\x03a9", 5);
    return which ? L"translated: \x041f\x0451\x0441 \x96ea \x1f63a!"
                 : L"translated: \x03a9 pet";
}

std::wstring translate(void* p, const wchar_t* source)
{
    trace(Translate, p);
    std::wstring input(source);
    capture->addText(input);
    unsigned which;
    if (input == L"Pet") which = 0;
    else if (input == L"Your pet cannot depart from here!") which = 1;
    else { require(false, 15); return L"wrong original literal"; }
    ++translations[which];
    number(which); number(translations[which]);
    if (!faultFired && current->fault == which + 1) { faultFired = true; throw Stop(); }
    return translationValue(which, translations[which]);
}

void modal(void* p, std::wstring title, std::wstring body, bool flag)
{
    trace(Modal, p); capture->addText(title); capture->addText(body); number(flag);
    require(!flag, 16);
    if (!faultFired && current->fault == 3) { faultFired = true; throw Stop(); }
    // The public method takes values. These writes must not corrupt either cache.
    title.assign(L"mutated modal copy");
    body.assign(L"different modal copy");
}

void moveFront(void* p) { trace(MoveFront, p); }

void initialize(const Case& c)
{
    autotest::g_arenaUsed = 0;
    blockCount = 0;
    std::memset(calls, 0, sizeof(calls));
    translations[0] = translations[1] = 0;
    faultFired = false;
    ui = object(0x1a08);
    for (unsigned i = 0; i < 2; ++i) {
        actors[i] = object(0x800); pets[i] = object(0x800);
        levels[i] = object(0x300); templates[i] = object(0xa0);
        settings[i] = object(0x40); equipment[i] = object(0x400);
        nodes[i] = object(0x40);
        followerArrays[i] = static_cast<void**>(object(2 * sizeof(void*)));
    }
    for (unsigned i = 0; i < 3; ++i) { sounds[i] = object(0x40); icons[i] = object(0x40); }
    for (unsigned i = 0; i < 4; ++i) menus[i] = object(0x100);
    translatorObject = object(0x40);
    for (unsigned i = 0; i < 16; ++i) menuVtable[i] = reinterpret_cast<void*>(&unexpectedSlot);
    menuVtable[5] = reinterpret_cast<void*>(&partial);
    menuVtable[8] = reinterpret_cast<void*>(&setOpen);
    for (unsigned i = 0; i < 4; ++i) {
        field<void*>(menus[i], 0) = menuVtable;
        menuOpen(menus[i]) = (c.menuStates & (1U << i)) != 0;
    }
    for (unsigned i = 0; i < 2; ++i) {
        field<void*>(actors[i], 0x58) = nodes[i];
        field<void*>(actors[i], 0x298) = c.flags & NoActorSound ? 0 : sounds[i + 1];
        field<int>(actors[i], 0x45c) = c.statPoints;
        field<int>(actors[i], 0x460) = c.skillPoints;
        field<int>(pets[i], 0x330) = i ? 43 : c.petState;
        field<int>(pets[i], 0x710) = 0x24681357 + i;
        field<void*>(levels[i], 0x1d8) = templates[i];
        field<bool>(templates[i], 0x84) = (c.flags & PortalAllowed) != 0;
        field<bool>(templates[i], 0x85) = (c.flags & DepartureAllowed) != 0;
        field<bool>(templates[i], 0x86) = (c.flags & Town) != 0;
        field<void*>(equipment[i], 0x2c8) = icons[i];
        field<int>(settings[i], 0x10) = 73 + i;
    }
    followers(0, c.followers); followers(1, 2);
    field<void*>(ui, 0x38) = actors[0];
    field<void*>(ui, 0x40) = c.flags & NullLevel ? 0 : levels[0];
    field<void*>(ui, 0x78) = settings[0];
    field<void*>(ui, 0x4e0) = menus[0]; field<void*>(ui, 0x558) = menus[1];
    field<void*>(ui, 0x16a8) = sounds[0];
    field<int>(ui, 0x16c8) = -2468;
    field<bool>(ui, 0x1998) = (c.flags & AlreadyConsumed) != 0;
    field<bool>(ui, 0x1999) = (c.flags & Paused) != 0;
    drag(c.dragged ? equipment[c.dragged - 1] : 0);
    KSETTINGS_TOGGLE_ITEM_NAME = 0x3819u;
}

void redirect(detour::Set& d)
{
    TL_REDIRECT(d, pauseCall, &pause); TL_REDIRECT(d, inventoryCall, &inventory);
    TL_REDIRECT(d, questCall, &quest); TL_REDIRECT(d, statsCall, &stats);
    TL_REDIRECT(d, skillCall, &skills); TL_REDIRECT(d, journalCall, &journal);
    TL_REDIRECT(d, petCall, &pet); TL_REDIRECT(d, optionsCall, &options);
    TL_REDIRECT(d, automapCall, &automap); TL_REDIRECT(d, zoomCall, &zoom);
    TL_REDIRECT(d, getIntCall, &getInt); TL_REDIRECT(d, setIntCall, &setInt);
    TL_REDIRECT(d, targetCall, &setTarget); TL_REDIRECT(d, usableCall, &usable);
    TL_REDIRECT(d, itemUseCall, &perform); TL_REDIRECT(d, returnDragCall, &returnDragged);
    TL_REDIRECT(d, playCall, &play); TL_REDIRECT(d, queueCall, &queue);
    TL_REDIRECT(d, modalPartialCall, &modalPartial);
    TL_REDIRECT(d, closeLeftCall, &closeLeft); TL_REDIRECT(d, closeRightCall, &closeRight);
    TL_REDIRECT(d, nearDeathCall, &nearDeath); TL_REDIRECT(d, aliveCall, &alive);
    TL_REDIRECT(d, sendTownCall, &sendTown); TL_REDIRECT(d, translatorCall, &translator);
    TL_REDIRECT(d, translateCall, &translate); TL_REDIRECT(d, modalCall, &modal);
    d.redirect(moveFrontLinked, moveFrontLinked, &moveFront);
}

bool consumes(int event)
{
    return (event >= 68 && event <= 71) || (event >= 82 && event <= 86) || event == 95;
}

int eventForIteration()
{
    if (current->sequence == 1) { // Eligible, then denied: no eager translation.
        field<bool>(templates[0], 0x85) = iteration == 0;
        field<int>(pets[0], 0x330) = 40;
    } else if (current->sequence == 2) { // Denied, eligible, denied: retain caches.
        field<bool>(templates[0], 0x85) = iteration == 1;
        field<int>(pets[0], 0x330) = 40;
    } else if (current->sequence == 3) { // No pet first; later pet uses cold caches.
        followers(0, iteration ? 2 : 0);
    } else if (current->sequence == 4 && iteration == 0) {
        return 94;
    }
    return current->event;
}

void snapshot()
{
    // Every payload byte was initialized. Object/vtable pointers have the same
    // identity across children; no heap strings or uninitialized padding appear.
    guards(); number(blockCount);
    for (unsigned i = 0; i < blockCount; ++i) {
        number(blocks[i].size);
        capture->add(blocks[i].start + 16, blocks[i].size);
    }
    number(KSETTINGS_TOGGLE_ITEM_NAME);
    for (unsigned i = 1; i <= MoveFront; ++i) number(calls[i]);
    number(translations[0]); number(translations[1]); number(faultFired);
}

void side(void* context, autotest::Capture& out, bool ours)
{
    current = static_cast<Case*>(context);
    capture = &out;
    initialize(*current);
    detour::Set d; redirect(d);
    if (d.failed()) { out.issue = autotest::Capture::UnsupportedPointer; return; }

    // Each call, including a warm-cache call and a retry after an exception,
    // has its own invoke receipt. The case receipt is complete only if all are.
    autotest::Capture invocation;
    bool expectedEmpty[2] = {true, true};
    unsigned expectedTranslations[2] = {0, 0};
    for (iteration = 0; iteration < current->repeat; ++iteration) {
        int event = eventForIteration();
        bool consumedBefore = field<bool>(ui, 0x1998);
        void** begin = field<void**>(field<void*>(ui, 0x38), 0x648);
        void** end = field<void**>(field<void*>(ui, 0x38), 0x650);
        bool warning = event == 95 && begin != end && *begin &&
                       !field<bool>(templates[0], 0x85);
        unsigned previousModals = calls[Modal];
        invocation.reset(); capture = &invocation;
        number(iteration); number(event);
        bool threw = false;
        try {
            autotest::invoke(invocation, ours ? &recoveredClick : &originalClick,
                             reinterpret_cast<CGameUI*>(ui), static_cast<ELayoutFunction>(event));
        } catch (const Stop&) { threw = true; }
        catch (...) { _exit(74); }
        if (!threw) {
            require(invocation.callCompleted && invocation.length &&
                    static_cast<unsigned char>(invocation.data[invocation.length - 1]) == 1, 17);
        }
        require(threw == (current->fault != 0 && iteration == 0), 18);
        require(field<bool>(ui, 0x1998) == (consumedBefore || consumes(event)), 19);
        guards(); number(threw);
        // Independent emptiness oracle, beyond differential matching. Both
        // cache entries retry independently, including repeated empty results.
        if (!current->fault) {
            if (warning) for (unsigned which = 0; which < 2; ++which)
                if (expectedEmpty[which]) {
                    ++expectedTranslations[which];
                    expectedEmpty[which] = translationValue(which, expectedTranslations[which]).empty();
                }
            require(translations[0] == expectedTranslations[0], 20);
            require(translations[1] == expectedTranslations[1], 21);
            require(calls[Modal] == previousModals + (warning ? 1 : 0), 22);
        }
        capture = &out;
        if (iteration == 0) {
            out.callTarget = invocation.callTarget;
            out.callStarted = invocation.callStarted;
            out.callCompleted = invocation.callCompleted;
        } else {
            require(invocation.callTarget == out.callTarget && invocation.callStarted == 1, 23);
            out.callCompleted = out.callCompleted && invocation.callCompleted;
        }
        if (invocation.issue) out.issue = invocation.issue;
        out.add(invocation.data, invocation.length);
    }
    capture = &out;
    snapshot();
    // COW warning strings and by-value modal temporaries must also unwind cleanly.
    if (current->fault) out.addHeapInUse();
}

void oldSide(void* p, autotest::Capture& out) { side(p, out, false); }
void newSide(void* p, autotest::Capture& out) { side(p, out, true); }

void diagnostic(const tlhybrid_host* host, const Case& c, const char* group,
                unsigned index, const autotest::Outcome& a, const autotest::Outcome& b)
{
    size_t first = 0;
    while (first < a.capture.length && first < b.capture.length &&
           a.capture.data[first] == b.capture.data[first]) ++first;
    host->log("    click %s #%u event=%d flags=%u followers=%u drag=%u state=%d "
              "menus=%u points=%d/%d mutation=%u use/return=%u/%u cache=%u sequence=%u fault=%u "
              "exits=%d/%d issues=%u/%u completed=%u/%u bytes=%lu/%lu first=%lu\n",
              group, index, c.event, c.flags, c.followers, c.dragged, c.petState,
              c.menuStates, c.statPoints, c.skillPoints, c.mutation, c.performed, c.returned,
              c.translation, c.sequence, c.fault, a.childStatus, b.childStatus,
              a.capture.issue, b.capture.issue, a.capture.callCompleted, b.capture.callCompleted,
              (unsigned long)a.capture.length, (unsigned long)b.capture.length, (unsigned long)first);
}

bool pair(const tlhybrid_host* host, autotest::Coverage& coverage, Case& c,
          const char* group, unsigned& count)
{
    autotest::Outcome a, b;
    autotest::runChild(oldSide, &c, a); autotest::runChild(newSide, &c, b);
    ++count;
    if (coverage.observe(host, a, b) || a.childStatus || b.childStatus ||
        !a.reportValid || !b.reportValid || !a.capture.callCompleted || !b.capture.callCompleted) {
        diagnostic(host, c, group, count, a, b); return false;
    }
    return true;
}

} // namespace

TL_TEST(gameui_click_dispatch_regression)
{
    autotest::Coverage coverage("gameui_click_dispatch_regression",
                               static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&originalClick)));
    unsigned count = 0;
#define CLICK_PAIR(label) do { if (!pair(host, coverage, c, label, count)) { coverage.report(host); return 1; } } while (0)

    // Full table plus both unsigned-dispatch boundaries; defaults still have a
    // valid actor because the original reads followers before dispatching.
    for (int event = -2; event <= 97; ++event)
        for (unsigned variant = 0; variant < 4; ++variant) {
            Case c(event); c.followers = variant & 1 ? 2 : 0;
            if (variant & 2) c.flags |= AlreadyConsumed;
            CLICK_PAIR("dispatch");
        }
    const int invalid[] = {INT_MIN, INT_MAX, -100, 0x10000, 0x10044, 0x1005f};
    for (unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
        Case c(invalid[i]); CLICK_PAIR("invalid-id");
    }

    for (int event = 69; event <= 71; ++event)
        for (unsigned petsPresent = 0; petsPresent < 4; ++petsPresent)
            for (unsigned mutate = 0; mutate < 2; ++mutate) {
                Case c(event); c.followers = petsPresent;
                c.mutation = mutate ? TargetRewritesModes : Unchanged;
                CLICK_PAIR("pet-mode-store-order");
            }

    const int mapEvents[] = {79, 82, 83};
    for (unsigned e = 0; e < 3; ++e)
        for (unsigned flags = 0; flags < 8; ++flags) {
            Case c(mapEvents[e]);
            c.flags |= (flags & 1 ? NullLevel : 0) | (flags & 2 ? Paused : 0) |
                       (flags & 4 ? AlreadyConsumed : 0);
            CLICK_PAIR("automap-gates");
        }
    const int settingsValues[] = {0, 1, -1, INT_MIN, INT_MAX, 7};
    for (unsigned value = 0; value < 6; ++value)
        for (unsigned mutation = 0; mutation < 3; ++mutation) {
            Case c(81); c.setting = settingsValues[value];
            c.mutation = mutation == 1 ? GetSwapsSettings : mutation == 2 ? GetChangesKey : Unchanged;
            CLICK_PAIR("settings-reload");
        }

    // Events 84/85/86 deliberately have different second-menu gates. In
    // particular, zero points never suppress either side of event 84.
    for (int event = 84; event <= 86; ++event)
        for (unsigned modal = 0; modal < 2; ++modal)
            for (unsigned menusOpen = 0; menusOpen < 4; ++menusOpen)
                for (int stat = -1; stat <= 1; ++stat)
                    for (int skill = -1; skill <= 1; ++skill) {
                        Case c(event); c.menuStates = menusOpen;
                        c.statPoints = stat; c.skillPoints = skill;
                        if (modal) c.flags |= ModalOpen;
                        CLICK_PAIR("menu-asymmetry");
                    }
    const unsigned menuMutations[] = {
        ModalSwapsMenus, PartialSwapsMenus, CloseSwapsMenus, SetSwapsToPositiveActor,
        SetSwapsToZeroActor, SetOpensOtherMenu, SetClosesOtherMenu,
        SetSwapsOtherMenu, PartialChangesPoints, SetMakesPointsNegative
    };
    for (int event = 84; event <= 86; ++event)
        for (unsigned m = 0; m < sizeof(menuMutations) / sizeof(menuMutations[0]); ++m)
            for (unsigned mask = 0; mask < 4; ++mask) {
                Case c(event); c.mutation = menuMutations[m];
                c.menuStates = mask | ((3 - mask) << 2);
                c.statPoints = c.skillPoints = mask & 1 ? 0 : 1;
                CLICK_PAIR("menu-callback-rereads");
            }

    for (unsigned mutation = 0; mutation < 3; ++mutation) {
        Case c(68); c.followers = 0; c.mutation = mutation;
        CLICK_PAIR("empty-drag-toggle");
    }
    const int itemStates[] = {0, 40, 41, 42, 43, -1};
    for (unsigned usableItem = 0; usableItem < 2; ++usableItem)
        for (unsigned state = 0; state < 6; ++state)
            for (unsigned sound = 0; sound < 2; ++sound) {
                Case c(68); c.dragged = 1; c.usable = usableItem;
                c.petState = itemStates[state]; if (!sound) c.flags |= NoActorSound;
                CLICK_PAIR("drag-eligibility");
            }
    // A usable dragged item with an initially null pet is outside the original
    // function's domain. The empty-current-list path instead starts with a real
    // cached pet and clears/replaces the current list from isUseable.
    for (unsigned mutation = UsableClearsFollowers; mutation <= UsableBlocksNewPet; ++mutation)
        for (unsigned usableItem = 0; usableItem < 2; ++usableItem) {
            Case c(68); c.dragged = 1; c.mutation = mutation; c.usable = usableItem;
            CLICK_PAIR("usable-callback-rereads");
        }
    for (unsigned used = 0; used < 3; ++used)
        for (unsigned returned = 0; returned < 3; ++returned) {
            Case c(68); c.dragged = 1; c.performed = used; c.returned = returned;
            CLICK_PAIR("perform-return-drag");
        }
    const unsigned soundMutations[] = {
        PlayClearsDrag, PlayReplacesDrag, PlaySwapsActor, PlaySwapsToSilentActor,
        QueueClearsDrag, QueueReplacesDrag, PlayChangesIcon, QueueChangesIcon
    };
    for (unsigned m = 0; m < sizeof(soundMutations) / sizeof(soundMutations[0]); ++m)
        for (unsigned state = 0; state < 3; ++state) {
            Case c(68); c.dragged = 1; c.mutation = soundMutations[m];
            c.usable = state != 0; c.petState = state ? 40 + state : 40;
            CLICK_PAIR("failed-item-audio-rereads");
        }
    for (unsigned m = 0; m < 2; ++m) {
        Case c(68); c.dragged = 1; c.mutation = m ? ReturnChangesIcon : PerformChangesIcon;
        CLICK_PAIR("icon-reread");
    }
    for (unsigned noPet = 0; noPet < 2; ++noPet) {
        Case c(68); c.dragged = 2; c.usable = false; c.followers = noPet ? 3 : 0;
        CLICK_PAIR("unusable-without-pet");
    }
    for (unsigned blockedState = 41; blockedState <= 42; ++blockedState) {
        Case c(68); c.dragged = 1; c.petState = blockedState;
        c.mutation = UsableClearsDrag; CLICK_PAIR("failure-cleared-drag-toggle");
        c.mutation = UsableReplacesFollower; CLICK_PAIR("cached-pet-remains-ineligible");
    }
    {
        Case c(68); c.dragged = 1; c.mutation = UsableNullsCurrentFollower;
        CLICK_PAIR("nonempty-current-list-null-first-follower");
    }

    for (unsigned near = 0; near < 2; ++near)
        for (unsigned living = 0; living < 2; ++living)
            for (unsigned state = 0; state < 6; ++state)
                for (unsigned sound = 0; sound < 2; ++sound) {
                    Case c(95); c.nearDeath = near; c.alive = living;
                    c.petState = itemStates[state]; if (!sound) c.flags |= NoActorSound;
                    CLICK_PAIR("departure-gate-order");
                }
    const unsigned departureMutations[] = {
        NearSwapsActor, NearReplacesFollower, NearBlocksPet, AliveBlocksPet,
        AliveSwapsLevel, QueueSwapsLevel
    };
    for (unsigned m = 0; m < sizeof(departureMutations) / sizeof(departureMutations[0]); ++m) {
        Case c(95); c.mutation = departureMutations[m];
        CLICK_PAIR("departure-callback-rereads");
    }
    for (unsigned absent = 0; absent < 2; ++absent) {
        Case c(95); c.followers = absent ? 3 : 0;
        c.flags = NullLevel; CLICK_PAIR("no-pet-no-level");
    }

    for (unsigned translation = 0; translation < 8; ++translation)
        for (unsigned adjacent = 0; adjacent < 4; ++adjacent)
            for (unsigned sequence = 0; sequence < 5; ++sequence) {
                Case c(95); c.flags = (adjacent & 1 ? PortalAllowed : 0) |
                                     (adjacent & 2 ? Town : 0);
                c.translation = translation; c.sequence = sequence; c.repeat = 4;
                CLICK_PAIR("warning-cache-and-template-byte");
            }

#undef CLICK_PAIR
    coverage.report(host);
    host->log("    CLICK DISPATCH: %u clean original/recovered cases; all 20 dispatch IDs, "
              "default IDs, guarded payloads, callback traces, menu slots 5/8 and warm caches\n", count);
    return count >= 20 ? 0 : 1;
}

TL_TEST(gameui_click_expected_warning_exceptions)
{
    unsigned count = 0;
    for (unsigned fault = 1; fault <= 3; ++fault)
        for (unsigned translation = 0; translation < 8; ++translation) {
            Case c(95); c.flags = PortalAllowed | Town;
            c.fault = fault; c.translation = translation; c.repeat = 3;
            autotest::Outcome a, b;
            autotest::runChild(oldSide, &c, a); autotest::runChild(newSide, &c, b);
            bool ok = a.reportValid && b.reportValid && !a.childStatus && !b.childStatus &&
                      !a.capture.issue && !b.capture.issue &&
                      a.capture.callStarted == 1 && b.capture.callStarted == 1 &&
                      !a.capture.callCompleted && !b.capture.callCompleted &&
                      a.capture.callTarget == static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&originalClick)) &&
                      host->comparison_pair && host->comparison_pair(a.capture.callTarget, b.capture.callTarget) &&
                      a.capture.length == b.capture.length &&
                      !std::memcmp(a.capture.data, b.capture.data, a.capture.length);
            if (!ok) { diagnostic(host, c, "expected-unwind-and-retry", count, a, b); return 1; }
            ++count;
        }
    host->log("    EXPECTED CLICK EXCEPTIONS: %u matching translation/modal unwinds with "
              "two successful retries each; excluded from normal completion coverage\n", count);
    return 0;
}
