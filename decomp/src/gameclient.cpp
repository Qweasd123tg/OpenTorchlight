#include "KeyManager.h"
#include "MouseManager.h"
#include "MasterResourceManager.h"
#include "QuestManager.h"
#include "SoundManager.h"
#include <OgreRoot.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include "GameClient.h"
namespace gameclient_input_detail {
inline __attribute__((always_inline)) CMouseManager& mouse(CGameClient* self) { return *reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(self)+0xfe8); }
inline __attribute__((always_inline)) CKeyManager& keys(CGameClient* self) { return *reinterpret_cast<CKeyManager*>(reinterpret_cast<char*>(self)+0x2d0); }
}
#include "GameClient.h"
#include "GameUI.h"
#include "Item.h"
#include <OgrePass.h>
#include <OgreRenderQueue.h>
#include <OgreSceneManager.h>
#include "Player.h"
#include "StringUtilities.h"


// Imported source candidates; historical status is not fresh acceptance.
void CGameClient::destroyGameUI()
{
    if (m_pGameUI) { delete m_pGameUI; m_pGameUI = NULL; }
    m_pGameUI = NULL;
}

void CGameClient::updateScreenInfo(void* window, int width, int height)
{
    m_window = window; m_width = width; m_height = height;
}

void CGameClient::handleFunctionKeys()
{
}

void CGameClient::toggleLighting(bool enabled)
{
}

void CGameClient::togglePlayerLight()
{
    if (m_playerLightNode && m_playerLight) {
        if (m_playerLight->getParentSceneNode()) m_playerLightNode->detachObject(m_playerLight);
        else m_playerLightNode->attachObject(m_playerLight);
    }
}

bool CGameClient::getPlayerIsCheat()
{
    return m_pPlayer && m_pPlayer->m_cheatMarker == 0xd6;
}

std::wstring CGameClient::getPlayerClassName()
{
    if (m_pPlayer) return m_pPlayer->getPlayerClassName();
    return STRINGS::StringUpper(m_editorCreationClass);
}

void CGameClient::setEditorCreationPet(std::wstring name)
{
    m_editorCreationPet = name;
}

void CGameClient::setEditorCreationClass(std::wstring name)
{
    m_editorCreationClass = name;
}

bool CGameClient::processMenuInput(void* window, float elapsed, bool enabled)
{
    if (m_pGameUI && !m_pGameUI->processInput(this, window, elapsed, enabled)) {
        if (gameclient_input_detail::mouse(this).buttonHeld(static_cast<EMouseButton>(0))) m_leftHeld = true;
        if (gameclient_input_detail::mouse(this).buttonHeld(static_cast<EMouseButton>(1))) m_rightHeld = true;
        m_inputConsumed = true;
    }
    gameclient_input_detail::mouse(this).update(window);
    return true;
}

void CGameClient::notifyOfDeletion(CItem* object)
{
    if (m_targetItem.getObject() == object) m_targetItem.setObject(NULL);
    if (m_selectedItem.getObject() == object) m_selectedItem.setObject(NULL);
    if (m_pGameUI) m_pGameUI->notifyOfDeletion(object);
}

void CGameClient::updateCursor()
{
    if (m_pGameUI) m_pGameUI->updateHardwareCursor();
}

void CGameClient::reloadSoundBankData()
{
    if (m_masterResources) { m_soundManager->stopAllSounds(); m_masterResources->reloadSoundBankData(); }
}

void CGameClient::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (m_questManager) m_questManager->questEventUpdate(event, character, target);
}

void CGameClient::clearSceneManagerPassMaps()
{
    m_pendingPassClear = false;
    if (m_root) {
        Ogre::SceneManagerEnumerator::SceneManagerIterator it = m_root->getSceneManagerIterator();
        while (it.hasMoreElements()) {
            Ogre::SceneManager* scene = it.getNext();
            if (scene) { Ogre::RenderQueue* queue = scene->getRenderQueue(); if (queue) queue->clear(true); }
        }
        Ogre::Pass::processPendingPassUpdates();
    }
}

void CGameClient::mouseEvent(unsigned int event, unsigned int button)
{
    if (m_pGameUI) m_pGameUI->mouseEvent(event, button);
    gameclient_input_detail::mouse(this).mouseEvent(event, button);
}

void CGameClient::keyEvent(unsigned int event, unsigned int key, long character)
{
    if (m_pGameUI) m_pGameUI->keyEvent(event, key, character);
    gameclient_input_detail::keys(this).keyEvent(event, key);
}

void CGameClient::setWindowActive(bool active)
{
    if (!active && m_pPlayer) {
        m_pPlayer->stopPathing();
        m_pPlayer->m_moveInputHeld = false;
        gameclient_input_detail::keys(this).flushAll(); gameclient_input_detail::mouse(this).flushAll();
        m_leftHeld = false; m_rightHeld = false; m_inputConsumed = true;
        if (m_pGameUI) m_pGameUI->setWindowActive(false);
    }
}

void CGameClient::notifyOfDeletion(CCharacter* object)
{
    if (m_targetCharacter.getObject() == object) m_targetCharacter.setObject(NULL);
    if (m_selectedCharacter.getObject() == object) m_selectedCharacter.setObject(NULL);
    if (m_pGameUI) m_pGameUI->notifyOfDeletion(object);
}

#include "SettingsVariables.h"
#include "CameraControl.h"
#include "UtilitiesMath.h"
#include "EmptyStrings.h"
#include "DungeonManager.h"
#include "Dungeon.h"
#include "Level.h"
#include "LevelState.h"
#include "CharacterSaveState.h"

void CGameClient::setSpeedMult(float speed)
{
    if (speed <= 0) m_speedMult = 0;
    else if (speed > 5) m_speedMult = 5;
    else m_speedMult = speed;
}

bool CGameClient::getIsPaused()
{
    if (m_interactionState) return true;
    if (m_pGameUI && m_pGameUI->bothCoveredPartial()) return true;
    if (m_pGameUI && m_pGameUI->getConsoleIsOpen() && !m_settings->GetInt(KSETTINGS_CONSOLE_NOPAUSE)) return true;
    if (m_pGameUI && m_pGameUI->modalDialogOpenPartial()) return true;
    if (m_pGameUI) return m_pGameUI->m_paused;
    return false;
}

void CGameClient::findCameraTargetLocation(Ogre::Vector3& result, float height)
{
    Ogre::Ray ray;
    Ogre::Vector3 normal(0,1,0);
    m_cameraControl->m_cameras[0]->getCameraToViewportRay(0.5f,0.5f,&ray);
    float x=ray.getDirection().x, z=ray.getDirection().z;
    float distance=MATH::distanceToPlane(ray.getOrigin(),ray.getDirection(),normal,height);
    result.z=ray.getOrigin().z+z*distance;
    result.y=0;
    result.x=ray.getOrigin().x+x*distance;
}

void CGameClient::killPets()
{
    for (int i=0;i<static_cast<int>(m_pPlayer->getFollowerCount());++i) {
        CCharacter* follower=m_pPlayer->getFollower(i);
        if (follower->diesOnWarp()) { follower->die(NULL,NULL,0,false); --i; }
    }
}

void CGameClient::setCurrentDungeon(std::wstring name)
{
    name=STRINGS::StringUpper(name);
    CDungeon* dungeon=CDungeonManager::getSingleton()->getDungeonByName(name);
    if(dungeon)m_currentDungeon=dungeon;
}

void CGameClient::warpLevels(std::wstring dungeon,int delta,int depth,bool flag,std::wstring name,bool pending)
{
    m_warpFlag=flag;
    m_warpPending=pending;
    m_warpName=STRINGS::StringUpper(name);
    if(STRINGS::StringUpper(dungeon)==L"LASTDUNGEON" && m_pPlayer->m_returnDungeon!=EMPTY_WSTRING) {
        m_warpDungeon=m_pPlayer->m_returnDungeon;
        m_warpDelta=0;
        m_warpDepth=m_pPlayer->m_returnDepth;
    } else {
        m_warpDungeon=dungeon;
        m_warpDepth=depth;
        m_warpDelta=delta;
    }
    m_warpWaypoint=true;
}

bool CGameClient::storedUnitExists(long long guid)
{
    if(!m_level || !m_pPlayer)return false;
    CLevelState* state=m_pPlayer->getLevelSavedState(m_level->getDungeonName(),m_level->getLevelDepth());
    for(unsigned int i=0;i<static_cast<unsigned int>(state->m_lCharacters.size());++i)
        if(state->m_lCharacters[i]->m_guid10==guid)return true;
    return false;
}
