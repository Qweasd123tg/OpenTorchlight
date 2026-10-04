#ifndef PLANECOLLIDERWRAPPER_H
#define PLANECOLLIDERWRAPPER_H

#include "ColliderWrapper.h"

namespace Ogre
{
	class Matrix4;
	class Vector3;
}

class CResourceManager;

class CPlaneColliderWrapper : public CColliderWrapper
{
public:
	virtual ~CPlaneColliderWrapper();
	virtual void positionUpdated(const Ogre::Vector3& position);
	virtual void orientationUpdated(const Ogre::Matrix4& orientation);
	void updatePlane();

	CPlaneColliderWrapper(CResourceManager* resourceManager);

	float mPlaneDistance;
	int mPlaneFlags;
};

#endif
