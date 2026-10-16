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
    struct CRoomPieceCoreData : public CRunicCore
    {
        virtual ~CRoomPieceCoreData();
        std::wstring m_name;                      // 0x10
        unsigned char m_unknown18[0x18];
        bool m_scalable;                         // 0x30
        unsigned char m_padding31[7];
        TArrayList<float> m_snapRotation;         // 0x38
        TArrayList<float> m_snapPosition;         // 0x50
        TArrayList<float> m_snapScale;            // 0x68
        TArrayList<std::wstring> m_visualMeshFiles; // 0x80
        TArrayList<std::wstring> m_collisionMeshFiles; // 0x98
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
