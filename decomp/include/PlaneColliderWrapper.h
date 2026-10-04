#ifndef PLANECOLLIDERWRAPPER_H
#define PLANECOLLIDERWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include "ColliderWrapper.h"
#include "ResourceManager.h"

class CPlaneColliderWrapper : public CColliderWrapper
{
public:
    virtual ~CPlaneColliderWrapper();
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void orientationUpdated(const Ogre::Matrix4&);
    void updatePlane();
    CPlaneColliderWrapper(CResourceManager*);

    // fields
    float m_fUnknown120;
    int m_iUnknown124;
};

#endif
