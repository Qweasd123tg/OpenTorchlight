#include "EmptyStrings.h"
#include "GameEnums.h"
#include "PathNode.h"
#include "GameUI.h"
#include "PathController.h"
#include "SceneNodeObject.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

#include "PathController.h"

void CPathNode::positionUpdated(const Ogre::Vector3& position)
{
    setText(m_sText);

    if (m_pPathController)
        m_pPathController->childNodeMoved();
}

CPathNode::~CPathNode()
{
    sceneNodeDestroyEntity();
    CGameUI::getSingleton()->returnTextEventObject(m_pTextEvent);
    m_pPathController = NULL;
}

void CPathNode::setVisible(bool bVisible)
{
    if (bVisible)
    {
        if (m_sText != EMPTY_WSTRING)
            setText(m_sText);
    }
    else
    {
        std::wstring text = m_sText;
        setText(L"");
        m_sText = text;
    }

    CSceneNodeObject::setVisible(bVisible);
}

#include "TextEvent.h"
#include "StringUtilities.h"

void CPathNode::setText(const std::wstring& text)
{
    m_sText = text;
    if (m_pTextEvent)
        m_pTextEvent->setText(getPosition(false) + Ogre::Vector3(0.0f, 1.7f, 0.0f),
            STRINGS::StringConvertToUTF8(m_sText), 1.0f, 255.0f,
            CEGUI::colour(1.0f,1.0f,1.0f,1.0f), CEGUI::colour(1.0f,1.0f,1.0f,1.0f));
}

