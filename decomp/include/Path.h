#ifndef PATH_H
#define PATH_H

#include <string>
#include <OgreVector3.h>
#include "RunicCore.h"
#include "TArrayList.h"

class CPath : public CRunicCore
{
public:
    virtual ~CPath();

    void Clear();
    Ogre::Vector3 GetPoint(unsigned int index) const;
    float GetPointDistance(unsigned int index) const;
    float GetSegmentAngle(unsigned int index) const;
    float GetRadiusLeft(unsigned int index) const;
    float GetRadiusRight(unsigned int index) const;
    void SetRadiusLeft(unsigned int index, float radius);
    void SetRadiusRight(unsigned int index, float radius);
    float GetTweenedRadiusRight(float distance) const;
    float GetTweenedRadiusLeft(float distance) const;
    Ogre::Vector3 GetSplinePositionAtDistance(float distance) const;
    float GetAngleOverDistance(float fromDistance, float toDistance) const;
    Ogre::Vector3 GetPathSegment(unsigned int index) const;
    Ogre::Vector3 GetPositionAtDistance(float distance) const;
    void ClosePath();
    bool FindNearestPoint(const Ogre::Vector3& target,
                          Ogre::Vector3& nearestPoint,
                          Ogre::Vector3& offset,
                          unsigned int& pointIndex,
                          float& distance,
                          float maximumDistance) const;
    void CalculatePathWidth(CPath& leftPath, CPath& rightPath);
    Ogre::Vector3 GetSegmentPerpendicularY(unsigned int index) const;
    void AddPoint(const Ogre::Vector3& point,
                  float radiusLeft,
                  float radiusRight);
    void Reverse();

    // Original narrow overload; its implementation still comes from the ELF.
    // The wide draft belongs to path.cpp and is tracked separately.
    CPath(std::string name, bool closed, const Ogre::Vector3& origin);
    CPath(std::wstring name, bool closed, const Ogre::Vector3& origin);
    void Resize(unsigned int pointCount);
    CPath(CPath& path);

    std::wstring m_sObjectName;
    float m_fPathLength;
    Ogre::Vector3 m_vOrigin;
    TArrayList<Ogre::Vector3> m_lPoints;
    TArrayList<float> m_lRadiusLeft;
    TArrayList<float> m_lRadiusRight;
    TArrayList<float> m_lSegmentAngle;
    TArrayList<float> m_lPointDistance;
    bool m_bClosedPath;
    std::wstring m_sName;
    Ogre::Vector3 m_vMinimum;
    Ogre::Vector3 m_vMaximum;
};

#endif
