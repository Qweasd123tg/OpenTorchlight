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
