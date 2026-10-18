#include "EmptyStrings.h"
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"
#include "RunicCore.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "EditorScene.h"
#include "StringUtilities.h"

EVARIABLE_TYPES CDescriptorProp::getVariableType()
{
    if (m_pInterpreter != NULL)
        return VARIABLE_TYPE_STRING;
    return m_eType;
}

CDescriptorProp::CDescriptorProp(std::wstring category, std::wstring name,
                                 std::wstring description, void* setFunction,
                                 void* getFunction, EVARIABLE_TYPES type,
                                 int flags)
    : CRunicCore(),
      m_sName(name),
      m_sDescription(description),
      m_pInterpreter(NULL),
      m_pSetFunction(setFunction),
      m_pGetFunction(getFunction),
      m_eType(type),
      m_iFlags(flags),
      m_sCategory(category),
      m_DefaultValue(10),
      m_LinkedProperties(10),
      m_pValueBuffer(NULL)
{
}

CDescriptorProp::~CDescriptorProp()
{
    delete m_pInterpreter;
    if (m_pValueBuffer != NULL)
    {
        Ogre::NedAllocImpl::deallocBytes(m_pValueBuffer);
        m_pValueBuffer = NULL;
    }
}


std::wstring CDescriptorProp::getListValueByIndex(CEditorScene* scene,
                                                CEditorBaseObject* object,
                                                unsigned int index)
{
    if (!(m_iFlags & FLAG_HAS_LIST_OF_VALUES))
        return EMPTY_WSTRING;
    return m_pInterpreter->GetValue(scene, object, index);
}

unsigned int CDescriptorProp::getElementSize()
{
    unsigned int count = m_DefaultValue.size();
    if (m_pInterpreter)
        count = 1;
    else {
        switch (m_eType) {
        case VARIABLE_TYPE_STRING: count = 1; break;
        case VARIABLE_TYPE_VECTOR2: count /= 2; break;
        case VARIABLE_TYPE_VECTOR3: count /= 3; break;
        case VARIABLE_TYPE_VECTOR4: count /= 4; break;
        default: break;
        }
    }
    return count;
}

UNIONDATA32BIT* CDescriptorProp::getData(unsigned int& count, CEditorBaseObject* object)
{
    count = 0;
    if (object != NULL && m_pGetFunction != NULL)
        return getDataFromObject(object, count);
    if (m_DefaultValue.size() != 0) {
        count = m_DefaultValue.size();
        return &m_DefaultValue[0];
    }
    return NULL;
}

UNIONDATA32BIT* CDescriptorProp::convertDataTo32bit(const UNIONDATA8BIT* data, unsigned int size, unsigned int& count)
{
    if (m_pInterpreter || m_eType == VARIABLE_TYPE_STRING || size % 4) {
        if (m_pValueBuffer) {
            Ogre::NedAllocImpl::deallocBytes(m_pValueBuffer);
            m_pValueBuffer = NULL;
        }
        count = ((size & ~3u) + 4) / 4;
        m_pValueBuffer = Ogre::NedAllocImpl::allocBytes(static_cast<size_t>(count) * 4, NULL, 0, NULL);
        std::memset(m_pValueBuffer, 0, static_cast<size_t>(count) * 4);
        std::memcpy(m_pValueBuffer, data, size);
        return static_cast<UNIONDATA32BIT*>(m_pValueBuffer);
    }
    count = size / 4;
    return reinterpret_cast<UNIONDATA32BIT*>(const_cast<UNIONDATA8BIT*>(data));
}
void CDescriptorProp::setPropertyInterpreter(CDescriptorPropertyInterpreter* interpreter)
{
    if (interpreter)
        setPropertyInterpreterFunctions(interpreter->m_pValueFunction, interpreter->m_pNameFunction, interpreter->m_pContext);
    else setPropertyInterpreterFunctions(NULL, NULL, NULL);
}
void CDescriptorProp::setDataOnObject(CEditorBaseObject* object, const UNIONDATA32BIT* data, unsigned int count)
{
    if (!object || !m_pGetFunction) return;
    typedef void (*SetFunction)(CEditorBaseObject*, const void*, unsigned int);
    if (m_pInterpreter && m_eType != VARIABLE_TYPE_STRING) {
        unsigned int value = m_pInterpreter->GetValue(object->getSceneOwner(), object,
                           std::wstring(reinterpret_cast<const wchar_t*>(data)));
        reinterpret_cast<SetFunction>(m_pSetFunction)(object, &value, 4);
    } else reinterpret_cast<SetFunction>(m_pSetFunction)(object, data, count);
}
UNIONDATA32BIT* CDescriptorProp::getDataFromObject(CEditorBaseObject* object, unsigned int& count)
{
    if (!object) return NULL;
    typedef UNIONDATA8BIT* (*GetFunction)(CEditorBaseObject*, unsigned int&);
    UNIONDATA8BIT* data = reinterpret_cast<GetFunction>(m_pGetFunction)(object, count);
    if (m_pInterpreter && m_eType != VARIABLE_TYPE_STRING) {
        std::wstring value = m_pInterpreter->GetValue(object->getSceneOwner(), object, data[0].m_ucValue);
        return convertDataTo32bit(reinterpret_cast<const UNIONDATA8BIT*>(value.c_str()), value.length() * 4, count);
    }
    if (count) return convertDataTo32bit(data, count, count);
    unsigned int zero = 0;
    return convertDataTo32bit(reinterpret_cast<const UNIONDATA8BIT*>(&zero), 4, count);
}
void CDescriptorProp::setData(const UNIONDATA32BIT* data, unsigned int count, CEditorBaseObject* object)
{
    if (!data) return;
    if (object && m_pSetFunction) {
        setDataOnObject(object, data, count);
        for (unsigned int i = 0; i < m_LinkedProperties.size(); ++i) {
            UNIONDATA32BIT* value = m_LinkedProperties[i]->getData(count, object);
            m_LinkedProperties[i]->setData(value, count, object);
        }
    } else {
        m_DefaultValue.clear();
        for (unsigned int i = 0; i < count; ++i) m_DefaultValue.add(data[i]);
    }
}
void CDescriptorProp::setData(const UNIONDATA8BIT* data, unsigned int size, CEditorBaseObject* object)
{
    unsigned int count = 0;
    UNIONDATA32BIT* value = convertDataTo32bit(data, size, count);
    setData(value, 0, object);
}
void CDescriptorProp::setData(const UNIONDATA16BIT* data, unsigned int size, CEditorBaseObject* object)
{
    unsigned int count = 0;
    UNIONDATA32BIT* value = convertDataTo32bit(reinterpret_cast<const UNIONDATA8BIT*>(data), size * 2, count);
    setData(value, count, object);
}
void CDescriptorProp::setData(const std::wstring& value, CEditorBaseObject* object)
{
    setData(reinterpret_cast<const UNIONDATA8BIT*>(value.c_str()), value.length() * 4, object);
}
void CDescriptorProp::copy(CDescriptorProp& source, CEditorBaseObject* object)
{
    m_iFlags = source.m_iFlags;
    m_eType = source.m_eType;
    m_sCategory = source.m_sCategory;
    m_sName = source.m_sName;
    m_sDescription = source.m_sName;
    if (object) {
        unsigned int count = 0;
        UNIONDATA32BIT* data = source.getData(count, object);
        setData(data, count, NULL);
    } else {
        m_pSetFunction = source.m_pSetFunction;
        m_pGetFunction = source.m_pGetFunction;
        m_pInterpreter = source.m_pInterpreter;
    }
}
std::wstring CDescriptorProp::getPropertyValueAsString(CEditorBaseObject* object)
{
    unsigned int count = 0;
    if (m_pInterpreter || m_eType == VARIABLE_TYPE_STRING)
        return std::wstring(reinterpret_cast<const wchar_t*>(getData(count, object)));
    UNIONDATA32BIT* data = getData(count, object);
    std::wstring result = EMPTY_WSTRING;
    for (unsigned int i = 0; i < count; ++i) {
        if (m_pInterpreter) return EMPTY_WSTRING;
        switch (m_eType) {
        case VARIABLE_TYPE_BOOL: result += STRINGS::GetValueAsWString(data[i].m_bValue); break;
        case VARIABLE_TYPE_UNSIGNED_INTEGER: result += STRINGS::GetValueAsWString(data[i].m_uValue); break;
        case VARIABLE_TYPE_FLOAT: case VARIABLE_TYPE_VECTOR2: case VARIABLE_TYPE_VECTOR3: case VARIABLE_TYPE_VECTOR4:
            result += STRINGS::GetValueAsWString(data[i].m_fValue); break;
        case VARIABLE_TYPE_INTEGER: result += STRINGS::GetValueAsWString(data[i].m_iValue); break;
        default: return EMPTY_WSTRING;
        }
        if (i != count - 1) result += L",";
    }
    return result;
}

void CDescriptorProp::setPropertyInterpreterFunctions(
    PropertyStringToIndexFunction stringToIndex,
    PropertyIndexToStringFunction indexToString, void* userData)
{
    if (stringToIndex && indexToString) {
        if (m_pInterpreter)
            m_pInterpreter->SetInterpreterFunctions(stringToIndex, indexToString, userData);
        else
            m_pInterpreter = new CDescriptorPropertyInterpreter(stringToIndex, indexToString, userData);
    } else {
        delete m_pInterpreter;
    }
}

CDescriptorProp::CDescriptorProp(CDescriptorProp* source, CEditorBaseObject* object)
    : CRunicCore(), m_sName(EMPTY_WSTRING), m_sDescription(EMPTY_WSTRING),
      m_pInterpreter(NULL), m_pSetFunction(NULL), m_pGetFunction(NULL),
      m_eType(VARIABLE_TYPE_NOT_SET), m_iFlags(0), m_sCategory(EMPTY_WSTRING),
      m_DefaultValue(10), m_LinkedProperties(10), m_pValueBuffer(NULL)
{
    if (source) copy(*source, object);
}

#include "DataGroup.h"
#include "Descriptor.h"

bool CDescriptorProp::cloneValue(CEditorBaseObject* object, CEditorBaseObject* source)
{
    if (m_iFlags & 0x4000) return true;
    if (!object || !source || !object->getDescriptor() || !source->getDescriptor() ||
        object->getDescriptor()->m_sName != source->getDescriptor()->m_sName)
        return false;
    unsigned int count = 1;
    UNIONDATA32BIT* data = getData(count, source);
    setData(data, count, object);
    return true;
}

bool CDescriptorProp::saveProperty(CEditorBaseObject* object, CDataGroup* group)
{
    if (m_iFlags & 0x100) return true;
    if (!group) return false;
    if (m_pInterpreter || m_eType == VARIABLE_TYPE_STRING) {
        group->AddDataValue(m_sName, getPropertyValueAsString(object), false);
        return true;
    }
    unsigned int count = 0;
    UNIONDATA32BIT* value = getData(count, object);
    if (m_pInterpreter) {
        group->AddDataValue(m_sName, EMPTY_WSTRING, false);
        return true;
    }
    switch (m_eType) {
    case VARIABLE_TYPE_INTEGER:
        if (count > 1) group->AddDataValue(m_sName, getPropertyValueAsString(object), false);
        else group->AddDataValue(m_sName, value[0].m_iValue);
        break;
    case VARIABLE_TYPE_UNSIGNED_INTEGER:
        if (count > 1) group->AddDataValue(m_sName, getPropertyValueAsString(object), false);
        else group->AddDataValue(m_sName, value[0].m_uValue);
        break;
    case VARIABLE_TYPE_FLOAT:
        if (count > 1) group->AddDataValue(m_sName, getPropertyValueAsString(object), false);
        else group->AddDataValue(m_sName, value[0].m_fValue);
        break;
    case VARIABLE_TYPE_BOOL:
        if (count > 1) group->AddDataValue(m_sName, getPropertyValueAsString(object), false);
        else group->AddDataValue(m_sName, value[0].m_bValue);
        break;
    case VARIABLE_TYPE_VECTOR2:
        group->AddDataValue(m_sName + L"X", value[0].m_fValue);
        group->AddDataValue(m_sName + L"Y", value[1].m_fValue);
        break;
    case VARIABLE_TYPE_VECTOR3:
        group->AddDataValue(m_sName + L"X", value[0].m_fValue);
        group->AddDataValue(m_sName + L"Y", value[1].m_fValue);
        group->AddDataValue(m_sName + L"Z", value[2].m_fValue);
        break;
    case VARIABLE_TYPE_VECTOR4:
        group->AddDataValue(m_sName + L"X", value[0].m_fValue);
        group->AddDataValue(m_sName + L"Y", value[1].m_fValue);
        group->AddDataValue(m_sName + L"Z", value[2].m_fValue);
        group->AddDataValue(m_sName + L"I", value[3].m_fValue);
        break;
    default: group->AddDataValue(m_sName, EMPTY_WSTRING, false); break;
    }
    return true;
}

bool CDescriptorProp::loadProperty(CEditorBaseObject* object, CDataGroup* group, unsigned int version)
{
    if (m_iFlags & 0x100) return true;
    if (version <= 2) {
        if (!group) return false;
        CDataGroup* property = group->GetDataGroupByName(m_sName, false);
        if (property)
            setPropertyValueByString(property->GetDataValue(L"VALUE", EMPTY_WSTRING), object);
        else {
            unsigned int count = 0;
            UNIONDATA32BIT* data = getData(count, object);
            setData(data, count, object);
        }
        return true;
    }
    CDataValue* stored = group->GetDataValueByName(m_sName);
    if (stored && stored->GetValueType() == CDataValue::DATAVALUE_STRING) {
        setPropertyValueByString(group->GetDataValue(m_sName, EMPTY_WSTRING), object);
        return true;
    }
    unsigned int count = 0;
    UNIONDATA32BIT* initial = getData(count, object);
    UNIONDATA32BIT data[4] = {};
    if (!initial) return false;
    if (m_pInterpreter) {
        if (stored) setData(group->GetDataValue(m_sName, reinterpret_cast<const wchar_t*>(initial)), object);
        return true;
    }
    switch (m_eType) {
    case VARIABLE_TYPE_INTEGER:
        if (stored) { data[0].m_iValue = group->GetDataValue(m_sName, initial[0].m_iValue); setData(data, 1, object); }
        break;
    case VARIABLE_TYPE_UNSIGNED_INTEGER:
        if (stored) { data[0].m_uValue = group->GetDataValue(m_sName, initial[0].m_uValue); setData(data, 1, object); }
        break;
    case VARIABLE_TYPE_FLOAT:
        if (stored) { data[0].m_fValue = group->GetDataValue(m_sName, initial[0].m_fValue); setData(data, 1, object); }
        break;
    case VARIABLE_TYPE_BOOL:
        if (stored) { data[0].m_bValue = group->GetDataValue(m_sName, initial[0].m_bValue); setData(data, 1, object); }
        break;
    case VARIABLE_TYPE_VECTOR2:
        data[0].m_fValue = group->GetDataValue(m_sName + L"X", initial[0].m_fValue);
        data[1].m_fValue = group->GetDataValue(m_sName + L"Y", initial[1].m_fValue);
        setData(data, 2, object); break;
    case VARIABLE_TYPE_VECTOR3:
        data[0].m_fValue = group->GetDataValue(m_sName + L"X", initial[0].m_fValue);
        data[1].m_fValue = group->GetDataValue(m_sName + L"Y", initial[1].m_fValue);
        data[2].m_fValue = group->GetDataValue(m_sName + L"Z", initial[2].m_fValue);
        setData(data, 3, object); break;
    case VARIABLE_TYPE_VECTOR4:
        data[0].m_fValue = group->GetDataValue(m_sName + L"X", initial[0].m_fValue);
        data[1].m_fValue = group->GetDataValue(m_sName + L"Y", initial[1].m_fValue);
        data[2].m_fValue = group->GetDataValue(m_sName + L"Z", initial[2].m_fValue);
        data[3].m_fValue = group->GetDataValue(m_sName + L"I", initial[3].m_fValue);
        setData(data, 4, object); break;
    default:
        if (stored) setData(group->GetDataValue(m_sName, reinterpret_cast<const wchar_t*>(initial)), object);
        break;
    }
    return true;
}

#include "GameNamespaces.h"

void CDescriptorProp::serializeProperty(CDataGroup* group, unsigned int index)
{
    if (m_iFlags & 0x80) return;
    CDataGroup* property = group->AddDataGroup(L"PROPERTY");
    property->AddDataValue(L"NAME", m_sName, false);
    property->AddDataValue(L"DESCRIPTION", m_sDescription, false);
    property->AddDataValue(L"TYPEOFDATA", KEditorObjectPropertyTypeNames[m_pInterpreter ? VARIABLE_TYPE_STRING : m_eType], false);
    property->AddDataValue(L"ID", index);
    property->AddDataValue(L"CATEGORY", m_sCategory, false);
    if (m_iFlags & 2) property->AddDataValue(L"EDITORTYPE", L"file", false);
    if (m_iFlags & 0x200) property->AddDataValue(L"EDITORTYPE", L"file_particlesystem", false);
    if (m_iFlags & 0x400) property->AddDataValue(L"EDITORTYPE", L"file_particlesystemimages", false);
    if (m_iFlags & 0x800) property->AddDataValue(L"EDITORTYPE", L"file_layout", false);
    if (m_iFlags & 0x1000) property->AddDataValue(L"EDITORTYPE", L"file_mesh", false);
    if (m_iFlags & 0x2000) property->AddDataValue(L"EDITORTYPE", L"file_images", false);
    else if (m_iFlags & 4) property->AddDataValue(L"EDITORTYPE", L"list", false);
    else if (m_iFlags & 8) property->AddDataValue(L"EDITORTYPE", L"color", false);
    else if (m_iFlags & 0x8000) property->AddDataValue(L"EDITORTYPE", L"line", false);
    else if (m_iFlags & 0x10) property->AddDataValue(L"EDITORTYPE", L"dynamicproperty", false);
    else if (m_iFlags & 0x20) property->AddDataValue(L"EDITORTYPE", L"dynamiccolor", false);
    if (m_iFlags & 0x40) property->AddDataValue(L"REFRESHAFTERCHANGE", true);
    if (m_iFlags & 1) property->AddDataValue(L"READONLY", true);
}

void CDescriptorProp::setPropertyValueByString(std::wstring value, CEditorBaseObject* object)
{
    if (m_eType == VARIABLE_TYPE_NOT_SET) return;
    if (m_pInterpreter || m_eType == VARIABLE_TYPE_STRING) { setData(value, object); return; }
    TArrayList<UNIONDATA32BIT> data(4);
    std::queue<std::wstring> tokens;
    STRINGS::TokenizeString(&tokens, value, L",");
    if (tokens.empty()) tokens.push(value);
    while (!tokens.empty()) {
        if (!m_pInterpreter) {
            UNIONDATA32BIT item;
            switch (m_eType) {
            case VARIABLE_TYPE_INTEGER: case VARIABLE_TYPE_UNSIGNED_INTEGER:
                item.m_iValue = STRINGS::GetInt(tokens.front()); break;
            case VARIABLE_TYPE_FLOAT: case VARIABLE_TYPE_VECTOR2: case VARIABLE_TYPE_VECTOR3: case VARIABLE_TYPE_VECTOR4:
                item.m_fValue = STRINGS::GetFloat(tokens.front()); break;
            case VARIABLE_TYPE_BOOL: item.m_uValue = static_cast<unsigned char>(STRINGS::GetBool(tokens.front())); break;
            default: tokens.pop(); continue;
            }
            data.add(item);
        }
        tokens.pop();
    }
    setData(data.size() ? &data[0] : NULL, data.size(), object);
}
