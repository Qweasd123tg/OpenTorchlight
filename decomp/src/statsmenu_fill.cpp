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

#include "StatsMenuFill.h"
#include "StringUtilities.h"
#include <CEGUI.h>
#include <algorithm>

namespace stats_fill_visual_detail {
// Named views of the original player's base-stat and allocated-experience fields.
struct PlayerFields {
    char prefix[0x428];
    int stat1,stat0,stat3,stat2;
    char gap438[0x448-0x438];
    int experience;
    char gap44c[0x870-0x44c];
    int allocated0,allocated1,allocated3,allocated2,spent;
};
static const PlayerFields& fields(const CPlayer* player) {
    return *reinterpret_cast<const PlayerFields*>(player);
}
static int stat(const CPlayer* player,unsigned index) {
    const PlayerFields& p=fields(player);
    switch(index){case 1:return p.stat1;case 2:return p.stat2;case 3:return p.stat3;default:return p.stat0;}
}
static int allocated(const CPlayer* player,unsigned index) {
    const PlayerFields& p=fields(player);
    switch(index){case 1:return p.allocated1;case 2:return p.allocated2;case 3:return p.allocated3;default:return p.allocated0;}
}
}
void CStatsMenuFill::updateVisuals()
{
    for(unsigned i=0;i<4;++i) {
        CEGUI::Window* bar=m_Bars[i];
        CEGUI::Window* amount=m_AmountTexts[i];
        CEGUI::Window* statText=m_PercentTexts[i];
        if(!m_pPlayer) {
            bar->setVisible(false);
            statText->setText(CEGUI::String((const unsigned char*)""));
            continue;
        }
        std::wstring value=STRINGS::GetValueAsWString(stats_fill_visual_detail::stat(m_pPlayer,i))+L"";
        statText->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(value).c_str()));
        float total=getStatBarTotalAmount(static_cast<ESTATSMENU_STATS>(i));
        float allocated=(float)(m_pPlayer?stats_fill_visual_detail::allocated(m_pPlayer,i):0);
        float ratio=allocated/total;
        bool visible=ratio>0.0f;
        bar->setVisible(visible);
        std::wstring text=L""+STRINGS::GetValueAsWString(allocated)+L"/"+STRINGS::GetValueAsWString(total);
        amount->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(text).c_str()));
        if(visible) {
            float height=m_pGameUI->scaledY(8.0f);
            float width=m_pGameUI->scaledY(std::max(1.0f,ratio*180.0f));
            bar->setSize(CEGUI::UVector2(CEGUI::UDim(0,width),CEGUI::UDim(0,height)));
        }
    }
    int remaining=0;
    if(m_pPlayer) {
        const stats_fill_visual_detail::PlayerFields& p=stats_fill_visual_detail::fields(m_pPlayer);
        remaining=static_cast<int>(static_cast<unsigned>(p.experience)-static_cast<unsigned>(p.spent));
    }
    std::wstring text=L"Total Experience to spend: "+STRINGS::GetValueAsWString(remaining);
    m_pExperienceText->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(text).c_str()));
    calculateMouseOver();
}

void CStatsMenuFill::calculateMouseOver()
{
    for(unsigned i=0;i<4;++i) {
        CEGUI::Window* window=m_StatSlots[i];
        std::wstring text=L"";
        int next=1;
        if(m_pPlayer)next=stats_fill_visual_detail::stat(m_pPlayer,i)+1;
        std::wstring value=STRINGS::GetValueAsWString(next);
        switch(i) {
        case 1:text=L"Increase Ranged Damage\n\nNext Point Gives:\n"+value+L"% ranged damage increase";break;
        case 2:text=L"Increase Magic and Skill Damage\n\nNext Point Gives:\n"+value+L"% increase magic damage";break;
        case 3:text=L"Increase Defense Against Damage\n\nNext Point Gives:\n"+value+L"% defense increase";break;
        default:text=L"Increase Melee Damage\n\nNext point gives:\n"+value+L"% melee damage increase";break;
        }
        window->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(text).c_str())));
    }
}

#include "Graph.h"
namespace stats_fill_input_detail {
struct Fields {char prefix[0x168];float heldElapsed;char gap16c[4];CGraph* statCost;char gap178[0x190-0x178];bool flag190;};
typedef char check_elapsed[__builtin_offsetof(Fields,heldElapsed)==0x168?1:-1];
typedef char check_graph[__builtin_offsetof(Fields,statCost)==0x170?1:-1];
typedef char check_flag[__builtin_offsetof(Fields,flag190)==0x190?1:-1];
inline Fields& fields(CStatsMenuFill* p){return *reinterpret_cast<Fields*>(p);}
}
bool CStatsMenuFill::handle_onMouseUp(const CEGUI::EventArgs&)
{
 stats_fill_input_detail::fields(this).flag190=false;
 stats_fill_input_detail::fields(this).heldElapsed=0.0f;
 for(unsigned i=0;i<4;++i){m_AddHeld[i]=false;m_RemoveHeld[i]=false;}
 return true;
}
bool CStatsMenuFill::handle_AddToStat(const CEGUI::EventArgs& args)
{
 unsigned int index=m_AddButtons.find(static_cast<const CEGUI::WindowEventArgs&>(args).window);
 if(index!=-1)m_AddHeld[index]=true;
 return true;
}
bool CStatsMenuFill::handle_RemoveFromStat(const CEGUI::EventArgs& args)
{
 unsigned int index=m_RemoveButtons.find(static_cast<const CEGUI::WindowEventArgs&>(args).window);
 if(index!=-1)m_RemoveHeld[index]=true;
 return true;
}
float CStatsMenuFill::getStatBarTotalAmount(ESTATSMENU_STATS which)
{
 int amount=0;
 if(m_pPlayer){
  const stats_fill_visual_detail::PlayerFields& p=stats_fill_visual_detail::fields(m_pPlayer);
  switch(which){case 0:amount=p.stat0;break;case 1:amount=p.stat1;break;case 2:amount=p.stat2;break;case 3:amount=p.stat3;break;default:break;}
 }
 return stats_fill_input_detail::fields(this).statCost->getValue(static_cast<float>(amount)+1.0f,0);
}


int CStatsMenuFill::getStatInvestment(ESTATSMENU_STATS which)
{
 if(m_pPlayer){
  const stats_fill_visual_detail::PlayerFields& p=stats_fill_visual_detail::fields(m_pPlayer);
  switch(which){case 0:return p.stat0;case 1:return p.stat1;case 2:return p.stat2;case 3:return p.stat3;}
 }
 return 0;
}
int CStatsMenuFill::getStatBarCurrentAmount(ESTATSMENU_STATS which)
{
 if(m_pPlayer){
  const stats_fill_visual_detail::PlayerFields& p=stats_fill_visual_detail::fields(m_pPlayer);
  switch(which){case 0:return p.allocated0;case 1:return p.allocated1;case 2:return p.allocated2;case 3:return p.allocated3;}
 }
 return 0;
}
float CStatsMenuFill::getExperienceToSpend()
{
 const stats_fill_visual_detail::PlayerFields& p=stats_fill_visual_detail::fields(m_pPlayer);
 return static_cast<float>(static_cast<int>(static_cast<unsigned>(p.experience)-static_cast<unsigned>(p.spent)));
}
void CStatsMenuFill::addExperienceSpent(int amount)
{
 if(m_pPlayer){
  stats_fill_visual_detail::PlayerFields& p=*reinterpret_cast<stats_fill_visual_detail::PlayerFields*>(m_pPlayer);
  unsigned spent=static_cast<unsigned>(p.spent);
  if(amount<0){unsigned remove=0u-static_cast<unsigned>(amount);if(remove>spent)p.spent=0;else p.spent=static_cast<int>(spent-remove);}
  else p.spent=static_cast<int>(spent+static_cast<unsigned>(amount));
 }
}
void CStatsMenuFill::addExperienceToStat(ESTATSMENU_STATS which,int amount)
{
 if(m_pPlayer){
  int value=static_cast<int>(static_cast<unsigned>(getStatBarCurrentAmount(which))+static_cast<unsigned>(amount));
  stats_fill_visual_detail::PlayerFields& p=*reinterpret_cast<stats_fill_visual_detail::PlayerFields*>(m_pPlayer);
  switch(which){case 0:p.allocated0=value;break;case 1:p.allocated1=value;break;case 2:p.allocated2=value;break;case 3:p.allocated3=value;break;}
  addExperienceSpent(amount);
 }
}
namespace stats_fill_open_detail {
struct SoundField {char prefix[0x180];CSoundBank* bank;};
typedef char sound_offset[__builtin_offsetof(SoundField,bank)==0x180?1:-1];
inline CSoundBank* sound(CStatsMenuFill* menu){return reinterpret_cast<SoundField*>(menu)->bank;}
}
void CStatsMenuFill::setOpen(bool open)
{
 updateVisuals();
 if(!m_bUnknown30){if(open)stats_fill_open_detail::sound(this)->playSample(22,0,0.0f,0.0f,false);}
 else {if(!open)stats_fill_open_detail::sound(this)->playSample(66,0,0.0f,0.0f,false);}
 CDropdownMenu::setOpen(open);
 m_pGameUI->setInteractiveMenuVisible(open);
}


#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"

CStatsMenuFill::CStatsMenuFill(CGameUI& ui, CSettings& settings,
 Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
 : CDropdownMenu(ui,settings,scene,parent,resources,0),
   m_AddButtons(4),m_RemoveButtons(4),m_Bars(4),m_AmountTexts(4),
   m_StatSlots(4),m_PercentTexts(10),m_pExperienceText(0),m_pPlayer(0),
   m_HeldTime(0),m_pPointGraph(0),m_BarCooldown(0),m_pFillSoundBank(0),
   m_FillSoundInterval(0),m_FillSoundCountdown(0),m_Filling(false)
{
 CSoundBankDataInformation* info=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
 m_pFillSoundBank=new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
 CSoundData* sound=info->getSoundDataObject(L"INVENTORYOPEN");
 if(sound)m_pFillSoundBank->addSample(22,sound->m_iGuid);
 sound=info->getSoundDataObject(L"INVENTORYCLOSE");
 if(sound)m_pFillSoundBank->addSample(66,sound->m_iGuid);
 sound=info->getSoundDataObject(L"POINTASSIGN");
 if(sound)m_pFillSoundBank->addSample(27,sound->m_iGuid);
 sound=info->getSoundDataObject(L"STATFILL");
 if(sound){m_FillSoundInterval=0.5f;m_pFillSoundBank->addSample(30,sound->m_iGuid);}
 setTitle(L"Stats");
 createMenus();
 m_pPointGraph=resources->getGraph(L"POINTGRAPH");
}

CStatsMenuFill::~CStatsMenuFill()
{
 if(m_pFillSoundBank){delete m_pFillSoundBank;m_pFillSoundBank=0;}
}
