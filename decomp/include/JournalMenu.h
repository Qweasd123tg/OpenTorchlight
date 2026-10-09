#ifndef JOURNALMENU_H
#define JOURNALMENU_H
#include "SubMenu.h"
#include "TArrayList.h"
namespace CEGUI {class Window;}
class CGameUI;class CResourceManager;
class CJournalMenu : public CSubMenu {
public:
 virtual ~CJournalMenu();
 virtual CBaseUnit* getOwner();
 virtual bool isRight();
 virtual bool open();
 virtual bool openPartial();
 virtual float screenEdge();
 virtual void setOwner(CCharacter*);
 virtual void setOpen(bool);
 virtual void updateLayout();
 virtual void update(float);
 virtual bool handle_onClick(const CEGUI::EventArgs&);
 virtual bool processInput(void*,float,bool);
 char m_Data10[8];
 CEGUI::Window* m_pRoot;
 char m_Data20[16];
 CCharacter* m_pOwner;
 char m_Data38[16];
 CGameUI* m_pGameUI;
 char m_Data50[16];
 CResourceManager* m_pResourceManager;
 char m_Data68[16];
 CEGUI::Window* m_pContent;
 char m_Data80[16];
 TArrayList<CEGUI::Window*> m_Children;
};
#endif
