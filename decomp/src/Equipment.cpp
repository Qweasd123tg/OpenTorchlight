#include "EmptyStrings.h"
#include "Equipment.h"
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
