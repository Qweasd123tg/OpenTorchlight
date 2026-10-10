#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <map>
#include <string>

#include "EditorDefines.h"
#include "PositionableObject.h"
#include "TArrayList.h"

class CDataGroup;
class CResourceManager;
class CDescriptorSaveConfiguration;
class CDescriptor;
class CDescriptorManager;
class CDynamicPropertyFile;
class CTimerStatics;
class CDescriptorLoadConfiguration;
class CDescriptorSaveConfiguration;

// Partial: layout from CEditorScene::CEditorScene(const wchar_t*); members of
// EditorScene.cpp are declared as recovered TUs need them. Return types of the
// virtual methods past setEnabled are not verified yet.
class CEditorScene : public CPositionableObject
{
public:
    unsigned int getNumberOfTimelinesThatDoLoop();
    unsigned int getNumberOfTimelinesUpdating(bool excludeLooping);

    void DeleteAllObjectsFromScene();
    int saveScene(std::wstring filename, TArrayList<CEditorBaseObject*>* objects);

    std::map<long long, CEditorBaseObject*>& getObjects() { return m_Objects; }

    TArrayList<CEditorBaseObject*>* GetObjectsCreatedByADescriptor(const std::wstring& name);
    void configureGroupsToParse(CEditorBaseObject* parent,CDataGroup& data,TArrayList<CDataGroup*>& groups,CDescriptorLoadConfiguration* configuration);
    int loadObject(CDataGroup* data,CDescriptorLoadConfiguration* configuration);
    int loadObjects(CEditorBaseObject* parent,CDataGroup* data,CDescriptorLoadConfiguration* configuration);

    void clearObjectIndex();
    unsigned int GetNumberOfObjectsInScene(bool includeOwner);
    TArrayList<CEditorBaseObject*>* GetObjectsCreatedByADescriptor(CDescriptor* descriptor);
    bool canObjectBeSaved(CResourceManager* manager, CEditorBaseObject* object);
    CEditorBaseObject* CreateObjectByDescriptor(const std::wstring& name, bool load);
    CDescriptor* GetDescriptorInSceneByName(const wchar_t* name, bool create);
    void setChildrenVisible(long long parent, bool visible);
    CEditorBaseObject* CreateObjectByDescriptor(unsigned int index, CEditorBaseObject* parent, CEditorBaseObject* owner, bool load);
    void AddDescriptor(CDescriptor* descriptor);
    void InitScene(CResourceManager* manager, unsigned int flags);
    void deleteUnusedDescriptors();
    void setFileLoaded(const std::wstring& path);
    unsigned int saveObjectsHavingParent(long long parent, CDataGroup* group, CDescriptorSaveConfiguration* configuration);
    unsigned int saveObjectAndChildren(CEditorBaseObject*, CDataGroup*, CDescriptorSaveConfiguration*);

    void RemoveObjectInScene(CEditorBaseObject* object);
    CEditorScene(const wchar_t* name);
    virtual ~CEditorScene();

    virtual void setEnabled(bool enabled);
    virtual void fireEvent(EEDITOR_EVENTS event, long long guid);
    virtual CEditorBaseObject* CreateObjectByDescriptor(CDescriptor* descriptor, CEditorBaseObject* parent,
                                                        CEditorBaseObject* owner, bool load);
    virtual void DeleteObjectInScene(CEditorBaseObject* object);
    virtual bool loadScene(std::wstring file, bool merge, TArrayList<CEditorBaseObject*>* objects, long long guid,
                           bool create, CTimerStatics* timers);
    virtual bool loadScene(std::wstring file, CDataGroup& data, TArrayList<CEditorBaseObject*>* objects,
                           long long guid, CTimerStatics* timers);
    virtual void clone(CEditorScene* scene, TArrayList<CEditorBaseObject*>* objects, CTimerStatics* timers);
    virtual void merge(CEditorScene* scene, TArrayList<CEditorBaseObject*>* objects, long long guid,
                       CTimerStatics* timers);
    virtual void update(float elapsed);
    virtual void eventFiredByDescriptor(unsigned int event, CDescriptor* descriptor, CEditorBaseObject* object);
    virtual void setActivated(bool activated);
    virtual unsigned int getNumberOfParticlesUpdating();
    virtual void createDescriptors();
    virtual void editorObjectCreated(CEditorBaseObject* object);
    virtual void editorObjectDelete(CEditorBaseObject* object);
    virtual void editorObjectsAboutToBeDelete();
    virtual void editorObjectLoaded(CEditorBaseObject* object);

    CEditorBaseObject* GetObjectInScene(long long guid);
    void AddDescriptor(const wchar_t* name);
    void GetObjectsCreatedByADescriptor(const std::wstring& name, TArrayList<CEditorBaseObject*>* objects);
    void EditorBaseObjectChangedID(CEditorBaseObject* object, long long oldGuid, long long newGuid);

    CDescriptorManager* getDescriptorManager() { return m_pDescriptorManager; }
    // Settings file read by CDescriptor::BroadcastEventFromObject (Descriptor.cpp).
    CDynamicPropertyFile* getSettings() { return static_cast<CDynamicPropertyFile*>(m_pUnknown170); }

private:
    CDescriptorManager* m_pDescriptorManager;
    std::map<long long, CEditorBaseObject*> m_Objects;
    TArrayList<CEditorBaseObject*> m_ObjectList0;
    TArrayList<CEditorBaseObject*> m_ObjectList1;
    std::wstring m_sFileLoaded;
    void* m_pUnknown170;
    void* m_pUnknown178;
    CDataGroup* m_pUnknown180;
    int m_iUnknown188;
    bool m_bActivated;
    bool m_bUnknown18D;
};

#endif
