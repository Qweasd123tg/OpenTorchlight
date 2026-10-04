#include "EmptyStrings.h"
#include "Equipment.h"
#include "EffectManager.h"
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
                int damage=m_ElementalDamageMaximums[i];
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
                    if (m_ElementalDamageMaximums[i]>0)
                    {
                        std::wstring damageType=CStringTranslate::getSinglton()->getTranslateString(gDAMAGE_TYPES[m_ElementalDamageTypes[i]].c_str());
                        result=result+L"\n+"+STRINGS::GetValueAsWString(m_ElementalDamageMaximums[i])+L" "+damageType+L" "+g_Damage;
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
