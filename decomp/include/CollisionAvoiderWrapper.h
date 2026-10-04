#ifndef COLLISIONAVOIDERWRAPPER_H
#define COLLISIONAVOIDERWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "ColliderWrapper.h"
#include "ResourceManager.h"

class CCollisionAvoiderWrapper : public CColliderWrapper
{
public:
    virtual ~CCollisionAvoiderWrapper();
    virtual void positionUpdated(const Ogre::Vector3&);
    void updateCircle();
    CCollisionAvoiderWrapper(CResourceManager*);

    // fields
};

#endif
