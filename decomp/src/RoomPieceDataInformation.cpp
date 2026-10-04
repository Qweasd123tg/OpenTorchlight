#include "EmptyStrings.h"
#include "RoomPieceDataInformation.h"
#include "DataGroup.h"
#include "MasterResourceManager.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "StringUtilities.h"
#include "TArrayList.h"
#include "Utilities.h"

CRoomPieceDataInformation* CRoomPieceDataInformation::getSingleton()
{
    extern CRoomPieceDataInformation* m_gRoomPieceInformation;
    return m_gRoomPieceInformation;
}

CRoomPieceDataInformation::CRoomPieceCoreData* CRoomPieceDataInformation::_GetRoomPieceCoreDataByGuid(long long guid)
{
    std::map<long long, CRoomPieceDataInformation::CRoomPieceCoreData*>::iterator it =
        m_RoomPieceCoreDataByGuid.lower_bound(guid);

    if (it != m_RoomPieceCoreDataByGuid.end() && it->first <= guid)
        return it->second;

    return m_pDefaultRoomPieceCoreData;
}

long long CRoomPieceDataInformation::getDefaultGuid()
{
    if (m_pDefaultRoomPieceCoreData != 0)
        return *reinterpret_cast<long long *>(
            reinterpret_cast<char *>(m_pDefaultRoomPieceCoreData) + 0x18);

    if (m_RoomPieceCoreDataByGuid.begin() != m_RoomPieceCoreDataByGuid.end())
        return m_RoomPieceCoreDataByGuid.begin()->first;

    return -1LL;
}

void CRoomPieceDataInformation::getRoomPieceCoreDataByTileset(
    const std::wstring& tilesetName,
    TArrayList<CRoomPieceCoreData*>& roomPieceCoreDataList)
{
}

void CRoomPieceDataInformation::DestroyRoomData()
{
    for (std::map<long long, CRoomPieceCoreData*>::iterator it = m_RoomPieceCoreDataByGuid.begin(); it != m_RoomPieceCoreDataByGuid.end(); ++it)
    {
        if (it->second != NULL)
        {
            delete reinterpret_cast<CRunicCore*>(it->second);
            it->second = NULL;
        }
    }
    m_RoomPieceCoreDataByGuid.clear();
}

CRoomPieceDataInformation::~CRoomPieceDataInformation()
{
    extern CRoomPieceDataInformation *m_gRoomPieceInformation;

    DestroyRoomData();
    m_gRoomPieceInformation = NULL;
    m_pResourceSettings = NULL;
}

bool CRoomPieceDataInformation::ParseRoomPieceData(
    const std::wstring& fileName,
    CDataGroup* dataGroup,
    int flags)
{
    if (dataGroup == NULL || dataGroup->GetGroupName() != L"PIECE")
        return false;

    if (CMasterResourceManager::getSingleton() == NULL)
        return false;

    std::wstring name = STRINGS::StringUpper(
        dataGroup->GetDataValue(std::wstring(L"NAME"), EMPTY_WSTRING));

    if (name.empty())
        return false;

    long long guid = dataGroup->GetDataValue(
        std::wstring(L"GUID"), static_cast<long long>(-1));
    bool generatedGuid = guid == -1;

    if (generatedGuid)
        guid = UTILITIES::createUniqueGuid();

    std::map<long long, CRoomPieceCoreData*>::iterator found =
        m_RoomPieceCoreDataByGuid.find(guid);

    if (found != m_RoomPieceCoreDataByGuid.end())
        return false;

    int type = dataGroup->GetDataValue(
        std::wstring(L"TYPE"), static_cast<int>(-1));

    if (type == -1)
        return false;

    CRoomPieceCoreData* roomPieceCoreData = new CRoomPieceCoreData;
    m_RoomPieceCoreDataByGuid[guid] = roomPieceCoreData;

    return generatedGuid;
}

CRoomPieceDataInformation::CRoomPieceDataInformation(CResourceSettings* resourceSettings)
    : CRunicCore(),
      m_pDefaultRoomPieceCoreData(NULL),
      m_pResourceSettings(resourceSettings),
      m_RoomPieceCoreDataByGuid()
{
    LoadRoomData();
}
