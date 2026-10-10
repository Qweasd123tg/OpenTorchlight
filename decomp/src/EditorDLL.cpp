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

#include "Mod.h"
#include "ModFileFilter.h"
#include "SkillParser.h"
#include "SpawnClassParser.h"

void EditorSetFlagState(unsigned int flag, bool set)
{
    if (!gEditor->isActive()) return;
    if (set) gEditor->setFlag(static_cast<EEDITOR_FLAGS>(flag));
    else gEditor->removeFlag(static_cast<EEDITOR_FLAGS>(flag));
}

void EditorResnapSelectedObjects(bool snap)
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorResnapSelectedObjects(snap);
}

void EditorResetOrientation()
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorResetOrientation();
}

void EditorResetScale()
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorResetScale();
}

void EditorApplyRotationNoise(float amount)
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorApplyRotationNoise(amount);
}

void EditorSnapObjectsToGround(bool snap)
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorSnapObjectsToGround(snap);
}

void EditorApplyNormalNoise(float amount)
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorApplyNormalNoise(amount);
}

void EditorApplyScaleNoise(float amount, bool uniform)
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) manager->EditorApplyScaleNoise(amount, uniform);
}

void EditorSetEditorCompletedQuests(wchar_t* quests)
{
    if (!gEditor->isActive()) return;
    gEditor->setCompletedQuests(std::wstring(quests));
}

void EditorSetEditorActiveQuests(wchar_t* quests)
{
    if (!gEditor->isActive()) return;
    gEditor->setActiveQuests(std::wstring(quests));
}

void EditorCreateMod(const wchar_t* name)
{
    if (!gEditor->isActive() || !name) return;
    CModFileFilter::getSingleton()->addNewMod(std::wstring(name));
}

void EditorReloadSkill(wchar_t* path)
{
    if (!gEditor->isActive()) return;
    CSkillParser::getSingleton()->parseSkill(std::wstring(path));
}

void EditorSetObjectName(long long guid, wchar_t* name)
{
    if (!gEditor->isActive() || !name) return;
    std::wstring value(name);
    if (!value.empty()) {
        CEditorBaseObject* object = GetObjectInScene(guid);
        if (object) object->SetName(value);
    }
}

wchar_t* EditorGetObjectName(long long guid)
{
    STRINGS::StringCopyWCharArray(sEditorString, 1000, L"ERROR");
    if (!gEditor->isActive()) return NULL;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return NULL;
    STRINGS::StringCopyWCharArray(sEditorString, 1000, object->getName().c_str());
    return sEditorString;
}

void SetModEnabled(const wchar_t* name, bool enabled)
{
    if (!gEditor->isActive()) return;
    TArrayList<CMod*>* mods = &CModFileFilter::getSingleton()->m_Mods;
    if (!mods) return;
    for (unsigned int i = 0; i < mods->size(); ++i) {
        if ((*mods)[i]->m_wUnknown50 == name) {
            (*mods)[i]->m_bUnknown70 = enabled;
            break;
        }
    }
}

void EditorPlayMusic(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    if (!gEditor->getEditorResourceManager()->getGameClient()) return;
    CSoundManager* sound = CMasterResourceManager::getSingleton()->m_pSoundManager;
    if (!sound) return;
    std::wstring track(name);
    sound->playMusic(track, true);
}

void EditorSetEditorPetType(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    if (gEditor->getGameClient())
        gEditor->getGameClient()->setEditorCreationPet(std::wstring(name));
}

void EditorSetEditorCharacterClass(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    if (gEditor->getGameClient())
        gEditor->getGameClient()->setEditorCreationClass(std::wstring(name));
}

float EditorTimelineUpdate(long long guid, float elapsed)
{
    if (!gEditor->isActive()) return 0.0f;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    return timeline ? timeline->UpdateTimeline(elapsed) : 0.0f;
}

int EditorGetCountOfLogicObjectsInLogicGroup(long long guid)
{
    if (!gEditor->isActive() || guid == -1) return -1;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    return group ? group->m_logicObjects.size() : -1;
}

bool EditorDeleteLogicObject(long long guid, int index)
{
    if (!gEditor->isActive() || index == -1 || guid == -1) return false;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    return group ? group->RemoveLogicObjectByIndex(index) : false;
}

long long EditorTimelineAddPointToProperty(long long timelineGuid, long long objectGuid,
                                   int property, bool event)
{
    if (!gEditor->isActive()) return 0xffffffffu;
    CTimeline* timeline = GetTimeline(timelineGuid);
    CEditorBaseObject* object = GetObjectInScene(objectGuid);
    if (!object) return 0xffffffffu;
    if (timeline)
        return timeline->AddPointToProperty(objectGuid, property, event);
    return 0xffffffffu;
}


void reloadSpawnClasses()
{
    if (!gEditor->isActive()) return;
    CSpawnClassParser::getSingleton()->reloadFromDirectory(L"media/spawnclasses/");
}

void EditorAmbientColor(int& red, int& green, int& blue, bool write)
{
    if (!gEditor->isActive()) return;
    if (write) gEditor->setAmbientColor(red, green, blue);
    else {
        red = gEditor->getSettings()->GetInt(KSETTINGS_AMBIENT_LIGHT_RED);
        green = gEditor->getSettings()->GetInt(KSETTINGS_AMBIENT_LIGHT_GREEN);
        blue = gEditor->getSettings()->GetInt(KSETTINGS_AMBIENT_LIGHT_BLUE);
    }
}

void EditorDiretionalColor(int& red, int& green, int& blue, bool write)
{
    if (!gEditor->isActive()) return;
    if (write) gEditor->setDirectionalColor(red, green, blue);
    else {
        red = gEditor->getSettings()->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_RED);
        green = gEditor->getSettings()->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_GREEN);
        blue = gEditor->getSettings()->GetInt(KSETTINGS_DIRECTIONAL_LIGHT_BLUE);
    }
}

void EditorMaterialAmbientColor(int& red, int& green, int& blue, bool write)
{
    if (!gEditor->isActive()) return;
    if (write) gEditor->setMaterialAmbientColor(red, green, blue);
    else {
        red = gEditor->getSettings()->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED);
        green = gEditor->getSettings()->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN);
        blue = gEditor->getSettings()->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE);
    }
}

unsigned int EditorGetLogicLinkInputFunctionID(long long guid, unsigned int objectIndex,
                                            unsigned int linkIndex)
{
    if (!gEditor->isActive() || objectIndex == ~0u || guid == -1 || linkIndex == ~0u) return ~0u;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return ~0u;
    CLogicObject* logic = group->GetLogicObjectByIndex(objectIndex);
    if (!logic) return ~0u;
    return logic->GetLogicLinkByIndex(linkIndex)->GetInputFuncID();
}

unsigned int EditorGetLogicLinkOutputFunctionID(long long guid, unsigned int objectIndex,
                                             unsigned int linkIndex)
{
    if (!gEditor->isActive() || objectIndex == ~0u || guid == -1 || linkIndex == ~0u) return ~0u;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return ~0u;
    CLogicObject* logic = group->GetLogicObjectByIndex(objectIndex);
    if (!logic) return ~0u;
    return logic->GetLogicLinkByIndex(linkIndex)->GetOutputFuncID();
}

unsigned int EditorGetLogicObjectIDLinkingTo(long long guid, unsigned int objectIndex,
                                         unsigned int linkIndex)
{
    if (!gEditor->isActive() || objectIndex == ~0u || guid == -1 || linkIndex == ~0u) return ~0u;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return ~0u;
    CLogicObject* logic = group->GetLogicObjectByIndex(objectIndex);
    if (!logic) return ~0u;
    CLogicLink* link = logic->GetLogicLinkByIndex(linkIndex);
    if (!link || !link->m_pLinkingToLogicObject) return ~0u;
    return group->GetLogicObjectIndex(link->m_pLinkingToLogicObject);
}

void EditorGetLogicObjectPosition(long long guid, unsigned int index, int& x, int& y)
{
    if (!gEditor->isActive() || index == ~0u || guid == -1) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return;
    CLogicObject* logic = group->GetLogicObjectByIndex(index);
    if (logic) {
        x = static_cast<int>(logic->m_fLeft);
        y = static_cast<int>(logic->m_fTop);
    }
}

void EditorSetLogicObjectPosition(long long guid, unsigned int index, int x, int y)
{
    if (!gEditor->isActive() || index == ~0u || guid == -1) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return;
    CLogicObject* logic = group->GetLogicObjectByIndex(index);
    if (logic) {
        logic->SetXPosition(x);
        logic->SetYPosition(y);
    }
}

bool EditorDeleteLogicLink(long long guid, unsigned int objectIndex, unsigned int linkIndex)
{
    if (!gEditor->isActive() || objectIndex == ~0u || guid == -1 || linkIndex == ~0u) return false;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    return group ? group->RemoveLogicObjectsLink(objectIndex, linkIndex) : false;
}

void EditorInvokeOutputFunction(long long guid, unsigned int objectIndex, unsigned int event)
{
    if (!gEditor->isActive() || objectIndex == ~0u || guid == -1 || event == ~0u) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(object);
    if (!group) return;
    CLogicObject* logic = group->GetLogicObjectByIndex(objectIndex);
    if (logic) logic->Invoke(event);
}

long long EditorTimelineGetPointIDInTimelinePropertyByIndex(long long timelineGuid,
        long long objectGuid, int property, int point, bool event)
{
    if (!gEditor->isActive()) return 0xffffffffu;
    CTimeline* timeline = GetTimeline(timelineGuid);
    CEditorBaseObject* object = GetObjectInScene(objectGuid);
    if (!object) return 0xffffffffu;
    if (timeline) return timeline->GetPointIDInTimelinePropertyByIndex(objectGuid, property, point, event);
    return 0xffffffffu;
}

long long EditorTimelineRemovePointFromProperty(long long timelineGuid, long long objectGuid,
        int property, int point, bool event)
{
    if (!gEditor->isActive()) return 0;
    CEditorBaseObject* object = GetObjectInScene(timelineGuid);
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    object = GetObjectInScene(objectGuid);
    if (object && timeline) return timeline->RemovePointFromProperty(objectGuid, property, point, event);
    return 0;
}

long long EditorTimelineRemoveProperty(long long timelineGuid, long long objectGuid,
        int property, bool event)
{
    if (!gEditor->isActive()) return 0;
    CEditorBaseObject* object = GetObjectInScene(timelineGuid);
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    object = GetObjectInScene(objectGuid);
    // The original forwards a null timeline when only the second lookup succeeds.
    if (object) return timeline->RemoveProperty(objectGuid, property, event);
    return 0;
}

float EditorTimelineGetTimePercentAtPoint(long long timelineGuid, long long objectGuid,
        int property, int point, bool event)
{
    if (!gEditor->isActive()) return 0.0f;
    CEditorBaseObject* object = GetObjectInScene(timelineGuid);
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    object = GetObjectInScene(objectGuid);
    if (object && timeline) return timeline->GetPropertyPointTimePercent(objectGuid, property, point, event);
    return 0.0f;
}

void EditorTimelineSetPropertyPointTimePercent(long long timelineGuid, long long objectGuid,
        int property, int point, float percent, bool event)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(timelineGuid);
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    object = GetObjectInScene(objectGuid);
    if (object && timeline) timeline->SetPropertyPointTimePercent(objectGuid, property, point, percent, event);
}

// Resource-name lists; byte counts preserve the original editor ABI.
#include "AIDefines.h"
#include "AnimationDefines.h"
#include "Cinematic.h"
#include "Constants.h"
#include "Dungeon.h"
#include "DungeonManager.h"
#include "GraphManager.h"
#include "SoundBankDataInformation.h"
#include "UnitResourceList.h"

wchar_t* EditorGetQuests()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CQuestManager::getSingleton()->getQuestNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetAffixes()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CMasterResourceManager::getSingleton()->m_effectGroups->getAffixNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetMissiles()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CMissilePreloader::getSinglelton()->getMissileNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* GetModNames()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CFileSystem::getSingleton()->getModNames(&names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSets()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CSets::getSingleton()->getSetNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* GetEnabledModNames()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CFileSystem::getSingleton()->getEnabledModNames(&names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSkills()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CSkillParser::getSingleton()->getSkillNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetUnits()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    gEditor->getResourceManager()->getMasterResourceList()->getUnitNames(names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSoundNames()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    std::wstring result(EMPTY_WSTRING);
    if (!gEditor->isActive()) return NULL;
    CSoundBankDataInformation* sound = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if (!sound) return NULL;
    TArrayList<std::wstring> names(10);
    sound->getSoundNames(&names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSoundNamesByCategory(wchar_t* category)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    std::wstring result(EMPTY_WSTRING);
    if (!gEditor->isActive()) return NULL;
    CSoundBankDataInformation* sound = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if (!sound) return NULL;
    std::wstring categoryName(category);
    TArrayList<std::wstring> names(10);
    sound->getSoundNamesByCatgoryName(std::wstring(category), &names);
    for (unsigned int i = 0; i < names.size(); ++i)
        result += names[i] + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSoundCategories()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    std::wstring result(EMPTY_WSTRING);
    if (!gEditor->isActive()) return NULL;
    CSoundBankDataInformation* sound = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if (!sound) return NULL;
    for (unsigned int i = 0; i < sound->m_categoryNames.size(); ++i)
        result += sound->m_categoryNames[i] + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetUnitTypes()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    if (hierarchy) {
        hierarchy->getTypeNames(&names);
        for (unsigned int i = 0; i < names.size(); ++i)
            result += names[i] + L",";
    }
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetDungeons()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    if (gEditor->getResourceManager()->getDungeonManager()) {
        CDungeonManager* manager = gEditor->getResourceManager()->getDungeonManager();
        for (unsigned int i = 0; i < manager->m_lDungeons.size(); ++i) {
            CDungeon* dungeon = manager->m_lDungeons[i];
            if (dungeon) result += dungeon->m_sName + L",";
        }
    }
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetGraphNames()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    CGraphManager* manager = CMasterResourceManager::getSingleton()->m_pGraphManager;
    if (!manager) return NULL;
    for (std::map<std::wstring, CGraph*>::iterator i = manager->m_GraphsByName.begin();
         i != manager->m_GraphsByName.end(); ++i)
        result += i->first + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetSpawnClasses()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    CSpawnClassParser* parser = CSpawnClassParser::getSingleton();
    for (std::map<std::wstring, CSpawnClass*>::iterator i = parser->m_spawnClasses.begin();
         i != parser->m_spawnClasses.end(); ++i)
        result += i->first + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetUnitThemes()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<CUnitTheme*>& themes = CUnitThemes::getSingleton()->getThemes();
    for (unsigned int i = 0; i < themes.size(); ++i)
        result = result + themes[i]->getName() + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetAlignments()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    for (unsigned int i = 0; i < 7; ++i)
        result += KALIGNMENT_STRINGS[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetAIFlags()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    TArrayList<std::wstring> names(10);
    for (unsigned int i = 0; i < 7; ++i)
        result += g_AIFLAG_TYPE_NAMES[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetDamageTypes()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    for (unsigned int i = 0; i < 7; ++i)
        result = result + gDAMAGE_TYPES[i] + L",";
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetAnimationKeyTypes()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    for (unsigned int i = 0; i < 29; ++i)
        result = result + gKEYFRAME_TYPES[i] + L",";
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorGetCinematics()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    unsigned int countOfCinematics = CCinematics::getSingleton()->m_lCinematics.size();
    for (unsigned int i = 0; i < countOfCinematics; ++i) {
        CCinematic* cinematic = CCinematics::getSingleton()->getCinematic(i);
        if (cinematic) result += cinematic->m_sName + L",";
    }
    unsigned int count = result.size();
    if (count < 2000000) {
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}


// Model animation and resource reload entry points.

wchar_t* EditorGetObjectPropertyString(long long guid, unsigned int property)
{
    STRINGS::StringCopyWCharArray(sEditorString, 1000, L"ERROR");
    void* value = EditorGetObjectProperty(guid, property);
    if (!value) return NULL;
    STRINGS::StringCopyWCharArray(sEditorString, 1000, static_cast<wchar_t*>(value));
    return sEditorString;
}

void EditorSetActiveAnimationPaused(long long guid, bool paused)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    if (model) model->m_animationPaused = paused;
}

float EditorGetActiveAnimationTimePosition(long long guid)
{
    if (!gEditor->isActive()) return 0.0f;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return 0.0f;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return 0.0f;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    return model ? model->getAnimationTime() : 0.0f;
}

void EditorSetActiveAnimationTimePosition(long long guid, float time)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    if (model) {
        model->setAnimationTime(time);
        model->updateAnimation(0.0f, true);
    }
}

void EditorReloadModelAnimations(long long guid)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    if (!model) return;
    model->clearAnimations();
    model->reloadAnimations();
    CCharacter* character = dynamic_cast<CCharacter*>(object);
    if (character) character->getBones();
}

void EditorReloadItem(wchar_t* path)
{
    if (!gEditor->isActive()) return;
    CUnitResourceList::getSingleton()->loadFile(static_cast<ERESOURCE_GROUPS>(0),
        std::wstring(L"ITEMS"), std::wstring(path), true, NULL);
}

void EditorReloadProp(wchar_t* path)
{
    if (!gEditor->isActive()) return;
    CUnitResourceList::getSingleton()->loadFile(static_cast<ERESOURCE_GROUPS>(3),
        std::wstring(L"PROPS"), std::wstring(path), true, NULL);
}

void EditorReloadPlayer(wchar_t* path)
{
    if (!gEditor->isActive()) return;
    CUnitResourceList::getSingleton()->loadFile(static_cast<ERESOURCE_GROUPS>(2),
        std::wstring(L"PLAYERS"), std::wstring(path), true, NULL);
}

void EditorReloadMonsters()
{
    if (!gEditor->isActive()) return;
    TArrayList<CEditorScene*>& scenes = gEditor->getEditorScenes();
    for (unsigned int i = 0; i < scenes.size(); ++i) {
        CDescriptor* descriptor = scenes[i]->GetDescriptorInSceneByName(L"Monster", false);
        CMonsterDescriptor* monster = dynamic_cast<CMonsterDescriptor*>(descriptor);
        if (monster) monster->ReloadMonsters();
    }
}
