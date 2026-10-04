#ifndef GAMESTATECONTROLLERDESCRIPTOR_H
#define GAMESTATECONTROLLERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "GameStateController.h"

class CGameStateControllerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CGameStateControllerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CGameStateControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CGameStateController*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPlayerInvulnerable(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGameStateController*>(object)->setPlayerInvulnerable(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getPlayerInvulnerable(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CGameStateController*>(object)->getPlayerInvulnerable();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setGameState(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGameStateController*>(object)->setGameState(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getGameState(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CGameStateController*>(object)->getGameState();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int getGameStateIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getGameStateStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setHelpTip(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGameStateController*>(object)->setHelpTip(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getHelpTip(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CGameStateController*>(object)->getHelpTip();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int getTipIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getTipStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
