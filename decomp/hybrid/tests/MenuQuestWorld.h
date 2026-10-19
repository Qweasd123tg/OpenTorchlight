#ifndef OTL_MENU_QUEST_WORLD_H
#define OTL_MENU_QUEST_WORLD_H
#include "AutoTest.h"
#include "HeadlessGui.h"
#define private public
#define protected public
#include "Player.h"
#undef protected
#undef private
#include "MenuGuiFixture.h"
#include "Quest.h"
#include "QuestRewards.h"
#include "QuestDialog.h"
#include "QuestManager.h"
namespace menugui {
// Native manager belongs to Client; active quests are borrowed, while this
// fixture owns the quests and their native owning rewards/dialog subgraphs.
struct QuestWorld {
    Fixture& f;
    CPlayer* player;
    CQuestManager* manager;
    std::vector<CQuest*> quests;
    explicit QuestWorld(Fixture& value):f(value),player(nativegame::createPlayer(&f.resources)),manager(f.nativeClient.client->m_questManager){
        if(!player||!manager||manager->m_Unknown18.size())std::abort();
        player->m_questManager=manager;manager->m_pPlayer=player;
        f.nativeClient.client->m_pPlayer=player;f.ui->m_pCharacter=player;
    }
    CQuest* add(const std::wstring&name,const std::wstring&details){
        CQuest*q=new CQuest(&f.resources,manager);quests.push_back(q);
        q->m_sUnknown58=name;q->m_bUnknown208=false;
        q->m_pQuestDialog=new CQuestDialog(q);q->m_pQuestDialog->m_dialogText.add(details);q->m_pQuestDialog->m_bMakePetOnAccept=false;
        q->m_pQuestRewards=new CQuestRewards(q);manager->m_Unknown18.add(q);return q;
    }
    ~QuestWorld(){
        f.quest->m_owner=NULL;f.dialog->m_unit=NULL;f.dialog->m_dialog=NULL;
        f.nativeClient.client->m_pPlayer=NULL;f.ui->m_pCharacter=NULL;
        manager->m_Unknown18.clear();manager->m_pPlayer=NULL;
        for(unsigned i=0;i<quests.size();++i)delete quests[i];
        player->m_questManager=NULL;nativegame::destroyPlayer(player);
    }
};
}
#endif
