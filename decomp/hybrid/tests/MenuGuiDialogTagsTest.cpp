#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
#include "UnitResourceList.h"
TL_ORIGINAL(void,mgOldTags,(CQuestDialogMenu*),"_ZN16CQuestDialogMenu16updateDialogTagsEv")
extern "C" void mgNewTags(CQuestDialogMenu*) __asm__("_ZN16CQuestDialogMenu16updateDialogTagsEv");
TL_ORIGINAL(void,mgTagEquipmentCtor,(CEquipment*,CResourceManager*),"_ZN10CEquipmentC1EP16CResourceManager")
TL_ORIGINAL(void,mgTagEquipmentDtor,(CEquipment*),"_ZN10CEquipmentD1Ev")
TL_FUNCTION(mgNamedUnitGroup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CDataGroup*namedGroup;unsigned scenario;
void n(unsigned x){output->add(&x,4);}void wide(const std::wstring&s){n(s.size());output->add(s.data(),4*s.size());}
CDataGroup*lookup(CUnitResourceList*p,const std::wstring&name){n(10);n(p==CUnitResourceList::getSingleton());wide(name);return scenario==7?NULL:(name==L"ARCHER"||name==L"TRINKET")?namedGroup:NULL;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    output=&out;scenario=c.index/16;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture level;
    CDataGroup own(L"owner",NULL,2,2,NULL),group(L"target",NULL,2,2,NULL),other(L"other",NULL,2,2,NULL);namedGroup=&group;
    CPlayer*owner=nativegame::createPlayer(&f.resources);CPlayer*player=nativegame::createPlayer(&f.resources);CEquipment*itemObject=static_cast<CEquipment*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEquipment),0,0,0));mgTagEquipmentCtor(itemObject,&f.resources);CEquipment&item=*itemObject;
    owner->m_pDataGroup=&own;player->m_pDataGroup=scenario==5?&other:&group;item.m_pDataGroup=scenario==5?&group:&other;
    f.nativeClient.client->m_pPlayer=player;f.ui->m_pCharacter=player;
    f.resources.m_pLevel=scenario>=4?&level.level:NULL;level.level.m_resourceManager=&f.resources;
    finishlevel::prepend(level.level.m_pCharacters,static_cast<CCharacter*>(NULL));finishlevel::prepend(level.level.m_pCharacters,static_cast<CCharacter*>(owner));if(scenario!=6)finishlevel::prepend(level.level.m_pCharacters,static_cast<CCharacter*>(player));finishlevel::prepend(level.level.m_items,static_cast<CItem*>(&item));
    f.dialog->m_unit=scenario==0?NULL:scenario==1?static_cast<CBaseUnit*>(&item):static_cast<CBaseUnit*>(owner);
    owner->m_bBaseUnitFlag0=false;owner->m_targetLocked=scenario==8;owner->m_eAIState=scenario==9?AISTATE_DEAD:static_cast<EAIState>(0);
    if(scenario==2)owner->m_pResourceManager=NULL;
    const char*texts[]={"","plain text","<OTHER=PLAYER>","<LOOKAT=PLAYER>","<LOOKAT=ARCHER>","<LOOKAT=TRINKET>","<LOOKAT=missing>","<LOOKAT=PLAYER>hello<LOOKAT=ARCHER>","<LOOKAT=ARCHER><LOOKAT=PLAYER>","<LOOKAT=TRINKET><LOOKAT=ARCHER>","<LOOKAT>","<LOOKAT=unfinished","<> malformed<OTHER=x>","<lookat=PLAYER>","<LOOKAT=>","<LOOKAT=PLAYER><LOOKAT=TRINKET>"};f.dialog->m_dialogName=texts[c.index%16];
    {detour::Set hooks;TL_REDIRECT(hooks,mgNamedUnitGroup,&lookup);if(hooks.failed())std::abort();typedef void(*Fn)(CQuestDialogMenu*);Fn fn=ours?mgNewTags:mgOldTags;if(!autotest::beginInvocation(out,fn))return;fn(f.dialog);out.callCompleted=1;}
    n(100);n(f.dialog->m_dialogName.size());out.add(f.dialog->m_dialogName.data(),f.dialog->m_dialogName.size());n(owner->m_targetCharacter.getObject()==player);n(owner->m_targetCharacter.getObject()==NULL);n(owner->m_targetItem.getObject()==&item);n(owner->m_targetItem.getObject()==NULL);
    f.dialog->m_unit=NULL;f.nativeClient.client->m_pPlayer=NULL;f.ui->m_pCharacter=NULL;owner->m_pResourceManager=&f.resources;f.resources.m_pLevel=NULL;level.level.m_resourceManager=&level.resources;
    nativegame::destroyPlayer(owner);nativegame::destroyPlayer(player);mgTagEquipmentDtor(itemObject);Ogre::NedAllocImpl::deallocBytes(itemObject);
}
}
TL_TEST(complete_menu_dialog_tags_real_owners){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_dialog_tags_real_owners",0xbb04c0,&side,160);}
