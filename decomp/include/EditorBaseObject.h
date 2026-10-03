#ifndef EDITORBASEOBJECT_H
#define EDITORBASEOBJECT_H

#include <string>

#include "RunicCore.h"

class CDescriptor;
class CEditorScene;
class CPositionableObject;

// Base of every object placed by the editor (logic objects, units, props).
// Members of EditorBaseObject.cpp other than the vtable and the layout are
// declared as that TU is recovered.
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
