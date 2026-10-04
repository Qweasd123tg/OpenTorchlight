#ifndef SPHERECOLLIDERWRAPPER_H
#define SPHERECOLLIDERWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "ColliderWrapper.h"
#include "ResourceManager.h"

class CSphereColliderWrapper : public CColliderWrapper
{
public:
    virtual ~CSphereColliderWrapper();
    virtual void positionUpdated(const Ogre::Vector3&);
    void updateCircle();
    CSphereColliderWrapper(CResourceManager*);

    // fields
};

#endif
