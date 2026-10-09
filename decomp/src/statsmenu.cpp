#include "StatsMenu.h"
#include "Character.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#include "GameGlobals.h"
#include "GenericModel.h"
#include "DynamicPropertyFile.h"
#include "GameVariables.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "TArrayList.h"
#include <CEGUI.h>
#include <OgreUTFString.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>

namespace stats_update {
typedef char check_m_pParent[__builtin_offsetof(CStatsMenu,m_pParent)==16?1:-1];
typedef char check_m_pRoot[__builtin_offsetof(CStatsMenu,m_pRoot)==24?1:-1];
typedef char check_m_pTopPanel[__builtin_offsetof(CStatsMenu,m_pTopPanel)==32?1:-1];
typedef char check_m_pBottomPanel[__builtin_offsetof(CStatsMenu,m_pBottomPanel)==40?1:-1];
typedef char check_m_pExperienceBar[__builtin_offsetof(CStatsMenu,m_pExperienceBar)==48?1:-1];
typedef char check_m_pFameBar[__builtin_offsetof(CStatsMenu,m_pFameBar)==56?1:-1];
typedef char check_m_ExperienceWidth[__builtin_offsetof(CStatsMenu,m_ExperienceWidth)==64?1:-1];
typedef char check_m_ExperienceHeight[__builtin_offsetof(CStatsMenu,m_ExperienceHeight)==72?1:-1];
typedef char check_m_FameWidth[__builtin_offsetof(CStatsMenu,m_FameWidth)==80?1:-1];
typedef char check_m_FameHeight[__builtin_offsetof(CStatsMenu,m_FameHeight)==88?1:-1];
typedef char check_m_pOwner[__builtin_offsetof(CStatsMenu,m_pOwner)==96?1:-1];
typedef char check_m_bOpenPartial[__builtin_offsetof(CStatsMenu,m_bOpenPartial)==104?1:-1];
typedef char check_m_bFullyClosed[__builtin_offsetof(CStatsMenu,m_bFullyClosed)==105?1:-1];
typedef char check_m_pProperties[__builtin_offsetof(CStatsMenu,m_pProperties)==112?1:-1];
typedef char check_m_pGameUI[__builtin_offsetof(CStatsMenu,m_pGameUI)==120?1:-1];
typedef char check_m_pNameText[__builtin_offsetof(CStatsMenu,m_pNameText)==144?1:-1];
typedef char check_m_pFameTitleText[__builtin_offsetof(CStatsMenu,m_pFameTitleText)==152?1:-1];
typedef char check_m_pLevelText[__builtin_offsetof(CStatsMenu,m_pLevelText)==192?1:-1];
typedef char check_m_pFameLevelText[__builtin_offsetof(CStatsMenu,m_pFameLevelText)==200?1:-1];
typedef char check_m_AttributeTexts[__builtin_offsetof(CStatsMenu,m_AttributeTexts)==208?1:-1];
typedef char check_m_DamageTexts[__builtin_offsetof(CStatsMenu,m_DamageTexts)==240?1:-1];
typedef char check_m_pArmorText[__builtin_offsetof(CStatsMenu,m_pArmorText)==264?1:-1];
typedef char check_m_pManaText[__builtin_offsetof(CStatsMenu,m_pManaText)==272?1:-1];
typedef char check_m_pHealthText[__builtin_offsetof(CStatsMenu,m_pHealthText)==280?1:-1];
typedef char check_m_pExperienceText[__builtin_offsetof(CStatsMenu,m_pExperienceText)==288?1:-1];
typedef char check_m_pFameText[__builtin_offsetof(CStatsMenu,m_pFameText)==296?1:-1];
typedef char check_m_ResistanceTexts[__builtin_offsetof(CStatsMenu,m_ResistanceTexts)==312?1:-1];
typedef char check_m_pPointsText[__builtin_offsetof(CStatsMenu,m_pPointsText)==304?1:-1];
typedef char check_m_pPointsContainer[__builtin_offsetof(CStatsMenu,m_pPointsContainer)==344?1:-1];
typedef char check_m_SpendButtons[__builtin_offsetof(CStatsMenu,m_SpendButtons)==352?1:-1];
typedef char check_m_ReclaimButtons[__builtin_offsetof(CStatsMenu,m_ReclaimButtons)==384?1:-1];
typedef char check_m_pModel[__builtin_offsetof(CStatsMenu,m_pModel)==416?1:-1];
typedef char check_m_pResourceManager[__builtin_offsetof(CStatsMenu,m_pResourceManager)==424?1:-1];
typedef char check_m_fScreenEdge[__builtin_offsetof(CStatsMenu,m_fScreenEdge)==432?1:-1];
typedef char check_m_InvestedPoints[__builtin_offsetof(CStatsMenu,m_InvestedPoints)==448?1:-1];

struct ActorFields {
 char prefix[0x100];unsigned level;
 char gap104[0x418-0x104];int baseHealth;
 char gap41c[0x428-0x41c];int dexterity,strength,defense,magic;
 char gap438[4];int baseMana;
 char gap440[8];int experience,fameExperience,fameLevel;
 char gap454[8];int unusedPoints;
 char gap460[0x4c0-0x460];std::wstring name;
};
struct GlobalsFields {char prefix[0xc0];TArrayList<std::wstring> fameNames;};
inline __attribute__((always_inline)) ActorFields& actor(CCharacter* p){return *reinterpret_cast<ActorFields*>(p);}
inline __attribute__((always_inline)) CEGUI::String utf8(const std::string& s){return CEGUI::String(reinterpret_cast<const unsigned char*>(s.c_str()));}
inline __attribute__((always_inline)) bool changed(CEGUI::Window*& window,const std::string& value){
 if(window->getText()==value)return false;window->setText(utf8(value));return true;
}
inline __attribute__((always_inline)) bool changed(CEGUI::Window*& window,const CEGUI::String& value){
 if(window->getText()==value)return false;window->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(value.c_str())));return true;
}
inline __attribute__((always_inline)) void textColour(CEGUI::Window*& window,int value,int base){
 window->setProperty("TextColour",value<base?"FFFF0000":value>base?"FFc0c0ff":"FFFFFFFF");
}
inline __attribute__((always_inline)) float clamped(float value){if(value<0)return 0;return value>1?1:value;}
inline __attribute__((always_inline)) int delta(int a,int b){return static_cast<int>(static_cast<unsigned>(a)-static_cast<unsigned>(b));}
inline __attribute__((always_inline)) void bar(CEGUI::Window*& window,const CEGUI::UDim& width,const CEGUI::UDim& height,float ratio){
 float h=height.asAbsolute(1.0f);float w=width.asAbsolute(1.0f);w=float(int(w*clamped(ratio)));
 window->setSize(CEGUI::UVector2(CEGUI::UDim(0,w),CEGUI::UDim(0,h)));
}
inline __attribute__((always_inline)) void tooltip(CEGUI::Window*& window,const std::wstring& text){
 std::string converted=STRINGS::StringConvertToUTF8(std::wstring(text.c_str()));
 // The original compares the narrow char* overload, then converts again.
 if(window->getTooltipText()!=converted.c_str())window->setTooltipText(utf8(STRINGS::StringConvertToUTF8(std::wstring(text.c_str()))));
}
inline __attribute__((always_inline)) std::string rangeText(int low,int high){
 std::string maximum=STRINGS::GetValueAsString(high);return STRINGS::GetValueAsString(low)+"-"+maximum;
}
inline __attribute__((always_inline)) std::wstring percentTip(const std::wstring& description,const std::wstring& caption,int value){
 std::wstring number=STRINGS::GetValueAsWString(value);return description+L"\n|cFF5e88ff"+caption+L":"+number+L"%";
}
typedef int(CCharacter::*Getter)();
inline __attribute__((always_inline)) void attribute(CStatsMenu* menu,unsigned index,Getter get,int ActorFields::*base){
 std::string text=STRINGS::GetValueAsString((menu->m_pOwner->*get)());
 if(changed(menu->m_AttributeTexts[index],text)) {
  int value=(menu->m_pOwner->*get)();int original=actor(menu->m_pOwner).*base;
  if(value<original)menu->m_AttributeTexts[index]->setProperty("TextColour","FFFF0000");
  else {value=(menu->m_pOwner->*get)();original=actor(menu->m_pOwner).*base;menu->m_AttributeTexts[index]->setProperty("TextColour",value>original?"FFc0c0ff":"FFFFFFFF");}
 }
}
}

__attribute__((flatten))
void CStatsMenu::update(float elapsed) {
 using namespace stats_update;
 int width=m_pProperties->GetInt(KSETTINGS_RES_WIDTH);
 int height=m_pProperties->GetInt(KSETTINGS_RES_HEIGHT);
 if(!m_bOpenPartial && m_bFullyClosed)return;
 if(m_pOwner) {
  if(actor(m_pOwner).unusedPoints>0 || m_InvestedPoints[0]>0 || m_InvestedPoints[1]>0 || m_InvestedPoints[2]>0 || m_InvestedPoints[3]>0) {
   m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(7));m_pPointsContainer->setVisible(true);
   for(unsigned i=0;i<4;++i)m_ReclaimButtons[i]->setVisible(m_InvestedPoints[i]>0);
   for(unsigned i=0;i<4;++i)m_SpendButtons[i]->setVisible(actor(m_pOwner).unusedPoints>0);
  } else m_pPointsContainer->setVisible(false);
  if(changed(m_pLevelText,STRINGS::GetValueAsString(actor(m_pOwner).level)))for(unsigned i=0;i<4;++i)m_InvestedPoints[i]=0;
  CEGUI::String name=utf8(STRINGS::StringConvertToNarrow(actor(m_pOwner).name.c_str()));changed(m_pNameText,name);
  static std::wstring g_XP;if(g_XP.empty())g_XP=CStringTranslate::getSinglton()->getTranslateString(L"XP");
  int level=int(actor(m_pOwner).level);
  std::string xpGate=STRINGS::GetValueAsString(CMasterResourceManager::getSingleton()->experienceGate(level));
  std::wstring xpText=(Ogre::UTFString(g_XP+L": "+STRINGS::GetValueAsWString(actor(m_pOwner).experience))+Ogre::UTFString("/")+Ogre::UTFString(xpGate)).asWStr();
  CEGUI::String xp=utf8(STRINGS::StringConvertToUTF8(xpText));
  if(changed(m_pExperienceText,xp)) {
   float current=float(actor(m_pOwner).experience);int previous=int(actor(m_pOwner).level-1U);
   float numerator=current-float(CMasterResourceManager::getSingleton()->experienceGate(previous));
   level=int(actor(m_pOwner).level);int upper=CMasterResourceManager::getSingleton()->experienceGate(level);
   previous=int(actor(m_pOwner).level-1U);int lower=CMasterResourceManager::getSingleton()->experienceGate(previous);
   bar(m_pExperienceBar,m_ExperienceWidth,m_ExperienceHeight,numerator/float(delta(upper,lower)));
  }
  int fameLevel=actor(m_pOwner).fameLevel;changed(m_pFameLevelText,STRINGS::GetValueAsString(fameLevel));
  unsigned fameIndex=static_cast<unsigned>(fameLevel)-1U;
  TArrayList<std::wstring>& titles=reinterpret_cast<GlobalsFields*>(CGameGlobals::getSingleton())->fameNames;
  unsigned last=titles.size()-1U;if(fameIndex>last)fameIndex=last;
  std::string title=STRINGS::StringConvertToUTF8(std::wstring(titles[fameIndex].c_str()));changed(m_pFameTitleText,title);
  static std::wstring g_Fame;if(g_Fame.empty())g_Fame=CStringTranslate::getSinglton()->getTranslateString(L"Fame");
  fameLevel=actor(m_pOwner).fameLevel;
  std::string fameGate=STRINGS::GetValueAsString(CMasterResourceManager::getSingleton()->fameGate(fameLevel));
  std::wstring fameText=(Ogre::UTFString(g_Fame+L": "+STRINGS::GetValueAsWString(actor(m_pOwner).fameExperience))+Ogre::UTFString("/")+Ogre::UTFString(fameGate)).asWStr();
  CEGUI::String fame=utf8(STRINGS::StringConvertToUTF8(fameText));
  if(changed(m_pFameText,fame)) {
   float current=float(actor(m_pOwner).fameExperience);int previous=delta(actor(m_pOwner).fameLevel,1);
   float numerator=current-float(CMasterResourceManager::getSingleton()->fameGate(previous));
   fameLevel=actor(m_pOwner).fameLevel;int upper=CMasterResourceManager::getSingleton()->fameGate(fameLevel);
   previous=delta(actor(m_pOwner).fameLevel,1);int lower=CMasterResourceManager::getSingleton()->fameGate(previous);
   // Original reuses experience height, not the cached fame height.
   bar(m_pFameBar,m_FameWidth,m_ExperienceHeight,numerator/float(delta(upper,lower)));
  }
  attribute(this,0,&CCharacter::strength,&ActorFields::strength);
  attribute(this,1,&CCharacter::dexterity,&ActorFields::dexterity);
  attribute(this,2,&CCharacter::magic,&ActorFields::magic);
  attribute(this,3,&CCharacter::defense,&ActorFields::defense);
  int low=m_pOwner->minimumDamageForDisplay(true,false,false);
  m_pOwner->minimumDamageForDisplay(true,false,true);
  int high=m_pOwner->maximumDamageForDisplay(true,false,false);
  int baseHigh=m_pOwner->maximumDamageForDisplay(true,false,true);
  std::string damage=rangeText(low,high);if(changed(m_DamageTexts[0],damage))textColour(m_DamageTexts[0],high,baseHigh);
  static std::wstring g_CritChance;if(g_CritChance.empty())g_CritChance=CStringTranslate::getSinglton()->getTranslateString(L"Critical Chance");
  std::wstring tip=percentTip(m_TextA0,g_CritChance,m_pOwner->getCriticalChance());tooltip(m_DamageTexts[0],tip);
  tip=percentTip(m_TextB0,g_CritChance,m_pOwner->getCriticalChance());tooltip(m_DamageTexts[1],tip);
  low=m_pOwner->minimumDamageForDisplay(false,false,false);m_pOwner->minimumDamageForDisplay(false,false,true);
  high=m_pOwner->maximumDamageForDisplay(false,false,false);baseHigh=m_pOwner->maximumDamageForDisplay(false,false,true);
  damage=rangeText(low,high);if(changed(m_DamageTexts[1],damage))textColour(m_DamageTexts[1],high,baseHigh);
  low=m_pOwner->minimumDamageForDisplay(false,true,false);int otherLow=m_pOwner->minimumDamageForDisplay(true,true,false);
  if(!low)low=otherLow;else if(otherLow && otherLow<low)low=otherLow;
  high=m_pOwner->maximumDamageForDisplay(false,true,false);int otherHigh=m_pOwner->maximumDamageForDisplay(true,true,false);if(otherHigh>high)high=otherHigh;
  baseHigh=m_pOwner->maximumDamageForDisplay(false,true,true);int otherBase=m_pOwner->maximumDamageForDisplay(true,true,true);if(otherBase>baseHigh)baseHigh=otherBase;
  damage=rangeText(low,high);if(changed(m_DamageTexts[2],damage))textColour(m_DamageTexts[2],high,baseHigh);
  tip=percentTip(m_DamageDescription,g_CritChance,m_pOwner->getCriticalChance());tooltip(m_DamageTexts[2],tip);
  int baseArmor=m_pOwner->baseAC();int armor=m_pOwner->AC();std::string armorMax=STRINGS::GetValueAsString(armor);
  std::string armorRange=STRINGS::GetValueAsString(m_pOwner->minimumAC())+"-"+armorMax;
  if(changed(m_pArmorText,armorRange))textColour(m_pArmorText,armor,baseArmor);
  static std::wstring g_BlockChance;if(g_BlockChance.empty())g_BlockChance=CStringTranslate::getSinglton()->getTranslateString(L"Block Chance");
  tip=percentTip(m_ArmorDescription,g_BlockChance,m_pOwner->getBlockChance());tooltip(m_pArmorText,tip);
  const int resistTypes[]={5,3,2,4};const unsigned resistWindows[]={0,1,3,2};
  for(unsigned i=0;i<4;++i)changed(m_ResistanceTexts[resistWindows[i]],STRINGS::GetValueAsString(m_pOwner->damageDefense(static_cast<EDAMAGE_TYPES>(resistTypes[i]))));
  static std::wstring g_PointsRemaining;if(g_PointsRemaining.empty())g_PointsRemaining=CStringTranslate::getSinglton()->getTranslateString(L"Points Remaining");
  CEGUI::String points=utf8(STRINGS::StringConvertToUTF8(g_PointsRemaining+L": "+STRINGS::GetValueAsWString(actor(m_pOwner).unusedPoints)));changed(m_pPointsText,points);
  static std::wstring g_MP;if(g_MP.empty())g_MP=CStringTranslate::getSinglton()->getTranslateString(L"MP");
  CEGUI::String mana=utf8(STRINGS::StringConvertToUTF8(g_MP+L": "+STRINGS::GetValueAsWString(m_pOwner->maxMana())));
  if(changed(m_pManaText,mana)) {
   int value=m_pOwner->maxMana();int base=actor(m_pOwner).baseMana;
   if(value<base)m_pManaText->setProperty("TextColour","FFFF0000");
   else {value=m_pOwner->maxMana();base=actor(m_pOwner).baseMana;m_pManaText->setProperty("TextColour",value>base?"FFc0c0ff":"FFFFFFFF");}
  }
  static std::wstring g_HP;if(g_HP.empty())g_HP=CStringTranslate::getSinglton()->getTranslateString(L"HP");
  CEGUI::String health=utf8(STRINGS::StringConvertToUTF8(g_HP+L": "+STRINGS::GetValueAsWString(m_pOwner->maxHP())));
  if(changed(m_pHealthText,health)) {
   int value=m_pOwner->maxHP();int base=actor(m_pOwner).baseHealth;
   if(value<base)m_pHealthText->setProperty("TextColour","FFFF0000");
   else {value=m_pOwner->maxHP();base=actor(m_pOwner).baseHealth;m_pHealthText->setProperty("TextColour",value>base?"FFc0c0ff":"FFFFFFFF");}
  }
 }
m_pModel->updateAnimation(elapsed,false);
m_pModel->getEntity()->_updateAnimation();
Ogre::Bone* top=m_pModel->m_pSkeleton->getBone("tag_topcharacter");
Ogre::Vector3 position=m_pModel->getPosition(false);
const Ogre::Vector3& tag=top->_getDerivedPosition();
float sumY=tag.y+position.y;
float scaledX=m_pGameUI->scaledY(tag.x+position.x);
float halfWidth=float(width)*0.5f;
float scaledY=m_pGameUI->scaledY(sumY);
float panelY=-(float(height)*-0.5f+scaledY);
m_pTopPanel->setPosition(CEGUI::UVector2(CEGUI::UDim(0,scaledX+halfWidth),CEGUI::UDim(0,panelY)));
Ogre::Bone* bottom=m_pModel->m_pSkeleton->getBone("tag_bottomcharacter");
position=m_pModel->getPosition(false);
float bottomX=bottom->_getDerivedPosition().x+position.x;
float bottomScaled=m_pGameUI->scaledY(bottomX);
m_pBottomPanel->setPosition(CEGUI::UVector2(CEGUI::UDim(0,bottomScaled+halfWidth),CEGUI::UDim(0,panelY)));
Ogre::Bone* right=m_pModel->m_pSkeleton->getBone("tag_bottomcharacterright");
position=m_pModel->getPosition(false);
float rightScaled=m_pGameUI->scaledY(right->_getDerivedPosition().x+position.x);
float margin=m_pGameUI->scaledY(50.0f);
float edge=(halfWidth+rightScaled)-margin;
// MAXSS returns the second operand (zero) for unordered inputs.
m_fScreenEdge=edge>0.0f?edge:0.0f;
if(!m_bOpenPartial && !m_bFullyClosed && !m_pModel->animationPlaying("CLOSE") && !m_pModel->animationQueued("CLOSE")) {
 m_pModel->setVisible(false);
 m_pParent->removeChildWindow(m_pRoot);
 m_bFullyClosed=true;
}

}

#include "FileSystem.h"
#include "Settings.h"
#include <OgreMesh.h>

// Original c16129/c16138 uses a hidden std::wstring result, then assign.
namespace STRINGS { std::wstring StringConvertUTF8ToWide(const std::string&); }

__attribute__((flatten)) void CStatsMenu::createMenus()
{
    float width = static_cast<float>(m_pProperties->GetInt(KSETTINGS_RES_WIDTH));
    float height = static_cast<float>(m_pProperties->GetInt(KSETTINGS_RES_HEIGHT));
    m_pModel = m_pResourceManager->createGenericModel(m_pSceneManager,
        L"media/ui/models/character/character.mesh", L"", false, false, false);
    m_pModel->generateExtremes(10, true);
    Ogre::AxisAlignedBox bounds(Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
                                Ogre::Vector3(100000.0f, 100000.0f, 100000.0f));
    m_pModel->getEntity()->getMesh()->_setBounds(bounds, true);
    float scale = width - height / 0.75f;
    scale /= m_pProperties->GetFloat(KSETTINGS_YRATIO);
    m_pModel->setPosition(-0.5f * scale, 0.0f, 0.0f);
    m_pModel->setVisible(false);
    CEGUI::ImagesetManager::getSingleton().getImageset(
        reinterpret_cast<const unsigned char*>("GuiLook"));
    m_pRoot = CEGUI::WindowManager::getSingleton().createWindow(
        reinterpret_cast<const unsigned char*>("DefaultWindow"),
        reinterpret_cast<const unsigned char*>("CharacterSheet"), "");
    m_pRoot->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
    m_pRoot->setProperty("RiseOnClick", "False");
    m_pRoot->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
    m_pRoot->setMousePassThroughEnabled(true);
    m_pRoot->setZOrderingEnabled(false);

    CFileInfo fileInfo;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/statsmenu.layout", fileInfo, false, true, false);
    CEGUI::Window* layoutRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout(
        CEGUI::String(fileInfo.m_sResourceName), true);
    m_pGameUI->convertToScreenScale(layoutRoot, false);
    m_pGameUI->mapToFunctions(layoutRoot);

    CEGUI::Window* blocker = layoutRoot->recursiveChildSearch("Blocker");
    blocker->getParent()->removeChildWindow(blocker);
    m_pRoot->addChildWindow(blocker);
    blocker->setProperty("RiseOnClick", "False");
    blocker->moveToBack();
    blocker->setZOrderingEnabled(false);

    CEGUI::Window* close = layoutRoot->recursiveChildSearch("Close");
    close->setRiseOnClickEnabled(false);
    close->moveToFront();
    {
        CEGUI::Event::Connection connection = close->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_CloseButton, this));
        (void)connection;
    }
    m_pNameText = layoutRoot->recursiveChildSearch("CharacterName");
    m_pFameTitleText = layoutRoot->recursiveChildSearch("CharacterTitle");
    m_pLevelText = layoutRoot->recursiveChildSearch("Level");
    m_pFameLevelText = layoutRoot->recursiveChildSearch("FameLevel");
    m_pExperienceText = layoutRoot->recursiveChildSearch("XP");
    m_pFameText = layoutRoot->recursiveChildSearch("Fame");
    m_pHealthText = layoutRoot->recursiveChildSearch("HP");
    m_pManaText = layoutRoot->recursiveChildSearch("Mana");
    m_pExperienceBar = layoutRoot->recursiveChildSearch("ExperienceBar");
    m_pFameBar = layoutRoot->recursiveChildSearch("FameBar");
    CEGUI::UVector2 fameSize = m_pFameBar->getSize();
    m_FameWidth = fameSize.d_x;
    m_FameHeight = fameSize.d_y;
    CEGUI::UVector2 experienceSize = m_pExperienceBar->getSize();
    m_ExperienceWidth = experienceSize.d_x;
    m_ExperienceHeight = experienceSize.d_y;
    m_AttributeTexts[0] = layoutRoot->recursiveChildSearch("Strength");
    m_AttributeTexts[1] = layoutRoot->recursiveChildSearch("Dexterity");
    m_AttributeTexts[2] = layoutRoot->recursiveChildSearch("Magic");
    m_AttributeTexts[3] = layoutRoot->recursiveChildSearch("Defense");
    m_DamageTexts[0] = layoutRoot->recursiveChildSearch("Melee Damage");
    m_TextA0 = STRINGS::StringConvertUTF8ToWide(std::string(m_DamageTexts[0]->getTooltipText().c_str()));
    m_DamageTexts[1] = layoutRoot->recursiveChildSearch("Ranged Damage");
    m_TextB0 = STRINGS::StringConvertUTF8ToWide(std::string(m_DamageTexts[1]->getTooltipText().c_str()));
    m_DamageTexts[2] = layoutRoot->recursiveChildSearch("Magic Damage");
    m_DamageDescription = STRINGS::StringConvertUTF8ToWide(std::string(m_DamageTexts[2]->getTooltipText().c_str()));
    m_pArmorText = layoutRoot->recursiveChildSearch("Damage Absorb");
    m_ArmorDescription = STRINGS::StringConvertUTF8ToWide(std::string(m_pArmorText->getTooltipText().c_str()));
    m_ResistanceTexts[0] = layoutRoot->recursiveChildSearch("Poison Resist");
    m_ResistanceTexts[3] = layoutRoot->recursiveChildSearch("Fire Resist");
    m_ResistanceTexts[1] = layoutRoot->recursiveChildSearch("Ice Resist");
    m_ResistanceTexts[2] = layoutRoot->recursiveChildSearch("Lightning Resist");
    m_pPointsText = layoutRoot->recursiveChildSearch("Stat Points");
    m_pPointsContainer = layoutRoot->recursiveChildSearch("SpendPoints");
    m_SpendButtons[0] = layoutRoot->recursiveChildSearch("SpendStrength");
    {
        CEGUI::Event::Connection connection = m_SpendButtons[0]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_SpendMelee, this));
        (void)connection;
    }
    m_SpendButtons[0]->setWantsMultiClickEvents(false);
    m_ReclaimButtons[0] = layoutRoot->recursiveChildSearch("ReclaimStrength");
    {
        CEGUI::Event::Connection connection = m_ReclaimButtons[0]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_ReclaimMelee, this));
        (void)connection;
    }
    m_ReclaimButtons[0]->setWantsMultiClickEvents(false);
    m_SpendButtons[1] = layoutRoot->recursiveChildSearch("SpendDexterity");
    {
        CEGUI::Event::Connection connection = m_SpendButtons[1]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_SpendRanged, this));
        (void)connection;
    }
    m_SpendButtons[1]->setWantsMultiClickEvents(false);
    m_ReclaimButtons[1] = layoutRoot->recursiveChildSearch("ReclaimDexterity");
    {
        CEGUI::Event::Connection connection = m_ReclaimButtons[1]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_ReclaimRanged, this));
        (void)connection;
    }
    m_ReclaimButtons[1]->setWantsMultiClickEvents(false);
    m_SpendButtons[2] = layoutRoot->recursiveChildSearch("SpendMagic");
    {
        CEGUI::Event::Connection connection = m_SpendButtons[2]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_SpendMagic, this));
        (void)connection;
    }
    m_SpendButtons[2]->setWantsMultiClickEvents(false);
    m_ReclaimButtons[2] = layoutRoot->recursiveChildSearch("ReclaimMagic");
    {
        CEGUI::Event::Connection connection = m_ReclaimButtons[2]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_ReclaimMagic, this));
        (void)connection;
    }
    m_ReclaimButtons[2]->setWantsMultiClickEvents(false);
    m_SpendButtons[3] = layoutRoot->recursiveChildSearch("SpendDefense");
    {
        CEGUI::Event::Connection connection = m_SpendButtons[3]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_SpendDefense, this));
        (void)connection;
    }
    m_SpendButtons[3]->setWantsMultiClickEvents(false);
    m_ReclaimButtons[3] = layoutRoot->recursiveChildSearch("ReclaimDefense");
    {
        CEGUI::Event::Connection connection = m_ReclaimButtons[3]->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStatsMenu::handle_ReclaimDefense, this));
        (void)connection;
    }
    m_ReclaimButtons[3]->setWantsMultiClickEvents(false);
    m_pBottomPanel = layoutRoot->recursiveChildSearch("BottomFrame");
    m_pBottomPanel->getParent()->removeChildWindow(m_pBottomPanel);
    m_pRoot->addChildWindow(m_pBottomPanel);
    m_pBottomPanel->setProperty("RiseOnClick", "False");
    m_pBottomPanel->moveToFront();
    m_pBottomPanel->setZOrderingEnabled(false);
    m_pTopPanel = layoutRoot->recursiveChildSearch("TopFrame");
    m_pTopPanel->getParent()->removeChildWindow(m_pTopPanel);
    m_pRoot->addChildWindow(m_pTopPanel);
    m_pTopPanel->setProperty("RiseOnClick", "False");
    m_pTopPanel->moveToFront();
    m_pTopPanel->setZOrderingEnabled(false);
}

void CStatsMenu::setOwner(CCharacter* owner)
{
    m_pOwner = owner;
}

bool CStatsMenu::handle_CloseButton(const CEGUI::EventArgs& args)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(args).button == CEGUI::LeftButton)
        m_bInputFlag = true;
    return true;
}

bool CStatsMenu::processInput(void*, float, bool active)
{
    if (active && m_bInputFlag) {
        setOpen(false);
        m_bInputFlag = false;
        return false;
    }
    return true;
}

#include "SoundBank.h"
namespace { typedef char stats_sound_offset[__builtin_offsetof(CStatsMenu,m_pSoundBank)==0x1b8?1:-1]; }
void CStatsMenu::setOpen(bool open)
{
    if (!m_bOpenPartial && open) {
        m_pProperties->GetInt(KSETTINGS_RES_WIDTH);
        m_pProperties->GetInt(KSETTINGS_RES_HEIGHT);
        m_pSoundBank->playSample(22, 0, 0.0f, 0.0f, false);
        m_pModel->setVisible(true);
        if (m_pModel->animationPlaying("CLOSE"))
            m_pModel->blendAnimation("OPEN", false, 0.1f, 2.0f, -1.0f);
        else
            m_pModel->playAnimation("OPEN", false, 2.0f, -1.0f);
        m_pModel->queueBlendAnimation("IDLE", true, 0.1f, 1.0f);
        m_pParent->addChildWindow(m_pRoot);
        m_pRoot->moveToBack();
    } else if (m_bOpenPartial && !open) {
        m_InvestedPoints[0] = 0;
        m_InvestedPoints[1] = 0;
        m_InvestedPoints[3] = 0;
        m_InvestedPoints[2] = 0;
        m_pSoundBank->playSample(66, 0, 0.0f, 0.0f, false);
        m_pModel->blendAnimation("CLOSE", false, 0.1f, 2.0f, -1.0f);
        m_bFullyClosed = false;
    }
    m_bOpenPartial = open;
}

#include "Inventory.h"

bool CStatsMenu::handle_ReclaimMelee(const CEGUI::EventArgs&)
{
    if (m_InvestedPoints[0] > 0) {
        --m_InvestedPoints[0];
        m_pOwner->reclaimMeleePoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
        m_pOwner->m_pInventory->verifyEquipment();
    }
    return true;
}

bool CStatsMenu::handle_SpendMelee(const CEGUI::EventArgs&)
{
    if (m_pOwner->m_iUnusedStatPoints > 0) {
        ++m_InvestedPoints[0];
        m_pOwner->spendMeleePoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
    }
    return true;
}

bool CStatsMenu::handle_ReclaimRanged(const CEGUI::EventArgs&)
{
    if (m_InvestedPoints[1] > 0) {
        --m_InvestedPoints[1];
        m_pOwner->reclaimRangedPoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
        m_pOwner->m_pInventory->verifyEquipment();
    }
    return true;
}

bool CStatsMenu::handle_SpendRanged(const CEGUI::EventArgs&)
{
    if (m_pOwner->m_iUnusedStatPoints > 0) {
        ++m_InvestedPoints[1];
        m_pOwner->spendRangedPoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
    }
    return true;
}

bool CStatsMenu::handle_ReclaimDefense(const CEGUI::EventArgs&)
{
    if (m_InvestedPoints[3] > 0) {
        --m_InvestedPoints[3];
        m_pOwner->reclaimDefensePoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
        m_pOwner->m_pInventory->verifyEquipment();
    }
    return true;
}

bool CStatsMenu::handle_SpendDefense(const CEGUI::EventArgs&)
{
    if (m_pOwner->m_iUnusedStatPoints > 0) {
        ++m_InvestedPoints[3];
        m_pOwner->spendDefensePoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
    }
    return true;
}

bool CStatsMenu::handle_ReclaimMagic(const CEGUI::EventArgs&)
{
    if (m_InvestedPoints[2] > 0) {
        --m_InvestedPoints[2];
        m_pOwner->reclaimMagicPoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
        m_pOwner->m_pInventory->verifyEquipment();
    }
    return true;
}

bool CStatsMenu::handle_SpendMagic(const CEGUI::EventArgs&)
{
    if (m_pOwner->m_iUnusedStatPoints > 0) {
        ++m_InvestedPoints[2];
        m_pOwner->spendMagicPoint();
        m_pSoundBank->playSample(27, 0, 0.0f, 0.0f, false);
        m_pGameUI->statsChanged();
    }
    return true;
}
