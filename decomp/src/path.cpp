#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Path.h"
#include "RunicCore.h"
#include "UtilitiesMath.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "TArrayList.h"

void CPath::Clear()
{
    m_lPoints.clear();
    m_fPathLength = 0.0f;
    m_vOrigin.x = 0.0f;
    m_vOrigin.y = 0.0f;
    m_vOrigin.z = 0.0f;
    m_lSegmentAngle.clear();
    m_lRadiusLeft.clear();
    m_lRadiusRight.clear();
    m_lPointDistance.clear();
}

Ogre::Vector3 CPath::GetPoint(unsigned int index) const
{
    if (index < m_lPoints.size())
    {
        const Ogre::Vector3& point = m_lPoints[index];
        return Ogre::Vector3(m_vOrigin.x + point.x,
                             m_vOrigin.y + point.y,
                             m_vOrigin.z + point.z);
    }

    return m_vOrigin;
}

float CPath::GetPointDistance(unsigned int index) const
{
    if (index < m_lPointDistance.size())
        return m_lPointDistance[index];

    return 0.0f;
}

float CPath::GetSegmentAngle(unsigned int index) const
{
    if (index < m_lSegmentAngle.size())
        return m_lSegmentAngle[index];

    return 0.0f;
}

float CPath::GetRadiusLeft(unsigned int index) const
{
    const std::vector<float>& radii = m_lRadiusLeft;

    if (m_bClosedPath && index >= radii.size())
        index -= radii.size();

    if (index >= radii.size())
        return 0.0f;

    return radii[index];
}

float CPath::GetRadiusRight(unsigned int index) const
{
    if (!m_bClosedPath)
    {
        if (index < m_lRadiusRight.size())
            return m_lRadiusRight[index];
        return 0.0f;
    }

    int size = m_lRadiusRight.size();
    if (index >= static_cast<unsigned int>(size))
        index -= static_cast<unsigned int>(size);

    if (index >= static_cast<unsigned int>(size))
        return 0.0f;

    return m_lRadiusRight[index];
}

float CPath::GetTweenedRadiusRight(float distance) const
{
    while (distance < 0.0f)
        distance += m_fPathLength;
    while (distance > m_fPathLength)
        distance -= m_fPathLength;

    const unsigned int pointCount = m_lPoints.size();
    for (unsigned int i = 0; i < pointCount; ++i)
    {
        unsigned int next = i + 1;
        if (next == pointCount)
            next = 0;

        if (distance < m_lPointDistance[next])
        {
            float segmentLength =
                m_lPointDistance[next] - m_lPointDistance[i];
            if (next == 0 && m_bClosedPath)
                segmentLength = m_fPathLength - m_lPointDistance[i];

            return m_lRadiusRight[i] +
                (m_lRadiusRight[next] - m_lRadiusRight[i]) *
                ((distance - m_lPointDistance[i]) / segmentLength);
        }
    }

    return 0.0f;
}

float CPath::GetTweenedRadiusLeft(float distance) const
{
    while (distance < 0.0f)
        distance += m_fPathLength;

    while (distance > m_fPathLength)
        distance -= m_fPathLength;

    unsigned int pointCount = m_lPoints.size();
    for (unsigned int i = 0; i < pointCount; ++i)
    {
        unsigned int nextIndex = (i + 1) % pointCount;
        if (distance < m_lPointDistance[nextIndex] || nextIndex == 0)
        {
            float pointDistance = m_lPointDistance[i];
            float segmentDistance = m_lPointDistance[nextIndex] - pointDistance;

            if (nextIndex == 0 && m_bClosedPath)
                segmentDistance = m_fPathLength - pointDistance;

            float radius = m_lRadiusLeft[i];
            float nextRadius = m_lRadiusLeft[nextIndex];

            return radius + (nextRadius - radius) *
                   ((distance - pointDistance) / segmentDistance);
        }
    }

    return 0.0f;
}

Ogre::Vector3 CPath::GetSplinePositionAtDistance(float distance) const
{
    if (m_fPathLength == 0.0f)
        return m_vOrigin;

    if (m_bClosedPath)
    {
        if (distance < 0.0f)
            distance = 0.0f;
        else if (distance > m_fPathLength)
            distance = m_fPathLength;
    }
    else
    {
        while (distance < 0.0f)
            distance += m_fPathLength;
        while (distance > m_fPathLength)
            distance -= m_fPathLength;
    }

    const unsigned int pointCount = m_lPoints.size();

    int segment = static_cast<int>(pointCount) - 1;
    for (; segment >= 0; --segment)
    {
        if (distance > m_lPointDistance[segment])
            break;
    }

    if (distance == m_fPathLength)
        return m_lPoints[pointCount - 1] + m_vOrigin;

    if (distance == 0.0f)
        return m_lPoints[0] + m_vOrigin;

    int previousPoint = segment - 1;
    int currentPoint = segment;
    int nextPoint = segment + 1;
    int nextNextPoint = segment + 2;

    if (currentPoint < 0)
    {
        previousPoint = -1;
        currentPoint = 0;
        nextPoint = 1;
        nextNextPoint = 2;
    }

    if (previousPoint < 0)
        previousPoint = m_bClosedPath ? static_cast<int>(pointCount) - 1 : 0;

    if (nextPoint >= static_cast<int>(pointCount))
        nextPoint = m_bClosedPath ? nextPoint - static_cast<int>(pointCount)
                                  : static_cast<int>(pointCount) - 1;

    if (nextNextPoint >= static_cast<int>(pointCount))
        nextNextPoint = m_bClosedPath
            ? nextNextPoint - static_cast<int>(pointCount)
            : static_cast<int>(pointCount) - 1;

    const Ogre::Vector3 p0 = m_lPoints[previousPoint];
    const Ogre::Vector3 p1 = m_lPoints[currentPoint];
    const Ogre::Vector3 p2 = m_lPoints[nextPoint];
    const Ogre::Vector3 p3 = m_lPoints[nextNextPoint];

    float segmentLength =
        m_lPointDistance[nextPoint] - m_lPointDistance[currentPoint];
    if (segmentLength < 0.0f)
        segmentLength += m_fPathLength;

    float t = distance - m_lPointDistance[currentPoint];
    if (distance < m_lPointDistance[currentPoint])
        t += m_fPathLength;
    t /= segmentLength;

    const float t2 = t * t;
    const float t3 = t2 * t;

    const float x =
        (2.0f * p1.x + (p3.x - p2.x) * t +
         (p1.x - 5.0f * p2.x + 4.0f * p3.x - p0.x) * t2 +
         (3.0f * p1.x - 3.0f * p2.x + p3.x - p0.x) * t3) * 0.5f;

    const float y =
        (2.0f * p1.y + (p3.y - p2.y) * t +
         (p1.y - 5.0f * p2.y + 4.0f * p3.y - p0.y) * t2 +
         (3.0f * p1.y - 3.0f * p2.y + p3.y - p0.y) * t3) * 0.5f;

    const float z =
        (2.0f * p1.z + (p3.z - p2.z) * t +
         (p1.z - 5.0f * p2.z + 4.0f * p3.z - p0.z) * t2 +
         (3.0f * p1.z - 3.0f * p2.z + p3.z - p0.z) * t3) * 0.5f;

    return Ogre::Vector3(x, y, z) + m_vOrigin;
}

float CPath::GetAngleOverDistance(float fromDistance, float toDistance) const
{
    if (fromDistance >= toDistance)
        return 0.0f;

    float startDistance = std::fabs(fromDistance);
    float endDistance = std::min(toDistance, m_fPathLength);

    int firstPoint = -1;
    int lastPoint = -1;

    for (unsigned int i = 0; i < m_lPointDistance.size(); ++i)
    {
        if (i == 0)
            continue;

        if (firstPoint == -1 && startDistance < m_lPointDistance[i])
            firstPoint = i;

        if (lastPoint == -1 && endDistance < m_lPointDistance[i])
            lastPoint = i;

        if (firstPoint != -1 && lastPoint != -1)
            break;
    }

    float angle = 0.0f;
    for (int i = firstPoint + 1; i <= lastPoint; ++i)
    {
        if (i == lastPoint)
        {
            float previousDistance = m_lPointDistance[i - 1];
            angle += ((endDistance - previousDistance) /
                      (m_lPointDistance[i] - previousDistance)) *
                     m_lSegmentAngle[i];
        }
        else
        {
            angle += m_lSegmentAngle[i];
        }
    }

    return angle;
}

Ogre::Vector3 CPath::GetPathSegment(unsigned int index) const
{
    if (m_lPoints.size() <= 1 || index >= m_lPoints.size() - 2)
        return Ogre::Vector3(0.0f, 0.0f, 0.0f);

    return m_lPoints[index + 1] - m_lPoints[index];
}

Ogre::Vector3 CPath::GetPositionAtDistance(float distance) const
{
    if (distance <= 0.0f)
    {
        do
        {
            distance += m_fPathLength;
        }
        while (distance <= 0.0f);
    }

    if (distance > m_fPathLength)
    {
        do
        {
            distance -= m_fPathLength;
        }
        while (distance > m_fPathLength);
    }

    if (distance == m_fPathLength)
        return m_lPoints[m_lPoints.size() - 1] + m_vOrigin;

    if (distance == 0.0f)
        return m_lPoints[0] + m_vOrigin;

    const unsigned int pointCount = m_lPoints.size();
    for (unsigned int i = 1; i <= pointCount; ++i)
    {
        const unsigned int nextIndex = i == pointCount ? 0 : i;
        if (distance > m_lPointDistance[nextIndex] || nextIndex == 0)
        {
            Ogre::Vector3 offset = m_lPoints[nextIndex] - m_lPoints[i];
            const float offsetLength = offset.length();

            if (offsetLength > 1e-08)
                offset /= offsetLength;

            offset *= distance - m_lPointDistance[i];
            return offset + m_lPoints[i] + m_vOrigin;
        }
    }

    return m_vOrigin;
}

void CPath::ClosePath()
{
    Ogre::Vector3 point = GetPoint(0);
    point -= GetPoint(m_lPoints.size() - 1);
    m_fPathLength += point.length();
}

bool CPath::FindNearestPoint(const Ogre::Vector3& target,
                             Ogre::Vector3& nearestPoint,
                             Ogre::Vector3& offset,
                             unsigned int& pointIndex,
                             float& distance,
                             float maximumDistance) const
{
    unsigned int segmentCount = m_lPoints.size();
    if (segmentCount <= 1)
        return false;

    if (!m_bClosedPath)
    {
        --segmentCount;
        if (m_fPathLength < maximumDistance)
            maximumDistance = m_fPathLength;
    }

    Ogre::Vector3 relativeTarget = target - m_vOrigin;

    nearestPoint = m_lPoints[0];
    offset = relativeTarget - nearestPoint;
    pointIndex = 0;
    distance = 0.0f;

    float closestDistance = 99999.0f;

    for (unsigned int i = 0; i < segmentCount; ++i)
    {
        if (closestDistance == 99999.0f &&
            m_lPointDistance[i] >= maximumDistance)
        {
            Ogre::Vector3 candidatePoint = m_lPoints[i];
            Ogre::Vector3 candidateOffset = relativeTarget - candidatePoint;
            float candidateDistance = candidateOffset.length();

            if (candidateDistance < closestDistance)
            {
                nearestPoint = candidatePoint;
                offset = candidateOffset;
                pointIndex = i;
                distance = m_lPointDistance[i];
                closestDistance = candidateDistance;
            }
        }

        unsigned int nextPointIndex = (i + 1) % m_lPoints.size();
        Ogre::Vector3 segmentStart = m_lPoints[i];
        Ogre::Vector3 segment = m_lPoints[nextPointIndex] - segmentStart;
        float segmentLength = segment.length();
        Ogre::Vector3 segmentOffset = relativeTarget - segmentStart;
        float pointParameter = segmentOffset.dotProduct(segment) /
                               (segmentLength * segmentLength);

        if (pointParameter < 0.0f || pointParameter > 1.0f)
        {
            float pathDistance = nextPointIndex == 0
                               ? m_fPathLength
                               : m_lPointDistance[nextPointIndex];

            if (pathDistance < maximumDistance)
            {
                pointParameter += (1.0f / segmentLength) *
                                  (maximumDistance - pathDistance + 1.0f);
                if (pointParameter > 1.0f)
                    pointParameter = 1.0f;

                pathDistance = m_lPointDistance[i] +
                               pointParameter * segmentLength;
            }

            if (pathDistance >= maximumDistance)
            {
                Ogre::Vector3 candidatePoint = m_lPoints[nextPointIndex];
                Ogre::Vector3 candidateOffset = relativeTarget - candidatePoint;
                float candidateDistance = candidateOffset.length();

                if (candidateDistance < closestDistance)
                {
                    nearestPoint = candidatePoint;
                    offset = candidateOffset;
                    pointIndex = i;
                    distance = pathDistance;
                    closestDistance = candidateDistance;
                }
            }
        }
        else
        {
            float pathDistance = m_lPointDistance[i] +
                                 pointParameter * segmentLength;

            if (pathDistance < maximumDistance)
            {
                pointParameter += (1.0f / segmentLength) *
                                  (maximumDistance - pathDistance + 1.0f);
                if (pointParameter > 1.0f)
                    pointParameter = 1.0f;

                pathDistance = m_lPointDistance[i] +
                               pointParameter * segmentLength;
            }

            if (pathDistance >= maximumDistance)
            {
                Ogre::Vector3 candidatePoint = segmentStart +
                                               segment * pointParameter;
                Ogre::Vector3 candidateOffset = relativeTarget - candidatePoint;
                float candidateDistance = candidateOffset.length();

                if (candidateDistance < closestDistance)
                {
                    nearestPoint = candidatePoint;
                    offset = candidateOffset;
                    pointIndex = i;
                    distance = pathDistance;
                    closestDistance = candidateDistance;
                }
            }
        }
    }

    if (closestDistance == 99999.0f)
        return false;

    nearestPoint += m_vOrigin;
    return true;
}

CPath::~CPath()
{
}

void CPath::CalculatePathWidth(CPath& leftPath, CPath& rightPath)
{
    Ogre::Vector3 nearestPoint;
    Ogre::Vector3 offset;
    unsigned int pointIndex = 0;
    float distance = 0.0f;
    for (unsigned int i = 0; i < m_lPoints.size(); ++i) {
        if (leftPath.FindNearestPoint(m_lPoints[i], nearestPoint, offset, pointIndex, distance, 0.0f)) {
            offset.normalise();
            nearestPoint -= m_lPoints[i];
            nearestPoint.y = 0.0f;
            m_lRadiusLeft[i] = offset.dotProduct(nearestPoint);
            if (m_lRadiusLeft[i] > 0.0f)
                m_lRadiusLeft[i] = 0.0f;
        }
        if (rightPath.FindNearestPoint(m_lPoints[i], nearestPoint, offset, pointIndex, distance, 0.0f)) {
            offset.normalise();
            offset = -offset;
            nearestPoint -= m_lPoints[i];
            nearestPoint.y = 0.0f;
            m_lRadiusRight[i] = offset.dotProduct(nearestPoint);
            if (m_lRadiusRight[i] < 0.0f)
                m_lRadiusRight[i] = 0.0f;
        }
    }
}

Ogre::Vector3 CPath::GetSegmentPerpendicularY(unsigned int index) const
{
    unsigned int pointCount = m_lPoints.size();
    if (pointCount < 2 || index >= pointCount - 1)
        return Ogre::Vector3::ZERO;

    unsigned int nextIndex = index + 1;
    if (nextIndex == pointCount && m_bClosedPath)
        nextIndex = 0;

    Ogre::Vector3 perpendicular(
        m_lPoints[nextIndex].z - m_lPoints[index].z,
        0.0f,
        m_lPoints[index].x - m_lPoints[nextIndex].x);
    perpendicular.normalise();
    return perpendicular;
}

void CPath::AddPoint(const Ogre::Vector3& point, float radiusLeft, float radiusRight)
{
    if (m_lPoints.size() == 0)
    {
        m_vMinimum = point;
        m_vMaximum = point;
    }
    else
    {
        MATH::expandBounds(m_vMinimum, m_vMaximum, point);
    }

    m_lPoints.push_back(point);
    m_lRadiusLeft.push_back(radiusLeft);
    m_lRadiusRight.push_back(radiusRight);

    if (m_lPoints.size() > 1)
    {
        Ogre::Vector3 segment = m_lPoints[m_lPoints.size() - 1] -
                                 m_lPoints[m_lPoints.size() - 2];
        float segmentLength = sqrtf(segment.squaredLength());

        m_fPathLength += segmentLength;
        m_lPointDistance.push_back(m_lPointDistance[m_lPointDistance.size() - 1] +
                             segmentLength);
        m_lSegmentAngle.push_back(0.0f);

        if (m_lPoints.size() > 2)
        {
            Ogre::Vector3 previousSegment =
                m_lPoints[m_lPoints.size() - 2] - m_lPoints[m_lPoints.size() - 3];
            float previousSegmentLength = sqrtf(previousSegment.squaredLength());

            if (segmentLength > 1e-08)
                segment /= segmentLength;
            if (previousSegmentLength > 1e-08)
                previousSegment /= previousSegmentLength;

            m_lSegmentAngle[m_lPoints.size() - 2] =
                MATH::angleBetween(segment, previousSegment) * 57.295826;
        }
    }
    else
    {
        m_lPointDistance.push_back(0.0f);
        m_lSegmentAngle.push_back(0.0f);
        m_fPathLength = 0.0f;
    }
}

void CPath::Reverse()
{
    std::vector<Ogre::Vector3> points(m_lPoints);
    unsigned int count = m_lPoints.size();
    Clear();
    for (unsigned int i = 0; i < count; ++i)
        AddPoint(points[count - i - 1], -60.0f, 60.0f);
    if (m_bClosedPath)
        ClosePath();
}

CPath::CPath(std::string name, bool closed, const Ogre::Vector3& origin)
    : CRunicCore(),
      m_sObjectName(),
      m_fPathLength(0.0f),
      m_vOrigin(origin),
      m_lPoints(),
      m_lRadiusLeft(),
      m_lRadiusRight(),
      m_lSegmentAngle(),
      m_lPointDistance(),
      m_bClosedPath(closed),
      m_sName(name)
{
}

void CPath::SetRadiusLeft(unsigned int index, float radius)
{
    if (index < m_lRadiusLeft.size())
        m_lRadiusLeft[index] = radius;
}

void CPath::SetRadiusRight(unsigned int index, float radius)
{
    if (index < m_lRadiusRight.size())
        m_lRadiusRight[index] = radius;
}

void CPath::Resize(unsigned int pointCount)
{
    if (pointCount >= m_lPoints.size())
        return;
    std::vector<Ogre::Vector3> points(m_lPoints);
    float step = static_cast<float>(m_lPoints.size()) / static_cast<float>(pointCount);
    Clear();
    for (unsigned int i = 0; i < pointCount; ++i) {
        unsigned int index = static_cast<unsigned int>(floorf(static_cast<float>(i) * step + 0.5f));
        AddPoint(points[index], -60.0f, 60.0f);
    }
    if (m_bClosedPath)
        ClosePath();
}

CPath::CPath(CPath& path)
{
    m_vOrigin = path.m_vOrigin;
    m_bClosedPath = path.m_bClosedPath;
    m_sName = path.m_sName;
    m_fPathLength = path.m_fPathLength;
    m_sObjectName = path.m_sObjectName;
    m_vMinimum = path.m_vMinimum;
    m_vMaximum = path.m_vMaximum;

    Resize(path.m_lPoints.size());

    for (unsigned int i = 0; i < path.m_lPoints.size(); ++i)
    {
        m_lPoints[i] = path.GetPoint(i) - m_vOrigin;
        m_lRadiusLeft[i] = path.GetRadiusLeft(i);
        m_lRadiusRight[i] = path.GetRadiusRight(i);
        m_lPointDistance[i] = path.GetPointDistance(i);
        m_lSegmentAngle[i] = path.GetSegmentAngle(i);
    }
}

Ogre::Vector3 CPath::GetPoint(unsigned int index)
{
    if (index < m_lPoints.size())
        return m_lPoints[index] + m_vOrigin;
    return m_vOrigin;
}

float CPath::GetPointDistance(unsigned int index)
{
    if (index < m_lPointDistance.size())
        return m_lPointDistance[index];
    return 0.0f;
}

float CPath::GetSegmentAngle(unsigned int index)
{
    if (index < m_lSegmentAngle.size())
        return m_lSegmentAngle[index];
    return 0.0f;
}

float CPath::GetRadiusLeft(unsigned int index)
{
    if (m_bClosedPath && index >= m_lRadiusLeft.size())
        index -= m_lRadiusLeft.size();
    unsigned int count = m_lRadiusLeft.size();
    if (index < count)
        return m_lRadiusLeft[index];
    return 0.0f;
}

float CPath::GetRadiusRight(unsigned int index)
{
    if (m_bClosedPath && index >= m_lRadiusRight.size())
        index -= m_lRadiusRight.size();
    unsigned int count = m_lRadiusRight.size();
    if (index < count)
        return m_lRadiusRight[index];
    return 0.0f;
}

float CPath::GetTweenedRadiusRight(float distance)
{
    while (distance < 0.0f)
        distance += m_fPathLength;
    while (distance > m_fPathLength)
        distance -= m_fPathLength;
    for (unsigned int i = 0; i < m_lPoints.size(); ++i) {
        unsigned int next = i + 1;
        if (next >= static_cast<unsigned int>(m_lPoints.size()))
            next -= m_lPoints.size();
        if (distance < m_lPointDistance[next] || next == 0) {
            float segment = m_lPointDistance[next] - m_lPointDistance[i];
            if (next == 0 && m_bClosedPath)
                segment = m_fPathLength - m_lPointDistance[i];
            return m_lRadiusRight[i] + (m_lRadiusRight[next] - m_lRadiusRight[i]) *
                ((distance - m_lPointDistance[i]) / segment);
        }
    }
    return 0.0f;
}

float CPath::GetTweenedRadiusLeft(float distance)
{
    while (distance < 0.0f)
        distance += m_fPathLength;
    while (distance > m_fPathLength)
        distance -= m_fPathLength;
    for (unsigned int i = 0; i < m_lPoints.size(); ++i) {
        unsigned int next = i + 1;
        if (next >= static_cast<unsigned int>(m_lPoints.size()))
            next -= m_lPoints.size();
        if (distance < m_lPointDistance[next] || next == 0) {
            float segment = m_lPointDistance[next] - m_lPointDistance[i];
            if (next == 0 && m_bClosedPath)
                segment = m_fPathLength - m_lPointDistance[i];
            return m_lRadiusLeft[i] + (m_lRadiusLeft[next] - m_lRadiusLeft[i]) *
                ((distance - m_lPointDistance[i]) / segment);
        }
    }
    return 0.0f;
}

float CPath::GetAngleOverDistance(float fromDistance, float toDistance)
{
    if (fromDistance >= toDistance)
        return 0.0f;
    fromDistance = std::max(fromDistance, 0.0f);
    toDistance = std::min(toDistance, m_fPathLength);
    int first = -1, last = -1;
    for (unsigned int i = 0; i < m_lPoints.size(); ++i) {
        if (i == 0)
            continue;
        if (first == -1 && fromDistance < m_lPointDistance[i])
            first = i;
        if (last == -1 && toDistance < m_lPointDistance[i])
            last = i;
        if (first != -1 && last != -1)
            break;
    }
    float angle = 0.0f;
    for (int i = first + 1; i <= last; ++i) {
        if (i == last)
            angle += (toDistance - m_lPointDistance[i - 1]) /
                (m_lPointDistance[i] - m_lPointDistance[i - 1]) * m_lSegmentAngle[i];
        else
            angle += m_lSegmentAngle[i];
    }
    return angle;
}

Ogre::Vector3 CPath::GetPathSegment(unsigned int index)
{
    if (m_lPoints.size() <= 1 || index > m_lPoints.size() - 2)
        return Ogre::Vector3::ZERO;
    return m_lPoints[index + 1] - m_lPoints[index];
}

Ogre::Vector3 CPath::GetPositionAtDistance(float distance)
{
    while (distance < 0.0f)
        distance += m_fPathLength;
    while (distance > m_fPathLength)
        distance -= m_fPathLength;
    Ogre::Vector3 position = Ogre::Vector3::ZERO;
    if (distance == m_fPathLength)
        position = m_lPoints[m_lPoints.size() - 1];
    else if (distance == 0.0f)
        position = m_lPoints[0];
    else {
        for (unsigned int i = 0; i < m_lPoints.size(); ++i) {
            unsigned int next = i + 1;
            if (next >= static_cast<unsigned int>(m_lPoints.size()))
                next -= m_lPoints.size();
            if (distance < m_lPointDistance[next] || next == 0) {
                Ogre::Vector3 direction = m_lPoints[next] - m_lPoints[i];
                direction.normalise();
                position = direction * (distance - m_lPointDistance[i]) + m_lPoints[i];
                break;
            }
        }
    }
    return position + m_vOrigin;
}

Ogre::Vector3 CPath::GetSegmentPerpendicularY(unsigned int index)
{
    if (m_lPoints.size() <= 1 || index > m_lPoints.size() - 1)
        return Ogre::Vector3::ZERO;
    unsigned int next = index + 1;
    if (next == static_cast<unsigned int>(m_lPoints.size()) && m_bClosedPath)
        next = 0;
    Ogre::Vector3 perpendicular(m_lPoints[next].z - m_lPoints[index].z,
                               0.0f,
                               -(m_lPoints[next].x - m_lPoints[index].x));
    perpendicular.normalise();
    return perpendicular;
}

Ogre::Vector3 CPath::GetSplinePositionAtDistance(float distance)
{
    if (m_fPathLength == 0.0f)
        return m_vOrigin;
    if (m_bClosedPath) {
        if (distance > m_fPathLength) distance = m_fPathLength;
        if (distance < 0.0f) distance = 0.0f;
    } else {
        while (distance < 0.0f) distance += m_fPathLength;
        while (distance > m_fPathLength) distance -= m_fPathLength;
    }
    int count = m_lPoints.size();
    int current = count - 1;
    for (; current >= 0; --current)
        if (distance > m_lPointDistance[current])
            break;
    int previous = current - 1;
    int next = current + 1;
    int afterNext = current + 2;
    if (current == -1) {
        previous = -1;
        current = 0;
        next = 1;
        afterNext = 2;
    }
    if (distance == m_fPathLength)
        return m_lPoints[count - 1] + m_vOrigin;
    if (distance == 0.0f)
        return m_lPoints[0] + m_vOrigin;
    if (previous == -1)
        previous = m_bClosedPath ? count - 1 : 0;
    if (next >= count)
        next = m_bClosedPath ? next - count : count - 1;
    if (afterNext >= count)
        afterNext = m_bClosedPath ? afterNext - count : count - 1;
    float segmentLength = m_lPointDistance[next] - m_lPointDistance[current];
    if (segmentLength < 0.0f)
        segmentLength += m_fPathLength;
    float t = distance - m_lPointDistance[current];
    if (m_lPointDistance[current] > distance)
        t += m_fPathLength;
    t /= segmentLength;
    float t2 = t * t;
    float t3 = t2 * t;
    const Ogre::Vector3 p0 = m_lPoints[previous];
    const Ogre::Vector3 p1 = m_lPoints[current];
    const Ogre::Vector3 p2 = m_lPoints[next];
    const Ogre::Vector3 p3 = m_lPoints[afterNext];
    return Ogre::Vector3(
        (2.0f*p1.x + (p2.x-p0.x)*t + (2.0f*p0.x + -5.0f*p1.x + 4.0f*p2.x-p3.x)*t2 + (3.0f*p1.x-p0.x + -3.0f*p2.x+p3.x)*t3)*0.5f + m_vOrigin.x,
        (2.0f*p1.y + (p2.y-p0.y)*t + (2.0f*p0.y + -5.0f*p1.y + 4.0f*p2.y-p3.y)*t2 + (3.0f*p1.y-p0.y + -3.0f*p2.y+p3.y)*t3)*0.5f + m_vOrigin.y,
        (2.0f*p1.z + (p2.z-p0.z)*t + (2.0f*p0.z + -5.0f*p1.z + 4.0f*p2.z-p3.z)*t2 + (3.0f*p1.z-p0.z + -3.0f*p2.z+p3.z)*t3)*0.5f + m_vOrigin.z);
}

bool CPath::FindNearestPoint(const Ogre::Vector3& target,
    Ogre::Vector3& nearestPoint, Ogre::Vector3& offset,
    unsigned int& pointIndex, float& distance, float minimumDistance)
{
    unsigned int segmentCount = m_lPoints.size();
    if (segmentCount <= 1)
        return false;
    if (!m_bClosedPath) {
        --segmentCount;
        if (minimumDistance > m_fPathLength)
            minimumDistance = m_fPathLength;
    }
    Ogre::Vector3 relativeTarget = target - m_vOrigin;
    nearestPoint = m_lPoints[0];
    offset = relativeTarget - nearestPoint;
    pointIndex = 0;
    distance = 0.0f;
    float closestDistance = 99999.0f;
    for (unsigned int i = 0; i < segmentCount; ++i) {
        if (closestDistance == 99999.0f && m_lPointDistance[i] >= minimumDistance) {
            Ogre::Vector3 candidateOffset = relativeTarget - m_lPoints[i];
            float separation = candidateOffset.length();
            if (separation < closestDistance) {
                nearestPoint = m_lPoints[i];
                offset = candidateOffset;
                pointIndex = i;
                distance = m_lPointDistance[i];
                closestDistance = separation;
            }
        }
        unsigned int next = i + 1;
        if (next >= m_lPoints.size())
            next -= m_lPoints.size();
        Ogre::Vector3 start = m_lPoints[i];
        Ogre::Vector3 segment = m_lPoints[next] - start;
        float length = segment.length();
        Ogre::Vector3 fromStart = relativeTarget - start;
        float parameter = (fromStart.x*segment.x + fromStart.z*segment.z + fromStart.y*segment.y) / (length*length);
        if (parameter < 0.0f || parameter > 1.0f) {
            float pathDistance = next == 0 ? m_fPathLength : m_lPointDistance[next];
            if (minimumDistance > pathDistance) {
                parameter += (1.0f / length) * (1.0f + (minimumDistance-pathDistance));
                if (parameter > 1.0f) parameter = 1.0f;
                pathDistance = m_lPointDistance[i] + parameter * length;
            }
            if (pathDistance >= minimumDistance) {
                Ogre::Vector3 candidateOffset = relativeTarget - m_lPoints[next];
                float separation = candidateOffset.length();
                if (separation < closestDistance) {
                    nearestPoint = m_lPoints[next];
                    offset = candidateOffset;
                    pointIndex = i;
                    distance = pathDistance;
                    closestDistance = separation;
                }
            }
        } else {
            float pathDistance = m_lPointDistance[i] + parameter * length;
            if (minimumDistance > pathDistance) {
                parameter += (1.0f / length) * (1.0f + (minimumDistance-pathDistance));
                if (parameter > 1.0f) parameter = 1.0f;
                pathDistance = m_lPointDistance[i] + parameter * length;
            }
            if (pathDistance >= minimumDistance) {
                Ogre::Vector3 candidatePoint = start + segment * parameter;
                Ogre::Vector3 candidateOffset = relativeTarget - candidatePoint;
                float separation = candidateOffset.length();
                if (separation < closestDistance) {
                    nearestPoint = candidatePoint;
                    offset = candidateOffset;
                    pointIndex = i;
                    distance = pathDistance;
                    closestDistance = separation;
                }
            }
        }
    }
    if (closestDistance == 99999.0f)
        return false;
    nearestPoint += m_vOrigin;
    return true;
}
