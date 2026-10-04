#ifndef TELEPORT_H
#define TELEPORT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "PositionableObject.h"
#include "ResourceManager.h"

class CTeleport : public CPositionableObject
{
public:
    virtual ~CTeleport();
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    void activate(Ogre::Vector3, Ogre::Vector3);
    CTeleport(CResourceManager*);

    // fields
    bool m_bEnabled;
    unsigned char m_gap101[0x7];
    CResourceManager* m_pResourceManager;
};

#endif
