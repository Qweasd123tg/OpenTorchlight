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
