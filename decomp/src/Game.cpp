#include "EmptyStrings.h"
#include "Game.h"
#include "CameraControl.h"
#include "GameClient.h"
#include "MasterResourceManager.h"
#include "Editor.h"
#include "GameUI.h"
#include "Level.h"
#include "Player.h"
#include "GameRuntimeGlobals.h"
#include <OgreRenderSystemCapabilities.h>
#include <OgreLogManager.h>

bool CGame::requestingRestart() { return m_requestRestart; }
void CGame::setupResources() {}
void CGame::createResourceListener() {}
void CGame::loadResources() {}
void CGame::windowResized(Ogre::RenderWindow*) {}

void CGame::destroyMasterResourceManager()
{
    if (m_masterResourceManager != NULL)
    {
        delete m_masterResourceManager;
        m_masterResourceManager = NULL;
    }
}

void CGame::destroyGameClient()
{
    if (m_gameClient != NULL)
    {
        delete m_gameClient;
        m_gameClient = NULL;
    }
}

Ogre::Camera* CGame::getGameCamera()
{
    return m_cameraControl ? m_cameraControl->m_pUnknown10 : NULL;
}

void CGame::editorUpdateSceneOnce(int)
{
    if (m_root) m_root->renderOneFrame();
}

void CGame::windowFocusChange(Ogre::RenderWindow* window)
{
    if (m_renderWindow == window) m_focused = m_renderWindow->isActive();
    if (m_gameClient) m_gameClient->setWindowActive(m_focused);
}

void CGame::createFrameListener()
{
    m_root->addFrameListener(this);
}

bool CGame::frameRenderingQueued(const Ogre::FrameEvent&)
{
    if (!m_renderWindow || m_renderWindow->isClosed()) return false;
    if (m_gameClient && m_gameClient->m_pendingPassClear)
        m_gameClient->clearSceneManagerPassMaps();
    return true;
}

void CGame::cleanUpGameObjects()
{
    if (m_masterResourceManager) m_masterResourceManager->destroyStash();
    destroyGameClient();
    destroyMasterResourceManager();
    if (m_sceneManager) m_sceneManager->clearScene();
    if (m_backgroundScene) m_backgroundScene->clearScene();
    if (m_uiScene) m_uiScene->clearScene();
    if (m_renderBehindScene) m_renderBehindScene->clearScene();
    if (m_renderBehindParticleScene) m_renderBehindParticleScene->clearScene();
    if (m_automapScene) m_automapScene->clearScene();
}

void CGame::shutdownForEditor()
{
    CEditor::getSingleton()->releaseResources();
    cleanUpGameObjects();
}




void CGame::createGameClient()
{
    m_gameClient = new CGameClient(*m_settings, m_masterResourceManager, m_renderWindow,
        m_root, m_cameraControl, m_sceneManager, m_uiScene, m_renderBehindScene, *m_soundManager);
    m_gameClient->create();
    if (m_gameClient) m_gameClient->updateScreenInfo(m_windowHandle,m_width,m_height);
    m_eventHandler.m_gameClient = m_gameClient;
}

void CGame::chooseSceneManager()
{
    Ogre::MovableObject::setDefaultVisibilityFlags(1);
    m_backgroundScene = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMBKInstance");
    m_sceneManager = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMInstance");
    m_sceneManager->setVisibilityMask(7);
    m_uiScene = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMUIInstance");
    m_uiScene->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
    m_renderBehindScene = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMRBInstance");
    m_renderBehindParticleScene = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMRBPInstance");
    m_automapScene = m_root->createSceneManager(Ogre::ST_INTERIOR,"SMAMInstance");
}

void CGame::checkCapabilities(Ogre::RenderSystem* renderer)
{
    const Ogre::RenderSystemCapabilities* caps = renderer->getCapabilities();
    if (caps)
    {
        std::set<std::string> profiles = caps->getSupportedShaderProfiles();
        m_settings->SetInt(KSETTINGS_ALLOW_HWSKINNING,0);
        if (!caps->hasCapability(Ogre::RSC_HWRENDER_TO_TEXTURE))
        {
            m_settings->SetInt(KSETTINGS_SHADOWS_ENABLED,0);
            m_settings->SetInt(KSETTINGS_LIGHTING_ENABLED,0);
        }
        if (!caps->hasCapability(Ogre::RSC_CUBEMAPPING))
            m_settings->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,0);
        if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM))
            m_settings->SetInt(KSETTINGS_ALLOW_HWSKINNING,0);
    }
}


bool CGame::setupForEditor(void* editorWindow, void* windowHandle)
{
    m_windowHandle = windowHandle;
    m_editorWindow = editorWindow;
    gEditor->removeFlag(EDITOR_FLAG_INGAME_MODE);
    bool result = setup(true);
    CEditor::getSingleton()->InitEditor(this,m_viewport);
    gEditor->getResourceManager()->getGameClients()->add(m_gameClient);
    return result;
}

void CGame::windowClosed(Ogre::RenderWindow*)
{
    if (m_gameClient && m_gameClient->m_gameState == static_cast<EGameState>(1) &&
        !m_gameClient->m_keyManager.keyHeld(0x10) &&
        m_gameClient->m_pPlayer->getEnabled() &&
        m_gameClient->m_cameraState != 1 &&
        m_gameClient->m_pPlayer->getAIState() != static_cast<EAIState>(31))
    {
        m_gameClient->killPets();
        m_gameClient->saveCharacter(false,true);
    }
}

#include "SteamStats.h"
#include "Achievements.h"
#include "SDL.h"

bool CGame::update(float elapsed, float time, bool flag)
{
    if (g_ResetFrames > 0) --g_ResetFrames;
    gfLastTimeElapsed = elapsed;
    m_renderBehind = m_settings->GetInt(KSETTINGS_RENDERBEHIND) != 0;
    if (!GResizing)
    {
        gLastWidth = m_settings->GetInt(KSETTINGS_RES_WIDTH);
        gLastHeight = m_settings->GetInt(KSETTINGS_RES_HEIGHT);
        gLastFullscreen = m_settings->GetInt(KSETTINGS_FULLSCREEN);
    }
    if (!m_gameClient) return true;
    if (elapsed > 0.0f)
    {
        m_frameTimeSum += elapsed;
        m_frameTimes.push_front(elapsed);
        if (m_frameTimes.size() >= m_frameTimeCount)
        {
            m_frameTimeSum -= m_frameTimes.back();
            m_frameTimes.pop_back();
        }
        m_settings->SetFloat(KSETTINGS_F_AVERAGE_FPS,
            1.0f / (m_frameTimeSum / static_cast<float>(m_frameTimes.size())));
    }
    if (!m_gameClient->processInput(m_windowHandle,elapsed,m_focused)) return false;
    m_gameClient->update(elapsed,m_renderWindow,time,flag);
    if (m_gameClient->m_restartRequested) { m_requestRestart = true; return false; }
    if (m_gameClient->m_quitRequested)
    {
        CSteamStats::getSingleton()->forceStatsToSave();
        return false;
    }
    m_disableRenderBehind = false;
    if ((SDL_GetWindowFlags(m_sdlWindow) & 0x240) != 0x200)
        m_disableRenderBehind = true;
    else
        m_disableRenderBehind = m_gameClient->m_pGameUI &&
            (m_gameClient->m_pGameUI->bothCovered() || m_gameClient->m_pGameUI->modalDialogOpenPartial());
    if (m_gameClient->m_pGameUI && m_gameClient->m_pGameUI->m_paused)
        m_disableRenderBehind = true;
    m_disableRendering = m_gameClient->m_pGameUI ? m_gameClient->m_pGameUI->getUIIsInCinematic() : false;
    if (CSteamStats::getSingleton() && CAchievements::getSingleton())
    {
        CSteamStats::getSingleton()->update(elapsed);
        CAchievements::getSingleton()->update(elapsed);
    }
    return true;
}

void CGame::postViewportUpdate(const Ogre::RenderTargetViewportEvent& event)
{
    if (event.source==m_viewport) {
        m_sceneManager->setVisibilityMask(7);
        if (m_gameClient && m_gameClient->m_level)
            m_gameClient->m_level->setLightStaticGeometryVisible(true);
        event.source->getCamera()->getSceneManager()->getRenderQueue()->setRenderableListener(NULL);
    }
}



bool CGame::frameStarted(const Ogre::FrameEvent& event)
{
    if (m_masterResourceManager && m_masterResourceManager->m_loadingResources) return true;
    static unsigned long g_LastTime=m_timer.getMilliseconds();
    if (!update(std::min(0.1f,event.timeSinceLastFrame),0.0f,true)) {
        if (m_gameClient && m_gameClient->m_pendingPassClear)
            m_gameClient->clearSceneManagerPassMaps();
        return false;
    }
    unsigned long current=m_timer.getMilliseconds();
    ++g_Frames;
    if (current-g_LastTime>1000) {
        float fps=static_cast<double>(m_settings->GetInt(KSETTINGS_NUM_TICKS_PER_SECOND))/(static_cast<double>(current-g_LastTime)/1000.0);
        g_LastTime=current;
        m_settings->SetInt(KSETTINGS_NUM_TICKS_PER_SECOND,g_Frames);
        m_settings->SetInt(KSETTINGS_CURRENT_FPS,static_cast<int>(fps));
        m_settings->SetInt(KSETTINGS_UPDATE_PERF,1);
        g_Frames=0;
    }
    if (m_gameClient && m_gameClient->m_pendingPassClear)
        m_gameClient->clearSceneManagerPassMaps();
    return true;
}

long CGame::WndProc(void*,unsigned int message,unsigned int key,long value)
{
    if (message==0x100 || message==0x101 || message==0x104 || message==0x102 || message==0x105)
        if (m_gameClient) m_gameClient->keyEvent(message,key,value);
    switch (message) {
    case 7:
    case 0x32:
        if (m_gameClient) m_gameClient->updateCursor();
        return 0;
    case 0x214:
        if (m_gameClient) m_gameClient->updateCursor();
        return 1;
    case 5:
        if ((key==0 || key==2 || key==3) && m_gameClient) m_gameClient->updateCursor();
        break;
    case 0x204: case 0x201: case 0x203: case 0x207: case 0x209:
    case 0x206: case 0x205: case 0x202: case 0x20a: case 0x208:
        if (m_gameClient) m_gameClient->mouseEvent(message,key);
        break;
    }
    return -1;
}

#include "StringUtilities.h"
#include "CmdLineParser.h"

void CGame::createViewports()
{
    if (!m_cameraControl || !m_renderWindow) return;
    Ogre::Viewport* main=m_renderWindow->addViewport(m_cameraControl->m_cameras[0],1);
    m_viewport=main;
    main->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
    main->setClearEveryFrame(false,3);
    Ogre::Viewport* ui=m_renderWindow->addViewport(m_cameraControl->m_cameras[1],5);
    ui->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
    ui->setClearEveryFrame(true,2);
    Ogre::Viewport* background=m_renderWindow->addViewport(m_cameraControl->m_cameras[2],0);
    background->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
    float height=static_cast<int>(background->getActualHeight());
    float width=static_cast<int>(background->getActualWidth());
    m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(0),width,height);
    m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(1),width,height);
    m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(2),width,height);
    Ogre::LogManager::getSingleton().logMessage("CreateViewports AspectRatio message - "+STRINGS::GetValueAsString(static_cast<float>(static_cast<int>(background->getActualWidth())))+" x "+STRINGS::GetValueAsString(static_cast<int>(background->getActualHeight())),Ogre::LML_CRITICAL);
    Ogre::LogManager::getSingleton().logMessage("CreateViewports AspectRatio message AR - "+STRINGS::GetValueAsString(static_cast<float>(static_cast<int>(background->getActualWidth()))/static_cast<float>(static_cast<int>(background->getActualHeight()))),Ogre::LML_CRITICAL);
}

void CGame::updateAspectRatio(float width,float height)
{
    Ogre::LogManager::getSingleton().logMessage("AspectRatio message - "+STRINGS::GetValueAsString(width)+" x "+STRINGS::GetValueAsString(height),Ogre::LML_CRITICAL);
    Ogre::LogManager::getSingleton().logMessage("stored res is - "+STRINGS::GetValueAsString(m_settings->GetInt(KSETTINGS_RES_WIDTH))+" x "+STRINGS::GetValueAsString(m_settings->GetInt(KSETTINGS_RES_HEIGHT)),Ogre::LML_CRITICAL);
    Ogre::LogManager::getSingleton().logMessage("AspectRatio message AR - "+STRINGS::GetValueAsString(width/height),Ogre::LML_CRITICAL);
    if (m_cameraControl) {
        m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(0),width,height);
        m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(1),width,height);
        m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(2),width,height);
    }
    if (m_gameClient) m_gameClient->updateScreenInfo(m_windowHandle,static_cast<int>(width),static_cast<int>(height));
}

bool CGame::configure(bool editor)
{
    if (getSettings()->m_pCmdLineParser->GetStringParam(L"COMPRESS",EMPTY_WSTRING)!=EMPTY_WSTRING) {
        gFirstRun=false;
        m_settings->SetInt(KSETTINGS_FULLSCREEN,0);
        m_settings->SetInt(KSETTINGS_RES_WIDTH,1024);
        m_settings->SetInt(KSETTINGS_RES_HEIGHT,768);
    }
    m_renderWindow=createWindow(editor);
    if (!m_renderWindow) {
        gFirstRun=false;
        gFailWidth=m_settings->GetInt(KSETTINGS_RES_WIDTH);
        gFailHeight=m_settings->GetInt(KSETTINGS_RES_HEIGHT);
        m_settings->SetInt(KSETTINGS_RES_WIDTH,1024);
        m_settings->SetInt(KSETTINGS_RES_HEIGHT,768);
        m_settings->SetInt(KSETTINGS_FSAA,0);
        m_renderWindow=createWindow(editor);
    }
    return true;
}

#include "SoundManager.h"
#include "Splash.h"
#include <CEGUISystem.h>

bool CGame::frameEnded(const Ogre::FrameEvent& event)
{
    if (m_masterResourceManager && m_masterResourceManager->m_loadingResources) return true;
    if (!m_settings->GetInt(KSETTINGS_FULLSCREEN) &&
        m_settings->GetInt(KSETTINGS_RES_WIDTH)==gLastWidth &&
        m_settings->GetInt(KSETTINGS_RES_HEIGHT)==gLastHeight &&
        m_settings->GetInt(KSETTINGS_FULLSCREEN)==gLastFullscreen) {
        int width,height;
        SDL_GetWindowSize(m_sdlWindow,&width,&height);
        int oldWidth=m_settings->GetInt(KSETTINGS_RES_WIDTH);
        int oldHeight=m_settings->GetInt(KSETTINGS_RES_HEIGHT);
        if ((width!=oldWidth || height!=oldHeight) && width>=512 && height>=384) {
            m_settings->SetInt(KSETTINGS_RES_WIDTH,width);
            m_settings->SetInt(KSETTINGS_RES_HEIGHT,height);
            gLastWidth=width;gLastHeight=height;
            GResizeWidth=width;GResizeHeight=height;GRecreateUI=true;
        }
    }
    if (gLastWidth!=0 && !m_gameClient->m_restartRequested) {
        if (m_settings->GetInt(KSETTINGS_RES_WIDTH)!=gLastWidth ||
            m_settings->GetInt(KSETTINGS_RES_HEIGHT)!=gLastHeight ||
            m_settings->GetInt(KSETTINGS_FULLSCREEN)!=gLastFullscreen) {
            GResizeWidth=m_settings->GetInt(KSETTINGS_RES_WIDTH);
            GResizeHeight=m_settings->GetInt(KSETTINGS_RES_HEIGHT);
            int width=GResizeWidth,height=GResizeHeight;
            m_settings->findClosestResolution(GResizeWidth,GResizeHeight,width,height);
            GResizeWidth=width;GResizeHeight=height;
            m_settings->GetInt(KSETTINGS_FULLSCREEN);
            m_width=GResizeWidth;m_height=GResizeHeight;
            m_settings->SetInt(KSETTINGS_RES_WIDTH,m_width);
            m_settings->SetInt(KSETTINGS_RES_HEIGHT,m_height);
            if (!m_settings->GetInt(KSETTINGS_FULLSCREEN)) {
                SDL_SetWindowGrab(m_sdlWindow,SDL_FALSE);
                SDL_SetWindowFullscreen(m_sdlWindow,0);
                SDL_SetWindowSize(m_sdlWindow,m_width,m_height);
            } else {
                SDL_SetWindowFullscreen(m_sdlWindow,0);
                SDL_SetWindowPosition(m_sdlWindow,0,0);
                SDL_SetWindowSize(m_sdlWindow,m_width,m_height);
                SDL_SetWindowFullscreen(m_sdlWindow,1);
                SDL_SetWindowGrab(m_sdlWindow,SDL_TRUE);
            }
            m_renderWindow->resize(m_width,m_height);
            m_renderWindow->windowMovedOrResized();
            float y=static_cast<float>(static_cast<unsigned>(m_height))/768.0f;
            float x=static_cast<float>(static_cast<unsigned>(m_width))*(1.0f/1024.0f);
            Ogre::LogManager::getSingleton().logMessage("Fullscreen Switch Setting YRatio - "+STRINGS::GetValueAsString(y),Ogre::LML_CRITICAL);
            m_settings->SetFloat(KSETTINGS_XRATIO,x);m_settings->SetFloat(KSETTINGS_YRATIO,y);
            float sound=m_settings->GetFloat(KSETTINGS_F_SOUNDVOLUME);
            float music=m_settings->GetFloat(KSETTINGS_F_MUSICVOLUME);
            bool soundMute=m_settings->GetInt(KSETTINGS_SOUNDMUTE)!=0;
            bool musicMute=m_settings->GetInt(KSETTINGS_MUSICMUTE)!=0;
            if (getSoundManager()) getSoundManager()->updateAudioLevels(sound,music,soundMute,musicMute);
            gLastWidth=m_settings->GetInt(KSETTINGS_RES_WIDTH);
            gLastHeight=m_settings->GetInt(KSETTINGS_RES_HEIGHT);
            gLastFullscreen=m_settings->GetInt(KSETTINGS_FULLSCREEN);
            GRecreateUI=true;
        } else if (GRecreateUI && m_gameClient) {
            m_width=GResizeWidth;m_height=GResizeHeight;
            if (!m_settings->GetInt(KSETTINGS_FULLSCREEN))
                SDL_GetWindowSize(m_sdlWindow,&m_width,&m_height);
            m_settings->SetInt(KSETTINGS_RES_WIDTH,m_width);
            m_settings->SetInt(KSETTINGS_RES_HEIGHT,m_height);
            if (m_gameClient) m_gameClient->updateScreenInfo(m_windowHandle,m_width,m_height);
            if (m_cameraControl) {
                float width=static_cast<float>(static_cast<unsigned>(m_width));
                float height=static_cast<float>(static_cast<unsigned>(m_height));
                m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(0),width,height);
                m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(1),width,height);
                m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(2),width,height);
            }
            float y=static_cast<float>(static_cast<unsigned>(m_height))/768.0f;
            float x=static_cast<float>(static_cast<unsigned>(m_width))*(1.0f/1024.0f);
            m_settings->SetFloat(KSETTINGS_XRATIO,x);m_settings->SetFloat(KSETTINGS_YRATIO,y);
            if (m_gameClient && m_gameClient->m_pGameUI) m_gameClient->m_pGameUI->setLoadingVisible(true);
            GRecreateUI=false;
            m_gameClient->rescaleUI();
            int width=m_width,height=m_height;
            if (CGameUI::getSingleton()) {
                int x,y;m_gSplash.findCenterForWindow(width,height,x,y);
                CEGUI::System::getSingleton().injectMousePosition(static_cast<float>(x),static_cast<float>(y));
                CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);
            }
            CMasterResourceManager::getSingleton()->m_loadingResources=false;
            if (gFailWidth) {
                m_settings->SetInt(KSETTINGS_RES_WIDTH,gFailWidth);
                m_settings->SetInt(KSETTINGS_RES_HEIGHT,gFailHeight);
                gFailWidth=0;gFailHeight=0;GResizing=true;
            }
        }
    }
    if (m_gameClient && m_soundManager) {
        Ogre::Vector3 position=m_gameClient->m_audioListenerPosition;
        m_soundManager->update(m_sceneManager->getRootSceneNode(),position,event.timeSinceLastFrame);
    }
    return true;
}

extern "C" void SDL_VideoQuit();

CGame::~CGame()
{
    if (m_settings) m_settings->SaveSettings(L"");
    if (m_renderWindow) {
        Ogre::WindowEventUtilities::removeWindowEventListener(m_renderWindow,this);
        windowClosed(m_renderWindow);
    }
    m_particleMaterial.setNull();
    m_behindMaterial.setNull();
    if (m_logManager) {delete m_logManager;m_logManager=NULL;}
    if (m_cameraControl) {delete m_cameraControl;m_cameraControl=NULL;}
    if (m_gameClient) {delete m_gameClient;m_gameClient=NULL;}
    if (m_soundManager) {delete m_soundManager;m_soundManager=NULL;}
    if (m_root) {delete m_root;m_root=NULL;}
    if (m_settings) {delete m_settings;m_settings=NULL;}
    SDL_VideoQuit();
}

#include "FileReader.h"
#include "FileUtilities.h"
#include <OgreUTFString.h>
#include <cstdlib>
#include <ctime>
#include <cstring>

CGame::CGame(std::string,CSettings* settings,bool firstRun)
    : m_cameraControl(NULL),m_root(NULL),m_backgroundScene(NULL),m_sceneManager(NULL),m_uiScene(NULL),
      m_renderBehindScene(NULL),m_renderBehindParticleScene(NULL),m_automapScene(NULL),m_viewport(NULL),m_renderWindow(NULL),
      m_pluginsFile(""),m_logManager(NULL),m_gameClient(NULL),m_windowHandle(NULL),m_editorWindow(NULL),m_settings(settings),m_soundManager(NULL),
      m_focused(true),m_disableRenderBehind(false),m_disableRendering(false),m_requestRestart(false),m_title(),m_masterResourceManager(NULL),
      m_renderParticles(false),m_frameTimeCount(60),m_frameTimeSum(0.0f),m_renderBehind(true),m_sdlWindow(NULL)
{
    setenv("SDL_VIDEO_X11_XINERAMA","0",0);
    if (SDL_VideoInit(NULL)<0) {
        std::string error="Could not initialize SDL Video: ";error+=SDL_GetError();
        MessageBoxA(NULL,error.c_str(),"Error on startup",0);
        std::exit(1);
    }
    PopulateSDLResolutions(m_settings);
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0,&mode);
    LinuxUtils::SaveDesktopResolution(mode.w,mode.h);
    std::atexit(SDL_Quit);
    m_timer.reset();
    gFirstRun=firstRun;
    if (firstRun || m_settings->m_pCmdLineParser->GetIntParam(L"SAFEMODE",0)==1) {
        m_settings->SetInt(KSETTINGS_FULLSCREEN,0);
        m_settings->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,0);
        m_settings->SetInt(KSETTINGS_ALLOW_HWSKINNING,0);
        if (!m_settings->SaveSettings(L"")) {
            std::string systemError=std::strerror(m_settings->m_lastFileError);
            std::wstring message=L"An error has occurred on startup. Settings were unable to save. It is recommend that you restart Torchlight.\n\nAttempted to save settings at:\n"+FILESYSTEM::GetAppDataPath();
            message=static_cast<std::wstring>(Ogre::UTFString(message)+Ogre::UTFString("\n\nWindows Error: ")+Ogre::UTFString(systemError));
            MessageBox(NULL,message.c_str(),L"Error on startup",0);
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow(message.c_str()),Ogre::LML_CRITICAL);
        }
    }
    if (gFirstRun) {
        m_settings->SetInt(KSETTINGS_FULLSCREEN,1);
        m_settings->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,1);
        m_settings->SetInt(KSETTINGS_ALLOW_HWSKINNING,1);
    }
    m_settings->SetString(KSETTINGS_S_VERSION,L"1");
    CFileReader reader;
    if (reader.ReadFile(FILESYSTEM::GetApplicationPath()+L"\\buildver.txt")) {
        std::wstring version=reader.ReadLine(0);
        if (version!=EMPTY_WSTRING) m_settings->SetString(KSETTINGS_S_VERSION,version);
    }
    m_settings->SetInt(KSETTINGS_NUM_TICKS_PER_SECOND,1);
    m_settings->SetInt(KSETTINGS_UPDATE_PERF,0);
    m_settings->SetInt(KSETTINGS_CURRENT_FPS,0);
    m_settings->SetInt(KSETTINGS_AI_FREEZE,0);
    m_settings->SetInt(KSETTINGS_PLAYER_UNTARGETABLE,0);
    m_settings->SetInt(KSETTINGS_DEBUG_LOGIC,0);
    if (m_settings->GetString(KSETTINGS_S_VERSION)==EMPTY_WSTRING || m_settings->GetInt(KSETTINGS_FULLSCREEN)) gUseSplash=false;
    std::srand(std::time(NULL));
}

struct SDLResolution
{
    int width,height;
    bool operator<(const SDLResolution& other)const
    {
        return width<other.width || (width==other.width && height<other.height);
    }
};

void PopulateSDLResolutions(CSettings* settings)
{
    std::set<SDLResolution> resolutions;
    int displays=SDL_GetNumVideoDisplays();
    for (int display=0;display<displays;++display) {
        int modes=SDL_GetNumDisplayModes(display);
        for (int index=0;index<modes;++index) {
            SDL_DisplayMode mode;
            if (SDL_GetDisplayMode(display,index,&mode)!=0) {
                MessageBoxA(NULL,SDL_GetError(),"Error Getting Display Modes",0);
                break;
            }
            int bits;Uint32 r,g,b,a;
            SDL_PixelFormatEnumToMasks(mode.format,&bits,&r,&g,&b,&a);
            if (bits>23 && mode.w>mode.h && mode.w<mode.h*2) {
                SDLResolution resolution={mode.w,mode.h};
                resolutions.insert(resolution);
            }
        }
    }
    for (std::set<SDLResolution>::reverse_iterator it=resolutions.rbegin();it!=resolutions.rend();++it)
        settings->addResolutionCombo(it->width,it->height,true,true,true);
}

long CGame::begin(void* editorWindow)
{
    m_editorWindow=editorWindow;
    bool runGame=getSettings()->m_pCmdLineParser->GetStringParam(L"COMPRESS",EMPTY_WSTRING)==EMPTY_WSTRING;
    bool createWindow=m_settings->m_pCmdLineParser->GetStringParam(L"NOWINDOW",EMPTY_WSTRING)==EMPTY_WSTRING;
    if (!setup(createWindow)) {
        if (gUseSplash) m_gSplash.Hide();
        return 0x80004005u;
    }
    if (!runGame) {
        convertAssetsToBinary();
        cleanUpGameObjects();
        return 0;
    }
    if (m_renderWindow) {
        m_renderWindow->setVisible(true);
        if (CGameUI::getSingleton()) {
            int x,y;m_gSplash.findCenterForWindow(m_width,m_height,x,y);
            CEGUI::System::getSingleton().injectMousePosition(static_cast<float>(x),static_cast<float>(y));
            CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);
        }
    }
    m_root->clearEventTimes();
    bool rendered,quit;
    do {
        quit=false;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==0x100) {quit=true;continue;}
            if (event.type==0x200) {
                if (event.window.event==4) {
                    m_renderWindow->reposition(event.window.data1,event.window.data2);
                    m_renderWindow->windowMovedOrResized();
                } else if (event.window.event==14) {
                    event.type=0x100;SDL_PushEvent(&event);
                }
            }
            m_eventHandler.ProcessEvent(event);
        }
        rendered=m_root->renderOneFrame();
    } while (rendered && !quit);
    cleanUpGameObjects();
    return 0;
}


void CGame::createCamera()
{
    if (m_cameraControl) { delete m_cameraControl; m_cameraControl = NULL; }
    Ogre::Camera* player = m_sceneManager->createCamera("PlayerCam");
    player->setFOVy(Ogre::Degree(35.0f));
    player->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f));
    player->lookAt(Ogre::Vector3(0.0f,0.0f,-300.0f));
    player->setNearClipDistance(1.0f);
    player->setAutoAspectRatio(true);
    player->setFarClipDistance(m_settings->GetInt(KSETTINGS_NETBOOK_MODE)==1 ? 45.0f : 90.0f);

    Ogre::Camera* ui = m_uiScene->createCamera("UICam");
    ui->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    ui->setFOVy(Ogre::Degree(35.0f));
    ui->setPosition(Ogre::Vector3(0.0f,0.0f,10.0f));
    ui->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f));
    ui->setNearClipDistance(0.1f);
    ui->setFarClipDistance(90.0f);
    ui->setAutoAspectRatio(true);

    Ogre::Camera* background = m_backgroundScene->createCamera("BKCam");
    background->setFOVy(Ogre::Degree(30.0f));
    background->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f));
    background->lookAt(Ogre::Vector3(0.0f,0.0f,-300.0f));
    background->setNearClipDistance(1.0f);
    background->setFarClipDistance(2.0f);
    background->setAutoAspectRatio(true);
    m_cameraControl = new CCameraControl(player,ui,background,NULL,NULL);
}

void CGame::preViewportUpdate(const Ogre::RenderTargetViewportEvent& event)
{
    if (event.source!=m_viewport) return;
    if (m_viewport && m_gameClient && m_gameClient->m_pGameUI &&
        (m_gameClient->m_pGameUI->bothCovered() || m_gameClient->m_pGameUI->rightCovered() || m_gameClient->m_pGameUI->leftCovered())) {
        unsigned width=m_settings->GetInt(KSETTINGS_RES_WIDTH);
        m_settings->GetInt(KSETTINGS_RES_HEIGHT);
        float right=m_gameClient && m_gameClient->m_pGameUI ? m_gameClient->m_pGameUI->rightScreenEdge() : -1.0f;
        float left=m_gameClient && m_gameClient->m_pGameUI ? m_gameClient->m_pGameUI->leftScreenEdge() : 0.0f;
        m_viewport->setDimensions(left/width,0.0f,right/width-left/width,1.0f);
    } else {
        m_viewport->setDimensions(0.0f,0.0f,1.0f,1.0f);
    }
    unsigned height=m_viewport->getActualHeight();
    unsigned width=m_viewport->getActualWidth();
    m_cameraControl->setAspectRatio(static_cast<ECAMERAS>(0),static_cast<float>(static_cast<int>(width)),static_cast<float>(static_cast<int>(height)));
    m_sceneManager->setVisibilityMask(5);
    if (m_gameClient && m_gameClient->m_level)
        m_gameClient->m_level->setLightStaticGeometryVisible(false);
    event.source->getCamera()->getSceneManager()->getRenderQueue()->setRenderableListener(this);
}


#include "Layout.h"
#include "DataGroup.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
void CGame::convertAssetsToBinary()
{
    if (!m_gameClient || !m_gameClient->m_gameResources)
        Ogre::LogManager::getSingleton().logMessage("Unable to convert raw assets to binary.",Ogre::LML_CRITICAL);
    Ogre::LogManager::getSingleton().logMessage("Starting to convert layouts to compressed binary",Ogre::LML_CRITICAL);
    TArrayList<std::wstring> files(10);
    std::wstring base=FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(),L"media/");
    FILESYSTEM::GetFileListRecursive(base,files,L"*.layout");
    for (unsigned i=0;i<files.size();++i) {
        std::wstring upper=STRINGS::StringUpper(files[i]);
        std::wstring::size_type ui=upper.find(L"/UI/");
        if (ui>0 && ui<upper.size()) continue;
        if (!FILESYSTEM::FileExists(upper+L".cmp")) {
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow((L"Compressing layout file: "+upper).c_str()),Ogre::LML_CRITICAL);
            CLayout* layout=new CLayout(m_gameClient->m_gameResources,static_cast<ELAYOUT_TYPES>(0));
            layout->loadLayoutFile(files[i],true,NULL,false,false,0);
            delete layout;
        }
    }
    files.clear();
    FILESYSTEM::GetFileListRecursive(base,files,L"*.dat");
    FILESYSTEM::GetFileListRecursive(base,files,L"*.hie");
    FILESYSTEM::GetFileListRecursive(base,files,L"*.animation");
    Ogre::LogManager::getSingleton().logMessage("Starting to convert dat and text files to binary",Ogre::LML_CRITICAL);
    for (unsigned i=0;i<files.size();++i) {
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow((L"Converting file to binary: "+files[i]).c_str()),Ogre::LML_CRITICAL);
        CDataGroup* group=new CDataGroup(EMPTY_WSTRING,NULL,20,10,NULL);
        group->LoadFile(files[i],NULL);
        delete group;
    }
    Ogre::LogManager::getSingleton().logMessage("Completed Compression of files.",Ogre::LML_CRITICAL);
}

#include "RenderableStates.h"
#include <OgreSubEntity.h>
#include <OgreRenderQueueSortingGrouping.h>
bool CGame::renderableQueued(Ogre::Renderable* renderable,unsigned char queueId,unsigned short priority,Ogre::Technique** technique,Ogre::RenderQueue* queue)
{
    if (static_cast<unsigned char>(queueId - 95) <= 4) return false;
    if (!renderable) return true;
    Ogre::SubEntity* sub = dynamic_cast<Ogre::SubEntity*>(renderable);
    if (!sub || sub->getUserAny().isEmpty()) return true;
    CRenderableStates* states = Ogre::any_cast<CRenderableStates*>(sub->getUserAny());
    if (!states || !*technique || !(*technique)->getNumPasses()) return true;
    (*technique)->getPass(0);
    if (m_renderParticles)
        queue->getQueueGroup(90)->addRenderable(renderable,m_particleMaterial->getTechnique(0),priority);
    if (!m_disableRenderBehind && !m_disableRendering && m_renderBehind && states->renderBehind && states->m_opacity > 0.0f && (!m_gameClient || m_gameClient->m_gameState != 0)) {
        Ogre::Technique* behind = states->highlighted ? states->material18->getTechnique(0) : *technique;
        queue->getQueueGroup(88)->addRenderable(renderable,behind,priority);
        if (states->m_state0) return false;
        *technique = (states->material20 ? states->material20 : m_behindMaterial.getPointer())->getTechnique(0);
    } else if (states->highlighted) {
        *technique = states->material18->getTechnique(0);
    }
    return true;
}

#include "FileSystem.h"
#include <OgreMaterialManager.h>

void CGame::createMaterials()
{
    Ogre::MaterialPtr wire = Ogre::MaterialManager::getSingleton().create("Wireframe", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    wire->setReceiveShadows(false);
    Ogre::Pass* pass = wire->getTechnique(0)->getPass(0);
    pass->setPolygonMode(Ogre::PM_WIREFRAME);
    pass->setSelfIllumination(1, 1, 1);
    pass->setDiffuse(Ogre::ColourValue(1, 1, 1, .1f));
    pass->setAmbient(Ogre::ColourValue(1, 1, 1, .1f));
    pass->setDepthWriteEnabled(false);
    wire->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    m_particleMaterial = Ogre::MaterialManager::getSingleton().create("WireframeOverlay", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    m_particleMaterial->setReceiveShadows(false);
    pass = m_particleMaterial->getTechnique(0)->getPass(0);
    pass->setPolygonMode(Ogre::PM_WIREFRAME);
    pass->setSelfIllumination(1, 1, 1);
    pass->setDiffuse(Ogre::ColourValue(1, 1, 1, .2f));
    pass->setAmbient(Ogre::ColourValue(1, 1, 1, .2f));
    pass->setDepthWriteEnabled(false);
    m_particleMaterial->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    m_particleMaterial->getTechnique(0)->setDepthFunction(Ogre::CMPF_LESS_EQUAL);
    m_particleMaterial->getTechnique(0)->setDepthWriteEnabled(false);

    Ogre::MaterialPtr trail = Ogre::MaterialManager::getSingleton().create("WeaponTrail", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    trail->setReceiveShadows(false);
    trail->setLightingEnabled(false);
    pass = trail->getTechnique(0)->getPass(0);
    pass->setDepthCheckEnabled(true);
    pass->setSelfIllumination(0, 0, 0);
    pass->setDepthWriteEnabled(false);
    trail->setSceneBlending(Ogre::SBT_ADD);
    trail->setCullingMode(Ogre::CULL_NONE);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/sharedTextures/weapontrail.dds", info, false, true, false);
    pass->createTextureUnitState(info.m_sResourceName);

    Ogre::MaterialPtr evil = Ogre::MaterialManager::getSingleton().create("WeaponTrailEvil", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    evil->setReceiveShadows(false);
    evil->setLightingEnabled(false);
    pass = evil->getTechnique(0)->getPass(0);
    pass->setDepthCheckEnabled(true);
    pass->setSelfIllumination(0, 0, 0);
    pass->setDepthWriteEnabled(false);
    evil->setSceneBlending(Ogre::SBT_ADD);
    evil->setCullingMode(Ogre::CULL_NONE);
    CFileSystem::getSingleton()->getFileInfo(L"media/sharedTextures/weapontrailevil.dds", info, false, true, false);
    pass->createTextureUnitState(info.m_sResourceName);

    Ogre::MaterialPtr arrow = Ogre::MaterialManager::getSingleton().create("ArrowTrail", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    arrow->setReceiveShadows(false);
    arrow->setLightingEnabled(false);
    pass = arrow->getTechnique(0)->getPass(0);
    pass->setDepthCheckEnabled(true);
    pass->setSelfIllumination(0, 0, 0);
    pass->setDepthWriteEnabled(false);
    pass->setFog(true, Ogre::FOG_NONE, Ogre::ColourValue::White, .001f, 0, 1);
    arrow->setSceneBlending(Ogre::SBT_ADD);
    arrow->setCullingMode(Ogre::CULL_NONE);
    CFileSystem::getSingleton()->getFileInfo(L"media/sharedTextures/arrowtrail.dds", info, false, true, false);
    pass->createTextureUnitState(info.m_sResourceName);

    Ogre::MaterialPtr reflected = Ogre::MaterialManager::getSingleton().create("ArrowTrailReflect", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    reflected->setReceiveShadows(false);
    reflected->setLightingEnabled(false);
    pass = reflected->getTechnique(0)->getPass(0);
    pass->setDepthCheckEnabled(true);
    pass->setSelfIllumination(1, 1, 1);
    pass->setAmbient(Ogre::ColourValue(1, 0, 0, 1));
    pass->setDiffuse(Ogre::ColourValue(1, 0, 0, 1));
    pass->setDepthWriteEnabled(false);
    pass->setFog(true, Ogre::FOG_NONE, Ogre::ColourValue::White, .001f, 0, 1);
    reflected->setSceneBlending(Ogre::SBT_ADD);
    reflected->setCullingMode(Ogre::CULL_NONE);
    CFileSystem::getSingleton()->getFileInfo(L"media/sharedTextures/arrowtrailreflect.dds", info, false, true, false);
    pass->createTextureUnitState(info.m_sResourceName);

    const char* names[] = { "lightBlue", "lightYellow", "lightOrange", "WireframeBlue", "WireframeYellow" };
    const Ogre::ColourValue illumination[] = {
        Ogre::ColourValue(0, 0, 1), Ogre::ColourValue(1, 1, 0), Ogre::ColourValue(1, .9f, 0),
        Ogre::ColourValue(0, 0, 1), Ogre::ColourValue(1, 1, 0)
    };
    Ogre::MaterialPtr colours[5];
    for (unsigned i = 0; i < 5; ++i) {
        colours[i] = Ogre::MaterialManager::getSingleton().create(names[i], Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        colours[i]->setReceiveShadows(false);
        pass = colours[i]->getTechnique(0)->getPass(0);
        pass->setDepthCheckEnabled(true);
        if (i >= 3) pass->setPolygonMode(Ogre::PM_WIREFRAME);
        pass->setSelfIllumination(illumination[i].r, illumination[i].g, illumination[i].b);
        Ogre::ColourValue colour = i == 4 ? Ogre::ColourValue(1, 1, .2f, .3f) : Ogre::ColourValue(.2f, .2f, 1, .3f);
        if (i == 4) {
            pass->setDiffuse(colour);
            pass->setAmbient(colour);
        } else {
            pass->setAmbient(colour);
            pass->setDiffuse(colour);
        }
        pass->setDepthWriteEnabled(false);
        colours[i]->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    }

    m_behindMaterial = Ogre::MaterialManager::getSingleton().create("RenderBehind", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    m_behindMaterial->setReceiveShadows(false);
    pass = m_behindMaterial->getTechnique(0)->getPass(0);
    pass->setSelfIllumination(.4f, .4f, .5f);
    pass->setAmbient(Ogre::ColourValue(0, 0, 0, 0));
    pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 0));
    pass->setDepthWriteEnabled(false);
    m_behindMaterial->getTechnique(0)->setDepthFunction(Ogre::CMPF_GREATER);
    m_behindMaterial->getTechnique(0)->setDepthWriteEnabled(false);
    pass->setSceneBlending(Ogre::SBF_ONE, Ogre::SBF_ZERO);
    pass->setMaxSimultaneousLights(0);
    m_behindMaterial->setSceneBlending(Ogre::SBT_TRANSPARENT_COLOUR);
    pass = m_behindMaterial->createTechnique()->createPass();
    pass->setSelfIllumination(.4f, .4f, .5f);
    pass->setAmbient(Ogre::ColourValue(0, 0, 0, 0));
    pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 0));
    pass->setDepthWriteEnabled(false);
    pass->setSceneBlending(Ogre::SBF_ONE, Ogre::SBF_ZERO);
    pass->setMaxSimultaneousLights(0);
    m_behindMaterial->compile();

    const char* shadows[] = { "RenderShadow", "RenderShadowSkinned", "RenderShadowSkinnedThree", "RenderShadowSkinnedTwo", "RenderShadowSkinnedOne" };
    for (unsigned i = 0; i < 64; ++i) {
        float intensity = .5f - static_cast<float>(i) * .0078125f;
        Ogre::MaterialPtr materials[5];
        for (unsigned j = 0; j < 5; ++j) {
            materials[j] = Ogre::MaterialManager::getSingleton().create(shadows[j] + STRINGS::GetValueAsString(i), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            materials[j]->setReceiveShadows(false);
            pass = materials[j]->getTechnique(0)->getPass(0);
            pass->setSelfIllumination(intensity, intensity, intensity);
            pass->setAmbient(Ogre::ColourValue(0, 0, 0, 1));
            pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 1));
            pass->setDepthWriteEnabled(false);
            pass->setDepthCheckEnabled(false);
            pass->setMaxSimultaneousLights(0);
            if (j) materials[j]->compile();
        }
    }
    Ogre::MaterialPtr points = Ogre::MaterialManager::getSingleton().create("Points", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    points->setReceiveShadows(false);
    pass = points->getTechnique(0)->getPass(0);
    pass->setPolygonMode(Ogre::PM_POINTS);
    pass->setSelfIllumination(1, 1, 1);
    Ogre::MaterialPtr fishing = Ogre::MaterialManager::getSingleton().create("FishingLine", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    fishing->setReceiveShadows(false);
    pass = fishing->getTechnique(0)->getPass(0);
    pass->setSelfIllumination(.6f, .6f, .6f);
    pass->setAmbient(Ogre::ColourValue(0, 0, 0, 1));
    pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 1));
    pass->setDepthWriteEnabled(true);
    pass->setDepthCheckEnabled(true);
    fishing->getTechnique(0)->setDepthWriteEnabled(true);
    fishing->setSceneBlending(Ogre::SBT_TRANSPARENT_COLOUR);
}

#include "Utilities.h"
#include <OgreDefaultHardwareBufferManager.h>
#include <OgreStringConverter.h>

extern "C" {
SDL_Window* SDL_CreateWindow(const char*,int,int,int,int,Uint32);
void SDL_DestroyWindow(SDL_Window*);
SDL_Surface* SDL_CreateRGBSurfaceFrom(void*,int,int,int,int,Uint32,Uint32,Uint32,Uint32);
void SDL_SetWindowIcon(SDL_Window*,SDL_Surface*);
}

// Public lodepng-bf09e0a.h file-decoder API; the library implementation is supplied separately.
enum LodePNGColorType { LCT_GREY=0, LCT_RGB=2, LCT_PALETTE=3, LCT_GREY_ALPHA=4, LCT_RGBA=6 };
namespace lodepng {
unsigned decode(std::vector<unsigned char>&, unsigned&, unsigned&, const std::string&, LodePNGColorType, unsigned);
}

Ogre::RenderWindow* CGame::createWindow(bool create)
{
    g_pGame=this;
    if (!m_root || getWindowHandle()) return NULL;
    static Ogre::RenderSystemList* pList=Ogre::Root::getSingleton().getAvailableRenderers();
    if (pList->empty()) {
        MessageBoxA(NULL,"Could not find a valid renderer","Initialization Error",0);
        return NULL;
    }
    Ogre::RenderSystem* renderer=(*pList)[0];
    std::string device;
    if (!m_settings->GetInt(KSETTINGS_OPENGL)) {
        Ogre::ConfigOption& option=renderer->getConfigOptions().find("Rendering Device")->second;
        option.currentValue=option.possibleValues[0];
        device=option.currentValue;
    }
    m_root->setRenderSystem(renderer);
    m_root->initialise(false,"Game");
    Ogre::NameValuePairList parameters;
    parameters["border"]="fixed";
    if (gFirstRun) {
        int speed=UTILITIES::getProcessorSpeed();
        int ram=UTILITIES::getAvailableRAM();
        m_settings->assignDefault(ram,speed,device);
    }
    int width=m_settings->GetInt(KSETTINGS_RES_WIDTH);
    int height=m_settings->GetInt(KSETTINGS_RES_HEIGHT);
    int desktopWidth,desktopHeight;
    LinuxUtils::GetDesktopResolution(desktopWidth,desktopHeight);
    if ((width>desktopWidth || height>desktopHeight) && m_settings->GetInt(KSETTINGS_FULLSCREEN)) return NULL;
    float yRatio=static_cast<float>(height)/768.0f;
    m_settings->SetFloat(KSETTINGS_XRATIO,static_cast<float>(width)*(1.0f/1024.0f));
    m_settings->SetFloat(KSETTINGS_YRATIO,yRatio);
    Ogre::LogManager::getSingleton().logMessage("Setting YRatio Init - "+STRINGS::GetValueAsString(yRatio),Ogre::LML_CRITICAL);
    bool fullscreen=m_settings->GetInt(KSETTINGS_FULLSCREEN)!=0;
    if (m_settings->GetInt(KSETTINGS_VSYNCH)) parameters["vsync"]="true";
    if (m_settings->GetInt(KSETTINGS_FSAA)) parameters["FSAA"]="2";
    if (m_settings->GetInt(KSETTINGS_OPENGL)) parameters["RTT Preferred Mode"]="FBO";
    if (gUseSplash) fullscreen=false;
    Ogre::RenderWindow* window=NULL;
    if (!create) {
        new Ogre::DefaultHardwareBufferManager;
        Ogre::MaterialManager::getSingleton().initialise();
    } else {
        SDL_Surface* icon=NULL;
        {
            std::vector<unsigned char> pixels;
            Ogre::UTFString filename("Torchlight.png");
            std::string path=STRINGS::StringConvertToUTF8(static_cast<std::wstring>(Ogre::UTFString(FILESYSTEM::GetApplicationPath())+filename));
            unsigned iconWidth,iconHeight;
            if (lodepng::decode(pixels,iconWidth,iconHeight,path,LCT_RGBA,8)==0) {
                icon=SDL_CreateRGBSurfaceFrom(&pixels[0],iconWidth,iconHeight,32,iconWidth*4,0xff,0xff00,0xff0000,0xff000000);
                if (!icon) MessageBoxA(NULL,SDL_GetError(),"Error loading icon",0);
            }
        }
        if (fullscreen) {
            m_width=width;m_height=height;
            m_settings->SetInt(KSETTINGS_RES_WIDTH,width);
            m_settings->SetInt(KSETTINGS_RES_HEIGHT,height);
            m_sdlWindow=SDL_CreateWindow("Torchlight",0,0,width,height,3);
            SDL_SetWindowIcon(m_sdlWindow,icon);
            SDL_SetWindowGrab(m_sdlWindow,SDL_TRUE);
            void* handle=LinuxUtils::GetSDLWindowHandle(m_sdlWindow);
            parameters["parentWindowHandle"]=Ogre::StringConverter::toString(reinterpret_cast<unsigned long>(handle));
            window=m_root->createRenderWindow("Torchlight",width,height,true,&parameters);
        } else {
            LinuxUtils::GetDesktopResolution(desktopWidth,desktopHeight);
            int windowWidth=std::min(width,desktopWidth),windowHeight=std::min(height,desktopHeight);
            m_sdlWindow=SDL_CreateWindow("Torchlight",0x2fff0000,0x2fff0000,windowWidth,windowHeight,gUseSplash?10:2);
            SDL_SetWindowIcon(m_sdlWindow,icon);
            void* handle=LinuxUtils::GetSDLWindowHandle(m_sdlWindow);
            parameters["parentWindowHandle"]=Ogre::StringConverter::toString(reinterpret_cast<unsigned long>(handle));
            window=m_root->createRenderWindow("Torchlight",windowWidth,windowHeight,false,&parameters);
        }
        window->setActive(true);
        window->setAutoUpdated(true);
        SDL_FreeSurface(icon);
        if (window) { unsigned long handle;window->getCustomAttribute("WINDOW",&handle); }
    }
    checkCapabilities(m_root->getRenderSystem());
    return window;
}

#include "FileUtilities.h"
#include "MissilePreloader.h"
#include "SteamStats.h"
#include <ParticleUniverseSystemManager.h>
#include <OgreException.h>
#include <OgreLog.h>
#include <algorithm>
#include <sstream>

int SetCurrentDirectory(std::wstring);

bool CGame::setup(bool create)
{
    if (create && gUseSplash) {
        m_gSplash.Init(m_editorWindow,0);
        m_gSplash.Show();
    }
    std::wstring localPath=FILESYSTEM::GetLocalPath();
    SetCurrentDirectory(localPath.c_str());
    std::string plugins=m_pluginsFile+"plugins.cfg";
    m_settings->SetInt(KSETTINGS_OPENGL,1);
    plugins=m_pluginsFile+"lib64/plugins_opengl.cfg";
    try {
        std::string appData=STRINGS::StringConvertToUTF8(FILESYSTEM::GetAppDataPath());
        m_root=new Ogre::Root(plugins,appData+"ogre.cfg",appData+"Ogre.log");
    } catch (Ogre::Exception error) {
        if (!m_settings->GetInt(KSETTINGS_FULLSCREEN))
            MessageBoxA(NULL,error.getFullDescription().c_str(),"Error in Root",0);
    }
    Ogre::LogManager::getSingleton().getDefaultLog()->setDebugOutputEnabled(false);
    Ogre::LogManager::getSingleton().getDefaultLog()->setLogDetail(Ogre::LL_LOW);
    std::wstring savePath=L"Path for saving is ... "+(FILESYSTEM::GetAppDataPath()+L"Save");
    std::string saveMessage=STRINGS::StringConvertToNarrow(savePath.c_str());
    Ogre::LogManager::getSingleton().logMessage(saveMessage,Ogre::LML_CRITICAL);
    setupResources();
    if (!configure(create) && create && !m_renderWindow) return false;
    if (m_renderWindow) {
        if (gUseSplash) m_gSplash.Show();
        m_renderWindow->setActive(false);
        m_width=m_renderWindow->getWidth();
        m_height=m_renderWindow->getHeight();
        m_windowHandle=reinterpret_cast<void*>(static_cast<unsigned long>(SDL_GetWindowID(m_sdlWindow)));
    }
    chooseSceneManager();
    createCamera();
    if (m_renderWindow) createViewports();
    m_viewport->setClearEveryFrame(true,3);
    m_root->renderOneFrame();
    m_viewport->setClearEveryFrame(false,3);
    m_masterResourceManager=new CMasterResourceManager(m_settings);
    CSteamStats::getSingleton()->m_game=this;
    m_soundManager=new CSoundManager(m_settings->GetInt(KSETTINGS_NO_SOUNDS)==0);
    m_soundManager->initialize(m_settings);
    m_soundManager->m_bUnknown6A9=false;
    int soundMute=m_settings->GetInt(KSETTINGS_SOUNDMUTE);
    int musicMute=m_settings->GetInt(KSETTINGS_MUSICMUTE);
    float soundVolume=m_settings->GetFloat(KSETTINGS_F_SOUNDVOLUME);
    float musicVolume=m_settings->GetFloat(KSETTINGS_F_MUSICVOLUME);
    m_soundManager->updateAudioLevels(soundVolume,musicVolume,soundMute!=0,musicMute!=0);
    m_masterResourceManager->m_renderTarget=m_renderWindow;
    m_masterResourceManager->m_pSoundManager=m_soundManager;
    m_masterResourceManager->m_pDefaultSceneManager=m_sceneManager;
    m_masterResourceManager->m_pSceneManager=m_renderBehindScene;
    m_masterResourceManager->m_renderBehindParticleScene=m_renderBehindParticleScene;
    m_masterResourceManager->m_automapScene=m_automapScene;
    m_masterResourceManager->m_pParticleSystemManager->setMaxNumberOfParticles(20000);
    m_masterResourceManager->m_pParticleSystemManager->m_particleFalloff=m_settings->GetFloat(KSETTINGS_F_PARTICLE_FALLOFF);
    ParticleUniverse::ParticleSystemManager::setParticleFPS(m_settings->GetFloat(KSETTINGS_F_PARTICLEFPS));
    float particlePercent=m_settings->GetFloat(KSETTINGS_F_PARTICLE_PCT);
    ParticleUniverse::ParticleSystemManager::setEmitterLoopingReleasePCT(std::max(0.f,std::min(100.f,particlePercent))/100.f);
    if (m_renderWindow && gUseSplash) m_gSplash.Show();
    m_masterResourceManager->loadParticles();
    m_masterResourceManager->m_missilePreloader->reloadMissiles();
    createResourceListener();
    loadResources();
    createMaterials();
    if (m_renderWindow) windowResized(m_renderWindow);
    createFrameListener();
    std::ostringstream windowText;
    unsigned long windowHandle=0;
    if (m_renderWindow) {
        m_renderWindow->getCustomAttribute("WINDOW",&windowHandle);
        windowText<<windowHandle;
        Ogre::WindowEventUtilities::addWindowEventListener(m_renderWindow,this);
        m_renderWindow->addListener(this);
        m_renderWindow->setActive(true);
        if (m_renderWindow && gUseSplash) {
            int desktopWidth,desktopHeight,windowWidth,windowHeight;
            LinuxUtils::GetDesktopResolution(desktopWidth,desktopHeight);
            SDL_GetWindowSize(m_sdlWindow,&windowWidth,&windowHeight);
            SDL_SetWindowPosition(m_sdlWindow,(desktopWidth-windowWidth)/2,(desktopHeight-windowHeight)/2);
            SDL_ShowWindow(m_sdlWindow);
            m_gSplash.Hide();
        }
    }
    m_soundManager->m_bUnknown6A9=true;
    createGameClient();
    return true;
}
