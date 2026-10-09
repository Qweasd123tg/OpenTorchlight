#ifndef SKILLMENU_H
#define SKILLMENU_H
#include "SubMenu.h"
#include "GameUI.h"
#include "TArrayList.h"
namespace CEGUI { class Window; class Imageset; class RadioButton; }
class CGameUI; class CResourceManager; class CDynamicPropertyFile; class CSkillTooltip;
// Partial data declaration through fields used by updateLayout.
class CGenericModel;
class CSettings;
namespace Ogre { class RenderWindow; class SceneManager; }
class CSkillMenu : public CSubMenu {
public:
    void createMenus();
    void mapEventHandlers(CEGUI::Window*);
    bool handle_MouseThrough(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    CSkillMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

 virtual ~CSkillMenu();
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
 virtual void onClick(ELayoutFunction);
 bool handle_SetSkill(const CEGUI::EventArgs&);
 bool handle_SpendSkill(const CEGUI::EventArgs&);
 bool handle_MouseOver(const CEGUI::EventArgs&);
 bool handle_MouseOut(const CEGUI::EventArgs&);
 char m_Data10[8];
 CEGUI::Window* m_pBackground;
 CEGUI::Window* m_pTopFrame;
 CEGUI::Window* m_pBottomFrame;
 CCharacter* m_pOwner;
 bool m_bOpenPartial;
 char m_Data39[15];
 CDynamicPropertyFile* m_pProperties;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 CGenericModel* m_pModel;
 CResourceManager* m_pResourceManager;
 char m_Data70[8];
 CEGUI::Imageset* m_pImages;
 char m_Data80[8];
 CEGUI::Window* m_pSkillPoints;
 CEGUI::Window* m_Panes[4];
 CEGUI::RadioButton* m_Tabs[3];
 CEGUI::Window* m_TabLabels[3];
 int m_iPane;
 char m_DataE4[12];
 long long m_SkillGuids[100];
 long long m_SpellGuids[100];
 char m_Data730[8];
 TArrayList<CEGUI::Window*> m_Children;
 CSkillTooltip* m_pTooltip;
};
#endif
