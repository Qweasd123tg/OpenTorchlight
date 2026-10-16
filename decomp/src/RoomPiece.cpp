#include "RoomPiece.h"

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
