#ifndef EDITOROBJECTMANAGER_H
#define EDITOROBJECTMANAGER_H

#include <map>

#include "RunicCore.h"
#include "TArrayList.h"

class CEditorBaseObject;
class CEditorScene;
class CObjectControl3D;
class CResourceManager;

// Partial: layout from CEditorObjectManager::CEditorObjectManager; members of
// EditorObjectManager.cpp are declared as recovered TUs need them.
class CEditorObjectManager : public CRunicCore
{
public:
    void keyEvent(unsigned int,unsigned int);
    void mouseEvent(unsigned int,unsigned int);
    void EditorSetChunkTemplateExits(int);
    void EditorSetChunkTemplateExit(int,float,float,float);
    void EditorDeleteAllObjectsInScene(CEditorScene*);

    typedef std::map<long long, CEditorBaseObject*> ObjectMap;

    CEditorObjectManager(CResourceManager* resourceManager);
    virtual ~CEditorObjectManager();

    ObjectMap* getObjects() { return &m_Objects; }
    TArrayList<CEditorBaseObject*>* getSelectedObjects() { return &m_SelectedObjects; }

private:
    ObjectMap m_Objects;
    TArrayList<CEditorBaseObject*> m_SelectedObjects;
    TArrayList<CEditorBaseObject*> m_CreatedObjects;
    CObjectControl3D* m_pObjectControl;
    bool m_bUnknown78;
    bool m_bUnknown79;
};

#endif
