#include "Cinematics.h"
#include "Editor.h"
#include "EditorObjectManager.h"
#include "EffectGroupManager.h"
#include "FileSystem.h"
#include "MasterResourceManager.h"
#include "MissilePreloader.h"
#include "QuestManager.h"
#include "Recipes.h"
#include "UnitThemes.h"


// Imported source candidates; historical status is not fresh acceptance.
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
