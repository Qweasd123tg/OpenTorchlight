#ifndef ILEVELUPDATE_H
#define ILEVELUPDATE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>

class iLevelUpdate
{
public:
    virtual ~iLevelUpdate();
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&) = 0;

    // fields
};

#endif
