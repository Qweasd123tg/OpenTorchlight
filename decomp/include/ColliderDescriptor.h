#ifndef COLLIDERDESCRIPTOR_H
#define COLLIDERDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CColliderDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CColliderDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CColliderDescriptor(const wchar_t* name);


    static void Set_setCollisionType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCollisionType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetParticleCollisionTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetParticleCollisionTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setIntersectionType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getIntersectionType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetParticleIntersectionTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetParticleIntersectionTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setFriction(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFriction(CEditorBaseObject* object, unsigned int& count);
    static void Set_setBouncyness(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBouncyness(CEditorBaseObject* object, unsigned int& count);
};

#endif
