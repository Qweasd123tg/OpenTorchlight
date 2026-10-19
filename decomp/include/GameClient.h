#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <string>
#include <vector>
#include "Level.h"
#include <OgreRenderTargetListener.h>
#include <OgreRenderQueue.h>
#include <OgreVector3.h>
#include <OgreMaterial.h>
#include <OgreRectangle2D.h>
#include <string>

#include "RunicCore.h"
#include "MouseManager.h"
#include "SafePointer.h"
class CItem;
class CEquipment;
class CGenericModel;
class CLayout;
class CSoundBank;
class CLevelState;
class CCharacterSaveState;
class CQuestManager;
class CMasterResourceManager;
class CSoundManager;
namespace Ogre { class Texture; class Light; class SceneNode; class Root; class RenderWindow; class SceneManager; }
class CCameraControl;
class CSettings;
class CResourceManager;
class CLevel;
class CDungeon;
#include "KeyManager.h"
#include "QuestEventTypes.h"
#include "GameEnums.h"

class CBaseUnit;
class CCharacter;
class CPlayer;
class CPositionableObject;
class CGameUI;

// Partial: player and UI fields. Preserve all three base
// subobjects and the original 0x3910-byte allocation from GameClient.cpp.
class CGameClient : public CRunicCore, public Ogre::RenderTargetListener,
                    public Ogre::RenderQueue::RenderableListener
{
friend class CLevel;
    friend class CSettingsMenu;
    friend class CCharacter;
    friend class CPlayer;
    friend class CConsole;
    friend class CGame;
    friend class CGenericModel;
    friend class CQuestRewards;
    friend class CMonster;
friend class CDropdownMenu;
    friend class CWaypointMenu;
    friend class CCinematicMenu;
    friend class CQuestDialogMenu;
friend class CDifficultyMenu;
    friend class CResourceManager;
    friend class CInteract;
    friend class CCameraController;
    friend class CRandomGroup;
    friend class CEditor;
public:
    void updateMenu(float, Ogre::RenderWindow*, float, bool);
    bool unloadCurrentLevel(bool);
    void moveToMouse(bool);
    void clickLeft();
    void mouseOverCharacter();
    bool processIngameInput(void*, float, bool);
    void restoreLevelState(CLevelState*);
    CPlayer* loadCharacter(const std::wstring&, std::vector<CCharacter*>&,
                           std::vector<CCharacterSaveState*>&, bool);
    void applyCharacterState(CCharacterSaveState*, std::wstring&, CCharacterSaveState*);
    int getRankOfMonstersOnFloor(int, const std::wstring&, bool);
    void loadMenuLevel(int, int, std::wstring);
    void loadLevel(std::wstring, std::wstring, bool, int, ELevelEntryType, std::wstring);
    void performWarp();
    void updateIngame(float, Ogre::RenderWindow*, float, bool);
    void setGameState(EGameState, EMenu);
    int getRankOfMonstersOnFloor(int, CDungeon*, bool);
    bool findWorldLocation(Ogre::Vector3&, bool);
    CGameClient(CSettings&, CMasterResourceManager*, Ogre::RenderWindow*, Ogre::Root*, CCameraControl*, Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CSoundManager&);
    bool create();
    void update(float, Ogre::RenderWindow*, float, bool);
    void setSpeedMult(float multiplier);
    void findCameraTargetLocation(Ogre::Vector3& result, float plane);
    void autoPickupGold();
    bool getIsPaused();
    void killPets();
    void createGameUI(Ogre::RenderWindow*, void* window);
    bool processInput(void* window, float elapsed, bool enabled);
    bool storedUnitExists(long long guid);
    void setCurrentDungeon(std::wstring name);
    void resetGameSeed(int);
    void destroyGameUI();
    void updateScreenInfo(void* window, int width, int height);
    void handleFunctionKeys();
    void toggleLighting(bool enabled);
    void togglePlayerLight();
    std::wstring getPlayerClassName();
    void setCreationClass(std::wstring name);
    void setCreationPet(std::wstring name);
    void resetShadows(bool);
    void setEditorCreationPet(std::wstring name);
    void setEditorCreationClass(std::wstring name);
    bool processMenuInput(void* window, float elapsed, bool enabled);
    void notifyOfDeletion(CItem* object);
    void updateCursor();
    void reloadSoundBankData();
    void clearSceneManagerPassMaps();
    void mouseEvent(unsigned int event, unsigned int button);
    void keyEvent(unsigned int event, unsigned int key, long character);
    void setWindowActive(bool active);
    void notifyOfDeletion(CCharacter* object);
    TSafePointer<CRunicCore>& getMouseClickUnit(unsigned int index) { return reinterpret_cast<TSafePointer<CRunicCore>*>(&m_selectedCharacter)[index]; }

    void rescaleUI();

    void saveCharacter(bool,bool);
    EGameState getGameState() const { return m_gameState; }

    void refreshLighting();
    CKeyManager* getKeyManager() { return &m_keyManager; }


    void clearMouseClickUnits();
    bool clickRight(long long, bool, bool);
    void warpLevels(std::wstring dungeon, int delta, int depth, bool waypoint, std::wstring warpName, bool flag);
    virtual ~CGameClient();
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual bool renderableQueued(Ogre::Renderable*, unsigned char, unsigned short,
                                  Ogre::Technique**, Ogre::RenderQueue*);

    void setStateControlFlag(bool value) { m_bStateControl10BC = value; }
    bool getPlayerIsCheat();
    void questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target);
    CPlayer* getPlayer() { return m_pPlayer; }
    CGameUI* getGameUI() { return m_pGameUI; }

private:
    CCameraControl* m_cameraControl; // +0x20
    Ogre::SceneManager* m_sceneManager28;
    Ogre::SceneManager* m_sceneManager30;
    Ogre::SceneManager* m_sceneManager38;
    Ogre::SceneManager* m_resources; // +0x40, borrowed master render-behind-particle scene
    CSoundManager* m_soundManager;
    CSettings* m_settings; // +0x50
    CPlayer* m_pPlayer;
    CCharacter* m_creationPet; // +0x60
    CQuestManager* m_questManager;
    CLevel* m_level; // +0x70
    CGameUI* m_pGameUI;
    float m_moveTimer; // +0x80
    int m_blockInputFrames; // +0x84
    void* m_window;
    int m_width;
    int m_height;
    bool m_inputConsumed;
    bool m_leftHeld;
    bool m_rightHeld;
    unsigned char m_gap9B[0x1a0-0x9b];
    std::wstring m_characterFilename; // +0x1a0
    std::wstring m_editorCreationClass;
    std::wstring m_editorCreationPet;
    bool m_startHardcore; // +0x1b8
    unsigned char m_gap1B9[7];
    CPositionableObject* m_cameraWatchTarget; // +0x1c0, console WATCH override
    TSafePointer<CCharacter> m_selectedCharacter;
    TSafePointer<CCharacter> m_targetCharacter;
    TSafePointer<CItem> m_targetItem;
    TSafePointer<CItem> m_selectedItem;
    Ogre::Texture* m_shadowTexture; // +0x208
    Ogre::Texture* m_lightTexture; // +0x210
    Ogre::SceneNode* m_shadowNode; // +0x218
    Ogre::SceneNode* m_playerLightNode;
    Ogre::SceneNode* m_lightMultiplyNode; // +0x228
    Ogre::Rectangle2D* m_playerLight; // +0x230, original lighting screen quad
    Ogre::Rectangle2D* m_lightMultiplyQuad; // +0x238
    Ogre::Rectangle2D* m_shadowQuad; // +0x240
    Ogre::MaterialPtr m_shadowMaterial; // +0x248
    Ogre::MaterialPtr m_lightMaterial; // +0x268
    Ogre::MaterialPtr m_lightMultiplyMaterial; // +0x288
    float m_lightFlicker; // +0x2a8
    float m_transitionTime; // +0x2ac
    bool m_shadowPass; // +0x2b0
    unsigned char m_gap2B1[7];
    CResourceManager* m_gameResources; // +0x2b8, owned by GameClient
    Ogre::Vector3 m_audioListenerPosition; // +0x2c0
    unsigned char m_gap2CC[4];
    CKeyManager m_keyManager;
    CMouseManager m_mouseManager; // +0xfe8
    int m_deferredFrames; // +0x1038
    bool m_quitRequested; // +0x103c, CGame::update
    bool m_restartRequested; // +0x103d, CGame::update
    unsigned char m_gap103E[2];
    CMasterResourceManager* m_masterResources;
    int m_value1048;
    int m_value104C;
    Ogre::RenderWindow* m_renderWindow; // +0x1050
    Ogre::Root* m_root;
    CGenericModel* m_menuModel0; // +0x1060
    CGenericModel* m_menuModel1; // +0x1068
    CGenericModel* m_menuModel2; // +0x1070
    CGenericModel* m_menuModel3; // +0x1078
    CLayout* m_menuLayout; // +0x1080
    CSoundBank* m_menuSound; // +0x1088
    int m_gameSeed; // +0x1090
    int m_levelDepth; // +0x1094; not initialized by native C1
    std::wstring m_menuLevelName; // +0x1098
    int m_warpDelta; // +0x10a0
    int m_warpDepth;
    std::wstring m_warpDungeon;
    std::wstring m_warpName;
    bool m_warpPending; // +0x10b8
    bool m_warpWaypoint;
    bool m_warpFlag;
    bool m_interactionState; // +0x10bb, pause/control predicate
    bool m_bStateControl10BC;
    unsigned char m_gap10BD[3];
    Ogre::MaterialPtr m_shadowOpaque[64]; // +0x10c0
    Ogre::MaterialPtr m_shadowAlpha[64]; // +0x18c0
    Ogre::MaterialPtr m_shadowBlend3[64]; // +0x20c0
    Ogre::MaterialPtr m_shadowBlend2[64]; // +0x28c0
    Ogre::MaterialPtr m_shadowBlend1[64]; // +0x30c0
    float m_speedMult; // +0x38c0
    float m_lastInputElapsed; // +0x38c4
    Ogre::Light* m_ambientLight; // +0x38c8
    EGameState m_gameState;
    bool m_pendingPassClear;
    unsigned char m_gap38D5[3];
    CDungeon* m_currentDungeon; // +0x38d8
    Ogre::Vector3 m_cameraPosition;
    int m_startDifficulty; // +0x38ec
    std::string m_projectorTexture; // +0x38f0
    std::string m_projectorFalloffTexture; // +0x38f8
    CEquipment* m_retirementReward; // +0x3900
    int m_retirementLevel; // +0x3908
    int m_cameraState;
};
#endif
