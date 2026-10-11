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

static const std::wstring gTIMELINE_INTERP_TYPES[] = {
    L"Linear", L"Linear Round", L"Linear Round Down", L"Linear Round Up",
    L"Spline", L"Quaternion", L"No Interpolation", L"Use Timeline Default"
};

void EditorTimelineSetPropertyPointValue(long long timelineID, long long objectID,
                                       int property, int point, void* value)
{
    if (!gEditor->isActive()) return;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(timelineID));
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (object && timeline) timeline->SetPropertyPointValue(objectID, property, point, value, 1);
}

void EditorTimelineSetPropertyPointValueArray(long long timelineID, long long objectID,
                                            int property, int point, int count, UNIONDATA32BIT* value)
{
    if (!gEditor->isActive()) return;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(timelineID));
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (object && timeline) timeline->SetPropertyPointValue(objectID, property, point, value, count);
}

void EditorTimelineAddProperty(long long timelineID, long long objectID, int property, bool event)
{
    if (!gEditor->isActive()) return;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(timelineID));
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (object && timeline) timeline->AddProperty(object->getSceneOwner(), objectID, property, event);
}

wchar_t* EditorTimelineGetPropertyInterpType(long long timelineID, long long objectID, int property)
{
    STRINGS::StringCopyWCharArray(sEditorString, 1000, gTIMELINE_INTERP_TYPES[0].c_str());
    if (!gEditor->isActive()) return sEditorString;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(timelineID));
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (object && timeline)
        STRINGS::StringCopyWCharArray(sEditorString, 1000,
            timeline->GetPropertyPointInterpolationType(objectID, property).c_str());
    return sEditorString;
}

void EditorTimelineSetPropertyInterpType(long long timelineID, long long objectID,
                                        int property, const wchar_t* name)
{
    if (!gEditor->isActive()) return;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(timelineID));
    CEditorBaseObject* object = GetObjectInScene(objectID);
    if (object && timeline) {
        std::wstring text(name);
        ETIMELINE_INTERP_TYPES type = static_cast<ETIMELINE_INTERP_TYPES>(0);
        for (int i = 0; i < 8; ++i) {
            if (text == gTIMELINE_INTERP_TYPES[i]) { type = static_cast<ETIMELINE_INTERP_TYPES>(i); break; }
        }
        timeline->SetPropertyPointInterpolationType(objectID, property, type);
    }
}

unsigned int EditorCreateLogicLink(long long guid, unsigned int first, unsigned int second,
                                  unsigned int output, unsigned int input)
{
    if (!gEditor->isActive()) return ~0u;
    if (first == ~0u || guid == -1 || output == ~0u || second == ~0u || input == ~0u) return ~0u;
    CLogicGroup* group = dynamic_cast<CLogicGroup*>(GetObjectInScene(guid));
    if (!group) return ~0u;
    CLogicObject* from = group->GetLogicObjectByIndex(first);
    CLogicObject* to = group->GetLogicObjectByIndex(second);
    if (to && from) return from->AddLogicLink(output, to, input);
    return ~0u;
}

unsigned int EditorGetLogicFuncId(unsigned int sceneID, unsigned int descriptorID, wchar_t* name, bool input)
{
    if (!gEditor->isActive()) return 0;
    if (!name || descriptorID == ~0u) return ~0u;
    CEditorScene* scene = gEditor->GetEditorScene(sceneID);
    if (!scene || !scene->getDescriptorManager()) return ~0u;
    CDescriptor* descriptor = scene->getDescriptorManager()->GetDescriptor(descriptorID);
    if (!descriptor) return ~0u;
    return input ? descriptor->GetInputLogicWrapperIndex(std::wstring(name))
                 : descriptor->GetOutputLogicWrapperIndex(std::wstring(name));
}

void EditorSetObjectPropertyArray(long long guid, int property, int count, UNIONDATA32BIT* data)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return;
    CDescriptor* descriptor = object->getDescriptor();
    if (!descriptor || !descriptor->GetPropertyByIndex(property)) return;
    if (descriptor->GetPropertyByIndex(property)->getVariableType() == static_cast<EVARIABLE_TYPES>(5)) return;
    CUndo* undo = new CUndo(object, property);
    gEditor->addUndo(undo, true);
    descriptor->SetProperty(object, property, data, count);
}

void EditorSetObjectProperty(long long guid, unsigned int property, void* data)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return;
    CDescriptor* descriptor = object->getDescriptor();
    if (!descriptor) return;
    CUndo* undo = new CUndo(object, property);
    gEditor->addUndo(undo, true);
    if (descriptor->GetPropertyByIndex(property) &&
        descriptor->GetPropertyByIndex(property)->getVariableType() == static_cast<EVARIABLE_TYPES>(5)) {
        std::wstring text(static_cast<wchar_t*>(data));
        descriptor->SetProperty(object, property, text.c_str(), text.size());
    } else descriptor->SetProperty(object, property, data, 1);
}

bool EditorDeleteObject(long long guid)
{
    if (!gEditor->isActive()) return false;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (object) {
        if (bGroupUndos) g_pGroupedUndos->AddObjectDeleted(object);
        else {
            CUndo* undo = new CUndo;
            undo->AddObjectDeleted(object);
            gEditor->addUndo(undo, true);
        }
    }
    return true;
}

CEditorBaseObject* cloneObject(unsigned int descriptor, CEditorBaseObject* object, CEditorBaseObject* owner)
{
    if (!object || !object->getSceneOwner()) return NULL;
    CEditorBaseObject* clone = object->getSceneOwner()->CreateObjectByDescriptor(descriptor, object, owner, true);
    if (clone) {
        gEditor->getObjectManager()->EditorObjectCreated(clone);
        gEditor->getObjectManager()->EditorObjectSelected(clone);
        if (bGroupUndos) g_pGroupedUndos->AddNewObject(clone);
        else {
            CUndo* undo = new CUndo;
            undo->AddNewObject(clone);
            gEditor->addUndo(undo, true);
        }
    }
    return clone;
}

void EditorReloadMonster(wchar_t* path)
{
    if (!gEditor->isActive()) return;
    CUnitResourceList::getSingleton()->loadFile(static_cast<ERESOURCE_GROUPS>(1),
        std::wstring(L"MONSTERS"), std::wstring(path), true, NULL);
    TArrayList<CEditorScene*>& scenes = gEditor->getEditorScenes();
    for (unsigned int i = 0; i < scenes.size(); ++i) {
        CDescriptor* descriptor = scenes[i]->GetDescriptorInSceneByName(L"Monster", false);
        CMonsterDescriptor* monster = dynamic_cast<CMonsterDescriptor*>(descriptor);
        if (monster) monster->ReloadMonsters();
    }
}

long long* EditorPollObjects(unsigned int sceneID, unsigned int& count)
{
    long long* output = reinterpret_cast<long long*>(sEditorTmpMemory);
    output[0] = -1;
    count = 0;
    if (!gEditor->isActive()) return output;
    CEditorScene* scene = gEditor->GetEditorScene(sceneID);
    if (!scene || scene->getObjects().size() > 500) return output;
    std::map<long long, CEditorBaseObject*>& objects = scene->getObjects();
    for (std::map<long long, CEditorBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
        output[count++] = it->first;
    output[count++] = -1;
    return output;
}

#include "Layout.h"
#include "FileUtilities.h"

static const std::wstring KAutomapTileName[34] = {
    L"right angle corner",
    L"straight wall",
    L"diag bottomleft-topright",
    L"convex corner",
    L"floor",
    L"bottom-right diagonal floor",
    L"bottom-left diagonal floor",
    L"bridge ns 2",
    L"double-bridge ns2",
    L"bridge ns2 offset 1",
    L"bridge ns2",
    L"doublewide bridge",
    L"top-left diagonal floor",
    L"diagonal bridge",
    L"top-right diagonal floor",
    L"pet icon",
    L"player icon",
    L"triple exit",
    L"triple-long bridge",
    L"stairsup",
    L"stairsdown",
    L"question",
    L"exclamation",
    L"exclamation gray",
    L"merchant",
    L"question gray",
    L"fixed map (static background)",
    L"right angle corner rotated",
    L"enchanter",
    L"gemrecover",
    L"gambler",
    L"transmuter",
    L"itemrecover",
    L"waypoint"
};

long long EditorPollObjectIDByIndex(unsigned int sceneID, unsigned int index)
{
    if (!gEditor->isActive()) return -1;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    CEditorScene* scene = gEditor->GetEditorScene(sceneID);
    if (!scene) return -1;
    CEditorObjectManager::ObjectMap* objects = manager->getObjects();
    if (!objects || objects->empty()) return -1;
    if (index == 0) iteratorOfObjectsInScene = objects->begin();
    while (iteratorOfObjectsInScene != objects->end()) {
        CEditorBaseObject* object = iteratorOfObjectsInScene->second;
        if (object->getSceneOwner() == scene) {
            long long result = object->getGuid();
            ++iteratorOfObjectsInScene;
            return result;
        }
        ++iteratorOfObjectsInScene;
    }
    return -1;
}

bool IsA(wchar_t* type, wchar_t* parent)
{
    if (!gEditor->isActive()) return false;
    return gEditor->getResourceManager()->ISA(std::wstring(type), std::wstring(parent));
}

wchar_t* EditorGetDebugOutput()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    std::wstring result(EMPTY_WSTRING);
    if (!gEditor->isActive()) return NULL;
    unsigned int count = gEditor->m_sUnknown1A8.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, gEditor->m_sUnknown1A8.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    gEditor->m_sUnknown1A8 = L"";
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

wchar_t* EditorAutomapTiles()
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result(EMPTY_WSTRING);
    for (unsigned int i = 0; i < 34; ++i) {
        result += KAutomapTileName[i];
        if (i < 33) result += L",";
    }
    unsigned int count = result.size();
    if (count < 2000000) {
        // Preserve the original two-byte copy length on the Linux build.
        unsigned int bytes = count * 2;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

float* EditorGetObjectSnap(long long guid, unsigned int& count, bool position, bool orientation, bool scale)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    count = 0;
    if (!gEditor->isActive()) return NULL;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return NULL;
    iSnap* snap = dynamic_cast<iSnap*>(object);
    if (!snap) return NULL;
    TArrayList<float>* values = snap->getSnapValues(static_cast<ESNAP_TYPES>(position ? 0 : orientation ? 1 : 2));
    if (!values) return NULL;
    count = values->size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, &(*values)[0], bytes);
        *reinterpret_cast<unsigned int*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<float*>(sEditorTmpMemory);
}

int EditorSaveScene(unsigned int sceneID, wchar_t* filename, bool selected)
{
    if (!gEditor->isActive()) return 0;
    CEditorScene* scene = gEditor->GetEditorScene(sceneID);
    if (!scene) return 1;
    return scene->saveScene(std::wstring(filename), selected ? gEditor->getObjectManager()->getSelectedObjects() : NULL);
}

void reloadEditorLayoutLinks()
{
    if (!gEditor->isActive()) return;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (!manager) return;
    CEditorObjectManager::ObjectMap* objects = manager->getObjects();
    bool first = true;
    for (CEditorObjectManager::ObjectMap::iterator it = objects->begin(); it != objects->end(); ++it) {
        CLayout* layout = dynamic_cast<CLayout*>(it->second);
        if (!layout) continue;
        if (first) layout->removeAllCloneableObjects();
        std::wstring filename(layout->getLoadedFilename());
        if (FILESYSTEM::FileExists(filename)) layout->loadLayoutFile(filename, false, NULL, false, true, 0);
        first = false;
    }
}

void EditorSetIngameRes(unsigned int width, unsigned int height)
{
    if (!gEditor->isActive()) return;
    gEditor->getSettings()->SetInt(KSETTINGS_RES_WIDTH, width);
    gEditor->getSettings()->SetInt(KSETTINGS_RES_HEIGHT, height);
    gEditor->getSettings()->SetInt(KSETTINGS_WIN_WIDTH, width);
    gEditor->getSettings()->SetInt(KSETTINGS_WIN_HEIGHT, height);
    gEditor->getSettings()->SetFloat(KSETTINGS_XRATIO, float(width) * (1.0f / 1024.0f));
    gEditor->getSettings()->SetFloat(KSETTINGS_YRATIO, float(height) / 768.0f);
    gEditor->getEditorResourceManager()->updateAspectRatio(float(width), float(height));
    gEditor->getEditorResourceManager()->getGameClient()->rescaleUI();
}

long long* EditorGetObjectsCreatedThisRender(unsigned int& count)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    count = 0;
    if (!gEditor->isActive()) return NULL;
    count = gEditor->getObjectManager()->getCreatedObjects().size();
    if (!count) return NULL;
    long long* ids = static_cast<long long*>(Ogre::NedAllocImpl::allocBytes(static_cast<size_t>(count) * 8, NULL, 0, NULL));
    for (unsigned int i = 0; i < count; ++i)
        ids[i] = gEditor->getObjectManager()->getCreatedObjects()[i]->getGuid();
    if (count < 500000) {
        unsigned int bytes = count * 8;
        std::memcpy(sEditorTmpMemory, ids, bytes);
        *reinterpret_cast<long long*>(sEditorTmpMemory + bytes) = 0;
    }
    if (ids) Ogre::NedAllocImpl::deallocBytes(ids);
    gEditor->getObjectManager()->getCreatedObjects().clear();
    return reinterpret_cast<long long*>(sEditorTmpMemory);
}

bool EditorFileExists(wchar_t* filename)
{
    if (!gEditor->isActive()) return false;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(std::wstring(filename), info, false, true, false);
    return info.m_bExists;
}

unsigned int EditorUpdate(int event)
{
    if (!gEditor->isActive() || !gEditor->getObjectManager()) return 0;
    gEditor->getObjectManager()->EditorUpdateBeginning();
    unsigned int oldCount = gEditor->getObjectManager()->getSelectedObjects()->size();
    long long oldGuid = -1;
    if (oldCount == 1) oldGuid = (*gEditor->getObjectManager()->getSelectedObjects())[0]->getGuid();
    gEditor->getEditorResourceManager()->editorUpdateSceneOnce(event);
    unsigned int result = 0;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager) {
        unsigned int count = manager->getSelectedObjects()->size();
        bool changed = count == 1 && (*manager->getSelectedObjects())[0]->getGuid() != oldGuid;
        if (oldCount != count || changed) result = 1;
        if (manager->getChanged()) {
            manager->clearChanged();
            result |= 2;
            manager = gEditor->getObjectManager();
        }
        if (manager->getCreatedObjects().size()) result |= 5;
    }
    if (gEditor->m_bUnknown164) {
        gEditor->m_bUnknown164 = false;
        gEditor->getObjectManager()->getCreatedObjects().clear();
        result |= 8;
        manager = gEditor->getObjectManager();
    }
    manager->EditorUpdateEnd();
    return result;
}

wchar_t* EditorGetAnimationNameByPath(long long guid, wchar_t* path)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    std::wstring result(EMPTY_WSTRING);
    if (!gEditor->isActive()) return NULL;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return NULL;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return NULL;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    if (!model) return NULL;
    result = STRINGS::StringConvertToWide(model->getAnimationNameByPath(std::wstring(path)));
    unsigned int count = result.size();
    if (count < 1000000) {
        unsigned int bytes = count * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

float EditorGetModelAnimationLengthSeconds(long long guid, char* name)
{
    *reinterpret_cast<unsigned int*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return -1.0f;
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (!object) return -1.0f;
    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (!model) {
        CCharacter* character = dynamic_cast<CCharacter*>(object);
        if (!character) return -1.0f;
        model = static_cast<CGenericModel*>(character->getUnitModel());
    }
    // The original exported char* parameter is passed to the wchar_t overload.
    if (!model || !model->animationExists(STRINGS::StringConvertToNarrow(reinterpret_cast<wchar_t*>(name)))) return -1.0f;
    return model->getAnimationLengthSeconds(STRINGS::StringConvertToNarrow(reinterpret_cast<wchar_t*>(name)));
}

#include <cstdlib>
#include <unistd.h>
#include "CameraControl.h"
#include "CameraShake.h"
#include "DataGroup.h"
#include "EmptyStrings.h"
#include "FileUtilities.h"
#include "GraphManager.h"
#include "Layout.h"
#include "ParticleWrapper.h"
#include "ParticleTechWrapper.h"
#include "RoomPiece.h"
#include "RoomPieceDataInformation.h"
#include "SpawnClassParser.h"
#include "UnitResourceList.h"
#include "Utilities.h"
#include "UTFConversion.h"

namespace ParticleUniverse { class ParticleSystem { public: void _update(float elapsed); }; }
static int gGlobalRandomScrubKey = 3473422;
extern bool convertRoomPieces(CDataGroup*, TArrayList<CRoomPieceDataInformation::CRoomPieceCoreData*>&);

void rollRoomPiece(long long guid)
{
    if (!gEditor->isActive()) return;
    CEditorBaseObject* object = GetObjectInScene(guid);
    CRoomPiece* piece = dynamic_cast<CRoomPiece*>(object);
    if (!piece) return;
    long long visualGuid = piece->m_iVisualIndex_140;
    void* visual = piece->m_pRoomPieceName;
    if (visualGuid != -1 && visual)
    {
        const char* core = *reinterpret_cast<const char**>(static_cast<char*>(visual) + 0x10);
        if (core && core[0x31])
        {
            TArrayList<CEditorBaseObject*>* selection = gEditor->getObjectManager()->getSelectedObjects();
            if (selection->find(object) == -1) return;
            piece->selectNewVisualIndex();
            visualGuid = piece->m_iVisualIndex_140;
        }
    }
    piece->setRoomPieceGuid(visualGuid);
}

void EditorToggleDisplayCollision()
{
    if (!gEditor->isActive() || !gEditor->getResourceManager()) return;
    int value = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DISPLAY_COLLISION);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_DISPLAY_COLLISION, value != 1);
    CEditorScene* scene = gEditor->GetEditorScene(L"Layout");
    if (!scene) return;
    TArrayList<CEditorBaseObject*>* objects = scene->GetObjectsCreatedByADescriptor(L"Room Piece");
    for (unsigned int i = 0; i < objects->size(); ++i)
    {
        CRoomPiece* piece = dynamic_cast<CRoomPiece*>((*objects)[i]);
        if (piece) piece->setRoomPieceGuid(piece->m_iVisualIndex_140);
    }
}

void EditorTestCameraShake(wchar_t* name, float duration)
{
    if (!gEditor->isActive() || !name) return;
    std::wstring shakeName(name);
    CCameraShake* shake = new CCameraShake(shakeName, Ogre::Vector3(0.0f, 1.0f, 0.0f), duration);
    CCameraControl* camera = gEditor->getResourceManager()->getCameraControl();
    TSafePointer<CCameraShake>* reference = OGRE_NEW_T(TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL)();
    reference->setObject(shake);
    reinterpret_cast<TArrayList<TSafePointer<CCameraShake>*>*>(camera->m_Unknown58)->add(reference);
}

void EditorPlaySound(wchar_t* name, float volume, float minimumDistance, float maximumDistance)
{
    if (!gEditor->isActive()) return;
    CGameClient* client = gEditor->getEditorResourceManager()->getGameClient();
    std::wstring path = FILESYSTEM::CleanPath(name);
    std::wstring local = FILESYSTEM::GetLocalPath();
    std::string localUtf8 = STRINGS::StringConvertToUTF8(local);
    chdir(localUtf8.c_str());
    if (!client) return;
    CSoundManager* manager = CMasterResourceManager::getSingleton()->m_pSoundManager;
    if (!manager) return;
    CSoundInstance* sound = manager->createSound(path, static_cast<SOUND_TYPE>(3), false, minimumDistance, maximumDistance);
    if (sound)
    {
        manager->playSound(sound, NULL, -1, volume);
        manager->releaseSound(sound);
    }
}

void EditorReloadAllAssets()
{
    if (!gEditor->isActive()) return;
    if (CMasterResourceManager::getSingleton()->m_pParticlePreloader)
        CMasterResourceManager::getSingleton()->m_pParticlePreloader->ReloadEditorParticles();
    Ogre::TextureManager::getSingleton().setPreferredBitDepths(0, 1, true);
    Ogre::TextureManager::getSingleton().reloadAll(true);
    CGameClient* client = gEditor->getEditorResourceManager()->getGameClient();
    if (client) client->reloadSoundBankData();
    CMissilePreloader::getSinglelton()->reloadMissiles();
    CQuestManager::getSingleton()->reloadQuests();
    CUnitThemes::getSingleton()->reload();
    if (CMasterResourceManager::getSingleton()->m_effectGroups)
    {
        CEffectGroupManager* groups = CMasterResourceManager::getSingleton()->m_effectGroups;
        CSets::getSingleton()->reload(groups);
    }
    CRecipes::getSingleton()->reload();
    CSpawnClassParser::getSingleton()->reloadFromDirectory(L"media/spawnclasses/");
    CCinematics::getSingleton()->reload();
    CMasterResourceManager::getSingleton()->m_effectGroups->reload();
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (!manager) return;
    CEditorObjectManager::ObjectMap* objects = manager->getObjects();
    bool first = true;
    for (CEditorObjectManager::ObjectMap::iterator it = objects->begin(); it != objects->end(); ++it)
    {
        CLayout* layout = dynamic_cast<CLayout*>(it->second);
        if (!layout) continue;
        if (first) layout->removeAllCloneableObjects();
        std::wstring filename = layout->getLoadedFilename();
        if (FILESYSTEM::FileExists(filename)) layout->loadLayoutFile(filename, false, NULL, false, true, 0);
        first = false;
    }
}

float EditorTimelineSetPercentDone(long long guid, float percent)
{
    if (!gEditor->isActive()) return 0.0f;
    CTimeline* timeline = dynamic_cast<CTimeline*>(GetObjectInScene(guid));
    if (!timeline) return 0.0f;
    float result = timeline->SetTimelinePercentDone(percent);
    if (!gEditor->getResourceManager() || !CMasterResourceManager::getSingleton()->m_pParticlePreview ||
        !CMasterResourceManager::getSingleton()->m_pParticlePreview->paused) return result;
    UTILITIES::setSeed(gGlobalRandomScrubKey);
    float duration = timeline->m_fSetTimelineDuration;
    TArrayList<CEditorBaseObject*>* particles = timeline->getSceneOwner()->GetObjectsCreatedByADescriptor(L"Particle");
    if (particles)
        for (unsigned int i = 0; i < particles->size(); ++i)
        {
            CParticleTechWrapper* particle = dynamic_cast<CParticleTechWrapper*>((*particles)[i]);
            if (!particle || !particle->isPlaying()) continue;
            particle->stop();
            particle->start();
            float elapsed = percent * duration;
            while (elapsed > 0.01666666753590107f)
            {
                particle->m_pParticleSystem->_update(0.01666666753590107f);
                elapsed -= 0.01666666753590107f;
            }
            particle->m_pParticleSystem->_update(elapsed);
        }
    return result;
}

void EditorConvertLayoutToNewTileset(const wchar_t* tilesetName, const wchar_t* filename)
{
    if (!gEditor->isActive()) return;
    std::wstring tileset(tilesetName), path(filename);
    CRoomPieceDataInformation* information = CRoomPieceDataInformation::getSingleton();
    TArrayList<CRoomPieceDataInformation::CRoomPieceCoreData*> pieces(10);
    information->getRoomPieceCoreDataByTileset(STRINGS::StringUpper(tileset), pieces);
    if (pieces.size())
    {
        CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
        group.LoadFile(path, NULL);
        CDataGroup* objects = group.GetDataGroupByName(L"OBJECTS", false);
        if (objects && convertRoomPieces(objects, pieces)) group.SaveToFile(path);
    }
}

wchar_t* EditorGetUnitsByUnittype(char* typeName)
{
    *reinterpret_cast<wchar_t*>(sEditorTmpMemory) = 0;
    if (!gEditor->isActive()) return NULL;
    std::wstring result = EMPTY_WSTRING;
    UNITTYPES::EUNITTYPES type = gEditor->getResourceManager()->getUnitTypeByName(reinterpret_cast<wchar_t*>(typeName));
    if (static_cast<unsigned int>(type) != 22)
    {
        TArrayList<CDataGroup*> groups(10);
        gEditor->getResourceManager()->getMasterResourceList()->getDataGroupsByUnitType(type, groups);
        for (unsigned int i = 0; i < groups.size(); ++i)
            result += groups[i]->GetDataValue(L"NAME", EMPTY_WSTRING) + L",";
    }
    unsigned int length = result.length();
    if (length <= 999999)
    {
        unsigned int bytes = length * 4;
        std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
        *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}

void EditorFireEvent(unsigned int sceneID, long long guid, unsigned int event)
{
    if (!gEditor->isActive() || event > 13) return;
    if (sceneID != 0xffffffffu)
    {
        CEditorScene* scene = gEditor->GetEditorScene(sceneID);
        if (scene) scene->fireEvent(static_cast<EEDITOR_EVENTS>(event), guid);
    }
    switch (event)
    {
    case 2: CMasterResourceManager::getSingleton()->m_pRoomPieceInformation->LoadRoomData(); break;
    case 4:
    {
        CEditorObjectManager* manager = gEditor->getObjectManager();
        manager->ClearSelectedObjects();
        CEditorObjectManager::ObjectMap* objects = manager->getObjects();
        for (CEditorObjectManager::ObjectMap::iterator it = objects->begin(); it != objects->end(); ++it)
        {
            CRoomPiece* piece = dynamic_cast<CRoomPiece*>(it->second);
            if (!piece || !piece->m_bCollisionEnabled) continue;
            // This primary-vtable entry returns the collision mesh pointer; the shared interface is still partial.
            typedef void* (*GetMesh)(CRoomPiece*);
            void** vtable = *reinterpret_cast<void***>(piece);
            if (reinterpret_cast<GetMesh>(vtable[0x1e0 / sizeof(void*)])(piece)) manager->EditorObjectSelected(it->second);
        }
        break;
    }
    case 5:
    case 6:
        if (gEditor->getResourceManager() && CMasterResourceManager::getSingleton()->m_pParticlePreview)
            CMasterResourceManager::getSingleton()->m_pParticlePreview->paused = event == 5;
        if (event == 6) gGlobalRandomScrubKey = std::rand();
        break;
    case 7: gEditor->m_iUnknown68 = 0x3a; break;
    case 8: gEditor->m_iUnknown68 = 2; break;
    case 9: gEditor->m_iUnknown68 = 8; break;
    case 10: gEditor->m_iUnknown68 = 0x10; break;
    case 11: gEditor->m_iUnknown68 = 0x20; break;
    case 12: CGraphManager::getSingleton()->reload(); break;
    case 13: gEditor->getGameClient()->togglePlayerLight(); break;
    }
}

wchar_t* EditorGetListOfItems(unsigned int sceneID, long long guid, unsigned int propertyID, wchar_t* separator)
{
    STRINGS::StringCopyWCharArray(sEditorString, 1000, EMPTY_WSTRING.c_str());
    if (!gEditor->isActive()) return sEditorString;
    *reinterpret_cast<wchar_t*>(sEditorTmpMemory) = 0;
    CEditorScene* scene = gEditor->GetEditorScene(sceneID);
    if (!scene) return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
    CEditorBaseObject* object = GetObjectInScene(guid);
    if (object && object->getDescriptor())
    {
        std::vector<std::wstring> values;
        object->getDescriptor()->GetPropertyListOfValues(object, propertyID, values);
        std::wstring result = EMPTY_WSTRING, delimiter(separator);
        for (unsigned int i = 0; i < values.size(); ++i)
            if (i) result = result + delimiter + values[i]; else result = values[i];
        unsigned int length = result.length();
        if (length <= 999999)
        {
            unsigned int bytes = length * 4;
            std::memcpy(sEditorTmpMemory, result.c_str(), bytes);
            *reinterpret_cast<wchar_t*>(sEditorTmpMemory + bytes) = 0;
        }
    }
    return reinterpret_cast<wchar_t*>(sEditorTmpMemory);
}
