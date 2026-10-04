#ifndef FORCEAFFECTORDESCRIPTOR_H
#define FORCEAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CForceAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CForceAffectorDescriptor();
    CForceAffectorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setForceApplication(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getForceApplication(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetForceApplicationIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetForceApplicationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setForceVector(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getForceVector(CEditorBaseObject* object, unsigned int& count);
};

#endif
