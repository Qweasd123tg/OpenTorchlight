#ifndef EDITORDLL_H
#define EDITORDLL_H

#include <cstddef>

class CEditorBaseObject;

// Partial: the editor API (exported functions). EditorBaseObject.cpp defines
// the ones declared here; the rest live in EditorDLL.cpp.
CEditorBaseObject* GetObjectInScene(long long guid);
int EditorGetEdtiorLevelDepth();
void EditorSetEditorLevelDepth(int depth);
void EditorSetEditorCharacterLevel(int level);
void EditorSetEditorRunGodded(bool godded);
void EditorSetEditorAiFreeze(bool freeze);
void EditorSetEditorLevelPopulate(bool populate);
void EditorSetEditorLevelPopulateChampions(bool populate);
void EditorSetEditorLevelCreatePet(bool create);
void EditorSetUseTempStartPos(bool use);
void EditorSetTempStartPos(float x, float y, float z);
bool EditorObjectExists(long long guid);
void EditorFlyToObject(long long guid);
long long EditorGetObjectSelectedByIndex(unsigned int index);
void EditorSetObjectParent(long long guid, long long parentGuid);
long long EditorGetObjectParent(long long guid);
int EditorGetObjectDescriptorID(long long guid);
bool EditorGetFlagState(unsigned int flag);
void EditorParticleMovementConfig(float& a, float& b, bool set);
void EditorMakeGuid();
void EditorSetModPriority(const wchar_t* mod, int priority);


class CLogicGroup;
class CTimeline;
class CUndo;
extern wchar_t sEditorString[];
extern CUndo* g_pGroupedUndos;
static bool bGroupUndos;
void* EditorGetObjectProperty(long long objectID, unsigned int propertyID);
CLogicGroup* GetLogicGroupByID(long long guid);
CTimeline* GetTimeline(long long guid);

#endif
