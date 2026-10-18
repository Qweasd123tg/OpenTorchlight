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
#include "Layout.h"
#include "EditorScene.h"
#include "Character.h"
#include "Level.h"
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

        m_sFileLoaded = std::wstring(pFormationNode->m_pEditorScene->getLoadedFilename());

        Ogre::Vector3 vPosition = pFormationNode->getPosition(true);
        m_fPositionX = vPosition.x;
        m_fPositionY = vPosition.y;
        m_fPositionZ = vPosition.z;
    }
}

bool CFormationNode::updateLevelObject(float fTime, Ogre::Camera* pCamera, const Ogre::Vector3& vTargetPosition)
{
    return reinterpret_cast<CFormationNode*>(
        reinterpret_cast<char*>(this) - 0x100
    )->CFormationNode::updateLevelObject(fTime, pCamera, vTargetPosition);
}

void CFormationNode::setLayoutFile(const std::wstring& layoutFile, CResourceManager* resources)
{
    if (m_pEditorScene) {
        delete m_pEditorScene;
        m_pEditorScene = NULL;
    }
    CLayout* layout = new CLayout(resources, static_cast<ELAYOUT_TYPES>(0));
    m_pEditorScene = layout;
    layout->loadLayoutFile(layoutFile, false, NULL, false, false, 0);
    m_pEditorScene->setVisible(false);
    TArrayList<CEditorBaseObject*> monsters(10);
    m_pEditorScene->GetObjectsCreatedByADescriptor(L"Monster", &monsters);
    for (unsigned int i = 0; i < monsters.size(); ++i) {
        CCharacter* character = static_cast<CCharacter*>(monsters[i]);
        if (resources->getLevel())
            resources->getLevel()->removeUnit(character, true);
        character->CCharacter::setVisible(false, true);
    }
}

CFormationNode::CFormationNode(CResourceManager* resources, CFormationNodeSaveAndLoad* saved)
    : CPositionableObject(resources, NULL), iLevelUpdate(), m_bActivationStarted(false), m_pEditorScene(NULL)
{
    if (m_pResourceManager->getLevel()) {
        m_pResourceManager->getLevel()->addUpdateObject(this);
        if (saved) {
            setLayoutFile(saved->m_sFileLoaded, resources);
            setPosition(Ogre::Vector3(saved->m_fPositionX, saved->m_fPositionY, saved->m_fPositionZ));
        }
    }
}
