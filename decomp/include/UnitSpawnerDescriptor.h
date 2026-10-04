#ifndef UNITSPAWNERDESCRIPTOR_H
#define UNITSPAWNERDESCRIPTOR_H

#include "ShapeDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CUnitSpawnerDescriptor : public CShapeDescriptor
{
public:
    virtual ~CUnitSpawnerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject*);
    virtual void descriptorSceneLoaded(CEditorScene*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CUnitSpawnerDescriptor();

    unsigned char m_gap170[0x8] __attribute__((aligned(8)));
    bool m_bUnknown178;
    bool m_bUnknown179;
    bool m_bUnknown17A;
    bool m_bUnknown17B;
    bool m_bUnknown17C;
    bool m_bUnknown17D;
    bool m_bUnknown17E;
    unsigned char m_gap17F[0x1];
    int m_iUnknown180;
    unsigned char m_gap184[0x4] __attribute__((aligned(4)));
    int m_iUnknown188;
    unsigned char m_gap18C[0x4] __attribute__((aligned(4)));
    int m_iUnknown190;
    int m_iUnknown194;
    int m_iUnknown198;
    int m_iUnknown19C;
    unsigned char m_gap1A0[0x4] __attribute__((aligned(4)));
    int m_iUnknown1A4;
    unsigned char m_gap1A8[0x8] __attribute__((aligned(8)));
    long long m_Unknown1B0;
    long long m_Unknown1B8;
    bool m_bUnknown1C0;
    unsigned char m_gap1C1[0x1];
    bool m_bUnknown1C2;
    unsigned char m_gap1C3[0x1];
    bool m_bUnknown1C4;
    unsigned char m_gap1C5[0x6b];
    bool m_bUnknown230;

    static void Set_setNumberOfUnitsToCreate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNumberOfUnitsToCreate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxNumMonstersAllowedAtATime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxNumMonstersAllowedAtATime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUpdateInEditor(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUpdateInEditor(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSpawnOnCreate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSpawnOnCreate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTargetPlayer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTargetPlayer(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSpawnDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSpawnDuration(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPulseNumber(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPulseNumber(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSpawnInCenter(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSpawnInCenter(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRequiresLOS(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRequiresLOS(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMustSpawn(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMustSpawn(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseSpawnAnimation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseSpawnAnimation(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSnapToGround(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSnapToGround(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnitsGiveXP(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitsGiveXP(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnitsGiveLoot(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitsGiveLoot(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSpawnLevelOverrideDelta(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSpawnLevelOverrideDelta(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDestroyMeshOnDeath(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDestroyMeshOnDeath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCategory(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCategory(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setResourceSpawn(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getResourceSpawn(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetResourceStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
