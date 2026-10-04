#ifndef SPHERECOLLIDERWRAPPER_H
#define SPHERECOLLIDERWRAPPER_H

#include "ColliderWrapper.h"

class CResourceManager;

namespace Ogre
{
    class Vector3;
}

class CSphereColliderWrapper : public CColliderWrapper
{
public:
    virtual ~CSphereColliderWrapper();
    virtual void positionUpdated(const Ogre::Vector3& position);

    void updateCircle();

    CSphereColliderWrapper(CResourceManager* resourceManager);
};

#endif
