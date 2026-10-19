#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include "Editor.h"
#include "EditorDLL.h"
#include "EditorObjectManager.h"
#include "GameClient.h"
#include "POV.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "Undo.h"
#include "iEditorResourceManager.h"

void CEditor::SetMouseWheelDelta(int delta)
{
    m_iMouseWheelDelta = delta;
}

void CEditor::SetPovVelocityMult(float multiplier)
{
    if (m_pCameraController) m_pCameraController->m_fUnknown144 = multiplier;
}

void CEditor::SetRenderWindowHasFocus(bool focused)
{
    if (m_pCameraController) m_pCameraController->m_bUnknown178 = focused;
    m_bRenderWindowHasFocus = focused;
}

CEditorScene* CEditor::GetEditorScene(unsigned int index)
{
    if (index < m_EditorScenes.size()) return m_EditorScenes[index];
    return NULL;
}

unsigned int CEditor::getUndoSize()
{
    return m_Undos.size();
}

void CEditor::doUndo()
{
    if (m_Undos.size() > 0) {
        CUndo* undo = m_Undos.back();
        m_Undos.pop_back();
        undo->DoAsUndo();
        delete undo;
    }
}

unsigned int CEditor::getRedoSize()
{
    return m_Redos.size();
}

void CEditor::doRedo()
{
    if (m_Redos.size() > 0) {
        CUndo* undo = m_Redos.back();
        m_Redos.pop_back();
        undo->DoAsRedo();
        delete undo;
    }
}

void CEditor::deleteAllUndos()
{
    for (std::list<CUndo*>::iterator it = m_Redos.begin(); it != m_Redos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
    for (std::list<CUndo*>::iterator it = m_Undos.begin(); it != m_Undos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
}

void CEditor::FlyToPositionLookingAtPos(Ogre::Vector3 position, Ogre::Vector3 target)
{
    if (m_pCameraController) m_pCameraController->FlyTo(position, target);
}

void CEditor::keyEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->keyEvent(event, code);
}

void CEditor::mouseEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->mouseEvent(event, code);
}

CGameClient* CEditor::getGameClient()
{
    return m_pEditorResourceManager->getGameClient();
}

void CEditor::SetBackgroundColor(float red,float green,float blue)
{
    if (m_pEditorResourceManager) {
        Ogre::Viewport* viewport = m_pEditorResourceManager->getRenderWindow()->getViewport(0);
        if (viewport) viewport->setBackgroundColour(Ogre::ColourValue(red, green, blue));
    }
}

void CEditor::flushKeyManager()
{
    if (getGameClient()) getGameClient()->getKeyManager()->flushAll();
    if (m_pObjectManager) m_pObjectManager->flushKeyManager();
}

CEditorScene* CEditor::GetEditorScene(std::wstring name)
{
    return GetEditorScene(GetEditorSceneIDByName(name.c_str()));
}

Ogre::Camera* CEditor::getCamera()
{
    if (!m_pEditorResourceManager) return NULL;
    if (!m_pUnknown88 || !(m_iFlags & (1 << EDITOR_FLAG_INGAME_MODE))) return m_pUnknown88;
    return m_pEditorResourceManager->getGameCamera();
}

void CEditor::setDirectionalColor(int red, int green, int blue)
{
    m_pSettings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_RED, red);
    m_pSettings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_GREEN, green);
    m_pSettings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_BLUE, blue);
    TArrayList<CGameClient*>* clients = m_pUnknown128->getGameClients();
    if (clients && clients->size()) (*clients)[0]->refreshLighting();
}

void CEditor::setMaterialAmbientColor(int red, int green, int blue)
{
    m_pSettings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED, red);
    m_pSettings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN, green);
    m_pSettings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE, blue);
    TArrayList<CGameClient*>* clients = m_pUnknown128->getGameClients();
    if (clients && clients->size()) (*clients)[0]->refreshLighting();
}

void CEditor::setAmbientColor(int red, int green, int blue)
{
    m_pSettings->SetInt(KSETTINGS_AMBIENT_LIGHT_RED, red);
    m_pSettings->SetInt(KSETTINGS_AMBIENT_LIGHT_GREEN, green);
    m_pSettings->SetInt(KSETTINGS_AMBIENT_LIGHT_BLUE, blue);
    TArrayList<CGameClient*>* clients = m_pUnknown128->getGameClients();
    if (clients && clients->size()) (*clients)[0]->refreshLighting();
}

void CEditor::setDirectionalIntensity(float intensity)
{
    m_pSettings->SetFloat(KSETTINGS_F_DIRECTIONAL_INTENSITY, intensity);
    TArrayList<CGameClient*>* clients = m_pUnknown128->getGameClients();
    if (clients && clients->size()) (*clients)[0]->refreshLighting();
}

void CEditor::addUndo(CUndo* undo, bool clearRedo)
{
    if (clearRedo) {
        for (std::list<CUndo*>::iterator i = m_Redos.begin(); i != m_Redos.end(); ++i) {
            if (*i) { delete *i; *i = NULL; }
        }
    }
    m_Undos.push_back(undo);
    while (!m_Undos.empty() && m_Undos.size() > m_iMaxUndos) {
        CUndo*& oldest = m_Undos.front();
        if (oldest) { delete oldest; oldest = NULL; }
        m_Undos.pop_front();
    }
}

void CEditor::addRedo(CUndo* redo)
{
    m_Redos.push_back(redo);
    while (!m_Redos.empty() && m_Redos.size() > m_iMaxUndos) {
        CUndo*& oldest = m_Redos.front();
        if (oldest) { delete oldest; oldest = NULL; }
        m_Redos.pop_front();
    }
}

CEditor* CEditor::getSingleton()
{
    if (gEditor) return gEditor;
    CEditor* editor = new CEditor;
    if (gEditor != editor) {
        if (gEditor) delete gEditor;
        gEditor = editor;
    }
    return editor;
}

unsigned int CEditor::GetEditorSceneIDByName(const wchar_t* name)
{
    if (!name) return ~0u;
    std::map<std::wstring, unsigned int>::iterator it = m_EditorSceneIDs.find(std::wstring(name));
    return it == m_EditorSceneIDs.end() ? ~0u : it->second;
}

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <queue>
#include <SDL.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreUTFString.h>
#include <ParticleUniverseSystemManager.h>
#include "EmptyStrings.h"
#include "DataGroup.h"
#include "EditorScene.h"
#include "FileUtilities.h"
#include "GameUI.h"
#include "LayoutScene.h"
#include "LinuxUtils.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "ModelViewerScene.h"
#include "MouseHandler.h"
#include "OgreUtilities.h"
#include "ParticleScene.h"
#include "ParticleTechWrapper.h"
#include "Quest.h"
#include "QuestManager.h"
#include "RoomPiece.h"
#include "StringUtilities.h"
#include "Utilities.h"

CEditor::CEditor()
    : m_bRenderWindowHasFocus(true), m_bDisabled(false), m_bUnknown4A(false),
      m_bUnknown4B(false), m_pSettings(NULL), m_pEditorResourceManager(NULL),
      m_fUnknown60(1.0f), m_iFlags(0), m_iUnknown68(0x3a),
      m_pCameraController(NULL), m_pUnknown88(NULL), m_pUnknown90(NULL),
      m_pUnknownB0(NULL), m_iMouseWheelDelta(0), m_EditorScenes(1),
      m_pObjectManager(NULL), m_pUnknown128(NULL), m_pUnknown130(NULL),
      m_pUnknown138(NULL), m_iMaxUndos(100), m_bUnknown164(false),
      m_pUnknown168(NULL), m_iCharacterLevel(1), m_iLevelDepth(0),
      m_bLevelPopulate(true), m_sUnknown180(EMPTY_WSTRING),
      m_bLevelPopulateChampions(true), m_bLevelCreatePet(true),
      m_bRunGodded(false), m_bAiFreeze(false), m_sUnknown190(EMPTY_WSTRING),
      m_sUnknown198(EMPTY_WSTRING), m_sUnknown1A0(EMPTY_WSTRING),
      m_bUseTempStartPos(false), m_vTempStartPos(0.0f,0.0f,0.0f),
      m_fParticleMovementA(5.0f), m_fParticleMovementB(10.0f),
      m_ActiveQuests(10), m_CompletedQuests(10)
{
    for (unsigned i=0; i<3; ++i) m_iUnknown78[i]=0.0f;
    for (unsigned i=0; i<6; ++i) m_iUnknown98[i]=0.0f;
    m_Timer.reset();
    std::srand(static_cast<unsigned>(std::time(NULL)));
    setFlag(EDITOR_FLAG_INGAME_MODE);
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/Torchlight/Torched/DataEditor/EditorFolder");
    std::wstring temporary=FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetAppDataPath(),L"Torched/DataEditor/EditorFolder/temp.layout");
    copyFileTo(FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(),L"/DataEditor/default.layout"),temporary);
    copyFileTo(FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(),L"/DataEditor/default.layout.cmp"),temporary+L".cmp");
}

CEditor::~CEditor()
{
    releaseResources();
    m_pEditorResourceManager=NULL;
}

void copyFileTo(const std::wstring& from,const std::wstring& to)
{
    Ogre::UTFString sourceName(from),destinationName(to);
    std::fstream source(sourceName.asUTF8_c_str(),std::ios::in|std::ios::binary);
    source.unsetf(std::ios::skipws);
    std::istream_iterator<char> begin(source),end;
    std::fstream destination(destinationName.asUTF8_c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
    std::copy(begin,end,std::ostream_iterator<char>(destination));
}

void CEditor::setCompletedQuests(const std::wstring& text)
{
    std::queue<std::wstring> quests;
    STRINGS::TokenizeString(&quests,text,L",");
    if (quests.empty()) quests.push(text);
    m_CompletedQuests.clear();
    while (!quests.empty()) {
        std::wstring name=quests.front();
        if (name!=EMPTY_WSTRING) m_CompletedQuests.add(name);
        quests.pop();
    }
}

void CEditor::setActiveQuests(const std::wstring& text)
{
    std::queue<std::wstring> quests;
    STRINGS::TokenizeString(&quests,text,L",");
    if (quests.empty()) quests.push(text);
    m_ActiveQuests.clear();
    while (!quests.empty()) {
        std::wstring name=quests.front();
        if (name!=EMPTY_WSTRING) m_ActiveQuests.add(name);
        quests.pop();
    }
}

void CEditor::releaseResources()
{
    deleteAllUndos();
    if (m_pUnknown130) {
        m_pUnknown130->removeAndDestroyAllChildren();
        OGRE_UTILITIES::removeChildFromParentNode(m_pUnknown130);
        m_pUnknown138=NULL;
        m_pUnknown130=NULL;
    }
    if (m_pUnknownB0) { delete m_pUnknownB0; m_pUnknownB0=NULL; }
    if (m_pCameraController) { delete m_pCameraController; m_pCameraController=NULL; }
    if (m_pObjectManager) { delete m_pObjectManager; m_pObjectManager=NULL; }
    m_EditorScenes.deleteAll();
    m_EditorSceneIDs.clear();
    if (m_pUnknown168) { delete m_pUnknown168; m_pUnknown168=NULL; }
    if (m_pUnknown128) { delete m_pUnknown128; m_pUnknown128=NULL; }
    m_iFlags=0;
}

void CEditor::reinitScene()
{
    if (m_pUnknown168) { delete m_pUnknown168; m_pUnknown168=NULL; }
    CSettings* settings=m_pEditorResourceManager->getSettings();
    CGameClient* client=m_pEditorResourceManager->getGameClient();
    Ogre::SceneManager* scene=m_pEditorResourceManager->getSceneManager();
    CSoundManager* sound=m_pEditorResourceManager->getSoundManager();
    m_pUnknown168=new CLevel(L"EDITOR",settings,client,m_pUnknown128,scene,sound,0,0);
    m_pUnknown128->m_pLevel=m_pUnknown168;
}

void CEditor::recreateScene(unsigned int index)
{
    if (index<m_EditorScenes.size() && m_EditorScenes[index]) {
        delete m_EditorScenes[index];
        m_EditorScenes[index]=NULL;
    }
    CEditorScene* scene;
    std::wstring name;
    unsigned int flags;
    if (index==0) { name=L"Mesh Viewer"; scene=new CModelViewerScene; flags=1; }
    else if (index==1) { name=L"Particle Creator"; scene=new CParticleScene; flags=2; }
    else if (index==2) { name=L"Layout"; scene=new CLayoutScene; flags=0; }
    else return;
    m_EditorSceneIDs[name]=m_EditorScenes.size();
    while (m_EditorScenes.size()<=index) m_EditorScenes.add(NULL);
    m_EditorScenes[index]=scene;
    scene->SetName(name);
    scene->InitScene(m_pUnknown128,flags);
}

bool CEditor::EditorDumpDescriptionOfObjectsToFile(const std::wstring& file)
{
    CDataGroup description(L"EDITOR OBJECT DESCRIPTIONS",NULL,20,10,NULL);
    CDataGroup* flags=description.AddDataGroup(L"EDITOR FLAGS");
    for (unsigned i=0;i<17;++i) {
        CDataGroup* flag=flags->AddDataGroup(L"FLAG");
        flag->AddDataValue(L"FLAG NAME",gEDITOR_FLAG_NAMES[i],false);
        flag->AddDataValue(L"FLAG ID",i);
    }
    CDataGroup* events=description.AddDataGroup(L"EDITOR EVENTS");
    for (unsigned i=0;i<14;++i) {
        CDataGroup* event=events->AddDataGroup(L"EVENT");
        event->AddDataValue(L"EVENT NAME",gEDITOR_EVENT_NAMES[i],false);
        event->AddDataValue(L"EVENT ID",i);
    }
    CDataGroup* masks=description.AddDataGroup(L"EDITOR UPDATE MASKS");
    for (unsigned i=0;i<4;++i) {
        CDataGroup* mask=masks->AddDataGroup(L"UPDATEMASK");
        mask->AddDataValue(L"MASK NAME",gEDITOR_UPDATE_MASKS[i],false);
        mask->AddDataValue(L"MASK",static_cast<int>(1u<<i));
    }
    for (unsigned i=0;i<m_EditorScenes.size();++i)
        m_EditorScenes[i]->SaveDescriptionOfSceneAndDescriptors(&description,i);
    description.SaveToFile(std::wstring(file.c_str()));
    return true;
}

void CEditor::UpdatePlayerInput(float elapsed)
{
    if (!m_pEditorResourceManager) return;
    if (!m_bRenderWindowHasFocus) {
        m_pCameraController->m_bUnknown14C=false;
        m_pCameraController->m_bUnknown14D=false;
        m_pCameraController->m_bUnknown14A=false;
        m_pCameraController->m_bUnknown14B=false;
        m_pCameraController->m_bUnknown148=false;
        m_pCameraController->m_bUnknown149=false;
        m_pCameraController->DeactivateMouse();
        return;
    }
    if (!m_pCameraController) return;
    m_pCameraController->UpdateMouseInput(m_pEditorResourceManager->getWindowHandle(),elapsed);
    if (m_iMouseWheelDelta>0) {
        m_pCameraController->m_fUnknownE0=m_pCameraController->m_viewAxis128+m_pCameraController->m_viewAxis128+m_pCameraController->m_fUnknownE0;
        m_pCameraController->m_fUnknownDC=m_pCameraController->m_fUnknown124+m_pCameraController->m_fUnknown124+m_pCameraController->m_fUnknownDC;
        m_pCameraController->m_fUnknownD8=m_pCameraController->m_viewAxis120+m_pCameraController->m_viewAxis120+m_pCameraController->m_fUnknownD8;
    } else if (m_iMouseWheelDelta<0) {
        m_pCameraController->m_fUnknownE0=m_pCameraController->m_viewAxis128*-2.0f+m_pCameraController->m_fUnknownE0;
        m_pCameraController->m_fUnknownDC=m_pCameraController->m_fUnknown124*-2.0f+m_pCameraController->m_fUnknownDC;
        m_pCameraController->m_fUnknownD8=m_pCameraController->m_viewAxis120*-2.0f+m_pCameraController->m_fUnknownD8;
    }
    m_iMouseWheelDelta=0;
    m_pCameraController->m_bUnknown148=GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[3]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[9]))<0;
    m_pCameraController->m_bUnknown149=GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[2]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[8]))<0;
    m_pCameraController->m_bUnknown14A=GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[4]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[10]))<0;
    m_pCameraController->m_bUnknown14B=GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[5]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[11]))<0;
    m_pCameraController->m_bUnknown14D=GetAsyncKeyState(0x22)<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[1]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[7]))<0;
    m_pCameraController->m_bUnknown14C=GetAsyncKeyState(0x21)<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[0]))<0 || GetAsyncKeyState(m_pSettings->GetInt(m_keyPropertyIndices[6]))<0;
}

void CEditor::updateParticleSystems(float elapsed,float height)
{
    static float fUpdateParticleTime=0.0f;
    fUpdateParticleTime+=elapsed;
    while (fUpdateParticleTime>=m_fParticleMovementA) fUpdateParticleTime-=m_fParticleMovementA;
    float angle=static_cast<float>(static_cast<double>((fUpdateParticleTime/m_fParticleMovementA)*360.0f)*0.01745329252);
    float x=std::cos(angle)*m_fParticleMovementB;
    float z=std::sin(angle)*m_fParticleMovementB;
    std::map<std::wstring,unsigned>::iterator found=m_EditorSceneIDs.find(L"Particle Creator");
    if (found==m_EditorSceneIDs.end()) return;
    CEditorScene* scene=m_EditorScenes[found->second];
    if (!scene) return;
    TArrayList<CEditorBaseObject*>* objects=scene->GetObjectsCreatedByADescriptor(L"Particle");
    if (!objects) return;
    for (unsigned i=0;i<objects->size();++i) {
        if (!(*objects)[i]) continue;
        CParticleTechWrapper* particle=dynamic_cast<CParticleTechWrapper*>((*objects)[i]);
        if (!particle) continue;
        particle->setPosition(x,height,z);
        if (height!=0.0f || x!=0.0f || z!=0.0f) {
            Ogre::Vector3 position=particle->getPosition(false);
            position.normalise();
            Ogre::Vector3 forward=position.crossProduct(Ogre::Vector3::UNIT_Y);
            Ogre::Quaternion orientation;
            orientation.FromAxes(position,Ogre::Vector3::UNIT_Y,forward);
            Ogre::Matrix3 rotation;
            orientation.ToRotationMatrix(rotation);
            Ogre::Matrix4 matrix=Ogre::Matrix4::IDENTITY;
            matrix=rotation;
            particle->setOrientation(matrix,false);
        } else particle->setOrientation(Ogre::Quaternion::IDENTITY);
    }
}

void CEditor::ResetCamera(Ogre::Vector3 position)
{
    static bool bResettingCamera=false;
    if (bResettingCamera) return;
    bResettingCamera=true;
    if (!m_pUnknown88 || !m_pCameraController) return;
    m_pUnknown88->setNearClipDistance(1.0f);
    m_pUnknown88->setFarClipDistance(20000.0f);
    m_pUnknown88->yaw(Ogre::Radian(0.0f));
    m_pUnknown88->pitch(Ogre::Radian(0.0f));
    m_pUnknown88->setPosition(position);
    m_pUnknown88->lookAt(Ogre::Vector3(m_iUnknown98[3],m_iUnknown98[4],m_iUnknown98[5]));
    m_pCameraController->ResetPOV(true,-45.0f,43.31f);
    m_pCameraController->m_fUnknownE0=position.z-14.299999237060547f;
    m_pCameraController->m_fUnknownDC=position.y+21.44999885559082f;
    m_pCameraController->m_fUnknownD8=position.x+14.299999237060547f;
    if (m_pCameraController) m_pCameraController->m_bUnknown178=true;
    m_bRenderWindowHasFocus=true;
    m_pCameraController->Update(1.0f,1.0f);
    update(1.0f);
    m_pEditorResourceManager->editorUpdateSceneOnce(0);
    m_pCameraController->m_bUnknown14C=false;
    m_pCameraController->m_bUnknown14D=false;
    m_pCameraController->m_bUnknown14A=false;
    m_pCameraController->m_bUnknown14B=false;
    m_pCameraController->m_bUnknown148=false;
    m_pCameraController->m_bUnknown149=false;
    m_pCameraController->DeactivateMouse();
    bResettingCamera=false;
}

void CEditor::update(float elapsed)
{
    if (!m_bUnknown4A || !m_pSettings) return;
    SDL_Window* window=SDL_GetWindowFromID(static_cast<unsigned>(reinterpret_cast<size_t>(m_pEditorResourceManager->getWindowHandle())));
    int width,height;
    SDL_GetWindowSize(window,&width,&height);
    m_pSettings->SetInt(KSETTINGS_WIN_WIDTH,width);
    m_pSettings->SetInt(KSETTINGS_WIN_HEIGHT,height);
    if (m_pUnknown138) m_pUnknown138->setVisible((m_iFlags>>8)&1);
    if (getCamera() && static_cast<float>(width)>0.0f && static_cast<float>(height)>0.0f)
        m_pEditorResourceManager->updateAspectRatio(static_cast<float>(width),static_cast<float>(height));
    if (getSingleton()->m_iFlags & (1u<<EDITOR_FLAG_INGAME_MODE)) {
        unsigned property=KSETTINGS_F_PARTICLE_FALLOFF;
        float falloff=CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(property);
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_particleFalloff=falloff;
    } else if (!(getSingleton()->m_iFlags & (1u<<EDITOR_FLAG_INGAME_MODE))) {
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_particleFalloff=999999.0f;
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_cameraPosition=Ogre::Vector3::ZERO;
        UpdatePlayerInput(elapsed);
        if (static_cast<short>(m_iFlags)<0) updateParticleSystems(elapsed,1.0f);
        if (m_pUnknown88 && m_pCameraController && m_bRenderWindowHasFocus) {
            m_pCameraController->Update(elapsed,1.0f);
            m_pUnknown88->setPosition(Ogre::Vector3(m_pCameraController->m_fUnknownD8,m_pCameraController->m_fUnknownDC,m_pCameraController->m_fUnknownE0));
            m_pUnknown88->lookAt(Ogre::Vector3(m_pCameraController->m_fUnknownD8+m_pCameraController->m_viewAxis120,m_pCameraController->m_fUnknownDC+m_pCameraController->m_fUnknown124,m_pCameraController->m_fUnknownE0+m_pCameraController->m_viewAxis128));
            if (GetAsyncKeyState(0x52)<0) {
                if (getSingleton()->m_pObjectManager->getSelectedObjects()->size()==0)
                    ResetCamera(Ogre::Vector3(m_iUnknown98[0],m_iUnknown98[1],m_iUnknown98[2]));
                else {
                    Ogre::Vector3 pivot=getSingleton()->m_pObjectManager->getSelectedPivot();
                    ResetCamera(Ogre::Vector3(pivot.x+m_iUnknown98[0],pivot.y+m_iUnknown98[1],pivot.z+m_iUnknown98[2]));
                }
            }
        }
        if (m_pUnknown128->getGameClientCount())
            m_pUnknown128->getGameClient(0)->m_audioListenerPosition=m_pUnknown88->getPosition();
        if (m_pUnknown168) {
            m_pUnknown168->update(m_pUnknown88,m_pUnknown88->getPosition(),elapsed,1.0f,NULL);
            m_pUnknown168->updateLayouts(elapsed);
            m_pUnknown168->updateCharacterAnimation(elapsed,1.0f,NULL);
            m_pUnknown168->updateItems(m_pUnknown88,m_pUnknown88->getPosition(),elapsed);
            m_pUnknown168->updateLevelUpdateObjects(m_pUnknown88,m_pUnknown88->getPosition(),elapsed);
        }
    }
    if (m_pObjectManager) m_pObjectManager->EditorUpdate(0.0f);
    if (!(getSingleton()->m_iFlags & (1u<<EDITOR_FLAG_INGAME_MODE)))
        for (unsigned i=0;i<m_EditorScenes.size();++i)
            if (m_EditorScenes[i]) m_EditorScenes[i]->update(elapsed);
}

void CEditor::setFlag(EEDITOR_FLAGS flag)
{
    unsigned mask=1u<<(static_cast<unsigned>(flag)&31);
    m_iFlags|=mask;
    if (flag==EDITOR_FLAG_SHOW_STATS) {
        if (m_pEditorResourceManager->getGameClient()->getGameUI())
            m_pEditorResourceManager->getGameClient()->getGameUI()->toggleFPS();
        return;
    }
    if (flag!=EDITOR_FLAG_INGAME_MODE || !m_pEditorResourceManager || !m_pEditorResourceManager->getGameClient()) return;
    m_iUnknown78[0]=m_pCameraController->m_fUnknownD8;
    m_iUnknown78[1]=m_pCameraController->m_fUnknownDC;
    m_iUnknown78[2]=m_pCameraController->m_fUnknownE0;
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/Torchlight/Torched/DataEditor/EditorFolder");
    Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("EDITORRESOURCES");
    CEditorScene* layout=m_EditorScenes[m_EditorSceneIDs[L"Layout"]];
    if (!layout) return;
    std::wstring temporary=FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetAppDataPath(),L"Torched/DataEditor/EditorFolder/temp.layout");
    TArrayList<CEditorBaseObject*>* objects=layout->GetObjectsCreatedByADescriptor(L"Room Piece");
    bool saved=false;
    if (objects && objects->size()) {
        for (unsigned i=0;i<objects->size();++i) {
            if (!(*objects)[i]) continue;
            CRoomPiece* piece=dynamic_cast<CRoomPiece*>((*objects)[i]);
            if (piece && piece->CSceneNodeObject::getVisible()) {
                layout->saveScene(temporary,NULL);
                saved=true;
                break;
            }
        }
    }
    if (!saved) {
        copyFileTo(FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(),L"/DataEditor/default.layout"),temporary);
        copyFileTo(FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(),L"/DataEditor/default.layout.cmp"),temporary+L".cmp");
    }
    CMasterResourceManager::getSingleton()->addResourceLocation(FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetAppDataPath(),L"Torched/"),"EDITORRESOURCES",true);
    m_iFlags&=~mask;
    layout->setVisible(false);
    layout->setEnabled(false);
    m_iFlags|=mask;
    CQuestManager::getSingleton()->resetQuestManager(false);
    int seed=UTILITIES::randomIntegerBetween(0,0x7fffffff);
    m_pEditorResourceManager->getGameClient()->m_gameSeed=seed;
    m_pEditorResourceManager->getGameClient()->loadLevel(std::wstring(EMPTY_WSTRING.c_str()),L"DataEditor/EditorRules.dat",false,m_iLevelDepth,static_cast<ELevelEntryType>(3),EMPTY_WSTRING);
    for (unsigned i=0;i<gEditor->m_ActiveQuests.size();++i) {
        CQuest* quest=reinterpret_cast<CQuest*>(CQuestManager::getSingleton()->getQuestByName(gEditor->m_ActiveQuests[i]));
        if (quest && !quest->m_questAccepted) {
            CQuestManager::getSingleton()->giveQuest(quest,NULL,false);
            quest->setQuestAcceptDialogInteracted(true);
        }
    }
    for (unsigned i=0;i<gEditor->m_CompletedQuests.size();++i) {
        CQuest* quest=reinterpret_cast<CQuest*>(CQuestManager::getSingleton()->getQuestByName(gEditor->m_CompletedQuests[i]));
        if (quest) CQuestManager::getSingleton()->completeQuest(quest);
    }
}

void CEditor::removeFlag(EEDITOR_FLAGS flag)
{
    unsigned old=m_iFlags;
    m_iFlags&=~(1u<<(static_cast<unsigned>(flag)&31));
    if (flag==EDITOR_FLAG_SHOW_STATS) {
        if (m_pEditorResourceManager->getGameClient()->getGameUI())
            m_pEditorResourceManager->getGameClient()->getGameUI()->toggleFPS();
        return;
    }
    if (flag==EDITOR_FLAG_UPDATE_PARTICLES_CIRCLE) {
        if (static_cast<short>(old)<0) {
            float radius=m_fParticleMovementB;
            m_fParticleMovementB=0.0f;
            updateParticleSystems(0.0f,0.0f);
            m_fParticleMovementB=radius;
        }
        return;
    }
    if (flag!=EDITOR_FLAG_INGAME_MODE || !m_pEditorResourceManager) return;
    m_pEditorResourceManager->getGameCamera();
    if (!m_pEditorResourceManager->getGameClient()) return;
    CEditorScene* layout=m_EditorScenes[m_EditorSceneIDs[L"Layout"]];
    CGameUI::getSingleton()->closeAll();
    CGameUI::getSingleton()->closeCinematicMenu();
    CGameUI::getSingleton()->closeLeft();
    CGameUI::getSingleton()->closeRight();
    CGameUI::getSingleton()->closeMenus();
    TArrayList<CEditorBaseObject*>* objects=layout->GetObjectsCreatedByADescriptor(L"Room Piece");
    if (objects->size() && m_pEditorResourceManager->getGameClient()->m_level)
        m_pEditorResourceManager->getGameClient()->m_level->clearProjectorPass(NULL,NULL);
    m_pEditorResourceManager->getGameClient()->refreshLighting();
    m_pEditorResourceManager->getGameClient()->unloadCurrentLevel(true);
    layout=m_EditorScenes[m_EditorSceneIDs[L"Layout"]];
    if (!layout) return;
    if (m_bUnknown4B) {
        layout->DeleteAllObjectsFromScene();
        m_bUnknown4B=false;
    }
    layout->setVisible(true);
    layout->setEnabled(true);
    bool focused=m_bRenderWindowHasFocus;
    if (m_pCameraController) m_pCameraController->m_bUnknown178=true;
    m_bRenderWindowHasFocus=true;
    m_pCameraController->m_fUnknownD8=m_iUnknown78[0];
    m_pCameraController->m_fUnknownDC=m_iUnknown78[1];
    m_pCameraController->m_fUnknownE0=m_iUnknown78[2];
    m_pCameraController->Update(1.0f,1.0f);
    update(1.0f);
    m_pEditorResourceManager->editorUpdateSceneOnce(0);
    if (m_pCameraController) m_pCameraController->m_bUnknown178=focused;
    m_bRenderWindowHasFocus=focused;
    gEditor->m_bUseTempStartPos=false;
}

void CEditor::InitEditor(iEditorResourceManager* manager,Ogre::Viewport* viewport)
{
    if (!manager || m_bUnknown4A) return;
    m_pEditorResourceManager=manager;
    m_bUnknown4A=true;
    m_pSettings=manager->getSettings();
    m_pUnknown90=viewport;
    m_pUnknown88=viewport->getCamera();
    if (!m_pUnknown88 || !m_pSettings || !m_pEditorResourceManager->getSceneManager()) return;
    m_pUnknown128=new CResourceManager(NULL);
    m_pObjectManager=new CEditorObjectManager(m_pUnknown128);
    CSettings* settings=m_pEditorResourceManager->getSettings();
    CGameClient* client=m_pEditorResourceManager->getGameClient();
    Ogre::SceneManager* scene=m_pEditorResourceManager->getSceneManager();
    CSoundManager* sound=m_pEditorResourceManager->getSoundManager();
    m_pUnknown168=new CLevel(L"EDITOR",settings,client,m_pUnknown128,scene,sound,0,0);
    m_pUnknown128->m_pLevel=m_pUnknown168;
    m_keyPropertyIndices[0]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEUPALT1",0x45,false);
    m_keyPropertyIndices[6]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEUPALT2",0x65,false);
    m_keyPropertyIndices[1]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEDOWNALT1",0x51,false);
    m_keyPropertyIndices[7]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEDOWNALT2",0x71,false);
    m_keyPropertyIndices[2]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVERIGHTALT1",0x44,false);
    m_keyPropertyIndices[8]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVERIGHTALT2",0x64,false);
    m_keyPropertyIndices[3]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVELEFTALT1",0x41,false);
    m_keyPropertyIndices[9]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVELEFTALT2",0x61,false);
    m_keyPropertyIndices[4]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEFORWARDALT1",0x57,false);
    m_keyPropertyIndices[10]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEFORWARDALT2",0x77,false);
    m_keyPropertyIndices[5]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEBACKWARDALT1",0x53,false);
    m_keyPropertyIndices[11]=m_pSettings->GetIntPropertyIndex(L"EDITORMOVEBACKWARDALT2",0x73,false);
    m_keyPropertyIndices[12]=m_pSettings->GetIntPropertyIndex(L"EDITORRESETCAMERA_ALT1",0x52,false);
    m_keyPropertyIndices[13]=m_pSettings->GetIntPropertyIndex(L"EDITORRESETCAMERA_ALT2",0x72,false);
    m_pUnknownB0=new CMouseHandler(m_pEditorResourceManager->getWindowHandle());
    m_pUnknown90->setBackgroundColour(Ogre::ColourValue(0.0f,0.0f,0.0f));
    m_pCameraController=new CPOV(*m_pSettings);
    ResetCamera(Ogre::Vector3(m_iUnknown98[0],m_iUnknown98[1],m_iUnknown98[2]));
    recreateScene(0);
    recreateScene(1);
    recreateScene(2);
    EditorDumpDescriptionOfObjectsToFile(FILESYSTEM::GetAppDataPath()+L"Torched/objects.dat");
    m_pUnknown130=m_pUnknown128->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
    m_pUnknown138=OGRE_UTILITIES::createEntity(m_pUnknown128->getSceneManager(),L"media/models/grid/grid.mesh",static_cast<OGRE_UTILITIES::EQUERYMASK>(1),"gm");
    OGRE_UTILITIES::attachEntityToSceneNode(m_pUnknown138,m_pUnknown130);
    m_pUnknown138->setMaterialName("Wireframe");
    m_pUnknown130->setPosition(0.0f,0.0f,0.0f);
    CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_paused=false;
}
