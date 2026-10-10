#ifndef STATSMENUFILL_H
#define STATSMENUFILL_H
#include "DropdownMenu.h"
#include "TArrayList.h"
class CPlayer;
class CGraph;
namespace STRINGS { std::wstring GetValueAsWString(float); }
enum ESTATSMENU_STATS { STATSMENU_STATS_FIRST = 0 };
// Layout through 0x190, recovered from the constructor and update.
class CStatsMenuFill : public CDropdownMenu {
public:
 CStatsMenuFill(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
 virtual ~CStatsMenuFill();
 virtual void update(float);
 virtual void setOpen(bool);
 virtual void setOwner(CPlayer*);
 void createMenus();
 void updateVisuals();
 void calculateMouseOver();
 int getStatInvestment(ESTATSMENU_STATS);
 int getStatBarCurrentAmount(ESTATSMENU_STATS);
 float getExperienceToSpend();
 void addExperienceToStat(ESTATSMENU_STATS,int);
 void addExperienceSpent(int);
 float getStatBarTotalAmount(ESTATSMENU_STATS);
 bool handle_ExitButton(const CEGUI::EventArgs&);
 bool handle_CloseButton(const CEGUI::EventArgs&);
 float getExperienceBarTotalAmount();
 float getAmountOfXPToAdd(ESTATSMENU_STATS,float);
 float getAmountOfXPToRemove(ESTATSMENU_STATS,float);
 void fillIntoBar(ESTATSMENU_STATS,float);
 void removeFromBar(ESTATSMENU_STATS,float);
 bool handle_onMouseUp(const CEGUI::EventArgs&);
 bool handle_AddToStat(const CEGUI::EventArgs&);
 bool handle_RemoveFromStat(const CEGUI::EventArgs&);
 TArrayList<CEGUI::Window*> m_AddButtons;
 TArrayList<CEGUI::Window*> m_RemoveButtons;
 TArrayList<CEGUI::Window*> m_Bars;
 TArrayList<CEGUI::Window*> m_AmountTexts;
 TArrayList<CEGUI::Window*> m_StatSlots;
 TArrayList<CEGUI::Window*> m_PercentTexts;
 CEGUI::Window* m_pExperienceText;
 bool m_AddHeld[4];
 bool m_RemoveHeld[4];
 CPlayer* m_pPlayer;
 float m_HeldTime;
 CGraph* m_pPointGraph;
 float m_BarCooldown;
 CSoundBank* m_pFillSoundBank;
 float m_FillSoundInterval;
 float m_FillSoundCountdown;
 bool m_Filling;
};
#endif
