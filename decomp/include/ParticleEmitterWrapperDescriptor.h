#ifndef PARTICLEEMITTERWRAPPERDESCRIPTOR_H
#define PARTICLEEMITTERWRAPPERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CParticleEmitterWrapperDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CParticleEmitterWrapperDescriptor();
    virtual void deleteNotification();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CParticleEmitterWrapperDescriptor();


    static void Set_setEmitterType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEmitterType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetEmitterTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetEmitterTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setParticleDirection(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleDirection(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnifiedScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnifiedScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropScaleOnLaunch(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropScaleOnLaunch(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropDepth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropDepth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropAngleOfRelease(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropAngleOfRelease(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropMass(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropMass(CEditorBaseObject* object, unsigned int& count);
    static void Set_setKeepLocal(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getKeepLocal(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropNonExpiring(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropNonExpiring(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDelayOccursFirst(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDelayOccursFirst(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropRepeatRate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropRepeatRate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropTimeToLive(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropTimeToLive(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropDuration(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropEmissionRate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropEmissionRate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNumberOfLoops(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNumberOfLoops(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEmitOverDistance(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEmitOverDistance(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynPropChanceOfRelease(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynPropChanceOfRelease(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMinLineIncrement(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMinLineIncrement(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxLineIncrement(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxLineIncrement(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxLineDeviation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxLineDeviation(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPositionEnd(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPositionEnd(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBoxWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBoxWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBoxHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBoxHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBoxDepth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBoxDepth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMinRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMinRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCircleStep(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCircleStep(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCircleFixedSize(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCircleFixedSize(CEditorBaseObject* object, unsigned int& count);
};

#endif
