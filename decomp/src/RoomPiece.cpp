#include "RoomPiece.h"
#include "CameraControl.h"
#include <OgreAxisAlignedBox.h>

void CRoomPiece::setHighlighted(bool highlighted)
{
    if (m_pGenericModel)
        m_pGenericModel->setHighlighted(highlighted);
}

bool CRoomPiece::getRoomPieceIsAnimated()
{
    if (m_pGenericModel)
        return m_pGenericModel->getAnimationCount() != 0;
    return false;
}

void CRoomPiece::updateAnimation(float elapsed)
{
    if (getRoomPieceIsAnimated()) {
        Ogre::Vector3 position = getPosition(true);
        Ogre::AxisAlignedBox bounds(m_pGenericModel->m_boundsMinimum + position,
                                   m_pGenericModel->m_boundsMaximum + position);
        if (m_pResourceManager->getCameraControl()->m_cameras[0]->isVisible(bounds, NULL))
            m_pGenericModel->updateAnimation(elapsed, false);
    }
}

#include "EditorScene.h"
#include "RandomGroup.h"

void CRoomPiece::setParentGuid(long long guid)
{
    CEditorBaseObject::setParentGuid(guid);
    if (getSceneOwner() && guid != -1)
    {
        while (CEditorBaseObject* parent = getSceneOwner()->GetObjectInScene(guid))
        {
            CRandomGroup* group = dynamic_cast<CRandomGroup*>(parent);
            if (group && group->m_iRandomType != 0)
            {
                m_bUnknown15D = true;
                break;
            }
            guid = parent->getParentGuid();
        }
    }
}

char CRoomPiece::getRoomPieceIsScalable()
{
    if (m_pRoomPieceData && m_pRoomPieceData->m_coreData)
        return m_pRoomPieceData->m_coreData->m_scalable;
    return 0;
}
TArrayList<float>* CRoomPiece::getSnapValues(ESNAP_TYPES type)
{
    if (m_pRoomPieceData && m_pRoomPieceData->m_coreData) {
        CRoomPieceDataInformation::CRoomPieceCoreData* data = m_pRoomPieceData->m_coreData;
        switch (type) {
        case 0: return &data->m_snapPosition;
        case 1: return &data->m_snapRotation;
        case 2: return &data->m_snapScale;
        default: break;
        }
    }
    return NULL;
}
int CRoomPiece::getVisualMeshCountInRoomPiece()
{
    if (m_iVisualIndex_140 != -1 && m_pRoomPieceData && m_pRoomPieceData->m_coreData)
        return m_pRoomPieceData->m_coreData->m_visualMeshFiles.size();
    return 1;
}

#include "Level.h"
#include "Utilities.h"
void CRoomPiece::clearCollisionData()
{
    m_pEntity=NULL;
    if (m_bUnknown154) {
        CMasterResourceManager::getSingleton()->removeBatchModel(m_pGenericModel);
        m_pGenericModel=NULL;
    } else if (m_pGenericModel) {delete m_pGenericModel;m_pGenericModel=NULL;}
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_collisionModel);
    m_collisionModel=NULL;
    if (m_pRoomPieceData) {delete m_pRoomPieceData;m_pRoomPieceData=NULL;}
}
void CRoomPiece::setVisible(bool visible)
{
    CSceneNodeObject::setVisible(visible);
    if (!m_bUnknown15C && m_iUnknown158>0 && visible && m_bVisibleOnMap && m_pResourceManager->getLevel()->m_automapRoomPieces) {
        m_bUnknown15C=true;
        m_pResourceManager->getLevel()->addRoomPieceToAutomap(this);
    }
}
void CRoomPiece::resetRoomPiece()
{
    clearCollisionData();
    m_bCollisionEnabled=false;m_bUnknown151=false;m_bUnknown152=false;m_bUnknown154=false;
    m_iUnknown158=0;m_bIsBakeable=true;m_bVisibleOnMap=true;m_bUnknown15C=false;
    m_iVisualIndex=-1;m_bUnknown15D=false;
    m_pRoomPieceData=new CRoomPieceData;
    m_pRoomPieceData->m_guid=-1;m_pRoomPieceData->m_coreData=NULL;
    m_pRoomPieceData->m_guid=m_iVisualIndex_140;
    if(m_iVisualIndex_140!=-1) m_pRoomPieceData->m_coreData=CRoomPieceDataInformation::getSingleton()->_GetRoomPieceCoreDataByGuid(m_iVisualIndex_140);
}
void CRoomPiece::setRoomPieceGuid(long long guid)
{
    m_iVisualIndex_140=guid;
    m_pRoomPieceData->m_guid=guid;
    if(guid!=-1) m_pRoomPieceData->m_coreData=CRoomPieceDataInformation::getSingleton()->_GetRoomPieceCoreDataByGuid(guid);
    if(m_iVisualIndex_140!=-1 && m_pRoomPieceData && m_pRoomPieceData->m_coreData && m_pResourceManager->getEditorIsRunning()) initRoomPiece();
}
void CRoomPiece::selectNewVisualIndex()
{
    if (m_iVisualIndex_140==-1 || !m_pRoomPieceData || !m_pRoomPieceData->m_coreData || m_pRoomPieceData->m_coreData->m_visualMeshFiles.size()==1) {
        m_iVisualIndex=0;setRoomPieceGuid(m_iVisualIndex_140);
    }
    int maximum=0;
    if(m_iVisualIndex_140!=-1 && m_pRoomPieceData && m_pRoomPieceData->m_coreData)
        maximum=m_pRoomPieceData->m_coreData->m_visualMeshFiles.size()-1;
    m_iVisualIndex=UTILITIES::randomIntegerBetween(0,maximum);
    setRoomPieceGuid(m_iVisualIndex_140);
}

#include "EmptyStrings.h"
CRoomPiece::CRoomPiece(CResourceManager* resources)
    : CPositionableObject(resources,NULL),m_collisionModel(NULL),m_pGenericModel(NULL),
      m_collisionMeshFile(EMPTY_WSTRING),m_meshFile(EMPTY_WSTRING),m_iVisualIndex(-1),m_iVisualIndex_140(-1),
      m_pRoomPieceData(NULL),m_bCollisionEnabled(true),m_bUnknown151(false),m_bUnknown152(false),m_bIsBakeable(true),
      m_bUnknown154(false),m_bVisibleOnMap(true),m_iUnknown158(0),m_bUnknown15C(false),m_bUnknown15D(false)
{
    m_pRoomPieceData=new CRoomPieceData;
    m_pRoomPieceData->m_coreData=NULL;m_pRoomPieceData->m_guid=-1;
    setVisible(true);
}
CRoomPiece::~CRoomPiece() { clearCollisionData(); }

void CRoomPiece::setCollisionMeshFilePath(const std::wstring& path)
{
    if(m_meshFile==path) return;
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_collisionModel);
    m_collisionModel=NULL;
    if(path.empty()) return;
    if(m_pResourceManager->getEditorIsRunning() && m_collisionMeshFile!=EMPTY_WSTRING) {
        m_meshFile=m_collisionMeshFile;
        m_collisionModel=CMasterResourceManager::getSingleton()->addCollisionModel(m_meshFile);
    } else {
        m_meshFile=path;
        if(!m_pResourceManager->getEditorIsRunning() && !m_bCollisionEnabled) m_meshFile=EMPTY_WSTRING;
        if(m_meshFile!=EMPTY_WSTRING) m_collisionModel=CMasterResourceManager::getSingleton()->addCollisionModel(path);
    }
}

#include <OgreEntity.h>
// m_collisionMeshFile (+0x128) holds the visual mesh path here; m_meshFile is the collision path.
void CRoomPiece::setMeshFilePath(const std::wstring& path)
{
    if (m_collisionMeshFile == path)
        return;
    sceneNodeDetachEntity();
    if (m_pGenericModel) {
        if (m_bUnknown154) {
            CMasterResourceManager::getSingleton()->removeBatchModel(m_pGenericModel);
            m_pGenericModel = NULL;
        } else {
            delete m_pGenericModel;
            m_pGenericModel = NULL;
        }
    }
    m_collisionMeshFile = path;
    m_pEntity = NULL;
    if (path.empty())
        return;
    bool batch = m_bIsBakeable && m_bVisible;
    if (batch) {
        m_bUnknown154 = true;
        bool shared;
        m_pGenericModel = CMasterResourceManager::getSingleton()->addBatchModel(m_pResourceManager, NULL, path, shared);
        if (!shared)
            m_bUnknown154 = false;
    } else {
        m_bUnknown154 = false;
        m_pGenericModel = new CGenericModel(m_pResourceManager, NULL, path, EMPTY_WSTRING, false);
    }
    if (m_pGenericModel) {
        m_pGenericModel->setVisible(false);
        if (!m_bUnknown154)
            m_pGenericModel->sceneNodeDetachEntity();
        if (m_bUnknown151)
            m_pGenericModel->getEntity()->setRenderQueueGroup(60);
        if (getRoomPieceIsAnimated())
            m_pGenericModel->playAnimation("IDLE", true, 1.0f, -1.0f);
        if (!m_bUnknown154)
            sceneNodeAttachEntity(m_pGenericModel->getEntity());
    }
}

#include "Settings.h"
void CRoomPiece::initRoomPiece()
{
    if (m_iVisualIndex_140 == -1)
        return;
    unsigned int index = m_iVisualIndex;
    unsigned int count = getVisualMeshCountInRoomPiece();
    if (index >= count) {
        index = 0;
        if (count != 1)
            index = UTILITIES::randomIntegerBetween(0, getVisualMeshCountInRoomPiece() - 1);
    }
    m_bUnknown151 = m_pRoomPieceData->m_coreData->m_postRender;
    m_bUnknown152 = m_pRoomPieceData->m_coreData->m_preRender;
    m_iUnknown158 = m_pRoomPieceData->m_coreData->m_automapLayer;
    if (m_pRoomPieceData->m_coreData->m_fixedVariation)
        m_iVisualIndex = index;
    if (m_bCollisionEnabled && CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DISPLAY_COLLISION)) {
        if (m_pRoomPieceData->m_coreData->m_collisionMeshFiles.size() != 0) {
            if (m_pRoomPieceData->m_coreData->m_collisionMeshFiles.size() == m_pRoomPieceData->m_coreData->m_visualMeshFiles.size()) {
                setMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[index]);
                setCollisionMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[index]);
            } else {
                setMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[0]);
                setCollisionMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[0]);
            }
        } else {
            setMeshFilePath(m_pRoomPieceData->m_coreData->m_visualMeshFiles[index]);
            setCollisionMeshFilePath(EMPTY_WSTRING);
        }
    } else {
        if (index < m_pRoomPieceData->m_coreData->m_visualMeshFiles.size())
            setMeshFilePath(m_pRoomPieceData->m_coreData->m_visualMeshFiles[index]);
        else
            setMeshFilePath(EMPTY_WSTRING);
        if (m_pRoomPieceData->m_coreData->m_collisionMeshFiles.size() != 0) {
            if (m_pRoomPieceData->m_coreData->m_collisionMeshFiles.size() == m_pRoomPieceData->m_coreData->m_visualMeshFiles.size())
                setCollisionMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[index]);
            else
                setCollisionMeshFilePath(m_pRoomPieceData->m_coreData->m_collisionMeshFiles[0]);
        } else
            setCollisionMeshFilePath(EMPTY_WSTRING);
    }
    if (m_pGenericModel)
        m_pGenericModel->setQueryMask((OGRE_UTILITIES::EQUERYMASK)m_pRoomPieceData->m_coreData->m_queryMask);
}
