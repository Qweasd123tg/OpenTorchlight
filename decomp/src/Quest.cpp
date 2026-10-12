#include "Dungeon.h"
#include "DungeonManager.h"
#include "GameClient.h"
#include "LevelTemplateData.h"
#include "Utilities.h"
#include <new>
#include "EmptyStrings.h"
#include "Quest.h"
#include "QuestDialog.h"
#include "QuestManager.h"
#include "QuestRequirements.h"
#include "QuestRewards.h"


// Imported source candidates; historical status is not fresh acceptance.
CPlayer* CQuest::getPlayer()
{
    if (m_pQuestManager) return m_pQuestManager->m_pPlayer;
    return NULL;
}

void CQuest::caculateRewards(CDataGroup* group)
{
}

void CQuest::setQuestAcceptDialogInteracted(bool value)
{
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i) m_acceptDialogs[i]->m_bDialogInitialized = value;
}

int CQuest::getQuestRewardFame()
{
    CQuestRewards* rewards = m_pQuestRewards;
    if (rewards) { rewards->calculateRewards(); return static_cast<int>(rewards->m_fFame); }
    return 0;
}

void CQuest::setIsComplete(bool value)
{
    if (m_complete != value) {
        m_complete = value;
        if (value) m_pQuestManager->questEventUpdate(static_cast<EQUEST_EVENTS>(4), NULL, NULL);
    }
}

void CQuest::destroyIcons()
{
    if (m_pQuestRewards) m_pQuestRewards->destroyIcons();
}

std::wstring CQuest::getQuestRewardString()
{
    if (m_pQuestRewards) return m_pQuestRewards->getRewardString();
    return EMPTY_WSTRING;
}

std::wstring CQuest::getQuestDetails()
{
    if (m_pQuestDialog) return replaceStringTags(m_pQuestDialog->getDialog(false));
    return EMPTY_WSTRING;
}


void CQuest::addQuestControllerListerner(CQuestController* controller)
{
    typedef TSafePointer<CQuestController> Pointer;
    TArrayList<Pointer*>& listeners =
        *reinterpret_cast<TArrayList<Pointer*>*>(&m_Unknown1B0);
    for (unsigned int i = 0; i < listeners.size(); ++i)
    {
        if (listeners[i]->getObject() == controller)
            return;
        if (listeners[i]->getObject() == NULL)
        {
            if (listeners[i])
            {
                Pointer* pointer = listeners[i];
                pointer->~Pointer();
                Ogre::NedAllocImpl::deallocBytes(pointer);
            }
            listeners[i] = NULL;
            listeners.removeAt(i);
        }
    }
    void* storage = Ogre::NedAllocImpl::allocBytes(sizeof(Pointer), NULL, 0, NULL);
    // Construction failure frees only the raw wrapper, not a registered object.
    struct RawAllocation
    {
        void* memory;
        explicit RawAllocation(void* value) : memory(value) {}
        ~RawAllocation()
        {
            if (memory) Ogre::NedAllocImpl::deallocBytes(memory);
        }
    };
    Pointer* pointer;
    {
        RawAllocation allocation(storage);
        pointer = new (storage) Pointer;
        pointer->setObject(controller);
        allocation.memory = NULL;
    }
    listeners.add(pointer);
}

void CQuest::removeQuestControllerListerner(CQuestController* controller)
{
    typedef TSafePointer<CQuestController> Pointer;
    TArrayList<Pointer*>& listeners =
        *reinterpret_cast<TArrayList<Pointer*>*>(&m_Unknown1B0);
    for (unsigned int i = 0; i < listeners.size(); ++i)
    {
        if (listeners[i]->getObject() == controller ||
            listeners[i]->getObject() == NULL)
        {
            if (listeners[i])
            {
                Pointer* pointer = listeners[i];
                pointer->~Pointer();
                Ogre::NedAllocImpl::deallocBytes(pointer);
            }
            listeners[i] = NULL;
            listeners.removeAt(i);
        }
    }
}


namespace {
typedef char QuestObjectSize[sizeof(CQuest)==0x218?1:-1];
typedef char QuestStringSize[sizeof(std::wstring)==8?1:-1];
typedef char QuestListSize[sizeof(TArrayList<CQuestDialog*>)==0x18?1:-1];
typedef char QuestPointerSize[sizeof(TSafePointer<CQuestController>)==0x10?1:-1];
typedef char QuestOffset_10[__builtin_offsetof(CQuest,m_Unknown10)==0x10?1:-1];
typedef char QuestOffset_18[__builtin_offsetof(CQuest,m_iUnknown18)==0x18?1:-1];
typedef char QuestOffset_1c[__builtin_offsetof(CQuest,m_iUnknown1C)==0x1c?1:-1];
typedef char QuestOffset_20[__builtin_offsetof(CQuest,m_iUnknown20)==0x20?1:-1];
typedef char QuestOffset_24[__builtin_offsetof(CQuest,m_complete)==0x24?1:-1];
typedef char QuestOffset_25[__builtin_offsetof(CQuest,m_gap25)==0x25?1:-1];
typedef char QuestOffset_26[__builtin_offsetof(CQuest,m_questAccepted)==0x26?1:-1];
typedef char QuestOffset_30[__builtin_offsetof(CQuest,m_pUnknown30)==0x30?1:-1];
typedef char QuestOffset_38[__builtin_offsetof(CQuest,m_pUnknown38)==0x38?1:-1];
typedef char QuestOffset_40[__builtin_offsetof(CQuest,m_pUnknown40)==0x40?1:-1];
typedef char QuestOffset_48[__builtin_offsetof(CQuest,m_pUnknown48)==0x48?1:-1];
typedef char QuestOffset_50[__builtin_offsetof(CQuest,m_sUnknown50)==0x50?1:-1];
typedef char QuestOffset_58[__builtin_offsetof(CQuest,m_sUnknown58)==0x58?1:-1];
typedef char QuestOffset_60[__builtin_offsetof(CQuest,m_acceptDialogs)==0x60?1:-1];
typedef char QuestOffset_78[__builtin_offsetof(CQuest,m_Unknown78)==0x78?1:-1];
typedef char QuestOffset_90[__builtin_offsetof(CQuest,m_Unknown90)==0x90?1:-1];
typedef char QuestOffset_a8[__builtin_offsetof(CQuest,m_UnknownA8)==0xa8?1:-1];
typedef char QuestOffset_c0[__builtin_offsetof(CQuest,m_pQuestDialog)==0xc0?1:-1];
typedef char QuestOffset_c8[__builtin_offsetof(CQuest,m_UnknownC8)==0xc8?1:-1];
typedef char QuestOffset_e0[__builtin_offsetof(CQuest,m_UnknownE0)==0xe0?1:-1];
typedef char QuestOffset_f8[__builtin_offsetof(CQuest,m_UnknownF8)==0xf8?1:-1];
typedef char QuestOffset_110[__builtin_offsetof(CQuest,m_UnknownF8)+sizeof(TArrayList<bool>)==0x110?1:-1];
typedef char QuestOffset_128[__builtin_offsetof(CQuest,m_pQuestRewards)==0x128?1:-1];
typedef char QuestOffset_130[__builtin_offsetof(CQuest,m_Unknown130)==0x130?1:-1];
typedef char QuestOffset_148[__builtin_offsetof(CQuest,m_Unknown148)==0x148?1:-1];
typedef char QuestOffset_160[__builtin_offsetof(CQuest,m_Unknown160)==0x160?1:-1];
typedef char QuestOffset_178[__builtin_offsetof(CQuest,m_Unknown178)==0x178?1:-1];
typedef char QuestOffset_190[__builtin_offsetof(CQuest,m_Unknown190)==0x190?1:-1];
typedef char QuestOffset_1a8[__builtin_offsetof(CQuest,m_iUnknown1A8)==0x1a8?1:-1];
typedef char QuestOffset_1ac[__builtin_offsetof(CQuest,m_iUnknown1AC)==0x1ac?1:-1];
typedef char QuestOffset_1b0[__builtin_offsetof(CQuest,m_Unknown1B0)==0x1b0?1:-1];
typedef char QuestOffset_1c8[__builtin_offsetof(CQuest,m_iUnknown1C8)==0x1c8?1:-1];
typedef char QuestOffset_1d0[__builtin_offsetof(CQuest,m_pQuestManager)==0x1d0?1:-1];
typedef char QuestOffset_1d8[__builtin_offsetof(CQuest,m_pResourceManager)==0x1d8?1:-1];
typedef char QuestOffset_1e0[__builtin_offsetof(CQuest,m_pQuestRequirements)==0x1e0?1:-1];
typedef char QuestOffset_1e8[__builtin_offsetof(CQuest,m_iUnknown1E8)==0x1e8?1:-1];
typedef char QuestOffset_1f0[__builtin_offsetof(CQuest,m_Unknown1F0)==0x1f0?1:-1];
typedef char QuestOffset_208[__builtin_offsetof(CQuest,m_bUnknown208)==0x208?1:-1];
typedef char QuestOffset_209[__builtin_offsetof(CQuest,m_bUnknown209)==0x209?1:-1];
typedef char QuestOffset_20c[__builtin_offsetof(CQuest,m_iUnknown20C)==0x20c?1:-1];
typedef char QuestOffset_210[__builtin_offsetof(CQuest,m_bUnknown210)==0x210?1:-1];
}

CQuest::CQuest(CResourceManager* resources, CQuestManager* manager)
    : m_Unknown10(0), m_iUnknown18(0), m_iUnknown1C(-1), m_iUnknown20(0),
      m_complete(false), m_gap25(0), m_questAccepted(false), m_gap27(0),
      m_bUnknown28(false), m_bUnknown29(true), m_bUnknown2A(false), m_bUnknown2B(false),
      m_pUnknown30(EMPTY_WSTRING), m_pUnknown38(EMPTY_WSTRING),
      m_pUnknown40(EMPTY_WSTRING), m_pUnknown48(EMPTY_WSTRING),
      m_acceptDialogs(10), m_Unknown78(10), m_Unknown90(10), m_UnknownA8(10),
      m_pQuestDialog(NULL), m_UnknownC8(10), m_UnknownE0(10),
      m_pQuestRewards(NULL),
      m_Unknown130(1), m_Unknown148(1), m_Unknown160(1), m_Unknown178(1), m_Unknown190(1),
      m_iUnknown1A8(1), m_iUnknown1AC(1), m_Unknown1B0(1), m_iUnknown1C8(-1),
      m_pQuestManager(manager), m_pResourceManager(resources),
      m_pQuestRequirements(NULL), m_iUnknown1E8(0), m_Unknown1F0(10),
      m_bUnknown209(false), m_bUnknown20A(false), m_bUnknown20B(false),
      m_iUnknown20C(1), m_bUnknown210(false)
{
    m_UnknownF8[0].setGrowBy(10);
    m_UnknownF8[1].setGrowBy(10);
    m_pQuestRequirements = new CQuestRequirements(this);
}

CQuest::~CQuest()
{
    m_Unknown10 = 0;
    typedef TSafePointer<CQuestController> Pointer;
    Pointer**& data = *reinterpret_cast<Pointer***>(&m_Unknown1B0);
    for (unsigned int i = 0; i < m_Unknown1B0.size(); ++i)
    {
        if (data[i])
        {
            Pointer* pointer = data[i];
            pointer->~Pointer();
            Ogre::NedAllocImpl::deallocBytes(pointer);
            data[i] = NULL;
        }
        data[i] = NULL;
    }
    m_Unknown1B0.clear();
    if (m_pQuestRewards)
    {
        delete m_pQuestRewards;
        m_pQuestRewards = NULL;
    }
    if (m_pQuestDialog)
    {
        delete m_pQuestDialog;
        m_pQuestDialog = NULL;
    }
    if (m_pQuestRequirements)
    {
        delete m_pQuestRequirements;
        m_pQuestRequirements = NULL;
    }
    m_UnknownA8.deleteAll();
    m_acceptDialogs.deleteAll();
    m_Unknown78.deleteAll();
    m_Unknown90.deleteAll();
    for (unsigned int i = 0; i < m_Unknown178.size(); ++i)
        m_Unknown178[i]->deleteAll();
    for (unsigned int i = 0; i < m_Unknown160.size(); ++i)
        m_Unknown160[i]->deleteAll();
    for (unsigned int i = 0; i < m_Unknown190.size(); ++i)
        m_Unknown190[i]->deleteAll();
    m_Unknown160.deleteAll();
    m_Unknown190.deleteAll();
    m_Unknown178.deleteAll();
    m_Unknown130.clear();
    m_Unknown148.clear();
    m_pQuestManager = NULL;
}

void CQuest::reinitializeQuest(bool resolveUnitData, bool preserveDungeon)
{
    m_complete = false;
    m_questAccepted = false;
    m_bUnknown209 = false;
    m_iUnknown1E8 = 0;
    m_bUnknown210 = false;
    if (!preserveDungeon)
    {
        if (m_iUnknown1C != -1)
            UTILITIES::setSeed(m_iUnknown1C);
        m_Unknown10 = 0;
        CGameClient* client = m_pResourceManager->getGameClient();
        CDungeon* dungeon = CDungeonManager::getSingleton()->getDungeonByName(m_pUnknown30);
        if (dungeon)
        {
            for (unsigned int attempt = 0; attempt < 10 && m_Unknown10 == 0; ++attempt)
            {
                if (m_pQuestManager->m_pPlayer)
                    m_iUnknown20 = m_pQuestManager->m_pPlayer->getMaxDepth(m_pUnknown30) + attempt + 1;
                else
                    m_iUnknown20 = attempt + 1;
                if (!dungeon->m_bBottomless && m_bUnknown20B &&
                    static_cast<int>(dungeon->m_levelTemplateData.size()) <= m_iUnknown20)
                {
                    m_bUnknown210 = true;
                    break;
                }
                if (m_iUnknown20 < 0)
                    m_iUnknown20 = 0;
                client->resetGameSeed(m_iUnknown20);
                CLevelTemplateData* data = dungeon->getLevelTemplateDataForDepth(
                    m_pResourceManager->getGameClient(), m_iUnknown20);
                m_Unknown10 = reinterpret_cast<long long>(data);
                if (data->getQuestSelectionExcluded())
                    m_Unknown10 = 0;
            }
        }
    }

    unsigned int firstCount = m_Unknown178.size();
    unsigned int secondCount = UTILITIES::randomIntegerBetween(m_iUnknown1A8, m_Unknown190.size());
    if (m_gap27)
        firstCount = m_Unknown178.size();
    m_Unknown130.clear();
    m_Unknown148.clear();
    for (unsigned int i = 0; i < m_Unknown160.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown160[i]->size(); ++j)
            (*m_Unknown160[i])[j]->reinitialize(resolveUnitData);
    for (unsigned int i = 0; i < firstCount; ++i)
    {
        m_Unknown130.add(m_Unknown178[i]);
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            (*m_Unknown130[i])[j]->reinitialize(resolveUnitData);
    }
    for (unsigned int i = 0; i < secondCount; ++i)
    {
        m_Unknown148.add(m_Unknown190[i]);
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
            (*m_Unknown148[i])[j]->reinitialize(resolveUnitData);
    }
    for (unsigned int i = 0; i < 2; ++i)
        for (unsigned int j = 0; j < m_UnknownF8[i].size(); ++j)
            m_UnknownF8[i][j] = false;
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i)
        m_acceptDialogs[i]->reinitialize();
    for (unsigned int i = 0; i < m_Unknown78.size(); ++i)
        m_Unknown78[i]->reinitialize();
    for (unsigned int i = 0; i < m_Unknown90.size(); ++i)
        m_Unknown90[i]->reinitialize();
    for (unsigned int i = 0; i < m_UnknownA8.size(); ++i)
        m_UnknownA8[i]->reinitialize();
}

void CQuest::load(_IO_FILE* file, CResourceManager*, unsigned int version)
{
    long long guid = -1;
    fread(&guid, 8, 1, file);
    if (guid != -1)
        m_iUnknown1E8 = reinterpret_cast<long long>(m_pResourceManager->getUnitDataByGuid(guid));
    fread(&m_iUnknown1C, 4, 1, file);
    fread(&m_iUnknown20, 4, 1, file);
    if (version > 19)
        fread(&m_iUnknown20C, 4, 1, file);
    m_pResourceManager->getGameClient()->resetGameSeed(m_iUnknown20);
    CDungeon* dungeon = CDungeonManager::getSingleton()->getDungeonByName(m_pUnknown30);
    if (dungeon)
        m_Unknown10 = reinterpret_cast<long long>(dungeon->getLevelTemplateDataForDepth(
            m_pResourceManager->getGameClient(), m_iUnknown20));
    long long unitData = m_iUnknown1E8;
    reinitializeQuest(true, true);
    m_iUnknown1E8 = unitData;

    unsigned int count;
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
        if (i < m_acceptDialogs.size())
            m_acceptDialogs[i]->load(file);
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
        if (i < m_Unknown78.size())
            m_Unknown78[i]->load(file);
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
        if (i < m_Unknown90.size())
            m_Unknown90[i]->load(file);
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
        if (i < m_UnknownA8.size())
            m_UnknownA8[i]->load(file);
    unsigned int innerCount;
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
    {
        fread(&innerCount, 4, 1, file);
        for (unsigned int j = 0; j < innerCount; ++j)
            if (m_Unknown130.size() >= count && m_Unknown130[i]->size() >= innerCount)
                (*m_Unknown130[i])[j]->load(file, version);
    }
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
    {
        fread(&innerCount, 4, 1, file);
        for (unsigned int j = 0; j < innerCount; ++j)
            if (m_Unknown148.size() >= count && m_Unknown148[i]->size() >= innerCount)
                (*m_Unknown148[i])[j]->load(file, version);
    }
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
    {
        fread(&innerCount, 4, 1, file);
        for (unsigned int j = 0; j < innerCount; ++j)
            if (m_Unknown160.size() >= count && m_Unknown160[i]->size() >= innerCount)
                (*m_Unknown160[i])[j]->load(file, version);
    }
    m_questAccepted = true;
}
