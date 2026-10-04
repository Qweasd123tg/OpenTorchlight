#ifndef SOUNDOBJECTDESCRIPTOR_H
#define SOUNDOBJECTDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "SoundObject.h"

class CSoundObjectDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CSoundObjectDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void descriptorSceneDeactivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CSoundObjectDescriptor();


    static void Set_setSoundStartsOnActivated(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSoundStartsOnActivated(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSoundObject*>(object)->getSoundStartsOnActivated();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setEnvironmental(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnvironmental(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSoundObject*>(object)->getEnvironmental();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setVolume(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVolume(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSoundBankCategory(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSoundObject*>(object)->setSoundBankCategory(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getSoundBankCategory(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CSoundObject*>(object)->getSoundBankCategory();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int GetSoundCategoryIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetSoundCategoryStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setSoundBankNameIndex(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSoundObject*>(object)->setSoundBankNameIndex(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_getSoundBankNameIndex(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(unsigned int);
        gUnionOf32BitData[0].m_uValue = static_cast<CSoundObject*>(object)->getSoundBankNameIndex();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int GetSoundDataIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetSoundDataStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setSoundBankGuidByString(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSoundBankGuidAsString(CEditorBaseObject* object, unsigned int& count);
};

#endif
