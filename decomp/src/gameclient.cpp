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

#include "Utilities.h"
#include "SharedStash.h"
#include "Inventory.h"
#include "Monster.h"
#include "ResourceManager.h"
#include "RenderableStates.h"
#include <OgreSubEntity.h>
#include <OgreTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTexture.h>
#include <cmath>

void CGameClient::autoPickupGold()
{
    if (!m_pPlayer || !m_pPlayer->alive() || !m_pPlayer->m_isPathing) return;
    TLinkedListNode<CItem*>* item = m_level->m_pendingItems->getHead();
    while (item) {
        TLinkedListNode<CItem*>* next = item->m_pNext;
        if (item->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x22))) {
            Ogre::Vector3 playerPosition = m_pPlayer->getPosition(true);
            Ogre::Vector3 itemPosition = item->m_Data->getPosition(true);
            float x = itemPosition.x-playerPosition.x;
            float z = itemPosition.z-playerPosition.z;
            if (std::sqrt(x*x+0.0f+z*z) < 3.0f)
                m_pPlayer->getItem(item->m_Data,*m_level);
        }
        item = next;
    }
}

void CGameClient::resetGameSeed(int seed)
{
    int dungeonIndex = m_currentDungeon ? m_currentDungeon->m_iDungeonIndex : 0;
    if (seed == -1) seed = m_levelDepth;
    UTILITIES::setSeed(dungeonIndex+m_gameSeed+seed);
}

void CGameClient::createGameUI(Ogre::RenderWindow* renderWindow, void* window)
{
    if (!m_pGameUI) {
        m_resources = CMasterResourceManager::getSingleton()->m_renderBehindParticleScene;
        Ogre::Camera* camera = m_cameraControl->m_pUnknown10;
        m_pGameUI = new CGameUI(*m_settings,*this,window,renderWindow,camera,
            m_sceneManager30,m_sceneManager38,m_resources,m_gameResources);
        m_pGameUI->setCursorState(static_cast<ECursorState>(1));
        m_pGameUI->updateHardwareCursor();
        m_pGameUI->setLoadingVisible(false);
        if (m_pPlayer) m_pGameUI->setPlayer(m_pPlayer);
        if (m_level) m_pGameUI->setLevel(m_level);
    }
}

void CGameClient::rescaleUI()
{
    if (m_pGameUI) {
        if (m_pPlayer) m_pPlayer->destroyIcons();
        if (m_creationPet) m_creationPet->destroyIcons();
        if (m_level) m_level->destroyIcons();
        if (m_questManager) m_questManager->destroyIcons();
        if (CSharedStash::getSingleton() && CSharedStash::getSingleton()->m_pInventory)
            CSharedStash::getSingleton()->m_pInventory->destroyIcons();
        destroyGameUI();
        createGameUI(m_renderWindow,NULL);
        if (m_gameState == static_cast<EGameState>(0)) {
            m_pGameUI->setIngameUIVisible(false);
            m_pGameUI->setActiveMenu(static_cast<EMenu>(0));
        } else m_pGameUI->setIngameUIVisible(true);
    }
    if (m_level) {
        m_level->toggleAutomap();
        m_level->toggleAutomap();
    }
}

void CGameClient::preRenderTargetUpdate(const Ogre::RenderTargetEvent& event)
{
    m_sceneManager28->getRenderQueue()->setRenderableListener(this);
    if (m_level) m_level->setNonLightStaticGeometryVisible(false);
    bool shadow = m_shadowTexture && m_shadowTexture->getBuffer(0,0)->getRenderTarget(0) == event.source;
    if (shadow) {
        m_shadowPass = true;
        m_sceneManager28->setVisibilityMask(4);
        if (!m_shadowNode->getParentSceneNode()) m_sceneManager28->getRootSceneNode()->addChild(m_shadowNode);
    } else {
        m_sceneManager28->setVisibilityMask(2);
        m_shadowPass = false;
        if (!m_playerLightNode->getParentSceneNode()) m_sceneManager28->getRootSceneNode()->addChild(m_playerLightNode);
        if (!m_lightMultiplyNode->getParentSceneNode()) m_sceneManager28->getRootSceneNode()->addChild(m_lightMultiplyNode);
    }
}

void CGameClient::postRenderTargetUpdate(const Ogre::RenderTargetEvent& event)
{
    m_sceneManager28->getRenderQueue()->setRenderableListener(NULL);
    if (m_level) m_level->setNonLightStaticGeometryVisible(true);
    m_sceneManager28->setVisibilityMask(7);
    bool shadow = m_shadowTexture && m_shadowTexture->getBuffer(0,0)->getRenderTarget(0) == event.source;
    if (shadow) {
        if (m_shadowNode->getParentSceneNode()) m_shadowNode->getParentSceneNode()->removeChild(m_shadowNode);
    } else {
        if (m_playerLightNode->getParentSceneNode()) m_playerLightNode->getParentSceneNode()->removeChild(m_playerLightNode);
        if (m_lightMultiplyNode->getParentSceneNode()) m_lightMultiplyNode->getParentSceneNode()->removeChild(m_lightMultiplyNode);
    }
}

void CGameClient::moveToMouse(bool)
{
    Ogre::Vector3 point;
    if (findWorldLocation(point,m_pPlayer->m_moveInputHeld)) {
        Ogre::Vector3 position = m_pPlayer->getPosition(true);
        if (point == position || m_moveTimer <= 0.0f) {
            m_pPlayer->setDestination(*m_level,point.x,point.z);
            m_moveTimer = 0.1f;
        }
    }
}

bool CGameClient::processInput(void* window,float elapsed,bool enabled)
{
    if (enabled) {
        if (m_gameState == static_cast<EGameState>(0)) return processMenuInput(window,elapsed,true);
        if (m_gameState == static_cast<EGameState>(1)) return processIngameInput(window,elapsed,true);
    }
    return true;
}

void CGameClient::setCreationClass(std::wstring name)
{
    if (m_editorCreationClass != name) {
        m_editorCreationClass = name;
        m_pGameUI->setPlayer(NULL);
        m_level->removeCharacter(m_pPlayer,true);
        if (m_pPlayer) { delete m_pPlayer; m_pPlayer = NULL; }
        m_pPlayer = m_level->m_resourceManager->createPlayer(m_editorCreationClass.c_str(),false);
        m_pPlayer->setAlignment(static_cast<EAlignment>(1));
        m_pPlayer->firstTimeSetup();
        m_pPlayer->m_characterDisplayName = std::wstring(m_pGameUI->m_name16B0);
        if (m_pPlayer) {
            m_level->addCharacter(m_pPlayer,m_level->m_playerStart,false);
            m_pPlayer->setToward(m_level->m_startDirection);
        }
        m_pGameUI->setPlayer(m_pPlayer);
    }
    m_deferredFrames = 3;
}

void CGameClient::setCreationPet(std::wstring name)
{
    if (m_editorCreationPet != name) {
        m_editorCreationPet = name;
        m_level->removeCharacter(m_creationPet,true);
        if (m_creationPet) { delete m_creationPet; m_creationPet = NULL; }
        m_creationPet = m_level->m_resourceManager->createMonster(m_editorCreationPet.c_str(),0,false);
        if (m_creationPet) {
            m_creationPet->m_characterDisplayName = std::wstring(m_pGameUI->m_name16B8);
            m_creationPet->setAlignment(static_cast<EAlignment>(1));
            m_creationPet->m_petMode = 2;
            m_level->addCharacter(m_creationPet,m_level->m_secondaryStart,false);
            m_creationPet->setToward(m_level->m_secondaryStartDirection);
        }
    }
    m_deferredFrames = 3;
}

void CGameClient::applyCharacterState(CCharacterSaveState* state,std::wstring& className,CCharacterSaveState* petState)
{
    if (state && m_pPlayer) {
        m_editorCreationClass = className;
        m_pGameUI->setPlayer(NULL);
        m_level->removeCharacter(m_pPlayer,true);
        if (m_pPlayer) { delete m_pPlayer; m_pPlayer = NULL; }
        m_pPlayer = m_level->m_resourceManager->createPlayer(className.c_str(),true);
        m_pPlayer->applySaveState(*state);
        m_pPlayer->m_characterDisplayName = std::wstring(state->m_name);
        m_level->addCharacter(m_pPlayer,m_level->m_playerStart,false);
        m_pPlayer->setToward(m_level->m_startDirection);
        m_pGameUI->setPlayer(m_pPlayer);
        m_level->removeCharacter(m_creationPet,true);
        if (m_creationPet) { delete m_creationPet; m_creationPet = NULL; }
        if (petState) {
            m_creationPet = dynamic_cast<CCharacter*>(m_gameResources->createUnit(petState->m_guid20,petState->m_valueD0,true,false));
            m_creationPet->applySaveState(*petState);
            m_editorCreationPet = m_creationPet->getName();
            m_creationPet->setAlignment(static_cast<EAlignment>(1));
            m_creationPet->m_petMode = 2;
            m_level->addCharacter(m_creationPet,m_level->m_secondaryStart,false);
            m_creationPet->setToward(m_level->m_secondaryStartDirection);
            m_creationPet->m_characterDisplayName = std::wstring(m_pGameUI->m_name16B8);
        }
    }
    m_deferredFrames = 3;
}

int CGameClient::getRankOfMonstersOnFloor(int floor,CDungeon* dungeon,bool matchPlayer)
{
    if (!dungeon) return floor > 0 ? floor : 1;
    int depth = floor+1;
    if (depth <= 0) depth = 1;
    int result = static_cast<int>(static_cast<float>(depth)*dungeon->m_fMonsterLevelMultiplier+0.5f);
    if (result <= 0) result = 1;
    if (m_pPlayer || !matchPlayer) {
        bool history = m_pPlayer->hasDungeonHistory(dungeon->m_sName);
        if (matchPlayer) {
            int rank = history ? m_pPlayer->getDungeonRank(dungeon->m_sName) : 0;
            if (rank == 0) rank = m_pPlayer->m_iUnitLevel;
            if (rank && (dungeon->m_iPlayerLevelMatchMin || dungeon->m_iPlayerLevelMatchMax > 0)) {
                result += dungeon->m_iPlayerLevelMatchOffset;
                if (rank < dungeon->m_iPlayerLevelMatchMin) rank = dungeon->m_iPlayerLevelMatchMin;
                if (rank > dungeon->m_iPlayerLevelMatchMax) rank = dungeon->m_iPlayerLevelMatchMax;
                result += rank-1;
            }
        }
    }
    return result > 0 ? result : 1;
}

int CGameClient::getRankOfMonstersOnFloor(int floor,const std::wstring& name,bool matchPlayer)
{
    if (!name.empty()) {
        CDungeon* dungeon = m_gameResources->getDungeonByName(name);
        if (dungeon) return getRankOfMonstersOnFloor(floor,dungeon,matchPlayer);
    }
    if (m_level) return getRankOfMonstersOnFloor(floor,m_level->getDungeonName(),matchPlayer);
    return floor > 0 ? floor : 1;
}

bool CGameClient::renderableQueued(Ogre::Renderable* renderable,unsigned char group,unsigned short,Ogre::Technique** technique,Ogre::RenderQueue*)
{
    if (m_shadowPass) {
        if (group == 94) return true;
    } else if (group == 0 || group == 101 || (group >= 95 && group <= 99)) return true;
    Ogre::SubEntity* sub = dynamic_cast<Ogre::SubEntity*>(renderable);
    if (!sub || sub->getUserAny().isEmpty()) return false;
    CRenderableStates* state = Ogre::any_cast<CRenderableStates*>(sub->getUserAny());
    if (!state || !m_shadowPass || !state->castsShadows || !(state->m_opacity > 0.0f)) return false;
    int index = static_cast<int>(floorf(state->m_opacity*64.0f))-1;
    if (index < 0) index = 0;
    if (!state->m_state2) *technique = m_shadowOpaque[index]->getTechnique(0);
    else if (state->m_value2c == 1) *technique = m_shadowBlend1[index]->getTechnique(0);
    else if (state->m_value2c == 2) *technique = m_shadowBlend2[index]->getTechnique(0);
    else if (state->m_value2c == 3) *technique = m_shadowBlend3[index]->getTechnique(0);
    else *technique = m_shadowAlpha[index]->getTechnique(0);
    return true;
}

#include "LinuxUtils.h"
#include "Layout.h"
#include "GenericModel.h"
#include "SoundBank.h"

CGameClient::~CGameClient()
{
    if (m_pPlayer && m_pGameUI) m_pGameUI->notifyOfDeletion(m_pPlayer);
    if (m_creationPet && m_pGameUI) m_pGameUI->notifyOfDeletion(m_creationPet);
    if (m_ambientLight) m_sceneManager28->destroyLight(m_ambientLight);
    if (m_gameResources) m_gameResources->getGameClients()->remove(this);
    if (m_menuLayout) { delete m_menuLayout; m_menuLayout = NULL; }
    if (m_menuModel0) { delete m_menuModel0; m_menuModel0 = NULL; }
    if (m_menuModel1) { delete m_menuModel1; m_menuModel1 = NULL; }
    if (m_menuModel2) { delete m_menuModel2; m_menuModel2 = NULL; }
    if (m_menuModel3) { delete m_menuModel3; m_menuModel3 = NULL; }
    m_currentDungeon = NULL;
    m_soundManager->stopMusic();
    if (m_shadowTexture) {
        Ogre::RenderTarget* target = m_shadowTexture->getBuffer(0,0)->getRenderTarget(0);
        target->removeListener(this);
    }
    if (m_lightTexture) {
        Ogre::RenderTarget* target = m_lightTexture->getBuffer(0,0)->getRenderTarget(0);
        target->removeListener(this);
    }
    unloadCurrentLevel(true);
    if (m_menuSound) { delete m_menuSound; m_menuSound = NULL; }
    if (m_questManager) { delete m_questManager; m_questManager = NULL; }
    if (m_pGameUI) { delete m_pGameUI; m_pGameUI = NULL; }
    if (m_masterResources) m_masterResources->removeUnused();
    if (m_gameResources) { delete m_gameResources; m_gameResources = NULL; }
    if (m_playerLight) { delete m_playerLight; m_playerLight = NULL; }
    if (m_lightMultiplyQuad) { delete m_lightMultiplyQuad; m_lightMultiplyQuad = NULL; }
    if (m_shadowQuad) { delete m_shadowQuad; m_shadowQuad = NULL; }
}
bool CGameClient::findWorldLocation(Ogre::Vector3& result,bool offset)
{
    POINT cursor;
    GetCursorPos(&cursor);
    long x = static_cast<int>(static_cast<float>(cursor.x)*(2048.0f/static_cast<float>(static_cast<unsigned int>(m_width))));
    int settingsWidth = m_settings->GetInt(KSETTINGS_RES_WIDTH);
    m_settings->GetInt(KSETTINGS_RES_HEIGHT);
    bool allowed = !m_pGameUI->mouseOverPanel(static_cast<int>(cursor.x),static_cast<int>(cursor.y));
    if (m_pGameUI && m_pGameUI->rightCovered()) {
        float edge = m_pGameUI ? m_pGameUI->rightScreenEdge() : 1024.0f;
        x = static_cast<long>(static_cast<float>(x)*(1.0f/(edge/static_cast<float>(static_cast<unsigned int>(settingsWidth)))));
        if (static_cast<float>(x) > 2048.0f) allowed = false;
    } else if (m_pGameUI && m_pGameUI->leftCovered()) {
        float edge = m_pGameUI ? m_pGameUI->leftScreenEdge() : 0.0f;
        float fraction = edge/static_cast<float>(static_cast<unsigned int>(settingsWidth));
        x = static_cast<long>(static_cast<float>(x)+fraction*-2048.0f);
        x = static_cast<long>(static_cast<float>(x)*(1.0f/(1.0f-fraction)));
        if (x < 0) allowed = false;
    }
    Ogre::Camera* camera = m_cameraControl->m_pUnknown10;
    float nearDistance = camera->getNearClipDistance();
    float farDistance = camera->getFarClipDistance();
    Ogre::Matrix4 projection = camera->getProjectionMatrix();
    int y = static_cast<int>(static_cast<float>(cursor.y)*(1536.0f/static_cast<float>(static_cast<unsigned int>(m_height))));
    float projectedX = (static_cast<float>(x)*0.0009765625f-1.0f)/projection[0][0];
    float projectedY = (static_cast<float>(y)/-768.0f+1.0f)/projection[1][1];
    Ogre::Vector3 nearPoint(nearDistance*projectedX,nearDistance*projectedY,-nearDistance);
    Ogre::Vector3 farPoint(farDistance*projectedX,farDistance*projectedY,-farDistance);
    Ogre::Matrix4 view = camera->getViewMatrix();
    view = view.inverse();
    view.setTrans(Ogre::Vector3::ZERO);
    Ogre::Quaternion orientation = camera->getOrientation();
    nearPoint = orientation*nearPoint;
    farPoint = orientation*farPoint;
    Ogre::Ray ray(Ogre::Vector3::ZERO,Ogre::Vector3::UNIT_Z);
    float screenX = static_cast<float>(x)*0.00048828125f;
    float screenY = static_cast<float>(y)/1536.0f;
    camera->getCameraToViewportRay(screenX,screenY,&ray);
    Ogre::Vector3 normal(0,1,0);
    const float* position = m_pPlayer->m_lastWorldPosition;
    float planeHeight = position[0]*normal.x+(position[1]+(offset?1.7f:0.0f))*normal.y+position[2]*normal.z;
    float distance = MATH::distanceToPlane(ray.getOrigin(),ray.getDirection(),normal,planeHeight);
    result.x = ray.getOrigin().x+ray.getDirection().x*distance;
    result.y = 0;
    result.z = ray.getOrigin().z+ray.getDirection().z*distance;
    if (m_level && !m_pPlayer->m_isPathing) {
        camera->getCameraToViewportRay(screenX,screenY,&ray);
        Ogre::Vector3 start = ray.getOrigin();
        Ogre::Vector3 end = ray.getOrigin()+ray.getDirection()*200.0f;
        Ogre::Vector3 hit,hitNormal,collisionPosition;
        unsigned int collisionIndex;
        if (m_gameResources->getLevel()->rayCollision(start,end,hit,hitNormal,collisionIndex,collisionPosition,false) && collisionIndex != 100 && (hit-start).length() > 10.0f) {
            start = hit;
            end = hit;
            start.y += 1000.0f;
            end.y -= 1000.0f;
            if (m_gameResources->getLevel()->rayCollision(start,end,hit,hitNormal,collisionIndex,collisionPosition,false) && collisionIndex != 100 && hitNormal.y > 0.2f) {
                float heightDelta = hit.y-m_pPlayer->m_lastWorldPosition[1];
                if (std::fabs(heightDelta) < 14.0f) {
                    camera->getCameraToViewportRay(screenX,screenY,&ray);
                    planeHeight = (m_pPlayer->m_lastWorldPosition[1]+heightDelta)+(offset?1.7f:0.0f);
                    distance = MATH::distanceToPlane(ray.getOrigin(),ray.getDirection(),normal,planeHeight);
                    result.x = ray.getOrigin().x+ray.getDirection().x*distance;
                    result.y = 0;
                    result.z = ray.getOrigin().z+ray.getDirection().z*distance;
                }
            }
        }
    }
    if (!allowed) {
        m_targetCharacter.setObject(NULL);
        m_targetItem.setObject(NULL);
    }
    return allowed;
}
void CGameClient::mouseOverCharacter()
{
    POINT cursor;
    GetCursorPos(&cursor);
    short left = GetAsyncKeyState(1);
    short right = GetAsyncKeyState(2);
    if (m_leftHeld && left >= 0) mouseEvent(0x202,1);
    if (m_rightHeld && right >= 0) mouseEvent(0x205,1);
    long x = static_cast<int>(static_cast<float>(cursor.x)*(2048.0f/static_cast<float>(static_cast<unsigned int>(m_width))));
    int settingsWidth = m_settings->GetInt(KSETTINGS_RES_WIDTH);
    m_settings->GetInt(KSETTINGS_RES_HEIGHT);
    if (m_pGameUI && m_pGameUI->rightCovered()) {
        float edge = m_pGameUI ? m_pGameUI->rightScreenEdge() : 1024.0f;
        x = static_cast<long>(static_cast<float>(x)*(1.0f/(edge/static_cast<float>(static_cast<unsigned int>(settingsWidth)))));
        if (x > 2048) {
            m_targetCharacter.setObject(NULL);
            m_targetItem.setObject(NULL);
            return;
        }
    } else if (m_pGameUI && m_pGameUI->leftCovered()) {
        float edge = m_pGameUI ? m_pGameUI->leftScreenEdge() : 0;
        float fraction = edge/static_cast<float>(static_cast<unsigned int>(settingsWidth));
        x = static_cast<long>(static_cast<float>(x)+fraction*-2048.0f);
        x = static_cast<long>(static_cast<float>(x)*(1.0f/(1.0f-fraction)));
        if (x < 0) {
            m_targetCharacter.setObject(NULL);
            m_targetItem.setObject(NULL);
            return;
        }
    }
    int y = static_cast<int>(static_cast<float>(cursor.y)*(1536.0f/static_cast<float>(static_cast<unsigned int>(m_height))));
    float screenX = (static_cast<float>(x)-1024.0f)*0.0009765625f;
    float screenY = -(static_cast<float>(y)-768.0f)/768.0f;
    Ogre::Matrix3 rotation;
    m_cameraControl->m_pUnknown10->getOrientation().ToRotationMatrix(rotation);
    Ogre::Matrix4 view = Ogre::Matrix4::IDENTITY;
    view = rotation;
    view.setTrans(m_cameraControl->m_pUnknown10->getPosition());
    view = view.inverse();
    Ogre::Matrix4 projection = m_cameraControl->m_pUnknown10->getProjectionMatrix();
    m_targetCharacter.setObject(m_level->findCharacterAtScreenCoordinates(view,projection,screenX,screenY,m_pPlayer));
    if (m_targetCharacter.getObject() && (!m_targetCharacter.getObject()->getVisible() || !m_targetCharacter.getObject()->getEnabled()))
        m_targetCharacter.setObject(NULL);
    if (m_targetCharacter.getObject()) m_targetItem.setObject(NULL);
    else m_targetItem.setObject(m_level->findItemAtScreenCoordinates(view,projection,screenX,screenY));
}
#include "SoundBankDataInformation.h"
#include "SoundBank.h"
#include "SoundData.h"

bool CGameClient::create()
{
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_OVERRIDE_LIGHTING) > 0) {
        Ogre::ColourValue ambient(
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_AMBIENT_LIGHT_RED)/255.0f,
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_AMBIENT_LIGHT_GREEN)/255.0f,
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_AMBIENT_LIGHT_BLUE)/255.0f,1.0f);
        m_sceneManager28->setAmbientLight(ambient);
    } else m_sceneManager28->setAmbientLight(Ogre::ColourValue(0.29019609093666077f,0.29019609093666077f,0.29019609093666077f,1.0f));
    m_ambientLight = m_sceneManager28->createLight("Sunlight");
    m_ambientLight->setType(Ogre::Light::LT_DIRECTIONAL);
    m_ambientLight->setPosition(40.0f,150.0f,-40.0f);
    Ogre::Vector3 direction = -m_ambientLight->getPosition();
    direction.normalise();
    m_ambientLight->setDirection(direction);
    m_ambientLight->setSpecularColour(0.5f,0.5f,0.5f);
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_OVERRIDE_LIGHTING) > 0) {
        CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_DIRECTIONAL_INTENSITY);
        Ogre::ColourValue diffuse(
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_RED)/255.0f*1.9f,
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_GREEN)/255.0f*1.9f,
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_BLUE)/255.0f*1.9f,1.0f);
        m_ambientLight->setDiffuseColour(diffuse);
    } else m_ambientLight->setDiffuseColour(Ogre::ColourValue(1.7733333110809326f,1.6317646503448486f,1.1549019813537598f,1.0f));
    m_ambientLight->setCastShadows(false);
    m_sceneManager38->setAmbientLight(Ogre::ColourValue(0.5f,0.5f,0.5f,1.0f));
    m_resources->setAmbientLight(Ogre::ColourValue(0.5f,0.5f,0.5f,1.0f));
    Ogre::Light* petLight = m_sceneManager38->createLight("Sunlight");
    petLight->setType(Ogre::Light::LT_DIRECTIONAL);
    petLight->setPosition(10.0f,80.0f,60.0f);
    direction = -petLight->getPosition();
    direction.normalise();
    petLight->setDirection(direction);
    petLight->setDiffuseColour(2.0f,2.0f,2.0f);
    petLight->setSpecularColour(0.5f,0.5f,0.5f);
    petLight->setCastShadows(false);
    m_menuSound = new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
    CSoundData* data = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation->getSoundDataObject(L"TOWNPORTALENTER");
    if (data) m_menuSound->addSample(28,data->m_iGuid);
    if (!m_gameResources->m_bFlag3) setGameState(static_cast<EGameState>(0),static_cast<EMenu>(0));
    return true;
}

#include "GameClientData.h"
#include "GameSpeed.h"
#include "Layout.h"
#include "GenericModel.h"
#include "SkillManager.h"
#include "ParticleUniverseSystemManager.h"
#include "LinuxUtils.h"
#include <OgreMeshManager.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>

void CGameClient::update(float elapsed,Ogre::RenderWindow* window,float otherElapsed,bool enabled)
{
    if (m_pGameUI) {
        if (GForceMenuExit && !m_pGameUI->modalDialogOpen()) {
            GForceMenuExit = false;
            setGameState(static_cast<EGameState>(0),static_cast<EMenu>(0));
        }
        m_pGameUI->getUIIsInCinematic();
        bool cinematic = m_pGameUI->getUIIsInCinematic();
        if (cinematic != gCinematicActive && m_level) {
            m_level->updateNPCIcons();
            gCinematicActive = cinematic;
        }
    }
    if (m_blockInputFrames > 0) {
        --m_blockInputFrames;
        m_gameResources->m_bFlag0 = true;
    } else m_gameResources->m_bFlag0 = false;
    if (m_pGameUI && m_pGameUI->m_requestedGameState != static_cast<EGameState>(6) &&
        !m_pGameUI->modalDialogOpen() && !m_pGameUI->leftCovered() && !m_pGameUI->rightCovered()) {
        if (m_pGameUI->m_requestedGameState == static_cast<EGameState>(0) && m_gameState == static_cast<EGameState>(1)) {
            m_pGameUI->closeAll();
            killPets();
            saveCharacter(false,true);
        }
        setGameState(m_pGameUI->m_requestedGameState,m_pGameUI->m_requestedMenu);
        m_pGameUI->clearGameStateRequest();
        m_mouseManager.flushAll();
        m_keyManager.flushAll();
        m_leftHeld = false;
        m_rightHeld = false;
        m_inputConsumed = true;
    }
    if (m_gameState == static_cast<EGameState>(0)) updateMenu(elapsed,window,otherElapsed,enabled);
    else if (m_gameState == static_cast<EGameState>(1)) updateIngame(elapsed,window,otherElapsed,enabled);
    else if (m_gameState == static_cast<EGameState>(5)) {
        m_transitionTime -= otherElapsed;
        if (m_transitionTime <= 0.0f) setGameState(static_cast<EGameState>(1),static_cast<EMenu>(0));
    }
    if (m_deferredFrames > 0 && --m_deferredFrames == 0) {
        Ogre::MeshManager::getSingleton().unloadUnreferencedResources(true);
        Ogre::MaterialManager::getSingleton().unloadUnreferencedResources(true);
        Ogre::TextureManager::getSingleton().unloadUnreferencedResources(true);
        CMasterResourceManager::getSingleton()->m_pSoundManager->releaseUnusedSounds();
        m_masterResources->removeUnused();
    }
}


#include "GameSpeed.h"
#include <OgreViewport.h>
bool CGameClient::unloadCurrentLevel(bool deleteCharacters)
{
    CGameSpeed::getSingleton()->clear();
    if (m_pGameUI) m_pGameUI->hideTextEvents();
    m_questManager->setPlayer(NULL);
    if (deleteCharacters) {
        if (m_pPlayer && m_level) m_level->removeCharacter(m_pPlayer,true);
        if (m_creationPet && m_level) m_level->removeCharacter(m_creationPet,true);
    }
    if (m_gameResources->getCameraControl()) m_gameResources->getCameraControl()->clearCameraShakes();
    if (m_renderWindow) m_renderWindow->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
    m_sceneManager28->setFog(Ogre::FOG_NONE,Ogre::ColourValue::White,0.001f,0.0f,1.0f);
    m_targetCharacter.setObject(NULL);
    m_selectedCharacter.setObject(NULL);
    m_targetItem.setObject(NULL);
    m_selectedItem.setObject(NULL);
    if (m_pGameUI) {
        m_pGameUI->setPlayer(NULL);
        m_pGameUI->setLevel(NULL);
        m_pGameUI->cleanupReferences();
    }
    if (m_level) {
        m_level->clearProjectorPass(m_menuModel1,m_menuModel2);
        if (m_level) { delete m_level; m_level = NULL; }
    }
    m_gameResources->m_pLevel = NULL;
    if (m_menuLayout) {
        m_menuLayout->setVisible(false);
        if (m_menuLayout) { delete m_menuLayout; m_menuLayout = NULL; }
    }
    if (m_menuModel0) {
        m_menuModel0->setVisible(false);
        if (m_menuModel0) { delete m_menuModel0; m_menuModel0 = NULL; }
        m_menuModel0 = NULL;
    }
    if (m_menuModel1) {
        m_menuModel1->setVisible(false);
        if (m_menuModel1) { delete m_menuModel1; m_menuModel1 = NULL; }
        m_menuModel1 = NULL;
    }
    if (m_menuModel3) {
        m_menuModel3->setVisible(false);
        if (m_menuModel3) { delete m_menuModel3; m_menuModel3 = NULL; }
        m_menuModel3 = NULL;
    }
    if (m_menuModel2) {
        m_menuModel2->setVisible(false);
        if (m_menuModel2) { delete m_menuModel2; m_menuModel2 = NULL; }
        m_menuModel2 = NULL;
    }
    if (deleteCharacters) {
        if (m_pPlayer) { delete m_pPlayer; m_pPlayer = NULL; }
        if (m_creationPet) { delete m_creationPet; m_creationPet = NULL; }
    }
    m_pPlayer = NULL;
    m_creationPet = NULL;
    m_questManager->setPlayer(NULL);
    return true;
}


void CGameClient::clickLeft()
{
    if (getIsPaused() || !m_pPlayer->alive() || !m_pPlayer->getEnabled()) return;
    if (m_pPlayer->m_eAIState == 34 || m_pPlayer->m_eAIState == 20) return;
    if (!m_leftHeld) m_pPlayer->m_pathGraceTime = 10;
    if (m_targetCharacter.getObject() && m_selectedCharacter.getObject() && !m_selectedCharacter.getObject()->alive()
        && m_targetCharacter.getObject() != m_selectedCharacter.getObject())
        m_selectedCharacter.setObject(m_targetCharacter.getObject());
    if (m_targetItem.getObject() && !m_selectedItem.getObject() && !m_selectedCharacter.getObject() && !m_leftHeld)
        m_selectedItem.setObject(m_targetItem.getObject());
    if (m_targetCharacter.getObject() && !m_selectedCharacter.getObject() && !m_selectedItem.getObject() && !m_leftHeld)
        m_selectedCharacter.setObject(m_targetCharacter.getObject());
    if (m_pPlayer->m_Padding4D0[0] || m_pPlayer->m_Padding4D0[1]) {
        if (!m_pPlayer->m_moveInputHeld) m_inputConsumed = true;
        m_pPlayer->m_Padding4D0[0] = 0;
        m_pPlayer->m_Padding4D0[1] = 0;
    }
    if (m_pPlayer->performingSkillLoose()) return;
    CItem* oldItem = m_pPlayer->m_targetItem.getObject();
    CCharacter* oldCharacter = m_pPlayer->m_targetCharacter.getObject();
    if (!m_pPlayer->performingSkillLoose() && !m_pPlayer->performingAttackLoose()) {
        if (m_selectedItem.getObject()) m_pPlayer->setTargetItem(m_selectedItem.getObject());
        if (m_selectedCharacter.getObject()) m_pPlayer->setTarget(m_selectedCharacter.getObject());
    }
    if (m_selectedCharacter.getObject() && (!m_selectedCharacter.getObject()->getVisible() || !m_selectedCharacter.getObject()->getEnabled()))
        m_selectedCharacter.setObject(NULL);
    if (m_selectedItem.getObject() && m_selectedItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) {
        if (!m_pPlayer->performingAttackLoose() && !m_pPlayer->inAttackRange(ATTACK_RANGE_DEFAULT)) {
            if (oldItem != m_selectedItem.getObject()) {
                m_pPlayer->stopPathing();
                oldItem = m_selectedItem.getObject();
            }
            m_pPlayer->setTargetItem(oldItem);
            goto approach;
        }
        goto attack;
    }
    if (m_selectedCharacter.getObject()) {
        if (m_pPlayer->isEnemy(m_selectedCharacter.getObject())) {
            if (!m_pPlayer->performingAttackLoose() && !m_pPlayer->inAttackRange(ATTACK_RANGE_DEFAULT)) {
                if (oldCharacter != m_selectedCharacter.getObject()) {
                    m_pPlayer->stopPathing();
                    oldCharacter = m_selectedCharacter.getObject();
                }
                m_pPlayer->setTarget(oldCharacter);
                goto approach;
            }
            goto attack;
        }
        if (m_selectedCharacter.getObject() && m_selectedCharacter.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(131))) {
            m_pPlayer->setTarget(m_selectedCharacter.getObject());
            m_pPlayer->setAIState(static_cast<EAIState>(9));
            m_pPlayer->setDestination(*m_level,m_selectedCharacter.getObject()->getPosition(true).x,m_selectedCharacter.getObject()->getPosition(true).z);
            return;
        }
    }
    if (m_selectedItem.getObject()) {
        if (!m_selectedItem.getObject()->m_bRangeEnabled || !m_selectedItem.getObject()->getEnabled()) return;
        CCharacter* actor = m_pPlayer;
        if (m_keyManager.keyHeld(m_settings->GetInt(KSETTINGS_KEYMAP_HOLDPOS)) && !m_pPlayer->m_Followers.empty()) {
            CCharacter* follower = m_pPlayer->m_Followers[0];
            if (follower && !follower->isPetNearDeath() && follower->alive() && follower->m_eAIState != 42 && follower->m_eAIState != 41)
                actor = m_pPlayer->m_Followers.empty() ? NULL : m_pPlayer->m_Followers[0];
        }
        if (oldItem != actor->m_targetItem.getObject()) actor->stopPathing();
        actor->setTargetItem(m_selectedItem.getObject());
        actor->setAIState(static_cast<EAIState>(7));
        actor->stopPathing();
        actor->getItemAI(0,*m_level);
        return;
    }
    if (!m_leftHeld) {
        m_inputConsumed = false;
        m_pPlayer->setTarget(NULL);
        m_pPlayer->setTargetItem(NULL);
        m_pPlayer->setAIState(static_cast<EAIState>(0));
    }
    if (m_inputConsumed && !m_pPlayer->m_moveInputHeld) return;
    moveToMouse(!m_leftHeld);
    return;
approach:
    m_pPlayer->setAIState(static_cast<EAIState>(4));
    m_pPlayer->huntAI(0,*m_level);
    if (m_pPlayer->m_eAIState != 3 && !m_pPlayer->performingSkill() && !m_pPlayer->m_isPathing) m_pPlayer->attack();
    return;
attack:
    if (!m_pPlayer->performingAttackLoose() && m_pPlayer->m_eAIState != 3 && !m_pPlayer->performingSkill()) {
        m_pPlayer->stopPathing();
        m_pPlayer->attack();
    }
}

void CGameClient::updateMenu(float elapsed,Ogre::RenderWindow* window,float otherElapsed,bool enabled)
{
    if (m_pGameUI && m_pGameUI->isCinematicMenuOpen()) m_pGameUI->closeCinematicMenu();
    if (elapsed > 0.3f) elapsed = 0.3f;
    static float gTorchlightUpdate = 0;
    gTorchlightUpdate += elapsed;
    if (gTorchlightUpdate > 0.016f) {
        gTorchlightUpdate = 0;
        m_lightFlicker += UTILITIES::randomBetweenVolatile(2.0f,5.0f)*elapsed;
        if (UTILITIES::randomBetweenVolatile(0.0f,10.0f) > 7.0f)
            m_lightFlicker += UTILITIES::randomBetweenVolatile(-0.2f,0.2f);
        while (m_lightFlicker >= 6.2831854820251465f) m_lightFlicker -= 6.2831854820251465f;
    }
    m_playerLight->setCorners(-0.5f,0.5f,0.5f,-0.5f);
    m_playerLight->setBoundingBox(Ogre::AxisAlignedBox(Ogre::Vector3::UNIT_SCALE*-100000.0f,Ogre::Vector3::UNIT_SCALE*100000.0f));
    CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_paused = false;
    m_mouseManager.capture();
    m_keyManager.capture();
    unsigned int steps = static_cast<unsigned int>(ceilf(elapsed/0.016f));
    if (steps > 5) steps = 5;
    if (!steps) steps = 1;
    elapsed /= static_cast<float>(steps);
    if (otherElapsed == 0.0f && enabled) otherElapsed = static_cast<float>(steps)*elapsed;
    for (unsigned int i=0;i<steps;++i)
        m_level->update(m_cameraControl->m_pUnknown10,m_level->m_auxiliaryPosition194,elapsed,1.0f,m_pPlayer);
    if (m_menuLayout) m_menuLayout->update(otherElapsed);
    if (enabled) {
        m_level->updateLayouts(otherElapsed);
        m_level->updateCharacterAnimation(otherElapsed,1.0f,NULL);
        bool paused = getIsPaused();
        Ogre::Vector3 position(m_cameraControl->m_fUnknown4C,m_cameraControl->m_fUnknown50,m_cameraControl->m_fUnknown54);
        m_level->updateVisibleParticles(m_cameraControl->m_pUnknown10,position,paused);
    }
    if (m_pGameUI) {
        m_pGameUI->update(otherElapsed,this,window);
        if (m_pGameUI->m_bExitButtonPressed) m_quitRequested = true;
        if (m_pGameUI->m_gap12FA) m_restartRequested = true;
        m_pGameUI->setCursorState(static_cast<ECursorState>(0));
    }
    if (m_cameraControl->m_pUnknown10) {
        m_cameraControl->updateGameCamera(otherElapsed,m_gameResources,m_level->m_auxiliaryPosition194,static_cast<ECAMERA_STATES>(3));
        if (m_menuModel0) m_menuModel0->setPosition(m_cameraControl->m_pUnknown10->getPosition());
    }
    m_audioListenerPosition = m_level->m_auxiliaryPosition194;
    CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_cameraPosition = m_level->m_auxiliaryPosition194;
    if (m_menuLayout) m_menuLayout->setPosition(m_level->m_auxiliaryPosition194);
    CSkillManager::globallyDisableSkills(false);
}

#include "LevelTemplateData.h"
#include <OgreViewport.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>

void CGameClient::refreshLighting()
{
    Ogre::ColourValue colour = Ogre::ColourValue::ZERO;
    if (m_gameState == static_cast<EGameState>(0)) m_cameraControl->m_pUnknown10->setFarClipDistance(180);
    else if (m_settings->GetInt(KSETTINGS_NETBOOK_MODE) == 1) m_cameraControl->m_pUnknown10->setFarClipDistance(45);
    else m_cameraControl->m_pUnknown10->setFarClipDistance(90);
    if (m_level && m_level->m_pLevelTemplateData) {
        CLevelTemplateData* data = m_level->m_pLevelTemplateData;
        colour = Ogre::ColourValue(data->m_ambientColorR,data->m_ambientColorG,data->m_ambientColorB,data->m_ambientColorA);
        m_sceneManager28->setAmbientLight(colour);
        data = m_level->m_pLevelTemplateData;
        colour = Ogre::ColourValue(data->m_directionalColorR,data->m_directionalColorG,data->m_directionalColorB,data->m_directionalColorA);
        m_ambientLight->setDiffuseColour(colour);
        data = m_level->m_pLevelTemplateData;
        m_ambientLight->setPosition(Ogre::Vector3(data->m_directionalX,data->m_directionalY,data->m_directionalZ));
        Ogre::Vector3 direction = -m_ambientLight->getPosition();
        direction.normalise();
        m_ambientLight->setDirection(direction);
        m_level->updateMaterialAmbient();
        data = m_level->m_pLevelTemplateData;
        m_renderWindow->getViewport(0)->setBackgroundColour(Ogre::ColourValue(data->m_fogColorR,data->m_fogColorG,data->m_fogColorB,data->m_fogColorA));
        float fogScale = m_settings->GetInt(KSETTINGS_NETBOOK_MODE) == 1 ? 1.0f : 1.2999999523162842f;
        data = m_level->m_pLevelTemplateData;
        m_sceneManager28->setFog(Ogre::FOG_LINEAR,Ogre::ColourValue(data->m_fogColorR,data->m_fogColorG,data->m_fogColorB,data->m_fogColorA),0,data->m_fogStart*fogScale,data->m_fogEnd*fogScale);
        if (m_lightTexture) {
            Ogre::RenderTarget* target = m_lightTexture->getBuffer(0,0)->getRenderTarget(0);
            data = m_level->m_pLevelTemplateData;
            target->getViewport(0)->setBackgroundColour(Ogre::ColourValue(data->m_lightmapColorR,data->m_lightmapColorG,data->m_lightmapColorB,data->m_lightmapColorA));
            Ogre::TextureUnitState* texture = m_lightMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
            texture->setTextureName(STRINGS::StringConvertToUTF8(std::wstring(m_level->m_pLevelTemplateData->m_torchlightTexture.c_str())),Ogre::TEX_TYPE_2D);
            texture = m_shadowMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
            texture->setTextureName(STRINGS::StringConvertToUTF8(std::wstring(m_level->m_pLevelTemplateData->m_shadowFadeTexture.c_str())),Ogre::TEX_TYPE_2D);
            texture = m_lightMultiplyMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
            texture->setTextureName(STRINGS::StringConvertToUTF8(std::wstring(m_level->m_pLevelTemplateData->m_lightMaskTexture.c_str())),Ogre::TEX_TYPE_2D);
            m_pendingPassClear = true;
        }
        Ogre::Camera* shadowCamera = m_cameraControl->m_pUnknown30;
        if (shadowCamera) {
            if (m_level->m_pLevelTemplateData->m_orthographicShadows) {
                shadowCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
                shadowCamera->setFrustumExtents(-8,8,8,-8);
            } else {
                shadowCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
                shadowCamera->setFOVy(Ogre::Degree(120));
                shadowCamera->resetFrustumExtents();
            }
        }
    } else {
        m_renderWindow->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
        m_sceneManager28->setFog(Ogre::FOG_LINEAR,Ogre::ColourValue(0.11764705926179886f,0.16470588743686676f,0.22745098173618317f,1),0,24,50);
        CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
        colour = Ogre::ColourValue(settings->GetInt(KSETTINGS_AMBIENT_LIGHT_RED)/255.0f,settings->GetInt(KSETTINGS_AMBIENT_LIGHT_GREEN)/255.0f,settings->GetInt(KSETTINGS_AMBIENT_LIGHT_BLUE)/255.0f,1);
        m_sceneManager28->setAmbientLight(colour);
        float intensity = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_DIRECTIONAL_INTENSITY);
        settings = CMasterResourceManager::getSingleton()->m_pSettings;
        colour = Ogre::ColourValue(settings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_RED)/255.0f*intensity,settings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_GREEN)/255.0f*intensity,settings->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_BLUE)/255.0f*intensity,1);
        m_ambientLight->setDiffuseColour(colour);
    }
}

void CGameClient::resetShadows(bool enabled)
{
    bool previous = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED) != 0;
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,enabled);
    if (m_level) m_level->clearProjectorPass(m_menuModel1,m_menuModel2);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,previous);
    if (m_shadowTexture) {
        Ogre::RenderTarget* target = m_shadowTexture->getBuffer(0,0)->getRenderTarget(0);
        target->removeAllListeners();
        target->removeAllViewports();
        Ogre::ResourcePtr resource = Ogre::TextureManager::getSingleton().getByHandle(m_shadowTexture->getHandle());
        Ogre::TextureManager::getSingleton().remove(resource);
    }
    if (m_lightTexture) {
        Ogre::RenderTarget* target = m_lightTexture->getBuffer(0,0)->getRenderTarget(0);
        target->removeAllListeners();
        target->removeAllViewports();
        Ogre::ResourcePtr resource = Ogre::TextureManager::getSingleton().getByHandle(m_lightTexture->getHandle());
        Ogre::TextureManager::getSingleton().remove(resource);
    }
    Ogre::TextureManager::getSingleton().unloadUnreferencedResources(true);
    m_shadowTexture = NULL;
    m_lightTexture = NULL;
    int resolution = m_settings->GetInt(KSETTINGS_SHADOW_RESOLUTION);
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED)) {
        m_projectorTexture = STRINGS::uniqueName("ProjectorRTT");
        m_shadowTexture = Ogre::TextureManager::getSingleton().createManual(m_projectorTexture,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,Ogre::TEX_TYPE_2D,resolution,resolution,1,0,Ogre::PF_R8G8B8,Ogre::TU_RENDERTARGET).getPointer();
        Ogre::RenderTarget* target = m_shadowTexture->getBuffer(0,0)->getRenderTarget(0);
        target->addViewport(m_cameraControl->m_pUnknown30,0,0,0,1,1);
        target->getViewport(0)->setShadowsEnabled(false);
        target->getViewport(0)->setClearEveryFrame(true,Ogre::FBT_COLOUR|Ogre::FBT_DEPTH);
        target->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0.5f,0.5f,0.5f,1));
        target->getViewport(0)->setOverlaysEnabled(true);
        target->setAutoUpdated(true);
        target->addListener(this);
    }
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_LIGHTING_ENABLED)) {
        m_projectorFalloffTexture = STRINGS::uniqueName("ProjectorRTTLight");
        m_lightTexture = Ogre::TextureManager::getSingleton().createManual(m_projectorFalloffTexture,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,Ogre::TEX_TYPE_2D,resolution,resolution,1,0,Ogre::PF_R8G8B8,Ogre::TU_RENDERTARGET).getPointer();
        Ogre::RenderTarget* target = m_lightTexture->getBuffer(0,0)->getRenderTarget(0);
        target->addViewport(m_cameraControl->m_pUnknown28,0,0,0,1,1);
        target->getViewport(0)->setShadowsEnabled(false);
        target->getViewport(0)->setClearEveryFrame(true,Ogre::FBT_COLOUR|Ogre::FBT_DEPTH);
        target->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0.094117648899555206f,0.094117648899555206f,0.094117648899555206f,1));
        target->getViewport(0)->setOverlaysEnabled(true);
        target->setAutoUpdated(true);
        target->addListener(this);
    }
    m_level->setProjectorPass(m_cameraControl->m_pUnknown30,m_cameraControl->m_pUnknown28,m_menuModel1,m_menuModel2,m_projectorTexture,m_projectorFalloffTexture);
    refreshLighting();
}

#include "SteamStats.h"
#include "LevelTemplateData.h"
#include <OgreEntity.h>

void CGameClient::loadMenuLevel(int,int depth,std::wstring dungeon)
{
    CSteamStats::getSingleton()->forceStatsToSave();
    setCurrentDungeon(dungeon);
    m_level = new CLevel(dungeon,m_settings,this,m_gameResources,m_sceneManager28,m_soundManager,m_gameSeed,0);
    resetGameSeed(depth);
    CLevelTemplateData* data = m_currentDungeon->getLevelTemplateDataForDepth(this,depth);
    if (data) m_level->loadRoomLayout(data->m_mainMenuRules,false,static_cast<ELevelEntryType>(3),NULL,EMPTY_WSTRING);
    else m_level->loadRoomLayout(L"media/layouts/mainmenus/mainmenu_townrules.dat",false,static_cast<ELevelEntryType>(3),NULL,EMPTY_WSTRING);
    m_level->m_updateRange = 9999999.0f;
    m_soundManager->m_bUnknown6A9 = true;
    m_level->activate();
    if (!m_menuModel0) {
        if (m_level->m_pLevelTemplateData) {
            if (!std::wstring(m_level->m_pLevelTemplateData->m_skybox).empty())
                { std::wstring filename = m_level->m_pLevelTemplateData->m_skybox;
                m_menuModel0 = m_gameResources->createGenericModel(NULL,filename.c_str(),L"",false,false,false); }
        } else m_menuModel0 = m_gameResources->createGenericModel(NULL,L"media/skyboxes/crypt/crypt_sky.mesh",L"",false,false,false);
        if (m_menuModel0) {
            m_menuModel0->getEntity()->setRenderQueueGroup(5);
            m_menuModel0->setVisible(true);
        }
    }
    if (!m_menuModel1) {
        if (m_level->m_pLevelTemplateData && std::wstring(m_level->m_pLevelTemplateData->m_water) != L"") {
            { std::wstring filename = m_level->m_pLevelTemplateData->m_water;
                m_menuModel1 = m_gameResources->createGenericModel(NULL,filename.c_str(),L"",false,false,false); }
            m_menuModel1->getEntity()->setRenderQueueGroup(4);
            m_menuModel1->setVisible(true);
            m_menuModel1->setPosition(Ogre::Vector3(0,0,0));
        }
    }
    if (!m_menuModel3) {
        if (m_level->m_pLevelTemplateData && std::wstring(m_level->m_pLevelTemplateData->m_postWater) != L"") {
            { std::wstring filename = m_level->m_pLevelTemplateData->m_postWater;
                m_menuModel3 = m_gameResources->createGenericModel(NULL,filename.c_str(),L"",false,false,false); }
            m_menuModel3->getEntity()->setRenderQueueGroup(89);
            m_menuModel3->setVisible(true);
            m_menuModel3->setPosition(Ogre::Vector3(0,0,0));
        }
    }
    if (!m_menuModel2) {
        if (m_level->m_pLevelTemplateData && std::wstring(m_level->m_pLevelTemplateData->m_midWater) != L"") {
            { std::wstring filename = m_level->m_pLevelTemplateData->m_midWater;
                m_menuModel2 = m_gameResources->createGenericModel(NULL,filename.c_str(),L"",false,false,false); }
            m_menuModel2->getEntity()->setRenderQueueGroup(88);
            m_menuModel2->setVisible(true);
            m_menuModel2->setPosition(Ogre::Vector3(0,0,0));
        }
    }
    m_level->setProjectorPass(m_cameraControl->m_pUnknown30,m_cameraControl->m_pUnknown28,m_menuModel1,m_menuModel2,m_projectorTexture,m_projectorFalloffTexture);
    refreshLighting();
    if (m_cameraControl->m_pUnknown10) {
        m_cameraControl->m_pUnknown10->setPosition(m_level->m_auxiliaryPosition188);
        m_cameraControl->m_pUnknown10->lookAt(m_level->m_auxiliaryPosition194);
    }
    if (m_pGameUI) m_pGameUI->setCursorState(static_cast<ECursorState>(0));
    m_soundManager->stopMusic();
    std::wstring music = L"../music/Title.ogg";
    m_soundManager->playMusic(music,true);
    if (m_menuLayout) { delete m_menuLayout; m_menuLayout = NULL; }
    if (m_level->m_pLevelTemplateData && !std::wstring(m_level->m_pLevelTemplateData->m_levelParticle).empty()) {
        m_menuLayout = new CLayout(m_gameResources,static_cast<ELAYOUT_TYPES>(2));
        std::wstring layoutFilename = m_level->m_pLevelTemplateData->m_levelParticle;
        m_menuLayout->loadLayoutFile(layoutFilename,true,NULL,false,false,0);
        m_menuLayout->setVisible(true);
        m_menuLayout->setActivated(true);
        m_menuLayout->start();
    }
    m_deferredFrames = 3;
    m_level->setInited(true);
}

#include "Skill.h"
static unsigned int KSkillSlotsKeys[10];

bool CGameClient::clickRight(long long guid,bool held,bool leftSkill)
{
    if (!m_pPlayer->alive() || !m_pPlayer->getEnabled()) return false;
    if (!held) {
        m_pPlayer->m_pathGraceTime=10;
        m_pPlayer->setTarget(m_selectedCharacter.getObject());
        m_pPlayer->setTargetItem(m_selectedItem.getObject());
    }
    CSkill* skill=NULL;
    if (m_pPlayer->getSkillManager()) {
        skill=m_pPlayer->getSkillManager()->getSkillByGuid(guid);
        if (!skill) skill=m_pPlayer->getSkillManager()->getSkillByGuid(m_pPlayer->m_activeSkillGuid);
    }
    if (skill) {
        bool cursorTarget=false;
        if (skill->getTargetType()==7 || skill->getTargetType()==8) {
            cursorTarget=true;
            if (held) return false;
            if (m_pGameUI->m_cursorState==4 || m_pGameUI->m_cursorState==3) {
                m_pGameUI->m_guidB0=-1;
                m_pGameUI->setCursorState(static_cast<ECursorState>(0));
                return false;
            }
        }
        if (skill->getTargetType()!=3 && skill->getTargetType()!=9 && skill->getTargetType()!=10 && !cursorTarget) {
            Ogre::Vector3 position;
            if (!findWorldLocation(position,true)) return false;
        }
    } else {
        Ogre::Vector3 position;
        if (!findWorldLocation(position,true)) return false;
    }
    if (m_targetCharacter.getObject() && m_selectedCharacter.getObject() && !m_selectedCharacter.getObject()->alive()
        && m_targetCharacter.getObject()!=m_selectedCharacter.getObject())
        m_selectedCharacter.setObject(m_targetCharacter.getObject());
    if (m_targetItem.getObject() && !m_selectedItem.getObject() && !m_selectedCharacter.getObject() && !m_leftHeld && !m_rightHeld)
        m_selectedItem.setObject(m_targetItem.getObject());
    if (m_targetCharacter.getObject() && !m_selectedCharacter.getObject() && !m_selectedItem.getObject() && !m_leftHeld && !m_rightHeld) {
        bool keep=false;
        for (unsigned i=0;i<10;++i) {
            if (m_pPlayer->m_skillMap[i]!=-1 && m_keyManager.keyHeld(m_settings->GetInt(KSkillSlotsKeys[i]))) {
                if (m_pPlayer->getSkillManager()) {
                    CSkill* mapped=m_pPlayer->getSkillManager()->getSkillByGuid(m_pPlayer->m_skillMap[i]);
                    if (mapped==m_pPlayer->m_activeSkill && m_pPlayer->performingSkillLoose()) keep=true;
                }
                break;
            }
        }
        if (!keep && m_targetCharacter.getObject()!=m_selectedCharacter.getObject())
            m_selectedCharacter.setObject(m_targetCharacter.getObject());
    }
    if (m_pPlayer->m_Padding4D0[0] || m_pPlayer->m_Padding4D0[1]) {
        if (!m_pPlayer->m_moveInputHeld) m_inputConsumed=true;
        m_pPlayer->m_Padding4D0[0]=0;
        m_pPlayer->m_Padding4D0[1]=0;
    }
    if (m_pPlayer->performingAttackLoose()) return false;
    if (m_pPlayer->getSkillManager()) {
        skill=m_pPlayer->getSkillManager()->getSkillByGuid(guid);
        if (!skill) {
            guid=m_pPlayer->m_activeSkillGuid;
            skill=m_pPlayer->getSkillManager()->getSkillByGuid(guid);
        }
        if (skill) {
            if (!(m_pGameUI->equipmentTooltipVisible() && m_mouseManager.buttonHeld(static_cast<EMouseButton>(1)))) {
                if (skill->getTargetType()==7 || skill->getTargetType()==8) {
                    m_pGameUI->setCursorState(static_cast<ECursorState>(4));
                    m_pGameUI->m_guidB0=guid;
                    m_pGameUI->flushInput();
                    m_pGameUI->setRightButtonPressed();
                    return true;
                }
            }
        }
        if (getIsPaused() && skill && skill->getAnimationIndex()!=-1) return false;
    }
    if (getIsPaused() && m_pPlayer->m_activeSkill && m_pPlayer->m_activeSkill->getAnimationIndex()!=-1) return false;
    if (m_pPlayer->m_activeSkill && m_pPlayer->m_activeSkill->stopsPathingOnCompletion()) {
        if (m_pPlayer->performingSkill()) { moveToMouse(true); return true; }
        if (!m_pPlayer->castSkill(guid) && m_pPlayer->m_eAIState!=13)
            m_pPlayer->setAIState(static_cast<EAIState>(2));
    }
    if (leftSkill) {
        if (!m_selectedItem.getObject() && !m_selectedCharacter.getObject()) return false;
        if (m_selectedCharacter.getObject() && !m_pPlayer->isEnemy(m_selectedCharacter.getObject())) return false;
        if (m_selectedItem.getObject() && !m_selectedItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) return false;
    }
    CItem* oldItem=m_pPlayer->m_targetItem.getObject();
    CCharacter* oldCharacter=m_pPlayer->m_targetCharacter.getObject();
    if (!m_pPlayer->performingSkillLoose() && !m_pPlayer->performingAttackLoose()) {
        if (m_selectedItem.getObject()) m_pPlayer->setTargetItem(m_selectedItem.getObject());
        if (m_selectedCharacter.getObject()) m_pPlayer->setTarget(m_selectedCharacter.getObject());
    }
    if (m_selectedItem.getObject() && m_selectedItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) {
        if (oldItem!=m_selectedItem.getObject()) m_pPlayer->stopPathing();
        if (!m_pPlayer->performingSkill() && m_pPlayer->inSkillRange(guid,true)) {
            m_pPlayer->setTargetItem(m_selectedItem.getObject());
            m_pPlayer->setAIState(static_cast<EAIState>(15));
            m_pPlayer->skillApproachAI(0,*m_level,guid);
            if (!m_pPlayer->performingSkill() && m_pPlayer->inSkillRange(guid,true) && !m_pPlayer->m_isPathing) {
                if (!m_pPlayer->castSkill(guid) && m_pPlayer->m_eAIState!=13) {
                    if (leftSkill) return false;
                    m_pPlayer->setAIState(static_cast<EAIState>(2));
                }
            }
            return true;
        }
        if (!m_pPlayer->performingSkill() && !m_pPlayer->castSkill(guid) && m_pPlayer->m_eAIState!=13) {
            if (leftSkill) return false;
            m_pPlayer->setAIState(static_cast<EAIState>(2));
        }
        return true;
    }
    if (m_selectedCharacter.getObject() && m_pPlayer->isEnemy(m_selectedCharacter.getObject())) {
        if (oldCharacter!=m_selectedCharacter.getObject()) m_pPlayer->stopPathing();
        if (!m_pPlayer->performingSkill() && m_pPlayer->inSkillRange(guid,true)) {
            m_pPlayer->setTarget(m_selectedCharacter.getObject());
            m_pPlayer->setAIState(static_cast<EAIState>(15));
            m_pPlayer->skillApproachAI(0,*m_level,guid);
            if (!m_pPlayer->performingSkill() && m_pPlayer->inSkillRange(guid,true) && !m_pPlayer->m_isPathing) {
                if (!m_pPlayer->castSkill(guid)) {
                    if (leftSkill) return false;
                    m_pPlayer->setAIState(static_cast<EAIState>(2));
                }
            }
            return true;
        }
        if (!m_pPlayer->performingSkill() && !m_pPlayer->castSkill(guid) && m_pPlayer->m_eAIState!=13) {
            if (leftSkill) return false;
            m_pPlayer->setAIState(static_cast<EAIState>(2));
        }
        return true;
    }
    if (!held) {
        m_inputConsumed=false;
        m_pPlayer->setTarget(NULL);
        m_pPlayer->setTargetItem(NULL);
        if (!m_pPlayer->performingSkillLoose()) m_pPlayer->setAIState(static_cast<EAIState>(0));
    }
    Ogre::Vector3 position;
    findWorldLocation(position,true);
    m_pPlayer->setTarget(NULL);
    m_pPlayer->setTargetItem(NULL);
    m_pPlayer->setTargetDirection(position.x,position.z);
    m_pPlayer->castSkill(guid);
    if (!m_pPlayer->castSkill(guid) && m_pPlayer->m_eAIState!=13) return !leftSkill;
    return true;
}
