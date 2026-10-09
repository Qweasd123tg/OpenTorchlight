#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H
#include "RunicCore.h"
#include <string>
// Partial: colour names follow the original reload() configuration keys.
class CGameGlobals : public CRunicCore
{
public:
    virtual ~CGameGlobals();
    static CGameGlobals* getSingleton();
    float getUnitShadowRange() const { return m_fUnitShadowRange; }
    float getUnitNearRange() const { return m_fUnitNearRange; }
    float getTriggerNearRange() const { return m_fTriggerNearRange; }
    float getIndoorUnitActiveRange() const { return m_fIndoorUnitActiveRange; }
    float getOutdoorUnitActiveRange() const { return m_fOutdoorUnitActiveRange; }
    const std::wstring& getRandomEnchantColor(bool selected) const { return selected ? m_sRandomEnchantColor : m_sRandomEnchantColorUnselected; }
    const std::wstring& getRareColor(bool selected) const { return selected ? m_sRareColor : m_sRareColorUnselected; }
    const std::wstring& getUniqueColor(bool selected) const { return selected ? m_sUniqueColor : m_sUniqueColorUnselected; }
    const std::wstring& getSocketedEffectColor() const { return m_sGlobalsString2B8; }
    const std::wstring& getSetColor(bool selected) const { return selected ? m_sSetColor : m_sSetColorUnselected; }
    const std::wstring& getQuestColor(bool selected) const { return selected ? m_sQuestColor : m_sQuestColorUnselected; }
private:
    friend class CEquipment;
    friend class CEnchantMenu;
    unsigned char m_GlobalsData10[0x24-0x10];
    float m_fRandomEnchantChance;
    float m_fRandomSocketChance;
    float m_fSecondSocketChance;
    int m_iMinRandomEnchantSlots;
    int m_iMaxRandomEnchantSlots;
    int m_iMinMagicItemSlots;
    int m_iMaxMagicItemSlots;
    int m_iMinUniqueItemSlots;
    int m_iMaxUniqueItemSlots;
    unsigned char m_GlobalsData48[0x64-0x48];
    float m_fEnchanterSocketChance;
    float m_fEnchanterEnchantChance;
    float m_fEnchanterPricePerEnchant; // ENCHANTER_PRICE_PER_ENCHANT
    float m_fEnchanterDisenchantBase;
    float m_fEnchanterDisenchantMax;
    float m_fShrineSocketChance;
    float m_fShrineEnchantChance;
    float m_fShrineDisenchantBase;
    float m_fShrineDisenchantMax;
    int m_iEnchanterMaxEnchantments;
    float m_fEnchanterDisenchantPerEnchant;
    int m_iShrineMaxEnchantments;
    float m_fShrineDisenchantPerEnchant;
    unsigned char m_GlobalsData98[0x10];
    float m_fUnitShadowRange;
    float m_fUnitNearRange;
    float m_fTriggerNearRange;
    float m_fIndoorUnitActiveRange;
    float m_fOutdoorUnitActiveRange;
    unsigned char m_GlobalsDataBC[0x268-0xbc];
    std::wstring m_sRandomEnchantColor;
    std::wstring m_sRareColor;
    std::wstring m_sUniqueColor;
    std::wstring m_sSetColor;
    std::wstring m_sQuestColor;
    std::wstring m_sRandomEnchantColorUnselected;
    std::wstring m_sRareColorUnselected;
    std::wstring m_sUniqueColorUnselected;
    std::wstring m_sSetColorUnselected;
    std::wstring m_sQuestColorUnselected;
    std::wstring m_sGlobalsString2B8;
    unsigned char m_GlobalsData2C0[0x10];
};
#endif
