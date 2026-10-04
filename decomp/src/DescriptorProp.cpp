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
