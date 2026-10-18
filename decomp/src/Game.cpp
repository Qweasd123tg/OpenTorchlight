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

int CGame::begin(void* editorWindow)
{
    m_editorWindow=editorWindow;
    bool runGame=getSettings()->m_pCmdLineParser->GetStringParam(L"COMPRESS",EMPTY_WSTRING)==EMPTY_WSTRING;
    bool createWindow=m_settings->m_pCmdLineParser->GetStringParam(L"NOWINDOW",EMPTY_WSTRING)==EMPTY_WSTRING;
    if (!setup(createWindow)) {
        if (gUseSplash) m_gSplash.Hide();
        return static_cast<int>(0x80004005u);
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
