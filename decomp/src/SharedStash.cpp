#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SharedStash.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Player.h"
#include "RunicCore.h"

CSharedStash* CSharedStash::getSingleton()
{
    return (CSharedStash*)g_pSharedStash;
}

CSharedStash::CSharedStash(const wchar_t* stashFileName,
                           const wchar_t* alternateStashFileName)
    : CRunicCore(),
      m_pInventory(NULL),
      m_stashFileName(stashFileName),
      m_alternateStashFileName(alternateStashFileName),
      m_bUseAlternateStash(false)
{
    if (g_pSharedStash == NULL)
    {
        m_pInventory = new CInventory(NULL, 42);
        g_pSharedStash = this;
    }
}

CSharedStash::~CSharedStash()
{
    g_pSharedStash = NULL;

    if (m_pInventory != NULL)
    {
        delete m_pInventory;
        m_pInventory = NULL;
    }
}

void CSharedStash::setPlayer(CPlayer* player)
{
    if (m_pInventory == NULL)
        return;
    m_pInventory->m_pPositionableObject = player;
    if (player == NULL)
        return;

    if (m_bUseAlternateStash != player->m_saveOnDeath)
    {
        m_bUseAlternateStash = player->m_saveOnDeath;
        if (m_pInventory != NULL)
        {
            delete m_pInventory;
            m_pInventory = NULL;
        }
        m_pInventory = NULL;
        loadSharedStash(player->getResourceManager(), player);
    }
    else
    {
        TArrayList<CEquipmentRef*>* equipment = &m_pInventory->m_equipmentRefs;
        if (equipment != NULL)
        {
            for (unsigned int i = 0; i < equipment->size(); ++i)
            {
                if ((*equipment)[i]->m_pEquipment != NULL)
                {
                    (*equipment)[i]->m_pEquipment->setResourceManager(player->getResourceManager());
                    (*equipment)[i]->m_pEquipment->setParentGuid(player->getGuid());
                }
            }
        }
    }
}

#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "ResourceManager.h"
#include "ItemSaveState.h"

static unsigned int m_gFileVersion = 23;

void CSharedStash::loadSharedStash(CResourceManager* resourceManager, CCharacter* character)
{
    if (m_pInventory != NULL) {
        if (m_pInventory->m_equipmentRefs.size() != 0)
            return;
        character = m_pInventory->m_pPositionableObject;
        delete m_pInventory;
        m_pInventory = NULL;
    }
    m_pInventory = new CInventory(NULL, 42);
    m_pInventory->m_pPositionableObject = character;
    std::wstring directory = FILESYSTEM::GetSaveDataPath();
    if (!FILESYSTEM::FileExists(directory))
        FILESYSTEM::CreateAppDataDirectory(directory);
    std::wstring filename;
    if (m_bUseAlternateStash)
        filename = FILESYSTEM::AssembleAbsolutePath(directory, m_alternateStashFileName);
    else
        filename = FILESYSTEM::AssembleAbsolutePath(directory, m_stashFileName);
    FILE* file;
    _wfopen_s(&file, filename.c_str(), L"rb");
    if (!file)
        return;
    unsigned int version = 0;
    fread(&version, 4, 1, file);
    unsigned int count = 0;
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CItemSaveState* state = new CItemSaveState;
        state->load(file, version);
        if (state->m_iUnitValue60 != -1) {
            CBaseUnit* unit = resourceManager->createUnit(state->m_iUnitValue60, 1, true, false);
            if (unit) {
                CEquipment* equipment = dynamic_cast<CEquipment*>(unit);
                int slot = state->m_iIndex;
                equipment->applySaveState(*state);
                if (!m_pInventory->pickupEquipment(equipment, slot, true))
                    delete equipment;
            }
        }
        delete state;
    }
    fclose(file);
    setPlayer(dynamic_cast<CPlayer*>(character));
}

void CSharedStash::saveSharedStash()
{
    CInventory* inventory = m_pInventory;
    if (!inventory)
        return;
    std::wstring directory = FILESYSTEM::GetSaveDataPath();
    if (!FILESYSTEM::FileExists(directory))
        FILESYSTEM::CreateAppDataDirectory(directory);
    std::wstring filename;
    if (m_bUseAlternateStash)
        filename = FILESYSTEM::AssembleAbsolutePath(directory, m_alternateStashFileName);
    else
        filename = FILESYSTEM::AssembleAbsolutePath(directory, m_stashFileName);
    FILE* file;
    _wfopen_s(&file, filename.c_str(), L"wb");
    if (!file)
        return;
    fwrite(&m_gFileVersion, 4, 1, file);
    unsigned int count = inventory->m_equipmentRefs.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CItemSaveState* state = new CItemSaveState;
        CEquipmentRef* equipment = inventory->m_equipmentRefs[i];
        equipment->m_pEquipment->fillSaveState(*state, equipment->m_iSlot, equipment->m_flag20);
        state->save(file);
        delete state;
    }
    fclose(file);
}
