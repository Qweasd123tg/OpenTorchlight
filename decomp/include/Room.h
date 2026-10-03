#ifndef ROOM_H
#define ROOM_H

#include <string>

#include "SceneNodeObject.h"

class CResourceManager;

// Scene node object of a level room; CRoomDescriptor fills the file names from
// the layout.
class CRoom : public CSceneNodeObject
{
public:
    CRoom(CResourceManager* resourceManager);
    virtual ~CRoom();

    void setSceneOverrideFile(const std::wstring& file) { m_sSceneOverrideFile = file; }
    void setMeshFileCreatedDynamically(const std::wstring& file) { m_sMeshFileCreatedDynamically = file; }

private:
    std::wstring m_sSceneOverrideFile;
    std::wstring m_sMeshFileCreatedDynamically;
};

#endif
