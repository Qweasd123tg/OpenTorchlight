#ifndef EDITORBASEOBJECT_H
#define EDITORBASEOBJECT_H

#include <string>

#include "RunicCore.h"

class CDescriptor;
class CEditorScene;
class CPositionableObject;

// Flags of AddBaseObjectFlag/HasBaseObjectFlag (both are empty in the shipped
// build). Enumerator names are ours, from Descriptor.cpp's use.
enum EEDITOROBJECT_FLAG
{
    EDITOROBJECT_FLAG_DONT_SAVE = 1,
    EDITOROBJECT_FLAG_SAVED = 4
};

// Base of every object placed by the editor (logic objects, units, props):
// identity (guid, parent guid), owning scene and the descriptor that created it.
class CEditorBaseObject : public CRunicCore
{
public:
    CEditorBaseObject();
    virtual ~CEditorBaseObject();

    virtual void setParentPositionableObject(CPositionableObject* parent) { m_pParentPositionableObject = parent; }
    virtual void setParentGuid(long long guid) { m_iParentGuid = guid; }
    virtual void SetName(const std::wstring& name) { m_sName = name; }
    virtual void SetSceneOwner(CEditorScene* scene) { m_pSceneOwner = scene; }
    virtual void BroadcastEvent(unsigned int event);
    virtual void removedFromSceneAndAddedToCache() {}

    void AddBaseObjectFlag(EEDITOROBJECT_FLAG flag);
    void RemoveBaseObjectFlag(EEDITOROBJECT_FLAG flag);
    bool HasBaseObjectFlag(EEDITOROBJECT_FLAG flag);
    bool isChildOfObject(long long guid);
    void setGuid(long long guid);
    void calculateParentHierarchyHashCode();

    long long getGuid() const { return m_iGuid; }
    long long getParentGuid() const { return m_iParentGuid; }
    long long getOriginalGuid() const { return m_iOriginalGuid; }
    void setOriginalGuid(long long guid) { m_iOriginalGuid = guid; }
    CDescriptor* getDescriptor() const { return m_pDescriptor; }
    const std::wstring& getName() const { return m_sName; }
    CEditorScene* getSceneOwner() const { return m_pSceneOwner; }
    CPositionableObject* getParentPositionableObject() const { return m_pParentPositionableObject; }
    long long getParentHierarchyHashCode()
    {
        if (m_iParentHierarchyHashCode == 0)
            calculateParentHierarchyHashCode();
        return m_iParentHierarchyHashCode;
    }

private:
    long long m_iGuid;
    long long m_iParentGuid;
    long long m_iOriginalGuid;
    long long m_iParentHierarchyHashCode;
    bool m_bHashFromOriginalGuid;
    CDescriptor* m_pDescriptor;
    std::wstring m_sName;
    CEditorScene* m_pSceneOwner;
    CPositionableObject* m_pParentPositionableObject;
};

#endif
