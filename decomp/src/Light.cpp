#include "Light.h"

void CLight::scaleUpdated(const Ogre::Vector3& scale)
{
    if (scale.y != 0.25f)
        setScale(scale.x, 0.25f, scale.z);
}
void CLight::orientationUpdated(const Ogre::Matrix4&)
{
}
