#include "EmptyStrings.h"

#include <cmath>

#include <OgreCamera.h>
#include <OgreMatrix4.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include "Constants.h"
#include "QuestDefines.h"
#include "UtilitiesMath.h"

float Percentage;
float LineLength;
float DistanceFromPlane;
float DeltaX;
float DeltaY;
float DeltaZ;
float ToPlaneX;
float ToPlaneY;
float ToPlaneZ;

static const float kPlaneEpsilon = 0.00001f;

namespace MATH
{

unsigned long vectorToRGB(const Ogre::Vector3& vector)
{
    unsigned long red = (unsigned long)(vector.x * 127.0f + 128.0f);
    unsigned long green = (unsigned long)(vector.y * 127.0f + 128.0f);
    unsigned long blue = (unsigned long)(vector.z * 127.0f + 128.0f);
    return 0xff000000 + (red << 16) + (green << 8) + blue;
}

bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& innerMinimum,
                    const Ogre::Vector3& innerMaximum)
{
    return maximum.x >= innerMaximum.x && maximum.y >= innerMaximum.y && maximum.z >= innerMaximum.z &&
           innerMinimum.x >= minimum.x && innerMinimum.y >= minimum.y && innerMinimum.z >= minimum.z;
}

bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& otherMinimum,
                     const Ogre::Vector3& otherMaximum)
{
    return boundsIntersectXY(minimum, maximum, otherMinimum, otherMaximum) && otherMaximum.y >= minimum.y &&
           maximum.y >= otherMinimum.y;
}

bool boundsContainsXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& innerMinimum,
                      const Ogre::Vector3& innerMaximum)
{
    return maximum.x >= innerMaximum.x && maximum.z >= innerMaximum.z && innerMinimum.x >= minimum.x &&
           innerMinimum.z >= minimum.z;
}

bool boundsIntersectXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& otherMinimum,
                       const Ogre::Vector3& otherMaximum)
{
    return otherMaximum.x >= minimum.x && otherMaximum.z >= minimum.z && maximum.x >= otherMinimum.x &&
           maximum.z >= otherMinimum.z;
}

bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                    float radius)
{
    return center.x >= minimum.x + radius && center.y >= minimum.y + radius && center.z >= minimum.z + radius &&
           maximum.x - radius >= center.x && maximum.y - radius >= center.y && maximum.z - radius >= center.z;
}

bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                     float radius)
{
    return center.x >= minimum.x - radius && center.y >= minimum.y - radius && center.z >= minimum.z - radius &&
           maximum.x + radius >= center.x && maximum.y + radius >= center.y && maximum.z + radius >= center.z;
}

void expandBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 point)
{
    if (point.x < minimum.x)
        minimum.x = point.x;
    if (point.x > maximum.x)
        maximum.x = point.x;
    if (point.y < minimum.y)
        minimum.y = point.y;
    if (point.y > maximum.y)
        maximum.y = point.y;
    if (point.z < minimum.z)
        minimum.z = point.z;
    if (point.z > maximum.z)
        maximum.z = point.z;
}

void expandCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent)
{
    float size = 0.0f;
    if (fabs(extent.x) > size)
        size = fabs(extent.x);
    if (fabs(extent.y) > size)
        size = fabs(extent.y);
    if (fabs(extent.z) > size)
        size = fabs(extent.z);
    expandBounds(minimum, maximum, Ogre::Vector3(size, size, size));
    expandBounds(minimum, maximum, Ogre::Vector3(-size, -size, -size));
}

void expandHorizontalCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent)
{
    float size = 0.0f;
    if (fabs(extent.x) > size)
        size = fabs(extent.x);
    if (fabs(extent.z) > size)
        size = fabs(extent.z);
    expandBounds(minimum, maximum, Ogre::Vector3(size, 0.0f, size));
    expandBounds(minimum, maximum, Ogre::Vector3(-size, 0.0f, -size));
}

void worldToLocalPerspective(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix)
{
    Ogre::Vector3 local = point;
    result.x = local.x * matrix[0][0] + local.y * matrix[1][0] + local.z * matrix[2][0];
    result.y = local.x * matrix[0][1] + local.y * matrix[1][1] + local.z * matrix[2][1];
    result.z = local.x * matrix[0][2] + local.y * matrix[1][2] + local.z * matrix[2][2];
    float depth = result.z;
    if (depth < 0.0f)
        depth = -depth;
    result.x /= depth;
    result.y /= depth;
}

void worldToLocal(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix)
{
    float x=point.x,y=point.y,z=point.z;
    result.x=x*matrix[0][0]+y*matrix[1][0]+z*matrix[2][0];
    result.y=x*matrix[0][1]+y*matrix[1][1]+z*matrix[2][1];
    result.z=x*matrix[0][2]+y*matrix[1][2]+z*matrix[2][2];
}


void closestPointOnLine(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& point,
                        Ogre::Vector3& result)
{
    Ogre::Vector3 direction = end - start;
    float t = (point - start).dotProduct(direction) / direction.squaredLength();
    if (t < 0.0f)
        result = start;
    else if (t > 1.0f)
        result = end;
    else
        result = start + direction * t;
}

void closestPointOnTriangle(const Ogre::Vector3& a, const Ogre::Vector3& b, const Ogre::Vector3& c,
                                            const Ogre::Vector3& point, Ogre::Vector3& result)
{
    Ogre::Vector3 closest;
    closestPointOnLine(a, b, point, closest);
    float best = (closest - point).squaredLength();
    result = closest;
    closestPointOnLine(b, c, point, closest);
    float distance = (closest - point).squaredLength();
    if (distance < best)
    {
        result = closest;
        best = distance;
    }
    closestPointOnLine(c, a, point, closest);
    distance = (closest - point).squaredLength();
    if (distance < best)
        result = closest;
}


EPLANE_SIDE classifyPoint(const Ogre::Vector3& point, const Ogre::Vector3& planePoint, const Ogre::Vector3& planeNormal)
{
    float distance = (planePoint - point).dotProduct(planeNormal);
    if (distance < -kPlaneEpsilon)
        return PLANE_SIDE_FRONT;
    if (distance > kPlaneEpsilon)
        return PLANE_SIDE_BACK;
    return PLANE_SIDE_ON;
}


EPLANE_SIDE classifyPointForSphere(const Ogre::Vector3& center, const Ogre::Vector3& planePoint,
                                                     const Ogre::Vector3& planeNormal, float radius)
{
    float distance = (planePoint.x - center.x) * planeNormal.x + (planePoint.y - center.y) * planeNormal.y + (planePoint.z - center.z) * planeNormal.z + radius;
    if (distance < -kPlaneEpsilon)
        return PLANE_SIDE_FRONT;
    if (distance > kPlaneEpsilon)
        return PLANE_SIDE_BACK;
    return PLANE_SIDE_ON;
}


bool getLinePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& planePoint,
                              const Ogre::Vector3& planeNormal, Ogre::Vector3& result)
{
    DeltaX = end.x - start.x;
    DeltaY = end.y - start.y;
    DeltaZ = end.z - start.z;
    LineLength = DeltaX * planeNormal.x + DeltaY * planeNormal.y + DeltaZ * planeNormal.z;
    if (fabs(LineLength) < kPlaneEpsilon)
        return false;

    ToPlaneX = planePoint.x - start.x;
    ToPlaneY = planePoint.y - start.y;
    ToPlaneZ = planePoint.z - start.z;
    DistanceFromPlane = ToPlaneX * planeNormal.x + ToPlaneY * planeNormal.y + ToPlaneZ * planeNormal.z;
    Percentage = DistanceFromPlane / LineLength;
    if (Percentage < 0.0f || Percentage > 1.0f)
        return false;

    result.x = start.x + DeltaX * Percentage;
    result.y = start.y + DeltaY * Percentage;
    result.z = start.z + DeltaZ * Percentage;
    return true;
}

bool getSpherePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& planePoint,
                                const Ogre::Vector3& planeNormal, Ogre::Vector3& result)
{
    DeltaX = end.x - start.x;
    DeltaY = end.y - start.y;
    DeltaZ = end.z - start.z;
    LineLength = DeltaX * planeNormal.x + DeltaY * planeNormal.y + DeltaZ * planeNormal.z;
    if (fabs(LineLength) < kPlaneEpsilon)
        return false;

    ToPlaneX = planePoint.x - start.x;
    ToPlaneY = planePoint.y - start.y;
    ToPlaneZ = planePoint.z - start.z;
    DistanceFromPlane = ToPlaneX * planeNormal.x + ToPlaneY * planeNormal.y + ToPlaneZ * planeNormal.z;
    Percentage = DistanceFromPlane / LineLength;

    result.x = start.x + DeltaX * Percentage;
    result.y = start.y + DeltaY * Percentage;
    result.z = start.z + DeltaZ * Percentage;
    return true;
}

float distanceToPlane(const Ogre::Vector3& origin, const Ogre::Vector3& direction, const Ogre::Vector3& planeNormal,
                      float planeDistance)
{
    float denominator = direction.dotProduct(planeNormal);
    if (denominator == 0.0f)
        return -1.0f;
    return (planeDistance - planeNormal.dotProduct(origin)) / denominator;
}

void matrixRotationZ(Ogre::Matrix4& matrix, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[1][0] = sine;
    matrix[0][0] = cosine;
    matrix[1][1] = cosine;
    matrix[0][1] = -sine;
}

void matrixRotationX(Ogre::Matrix4& matrix, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[1][1] = cosine;
    matrix[2][1] = sine;
    matrix[1][2] = -sine;
    matrix[2][2] = cosine;
}

void matrixRotationY(Ogre::Matrix4& matrix, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[2][0] = -sine;
    matrix[0][0] = cosine;
    matrix[0][2] = sine;
    matrix[2][2] = cosine;
}


void rotateZ(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float y = vector->y;
    float x = vector->x;
    vector->x = x * cosine + y * sine;
    vector->y = -x * sine + y * cosine;
}

void rotateX(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float z = vector->z;
    float y = vector->y;
    vector->y = y * cosine + z * sine;
    vector->z = -y * sine + z * cosine;
}

void rotateY(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float z = vector->z;
    float x = vector->x;
    vector->x = x * cosine + z * sine;
    vector->z = -x * sine + z * cosine;
}

float angleBetween(Ogre::Vector3 a, Ogre::Vector3 b)
{
    return acosf(a.dotProduct(b));
}

// Positions are scaled to a virtual 1024x768 screen first.
Ogre::Vector3 screenToWorldRay(Ogre::Camera* camera, float x, float y, float width, float height)
{
    float nearDistance = camera->getNearClipDistance();
    float farDistance = camera->getFarClipDistance();
    Ogre::Matrix4 projection = camera->getProjectionMatrix();

    float screenX = (2.0f * 1024.0f / width * x) / 1024.0f - 1.0f;
    float screenY = 1.0f - (2.0f * 768.0f / height * y) / 768.0f;
    screenX /= projection[0][0];
    screenY /= projection[1][1];

    Ogre::Vector3 nearPoint(screenX * nearDistance, screenY * nearDistance, -nearDistance);
    Ogre::Vector3 farPoint(screenX * farDistance, screenY * farDistance, -farDistance);

    Ogre::Matrix4 view = camera->getViewMatrix();
    view = view.inverse();
    view[0][3] = 0.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;

    Ogre::Quaternion orientation = camera->getOrientation();
    nearPoint = orientation * nearPoint;
    Ogre::Vector3 direction = orientation * farPoint - nearPoint;
    direction.normalise();
    return direction;
}

}

#include <cstdlib>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreHardwareBufferManager.h>

namespace MATH
{
void setMeshInformation(Ogre::Mesh* mesh, unsigned long vertexCount,
    Ogre::Vector3*& vertices, Ogre::Vector3*& normals, Ogre::Vector3*& texcoords,
    unsigned long, unsigned long*& indices, unsigned long triangleCount,
    unsigned long, unsigned int*& triangleMaterials, std::vector<std::string>& materials,
    unsigned long boneCount, Ogre::VertexBoneAssignment*& bones)
{
    for (unsigned short s=0;s<mesh->getNumSubMeshes();++s) {
        Ogre::SubMesh* sub=mesh->getSubMesh(s);
        unsigned long count=0;
        for (unsigned int t=0;t<triangleCount;++t)
            if (triangleMaterials[t]==s) ++count;
        sub->indexData->indexCount=count*3;
        mesh->sharedVertexData->vertexCount=vertexCount;
    }
    Ogre::VertexData* data=mesh->sharedVertexData;
    Ogre::HardwareVertexBufferSharedPtr buffer=Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        data->vertexDeclaration->getVertexSize(0),data->vertexCount,Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,false);
    data->vertexBufferBinding->setBinding(0,buffer);
    float* target=static_cast<float*>(buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
    for (unsigned short v=0;v<vertexCount;++v) {
        *target++=vertices[v].x;*target++=vertices[v].y;*target++=vertices[v].z;
        *target++=normals[v].x;*target++=normals[v].y;*target++=normals[v].z;
    }
    buffer->unlock();
    buffer=Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        data->vertexDeclaration->getVertexSize(1),data->vertexCount,Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,false);
    data->vertexBufferBinding->setBinding(1,buffer);
    target=static_cast<float*>(buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
    for (unsigned short v=0;v<vertexCount;++v) {
        *target++=texcoords[v].x;*target++=texcoords[v].y;
    }
    buffer->unlock();
    for (unsigned short s=0;s<mesh->getNumSubMeshes();++s) {
        Ogre::SubMesh* sub=mesh->getSubMesh(s);
        sub->setMaterialName(materials[s]);
        Ogre::HardwareIndexBufferSharedPtr indexBuffer=Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
            Ogre::HardwareIndexBuffer::IT_16BIT,sub->indexData->indexCount,Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,false);
        sub->indexData->indexBuffer=indexBuffer;
        unsigned short* dest=static_cast<unsigned short*>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        for (unsigned int t=0;t<triangleCount;++t) {
            if (triangleMaterials[t]==s) {
                *dest++=static_cast<unsigned short>(indices[t*3]);
                *dest++=static_cast<unsigned short>(indices[t*3+1]);
                *dest++=static_cast<unsigned short>(indices[t*3+2]);
            }
        }
        indexBuffer->unlock();
    }
    for (unsigned int b=0;b<boneCount;++b) mesh->addBoneAssignment(bones[b]);
    mesh->_compileBoneAssignments();
}

void getSubMeshInformation(const Ogre::SubMesh* sub, bool collectBones,
    unsigned long& vertexCount, Ogre::Vector3*& vertices, Ogre::Vector3*& normals, Ogre::Vector3*& texcoords,
    unsigned long& indexCount, unsigned long*& indices, unsigned long& triangleCount,
    unsigned long& boneCount, Ogre::VertexBoneAssignment*& bones, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, const Ogre::Vector3& scale)
{
    const unsigned long oldVertices=vertexCount, oldIndices=indexCount, oldBones=boneCount;
    Ogre::VertexData* data=sub->vertexData;
    vertexCount+=data->vertexCount;
    indexCount+=sub->indexData->indexCount;
    triangleCount+=sub->indexData->indexCount/3;
    if (vertices) {
        vertices=static_cast<Ogre::Vector3*>(std::realloc(vertices,vertexCount*sizeof(Ogre::Vector3)));
        normals=static_cast<Ogre::Vector3*>(std::realloc(normals,vertexCount*sizeof(Ogre::Vector3)));
        texcoords=static_cast<Ogre::Vector3*>(std::realloc(texcoords,vertexCount*sizeof(Ogre::Vector3)));
        indices=static_cast<unsigned long*>(std::realloc(indices,indexCount*sizeof(unsigned long)));
    } else {
        vertices=static_cast<Ogre::Vector3*>(std::malloc(vertexCount*sizeof(Ogre::Vector3)));
        normals=static_cast<Ogre::Vector3*>(std::malloc(vertexCount*sizeof(Ogre::Vector3)));
        texcoords=static_cast<Ogre::Vector3*>(std::malloc(vertexCount*sizeof(Ogre::Vector3)));
        indices=static_cast<unsigned long*>(std::malloc(indexCount*sizeof(unsigned long)));
    }
    const Ogre::VertexElement* element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
    Ogre::HardwareVertexBufferSharedPtr buffer=data->vertexBufferBinding->getBuffer(element->getSource());
    unsigned char* source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
    for (unsigned long v=0;v<data->vertexCount;++v) {
        float* value; element->baseVertexPointerToElement(source,&value);
        vertices[oldVertices+v]=orientation*(Ogre::Vector3(value[0],value[1],value[2])*scale)+position;
        source+=buffer->getVertexSize();
    }
    buffer->unlock();
    element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
    if (buffer!=data->vertexBufferBinding->getBuffer(element->getSource()))
        buffer=data->vertexBufferBinding->getBuffer(element->getSource());
    source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
    for (unsigned long v=0;v<data->vertexCount;++v) {
        float* value; element->baseVertexPointerToElement(source,&value);
        normals[oldVertices+v]=Ogre::Vector3(value[0],value[1],value[2]);source+=buffer->getVertexSize();
    }
    buffer->unlock();
    element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);
    if (element) {
        if (buffer!=data->vertexBufferBinding->getBuffer(element->getSource()))
            buffer=data->vertexBufferBinding->getBuffer(element->getSource());
        source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        for (unsigned long v=0;v<data->vertexCount;++v) {
            float* value;element->baseVertexPointerToElement(source,&value);
            texcoords[oldVertices+v]=Ogre::Vector3(value[0],value[1],0.0f);source+=buffer->getVertexSize();
        }
        buffer->unlock();
    }
    if (collectBones) {
        boneCount+=const_cast<Ogre::SubMesh*>(sub)->getBoneAssignments().size();
        if (bones) bones=static_cast<Ogre::VertexBoneAssignment*>(std::realloc(bones,boneCount*sizeof(Ogre::VertexBoneAssignment)));
        else bones=new Ogre::VertexBoneAssignment[const_cast<Ogre::SubMesh*>(sub)->getBoneAssignments().size()];
        Ogre::SubMesh::BoneAssignmentIterator i=const_cast<Ogre::SubMesh*>(sub)->getBoneAssignmentIterator();
        unsigned long n=oldBones;
        while (i.hasMoreElements()) {
            const Ogre::VertexBoneAssignment& bone=i.getNext();
            bones[n].vertexIndex=bone.vertexIndex+oldVertices;
            bones[n].boneIndex=bone.boneIndex;bones[n].weight=bone.weight;++n;
        }
    }
    Ogre::HardwareIndexBufferSharedPtr indexBuffer=sub->indexData->indexBuffer;
    void* indexSource=indexBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
    if (indexBuffer->getType()==Ogre::HardwareIndexBuffer::IT_32BIT) {
        // The original Linux build reads these entries at unsigned-long width.
        unsigned long* values=static_cast<unsigned long*>(indexSource);
        for (unsigned long i=0;i<sub->indexData->indexCount/3*3;++i) indices[oldIndices+i]=oldVertices+values[i];
    } else {
        unsigned short* values=static_cast<unsigned short*>(indexSource);
        for (unsigned long i=0;i<sub->indexData->indexCount/3*3;++i) indices[oldIndices+i]=oldVertices+values[i];
    }
    indexBuffer->unlock();
}

void getMeshInformation(const Ogre::Mesh* mesh, unsigned long& vertexCount,
    Ogre::Vector3*& vertices, Ogre::Vector3*& normals, Ogre::Vector3*& texcoords,
    unsigned long& indexCount, unsigned long*& indices, unsigned long& triangleCount,
    unsigned long& materialCount, unsigned int*& triangleMaterials, std::vector<std::string>& materials,
    unsigned long& boneCount, Ogre::VertexBoneAssignment*& bones, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, const Ogre::Vector3& scale)
{
    vertexCount=indexCount=triangleCount=materialCount=0;
    bool shared=false;
    for (unsigned short s=0;s<mesh->getNumSubMeshes();++s) {
        Ogre::SubMesh* sub=mesh->getSubMesh(s);
        if (sub->useSharedVertices) {
            if (!shared) {vertexCount+=mesh->sharedVertexData->vertexCount;shared=true;}
        } else vertexCount+=sub->vertexData->vertexCount;
        indexCount+=sub->indexData->indexCount;
    }
    triangleCount=indexCount/3;
    vertices=new Ogre::Vector3[vertexCount];normals=new Ogre::Vector3[vertexCount];texcoords=new Ogre::Vector3[vertexCount];
    indices=new unsigned long[indexCount];triangleMaterials=new unsigned int[triangleCount];
    unsigned long offset=0,nextOffset=0,sharedOffset=0,indexOffset=0;
    int triangleOffset=0;shared=false;
    for (unsigned short s=0;s<mesh->getNumSubMeshes();++s) {
        Ogre::SubMesh* sub=mesh->getSubMesh(s);
        std::string material=sub->getMaterialName();
        unsigned int materialID=material.find("nocollide")!=std::string::npos?100:s;
        materials.push_back(sub->getMaterialName());++materialCount;
        Ogre::VertexData* data=sub->useSharedVertices?mesh->sharedVertexData:sub->vertexData;
        if (!sub->useSharedVertices || !shared) {
            if (sub->useSharedVertices) {shared=true;sharedOffset=offset;}
            const Ogre::VertexElement* element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
            Ogre::HardwareVertexBufferSharedPtr buffer=data->vertexBufferBinding->getBuffer(element->getSource());
            unsigned char* source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            for (unsigned long v=0;v<data->vertexCount;++v) {
                float* value;element->baseVertexPointerToElement(source,&value);
                vertices[offset+v]=orientation*(Ogre::Vector3(value[0],value[1],value[2])*scale)+position;
                source+=buffer->getVertexSize();
            }
            buffer->unlock();nextOffset+=data->vertexCount;
            element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
            if (buffer!=data->vertexBufferBinding->getBuffer(element->getSource()))
                buffer=data->vertexBufferBinding->getBuffer(element->getSource());
            source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            for (unsigned long v=0;v<data->vertexCount;++v) {
                float* value;element->baseVertexPointerToElement(source,&value);
                normals[offset+v]=Ogre::Vector3(value[0],value[1],value[2]);source+=buffer->getVertexSize();
            }
            buffer->unlock();
            element=data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);
            if (element) {
                if (buffer!=data->vertexBufferBinding->getBuffer(element->getSource()))
                    buffer=data->vertexBufferBinding->getBuffer(element->getSource());
                source=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
                for (unsigned long v=0;v<data->vertexCount;++v) {
                    float* value;element->baseVertexPointerToElement(source,&value);
                    texcoords[offset+v]=Ogre::Vector3(value[0],value[1],0.0f);source+=buffer->getVertexSize();
                }
                buffer->unlock();
            }
        }
        if (mesh->hasSkeleton()) {
            boneCount=mesh->getBoneAssignments().size();bones=new Ogre::VertexBoneAssignment[boneCount];
            Ogre::Mesh::BoneAssignmentIterator i=const_cast<Ogre::Mesh*>(mesh)->getBoneAssignmentIterator();
            unsigned long n=0;
            while (i.hasMoreElements()) {
                const Ogre::VertexBoneAssignment& bone=i.getNext();
                bones[n].vertexIndex=bone.vertexIndex;bones[n].boneIndex=bone.boneIndex;bones[n].weight=bone.weight;++n;
            }
        }
        Ogre::HardwareIndexBufferSharedPtr buffer=sub->indexData->indexBuffer;
        void* source=buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
        unsigned long count=sub->indexData->indexCount/3;
        unsigned long start=sub->useSharedVertices?sharedOffset:offset;
        for (unsigned long t=0;t<count;++t) triangleMaterials[triangleOffset+t]=materialID;
        if (buffer->getType()==Ogre::HardwareIndexBuffer::IT_32BIT) {
            unsigned long* values=static_cast<unsigned long*>(source);
            for (unsigned long i=0;i<count*3;++i) indices[indexOffset+i]=start+values[i];
        } else {
            unsigned short* values=static_cast<unsigned short*>(source);
            for (unsigned long i=0;i<count*3;++i) indices[indexOffset+i]=start+values[i];
        }
        indexOffset+=count*3;buffer->unlock();triangleOffset+=count;offset=nextOffset;
    }
}
}
