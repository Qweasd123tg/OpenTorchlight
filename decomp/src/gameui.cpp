#include "GameUICallBoundaries.h"
#include "GameUIOgreUTFString.h"
extern unsigned int KSETTINGS_XRATIO;
#include <CEGUIWindow.h>
#include "Console.h"
#include "DropdownMenu.h"
#include "DynamicPropertyFile.h"
#include "GameUI.h"
#include "GameVariables.h"
#include "InteractiveMenu.h"
#include "Level.h"
#include "MenuManager.h"
#include "Settings.h"
#include "SkillFoldout.h"
#include "SubMenu.h"
#include <algorithm>
#include "GameUI.h"
#include "GameUIUpdate.h"
// Keep recovered private phases inside the original single public entry.
__attribute__((flatten))
void CGameUI::updateIngameUI(float elapsed,CGameClient* client,Ogre::RenderWindow* renderWindow)
{
    static std::string g_HP=gameui_detail::translatedUTF8(L"HP");
    static std::string g_Mana=gameui_detail::translatedUTF8(L"Mana");
    static std::string g_XP=gameui_detail::translatedUTF8(L"XP");
    static std::string g_Fleeing=gameui_detail::translatedUTF8(L"Fleeing");
    gameui_detail::Labels labels={g_HP.c_str(),g_Mana.c_str(),g_XP.c_str(),g_Fleeing.c_str()};
    gameui_detail::Frame frame(this,client,renderWindow,elapsed,labels);
    if(frame.entry())return;
    if(!frame.hasActor()){frame.noCharacterFrame();return;}
    if(frame.beginServiceMenus()){
        static std::wstring g_Retire;
        if(g_Retire.empty())g_Retire=gameui_detail::service::translate(gameui_detail::service::translator(),L"Retire");
        static std::wstring g_CannotRetire;
        if(g_CannotRetire.empty())g_CannotRetire=gameui_detail::service::translate(gameui_detail::service::translator(),L"You cannot retire until you reach level ");
        frame.finishRetirement(g_Retire,g_CannotRetire);
    }
    frame.restOfActiveFrame();
}

#include "GameUIEquipmentTooltip.h"
#include "EmptyStrings.h"
extern short tooltipKeyState(unsigned) __asm__("_Z16GetAsyncKeyStatej");
#define TOOLTIP_TRANSLATION(NAME,TEXT) static std::wstring NAME;if(NAME.empty())NAME=CStringTranslate::getSinglton()->getTranslateString(TEXT)
__attribute__((flatten))
void CGameUI::showEquipmentTooltip(CCharacter* owner,CEquipment* item,CEquipmentTooltip* tip,CEquipmentTooltip* first,CEquipmentTooltip* second){
 using namespace equipment_tooltip;
 typedef char player_level_offset[__builtin_offsetof(CCharacter,m_iUnitLevel)==0x100?1:-1];
 typedef char inventory_offset[__builtin_offsetof(CCharacter,m_pInventory)==0x490?1:-1];
 typedef char gold_offset[__builtin_offsetof(CCharacter,m_iGold)==0x444?1:-1];
 typedef char identified_offset[__builtin_offsetof(CEquipment,m_bUnknown348)==0x348?1:-1];
 typedef char armor_offset[__builtin_offsetof(CEquipment,m_iUnknown338)==0x338?1:-1];
 TOOLTIP_TRANSLATION(g_DamagePerSecond,L"damage per second");
 TOOLTIP_TRANSLATION(g_Armor,L"armor");
 TOOLTIP_TRANSLATION(g_Equipped,L"equipped");
 TOOLTIP_TRANSLATION(g_LeftHand,L"left hand");
 TOOLTIP_TRANSLATION(g_RightHand,L"right hand");
 TOOLTIP_TRANSLATION(g_OneHanded,L"1-handed");
 TOOLTIP_TRANSLATION(g_TwoHanded,L"2-handed");
 TOOLTIP_TRANSLATION(g_RequiresLevel,L"Requires Level");
 TOOLTIP_TRANSLATION(g_RequiresStr,L"requires Strength");
 TOOLTIP_TRANSLATION(g_RequiresDex,L"requires Dexterity");
 TOOLTIP_TRANSLATION(g_RequiresMag,L"requires Magic");
 TOOLTIP_TRANSLATION(g_RequiresDef,L"requires Defense");
 TOOLTIP_TRANSLATION(g_Price,L"price");
 TOOLTIP_TRANSLATION(g_SellPrice,L"sell price");
 TOOLTIP_TRANSLATION(g_CantUseUnidentified,L"Unidentified items cannot be used-");
 TOOLTIP_TRANSLATION(g_UseIdentify,L"use an Identify Scroll to reveal enchantments");

 if(!tip->m_pRoot->getParent()){tip->m_pParent->addChildWindow(tip->m_pRoot);tip->m_pRoot->moveToFront();}
 std::wstring value;
 if(tip->m_iCachedItemGuid!=item->getGuid()){
  tip->m_iCachedItemGuid=item->getGuid();
  bool gamble=owner!=m_pCharacter&&owner->ISA(UNITTYPES::GAMBLER);
  float minimumWidth=gameuiBoundaryScaledY(this,160.0f);float minimumHeight=gameuiBoundaryScaledY(this,100.0f);
  value=gamble?L"???":item->getFullItemName(false);
  std::string bytes=STRINGS::StringConvertToUTF8(value);
  Size titleSize=measure(tip->m_pItemName->getFont(true),bytes,1000.0f,2);size(tip->m_pItemName,titleSize);text(tip->m_pItemName,bytes);
  float width=maxSecond(titleSize.width,minimumWidth);
  std::wstring hand=EMPTY_WSTRING;
  if((item->ISA(UNITTYPES::RING)||item->ISA(UNITTYPES::WEAPON)||item->ISA(UNITTYPES::SHIELD))&&first&&owner){int slot=owner->m_pInventory->findEquipmentSlot(item);hand=(slot==9||slot==1)?g_LeftHand:g_RightHand;}
  std::wstring type=item->getEquipmentType(!gamble);
  if(first)value=hand!=EMPTY_WSTRING?L"("+g_Equipped+L"-"+hand+L") "+type:L"("+g_Equipped+L") "+type;else value=type;
  bytes=STRINGS::StringConvertToUTF8(value);Size typeSize=measure(tip->m_pItemType->getFont(true),bytes,1000.0f,2);size(tip->m_pItemType,typeSize);text(tip->m_pItemType,bytes);width=maxSecond(typeSize.width,width);
  int colourKind=0;
  if(item->getIsQuestUnit())colourKind=1;
  else if(!gamble&&(item->isMagical()||item->ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE))){
   if(item->getSet()!=EMPTY_WSTRING)colourKind=2;else if(item->ISA(UNITTYPES::UNIQUE))colourKind=3;else if(item->ISA(UNITTYPES::MAGIC))colourKind=4;else colourKind=5;
  }
  for(int i=0;i<2;++i){CEGUI::Window*& window=i==0?tip->m_pItemType:tip->m_pItemName;
   if(!colourKind)whiteOrRed(window,false);
   else{CGameGlobals* globals=CGameGlobals::getSingleton();const std::wstring& colour=colourKind==1?globals->getQuestColor(true):colourKind==2?globals->getSetColor(true):colourKind==3?globals->getUniqueColor(true):colourKind==4?globals->getRareColor(true):globals->getRandomEnchantColor(true);window->setProperty("TextColour",CEGUI::String(STRINGS::StringConvertToUTF8(colour)));}
  }
  bool unidentified=item->isMagical()&&!item->m_bUnknown348;
  tip->m_pBigDPS->setVisible(true);CEGUI::Font* firstFont=tip->m_pBigDPS->getFont(true);
  float baseY=tip->m_pBigDPS->getPosition().d_y.asAbsolute(0.0f);float y;
  bool weapon=false,armor=false;
  if(!gamble){weapon=item->ISA(UNITTYPES::WEAPON);if(!weapon)armor=item->ISA(UNITTYPES::ARMOR);}
  if(weapon||armor){
   if(weapon)tip->m_pDPS->setVisible(true);
   bytes=unidentified?"??":STRINGS::StringConvertToUTF8(weapon?STRINGS::GetValueAsWString(static_cast<unsigned>(item->DPS())):STRINGS::GetValueAsWString(item->m_iUnknown338));
   if(armor)tip->m_pDPS->setVisible(true);
   text(tip->m_pBigDPS,bytes);CEGUI::Rect area(0,0,1000.0f,1000.0f);
   float bigWidth=firstFont->getFormattedTextExtent(utf8(bytes),area,static_cast<CEGUI::TextFormatting>(2),1.0f)+4.0f;
   CEGUI::Font* nextFont=tip->m_pBigDPS->getFont(true);float lineHeight=nextFont->getFontHeight()+2.0f;
   int lines=static_cast<int>(nextFont->getFormattedLineCount(utf8(bytes),area,static_cast<CEGUI::TextFormatting>(2),1.0f));y=(float(lines)*lineHeight+4.0f)+baseY;
   CEGUI::UDim oldY=tip->m_pDPS->getPosition().d_y;tip->m_pDPS->setPosition(CEGUI::UVector2(CEGUI::UDim(0,bigWidth),oldY));caption(tip->m_pDPS,weapon?g_DamagePerSecond:g_Armor);
  }else{y=tip->m_pBigDPS->getPosition().d_y.asAbsolute(0.0f);tip->m_pBigDPS->setVisible(false);tip->m_pDPS->setVisible(false);}
  value=gamble||unidentified?L"":item->getEquipmentStats();
  if(item->ISA(UNITTYPES::WEAPON)){bool two=item->ISA(static_cast<UNITTYPES::EUNITTYPES>(10));value=L"("+(two?g_TwoHanded:g_OneHanded)+L")\n"+value;}
  bytes=STRINGS::StringConvertToUTF8(value);Size stats=measure(tip->m_pStats->getFont(true),bytes,1000.0f,2);size(tip->m_pStats,stats);moveY(tip->m_pStats,y);text(tip->m_pStats,bytes);width=maxSecond(stats.width+40.0f,width);
  value=gamble?L"????\n":item->getEquipmentEffects();y=y+(4.0f+stats.height);
  if(!value.empty()){float effectY=y+4.0f;tip->m_pEffects->setVisible(true);bytes=STRINGS::StringConvertToUTF8(value);Size effects=measure(tip->m_pEffects->getFont(true),bytes,1000.0f,2,0.0f);size(tip->m_pEffects,effects);text(tip->m_pEffects,bytes);moveY(tip->m_pEffects,effectY);width=maxSecond(effects.width+40.0f,width);y=effectY+(4.0f+effects.height);}else tip->m_pEffects->setVisible(false);
  y+=6.0f;std::wstring unknown=L"???";
  typedef int(CEquipment::*Requirement)(CCharacter*);
  const Requirement requirements[]={&CEquipment::getLevelRequirement,&CEquipment::getStrengthRequirement,&CEquipment::getDexterityRequirement,&CEquipment::getMagicRequirement,&CEquipment::getDefenseRequirement};
  const std::wstring* captions[]={&g_RequiresLevel,&g_RequiresStr,&g_RequiresDex,&g_RequiresMag,&g_RequiresDef};
  CEGUI::Window** requirementWindows[]={&tip->m_pLevelRequirement,&tip->m_pStrengthRequirement,&tip->m_pDexterityRequirement,&tip->m_pMagicRequirement,&tip->m_pDefenseRequirement};
  for(int i=0;i<5;++i){CEGUI::Window*& window=*requirementWindows[i];
   if((gamble||!unidentified)&&(item->*requirements[i])(m_pCharacter)>0){window->setVisible(true);
    std::wstring number=gamble?unknown:STRINGS::GetValueAsWString((item->*requirements[i])(m_pCharacter));value=*captions[i]+L" "+number;
    bool insufficient=false;if(!gamble){int needed=(item->*requirements[i])(m_pCharacter);int have=i==0?int(m_pCharacter->m_iUnitLevel):i==1?m_pCharacter->strength():i==2?m_pCharacter->dexterity():i==3?m_pCharacter->magic():m_pCharacter->defense();insufficient=needed>have;}
    whiteOrRed(window,insufficient);bytes=STRINGS::StringConvertToUTF8(value);addRow(window,bytes,width,y);
   }else window->setVisible(false);
  }
  bool flavor=false;if(gamble||!unidentified)flavor=item->getFlavorDescription()!=EMPTY_WSTRING;
  if(flavor){tip->m_pDescription->setVisible(true);value=item->getFlavorDescription();value=STRINGS::replaceWString(value,L"\\n",L"\n");description(tip,value,false,width,y);}
  else if(unidentified){tip->m_pDescription->setVisible(true);value=g_CantUseUnidentified+g_UseIdentify;description(tip,value,true,width,y);}
  else tip->m_pDescription->setVisible(false);
  int priceKind=0;
  if(!first&&!second){if(owner!=m_pCharacter&&!item->ISA(UNITTYPES::QUESTITEM)&&owner->ISA(UNITTYPES::MERCHANT))priceKind=1;else if(reinterpret_cast<UIFields*>(this)->merchant->open()&&!item->ISA(UNITTYPES::QUESTITEM))priceKind=2;}
  if(priceKind){tip->m_pPrice->setVisible(true);int amount=priceKind==1?item->buyPrice():item->sellPrice();std::wstring number=STRINGS::GetValueAsWString(amount);value=(priceKind==1?g_Price:g_SellPrice)+L" :"+number;bytes=STRINGS::StringConvertToUTF8(value);CEGUI::Font* font=tip->m_pPrice->getFont(true);
   if(priceKind==1){if(amount>m_pCharacter->getGold())tip->m_pPrice->setProperty("TextColour",CEGUI::PropertyHelper::colourToString(CEGUI::colour(1.0f,.5f,.5f,1.0f)));else tip->m_pPrice->setProperty("TextColour","FFffeb9a");}
   Size p=measure(font,bytes,1000.0f,2);if(priceKind==2)tip->m_pPrice->setProperty("TextColour","FFffeb9a");size(tip->m_pPrice,p);text(tip->m_pPrice,bytes);moveY(tip->m_pPrice,y);width=maxSecond(p.width+40.0f,width);y=(p.height+4.0f)+y;
  }else tip->m_pPrice->setVisible(false);
  float height=maxSecond(minimumHeight,y);float borderWidth=gameuiBoundaryScaledY(this,52.0f)-52.0f;float borderHeight=gameuiBoundaryScaledY(this,52.0f)-52.0f;
  borderWidth=borderWidth>0.0f?borderWidth:0.0f;borderHeight=maxSecond(borderHeight,0.0f);
  tip->m_pRoot->setSize(CEGUI::UVector2(CEGUI::UDim(0,borderWidth+width),CEGUI::UDim(0,borderHeight+height)));
 }
 place(this,tip,first,second);
 if(tooltipKeyState(0x11)<0&&tip->m_pRoot->getParent())tip->m_pParent->removeChildWindow(tip->m_pRoot);
}
#undef TOOLTIP_TRANSLATION

#include "GameUISkillTooltip.h"
#define SKILL_TRANSLATION(NAME,TEXT) static std::wstring NAME;if(NAME.empty())NAME=CStringTranslate::getSinglton()->getTranslateString(TEXT)
__attribute__((flatten))
void CSkillTooltip::showTooltip(CBaseUnit* owner,CSkill* skill,float mouseX,float mouseY){
 using namespace skill_tooltip;
 typedef char tooltip_size[(sizeof(CSkillTooltip)==0x178)?1:-1];
 typedef char skill_size[(sizeof(CSkill)==0x160)?1:-1];
 typedef char tooltip_m_pGameUI[(__builtin_offsetof(CSkillTooltip,m_pGameUI)==0x10)?1:-1];
 typedef char tooltip_m_sText[(__builtin_offsetof(CSkillTooltip,m_sText)==0x18)?1:-1];
 typedef char tooltip_m_iIndex[(__builtin_offsetof(CSkillTooltip,m_iIndex)==0x20)?1:-1];
 typedef char tooltip_m_pRoot[(__builtin_offsetof(CSkillTooltip,m_pRoot)==0x28)?1:-1];
 typedef char tooltip_m_pWindow[(__builtin_offsetof(CSkillTooltip,m_pWindow)==0x30)?1:-1];
 typedef char tooltip_m_pSkillName[(__builtin_offsetof(CSkillTooltip,m_pSkillName)==0x38)?1:-1];
 typedef char tooltip_m_pSkillRank[(__builtin_offsetof(CSkillTooltip,m_pSkillRank)==0x40)?1:-1];
 typedef char tooltip_m_pDescription[(__builtin_offsetof(CSkillTooltip,m_pDescription)==0x48)?1:-1];
 typedef char tooltip_m_pSkillType[(__builtin_offsetof(CSkillTooltip,m_pSkillType)==0x50)?1:-1];
 typedef char tooltip_m_pManaCost[(__builtin_offsetof(CSkillTooltip,m_pManaCost)==0x58)?1:-1];
 typedef char tooltip_m_pCooldown[(__builtin_offsetof(CSkillTooltip,m_pCooldown)==0x60)?1:-1];
 typedef char tooltip_m_pEffects[(__builtin_offsetof(CSkillTooltip,m_pEffects)==0x68)?1:-1];
 typedef char tooltip_m_pNextDescription[(__builtin_offsetof(CSkillTooltip,m_pNextDescription)==0x70)?1:-1];
 typedef char tooltip_m_pNextEffects[(__builtin_offsetof(CSkillTooltip,m_pNextEffects)==0x78)?1:-1];
 typedef char tooltip_m_pNextLevel[(__builtin_offsetof(CSkillTooltip,m_pNextLevel)==0x80)?1:-1];
 typedef char tooltip_m_pNextManaCost[(__builtin_offsetof(CSkillTooltip,m_pNextManaCost)==0x88)?1:-1];
 typedef char tooltip_m_pNextCooldown[(__builtin_offsetof(CSkillTooltip,m_pNextCooldown)==0x90)?1:-1];
 typedef char tooltip_m_pLevelRequirement[(__builtin_offsetof(CSkillTooltip,m_pLevelRequirement)==0x98)?1:-1];
 typedef char tooltip_m_pSkillRequirement[(__builtin_offsetof(CSkillTooltip,m_pSkillRequirement)==0xa0)?1:-1];
 typedef char tooltip_m_pSkillIcon[(__builtin_offsetof(CSkillTooltip,m_pSkillIcon)==0xa8)?1:-1];
 typedef char tooltip_m_pUsage[(__builtin_offsetof(CSkillTooltip,m_pUsage)==0xb0)?1:-1];
 typedef char tooltip_m_pStatIcons[(__builtin_offsetof(CSkillTooltip,m_pStatIcons)==0xb8)?1:-1];
 typedef char tooltip_m_pStatLabels[(__builtin_offsetof(CSkillTooltip,m_pStatLabels)==0xd8)?1:-1];
 typedef char tooltip_m_StatOffsets[(__builtin_offsetof(CSkillTooltip,m_StatOffsets)==0xf8)?1:-1];
 typedef char tooltip_m_pNextStatIcons[(__builtin_offsetof(CSkillTooltip,m_pNextStatIcons)==0x118)?1:-1];
 typedef char tooltip_m_pNextStatLabels[(__builtin_offsetof(CSkillTooltip,m_pNextStatLabels)==0x138)?1:-1];
 typedef char tooltip_m_NextStatOffsets[(__builtin_offsetof(CSkillTooltip,m_NextStatOffsets)==0x158)?1:-1];
 typedef char skill_m_eActivationType[(__builtin_offsetof(CSkill,m_eActivationType)==0x60)?1:-1];
 typedef char skill_m_bExecutedByProperty[(__builtin_offsetof(CSkill,m_bExecutedByProperty)==0x6b)?1:-1];
 typedef char skill_m_bEnabled[(__builtin_offsetof(CSkill,m_bEnabled)==0x6d)?1:-1];
 typedef char skill_m_iSkillLevelCount[(__builtin_offsetof(CSkill,m_iSkillLevelCount)==0xa8)?1:-1];
 typedef char skill_m_iEffectiveSkillLevel[(__builtin_offsetof(CSkill,m_iEffectiveSkillLevel)==0xe0)?1:-1];
 typedef char skill_m_iDisplayedMaxRank[(__builtin_offsetof(CSkill,m_iDisplayedMaxRank)==0x158)?1:-1];
 if(!m_pWindow->getParent()){m_pRoot->addChildWindow(m_pWindow);m_pWindow->moveToFront();}
 SKILL_TRANSLATION(g_AlwaysEnabled,L"Always Enabled");SKILL_TRANSLATION(g_ManaCost,L"Mana Cost");
 SKILL_TRANSLATION(g_Cooldown,L"Cooldown");SKILL_TRANSLATION(g_PerSecond,L"per second");
 SKILL_TRANSLATION(g_Seconds,L"seconds");SKILL_TRANSLATION(g_NextLevel,L"Next Level");
 SKILL_TRANSLATION(g_Requires,L"Requires");SKILL_TRANSLATION(g_RequiresLevel,L"Requires Level");SKILL_TRANSLATION(g_Rank,L"Rank");
 bool rebuild=m_sText!=skill->getName();
 if(!rebuild){int cachedLevel=m_iIndex;skill->calculateEffectiveSkillLevel();rebuild=static_cast<unsigned>(cachedLevel)!=skill->m_iEffectiveSkillLevel;}
 if(rebuild){
m_sText=skill->getName();
skill->calculateEffectiveSkillLevel();
m_iIndex=skill->m_iEffectiveSkillLevel;
float minimumWidth=gameuiBoundaryScaledY(m_pGameUI,160.0f);
float minimumHeight=gameuiBoundaryScaledY(m_pGameUI,100.0f);
float bonuses[6]={0,0,0,0,0,0};
skill->calculateEffectiveSkillLevel();
unsigned bonusLevel=skill->m_iEffectiveSkillLevel&&!skill->m_bExecutedByProperty&&skill->m_bEnabled?~0u:1u;
skill->fillOutStatBonuses(bonuses,true,bonusLevel);
std::string iconName=STRINGS::StringConvertToNarrow(skill->getSkillIcon().c_str());
const CEGUI::Image* icon=m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(iconName.c_str()));
m_pSkillIcon->setProperty("Image",CEGUI::PropertyHelper::imageToString(icon));
std::wstring value=skill->getDisplayName();
std::string bytes=STRINGS::StringConvertToUTF8(value);
Size title=measureExtentFirst(m_pSkillName->getFont(true),bytes,1000.0f,2,15.0f);
setSize(m_pSkillName,title);setText(m_pSkillName,bytes);
float width=maxSecond(title.width+40.0f,minimumWidth);
unsigned maxRank=skill->m_iDisplayedMaxRank;
if(!maxRank){maxRank=skill->m_iSkillLevelCount;if(!maxRank)maxRank=1;}
std::wstring maximumText=STRINGS::GetValueAsWString(maxRank);
skill->calculateEffectiveSkillLevel();
std::wstring currentText=STRINGS::GetValueAsWString(skill->m_iEffectiveSkillLevel);
value=g_Rank+L" "+currentText+L"/"+maximumText;
bytes=STRINGS::StringConvertToUTF8(value);
Size rank=measureExtentFirst(m_pSkillRank->getFont(true),bytes,1000.0f,2,4.0f);
setSize(m_pSkillRank,rank);setText(m_pSkillRank,bytes);
width=maxSecond(rank.width+40.0f,width);
setTextColour(m_pSkillRank,0.75f,0.75f,1.0f,1.0f);
bytes=STRINGS::StringConvertToUTF8(skill->getSkillTypeDisplayName());
m_pSkillType->setVisible(true);
CEGUI::Font* font=m_pSkillType->getFont(true);
float lineHeight=font->getFontHeight()+2.0f;
float y=m_pSkillType->getPosition().d_y.asAbsolute(0.0f);
Size type=measureLinesFirst(font,bytes,420.0f,0,lineHeight);
setSize(m_pSkillType,type);setText(m_pSkillType,bytes);
width=maxSecond(type.width+40.0f,width);
y=(type.height+4.0f)+y;
skill->calculateEffectiveSkillLevel();
bytes=STRINGS::StringConvertToUTF8(skill->getSkillLevelDescription(owner,skill->m_iEffectiveSkillLevel));
m_pDescription->setVisible(true);
font=m_pDescription->getFont(true);lineHeight=font->getFontHeight()+2.0f;
float descriptionBound=gameuiBoundaryScaledY(m_pGameUI,300.0f);
Size description=measureLinesFirst(font,bytes,descriptionBound,4,lineHeight);
setSize(m_pDescription,description);setText(m_pDescription,bytes);setY(m_pDescription,y);
width=maxSecond(description.width+40.0f,width);
if(skill->m_eActivationType==SKILL_ACTIVATION_PASSIVE){
 bytes=STRINGS::StringConvertToUTF8(g_AlwaysEnabled);
}else{
 skill->calculateEffectiveSkillLevel();
 int costOT=skill->getSkillLevelManaCostOT(owner,skill->m_iEffectiveSkillLevel);
 if(costOT){
  bytes=STRINGS::StringConvertToUTF8(g_ManaCost+L":"+STRINGS::GetValueAsWString(costOT)+L" "+g_PerSecond);
 }else{
  skill->calculateEffectiveSkillLevel();
  int cost=skill->getSkillLevelManaCost(owner,skill->m_iEffectiveSkillLevel);
  bytes=STRINGS::StringConvertToUTF8(g_ManaCost+L":"+STRINGS::GetValueAsWString(cost));
 }
}
m_pManaCost->setVisible(true);
font=m_pManaCost->getFont(true);lineHeight=font->getFontHeight()+2.0f;
Size mana=measureLinesFirst(font,bytes,300.0f,4,lineHeight);
setSize(m_pManaCost,mana);setText(m_pManaCost,bytes);
y=y+(description.height+4.0f);setY(m_pManaCost,y);
width=maxSecond(mana.width+40.0f,width);y=y+(mana.height+4.0f);
setTextColour(m_pManaCost,0.75f,0.75f,1.0f,1.0f);
skill->calculateEffectiveSkillLevel();
if(skill->getSkillLevelCooldown(owner,skill->m_iEffectiveSkillLevel)>0){
 skill->calculateEffectiveSkillLevel();
 int cooldown=skill->getSkillLevelCooldown(owner,skill->m_iEffectiveSkillLevel);
 bytes=STRINGS::StringConvertToUTF8(g_Cooldown+L":"+STRINGS::GetValueAsWString(cooldown)+L" "+g_Seconds);
 m_pCooldown->setVisible(true);
 font=m_pCooldown->getFont(true);lineHeight=font->getFontHeight()+2.0f;
 Size cooldownSize=measureLinesFirst(font,bytes,300.0f,4,lineHeight);
 setSize(m_pCooldown,cooldownSize);setText(m_pCooldown,bytes);setY(m_pCooldown,y);
 width=maxSecond(cooldownSize.width+40.0f,width);y=(cooldownSize.height+4.0f)+y;
 setTextColour(m_pCooldown,0.75f,0.75f,1.0f,1.0f);
}else m_pCooldown->setVisible(false);

// Packed visible stat rows consider only the first four of the six bonuses.
float statHeight=layoutStatRows(m_pGameUI,m_pStatIcons,m_pStatLabels,m_StatOffsets,bonuses,y,6.0f);
skill->calculateEffectiveSkillLevel();
value=skill->getSkillLevelStats(owner,skill->m_iEffectiveSkillLevel);
y=y+statHeight;
if(!value.empty()){
 y=4.0f+y;m_pEffects->setVisible(true);
 bytes=STRINGS::StringConvertToUTF8(value);
 Size effects=measureExtentFirst(m_pEffects->getFont(true),bytes,1000.0f,4,4.0f);
 setSize(m_pEffects,effects);setText(m_pEffects,bytes);setY(m_pEffects,y);
 width=maxSecond(effects.width+40.0f,width);y=y+(effects.height+4.0f);
}else m_pEffects->setVisible(false);
y=18.0f+y;
skill->calculateEffectiveSkillLevel();
unsigned levelCount=skill->m_iSkillLevelCount?skill->m_iSkillLevelCount:1;
bool showNext=false;
if(skill->m_iEffectiveSkillLevel<levelCount){
 skill->calculateEffectiveSkillLevel();showNext=skill->m_iEffectiveSkillLevel!=0;
}
if(showNext){

 for(int i=0;i<6;++i)bonuses[i]=0.0f;
 skill->calculateEffectiveSkillLevel();
 skill->fillOutStatBonuses(bonuses,true,nextIndex(skill->m_iEffectiveSkillLevel));
 font=m_pNextLevel->getFont(true);m_pNextLevel->setVisible(true);
 skill->calculateEffectiveSkillLevel();
 bytes=STRINGS::StringConvertToUTF8(g_NextLevel+L" : "+STRINGS::GetValueAsWString(static_cast<int>(nextIndex(skill->m_iEffectiveSkillLevel))));
 Size heading=measureExtentFirst(font,bytes,300.0f,2,4.0f);
 setSize(m_pNextLevel,heading);setY(m_pNextLevel,y);setText(m_pNextLevel,bytes);
 width=maxSecond(heading.width+40.0f,width);y=18.0f+(y+heading.height);
 skill->calculateEffectiveSkillLevel();
 std::wstring oldDescription=skill->getSkillLevelDescription(owner,skill->m_iEffectiveSkillLevel);
 skill->calculateEffectiveSkillLevel();
 std::wstring nextDescription=skill->getSkillLevelDescription(owner,nextIndex(skill->m_iEffectiveSkillLevel));
 if(nextDescription==oldDescription)m_pNextDescription->setVisible(false);
 else{
  skill->calculateEffectiveSkillLevel();
  bytes=STRINGS::StringConvertToUTF8(skill->getSkillLevelDescription(owner,nextIndex(skill->m_iEffectiveSkillLevel)));
  m_pNextDescription->setVisible(true);font=m_pNextDescription->getFont(true);lineHeight=font->getFontHeight()+2.0f;
  float bound=gameuiBoundaryScaledY(m_pGameUI,300.0f);
  Size nextDescriptionSize=measureLinesFirst(font,bytes,bound,4,lineHeight);
  setSize(m_pNextDescription,nextDescriptionSize);setText(m_pNextDescription,bytes);setY(m_pNextDescription,y);
  width=maxSecond(nextDescriptionSize.width+40.0f,width);y=(nextDescriptionSize.height+4.0f)+y;
 }
 if(skill->m_eActivationType==SKILL_ACTIVATION_PASSIVE)bytes=STRINGS::StringConvertToUTF8(g_AlwaysEnabled);
 else{
  skill->calculateEffectiveSkillLevel();
  int nextCostOT=skill->getSkillLevelManaCostOT(owner,nextIndex(skill->m_iEffectiveSkillLevel));
  if(nextCostOT)bytes=STRINGS::StringConvertToUTF8(g_ManaCost+L":"+STRINGS::GetValueAsWString(nextCostOT)+L" "+g_PerSecond);
  else{skill->calculateEffectiveSkillLevel();int cost=skill->getSkillLevelManaCost(owner,nextIndex(skill->m_iEffectiveSkillLevel));bytes=STRINGS::StringConvertToUTF8(g_ManaCost+L":"+STRINGS::GetValueAsWString(cost));}
 }
 m_pNextManaCost->setVisible(true);font=m_pNextManaCost->getFont(true);lineHeight=font->getFontHeight()+2.0f;
 Size nextMana=measureLinesFirst(font,bytes,300.0f,4,lineHeight);
 setSize(m_pNextManaCost,nextMana);setText(m_pNextManaCost,bytes);setY(m_pNextManaCost,y);
 width=maxSecond(nextMana.width+40.0f,width);y=(nextMana.height+4.0f)+y;
 setTextColour(m_pNextManaCost,.75f,.75f,1.0f,1.0f);
 skill->calculateEffectiveSkillLevel();
 if(skill->getSkillLevelCooldown(owner,nextIndex(skill->m_iEffectiveSkillLevel))>0){
  skill->calculateEffectiveSkillLevel();int cooldown=skill->getSkillLevelCooldown(owner,nextIndex(skill->m_iEffectiveSkillLevel));
  bytes=STRINGS::StringConvertToUTF8(g_Cooldown+L":"+STRINGS::GetValueAsWString(cooldown)+L" "+g_Seconds);
  m_pNextCooldown->setVisible(true);font=m_pNextCooldown->getFont(true);lineHeight=font->getFontHeight()+2.0f;
  Size nextCooldown=measureLinesFirst(font,bytes,300.0f,4,lineHeight);
  setSize(m_pNextCooldown,nextCooldown);setText(m_pNextCooldown,bytes);setY(m_pNextCooldown,y);
  width=maxSecond(nextCooldown.width+40.0f,width);y=(nextCooldown.height+4.0f)+y;
  setTextColour(m_pNextCooldown,.75f,.75f,1.0f,1.0f);
 }else m_pNextCooldown->setVisible(false);
 float nextStatHeight=layoutStatRows(m_pGameUI,m_pNextStatIcons,m_pNextStatLabels,m_NextStatOffsets,bonuses,y,4.0f);
 skill->calculateEffectiveSkillLevel();value=skill->getSkillLevelStats(owner,nextIndex(skill->m_iEffectiveSkillLevel));
 y=nextStatHeight+y;
 if(!value.empty()){
  y=4.0f+y;m_pNextEffects->setVisible(true);bytes=STRINGS::StringConvertToUTF8(value);
  Size nextEffects=measureExtentFirst(m_pNextEffects->getFont(true),bytes,1000.0f,4,4.0f);
  setSize(m_pNextEffects,nextEffects);setText(m_pNextEffects,bytes);setY(m_pNextEffects,y);
  width=maxSecond(nextEffects.width+40.0f,width);y=y+(nextEffects.height+4.0f);
 }else m_pNextEffects->setVisible(false);
 y=y+6.0f;

}else{
 m_pNextLevel->setVisible(false);m_pNextDescription->setVisible(false);
 m_pNextEffects->setVisible(false);m_pNextManaCost->setVisible(false);
 m_pNextCooldown->setVisible(false);
 for(int i=0;i<4;++i){m_pNextStatIcons[i]->setVisible(false);m_pNextStatLabels[i]->setVisible(false);}
}
// Usage, requirements, overall size and common placement follow.

if(skill->getSkillUsageDescription()!=EMPTY_WSTRING){
 m_pUsage->setVisible(true);value=skill->getSkillUsageDescription();bytes=STRINGS::StringConvertToUTF8(value);
 Size usage=measureExtentFirst(m_pUsage->getFont(true),bytes,width*1.5f,4,4.0f);
 setSize(m_pUsage,usage);setText(m_pUsage,bytes);setY(m_pUsage,y);
 width=maxSecond(usage.width+40.0f,width);y=(usage.height+4.0f)+y;
}else m_pUsage->setVisible(false);
bytes=STRINGS::StringConvertToUTF8(g_RequiresLevel+L" "+STRINGS::GetValueAsWString(skill->getLevelRequiredForInvestment()));
Size requirement=measureExtentFirst(m_pLevelRequirement->getFont(true),bytes,1000.0f,2,4.0f);
setSize(m_pLevelRequirement,requirement);setText(m_pLevelRequirement,bytes);setY(m_pLevelRequirement,y);
width=maxSecond(requirement.width+40.0f,width);y=(requirement.height+4.0f)+y;
CSkill* required=0;
if(skill->getSkillRequiredForInvestment()!=EMPTY_WSTRING){const std::wstring& requiredName=skill->getSkillRequiredForInvestment();required=owner->getSkillManager()->getSkill(requiredName);}
if(required){
 const std::wstring& display=required->getDisplayName();bytes=STRINGS::StringConvertToUTF8(g_Requires+L" "+display);
 Size skillRequirement=measureExtentFirst(m_pSkillRequirement->getFont(true),bytes,1000.0f,2,4.0f);
 setSize(m_pSkillRequirement,skillRequirement);setText(m_pSkillRequirement,bytes);setY(m_pSkillRequirement,y);
 width=maxSecond(skillRequirement.width+40.0f,width);y=(skillRequirement.height+4.0f)+y;
 m_pSkillRequirement->setVisible(true);
}else m_pSkillRequirement->setVisible(false);
float height=maxSecond(minimumHeight,y);
float extraWidth=gameuiBoundaryScaledY(g_pGameUI,52.0f)-52.0f;
float extraHeight=gameuiBoundaryScaledY(g_pGameUI,52.0f)-52.0f;
Size total={width+(0.0f<extraWidth?extraWidth:0.0f),(0.0f<extraHeight?extraHeight:0.0f)+height};
setSize(m_pWindow,total);

 }
 skill_tooltip::place(this,mouseX,mouseY);
}
#undef SKILL_TRANSLATION

#include "MenuItemClickState.h"
namespace menu_item_click_detail {
inline bool is(CBaseUnit* unit, int tag) {
    return unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(tag));
}
inline void sound(UIState& s, int sample) {
    s.soundBank->playSample(sample,s.player->getSceneNode(),0.0f,0.0f,false);
}
inline void error(UIState& s, int voice) {
    sound(s,24);
    if(actor(s.player).soundBank)
        actor(s.player).soundBank->queueGlobalSample(voice,0.0f,0.1f);
}
inline void recordPurchase(UIState& s, CCharacter* seller, CEquipment* item) {
    if(is(seller,UNITTYPES::GAMBLER)) {
        s.player->incrementJournalStatistic(static_cast<EJournalStatistic>(15),1);
        if(is(item,UNITTYPES::UNIQUE)) {
            CAchievement* achievement=CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(5));
            if(achievement)achievement->forceComplete();
        }
    }
}
inline void chargeDraggedPurchase(UIState& s) {
    int price=s.draggedItem.getObject()->buyPrice();
    if(is(s.dragOwner.getObject(),UNITTYPES::GAMBLER)) {
        s.player->incrementJournalStatistic(static_cast<EJournalStatistic>(15),1);
        if(is(s.draggedItem.getObject(),UNITTYPES::UNIQUE)) {
            CAchievement* achievement=CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(5));
            if(achievement)achievement->forceComplete();
        }
    }
    s.player->giveGold(-price);
    sound(s,23);
}
inline void removeDragIcon(UIState& s) {
    if(s.dragWindow==s.draggedItem.getObject()->m_pIconWindow->getParent())
        s.dragWindow->removeChildWindow(s.draggedItem.getObject()->m_pIconWindow);
}
inline void positionDragIcon(CGameUI* ui, UIState& s) {
    s.dragWindow->addChildWindow(s.draggedItem.getObject()->m_pIconWindow);
    float y=static_cast<float>(s.mouseY);
    y-=gameuiBoundaryScaledY(ui,48.0f);
    float x=static_cast<float>(s.mouseX);
    x-=gameuiBoundaryScaledY(ui,32.0f);
    s.draggedItem.getObject()->m_pIconWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
    float height=gameuiBoundaryScaledY(ui,96.0f);
    float width=gameuiBoundaryScaledY(ui,64.0f);
    s.draggedItem.getObject()->m_pIconWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0,width),CEGUI::UDim(0,height)));
}
inline void putBackOrDrop(UIState& s,CCharacter* owner,CInventory* inventory,CEquipment* item) {
    if(!inventory->pickupEquipment(item,true)) {
        Ogre::Vector3 position=owner->getPosition(true);
        s.level->addItem(item,position,true);
        item->drop();
    }
}
}

// Full entry candidate; requires original-versus-candidate branch tests before publication.
__attribute__((flatten))
bool CGameUI::menuItemClick(CCharacter* owner,CSubMenu* menu,int clickedSlot,bool result) {
    using namespace menu_item_click_detail;
    UIState& s=state(this);
    CInventory* inventory=NULL;
    if(owner) {
        if(is(owner,UNITTYPES::SHAREDSTASH))inventory=CSharedStash::getSingleton()->m_pInventory;
        else inventory=actor(owner).inventory;
    }
    bool quickTrade=false,quickTransfer=false;
    if(!s.draggedItem.getObject() && GetAsyncKeyState(16)<0 && s.merchantMenu->open())quickTrade=true;
    if(!s.draggedItem.getObject() && GetAsyncKeyState(16)<0 &&
       (s.petMenu->open() || s.stashMenu->open() || s.enchantMenu->open() || s.combineMenu->open()))quickTransfer=true;
    if(!quickTrade && !s.draggedItem.getObject() && GetAsyncKeyState(16)<0) {
        if(!s.merchantMenu->open() && !s.combineMenu->open() && !s.stashMenu->open() && !s.enchantMenu->open()) {
            if(s.petMenu->open() && !s.inventoryMenu->open()) {
                gameuiBoundaryCloseRight(this);s.inventoryMenu->setOpen(true);quickTransfer=true;
            } else if(!s.petMenu->open() && s.inventoryMenu->open() && s.player->getFollowerCount()) {
                if(actor(s.player->getFollower(0)).aiState!=42) {
                    gameuiBoundaryCloseLeft(this);s.petMenu->setOpen(true);quickTransfer=true;
                }
            }
        }
    }
    CEquipment* initialDragged=s.draggedItem.getObject();
    CCharacter* merchant=NULL;
    bool merchantDestination=false;
    if(s.merchantMenu->open()) {
        merchant=static_cast<CCharacter*>(s.merchantMenu->getOwner());
        merchantDestination=owner==merchant;
    }
    if(s.stashMenu->open() && s.stashMenu->getOwner()==owner && s.draggedItem.getObject() && is(s.draggedItem.getObject(),UNITTYPES::QUESTITEM)) {
        error(s,49);return false;
    }
    unsigned slot=static_cast<unsigned>(clickedSlot);
    if(s.draggedItem.getObject()) {
        if(slot!=static_cast<unsigned>(-1) && owner && slot!=999) {
            int pane=inventory->getRequiredPane(s.draggedItem.getObject());
            int currentPane=inventory->getItemPane(slot);
            if(slot-15>3 && pane!=currentPane) {
                if(pane>2)pane-=2;
                if(s.player==owner) { slot=static_cast<unsigned>(-1);s.inventoryMenu->setTab(pane); }
                else if(s.player->getFollowerCount() && inventory->m_pPositionableObject==s.player->getFollower(0)) {
                    slot=static_cast<unsigned>(-1);
                    if(s.stashMenu->open())s.stashMenu->setPetTab(pane);
                    else if(s.merchantMenu->open())s.merchantMenu->setPetTab(pane);
                    else s.petMenu->setTab(pane);
                } else {
                    slot=static_cast<unsigned>(-1);
                    if(merchantDestination)s.merchantMenu->setTab(pane);
                }
            }
        }
        if(s.draggedItem.getObject() && is(s.draggedItem.getObject(),10) && slot<2) {
            if(is(s.draggedItem.getObject(),38))slot=1;
            else if(is(s.draggedItem.getObject(),37))slot=0;
        }
    }
    CEquipment* displaced0=NULL;
    CEquipment* displaced1=NULL;
    CEquipment* clicked=NULL;
    if(s.draggedItem.getObject() && slot<2 && is(s.draggedItem.getObject(),10)) {
        displaced1=inventory->getEquipmentInSlot(1);
        displaced0=inventory->getEquipmentInSlot(0);
        clicked=displaced1?displaced1:displaced0;
    } else clicked=inventory->getEquipmentInSlot(slot);
    if(clicked) {
        if(s.selectedSkill!=-1) {
            s.player->setTargetItem(clicked);
            s.player->castSkill(s.selectedSkill);
            s.selectedSkill=-1;
            setMouseOverItem(NULL,false);clearHover<0x1020>(s.inventoryMenu);
            gameuiBoundaryCursor(this,static_cast<ECursorState>(0));
            goto RefreshTargetMenus;
        }
        if(s.targetedItem.getObject()) {
            if(!s.targetedItem.getObject()->canUseOnTarget(s.itemUser.getObject(),clicked)) { error(s,49);return false; }
            s.targetedItem.getObject()->useOnTarget(s.itemUser.getObject(),clicked);
            CEquipment* used=s.targetedItem.getObject();
            if(used->m_iUnknown238<2 && used->m_iUnknown248<1 && used->m_iUnknown248!=-9999 && used->m_pInventory) {
                used->m_pInventory->removeEquipment(used);
                if(s.targetedItem.getObject())delete s.targetedItem.getObject();
            }
            setMouseOverItem(NULL,false);clearHover<0x1020>(s.inventoryMenu);
            gameuiBoundaryCursor(this,static_cast<ECursorState>(0));
            s.targetedItem.setObject(NULL);s.itemUser.setObject(NULL);s.targetCharacter.setObject(NULL);
            goto RefreshTargetMenus;
        }
    }
    if(quickTransfer && clicked) {
        CCharacter* destination=s.player;
        CCharacter* defaultDestination=destination;
        int oldSlot=inventory->findEquipmentSlot(clicked);
        int newSlot=-1;
        bool allowEquip=true;
        if(s.enchantMenu->open()) { if(oldSlot!=14)newSlot=14; }
        else if(s.combineMenu->open()) {
            if(static_cast<unsigned>(oldSlot)-15>=4) {
                for(unsigned i=15;i<=18;++i)if(!inventory->getEquipmentInSlot(i)){newSlot=i;break;}
            }
        } else {
            if(!s.stashMenu->open() && is(owner,UNITTYPES::PLAYER)) {
                if(s.player->getFollowerCount()) { destination=s.player->getFollower(0);goto TransferSelected; }
            } else {
                destination=s.player;
                if(destination->getFollowerCount() && owner==destination->getFollower(0))goto TransferSelected;
            }
            if(s.stashMenu->open() && s.stashMenu->getOwner()!=owner) {
                if(is(clicked,UNITTYPES::QUESTITEM)){error(s,49);return false;}
                destination=static_cast<CCharacter*>(s.stashMenu->getOwner());allowEquip=false;
            } else destination=defaultDestination;
        }
TransferSelected:
        inventory->removeEquipment(clicked);
        CInventory* targetInventory=actor(destination).inventory;
        if(is(destination,UNITTYPES::SHAREDSTASH)){targetInventory=CSharedStash::getSingleton()->m_pInventory;allowEquip=false;}
        CEquipment* placed=newSlot==-1?targetInventory->pickupEquipment(clicked,allowEquip):targetInventory->pickupEquipment(clicked,newSlot,allowEquip);
        if(!placed){inventory->pickupEquipment(clicked,oldSlot,true);error(s,47);return result;}
        placed->playDropSound(s.player->getSceneNode());
        goto ClearAndRefresh;
    }
    if(merchantDestination && s.draggedItem.getObject()) {
        if(is(s.draggedItem.getObject(),UNITTYPES::QUESTITEM)){error(s,49);return false;}
        if(merchant!=s.dragOwner.getObject()) {
            sound(s,23);
            int price=s.draggedItem.getObject()->sellPrice();
            s.player->giveGold(price);s.player->soldItem(s.draggedItem.getObject());
            clearHoverAndTooltips(s);
        }
        s.draggedItem.getObject()->playDropSound(s.player->getSceneNode());removeDragIcon(s);
        CEquipment* placed=inventory->pickupEquipment(s.draggedItem.getObject(),true);
        if(!placed){if(s.draggedItem.getObject())delete s.draggedItem.getObject();}
        else {s.draggedItem.setObject(placed);clearHoverAndTooltips(s);}
        s.draggedItem.setObject(NULL);s.dragOwner.setObject(NULL);s.dragSlot=-1;updateHardwareCursor();return false;
    }
    if(quickTrade && clicked && is(owner,UNITTYPES::MERCHANT)) {
        int price=clicked->buyPrice();
        if(s.player->getGold()<price){error(s,48);return result;}
        price=clicked->buyPrice();clearHoverAndTooltips(s);
        int oldSlot=inventory->findEquipmentSlot(clicked);
        bool clone=clicked->m_iUnknown238==1 && clicked->m_bUnknown25F;
        if(clone)clicked=static_cast<CEquipment*>(s.resourceManager->createUnit(clicked->getDataGroup(),0,false,false));
        else inventory->removeEquipment(clicked);
        if(!actor(s.player).inventory->pickupEquipment(clicked,true)) {
            if(clone){if(clicked)delete clicked;}else inventory->pickupEquipment(clicked,oldSlot,true);
            error(s,47);return result;
        }
        recordPurchase(s,owner,clicked);s.player->giveGold(-price);sound(s,23);goto ClearAndRefresh;
    }
    if(!s.draggedItem.getObject() || !s.dragOwner.getObject() || owner==s.dragOwner.getObject()) {
        if(quickTrade && clicked && s.merchantMenu->open() && !is(owner,UNITTYPES::MERCHANT)) {
            if(is(clicked,UNITTYPES::QUESTITEM)){error(s,49);return false;}
            sound(s,23);int price=clicked->sellPrice();s.player->giveGold(price);s.player->soldItem(clicked);
            clearHoverAndTooltips(s);inventory->removeEquipment(clicked);
            if(!actor(merchant).inventory->pickupEquipment(clicked,true))delete clicked;
            clicked=NULL;result=false;updateHardwareCursor();
        }
    } else if(!is(s.dragOwner.getObject(),UNITTYPES::MERCHANT) && !is(s.dragOwner.getObject(),UNITTYPES::STASH) && !is(s.dragOwner.getObject(),UNITTYPES::SHAREDSTASH))clearHoverAndTooltips(s);
    else if(!merchantDestination && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT)) {
        int price=s.draggedItem.getObject()->buyPrice();
        if(s.player->getGold()<price){error(s,48);return result;}
    }
    if(s.draggedItem.getObject() && slot<12 && !s.draggedItem.getObject()->canEquip(owner,true) && !is(s.draggedItem.getObject(),UNITTYPES::SOCKETABLE)) {
        error(s,49);return result;
    }
    if(clicked) {
        if(!s.draggedItem.getObject()) {
            s.dragSlot=inventory->findEquipmentSlot(clicked);inventory->removeEquipment(clicked);
            s.dragOwner.setObject(static_cast<CCharacter*>(menu->getOwner()));s.draggedItem.setObject(clicked);
            s.draggedItem.getObject()->playTakeSound(s.player->getSceneNode());menu->updateLayout();
            clearHoverAndTooltips(s);positionDragIcon(this,s);updateHardwareCursor();return false;
        }
        bool clone=s.dragOwner.getObject() && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT) && s.draggedItem.getObject()->m_iUnknown238==1 && s.draggedItem.getObject()->m_bUnknown25F;
        if(is(s.draggedItem.getObject(),UNITTYPES::SOCKETABLE) && clicked->m_bUnknown348 && clicked->m_iSocketCount!=clicked->m_SocketedEquipment.size()) {
            removeDragIcon(s);s.draggedItem.getObject()->playDropSound(s.player->getSceneNode());
            clicked->addContainerItem(s.draggedItem.getObject());clicked->createElementalDamages();
            if(!merchantDestination && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT)){chargeDraggedPurchase(s);s.dragOwner.setObject(NULL);}
            s.draggedItem.setObject(NULL);inventory->updateBonuses();inventory->calculateEffectValues();inventory->refreshEquipped();
            s.dragOwner.setObject(NULL);s.dragSlot=-1;updateHardwareCursor();menu->updateLayout();return false;
        }
        inventory->findEquipmentSlot(clicked);
        if(!displaced0 || !displaced1) {
            inventory->removeEquipment(clicked);
            if(guid(clicked)==guid(s.draggedItem.getObject()) && clicked->m_iUnknown238<clicked->m_iUnknown23C && s.draggedItem.getObject()->m_iUnknown238<s.draggedItem.getObject()->m_iUnknown23C) {
                int quantity=clicked->m_iUnknown238, capacity=clicked->m_iUnknown23C;
                if(capacity<s.draggedItem.getObject()->m_iUnknown238+quantity) {
                    clicked->incrementStackBy(capacity-quantity);
                    if(!clone)s.draggedItem.getObject()->incrementStackBy(-(capacity-quantity));
                } else {
                    clicked->incrementStackBy(s.draggedItem.getObject()->m_iUnknown238);
                    if(!clone)s.draggedItem.getObject()->incrementStackBy(-s.draggedItem.getObject()->m_iUnknown238);
                }
                if(!merchantDestination && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT))chargeDraggedPurchase(s);
                inventory->pickupEquipment(clicked,slot,true);
                if(s.draggedItem.getObject()->m_iUnknown238<1) {
                    delete s.draggedItem.getObject();s.draggedItem.setObject(NULL);s.dragOwner.setObject(NULL);
                    setMouseOverItem(NULL,false);s.dragSlot=-1;menu->updateLayout();clicked->playDropSound(s.player->getSceneNode());
                }
                updateHardwareCursor();if(clone)returnDraggedItem();goto RestoreDisplaced;
            }
        } else {inventory->removeEquipment(displaced1);inventory->removeEquipment(displaced0);}
        {
            CEquipment* item=s.draggedItem.getObject();
            if(clone)item=static_cast<CEquipment*>(s.resourceManager->createUnit(item->getDataGroup(),0,false,false));
            if(!inventory->pickupEquipment(item,slot,true)) {
                if(clone && item)delete item;
                if(!displaced0 || !displaced1)inventory->pickupEquipment(clicked,slot,true);
                else {inventory->pickupEquipment(displaced1,slot,true);inventory->pickupEquipment(displaced0,slot,true);displaced0=NULL;displaced1=NULL;}
            } else {
                clicked->playTakeSound(s.player->getSceneNode());s.draggedItem.getObject()->playDropSound(s.player->getSceneNode());removeDragIcon(s);
                if(!merchantDestination && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT))chargeDraggedPurchase(s);
                if(clone)returnDraggedItem();
                s.draggedItem.setObject(clicked);s.dragOwner.setObject(owner);clearHoverAndTooltips(s);s.dragSlot=-1;menu->updateLayout();
                if(clicked==displaced1)displaced1=NULL;
                else if(clicked==displaced0)displaced0=NULL;
                positionDragIcon(this,s);
            }
        }
        updateHardwareCursor();
RestoreDisplaced:
        if(displaced1)putBackOrDrop(s,owner,inventory,displaced1);
        if(displaced0)putBackOrDrop(s,owner,inventory,displaced0);
        return false;
    }
    if(!s.draggedItem.getObject())return result;
    if(static_cast<int>(slot)>=0 && static_cast<int>(slot)<12 && !inventory->canEquip(s.draggedItem.getObject(),true))slot=999;
    {
        bool clone=s.dragOwner.getObject() && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT) && s.draggedItem.getObject()->m_iUnknown238==1 && s.draggedItem.getObject()->m_bUnknown25F;
        CDataGroup* data=s.draggedItem.getObject()->getDataGroup();
        int price=s.draggedItem.getObject()->buyPrice();
        CEquipment* placed=NULL;
        if(slot==999){if(inventory->equipEquipmentIntoFirstFreeLocation(s.draggedItem.getObject()))placed=s.draggedItem.getObject();}
        else if(static_cast<int>(slot)<=82)placed=inventory->pickupEquipment(s.draggedItem.getObject(),slot,true);
        if(placed) {
            placed->playDropSound(s.player->getSceneNode());s.rootWindow->removeChildWindow(s.draggedItem.getObject()->m_pIconWindow);
            s.draggedItem.setObject(NULL);s.dragSlot=-1;goto ChargePlaced;
        }
        if(slot>11 && slot!=999)goto ClearAndRefresh;
        if(inventory->equipEquipmentIntoFirstFreeLocation(s.draggedItem.getObject())) {
            owner->setRenderBehind(true);s.draggedItem.getObject()->playDropSound(s.player->getSceneNode());removeDragIcon(s);
            s.draggedItem.setObject(NULL);s.dragSlot=-1;goto ChargePlaced;
        }
        if(!s.draggedItem.getObject()->canEquip(owner,true)) {
            if(s.draggedItem.getObject()){returnDraggedItem();error(s,49);}
            goto ClearAndRefresh;
        }
        {
            CEquipment* first=NULL;CEquipment* second=NULL;
            inventory->getComparisonItems(s.draggedItem.getObject(),&first,&second);
            if(is(s.draggedItem.getObject(),10) && second)inventory->removeEquipment(second);
            bool equipped=false;
            if(first) {
                inventory->removeEquipment(first);
                if(inventory->equipEquipmentIntoFirstFreeLocation(s.draggedItem.getObject())) {
                    equipped=true;owner->setRenderBehind(true);s.draggedItem.getObject()->playDropSound(owner->getSceneNode());removeDragIcon(s);
                }
                if(!inventory->pickupEquipment(first,true)){Ogre::Vector3 p=owner->getPosition(true);s.level->addItem(first,p,true);first->drop();}
                else first->playDropSound(owner->getSceneNode());
            }
            if(is(s.draggedItem.getObject(),10) && second) {
                if(!inventory->pickupEquipment(second,true)){Ogre::Vector3 p=owner->getPosition(true);s.level->addItem(second,p,true);second->drop();}
                else second->playDropSound(owner->getSceneNode());
            }
            if(equipped){s.draggedItem.setObject(NULL);s.dragSlot=-1;goto ChargePlaced;}
            returnDraggedItem();s.dragOwner.setObject(NULL);error(s,49);s.draggedItem.setObject(NULL);s.dragSlot=-1;goto ClearAndRefresh;
        }
ChargePlaced:
        if(!merchantDestination && is(s.dragOwner.getObject(),UNITTYPES::MERCHANT)) {
            if(clone){CEquipment* copy=static_cast<CEquipment*>(s.resourceManager->createUnit(data,0,false,false));actor(s.dragOwner.getObject()).inventory->pickupEquipment(copy,true);}
            if(is(s.dragOwner.getObject(),UNITTYPES::GAMBLER)) {
                s.player->incrementJournalStatistic(static_cast<EJournalStatistic>(15),1);
                if(initialDragged && is(initialDragged,UNITTYPES::UNIQUE)) {
                    CAchievement* achievement=CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(5));
                    if(achievement)achievement->forceComplete();
                }
            }
            s.player->giveGold(-price);sound(s,23);s.dragOwner.setObject(NULL);
        }
    }
ClearAndRefresh:
    clearHoverAndTooltips(s);updateHardwareCursor();return false;
RefreshTargetMenus:
    updateHardwareCursor();s.inventoryMenu->updateLayout();
    if(s.petMenu->open())s.petMenu->updateLayout();
    if(s.merchantMenu->open())s.merchantMenu->updateLayout();
    if(s.stashMenu->open())s.stashMenu->updateLayout();
    clearHoverAndTooltips(s);CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);return false;
}

#include "GameUISlotsState.h"
void CGameUI::updateSlots() {
    using namespace gameui_slots_detail;
    UIState& ui=state(this);
    if(!ui.player || !actor(ui.player).inventory)return;
    primary(this,ui,0,ui.leftIcon,ui.leftCooldown,ui.leftGuid);
    primary(this,ui,1,ui.rightIcon,ui.rightCooldown,ui.rightGuid);
    primary(this,ui,2,ui.attackIcon,ui.attackCooldown,ui.attackGuid);
    for(int i=0;i<10;++i) {
        if(!ui.buttons[i])continue;
        long long skillGuid=actor(ui.player).hotkeySkills[i];
        CSkill* skill=actor(ui.player).skills ? actor(ui.player).skills->getSkillByGuid(skillGuid) : NULL;
        if(skill && !skill->getSkillIcon().empty()) {
            ui.icons[i]->setSize(CEGUI::UVector2(CEGUI::UDim(0,ui.slotWidth),CEGUI::UDim(0,ui.slotHeight)));
            if(ui.skillGuids[i]!=skillGuid) {
                ui.icons[i]->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
                image(ui.icons[i],getImageFromImageSet(reinterpret_cast<const unsigned char*>(
                    STRINGS::StringConvertToNarrow(skill->getSkillIcon().c_str()).c_str())));
                ui.icons[i]->getParent()->setUserData(&ui.skillGuids[i]);
                ui.buttons[i]->setTooltipText(utf8(""));
                ui.counts[i]=-1;
            }
            int seconds=static_cast<int>(ceilf(actor(ui.player).skills->getSkillCoolingTime(skill)));
            if(ui.counts[i]!=seconds) {
                ui.counts[i]=seconds;
                if(seconds>0) {
                    tint(ui.icons[i],0.6f);
                    ui.labels[i]->setText(utf8(STRINGS::StringConvertToUTF8(STRINGS::GetValueAsWString(seconds))));
                } else {
                    tint(ui.icons[i],1.0f);
                    clearText(ui.labels[i]);
                }
            }
            ui.buttons[i]->setID(0);
            ui.itemGuids[i]=-1;
            ui.skillGuids[i]=skillGuid;
        } else {
            static std::string g_LeftClickAssign=STRINGS::StringConvertToUTF8(
                CStringTranslate::getSinglton()->getTranslateString(L"Left-Click to assign Skills or Items"));
            long long itemGuid=actor(ui.player).hotkeyItems[i];
            if(itemGuid!=-1) {
                ui.skillGuids[i]=-1;
                CDataGroup* data=ui.resources->getUnitDataByGuid(itemGuid);
                if(data) {
                    if(ui.itemGuids[i]!=itemGuid) {
                        ui.counts[i]=-1;
                        const CEGUI::Image* itemImage=getImageFromImageSet(reinterpret_cast<const unsigned char*>(
                            STRINGS::StringConvertToNarrow(data->GetDataValue(L"ICON",EMPTY_WSTRING).c_str()).c_str()));
                        // The original abandons all remaining slots if this icon is missing.
                        if(!itemImage)return;
                        float width=itemImage->getWidth();
                        unsigned ratioKey=KSETTINGS_YRATIO;
                        width=gameuiBoundaryScaledY(this,width/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(ratioKey));
                        float height=itemImage->getHeight();
                        ratioKey=KSETTINGS_YRATIO;
                        height=gameuiBoundaryScaledY(this,height/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(ratioKey));
                        float scale=ui.slotWidth/height;
                        width*=scale; height*=scale;
                        ui.icons[i]->setPosition(CEGUI::UVector2(CEGUI::UDim(0,(ui.slotWidth-width)*0.5f),CEGUI::UDim(0,0)));
                        ui.icons[i]->setSize(CEGUI::UVector2(CEGUI::UDim(0,width),CEGUI::UDim(0,height)));
                        image(ui.icons[i],itemImage);
                        ui.buttons[i]->setID(1000);
                        ui.buttons[i]->setUserData(&ui.itemGuids[i]);
                    }
                    int count=actor(ui.player).inventory->getEquipmentCountOfGuid(itemGuid);
                    if(count!=ui.counts[i] || itemGuid!=ui.itemGuids[i]) {
                        ui.counts[i]=count;
                        if(count!=0) {
                            ui.labels[i]->setText(utf8(STRINGS::StringConvertToUTF8(STRINGS::GetValueAsWString(static_cast<unsigned>(count)))));
                            tint(ui.icons[i],1.0f);
                            ui.buttons[i]->setTooltipText(utf8(""));
                        } else {
                            clearText(ui.labels[i]);
                            tint(ui.icons[i],0.6f);
                            ui.buttons[i]->setTooltipText(utf8(g_LeftClickAssign));
                        }
                    }
                    ui.itemGuids[i]=itemGuid;
                } else if(ui.itemGuids[i]!=-1) {
                    ui.itemGuids[i]=-1;
                    clearText(ui.labels[i]);
                    ui.buttons[i]->setTooltipText(utf8(g_LeftClickAssign));
                    ui.buttons[i]->setID(0);
                    ui.icons[i]->setProperty("Image","");
                    ui.icons[i]->getParent()->setUserData(&ui.emptyGuid);
                }
            } else if(ui.itemGuids[i]!=-1 || ui.skillGuids[i]!=-1) {
                ui.skillGuids[i]=-1;
                ui.itemGuids[i]=-1;
                ui.buttons[i]->setTooltipText(utf8(g_LeftClickAssign));
                ui.buttons[i]->setID(0);
                clearText(ui.labels[i]);
                ui.icons[i]->setProperty("Image","");
                ui.icons[i]->getParent()->setUserData(&ui.emptyGuid);
            }
        }
    }
}

// Filled from KSETTINGS_KEYMAP_1..9,0 by the original constructor before create.
#include "GameUIStartupData.h"

// Full startup entry. The phases retain original construction and event order.
#include "GameUIStartup/startup_finalize.h"
bool CGameUI::create() {
    using namespace gameui_create_detail;
    PrefixState& ui=*reinterpret_cast<PrefixState*>(this);
    SceneState& scenes=*reinterpret_cast<SceneState*>(this);
    SheetState& sheets=*reinterpret_cast<SheetState*>(this);
    ImagesetState& images=*reinterpret_cast<ImagesetState*>(this);
    HUDState& hud=*reinterpret_cast<HUDState*>(this);
    HUDGeometry& geom=*reinterpret_cast<HUDGeometry*>(this);
    SkillStartupState& slots=*reinterpret_cast<SkillStartupState*>(this);
    MenuState& menus=*reinterpret_cast<MenuState*>(this);
    FinalState& finalState=*reinterpret_cast<FinalState*>(this);
    createCursors(ui);
    const float initialAspect=logDisplay(this);
    createSounds(ui);
    createRenderer(ui);
    std::wstring logPath=FILESYSTEM::GetAppDataPath()+L"CEGUI.log";
    createSystem(ui,logPath);
    CFileInfo info;
    loadSchemes(info);
    configureFontMarkup(ui);
    const float nativeWidth=configureTooltipAndFontSizes(ui,initialAspect);
    createSheets(this,ui,sheets,info);
    loadImagesets(images,nativeWidth);
    createHUD(this,ui,sheets,hud,geom,info);
    createSkillWidgets(this,ui,hud,images,slots);
    createMenus(this,ui,scenes,sheets,menus);
    finalize(this,ui,scenes,sheets,menus,finalState);
    return true;
}

#include "GameUIInput/Lifecycle.h"
#include "GameUIInput/Hover.h"
#include "GameUIInput/Skills.h"
// Inline only private phases, retaining calls to other original GameUI entries.
bool CGameUI::processIngameInput(void* window,float elapsed,bool enabled)
{
    using namespace gameui_input_detail;
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(this);
    InputState& state=input(this);
    if(!ui.player)return finish(this,true);
    bool result=!state.consumeNextInput;
    state.consumeNextInput=false;
    if(!enabled)return finish(this,result);
    captureAndPosition(this,window,elapsed,result);
    processPlayerState(this);
    Selection selected=collectClicks(this,result);
    processClicks(this,selected,result);
    dispatchMenus(this,window,elapsed,enabled,result);
    processWorldClick(this,result);
    if(!state.labelHovered)detachFromActualParent(state.hoveredLabel);
    updateEquipmentTooltips(this,selected);
    processSkillKeys(this);
    return finish(this,result);
}

#include "SkillFoldout.h"
#include "SkillManager.h"
#include "Skill.h"
#include "Inventory.h"
#include "EquipmentRef.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "DataGroup.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include "GameUIData.h"
#include <vector>
#include <cmath>

namespace foldout_show_detail {
struct OwnerFields {
 char prefix[0x1c8]; CSkillManager* manager;
 char gap1d0[0x490-0x1d0]; CInventory* inventory;
 char gap498[0x950-0x498]; long long primary[12],secondary[12];
};
struct ManagerFields { char prefix[0x60]; TArrayList<CSkill*> skills; };
struct InventoryFields { char prefix[0x30]; TArrayList<CEquipmentRef*> items; };
struct ItemFields { char prefix[0x1a0]; long long guid; };
struct SkillFields {
 char prefix[0x60]; int activation; char gap64[7]; unsigned char blocked;
 char gap6c; unsigned char assignable; char gap6e; unsigned char leftAllowed;
 char gap70[0xd8-0x70]; unsigned int requiredLevel; char gapdc[4]; unsigned int effectiveLevel;
 char gape4[0x150-0xe4]; long long guid;
};
inline __attribute__((always_inline)) OwnerFields& owner(CBaseUnit* p){return *reinterpret_cast<OwnerFields*>(p);}
inline __attribute__((always_inline)) SkillFields& skill(CSkill* p){return *reinterpret_cast<SkillFields*>(p);}
inline __attribute__((always_inline)) CEGUI::String utf8(const char* p){return CEGUI::String(reinterpret_cast<const unsigned char*>(p));}
inline __attribute__((always_inline)) void position(CSkillFoldout* p,int column,int row,bool label,float x,float y){
 float sy=gameuiBoundaryScaledY(p->m_pGameUI,y);float sx=gameuiBoundaryScaledY(p->m_pGameUI,x);
 (label?p->m_Hotkeys[column][row]:p->m_Icons[column][row])->setPosition(CEGUI::UVector2(CEGUI::UDim(0,sx),CEGUI::UDim(0,sy)));
}
inline __attribute__((always_inline)) void size(CSkillFoldout* p,int column,int row,bool label,float x,float y){
 float sy=gameuiBoundaryScaledY(p->m_pGameUI,y);float sx=gameuiBoundaryScaledY(p->m_pGameUI,x);
 (label?p->m_Hotkeys[column][row]:p->m_Icons[column][row])->setSize(CEGUI::UVector2(CEGUI::UDim(0,sx),CEGUI::UDim(0,sy)));
}
inline __attribute__((always_inline)) void hotkey(CSkillFoldout* p,int column,int row,int index,float x,float y){
 p->m_Hotkeys[column][row]->setVisible(true);p->m_Hotkeys[column][row]->setEnabled(true);
 position(p,column,row,true,x,y);
 p->m_Hotkeys[column][row]->setText(utf8(("F"+STRINGS::GetValueAsString(index+1)).c_str()));
 size(p,column,row,true,36.0f,14.0f);
}
}

__attribute__((flatten))
void CSkillFoldout::showFoldout(CBaseUnit* unit,float x,float y,bool includeItems,bool left)
{
 using namespace foldout_show_detail;
 m_bIncludeItems=includeItems;m_bFlagCB1=left;
 if(m_pWindow->getParent() || !unit)return;
 CSkillManager* manager=owner(unit).manager;if(!manager)return;
 m_pParent->addChildWindow(m_pWindow);m_pWindow->moveToFront();
 gameuiBoundaryScaledY(m_pGameUI,160.0f);gameuiBoundaryScaledY(m_pGameUI,100.0f);
 for(int column=0;column<10;++column)for(int row=0;row<10;++row){
  m_Icons[column][row]->setVisible(false);m_Icons[column][row]->setEnabled(false);
  m_Hotkeys[column][row]->setVisible(false);m_Hotkeys[column][row]->setEnabled(false);
 }
 float maxWidth=0.0f,maxHeight=0.0f;int maxColumns=0;
 if(left){
  m_Icons[0][0]->setVisible(true);m_Icons[0][0]->moveToFront();m_Icons[0][0]->setEnabled(true);
  position(this,0,0,false,4,4);
  m_Icons[0][0]->setProperty("Image",CEGUI::PropertyHelper::imageToString(m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>("skill_attack"))));
  size(this,0,0,false,48,48);
  static std::wstring g_WeaponAttack;
  if(g_WeaponAttack.empty())g_WeaponAttack=CStringTranslate::getSinglton()->getTranslateString(L"Assign weapon attack");
  m_Icons[0][0]->setTooltipText(utf8(STRINGS::StringConvertToUTF8(std::wstring(g_WeaponAttack.c_str())).c_str()));
  m_SkillIndices[95]=-999;m_Icons[0][0]->setUserData(&m_SkillIndices[95]);m_Icons[0][0]->setID(95);
  int index=0;while(index<12 && owner(unit).secondary[index]!=-999)++index;
  // A miss exits the scan directly without creating a hotkey label.
  if(index<12)hotkey(this,0,0,index,4,4);
  maxWidth=48;maxHeight=50;maxColumns=1;
 }
 float rowY=0.0f;int lastRow=0,nextColumn=0;
 for(int row=0;row<100;++row){
  int column=left?1:0;
  for(int i=0;i<manager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));++i){
   TArrayList<CSkill*>& skills=reinterpret_cast<ManagerFields*>(manager)->skills;
   CSkill* current=i<static_cast<int>(skills.size())?skills[i]:0;
   int tier=static_cast<int>(::floorf(static_cast<float>(skill(current).requiredLevel)/5.0f));
   if(tier>10)tier=10;if(tier!=row)continue;
   current->calculateEffectiveSkillLevel();
   if(!skill(current).effectiveLevel || !((skill(current).blocked^1)&skill(current).assignable))continue;
   if(left&&!skill(current).leftAllowed)continue;
   if(skill(current).activation==4 || row>9 || column>9)continue;
   m_Icons[column][row]->setVisible(true);m_Icons[column][row]->moveToFront();m_Icons[column][row]->setEnabled(true);
   float columnX=static_cast<float>(column)*50.0f;
   position(this,column,row,false,columnX+4.0f,rowY+4.0f);
   m_Icons[column][row]->setProperty("Image",CEGUI::PropertyHelper::imageToString(m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToNarrow(current->getSkillIcon().c_str()).c_str()))));
   size(this,column,row,false,48,48);
   m_SkillIndices[i]=skill(current).guid;m_Icons[column][row]->setUserData(&m_SkillIndices[i]);m_Icons[column][row]->setID(i);
   m_Icons[column][row]->setTooltipText(utf8(""));
   int index=0;while(index<12 && (left?owner(unit).secondary[index]:owner(unit).primary[index])!=skill(current).guid)++index;
   if(index<12)hotkey(this,column,row,index,columnX+4.0f,rowY+4.0f);
   ++column;if(column>maxColumns)maxColumns=column;
   float width=columnX+48.0f;maxWidth=width>maxWidth?width:maxWidth;
   float height=rowY+50.0f;maxHeight=height>maxHeight?height:maxHeight;
   lastRow=row;nextColumn=column;
  }
  if(column!=0)rowY+=50.0f;
 }
 if(lastRow<9){++lastRow;nextColumn=0;}
 if(includeItems){
  CInventory* inventory=owner(unit).inventory;
  TArrayList<CEquipmentRef*>& items=reinterpret_cast<InventoryFields*>(inventory)->items;
  std::vector<long long> shown;
  for(unsigned int i=0;i<items.size();++i){
   CBaseUnit* item=static_cast<CBaseUnit*>(items[i]->m_pUnknown10);
   if(!item->ISA(static_cast<UNITTYPES::EUNITTYPES>(1)) || item->ISA(static_cast<UNITTYPES::EUNITTYPES>(129)))continue;
   long long guid=reinterpret_cast<ItemFields*>(item)->guid;bool duplicate=false;
   for(unsigned int j=0;j<shown.size();++j)if(shown[j]==guid)duplicate=true;
   if(duplicate)continue;shown.push_back(guid);
   if(nextColumn>9||lastRow>9)continue;
   m_Icons[nextColumn][lastRow]->setVisible(true);m_Icons[nextColumn][lastRow]->moveToFront();m_Icons[nextColumn][lastRow]->setEnabled(true);
   const CEGUI::Image* image=m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToNarrow(item->getDataGroup()->GetDataValue(L"ICON",EMPTY_WSTRING).c_str()).c_str()));
   if(!image)return;
   unsigned int widthRatioKey=KSETTINGS_YRATIO;
   float width=image->getWidth();
   width/=CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(widthRatioKey);
   float height=image->getHeight();
   unsigned int heightRatioKey=KSETTINGS_YRATIO;
   height/=CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(heightRatioKey);
   float factor=48.0f/height;width*=factor;height*=factor;
   float columnX=static_cast<float>(nextColumn)*50.0f;
   position(this,nextColumn,lastRow,false,columnX+4.0f+(48.0f-width)*0.5f,rowY+4.0f);
   m_Icons[nextColumn][lastRow]->setProperty("Image",CEGUI::PropertyHelper::imageToString(image));
   size(this,nextColumn,lastRow,false,width,height);m_Icons[nextColumn][lastRow]->setTooltipText(utf8(""));
   m_ItemGuids[nextColumn][lastRow]=reinterpret_cast<ItemFields*>(item)->guid;m_Icons[nextColumn][lastRow]->setUserData(&m_ItemGuids[nextColumn][lastRow]);m_Icons[nextColumn][lastRow]->setID(1000);
   ++nextColumn;
   float right=columnX+48.0f;maxWidth=right>maxWidth?right:maxWidth;
   float bottom=rowY+50.0f;maxHeight=bottom>maxHeight?bottom:maxHeight;
   if(nextColumn>(maxColumns>4?maxColumns:4)&&lastRow!=9){++lastRow;rowY=bottom;nextColumn=0;}
  }
 }
 float height=gameuiBoundaryScaledY(m_pGameUI,maxHeight+5.0f)+0.0f;
 float width=gameuiBoundaryScaledY(m_pGameUI,maxWidth)+0.0f;
 m_pWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0,width),CEGUI::UDim(0,height)));
 float screenWidth=gameuiBoundaryWidth(g_pGameUI);float screenHeight=gameuiBoundaryHeight(g_pGameUI);
 CEGUI::UDim w=m_pWindow->getWidth();CEGUI::UDim h=m_pWindow->getHeight();
 if(x==-1.0f&&y==-1.0f)return;
 float pixelWidth=static_cast<float>(static_cast<int>(w.d_scale+(w.d_scale>0.0f?0.5f:-0.5f)))+w.d_offset;
 float pixelHeight=static_cast<float>(static_cast<int>(h.d_scale+(h.d_scale>0.0f?0.5f:-0.5f)))+h.d_offset;
 float screenX=static_cast<float>(static_cast<unsigned int>(screenWidth));float screenY=static_cast<float>(static_cast<unsigned int>(screenHeight));
 float px=x+16.0f+26.0f,py=y-pixelHeight-26.0f;
 if(px+pixelWidth+26.0f>screenX)px=screenX-(pixelWidth+26.0f);
 if(py+pixelHeight+26.0f>screenY)py=screenY-(pixelHeight+26.0f);
 if(0.0f>px-26.0f)px=x+26.0f;
 if(py-26.0f<0.0f)py=26.0f;
 m_pWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,px),CEGUI::UDim(0,py)));
}

#include "SkillTooltip.h"
#include "FileSystem.h"
#include "StringUtilities.h"
namespace skill_tooltip_load_detail {
__attribute__((always_inline)) inline float pixelY(CEGUI::Window* window) {
    const CEGUI::UDim& y=window->getYPosition();
    return static_cast<float>(static_cast<int>(y.d_scale+(y.d_scale>0.0f?0.5f:-0.5f)))+y.d_offset;
}
}
__attribute__((flatten))
void CSkillTooltip::load(CGameUI* ui,std::wstring path) {
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
    m_pWindow=CEGUI::WindowManager::getSingleton().loadWindowLayout(
        CEGUI::String(info.m_sResourceName),
        CEGUI::String(STRINGS::uniqueName(std::string("gui_"))),
        CEGUI::String(""),0,0);
    m_pWindow->setAlwaysOnTop(true);
    m_pWindow->setMutedState(true);
    m_pWindow->setMousePassThroughEnabled(true);
    ui->convertToScreenScale(m_pWindow,false);
    m_pSkillIcon=m_pWindow->recursiveChildSearch("SkillIcon");
    m_pSkillName=m_pWindow->recursiveChildSearch("SkillName");
    m_pManaCost=m_pWindow->recursiveChildSearch("ManaCost");
    m_pCooldown=m_pWindow->recursiveChildSearch("Cooldown");
    m_pNextManaCost=m_pWindow->recursiveChildSearch("ManaCostNext");
    m_pNextCooldown=m_pWindow->recursiveChildSearch("CooldownNext");
    m_pSkillRank=m_pWindow->recursiveChildSearch("SkillRank");
    m_pSkillType=m_pWindow->recursiveChildSearch("SkillType");
    m_pDescription=m_pWindow->recursiveChildSearch("Description");
    m_pEffects=m_pWindow->recursiveChildSearch("Effects");
    m_pNextLevel=m_pWindow->recursiveChildSearch("Next Level");
    m_pNextDescription=m_pWindow->recursiveChildSearch("DescriptionNext");
    m_pNextEffects=m_pWindow->recursiveChildSearch("EffectsNext");
    m_pLevelRequirement=m_pWindow->recursiveChildSearch("Level Requirement");
    m_pSkillRequirement=m_pWindow->recursiveChildSearch("Skill Requirement");
    m_pUsage=m_pWindow->recursiveChildSearch("Usage");
    const char* iconNames[4]={"Icon1","Icon2","Icon3","Icon4"};
    const char* textNames[4]={"IconText1","IconText2","IconText3","IconText4"};
    const char* nextIconNames[4]={"NextIcon1","NextIcon2","NextIcon3","NextIcon4"};
    const char* nextTextNames[4]={"NextIconText1","NextIconText2","NextIconText3","NextIconText4"};
    m_pStatIcons[0]=m_pWindow->recursiveChildSearch(iconNames[0]);
    m_StatOffsets[0]=0.0f;
    for(unsigned i=1;i<4;++i) {
        m_pStatIcons[i]=m_pWindow->recursiveChildSearch(iconNames[i]);
        float y=skill_tooltip_load_detail::pixelY(m_pStatIcons[i]);
        float base=skill_tooltip_load_detail::pixelY(m_pStatIcons[0]);
        m_StatOffsets[i]=y-base;
    }
    for(unsigned i=0;i<4;++i) {
        m_pStatLabels[i]=m_pWindow->recursiveChildSearch(textNames[i]);
        float y=skill_tooltip_load_detail::pixelY(m_pStatLabels[i]);
        float base=skill_tooltip_load_detail::pixelY(m_pStatIcons[0]);
        m_StatOffsets[4+i]=y-base;
    }
    m_pNextStatIcons[0]=m_pWindow->recursiveChildSearch(nextIconNames[0]);
    m_NextStatOffsets[0]=0.0f;
    for(unsigned i=1;i<4;++i) {
        m_pNextStatIcons[i]=m_pWindow->recursiveChildSearch(nextIconNames[i]);
        float y=skill_tooltip_load_detail::pixelY(m_pNextStatIcons[i]);
        float base=skill_tooltip_load_detail::pixelY(m_pNextStatIcons[0]);
        m_NextStatOffsets[i]=y-base;
    }
    for(unsigned i=0;i<4;++i) {
        m_pNextStatLabels[i]=m_pWindow->recursiveChildSearch(nextTextNames[i]);
        float y=skill_tooltip_load_detail::pixelY(m_pNextStatLabels[i]);
        float base=skill_tooltip_load_detail::pixelY(m_pNextStatIcons[0]);
        m_NextStatOffsets[4+i]=y-base;
    }
}

#include "SkillFoldout.h"
#include "FileSystem.h"
#include "StringUtilities.h"
#include <CEGUIMemberFunctionSlot.h>
__attribute__((flatten))
void CSkillFoldout::load(CGameUI* ui,std::wstring path) {
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
    m_pWindow=CEGUI::WindowManager::getSingleton().loadWindowLayout(
        CEGUI::String(info.m_sResourceName),
        CEGUI::String(STRINGS::uniqueName(std::string("gui_"))),
        CEGUI::String(""),0,0);
    m_pWindow->setAlwaysOnTop(true);
    m_pWindow->setMousePassThroughEnabled(false);
    ui->convertToScreenScale(m_pWindow,false);
    for(int column=0;column<10;++column)for(int row=0;row<10;++row) {
        m_Icons[column][row]=m_pWindow->recursiveChildSearch(CEGUI::String(
            "SkillIcon"+STRINGS::GetValueAsString(column+1)+STRINGS::GetValueAsString(row+1)));
        m_Icons[column][row]->subscribeEvent(CEGUI::Window::EventMouseMove,
            CEGUI::Event::Subscriber(&CGameUI::handle_SkillSelectMouseOver,m_pGameUI));
        m_Icons[column][row]->subscribeEvent(CEGUI::Window::EventMouseLeaves,
            CEGUI::Event::Subscriber(&CGameUI::handle_SkillSelectMouseOut,m_pGameUI));
        m_Icons[column][row]->subscribeEvent(CEGUI::Window::EventMouseButtonDown,
            CEGUI::Event::Subscriber(&CGameUI::handle_SkillSelectClick,m_pGameUI));
        m_Hotkeys[column][row]=m_pWindow->recursiveChildSearch(CEGUI::String(
            "SkillHotkey"+STRINGS::GetValueAsString(column+1)+STRINGS::GetValueAsString(row+1)));
    }
}

#include "Console.h"
#include "FileUtilities.h"
#include "Utilities.h"
#include "EditorScene.h"
#include <OgreRenderWindow.h>
#include <OgreUTFString.h>
namespace gameui_keys_detail {
struct ConsoleFields { char prefix[0x1690]; CConsole* console; };
struct RenderFields { char prefix[0xb0]; Ogre::RenderWindow* window; };
struct LevelFields { char prefix[0x1a4]; int depth; char gap[0x228-0x1a8]; int seed; };
struct RoomFields { char prefix[0x168]; std::wstring file; };
struct ActorFields { char prefix[0x58]; Ogre::SceneNode* node; };
#define OTL_KEYS_OFFSET(T,F,O) typedef char check_##T##_##F[__builtin_offsetof(T,F)==O?1:-1]
OTL_KEYS_OFFSET(ConsoleFields,console,0x1690);
OTL_KEYS_OFFSET(RenderFields,window,0xb0);
OTL_KEYS_OFFSET(LevelFields,depth,0x1a4);
OTL_KEYS_OFFSET(LevelFields,seed,0x228);
OTL_KEYS_OFFSET(RoomFields,file,0x168);
OTL_KEYS_OFFSET(ActorFields,node,0x58);
#undef OTL_KEYS_OFFSET

inline __attribute__((always_inline)) void capture(CGameUI* self) {
    gameui_input_detail::InputState& s=gameui_input_detail::input(self);
    s.mouseThrough=false;s.leftSlot=-1;s.rightSlot=-1;s.pendingRightSlot=-1;
    self->captureProcessInput();
}
inline __attribute__((always_inline)) bool pressed(CGameUI* self,unsigned setting) {
    return gameui_input_detail::keys(self).keyPressed(gameui_input_detail::settings(self)->GetInt(setting));
}
}
void CGameUI::handleKeyPresses()
{
    using namespace gameui_input_detail;
    using namespace gameui_keys_detail;
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(this);
    if(!ui.resourceManager)return;
    if(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_KEYMAP_CONSOLE_HOLD)<=0 ||
       keys(this).keyHeld(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_KEYMAP_CONSOLE_HOLD))) {
        if(keys(this).keyPressed(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_KEYMAP_CONSOLE_PRESS))) {
            capture(this);toggleConsole();
        }
    }
    if(reinterpret_cast<ConsoleFields*>(this)->console->getVisible()){capture(this);return;}
    if(pressed(this,KSETTINGS_KEYMAP_INVENTORY)||gToggleInventory){gToggleInventory=false;toggleInventory();}
    if(pressed(this,KSETTINGS_KEYMAP_WEAPONSET)&&ui.inventoryMenu) {
        if(ui.player->hasWeaponsInOffSet()||ui.inventoryMenu->open())ui.inventoryMenu->toggleWeaponSet();
    }
    if(pressed(this,KSETTINGS_KEYMAP_SKILLS))toggleSkill();
    if(pressed(this,KSETTINGS_KEYMAP_JOURNAL))toggleJournal();
    if(pressed(this,KSETTINGS_KEYMAP_QUESTS))toggleQuest();
    if(pressed(this,KSETTINGS_KEYMAP_STATS)||gToggleStats){gToggleStats=false;toggleStats();}
    if(pressed(this,KSETTINGS_KEYMAP_PET)||gTogglePet){gTogglePet=false;togglePet();}
    if(pressed(this,KSETTINGS_KEYMAP_SWAPSKILLS)) {
        ui.player->swapSkills();detachFromActualParent(foldout(skillWindows(this).foldout).root);
    }
    if(ui.level) {
        if(pressed(this,KSETTINGS_KEYMAP_AUTOMAP)&&!input(this).paused)ui.level->toggleAutomap();
        if(pressed(this,KSETTINGS_KEYMAP_AUTOMAPZOOMOUT))ui.level->zoomAutomap(5.0f);
        if(pressed(this,KSETTINGS_KEYMAP_AUTOMAPZOOMIN))ui.level->zoomAutomap(-5.0f);
        if(keys(this).keyPressed(0x90)) {
            std::wstring text=L"Seed: "+STRINGS::GetValueAsWString(reinterpret_cast<LevelFields*>(ui.level)->seed)+L"\r\n";
            text+=L"Depth: "+STRINGS::GetValueAsWString(reinterpret_cast<LevelFields*>(ui.level)->depth)+L"\r\n";
            if(ui.player&&ui.level) {
                Ogre::Vector3 position=ui.player->getPosition(true);
                CEditorScene* room=ui.level->getRoomThatPositionIsIn(position);
                if(room)text+=std::wstring((Ogre::UTFString("Room: ")+Ogre::UTFString(std::wstring(reinterpret_cast<RoomFields*>(room)->file))).asWStr());
            }
            UTILITIES::SetClipBoardText(std::wstring(text));
        }
        if(keys(this).keyHeld(0x10)&&keys(this).keyPressed(0x78)) {
            Ogre::RenderWindow* window=reinterpret_cast<RenderFields*>(CMasterResourceManager::getSingleton())->window;
            if(window) {
                const std::wstring& folder=settings(this)->GetString(KSETTINGS_S_PATH_SCREENSHOTS);
                std::wstring full=FILESYSTEM::GetAppDataPath()+folder;
                FILESYSTEM::CreateAppDataDirectory(full);
                window->writeContentsToTimestampedFile(STRINGS::StringConvertToNarrow(full.c_str()),".png");
            }
        }
    }
    if(pressed(this,KSETTINGS_KEYMAP_CYCLESKILLDOWN)) {
        ui.soundBank->playSample(30,reinterpret_cast<ActorFields*>(ui.player)->node,0.0f,0.0f,false);
        ui.player->cycleSkill(-1);
    } else if(pressed(this,KSETTINGS_KEYMAP_CYCLESKILLUP)) {
        ui.soundBank->playSample(30,reinterpret_cast<ActorFields*>(ui.player)->node,0.0f,0.0f,false);
        ui.player->cycleSkill(1);
    }
}


// Imported source candidates; historical status is not fresh acceptance.
void CGameUI::requestSetGameState(EGameState state, EMenu menu)
{
    m_requestedGameState = state;
    m_requestedMenu = menu;
}

void CGameUI::clearGameStateRequest()
{
    m_requestedGameState = static_cast<EGameState>(6);
    m_requestedMenu = static_cast<EMenu>(6);
}

void CGameUI::statsChanged()
{
    m_statsMenu->updateLayout();
    m_inventoryMenu->updateLayout();
}

bool CGameUI::getDieMenuIsOpen()
{
    return m_dieMenu ? (m_dieMenu->m_bUnknown30 || !m_dieMenu->m_bUnknown31) : false;
}

bool CGameUI::questDialogOpen()
{
    return m_questDialogMenu ? (m_questDialogMenu->m_bUnknown30 || !m_questDialogMenu->m_bUnknown31) : false;
}

bool CGameUI::isCinematicMenuOpen()
{
    return m_cinematicMenu ? (m_cinematicMenu->m_bUnknown30 || !m_cinematicMenu->m_bUnknown31) : false;
}

void CGameUI::hideModalDialogs()
{
    m_optionsMenu->setOpen(false);
    m_dialogMenu->setOpen(false);
    m_dropdown548->setOpen(false);
    m_tipMenu->setOpen(false);
}

bool CGameUI::tipMenuOpen()
{
    return m_tipMenu->m_bUnknown30 || !m_tipMenu->m_bUnknown31;
}

bool CGameUI::modalDialogOpen()
{
    for (unsigned int i = 0; i < m_dropdowns.size(); ++i)
        if (m_dropdowns[i]->m_bUnknown30 || !m_dropdowns[i]->m_bUnknown31) return true;
    return false;
}

bool CGameUI::modalDialogOpenPartial()
{
    for (unsigned int i = 0; i < m_dropdowns.size(); ++i)
        if (m_dropdowns[i]->m_bUnknown30) return true;
    return false;
}

bool CGameUI::eitherCoveredPartial()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (m_submenus[i]->openPartial()) return true;
    return false;
}

bool CGameUI::leftCovered()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (!m_submenus[i]->isRight() && m_submenus[i]->open()) return true;
    return false;
}

bool CGameUI::rightCovered()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (m_submenus[i]->isRight() && m_submenus[i]->open()) return true;
    return false;
}

bool CGameUI::bothCovered()
{
    return leftCovered() && rightCovered();
}

void CGameUI::toggleStatFill()
{
}

CEquipment* CGameUI::getMouseOverItem()
{
    return m_mouseOverItem;
}

void CGameUI::flushProcessInput()
{
    m_mouseThrough = false;
    m_leftSlot = -1;
    m_rightSlot = -1;
    m_pendingRightSlot = -1;
}

void CGameUI::closeLeft()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (!m_submenus[i]->isRight()) m_submenus[i]->setOpen(false);
}

void CGameUI::closeRight()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (m_submenus[i]->isRight()) m_submenus[i]->setOpen(false);
}

void CGameUI::refreshQuestMenu()
{
    if (m_questMenu->open() || m_questMenu->openPartial()) m_questMenu->updateLayout();
}

void CGameUI::closeCinematicMenu()
{
    if (m_cinematicMenu) m_cinematicMenu->setOpen(false);
}

void CGameUI::clickLeft()
{
}

bool CGameUI::handle_MouseOut(const CEGUI::EventArgs& event)
{
    return true;
}

void CGameUI::removeMenuListener(EMENU_TYPE type, iMenuListener* listener)
{
    if (type == 0)
    {
        if (m_questDialogMenu) m_questDialogMenu->removeMenuListener(listener);
    }
    else if (type == 1)
    {
        if (m_cinematicMenu) m_cinematicMenu->removeMenuListener(listener);
    }
}

float CGameUI::getWindowHeight()
{
    return static_cast<float>(m_settings->GetInt(KSETTINGS_RES_HEIGHT));
}

float CGameUI::getWindowWidth()
{
    return static_cast<float>(m_settings->GetInt(KSETTINGS_RES_WIDTH));
}

float CGameUI::getAspectRatio()
{
    float width = getWindowWidth();
    return width / getWindowHeight();
}

void CGameUI::setCursorState(ECursorState state)
{
    if (m_cursorState != state)
    {
        m_cursorState = state;
        updateHardwareCursor();
    }
}

float CGameUI::scaledY(float value)
{
    return m_settings->GetFloat(KSETTINGS_YRATIO) * value;
}

float CGameUI::scaledX(float value)
{
    return m_settings->GetFloat(KSETTINGS_XRATIO) * value;
}

bool CGameUI::getConsoleIsOpen()
{
    return m_console ? m_console->getVisible() : false;
}

void CGameUI::captureProcessInput()
{
    gameui_input_detail::mouse(this).capture();
    gameui_input_detail::keys(this).capture();
}

void CGameUI::setRightButtonPressed()
{
    gameui_input_detail::mouse(this).mouseEvent(0x204, 0);
    gameui_input_detail::mouse(this).capture();
}

void CGameUI::flushInput()
{
    m_mouseThrough = false;
    m_leftSlot = -1;
    m_rightSlot = -1;
    m_pendingRightSlot = -1;
    gameui_input_detail::keys(this).flushAll();
    gameui_input_detail::mouse(this).flushAll();
}

void CGameUI::setActiveMenu(EMenu menu)
{
    if (m_menuManager) m_menuManager->setActiveMenu(menu);
}

void CGameUI::reloadMenuCharacters()
{
    m_menuManager->reloadMenuCharacters();
}

void CGameUI::closeMenus()
{
    if (m_menuManager) m_menuManager->closeMenus();
    m_mouseThrough = false;
    m_leftSlot = -1;
    m_rightSlot = -1;
    m_pendingRightSlot = -1;
    gameui_input_detail::keys(this).flushAll();
    gameui_input_detail::mouse(this).flushAll();
}

void CGameUI::unPause()
{
    if (m_paused) togglePause();
}

bool CGameUI::handle_SkillMouseOut(const CEGUI::EventArgs& event)
{
    const CEGUI::WindowEventArgs& e = static_cast<const CEGUI::WindowEventArgs&>(event);
    if (e.window)
    {
        if (e.window->getID() == 1000) m_itemHovered = false;
        else m_skillHovered = false;
    }
    return true;
}

bool CGameUI::handle_SkillSelectMouseOut(const CEGUI::EventArgs& event)
{
    const CEGUI::WindowEventArgs& e = static_cast<const CEGUI::WindowEventArgs&>(event);
    if (e.window)
    {
        m_foldoutSkillHovered = false;
        m_foldoutItemHovered = false;
        m_foldoutItemGuid = -1;
        m_foldoutSkillGuid = -1;
    }
    m_skillHovered = false;
    m_itemHovered = false;
    return true;
}

bool CGameUI::handle_ClickThrough(const CEGUI::EventArgs& event)
{
    m_mouseThrough = true;
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    return true;
}

void CGameUI::closeAll()
{
    closeLeft();
    closeRight();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_questDialogMenu->setOpen(false);
    m_dropdown530->setOpen(false);
    m_dropdown548->setOpen(false);
    m_tipMenu->setOpen(false);
}

bool CGameUI::handle_ToggleOptions(const CEGUI::EventArgs& event)
{
    closeAll();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_optionsMenu->setOpen(true);
    return true;
}

void CGameUI::toggleSettings()
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_optionsMenu->setOpen(false);
    if (m_dialogMenu) m_dialogMenu->setOpen(!m_dialogMenu->m_bUnknown30);
}

void CGameUI::togglePet()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_inventoryMenu->openPartial() || !modalDialogOpen()) {
        if (!m_inventoryMenu->openPartial()) closeLeft();
        m_inventoryMenu->setOpen(!m_inventoryMenu->openPartial());
        m_topWindow->moveToFront();
    }
}

void CGameUI::toggleQuest()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_questMenu->openPartial() || !modalDialogOpen()) {
        if (!m_questMenu->openPartial()) closeRight();
        m_questMenu->setOpen(!m_questMenu->openPartial());
        m_topWindow->moveToFront();
    }
}

void CGameUI::toggleJournal()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_journalMenu->openPartial() || !modalDialogOpen()) {
        if (!m_journalMenu->openPartial()) closeRight();
        m_journalMenu->setOpen(!m_journalMenu->openPartial());
        m_topWindow->moveToFront();
    }
}

bool CGameUI::handle_ToggleQuest(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleQuest();
    return true;
}

bool CGameUI::handle_ToggleJournal(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleJournal();
    return true;
}

bool CGameUI::handle_ToggleSkill(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleSkill();
    return true;
}

bool CGameUI::handle_ToggleInventory(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleInventory();
    return true;
}

void CGameUI::toggleOptions()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (!m_optionsMenu->m_bUnknown30) closeAll();
    if (m_optionsMenu) {
        m_dialogMenu->setOpen(false);
        m_optionsMenu->setOpen(!m_optionsMenu->m_bUnknown30);
    }
}

void CGameUI::toggleDeath()
{
    if (m_dieMenu) {
        unPause();
        closeAll();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_optionsMenu->setOpen(false);
        m_dialogMenu->setOpen(false);
        m_dieMenu->setOpen(!m_dieMenu->m_bUnknown30);
    }
}

void CGameUI::toggleWaypointMenu()
{
    if (m_waypointMenu) {
        unPause();
        closeAll();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_optionsMenu->setOpen(false);
        m_dialogMenu->setOpen(false);
        m_waypointMenu->setOpen(!m_waypointMenu->m_bUnknown30);
    }
}

void CGameUI::toggleDialog()
{
    if (m_dropdown530) {
        unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_dropdown530->setOpen(!m_dropdown530->m_bUnknown30);
    }
}

float CGameUI::leftScreenEdge()
{
    float edge = 0.0f;
    for (unsigned int i=0; i<m_submenus.size(); ++i) {
        if (!m_submenus[i]->isRight()) edge = std::max(edge, m_submenus[i]->screenEdge());
    }
    return edge;
}

float CGameUI::rightScreenEdge()
{
    float edge = 10000.0f;
    for (unsigned int i=0; i<m_submenus.size(); ++i) {
        if (m_submenus[i]->isRight()) edge = std::min(edge, m_submenus[i]->screenEdge());
    }
    return edge;
}

bool CGameUI::handle_TogglePet(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    gTogglePet = true;
    return true;
}

bool CGameUI::handle_ToggleStats(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    gToggleStats = true;
    return true;
}

bool CGameUI::handle_ToggleMap(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_level && !m_paused) m_level->toggleAutomap();
    return true;
}

void CGameUI::toggleStats()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_characterStatsMenu->openPartial() || !modalDialogOpen()) {
        if (!m_characterStatsMenu->openPartial()) closeLeft();
        m_characterStatsMenu->setOpen(!m_characterStatsMenu->openPartial());
        m_topWindow->moveToFront();
    }
}

void CGameUI::toggleSkill()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_pWindow;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_skillsMenu->openPartial() || !modalDialogOpen()) {
        if (!m_skillsMenu->openPartial()) closeRight();
        m_skillsMenu->setOpen(!m_skillsMenu->openPartial());
        m_topWindow->moveToFront();
    }
}

void CGameUI::toggleFPS()
{
    if (!m_displayStats) {
        m_settings->SetInt(KSETTINGS_DISPLAY_STATS, 1);
        m_rootWindow->addChildWindow(m_statsWindow);
    } else {
        m_settings->SetInt(KSETTINGS_DISPLAY_STATS, 0);
        m_rootWindow->removeChildWindow(m_statsWindow);
    }
    m_displayStats = !m_displayStats;
}
