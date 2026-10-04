#ifndef PARTICLETECHWRAPPERDESCRIPTOR_H
#define PARTICLETECHWRAPPERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CParticleTechWrapperDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CParticleTechWrapperDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void descriptorSceneDeactivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CParticleTechWrapperDescriptor();

    int m_iUnknown170;
    int m_iUnknown174;
    bool m_bUnknown178;
    unsigned char m_gap179[0x37];
    void* m_pUnknown1B0;
    void* m_pUnknown1B8;
    unsigned char m_gap1C0[0x8] __attribute__((aligned(8)));
    int m_iUnknown1C8;
    bool m_bUnknown1CC;
    bool m_bUnknown1CD;
    unsigned char m_gap1CE[0x2];
    int m_iUnknown1D0;
    int m_iUnknown1D4;

    static void Set_setRenderType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRenderType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetParticleRenderIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetParticleRenderStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setWorldVisualScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldVisualScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWorldScaleTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldScaleTime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWorldScaleVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldScaleVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setFixedLifeTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFixedLifeTime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAlwaysUp(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAlwaysUp(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNoCull(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNoCull(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAsLight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getIsLight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSorts(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSorts(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSortIndex(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSortIndex(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetSortIndexIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetSortIndexStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setDepthBias(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDepthBias(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVisualParticleQuota(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVisualParticleQuota(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTexturePath(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTexturePath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setParticleRenderStyle(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleRenderStyle(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetParticleRenderStyleIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetParticleRenderStyleStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setModelPath(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getModelPath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDepthCheck(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDepthCheck(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBillboardRotationType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBillboardRotationType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetBillboardRotationTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetBillboardRotationTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setBillboardOrigin(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBillboardOrigin(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetBillboardOriginTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetBillboardOriginTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRibbonLength(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRibbonLength(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRibbonWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRibbonWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRibbonMaxChains(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRibbonMaxChains(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRibbonEndFade(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRibbonEndFade(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRibbonLocalTrail(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRibbonLocalTrail(CEditorBaseObject* object, unsigned int& count);
    static void Set_setFlipbookWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFlipbookWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setFlipbookHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFlipbookHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUScroll(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUScroll(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVScroll(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVScroll(CEditorBaseObject* object, unsigned int& count);
};

#endif
