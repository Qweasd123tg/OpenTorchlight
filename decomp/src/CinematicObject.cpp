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

long long CCinematicObject::updateLevelObject(float fTime, Ogre::Camera* pCamera,
                                               const Ogre::Vector3& vPosition)
{
}

void CCinematicObject::menuEventOccured(void* pTarget,
                                       EMENU_TYPE eMenuType,
                                       EMENU_EVENT eMenuEvent)
{
    if (m_eMenuEvent == eMenuEvent)
    {
        play();
    }
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
