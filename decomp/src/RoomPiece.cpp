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
