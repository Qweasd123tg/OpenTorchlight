#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H

#include <string>

#include <OgreVector3.h>

#include "RunicCore.h"

namespace Ogre { class SceneManager; }
class CCollisionList;

// Collision triangles of a mesh file, loaded through the OGRE MeshManager.
// Size 0x48 (MasterResourceManager::getCollisionModel allocation).
class CCollisionModel : public CRunicCore
{
public:
    CCollisionModel(Ogre::SceneManager* sceneManager, std::wstring filename);
    virtual ~CCollisionModel();

    void loadModel(std::wstring filename);
    void unloadModel();

    CCollisionList* getCollisionList() { return m_pCollisionList; }

private:
    std::wstring m_sFilename;
    std::string m_sMeshName;
    // Zeroed by the constructor, not used by this TU.
    Ogre::Vector3 m_vUnknown20;
    Ogre::Vector3 m_vUnknown2C;
    CCollisionList* m_pCollisionList;
    Ogre::SceneManager* m_pSceneManager;
};

#endif
