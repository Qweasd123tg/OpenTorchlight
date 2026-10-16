#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>
#include <OgreVector3.h>
#include "RunicCore.h"
#include "TArrayList.h"

class CPath : public CRunicCore
{
public:
    virtual ~CPath();

    void Clear();
    Ogre::Vector3 GetPoint(unsigned int index);
    Ogre::Vector3 GetPoint(unsigned int index) const;
    float GetPointDistance(unsigned int index);
    float GetPointDistance(unsigned int index) const;
    float GetSegmentAngle(unsigned int index);
    float GetSegmentAngle(unsigned int index) const;
    float GetRadiusLeft(unsigned int index);
    float GetRadiusLeft(unsigned int index) const;
    float GetRadiusRight(unsigned int index);
    float GetRadiusRight(unsigned int index) const;
    void SetRadiusLeft(unsigned int index, float radius);
    void SetRadiusRight(unsigned int index, float radius);
    float GetTweenedRadiusRight(float distance);
    float GetTweenedRadiusRight(float distance) const;
    float GetTweenedRadiusLeft(float distance);
    float GetTweenedRadiusLeft(float distance) const;
    // Original mutable ABI; const draft belongs to path.cpp and remains separate.
    Ogre::Vector3 GetSplinePositionAtDistance(float distance);
    Ogre::Vector3 GetSplinePositionAtDistance(float distance) const;
    float GetAngleOverDistance(float fromDistance, float toDistance);
    float GetAngleOverDistance(float fromDistance, float toDistance) const;
    Ogre::Vector3 GetPathSegment(unsigned int index);
    Ogre::Vector3 GetPathSegment(unsigned int index) const;
    Ogre::Vector3 GetPositionAtDistance(float distance);
    Ogre::Vector3 GetPositionAtDistance(float distance) const;
    void ClosePath();
    bool FindNearestPoint(const Ogre::Vector3& target,
                          Ogre::Vector3& nearestPoint,
                          Ogre::Vector3& offset,
                          unsigned int& pointIndex,
                          float& distance,
                          float maximumDistance);
    bool FindNearestPoint(const Ogre::Vector3& target,
                          Ogre::Vector3& nearestPoint,
                          Ogre::Vector3& offset,
                          unsigned int& pointIndex,
                          float& distance,
                          float maximumDistance) const;
    void CalculatePathWidth(CPath& leftPath, CPath& rightPath);
    Ogre::Vector3 GetSegmentPerpendicularY(unsigned int index);
    Ogre::Vector3 GetSegmentPerpendicularY(unsigned int index) const;
    void AddPoint(const Ogre::Vector3& point,
                  float radiusLeft,
                  float radiusRight);
    void Reverse();

    CPath(std::string name, bool closed, const Ogre::Vector3& origin);
    void Resize(unsigned int pointCount);
    CPath(CPath& path);

    std::string m_sObjectName;
    float m_fPathLength;
    Ogre::Vector3 m_vOrigin;
    std::vector<Ogre::Vector3> m_lPoints;
    std::vector<float> m_lRadiusLeft;
    std::vector<float> m_lRadiusRight;
    std::vector<float> m_lSegmentAngle;
    std::vector<float> m_lPointDistance;
    bool m_bClosedPath;
    std::string m_sName;
    Ogre::Vector3 m_vMinimum;
    Ogre::Vector3 m_vMaximum;
};

#endif
