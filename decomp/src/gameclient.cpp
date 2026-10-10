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
