#ifndef STATSMENUFILL_H
#define STATSMENUFILL_H
#include "DropdownMenu.h"
#include "TArrayList.h"
class CPlayer;
// Partial through the creation fields. Unused trailing state is unrecovered.
class CStatsMenuFill : public CDropdownMenu {
public:
 virtual ~CStatsMenuFill();
 virtual void update(float);
 virtual void setOpen(bool);
 virtual void setOwner(CPlayer*);
 void createMenus();
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
};
#endif
