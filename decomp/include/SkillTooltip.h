#ifndef SKILLTOOLTIP_H
#define SKILLTOOLTIP_H
#include "RunicCore.h"
#include <string>
class CBaseUnit;
class CSkill;
class CGameUI;
namespace CEGUI { class Window; }
// Prefix established by the inlined constructor in Inventory createMenus.
// Allocation is0x178; only two destructor entries belong to the vtable.
class CSkillTooltip : public CRunicCore {
public:
    virtual ~CSkillTooltip();
    CSkillTooltip(CGameUI*,CEGUI::Window*);
    void load(CGameUI*,std::wstring);
    void showTooltip(CBaseUnit*,CSkill*,float,float);
    CGameUI* m_pGameUI;
    std::wstring m_sText;
    int m_iIndex;
    char pad24[4];
    CEGUI::Window* m_pRoot;
    CEGUI::Window* m_pWindow;
    CEGUI::Window* m_pSkillName; // 0x38
    CEGUI::Window* m_pSkillRank;
    CEGUI::Window* m_pDescription;
    CEGUI::Window* m_pSkillType;
    CEGUI::Window* m_pManaCost;
    CEGUI::Window* m_pCooldown;
    CEGUI::Window* m_pEffects;
    CEGUI::Window* m_pNextDescription;
    CEGUI::Window* m_pNextEffects;
    CEGUI::Window* m_pNextLevel;
    CEGUI::Window* m_pNextManaCost;
    CEGUI::Window* m_pNextCooldown;
    CEGUI::Window* m_pLevelRequirement;
    CEGUI::Window* m_pSkillRequirement;
    CEGUI::Window* m_pSkillIcon;
    CEGUI::Window* m_pUsage;
    CEGUI::Window* m_pStatIcons[4]; // 0xb8
    CEGUI::Window* m_pStatLabels[4]; // 0xd8
    float m_StatOffsets[8]; // 0xf8
    CEGUI::Window* m_pNextStatIcons[4]; // 0x118
    CEGUI::Window* m_pNextStatLabels[4]; // 0x138
    float m_NextStatOffsets[8]; // 0x158
};
#endif
