#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <cstring>
#include "Character.h"
#include "Cinematics.h"
#include "Descriptor.h"
#include "DescriptorController.h"
#include "DescriptorManager.h"
#include "DescriptorProp.h"
#include "Editor.h"
#include "EditorBaseObject.h"
#include "EditorDLL.h"
#include "EditorObjectManager.h"
#include "EditorScene.h"
#include "EffectGroupManager.h"
#include "FileSystem.h"
#include "GameClient.h"
#include "GenericModel.h"
#include "LogicGroup.h"
#include "LogicLink.h"
#include "LogicObject.h"
#include "MasterResourceManager.h"
#include "MissilePreloader.h"
#include "MonsterDescriptor.h"
#include "ParticlePreloader.h"
#include "QuestManager.h"
#include "Recipes.h"
#include "ResourceManager.h"
#include "Sets.h"
#include "Settings.h"
#include "SoundManager.h"
#include "StringUtilities.h"
#include "Timeline.h"
#include "Undo.h"
#include "UnitThemes.h"
#include "iEditorResourceManager.h"
#include "iSnap.h"
// Shared output buffers supplied by the original editor.
extern char sEditorTmpMemory[4000];
extern wchar_t sEditorString[];

extern CUndo* g_pGroupedUndos;
extern CEditorObjectManager::ObjectMap::iterator iteratorOfObjectsInScene;

// This existing helper remains supplied by the original ELF.
extern CTimeline* GetTimeline(long long id);


void EditorSetPOVVelocityMult(float value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetPovVelocityMult(value);
}

void EditorSetMouseWheelDelta(int value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetMouseWheelDelta(value);
}

void EditorRedo()
{
    if (!gEditor->isActive()) return;
    gEditor->doRedo();
}

void EditorUndo()
{
    if (!gEditor->isActive()) return;
    gEditor->doUndo();
}

void EditorWindowHasFocus(bool value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetRenderWindowHasFocus(value);
}

void EditorDeleteAllUndos()
{
    gEditor->deleteAllUndos();
}

void EditorGetUndoRedoCounts(unsigned int& undo, unsigned int& redo)
{
    if (!gEditor->isActive()) return;
    undo = gEditor->getUndoSize();
    redo = gEditor->getRedoSize();
}

void EditorSetChunkTemplateExits(int value)
{
    if (!gEditor->isActive()) return;
    gEditor->getObjectManager()->EditorSetChunkTemplateExits(value);
}

void EditorSetChunkTemplateExit(int index, float x, float y, float z)
{
    if (!gEditor->isActive()) return;
    gEditor->getObjectManager()->EditorSetChunkTemplateExit(index, x, y, z);
}

void EditorResetCamera(float x, float y, float z)
{
    if (!gEditor->isActive()) return;
    gEditor->ResetCamera(Ogre::Vector3(x, y, z));
}

void reloadRecipes()
{
    if (!gEditor->isActive()) return;
    CRecipes::getSingleton()->reload();
}

void reloadUnitThemes()
{
    if (!gEditor->isActive()) return;
    CUnitThemes::getSingleton()->reload();
}

void reloadQuests()
{
    if (!gEditor->isActive()) return;
    CQuestManager::getSingleton()->reloadQuests();
}

void reloadModFileFilter()
{
    if (!gEditor->isActive()) return;
    CFileSystem::getSingleton()->reload();
}

void reloadMissiles()
{
    if (!gEditor->isActive()) return;
    CMissilePreloader::getSinglelton()->reloadMissiles();
}

void reloadCinematics()
{
    if (!gEditor->isActive()) return;
    CCinematics::getSingleton()->reload();
}

void reloadAffixes()
{
    if (!gEditor->isActive()) return;
    CMasterResourceManager::getSingleton()->m_effectGroups->reload();
}

void EditorDeleteAllObjectsInScene(unsigned int index)
{
    if (!gEditor->isActive()) return;
    CEditorScene* scene = gEditor->GetEditorScene(index);
    if (scene) gEditor->getObjectManager()->EditorDeleteAllObjectsInScene(scene);
}

void EditorSetMonsterAutoSpawn(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    gEditor->m_sUnknown198 = name;
}

void EditorSetOrientSnapSize(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetOrientSnapSize(arg1);
}
void EditorSetPosVSnapSize(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetPosVSnapSize(arg1);
}
void EditorSetPosHSnapSize(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetPosHSnapSize(arg1);
}
void EditorSetChunkTemplateHeight(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetChunkTemplateHeight(arg1);
}
void EditorSetChunkTemplateWidth(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetChunkTemplateWidth(arg1);
}
void EditorSetChunkTemplateBasisSize(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetChunkTemplateBasisSize(arg1);
}
float EditorGetWorkingPlaneHeight()
{
    if (!gEditor->isActive())
        return 0.0f;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    return manager->EditorGetWorkingPlaneHeight();
}
void EditorSetWorkingPlaneHeight(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetWorkingPlaneHeight(arg1);
}
void EditorSetSnapToGroundBias(float arg1)
{
    if (!gEditor->isActive())
        return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    manager->EditorSetSnapToGroundBias(arg1);
}
unsigned int EditorGetDescriptorHash()
{
    if (!gEditor->isActive()) return static_cast<unsigned int>(-1);
    return CDescriptorController::getDescriptionVersion();
}

void EditorSetBackgroundColor(float red, float green, float blue)
{
    if (!gEditor->isActive()) return;
    gEditor->SetBackgroundColor(red, green, blue);
}

void EditorFlushKeymanager()
{
    if (!gEditor->isActive()) return;
    gEditor->flushKeyManager();
}

void EditorSetObjectSelected(long long guid, bool clear)
{
    if (!gEditor->isActive()) return;
    if (clear) gEditor->getObjectManager()->ClearSelectedObjects();
    if (guid == -1) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (object) gEditor->getObjectManager()->EditorObjectSelected(object);
}

long long EditorGetObjectUnderMouse()
{
    if (!gEditor->isActive()) return 0;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) {
        CEditorBaseObject* object = manager->getObjectUnderMouse();
        if (object) return object->getGuid();
    }
    return -1;
}

unsigned int EditorGetObjectSceneID(long long guid)
{
    if (!gEditor->isActive()) return static_cast<unsigned int>(-1);
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (object && object->getSceneOwner())
        return gEditor->GetEditorSceneIDByName(object->getSceneOwner()->getName().c_str());
    return static_cast<unsigned int>(-1);
}

void EditorSetSceneVisible(unsigned int index, bool visible)
{
    if (!gEditor->isActive()) return;
    CEditorScene* scene = gEditor->GetEditorScene(index);
    if (scene) scene->setVisible(visible);
}

int EditorCreateLogicObject(long long guid, long long objectGuid)
{
    if (!gEditor->isActive()) return -1;
    if (objectGuid == -1 || guid == -1) return -1;
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(GetObjectInScene(guid));
    if (!group || !GetObjectInScene(objectGuid)) return -1;
    return group->AddLogicObject(objectGuid);
}

long long EditorGetObjectIDRefedInLogicObject(long long guid, unsigned int index)
{
    if (!gEditor->isActive()) return -1;
    if (index == static_cast<unsigned int>(-1) || guid == -1) return -1;
    CLogicGroup* group = GetLogicGroupByID(guid);
    if (!group) return -1;
    CLogicObject* node = group->GetLogicObjectByIndex(index);
    if (!node) return -1;
    return node->m_iObjectID;
}

long long EditorTimelineGetObjectIDInTimelineByIndex(long long guid, int index)
{
    if (!gEditor->isActive()) return -1;
    CTimeline* timeline = GetTimeline(guid);
    if (!timeline) return -1;
    return timeline->GetObjectIDInTimelineByIndex(index);
}

int EditorGetCountOfLogicLinksInLogicObject(long long guid, unsigned int index)
{
    if (!(!gEditor->isActive())) {
        if (!(index == static_cast<unsigned int>(-1))) {
            if (!(guid == -1)) {
                CEditorBaseObject* object = GetObjectInScene(guid);
                if (!(!object)) {
                    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
                    if (!(!group)) {
                        CLogicObject* node = group->GetLogicObjectByIndex(index);
                        if (!(!node)) {
                            return node->m_Links.size();
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void EditorSetEditorMonsterSpawnclass(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    gEditor->m_sUnknown180 = name;
}

void EditorSetCommandAutoRun(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    gEditor->m_sUnknown1A0 = name;
}

void EditorSetEditorPlayerFile(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    gEditor->m_sUnknown190 = name;
}

void reloadItemSets()
{
    if (!gEditor->isActive()) return;
    if (CMasterResourceManager::getSingleton()->m_effectGroups)
        CSets::getSingleton()->reload(CMasterResourceManager::getSingleton()->m_effectGroups);
}

void reloadEditorParticles()
{
    if (!gEditor->isActive()) return;
    if (CMasterResourceManager::getSingleton()->m_pParticlePreloader)
        CMasterResourceManager::getSingleton()->m_pParticlePreloader->ReloadEditorParticles();
}

void EditorReloadSoundData()
{
    if (!gEditor->isActive()) return;
    CGameClient* client = gEditor->getEditorResourceManager()->getGameClient();
    if (client) client->reloadSoundBankData();
}

void EditorStopMusic()
{
    if (!gEditor->isActive()) return;
    if (gEditor->getEditorResourceManager()->getGameClient()) {
        CSoundManager* sound = CMasterResourceManager::getSingleton()->m_pSoundManager;
        if (sound) sound->stopMusic();
    }
}

bool EditorGetMuted()
{
    if (!gEditor->isActive()) return false;
    if (gEditor->m_pUnknown128 && CMasterResourceManager::getSingleton()->m_pSoundManager) {
        CSoundManager* sound = CMasterResourceManager::getSingleton()->m_pSoundManager;
        return !sound->m_bUnknown6A9 || !sound->m_bUnknown6A8;
    }
    return false;
}

void EditorSetMuted(bool muted)
{
    if (!gEditor->isActive()) return;
    if (gEditor->m_pUnknown128 && CMasterResourceManager::getSingleton()->m_pSoundManager) {
        if (muted) CMasterResourceManager::getSingleton()->m_pSoundManager->stopAllSounds();
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SOUNDMUTE, muted ? 1 : 0);
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_MUSICMUTE, muted ? 1 : 0);
    }
}

void EditorDiretionalIntensity(float& intensity, bool write)
{
    if (!gEditor->isActive()) return;
    if (write) gEditor->setDirectionalIntensity(intensity);
    else intensity = gEditor->getSettings()->GetFloat(KSETTINGS_F_DIRECTIONAL_INTENSITY);
}

void EditorSetWorkingPlaneHeightToSelectedPivot()
{
    if (!gEditor->isActive()) return;
    Ogre::Vector3 pivot = gEditor->getObjectManager()->getSelectedPivot();
    gEditor->getObjectManager()->EditorSetWorkingPlaneHeight(pivot.y);
}

void EditorStartUndo()
{
    if (gEditor->isActive())
    {
        g_pGroupedUndos = new CUndo;
        bGroupUndos = true;
    }
}

void EditorEndUndo()
{
    if (gEditor->isActive() && bGroupUndos && g_pGroupedUndos)
    {
        gEditor->addUndo(g_pGroupedUndos, false);
        bGroupUndos = false;
    }
}

float EditorGetTime()
{
    if (gEditor->isActive())
        return gEditor->getTimer()->getMillisecondsCPU() / 1000.0;
    return 0;
}

int EditorTimelineGetPropertyIDForObjectInTimelineByIndex(long long timelineID,
                          long long objectID, int index, bool& isEvent)
{
    if (!gEditor->isActive())
        return -1;
    CTimeline* timeline = GetTimeline(timelineID);
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (timeline && object)
    {
        std::pair<int, bool> property = timeline->GetPropertyIDForObjectInTimelineByIndex(objectID, index);
        isEvent = property.second;
        return property.first;
    }
    return -1;
}

void* EditorGetObjectProperty(long long objectID, unsigned int propertyID)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive())
        return NULL;
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (!object)
        return NULL;
    CDescriptor* descriptor = object->getDescriptor();
    if (descriptor)
    {
        unsigned int count = 0;
        void* data = descriptor->GetPropertyValue(object, propertyID, count);
        if (count < 1000000)
        {
            count *= sizeof(wchar_t);
            unsigned long bytes = count;
            std::memcpy(sEditorTmpMemory, data, bytes);
            *reinterpret_cast<wchar_t*>(reinterpret_cast<char*>(sEditorTmpMemory) + bytes) = 0;
        }
        return sEditorTmpMemory;
    }
    return NULL;
}

void* EditorGetObjectPropertyArray(long long objectID, unsigned int propertyID,
                                  unsigned int& count)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive())
        return NULL;
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (!object)
        return NULL;
    CDescriptor* descriptor = object->getDescriptor();
    if (descriptor)
    {
        void* data = descriptor->GetPropertyValue(object, propertyID, count);
        if (count < 1000000)
        {
            unsigned int bytes = count * sizeof(wchar_t);
            std::memcpy(sEditorTmpMemory, data, bytes);
            *reinterpret_cast<wchar_t*>(reinterpret_cast<char*>(sEditorTmpMemory) + bytes) = 0;
        }
        return sEditorTmpMemory;
    }
    return NULL;
}

void EditorLogMessage(wchar_t* message, Ogre::LogMessageLevel level)
{
    if (gEditor->isActive())
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow(message), level, false);
}

void* EditorTimelineGetValueAtPoint(long long timelineID, long long objectID, int propertyID, int pointID)
{
    if (gEditor->isActive())
    {
        CTimeline* timeline = GetTimeline(timelineID);
        if (!GetObjectInScene(objectID))
            return NULL;
        if (timeline)
        {
            unsigned int count;
            return timeline->GetPropertyPointValue(objectID, propertyID, pointID, count);
        }
    }
    return NULL;
}

void* EditorTimelineGetValueAtPointArray(long long timelineID, long long objectID, int propertyID, int pointID,
                                           unsigned int& count)
{
    if (gEditor->isActive())
    {
        CTimeline* timeline = GetTimeline(timelineID);
        if (!GetObjectInScene(objectID))
            return NULL;
        if (timeline)
            return timeline->GetPropertyPointValue(objectID, propertyID, pointID, count);
    }
    return NULL;
}

void reloadTextures()
{
    if (gEditor->isActive())
    {
        Ogre::TextureManager::getSingleton().setPreferredBitDepths(0, 1, true);
        Ogre::TextureManager::getSingleton().reloadAll(true);
    }
}
