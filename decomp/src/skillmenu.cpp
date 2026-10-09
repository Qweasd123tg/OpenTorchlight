#include "SkillMenu.h"
#include "Skill.h"
#include "Character.h"
#include "SkillManager.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include <CEGUI.h>
#include <cmath>

namespace skill_layout {
// Views of original fields beyond the currently recovered public declarations.
struct ActorFields {
 char prefix[0x100]; unsigned int level;
 char gap104[0x1c8-0x104]; CSkillManager* manager;
 char gap1d0[0x460-0x1d0]; int points;
 char gap464[0x950-0x464]; long long primary[12]; long long secondary[12];
};
struct SkillFields {
 char prefix[0x60]; int activation;
 char gap64[0xa8-0x64]; unsigned int levelCount;
 char gapac[0xdc-0xac]; unsigned int baseLevel; unsigned int effectiveLevel;
 char gape4[0x10c-0xe4]; int column,row,pane;
 char gap118[0x150-0x118]; long long guid; unsigned int maxLevel;
};
struct ManagerFields { char prefix[0x60]; TArrayList<CSkill*> skills; };
inline __attribute__((always_inline)) ActorFields& actor(CCharacter* p) {return *reinterpret_cast<ActorFields*>(p);}
inline __attribute__((always_inline)) SkillFields& fields(CSkill* p) {return *reinterpret_cast<SkillFields*>(p);}
inline __attribute__((always_inline)) CEGUI::String utf8(const char* p) {return CEGUI::String(reinterpret_cast<const unsigned char*>(p));}
inline __attribute__((always_inline)) CEGUI::Window* create(const char* type) {
 return CEGUI::WindowManager::getSingleton().createWindow(utf8(type),STRINGS::uniqueName(std::string("gui_")).c_str(),"");
}
inline __attribute__((always_inline)) void pos(CSkillMenu* menu,CEGUI::Window* w,float x,float y) {
 float sy=menu->m_pGameUI->scaledY(y);float sx=menu->m_pGameUI->scaledY(x);
 w->setPosition(CEGUI::UVector2(CEGUI::UDim(0,sx),CEGUI::UDim(0,sy)));
}
inline __attribute__((always_inline)) void size(CSkillMenu* menu,CEGUI::Window* w,float x,float y) {
 float sy=menu->m_pGameUI->scaledY(y);float sx=menu->m_pGameUI->scaledY(x);
 w->setSize(CEGUI::UVector2(CEGUI::UDim(0,sx),CEGUI::UDim(0,sy)));
}
inline __attribute__((always_inline)) void image(CSkillMenu* menu,CEGUI::Window* w,const char* name,const char* prop="Image") {
 w->setProperty(prop,CEGUI::PropertyHelper::imageToString(&menu->m_pImages->getImage(utf8(name))));
}
inline __attribute__((always_inline)) void skillImage(CSkillMenu* menu,CEGUI::Window* w,const std::wstring& name) {
 w->setProperty("Image",CEGUI::PropertyHelper::imageToString(menu->m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToNarrow(name.c_str()).c_str()))));
}
inline __attribute__((always_inline)) void tint(CEGUI::Window* w,float value) {
 // GCC evaluates this original chained expression from the last colour back.
 CEGUI::String br=CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1));
 CEGUI::String bl=CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1));
 CEGUI::String tr=CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1));
 CEGUI::String tl=CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1));
 w->setProperty("ImageColours","tl:"+tl+"tr:"+tr+"bl:"+bl+"br:"+br);
}
inline __attribute__((always_inline)) void overlay(CSkillMenu* menu,float x,float y,float width,const char* horizontal,const char* vertical,int value,bool hotkey) {
 CEGUI::Window* w=create("GuiLook/StaticTextOutline");menu->m_Panes[menu->m_iPane]->addChildWindow(w);w->moveToFront();w->setRiseOnClickEnabled(false);w->setMousePassThroughEnabled(true);
 pos(menu,w,x,y);size(menu,w,width,42);w->setZOrderingEnabled(false);
 w->setProperty("HorzTextFormatting",horizontal);w->setProperty("VertFormatting",vertical);std::string text=STRINGS::GetValueAsString(value);if(hotkey)text=std::string("F")+text;w->setText(utf8(text.c_str()));w->setClippedByParent(false);menu->m_Children.add(w);
}

typedef char check_ActorFields_level[__builtin_offsetof(ActorFields,level)==256?1:-1];
typedef char check_ActorFields_manager[__builtin_offsetof(ActorFields,manager)==456?1:-1];
typedef char check_ActorFields_points[__builtin_offsetof(ActorFields,points)==1120?1:-1];
typedef char check_ActorFields_primary[__builtin_offsetof(ActorFields,primary)==2384?1:-1];
typedef char check_ActorFields_secondary[__builtin_offsetof(ActorFields,secondary)==2480?1:-1];
typedef char check_SkillFields_activation[__builtin_offsetof(SkillFields,activation)==96?1:-1];
typedef char check_SkillFields_levelCount[__builtin_offsetof(SkillFields,levelCount)==168?1:-1];
typedef char check_SkillFields_baseLevel[__builtin_offsetof(SkillFields,baseLevel)==220?1:-1];
typedef char check_SkillFields_effectiveLevel[__builtin_offsetof(SkillFields,effectiveLevel)==224?1:-1];
typedef char check_SkillFields_column[__builtin_offsetof(SkillFields,column)==268?1:-1];
typedef char check_SkillFields_row[__builtin_offsetof(SkillFields,row)==272?1:-1];
typedef char check_SkillFields_pane[__builtin_offsetof(SkillFields,pane)==276?1:-1];
typedef char check_SkillFields_guid[__builtin_offsetof(SkillFields,guid)==336?1:-1];
typedef char check_SkillFields_maxLevel[__builtin_offsetof(SkillFields,maxLevel)==344?1:-1];
typedef char check_ManagerFields_skills[__builtin_offsetof(ManagerFields,skills)==96?1:-1];
typedef char check_CSkillMenu_m_pBackground[__builtin_offsetof(CSkillMenu,m_pBackground)==24?1:-1];
typedef char check_CSkillMenu_m_pOwner[__builtin_offsetof(CSkillMenu,m_pOwner)==48?1:-1];
typedef char check_CSkillMenu_m_bOpenPartial[__builtin_offsetof(CSkillMenu,m_bOpenPartial)==56?1:-1];
typedef char check_CSkillMenu_m_pGameUI[__builtin_offsetof(CSkillMenu,m_pGameUI)==80?1:-1];
typedef char check_CSkillMenu_m_pResourceManager[__builtin_offsetof(CSkillMenu,m_pResourceManager)==104?1:-1];
typedef char check_CSkillMenu_m_pImages[__builtin_offsetof(CSkillMenu,m_pImages)==120?1:-1];
typedef char check_CSkillMenu_m_Panes[__builtin_offsetof(CSkillMenu,m_Panes)==144?1:-1];
typedef char check_CSkillMenu_m_TabLabels[__builtin_offsetof(CSkillMenu,m_TabLabels)==200?1:-1];
typedef char check_CSkillMenu_m_iPane[__builtin_offsetof(CSkillMenu,m_iPane)==224?1:-1];
typedef char check_CSkillMenu_m_SkillGuids[__builtin_offsetof(CSkillMenu,m_SkillGuids)==240?1:-1];
typedef char check_CSkillMenu_m_SpellGuids[__builtin_offsetof(CSkillMenu,m_SpellGuids)==1040?1:-1];
typedef char check_CSkillMenu_m_Children[__builtin_offsetof(CSkillMenu,m_Children)==1848?1:-1];
}

__attribute__((flatten))
void CSkillMenu::updateLayout() {
 using namespace skill_layout;
 if(!m_pOwner)return;
 for(unsigned i=0;i<m_Children.size();++i) {
  CEGUI::Window* window=m_Children[i];
  if(window->getParent())window->getParent()->removeChildWindow(window);
  CEGUI::WindowManager::getSingleton().destroyWindow(window);
 }
 m_Children.clear();
 if(m_bOpenPartial && actor(m_pOwner).points>0)m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(7));
 std::wstring tab;
 for(int i=0;i<3;++i) {
  tab=CStringTranslate::getSinglton()->getTranslateString(m_pOwner->getSkillTabName(i+1));
  m_TabLabels[i]->setText(utf8(STRINGS::StringConvertToUTF8(tab).c_str()));
 }
 CSkillManager* manager=actor(m_pOwner).manager;
 if(manager) {
  int count=manager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));
  for(int i=0;i<count;++i) {
   TArrayList<CSkill*>& skills=reinterpret_cast<ManagerFields*>(manager)->skills;
   CSkill* skill=i<static_cast<int>(skills.size())?skills[i]:0;
   if(skill->getSkillIcon().empty() || m_iPane!=fields(skill).pane || fields(skill).column==-1)continue;
   CEGUI::Window* housing=create("GuiLook/StaticImage");m_Panes[m_iPane]->addChildWindow(housing);housing->moveToFront();housing->setRiseOnClickEnabled(false);housing->setWantsMultiClickEvents(false);housing->setMousePassThroughEnabled(true);
   int column=fields(skill).column;
   skill->calculateEffectiveSkillLevel();int effective=static_cast<int>(fields(skill).effectiveLevel);
   float calculatedRow=::floorf(static_cast<float>(skill->getLevelRequiredForInvestment())/5.0f);
   int row=fields(skill).row;if(row==-1)row=static_cast<int>(calculatedRow);
   float x=static_cast<float>(column)*86.0f+0.0f,y=0.0f+static_cast<float>(row)*75.0f;
   pos(this,housing,x,y);size(this,housing,55,55.4f);housing->setZOrderingEnabled(false);
   image(this,housing,fields(skill).activation==4?"PassiveSkillHousing":"ActiveSkillHousing");m_Children.add(housing);
   CEGUI::Window* icon=create("GuiLook/StaticImage");m_Panes[m_iPane]->addChildWindow(icon);icon->moveToFront();icon->setRiseOnClickEnabled(false);icon->setWantsMultiClickEvents(false);
   float ix=x+6.5f,iy=y+6.5f;pos(this,icon,ix,iy);size(this,icon,42,42);icon->setZOrderingEnabled(false);
   if(effective!=0) {skillImage(this,icon,skill->getSkillIcon());tint(icon,1);}
   else {
    unsigned required=skill->getLevelRequiredForInvestment();unsigned level=actor(m_pOwner).level;bool blocked=false;
    if(skill->getSkillRequiredForInvestment()!=EMPTY_WSTRING) {
     CSkill* dependency=actor(m_pOwner).manager->getSkill(skill->getSkillRequiredForInvestment());
     if(dependency && fields(dependency).baseLevel==0)blocked=true;
    }
    if(blocked || required>level) {tint(icon,1);skillImage(this,icon,skill->getSkillIconInactive());}
    else {tint(icon,.3f);skillImage(this,icon,skill->getSkillIcon());}
   }
   icon->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CSkillMenu::handle_SetSkill,this));
   m_SkillGuids[i]=fields(skill).guid;icon->setUserData(&m_SkillGuids[i]);
   icon->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CSkillMenu::handle_MouseOver,this));
   icon->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CSkillMenu::handle_MouseOut,this));m_Children.add(icon);
   for(int hotkey=0;hotkey<12;++hotkey) {
    if(actor(m_pOwner).primary[hotkey]==fields(skill).guid || actor(m_pOwner).secondary[hotkey]==fields(skill).guid) {
     overlay(this,ix,iy,42,"LeftAligned","TopAligned",hotkey+1,true);break;
    }
   }
   if(effective>0)overlay(this,ix,iy,37.8f,"RightAligned","BottomAligned",effective,false);
   bool allowed=skill->getLevelRequiredForInvestment()<=actor(m_pOwner).level;
   if(skill->getSkillRequiredForInvestment()!=EMPTY_WSTRING) {
    CSkill* dependency=actor(m_pOwner).manager->getSkill(skill->getSkillRequiredForInvestment());
    if(dependency && fields(dependency).baseLevel==0)allowed=false;
   }
   if(actor(m_pOwner).points<=0 || !allowed)continue;
   skill->calculateEffectiveSkillLevel();unsigned max=fields(skill).maxLevel;
   if(!max) {max=fields(skill).levelCount;if(!max)max=1;}
   if(fields(skill).effectiveLevel>=max)continue;
   x=(x+27.5f)-10.5f;y=y+55.4f;
   CEGUI::Window* plus=create("GuiLook/ImageButton");m_Panes[m_iPane]->addChildWindow(plus);plus->setRiseOnClickEnabled(false);
   size(this,plus,21,17.25f);pos(this,plus,x,y);plus->moveToFront();
   image(this,plus,"SkillPointPlus","NormalImage");image(this,plus,"SkillPointPlusLit","HoverImage");image(this,plus,"SkillPointPlusLit","PushedImage");
   plus->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CSkillMenu::handle_SpendSkill,this));plus->setWantsMultiClickEvents(false);
   static std::wstring g_Purchase;if(g_Purchase.empty())g_Purchase=CStringTranslate::getSinglton()->getTranslateString(L"Purchase");
   const std::wstring& name=skill->getDisplayName();std::wstring tooltip=g_Purchase+L" "+name;
   plus->setTooltipText(utf8(STRINGS::StringConvertToUTF8(tooltip).c_str()));m_SkillGuids[i]=fields(skill).guid;plus->setUserData(&m_SkillGuids[i]);m_Children.add(plus);
  }
 }
 for(unsigned slot=0;slot<4;++slot) {
  CSkill* spell=m_pOwner->getKnownSpell(slot);if(!spell || spell->getSkillIcon().empty())continue;
  CEGUI::Window* housing=create("GuiLook/StaticImage");m_Panes[3]->addChildWindow(housing);housing->moveToFront();housing->setRiseOnClickEnabled(false);housing->setWantsMultiClickEvents(false);housing->setMousePassThroughEnabled(true);
  int row=static_cast<int>(::floorf(static_cast<float>(spell->getLevelRequiredForInvestment())/5.0f));
  float x=static_cast<float>(slot)*64.0f+0.0f,y=0.0f+static_cast<float>(row)*85.0f;
  pos(this,housing,x,y);size(this,housing,54,54);housing->setZOrderingEnabled(false);image(this,housing,"ActiveSkillHousing");m_Children.add(housing);
  CEGUI::Window* icon=create("GuiLook/StaticImage");m_Panes[3]->addChildWindow(icon);icon->moveToFront();icon->setRiseOnClickEnabled(false);icon->setWantsMultiClickEvents(false);
  pos(this,icon,x+3,y+3);size(this,icon,48,48);icon->setZOrderingEnabled(false);skillImage(this,icon,spell->getSkillIconInactive());
  icon->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CSkillMenu::handle_SetSkill,this));m_SpellGuids[slot]=fields(spell).guid;icon->setUserData(&m_SpellGuids[slot]);
  icon->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CSkillMenu::handle_MouseOver,this));icon->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CSkillMenu::handle_MouseOut,this));m_Children.add(icon);
 }
 m_pBackground->moveToBack();
}

#include <OgreMesh.h>
#include <OgreEntity.h>
#include "DynamicPropertyFile.h"
#include "Settings.h"
#include "GameVariables.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include "SkillTooltip.h"

namespace skill_create_detail {
struct UIRoot { char prefix[0x488]; CEGUI::Window* root; };
}

inline __attribute__((always_inline))
CSkillTooltip::CSkillTooltip(CGameUI* ui, CEGUI::Window* root)
    : m_pGameUI(ui), m_sText(EMPTY_WSTRING), m_iIndex(-1), m_pRoot(root) {}

__attribute__((flatten)) void CSkillMenu::createMenus()
{
    float width = static_cast<float>(m_pProperties->GetInt(KSETTINGS_RES_WIDTH));
    float height = static_cast<float>(m_pProperties->GetInt(KSETTINGS_RES_HEIGHT));
    m_pModel = m_pResourceManager->createGenericModel(m_pSceneManager,
        L"media/ui/models/skill/skill.mesh", L"", false, false, false);
    m_pModel->generateExtremes(5, true);
    Ogre::AxisAlignedBox bounds(Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
                                Ogre::Vector3(100000.0f, 100000.0f, 100000.0f));
    m_pModel->getEntity()->getMesh()->_setBounds(bounds, true);
    float scale = width - height / 0.75f;
    scale /= m_pProperties->GetFloat(KSETTINGS_YRATIO);
    m_pModel->setPosition(0.5f * scale, 0.0f, 0.0f);
    m_pModel->setVisible(false);
    m_pImages = CEGUI::ImagesetManager::getSingleton().getImageset(
        reinterpret_cast<const unsigned char*>("ui2"));
    m_pBackground = CEGUI::WindowManager::getSingleton().createWindow(
        reinterpret_cast<const unsigned char*>("DefaultWindow"),
        reinterpret_cast<const unsigned char*>("SkillSheet"), "");
    m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
    m_pBackground->setProperty("RiseOnClick", "False");
    m_pBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
    m_pBackground->setMousePassThroughEnabled(true);
    m_pBackground->setZOrderingEnabled(false);
    {
        CEGUI::Event::Connection connection = m_pBackground->subscribeEvent(
            CEGUI::Window::EventMouseMove,
            CEGUI::SubscriberSlot(&CSkillMenu::handle_MouseThrough, this));
        (void)connection;
    }

    CFileInfo fileInfo;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/skillmenu.layout", fileInfo, false, true, false);
    CEGUI::Window* layoutRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout(
        CEGUI::String(fileInfo.m_sResourceName), true);
    m_pGameUI->convertToScreenScale(layoutRoot, false);
    m_pGameUI->mapToFunctions(layoutRoot);
    mapEventHandlers(layoutRoot);

    CEGUI::Window* blocker = layoutRoot->recursiveChildSearch("Blocker");
    blocker->getParent()->removeChildWindow(blocker);
    m_pBackground->addChildWindow(blocker);
    blocker->setProperty("RiseOnClick", "False");
    blocker->moveToBack();
    blocker->setZOrderingEnabled(false);

    CEGUI::Window* close = layoutRoot->recursiveChildSearch("Close");
    close->setRiseOnClickEnabled(false);
    close->moveToFront();
    {
        CEGUI::Event::Connection connection = close->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CSkillMenu::handle_CloseButton, this));
        (void)connection;
    }
    m_Panes[0] = layoutRoot->recursiveChildSearch("SkillFrameA");
    m_Panes[1] = layoutRoot->recursiveChildSearch("SkillFrameB");
    m_Panes[1]->setVisible(false);
    m_Panes[2] = layoutRoot->recursiveChildSearch("SkillFrameC");
    m_Panes[2]->setVisible(false);
    m_TabLabels[0] = layoutRoot->recursiveChildSearch("TabTextA");
    m_TabLabels[1] = layoutRoot->recursiveChildSearch("TabTextB");
    m_TabLabels[2] = layoutRoot->recursiveChildSearch("TabTextC");
    m_Tabs[0] = static_cast<CEGUI::RadioButton*>(layoutRoot->recursiveChildSearch("TabA"));
    m_Tabs[0]->setSelected(true);
    m_Tabs[1] = static_cast<CEGUI::RadioButton*>(layoutRoot->recursiveChildSearch("TabB"));
    m_Tabs[1]->setSelected(false);
    m_Tabs[2] = static_cast<CEGUI::RadioButton*>(layoutRoot->recursiveChildSearch("TabC"));
    m_Tabs[2]->setSelected(false);
    m_Tabs[0]->setZOrderingEnabled(false);
    m_Tabs[1]->setZOrderingEnabled(false);
    m_Tabs[2]->setZOrderingEnabled(false);
    m_Panes[3] = layoutRoot->recursiveChildSearch("SpellFrame");
    m_pSkillPoints = layoutRoot->recursiveChildSearch("Skill Points");

    m_pBottomFrame = layoutRoot->recursiveChildSearch("BottomFrame");
    m_pBottomFrame->getParent()->removeChildWindow(m_pBottomFrame);
    m_pBackground->addChildWindow(m_pBottomFrame);
    m_pBottomFrame->setProperty("RiseOnClick", "False");
    m_pBottomFrame->moveToFront();
    m_pBottomFrame->setZOrderingEnabled(false);
    m_pTopFrame = layoutRoot->recursiveChildSearch("TopFrame");
    m_pTopFrame->getParent()->removeChildWindow(m_pTopFrame);
    m_pBackground->addChildWindow(m_pTopFrame);
    m_pTopFrame->setProperty("RiseOnClick", "False");
    m_pTopFrame->moveToFront();
    m_pTopFrame->setZOrderingEnabled(false);

    m_pTooltip = new CSkillTooltip(m_pGameUI,
        reinterpret_cast<skill_create_detail::UIRoot*>(m_pGameUI)->root);
    m_pTooltip->load(m_pGameUI, L"media/UI/skilltooltip.layout");
}

#include <OgreUTFString.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>

namespace skill_update_detail {
struct PointerFields { char prefix[0x12d0]; long x,y; };
}

__attribute__((flatten)) void CSkillMenu::update(float elapsed)
{
    int width=m_pProperties->GetInt(KSETTINGS_RES_WIDTH);
    int height=m_pProperties->GetInt(KSETTINGS_RES_HEIGHT);
    int points=skill_layout::actor(m_pOwner).points;
    if(m_iCachedSkillPoints!=points) {
        m_iCachedSkillPoints=points;
        updateLayout();
    }
    static std::wstring g_PointsRemaining;
    if(g_PointsRemaining.empty())
        g_PointsRemaining=CStringTranslate::getSinglton()->getTranslateString(L"Points Remaining");
    CEGUI::String text(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(
        std::wstring((Ogre::UTFString(g_PointsRemaining)+Ogre::UTFString(": ")+
        Ogre::UTFString(STRINGS::GetValueAsString(skill_layout::actor(m_pOwner).points))).asWStr())).c_str()));
    if(m_pSkillPoints->getText()!=text)
        m_pSkillPoints->setText(reinterpret_cast<const unsigned char*>(text.c_str()));
    if(!m_bOpenPartial && m_bClosed) {
        if(m_pTooltip && m_pTooltip->m_pWindow->getParent())
            m_pTooltip->m_pWindow->getParent()->removeChildWindow(m_pTooltip->m_pWindow);
        return;
    }
    m_pModel->updateAnimation(elapsed,false);
    m_pModel->getEntity()->_updateAnimation();
    Ogre::Bone* top=m_pModel->m_pSkeleton->getBone("tag_topskill");
    Ogre::Vector3 position=m_pModel->getPosition(false);
    const Ogre::Vector3& tag=top->_getDerivedPosition();
    float sumY=tag.y+position.y;
    float scaledX=m_pGameUI->scaledY(tag.x+position.x);
    float halfWidth=float(width)*0.5f;
    float panelY=-(m_pGameUI->scaledY(sumY)+float(height)*-0.5f);
    m_fTopX=scaledX+halfWidth;
    m_pTopFrame->setPosition(CEGUI::UVector2(CEGUI::UDim(0,m_fTopX),CEGUI::UDim(0,panelY)));
    Ogre::Bone* bottom=m_pModel->m_pSkeleton->getBone("tag_bottomskill");
    position=m_pModel->getPosition(false);
    float bottomX=bottom->_getDerivedPosition().x+position.x;
    float scaledBottom=m_pGameUI->scaledY(bottomX);
    float bottomScreen=halfWidth+scaledBottom;
    m_pBottomFrame->setPosition(CEGUI::UVector2(CEGUI::UDim(0,bottomScreen),CEGUI::UDim(0,panelY)));
    float edge=m_pGameUI->scaledY(50.0f)+bottomScreen;
    m_fScreenEdge=edge<float(width)?edge:float(width);
    if(!m_bOpenPartial && !m_bClosed) {
        if(!m_pModel->animationPlaying("CLOSE") && !m_pModel->animationQueued("CLOSE")) {
            m_pModel->setVisible(false);
            m_bClosed=true;
            m_pRoot->removeChildWindow(m_pBackground);
        }
    }
    if(m_bSkillHovered && m_pOwner) {
        CSkillManager* manager=skill_layout::actor(m_pOwner).manager;
        long long guid=m_HoveredSkillGuid;
        if(!manager)return;
        CSkill* skill=manager->getSkillByGuid(guid);
        if(!skill)return;
        skill_update_detail::PointerFields& mouse=*reinterpret_cast<skill_update_detail::PointerFields*>(m_pGameUI);
        m_pTooltip->showTooltip(m_pOwner,skill,float(mouse.x),float(mouse.y));
    } else {
        CEGUI::Window* window=m_pTooltip->m_pWindow;
        if(window->getParent())window->getParent()->removeChildWindow(window);
    }
}
