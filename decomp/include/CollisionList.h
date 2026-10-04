#ifndef COLLISIONLIST_H
#define COLLISIONLIST_H
#include "RunicCore.h"
#include <OgreVector3.h>
// Partial, complete original allocation size 0x108.
class CCollisionList : public CRunicCore
{
public:
    CCollisionList();
    virtual ~CCollisionList();
    bool rayCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,Ogre::Vector3& hit,Ogre::Vector3& normal,float& distance);
    bool sphereCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,float radius,Ogre::Vector3& position,Ogre::Vector3& hit,Ogre::Vector3& normal,float& distance);
    void addVertex(const Ogre::Vector3& vertex,int index);
    void addFace(int a,int b,int c,unsigned int material,int index);
    void calculateNormals();
    void calculateFaceBounds();
private:
    unsigned char m_CollisionData10[0x108-0x10];
};
#endif
