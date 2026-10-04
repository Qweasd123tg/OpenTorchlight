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
    m_fPathLength = 0.0f;
    m_vOrigin = Ogre::Vector3::ZERO;
    m_lPoints.clear();
    m_lRadiusLeft.clear();
    m_lRadiusRight.clear();
    m_lSegmentAngle.clear();
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
    TArrayList<float>& radii = const_cast<TArrayList<float>&>(m_lRadiusLeft);

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
    struct Vector3Buffer
    {
        Ogre::Vector3* data;
        Ogre::Vector3* end;
        Ogre::Vector3* capacity;
    };
    struct FloatBuffer
    {
        float* data;
        float* end;
        float* capacity;
    };

    Vector3Buffer& points =
        reinterpret_cast<Vector3Buffer&>(m_lPoints);
    FloatBuffer& radiusLeft =
        reinterpret_cast<FloatBuffer&>(m_lRadiusLeft);
    FloatBuffer& radiusRight =
        reinterpret_cast<FloatBuffer&>(m_lRadiusRight);

    Ogre::Vector3 nearestPoint;
    Ogre::Vector3 offset;
    unsigned int pointIndex = 0;
    float distance = 0.0f;

    for (unsigned int i = 0;
         i < static_cast<unsigned int>(points.end - points.data);
         ++i)
    {
        if (leftPath.FindNearestPoint(points.data[i], nearestPoint, offset,
                                      pointIndex, distance, 0.0f))
        {
            offset.normalise();
            offset = -offset;

            Ogre::Vector3 pointOffset = points.data[i] - nearestPoint;
            pointOffset.y = 0.0f;

            radiusLeft.data[i] = offset.dotProduct(pointOffset);
            if (radiusLeft.data[i] < 0.0f)
                radiusLeft.data[i] = 0.0f;
        }

        if (rightPath.FindNearestPoint(points.data[i], nearestPoint, offset,
                                       pointIndex, distance, 0.0f))
        {
            offset.normalise();

            Ogre::Vector3 pointOffset = points.data[i] - nearestPoint;
            pointOffset.y = 0.0f;

            radiusRight.data[i] = offset.dotProduct(pointOffset);
            if (radiusRight.data[i] > 0.0f)
                radiusRight.data[i] = 0.0f;
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

    m_lPoints.add(point);
    m_lRadiusLeft.add(radiusLeft);
    m_lRadiusRight.add(radiusRight);

    if (m_lPoints.size() > 1)
    {
        Ogre::Vector3 segment = m_lPoints[m_lPoints.size() - 1] -
                                 m_lPoints[m_lPoints.size() - 2];
        float segmentLength = sqrtf(segment.squaredLength());

        m_fPathLength += segmentLength;
        m_lPointDistance.add(m_lPointDistance[m_lPointDistance.size() - 1] +
                             segmentLength);
        m_lSegmentAngle.add(0.0f);

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
        m_lPointDistance.add(0.0f);
        m_lSegmentAngle.add(0.0f);
        m_fPathLength = 0.0f;
    }
}

void CPath::Reverse()
{
    typedef Ogre::Vector3* PointPointer;

    PointPointer* pointStorage =
        reinterpret_cast<PointPointer*>(&m_lPoints);
    PointPointer pointBegin = pointStorage[0];
    PointPointer pointEnd = pointStorage[1];

    unsigned int pointCount =
        static_cast<unsigned int>((pointEnd - pointBegin) /
                                  sizeof(Ogre::Vector3));
    Ogre::Vector3* points = 0;

    if (pointCount != 0)
        points = new Ogre::Vector3[pointCount];

    for (unsigned int i = 0; i < pointCount; ++i)
        points[i] = pointBegin[i];

    m_fPathLength = 0.0f;
    m_vOrigin = Ogre::Vector3(0.0f, 0.0f, 0.0f);

    pointStorage = reinterpret_cast<PointPointer*>(&m_lPoints);
    pointStorage[1] = pointStorage[0];

    pointStorage = reinterpret_cast<PointPointer*>(&m_lRadiusLeft);
    pointStorage[1] = pointStorage[0];

    pointStorage = reinterpret_cast<PointPointer*>(&m_lRadiusRight);
    pointStorage[1] = pointStorage[0];

    pointStorage = reinterpret_cast<PointPointer*>(&m_lSegmentAngle);
    pointStorage[1] = pointStorage[0];

    pointStorage = reinterpret_cast<PointPointer*>(&m_lPointDistance);
    pointStorage[1] = pointStorage[0];

    for (unsigned int i = pointCount; i != 0; --i)
        AddPoint(points[i - 1], -60.0f, 60.0f);

    if (m_bClosedPath)
        ClosePath();

    delete[] points;
}

CPath::CPath(std::wstring name, bool closed, const Ogre::Vector3& origin)
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
    float *data = *reinterpret_cast<float **>(&m_lRadiusRight);
    long end = *reinterpret_cast<long *>(
        reinterpret_cast<char *>(&m_lRadiusRight) + 8);
    long size = (end - reinterpret_cast<long>(data)) / 4;

    if (static_cast<unsigned long>(index) <
        static_cast<unsigned long>(size))
    {
        data[index] = radius;
    }
}

void CPath::Resize(unsigned int pointCount)
{
    Ogre::Vector3** points =
        reinterpret_cast<Ogre::Vector3**>(&m_lPoints);
    Ogre::Vector3* firstPoint = points[0];
    Ogre::Vector3* lastPoint = points[1];

    if (pointCount < (unsigned int)(lastPoint - firstPoint))
        return;

    std::vector<Ogre::Vector3> oldPoints(firstPoint, lastPoint);

    m_fPathLength = 0.0f;
    m_vOrigin.x = 0.0f;
    m_vOrigin.y = 0.0f;
    m_vOrigin.z = 0.0f;

    points[1] = points[0];

    float** radiusLeft = reinterpret_cast<float**>(&m_lRadiusLeft);
    radiusLeft[1] = radiusLeft[0];

    float** radiusRight = reinterpret_cast<float**>(&m_lRadiusRight);
    radiusRight[1] = radiusRight[0];

    float** segmentAngles = reinterpret_cast<float**>(&m_lSegmentAngle);
    segmentAngles[1] = segmentAngles[0];

    float** pointDistances = reinterpret_cast<float**>(&m_lPointDistance);
    pointDistances[1] = pointDistances[0];

    for (unsigned int i = 0; i < pointCount; ++i)
    {
        unsigned int index =
            (unsigned int)floorf((float)i *
                                 ((float)(lastPoint - firstPoint) /
                                  (float)pointCount) + 0.5f);
        AddPoint(oldPoints[index], -60.0f, 60.0f);
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
