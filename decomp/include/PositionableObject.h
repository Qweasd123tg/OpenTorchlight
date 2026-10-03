#ifndef POSITIONABLEOBJECT_H
#define POSITIONABLEOBJECT_H

#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreQuaternion.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "SceneNodeObject.h"

// Scene node object with a position, scale and orientation. The orientation
// matrix holds right, up and forward in its columns; the vectors are cached in
// m_vRight, m_vUp and m_vForward. Changes are pushed to the scene node.
class CPositionableObject : public CSceneNodeObject
{
public:
    CPositionableObject(CResourceManager* resourceManager, Ogre::SceneManager* sceneManager);
    virtual ~CPositionableObject();

    virtual void setPosition(float x, float y, float z) { setPosition(Ogre::Vector3(x, y, z)); }
    virtual void setX(float x) { setPosition(x, getY(), getZ()); }
    virtual float getX() { return m_vPosition.x; }
    virtual void setY(float y) { setPosition(getX(), y, getZ()); }
    virtual float getY() { return m_vPosition.y; }
    virtual void setZ(float z) { setPosition(getX(), getY(), z); }
    virtual float getZ() { return m_vPosition.z; }

    virtual void setScale(float scale) { setScale(scale, scale, scale); }
    virtual void setScale(float x, float y, float z)
    {
        m_vScale.x = x;
        m_vScale.y = y;
        m_vScale.z = z;
        if (m_pSceneNode)
            m_pSceneNode->setScale(x, y, z);
        scaleUpdated(m_vScale);
    }
    virtual float* getScaleFloat() { return m_vScale.ptr(); }
    virtual const Ogre::Vector3& getScale() { return m_vScale; }
    virtual float getScaleX() { return m_vScale.x; }
    virtual float getScaleY() { return m_vScale.y; }
    virtual float getScaleZ() { return m_vScale.z; }
    virtual void setScaleX(float x) { setScale(x, getScaleY(), getScaleZ()); }
    virtual void setScaleY(float y) { setScale(getScaleX(), y, getScaleZ()); }
    virtual void setScaleZ(float z) { setScale(getScaleX(), getScaleY(), z); }

    virtual void getOrientation(Ogre::Matrix3& orientation) { m_mOrientation.extract3x3Matrix(orientation); }
    virtual const Ogre::Matrix4& getOrientation() { return m_mOrientation; }
    virtual Ogre::Quaternion getOrientationQuaternion() { return Ogre::Quaternion(m_vRight, m_vUp, m_vForward); }
    virtual Ogre::Quaternion getOrientationQuaternionAbsolute() { return m_pSceneNode->_getDerivedOrientation(); }
    virtual Ogre::Matrix4 getTransformation()
    {
        Ogre::Matrix3 rotation;
        m_pSceneNode->_getDerivedOrientation().ToRotationMatrix(rotation);
        Ogre::Matrix4 transformation = Ogre::Matrix4::IDENTITY;
        transformation = rotation;
        transformation.setTrans(getPosition(true));
        return transformation;
    }
    virtual void setOrientation(const Ogre::Quaternion& orientation)
    {
        Ogre::Matrix3 rotation;
        orientation.ToRotationMatrix(rotation);
        m_mOrientation = Ogre::Matrix4(rotation);
        setOrientation(m_mOrientation, false);
    }
    virtual void setOrientation(const Ogre::Matrix3& orientation)
    {
        Ogre::Quaternion quaternion(orientation);
        setOrientation(quaternion);
    }
    virtual void setOrientation(const Ogre::Matrix4& orientation, bool setTranslation)
    {
        m_mOrientation = orientation;
        if (m_pSceneNode)
        {
            Ogre::Matrix3 rotation;
            getOrientation(rotation);
            Ogre::Quaternion quaternion(rotation);
            m_pSceneNode->setOrientation(quaternion);
        }
        if (setTranslation)
            setPosition(m_mOrientation[0][3], m_mOrientation[1][3], m_mOrientation[2][3]);
        extractOrientationVectors();
        orientationUpdated(m_mOrientation);
    }
    virtual void setDirection(Ogre::Vector3 direction)
    {
        if (m_pSceneNode)
        {
            m_pSceneNode->setDirection(direction, Ogre::Node::TS_LOCAL, Ogre::Vector3::UNIT_Z);
            setOrientation(m_pSceneNode->getOrientation());
        }
    }
    virtual void setOrientation(Ogre::Vector3& forward, Ogre::Vector3& up)
    {
        forward.normalise();
        up.normalise();
        Ogre::Vector3 right = up.crossProduct(forward);
        up = forward.crossProduct(right);
        right = up.crossProduct(forward);
        setOrientation(Ogre::Matrix4(right.x, up.x, forward.x, 0.0f,
                                     right.y, up.y, forward.y, 0.0f,
                                     right.z, up.z, forward.z, 0.0f,
                                     0.0f, 0.0f, 0.0f, 0.0f),
                       false);
    }

    virtual const Ogre::Vector3& getForward() { return m_vForward; }
    virtual Ogre::Vector3 getForwardAbsolute()
    {
        if (m_pSceneNode)
            return m_pSceneNode->_getDerivedOrientation().zAxis();
        return m_vForward;
    }
    virtual Ogre::Vector3& getForward(Ogre::Vector3& forward)
    {
        forward = m_vForward;
        return forward;
    }
    virtual void setForward(const Ogre::Vector3& forward) { setForward(forward.x, forward.y, forward.z); }
    virtual void setForward(float x, float y, float z)
    {
        m_vForward.x = m_mOrientation[0][2] = x;
        m_vForward.y = m_mOrientation[1][2] = y;
        m_vForward.z = m_mOrientation[2][2] = z;
        setOrientation(m_mOrientation, false);
    }

    virtual const Ogre::Vector3& getRight() { return m_vRight; }
    // The original never copies m_vRight here.
    virtual Ogre::Vector3& getRight(Ogre::Vector3& right) { return right; }
    virtual Ogre::Vector3 getRightAbsolute()
    {
        if (m_pSceneNode)
            return m_pSceneNode->_getDerivedOrientation().xAxis();
        return m_vRight;
    }
    virtual void setRight(const Ogre::Vector3& right) { setRight(right.x, right.y, right.z); }
    virtual void setRight(float x, float y, float z)
    {
        m_vRight.x = m_mOrientation[0][0] = x;
        m_vRight.y = m_mOrientation[1][0] = y;
        m_vRight.z = m_mOrientation[2][0] = z;
        setOrientation(m_mOrientation, false);
    }

    virtual const Ogre::Vector3& getUp() { return m_vUp; }
    virtual Ogre::Vector3& getUp(Ogre::Vector3& up)
    {
        up = m_vUp;
        return up;
    }
    virtual Ogre::Vector3 getUpAbsolute()
    {
        if (m_pSceneNode)
            return m_pSceneNode->_getDerivedOrientation().yAxis();
        return m_vUp;
    }
    virtual void setUp(const Ogre::Vector3& up) { setUp(up.x, up.y, up.z); }
    virtual void setUp(float x, float y, float z)
    {
        m_vUp.x = m_mOrientation[0][1] = x;
        m_vUp.y = m_mOrientation[1][1] = y;
        m_vUp.z = m_mOrientation[2][1] = z;
        setOrientation(m_mOrientation, false);
    }

    virtual void positionUpdated(const Ogre::Vector3& position) {}
    virtual void orientationUpdated(const Ogre::Matrix4& orientation) {}
    virtual void scaleUpdated(const Ogre::Vector3& scale) {}
    virtual void extractOrientationVectors()
    {
        m_vForward.x = m_mOrientation[0][2];
        m_vForward.y = m_mOrientation[1][2];
        m_vForward.z = m_mOrientation[2][2];
        m_vUp.x = m_mOrientation[0][1];
        m_vUp.y = m_mOrientation[1][1];
        m_vUp.z = m_mOrientation[2][1];
        m_vRight.x = m_mOrientation[0][0];
        m_vRight.y = m_mOrientation[1][0];
        m_vRight.z = m_mOrientation[2][0];
    }
    virtual void updateOrientation();

    Ogre::Vector3 getPosition(bool absolute);
    void setPosition(const Ogre::Vector3& position);

protected:
    Ogre::Vector3 m_vPosition;
    Ogre::Vector3 m_vScale;
    Ogre::Vector3 m_vUp;
    Ogre::Vector3 m_vRight;
    Ogre::Vector3 m_vForward;
    Ogre::Matrix4 m_mOrientation;
};

#endif
