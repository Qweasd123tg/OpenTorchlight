#ifndef EQUIPMENTTOOLTIP_H
#define EQUIPMENTTOOLTIP_H
#include "RunicCore.h"
#include <string>
class CGameUI;
namespace CEGUI {class Window;}
// Allocation0x98 and field identities verified in load(CGameUI*,wstring).
class CEquipmentTooltip : public CRunicCore {
public:
 virtual ~CEquipmentTooltip();
 CEquipmentTooltip(CEGUI::Window*);
 void load(CGameUI*,std::wstring);
 long long m_iCachedItemGuid;
 CEGUI::Window* m_pParent;
 CEGUI::Window* m_pRoot;
 CEGUI::Window* m_pItemName;
 CEGUI::Window* m_pItemType;
 CEGUI::Window* m_pItemHanded;
 CEGUI::Window* m_pBigDPS;
 CEGUI::Window* m_pDPS;
 CEGUI::Window* m_pStats;
 CEGUI::Window* m_pEffects;
 CEGUI::Window* m_pLevelRequirement;
 CEGUI::Window* m_pStrengthRequirement;
 CEGUI::Window* m_pDexterityRequirement;
 CEGUI::Window* m_pMagicRequirement;
 CEGUI::Window* m_pDefenseRequirement;
 CEGUI::Window* m_pDescription;
 CEGUI::Window* m_pPrice;
};
#endif
