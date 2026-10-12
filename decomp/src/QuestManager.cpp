#include "Achievement.h"
#include "Achievements.h"
#include "GameClient.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "SteamStats.h"
#include "StringTranslate.h"
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


namespace {
typedef char QuestManagerCompleteMapOffset[__builtin_offsetof(CQuestManager,m_Unknown70)==0x70?1:-1];
typedef char QuestManagerResourcesOffset[__builtin_offsetof(CQuestManager,m_pResourceManager)==0x38?1:-1];
typedef char QuestTitleOffset[__builtin_offsetof(CQuest,m_pUnknown38)==0x38?1:-1];
typedef char QuestSubtitleOffset[__builtin_offsetof(CQuest,m_pUnknown40)==0x40?1:-1];
typedef char QuestControllerListOffset[__builtin_offsetof(CQuest,m_Unknown1B0)==0x1b0?1:-1];
typedef char QuestNotificationOffset[__builtin_offsetof(CQuest,m_bUnknown209)==0x209?1:-1];
typedef char QuestRepeatabilityOffset[__builtin_offsetof(CQuest,m_bUnknown20B)==0x20b?1:-1];
typedef char QuestControllerNameOffset[__builtin_offsetof(CQuestController,m_sQuestName)==0xa8?1:-1];
typedef char QuestManagerWideStringSize[sizeof(std::wstring)==8?1:-1];
}

long long CQuestManager::removeQuest(CQuest* quest, bool abandoned)
{
    if (!quest)
        return 0;

    reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).remove(quest);
    quest->initializeQuestWithNPC(NULL);
    quest->setQuestAccepted(false);
    if (abandoned)
    {
        quest->cleanUp(false);
        quest->reinitializeQuest(true, false);
    }

    TArrayList<TSafePointer<CQuestController>*>& controllers =
        reinterpret_cast<TArrayList<TSafePointer<CQuestController>*>&>(quest->m_Unknown1B0);
    for (unsigned int i = 0; i < controllers.size(); ++i)
    {
        if (controllers[i]->getObject() != NULL &&
            std::wstring(controllers[i]->getObject()->m_sQuestName) == quest->m_sUnknown50)
        {
            controllers[i]->getObject()->questHasBeenAccepted(false);
            if (abandoned)
                controllers[i]->getObject()->questHasBeenAbandoned();
        }
    }

    m_pResourceManager->getLevel()->updateNPCIcons();
    m_pResourceManager->getLevel()->updateAutomapIcons();
    return 1;
}

void CQuestManager::questEventUpdate(EQUEST_EVENTS event, CCharacter* character,
                                     CBaseUnit* target)
{
    if (!m_pPlayer)
        return;

    TArrayList<CQuest*>& active = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    bool refresh = false;
    for (unsigned int i = 0; i < active.size(); ++i)
    {
        CQuest* quest = active[i];
        if (!quest)
            continue;

        const unsigned char wasComplete = static_cast<unsigned char>(quest->isComplete(false));
        if (wasComplete != 0 && event != static_cast<EQUEST_EVENTS>(5))
            continue;

        quest->questEventUpdate(event, character, target);
        if (static_cast<unsigned char>(quest->isComplete(false)) != 0 &&
            wasComplete == 0 && !quest->m_bUnknown209)
        {
            if (!quest->getQuestDetails().empty())
            {
                // Character's sound bank is an opaque/private field at +0x298.
                CSoundBank* playerSound = *reinterpret_cast<CSoundBank**>(
                    reinterpret_cast<char*>(m_pPlayer) + 0x298);
                if (playerSound)
                    playerSound->queueGlobalSample(32, 1.0f, 1.0f);
                if (m_pSoundBank)
                    m_pSoundBank->playSample(32, NULL, 0.0f, 0.0f, false);
            }

            CLevel* level = m_pPlayer->getLevel();
            if (level && quest->m_bUnknown29)
            {
                static std::wstring g_QuestComplete;
                if (g_QuestComplete.empty())
                    g_QuestComplete = CStringTranslate::getSinglton()->getTranslateString(L"Quest Complete");

                // Keep this level, but re-read its GameClient/UI after each callback.
                (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                    getGameUI()->setBigText(g_QuestComplete, 2.0f);
                {
                    std::wstring text = quest->replaceStringTags(quest->m_sUnknown58);
                    (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                        getGameUI()->setSmallText(text, 2.0f);
                }
                if (quest->m_bUnknown2C || quest->m_bUnknown208)
                    CGameUI::getSingleton()->queueTip(static_cast<EContextTip>(20));
            }

            quest->m_bUnknown209 = true;
            refresh = true;
        }
        else if (static_cast<unsigned char>(quest->isComplete(false)) == wasComplete)
        {
            // The original third query refreshes on equal low bytes, not a change.
            refresh = true;
        }
    }

    if (refresh)
        CGameUI::getSingleton()->refreshQuestMenu();
}

long long CQuestManager::completeQuest(CQuest* quest)
{
    if (!quest)
        return 0;

    if (m_pPlayer)
        giveRewardForQuest(quest);
    quest->setQuestAccepted(false);
    quest->initializeQuestWithNPC(NULL);
    quest->setIsComplete(!quest->m_bUnknown20B);
    reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).remove(quest);

    typedef std::map<std::wstring, bool> CompleteMap;
    CompleteMap& completed = *reinterpret_cast<CompleteMap*>(&m_Unknown70);
    bool& complete = completed[quest->m_sUnknown50];
    complete = !quest->m_bUnknown20B;

    TArrayList<TSafePointer<CQuestController>*>& controllers =
        reinterpret_cast<TArrayList<TSafePointer<CQuestController>*>&>(quest->m_Unknown1B0);
    for (unsigned int i = 0; i < controllers.size(); ++i)
    {
        if (controllers[i]->getObject() != NULL &&
            std::wstring(controllers[i]->getObject()->m_sQuestName) == quest->m_sUnknown50)
        {
            controllers[i]->getObject()->questHasBeenCompleted(true);
        }
    }

    if (m_pResourceManager->getLevel())
    {
        m_pResourceManager->getLevel()->updateNPCIcons();
        m_pResourceManager->getLevel()->updateAutomapIcons();
    }

    bool palaceComplete;
    {
        const std::wstring palaceAlric = STRINGS::StringUpper(L"PalaceAlricDead");
        const std::wstring questName = STRINGS::StringUpper(quest->m_sUnknown50);
        palaceComplete = questName == palaceAlric;
        if (!palaceComplete)
        {
            const std::wstring palacePT2 = STRINGS::StringUpper(L"PalacePT2");
            const std::wstring nextQuestName = STRINGS::StringUpper(quest->m_sUnknown50);
            palaceComplete = nextQuestName == palacePT2;
        }
    }
    if (palaceComplete)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(13))->forceComplete();

    if (m_pPlayer)
    {
        bool retireeQuest;
        {
            const unsigned int property = KSETTINGS_RETIREE_QUEST;
            CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
            const std::wstring retireeName = STRINGS::StringUpper(settings->GetString(property));
            const std::wstring questName = STRINGS::StringUpper(quest->m_sUnknown50);
            retireeQuest = questName == retireeName;
        }
        if (retireeQuest)
        {
            const unsigned int property = KSETTINGS_GAME_COMPLETED_ONCE;
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(property, 1);

            CGameClient* client = m_pResourceManager->getGameClient();
            if (client && client->getGameState() == static_cast<EGameState>(1))
            {
                int destroyer = CSteamStats::getSingleton()->getStatInt(static_cast<ESTATS>(23));
                int alchemist = CSteamStats::getSingleton()->getStatInt(static_cast<ESTATS>(22));
                int vanquisher = CSteamStats::getSingleton()->getStatInt(static_cast<ESTATS>(21));

                if (m_pPlayer->getPlayerClassName() == L"DESTROYER" && destroyer == 0)
                {
                    CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(23), 1);
                    ++destroyer;
                }
                else if (m_pPlayer->getPlayerClassName() == L"ALCHEMIST" && alchemist == 0)
                {
                    CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(22), 1);
                    ++alchemist;
                }
                else if (m_pPlayer->getPlayerClassName() == L"VANQUISHER" && vanquisher == 0)
                {
                    CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(21), 1);
                    ++vanquisher;
                }

                if (destroyer != 0 && vanquisher != 0 && alchemist != 0)
                    CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(23))->forceComplete();
            }
        }
    }
    return 1;
}

long long CQuestManager::giveQuest(CQuest* quest, CBaseUnit*, bool announce)
{
    if (!quest || quest->m_questAccepted)
        return 0;

    TArrayList<CQuest*>& active = reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18);
    for (unsigned int i = 0; i < active.size(); ++i)
        if (active[i] == quest)
            return 0;

    static std::wstring g_NewQuest;
    if (g_NewQuest.empty())
        g_NewQuest = CStringTranslate::getSinglton()->getTranslateString(L"New Quest");

    active.add(quest);
    quest->setQuestAccepted(true);
    if (m_pPlayer)
    {
        if (announce && !quest->m_gap25)
        {
            if (!quest->getQuestDetails().empty() &&
                !quest->replaceStringTags(quest->m_sUnknown58).empty())
            {
                CSoundBank* playerSound = *reinterpret_cast<CSoundBank**>(
                    reinterpret_cast<char*>(m_pPlayer) + 0x298);
                if (playerSound)
                    playerSound->queueGlobalSample(31, 1.0f, 1.0f);
                if (m_pSoundBank)
                    m_pSoundBank->playSample(31, NULL, 0.0f, 0.0f, false);
            }

            if (!quest->m_gap25)
            {
                CLevel* level = m_pPlayer->getLevel();
                if (level)
                {
                    const std::wstring& title = *reinterpret_cast<const std::wstring*>(&quest->m_pUnknown38);
                    const std::wstring& subtitle = *reinterpret_cast<const std::wstring*>(&quest->m_pUnknown40);
                    if (!quest->replaceStringTags(title).empty() &&
                        quest->replaceStringTags(subtitle).empty())
                    {
                        std::wstring text = quest->replaceStringTags(title);
                        (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                            getGameUI()->setBigText(text, 2.0f);
                    }
                    else if (quest->replaceStringTags(title).empty() &&
                             !quest->replaceStringTags(subtitle).empty())
                    {
                        std::wstring text = quest->replaceStringTags(subtitle);
                        (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                            getGameUI()->setSmallText(text, 2.0f);
                    }
                    else if (!quest->replaceStringTags(title).empty() &&
                             !quest->replaceStringTags(subtitle).empty())
                    {
                        {
                            std::wstring text = quest->replaceStringTags(title);
                            (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                                getGameUI()->setBigText(text, 2.0f);
                        }
                        {
                            std::wstring text = quest->replaceStringTags(subtitle);
                            (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                                getGameUI()->setSmallText(text, 2.0f);
                        }
                    }
                    else if (!quest->replaceStringTags(quest->m_sUnknown58).empty())
                    {
                        (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                            getGameUI()->setBigText(g_NewQuest, 2.0f);
                        std::wstring text = quest->replaceStringTags(quest->m_sUnknown58);
                        (*reinterpret_cast<CGameClient**>(reinterpret_cast<char*>(level) + 0x220))->
                            getGameUI()->setSmallText(text, 2.0f);
                    }
                }
            }
        }

        if (quest->m_bUnknown2B &&
            static_cast<unsigned char>(quest->isComplete(false)) != 0)
        {
            completeQuest(quest);
            removeQuest(quest, false);
        }
    }

    if (m_pResourceManager->getLevel())
    {
        m_pResourceManager->getLevel()->updateNPCIcons();
        m_pResourceManager->getLevel()->updateAutomapIcons();
    }

    TArrayList<TSafePointer<CQuestController>*>& controllers =
        reinterpret_cast<TArrayList<TSafePointer<CQuestController>*>&>(quest->m_Unknown1B0);
    for (unsigned int i = 0; i < controllers.size(); ++i)
    {
        if (controllers[i]->getObject() != NULL &&
            std::wstring(controllers[i]->getObject()->m_sQuestName) == quest->m_sUnknown50)
        {
            controllers[i]->getObject()->questHasBeenAccepted(true);
        }
    }
    return 1;
}
