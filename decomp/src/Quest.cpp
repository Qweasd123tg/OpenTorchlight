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
