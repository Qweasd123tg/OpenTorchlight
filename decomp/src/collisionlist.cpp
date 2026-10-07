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

