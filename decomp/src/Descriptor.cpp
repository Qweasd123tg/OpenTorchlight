#include "EmptyStrings.h"
#include "Descriptor.h"
#include "DataGroup.h"
#include "DescriptorController.h"
#include "LogicWrapper.h"
#include "DescriptorLoadConfiguration.h"
#include "OgreReader.h"
#include "UTFConversion.h"
#include "EditorScene.h"
#include "LogicObject.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "StringUtilities.h"

#include <OgreLogManager.h>

#include <cstring>
#include <fstream>

CDescriptor::CDescriptor(int flags)
    : m_sName(L"Not Set"), m_sDescription(L"Not Set"), m_sIcon(EMPTY_WSTRING), m_iID(0), m_Properties(10),
      m_DefaultProperties(10), m_Objects(25), m_ParentFilters(10)
{
    m_iFlags = flags | DESCRIPTOR_FLAGS_DEFAULT;
}

CLogicWrapper* CDescriptor::GetInputLogicWrapper(unsigned int index)
{
    if (index < m_InputLogicWrappers.size())
        return m_InputLogicWrappers[index];
    return NULL;
}

unsigned int CDescriptor::GetInputLogicFuncIndexByWrapper(CLogicWrapper* wrapper)
{
    if (wrapper == NULL)
        return 0xFFFFFFFF;
    for (unsigned int i = 0; i < m_InputLogicWrappers.size(); i++)
    {
        if (m_InputLogicWrappers[i] == wrapper)
            return i;
    }
    return 0xFFFFFFFF;
}

CLogicWrapper* CDescriptor::GetOutputLogicWrapper(unsigned int index)
{
    if (index < m_OutputLogicWrappers.size())
        return m_OutputLogicWrappers[index];
    return NULL;
}

unsigned int CDescriptor::GetOutputLogicFuncIndexByWrapper(CLogicWrapper* wrapper)
{
    if (wrapper == NULL)
        return 0xFFFFFFFF;
    for (unsigned int i = 0; i < m_OutputLogicWrappers.size(); i++)
    {
        if (m_OutputLogicWrappers[i] == wrapper)
            return i;
    }
    return 0xFFFFFFFF;
}

CDescriptorProp* CDescriptor::GetPropertyByIndex(unsigned int index)
{
    if (index < m_Properties.size())
        return m_Properties[index];
    return NULL;
}

CDescriptorProp* CDescriptor::GetProperty(unsigned int index)
{
    if (index < m_Properties.size())
        return m_Properties[index];
    return NULL;
}

void CDescriptor::deleteAllObjects()
{
    while (m_Objects.size() != 0)
    {
        CEditorBaseObject* object = m_Objects[0];
        if (object && object->getSceneOwner())
            object->getSceneOwner()->DeleteObjectInScene(object);
    }
}

void CDescriptor::LinkProperty(unsigned int property, unsigned int linkedProperty)
{
    CDescriptorProp* source = GetProperty(property);
    CDescriptorProp* linked = GetProperty(linkedProperty);
    if (linked == NULL || source == NULL)
        return;
    source->m_LinkedProperties.add(linked);
}

void CDescriptor::EditorSceneCreatedObject(CEditorBaseObject* object)
{
    m_Objects.add(object);
}

void CDescriptor::SetProperty(CEditorBaseObject* object, unsigned int index, const void* data, unsigned int count)
{
    if (data == NULL || object == NULL)
        return;
    CDescriptorProp* property = GetProperty(index);
    if (property == NULL)
        return;
    property->setData(static_cast<const UNIONDATA32BIT*>(data), count, object);
}

void* CDescriptor::GetPropertyValue(CEditorBaseObject* object, unsigned int index, unsigned int& count)
{
    count = 0;
    if (object == NULL)
        return NULL;
    CDescriptorProp* property = GetProperty(index);
    if (property == NULL)
        return NULL;
    return property->getData(count, object);
}

CEditorBaseObject* CDescriptor::loadObject(CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    CEditorScene* scene = getSceneOwner();
    if (group == NULL || scene == NULL || configuration == NULL)
        return NULL;

    std::wstring groupName(configuration->m_iVersion == 1 ? L"BASEOBJECT" : L"PROPERTIES");
    if (group->GetGroupName() != groupName)
        return NULL;

    std::wstring name = group->GetDataValue(L"NAME", EMPTY_WSTRING);
    long long id = group->GetDataValue(L"ID", -1LL);
    if (id == -1)
        return NULL;

    CEditorBaseObject* object = scene->CreateObjectByDescriptor(this, NULL, NULL, false);
    if (object == NULL)
        return NULL;

    configuration->addRemap(id, object->getGuid());
    object->setOriginalGuid(id);
    object->SetName(name.c_str());
    for (unsigned int i = 0; i < m_Properties.size(); i++)
        m_Properties[i]->loadProperty(object, group, configuration->m_iVersion);
    DescriptorObjectHasBeenInited(object);
    return object;
}

int CDescriptor::loadObjects(CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    if (configuration == NULL || group == NULL || getSceneOwner() == NULL)
        return 0;
    CDataGroup* objects = group->GetDataGroupByName(m_sName, false);
    if (objects == NULL)
        return 0;

    int loaded = 0;
    for (unsigned int i = 0; i < objects->GetNumberOfDataGroups(); i++)
    {
        if (loadObject(objects->GetDataGroup(i), configuration))
            loaded++;
    }
    return loaded;
}

unsigned int CDescriptor::saveObjects(CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    if (m_iFlags & DESCRIPTOR_FLAG_NOT_SAVED)
        return 0;
    if (group == NULL)
        return 0;
    if (m_Objects.size() == 0)
        return 0;

    CDataGroup* objects = group->AddDataGroup(m_sName);
    for (unsigned int i = 0; i < m_Objects.size(); i++)
    {
        CEditorBaseObject* object = m_Objects[i];
        saveObject(object, objects, configuration);
    }
    return m_Objects.size();
}

void CDescriptor::EditorSceneRemovingObject(CEditorBaseObject* object)
{
    m_Objects.remove(object);

    std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>::iterator it = m_OutputLogicObjects.find(object);
    if (it != m_OutputLogicObjects.end())
    {
        delete it->second;
        m_OutputLogicObjects.erase(it);
    }
}

void CDescriptor::cleanForQuickShutDown()
{
    std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>::iterator it = m_OutputLogicObjects.begin();
    if (it != m_OutputLogicObjects.end())
    {
        if (it->second)
        {
            delete it->second;
            it->second = NULL;
        }
        it++;
    }
    m_OutputLogicObjects.clear();
    m_Objects.clear();
}

unsigned int CDescriptor::AddInputLogic(std::wstring name, unsigned int id)
{
    m_InputLogicWrappers.add(new CLogicWrapper(this, id, name));
    return m_InputLogicWrappers.size() - 1;
}

long long CDescriptor::getUniqueNumericValueRepresentation()
{
    long long value = 0;
    unsigned int shift = 0;

    const wchar_t* name = m_sName.c_str();
    for (unsigned int i = 0; i < m_sName.length(); i++)
    {
        value += name[i] << shift;
        shift += 3;
        if (shift > 56)
            shift = 0;
    }

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        CDescriptorProp* property = m_Properties[i];
        if (property == NULL)
            continue;
        value += 1LL << property->getVariableType();
        const wchar_t* propertyName = property->m_sName.c_str();
        for (unsigned int j = 0; j < property->m_sName.length(); j++)
        {
            value += propertyName[j] << shift;
            shift += 7;
            if (shift > 56)
                shift = 0;
        }
    }
    return value;
}

unsigned int CDescriptor::GetOutputLogicWrapperIndex(std::wstring name)
{
    for (unsigned int i = 0; i < m_OutputLogicWrappers.size(); i++)
    {
        if (name == m_OutputLogicWrappers[i]->m_sName)
            return i;
    }
    return 0xFFFFFFFF;
}

unsigned int CDescriptor::GetInputLogicWrapperIndex(std::wstring name)
{
    for (unsigned int i = 0; i < m_InputLogicWrappers.size(); i++)
    {
        if (name == m_InputLogicWrappers[i]->m_sName)
            return i;
    }
    return 0xFFFFFFFF;
}

void CDescriptor::OutputLogicObjectRemove(CEditorBaseObject* object, CLogicObject* logicObject)
{
    if (logicObject == NULL || object == NULL)
        return;
    if (m_OutputLogicObjects.find(object) == m_OutputLogicObjects.end())
        return;
    m_OutputLogicObjects[object]->remove(logicObject);
}

bool CDescriptor::Clone(CEditorBaseObject* object, CEditorBaseObject* source, CEditorBaseObject* parent)
{
    if (source == NULL || object == NULL || object->getDescriptor() == NULL || source->getDescriptor() == NULL)
        return false;
    if (object->getDescriptor()->m_sName != source->getDescriptor()->m_sName)
        return false;

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        if (m_Properties[i])
            m_Properties[i]->cloneValue(object, source);
    }

    long long parentGuid = source->getParentGuid();
    if (parent)
        parentGuid = parent->getGuid();
    object->setParentGuid(parentGuid);
    return true;
}

void CDescriptor::calculateDefaultValues(CEditorBaseObject* object)
{
    if (m_DefaultProperties.size() != 0)
        return;

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        CDescriptorProp* property = CDescriptorController::getDescriptorPropertyByName(this, m_Properties[i]->m_sName, true);
        if (property == NULL)
        {
            property = new CDescriptorProp(m_Properties[i], object);
            CDescriptorController::addDescriptorProperty(this, property, true);
        }
        m_DefaultProperties.add(property);
    }
}

unsigned int CDescriptor::AddOutputLogic(std::wstring name, unsigned int id)
{
    m_OutputLogicWrappers.add(new CLogicWrapper(this, id, name));
    return m_OutputLogicWrappers.size() - 1;
}

unsigned int CDescriptor::GetPropertyID(const std::wstring& name)
{
    std::map<std::wstring, unsigned int>::iterator it = m_PropertyIDs.find(name);
    if (it == m_PropertyIDs.end())
        return 0xFFFFFFFF;
    return it->second;
}

CDescriptorProp* CDescriptor::GetPropertyByName(const std::wstring& name)
{
    std::map<std::wstring, unsigned int>::iterator it = m_PropertyIDs.find(name);
    if (it == m_PropertyIDs.end())
        return NULL;
    return GetProperty(it->second);
}

bool CDescriptor::HasProperty(const std::wstring& name)
{
    return m_PropertyIDs.find(name) != m_PropertyIDs.end();
}

CDescriptor::~CDescriptor()
{
    for (std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>::iterator it = m_OutputLogicObjects.begin();
         it != m_OutputLogicObjects.end(); it++)
    {
        if (it->second)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    m_Objects.clear();
    m_Properties.clear();
    m_OutputLogicWrappers.deleteAll();
    m_OutputLogicWrappers.clear();
    m_InputLogicWrappers.deleteAll();
    m_InputLogicWrappers.clear();
}

unsigned int CDescriptor::AddOutputLogic(EOUTPUT_EVENTS event)
{
    return AddOutputLogic(gOUTPUT_EVENTS_NAMES[event], event);
}

unsigned int CDescriptor::AddInputLogic(EINPUT_EVENTS event)
{
    return AddInputLogic(gINPUT_EVENT_NAMES[event], event);
}

CEditorBaseObject* CDescriptor::postProcessObject(CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    CEditorScene* scene = getSceneOwner();
    if (configuration == NULL || scene == NULL)
        return NULL;

    long long id = group->GetDataValue(L"ID", -1LL);
    id = configuration->getRemappedID(id);
    if (id == -1)
        return NULL;

    CEditorBaseObject* object = scene->GetObjectInScene(id);
    if (object == NULL)
        return NULL;

    long long parentGuid = group->GetDataValue(L"PARENTID", -1LL);
    parentGuid = configuration->getRemappedID(parentGuid);
    if (parentGuid == -1)
        parentGuid = configuration->m_iParentGuid;
    object->setParentGuid(parentGuid);
    loadAdditionalInfo(object, NULL, group, configuration);
    object->BroadcastEvent(OUTPUT_EVENT_INITIALIZED);
    return object;
}

void CDescriptor::postProcessObjects(CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    if (m_Objects.size() == 0 || group == NULL)
        return;
    CDataGroup* objects = group->GetDataGroupByName(m_sName, false);
    if (objects == NULL)
        return;

    for (unsigned int i = 0; i < objects->GetNumberOfDataGroups(); i++)
        postProcessObject(objects->GetDataGroup(i), configuration);
}

bool CDescriptor::saveObjectInBinaryFile(std::ofstream& file, CEditorBaseObject* object,
                                         CDescriptorSaveConfiguration* configuration)
{
    if (object == NULL || (m_iFlags & DESCRIPTOR_FLAG_NOT_SAVED))
        return false;

    file.write(reinterpret_cast<const char*>(&m_iID), sizeof(m_iID));

    long long guid = object->getOriginalGuid();
    if (guid == -1)
        guid = object->getGuid();
    file.write(reinterpret_cast<const char*>(&guid), sizeof(guid));

    CEditorBaseObject* parent = getSceneOwner()->GetObjectInScene(object->getParentGuid());
    long long parentGuid = -1;
    if (parent)
        parentGuid = parent->getOriginalGuid();
    file.write(reinterpret_cast<const char*>(&parentGuid), sizeof(parentGuid));

    std::wstring name = object->getName();
    unsigned int nameLength = name.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    if (nameLength != 0)
    {
        utf16string utf16 = UTF32ToUTF16(name);
        file.write(reinterpret_cast<const char*>(utf16.c_str()), nameLength * sizeof(unsigned short));
    }

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        CDescriptorProp* property = m_Properties[i];
        if (property->m_iFlags & CDescriptorProp::FLAG_NOT_SAVED_IN_BINARY)
            continue;

        unsigned int count;
        UNIONDATA32BIT* data = property->getData(count, object);
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        file.write(reinterpret_cast<const char*>(data), count * sizeof(UNIONDATA32BIT));
    }
    return true;
}

unsigned int CDescriptor::AddProperty(std::wstring category, std::wstring name, std::wstring description,
                                      void* setFunction, void* getFunction, EVARIABLE_TYPES type, int flags)
{
    if (getFunction == NULL || setFunction == NULL)
        return 0xFFFFFFFF;

    while (m_PropertyIDs.find(name) != m_PropertyIDs.end())
        name = name + L"_";

    CDescriptorProp* property = CDescriptorController::getDescriptorPropertyByName(this, name, false);
    if (property == NULL)
    {
        property = new CDescriptorProp(category, name, description, setFunction, getFunction, type, flags);
        CDescriptorController::addDescriptorProperty(this, property, false);
    }

    unsigned int id = m_Properties.size();
    m_PropertyIDs[name] = id;
    m_Properties.add(property);
    return id;
}

unsigned int CDescriptor::AddPropertyWithInterpreterFunctions(std::wstring category, std::wstring name,
                                                              std::wstring description, void* setFunction,
                                                              void* getFunction,
                                                              PropertyStringToIndexFunction stringToIndex,
                                                              PropertyIndexToStringFunction indexToString,
                                                              void* userData, EVARIABLE_TYPES type, int flags)
{
    unsigned int id = AddProperty(category, name, description, setFunction, getFunction, type, flags);
    if (id == 0xFFFFFFFF)
        return id;

    CDescriptorProp* property = GetProperty(id);
    if (property == NULL)
        return 0xFFFFFFFF;
    property->setPropertyInterpreterFunctions(stringToIndex, indexToString, userData);
    return id;
}

bool CDescriptor::loadObjectFromBinaryFile(COgreReader& reader, CEditorBaseObject* object,
                                           CDescriptorLoadConfiguration& configuration)
{
    if (object == NULL)
        return false;

    long long guid = 0;
    long long parentGuid = 0;
    reader.read(&guid, sizeof(guid));
    reader.read(&parentGuid, sizeof(parentGuid));
    object->setOriginalGuid(guid);
    object->setParentGuid(parentGuid);
    configuration.addRemap(guid, object->getGuid());

    unsigned int nameLength = 0;
    reader.read(&nameLength, sizeof(nameLength));
    if (nameLength != 0)
    {
        wchar_t* name = new wchar_t[nameLength + 1];
        memset(name, 0, (nameLength + 1) * sizeof(wchar_t));
        unsigned short utf16[nameLength];
        reader.read(utf16, nameLength * sizeof(unsigned short));
        ReadUTF16ToUTF32(utf16, name, nameLength);
        object->SetName(name);
        if (name)
            delete[] name;
    }

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        CDescriptorProp* property = m_Properties[i];
        if (property->m_iFlags & CDescriptorProp::FLAG_NOT_SAVED_IN_BINARY)
            continue;

        unsigned int count;
        reader.read(&count, sizeof(count));
        UNIONDATA32BIT* data = new UNIONDATA32BIT[count];
        reader.read(data, count * sizeof(UNIONDATA32BIT));
        property->setData(data, count, object);
        if (data)
            delete[] data;
    }
    return true;
}

void CDescriptor::SerializeDescriptor(CDataGroup* group, unsigned int id)
{
    if (group == NULL)
        return;

    CDataGroup* descriptor = group->AddDataGroup(L"OBJECT");
    descriptor->AddDataValue(L"NAME", m_sName, false);
    descriptor->AddDataValue(L"DESCRIPTION", m_sDescription, false);
    descriptor->AddDataValue(L"ICON", m_sIcon, false);
    descriptor->AddDataValue(L"MENUCATEGORY", m_sMenuCategory, false);
    descriptor->AddDataValue(L"ID", id);
    descriptor->AddDataValue(L"CLONABLE", (m_iFlags & DESCRIPTOR_FLAG_CLONABLE) != 0);
    descriptor->AddDataValue(L"CHILDREN", (m_iFlags & DESCRIPTOR_FLAG_CHILDREN) != 0);
    descriptor->AddDataValue(L"DRAGGABLE", (m_iFlags & DESCRIPTOR_FLAG_DRAGGABLE) != 0);
    descriptor->AddDataValue(L"POSITIONABLE", (m_iFlags & DESCRIPTOR_FLAG_POSITIONABLE) != 0);
    descriptor->AddDataValue(L"ROTATEABLE", (m_iFlags & DESCRIPTOR_FLAG_ROTATEABLE) != 0);

    for (unsigned int i = 0; i < m_InputLogicWrappers.size(); i++)
    {
        CDataGroup* function = descriptor->AddDataGroup(L"FUNCTION");
        CLogicWrapper* wrapper = m_InputLogicWrappers[i];
        function->AddDataValue(L"NAME", wrapper->m_sName, false);
        function->AddDataValue(L"INPUT", true);
        function->AddDataValue(L"ID", i);
    }
    for (unsigned int i = 0; i < m_OutputLogicWrappers.size(); i++)
    {
        CDataGroup* function = descriptor->AddDataGroup(L"FUNCTION");
        CLogicWrapper* wrapper = m_OutputLogicWrappers[i];
        function->AddDataValue(L"NAME", wrapper->m_sName, false);
        function->AddDataValue(L"INPUT", false);
        function->AddDataValue(L"ID", i);
    }

    CDataGroup* parentFilter = descriptor->AddDataGroup(L"PARENT FILTER");
    if (m_ParentFilters.size() == 0)
    {
        parentFilter->AddDataValue(L"FILTER", true);
    }
    else
    {
        for (unsigned int i = 0; i < m_ParentFilters.size(); i++)
            parentFilter->AddDataValue(L"FILTER", m_ParentFilters[i], false);
    }

    for (unsigned int i = 0; i < m_Properties.size(); i++)
        m_Properties[i]->serializeProperty(descriptor, i);
}

void CDescriptor::GetPropertyListOfValues(CEditorBaseObject* object, unsigned int index,
                                          std::vector<std::wstring>& values)
{
    CDescriptorProp* property = GetProperty(index);
    if (property == NULL || !(property->m_iFlags & CDescriptorProp::FLAG_HAS_LIST_OF_VALUES))
        return;

    std::wstring previous = L"supercalaphasticexpelodotues";
    std::wstring value = property->getListValueByIndex(getSceneOwner(), object, 0);
    unsigned int next = 1;
    while (value != previous)
    {
        bool found = false;
        for (unsigned int i = 0; i < values.size(); i++)
        {
            if (values[i] == value)
            {
                found = true;
                break;
            }
        }
        if (!found)
            values.push_back(value);

        previous = value;
        value = property->getListValueByIndex(getSceneOwner(), object, next++);
    }
}

void CDescriptor::BroadcastEventFromObject(CEditorBaseObject* object, unsigned int event)
{
    if (event == 0xFFFFFFFF || object == NULL)
        return;
    if (getSceneOwner() == NULL || getSceneOwner()->getSettings() == NULL ||
        getSceneOwner()->getResourceManager() == NULL)
        return;

    if (getSceneOwner()->getSettings()->GetInt(KSETTINGS_DEBUG_LOGIC) > 0)
    {
        std::wstring message = L"Attempting to fire message" + gOUTPUT_EVENTS_NAMES[event] + L" for object " +
                               object->getName() + L" of type " + m_sName;
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToUTF8(message), Ogre::LML_CRITICAL);
    }

    if (m_OutputLogicObjects.size() != 0 && getSceneOwner()->getResourceManager()->getLogicMessagesEnabled())
    {
        std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>::iterator it = m_OutputLogicObjects.find(object);
        if (it == m_OutputLogicObjects.end())
        {
            getSceneOwner()->eventFiredByDescriptor(event, this, object);
            return;
        }

        if (getSceneOwner()->getSettings()->GetInt(KSETTINGS_DEBUG_LOGIC) > 0 &&
            !getSceneOwner()->getResourceManager()->getLogicMessagesEnabled())
        {
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToUTF8(
                L"******************************************INVOKING EVENT"
                L"****************************************************"), Ogre::LML_CRITICAL);
        }

        TArrayList<CLogicObject*>* logicObjects = it->second;
        if (logicObjects)
        {
            for (unsigned int i = 0; i < logicObjects->size(); i++)
            {
                if ((*logicObjects)[i])
                    (*logicObjects)[i]->Invoke(event);
            }
        }

        if (getSceneOwner())
            getSceneOwner()->eventFiredByDescriptor(event, this, object);

        if (getSceneOwner()->getSettings()->GetInt(KSETTINGS_DEBUG_LOGIC) > 0 &&
            !getSceneOwner()->getResourceManager()->getLogicMessagesEnabled())
        {
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToUTF8(
                L"========================================DONE INVOKING EVENT"
                L"====================================================="), Ogre::LML_CRITICAL);
        }
    }
    else if (getSceneOwner()->getSettings()->GetInt(KSETTINGS_DEBUG_LOGIC) > 0 &&
             !getSceneOwner()->getResourceManager()->getLogicMessagesEnabled())
    {
        std::wstring message = L"Unable to fire message" + gOUTPUT_EVENTS_NAMES[event] + L" for object " +
                               object->getName() + L" of type " + m_sName +
                               L" because resource manager has disabled logic messages";
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToUTF8(message), Ogre::LML_CRITICAL);
    }
}

void CDescriptor::saveObject(CEditorBaseObject* object, CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    if (group == NULL || (m_iFlags & DESCRIPTOR_FLAG_NOT_SAVED) ||
        object->HasBaseObjectFlag(EDITOROBJECT_FLAG_DONT_SAVE))
        return;

    object->AddBaseObjectFlag(EDITOROBJECT_FLAG_SAVED);
    CDataGroup* properties = group->AddDataGroup(L"PROPERTIES");
    properties->AddDataValue(L"DESCRIPTOR", m_sName, false);
    properties->AddDataValue(L"NAME", object->getName(), false);
    properties->AddDataValue(L"ID", object->getOriginalGuid());

    CEditorBaseObject* parent = object->getSceneOwner()->GetObjectInScene(object->getParentGuid());
    if (parent == NULL)
        properties->AddDataValue(L"PARENTID", -1LL);
    else
        properties->AddDataValue(L"PARENTID", parent->getOriginalGuid());

    for (unsigned int i = 0; i < m_Properties.size(); i++)
    {
        if (m_DefaultProperties.size() != 0)
        {
            unsigned int defaultCount = 0;
            unsigned int count = 0;
            UNIONDATA32BIT* defaultData = m_DefaultProperties[i]->getData(defaultCount, NULL);
            UNIONDATA32BIT* data = m_Properties[i]->getData(count, object);
            if (defaultCount == count)
            {
                bool same = true;
                for (unsigned int j = 0; j < count; j++)
                {
                    if (defaultData[j].m_iValue != data[j].m_iValue)
                    {
                        same = false;
                        break;
                    }
                }
                if (same)
                    continue;
            }
        }
        m_Properties[i]->saveProperty(object, properties);
    }
    saveAdditionalInfo(object, NULL, properties, configuration);
}

void CDescriptor::OutputLogicObjectAdd(CEditorBaseObject* object, CLogicObject* logicObject)
{
    if (logicObject == NULL || object == NULL)
        return;

    std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*>::iterator it = m_OutputLogicObjects.find(object);
    if (it == m_OutputLogicObjects.end())
    {
        m_OutputLogicObjects[object] = new TArrayList<CLogicObject*>(1);
        m_OutputLogicObjects[object]->add(logicObject);
    }
    else
    {
        TArrayList<CLogicObject*>* logicObjects = it->second;
        if (logicObjects->find(logicObject) == -1)
            logicObjects->add(logicObject);
    }
}
