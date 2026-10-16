#include "EmptyStrings.h"
#include "DescriptorProp.h"
#include "RunicCore.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

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

#include "DescriptorPropertyInterpreter.h"

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
