#ifndef COLLISIONLIST_H
#define COLLISIONLIST_H

#include <vector>

#include <OgreVector3.h>

#include "RunicCore.h"

namespace Ogre { class Matrix4; }

// Triangle soup used for unit and level collision: vertices, per-face corner
// indices, materials, normals and face bounds. Size 0x108.
class CCollisionList : public CRunicCore
{
public:
    CCollisionList();
    virtual ~CCollisionList();

    unsigned int getMemoryUsage();
    Ogre::Vector3& getVertex(unsigned int index);
    Ogre::Vector3& getNormal(unsigned int face);
    Ogre::Vector3& getMinFaceBounds(unsigned int face);
    Ogre::Vector3& getMaxFaceBounds(unsigned int face);
    unsigned int getVertexIndex(unsigned int face, unsigned int corner);
    unsigned int getVertexIndexA(unsigned int face);
    unsigned int getVertexIndexB(unsigned int face);
    unsigned int getVertexIndexC(unsigned int face);
    unsigned int getMaterial(unsigned int face);
    int getVertexCount() { return m_Vertices.size(); }
    int getFaceCount() { return m_IndicesA.size(); }

    void optimize();
    bool pointIn(const Ogre::Vector3& point, int face);

    bool sphereCollision(const std::vector<unsigned int>& faces, const Ogre::Vector3& start, const Ogre::Vector3& end,
                         const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax, float radius,
                         Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal, unsigned int& material,
                         Ogre::Vector3& faceNormal, float& distance);
    bool sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& boundsMin,
                         const Ogre::Vector3& boundsMax, float radius, Ogre::Vector3& position, Ogre::Vector3& hit,
                         Ogre::Vector3& normal, unsigned int& material, Ogre::Vector3& faceNormal, float& distance);
    bool sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius, Ogre::Vector3& position,
                         Ogre::Vector3& hit, Ogre::Vector3& normal, unsigned int& material, float& distance);
    bool sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius, Ogre::Vector3& position,
                         Ogre::Vector3& hit, Ogre::Vector3& normal, float& distance);
    bool sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& boundsMin,
                         const Ogre::Vector3& boundsMax, float radius, Ogre::Vector3& position, Ogre::Vector3& hit,
                         Ogre::Vector3& normal, float& distance);

    bool rayCollision(const std::vector<unsigned int>& faces, const Ogre::Vector3& start, const Ogre::Vector3& end,
                      const Ogre::Vector3& boundsMin, const Ogre::Vector3& boundsMax, Ogre::Vector3& hit,
                      Ogre::Vector3& normal, unsigned int& material, Ogre::Vector3& faceNormal, float& distance);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& boundsMin,
                      const Ogre::Vector3& boundsMax, Ogre::Vector3& hit, Ogre::Vector3& normal,
                      unsigned int& material, Ogre::Vector3& faceNormal, float& distance);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit, Ogre::Vector3& normal,
                      unsigned int& material, float& distance);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit, Ogre::Vector3& normal,
                      float& distance);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& boundsMin,
                      const Ogre::Vector3& boundsMax, Ogre::Vector3& hit, Ogre::Vector3& normal, float& distance);

    // index -1 appends, a valid index overwrites, anything else is ignored.
    void addNormal(const Ogre::Vector3& normal, int index);
    void addColor(const Ogre::Vector3& color, int index);
    void addVertex(const Ogre::Vector3& vertex, int index);
    void addFace(int a, int b, int c, unsigned int material, int index);
    void addFace(int a, int b, int c, int index);
    void addCollisionList(CCollisionList* list, const Ogre::Matrix4& transform, int material);

    void calculateFaceBounds();
    void calculateNormals();

private:
    Ogre::Vector3 m_vBoundsMin;
    Ogre::Vector3 m_vBoundsMax;
    std::vector<Ogre::Vector3> m_FaceMaxBounds;
    std::vector<Ogre::Vector3> m_FaceMinBounds;
    std::vector<Ogre::Vector3> m_Vertices;
    std::vector<Ogre::Vector3> m_Colors;
    std::vector<Ogre::Vector3> m_Normals;
    std::vector<unsigned int> m_IndicesA;
    std::vector<unsigned int> m_IndicesB;
    std::vector<unsigned int> m_IndicesC;
    std::vector<unsigned int> m_Materials;
    // Faces with this material are skipped by the collision queries.
    unsigned int m_iIgnoredMaterial;
};

#endif
