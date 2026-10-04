#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H
#include "RunicCore.h"
#include <string>
namespace Ogre {class SceneManager;}
class CCollisionList;
// Partial, size 0x48 from MasterResourceManager::getCollisionModel allocation.
class CCollisionModel : public CRunicCore
{
public:
    CCollisionModel(Ogre::SceneManager* scene,std::wstring filename);
    virtual ~CCollisionModel();
    CCollisionList* getCollisionList() {return m_pCollisionList;}
private:
    unsigned char m_ModelData10[0x38-0x10];
    CCollisionList* m_pCollisionList;
    Ogre::SceneManager* m_pSceneManager;
};
#endif
