#include "Light.h"

void CLight::scaleUpdated(const Ogre::Vector3& scale)
{
    if (scale.y != 0.25f)
        setScale(scale.x, 0.25f, scale.z);
}
void CLight::orientationUpdated(const Ogre::Matrix4&)
{
}

float CLight::getRotation()
{
    Ogre::Matrix3 orientation;
    getOrientation(orientation);
    Ogre::Quaternion rotation(orientation);
    return rotation.getYaw().valueDegrees();
}

void CLight::setRotation(float rotation)
{
    Ogre::Quaternion orientation(Ogre::Degree(rotation), Ogre::Vector3::UNIT_Y);
    setOrientation(orientation);
}
