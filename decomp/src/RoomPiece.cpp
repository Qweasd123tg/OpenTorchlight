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
