#include "EmptyStrings.h"
#include "CollisionList.h"
#include "RunicCore.h"
#include "UtilitiesMath.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"

unsigned int CCollisionList::getMemoryUsage()
{
    return sizeof(m_vBoundsMin) + sizeof(m_vBoundsMax)
        + (m_FaceMaxBounds.capacity() + m_FaceMinBounds.capacity()
           + m_Vertices.capacity() + m_Colors.capacity()
           + m_Normals.capacity()) * sizeof(Ogre::Vector3)
        + (m_IndicesA.capacity() + m_IndicesB.capacity()
           + m_IndicesC.capacity() + m_Materials.capacity()) * sizeof(unsigned int);
}

Ogre::Vector3& CCollisionList::getVertex(unsigned int index)
{
    return m_Vertices[index];
}

Ogre::Vector3& CCollisionList::getNormal(unsigned int index)
{
    return m_Normals[index];
}

Ogre::Vector3& CCollisionList::getMinFaceBounds(unsigned int face)
{
    return m_FaceMinBounds[face];
}

Ogre::Vector3& CCollisionList::getMaxFaceBounds(unsigned int index)
{
    return m_FaceMaxBounds[index];
}

unsigned int CCollisionList::getVertexIndex(unsigned int face, unsigned int corner)
{
    if (corner == 0)
        return m_IndicesA[face];

    if (corner == 1)
        return m_IndicesB[face];

    return m_IndicesC[face];
}

unsigned int CCollisionList::getVertexIndexA(unsigned int index)
{
    return m_IndicesA[index];
}

unsigned int CCollisionList::getVertexIndexB(unsigned int index)
{
    return m_IndicesB[index];
}

unsigned int CCollisionList::getVertexIndexC(unsigned int face)
{
    return m_IndicesC[face];
}

unsigned int CCollisionList::getMaterial(unsigned int face)
{
    return m_Materials[face];
}

void CCollisionList::optimize()
{
    for (unsigned int i = 0; i < m_Vertices.size(); i++)
    {
        for (unsigned int j = i + 1; j < m_Vertices.size(); j++)
        {
            if (m_Vertices[i] == m_Vertices[j])
            {
                for (unsigned int k = 0; k < m_IndicesA.size(); k++)
                {
                    if (m_IndicesA[k] == j)
                        m_IndicesA[k] = i;
                    if (m_IndicesB[k] == j)
                        m_IndicesB[k] = i;
                    if (m_IndicesC[k] == j)
                        m_IndicesC[k] = i;
                }

                unsigned int last = m_Vertices.size() - 1;
                m_Vertices[j] = m_Vertices[last];
                m_Vertices.pop_back();

                for (unsigned int k = 0; k < m_IndicesA.size(); k++)
                {
                    if (m_IndicesA[k] == last)
                        m_IndicesA[k] = j;
                    if (m_IndicesB[k] == last)
                        m_IndicesB[k] = j;
                    if (m_IndicesC[k] == last)
                        m_IndicesC[k] = j;
                }
            }
        }
    }
}

bool CCollisionList::sphereCollision(
    const Ogre::Vector3& start,
    const Ogre::Vector3& end,
    const Ogre::Vector3& boundsMin,
    const Ogre::Vector3& boundsMax,
    float radius,
    Ogre::Vector3& position,
    Ogre::Vector3& hit,
    Ogre::Vector3& normal,
    unsigned int& material,
    Ogre::Vector3& faceNormal,
    float& distance)
{
    if (!m_IndicesA.empty() &&
        MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
    {
        float closestFaceDot = 1.0f;

        for (unsigned int face = 0; face < m_IndicesA.size(); ++face)
        {
            if (m_Materials[face] == m_iIgnoredMaterial)
                continue;

            if (!MATH::boundsIntersect(m_FaceMinBounds[face],
                                       m_FaceMaxBounds[face],
                                       boundsMin, boundsMax))
                continue;

            const Ogre::Vector3& vertex =
                m_Vertices[m_IndicesA[face]];
            const Ogre::Vector3& planeNormal = m_Normals[face];

            int pointClass = MATH::classifyPoint(start, vertex, planeNormal);
            if (MATH::classifyPointForSphere(end, vertex, planeNormal, radius) &&
                pointClass != MATH::classifyPointForSphere(end, vertex,
                                                          planeNormal, radius))
            {
                Ogre::Vector3 spherePosition =
                    end - planeNormal * radius;
                Ogre::Vector3 intersection;

                if (MATH::getSpherePlaneIntersection(start, spherePosition,
                                                     vertex, planeNormal,
                                                     intersection))
                {
                    if (pointIn(intersection, face))
                    {
                        float intersectionDistance =
                            (intersection - start).length();

                        if (intersectionDistance < distance)
                        {
                            distance = intersectionDistance;
                            hit = intersection;
                            normal = planeNormal;
                            position = intersection + planeNormal * radius;
                            material = m_Materials[face];

                            if (m_IndicesA[face] < m_Colors.size())
                                faceNormal =
                                    (m_Colors[m_IndicesA[face]] +
                                     m_Colors[m_IndicesB[face]] +
                                     m_Colors[m_IndicesC[face]]) / 3.0f;
                            else
                                faceNormal = Ogre::Vector3(1.0f, 1.0f, 1.0f);
                        }
                    }
                    else
                    {
                        Ogre::Vector3 closestPoint;
                        MATH::closestPointOnTriangle(
                            vertex,
                            m_Vertices[m_IndicesB[face]],
                            m_Vertices[m_IndicesC[face]],
                            start,
                            closestPoint);

                        if ((end - closestPoint).length() <= radius)
                        {
                            float closestDistance =
                                (closestPoint - start).length();

                            if (closestDistance <= distance)
                            {
                                Ogre::Vector3 collisionNormal =
                                    end - closestPoint;
                                collisionNormal.normalise();

                                if (collisionNormal.dotProduct(planeNormal) <
                                        closestFaceDot &&
                                    !MATH::classifyPoint(end, vertex,
                                                         planeNormal))
                                {
                                    distance = closestDistance;
                                    hit = closestPoint;
                                    normal = collisionNormal;
                                    position = closestPoint +
                                               collisionNormal * radius;
                                    material = m_Materials[face];
                                    closestFaceDot =
                                        collisionNormal.dotProduct(planeNormal);

                                    if (m_IndicesA[face] < m_Colors.size())
                                        faceNormal =
                                            (m_Colors[m_IndicesA[face]] +
                                             m_Colors[m_IndicesB[face]] +
                                             m_Colors[m_IndicesC[face]]) / 3.0f;
                                    else
                                        faceNormal =
                                            Ogre::Vector3(1.0f, 1.0f, 1.0f);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return distance != 1024.0f;
}

bool CCollisionList::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius,
                                     Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal,
                                     unsigned int& material, float& distance)
{
    Ogre::Vector3 boundsMin = start;
    Ogre::Vector3 boundsMax = start;
    MATH::expandBounds(boundsMin, boundsMax, end);
    boundsMin -= radius;
    boundsMax += radius;
    Ogre::Vector3 faceNormal;

    return sphereCollision(start, end, boundsMin, boundsMax, radius, position, hit, normal, material, faceNormal, distance);
}

bool CCollisionList::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius,
                                     Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal,
                                     float& distance)
{
    unsigned int material;
    return sphereCollision(start, end, radius, position, hit, normal, material, distance);
}

bool CCollisionList::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                     const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax,
                                     float radius, Ogre::Vector3& position, Ogre::Vector3& hit,
                                     Ogre::Vector3& normal, float& distance)
{
    Ogre::Vector3 faceNormal;
    unsigned int material;

    return sphereCollision(start, end, boundsMin, boundsMax, radius, position, hit, normal,
                           material, faceNormal, distance);
}

bool CCollisionList::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                  const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax,
                                  Ogre::Vector3& hit, Ogre::Vector3& normal,
                                  unsigned int& material, Ogre::Vector3& faceNormal,
                                  float& distance)
{
    distance = 99999.0f;

    if (!m_IndicesA.empty() &&
        MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
    {
        for (unsigned int face = 0; face < m_IndicesA.size(); ++face)
        {
            if (m_Materials[face] == m_iIgnoredMaterial ||
                !MATH::boundsIntersect(m_FaceMaxBounds[face], m_FaceMinBounds[face],
                                       boundsMin, boundsMax))
            {
                continue;
            }

            unsigned int indexA = m_IndicesA[face];
            char startSide = MATH::classifyPoint(start, m_Vertices[indexA], m_Normals[face]);
            char endSide = MATH::classifyPoint(end, m_Vertices[indexA], m_Normals[face]);

            if (startSide == 1 || startSide == endSide)
                continue;

            Ogre::Vector3 intersection = Ogre::Vector3::ZERO;
            if (!MATH::getLinePlaneIntersection(start, end, m_Vertices[indexA], m_Normals[face],
                                                 intersection) ||
                !pointIn(intersection, face))
            {
                continue;
            }

            float newDistance = (intersection - start).length();
            if (newDistance < distance)
            {
                distance = newDistance;
                hit = intersection;
                normal = m_Normals[face];
                material = m_Materials[face];

                if (indexA < m_Colors.size())
                {
                    faceNormal = (m_Colors[indexA] + m_Colors[m_IndicesB[face]] +
                                  m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                }
                else
                {
                    faceNormal = Ogre::Vector3(1.0f, 1.0f, 1.0f);
                }
            }
        }
    }

    return distance != 99999.0f;
}

bool CCollisionList::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                  Ogre::Vector3& hit, Ogre::Vector3& normal,
                                  unsigned int& material, float& distance)
{
    Ogre::Vector3 boundsMin = start;
    Ogre::Vector3 boundsMax = start;
    MATH::expandBounds(boundsMin, boundsMax, end);

    Ogre::Vector3 faceNormal;
    return rayCollision(start, end, boundsMin, boundsMax, hit, normal, material,
                        faceNormal, distance);
}

bool CCollisionList::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                  Ogre::Vector3& hit, Ogre::Vector3& normal, float& distance)
{
    unsigned int material;
    return rayCollision(start, end, hit, normal, material, distance);
}

bool CCollisionList::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                   const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax,
                                   Ogre::Vector3& hit, Ogre::Vector3& normal, float& distance)
{
    unsigned int material;
    Ogre::Vector3 faceNormal;
    return rayCollision(start, end, boundsMin, boundsMax, hit, normal, material, faceNormal, distance);
}

void CCollisionList::addNormal(const Ogre::Vector3& normal, int index)
{
    if (index == -1)
        m_Normals.push_back(normal);
    else if (index < (int)m_Normals.size())
        m_Normals[index] = normal;
}

void CCollisionList::addColor(const Ogre::Vector3& color, int index)
{
    if (index == -1)
        m_Colors.push_back(color);
    else if (index < static_cast<int>(m_Colors.size()))
        m_Colors[index] = color;
}

void CCollisionList::addVertex(const Ogre::Vector3& vertex, int index)
{
    if (index == -1)
        m_Vertices.push_back(vertex);
    else if (index < static_cast<int>(m_Vertices.size()))
        m_Vertices[index] = vertex;
}

void CCollisionList::calculateFaceBounds()
{
    if (!m_Vertices.empty()) {
        m_vBoundsMin = m_Vertices[0];
        m_vBoundsMax = m_Vertices[0];

        for (unsigned int i = 0; i < m_Vertices.size(); ++i)
            MATH::expandBounds(m_vBoundsMin, m_vBoundsMax, m_Vertices[i]);
    }

    for (unsigned int i = 0; i < m_IndicesA.size(); ++i) {
        m_FaceMinBounds.push_back(m_Vertices[m_IndicesA[i]]);
        m_FaceMaxBounds.push_back(m_Vertices[m_IndicesA[i]]);

        MATH::expandBounds(m_FaceMinBounds[i], m_FaceMaxBounds[i],
                           m_Vertices[m_IndicesB[i]]);
        MATH::expandBounds(m_FaceMinBounds[i], m_FaceMaxBounds[i],
                           m_Vertices[m_IndicesC[i]]);
    }
}

void CCollisionList::calculateNormals()
{
    m_Normals.clear();

    for (unsigned int i = 0; i < m_IndicesA.size(); ++i)
    {
        Ogre::Vector3 vNormal = m_Vertices[m_IndicesA[i]] - m_Vertices[m_IndicesB[i]];
        vNormal.crossProduct(m_Vertices[m_IndicesB[i]] - m_Vertices[m_IndicesC[i]]);

        float fLength = vNormal.length();
        if (fLength > 1e-12)
            vNormal *= 1.0f / fLength;

        m_Normals.push_back(vNormal);
    }
}

void CCollisionList::addFace(int a, int b, int c, unsigned int material, int index)
{
    if (index == -1)
    {
        m_Materials.push_back(material);
        m_IndicesA.push_back(a);
        m_IndicesB.push_back(b);
        m_IndicesC.push_back(c);
    }
    else
    {
        if (index < static_cast<int>(m_IndicesA.size()))
        {
            m_IndicesA[index] = a;
            m_IndicesB[index] = b;
            m_IndicesC[index] = c;
        }

        if (index < static_cast<int>(m_Materials.size()))
            m_Materials[index] = material;
    }
}

void CCollisionList::addFace(int a, int b, int c, int index)
{
    addFace(a, b, c, 1, index);
}

CCollisionList::~CCollisionList()
{
}

CCollisionList::CCollisionList()
    : CRunicCore(),
      m_vBoundsMin(0.0f, 0.0f, 0.0f),
      m_vBoundsMax(0.0f, 0.0f, 0.0f),
      m_iIgnoredMaterial(100000)
{
    m_FaceMaxBounds.reserve(10);
    m_FaceMinBounds.reserve(10);
    m_Vertices.reserve(10);
    m_Colors.reserve(10);
    m_Normals.reserve(10);
    m_IndicesA.reserve(10);
    m_IndicesB.reserve(10);
    m_IndicesC.reserve(10);
    m_Materials.reserve(10);
}
