#ifndef TELEPORT_H
#define TELEPORT_H

#include <OgreVector3.h>
#include "PositionableObject.h"

class CResourceManager;

// Moves every client's player and its pets to a position.
class CTeleport : public CPositionableObject
{
public:
    CTeleport(CResourceManager* resourceManager);
    virtual ~CTeleport();
    virtual void setEnabled(bool enabled) { m_bTeleportEnabled = enabled; }
    virtual bool getEnabled() { return m_bTeleportEnabled; }

    void activate(Ogre::Vector3 position, Ogre::Vector3 direction);

private:
    bool m_bTeleportEnabled;
    CResourceManager* m_pResourceManager;
};

#endif
