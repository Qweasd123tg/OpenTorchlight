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



unsigned int CCollisionList::getMemoryUsage()
{
    unsigned int vectors = m_FaceMinBounds.size();
    vectors += m_FaceMaxBounds.size();
    vectors += m_Vertices.size();
    vectors += m_Colors.size();
    vectors += m_Normals.size();
    unsigned int indices = m_IndicesA.size();
    indices += m_IndicesB.size();
    indices += m_IndicesC.size();
    indices += m_Materials.size();
    return vectors * sizeof(Ogre::Vector3) + indices * sizeof(unsigned int) + 24;
}

CCollisionList::CCollisionList()
    : m_vBoundsMin(0, 0, 0), m_vBoundsMax(0, 0, 0), m_iIgnoredMaterial(100000)
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

void CCollisionList::optimize()
{
    for (unsigned int i = 0; i < m_Vertices.size(); ++i)
        for (unsigned int j = i + 1; j < m_Vertices.size(); ++j)
            if (m_Vertices[i] == m_Vertices[j])
            {
                for (unsigned int face = 0; face < m_IndicesA.size(); ++face)
                {
                    if (m_IndicesA[face] == j) m_IndicesA[face] = i;
                    if (m_IndicesB[face] == j) m_IndicesB[face] = i;
                    if (m_IndicesC[face] == j) m_IndicesC[face] = i;
                }
                unsigned int last = m_Vertices.size() - 1;
                m_Vertices[j] = m_Vertices[last];
                m_Vertices.pop_back();
                for (unsigned int face = 0; face < m_IndicesA.size(); ++face)
                {
                    if (m_IndicesA[face] == last) m_IndicesA[face] = j;
                    if (m_IndicesB[face] == last) m_IndicesB[face] = j;
                    if (m_IndicesC[face] == last) m_IndicesC[face] = j;
                }
            }
}

void CCollisionList::calculateNormals()
{
    Ogre::Vector3 normal(0, 0, 0);
    m_Normals.clear();
    for (unsigned int i = 0; i < m_IndicesA.size(); ++i)
    {
        const Ogre::Vector3& a = m_Vertices[m_IndicesA[i]];
        const Ogre::Vector3& b = m_Vertices[m_IndicesB[i]];
        const Ogre::Vector3& c = m_Vertices[m_IndicesC[i]];
        normal = (c - b).crossProduct(b - a);
        normal.normalise();
        m_Normals.push_back(normal);
    }
}

void CCollisionList::calculateFaceBounds()
{
    if (m_Vertices.empty()) return;
    m_vBoundsMax = m_vBoundsMin = m_Vertices[0];
    for (unsigned int i = 0; i < m_Vertices.size(); ++i)
        MATH::expandBounds(m_vBoundsMax, m_vBoundsMin, m_Vertices[i]);
    m_FaceMaxBounds.clear();
    m_FaceMinBounds.clear();
    for (unsigned int i = 0; i < m_IndicesA.size(); ++i)
    {
        m_FaceMinBounds.push_back(m_Vertices[m_IndicesA[i]]);
        m_FaceMaxBounds.push_back(m_Vertices[m_IndicesA[i]]);
        MATH::expandBounds(m_FaceMinBounds[i], m_FaceMaxBounds[i], m_Vertices[m_IndicesB[i]]);
        MATH::expandBounds(m_FaceMinBounds[i], m_FaceMaxBounds[i], m_Vertices[m_IndicesC[i]]);
    }
}

bool CCollisionList::pointIn(const Ogre::Vector3& point, int face)
{
    const Ogre::Vector3& a = m_Vertices[m_IndicesA[face]];
    const Ogre::Vector3& b = m_Vertices[m_IndicesB[face]];
    const Ogre::Vector3& c = m_Vertices[m_IndicesC[face]];
    const Ogre::Vector3& normal = m_Normals[face];
    Ogre::Vector3 offset = point - a;
    Ogre::Vector3 edge = b - a;
    Ogre::Vector3 side = normal.crossProduct(c - a);
    float u = offset.dotProduct(side);
    if (u < 0.0f) return false;
    float total = edge.dotProduct(side);
    if (u > total) return false;
    float v = offset.crossProduct(edge).dotProduct(normal);
    if (v < 0.0f) return false;
    return u + v <= total;
}

void CCollisionList::addCollisionList(CCollisionList* list, const Ogre::Matrix4& transform, int material)
{
    unsigned int first = m_Vertices.size();
    for (unsigned int i = 0; i < static_cast<unsigned int>(list->getVertexCount()); ++i)
        addVertex(transform * list->m_Vertices[i], -1);
    for (unsigned int i = 0; i < list->m_Colors.size(); ++i)
        addColor(list->m_Colors[i], -1);
    for (unsigned int i = 0; i < static_cast<unsigned int>(list->getFaceCount()); ++i)
        addFace(first + list->m_IndicesA[i], first + list->m_IndicesB[i], first + list->m_IndicesC[i],
                material == -1 ? list->m_Materials[i] : static_cast<unsigned int>(material), -1);
}

bool CCollisionList::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
    const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax,
    Ogre::Vector3& hit, Ogre::Vector3& normal, unsigned int& material,
    Ogre::Vector3& faceNormal, float& distance)
{
    distance = 99999.0f;
    if (m_IndicesA.size() != 0 && MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
        for (unsigned int i = 0; i < m_IndicesA.size(); ++i)
        {
            if (m_Materials[i] == m_iIgnoredMaterial) continue;
            unsigned int face = i;
            if (!MATH::boundsIntersect(m_FaceMinBounds[face], m_FaceMaxBounds[face], boundsMin, boundsMax)) continue;
            EPLANE_SIDE from = MATH::classifyPoint(start, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            EPLANE_SIDE to = MATH::classifyPoint(end, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            if (from == PLANE_SIDE_BACK || from == to) continue;
            Ogre::Vector3 offset = end;
            Ogre::Vector3 intersection(0, 0, 0);
            if (!MATH::getLinePlaneIntersection(start, end, m_Vertices[m_IndicesA[face]], m_Normals[face], intersection)) continue;
            if (!pointIn(intersection, face)) continue;
            offset = intersection - start;
            float length = offset.length();
            if (length < distance)
            {
                distance = length;
                hit = intersection;
                normal = m_Normals[face];
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else
                    faceNormal = Ogre::Vector3(1, 1, 1);
            }
        }
    return distance != 99999.0f;
}

bool CCollisionList::rayCollision(const std::vector<unsigned int>& faces, const Ogre::Vector3& start, const Ogre::Vector3& end,
    const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax,
    Ogre::Vector3& hit, Ogre::Vector3& normal, unsigned int& material,
    Ogre::Vector3& faceNormal, float& distance)
{
    if (faces.size() != 0 && MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
        for (unsigned int i = 0; i < faces.size(); ++i)
        {
            if (m_Materials[i] == m_iIgnoredMaterial) continue;
            unsigned int face = faces[i];
            if (!MATH::boundsIntersect(m_FaceMinBounds[face], m_FaceMaxBounds[face], boundsMin, boundsMax)) continue;
            EPLANE_SIDE from = MATH::classifyPoint(start, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            EPLANE_SIDE to = MATH::classifyPoint(end, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            if (from == PLANE_SIDE_BACK || from == to) continue;
            Ogre::Vector3 offset = end;
            Ogre::Vector3 intersection(0, 0, 0);
            if (!MATH::getLinePlaneIntersection(start, end, m_Vertices[m_IndicesA[face]], m_Normals[face], intersection)) continue;
            if (!pointIn(intersection, face)) continue;
            offset = intersection - start;
            float length = offset.length();
            if (length < distance)
            {
                distance = length;
                hit = intersection;
                normal = m_Normals[face];
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else
                    faceNormal = Ogre::Vector3(1, 1, 1);
            }
        }
    return distance != 99999.0f;
}

bool CCollisionList::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
    const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax, float radius,
    Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal,
    unsigned int& material, Ogre::Vector3& faceNormal, float& distance)
{
    if (m_IndicesA.size() != 0 && MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
    {
        float bestAlignment = 1.0f;
        for (unsigned int i = 0; i < m_IndicesA.size(); ++i)
        {
            if (m_Materials[i] == m_iIgnoredMaterial) continue;
            unsigned int face = i;
            if (!MATH::boundsIntersect(m_FaceMinBounds[face], m_FaceMaxBounds[face], boundsMin, boundsMax)) continue;
            EPLANE_SIDE from = MATH::classifyPoint(start, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            EPLANE_SIDE to = MATH::classifyPointForSphere(end, m_Vertices[m_IndicesA[face]], m_Normals[face], radius);
            if (to == PLANE_SIDE_FRONT || from == to) continue;
            Ogre::Vector3 offset = end;
            Ogre::Vector3 intersection(0, 0, 0);
            offset -= m_Normals[face] * radius;
            if (!MATH::getSpherePlaneIntersection(start, offset, m_Vertices[m_IndicesA[face]], m_Normals[face], intersection)) continue;
            if (pointIn(intersection, face))
            {
                offset = intersection - start;
                float length = offset.length();
                if (!(length < distance)) continue;
                distance = length;
                hit = intersection;
                position = intersection + m_Normals[face] * radius;
                normal = m_Normals[face];
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else faceNormal = Ogre::Vector3(1, 1, 1);
            }
            else
            {
                MATH::closestPointOnTriangle(m_Vertices[m_IndicesA[face]], m_Vertices[m_IndicesB[face]], m_Vertices[m_IndicesC[face]], start, intersection);
                offset = end - intersection;
                if (!(radius >= offset.length())) continue;
                offset = intersection - start;
                float length = offset.length();
                if (!(distance >= length)) continue;
                offset = end - intersection;
                offset.normalise();
                // The subset overload compares this normal against the loop index.
                float alignment = offset.dotProduct(m_Normals[face]);
                if (!(alignment < bestAlignment)) continue;
                if (MATH::classifyPoint(end, m_Vertices[m_IndicesA[face]], m_Normals[face]) != PLANE_SIDE_FRONT) continue;
                distance = length;
                normal = offset;
                hit = intersection;
                position = intersection + normal * radius;
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else faceNormal = Ogre::Vector3(1, 1, 1);
                bestAlignment = alignment;
            }
        }
    }
    return distance != 99999.0f;
}

bool CCollisionList::sphereCollision(const std::vector<unsigned int>& faces, const Ogre::Vector3& start, const Ogre::Vector3& end,
    const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax, float radius,
    Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal,
    unsigned int& material, Ogre::Vector3& faceNormal, float& distance)
{
    if (faces.size() != 0 && MATH::boundsIntersect(m_vBoundsMax, m_vBoundsMin, boundsMin, boundsMax))
    {
        float bestAlignment = 1.0f;
        for (unsigned int i = 0; i < faces.size(); ++i)
        {
            if (m_Materials[i] == m_iIgnoredMaterial) continue;
            unsigned int face = faces[i];
            if (!MATH::boundsIntersect(m_FaceMinBounds[face], m_FaceMaxBounds[face], boundsMin, boundsMax)) continue;
            EPLANE_SIDE from = MATH::classifyPoint(start, m_Vertices[m_IndicesA[face]], m_Normals[face]);
            EPLANE_SIDE to = MATH::classifyPointForSphere(end, m_Vertices[m_IndicesA[face]], m_Normals[face], radius);
            if (to == PLANE_SIDE_FRONT || from == to) continue;
            Ogre::Vector3 offset = end;
            Ogre::Vector3 intersection(0, 0, 0);
            offset -= m_Normals[face] * radius;
            if (!MATH::getSpherePlaneIntersection(start, offset, m_Vertices[m_IndicesA[face]], m_Normals[face], intersection)) continue;
            if (pointIn(intersection, face))
            {
                offset = intersection - start;
                float length = offset.length();
                if (!(distance >= length)) continue;
                distance = length;
                hit = intersection;
                position = intersection + m_Normals[face] * radius;
                normal = m_Normals[face];
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else faceNormal = Ogre::Vector3(1, 1, 1);
            }
            else
            {
                MATH::closestPointOnTriangle(m_Vertices[m_IndicesA[face]], m_Vertices[m_IndicesB[face]], m_Vertices[m_IndicesC[face]], start, intersection);
                offset = end - intersection;
                if (!(radius >= offset.length())) continue;

                float length = offset.length();
                if (!(distance >= length)) continue;
                offset = end - intersection;
                offset.normalise();
                // The subset overload compares this normal against the loop index.
                float alignment = offset.dotProduct(m_Normals[i]);
                if (!(alignment < bestAlignment)) continue;
                if (MATH::classifyPoint(end, m_Vertices[m_IndicesA[face]], m_Normals[face]) != PLANE_SIDE_FRONT) continue;
                distance = length;
                normal = offset;
                hit = intersection;
                position = intersection + normal * radius;
                material = m_Materials[face];
                if (m_IndicesA[face] < m_Colors.size())
                    faceNormal = (m_Colors[m_IndicesA[face]] + m_Colors[m_IndicesB[face]] + m_Colors[m_IndicesC[face]]) * (1.0f / 3.0f);
                else faceNormal = Ogre::Vector3(1, 1, 1);
                bestAlignment = alignment;
            }
        }
    }
    return distance != 99999.0f;
}
