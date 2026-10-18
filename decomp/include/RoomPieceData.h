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
    long long m_guid; // +0x18
};

#endif
