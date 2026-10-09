#include "CollisionAvoiderWrapper.h"

CCollisionAvoiderWrapper::~CCollisionAvoiderWrapper()
{
}

#include <map>
#include <string>
#include "AffectorWrapper.h"

void CCollisionAvoiderWrapper::positionUpdated(const Ogre::Vector3& position)
{
    CAffectorWrapper::positionUpdated(position);
}
