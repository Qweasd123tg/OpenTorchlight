#ifndef GAME_H
#define GAME_H

// Original bases, virtual order, and member offsets established by CGame construction and callers.

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OgreRenderQueue.h>
#include <OgreRenderSystem.h>
#include <OgreRenderTargetListener.h>
#include <OgreRenderWindow.h>
#include <OgreRenderable.h>
#include <OgreTechnique.h>
#include <OgreWindowEventUtilities.h>
#include <string>
#include "RunicCore.h"
#include "Settings.h"
#include "iEditorResourceManager.h"
#include "OgreGpuCommandBufferFlush.h"
#include "SDLEventHandler.h"
#include <OgreMaterial.h>
#include <OgreTimer.h>
#include <list>
class CCameraControl; class CMasterResourceManager; struct SDL_Window;

class CGame : public CRunicCore, public Ogre::WindowEventUtilities, public Ogre::FrameListener, public Ogre::WindowEventListener, public iEditorResourceManager, public Ogre::RenderQueue::RenderableListener, public Ogre::RenderTargetListener
{
public:
    virtual ~CGame();
    virtual void* getWindowHandle();
    virtual CSettings* getSettings();
    virtual Ogre::SceneManager* getSceneManager();
    virtual Ogre::RenderWindow* getRenderWindow();
    virtual CSoundManager* getSoundManager();
    virtual Ogre::Camera* getGameCamera();
    virtual CGameClient* getGameClient();
    virtual void updateAspectRatio(float, float);
    virtual long begin(void*);
    virtual void editorUpdateSceneOnce(int);
    virtual bool setup(bool);
    virtual bool configure(bool);
    virtual void chooseSceneManager();
    virtual void createCamera();
    virtual void createFrameListener();
    virtual void createGameClient();
    virtual void destroyGameClient();
    virtual void createViewports();
    virtual void setupResources();
    virtual void createResourceListener();
    virtual void loadResources();
    virtual void windowResized(Ogre::RenderWindow*);
    virtual void windowClosed(Ogre::RenderWindow*);
    virtual void windowFocusChange(Ogre::RenderWindow*);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
    virtual bool frameStarted(const Ogre::FrameEvent&);
    virtual bool frameEnded(const Ogre::FrameEvent&);
    virtual void preViewportUpdate(const Ogre::RenderTargetViewportEvent&);
    virtual void postViewportUpdate(const Ogre::RenderTargetViewportEvent&);
    virtual bool renderableQueued(Ogre::Renderable*, unsigned char, unsigned short, Ogre::Technique**, Ogre::RenderQueue*);
    bool requestingRestart();
    void destroyMasterResourceManager();
    bool setupForEditor(void*, void*);
    bool update(float, float, bool);
    long WndProc(void*, unsigned int, unsigned int, long);
    void cleanUpGameObjects();
    void shutdownForEditor();
    void checkCapabilities(Ogre::RenderSystem*);
    void convertAssetsToBinary();
    void createMaterials();
    Ogre::RenderWindow* createWindow(bool);
    CGame(std::string, CSettings*, bool);

    CCameraControl* m_cameraControl;             // 0x38
    Ogre::Root* m_root;                         // 0x40
    Ogre::SceneManager* m_backgroundScene;      // 0x48
    Ogre::SceneManager* m_sceneManager;         // 0x50
    Ogre::SceneManager* m_uiScene;              // 0x58
    Ogre::SceneManager* m_renderBehindScene;    // 0x60
    Ogre::SceneManager* m_renderBehindParticleScene; // 0x68
    Ogre::SceneManager* m_automapScene;         // 0x70
    Ogre::Viewport* m_viewport;                // 0x78
    Ogre::RenderWindow* m_renderWindow;        // 0x80
    std::string m_pluginsFile;                 // 0x88
    Ogre::LogManager* m_logManager;            // 0x90
    CGameClient* m_gameClient;                 // 0x98
    void* m_windowHandle;                      // 0xa0
    void* m_editorWindow;                      // 0xa8
    int m_width;                              // 0xb0
    int m_height;                             // 0xb4
    CSettings* m_settings;                     // 0xb8
    CSoundManager* m_soundManager;             // 0xc0
    bool m_focused;                           // 0xc8
    bool m_disableRenderBehind;               // 0xc9
    bool m_disableRendering;                  // 0xca
    bool m_requestRestart;                    // 0xcb
    unsigned char m_gapCC[4];
    std::wstring m_title;                     // 0xd0
    unsigned char m_unrecoveredD8[0x100];
    CMasterResourceManager* m_masterResourceManager; // 0x1d8
    Ogre::Timer m_timer;                      // 0x1e0
    Ogre::MaterialPtr m_behindMaterial;        // 0x1f8
    Ogre::MaterialPtr m_particleMaterial;      // 0x218
    bool m_renderParticles;                   // 0x238
    unsigned char m_gap239[7];
    std::list<float> m_frameTimes;             // 0x240
    unsigned int m_frameTimeCount;            // 0x250
    float m_frameTimeSum;                       // 0x254
    bool m_renderBehind;                      // 0x258
    unsigned char m_gap259[7];
    Ogre::GpuCommandBufferFlush m_gpuFlush;    // 0x260
    SDL_Window* m_sdlWindow;                   // 0x2a0
    SDLEventHandler m_eventHandler;            // 0x2a8
};

void PopulateSDLResolutions(CSettings*);

#endif
