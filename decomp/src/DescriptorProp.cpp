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
