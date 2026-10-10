#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <string>
#include <OgreRenderTargetListener.h>
#include <OgreRenderQueue.h>
#include <string>

#include "RunicCore.h"
#include "SafePointer.h"
class CItem;
class CQuestManager;
class CMasterResourceManager;
class CSoundManager;
namespace Ogre { class Light; class SceneNode; class Root; }
#include "QuestEventTypes.h"

class CBaseUnit;
class CCharacter;
class CPlayer;
class CGameUI;

// Partial: player and UI fields. Preserve all three base
// subobjects and the original 0x3910-byte allocation from GameClient.cpp.
class CGameClient : public CRunicCore, public Ogre::RenderTargetListener,
                    public Ogre::RenderQueue::RenderableListener
{
friend class CLevel;
public:
    void destroyGameUI();
    void updateScreenInfo(void* window, int width, int height);
    void handleFunctionKeys();
    void toggleLighting(bool enabled);
    void togglePlayerLight();
    std::wstring getPlayerClassName();
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
    void clearMouseClickUnits();
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
    unsigned char m_gap20[0x28];
    CSoundManager* m_soundManager;
    unsigned char m_gap50[0x8];
    CPlayer* m_pPlayer;
    unsigned char m_gap60[0x8];
    CQuestManager* m_questManager;
    unsigned char m_gap70[0x8];
    CGameUI* m_pGameUI;
    unsigned char m_gap80[0x8];
    void* m_window;
    int m_width;
    int m_height;
    bool m_inputConsumed;
    bool m_leftHeld;
    bool m_rightHeld;
    unsigned char m_gap9B[0x10d];
    std::wstring m_editorCreationClass;
    std::wstring m_editorCreationPet;
    unsigned char m_gap1B8[0x10];
    TSafePointer<CCharacter> m_selectedCharacter;
    TSafePointer<CCharacter> m_targetCharacter;
    TSafePointer<CItem> m_targetItem;
    TSafePointer<CItem> m_selectedItem;
    unsigned char m_gap208[0x18];
    Ogre::SceneNode* m_playerLightNode;
    unsigned char m_gap228[0x8];
    Ogre::Light* m_playerLight;
    unsigned char m_gap238[0xe08];
    CMasterResourceManager* m_masterResources;
    unsigned char m_gap1048[0x10];
    Ogre::Root* m_root;
    unsigned char m_gap1060[0x5c];
    bool m_bStateControl10BC;
    unsigned char m_gap10BD[0x2817];
    bool m_pendingPassClear;
    unsigned char m_gap38D5[0x3b];
};
#endif
