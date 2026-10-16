#ifndef ROOMPIECEDATA_H
#define ROOMPIECEDATA_H

#include "RunicCore.h"
#include "RoomPieceDataInformation.h"

// Original RTTI/base/size and CRoomPiece's typed reads.
class CRoomPieceData : public CRunicCore
{
public:
    virtual ~CRoomPieceData();
    CRoomPieceDataInformation::CRoomPieceCoreData* m_coreData; // 0x10
    unsigned char m_unknown18[8];
};

#endif
