#ifndef MONSTERDESCRIPTOR_H
#define MONSTERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CMonsterDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CMonsterDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    void ReloadMonsters();
    CMonsterDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_createNewCharacter(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitDataName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getMonsterIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getMonsterStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setModelPathDummy(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getModelPath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMonsterNoTarget(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMonsterNoTarget(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBroadcastAllHPEvents(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBroadcastAllHPEvents(CEditorBaseObject* object, unsigned int& count);
    static void Set_setInvincible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getInvincible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPathToFollowByName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPathNameToFollow(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getPathIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getPathStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setShouldLoopOnPath(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShouldLoopOnPath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMeshVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMeshVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCanBeTargeted(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCanBeTargeted(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getScaleFloat(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDisableWandering(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDisableWandering(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDontDropGold(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDontDropGold(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDontDropTreasure(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDontDropTreasure(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAnimationPlaying(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationPlaying(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetAnimationIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetAnimationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setEditorThemeID(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEditorThemeID(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getThemeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getThemeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setAnimationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAnimationLoop(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationLoop(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeChestMesh(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeChestMesh(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeBootsMesh(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeBootsMesh(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeGlovesMesh(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeGlovesMesh(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeHelmMesh(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeHelmMesh(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeShoulderMesh(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeShoulderMesh(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeChestTexture(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeChestTexture(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeBootsTexture(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeBootsTexture(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWardrobeGlovesTexture(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWardrobeGlovesTexture(CEditorBaseObject* object, unsigned int& count);
};

#endif
