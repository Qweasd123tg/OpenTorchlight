#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestManager.h"
#include "Character.h"
#include "GameUI.h"
#include "Level.h"
#include "Player.h"
#include "Quest.h"
#include "QuestController.h"
#include "QuestDialog.h"
#include "TArrayList.h"
#include "UnitTypes.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "StringUtilities.h"
#include "Utilities.h"

namespace {
typedef char QuestManagerNPCMapOffset[__builtin_offsetof(CQuestManager,m_UnknownA0)==0xa0?1:-1];
typedef char QuestManagerActiveOffset[__builtin_offsetof(CQuestManager,m_Unknown18)==0x18?1:-1];
typedef char QuestThresholdOffset[__builtin_offsetof(CQuest,m_Unknown10)+0x10==0x20?1:-1];
typedef char QuestDungeonOffset[__builtin_offsetof(CQuest,m_pUnknown30)==0x30?1:-1];
typedef char QuestAcceptedOffset[__builtin_offsetof(CQuest,m_questAccepted)==0x26?1:-1];
typedef char QuestDataOffset[__builtin_offsetof(CQuest,m_iUnknown1E8)==0x1e8?1:-1];
typedef char DataGroupValuesOffset[__builtin_offsetof(CDataGroup,m_DataValues)==0x20?1:-1];
typedef char NPCQuestMapSize[sizeof(std::map<CDataGroup*,TArrayList<CQuest*>*>)==48?1:-1];
}


CQuestManager* CQuestManager::getSingleton()
{
    return (CQuestManager*)g_pQuestManager;
}

void CQuestManager::setPlayer(CPlayer* player)
{
    m_pPlayer = player;
}

void CQuestManager::update(float)
{
}

bool CQuestManager::getPlayerHasQuest(CQuest* pQuest)
{
    return reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).find(pQuest) != -1;
}

void CQuestManager::destroyIcons()
{
    typedef std::map<std::wstring, CQuest*> TQuestMap;
    TQuestMap& quests = *reinterpret_cast<TQuestMap*>(&m_Unknown40);

    for (TQuestMap::iterator it = quests.begin(); it != quests.end(); ++it)
        it->second->destroyIcons();
}

void CQuestManager::giveRewardForQuest(CQuest* quest)
{
    if (quest != 0) {
        quest->giveRewardForQuest();
    }
}

void CQuestManager::populate(CLevel* pLevel)
{
    std::map<std::wstring, CQuest*>& quests =
        *reinterpret_cast<std::map<std::wstring, CQuest*>*>(
            reinterpret_cast<char*>(&m_iUnknown48) - 8);

    for (std::map<std::wstring, CQuest*>::iterator it = quests.begin();
         it != quests.end(); ++it)
        it->second->populate(pLevel);
}

char CQuestManager::getQuestComplete(const std::wstring& name)
{
    typedef std::map<std::wstring, bool> QuestCompleteMap;
    QuestCompleteMap& quests =
        *reinterpret_cast<QuestCompleteMap*>(&m_Unknown70);
    QuestCompleteMap::iterator i = quests.find(name);
    return i != quests.end() ? i->second : 0;
}

long long CQuestManager::getQuestByName(const std::wstring& name)
{
    typedef std::map<std::wstring, CQuest*> QuestMap;
    QuestMap& quests = *reinterpret_cast<QuestMap*>(&m_Unknown40);
    QuestMap::iterator found = quests.find(name);
    return found != quests.end() ? reinterpret_cast<long long>(found->second) : 0;
}

int CQuestManager::getNPCIcon(CCharacter* npc)
{
    if (!npc ||
        !npc->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x68)) ||
        !m_pPlayer)
        return -1;

    CQuest* quest = getQuestForNPC(npc);
    if (!quest)
        return -1;

    TArrayList<CQuest*>& quests = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    for (unsigned int i = 0; i < quests.size(); ++i)
        if (quests[i] == quest)
            break;

    CQuestDialog* dialog = reinterpret_cast<CQuestDialog*>(
        quest->getQuestDialog(npc));

    if (!dialog || !*reinterpret_cast<unsigned char*>(
            reinterpret_cast<char*>(dialog) + 0x75))
        return -1;

    switch (*reinterpret_cast<int*>(
                reinterpret_cast<char*>(dialog) + 0x70))
    {
        case 1:
            return 23;
        case 2:
            return 26;
        case 3:
            return 22;
        case 4:
            return -1;
        default:
            return -1;
    }
}

long long CQuestManager::calculateNPCIcon(CCharacter* pCharacter)
{
    if (pCharacter == NULL || m_pPlayer == NULL)
        return 0;

    CQuest* quest = getQuestForNPC(pCharacter);

    pCharacter->removeUnitTheme(L"QUEST COMPLETE");
    pCharacter->removeUnitTheme(L"QUEST INCOMPLETE");
    pCharacter->removeUnitTheme(L"QUEST GIVING");
    pCharacter->removeUnitTheme(L"QUEST PASSIVE");

    if (CGameUI::getSingleton() != NULL &&
        CGameUI::getSingleton()->getUIIsInCinematic())
        return 1;

    if (quest == NULL)
        return 0;

    const unsigned char* characterData =
        reinterpret_cast<const unsigned char*>(pCharacter);
    if (!pCharacter->getEnabled() && characterData[0x70d])
        return 0;

    TArrayList<CQuest*>* quests =
        reinterpret_cast<TArrayList<CQuest*>*>(&m_Unknown18);
    bool questInList = false;
    for (unsigned int i = 0; i < quests->size(); ++i)
        if ((*quests)[i] == quest) {
            questInList = true;
            break;
        }

    CQuestDialog* dialog = reinterpret_cast<CQuestDialog*>(
        quest->getQuestDialog(pCharacter));
    if (dialog == NULL)
        return 0;

    const unsigned char* dialogData =
        reinterpret_cast<const unsigned char*>(dialog);

    if (*(dialogData + 0x75) == 0)
        return 1;

    const std::wstring& icon =
        *reinterpret_cast<const std::wstring*>(dialogData + 0x98);
    if (!icon.empty())
    {
        pCharacter->addUnitTheme(icon);
        return 1;
    }

    if (*reinterpret_cast<const int*>(dialogData + 0x70) == 4)
    {
        if (*(dialogData + 0x76) == 0)
            pCharacter->addUnitTheme(L"QUEST PASSIVE");
        else
            pCharacter->removeUnitTheme(L"QUEST PASSIVE");

        pCharacter->removeUnitTheme(L"QUEST COMPLETE");
        pCharacter->removeUnitTheme(L"QUEST INCOMPLETE");
        pCharacter->removeUnitTheme(L"QUEST GIVING");
        return 1;
    }

    if (questInList)
    {
        if (static_cast<unsigned char>(quest->isComplete(false)) != 0)
        {
            pCharacter->addUnitTheme(L"QUEST COMPLETE");
            pCharacter->removeUnitTheme(L"QUEST INCOMPLETE");
            pCharacter->removeUnitTheme(L"QUEST GIVING");
            pCharacter->removeUnitTheme(L"QUEST PASSIVE");
        }
        else
        {
            pCharacter->removeUnitTheme(L"QUEST COMPLETE");
            pCharacter->removeUnitTheme(L"QUEST GIVING");
            pCharacter->removeUnitTheme(L"QUEST PASSIVE");
            pCharacter->addUnitTheme(L"QUEST INCOMPLETE");
        }
    }
    else
    {
        pCharacter->addUnitTheme(L"QUEST GIVING");
        pCharacter->removeUnitTheme(L"QUEST COMPLETE");
        pCharacter->removeUnitTheme(L"QUEST INCOMPLETE");
        pCharacter->removeUnitTheme(L"QUEST PASSIVE");
    }

    return 1;
}

void CQuestManager::resetQuest(CQuest* quest)
{
    if (quest == NULL)
        return;

    reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).remove(quest);

    reinterpret_cast<std::map<std::wstring, bool>&>(m_Unknown70)[quest->m_sUnknown50] = false;

    // This array contains registered weak controller references, not dialogs.
    TArrayList<TSafePointer<CQuestController>*>& controllers =
        reinterpret_cast<TArrayList<TSafePointer<CQuestController>*>&>(quest->m_Unknown1B0);

    for (unsigned int i = 0; i < controllers.size(); ++i)
    {
        if (controllers[i]->getObject() != NULL &&
            std::wstring(controllers[i]->getObject()->m_sQuestName) == quest->m_sUnknown50)
        {
            controllers[i]->getObject()->questHasBeenCompleted(false);
        }
    }
}

void CQuestManager::resetQuestManager(bool reset)
{
    reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).clear();
    typedef std::map<std::wstring, bool> CompleteMap;
    CompleteMap& completed = *reinterpret_cast<CompleteMap*>(&m_Unknown70);
    for (CompleteMap::iterator i = completed.begin(); i != completed.end(); ++i)
        i->second = false;
    typedef std::map<std::wstring, CQuest*> QuestMap;
    QuestMap& quests = *reinterpret_cast<QuestMap*>(&m_Unknown40);
    for (QuestMap::iterator i = quests.begin(); i != quests.end(); ++i)
        i->second->reinitializeQuest(reset, false);
}

std::wstring CQuestManager::getDetailsForQuest(CQuest* quest)
{
    if (quest)
        return quest->getQuestDetails();
    return EMPTY_WSTRING;
}

bool CQuestManager::getQuestIsActive(const std::wstring& name)
{
    TArrayList<CQuest*>& quests = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    for (unsigned int i = 0; i < quests.size(); ++i)
        if (quests[i]->m_sUnknown50 == name)
            return true;
    return false;
}

void CQuestManager::getQuestNames(TArrayList<std::wstring>& names)
{
    typedef std::map<std::wstring, CQuest*> QuestMap;
    QuestMap& quests = *reinterpret_cast<QuestMap*>(&m_Unknown40);
    for (QuestMap::iterator i = quests.begin(); i != quests.end(); ++i)
        names.add(i->first);
}

CQuest* CQuestManager::getQuestForNPC(CBaseUnit* npc)
{
    if (!npc || !npc->getDataGroup())
        return 0;
    CDataGroup* data = npc->getDataGroup();
    typedef std::map<CDataGroup*, TArrayList<CQuest*>*> NPCQuestMap;
    NPCQuestMap& npcQuests = *reinterpret_cast<NPCQuestMap*>(&m_UnknownA0);
    NPCQuestMap::iterator entry = npcQuests.find(data);
    TArrayList<CQuest*> candidates(10);
    if (entry != npcQuests.end())
        for (unsigned int i = 0; i < entry->second->size(); ++i)
            if (static_cast<unsigned char>((*entry->second)[i]->getQuestIsValidForNPC(npc)))
                candidates.add((*entry->second)[i]);

    TArrayList<CQuest*>& active = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    for (unsigned int i = 0; i < active.size(); ++i)
        if (reinterpret_cast<CDataGroup*>(active[i]->m_iUnknown1E8) == npc->getDataGroup())
            return active[i];

    if (!candidates.size()) {
        CDataGroup* group = data->GetDataGroupByName(L"QUESTS", false);
        if (group) {
            typedef std::map<std::wstring, CQuest*> QuestMap;
            QuestMap& quests = *reinterpret_cast<QuestMap*>(&m_Unknown40);
            for (unsigned int i = 0; i < group->GetNumberOfDataValues(); ++i) {
                CDataValue::EDATAVALUETYPES type = group->GetDataValue(i)->GetValueType();
                if (type != CDataValue::DATAVALUE_STRING && type != CDataValue::DATAVALUE_TRANSLATE)
                    continue;
                std::wstring name = STRINGS::StringUpper(group->GetDataValue(i)->GetValueString(true));
                QuestMap::iterator found = quests.find(name);
                if (found == quests.end() || found->second->m_questAccepted)
                    continue;
                if (!static_cast<unsigned char>(found->second->getQuestIsValidForNPC(npc)))
                    continue;
                CQuest* quest = found->second;
                if (reinterpret_cast<CDataGroup*>(quest->m_iUnknown1E8) == npc->getDataGroup()) {
                    // Original quest threshold and dungeon string occupy opaque header fields.
                    int threshold = *reinterpret_cast<int*>(reinterpret_cast<char*>(quest) + 0x20);
                    bool below = m_pPlayer->getMaxDepth(
                        *reinterpret_cast<std::wstring*>(&quest->m_pUnknown30)) < threshold;
                    if (below)
                        return found->second;
                    quest = found->second;
                }
                candidates.add(quest);
            }
        }
    }
    if (!candidates.size())
        return 0;
    CQuest* selected = candidates[UTILITIES::randomIntegerBetweenVolatile(0, candidates.size() - 1)];
    if (selected)
        selected->initializeQuestWithNPC(npc);
    return selected;
}

void CQuestManager::getDialogsForNPC(TArrayList<CQuestDialog*>& dialogs, CBaseUnit* npc, bool retry)
{
    if (!npc)
        return;
    TArrayList<CQuest*>& active = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    for (unsigned int i = 0; i < active.size(); ++i) {
        CQuestDialog* dialog = reinterpret_cast<CQuestDialog*>(active[i]->getQuestDialog(npc));
        if (dialog)
            dialogs.add(dialog);
    }
    CQuest* quest = getQuestForNPC(npc);
    if (!quest)
        return;
    CQuestDialog* dialog = reinterpret_cast<CQuestDialog*>(quest->getQuestDialog(npc));
    if (dialog)
        dialogs.add(dialog);
    if (retry && !dialogs.size()) {
        quest = getQuestForNPC(npc);
        if (quest) {
            dialog = reinterpret_cast<CQuestDialog*>(quest->getQuestDialog(npc));
            if (dialog)
                dialogs.add(dialog);
        }
    }
}
