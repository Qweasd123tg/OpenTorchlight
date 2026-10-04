#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "ResourceManager.h"
#include "Shape.h"

class CCollisionShape : public CShape
{
public:
    virtual ~CCollisionShape();
    virtual void setEnabled(bool);
    virtual void setBoxSize(const Ogre::Vector3&);
    void update(float);
    void updateCollision();
    CCollisionShape(CResourceManager*);

    // fields
};

#endif
