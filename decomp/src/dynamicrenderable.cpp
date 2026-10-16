#include "DynamicRenderable.h"

Ogre::Real CDynamicRenderable::getBoundingRadius() const
{
    return sqrtf(std::max(mBox.getMaximum().squaredLength(),
                          mBox.getMinimum().squaredLength()));
}

#include <OgreCamera.h>

Ogre::Real CDynamicRenderable::getSquaredViewDepth(const Ogre::Camera* camera) const
{
    Ogre::Vector3 center = mBox.getMinimum() +
        (mBox.getMaximum() - mBox.getMinimum()) * 0.5f;
    return (camera->getDerivedPosition() - center).squaredLength();
}
