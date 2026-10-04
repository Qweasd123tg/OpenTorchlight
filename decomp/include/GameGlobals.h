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
    const std::wstring& getRandomEnchantColor(bool selected) const { return selected ? m_sRandomEnchantColor : m_sRandomEnchantColorUnselected; }
    const std::wstring& getRareColor(bool selected) const { return selected ? m_sRareColor : m_sRareColorUnselected; }
    const std::wstring& getUniqueColor(bool selected) const { return selected ? m_sUniqueColor : m_sUniqueColorUnselected; }
    const std::wstring& getQuestColor(bool selected) const { return selected ? m_sQuestColor : m_sQuestColorUnselected; }
private:
    unsigned char m_GlobalsData10[0x268-0x10];
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
