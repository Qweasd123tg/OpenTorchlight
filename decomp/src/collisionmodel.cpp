#include "CollisionModel.h"
#include "CollisionList.h"
#include "EmptyStrings.h"

void CCollisionModel::unloadModel()
{
    m_sFilename = L"";
}

CCollisionModel::~CCollisionModel()
{
    unloadModel();
    if (m_pCollisionList) {
        delete m_pCollisionList;
        m_pCollisionList = 0;
    }
}

CCollisionModel::CCollisionModel(Ogre::SceneManager* sceneManager, std::wstring filename)
    : CRunicCore(), m_sFilename(L""), m_sMeshName(""),
      m_vUnknown20(0.0f,0.0f,0.0f), m_vUnknown2C(0.0f,0.0f,0.0f),
      m_pCollisionList(0), m_pSceneManager(sceneManager)
{
    if (filename != EMPTY_WSTRING)
        loadModel(filename);
}
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include "FileSystem.h"
#include "FileUtilities.h"
#include "UtilitiesMath.h"

void CCollisionModel::loadModel(std::wstring filename)
{
    CFileInfo file;
    CFileSystem::getSingleton()->getFileInfo(filename,file,false,true,false);
    if (!file.m_bExists || m_sFilename==file.m_sPath) return;

    m_pCollisionList=new CCollisionList;
    unloadModel();
    m_sFilename=file.m_sPath;
    std::wstring directory=FILESYSTEM::RemoveFileName(m_sFilename);
    Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().load(file.m_sResourceName,
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,true,true);
    unsigned long vertexCount=0,indexCount=0,triangleCount=0,materialCount=0,boneCount=0;
    Ogre::Vector3* vertices=NULL;
    Ogre::Vector3* normals=NULL;
    Ogre::Vector3* texcoords=NULL;
    unsigned long* indices=NULL;
    unsigned int* triangleMaterials=NULL;
    Ogre::VertexBoneAssignment* bones=NULL;
    std::vector<std::string> materials;
    MATH::getMeshInformation(mesh.getPointer(),vertexCount,vertices,normals,texcoords,
        indexCount,indices,triangleCount,materialCount,triangleMaterials,materials,boneCount,bones,
        Ogre::Vector3(0,0,0),Ogre::Quaternion(1,0,0,0),Ogre::Vector3(1,1,1));
    for (unsigned int v=0;v<vertexCount;++v) m_pCollisionList->addVertex(vertices[v],-1);
    for (unsigned int t=0;t<indexCount/3;++t)
        m_pCollisionList->addFace(indices[t*3+2],indices[t*3+1],indices[t*3],triangleMaterials[t],-1);
    m_pCollisionList->calculateFaceBounds();
    m_pCollisionList->calculateNormals();
    delete[] triangleMaterials;delete[] vertices;delete[] normals;delete[] texcoords;delete[] indices;delete[] bones;
    Ogre::ResourcePtr resource=mesh;
    Ogre::MeshManager::getSingleton().remove(resource);
}
