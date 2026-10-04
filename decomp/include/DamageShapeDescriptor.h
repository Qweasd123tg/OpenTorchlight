#ifndef DAMAGESHAPEDESCRIPTOR_H
#define DAMAGESHAPEDESCRIPTOR_H

#include "ShapeDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CDamageShapeDescriptor : public CShapeDescriptor
{
public:
    virtual ~CDamageShapeDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CDamageShapeDescriptor();

    unsigned char m_gap170[0x14] __attribute__((aligned(4)));
    int m_iUnknown184;
    unsigned char m_gap188[0x4] __attribute__((aligned(4)));
    int m_iUnknown18C;
    unsigned char m_gap190[0x4] __attribute__((aligned(4)));
    int m_iUnknown194;
    int m_iUnknown198;
    int m_iUnknown19C;
    int m_iUnknown1A0;
    bool m_bUnknown1A4;
    bool m_bUnknown1A5;
    unsigned char m_gap1A6[0x1];
    bool m_bUnknown1A7;
    bool m_bUnknown1A8;
    unsigned char m_gap1A9[0x3];
    int m_iUnknown1AC;
    int m_iUnknown1B0;
    int m_iUnknown1B4;
    int m_iUnknown1B8;
    unsigned char m_gap1BC[0x3c] __attribute__((aligned(4)));
    int m_iUnknown1F8;

    static void Set_setDamageType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDamageType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetDamageTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetDamageTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setDamageOnlyUnitTypeByUnitTypeLoadIndex(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDamageOnlyUnitTypeLoadIndex(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getUnitTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getUnitTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setAlignmentTypAllowedToDamage(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAlignmentTypAllowedToDamage(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getAlignmentIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getAlignmentStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setUpdateInEditor(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUpdateInEditor(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDamageOverTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDamageOverTime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTargetOnlyDead(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTargetOnlyDead(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTotalNumberOfTargets(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTotalNumberOfTargets(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMinDamage(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMinDamage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxDamage(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxDamage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLoopsForEver(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopsForEver(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNumLoops(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNumLoops(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTimer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTimer(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDelayTimer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDelayTimer(CEditorBaseObject* object, unsigned int& count);
};

#endif
