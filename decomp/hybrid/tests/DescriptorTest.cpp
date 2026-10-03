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

#include "HybridTest.h"
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
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
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

TL_TEST(Descriptor_logicWrappers)
{
    int failures = 0;
    for (int round = 0; round < 300 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            TestDescriptor* d = makeDescriptor(s, L"WRAPPERS", 0);
            unsigned int inputs = nextRandom() % 6;
            for (unsigned int i = 0; i < inputs; i++)
            {
                std::wstring name = randomName();
                unsigned int id = nextRandom() % 50;
                record("addinput %u\n", s == 0 ? originalAddInputLogic(d, name, id) : d->AddInputLogic(name, id));
            }
            unsigned int outputs = nextRandom() % 6;
            for (unsigned int i = 0; i < outputs; i++)
            {
                std::wstring name = randomName();
                d->AddOutputLogic(name, nextRandom() % 50);
            }
            if (inputs && nextRandom() % 3 == 0)
                d->inputs().add(d->inputs()[nextRandom() % inputs]);
            if (outputs && nextRandom() % 3 == 0)
                d->outputs().add(d->outputs()[nextRandom() % outputs]);
            dumpDescriptor(d);

            std::vector<CLogicWrapper*> probes;
            probes.push_back(NULL);
            for (unsigned int i = 0; i < d->inputs().size(); i++)
                probes.push_back(d->inputs()[i]);
            for (unsigned int i = 0; i < d->outputs().size(); i++)
                probes.push_back(d->outputs()[i]);
            probes.push_back(reinterpret_cast<CLogicWrapper*>(g_side));
            for (unsigned int i = 0; i < probes.size(); i++)
            {
                unsigned int in = s == 0 ? originalGetInputFuncIndex(d, probes[i])
                                         : d->GetInputLogicFuncIndexByWrapper(probes[i]);
                unsigned int out = s == 0 ? originalGetOutputFuncIndex(d, probes[i])
                                          : d->GetOutputLogicFuncIndexByWrapper(probes[i]);
                record("probe %u %u\n", in, out);
            }
        }
        failures += compareSides(host, "logic wrappers", round);
    }
    return failures;
}

TL_TEST(Descriptor_addProperty)
{
    int failures = 0;
    for (int round = 0; round < 200 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            // The descriptor controller shares properties by descriptor name.
            std::wstring type = sideName(L"TLTEST_PROPERTIES", s, round);
            TestDescriptor* descriptors[2] = {makeDescriptor(s, type, 0), makeDescriptor(s, type, 0)};
            for (int k = 0; k < 2; k++)
            {
                TestDescriptor* d = descriptors[k];
                unsigned int count = 1 + nextRandom() % 7;
                for (unsigned int i = 0; i < count; i++)
                {
                    std::wstring category = randomName();
                    std::wstring name = randomName();
                    std::wstring description = randomName();
                    int slot = nextRandom() % kValueSlots;
                    void* set = nextRandom() % 10 ? g_setters[slot] : NULL;
                    void* get = nextRandom() % 10 ? g_getters[slot] : NULL;
                    EVARIABLE_TYPES variable = static_cast<EVARIABLE_TYPES>(nextRandom() % VARIABLE_TYPE_COUNT);
                    int flags = nextRandom() % 0x200;
                    unsigned int id;
                    if (nextRandom() % 2)
                    {
                        id = s == 0 ? originalAddProperty(d, category, name, description, set, get, variable, flags)
                                    : d->AddProperty(category, name, description, set, get, variable, flags);
                    }
                    else
                    {
                        PropertyStringToIndexFunction toIndex = &testStringToIndex;
                        PropertyIndexToStringFunction toString = &testIndexToString;
                        void* user = reinterpret_cast<void*>(static_cast<unsigned long>(nextRandom() % 3) * 16);
                        id = s == 0 ? originalAddPropertyWithInterpreter(d, category, name, description, set, get,
                                                                         toIndex, toString, user, variable, flags)
                                    : d->AddPropertyWithInterpreterFunctions(category, name, description, set, get,
                                                                             toIndex, toString, user, variable,
                                                                             flags);
                    }
                    record("add %u\n", id);
                }
            }
            dumpDescriptor(descriptors[0]);
            dumpDescriptor(descriptors[1]);
        }
        failures += compareSides(host, "add property", round);
    }
    return failures;
}

TL_TEST(Descriptor_propertyValues)
{
    int failures = 0;
    for (int round = 0; round < 400 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            int scenario = nextRandom() % 5;
            if (scenario == 0)
            {
                // getUniqueNumericValueRepresentation over long names and NULL properties.
                TestDescriptor* d = makeDescriptor(s, randomText(40, 0x3000), 0);
                unsigned int count = nextRandom() % 5;
                for (unsigned int i = 0; i < count; i++)
                {
                    std::wstring name = randomText(30, 0x500);
                    EVARIABLE_TYPES variable = static_cast<EVARIABLE_TYPES>(nextRandom() % VARIABLE_TYPE_COUNT);
                    d->properties().add(nextRandom() % 5 ? makeProperty(i % kValueSlots, name, variable, 0) : NULL);
                }
                record("unique %lld\n", s == 0 ? originalUniqueValue(d) : d->getUniqueNumericValueRepresentation());
                continue;
            }

            TestDescriptor* d = makeDescriptor(s, L"VALUES", 0);
            unsigned int count = nextRandom() % 5;
            for (unsigned int i = 0; i < count; i++)
            {
                wchar_t name[8];
                std::swprintf(name, 8, L"P%u", i);
                d->properties().add(nextRandom() % 6 ? makeProperty(i % kValueSlots, name, VARIABLE_TYPE_INTEGER, 0)
                                                     : NULL);
            }
            if (scenario == 1)
            {
                unsigned int links = nextRandom() % 8;
                for (unsigned int i = 0; i < links; i++)
                {
                    unsigned int a = nextRandom() % (count + 2);
                    unsigned int b = nextRandom() % (count + 2);
                    if (s == 0)
                        originalLinkProperty(d, a, b);
                    else
                        d->LinkProperty(a, b);
                }
            }
            else if (scenario == 2)
            {
                // Links only forward: CDescriptorProp::setData follows them recursively.
                for (unsigned int i = 0; i + 1 < count; i++)
                {
                    unsigned int j = i + 1 + nextRandom() % (count - i - 1);
                    if (nextRandom() % 3 == 0 && d->properties()[i] && d->properties()[j])
                        d->properties()[i]->m_LinkedProperties.add(d->properties()[j]);
                }
                TestObject* object = newObject(d);
                randomValues(object, 1, 3, 100);
                unsigned int calls = 1 + nextRandom() % 4;
                for (unsigned int i = 0; i < calls; i++)
                {
                    int data[kMaxValues];
                    for (unsigned int j = 0; j < kMaxValues; j++)
                        data[j] = nextRandom() % 1000;
                    CEditorBaseObject* target = nextRandom() % 6 ? object : NULL;
                    unsigned int index = nextRandom() % (count + 2);
                    const void* values = nextRandom() % 6 ? data : NULL;
                    unsigned int size = nextRandom() % (kMaxValues + 1);
                    if (s == 0)
                        originalSetProperty(d, target, index, values, size);
                    else
                        d->SetProperty(target, index, values, size);
                }
                dumpObject(object);
            }
            else
            {
                TestDescriptor* other = makeDescriptor(s, nextRandom() % 2 ? L"VALUES" : L"OTHER", 0);
                TestDescriptor* choices[3] = {d, other, NULL};
                TestObject* object = newObject(choices[nextRandom() % 3]);
                TestObject* source = newObject(choices[nextRandom() % 3]);
                TestObject* parent = nextRandom() % 2 ? newObject(d) : NULL;
                randomValues(object, 1, 3, 100);
                randomValues(source, 1, 3, 100);
                setGuids(source, source->getGuid(), nextRandom() % 3 ? 77 : -1, source->getOriginalGuid());
                CEditorBaseObject* a = nextRandom() % 8 ? object : NULL;
                CEditorBaseObject* b = nextRandom() % 8 ? source : NULL;
                bool cloned = s == 0 ? originalClone(d, a, b, parent) : d->Clone(a, b, parent);
                record("clone %d\n", cloned);
                dumpObject(object);
            }
            dumpDescriptor(d);
        }
        failures += compareSides(host, "property values", round);
    }
    return failures;
}

TL_TEST(Descriptor_defaults)
{
    int failures = 0;
    for (int round = 0; round < 150 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            std::wstring type = sideName(L"TLTEST_DEFAULTS", s, round);
            for (int k = 0; k < 2; k++)
            {
                // The second descriptor of the type finds the defaults of the first.
                TestDescriptor* d = makeDescriptor(s, type, 0);
                unsigned int count = 1 + nextRandom() % 4;
                for (unsigned int i = 0; i < count; i++)
                {
                    wchar_t name[8];
                    std::swprintf(name, 8, L"P%u", i + nextRandom() % 2);
                    d->properties().add(makeProperty(i % kValueSlots, name, VARIABLE_TYPE_INTEGER, 0));
                }
                if (nextRandom() % 5 == 0)
                    d->defaults().add(makeProperty(0, L"EXISTING", VARIABLE_TYPE_INTEGER, 0));
                TestObject* object = newObject(d);
                randomValues(object, 1, 3, 100);
                if (s == 0)
                    originalCalculateDefaults(d, object);
                else
                    d->calculateDefaultValues(object);
                dumpDescriptor(d);
            }
        }
        failures += compareSides(host, "default values", round);
    }
    return failures;
}

TL_TEST(Descriptor_dataGroups)
{
    int failures = 0;
    for (int round = 0; round < 400 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            int scenario = nextRandom() % 3;
            unsigned int count = nextRandom() % 4;
            if (scenario == 0)
            {
                TestDescriptor* d =
                    makeDescriptor(s, L"SAVED", nextRandom() % 6 ? 0 : CDescriptor::DESCRIPTOR_FLAG_NOT_SAVED);
                for (unsigned int i = 0; i < count; i++)
                    d->properties().add(makeProperty(i, std::wstring(1, L'P') + wchar_t(L'0' + i),
                                                     VARIABLE_TYPE_INTEGER, 0));
                if (nextRandom() % 2)
                {
                    for (unsigned int i = 0; i < count; i++)
                    {
                        CDescriptorProp* initial = makeProperty(i, L"DEFAULT", VARIABLE_TYPE_INTEGER, 0);
                        UNIONDATA32BIT values[2];
                        values[0].m_iValue = nextRandom() % 2;
                        values[1].m_iValue = nextRandom() % 2;
                        initial->setData(values, nextRandom() % 3, NULL);
                        d->defaults().add(initial);
                    }
                }
                unsigned int objects = nextRandom() % 4;
                std::vector<TestObject*> created;
                for (unsigned int i = 0; i < objects; i++)
                {
                    TestObject* object = newObject(d);
                    created.push_back(object);
                    randomValues(object, 1, 2, 2);
                    object->CEditorBaseObject::SetName(randomText(5, 0x80));
                    long long parent = nextRandom() % 3 == 0 ? -1 : (nextRandom() % 2 ? 1000 : 4444);
                    setGuids(object, object->getGuid(), parent, nextRandom() % 4 ? 500 + i : -1);
                    d->objects().add(object);
                }
                CDataGroup* group = nextRandom() % 8 ? newGroup(L"ROOT") : NULL;
                CDescriptorSaveConfiguration* configuration =
                    nextRandom() % 2 ? new CDescriptorSaveConfiguration : NULL;
                ordinal(configuration);
                if (nextRandom() % 2 || created.empty())
                {
                    record("saved %u\n", s == 0 ? originalSaveObjects(d, group, configuration)
                                                : d->saveObjects(group, configuration));
                }
                else
                {
                    TestObject* object = created[nextRandom() % created.size()];
                    if (s == 0)
                        originalSaveObject(d, object, group, configuration);
                    else
                        d->CDescriptor::saveObject(object, group, configuration);
                }
                if (group)
                    dumpGroup(group, 0);
            }
            else if (scenario == 1)
            {
                TestDescriptor* d = makeDescriptor(s, L"LOADED", 0);
                for (unsigned int i = 0; i < count; i++)
                    d->properties().add(makeProperty(i, std::wstring(1, L'P') + wchar_t(L'0' + i),
                                                     VARIABLE_TYPE_INTEGER, 0));
                if (nextRandom() % 10 == 0)
                    d->CEditorBaseObject::SetSceneOwner(NULL);
                g_side->failCreate = nextRandom() % 8 == 0;
                CDescriptorLoadConfiguration* configuration = NULL;
                if (nextRandom() % 8)
                {
                    configuration = new CDescriptorLoadConfiguration;
                    configuration->m_iVersion = nextRandom() % 3;
                }
                ordinal(configuration);
                CDataGroup* root = nextRandom() % 8 ? newGroup(L"LEVEL") : NULL;
                std::vector<CDataGroup*> groups;
                std::vector<long long> ids;
                if (root)
                {
                    root->AddDataGroup(L"DECOY");
                    if (nextRandom() % 6)
                    {
                        CDataGroup* objects = root->AddDataGroup(L"LOADED");
                        unsigned int entries = nextRandom() % 4;
                        const wchar_t* const names[] = {L"PROPERTIES", L"BASEOBJECT", L"OTHER"};
                        for (unsigned int i = 0; i < entries; i++)
                        {
                            CDataGroup* entry = objects->AddDataGroup(names[nextRandom() % 3]);
                            groups.push_back(entry);
                            if (nextRandom() % 5)
                                entry->AddDataValue(L"NAME", randomText(5, 0x80), false);
                            if (nextRandom() % 5)
                            {
                                long long id = nextRandom() % 6 ? 300 + nextRandom() % 5 : -1;
                                ids.push_back(id);
                                entry->AddDataValue(L"ID", id);
                            }
                        }
                    }
                }
                if (nextRandom() % 3 || groups.empty())
                {
                    record("loaded %d\n", s == 0 ? originalLoadObjects(d, root, configuration)
                                                 : d->loadObjects(root, configuration));
                }
                else
                {
                    CDataGroup* group = nextRandom() % 6 ? groups[nextRandom() % groups.size()] : NULL;
                    CEditorBaseObject* object = s == 0 ? originalLoadObject(d, group, configuration)
                                                       : d->loadObject(group, configuration);
                    record("loaded %lld\n", tag(object));
                }
                for (ObjectMap::iterator it = sceneObjects(g_side->scene).begin();
                     it != sceneObjects(g_side->scene).end(); ++it)
                    dumpObject(it->second);
                if (configuration)
                {
                    for (unsigned int i = 0; i < ids.size(); i++)
                        record("remap %lld %lld\n", ids[i], configuration->getRemappedID(ids[i]));
                }
            }
            else
            {
                TestDescriptor* d = makeDescriptor(s, L"POST", 0);
                std::vector<TestObject*> created;
                for (unsigned int i = 0; i < count; i++)
                {
                    created.push_back(newObject(d));
                    d->objects().add(created.back());
                }
                CDescriptorLoadConfiguration* configuration = NULL;
                if (nextRandom() % 8)
                {
                    configuration = new CDescriptorLoadConfiguration;
                    configuration->m_iParentGuid = 900 + nextRandom() % 3;
                    for (long long id = 300; id < 305; id++)
                    {
                        if (nextRandom() % 3)
                            configuration->addRemap(id, 1000 + nextRandom() % 5);
                    }
                }
                ordinal(configuration);
                CDataGroup* root = nextRandom() % 8 ? newGroup(L"LEVEL") : NULL;
                if (root && nextRandom() % 6)
                {
                    CDataGroup* objects = root->AddDataGroup(L"POST");
                    unsigned int entries = nextRandom() % 4;
                    for (unsigned int i = 0; i < entries; i++)
                    {
                        CDataGroup* entry = objects->AddDataGroup(L"PROPERTIES");
                        if (nextRandom() % 5)
                            entry->AddDataValue(L"ID", static_cast<long long>(299 + nextRandom() % 7));
                        if (nextRandom() % 3)
                            entry->AddDataValue(L"PARENTID", static_cast<long long>(299 + nextRandom() % 7));
                    }
                }
                if (s == 0)
                    originalPostProcessObjects(d, root, configuration);
                else
                    d->postProcessObjects(root, configuration);
                for (unsigned int i = 0; i < created.size(); i++)
                    dumpObject(created[i]);
            }
        }
        failures += compareSides(host, "data groups", round);
    }
    return failures;
}

template <class T>
void put(std::string& out, T value)
{
    out.append(reinterpret_cast<const char*>(&value), sizeof(T));
}

TL_TEST(Descriptor_binary)
{
    int failures = 0;
    for (int round = 0; round < 400 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            TestDescriptor* d =
                makeDescriptor(s, L"BINARY", nextRandom() % 8 ? 0 : CDescriptor::DESCRIPTOR_FLAG_NOT_SAVED);
            d->id() = nextRandom() % 100;
            unsigned int count = nextRandom() % 4;
            for (unsigned int i = 0; i < count; i++)
                d->properties().add(makeProperty(i, std::wstring(1, L'P') + wchar_t(L'0' + i), VARIABLE_TYPE_INTEGER,
                                                 nextRandom() % 3 ? 0 : CDescriptorProp::FLAG_NOT_SAVED_IN_BINARY));
            TestObject* parent = newObject(d);
            setGuids(parent, parent->getGuid(), -1, 77);
            TestObject* object = newObject(d);
            CEditorBaseObject* target = nextRandom() % 8 ? object : NULL;
            if (nextRandom() % 2)
            {
                randomValues(object, 1, 3, 1000);
                std::wstring name = randomText(5, 0x80);
                if (nextRandom() % 3 == 0)
                    name += static_cast<wchar_t>(0x10000 + nextRandom() % 0x1000);
                object->CEditorBaseObject::SetName(name);
                long long parentGuid = nextRandom() % 2 ? parent->getGuid() : 4444;
                setGuids(object, object->getGuid(), parentGuid, nextRandom() % 3 ? 600 : -1);
                std::ofstream file;
                std::stringbuf buffer;
                file.std::ios::rdbuf(&buffer);
                bool saved = s == 0 ? originalSaveBinary(d, file, target, NULL) : d->saveObjectInBinaryFile(file, target, NULL);
                record("saved %d\n", saved);
                g_side->log += hex(buffer.str()) + "\n";
            }
            else
            {
                std::string bytes;
                long long guid = 300 + nextRandom() % 5;
                put(bytes, guid);
                put(bytes, static_cast<long long>(nextRandom() % 5));
                unsigned int length = nextRandom() % 5;
                put(bytes, length);
                for (unsigned int i = 0; i < length; i++)
                {
                    if (i + 1 < length && nextRandom() % 4 == 0)
                    {
                        put(bytes, static_cast<unsigned short>(0xd800 + nextRandom() % 0x400));
                        put(bytes, static_cast<unsigned short>(0xdc00 + nextRandom() % 0x400));
                        i++;
                    }
                    else
                    {
                        put(bytes, static_cast<unsigned short>(0x20 + nextRandom() % 0x300));
                    }
                }
                for (unsigned int i = 0; i < count; i++)
                {
                    if (d->properties()[i]->m_iFlags & CDescriptorProp::FLAG_NOT_SAVED_IN_BINARY)
                        continue;
                    unsigned int values = nextRandom() % 4;
                    put(bytes, values);
                    for (unsigned int j = 0; j < values; j++)
                        put(bytes, static_cast<int>(nextRandom() % 1000));
                }
                COgreReader* reader = new COgreReader;
                char* data = zeroed(bytes.size() + 64);
                std::memcpy(data, bytes.data(), bytes.size());
                poke(reader, 0x8, data);
                poke(reader, 0x10, static_cast<unsigned int>(bytes.size()));
                CDescriptorLoadConfiguration* configuration = new CDescriptorLoadConfiguration;
                bool loaded = s == 0 ? originalLoadBinary(d, *reader, target, *configuration)
                                     : d->loadObjectFromBinaryFile(*reader, target, *configuration);
                record("loaded %d position %u remap %lld\n", loaded, peek<unsigned int>(reader, 0x14),
                       configuration->getRemappedID(guid));
                dumpObject(object);
            }
        }
        failures += compareSides(host, "binary", round);
    }
    return failures;
}


// Logic object whose single-link Invoke reaches TestDescriptor::InputLogicEvent
// (CLogicObject: +0x48 scene, +0x60 object id, +0x68, +0x80 links; CLogicLink:
// +0x10 scene, +0x18 descriptor, +0x28 target, +0x30 input, +0x38 output).
char* newLogicObject(TestDescriptor* d, long long objectGuid, unsigned int event, unsigned int input)
{
    char* logic = zeroed(0x98);
    poke(logic, 0x48, g_side->scene);
    poke(logic, 0x60, objectGuid);
    poke(logic, 0x68, logic);
    unsigned int links = nextRandom() % 3;
    char** array = reinterpret_cast<char**>(zeroed(8 * (links + 1)));
    for (unsigned int i = 0; i < links; i++)
    {
        char* link = zeroed(0x40);
        char* target = zeroed(0x98);
        char* output = zeroed(0x28);
        char* in = zeroed(0x28);
        poke(target, 0x48, g_side->scene);
        poke(target, 0x60, static_cast<long long>(nextRandom() % 3 ? 1000 : 5555));
        poke(output, 0x18, nextRandom() % 3 ? event : event + 1);
        poke(in, 0x18, input + i);
        poke(link, 0x10, g_side->scene);
        poke(link, 0x18, d);
        poke(link, 0x28, target);
        poke(link, 0x30, in);
        poke(link, 0x38, output);
        array[i] = link;
    }
    poke(logic, 0x80, array);
    poke(logic, 0x88, links);
    poke(logic, 0x8c, links);
    return logic;
}

TL_TEST(Descriptor_events)
{
    int failures = 0;
    bool logging = true;

    char fakeEditor[0x100];
    std::memset(fakeEditor, 0, sizeof(fakeEditor));
    char* savedEditor = gEditor;
    gEditor = fakeEditor;
    for (int round = 0; round < 600 && failures == 0; round++)
    {
        unsigned int seed = g_seed;
        for (int s = 0; s < 2; s++)
        {
            g_seed = seed;
            beginSide(s);
            TestDescriptor* d = makeDescriptor(s, L"EMITTER", 0);
            if (nextRandom() % 4 == 0)
            {
                unsigned int count = nextRandom() % 6;
                for (unsigned int i = 0; i < count; i++)
                    d->objects().add(newObject(d));
                if (s == 0)
                    originalDeleteAll(d);
                else
                    d->deleteAllObjects();
                record("left %u\n", d->objects().size());
                continue;
            }

            static const int kDebugValues[] = {-1, 0, 1, 2};
            int debug = kDebugValues[nextRandom() % (logging ? 4 : 2)];
            setDebugLogic(debug);
            g_side->resources[kResourceLogicEnabled] = nextRandom() % 4 != 0;
            g_side->flipOnFire = nextRandom() % 3 == 0;
            unsigned int event = nextRandom() % 8 ? nextRandom() % 20 : 0xFFFFFFFF;
            TestObject* target = newObject(d);
            target->CEditorBaseObject::SetName(L"TARGET");
            std::vector<TestObject*> emitters;
            unsigned int count = 1 + nextRandom() % 3;
            for (unsigned int i = 0; i < count; i++)
            {
                TestObject* emitter = newObject(d);
                emitter->CEditorBaseObject::SetName(randomText(4, 0x7f));
                emitters.push_back(emitter);
                if (nextRandom() % 3 == 0)
                    continue;
                TArrayList<CLogicObject*>* list = NULL;
                if (nextRandom() % 4)
                {
                    list = new TArrayList<CLogicObject*>(2);
                    unsigned int entries = nextRandom() % 4;
                    for (unsigned int j = 0; j < entries; j++)
                    {
                        // Invoke's debug output needs real links; only quiet rounds invoke.
                        bool real = debug <= 0 && nextRandom() % 4;
                        long long source = nextRandom() % 4 ? emitter->getGuid() : 5555;
                        list->add(real ? reinterpret_cast<CLogicObject*>(newLogicObject(d, source, event, 100 * i + 10 * j))
                                       : NULL);
                    }
                }
                d->logicObjects()[emitter] = list;
            }
            CEditorBaseObject* object = NULL;
            if (nextRandom() % 10)
                object = nextRandom() % 5 ? emitters[nextRandom() % emitters.size()] : target;
            if (nextRandom() % 12 == 0)
                d->CEditorBaseObject::SetSceneOwner(NULL);
            if (nextRandom() % 12 == 0)
                poke(g_side->scene, kSceneSettings, static_cast<void*>(NULL));
            if (nextRandom() % 12 == 0)
                poke(g_side->scene, kSceneResourceManager, static_cast<void*>(NULL));
            if (s == 0)
                originalBroadcast(d, object, event);
            else
                d->BroadcastEventFromObject(object, event);
            record("enabled %d\n", g_side->resources[kResourceLogicEnabled]);
        }
        failures += compareSides(host, "events", round);
    }
    gEditor = savedEditor;
    g_side = NULL;
    return failures;
}
