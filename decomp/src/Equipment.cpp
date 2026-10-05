#include "ItemSaveState.h"
#include "ParticlePreloader.h"
#include "Missile.h"
#include "MissilePreloader.h"
#include "GraphManager.h"
#include <algorithm>
#include "Skill.h"
#include "SkillManager.h"
#include <OgreMesh.h>
#include <OgreSubEntity.h>
#include <OgreTagPoint.h>
#include <OgreSceneManager.h>
#include "Particle.h"
#include "OgreUtilities.h"
#include <OgreEntity.h>
#include "LevelTemplateData.h"
#include <CEGUI.h>
#include "Settings.h"
#include "EmptyStrings.h"
#include "Equipment.h"
#include "EffectManager.h"
#include "Effect.h"
#include "DataGroup.h"
#include "Utilities.h"
#include "UtilitiesMath.h"
#include "Path.h"
#include "GenericModel.h"
#include "FileUtilities.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Character.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include <OgreLogManager.h>
#include "Level.h"
#include "AttackDescription.h"
#include "Set.h"
#include "Sets.h"
#include "Inventory.h"
#include "Affix.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "GameGlobals.h"
#include <OgreUTFString.h>
#include <cmath>

static const float KWeaponSpeedValues[] = {130.0f, 110.0f, 90.0f, 80.0f, 0.0f};

std::wstring CEquipment::getEquipmentStats()
{
    std::wstring result;
    static std::wstring g_PhysicalDamage;
    if (g_PhysicalDamage.empty())
        g_PhysicalDamage=CStringTranslate::getSinglton()->getTranslateString(L"Physical Damage");
    static std::wstring g_Damage;
    if (g_Damage.empty())
        g_Damage=CStringTranslate::getSinglton()->getTranslateString(L"Damage");
    static std::wstring g_Sockets;
    if (g_Sockets.empty())
        g_Sockets=CStringTranslate::getSinglton()->getTranslateString(L"Sockets");
    static std::wstring g_Set;
    if (g_Set.empty())
        g_Set=CStringTranslate::getSinglton()->getTranslateString(L"Set");

    if (ISA(UNITTYPES::WEAPON))
    {
        if (m_iMinimumDamage>0 && m_iMaximumDamage>0)
        {
            if (m_iMinimumDamage==m_iMaximumDamage)
                result=g_PhysicalDamage+L": "+STRINGS::GetValueAsWString(static_cast<int>(ceilf(m_iMaximumDamage*0.5f)))+L"-"+STRINGS::GetValueAsWString(m_iMinimumDamage);
            else
                result=g_PhysicalDamage+L": "+STRINGS::GetValueAsWString(m_iMinimumDamage)+L"-"+STRINGS::GetValueAsWString(m_iMaximumDamage);
        }
        if (m_bUnknown348)
        {
            for (int i=0;i<static_cast<int>(m_ElementalDamageTypes.size());++i)
            {
                int damage=m_InherentElementalDamage[i];
                if (damage!=0)
                {
                    float minimum=ceilf(damage*0.5f);
                    if (!result.empty()) result=result+L"\n";
                    result=result+CStringTranslate::getSinglton()->getTranslateString(gDAMAGE_TYPES[m_ElementalDamageTypes[i]].c_str())
                        +L" "+g_Damage+L": "+STRINGS::GetValueAsWString(static_cast<int>(minimum))+L"-"+STRINGS::GetValueAsWString(damage);
                }
            }
        }
        CAttackDescription* attack=m_pAttackDescriptionOverride ? m_pAttackDescriptionOverride : m_pAttackDescription;
        for (int i=0;i<5;++i)
        {
            if (KWeaponSpeedValues[i]<=attack->m_fAttackSpeed*100.0f)
            {
                if (!result.empty()) result=result+L"\n";
                result=result+getAttackSpeedString(static_cast<EWeaponSpeed>(i));
                break;
            }
        }
    }
    if (m_iSocketCount!=0)
    {
        if (!result.empty()) result=result+L"\n";
        result=result+g_Sockets+L" "+STRINGS::GetValueAsWString(m_SocketedEquipment.size())+L"/"+STRINGS::GetValueAsWString(m_iSocketCount);
    }

    std::wstring setName=getSet();
    static std::string g_SetPieces;
    if (g_SetPieces.empty())
        g_SetPieces=STRINGS::StringConvertToNarrow(CStringTranslate::getSinglton()->getTranslateString(L"pieces").c_str());
    if (setName!=EMPTY_WSTRING)
    {
        CSet* set=CSets::getSingleton()->getSet(setName.c_str());
        if (set!=NULL)
        {
            int equippedCount=m_pInventory ? m_pInventory->getSetCount(set) : 0;
            result=result+L"\n\n|c"+CGameGlobals::getSingleton()->getSetColor(true)+g_Set+L" : "+set->m_sDisplayName+L"|u";
            // The original groups active bonuses first and inactive bonuses second,
            // preserving list order in each group and re-reading the list after calls.
            for (int pass=0;pass<2;++pass)
            {
                if (pass==0 && equippedCount<=0) continue;
                for (unsigned int i=0;i<set->m_Affixes.size();++i)
                {
                    CSetAffix* bonus=set->m_Affixes[i];
                    if (pass==0 ? bonus->m_iRequiredCount<=equippedCount : equippedCount<bonus->m_iRequiredCount)
                    {
                        std::wstring description=bonus->m_pAffix->getDisplayStats(bonus->m_iLevel);
                        description=STRINGS::replaceWString(description,L"\n",L"\\n");
                        std::wstring continuation=(Ogre::UTFString(L"\n  "+STRINGS::GetValueAsWString(bonus->m_iRequiredCount)+L" ")
                            +Ogre::UTFString(g_SetPieces)+Ogre::UTFString(L" : ")).asWStr();
                        description=STRINGS::replaceWString(description,L"\\n",continuation);
                        result=(Ogre::UTFString(result+L"\n  |c"+CGameGlobals::getSingleton()->getSetColor(pass==0)
                            +STRINGS::GetValueAsWString(bonus->m_iRequiredCount)+L" ")+Ogre::UTFString(g_SetPieces)
                            +Ogre::UTFString(L" : ")+Ogre::UTFString(description)+Ogre::UTFString(L"|u")).asWStr();
                    }
                }
            }
        }
    }
    return result;
}

std::wstring CEquipment::getEquipmentDescription(bool showBuyPrice, bool showSellPrice)
{
    std::wstring result;
    static std::wstring g_Unidentified;
    if (g_Unidentified.empty()) g_Unidentified=CStringTranslate::getSinglton()->getTranslateString(L"Unidentified");
    static std::wstring g_Damage;
    if (g_Damage.empty()) g_Damage=CStringTranslate::getSinglton()->getTranslateString(L"Damage");
    static std::wstring g_Armor;
    if (g_Armor.empty()) g_Armor=CStringTranslate::getSinglton()->getTranslateString(L"Armor");
    static std::wstring g_Type;
    if (g_Type.empty()) g_Type=CStringTranslate::getSinglton()->getTranslateString(L"Type");
    static std::wstring g_Sockets;
    if (g_Sockets.empty()) g_Sockets=CStringTranslate::getSinglton()->getTranslateString(L"Sockets");
    static std::wstring g_BuyPrice;
    if (g_BuyPrice.empty()) g_BuyPrice=CStringTranslate::getSinglton()->getTranslateString(L"Buy Price");
    static std::wstring g_SellPrice;
    if (g_SellPrice.empty()) g_SellPrice=CStringTranslate::getSinglton()->getTranslateString(L"Sell Price");
    static std::wstring g_Unique;
    if (g_Unique.empty()) g_Unique=CStringTranslate::getSinglton()->getTranslateString(L"Unique");
    static std::wstring g_Rare;
    if (g_Rare.empty()) g_Rare=CStringTranslate::getSinglton()->getTranslateString(L"Rare");
    static std::wstring g_Enchanted;
    if (g_Enchanted.empty()) g_Enchanted=CStringTranslate::getSinglton()->getTranslateString(L"Enchanted");
    if (!m_bUnknown348)
    {
        result=g_Unidentified+L" ";
        result=result+getItemName();
    }
    else result=getItemName();
    if (m_bUnknown348 && m_pEffectManager)
    {
        std::wstring prefix=m_sPrefix, suffix=m_sSuffix;
        int rank=-1;
        for (unsigned int i=0;i<m_pEffectManager->getAffixes().size();++i)
        {
            CAffix* affix=m_pEffectManager->getAffixes()[i];
            if (affix->m_iRank>rank && affix->m_sPrefix!=EMPTY_WSTRING)
            {
                prefix=affix->m_sPrefix.c_str();
                rank=affix->m_iRank;
            }
            // Original suffix selection tests against zero and updates the same
            // rank as prefix selection, even when the suffix rank is lower.
            if (affix->m_iRank>=0 && affix->m_sSuffix!=EMPTY_WSTRING)
            {
                suffix=affix->m_sSuffix.c_str();
                rank=affix->m_iRank;
            }
        }
        if (prefix!=EMPTY_WSTRING) {result=prefix+L" "+result;m_sPrefix=prefix;}
        if (suffix!=EMPTY_WSTRING) {result=result+L" "+suffix;m_sSuffix=suffix;}
    }
    if (m_iSocketCount!=0)
        result=result+L"\n"+g_Sockets+L": "+STRINGS::GetValueAsWString(m_SocketedEquipment.size())+L"/"+STRINGS::GetValueAsWString(m_iSocketCount);
    if (showBuyPrice) result=result+L"\n"+g_BuyPrice+L": "+STRINGS::GetValueAsWString(buyPrice());
    if (showSellPrice) result=result+L"\n"+g_SellPrice+L": "+STRINGS::GetValueAsWString(sellPrice());
    int category=0;
    if (ISA(UNITTYPES::WEAPON)) category=1;
    else if (ISA(UNITTYPES::ARMOR)) category=2;
    else if (ISA(UNITTYPES::TRINKET)) category=3;
    else if (ISA(UNITTYPES::POTION)) category=4;
    else if (ISA(UNITTYPES::SCROLL)) category=5;
    if (category>=1 && category<=3)
    {
        if (category==3)
            result=result+L"\n"+CStringTranslate::getSinglton()->getTranslateString(g_Type)+L": ";
        else result=result+L"\n"+g_Type+L": ";
        if (m_bUnknown348)
        {
            if (ISA(UNITTYPES::UNIQUE)) result=result+g_Unique+L" ";
            else if (ISA(UNITTYPES::MAGIC)) result=result+g_Rare+L" ";
            else if (isMagical()) result=result+g_Enchanted+L" ";
        }
        if (category==1)
        {
            if (ISA(UNITTYPES::SWORD))
            {
                static std::wstring g_Sword;
                if (g_Sword.empty()) g_Sword=CStringTranslate::getSinglton()->getTranslateString(L"Sword");
                result=result+g_Sword;
            }
            else if (ISA(UNITTYPES::BOW))
            {
                static std::wstring g_Bow;
                if (g_Bow.empty()) g_Bow=CStringTranslate::getSinglton()->getTranslateString(L"Bow");
                result=result+g_Bow;
            }
            else if (ISA(UNITTYPES::AXE))
            {
                static std::wstring g_Axe;
                if (g_Axe.empty()) g_Axe=CStringTranslate::getSinglton()->getTranslateString(L"Axe");
                result=result+g_Axe;
            }
            else
            {
                static std::wstring g_Weapon;
                if (g_Weapon.empty()) g_Weapon=CStringTranslate::getSinglton()->getTranslateString(L"Weapon");
                result=result+g_Weapon;
            }
            if (m_iMinimumDamage!=0 && m_iMaximumDamage!=0)
            {
                if (m_iMinimumDamage==m_iMaximumDamage)
                    result=result+L"\n"+g_Damage+L": "+STRINGS::GetValueAsWString(m_iMinimumDamage);
                else result=result+L"\n"+g_Damage+L": "+STRINGS::GetValueAsWString(m_iMinimumDamage)+L"-"+STRINGS::GetValueAsWString(m_iMaximumDamage);
            }
            CAttackDescription* attack=m_pAttackDescriptionOverride ? m_pAttackDescriptionOverride : m_pAttackDescription;
            for (int i=0;i<5;++i)
                if (KWeaponSpeedValues[i]<=attack->m_fAttackSpeed*100.0f)
                { result=result+L"\n"+getAttackSpeedString(static_cast<EWeaponSpeed>(i));break; }
            if (m_bUnknown348)
                for (int i=0;i<static_cast<int>(m_ElementalDamageTypes.size());++i)
                    if (m_InherentElementalDamage[i]>0)
                    {
                        std::wstring damageType=CStringTranslate::getSinglton()->getTranslateString(gDAMAGE_TYPES[m_ElementalDamageTypes[i]].c_str());
                        result=result+L"\n+"+STRINGS::GetValueAsWString(m_InherentElementalDamage[i])+L" "+damageType+L" "+g_Damage;
                    }
        }
        else if (category==2)
        {
            result=result+g_Armor;
            int baseArmor=m_iUnknown338;
            float percent=ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(0x17),0.0f,static_cast<EDAMAGE_TYPES>(7))*baseArmor/100.0f);
            float flat=ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(8),0.0f,static_cast<EDAMAGE_TYPES>(7)));
            int armor=baseArmor+static_cast<int>(percent)+static_cast<int>(flat);
            result=result+L"\n"+g_Armor+L": "+STRINGS::GetValueAsWString(armor);
            if (armor!=m_iUnknown338) result=result+L"*";
        }
        else
        {
            static std::wstring g_Trinket;
            if (g_Trinket.empty()) g_Trinket=CStringTranslate::getSinglton()->getTranslateString(L"Trinket");
            result=result+g_Trinket;
        }
    }
    else if (category==4)
    {
        static std::wstring g_Potion;
        if (g_Potion.empty()) g_Potion=CStringTranslate::getSinglton()->getTranslateString(L"Potion");
        result=result+L"\n"+g_Type+L":"+g_Potion;
    }
    else if (category==5)
    {
        static std::wstring g_Scroll;
        if (g_Scroll.empty()) g_Scroll=CStringTranslate::getSinglton()->getTranslateString(L"Scroll");
        result=result+L"\n"+g_Type+L":"+g_Scroll;
    }
    if (m_iUnknown278!=0)
    {
        static std::wstring g_RequiresLevel;
        if (g_RequiresLevel.empty()) g_RequiresLevel=CStringTranslate::getSinglton()->getTranslateString(L"Requires Level");
        result=result+L"\n\n"+g_RequiresLevel+L": "+STRINGS::GetValueAsWString(getLevelRequirement(getLevel()->getPlayer()));
    }
    if (m_bUnknown348)
    {
        std::wstring effects=getEquipmentEffects();
        if (effects.compare(L"")!=0) result=result+L"\n"+effects;
    }
    if (result!=EMPTY_WSTRING)
        while (result[result.size()-1]==L'\n') result=result.substr(0,result.size()-1);
    return result;
}

std::wstring CEquipment::getEquipmentType(bool showQuality)
{
    std::wstring result;
    static std::wstring g_Unidentified;
    if (g_Unidentified.empty()) g_Unidentified=CStringTranslate::getSinglton()->getTranslateString(L"Unidentified");
    static std::wstring g_Unique;
    if (g_Unique.empty()) g_Unique=CStringTranslate::getSinglton()->getTranslateString(L"Unique");
    static std::wstring g_Rare;
    if (g_Rare.empty()) g_Rare=CStringTranslate::getSinglton()->getTranslateString(L"Rare");
    static std::wstring g_Enchanted;
    if (g_Enchanted.empty()) g_Enchanted=CStringTranslate::getSinglton()->getTranslateString(L"Enchanted");
    static std::wstring g_QuestItem;
    if (g_QuestItem.empty()) g_QuestItem=CStringTranslate::getSinglton()->getTranslateString(L"(Quest Item)");
    if (getIsQuestUnit()) result=g_QuestItem;
    int category=0;
    if (ISA(UNITTYPES::WEAPON)) category=1;
    else if (ISA(UNITTYPES::ARMOR)) category=2;
    else if (ISA(UNITTYPES::SOCKETABLE)) category=3;
    else if (ISA(UNITTYPES::TRINKET)) category=4;
    else if (ISA(UNITTYPES::POTION)) category=5;
    else if (ISA(UNITTYPES::SCROLL)) category=6;
    if (category==1 || category==2 || category==4)
    {
        if (!m_bUnknown348) result=result+g_Unidentified+L" ";
        else if (showQuality)
        {
            if (ISA(UNITTYPES::UNIQUE)) result=result+g_Unique+L" ";
            else if (ISA(UNITTYPES::MAGIC)) result=result+g_Rare+L" ";
            else if (isMagical()) result=result+g_Enchanted+L" ";
        }
    }
    if (category==1)
    {
        if (ISA(UNITTYPES::SWORD))
        {
            static std::wstring g_Sword;
            if (g_Sword.empty()) g_Sword=CStringTranslate::getSinglton()->getTranslateString(L"Sword");
            result=result+g_Sword;
        }
        else if (ISA(UNITTYPES::BOW))
        {
            static std::wstring g_Bow;
            if (g_Bow.empty()) g_Bow=CStringTranslate::getSinglton()->getTranslateString(L"Bow");
            result=result+g_Bow;
        }
        else if (ISA(UNITTYPES::AXE))
        {
            static std::wstring g_Axe;
            if (g_Axe.empty()) g_Axe=CStringTranslate::getSinglton()->getTranslateString(L"Axe");
            result=result+g_Axe;
        }
        else if (ISA(UNITTYPES::MACE))
        {
            static std::wstring g_Mace;
            if (g_Mace.empty()) g_Mace=CStringTranslate::getSinglton()->getTranslateString(L"Mace");
            result=result+g_Mace;
        }
        else if (ISA(UNITTYPES::POLEARM))
        {
            static std::wstring g_Polearm;
            if (g_Polearm.empty()) g_Polearm=CStringTranslate::getSinglton()->getTranslateString(L"Polearm");
            result=result+g_Polearm;
        }
        else if (ISA(UNITTYPES::STAFF))
        {
            static std::wstring g_Staff;
            if (g_Staff.empty()) g_Staff=CStringTranslate::getSinglton()->getTranslateString(L"Staff");
            result=result+g_Staff;
        }
        else if (ISA(UNITTYPES::PISTOL))
        {
            static std::wstring g_Pistol;
            if (g_Pistol.empty()) g_Pistol=CStringTranslate::getSinglton()->getTranslateString(L"Pistol");
            result=result+g_Pistol;
        }
        else if (ISA(UNITTYPES::RIFLE))
        {
            static std::wstring g_Rifle;
            if (g_Rifle.empty()) g_Rifle=CStringTranslate::getSinglton()->getTranslateString(L"Rifle");
            result=result+g_Rifle;
        }
        else if (ISA(UNITTYPES::CROSSBOW))
        {
            static std::wstring g_Crossbow;
            if (g_Crossbow.empty()) g_Crossbow=CStringTranslate::getSinglton()->getTranslateString(L"Crossbow");
            result=result+g_Crossbow;
        }
        else if (ISA(UNITTYPES::WAND))
        {
            static std::wstring g_Wand;
            if (g_Wand.empty()) g_Wand=CStringTranslate::getSinglton()->getTranslateString(L"Wand");
            result=result+g_Wand;
        }
        else
        {
            static std::wstring g_Weapon;
            if (g_Weapon.empty()) g_Weapon=CStringTranslate::getSinglton()->getTranslateString(L"Weapon");
            result=result+g_Weapon;
        }
    }
    else if (category==2)
    {
        if (ISA(UNITTYPES::HELMET))
        {
            static std::wstring g_Helmet;
            if (g_Helmet.empty()) g_Helmet=CStringTranslate::getSinglton()->getTranslateString(L"Helmet");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Helmet");
        }
        else if (ISA(UNITTYPES::GLOVES))
        {
            static std::wstring g_Gloves;
            if (g_Gloves.empty()) g_Gloves=CStringTranslate::getSinglton()->getTranslateString(L"Gloves");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Gloves");
        }
        else if (ISA(UNITTYPES::BOOTS))
        {
            static std::wstring g_Boots;
            if (g_Boots.empty()) g_Boots=CStringTranslate::getSinglton()->getTranslateString(L"Boots");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Boots");
        }
        else if (ISA(UNITTYPES::BELT))
        {
            static std::wstring g_Belt;
            if (g_Belt.empty()) g_Belt=CStringTranslate::getSinglton()->getTranslateString(L"Belt");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Belt");
        }
        else if (ISA(UNITTYPES::CHEST_ARMOR))
        {
            static std::wstring g_ChestArmor;
            if (g_ChestArmor.empty()) g_ChestArmor=CStringTranslate::getSinglton()->getTranslateString(L"Chest Armor");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Chest Armor");
        }
        else if (ISA(UNITTYPES::SHOULDER_ARMOR))
        {
            static std::wstring g_ShoulderArmor;
            if (g_ShoulderArmor.empty()) g_ShoulderArmor=CStringTranslate::getSinglton()->getTranslateString(L"Shoulder Armor");
            result=result+g_ShoulderArmor;
        }
        else if (ISA(UNITTYPES::SHIELD))
        {
            static std::wstring g_Shield;
            if (g_Shield.empty()) g_Shield=CStringTranslate::getSinglton()->getTranslateString(L"Shield");
            result=result+CStringTranslate::getSinglton()->getTranslateString(L"Shield");
        }
        else
        {
            static std::wstring g_Armor;
            if (g_Armor.empty()) g_Armor=CStringTranslate::getSinglton()->getTranslateString(L"Armor");
            result=result+g_Armor;
        }
    }
    else if (category==3)
    {
        static std::wstring g_Socketable;
        if (g_Socketable.empty()) g_Socketable=CStringTranslate::getSinglton()->getTranslateString(L"Socketable");
        result=g_Socketable;
    }
    else if (category==4)
    {
        static std::wstring g_Trinket;
        if (g_Trinket.empty()) g_Trinket=CStringTranslate::getSinglton()->getTranslateString(L"Trinket");
        result=result+g_Trinket;
    }
    else if (category==5)
    {
        static std::wstring g_Potion;
        if (g_Potion.empty()) g_Potion=CStringTranslate::getSinglton()->getTranslateString(L"Potion");
        result=g_Potion;
    }
    else if (category==6)
    {
        static std::wstring g_Scroll;
        if (g_Scroll.empty()) g_Scroll=CStringTranslate::getSinglton()->getTranslateString(L"Scroll");
        result=g_Scroll;
    }
    int start=static_cast<int>(result.find(L"{"));
    int end=static_cast<int>(result.find(L"}",start));
    if (end!=-1 && start!=-1 && start+1<end)
        result.replace(start,end-start+1,L"");
    return result;
}

void CEquipment::calculateCombatStats(bool skipArmorEffects)
{
    m_iMinimumDamage=m_pDataGroup->GetDataValue(L"MINDAMAGE",0);
    m_iMaximumDamage=m_pDataGroup->GetDataValue(L"MAXDAMAGE",0);
    float range=m_pDataGroup->GetDataValue(L"RANGE",0.45f);
    float strikeRange=m_pDataGroup->GetDataValue(L"STRIKERANGE",0.6f);
    int toHit=m_pDataGroup->GetDataValue(L"TOHIT",0);
    m_sUnknown400=STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"MISSILE",EMPTY_WSTRING));
    m_fUnknown408=m_pDataGroup->GetDataValue(L"AI_ATTACKCOOLDOWN",0.0f);
    int speed=m_pDataGroup->GetDataValue(L"SPEED",100);
    int armorRarity=m_pDataGroup->GetDataValue(L"RARITY_AMR_MOD",100);
    int armorSpecial=m_pDataGroup->GetDataValue(L"SPECIAL_AMR_MOD",100);
    m_iUnknown338=m_pDataGroup->GetDataValue(L"ARMOR",0);
    int armorMinimum=m_pDataGroup->GetDataValue(L"ARMORMIN",0);
    int armorMaximum=m_pDataGroup->GetDataValue(L"ARMORMAX",0);
    if (m_iUnknown338!=0)
        setGraphAC(static_cast<int>(m_iUnknown338*(armorRarity/100.0f)*(armorSpecial/100.0f)));
    else if (armorMaximum!=0 && armorMinimum!=0)
    {
        int armor=UTILITIES::randomIntegerBetweenVolatile(armorMinimum,armorMinimum>armorMaximum?armorMinimum:armorMaximum);
        setGraphAC(static_cast<int>(armor*(armorRarity/100.0f)*(armorSpecial/100.0f)));
    }
    int damageRarity=m_pDataGroup->GetDataValue(L"RARITY_DMG_MOD",100);
    int damageSpeed=m_pDataGroup->GetDataValue(L"SPEED_DMG_MOD",100);
    if (m_iMaximumDamage!=0)
    {
        int damage=UTILITIES::randomIntegerBetweenVolatile(m_iMinimumDamage,m_iMaximumDamage);
        if (m_iUnknown28C>0) damage=m_iMaximumDamage;
        setGraphDamage(static_cast<int>(damage*(damageRarity/100.0f)*(damageSpeed/100.0f)));
    }
    if (ISA(UNITTYPES::ARMOR))
    {
        float armor=m_iUnknown338;
        if (!skipArmorEffects)
        {
            static const wchar_t* const keys[]={L"ARMOR_ELECTRIC",L"ARMOR_FIRE",L"ARMOR_ICE",L"ARMOR_POISON"};
            static const int types[]={39,37,38,40};
            for (unsigned int i=0;i<4;++i)
            {
                int percent=m_pDataGroup->GetDataValue(keys[i],0);
                if (percent>0)
                    addNewEffect(new CEffect(static_cast<EEFFECT_TYPE>(types[i]),true,EFFECT_ACTIVATION_PASSIVE,-1000.0f,(percent/100.0f)*armor,1.0f,false));
            }
        }
        int physical=m_pDataGroup->GetDataValue(L"ARMOR_PHYSICAL",-1);
        if (physical!=-1)
        {
            m_iUnknown338=static_cast<int>((physical/100.0f)*armor);
            if (m_iUnknown338<1) m_iUnknown338=1;
            m_iUnknown33C=m_iUnknown338;
        }
    }
    for (unsigned int i=0;i<m_ElementalDamageTypes.size();++i) m_InherentElementalDamage[i]=0;
    destroyItemText();
    if (ISA(UNITTYPES::WEAPON))
    {
        float damage=m_iMaximumDamage/100.0f;
        static const wchar_t* const keys[]={L"DAMAGE_ELECTRIC",L"DAMAGE_FIRE",L"DAMAGE_ICE",L"DAMAGE_POISON"};
        static const EDAMAGE_TYPES types[]={DAMAGE_ELECTRIC,DAMAGE_FIRE,DAMAGE_ICE,DAMAGE_POISON};
        for (unsigned int i=0;i<4;++i)
        {
            int percent=m_pDataGroup->GetDataValue(keys[i],0);
            if (percent>0) addInherentDamage(types[i],static_cast<int>(percent*damage));
        }
        int physical=m_pDataGroup->GetDataValue(L"DAMAGE_PHYSICAL",-1);
        if (physical>=0) m_iMaximumDamage=static_cast<int>(physical*damage);
        m_iMinimumDamage=m_iMaximumDamage;
        m_iUnknown340=m_iMaximumDamage;
        if (m_pAttackDescriptionOverride) {delete m_pAttackDescriptionOverride;m_pAttackDescriptionOverride=NULL;}
        if (m_pAttackDescription) {delete m_pAttackDescription;m_pAttackDescription=NULL;}
        float attackSpeed=speed/100.0f;
        if (ISA(UNITTYPES::BOW))
            m_pAttackDescriptionOverride=new CAttackDescription("BOW",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        else if (ISA(UNITTYPES::CROSSBOW))
            m_pAttackDescription=new CAttackDescription("CROSSBOW",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        else if (ISA(UNITTYPES::RIFLE))
            m_pAttackDescription=new CAttackDescription("RIFLE",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        else if (ISA(UNITTYPES::PISTOL))
        {
            m_pAttackDescription=new CAttackDescription("RPISTOL",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
            m_pAttackDescriptionOverride=new CAttackDescription("LPISTOL",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        }
        else if (ISA(UNITTYPES::WAND))
        {
            m_pAttackDescription=new CAttackDescription("RWAND",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
            m_pAttackDescriptionOverride=new CAttackDescription("LWAND",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        }
        else if (ISA(UNITTYPES::POLEARM) || ISA(UNITTYPES::STAFF))
            m_pAttackDescription=new CAttackDescription("POLEARM",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        else
        {
            m_pAttackDescription=new CAttackDescription("RSLASH",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
            m_pAttackDescriptionOverride=new CAttackDescription("LSLASH",true,range,strikeRange,m_iMinimumDamage,m_iMaximumDamage,toHit,attackSpeed);
        }
    }
}

void CEquipment::unitInit(CDataGroup* data,bool skipEffects)
{
    if (!data) return;
    CItem::unitInit(data,skipEffects);
    m_sUnidentifiedName=m_pDataGroup->GetDataValue(L"UNIDENTIFIED_NAME",EMPTY_WSTRING);
    int start=static_cast<int>(m_sUnidentifiedName.find(L"{"));
    int end=static_cast<int>(m_sUnidentifiedName.find(L"}",start));
    if (end!=-1 && start!=-1 && start+1<end) m_sUnidentifiedName.replace(start,end-start+1,L"");
    m_sDisplayName=m_pDataGroup->GetDataValue(L"NAME",EMPTY_WSTRING);
    m_sDisplayName=m_pDataGroup->GetDataValue(L"DISPLAYNAME",m_sDisplayName);
    start=static_cast<int>(m_sDisplayName.find(L"{"));
    end=static_cast<int>(m_sDisplayName.find(L"}",start));
    if (end!=-1 && start!=-1 && start+1<end) m_sDisplayName.replace(start,end-start+1,L"");
    std::wstring mesh=data->GetDataValue(L"MESHFILE",EMPTY_WSTRING);
    if (mesh==EMPTY_WSTRING)
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow((L"No model created for equipment "+getName()).c_str()),Ogre::LML_NORMAL);
    else
    {
        std::wstring path=data->GetDataValue(L"RESOURCEDIRECTORY",EMPTY_WSTRING);
        path=FILESYSTEM::CleanPath(path+L"/"+mesh+L".mesh");
        CGameClient* client=m_pResourceManager->getGameClient();
        if (client && client->getGameUI() && client->getGameUI()->getCharacter())
        {
            std::wstring playerClass=STRINGS::StringUpper(client->getGameUI()->getCharacter()->getName());
            std::vector<CDataGroup*> wardrobes;
            unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"WARDROBE",&wardrobes);
            for (unsigned int i=0;i<count;++i)
            {
                std::wstring wardrobeClass=STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""));
                if (playerClass.compare(L"")==0 || wardrobeClass==playerClass)
                    if (wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING)!=EMPTY_WSTRING)
                        path=wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING);
            }
        }
        loadModel(path,EMPTY_WSTRING);
    }
    std::wstring uses=STRINGS::StringUpper(data->GetDataValue(L"USES",L"0"));
    m_iUnknown248=uses.compare(L"UNLIMITED")==0 ? -9999 : STRINGS::GetInt(uses);
    std::wstring target=STRINGS::StringUpper(data->GetDataValue(L"TARGET_TYPE",L"USER"));
    for (unsigned int i=0;i<2;++i)
        if (target==STRINGS::StringUpper(gTARGET_TYPES[i])) {m_iUnknown260=i;break;}
    m_bUnknown25F=data->GetDataValue(L"MERCHANTINFINITE",m_bUnknown25F);
    m_iUnknown23C=data->GetDataValue(L"MAXSTACKSIZE",1);
    m_sUnknown3D8=STRINGS::StringUpper(data->GetDataValue(L"DROPPARTICLE",EMPTY_WSTRING));
    m_sUnknown3D8=FILESYSTEM::CleanPath(m_sUnknown3D8);
    m_iUnknown274=data->GetDataValue(L"LEVEL",1);
    int sockets=data->GetDataValue(L"SOCKETS",0);
    m_iSocketCount=sockets<2 ? sockets : 2;
    int blockChance=data->GetDataValue(L"BLOCK_CHANCE",0);
    if (!skipEffects && static_cast<float>(blockChance)!=0.0f)
        addNewEffect(new CEffect(static_cast<EEFFECT_TYPE>(62),static_cast<float>(blockChance)>0.0f,EFFECT_ACTIVATION_PASSIVE,-1000.0f,static_cast<float>(blockChance),1.0f,false));
    calculateCombatStats(skipEffects);
    setRequirements();
    if (!skipEffects)
    {
        if (ISA(UNITTYPES::UNIQUE)) m_bUnknown348=false;
        enchant(false);
        if (ISA(UNITTYPES::SOCKETABLE) || (!m_bUnknown348 && m_pDataGroup->GetDataValue(L"ALWAYS_IDENTIFIED",false))) m_bUnknown348=true;
    }
    if (m_pEffectManager) m_pEffectManager->calculateEffectValues();
    createElementalDamages();
    recalculatePrice();
    if (!m_pSoundBank)
    {
        CSoundManager* manager=m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSoundManager : NULL;
        m_pSoundBank=new CSoundBank(*manager,false);
    }
    CSoundBankDataInformation* sounds=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    static const wchar_t* const keys[]={L"FALL_SOUND",L"LAND_SOUND",L"TAKE_SOUND",L"ATTACK_SOUND",L"STRIKE_SOUND",L"USE_SOUND"};
    static const int slots[]={16,17,18,10,1,20};
    for (unsigned int i=0;i<6;++i)
    {
        std::wstring name=m_pDataGroup->GetDataValue(keys[i],EMPTY_WSTRING);
        CSoundData* sound=sounds->getSoundDataObject(STRINGS::StringUpper(name));
        if (sound) m_pSoundBank->addSample(slots[i],sound->m_iGuid);
    }
    std::wstring layout=data->GetDataValue(L"ATTACHEDLAYOUT",L"");
    if (!layout.empty()) m_bUnknown430=true;
}

void CEquipment::drop()
{
    if (!getLevel()) return;
    float angle=UTILITIES::randomBetweenVolatile(0.0f,360.0f);
    m_mOrientation=Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 rotation;
    if (ISA(UNITTYPES::CROSSBOW))
    {
        MATH::matrixRotationX(rotation,-1.2217305f);
        m_mOrientation=m_mOrientation*rotation;
    }
    else if (ISA(UNITTYPES::WEAPON))
    {
        MATH::matrixRotationZ(rotation,1.5707964f);
        m_mOrientation=m_mOrientation*rotation;
    }
    else if (ISA(UNITTYPES::SHIELD))
    {
        MATH::matrixRotationZ(rotation,-1.5707964f);
        m_mOrientation=m_mOrientation*rotation;
    }
    else if ((ISA(UNITTYPES::SHOULDER_ARMOR) || ISA(UNITTYPES::HELMET)) && m_pUnitModel)
    {
        m_pUnitModel->setPosition(0.0f,0.0f,0.0f);
        m_pUnitModel->setOrientation(Ogre::Matrix4::IDENTITY,false);
    }
    MATH::matrixRotationY(rotation,angle*0.017453292f);
    m_mOrientation=rotation*m_mOrientation;
    m_mDropOrientation=m_mOrientation;
    setOrientation(m_mOrientation,false);
    if (!m_bUnknown25E)
    {
        Ogre::Vector3 destination=getLevel()->randomOpenItemPosition(m_vPosition,1.0f,false);
        destination.y=getLevel()->floorHeight(destination)+0.01f;
        if (ISA(UNITTYPES::WEAPON)) destination.y+=0.05f;
        m_pSoundBank->playSample(16,m_pSceneNode,0.0f,0.0f,false);
        setPosition(destination);
    }
    else
    {
        m_pSoundBank->playSample(16,m_pSceneNode,0.0f,0.0f,false);
        Ogre::Vector3 destination=getLevel()->randomOpenItemPosition(m_vPosition,1.5f,false);
        destination.y=getLevel()->floorHeight(destination)+0.01f;
        if (ISA(UNITTYPES::WEAPON)) destination.y+=0.05f;
        if (!m_pPath) m_pPath=new CPath("DROP",false,Ogre::Vector3(0.0f,0.0f,0.0f));
        m_pPath->Clear();
        setEnabled(false);
        m_bUnknown25C=true;
        m_fUnknown258=0.0f;
        Ogre::Vector3 middle((destination.x+m_vPosition.x)*0.5f,
                             (destination.y+m_vPosition.y)*0.5f,
                             (destination.z+m_vPosition.z)*0.5f);
        float middleHeight=middle.y;
        middle.y=UTILITIES::randomBetweenVolatile(3.5f,4.5f);
        middle.y+=middleHeight;
        m_pPath->AddPoint(m_vPosition,-60.0f,60.0f);
        m_pPath->AddPoint(middle,-60.0f,60.0f);
        m_pPath->AddPoint(destination,-60.0f,60.0f);
    }
    if (getUnitModel())
    {
        m_fOpacity=1.0f;
        updateOpacity(0.0f,true);
        static_cast<CGenericModel*>(getUnitModel())->setOpacity(1.0f);
        m_bItemFlag218=false;
        setVisible(true,true);
    }
    setRenderBehind(true);
}

std::wstring CEquipment::effectsDescription(EEFFECT_ACTIVATION activation,bool embedded,bool socketedOnly)
{
    static std::wstring g_Damage;
    if (g_Damage.empty()) g_Damage=CStringTranslate::getSinglton()->getTranslateString(L"Damage");
    std::wstring result(L"");
    if (!socketedOnly)
    {
        if (activation==EFFECT_ACTIVATION_PASSIVE)
            for (unsigned int i=0;i<m_ElementalDamageTypes.size();++i)
                if (m_ElementalDamageBonuses[i]>0)
                {
                    std::wstring type=CStringTranslate::getSinglton()->getTranslateString(gDAMAGE_TYPES[m_ElementalDamageTypes[i]].c_str());
                    result=result+L"+"+STRINGS::GetValueAsWString(m_ElementalDamageBonuses[i])+L" "+type+L" "+g_Damage;
                    if (i!=m_ElementalDamageTypes.size()-1) result=result+L"\n";
                }
        if (m_pEffectManager)
        {
            bool socketableFilter=false;
            if (!embedded) socketableFilter=ISA(UNITTYPES::SOCKETABLE) && !ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE);
            const std::wstring& description=m_pEffectManager->getVisualDescription(activation,static_cast<unsigned int>(-1),true,socketableFilter);
            if (description!=EMPTY_WSTRING)
            {
                if (result==EMPTY_WSTRING) result=description;
                else result=result+L"\n"+description;
            }
        }
    }
    else
    {
        int count=m_SocketedEquipment.size();
        std::wstring sockets=EMPTY_WSTRING;
        for (unsigned int i=0;static_cast<int>(i)<count;++i)
        {
            std::wstring description=m_SocketedEquipment[i]->effectsDescription(activation,true,false);
            if (description!=EMPTY_WSTRING)
            {
                if (!sockets.empty() && sockets[sockets.size()-1]!=L'\n') sockets=sockets+L"\n";
                sockets=sockets+description;
            }
            if (!sockets.empty() && sockets[sockets.size()-1]==L'\n') sockets=sockets.substr(0,sockets.size()-1);
        }
        if (!sockets.empty())
        {
            if (result.empty() || result[result.size()-1]!=L'\n') result=result+L"\n";
            result=result+L"|c"+CGameGlobals::getSingleton()->getSocketedEffectColor()+sockets+L"|u";
        }
    }
    if (!result.empty() && result[result.size()-1]!=L'\n') result.append(L"\n");
    return result;
}

std::wstring CEquipment::getEquipmentEffects()
{
    std::wstring result;
    if (!m_bUnknown348) return result;
    result=result+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false));
    // These returned copies are discarded in the original as well.
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,false));
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_TRANSFER,false,false));
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,true));
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,true));
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_TRANSFER,false,true));
    removeWhiteSpace(result);
    result=result+L"\n"+removeWhiteSpace(skillDescription());
    removeWhiteSpace(result);
    if (!result.empty()) result=result+L"\n";
    return result;
}

std::wstring CEquipment::getFullItemName(bool forceIdentified)
{
    if (!forceIdentified && !m_bUnknown348 && !m_sUnidentifiedName.empty())
        return m_sUnidentifiedName;
    std::wstring name=m_sItemName;
    int begin=name.find(L"{"), end=name.find(L"}",begin);
    std::wstring tag=EMPTY_WSTRING;
    if (end!=-1 && begin!=-1 && begin+1<end)
    {
        tag=STRINGS::StringUpper(name.substr(begin,end-begin+1));
        name.replace(begin,end-begin+1,L"");
        tag=tag.substr(1,end-begin-1);
    }
    if ((forceIdentified || m_bUnknown348) && !ISA(UNITTYPES::UNIQUE)
        && getSet().empty() && m_pEffectManager)
    {
        std::wstring prefix=m_sPrefix, suffix=m_sSuffix;
        int rank=-1;
        for (unsigned int i=0;i<m_pEffectManager->getAffixes().size();++i)
        {
            CAffix* affix=m_pEffectManager->getAffixes()[i];
            if (affix->m_iRank>rank && affix->m_sPrefix!=EMPTY_WSTRING)
            {
                prefix=affix->m_sPrefix.c_str();
                rank=affix->m_iRank;
            }
            if (affix->m_iRank>=0 && affix->m_sSuffix!=EMPTY_WSTRING)
            {
                suffix=affix->m_sSuffix.c_str();
                rank=affix->m_iRank;
            }
        }
        if (prefix!=EMPTY_WSTRING)
        {
            name=STRINGS::replaceWString(prefix,L"[ITEM]",name);
            m_sPrefix=prefix;
        }
        if (suffix!=EMPTY_WSTRING)
        {
            name=STRINGS::replaceWString(suffix,L"[ITEM]",name);
            m_sSuffix=suffix;
        }
        if (tag!=EMPTY_WSTRING)
        {
            begin=name.find(L"{"); end=name.find(L"}",begin);
            while (begin!=-1 && end!=-1)
            {
                std::wstring current=name.substr(begin+1,end-begin-1);
                if (tag==STRINGS::StringUpper(current))
                {
                    int closing=name.find(L"{/"+current,end);
                    int closingEnd=name.find(L"}",closing+1);
                    if (closing==-1) break;
                    name.replace(closing,closingEnd-closing+1,L"");
                    name.replace(begin,end-begin+1,L"");
                }
                else
                {
                    if (static_cast<std::wstring::size_type>(end)>=name.size()-2) break;
                    end=name.find(L"}",end+1);
                    if (end==-1) break;
                    name.replace(begin,end-begin+1,L"");
                }
                begin=name.find(L"{"); end=name.find(L"}",begin);
            }
        }
    }
    return name;
}

void CEquipment::createIcon(CGameUI& ui,bool force)
{
    if (!m_pDataGroup || (m_pIconWindow && !force)) return;
    std::wstring icon=m_pDataGroup->GetDataValue(L"ICON",EMPTY_WSTRING);
    m_bGamblerIcon=false;
    if (m_pInventory && m_pInventory->m_pPositionableObject
        && static_cast<CBaseUnit*>(m_pInventory->m_pPositionableObject)->ISA(UNITTYPES::GAMBLER))
    {
        m_bGamblerIcon=true;
        icon=m_pDataGroup->GetDataValue(L"GAMBLER_ICON",icon);
    }
    else if (ui.getCharacter())
    {
        std::wstring playerClass=STRINGS::StringUpper(ui.getCharacter()->getName());
        std::vector<CDataGroup*> wardrobes;
        unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"WARDROBE",&wardrobes);
        std::wstring unused=EMPTY_WSTRING;
        for (unsigned int i=0;i<count;++i)
        {
            std::wstring wardrobeClass=STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""));
            if (playerClass.compare(L"")==0 || wardrobeClass==playerClass)
                if (wardrobes[i]->GetDataValue(L"ICON",EMPTY_WSTRING)!=EMPTY_WSTRING)
                    icon=wardrobes[i]->GetDataValue(L"ICON",EMPTY_WSTRING);
        }
    }
    bool existing=m_pIconWindow!=0;
    CEGUI::Window* imageWindow;
    if (!existing)
    {
        m_pIconWindow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName("icon_"));
        imageWindow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName("icon_"));
    }
    else imageWindow=m_pIconWindow->getChildAtIdx(0);
    m_pIconWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0,ui.scaledY(64.0f)),CEGUI::UDim(0,ui.scaledY(96.0f))));
    float width=64.0f,height=96.0f;
    if (icon.empty())
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow((L"No icon specified for equipment "+getName()).c_str()),Ogre::LML_NORMAL);
    else
    {
        const CEGUI::Image* image=ui.getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(std::wstring(icon.c_str())).c_str()));
        if (!image) return;
        width=image->getWidth()/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_YRATIO);
        height=image->getHeight()/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_YRATIO);
    }
    imageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim((64.0f-width)*0.5f/64.0f,0),CEGUI::UDim((96.0f-height)*0.5f/96.0f,0)));
    imageWindow->setSize(CEGUI::UVector2(CEGUI::UDim(width/64.0f,0),CEGUI::UDim(height/96.0f,0)));
    imageWindow->setProperty("Image",CEGUI::PropertyHelper::imageToString(ui.getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(std::wstring(icon.c_str())).c_str()))));
    imageWindow->setMousePassThroughEnabled(true);
    imageWindow->setMutedState(true);
    if (!existing) m_pIconWindow->addChildWindow(imageWindow);
}

void CEquipment::loadModel(std::wstring mesh,std::wstring secondaryMesh)
{
    if (!m_pResourceManager) return;
    unloadModel();
    m_pUnitModel=m_pResourceManager->createGenericModel(NULL,mesh.c_str(),NULL,false,false,true);
    if (m_pUnitModel->getSceneNode() && m_pUnitModel->getSceneNode()->getParent())
        m_pUnitModel->getSceneNode()->getParent()->removeChild(m_pUnitModel->getSceneNode());
    m_pUnitModel->setRimLighting(m_pResourceManager && m_pResourceManager->getLevel() && m_pResourceManager->getLevel()->getLevelTemplateData()
        ? m_pResourceManager->getLevel()->getLevelTemplateData()->m_sRimlightTexture
        : std::wstring(L"media/sharedtextures/rimlight.dds"));
    m_pUnitModel->setCastsShadows(false);
    m_pSceneNode->addChild(m_pUnitModel->getSceneNode());
    setVisible(false,true);
    m_pUnitModel->setPosition(0.0f,0.0f,0.0f);
    if (!m_pUnitModel->m_pEntity)
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow((L"Error loading model : "+mesh).c_str()),Ogre::LML_NORMAL);
    else
    {
        m_pUnitModel->m_pEntity->setRenderQueueGroup(50);
        std::wstring second=secondaryMesh==EMPTY_WSTRING?m_pDataGroup->GetDataValue(L"MESHFILE_SECONDARY",EMPTY_WSTRING):secondaryMesh;
        if (!second.empty())
        {
            std::wstring path=second;
            if (secondaryMesh.empty())
            {
                path=m_pDataGroup->GetDataValue(L"RESOURCEDIRECTORY",EMPTY_WSTRING);
                path=FILESYSTEM::CleanPath(path+L"/"+second+L".mesh");
            }
            m_pUnitModelSecondary=m_pResourceManager->createGenericModel(NULL,path.c_str(),NULL,false,false,true);
            if (m_pUnitModelSecondary->getSceneNode() && m_pUnitModelSecondary->getSceneNode()->getParent())
                m_pUnitModelSecondary->getSceneNode()->getParent()->removeChild(m_pUnitModelSecondary->getSceneNode());
            m_pUnitModelSecondary->setRimLighting(m_pResourceManager && m_pResourceManager->getLevel() && m_pResourceManager->getLevel()->getLevelTemplateData()
                ? m_pResourceManager->getLevel()->getLevelTemplateData()->m_sRimlightTexture
                : std::wstring(L"media/sharedtextures/rimlight.dds"));
            m_pUnitModelSecondary->setCastsShadows(false);
            m_pUnitModelSecondary->setPosition(0.0f,0.0f,0.0f);
            m_pUnitModelSecondary->m_pEntity->setRenderQueueGroup(50);
        }
        std::wstring texture=m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE",EMPTY_WSTRING);
        if (!texture.empty()) m_pUnitModel->setTextureOverride(texture);
        std::vector<CDataGroup*> replacements;
        unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"TEXTURE_REPLACE",&replacements);
        for (unsigned int i=0;i<count;++i)
        {
            std::wstring name=replacements[i]->GetDataValue(L"NAME",L"");
            std::wstring replacement=replacements[i]->GetDataValue(L"TEXTURE",L"");
            m_pUnitModel->setTextureOverrideSingle(STRINGS::StringConvertToNarrow(name.c_str()),replacement);
        }
    }
}

void CEquipment::unloadModel()
{
    if (m_pUnitModel) { delete m_pUnitModel; m_pUnitModel=NULL; }
    if (m_pUnitModelSecondary) { delete m_pUnitModelSecondary; m_pUnitModelSecondary=NULL; }
}

void CEquipment::resetVisualLayout()
{
    if (m_pPositionableObject) m_pPositionableObject->setVisible(false);
}

void* CEquipment::getUnitModel() { return m_pUnitModel; }
void* CEquipment::getUnitModelSecondary() { return m_pUnitModelSecondary; }
void* CEquipment::getUnitCollisionModel() { return reinterpret_cast<void*>(m_iUnitCollisionModel); }

bool CEquipment::isWardrobed(std::wstring characterClass)
{
    characterClass=STRINGS::StringUpper(characterClass);
    std::vector<CDataGroup*> wardrobes;
    unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"WARDROBE",&wardrobes);
    std::wstring mesh=EMPTY_WSTRING, texture=EMPTY_WSTRING;
    for (unsigned int i=0;i<count;++i)
    {
        std::wstring wardrobeClass=STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""));
        if (characterClass.compare(L"")==0 || wardrobeClass==characterClass)
            if (wardrobes[i]->GetDataValue(L"MESH",EMPTY_WSTRING)!=EMPTY_WSTRING ||
                wardrobes[i]->GetDataValue(L"TEXTURE",EMPTY_WSTRING)!=EMPTY_WSTRING)
                return true;
    }
    return false;
}

void CEquipment::attachToGivenLocation(CCharacter* character,EEQUIP_LOCATIONS location)
{
    if (isWardrobed(character->getName())) return;
    if (!character || !character->getUnitModel() || !static_cast<CGenericModel*>(character->getUnitModel())->m_pEntity) return;
    if (!m_pUnitModel || !m_pUnitModel->m_pEntity) return;
    m_pUnitModel->setParentGuid(-1);
    if (m_pUnitModelSecondary) m_pUnitModelSecondary->setParentGuid(-1);
    resetVisualLayout();
    detachFromLocation();
    m_pEquippedTo=character;
    m_iUnknown298=location;
    if (m_pParticle_3D0 && m_pUnitModel && m_pParticle_3D0->getSceneNode())
    {
        m_pParticle_3D0->Stop(false);
        OGRE_UTILITIES::removeChildFromParentNode(m_pParticle_3D0->getSceneNode());
    }
    createParticles();
    character->getUnitModel();
    Ogre::Entity* entity=m_pUnitModel->m_pEntity;
    if (KEQUIP_LOCATION_BONES[location]!=EMPTY_STRING)
    {
        std::string bone=KEQUIP_LOCATION_BONES[location];
        int anchor=location;
        if (ISA(UNITTYPES::SHIELD)) {bone=KEQUIP_LOCATION_BONES[11];anchor=11;}
        Ogre::SceneNode* node=NULL;
        switch(anchor)
        {
            case 0: node=character->m_pRightHandNode;break;
            case 1: node=character->m_pLeftHandNode;break;
            case 3: node=character->m_pHeadNode;break;
            case 5: node=character->m_pLeftShoulderNode;break;
            case 11: node=character->m_pShieldNode;break;
        }
        if (node)
        {
            Ogre::SceneNode* parent=m_pUnitModel->getSceneNode()->getParentSceneNode();
            if (parent) parent->removeChild(m_pUnitModel->getSceneNode());
            node->addChild(m_pUnitModel->getSceneNode());
            if (m_pParticle)
            {
                parent=m_pParticle->getSceneNode()->getParentSceneNode();
                if (parent) parent->removeChild(m_pParticle->getSceneNode());
                node->addChild(m_pParticle->getSceneNode());
                m_pParticle->Start();
            }
        }
        if (character->m_pPaperdollModel)
        {
            Ogre::Entity* paperdoll=character->m_pPaperdollModel->m_pEntity;
            std::string name=STRINGS::uniqueName("itemdummy_");
            Ogre::MeshPtr mesh=entity->getMesh();
            mesh->clone(name);
            Ogre::Entity* dummy=CMasterResourceManager::getSingleton()->m_pSceneManager->createEntity(STRINGS::uniqueName("dummyentity_"),name);
            unsigned int count=entity->getNumSubEntities();
            if (count==dummy->getNumSubEntities() && count!=0)
                for (unsigned int i=0;i<count;++i)
                {
                    Ogre::SubEntity* source=entity->getSubEntity(i);
                    Ogre::SubEntity* target=dummy->getSubEntity(i);
                    if (!target->getMaterial().isNull()) target->setMaterial(source->getMaterial());
                }
            float scale=1.0f;
            if (ISA(UNITTYPES::WEAPON)) scale=character->getDataGroup()->GetDataValue(L"WEAPON_SCALE",1.0f);
            else if (ISA(UNITTYPES::SHIELD)) scale=character->getDataGroup()->GetDataValue(L"SHIELD_SCALE",1.0f);
            character->setPaperdollItem(location,dummy);
            Ogre::TagPoint* tag=paperdoll->attachObjectToBone(bone,dummy,Ogre::Quaternion::IDENTITY,Ogre::Vector3::ZERO);
            if (tag) tag->setScale(scale,scale,scale);
        }
    }
    if (KEQUIP_LOCATION_BONES_SECONDARY[location]!=EMPTY_STRING && m_pUnitModelSecondary)
    {
        Ogre::SceneNode* node=NULL;
        entity=m_pUnitModelSecondary->m_pEntity;
        if (location==5 && (node=character->m_pRightShoulderNode)!=NULL)
        {
            Ogre::SceneNode* parent=m_pUnitModelSecondary->getSceneNode()->getParentSceneNode();
            if (parent) parent->removeChild(m_pUnitModelSecondary->getSceneNode());
            node->addChild(m_pUnitModelSecondary->getSceneNode());
        }
        if (m_pParticle)
        {
            Ogre::SceneNode* parent=m_pParticle->getSceneNode()->getParentSceneNode();
            if (parent) parent->removeChild(m_pParticle->getSceneNode());
            node->addChild(m_pParticle->getSceneNode());
            m_pParticle->Start();
        }
        if (character->m_pPaperdollModel)
        {
            Ogre::Entity* paperdoll=character->m_pPaperdollModel->m_pEntity;
            std::string name=STRINGS::uniqueName("itemdummy_");
            Ogre::MeshPtr mesh=entity->getMesh();
            mesh->clone(name);
            Ogre::Entity* dummy=CMasterResourceManager::getSingleton()->m_pSceneManager->createEntity(STRINGS::uniqueName("dummyentity_"),name);
            float scale=1.0f;
            if (ISA(UNITTYPES::WEAPON)) scale=character->getDataGroup()->GetDataValue(L"WEAPON_SCALE",1.0f);
            else if (ISA(UNITTYPES::SHIELD)) scale=character->getDataGroup()->GetDataValue(L"SHIELD_SCALE",1.0f);
            character->setPaperdollItemSecondary(location,dummy);
            if (dummy->getParentSceneNode()) dummy->getParentSceneNode()->setScale(scale,scale,scale);
            unsigned int count=entity->getNumSubEntities();
            if (count==dummy->getNumSubEntities() && count!=0)
                for (unsigned int i=0;i<count;++i)
                {
                    Ogre::SubEntity* source=entity->getSubEntity(i);
                    Ogre::SubEntity* target=dummy->getSubEntity(i);
                    if (!target->getMaterial().isNull()) target->setMaterial(source->getMaterial());
                }
            Ogre::TagPoint* tag=paperdoll->attachObjectToBone(KEQUIP_LOCATION_BONES_SECONDARY[location],dummy,Ogre::Quaternion::IDENTITY,Ogre::Vector3::ZERO);
            if (tag) tag->setScale(scale,scale,scale);
        }
    }
}

std::wstring CEquipment::skillDescription()
{
    static std::wstring g_Level;
    if (g_Level.empty()) g_Level=CStringTranslate::getSinglton()->getTranslateString(L"Level");
    std::wstring result=EMPTY_WSTRING;
    std::vector<CDataGroup*> groups;
    unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"SKILL_TO_GIVE",&groups);
    for (unsigned int i=0;i<count;++i)
    {
        std::wstring name=EMPTY_WSTRING;
        name=groups[i]->GetDataValue(L"NAME",name);
        name=groups[i]->GetDataValue(L"DISPLAYNAME",name);
        int level=groups[i]->GetDataValue(L"LEVEL",m_pDataGroup->GetDataValue(L"LEVEL",1));
        if (i!=0) result=result+L"\n";
        result=result+name+L" "+g_Level+L": "+STRINGS::GetValueAsWString(level);
    }
    if (m_pSkillManager)
        for (unsigned int i=0;i<static_cast<unsigned int>(m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY));++i)
        {
            CSkill* skill=static_cast<int>(i)<static_cast<int>(m_pSkillManager->m_OtherSkills.size()) && i!=static_cast<unsigned int>(-1)
                ? m_pSkillManager->m_OtherSkills[i] : NULL;
            if ((skill->m_bEnabled & !skill->m_bExecutedByProperty) && skill)
            {
                if (i!=0) result=result+L"\n";
                result.append(skill->getDescription(this,static_cast<unsigned int>(-1),true));
            }
        }
    return result;
}
void CEquipment::setItemTextHighlighted(bool highlighted)
{
    if (getHighlighted() == highlighted || m_pItemText == NULL)
        return;
    if (getIsQuestUnit())
    {
        m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getQuestColor(highlighted)));
    }
    else if (getSet()!=EMPTY_WSTRING)
    {
        m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getSetColor(highlighted)));
    }
    else if (ISA(UNITTYPES::UNIQUE))
    {
        m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getUniqueColor(highlighted)));
    }
    else if (isMagical() || ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE))
    {
        if (ISA(UNITTYPES::MAGIC))
            m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getRareColor(highlighted)));
        else
            m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getRandomEnchantColor(highlighted)));
    }
    else
    {
        CEGUI::colour color = highlighted ? CEGUI::colour(1.0f,1.0f,1.0f,1.0f) : CEGUI::colour(0.8f,0.8f,0.8f,1.0f);
        m_pItemText->setProperty("TextColour", CEGUI::PropertyHelper::colourToString(color));
    }
    if (highlighted)
        m_pItemText->moveToFront();
}

void CEquipment::setRequirements()
{
    m_iUnknown278=m_pDataGroup->GetDataValue(L"LEVEL_REQUIRED",0);
    int reduction=std::min(m_iUnknown28C,5);
    if (m_iUnknown278==0 && (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR) || ISA(UNITTYPES::TRINKET)))
    {
        CGraph* graph=CGraphManager::getSingleton()->getGraph(L"ITEM_LEVEL_REQUIREMENTS");
        int requirement=static_cast<int>(floorf(graph->getValue(static_cast<float>(m_iUnknown274),0)))-reduction;
        m_iUnknown278=requirement>1?requirement:0;
    }
    reduction=std::min(m_iUnknown28C,10);
    m_iUnknown27C=m_pDataGroup->GetDataValue(L"STRENGTH_REQUIRED",0);
    if (m_iUnknown27C!=0 && (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR)))
    {
        CGraph* graph=CGraphManager::getSingleton()->getGraph(L"ITEM_STRENGTH_REQUIREMENTS");
        float value=graph->getValue(static_cast<float>(m_iUnknown274),0);
        int requirement=static_cast<int>(floorf(value*static_cast<float>(m_iUnknown27C)/100.0f))-reduction;
        m_iUnknown27C=requirement>1?requirement:0;
    }
    m_iUnknown280=m_pDataGroup->GetDataValue(L"DEXTERITY_REQUIRED",0);
    if (m_iUnknown280!=0 && (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR)))
    {
        CGraph* graph=CGraphManager::getSingleton()->getGraph(L"ITEM_DEXTERITY_REQUIREMENTS");
        float value=graph->getValue(static_cast<float>(m_iUnknown274),0);
        int requirement=static_cast<int>(floorf(value*static_cast<float>(m_iUnknown280)/100.0f))-reduction;
        m_iUnknown280=requirement>1?requirement:0;
    }
    m_iUnknown284=m_pDataGroup->GetDataValue(L"MAGIC_REQUIRED",0);
    if (m_iUnknown284!=0 && (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR)))
    {
        CGraph* graph=CGraphManager::getSingleton()->getGraph(L"ITEM_MAGIC_REQUIREMENTS");
        float value=graph->getValue(static_cast<float>(m_iUnknown274),0);
        int requirement=static_cast<int>(floorf(value*static_cast<float>(m_iUnknown284)/100.0f))-reduction;
        m_iUnknown284=requirement>1?requirement:0;
    }
    m_iUnknown288=m_pDataGroup->GetDataValue(L"DEFENSE_REQUIRED",0);
    if (m_iUnknown288!=0 && (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR)))
    {
        CGraph* graph=CGraphManager::getSingleton()->getGraph(L"ITEM_DEFENSE_REQUIREMENTS");
        float value=graph->getValue(static_cast<float>(m_iUnknown274),0);
        int requirement=static_cast<int>(floorf(value*static_cast<float>(m_iUnknown288)/100.0f))-reduction;
        m_iUnknown288=requirement>1?requirement:0;
    }
}

void CEquipment::reskinByClass(std::wstring characterClass)
{
    if (m_pUnitModel)
    {
        std::vector<CDataGroup*> wardrobes;
        unsigned int count=m_pDataGroup->GetDataGroupsMatchingName(L"WARDROBE",&wardrobes);
        std::wstring primary=EMPTY_WSTRING, secondary=EMPTY_WSTRING;
        for (unsigned int i=0;i<count;++i)
        {
            std::wstring wardrobeClass=STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""));
            if (wardrobeClass==STRINGS::StringUpper(characterClass))
            {
                primary=wardrobes[i]->GetDataValue(L"ITEM_MESH",primary);
                secondary=wardrobes[i]->GetDataValue(L"ITEM_MESH_SECONDARY",secondary);
            }
        }
        if (primary!=EMPTY_WSTRING)
        {
            std::wstring current=m_pUnitModel->m_sModelPath;
            if (STRINGS::StringUpper(primary)!=STRINGS::StringUpper(current))
                loadModel(primary,secondary);
        }
    }
}
void CEquipment::recalculatePrice()
{
    m_iUnknown264=1;
    m_iUnknown268=1;
    int value=m_pDataGroup->GetDataValue(L"VALUE",100);
    if (value!=0)
    {
        int level=std::max(m_iUnknown274,1);
        CGraph* buy;
        CGraph* sell;
        if (ISA(UNITTYPES::UNIQUE))
        {
            buy=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERBUY_UNIQUE");
            sell=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERSELL_UNIQUE");
        }
        else if (isMagical())
        {
            buy=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERBUY_MAGIC");
            sell=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERSELL_MAGIC");
        }
        else
        {
            buy=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERBUY_NORMAL");
            sell=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERSELL_NORMAL");
        }
        float buyValue=buy->getValue(static_cast<float>(level),0);
        float sellValue=sell->getValue(static_cast<float>(level),0);
        m_iUnknown264=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)));
        m_iUnknown268=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)));
        if (m_pInventory && m_pInventory->m_pPositionableObject &&
            static_cast<CBaseUnit*>(m_pInventory->m_pPositionableObject)->ISA(UNITTYPES::GAMBLER))
        {
            CGraph* gamble=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERGAMBLE_MAGIC");
            m_iUnknown264=static_cast<int>(ceilf(gamble->getValue(static_cast<float>(level),0)*(static_cast<float>(value)/100.0f)));
        }
        buy=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERBUY_NORMAL");
        sell=CGraphManager::getSingleton()->getGraph(L"PRICE_PLAYERSELL_NORMAL");
        buyValue=buy->getValue(static_cast<float>(level),0);
        sellValue=sell->getValue(static_cast<float>(level),0);
        m_iUnknown26C=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)));
        m_iUnknown270=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)));
    }
}

CCharacter* CEquipment::getEquippedTo()
{
    return m_pEquippedTo;
}

bool CEquipment::fireMissiles(CCharacter* shooter,CCharacter* target)
{
    if (m_sUnknown400.empty() || shooter==NULL)
        return false;
    Ogre::Vector3 origin=(shooter->getWeaponInLeftHand()==this
        ? shooter->m_pLeftHandNode : shooter->m_pRightHandNode)->_getDerivedPosition();
    Ogre::Vector3 direction=shooter->getForwardAbsolute();
    if (target)
    {
        direction=target->getPosition(true)-origin;
        direction.normalise();
    }
    float scale=shooter->getDataGroup()->GetDataValue(L"WEAPON_SCALE",1.0f);
    Ogre::Vector3 offset=direction;
    if (getUnitModel())
    {
        CGenericModel* model=static_cast<CGenericModel*>(getUnitModel());
        float height=model->m_pEntity->getBoundingBox().getSize().y;
        offset=direction*height*(scale*0.8f);
    }
    Ogre::Vector3 launch=origin+offset;
    CResourceManager* resources=m_pResourceManager;
    CMissile* missile=resources->getMissilePreloader()->createNewMissileRef(resources,m_sUnknown400);
    if (!missile)
        return false;
    iMissile* listener=static_cast<iMissile*>(this);
    if (missile->m_Listeners.find(listener)==-1)
        missile->m_Listeners.add(listener);
    Ogre::Vector3 targetPosition=target?target->getPosition(true):Ogre::Vector3::ZERO;
    Ogre::Vector3 right=Ogre::Vector3::UNIT_Y.crossProduct(direction);
    Ogre::Quaternion orientation;
    orientation.FromAxes(right,Ogre::Vector3::UNIT_Y,direction);
    missile->fireMissile(getEquippedTo(),launch,orientation,target,targetPosition);
    TSafePointer<CMissile>* reference=OGRE_NEW_T(TSafePointer<CMissile>,Ogre::MEMCATEGORY_GENERAL)();
    reference->setObject(missile);
    m_ActiveMissileRefs.add(reference);
    return true;
}

void CEquipment::createParticles()
{
    if (m_sUnknown3D8!=EMPTY_WSTRING)
    {
        if (!m_pParticle_3D0)
        {
            CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(m_sUnknown3D8);
            m_pParticle_3D0=m_pResourceManager->createParticle(m_sUnknown3D8.c_str());
        }
    }
    else
    {
        std::wstring particle=EMPTY_WSTRING;
        if (getIsQuestUnit()) particle=L"QUEST_ITEM";
        else if (ISA(UNITTYPES::UNIQUE)) particle=L"UNIQUE_WEAPON";
        else if (isMagical()) particle=L"MAGIC_WEAPON";
        else particle=L"GENERIC_WEAPON";
        // +0x110 is the original live wstring. Keep Particle's scaffold field
        // unchanged here: changing its owning type would also alter that TU's
        // unrecovered destructor. No Particle implementation is changed.
        if (m_pParticle_3D0 && STRINGS::StringUpper(*reinterpret_cast<const std::wstring*>(&m_pParticle_3D0->m_pUnknown110))!=particle)
        {
            delete m_pParticle_3D0;
            m_pParticle_3D0=NULL;
        }
        if (!m_pParticle_3D0)
            m_pParticle_3D0=m_pResourceManager->createParticle(particle.c_str());
    }
    if (m_pParticle_3D0 && m_bVisible && !m_pEquippedTo && m_pUnitModel)
    {
        m_pParticle_3D0->sceneNodeSetParent(m_pUnitModel->getSceneNode(),false);
        m_pParticle_3D0->setPosition(Ogre::Vector3(0,0,0));
        m_pParticle_3D0->Start();
    }
    if (!ISA(UNITTYPES::WEAPON)) return;
    int damage=getDamageBonus(DAMAGE_ELECTRIC);
    int largest=std::max(damage,0);
    EDAMAGE_TYPES type=damage>0?DAMAGE_ELECTRIC:DAMAGE_PHYSICAL;
    damage=getDamageBonus(DAMAGE_FIRE);
    if (damage>largest) {largest=damage;type=DAMAGE_FIRE;}
    damage=getDamageBonus(DAMAGE_ICE);
    if (damage>largest) {largest=damage;type=DAMAGE_ICE;}
    damage=getDamageBonus(DAMAGE_POISON);
    if (damage>largest) type=DAMAGE_POISON;
    std::wstring particle=EMPTY_WSTRING;
    switch (type)
    {
    case DAMAGE_ELECTRIC: particle=ISA(UNITTYPES::PISTOL)?L"WEAPON_ELECTRICITY_PISTOL":L"WEAPON_ELECTRICITY";break;
    case DAMAGE_FIRE: particle=ISA(UNITTYPES::PISTOL)?L"WEAPON_FIRE_PISTOL":L"WEAPON_FIRE";break;
    case DAMAGE_ICE: particle=ISA(UNITTYPES::PISTOL)?L"WEAPON_ICE_PISTOL":L"WEAPON_ICE";break;
    case DAMAGE_POISON: particle=ISA(UNITTYPES::PISTOL)?L"WEAPON_POISON_PISTOL":L"WEAPON_POISON";break;
    default:break;
    }
    if (m_pParticle && STRINGS::StringUpper(*reinterpret_cast<const std::wstring*>(&m_pParticle->m_pUnknown110))!=particle)
    {
        delete m_pParticle;
        m_pParticle=NULL;
    }
    if (!m_pParticle) m_pParticle=m_pResourceManager->createParticle(particle.c_str());
    if (m_pParticle && m_pUnitModel)
    {
        m_pParticle->sceneNodeSetParent(m_pUnitModel->getSceneNode(),false);
        m_pParticle->setPosition(Ogre::Vector3(0,0,0));
        m_pParticle->Start();
    }
}

CEquipment::~CEquipment()
{
    if (m_pPositionableObject)
    {
        resetVisualLayout();
        if (m_pPositionableObject)
        {
            delete m_pPositionableObject;
            m_pPositionableObject=NULL;
        }
    }
    for (unsigned int i=0;i<m_ActiveMissileRefs.size();++i)
        if (m_ActiveMissileRefs[i] && m_ActiveMissileRefs[i]->getObject())
            m_ActiveMissileRefs[i]->getObject()->m_Listeners.remove(static_cast<iMissile*>(this));
    m_SocketedEquipment.deleteAll();
    if (m_pParticle) {delete m_pParticle;m_pParticle=NULL;}
    if (m_pParticle_3D0) {delete m_pParticle_3D0;m_pParticle_3D0=NULL;}
    CItem::setVisible(false,true);
    detachFromLocation();
    m_pEntity=NULL;
    destroyIcon();
    if (m_pSoundBank) {delete m_pSoundBank;m_pSoundBank=NULL;}
    if (m_pPath) {delete m_pPath;m_pPath=NULL;}
    CMasterResourceManager::getSingleton()->removeCollisionModel(reinterpret_cast<CCollisionModel*>(m_iUnitCollisionModel));
    if (m_pAttackDescription) {delete m_pAttackDescription;m_pAttackDescription=NULL;}
    if (m_pAttackDescriptionOverride) {delete m_pAttackDescriptionOverride;m_pAttackDescriptionOverride=NULL;}
    unloadModel();
    detachFromLocation();
    m_pInventory=NULL;
    m_pEquippedTo=NULL;
}

void CEquipment::updateDrop(float elapsed)
{
    if (!m_bUnknown25C) return;
    m_fUnknown258+=elapsed*20.0f;
    if (m_pPath->m_fPathLength<=m_fUnknown258)
    {
        m_fUnknown258=m_pPath->m_fPathLength;
        setEnabled(true);
        m_bUnknown25C=false;
        m_pSoundBank->playSample(17,m_pSceneNode,0.0f,0.0f,false);
    }
    m_vPosition=m_pPath->GetSplinePositionAtDistance(m_fUnknown258);
    CPositionableObject::setPosition(m_vPosition);
    if (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::SHIELD) || ISA(UNITTYPES::POTION) || ISA(UNITTYPES::SCROLL))
    {
        float progress=std::min(m_fUnknown258/m_pPath->m_fPathLength,1.0f);
        Ogre::Matrix4 rotation;
        MATH::matrixRotationZ(rotation,progress*6.2831855f);
        m_mOrientation=m_mDropOrientation*rotation;
        setOrientation(m_mOrientation,false);
    }
}

void CEquipment::fillSaveState(CItemSaveState& state,int index,bool flag)
{
    if (m_pEffectManager && ISA(UNITTYPES::SOCKETABLE) && !ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE))
        m_pEffectManager->clearOutAffixEffects();
    CItem::fillSaveState(state,index,flag);
    state.m_iStateValue28=m_iUnknown28C;
    state.m_iStackSize=m_iUnknown238;
    state.m_bIdentified=m_bUnknown348;
    state.m_iSocketCount=m_iSocketCount;
    state.m_iStateValue6C=m_iUnknown344;
    if (m_bUnknown25C && !getEnabled()) state.m_bEnabled=true;
    state.m_iBaseArmor=m_iUnknown33C;
    state.m_iBaseDamage=m_iUnknown340;
    getFullItemName(true);
    state.m_sStateString20=m_sSuffix;
    state.m_sStateString18=m_sPrefix;
    createElementalDamages();
    int sockets=static_cast<int>(m_SocketedEquipment.size());
    for (int i=0;i<sockets;++i)
    {
        CItemSaveState* child=new CItemSaveState;
        m_SocketedEquipment[i]->fillSaveState(*child,-1,false);
        state.m_SocketedItems.push_back(child);
    }
    if (m_pEffectManager)
        for (int activation=0;activation<3;++activation)
        {
            // EffectManager retains its opaque layout in its own TU. These
            // three original TArrayLists start at manager+0x28, stride0x18.
            TArrayList<CEffect*>& effects=reinterpret_cast<TArrayList<CEffect*>*>(m_pEffectManager->m_EffectData10+0x18)[activation];
            for (unsigned int i=0;i<effects.size();++i)
            {
                CEffect* copy=new CEffect(effects[i]);
                copy->setOwner(NULL,true);
                copy->setSkillOwner(NULL);
                copy->m_fValueC0=effects[i]->m_fValueC0;
                state.m_Effects[activation].push_back(copy);
            }
        }
    for (unsigned int i=0;i<m_ElementalDamageTypes.size();++i)
    {
        state.m_DamageTypes.push_back(m_ElementalDamageTypes[i]);
        state.m_DamageBonuses.push_back(m_ElementalDamageBonuses[i]);
    }
    if (m_pEffectManager && ISA(UNITTYPES::SOCKETABLE) && !ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE))
        m_pEffectManager->addAffixEffectsBackIn();
}

void CEquipment::enchant(bool force)
{
    if (ISA(UNITTYPES::RANDOMMAGIC)) force=true;
    bool emptyUnique=false;
    if (ISA(UNITTYPES::UNIQUE))
        emptyUnique=!m_pEffectManager || m_pEffectManager->getAffixes().size()==0;
    bool attempt=ISA(UNITTYPES::MAGIC);
    if (!attempt && m_bItemFlag20A)
    {
        attempt=force;
        if (!force)
        {
            float roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
            attempt=roll<CGameGlobals::getSingleton()->m_fRandomEnchantChance*10.0f;
        }
    }
    if (attempt && (!ISA(UNITTYPES::UNIQUE) || emptyUnique) &&
        (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR) || ISA(UNITTYPES::RING) ||
         ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE) || ISA(UNITTYPES::NECKLACE)))
    {
        unsigned int count;
        if (ISA(UNITTYPES::UNIQUE))
            count=UTILITIES::randomIntegerBetweenVolatile(CGameGlobals::getSingleton()->m_iMinUniqueItemSlots,CGameGlobals::getSingleton()->m_iMaxUniqueItemSlots);
        else if (ISA(UNITTYPES::MAGIC))
            count=UTILITIES::randomIntegerBetweenVolatile(CGameGlobals::getSingleton()->m_iMinMagicItemSlots,CGameGlobals::getSingleton()->m_iMaxMagicItemSlots);
        else
            count=UTILITIES::randomIntegerBetweenVolatile(CGameGlobals::getSingleton()->m_iMinRandomEnchantSlots,CGameGlobals::getSingleton()->m_iMaxRandomEnchantSlots);
        m_pResourceManager->createAffixesForUnit(this,m_iUnknown274,count);
        m_bUnknown348=false;
    }
    if (ISA(UNITTYPES::UNIQUE) && (!m_pEffectManager || reinterpret_cast<TArrayList<CEffect*>*>(m_pEffectManager->m_EffectData10+0x18)->size()==0))
    {
        unsigned int count=UTILITIES::randomIntegerBetweenVolatile(CGameGlobals::getSingleton()->m_iMinUniqueItemSlots,CGameGlobals::getSingleton()->m_iMaxUniqueItemSlots);
        m_pResourceManager->createAffixesForUnit(this,m_iUnknown274+1,count);
        m_bUnknown348=false;
    }
    if (m_iSocketCount==0 && m_pResourceManager && m_pResourceManager->getLevel() && m_bItemFlag20A)
    {
        float roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
        if (roll<CGameGlobals::getSingleton()->m_fRandomSocketChance*10.0f && !ISA(UNITTYPES::UNIQUE) &&
            (ISA(UNITTYPES::WEAPON) || ISA(UNITTYPES::ARMOR) || ISA(UNITTYPES::RING) || ISA(UNITTYPES::NECKLACE)))
        {
            roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
            m_iSocketCount=1+(roll<CGameGlobals::getSingleton()->m_fSecondSocketChance*10.0f);
        }
    }
    if (!m_bUnknown348 && m_pDataGroup->GetDataValue(L"ALWAYS_IDENTIFIED",false))
        m_bUnknown348=true;
    recalculatePrice();
}

std::wstring CEquipment::getAttackSpeedString(EWeaponSpeed speed)
{
    std::wstring result=EMPTY_WSTRING;
    switch (speed)
    {
    case 0:
    {
        static std::wstring g_Slowest;
        if (g_Slowest.empty())
            g_Slowest=CStringTranslate::getSinglton()->getTranslateString(L"Slowest Attack Speed");
        result=g_Slowest;
        break;
    }
    case 1:
    {
        static std::wstring g_Slow;
        if (g_Slow.empty())
            g_Slow=CStringTranslate::getSinglton()->getTranslateString(L"Slow Attack Speed");
        result=g_Slow;
        break;
    }
    case 2:
    {
        static std::wstring g_Average;
        if (g_Average.empty())
            g_Average=CStringTranslate::getSinglton()->getTranslateString(L"Average Attack Speed");
        result=g_Average;
        break;
    }
    case 3:
    {
        static std::wstring g_Fast;
        if (g_Fast.empty())
            g_Fast=CStringTranslate::getSinglton()->getTranslateString(L"Fast Attack Speed");
        result=g_Fast;
        break;
    }
    case 4:
    {
        static std::wstring g_Fastest;
        if (g_Fastest.empty())
            g_Fastest=CStringTranslate::getSinglton()->getTranslateString(L"Fastest Attack Speed");
        result=g_Fastest;
        break;
    }
    }
    return result;
}

void CEquipment::setRimlight(std::wstring texture)
{
    if (m_pDataGroup)
    {
        if (m_pUnitModel)
        {
            m_pUnitModel->setRimLighting(texture);
            std::wstring overrideTexture=m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE",EMPTY_WSTRING);
            if (!overrideTexture.empty()) m_pUnitModel->setTextureOverride(overrideTexture);
        }
        if (m_pUnitModelSecondary)
        {
            m_pUnitModelSecondary->setRimLighting(texture);
            std::wstring overrideTexture=m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE",EMPTY_WSTRING);
            if (!overrideTexture.empty()) m_pUnitModelSecondary->setTextureOverride(overrideTexture);
        }
    }
}

CEquipment::CEquipment(CResourceManager* resources)
    : CItem(resources),
      m_iUnknown238(1),m_iUnknown23C(1),m_pInventory(NULL),m_iUnknown248(0),
      m_pPath(NULL),m_fUnknown258(0.0f),m_bUnknown25C(false),m_bGamblerIcon(false),
      m_bUnknown25E(true),m_bUnknown25F(false),m_iUnknown260(0),m_iUnknown274(1),
      m_iUnknown28C(0),m_pEquippedTo(NULL),m_pAttackDescription(NULL),
      m_pAttackDescriptionOverride(NULL),m_pUnitModel(NULL),m_pUnitModelSecondary(NULL),
      m_iUnitCollisionModel(0),m_pIconWindow(NULL),m_sUnidentifiedName(EMPTY_WSTRING),
      m_sDisplayName(EMPTY_WSTRING),m_sPrefix(EMPTY_WSTRING),m_sSuffix(EMPTY_WSTRING),
      m_iMinimumDamage(1),m_iMaximumDamage(1),m_iUnknown338(0),m_iUnknown33C(-1),
      m_iUnknown340(-1),m_iUnknown344(0),m_bUnknown348(true),m_pParticle(NULL),
      m_pParticle_3D0(NULL),m_iSocketCount(0),m_SocketedEquipment(1),
      m_fUnknown408(0.0f),m_ActiveMissileRefs(1),m_pPositionableObject(NULL)
{
    m_fBaseUnitValue194=0.375f;
}
