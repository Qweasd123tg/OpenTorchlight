// Shadow tests: CAIStatWatcher functions whose code differs from the original
// only in register allocation or block layout. Character, level, AI manager,
// data group and hierarchy calls are redirected to fakes (Detour.h); both
// implementations run on identical objects and their effects are compared.
#include <cstring>
#include <new>
#include <string>
#include <vector>

#include <OgreVector3.h>

#include "Detour.h"
#include "HybridTest.h"
#include "AISkill.h"
#include "AIStatWatcher.h"

class CDataValue;

TL_ORIGINAL(void, originalConstruct, (void*, CDataGroup*, CAIManager*),
            "_ZN14CAIStatWatcherC1EP10CDataGroupP10CAIManager")
TL_ORIGINAL(void, originalDestroy, (void*), "_ZN14CAIStatWatcherD1Ev")
TL_ORIGINAL(void, originalGetTargets, (void*, TArrayList<CCharacter*>*),
            "_ZN14CAIStatWatcher10getTargetsER10TArrayListIP10CCharacterE")
TL_ORIGINAL(void, originalAddFlag, (void*), "_ZN14CAIStatWatcher7addFlagEv")
TL_ORIGINAL(void, originalUpdate, (void*, float), "_ZN14CAIStatWatcher6updateEf")

TL_FUNCTION(valueString, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(valueChars, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(valueFloat, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(valueBool, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(valuesMatching,
            "_ZN10CDataGroup25GetDataValuesMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIP10CDataValueSaIS8_EE")
TL_FUNCTION(valueAsString, "_ZN10CDataValue16GetValueAsStringEv")
TL_FUNCTION(masterSingleton, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(typeIDByName, "_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(alive, "_ZN10CCharacter5aliveEv")
TL_FUNCTION(hp, "_ZN10CCharacter2HPEv")
TL_FUNCTION(maxHP, "_ZN10CCharacter5maxHPEv")
TL_FUNCTION(mana, "_ZN10CCharacter4manaEv")
TL_FUNCTION(maxMana, "_ZN10CCharacter7maxManaEv")
TL_FUNCTION(playAnimation, "_ZN10CCharacter18setAIPlayAnimationERKSsbff")
TL_FUNCTION(position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(characterByGuid, "_ZN6CLevel18getCharacterByGuidEx")
TL_FUNCTION(activeCharacters, "_ZN6CLevel29getActiveCharactersAtPositionERKN4Ogre7Vector3EN9UNITTYPES10EUNITTYPESE"
                              "10EAlignmentfbbR10TArrayListIP10CCharacterE")
TL_FUNCTION(hasFlag, "_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(addFlag, "_ZN10CAIManager9addAIFlagE13EAIFLAG_TYPESf")
TL_FUNCTION(removeFlag, "_ZN10CAIManager12removeAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(hasSkill, "_ZN10CAIManager10hasAISkillEP8CAISkill")
TL_FUNCTION(addSkill, "_ZN10CAIManager10addAISkillEP8CAISkillf")
TL_FUNCTION(removeSkill, "_ZN10CAIManager13removeAISkillEP8CAISkill")

namespace
{

// CAIStatWatcher layout (offsets checked against the original constructor).
const int kWatcherSize = 0xb8;
const int kAIManager = 0x10;
const int kCharacter = 0x18;
const int kStat = 0x20;
const int kLogic = 0x24;
const int kFlags = 0x28;
const int kSkills = 0x40;
const int kFlaggedUnits = 0x58;
const int kSkilledUnits = 0x70;
const int kTarget = 0x88;
const int kUnitType = 0x8c;
const int kAlignment = 0x90;
const int kArea = 0x94;
const int kDuration = 0x98;
const int kValue = 0x9c;
const int kOnlyOnce = 0xa0;
const int kTriggered = 0xa1;
const int kAnimation = 0xa8;
const int kEnableOnEvent = 0xb0;
const int kIncludeLiving = 0xb1;
const int kIncludeDead = 0xb2;

// Collaborator fields read inline by the watcher.
const int kGuid = 0x10;             // CEditorBaseObject
const int kResourceManager = 0x68;  // CBaseUnit
const int kUnitAIManager = 0x718;   // CCharacter
const int kLevel = 0x18;            // CResourceManager
const int kGameClients = 0x28;      // CResourceManager
const int kLevelCharacters = 0x98;  // CLevel
const int kManagerCharacter = 0x10; // CAIManager
const int kFormation = 0x40;        // CAIManager
const int kHierarchy = 0x80;        // CMasterResourceManager

const int kUnits = 6;
const int kSkillCount = 4;
const long long kFirstGuid = 1000;

typedef TArrayList<int> IntList;
typedef TArrayList<void*> PointerList;
typedef TArrayList<long long> GuidList;
typedef std::string String;

struct ListView
{
    const void* data;
    unsigned int count;
    unsigned int capacity;
    unsigned int growBy;
};

unsigned int g_seed = 2718;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

unsigned int pick(unsigned int count)
{
    return nextRandom() % count;
}

template <class T>
void put(void* base, int offset, T value)
{
    std::memcpy(static_cast<char*>(base) + offset, &value, sizeof(value));
}

template <class T>
T get(const void* base, int offset)
{
    T value;
    std::memcpy(&value, static_cast<const char*>(base) + offset, sizeof(value));
    return value;
}

// Calls with side effects, in call order.
enum
{
    CALL_ADD_FLAG,
    CALL_REMOVE_FLAG,
    CALL_ADD_SKILL,
    CALL_REMOVE_SKILL,
    CALL_ANIMATION,
    CALL_ACTIVE_CHARACTERS
};

struct Call
{
    int what;
    const void* object;
    long long a;
    long long b;
    float f[4];
};

const int kMaxCalls = 128;

struct Log
{
    Call calls[kMaxCalls];
    int count;
    bool overflow;

    void clear() { std::memset(this, 0, sizeof(*this)); }

    Call& add(int what, const void* object)
    {
        static Call spare;
        if (count == kMaxCalls)
        {
            overflow = true;
            return spare;
        }
        Call& call = calls[count++];
        std::memset(&call, 0, sizeof(call));
        call.what = what;
        call.object = object;
        return call;
    }
};

bool sameLogs(const Log& a, const Log& b)
{
    if (a.overflow || b.overflow || a.count != b.count)
        return false;
    for (int i = 0; i < a.count; i++)
    {
        const Call& x = a.calls[i];
        const Call& y = b.calls[i];
        if (x.what != y.what || x.object != y.object || x.a != y.a || x.b != y.b ||
            std::memcmp(x.f, y.f, sizeof(x.f)) != 0)
            return false;
    }
    return true;
}

struct Node
{
    void* data;
    Node* next;
    Node* previous;
};

struct UnitState
{
    bool known;
    bool alive;
    int hp;
    int maxHp;
    int mana;
    int maxMana;
    float x;
    float y;
    int type;
};

// State the fake AI managers change: AI flag and AI skill bits per manager.
struct Effects
{
    unsigned int flags[kUnits];
    unsigned int skills[kUnits];
};

// Images of the collaborators; unit 0 owns the watcher.
struct World
{
    long long units[kUnits][0x100];
    long long managers[kUnits][0x10];
    long long resourceManager[0x10];
    long long level[0x20];
    long long masterResourceManager[0x20];
    long long hierarchy[4];
    long long dataGroup[4];
    long long gameClient[4];
    void* gameClients[1];
    Node* firstNode;
    Node nodes[kUnits];
    long long skills[kSkillCount][8];
    UnitState state[kUnits];
    Effects effects;
    unsigned int activeCount;
};

World g_world;
Log g_log;

int unitIndex(const void* unit)
{
    for (int i = 0; i < kUnits; i++)
    {
        if (unit == g_world.units[i])
            return i;
    }
    return -1;
}

int managerIndex(const void* manager)
{
    for (int i = 0; i < kUnits; i++)
    {
        if (manager == g_world.managers[i])
            return i;
    }
    return -1;
}

long long skillIndex(const void* skill)
{
    for (int i = 0; i < kSkillCount; i++)
    {
        if (skill == g_world.skills[i])
            return i;
    }
    return -1;
}

// --- fakes ------------------------------------------------------------------

bool fakeAlive(void* unit)
{
    int i = unitIndex(unit);
    return i >= 0 && g_world.state[i].alive;
}

int fakeHP(void* unit)
{
    int i = unitIndex(unit);
    return i >= 0 ? g_world.state[i].hp : -7;
}

int fakeMaxHP(void* unit)
{
    int i = unitIndex(unit);
    return i >= 0 ? g_world.state[i].maxHp : -7;
}

int fakeMana(void* unit)
{
    int i = unitIndex(unit);
    return i >= 0 ? g_world.state[i].mana : -7;
}

int fakeMaxMana(void* unit)
{
    int i = unitIndex(unit);
    return i >= 0 ? g_world.state[i].maxMana : -7;
}

Ogre::Vector3 fakePosition(void* object, bool absolute)
{
    int i = unitIndex(object);
    Ogre::Vector3 position(99.0f, 99.0f, 0.0f);
    if (i >= 0)
        position = Ogre::Vector3(g_world.state[i].x, g_world.state[i].y, 0.0f);
    // The relative position differs, so the flag the caller passes matters.
    if (!absolute)
        position.z += 0.25f;
    return position;
}

bool fakeISA(void* unit, int type)
{
    int i = unitIndex(unit);
    return i >= 0 && g_world.state[i].type == type;
}

void* fakeCharacterByGuid(void*, long long guid)
{
    for (int i = 0; i < kUnits; i++)
    {
        if (g_world.state[i].known && get<long long>(g_world.units[i], kGuid) == guid)
            return g_world.units[i];
    }
    return NULL;
}

void fakeActiveCharacters(void* level, const Ogre::Vector3& position, int unitType, int alignment, float radius,
                          bool living, bool dead, TArrayList<CCharacter*>& characters)
{
    Call& call = g_log.add(CALL_ACTIVE_CHARACTERS, level);
    call.a = unitType | (alignment << 8);
    call.b = (living ? 1 : 0) | (dead ? 2 : 0);
    call.f[0] = position.x;
    call.f[1] = position.y;
    call.f[2] = position.z;
    call.f[3] = radius;
    for (unsigned int i = 0; i < g_world.activeCount; i++)
        characters.add(reinterpret_cast<CCharacter*>(g_world.units[i]));
}

bool fakeHasFlag(void* manager, int flag)
{
    int i = managerIndex(manager);
    return i >= 0 && ((g_world.effects.flags[i] >> flag) & 1) != 0;
}

void* fakeAddFlag(void* manager, int flag, float time)
{
    Call& call = g_log.add(CALL_ADD_FLAG, manager);
    call.a = flag;
    call.f[0] = time;
    int i = managerIndex(manager);
    if (i >= 0)
        g_world.effects.flags[i] |= 1u << flag;
    return NULL;
}

void fakeRemoveFlag(void* manager, int flag)
{
    g_log.add(CALL_REMOVE_FLAG, manager).a = flag;
    int i = managerIndex(manager);
    if (i >= 0)
        g_world.effects.flags[i] &= ~(1u << flag);
}

bool fakeHasSkill(void* manager, void* skill)
{
    int i = managerIndex(manager);
    long long k = skillIndex(skill);
    return i >= 0 && k >= 0 && ((g_world.effects.skills[i] >> k) & 1) != 0;
}

void fakeAddSkill(void* manager, void* skill, float time)
{
    Call& call = g_log.add(CALL_ADD_SKILL, manager);
    call.a = skillIndex(skill);
    call.f[0] = time;
    int i = managerIndex(manager);
    if (i >= 0 && call.a >= 0)
        g_world.effects.skills[i] |= 1u << call.a;
}

void fakeRemoveSkill(void* manager, void* skill)
{
    long long k = skillIndex(skill);
    g_log.add(CALL_REMOVE_SKILL, manager).a = k;
    int i = managerIndex(manager);
    if (i >= 0 && k >= 0)
        g_world.effects.skills[i] &= ~(1u << k);
}

void fakePlayAnimation(void* unit, const std::string& animation, bool loop, float blend, float speed)
{
    Call& call = g_log.add(CALL_ANIMATION, unit);
    long long hash = (long long)animation.size();
    for (unsigned int i = 0; i < animation.size(); i++)
        hash = hash * 131 + (unsigned char)animation[i];
    call.a = hash;
    call.b = loop;
    call.f[0] = blend;
    call.f[1] = speed;
}

// Data group: named entries readable as text, number or flag.
struct Entry
{
    std::wstring name;
    std::wstring text;
    float number;
    bool flag;
};

const int kMaxEntries = 32;
Entry g_entries[kMaxEntries];
int g_entryCount;

const Entry* findEntry(const std::wstring& name)
{
    for (int i = 0; i < g_entryCount; i++)
    {
        if (g_entries[i].name == name)
            return &g_entries[i];
    }
    return NULL;
}

const std::wstring& fakeValueString(void*, const std::wstring& name, const std::wstring& defaultValue)
{
    const Entry* entry = findEntry(name);
    return entry ? entry->text : defaultValue;
}

const std::wstring& fakeValueChars(void*, const std::wstring& name, const wchar_t* defaultValue)
{
    static std::wstring fallback;
    const Entry* entry = findEntry(name);
    if (entry)
        return entry->text;
    fallback = defaultValue;
    return fallback;
}

float fakeValueFloat(void*, const std::wstring& name, float defaultValue)
{
    const Entry* entry = findEntry(name);
    return entry ? entry->number : defaultValue;
}

bool fakeValueBool(void*, const std::wstring& name, bool defaultValue)
{
    const Entry* entry = findEntry(name);
    return entry ? entry->flag : defaultValue;
}

void fakeValuesMatching(void*, const std::wstring& name, std::vector<CDataValue*>* values)
{
    for (int i = 0; i < g_entryCount; i++)
    {
        if (g_entries[i].name == name)
            values->push_back(reinterpret_cast<CDataValue*>(&g_entries[i]));
    }
}

std::wstring fakeValueAsString(void* value)
{
    return static_cast<Entry*>(value)->text;
}

void* fakeMasterSingleton()
{
    return g_world.masterResourceManager;
}

int fakeTypeIDByName(void*, const std::wstring& name)
{
    int id = (int)name.size() * 3;
    if (!name.empty())
        id += name[0];
    return id % 50;
}

void redirectAll(detour::Set& set)
{
    TL_REDIRECT(set, valueString, &fakeValueString);
    TL_REDIRECT(set, valueChars, &fakeValueChars);
    TL_REDIRECT(set, valueFloat, &fakeValueFloat);
    TL_REDIRECT(set, valueBool, &fakeValueBool);
    TL_REDIRECT(set, valuesMatching, &fakeValuesMatching);
    TL_REDIRECT(set, valueAsString, &fakeValueAsString);
    TL_REDIRECT(set, masterSingleton, &fakeMasterSingleton);
    TL_REDIRECT(set, typeIDByName, &fakeTypeIDByName);
    TL_REDIRECT(set, alive, &fakeAlive);
    TL_REDIRECT(set, hp, &fakeHP);
    TL_REDIRECT(set, maxHP, &fakeMaxHP);
    TL_REDIRECT(set, mana, &fakeMana);
    TL_REDIRECT(set, maxMana, &fakeMaxMana);
    TL_REDIRECT(set, playAnimation, &fakePlayAnimation);
    TL_REDIRECT(set, position, &fakePosition);
    TL_REDIRECT(set, isa, &fakeISA);
    TL_REDIRECT(set, characterByGuid, &fakeCharacterByGuid);
    TL_REDIRECT(set, activeCharacters, &fakeActiveCharacters);
    TL_REDIRECT(set, hasFlag, &fakeHasFlag);
    TL_REDIRECT(set, addFlag, &fakeAddFlag);
    TL_REDIRECT(set, removeFlag, &fakeRemoveFlag);
    TL_REDIRECT(set, hasSkill, &fakeHasSkill);
    TL_REDIRECT(set, addSkill, &fakeAddSkill);
    TL_REDIRECT(set, removeSkill, &fakeRemoveSkill);
}

// --- world ------------------------------------------------------------------

GuidList* formation()
{
    return reinterpret_cast<GuidList*>(reinterpret_cast<char*>(g_world.managers[0]) + kFormation);
}

void randomWorld()
{
    World& w = g_world;
    std::memset(w.units, 0, sizeof(w.units));
    std::memset(w.managers, 0, sizeof(w.managers));
    std::memset(w.resourceManager, 0, sizeof(w.resourceManager));
    std::memset(w.level, 0, sizeof(w.level));
    std::memset(w.masterResourceManager, 0, sizeof(w.masterResourceManager));
    static const int maxima[] = {0, 50, 100, 200};
    for (int i = 0; i < kUnits; i++)
    {
        UnitState& s = w.state[i];
        s.known = i == 0 || pick(5) != 0;
        s.alive = pick(4) != 0;
        s.hp = (int)pick(120);
        s.maxHp = maxima[pick(4)];
        s.mana = (int)pick(120);
        s.maxMana = maxima[pick(4)];
        // Whole coordinates: distances such as 5 = |(3, 4)| hit the area bound exactly.
        s.x = i == 0 ? (float)pick(2) : (float)((int)pick(13) - 6);
        s.y = i == 0 ? 0.0f : (float)((int)pick(13) - 6);
        s.type = (int)pick(3);
        put<long long>(w.units[i], kGuid, kFirstGuid + i);
        put<void*>(w.units[i], kResourceManager, w.resourceManager);
        put<void*>(w.units[i], kUnitAIManager, pick(5) != 0 ? w.managers[i] : NULL);
        put<void*>(w.managers[i], kManagerCharacter, w.units[i]);
        w.effects.flags[i] = nextRandom() & 0x7f;
        w.effects.skills[i] = nextRandom() & 0xf;
    }
    put<void*>(w.resourceManager, kLevel, w.level);
    unsigned int clients = pick(3);
    w.gameClients[0] = clients == 2 ? w.gameClient : NULL;
    put<void*>(w.resourceManager, kGameClients, w.gameClients);
    put<unsigned int>(w.resourceManager, kGameClients + 8, clients != 0 ? 1 : 0);
    put<unsigned int>(w.resourceManager, kGameClients + 12, 1);
    put<unsigned int>(w.resourceManager, kGameClients + 16, 1);

    // Level unit list in a random order.
    w.firstNode = NULL;
    for (int i = 0; i < kUnits; i++)
    {
        int k = (i + 1 + (int)pick(kUnits)) % kUnits;
        if (pick(4) == 0)
            continue;
        bool listed = false;
        for (Node* n = w.firstNode; n; n = n->next)
            listed = listed || n->data == w.units[k];
        if (listed)
            continue;
        Node& node = w.nodes[k];
        node.data = w.units[k];
        node.previous = NULL;
        node.next = w.firstNode;
        if (w.firstNode)
            w.firstNode->previous = &node;
        w.firstNode = &node;
    }
    put<void*>(w.level, kLevelCharacters, &w.firstNode);
    put<void*>(w.masterResourceManager, kHierarchy, w.hierarchy);
    w.activeCount = pick(kUnits + 1);

    GuidList* units = ::new (formation()) GuidList(10);
    for (unsigned int n = pick(5); n > 0; n--)
        units->add(kFirstGuid + pick(kUnits + 1));
}

void destroyWorld()
{
    formation()->~GuidList();
}

struct Spec
{
    int stat;
    int logic;
    int target;
    int unitType;
    int alignment;
    int flags[4];
    unsigned int flagCount;
    int skills[4];
    unsigned int skillCount;
    long long flagged[4];
    unsigned int flaggedCount;
    float area;
    float duration;
    float value;
    bool onlyOnce;
    bool triggered;
    bool enableOnEvent;
    bool includeLiving;
    bool includeDead;
    const char* animation;
};

Spec randomSpec()
{
    static const float areas[] = {0.0f, 3.0f, 5.0f, 7.5f, 100.0f};
    static const float durations[] = {0.0f, 0.0f, 2.5f};
    static const float values[] = {0.0f, 2.0f, 30.0f, 50.0f, 100.0f};
    Spec s;
    // One past each enumeration: values the switches and chains do not name.
    s.stat = (int)pick(AISTAT_TYPE_COUNT + 1);
    s.logic = (int)pick(AISTAT_LOGIC_COUNT + 1);
    s.target = (int)pick(AISTAT_TARGET_COUNT + 1);
    s.unitType = (int)pick(3);
    s.alignment = (int)pick(7);
    s.flagCount = pick(4);
    for (unsigned int i = 0; i < s.flagCount; i++)
        s.flags[i] = (int)pick(AIFLAG_COUNT);
    s.skillCount = pick(4);
    for (unsigned int i = 0; i < s.skillCount; i++)
        s.skills[i] = (int)pick(kSkillCount);
    s.flaggedCount = pick(4);
    for (unsigned int i = 0; i < s.flaggedCount; i++)
        s.flagged[i] = kFirstGuid + pick(kUnits + 1);
    s.area = areas[pick(5)];
    s.duration = durations[pick(3)];
    s.value = values[pick(5)];
    s.onlyOnce = pick(2) != 0;
    s.triggered = pick(2) != 0;
    s.enableOnEvent = pick(2) != 0;
    s.includeLiving = pick(2) != 0;
    s.includeDead = pick(2) != 0;
    s.animation = pick(2) != 0 ? "" : "SPECIAL1";
    return s;
}

void build(void* image, const Spec& s)
{
    char* w = static_cast<char*>(image);
    std::memset(w, 0, kWatcherSize);
    put<void*>(w, kAIManager, g_world.managers[0]);
    put<void*>(w, kCharacter, g_world.units[0]);
    put<int>(w, kStat, s.stat);
    put<int>(w, kLogic, s.logic);
    IntList* flags = ::new (w + kFlags) IntList(2);
    for (unsigned int i = 0; i < s.flagCount; i++)
        flags->add(s.flags[i]);
    PointerList* skills = ::new (w + kSkills) PointerList(2);
    for (unsigned int i = 0; i < s.skillCount; i++)
        skills->add(g_world.skills[s.skills[i]]);
    GuidList* flagged = ::new (w + kFlaggedUnits) GuidList(5);
    for (unsigned int i = 0; i < s.flaggedCount; i++)
        flagged->add(s.flagged[i]);
    ::new (w + kSkilledUnits) GuidList(5);
    put<int>(w, kTarget, s.target);
    put<int>(w, kUnitType, s.unitType);
    put<int>(w, kAlignment, s.alignment);
    put<float>(w, kArea, s.area);
    put<float>(w, kDuration, s.duration);
    put<float>(w, kValue, s.value);
    put<bool>(w, kOnlyOnce, s.onlyOnce);
    put<bool>(w, kTriggered, s.triggered);
    ::new (w + kAnimation) String(s.animation);
    put<bool>(w, kEnableOnEvent, s.enableOnEvent);
    put<bool>(w, kIncludeLiving, s.includeLiving);
    put<bool>(w, kIncludeDead, s.includeDead);
}

void destroy(void* image)
{
    char* w = static_cast<char*>(image);
    reinterpret_cast<IntList*>(w + kFlags)->~IntList();
    reinterpret_cast<PointerList*>(w + kSkills)->~PointerList();
    reinterpret_cast<GuidList*>(w + kFlaggedUnits)->~GuidList();
    reinterpret_cast<GuidList*>(w + kSkilledUnits)->~GuidList();
    reinterpret_cast<String*>(w + kAnimation)->~String();
}

bool sameList(const char* a, const char* b, int offset, unsigned int elementSize)
{
    ListView x = get<ListView>(a, offset);
    ListView y = get<ListView>(b, offset);
    if (x.count != y.count || x.capacity != y.capacity || x.growBy != y.growBy || (x.data == 0) != (y.data == 0))
        return false;
    return x.count == 0 || std::memcmp(x.data, y.data, x.count * elementSize) == 0;
}

bool sameSkillNames(const char* a, const char* b)
{
    ListView x = get<ListView>(a, kSkills);
    ListView y = get<ListView>(b, kSkills);
    if (x.count != y.count || x.capacity != y.capacity || x.growBy != y.growBy)
        return false;
    for (unsigned int i = 0; i < x.count; i++)
    {
        CAISkill* p = static_cast<CAISkill* const*>(x.data)[i];
        CAISkill* q = static_cast<CAISkill* const*>(y.data)[i];
        if ((p == NULL) != (q == NULL) || (p && p->getName() != q->getName()))
            return false;
    }
    return true;
}

int compareWatchers(const tlhybrid_host* host, const void* left, const void* right, bool skillsByName)
{
    int failures = 0;
    const char* a = static_cast<const char*>(left);
    const char* b = static_cast<const char*>(right);
    // vptr, safe pointers, manager, character, stat, logic.
    TL_CHECK(failures, std::memcmp(a, b, kFlags) == 0);
    TL_CHECK(failures, sameList(a, b, kFlags, sizeof(int)));
    TL_CHECK(failures, skillsByName ? sameSkillNames(a, b) : sameList(a, b, kSkills, sizeof(void*)));
    TL_CHECK(failures, sameList(a, b, kFlaggedUnits, sizeof(long long)));
    TL_CHECK(failures, sameList(a, b, kSkilledUnits, sizeof(long long)));
    TL_CHECK(failures, std::memcmp(a + kTarget, b + kTarget, kTriggered + 1 - kTarget) == 0);
    TL_CHECK(failures, *reinterpret_cast<const String*>(a + kAnimation) ==
                           *reinterpret_cast<const String*>(b + kAnimation));
    TL_CHECK(failures, std::memcmp(a + kEnableOnEvent, b + kEnableOnEvent, kIncludeDead + 1 - kEnableOnEvent) == 0);
    return failures;
}

// --- constructor data ---------------------------------------------------------

void addEntry(const wchar_t* name, const wchar_t* text, float number, bool flag)
{
    if (g_entryCount == kMaxEntries)
        return;
    Entry& entry = g_entries[g_entryCount++];
    entry.name = name;
    entry.text = text;
    entry.number = number;
    entry.flag = flag;
}

const wchar_t* oneOf(const wchar_t* const* table, unsigned int count)
{
    return table[pick(count)];
}

#define COUNT(table) (sizeof(table) / sizeof(table[0]))

void randomEntries()
{
    static const wchar_t* const stats[] = {L"HP", L"mana", L"HP PCT", L"Mana Pct", L"ACTIVE UNITS", L"NONE", L"HP_PCT", L""};
    static const wchar_t* const logics[] = {L"BELOW", L"above", L"SIDEWAYS"};
    static const wchar_t* const flags[] = {L"AWARE", L"berserk", L"CANNOT INTERRUPT", L"FRIGHTEN",
                                           L"NO LINE OF SIGHT", L"NEVER CHANGE TARGET", L"CANNOT TARGET", L"SLEEPY"};
    static const wchar_t* const skills[] = {L"FIREBALL", L"Heal", L"SUMMON SKELETON"};
    static const wchar_t* const targets[] = {L"SELF", L"FORMATION", L"area", L"AREAUNITTYPES", L"AREAFORMATION",
                                             L"NOWHERE"};
    static const wchar_t* const alignments[] = {L"NEUTRAL", L"GOOD", L"evil", L"ALL", L"BERSERK", L"EVILBERSERK",
                                                L"GOODBERSERK", L"CHAOTIC"};
    static const wchar_t* const unitTypes[] = {L"MONSTER", L"PLAYER", L"ANY", L"x"};
    static const wchar_t* const animations[] = {L"attack", L"Special1", L"", L"IDLE"};
    static const float numbers[] = {0.0f, 1.5f, 25.0f, 100.0f, -2.0f};

    g_entryCount = 0;
    if (pick(5) != 0)
        addEntry(L"STAT", oneOf(stats, COUNT(stats)), 0.0f, false);
    if (pick(4) != 0)
        addEntry(L"LOGIC", oneOf(logics, COUNT(logics)), 0.0f, false);
    for (unsigned int n = pick(5); n > 0; n--)
        addEntry(L"FLAG", oneOf(flags, COUNT(flags)), 0.0f, false);
    for (unsigned int n = pick(4); n > 0; n--)
        addEntry(L"SKILL", oneOf(skills, COUNT(skills)), 0.0f, false);
    if (pick(4) != 0)
        addEntry(L"TARGET", oneOf(targets, COUNT(targets)), 0.0f, false);
    if (pick(3) != 0)
        addEntry(L"TARGET_ALIGNMENT", oneOf(alignments, COUNT(alignments)), 0.0f, false);
    if (pick(3) != 0)
        addEntry(L"TARGETUNITTYPE", oneOf(unitTypes, COUNT(unitTypes)), 0.0f, false);
    static const wchar_t* const numberNames[] = {L"TARGETAREA", L"VALUE", L"DURATION"};
    for (unsigned int i = 0; i < COUNT(numberNames); i++)
    {
        if (pick(3) != 0)
            addEntry(numberNames[i], L"", numbers[pick(COUNT(numbers))], false);
    }
    static const wchar_t* const flagNames[] = {L"ONLYONCE", L"ENABLE_ON_EVENT", L"INCLUDE_LIVING", L"INCLUDE_DEAD"};
    for (unsigned int i = 0; i < COUNT(flagNames); i++)
    {
        if (pick(3) != 0)
            addEntry(flagNames[i], L"", 0.0f, pick(2) != 0);
    }
    if (pick(2) != 0)
        addEntry(L"ANIMATION", oneOf(animations, COUNT(animations)), 0.0f, false);
}

} // namespace

TL_TEST(AIStatWatcher_constructor_shadow)
{
    int failures = 0;
    detour::Set set;
    redirectAll(set);
    TL_CHECK(failures, !set.failed());
    TL_CHECK(failures, sizeof(CAIStatWatcher) == kWatcherSize);
    if (failures)
        return failures;

    static long long a[kWatcherSize / 8];
    static long long b[kWatcherSize / 8];
    CDataGroup* group = reinterpret_cast<CDataGroup*>(g_world.dataGroup);
    for (int round = 0; round < 3000 && failures == 0; round++)
    {
        randomWorld();
        randomEntries();
        CAIManager* manager = reinterpret_cast<CAIManager*>(g_world.managers[0]);
        std::memset(a, 0xcd, sizeof(a));
        std::memset(b, 0xcd, sizeof(b));
        originalConstruct(a, group, manager);
        ::new (b) CAIStatWatcher(group, manager);
        failures += compareWatchers(host, a, b, true);
        if (failures)
            host->log("    constructor round %d\n", round);
        originalDestroy(a);
        reinterpret_cast<CAIStatWatcher*>(b)->CAIStatWatcher::~CAIStatWatcher();
        destroyWorld();
    }
    for (int i = 0; i < kMaxEntries; i++)
    {
        std::wstring().swap(g_entries[i].name);
        std::wstring().swap(g_entries[i].text);
    }
    return failures;
}

TL_TEST(AIStatWatcher_behaviour_shadow)
{
    int failures = 0;
    detour::Set set;
    redirectAll(set);
    TL_CHECK(failures, !set.failed());
    if (failures)
        return failures;

    static long long images[2][kWatcherSize / 8];
    static Log logs[2];
    for (int round = 0; round < 4000 && failures == 0; round++)
    {
        randomWorld();
        Spec spec = randomSpec();
        build(images[0], spec);
        build(images[1], spec);
        Effects effects[2] = {g_world.effects, g_world.effects};
        for (int step = 0; step < 8 && failures == 0; step++)
        {
            // Changes of the shared world apply to both sides.
            if (pick(3) == 0)
            {
                UnitState& self = g_world.state[0];
                self.alive = pick(4) != 0;
                self.hp = (int)pick(120);
                self.mana = (int)pick(120);
                g_world.activeCount = pick(kUnits + 1);
            }
            unsigned int operation = pick(3);
            float elapsed = (float)pick(100) / 64.0f;
            void* targets[2][kUnits * 4];
            unsigned int targetCount[2] = {0, 0};
            for (int side = 0; side < 2; side++)
            {
                g_world.effects = effects[side];
                g_log.clear();
                void* w = images[side];
                if (operation == 0)
                {
                    TArrayList<CCharacter*> list(pick(3) + 1);
                    if (side == 0)
                        originalGetTargets(w, &list);
                    else
                        static_cast<CAIStatWatcher*>(w)->getTargets(list);
                    targetCount[side] = list.size();
                    for (unsigned int i = 0; i < list.size() && i < kUnits * 4; i++)
                        targets[side][i] = list[i];
                }
                else if (operation == 1)
                {
                    if (side == 0)
                        originalAddFlag(w);
                    else
                        static_cast<CAIStatWatcher*>(w)->addFlag();
                }
                else
                {
                    if (side == 0)
                        originalUpdate(w, elapsed);
                    else
                        static_cast<CAIStatWatcher*>(w)->update(elapsed);
                }
                logs[side] = g_log;
                effects[side] = g_world.effects;
            }
            TL_CHECK(failures, sameLogs(logs[0], logs[1]));
            TL_CHECK(failures, std::memcmp(&effects[0], &effects[1], sizeof(Effects)) == 0);
            TL_CHECK(failures, targetCount[0] == targetCount[1]);
            TL_CHECK(failures, targetCount[0] <= kUnits * 4);
            TL_CHECK(failures, targetCount[1] <= kUnits * 4);
            if (targetCount[0] == targetCount[1] && targetCount[0] <= kUnits * 4)
                TL_CHECK(failures, std::memcmp(targets[0], targets[1], targetCount[0] * sizeof(void*)) == 0);
            failures += compareWatchers(host, images[0], images[1], false);
            if (failures)
                host->log("    round %d step %d operation %u\n", round, step, operation);
        }
        destroy(images[0]);
        destroy(images[1]);
        destroyWorld();
    }
    return failures;
}
