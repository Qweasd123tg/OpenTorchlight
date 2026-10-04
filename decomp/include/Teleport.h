#ifndef TELEPORT_H
#define TELEPORT_H

// Logic teleport object; original positionable base and per-object enabled flag.

#include <OgreVector3.h>
#include "PositionableObject.h"
#include "ResourceManager.h"

class CTeleport : public CPositionableObject
{
public:
    virtual ~CTeleport();
    virtual void setEnabled(bool enabled) { m_bEnabled = enabled; }
    virtual bool getEnabled() { return m_bEnabled; }
    void activate(Ogre::Vector3, Ogre::Vector3);
    CTeleport(CResourceManager*);

    // fields
    bool m_bEnabled;
    unsigned char m_gap101[0x7];
    CResourceManager* m_pResourceManager;
};

#endif
