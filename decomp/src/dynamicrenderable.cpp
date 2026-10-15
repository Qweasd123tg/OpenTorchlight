#include "DynamicRenderable.h"

Ogre::Real CDynamicRenderable::getBoundingRadius() const
{
    return sqrtf(std::max(mBox.getMaximum().squaredLength(),
                          mBox.getMinimum().squaredLength()));
}
