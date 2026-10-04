#ifndef CINEMATICDESCRIPTOR_H
#define CINEMATICDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CCinematicDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CCinematicDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCinematicDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setCinematicName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCinematicName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getCinematicIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getCinematicStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
