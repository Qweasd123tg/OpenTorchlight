#ifndef CULLINGBOUNDS_H
#define CULLINGBOUNDS_H
#include "RunicCore.h"
#include <OgreVector3.h>
// Partial: original allocation is 0xb8; Item reads the world-space bounds.
class CCullingBounds : public CRunicCore
{
public:
    virtual ~CCullingBounds();
    const Ogre::Vector3& getLocalMinimum() const { return m_vLocalMinimum; }
    const Ogre::Vector3& getLocalMaximum() const { return m_vLocalMaximum; }
    const Ogre::Vector3& getWorldMinimum() const { return m_vWorldMinimum; }
    const Ogre::Vector3& getWorldMaximum() const { return m_vWorldMaximum; }
private:
    unsigned char m_BoundsData10[0x28-0x10];
    Ogre::Vector3 m_vLocalMinimum;
    Ogre::Vector3 m_vLocalMaximum;
    Ogre::Vector3 m_vWorldMinimum;
    Ogre::Vector3 m_vWorldMaximum;
    unsigned char m_BoundsData58[0xb8-0x58];
};
#endif
