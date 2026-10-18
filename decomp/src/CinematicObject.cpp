#include "Level.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "CinematicObject.h"
#include "EditorBaseObject.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "iLevelUpdate.h"
#include "iMenuListener.h"

bool CCinematicObject::updateLevelObject(float fTime, Ogre::Camera* pCamera,
                                               const Ogre::Vector3& vPosition)
{
    if (m_eMenuEvent == static_cast<EMENU_EVENT>(3) ||
        m_eMenuEvent == static_cast<EMENU_EVENT>(4) ||
        m_eMenuEvent == static_cast<EMENU_EVENT>(2))
        BroadcastEvent(92);
    CGameUI::getSingleton()->removeMenuListener(static_cast<EMENU_TYPE>(1), this);
    return false;
}

void CCinematicObject::menuEventOccured(void* pTarget,
                                       EMENU_TYPE eMenuType,
                                       EMENU_EVENT eMenuEvent)
{
    m_eMenuEvent = eMenuEvent;
    m_pResourceManager->getLevel()->addUpdateObject(this);
}

CCinematicObject::CCinematicObject(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      iMenuListener(),
      iLevelUpdate(),
      m_sCinematicName(),
      m_pResourceManager(resourceManager)
{
}

CCinematicObject::~CCinematicObject()
{
    CCinematicObject* adjustedThis =
        reinterpret_cast<CCinematicObject*>(reinterpret_cast<char*>(this) - 0xa0);
    adjustedThis->~CCinematicObject();
}

void CCinematicObject::play()
{
    if (m_sCinematicName == EMPTY_WSTRING)
        return;

    CGameUI::getSingleton()->setCinematicOpen(m_sCinematicName);
    CGameUI::getSingleton()->addMenuListener(static_cast<EMENU_TYPE>(1), this);
}
