#include "MenuQuestWorld.h"
#include "MenuModelGpuBoundary.h"
#include "DataGroup.h"
#include "GameVariables.h"
#include <cwchar>
TL_ORIGINAL(void,mgCreateQuestForLayout,(CQuestMenu*),"_ZN10CQuestMenu11createMenusEv")
TL_ORIGINAL(void,mgOldQuestLayout,(CQuestMenu*),"_ZN10CQuestMenu12updateLayoutEv")
extern "C" void mgNewQuestLayout(CQuestMenu*) __asm__("_ZN10CQuestMenu12updateLayoutEv");
TL_FUNCTION(mgLayoutEditorState,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;
bool notEditor(CResourceManager*){return false;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    settings->SetInt(KSETTINGS_RES_WIDTH,c.index&1?1600:800);settings->SetInt(KSETTINGS_RES_HEIGHT,c.index&2?900:600);
    CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);
    CDataGroup group(L"REWARD",NULL,4,4,NULL);group.AddDataValue(L"ICON",std::wstring(L"iconhelm"),false);
    menugui::QuestWorld world(f);
    detour::Set editor;TL_REDIRECT(editor,mgLayoutEditorState,&notEditor);if(editor.failed())std::abort();
    mgCreateQuestForLayout(f.quest);f.root->addChildWindow(f.quest->m_rootWindow);
    f.ui->m_itemImagesets.add(CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons"));
    unsigned count=c.index%9,selected=c.index/9%9,profile=c.index/81;
    for(unsigned i=0;i<count;++i){
        wchar_t name[40];std::swprintf(name,40,L"Quest %u",i);std::wstring details=(profile&1)&&i%3==0?L"":i%2?L"Unicode квест\nsecond line":L"Quest description";
        CQuest*q=world.add(name,details);q->m_complete=true;q->m_UnknownF8[0].add((i+profile)%2!=0);q->m_bUnknown208=(i+profile)%2!=0;
        q->m_pQuestRewards->m_fExperience=float(i*137);q->m_pQuestRewards->m_fGold=float(i*23);q->m_pQuestRewards->m_fFame=float(i*7);
        for(unsigned j=0;j<(i+profile)%5;++j){CEquipment*item=new CEquipment(&f.resources);item->m_pDataGroup=&group;item->m_iUnknown238=j+1;item->m_bUnknown348=true;q->m_pQuestRewards->m_rewardItems.add(item);}
    }
    if(profile==2)world.player->m_questManager=NULL;
    f.quest->m_owner=profile>=3?NULL:world.player;f.quest->m_allowAbandon=(profile&1)!=0;f.quest->m_hoveredReward=world.player;
    f.quest->m_selectedQuestID=selected;f.quest->m_selectedQuestIndex=123;
    for(unsigned i=0;i<3;++i){char name[40];std::sprintf(name,"old-quest-child-%u",i);CEGUI::Window*w=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow",name);if(i<2)(i?f.quest->m_bottomWindow:f.quest->m_topWindow)->addChildWindow(w);f.quest->m_questWindows.add(w);}
    typedef void(*Fn)(CQuestMenu*);Fn fn=ours?mgNewQuestLayout:mgOldQuestLayout;if(!autotest::beginInvocation(out,fn))return;fn(f.quest);out.callCompleted=1;
    unsigned values[]={f.quest->m_selectedQuestID,unsigned(f.quest->m_selectedQuestIndex),f.quest->m_hoveredReward==world.player,f.quest->m_questWindows.size()};out.add(values,sizeof(values));
    for(unsigned i=0;i<3;++i){char name[40];std::sprintf(name,"old-quest-child-%u",i);unsigned exists=CEGUI::WindowManager::getSingleton().isWindowPresent(name);out.add(&exists,4);}
    for(unsigned i=0;i<world.quests.size();++i){unsigned completed=world.quests[i]->m_complete;out.add(&completed,4);}
    std::string snapshot=tlheadless::snapshot(*f.root);unsigned n=snapshot.size();out.add(&n,4);out.add(snapshot.data(),snapshot.size());
    for(unsigned i=0;i<3;++i){char name[40];std::sprintf(name,"old-quest-child-%u",i);if(CEGUI::WindowManager::getSingleton().isWindowPresent(name))CEGUI::WindowManager::getSingleton().destroyWindow(name);}
    f.quest->m_questWindows.clear();
}
}
TL_TEST(complete_menu_quest_layout_real_graph){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_quest_layout_real_graph",0xbc4430,&side,405);}
