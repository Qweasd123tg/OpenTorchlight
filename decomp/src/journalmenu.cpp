#include "JournalMenu.h"
#include "Player.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "StringUtilities.h"
#include "StringTranslate.h"
#include <CEGUI.h>
#include <OgreUTFString.h>
#include <cmath>
#include "EmptyStrings.h"
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

#include "JournalMenu.h"
#include "Settings.h"
#include "GameVariables.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include "ResourceManager.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <CEGUI.h>

void CJournalMenu::createMenus()
{
    float width = (float)m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
    float height = (float)m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
    m_pModel = m_pResourceManager->createGenericModel(m_pSceneManager,
        L"media/ui/models/journal/journal.mesh", L"", false, false, false);
    m_pModel->generateExtremes(5, true);
    Ogre::AxisAlignedBox bounds(Ogre::Vector3(-100000,-100000,-100000),
                               Ogre::Vector3(100000,100000,100000));
    m_pModel->getEntity()->getMesh()->_setBounds(bounds, true);
    float x = width - height / 0.75f;
    m_pModel->setPosition(0.5f * (x / m_pSettings->GetFloat(KSETTINGS_YRATIO)),0.0f,0.0f);
    m_pModel->setVisible(false);
    m_pImageset = CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");
    m_pRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","JournalSheet","");
    m_pRoot->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    m_pRoot->setProperty("RiseOnClick","False");
    m_pRoot->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pRoot->setMousePassThroughEnabled(true);
    m_pRoot->setZOrderingEnabled(false);
    m_pRoot->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CJournalMenu::handle_MouseThrough,this));
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/journalmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    CEGUI::Window* blocker=layout->recursiveChildSearch("Blocker");
    blocker->getParent()->removeChildWindow(blocker);
    m_pRoot->addChildWindow(blocker);
    blocker->setProperty("RiseOnClick","False");
    blocker->moveToBack();
    blocker->setZOrderingEnabled(false);
    CEGUI::Window* close=layout->recursiveChildSearch("Close");
    close->setRiseOnClickEnabled(false);
    close->moveToFront();
    close->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CJournalMenu::handle_CloseButton,this));
    m_pContent=layout->recursiveChildSearch("JournalFrame");
    m_pBottomFrame=layout->recursiveChildSearch("BottomFrame");
    m_pBottomFrame->getParent()->removeChildWindow(m_pBottomFrame);
    m_pRoot->addChildWindow(m_pBottomFrame);
    m_pBottomFrame->setProperty("RiseOnClick","False");
    m_pBottomFrame->moveToFront();
    m_pBottomFrame->setZOrderingEnabled(false);
    m_pTopFrame=layout->recursiveChildSearch("TopFrame");
    m_pTopFrame->getParent()->removeChildWindow(m_pTopFrame);
    m_pRoot->addChildWindow(m_pTopFrame);
    m_pTopFrame->setProperty("RiseOnClick","False");
    m_pTopFrame->moveToFront();
    m_pTopFrame->setZOrderingEnabled(false);
}


#include "GenericModel.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "GameVariables.h"
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <fenv.h>
namespace journal_lifetime_layout {
typedef char parent[__builtin_offsetof(CJournalMenu,m_pParentWindow)==0x10?1:-1];
typedef char opened[__builtin_offsetof(CJournalMenu,m_bOpen)==0x38?1:-1];
typedef char closed[__builtin_offsetof(CJournalMenu,m_bClosed)==0x39?1:-1];
typedef char pending[__builtin_offsetof(CJournalMenu,m_bCloseRequested)==0x3a?1:-1];
typedef char edge[__builtin_offsetof(CJournalMenu,m_ScreenEdge)==0x70?1:-1];
typedef char top[__builtin_offsetof(CJournalMenu,m_TopEdge)==0x74?1:-1];
typedef char bank[__builtin_offsetof(CJournalMenu,m_pSoundBank)==0x80?1:-1];
typedef char seconds[__builtin_offsetof(CJournalMenu,m_LastPlayedSeconds)==0x88?1:-1];
typedef char size[sizeof(CJournalMenu)==0xa8?1:-1];
// The original converts ceilf to signed 64 bits, then keeps its low 32 bits.
inline int playedSeconds(float value) {
 if(value>=-9223372036854775808.0f && value<9223372036854775808.0f)
  return static_cast<int>(static_cast<unsigned>(static_cast<long long>(value)));
 ::feraiseexcept(FE_INVALID);
 return 0;
}
}
void CJournalMenu::setOwner(CCharacter* owner) { m_pOwner=owner; }
bool CJournalMenu::handle_CloseButton(const CEGUI::EventArgs& args) {
 if(static_cast<const CEGUI::MouseEventArgs&>(args).button==CEGUI::LeftButton)m_bCloseRequested=true;
 return true;
}
bool CJournalMenu::handle_MouseThrough(const CEGUI::EventArgs&) { return true; }
bool CJournalMenu::processInput(void*,float,bool active) {
 if(active&&m_bCloseRequested){setOpen(false);m_bCloseRequested=false;return false;}
 return true;
}
CJournalMenu::~CJournalMenu() {
 if(m_pModel){delete m_pModel;m_pModel=0;}
 if(m_pSoundBank){delete m_pSoundBank;m_pSoundBank=0;}
}
CJournalMenu::CJournalMenu(CGameUI& ui,CSettings& settings,Ogre::RenderWindow*,
 Ogre::SceneManager* scene,Ogre::SceneManager*,CEGUI::Window* parent,CResourceManager* resources)
 :m_pParentWindow(parent),m_pOwner(0),m_bOpen(false),m_bClosed(true),m_bCloseRequested(false),
 m_pSettings(&settings),m_pGameUI(&ui),m_pSceneManager(scene),m_pModel(0),m_pResourceManager(resources),
 m_TopEdge(5000.0f),m_pSoundBank(0),m_LastPlayedSeconds(0),m_Children(10)
{
 CSoundBankDataInformation* sounds=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
 m_pSoundBank=new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
 CSoundData* open=sounds->getSoundDataObject(L"INVENTORYOPEN");
 if(open)m_pSoundBank->addSample(22,open->m_iGuid);
 CSoundData* close=sounds->getSoundDataObject(L"INVENTORYCLOSE");
 if(close)m_pSoundBank->addSample(66,close->m_iGuid);
 CSoundData* assign=sounds->getSoundDataObject(L"POINTASSIGN");
 if(assign)m_pSoundBank->addSample(27,assign->m_iGuid);
 CSoundData* skill=sounds->getSoundDataObject(L"ASSIGNSKILL");
 if(skill)m_pSoundBank->addSample(30,skill->m_iGuid);
 float width=static_cast<float>(m_pSettings->GetInt(KSETTINGS_RES_WIDTH));
 m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
 m_ScreenEdge=width;
 createMenus();
}
void CJournalMenu::setOpen(bool open) {
 if(!m_bOpen&&open){
  m_pSoundBank->playSample(22,0,0.0f,0.0f,false);
  m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
  m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
  m_pModel->setVisible(true);
  if(m_pModel->animationPlaying("CLOSE"))m_pModel->blendAnimation("OPEN",false,0.1f,2.0f,-1.0f);
  else m_pModel->playAnimation("OPEN",false,2.0f,-1.0f);
  m_pModel->queueBlendAnimation("IDLE",true,0.1f,1.0f);
  m_pParentWindow->addChildWindow(m_pRoot);
  m_pRoot->moveToBack();
  updateLayout();
  m_pRoot->moveToBack();
  m_pTopFrame->moveToFront();
  m_pBottomFrame->moveToFront();
 }else if(m_bOpen&&!open){
  m_pSoundBank->playSample(66,0,0.0f,0.0f,false);
  m_pModel->blendAnimation("CLOSE",false,0.1f,2.0f,-1.0f);
  m_bClosed=false;
 }
 m_bOpen=open;
}
void CJournalMenu::update(float elapsed) {
 int width=m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
 int height=m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
 if(!m_bOpen&&m_bClosed)return;
 m_pModel->updateAnimation(elapsed,false);
 m_pModel->getEntity()->_updateAnimation();
 Ogre::Bone* top=m_pModel->m_pSkeleton->getBone("tag_topskill");
 Ogre::Vector3 position=m_pModel->getPosition(false);
 const Ogre::Vector3& tag=top->_getDerivedPosition();
 float sumY=tag.y+position.y;
 float scaledX=m_pGameUI->scaledY(tag.x+position.x);
 float halfWidth=float(width)*0.5f;
 float topX=scaledX+halfWidth;
 float panelY=-(m_pGameUI->scaledY(sumY)+float(height)*-0.5f);
 m_TopEdge=topX;
 m_pTopFrame->setPosition(CEGUI::UVector2(CEGUI::UDim(0,topX),CEGUI::UDim(0,panelY)));
 Ogre::Bone* bottom=m_pModel->m_pSkeleton->getBone("tag_bottomskill");
 position=m_pModel->getPosition(false);
 float bottomX=bottom->_getDerivedPosition().x+position.x;
 float bottomScreen=halfWidth+m_pGameUI->scaledY(bottomX);
 m_pBottomFrame->setPosition(CEGUI::UVector2(CEGUI::UDim(0,bottomScreen),CEGUI::UDim(0,panelY)));
 float edge=m_pGameUI->scaledY(50.0f)+bottomScreen;
 m_ScreenEdge=edge<float(width)?edge:float(width);
 if(m_bOpen){
  int seconds=journal_lifetime_layout::playedSeconds(::ceilf(journal_layout::player(m_pOwner).timePlayed));
  if(m_LastPlayedSeconds==seconds)return;
  updateLayout();
  m_LastPlayedSeconds=seconds;
 }
 if(!m_bOpen&&!m_bClosed){
  if(!m_pModel->animationPlaying("CLOSE")&&!m_pModel->animationQueued("CLOSE")){
   m_pModel->setVisible(false);m_bClosed=true;m_pParentWindow->removeChildWindow(m_pRoot);
  }
 }
}
