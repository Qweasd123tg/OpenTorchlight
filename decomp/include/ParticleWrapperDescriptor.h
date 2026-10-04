#ifndef PARTICLEWRAPPERDESCRIPTOR_H
#define PARTICLEWRAPPERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CParticleWrapperDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CParticleWrapperDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CParticleWrapperDescriptor();


    static void Set_setFixedLifeTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFixedLifeTime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWorldVisualScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldVisualScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWorldScaleTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldScaleTime(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWorldScaleVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWorldScaleVelocity(CEditorBaseObject* object, unsigned int& count);
};

#endif
