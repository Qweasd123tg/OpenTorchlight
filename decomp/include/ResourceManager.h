#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ParticleUniverseConstants.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CHierarchy;
class CLevel;

namespace Ogre
{
    class SceneManager;
}

// Partial: members are declared as ResourceManager.cpp is recovered. The
// layout follows the constructor.
class CResourceManager : public CRunicCore
{
public:
    CResourceManager(Ogre::SceneManager* sceneManager);
    virtual ~CResourceManager();

    bool getEditorIsRunning();
    Ogre::SceneManager* getSceneManager() { return m_pSceneManager; }
    CLevel* getLevel() { return m_pLevel; }

private:
    Ogre::SceneManager* m_pSceneManager;
    CLevel* m_pLevel;
    CHierarchy* m_pHierarchy;
    TArrayList<void*> m_ResourceList;
    bool m_bFlag0;
    bool m_bFlag1;
    bool m_bFlag2;
    bool m_bFlag3;
};

#endif
