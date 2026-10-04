#ifndef ROOMPIECEDATAINFORMATION_H
#define ROOMPIECEDATAINFORMATION_H

#include <map>
#include <string>

#include "DataGroup.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CRoomPieceDataInformation : public CRunicCore
{
public:
    struct CRoomPieceCoreData
    {
    };

    virtual ~CRoomPieceDataInformation();

    static CRoomPieceDataInformation* getSingleton();

    CRoomPieceCoreData* _GetRoomPieceCoreDataByGuid(long long guid);
    long long getDefaultGuid();
    void getRoomPieceCoreDataByTileset(
        const std::wstring& tilesetName,
        TArrayList<CRoomPieceCoreData*>& roomPieceCoreDataList);
    CRoomPieceCoreData* _GetRoomPieceCoreDataByGuidByClosestGuid(long long guid);

    void DestroyRoomData();
    bool ParseRoomPieceData(
        const std::wstring& fileName,
        CDataGroup* dataGroup,
        int flags);
    void LoadSpecificLevelTileSet(std::wstring& fileName);
    void LoadRoomData();

    CRoomPieceDataInformation(CResourceSettings* resourceSettings);

    CRoomPieceCoreData* m_pDefaultRoomPieceCoreData;
    CResourceSettings* m_pResourceSettings;
    std::map<long long, CRoomPieceCoreData*> m_RoomPieceCoreDataByGuid;
};

#endif
