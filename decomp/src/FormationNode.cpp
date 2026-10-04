#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "FormationNode.h"
#include "FormationNodeSaveAndLoad.h"
#include "RunicCore.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

CFormationNode::~CFormationNode()
{
}

CFormationNodeSaveAndLoad::CFormationNodeSaveAndLoad(CFormationNode* pFormationNode)
    : CRunicCore()
{
    if (pFormationNode != 0)
    {
        m_bSavePosition = !pFormationNode->m_bActivationStarted;

        const std::wstring& fileLoaded =
            *reinterpret_cast<const std::wstring*>(
                reinterpret_cast<const unsigned char*>(pFormationNode->m_pEditorScene) + 0x168);
        m_sFileLoaded = fileLoaded;

        Ogre::Vector3 vPosition = pFormationNode->getPosition(true);
        m_fPositionX = vPosition.x;
        m_fPositionY = vPosition.y;
        m_fPositionZ = vPosition.z;
    }
}

long long CFormationNode::updateLevelObject(float fTime, Ogre::Camera* pCamera, const Ogre::Vector3& vTargetPosition)
{
    return reinterpret_cast<CFormationNode*>(
        reinterpret_cast<char*>(this) - 0x100
    )->CFormationNode::updateLevelObject(fTime, pCamera, vTargetPosition);
}
