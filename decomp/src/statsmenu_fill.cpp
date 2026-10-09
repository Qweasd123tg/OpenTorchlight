#include "StatsMenuFill.h"
#include "StringUtilities.h"
#include <CEGUI.h>
#include <OgreLogManager.h>

static std::wstring gSTATSMENU_STATS[]={L"MELEE",L"RANGED",L"MAGIC",L"DEFENSE"};
namespace stats_fill_detail {
inline __attribute__((always_inline)) CEGUI::Window* create(const char* type) {
 return CEGUI::WindowManager::getSingleton().createWindow(CEGUI::String(reinterpret_cast<const unsigned char*>(type)),STRINGS::uniqueName(std::string("gui_")).c_str(),"");
}
inline __attribute__((always_inline)) void attach(CStatsMenuFill* menu,CEGUI::Window* window) {
 static_cast<CEGUI::Window*>(menu->m_pUnknown20)->addChildWindow(window);
}
inline __attribute__((always_inline)) void rect(CStatsMenuFill* menu,CEGUI::Window* window,float width,float height,float x,float y) {
 float h=menu->m_pGameUI->scaledY(height);
 float w=menu->m_pGameUI->scaledY(width);
 window->setSize(CEGUI::UVector2(CEGUI::UDim(0,w),CEGUI::UDim(0,h)));
 float sy=menu->m_pGameUI->scaledY(y);
 float sx=menu->m_pGameUI->scaledY(x);
 window->setPosition(CEGUI::UVector2(CEGUI::UDim(0,sx),CEGUI::UDim(0,sy)));
}
inline __attribute__((always_inline)) void image(CEGUI::Window* window,CEGUI::Imageset* set,const char* name,const char* property="Image") {
 window->setProperty(property,CEGUI::PropertyHelper::imageToString(&set->getImage(CEGUI::String(reinterpret_cast<const unsigned char*>(name)))));
}
inline __attribute__((always_inline)) void passive(CEGUI::Window* window) {
 window->setRiseOnClickEnabled(false);window->setWantsMultiClickEvents(false);window->setMousePassThroughEnabled(true);
}
inline __attribute__((always_inline)) void textStyle(CEGUI::Window* window,const char* alignment) {
 window->setProperty("TextColour",CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,1)));
 window->setProperty("HorzTextFormatting",alignment);
}
}
__attribute__((flatten))
void CStatsMenuFill::createMenus() {
 using namespace stats_fill_detail;
 CEGUI::Imageset* gui=CEGUI::ImagesetManager::getSingleton().getImageset(CEGUI::String(reinterpret_cast<const unsigned char*>("GuiLook")));
 CEGUI::Imageset* stats=CEGUI::ImagesetManager::getSingleton().getImageset(CEGUI::String(reinterpret_cast<const unsigned char*>("StatsMenu_UI")));
 if(!stats) {Ogre::LogManager::getSingleton().logMessage("Unable to find imageset.",Ogre::LML_CRITICAL,false);return;}
 static_cast<CEGUI::Window*>(m_pUnknown20)->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CStatsMenuFill::handle_onMouseUp,this));
 // The original stores the address of this shared loop counter in both button
 // families. Preserve that aliasing, including its lifetime limitation.
 unsigned row;
 for(row=0;row<4;++row) {
  m_AddHeld[row]=false;m_RemoveHeld[row]=false;
  CEGUI::Window* left=create("GuiLook/StaticImage");attach(this,left);passive(left);
  rect(this,left,32,32,70,45+50*float(row+1));left->setZOrderingEnabled(false);image(left,stats,"leftBrace");
  CEGUI::Window* center=create("GuiLook/StaticImage");attach(this,center);passive(center);
  rect(this,center,158,32,102,45+50*float(row+1));center->setZOrderingEnabled(false);image(center,stats,"centerBrace");
  CEGUI::Window* right=create("GuiLook/StaticImage");attach(this,right);passive(right);
  rect(this,right,32,32,260,45+50*float(row+1));right->setZOrderingEnabled(false);image(right,stats,"rightBrace");
  CEGUI::Window* plus=create("GuiLook/ImageButton");attach(this,plus);plus->setRiseOnClickEnabled(false);
  rect(this,plus,24,24,280,50+50*float(row+1));plus->moveToFront();
  image(plus,gui,"StatButton","NormalImage");image(plus,gui,"StatButtonOver","HoverImage");image(plus,gui,"StatButtonOver","PushedImage");
  plus->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CStatsMenuFill::handle_AddToStat,this));
  plus->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CStatsMenuFill::handle_onMouseUp,this));
  plus->setWantsMultiClickEvents(false);
  plus->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>("Increase the amount invested")));
  plus->setUserData(&row);m_AddButtons.add(plus);
  CEGUI::Window* minus=create("GuiLook/ImageButton");attach(this,minus);minus->setRiseOnClickEnabled(false);
  rect(this,minus,32,32,35,50+50*float(row+1));minus->moveToFront();
  image(minus,stats,"minusButton","NormalImage");image(minus,stats,"minusButtonHighlight","HoverImage");image(minus,stats,"minusButtonHighlight","PushedImage");
  minus->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CStatsMenuFill::handle_RemoveFromStat,this));
  minus->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CStatsMenuFill::handle_onMouseUp,this));
  minus->setWantsMultiClickEvents(false);
  minus->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>("Reduce the amount invested")));
  minus->setUserData(&row);m_RemoveButtons.add(minus);
  CEGUI::Window* slot=create("GuiLook/StaticImage");attach(this,slot);slot->setRiseOnClickEnabled(false);slot->setWantsMultiClickEvents(false);
  rect(this,slot,75,32,310,45+50*float(row+1));slot->setZOrderingEnabled(false);
  slot->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>("Increase the amount invested")));
  image(slot,gui,"SkillSlot");m_StatSlots.add(slot);
  CEGUI::Window* percent=create("GuiLook/StaticText");attach(this,percent);percent->setMousePassThroughEnabled(true);
  rect(this,percent,75,32,325,45+50*float(row+1));percent->setText(CEGUI::String(reinterpret_cast<const unsigned char*>("100%")));textStyle(percent,"CenterAligned");m_PercentTexts.add(percent);
  CEGUI::Window* label=create("GuiLook/StaticText");attach(this,label);
  rect(this,label,90,15,65,32+50*float(row+1));label->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(gSTATSMENU_STATS[row]).c_str())));textStyle(label,"LeftAligned");
  CEGUI::Window* bar=create("GuiLook/StaticImage");attach(this,bar);passive(bar);
  rect(this,bar,180,8,88,58+50*float(row+1));bar->setZOrderingEnabled(false);image(bar,gui,"TargetHealthBar");m_Bars.add(bar);
  CEGUI::Window* amount=create("GuiLook/StaticText");attach(this,amount);amount->setMousePassThroughEnabled(true);
  amount->setFont(CEGUI::String(reinterpret_cast<const unsigned char*>("FrizQuadrataSmall")));
  rect(this,amount,75,15,150,55+50*float(row+1));amount->setText(CEGUI::String(reinterpret_cast<const unsigned char*>("0/12322")));textStyle(amount,"CenterAligned");m_AmountTexts.add(amount);
 }
 m_pExperienceText=create("GuiLook/StaticText");attach(this,m_pExperienceText);
 rect(this,m_pExperienceText,320,15,65,310);m_pExperienceText->setText(CEGUI::String(reinterpret_cast<const unsigned char*>("Total Experience to spend:0")));textStyle(m_pExperienceText,"CenterAligned");
}
