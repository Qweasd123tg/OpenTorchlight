// Shadow tests for Descriptor.cpp. Every round builds the same input twice:
// side A runs the original machine code, side B the decompiled CDescriptor.
// Each side writes what it observably does (virtual calls on objects, the
// descriptor and a fake scene, property accessors, log messages) and its
// resulting state into a text log; the two logs must agree.
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <map>
#include <new>
#include <sstream>
#include <string>
#include <vector>

#include <OgreLog.h>
#include <OgreLogManager.h>

#include "AutoTest.h"
#include "Detour.h"
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "DescriptorSaveConfiguration.h"
#include "LogicWrapper.h"
#include "OgreReader.h"
#include "Settings.h"

TL_ORIGINAL(unsigned int, originalGetInputFuncIndex, (void*, CLogicWrapper*),
            "_ZN11CDescriptor31GetInputLogicFuncIndexByWrapperEP13CLogicWrapper")
TL_ORIGINAL(unsigned int, originalGetOutputFuncIndex, (void*, CLogicWrapper*),
            "_ZN11CDescriptor32GetOutputLogicFuncIndexByWrapperEP13CLogicWrapper")
TL_ORIGINAL(unsigned int, originalAddInputLogic, (void*, std::wstring, unsigned int),
            "_ZN11CDescriptor13AddInputLogicESbIwSt11char_traitsIwESaIwEEj")
TL_ORIGINAL(long long, originalUniqueValue, (void*), "_ZN11CDescriptor35getUniqueNumericValueRepresentationEv")
TL_ORIGINAL(void, originalLinkProperty, (void*, unsigned int, unsigned int), "_ZN11CDescriptor12LinkPropertyEjj")
TL_ORIGINAL(void, originalSetProperty, (void*, CEditorBaseObject*, unsigned int, const void*, unsigned int),
            "_ZN11CDescriptor11SetPropertyEP17CEditorBaseObjectjPKvj")
TL_ORIGINAL(void, originalCalculateDefaults, (void*, CEditorBaseObject*),
            "_ZN11CDescriptor22calculateDefaultValuesEP17CEditorBaseObject")
TL_ORIGINAL(unsigned int, originalAddProperty,
            (void*, std::wstring, std::wstring, std::wstring, void*, void*, EVARIABLE_TYPES, int),
            "_ZN11CDescriptor11AddPropertyESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_15EVARIABLE_TYPESi")
TL_ORIGINAL(unsigned int, originalAddPropertyWithInterpreter,
            (void*, std::wstring, std::wstring, std::wstring, void*, void*, PropertyStringToIndexFunction,
             PropertyIndexToStringFunction, void*, EVARIABLE_TYPES, int),
            "_ZN11CDescriptor35AddPropertyWithInterpreterFunctionsESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_PFjP12"
            "CEditorSceneP17CEditorBaseObjectRKS3_S4_EPFS3_S6_S8_jS4_ES4_15EVARIABLE_TYPESi")
TL_ORIGINAL(bool, originalClone, (void*, CEditorBaseObject*, CEditorBaseObject*, CEditorBaseObject*),
            "_ZN11CDescriptor5CloneEP17CEditorBaseObjectS1_S1_")
TL_ORIGINAL(CEditorBaseObject*, originalLoadObject, (void*, CDataGroup*, CDescriptorLoadConfiguration*),
            "_ZN11CDescriptor10loadObjectEP10CDataGroupP28CDescriptorLoadConfiguration")
TL_ORIGINAL(int, originalLoadObjects, (void*, CDataGroup*, CDescriptorLoadConfiguration*),
            "_ZN11CDescriptor11loadObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
TL_ORIGINAL(void, originalPostProcessObjects, (void*, CDataGroup*, CDescriptorLoadConfiguration*),
            "_ZN11CDescriptor18postProcessObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
TL_ORIGINAL(void, originalSaveObject, (void*, CEditorBaseObject*, CDataGroup*, CDescriptorSaveConfiguration*),
            "_ZN11CDescriptor10saveObjectEP17CEditorBaseObjectP10CDataGroupP28CDescriptorSaveConfiguration")
TL_ORIGINAL(unsigned int, originalSaveObjects, (void*, CDataGroup*, CDescriptorSaveConfiguration*),
            "_ZN11CDescriptor11saveObjectsEP10CDataGroupP28CDescriptorSaveConfiguration")
TL_ORIGINAL(bool, originalSaveBinary, (void*, std::ofstream&, CEditorBaseObject*, CDescriptorSaveConfiguration*),
            "_ZN11CDescriptor22saveObjectInBinaryFileERSt14basic_ofstreamIcSt11char_traitsIcEEP17CEditorBaseObject"
            "P28CDescriptorSaveConfiguration")
TL_ORIGINAL(bool, originalLoadBinary, (void*, COgreReader&, CEditorBaseObject*, CDescriptorLoadConfiguration&),
            "_ZN11CDescriptor24loadObjectFromBinaryFileER11COgreReaderP17CEditorBaseObjectR28CDescriptorLoadConfiguration")
TL_ORIGINAL(void, originalBroadcast, (void*, CEditorBaseObject*, unsigned int),
            "_ZN11CDescriptor24BroadcastEventFromObjectEP17CEditorBaseObjectj")
TL_ORIGINAL(void, originalDeleteAll, (void*), "_ZN11CDescriptor16deleteAllObjectsEv")

// Readers of the values in a CDataGroup (DataValue.cpp has no header yet).
class CDataValue;
extern "C" const std::wstring& dataValueName(CDataValue*) __asm__("_ZN10CDataValue16GetDataValueNameEv");
extern "C" std::wstring dataValueText(CDataValue*) __asm__("_ZN10CDataValue16GetValueAsStringEv");
extern "C" std::wstring dataValueType(CDataValue*) __asm__("_ZN10CDataValue20GetValueTypeAsStringEv");

// The original global read by CLogicLink::InitiateInputEvent (bit 0 of +0x66).
extern char* gEditor;

namespace
{

const int kValueSlots = 6;
const unsigned int kMaxValues = 4;
const int kDescriptorSlots = 21;
const int kSaveObjectSlot = 17;
const int kPropertySlots = 4;
const int kSceneSlots = 80;
const int kSceneCreateSlot = 59;
const int kSceneDeleteSlot = 60;
const int kSceneEventSlot = 66;

// Members of CEditorScene, CEditorBaseObject, CLogicObject and CLogicLink the
// tests fill directly (offsets from the constructors and the machine code).
const int kSceneSize = 0x200;
const int kSceneResourceManager = 0x68;
const int kSceneObjects = 0x108;
const int kSceneSettings = 0x170;
const int kSceneSide = 0x1f8;
const int kResourceLogicEnabled = 0x41;
const int kSettingsInts = 0x40;

typedef std::map<long long, CEditorBaseObject*> ObjectMap;

struct Side
{
    char* scene;
    char resources[0x80];
    char settings[0x80];
    std::vector<int> ints;
    std::string log;
    std::map<const void*, int> ordinals;
    long long nextGuid;
    bool failCreate;
    bool flipOnFire;
};

Side g_sides[2];
Side* g_side;

unsigned int g_seed = 4242;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

void record(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    int written=vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    if(written<0||static_cast<size_t>(written)>=sizeof(buffer))_exit(71);
    g_side->log += buffer;
}

std::string text(const std::wstring& value)
{
    std::string out;
    for (unsigned int i = 0; i < value.length(); i++)
    {
        unsigned int c = value[i];
        if (c >= 0x20 && c < 0x7f)
        {
            out += static_cast<char>(c);
        }
        else
        {
            char buffer[16];
            std::sprintf(buffer, "\\%x;", c);
            out += buffer;
        }
    }
    return out;
}

std::string hex(const std::string& bytes)
{
    std::string out;
    for (unsigned int i = 0; i < bytes.size(); i++)
    {
        char buffer[4];
        std::sprintf(buffer, "%02x", static_cast<unsigned char>(bytes[i]));
        out += buffer;
    }
    return out;
}

// Pointers differ between the sides; they are logged by order of appearance.
int ordinal(const void* pointer)
{
    if (pointer == NULL)
        return -1;
    std::map<const void*, int>::iterator it = g_side->ordinals.find(pointer);
    if (it != g_side->ordinals.end())
        return it->second;
    int value = g_side->ordinals.size();
    g_side->ordinals[pointer] = value;
    return value;
}

long long tag(const CEditorBaseObject* object)
{
    return object ? object->getGuid() : -2;
}

template <class T>
void poke(void* base, int offset, T value)
{
    std::memcpy(static_cast<char*>(base) + offset, &value, sizeof(T));
}

template <class T>
T peek(const void* base, int offset)
{
    T value;
    std::memcpy(&value, static_cast<const char*>(base) + offset, sizeof(T));
    return value;
}

char* zeroed(unsigned int size)
{
    char* memory = static_cast<char*>(operator new(size));
    std::memset(memory, 0, size);
    return memory;
}

int compareSides(const tlhybrid_host* host, const char* what, int round)
{
    const std::string& a = g_sides[0].log;
    const std::string& b = g_sides[1].log;
    if (a == b)
        return 0;
    unsigned int at = 0;
    while (at < a.size() && at < b.size() && a[at] == b[at])
        at++;
    unsigned int from = at > 200 ? at - 200 : 0;
    host->log("    %s round %d differs at %u\n    original:   %s\n    decompiled: %s\n", what, round, at,
              a.substr(from, 400).c_str(), b.substr(from, 400).c_str());
    return 1;
}

// Editor objects: the recorded virtuals and per-slot property values.
class TestObject : public CEditorBaseObject
{
public:
    TestObject()
    {
        std::memset(m_Values, 0, sizeof(m_Values));
        std::memset(m_Counts, 0, sizeof(m_Counts));
    }

    virtual void setParentGuid(long long guid)
    {
        record("setparent %lld %lld\n", getGuid(), guid);
        CEditorBaseObject::setParentGuid(guid);
    }

    virtual void SetName(const std::wstring& name)
    {
        record("setname %lld %s\n", getGuid(), text(name).c_str());
        CEditorBaseObject::SetName(name);
    }

    virtual void BroadcastEvent(unsigned int event)
    {
        record("broadcast %lld %u\n", getGuid(), event);
    }

    int m_Values[kValueSlots][kMaxValues];
    unsigned int m_Counts[kValueSlots];
};

void setGuids(CEditorBaseObject* object, long long guid, long long parent, long long original)
{
    poke(object, 0x10, guid);
    poke(object, 0x18, parent);
    poke(object, 0x20, original);
}

void setDescriptor(CEditorBaseObject* object, CDescriptor* descriptor)
{
    poke(object, 0x38, descriptor);
}

ObjectMap& sceneObjects(char* scene)
{
    return *reinterpret_cast<ObjectMap*>(scene + kSceneObjects);
}

TestObject* newObject(CDescriptor* descriptor)
{
    TestObject* object = new TestObject;
    long long guid = g_side->nextGuid++;
    setGuids(object, guid, -1, guid);
    setDescriptor(object, descriptor);
    object->CEditorBaseObject::SetSceneOwner(reinterpret_cast<CEditorScene*>(g_side->scene));
    sceneObjects(g_side->scene)[guid] = object;
    return object;
}

void randomValues(TestObject* object, unsigned int minimum, unsigned int range, int maxValue)
{
    for (int k = 0; k < kValueSlots; k++)
    {
        object->m_Counts[k] = minimum + nextRandom() % range;
        for (unsigned int i = 0; i < kMaxValues; i++)
            object->m_Values[k][i] = nextRandom() % maxValue;
    }
}

void dumpObject(CEditorBaseObject* base)
{
    TestObject* object = static_cast<TestObject*>(base);
    std::string values;
    for (int k = 0; k < kValueSlots; k++)
    {
        values += " [";
        for (unsigned int i = 0; i < object->m_Counts[k]; i++)
        {
            char buffer[16];
            std::sprintf(buffer, " %d", object->m_Values[k][i]);
            values += buffer;
        }
        values += " ]";
    }
    record("object %lld parent %lld original %lld name %s%s\n", object->getGuid(), object->getParentGuid(),
           object->getOriginalGuid(), text(object->getName()).c_str(), values.c_str());
}

// Property accessors; each slot reads and writes its own values on a TestObject.
template <int K>
UNIONDATA8BIT* getValue(CEditorBaseObject* base, unsigned int& bytes)
{
    TestObject* object = static_cast<TestObject*>(base);
    record("get %d %lld\n", K, object->getGuid());
    bytes = object->m_Counts[K] * sizeof(int);
    return reinterpret_cast<UNIONDATA8BIT*>(object->m_Values[K]);
}

template <int K>
void setValue(CEditorBaseObject* base, const UNIONDATA32BIT* data, unsigned int count)
{
    TestObject* object = static_cast<TestObject*>(base);
    std::string values;
    for (unsigned int i = 0; i < count; i++)
    {
        char buffer[16];
        std::sprintf(buffer, " %d", data[i].m_iValue);
        values += buffer;
    }
    record("set %d %lld %u%s\n", K, object->getGuid(), count, values.c_str());
    object->m_Counts[K] = count < kMaxValues ? count : kMaxValues;
    std::memmove(object->m_Values[K], data, object->m_Counts[K] * sizeof(int));
}

typedef UNIONDATA8BIT* (*Getter)(CEditorBaseObject*, unsigned int&);
typedef void (*Setter)(CEditorBaseObject*, const UNIONDATA32BIT*, unsigned int);

void* const g_getters[kValueSlots] = {
    reinterpret_cast<void*>(static_cast<Getter>(&getValue<0>)), reinterpret_cast<void*>(static_cast<Getter>(&getValue<1>)),
    reinterpret_cast<void*>(static_cast<Getter>(&getValue<2>)), reinterpret_cast<void*>(static_cast<Getter>(&getValue<3>)),
    reinterpret_cast<void*>(static_cast<Getter>(&getValue<4>)), reinterpret_cast<void*>(static_cast<Getter>(&getValue<5>))};
void* const g_setters[kValueSlots] = {
    reinterpret_cast<void*>(static_cast<Setter>(&setValue<0>)), reinterpret_cast<void*>(static_cast<Setter>(&setValue<1>)),
    reinterpret_cast<void*>(static_cast<Setter>(&setValue<2>)), reinterpret_cast<void*>(static_cast<Setter>(&setValue<3>)),
    reinterpret_cast<void*>(static_cast<Setter>(&setValue<4>)), reinterpret_cast<void*>(static_cast<Setter>(&setValue<5>))};

unsigned int testStringToIndex(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*)
{
    return 0;
}

std::wstring testIndexToString(CEditorScene*, CEditorBaseObject*, unsigned int, void*)
{
    return std::wstring();
}

std::string groupName(CDataGroup* group)
{
    return group ? text(group->GetGroupName()) : std::string("-");
}

// Properties get a copy of the original vtable whose save/load slots record.
void recordSaveProperty(CDescriptorProp* property, CEditorBaseObject* object, CDataGroup* group)
{
    record("saveproperty %s %lld %s\n", text(property->m_sName).c_str(), tag(object), groupName(group).c_str());
}

void recordLoadProperty(CDescriptorProp* property, CEditorBaseObject* object, CDataGroup* group,
                        unsigned int version)
{
    record("loadproperty %s %lld %s %u\n", text(property->m_sName).c_str(), tag(object), groupName(group).c_str(),
           version);
}

void* g_propertyVtable[kPropertySlots + 2];

CDescriptorProp* makeProperty(int slot, const std::wstring& name, EVARIABLE_TYPES type, int flags)
{
    CDescriptorProp* property =
        new CDescriptorProp(L"CATEGORY", name, L"DESCRIPTION", g_setters[slot], g_getters[slot], type, flags);
    void** vptr = *reinterpret_cast<void***>(property);
    if (g_propertyVtable[2] == NULL)
    {
        std::memcpy(g_propertyVtable, vptr - 2, sizeof(g_propertyVtable));
        g_propertyVtable[2 + 2] = reinterpret_cast<void*>(&recordSaveProperty);
        g_propertyVtable[2 + 3] = reinterpret_cast<void*>(&recordLoadProperty);
    }
    *reinterpret_cast<void***>(property) = g_propertyVtable + 2;
    return property;
}

class TestDescriptor : public CDescriptor
{
public:
    TestDescriptor(int flags) : CDescriptor(flags) {}

    virtual CEditorBaseObject* CreateObject(CEditorScene*) { return NULL; }

    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject* object)
    {
        record("inited %lld\n", tag(object));
    }

    virtual bool saveAdditionalInfo(CEditorBaseObject* object, std::ofstream* file, CDataGroup* group,
                                    CDescriptorSaveConfiguration* configuration)
    {
        record("saveinfo %lld %d %s %d\n", tag(object), file != NULL, groupName(group).c_str(),
               ordinal(configuration));
        return false;
    }

    virtual bool loadAdditionalInfo(CEditorBaseObject* object, COgreReader* reader, CDataGroup* group,
                                    CDescriptorLoadConfiguration* configuration)
    {
        record("loadinfo %lld %d %s %d\n", tag(object), reader != NULL, groupName(group).c_str(),
               ordinal(configuration));
        return true;
    }

    virtual void InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender)
    {
        record("input %lld %u %lld\n", tag(object), event, tag(sender));
    }

    TArrayList<std::wstring>& parentFilters() { return m_ParentFilters; }
    std::wstring& name() { return m_sName; }
    unsigned int& flags() { return m_iFlags; }
    unsigned int& id() { return m_iID; }
    std::map<std::wstring, unsigned int>& propertyIDs() { return m_PropertyIDs; }
    TArrayList<CDescriptorProp*>& properties() { return m_Properties; }
    TArrayList<CDescriptorProp*>& defaults() { return m_DefaultProperties; }
    TArrayList<CEditorBaseObject*>& objects() { return m_Objects; }
    TArrayList<CLogicWrapper*>& inputs() { return m_InputLogicWrappers; }
    TArrayList<CLogicWrapper*>& outputs() { return m_OutputLogicWrappers; }
    std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>& logicObjects() { return m_OutputLogicObjects; }
};

// Side A's descriptors call the original saveObject through their vtable.
void* g_descriptorVtableA[kDescriptorSlots + 2];

TestDescriptor* makeDescriptor(int side, const std::wstring& name, int flags)
{
    TestDescriptor* descriptor = new TestDescriptor(flags);
    if (side == 0)
    {
        if (g_descriptorVtableA[2] == NULL)
        {
            void** vptr = *reinterpret_cast<void***>(descriptor);
            std::memcpy(g_descriptorVtableA, vptr - 2, sizeof(g_descriptorVtableA));
            g_descriptorVtableA[2 + kSaveObjectSlot] = reinterpret_cast<void*>(&originalSaveObject);
        }
        *reinterpret_cast<void***>(descriptor) = g_descriptorVtableA + 2;
    }
    descriptor->name() = name;
    descriptor->CEditorBaseObject::SetSceneOwner(reinterpret_cast<CEditorScene*>(g_side->scene));
    ordinal(descriptor);
    return descriptor;
}

std::wstring sideName(const wchar_t* base, int side, int round)
{
    wchar_t buffer[64];
    std::swprintf(buffer, 64, L"%ls_%c%d", base, side ? L'B' : L'A', round);
    return buffer;
}

const wchar_t* const kNames[] = {L"VALUE", L"VALUE_", L"COLOR", L"SIZE", L"", L"ON"};
const int kNameCount = sizeof(kNames) / sizeof(kNames[0]);

std::wstring randomName()
{
    return kNames[nextRandom() % kNameCount];
}

std::wstring randomText(unsigned int maxLength, unsigned int maxChar)
{
    std::wstring value;
    unsigned int length = nextRandom() % (maxLength + 1);
    for (unsigned int i = 0; i < length; i++)
        value += static_cast<wchar_t>(0x20 + nextRandom() % (maxChar - 0x20));
    return value;
}

int slotOf(void* function, void* const* table)
{
    for (int i = 0; i < kValueSlots; i++)
    {
        if (table[i] == function)
            return i;
    }
    return function ? 99 : -1;
}

void dumpProperty(const char* what, CDescriptorProp* property)
{
    if (property == NULL)
    {
        record("  %s null\n", what);
        return;
    }
    record("  %s %d %s [%s] [%s] type %d flags %x set %d get %d\n", what, ordinal(property),
           text(property->m_sName).c_str(), text(property->m_sCategory).c_str(),
           text(property->m_sDescription).c_str(), property->m_eType, property->m_iFlags,
           slotOf(property->m_pSetFunction, g_setters), slotOf(property->m_pGetFunction, g_getters));
    if (property->m_pInterpreter)
        record("    interpreter %p %p %p\n", peek<void*>(property->m_pInterpreter, 0x10),
               peek<void*>(property->m_pInterpreter, 0x18), peek<void*>(property->m_pInterpreter, 0x20));
    record("    defaults");
    for (unsigned int i = 0; i < property->m_DefaultValue.size(); i++)
        record(" %d", property->m_DefaultValue[i].m_iValue);
    record("\n    links");
    for (unsigned int i = 0; i < property->m_LinkedProperties.size(); i++)
        record(" %d", ordinal(property->m_LinkedProperties[i]));
    record("\n");
}

void dumpDescriptor(TestDescriptor* descriptor)
{
    record("descriptor %d flags %x id %u\n", ordinal(descriptor), descriptor->flags(), descriptor->id());
    for (std::map<std::wstring, unsigned int>::iterator it = descriptor->propertyIDs().begin();
         it != descriptor->propertyIDs().end(); ++it)
        record("  name %s %u\n", text(it->first).c_str(), it->second);
    for (unsigned int i = 0; i < descriptor->properties().size(); i++)
        dumpProperty("property", descriptor->properties()[i]);
    for (unsigned int i = 0; i < descriptor->defaults().size(); i++)
        dumpProperty("default", descriptor->defaults()[i]);
    for (unsigned int i = 0; i < descriptor->objects().size(); i++)
        record("  object %lld\n", tag(descriptor->objects()[i]));
    for (unsigned int i = 0; i < descriptor->inputs().size(); i++)
    {
        CLogicWrapper* wrapper = descriptor->inputs()[i];
        record("  input %s %u %d\n", text(wrapper->m_sName).c_str(), wrapper->m_iID, ordinal(wrapper->m_pDescriptor));
    }
    for (unsigned int i = 0; i < descriptor->outputs().size(); i++)
    {
        CLogicWrapper* wrapper = descriptor->outputs()[i];
        record("  output %s %u %d\n", text(wrapper->m_sName).c_str(), wrapper->m_iID, ordinal(wrapper->m_pDescriptor));
    }
}

void dumpGroup(CDataGroup* group, int depth)
{
    std::string indent(depth * 2, ' ');
    record("%sgroup %s\n", indent.c_str(), groupName(group).c_str());
    for (unsigned int i = 0; i < group->m_DataValues.size(); i++)
    {
        CDataValue* value = group->m_DataValues[i];
        record("%s  %s = %s (%s)\n", indent.c_str(), text(dataValueName(value)).c_str(),
               text(dataValueText(value)).c_str(), text(dataValueType(value)).c_str());
    }
    for (unsigned int i = 0; i < group->m_DataGroups.size(); i++)
        dumpGroup(group->m_DataGroups[i], depth + 1);
}

CDataGroup* newGroup(const wchar_t* name)
{
    return new CDataGroup(name, NULL, 10, 10, NULL);
}

// Fake scene: only the slots and members the descriptor uses.
Side* sideOf(char* scene)
{
    return peek<Side*>(scene, kSceneSide);
}

CEditorBaseObject* sceneCreateObject(char* scene, CDescriptor* descriptor, CEditorBaseObject* parent,
                                     CEditorBaseObject* owner, bool load)
{
    record("create %d %d %d %d\n", ordinal(descriptor), parent != NULL, owner != NULL, load);
    if (sideOf(scene)->failCreate)
        return NULL;
    return newObject(descriptor);
}

void sceneDeleteObject(char*, CEditorBaseObject* object)
{
    record("delete %lld\n", tag(object));
    object->getDescriptor()->EditorSceneRemovingObject(object);
}

void sceneEventFired(char* scene, unsigned int event, CDescriptor* descriptor, CEditorBaseObject* object)
{
    Side* side = sideOf(scene);
    record("fired %u %d %lld\n", event, ordinal(descriptor), tag(object));
    if (side->flipOnFire)
        side->resources[kResourceLogicEnabled] = !side->resources[kResourceLogicEnabled];
}

void* g_sceneVtable[kSceneSlots];

void setDebugLogic(int value)
{
    g_side->ints.assign(KSETTINGS_DEBUG_LOGIC + 1, 0);
    g_side->ints[KSETTINGS_DEBUG_LOGIC] = value;
    int* begin = &g_side->ints[0];
    poke(g_side->settings, kSettingsInts, begin);
    poke(g_side->settings, kSettingsInts + 8, begin + g_side->ints.size());
}

class LogRecorder : public Ogre::LogListener
{
public:
    virtual void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel level, bool maskDebug,
                               const Ogre::String&)
    {
        if (g_side)
            g_side->log += "log " + message + (level == Ogre::LML_CRITICAL && !maskDebug ? "\n" : " ?\n");
    }
};

LogRecorder g_logRecorder;

// Some original callees log (CDescriptorLoadConfiguration::addRemap on a
// duplicate id); before main there is no LogManager yet.
void prepareLog()
{
    static bool prepared = false;
    if (prepared)
        return;
    prepared = true;
    Ogre::LogManager* manager = Ogre::LogManager::getSingletonPtr();
    if (manager == NULL)
        manager = new Ogre::LogManager();
    manager->createLog("tlhybrid-descriptor-test.log", true, false, true)->addListener(&g_logRecorder);
}

void beginSide(int index)
{
    prepareLog();
    g_side = &g_sides[index];
    g_side->log.clear();
    g_side->ordinals.clear();
    g_side->nextGuid = 1000;
    g_side->failCreate = false;
    g_side->flipOnFire = false;

    if (g_sceneVtable[kSceneCreateSlot] == NULL)
    {
        g_sceneVtable[kSceneCreateSlot] = reinterpret_cast<void*>(&sceneCreateObject);
        g_sceneVtable[kSceneDeleteSlot] = reinterpret_cast<void*>(&sceneDeleteObject);
        g_sceneVtable[kSceneEventSlot] = reinterpret_cast<void*>(&sceneEventFired);
    }
    g_side->scene = zeroed(kSceneSize);
    poke(g_side->scene, 0, &g_sceneVtable[0]);
    new (g_side->scene + kSceneObjects) ObjectMap();
    std::memset(g_side->resources, 0, sizeof(g_side->resources));
    std::memset(g_side->settings, 0, sizeof(g_side->settings));
    g_side->resources[kResourceLogicEnabled] = 1;
    poke(g_side->scene, kSceneResourceManager, &g_side->resources[0]);
    poke(g_side->scene, kSceneSettings, &g_side->settings[0]);
    poke(g_side->scene, kSceneSide, g_side);
    setDebugLogic(0);
}

} // namespace

TL_ORIGINAL(void, nextOriginalCtor,(void*,int),"_ZN11CDescriptorC1Ei")
extern "C" void nextCandidateCtor(void*,int) __asm__("_ZN11CDescriptorC1Ei");
TL_ORIGINAL(CEditorBaseObject*,nextOriginalPost,(void*,CDataGroup*,CDescriptorLoadConfiguration*),"_ZN11CDescriptor17postProcessObjectEP10CDataGroupP28CDescriptorLoadConfiguration")
extern "C" CEditorBaseObject* nextCandidatePost(void*,CDataGroup*,CDescriptorLoadConfiguration*) __asm__("_ZN11CDescriptor17postProcessObjectEP10CDataGroupP28CDescriptorLoadConfiguration");
TL_ORIGINAL(void,nextOriginalSerialize,(void*,CDataGroup*,unsigned),"_ZN11CDescriptor19SerializeDescriptorEP10CDataGroupj")
extern "C" void nextCandidateSerialize(void*,CDataGroup*,unsigned) __asm__("_ZN11CDescriptor19SerializeDescriptorEP10CDataGroupj");
TL_ORIGINAL(void,nextOriginalList,(void*,CEditorBaseObject*,unsigned,std::vector<std::wstring>&),"_ZN11CDescriptor23GetPropertyListOfValuesEP17CEditorBaseObjectjRSt6vectorISbIwSt11char_traitsIwESaIwEESaIS6_EE")
extern "C" void nextCandidateList(void*,CEditorBaseObject*,unsigned,std::vector<std::wstring>&) __asm__("_ZN11CDescriptor23GetPropertyListOfValuesEP17CEditorBaseObjectjRSt6vectorISbIwSt11char_traitsIwESaIwEESaIS6_EE");
TL_FUNCTION(nextListValue,"_ZN15CDescriptorProp19getListValueByIndexEP12CEditorSceneP17CEditorBaseObjectj")
namespace {
struct NextCase { unsigned op,seed; };NextCase*nextCase;TestDescriptor*nextDescriptor;
std::wstring nextValue(void*p,CEditorScene*scene,CEditorBaseObject*object,unsigned index){
 record("list %d scene %d object %lld index %u\n",ordinal(p),ordinal(scene),tag(object),index);
 if(nextCase->seed%5==1)nextDescriptor->CEditorBaseObject::SetSceneOwner(index%2?reinterpret_cast<CEditorScene*>(g_side->scene):NULL);
 const wchar_t*items[]={L"alpha",L"",L"alpha",L"\x3a9\x4f60",L"omega",L"omega"};
 if(nextCase->seed%7==0)return L"supercalaphasticexpelodotues";
 unsigned limit=nextCase->seed%6;return items[index>=limit?limit:index];
}
void nextSide(void*p,autotest::Capture&out,bool ours){NextCase&c=*static_cast<NextCase*>(p);nextCase=&c;g_seed=c.seed*71329+19;beginSide(0);
 if(c.op==0){unsigned long long storage[(sizeof(TestDescriptor)+7)/8];std::memset(storage,(c.seed*37+3)&255,sizeof(storage));void(*fn)(void*,int)=ours?nextCandidateCtor:nextOriginalCtor;
  int flags=(c.seed&1)?int(1u<<((c.seed/2)%32)):int(c.seed*0x7891345u);
  if(!autotest::beginInvocation(out,fn))return;fn(storage,flags);out.callCompleted=1;out.add(storage,sizeof(TestDescriptor));
  TestDescriptor*d=reinterpret_cast<TestDescriptor*>(storage);dumpDescriptor(d);record("base %lld %lld %lld %s\n",d->getGuid(),d->getParentGuid(),d->getOriginalGuid(),text(d->getName()).c_str());
  for(unsigned offset=0x58;offset<=0x70;offset+=8)record("string %u %s\n",offset,text(*reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(storage)+offset)).c_str());
 }else{
  TestDescriptor*d=makeDescriptor(0,L"TYPE",c.seed*0x1f43u);nextDescriptor=d;d->id()=c.seed*17;TestObject*object=newObject(d);d->objects().add(object);
  unsigned count=(c.seed/3)%7;for(unsigned i=0;i<count;++i){CDescriptorProp*prop=makeProperty(i%kValueSlots,randomName(),static_cast<EVARIABLE_TYPES>(i%10),int(c.seed*7+i));d->properties().add(prop);}
  if(c.op==1){CDescriptorLoadConfiguration*config=new CDescriptorLoadConfiguration;config->m_iParentGuid=900+(c.seed%13);
   for(unsigned i=0;i<5;++i)if((c.seed>>i)&1)config->addRemap(300+i,1000+(i%3));
   for(unsigned i=0;i<c.seed%4;++i){TestObject*another=newObject(d);d->objects().add(another);}
   CDataGroup*group=newGroup(L"PROPERTIES");if(c.seed%4)group->AddDataValue(L"ID",static_cast<long long>(299+(c.seed/4)%7));if(c.seed%3)group->AddDataValue(L"PARENTID",static_cast<long long>(299+(c.seed/9)%7));
   if(c.seed%11==0)d->CEditorBaseObject::SetSceneOwner(NULL);
   CEditorBaseObject*(*fn)(void*,CDataGroup*,CDescriptorLoadConfiguration*)=ours?nextCandidatePost:nextOriginalPost;
   if(!autotest::beginInvocation(out,fn))return;CEditorBaseObject*ret=fn(d,group,c.seed%13?config:NULL);out.callCompleted=1;record("returned %lld\n",tag(ret));dumpGroup(group,0);
   for(long long id=299;id<307;++id)record("remap %lld %lld\n",id,config->getRemappedID(id));
  }else if(c.op==2){
   for(unsigned off=0x58;off<=0x70;off+=8)*reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(d)+off)=randomText(20,0x530);
   for(unsigned i=0;i<(c.seed/7)%6;++i)d->AddInputLogic(randomName(),c.seed+i);
   for(unsigned i=0;i<(c.seed/11)%6;++i)d->AddOutputLogic(randomName(),c.seed-i);
   TArrayList<std::wstring>&filters=d->parentFilters();
   for(unsigned i=0;i<c.seed%5;++i)filters.add(randomName());
   CDataGroup*group=newGroup(L"ROOT");group->AddDataValue(L"BEFORE",c.seed);if(c.seed&1)group->AddDataGroup(L"OBJECT")->AddDataValue(L"OLD",true);
   void(*fn)(void*,CDataGroup*,unsigned)=ours?nextCandidateSerialize:nextOriginalSerialize;if(!autotest::beginInvocation(out,fn))return;fn(d,c.seed%13?group:NULL,c.seed*7919u);out.callCompleted=1;dumpGroup(group,0);
  }else{
   std::vector<std::wstring>values;unsigned before=(c.seed/5)%6;for(unsigned i=0;i<before;++i)values.push_back(i%2?L"alpha":L"prefix");
   detour::Set patches;TL_REDIRECT(patches,nextListValue,&nextValue);if(patches.failed())_exit(41);
   unsigned index=c.seed%9==0?0xffffffffu:c.seed%8;
   void(*fn)(void*,CEditorBaseObject*,unsigned,std::vector<std::wstring>&)=ours?nextCandidateList:nextOriginalList;if(!autotest::beginInvocation(out,fn))return;fn(d,c.seed&8?object:NULL,index,values);out.callCompleted=1;patches.restore();
   record("values %lu capacity %lu\n",static_cast<unsigned long>(values.size()),static_cast<unsigned long>(values.capacity()));for(unsigned i=0;i<values.size();++i)record("value %s\n",text(values[i]).c_str());
  }
  dumpDescriptor(d);for(ObjectMap::iterator it=sceneObjects(g_side->scene).begin();it!=sceneObjects(g_side->scene).end();++it)dumpObject(it->second);
 }
 out.addText(g_side->log);out.add(g_side->resources,sizeof(g_side->resources));
}
void nextOriginal(void*p,autotest::Capture&out){nextSide(p,out,false);}void nextRecovered(void*p,autotest::Capture&out){nextSide(p,out,true);}
int nextRun(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)nextOriginalCtor,(uint64_t)(uintptr_t)nextOriginalPost,(uint64_t)(uintptr_t)nextOriginalSerialize,(uint64_t)(uintptr_t)nextOriginalList};autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<480;++n){NextCase c={op,n};autotest::Outcome a,b;autotest::runChild(nextOriginal,&c,a);autotest::runChild(nextRecovered,&c,b);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    descriptor next %u/%u status %d/%d first %lu bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(size_t k=at;k<a.capture.length&&k<b.capture.length&&k<at+160;++k)host->log("%02x/%02x ",(unsigned char)a.capture.data[k],(unsigned char)b.capture.data[k]);host->log("\n");coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(descriptor_next_ctor){return nextRun(host,0,"descriptor_next_ctor");}
TL_TEST(descriptor_next_post){return nextRun(host,1,"descriptor_next_post");}
TL_TEST(descriptor_next_serialize){return nextRun(host,2,"descriptor_next_serialize");}
TL_TEST(descriptor_next_list){return nextRun(host,3,"descriptor_next_list");}
