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

long long CQuestManager::getPlayerHasQuest(CQuest* pQuest)
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
    typedef std::map<std::wstring, char> QuestCompleteMap;
    QuestCompleteMap& quests =
        *reinterpret_cast<QuestCompleteMap*>(&m_iUnknown78);
    QuestCompleteMap::iterator i = quests.find(name);
    return i != quests.end() ? i->second : 0;
}

long long CQuestManager::getQuestByName(const std::wstring& name)
{
    struct Node
    {
        void* parent;
        Node* left;
        Node* right;
        std::wstring key;
        void* value;
    };

    Node* node = static_cast<Node*>(m_pUnknown50);
    Node* candidate = 0;

    while (node != 0)
    {
        if (node->key.compare(name) < 0)
        {
            node = node->left;
        }
        else
        {
            candidate = node;
            node = node->right;
        }
    }

    return candidate != 0 && candidate->key == name
        ? reinterpret_cast<long long>(candidate->value)
        : 0;
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

    reinterpret_cast<TArrayList<CQuest*>&>(m_Unknown18).find(quest);

    CQuestDialog* dialog = reinterpret_cast<CQuestDialog*>(
        quest->getQuestDialog(npc));

    if (!dialog || !*reinterpret_cast<unsigned char*>(
            reinterpret_cast<char*>(dialog) + 0x75))
        return -1;

    switch (*reinterpret_cast<int*>(
                reinterpret_cast<char*>(dialog) + 0x70))
    {
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
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
    bool questInList = quests->find(quest);

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
        if (quest->isComplete(false))
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

    TArrayList<CQuestDialog*>& dialogs =
        reinterpret_cast<TArrayList<CQuestDialog*>&>(quest->m_Unknown1B0);

    for (unsigned int i = 0; i < dialogs.size(); ++i)
    {
        CQuestDialog* dialog = dialogs[i];
        CQuestController* controller =
            *reinterpret_cast<CQuestController**>(dialog);

        const std::wstring& questName =
            *reinterpret_cast<const std::wstring*>(
                reinterpret_cast<const char*>(controller) + 0xA8);

        if (*reinterpret_cast<void**>(controller) != NULL &&
            questName == quest->m_sUnknown50)
        {
            controller->questHasBeenCompleted(false);
        }
    }
}
