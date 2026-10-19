#include "StringUtilities.h"
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

long long CQuest::isComplete(bool requireObjectives)
{
    if (!requireObjectives && m_complete)
        return true;
    if (m_bUnknown2A)
        return false;

    bool hasObjectives = false;
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
    {
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
        {
            if (!(*m_Unknown130[i])[j]->isComplete(false))
                return false;
            hasObjectives = true;
        }
    }
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
    {
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
        {
            if (!(*m_Unknown148[i])[j]->isComplete(false))
                return false;
            hasObjectives = true;
        }
    }
    for (unsigned int i = 0; i < 2; ++i)
    {
        for (unsigned int j = 0; j < m_UnknownF8[i].size(); ++j)
        {
            if (!m_UnknownF8[i][j])
                return false;
            hasObjectives = true;
        }
    }
    if (!hasObjectives)
    {
        if (requireObjectives)
            return false;
        bool interacted = m_acceptDialogs.size() == 0;
        for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i)
        {
            if (m_acceptDialogs[i]->m_bDialogInitialized)
            {
                interacted = true;
                break;
            }
        }
        if (!interacted)
            return false;
    }
    setIsComplete(true);
    return true;
}

void CQuest::questEventUpdate(EQUEST_EVENTS event, CBaseUnit* actor,
                              CBaseUnit* target)
{
    switch (static_cast<unsigned int>(event))
    {
    case 0:
        for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
                if (static_cast<unsigned char>((*m_Unknown130[i])[j]->unitPickedUp(target)))
                {
                    isComplete(false);
                    break;
                }
        for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
                if (static_cast<unsigned char>((*m_Unknown148[i])[j]->unitPickedUp(target)))
                {
                    isComplete(false);
                    break;
                }
        break;
    case 1:
        for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
                if ((*m_Unknown130[i])[j]->unitDefeated(target))
                {
                    isComplete(false);
                    break;
                }
        for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
                if ((*m_Unknown148[i])[j]->unitDefeated(target))
                {
                    isComplete(false);
                    break;
                }
        break;
    case 2:
        if (actor != m_pQuestManager->m_pPlayer)
            break;
        for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
                if ((*m_Unknown130[i])[j]->unitInteracted(target))
                {
                    isComplete(false);
                    break;
                }
        for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
                if ((*m_Unknown148[i])[j]->unitInteracted(target))
                {
                    isComplete(false);
                    break;
                }
        break;
    case 3:
        for (unsigned int i = 0; i < m_UnknownC8.size(); ++i)
            if (!m_UnknownF8[0][i] && m_pQuestManager->getQuestIsActive(m_UnknownC8[i]))
                m_UnknownF8[0][i] = true;
        isComplete(false);
        break;
    case 4:
        for (unsigned int i = 0; i < m_UnknownE0.size(); ++i)
            if (!m_UnknownF8[1][i] && m_pQuestManager->getQuestComplete(m_UnknownE0[i]))
                m_UnknownF8[1][i] = true;
        isComplete(false);
        break;
    case 5:
        for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
                if ((*m_Unknown130[i])[j]->unitDropped(target))
                {
                    m_complete = false;
                    break;
                }
        for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
            for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
                if ((*m_Unknown148[i])[j]->unitDropped(target))
                {
                    m_complete = false;
                    break;
                }
        break;
    }
}

inline std::wstring getAcquireTags(CQuestUnitData* unit, std::wstring prefix,
                                  unsigned int index, std::wstring& text)
{
    if (!unit)
        return text;
    std::wstring tag = prefix + STRINGS::GetValueAsWString(index + 1);
    text = STRINGS::replaceWString(text, tag + L"COUNT]",
                                  STRINGS::GetValueAsWString(static_cast<unsigned int>(unit->m_requiredUnitCount)));
    text = STRINGS::replaceWString(text, tag + L"DEPTH]",
                                  STRINGS::GetValueAsWString(unit->getDungeonFloorActiveOn() + 1));
    text = STRINGS::replaceWString(text, tag + L"COMPLETE]",
                                  unit->isComplete(false) ? L"Complete" : L"Incomplete");
    text = STRINGS::replaceWString(text, tag + L"]", unit->getUnitName());
    return text;
}

std::wstring CQuest::replaceStringTags(const std::wstring& input)
{
    std::wstring text = input;
    unsigned int acquireCompleteCount = 0;
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            acquireCompleteCount += (*m_Unknown130[i])[j]->m_currentUnitCount;
    unsigned int defeatCompleteCount = 0;
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
            defeatCompleteCount += (*m_Unknown148[i])[j]->m_currentUnitCount;

    text = STRINGS::replaceWString(text, L"[DEPTH]", STRINGS::GetValueAsWString(m_iUnknown20 + 1));
    text = STRINGS::replaceWString(text, L"[DEFEATCOMPLETECOUNT]", STRINGS::GetValueAsWString(defeatCompleteCount));
    text = STRINGS::replaceWString(text, L"[ACQUIRECOMPLETECOUNT]", STRINGS::GetValueAsWString(acquireCompleteCount));

    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        text = getAcquireTags((*m_Unknown130[i])[0], L"[ACQUIRE", i, text);

    CDungeon* dungeon = m_pResourceManager->getDungeonByName(m_pUnknown30);
    if (dungeon)
        text = STRINGS::replaceWString(text, L"[DUNEGONNAME]", dungeon->m_sDisplayName);

    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
    {
        CQuestUnitData* unit = (*m_Unknown148[i])[0];
        if (!unit)
            continue;
        std::wstring tag = L"[DEFEAT" + STRINGS::GetValueAsWString(i + 1);
        text = STRINGS::replaceWString(text, tag + L"COUNT]",
                                      STRINGS::GetValueAsWString(static_cast<unsigned int>(unit->m_requiredUnitCount)));
        text = STRINGS::replaceWString(text, tag + L"DEPTH]",
                                      STRINGS::GetValueAsWString(unit->getDungeonFloorActiveOn() + 1));
        text = STRINGS::replaceWString(text, tag + L"COMPLETE]",
                                      unit->isComplete(true) ? L"Complete" : L"Incomplete");
        text = STRINGS::replaceWString(text, tag + L"]", unit->getUnitName());
        for (unsigned int j = 0; j < unit->m_children.size(); ++j)
            text = getAcquireTags(unit->m_children[j], tag + L"ACQUIRE", j, text);
    }
    return text;
}

void CQuest::getAllNPCUnitDataInvolvedInQuest(TArrayList<CDataGroup*>& groups)
{
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i)
    {
        if (m_acceptDialogs[i]->m_pNPCDataGroup &&
            groups.find(m_acceptDialogs[i]->m_pNPCDataGroup) == -1)
            groups.add(m_acceptDialogs[i]->m_pNPCDataGroup);
    }
    for (unsigned int i = 0; i < m_Unknown78.size(); ++i)
    {
        if (m_Unknown78[i]->m_pNPCDataGroup &&
            groups.find(m_Unknown78[i]->m_pNPCDataGroup) == -1)
            groups.add(m_Unknown78[i]->m_pNPCDataGroup);
    }
    for (unsigned int i = 0; i < m_Unknown90.size(); ++i)
    {
        if (m_Unknown90[i]->m_pNPCDataGroup &&
            groups.find(m_Unknown90[i]->m_pNPCDataGroup) == -1)
            groups.add(m_Unknown90[i]->m_pNPCDataGroup);
    }
    for (unsigned int i = 0; i < m_UnknownA8.size(); ++i)
    {
        if (m_UnknownA8[i]->m_pNPCDataGroup &&
            groups.find(m_UnknownA8[i]->m_pNPCDataGroup) == -1)
            groups.add(m_UnknownA8[i]->m_pNPCDataGroup);
    }
}

void CQuest::save(_IO_FILE* file)
{
    long long unitGuid = -1;
    if (m_iUnknown1E8)
        unitGuid = m_pResourceManager->getUnitGuidByDataGroup(
            reinterpret_cast<CDataGroup*>(m_iUnknown1E8), L"UNIT_GUID");
    fwrite(&unitGuid, 8, 1, file);
    fwrite(&m_iUnknown1C, 4, 1, file);
    fwrite(&m_iUnknown20, 4, 1, file);
    fwrite(&m_iUnknown20C, 4, 1, file);

    unsigned int count = m_acceptDialogs.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i)
        m_acceptDialogs[i]->save(file);

    count = m_Unknown78.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_Unknown78.size(); ++i)
        m_Unknown78[i]->save(file);

    count = m_Unknown90.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_Unknown90.size(); ++i)
        m_Unknown90[i]->save(file);

    count = m_UnknownA8.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_UnknownA8.size(); ++i)
        m_UnknownA8[i]->save(file);

    count = m_Unknown130.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
    {
        count = m_Unknown130[i]->size();
        fwrite(&count, 4, 1, file);
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            (*m_Unknown130[i])[j]->save(file);
    }

    count = m_Unknown148.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
    {
        unsigned int innerCount = 0;
        if (m_Unknown148[i])
            innerCount = m_Unknown148[i]->size();
        fwrite(&innerCount, 4, 1, file);
        for (unsigned int j = 0; j < innerCount; ++j)
            (*m_Unknown148[i])[j]->save(file);
    }

    count = m_Unknown160.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_Unknown160.size(); ++i)
    {
        count = m_Unknown160[i]->size();
        fwrite(&count, 4, 1, file);
        for (unsigned int j = 0; j < m_Unknown160[i]->size(); ++j)
            (*m_Unknown160[i])[j]->save(file);
    }
}

int CQuest::getDungeonMaxFloor()
{
    int floor = m_iUnknown20;
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
        {
            int depth = (*m_Unknown130[i])[j]->getDeepestFloor();
            if (depth > floor) floor = depth;
        }
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
        {
            int depth = (*m_Unknown148[i])[j]->getDeepestFloor();
            if (depth > floor) floor = depth;
        }
    return floor;
}

long long CQuest::getQuestHasRandomPieces()
{
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            if ((*m_Unknown130[i])[j]->getIsRandom()) return true;
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
            if ((*m_Unknown148[i])[j]->getIsRandom()) return true;
    return false;
}

int CQuest::getQuestRewardXP()
{
    CQuestRewards* rewards = m_pQuestRewards;
    if (rewards) { rewards->calculateRewards(); return static_cast<int>(rewards->m_fExperience); }
    return 0;
}

int CQuest::getQuestRewardGold()
{
    CQuestRewards* rewards = m_pQuestRewards;
    if (rewards) { rewards->calculateRewards(); return static_cast<int>(rewards->m_fGold); }
    return 0;
}

void CQuest::setQuestAccepted(bool accepted)
{
    if (m_questAccepted != accepted)
    {
        m_questAccepted = accepted;
        if (accepted)
            m_pQuestManager->questEventUpdate(static_cast<EQUEST_EVENTS>(3), NULL, NULL);
        else
            setQuestAcceptDialogInteracted(false);
    }
}

void CQuest::cleanUpDialog(TArrayList<CQuestDialog*>& dialogs)
{
    for (unsigned int i = 0; i < dialogs.size(); ++i)
        dialogs[i]->cleanUp();
}

void CQuest::populate(CLevel* level)
{
    if (level == NULL) return;
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            (*m_Unknown130[i])[j]->populate(level);
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
            (*m_Unknown148[i])[j]->populate(level);
    for (unsigned int i = 0; i < m_Unknown160.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown160[i]->size(); ++j)
            (*m_Unknown160[i])[j]->populate(level);
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i) m_acceptDialogs[i]->populate();
    for (unsigned int i = 0; i < m_Unknown78.size(); ++i) m_Unknown78[i]->populate();
    for (unsigned int i = 0; i < m_Unknown90.size(); ++i) m_Unknown90[i]->populate();
    for (unsigned int i = 0; i < m_UnknownA8.size(); ++i) m_UnknownA8[i]->populate();
    m_bUnknown2D = true;
}

long long CQuest::getQuestDialog(CBaseUnit* npc)
{
    if (npc == NULL) return 0;
    TArrayList<CQuestDialog*>* dialogs = NULL;
    for (unsigned int i = 0; i < m_Unknown78.size(); ++i)
        if (m_Unknown78[i]->dialogIsForNPC(npc)) { dialogs = &m_Unknown78; break; }
    TArrayList<CQuestDialog*>* preferred = &m_Unknown90;
    if (!isComplete(false))
    {
        bool useAcceptance = !m_questAccepted;
        if (!useAcceptance)
        {
            if (dialogIsForNPC(npc, m_acceptDialogs))
            {
                useAcceptance = true;
                for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i)
                    if (m_acceptDialogs[i]->dialogIsForNPC(npc) && m_acceptDialogs[i]->m_bDialogInitialized)
                    { useAcceptance = false; break; }
            }
            if (!useAcceptance && !m_questAccepted) useAcceptance = true;
        }
        preferred = useAcceptance ? &m_acceptDialogs : NULL;
    }
    if (preferred != NULL && dialogIsForNPC(npc, *preferred)) dialogs = preferred;
    if (dialogs == NULL && m_questAccepted && dialogIsForNPC(npc, m_UnknownA8)) dialogs = &m_UnknownA8;
    if (dialogs != NULL)
        for (unsigned int i = 0; i < dialogs->size(); ++i)
            if ((*dialogs)[i]->dialogIsForNPC(npc)) return reinterpret_cast<long long>((*dialogs)[i]);
    return 0;
}

int CQuest::getQuestIsValidForNPC(CBaseUnit* npc)
{
    if (npc == NULL || m_bUnknown210) return false;
    int valid = m_pQuestRequirements ? m_pQuestRequirements->questRequirmentsHaveBeenMet() : true;
    if (valid && getQuestDialog(npc) == 0 && !m_bUnknown20B) return false;
    return valid;
}

void CQuest::getQuestStrings(CDataGroup* data, const std::wstring& name, TArrayList<CQuestDialog*>& dialogs)
{
    if (data == NULL) return;
    std::vector<CDataGroup*> groups;
    data->GetDataGroupsMatchingName(name, &groups);
    for (unsigned int i = 0; i < groups.size(); ++i)
    {
        CQuestDialog* dialog = new CQuestDialog(this);
        if (dialog->parseDialogTag(data->GetDataValue(L"UNITNAME", EMPTY_WSTRING), groups[i]))
            dialogs.add(dialog);
        else
            delete dialog;
    }
}

void CQuest::initializeQuestWithNPC(CBaseUnit* npc)
{
    if (npc != NULL && m_iUnknown1E8 == reinterpret_cast<long long>(npc->getDataGroup())) return;
    if (m_pQuestManager->getPlayerHasQuest(this) && npc != NULL) return;
    CDungeon* dungeon = m_pResourceManager->getDungeonByName(m_pUnknown30);
    if (dungeon != NULL && m_pResourceManager != NULL && m_pResourceManager->getGameClient() != NULL)
    {
        if (m_bUnknown20A && getPlayer() != NULL)
        {
            getPlayer()->clearDungeonHistory(m_pUnknown30);
            CResourceManager* resources = getPlayer()->getResourceManager();
            getPlayer()->updateStoredLevels(*(resources ? resources->getLevel() : NULL));
        }
        int floor = getDungeonMaxFloor();
        m_iUnknown20C = m_pResourceManager->getGameClient()->getRankOfMonstersOnFloor(floor > 0 ? floor : 1, dungeon, true);
    }
    if (npc != NULL)
    {
        m_iUnknown1C = UTILITIES::randomIntegerBetweenVolatile(0, 2147483647);
        reinitializeQuest(true, false);
        m_iUnknown1E8 = reinterpret_cast<long long>(npc->getDataGroup());
        if (m_pQuestRewards != NULL && m_bUnknown2D)
        {
            m_bUnknown2D = false;
            m_pQuestRewards->reInitializeRewards();
        }
    }
    else
        reinitializeQuest(false, false);
}

unsigned int CQuest::calculateUnitsFromTag(CDataGroup* data,
    TArrayList<TArrayList<CQuestUnitData*>*>* alternatives,
    TArrayList<CQuestUnitData*>* units, unsigned int searchMode)
{
    if (data == NULL || (alternatives == NULL && units == NULL)) return 0;
    unsigned int minimum = data->GetDataValue(L"MINCREATE", 0);
    unsigned int maximum = data->GetDataValue(L"MAXCREATE", 0);
    if (static_cast<int>(minimum) <= 0) minimum = 1;
    if (maximum < minimum) maximum = minimum;
    m_gap27 = minimum == 0 && maximum == 0;
    std::vector<CDataGroup*> groups;
    data->GetDataGroupsMatchingName(L"UNIT", &groups);
    if (groups.empty()) return 0;
    if (m_gap27) minimum = groups.size();
    for (unsigned int i = 0; i < groups.size(); ++i)
    {
        CQuestUnitData* unit = new CQuestUnitData(this);
        if (!unit->parseDataGroup(groups[i], NULL)) { delete unit; continue; }
        unit->m_unitSearchMode = searchMode;
        unit->m_pBaseUnitDataGroup = unit->getBaseUnitDataGroup();
        if (alternatives != NULL)
        {
            unsigned int index = alternatives->size();
            alternatives->add(new TArrayList<CQuestUnitData*>(1));
            (*alternatives)[index]->add(unit);
            calculateUnitsFromTag(groups[i]->GetDataGroupByName(L"ACQUIRE", false), NULL, &unit->m_children, 1);
            for (unsigned int j = 1; j < static_cast<unsigned int>(unit->m_requiredUnitCount); ++j)
            {
                CQuestUnitData* extra = new CQuestUnitData(this);
                extra->parseDataGroup(groups[i], unit->m_pBaseUnitDataGroup);
                extra->m_unitSearchMode = 1;
                extra->m_pBaseUnitDataGroup = extra->getBaseUnitDataGroup();
                extra->m_requiredUnitCount = unit->m_requiredUnitCount;
                (*alternatives)[index]->add(extra);
                calculateUnitsFromTag(groups[i]->GetDataGroupByName(L"ACQUIRE", false), NULL, &extra->m_children, 1);
            }
        }
        else if (units != NULL)
        {
            units->add(unit);
            calculateUnitsFromTag(groups[i]->GetDataGroupByName(L"ACQUIRE", false), NULL, &unit->m_children, 1);
        }
    }
    return minimum;
}

void CQuest::cleanUp(bool removeAll)
{
    if (getPlayer() == NULL) return;
    if (m_bUnknown20A)
    {
        getPlayer()->clearDungeonHistory(m_pUnknown30);
        CResourceManager* resources = getPlayer()->getResourceManager();
        getPlayer()->updateStoredLevels(*(resources ? resources->getLevel() : NULL));
    }
    for (unsigned int i = 0; i < m_Unknown130.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown130[i]->size(); ++j)
            (*m_Unknown130[i])[j]->cleanUpForQuestRemoveall(removeAll);
    for (unsigned int i = 0; i < m_Unknown148.size(); ++i)
        for (unsigned int j = 0; j < m_Unknown148[i]->size(); ++j)
            (*m_Unknown148[i])[j]->cleanUpForQuestRemoveall(removeAll);
    cleanUpDialog(m_acceptDialogs);
    cleanUpDialog(m_Unknown78);
    cleanUpDialog(m_Unknown90);
    cleanUpDialog(m_UnknownA8);
    getPlayer()->removeQuestItemFromInventoryOrPetsInventoryByGuid(m_iUnknown1C8, -1, false, true, static_cast<UNITTYPES::EUNITTYPES>(103));
    CResourceManager* resources = getPlayer()->getResourceManager();
    if (resources != NULL && resources->getLevel() != NULL)
        resources->getLevel()->makeQuestUnitsUncool(m_iUnknown1C8, true);
    reinitializeQuest(false, false);
}

void CQuest::giveRewardForQuest()
{
    if (getPlayer() == NULL) return;
    getPlayer()->incrementJournalStatistic(static_cast<EJournalStatistic>(4), 1);
    if (m_pQuestRewards != NULL)
    {
        m_pQuestRewards->rewardPlayer();
        m_bUnknown2D = true;
    }
    for (unsigned int i = 0; i < m_Unknown1F0.size(); ++i)
    {
        CQuest* next = reinterpret_cast<CQuest*>(m_pQuestManager->getQuestByName(STRINGS::StringUpper(m_Unknown1F0[i])));
        if (next != NULL)
        {
            m_pQuestManager->giveQuest(next, NULL, false);
            next->setQuestAccepted(true);
        }
    }
    cleanUp(true);
}

long long CQuest::loadQuestData(const std::wstring& filename)
{
    m_complete = false;
    if (m_pQuestManager == NULL || !m_pUnknown48.empty()) return false;
    m_pUnknown48 = filename;
    CDataGroup data(L"ERROR", NULL, 20, 10, NULL);
    data.LoadFile(m_pUnknown48, NULL);
    if (data.GetGroupName() == L"ERROR") return false;
    m_bUnknown2B = data.GetDataValue(L"COMPLETESONACCEPT", false);
    m_bUnknown28 = data.GetDataValue(L"FORCEACCEPT", false);
    m_bUnknown29 = data.GetDataValue(L"SHOWQUESTCOMPLETE", true);
    m_bUnknown2A = data.GetDataValue(L"QUESTCONTROLLERCOMPLETES", false);
    m_gap25 = data.GetDataValue(L"NO_NOTIFICATION", false);
    m_bUnknown20A = data.GetDataValue(L"CLEAR_DUNGEON_HISTORY", false);
    m_bUnknown20B = data.GetDataValue(L"REPEATABLE", false);
    m_iUnknown1C8 = data.GetDataValue(L"QUEST_GUID", -1LL);
    if (m_iUnknown1C8 == -1)
    {
        do { m_iUnknown1C8 = UTILITIES::createUniqueGuid(); } while (m_iUnknown1C8 == -1);
        data.SetDataValue(L"QUEST_GUID", m_iUnknown1C8);
        data.SaveToFile(filename);
    }
    m_bUnknown208 = data.GetDataValue(L"CANABANDON", false);
    m_bUnknown2C = data.GetDataValue(L"SHOWTIPS", m_bUnknown208);
    m_pUnknown30 = STRINGS::StringUpper(data.GetDataValue(L"DUNGEON", m_pUnknown30));
    m_iUnknown18 = STRINGS::getStringIndex(STRINGS::StringUpper(data.GetDataValue(L"QUESTTYPE", EMPTY_WSTRING)), gQUEST_TYPE_NAMES, 4, 0, false);
    CDataGroup* giveQuests = data.GetDataGroupByName(L"GIVE_QUESTS_ON_COMPLETE", false);
    if (giveQuests != NULL)
        for (unsigned int i = 0; i < giveQuests->GetNumberOfDataValues(); ++i)
        {
            CDataValue::EDATAVALUETYPES type = giveQuests->GetDataValue(i)->GetValueType();
            if (type == CDataValue::DATAVALUE_STRING || type == CDataValue::DATAVALUE_TRANSLATE)
                m_Unknown1F0.add(giveQuests->GetDataValue(i)->GetValueString(true));
        }
    m_sUnknown50 = STRINGS::StringUpper(data.GetDataValue(L"NAME", EMPTY_WSTRING));
    m_sUnknown58 = data.GetDataValue(L"DISPLAYNAME", EMPTY_WSTRING);
    m_pUnknown38 = data.GetDataValue(L"ALTERNATIVECOMPLETETEXT", EMPTY_WSTRING);
    m_pUnknown40 = data.GetDataValue(L"ALTERNATIVECOMPLETETEXTSMALL", EMPTY_WSTRING);
    m_iUnknown1C = -1;
    m_iUnknown1A8 = calculateUnitsFromTag(data.GetDataGroupByName(L"DEFEAT", false), &m_Unknown190, NULL, 0);
    m_iUnknown1AC = calculateUnitsFromTag(data.GetDataGroupByName(L"ACQUIRE", false), &m_Unknown178, NULL, 1);
    calculateUnitsFromTag(data.GetDataGroupByName(L"POPULATE", false), &m_Unknown160, NULL, 0);
    TArrayList<std::wstring>* names[2] = {&m_UnknownC8, &m_UnknownE0};
    for (unsigned int i = 0; i < 2; ++i)
    {
        CDataGroup* group = data.GetDataGroupByName(g_QUEST_COMPLETE_TYPE_NAMES[i], false);
        if (group != NULL)
        {
            names[i]->setGrowBy(2);
            m_UnknownF8[i].setGrowBy(2);
            for (unsigned int j = 0; j < group->GetNumberOfDataValues(); ++j)
            {
                CDataValue::EDATAVALUETYPES type = group->GetDataValue(j)->GetValueType();
                if (type == CDataValue::DATAVALUE_STRING || type == CDataValue::DATAVALUE_TRANSLATE)
                {
                    names[i]->add(STRINGS::StringUpper(group->GetDataValue(j)->GetValueString(true)));
                    m_UnknownF8[i].add(false);
                }
            }
        }
    }
    m_pQuestRequirements->parseRequirementTag(data.GetDataGroupByName(L"REQUIREMENTS", false));
    if (m_pQuestRewards == NULL) m_pQuestRewards = new CQuestRewards(this);
    CDataGroup* reward = data.GetDataGroupByName(L"REWARD", false);
    if (reward != NULL) m_pQuestRewards->parseRewardTag(reward);
    CDataGroup* dialog = data.GetDataGroupByName(L"DIALOG", false);
    if (dialog != NULL)
    {
        getQuestStrings(dialog, gQUEST_DIALOG_TYPE_NAMES[1], m_acceptDialogs);
        getQuestStrings(dialog, gQUEST_DIALOG_TYPE_NAMES[2], m_Unknown78);
        getQuestStrings(dialog, gQUEST_DIALOG_TYPE_NAMES[3], m_Unknown90);
        getQuestStrings(dialog, gQUEST_DIALOG_TYPE_NAMES[4], m_UnknownA8);
        CDataGroup* details = dialog->GetDataGroupByName(gQUEST_DIALOG_TYPE_NAMES[5], false);
        if (details != NULL)
        {
            m_pQuestDialog = new CQuestDialog(this);
            if (!m_pQuestDialog->parseDialogTag(dialog->GetDataValue(L"UNITNAME", EMPTY_WSTRING), details))
            {
                delete m_pQuestDialog;
                m_pQuestDialog = NULL;
            }
        }
    }
    return true;
}
