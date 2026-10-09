#include "JournalMenu.h"
#include "Player.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "StringUtilities.h"
#include "StringTranslate.h"
#include <CEGUI.h>
#include <OgreUTFString.h>
#include <cmath>
static const std::wstring EMPTY_WSTRING;
namespace journal_layout {
struct PlayerFields {char prefix[0x388];float timePlayed;char gap38c[0x7dc-0x38c];int counters[18];char gap824[0xa10-0x824];int ancestors;char flagA14;bool hardcore;};
struct ClientFields {char prefix[0x38ec];int difficulty;};
typedef char check_m_pRoot[__builtin_offsetof(CJournalMenu,m_pRoot)==24?1:-1];
typedef char check_m_pOwner[__builtin_offsetof(CJournalMenu,m_pOwner)==48?1:-1];
typedef char check_m_pGameUI[__builtin_offsetof(CJournalMenu,m_pGameUI)==72?1:-1];
typedef char check_m_pResourceManager[__builtin_offsetof(CJournalMenu,m_pResourceManager)==96?1:-1];
typedef char check_m_pContent[__builtin_offsetof(CJournalMenu,m_pContent)==120?1:-1];
typedef char check_m_Children[__builtin_offsetof(CJournalMenu,m_Children)==144?1:-1];
typedef char check_timePlayed[__builtin_offsetof(PlayerFields,timePlayed)==904?1:-1];
typedef char check_counters[__builtin_offsetof(PlayerFields,counters)==2012?1:-1];
typedef char check_ancestors[__builtin_offsetof(PlayerFields,ancestors)==2576?1:-1];
typedef char check_hardcore[__builtin_offsetof(PlayerFields,hardcore)==2581?1:-1];
typedef char check_difficulty[__builtin_offsetof(ClientFields,difficulty)==0x38ec?1:-1];
inline __attribute__((always_inline)) PlayerFields& player(CCharacter* p){return *reinterpret_cast<PlayerFields*>(p);}
inline __attribute__((always_inline)) CEGUI::Window* create(CJournalMenu* menu,float width,float y){
 CEGUI::Window* window=CEGUI::WindowManager::getSingleton().createWindow((const unsigned char*)"GuiLook/StaticText",STRINGS::uniqueName("gui_"),"");
 float h=menu->m_pGameUI->scaledY(23.0f);float w=menu->m_pGameUI->scaledY(width);
 window->setSize(CEGUI::UVector2(CEGUI::UDim(0,w),CEGUI::UDim(0,h)));
 float py=menu->m_pGameUI->scaledY(y);float px=menu->m_pGameUI->scaledY(0.0f);
 window->setPosition(CEGUI::UVector2(CEGUI::UDim(0,px),CEGUI::UDim(0,py)));
 menu->m_pContent->addChildWindow(window);return window;
}
inline __attribute__((always_inline)) void finish(CJournalMenu* menu,CEGUI::Window* window,const std::wstring& text,const char* alignment,bool value){
 std::string converted=STRINGS::StringConvertToUTF8(std::wstring(text.c_str()));window->setText((const unsigned char*)converted.c_str());
 if(value)window->setProperty("TextColour",CEGUI::PropertyHelper::colourToString(CEGUI::colour(1.0f,.88f,.24f,1.0f)));
 window->setProperty("HorzTextFormatting",alignment);window->moveToFront();menu->m_Children.add(window);window->setAlwaysOnTop(true);window->setMousePassThroughEnabled(true);
}
}
#define TRANSLATION(NAME,TEXT) static std::wstring NAME;if(NAME.empty())NAME=CStringTranslate::getSinglton()->getTranslateString(TEXT)
__attribute__((flatten)) void CJournalMenu::updateLayout(){
 using namespace journal_layout;
 if(!m_pOwner)return;CPlayer* owner=dynamic_cast<CPlayer*>(m_pOwner);if(!owner)return;
 for(unsigned i=0;i<m_Children.size();++i){CEGUI::Window* child=m_Children[i];if(child->getParent())child->getParent()->removeChildWindow(child);CEGUI::WindowManager::getSingleton().destroyWindow(child);}m_Children.clear();
 TRANSLATION(g_Difficulty,L"Difficulty");
 TRANSLATION(g_Easy,L"Easy");
 TRANSLATION(g_Normal,L"Normal");
 TRANSLATION(g_Hard,L"Hard");
 TRANSLATION(g_VeryHard,L"Very Hard");
 TRANSLATION(g_Hardcore,L"Hardcore");
 TRANSLATION(g_Ancestors,L"Ancestors");
 int row=0;CEGUI::Window* window;
 if(player(m_pOwner).hardcore){window=create(this,240,0);finish(this,window,g_Hardcore,"CentreAligned",false);row=1;}
 float y=24.0f*float(row);window=create(this,270,y);finish(this,window,g_Difficulty+L":","LeftAligned",false);
 std::wstring difficulty=EMPTY_WSTRING;switch(reinterpret_cast<ClientFields*>(m_pResourceManager->getGameClient())->difficulty){case 0:difficulty=g_Easy;break;case 1:difficulty=g_Normal;break;case 2:difficulty=g_Hard;break;case 3:difficulty=g_VeryHard;break;}
 window=create(this,270,y);finish(this,window,difficulty,"RightAligned",true);++row;
 y=24.0f*float(row);window=create(this,270,y);finish(this,window,g_Ancestors+L":","LeftAligned",false);
 std::wstring ancestors=STRINGS::GetValueAsWString(player(m_pOwner).ancestors);window=create(this,270,y);finish(this,window,ancestors,"RightAligned",true);++row;
 for(unsigned i=0;i<18;++i,++row){std::wstring label=EMPTY_WSTRING;switch(i){
 case 0:{TRANSLATION(g_TimePlayed,L"Time Played");label=g_TimePlayed;break;}
 case 1:{TRANSLATION(g_GoldGathered,L"Gold Gathered");label=g_GoldGathered;break;}
 case 2:{TRANSLATION(g_LevelsExplored,L"Levels Explored");label=g_LevelsExplored;break;}
 case 3:{TRANSLATION(g_StepsTaken,L"Steps Taken");label=g_StepsTaken;break;}
 case 4:{TRANSLATION(g_QuestsCompleted,L"Quests Completed");label=g_QuestsCompleted;break;}
 case 5:{TRANSLATION(g_Deaths,L"Deaths");label=g_Deaths;break;}
 case 6:{TRANSLATION(g_MonstersDefeated,L"Monsters Defeated");label=g_MonstersDefeated;break;}
 case 7:{TRANSLATION(g_ChampionsDefeated,L"Champions Defeated");label=g_ChampionsDefeated;break;}
 case 8:{TRANSLATION(g_SkillsCast,L"Skills/Spells Cast");label=g_SkillsCast;break;}
 case 9:{TRANSLATION(g_ChestsOpened,L"Chests Opened");label=g_ChestsOpened;break;}
 case 10:{TRANSLATION(g_TrapsSprung,L"Traps Sprung");label=g_TrapsSprung;break;}
 case 11:{TRANSLATION(g_BarrelsBroken,L"Barrels Broken");label=g_BarrelsBroken;break;}
 case 12:{TRANSLATION(g_PotionsUsed,L"Potions Used");label=g_PotionsUsed;break;}
 case 13:{TRANSLATION(g_PortalsUsed,L"Portals Used");label=g_PortalsUsed;break;}
 case 14:{TRANSLATION(g_FishCaught,L"Fish Caught");label=g_FishCaught;break;}
 case 15:{TRANSLATION(g_TimesGambled,L"Times Gambled");label=g_TimesGambled;break;}
 case 16:{TRANSLATION(g_ItemsTransmuted,L"Items Transmuted");label=g_ItemsTransmuted;break;}
 case 17:{TRANSLATION(g_ItemsEnchanted,L"Items Enchanted");label=g_ItemsEnchanted;break;}
 }label+=L":";std::wstring value=EMPTY_WSTRING;
 if(i==0){float elapsed=ceilf(player(owner).timePlayed);TRANSLATION(g_Hrs,L"hrs");TRANSLATION(g_Mins,L"mins");TRANSLATION(g_Secs,L"secs");
  unsigned seconds=static_cast<unsigned>(static_cast<long long>(elapsed));unsigned minutes=seconds/60;unsigned hours=minutes/60;
  std::string sec=STRINGS::GetValueAsString(int(seconds-minutes*60));std::string min=STRINGS::GetValueAsString(minutes-hours*60);std::string hr=STRINGS::GetValueAsString(hours);
  value=(Ogre::UTFString(hr)+Ogre::UTFString(g_Hrs)+Ogre::UTFString(L" ")+Ogre::UTFString(min)+Ogre::UTFString(g_Mins)+Ogre::UTFString(L" ")+Ogre::UTFString(sec)+Ogre::UTFString(g_Secs)).asWStr();
 }else value=STRINGS::GetValueAsWString(player(owner).counters[i]);
 y=24.0f*float(row);window=create(this,270,y);finish(this,window,label,"LeftAligned",false);window=create(this,270,y);finish(this,window,value,"RightAligned",true);
 }
 m_pRoot->moveToBack();
}
#undef TRANSLATION
