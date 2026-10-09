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
  float minimumWidth=scaledY(160.0f);float minimumHeight=scaledY(100.0f);
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
  float height=maxSecond(minimumHeight,y);float borderWidth=scaledY(52.0f)-52.0f;float borderHeight=scaledY(52.0f)-52.0f;
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
float minimumWidth=m_pGameUI->scaledY(160.0f);
float minimumHeight=m_pGameUI->scaledY(100.0f);
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
float descriptionBound=m_pGameUI->scaledY(300.0f);
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
  float bound=m_pGameUI->scaledY(300.0f);
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
float extraWidth=g_pGameUI->scaledY(52.0f)-52.0f;
float extraHeight=g_pGameUI->scaledY(52.0f)-52.0f;
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
    y-=ui->scaledY(48.0f);
    float x=static_cast<float>(s.mouseX);
    x-=ui->scaledY(32.0f);
    s.draggedItem.getObject()->m_pIconWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
    float height=ui->scaledY(96.0f);
    float width=ui->scaledY(64.0f);
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
                closeRight();s.inventoryMenu->setOpen(true);quickTransfer=true;
            } else if(!s.petMenu->open() && s.inventoryMenu->open() && s.player->getFollowerCount()) {
                if(actor(s.player->getFollower(0)).aiState!=42) {
                    closeLeft();s.petMenu->setOpen(true);quickTransfer=true;
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
            setCursorState(static_cast<ECursorState>(0));
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
            setCursorState(static_cast<ECursorState>(0));
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
                        width=scaledY(width/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(ratioKey));
                        float height=itemImage->getHeight();
                        ratioKey=KSETTINGS_YRATIO;
                        height=scaledY(height/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(ratioKey));
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
