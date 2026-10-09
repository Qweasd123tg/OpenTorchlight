#ifndef STATSMENU_H
#define STATSMENU_H
#include "SubMenu.h"
#include <CEGUIUDim.h>
#include <string>
namespace CEGUI { class Window; }
class CGameUI;class CResourceManager;class CDynamicPropertyFile;class CGenericModel;
namespace Ogre {class SceneManager;class RenderWindow;}
// Partial through the fields used by update(float); allocation size not asserted.
class CSettings;
class CStatsMenu : public CSubMenu {
public:
    CStatsMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

 virtual ~CStatsMenu();
 virtual CBaseUnit* getOwner();
 virtual bool isRight();
 virtual bool open();
 virtual bool openPartial();
 virtual float screenEdge();
 virtual void setOwner(CCharacter*);
 virtual void setOpen(bool);
 virtual void updateLayout();
 virtual void update(float);
 virtual bool processInput(void*,float,bool);
 CEGUI::Window* m_pParent;
 CEGUI::Window* m_pRoot;
 CEGUI::Window* m_pTopPanel;
 CEGUI::Window* m_pBottomPanel;
 CEGUI::Window* m_pExperienceBar;
 CEGUI::Window* m_pFameBar;
 CEGUI::UDim m_ExperienceWidth;
 CEGUI::UDim m_ExperienceHeight;
 CEGUI::UDim m_FameWidth;
 CEGUI::UDim m_FameHeight;
 CCharacter* m_pOwner;
 bool m_bOpenPartial;
 bool m_bFullyClosed;
 bool m_bInputFlag;
 char m_Data6B[5];
 CDynamicPropertyFile* m_pProperties;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 Ogre::RenderWindow* m_pRenderWindow;
 CEGUI::Window* m_pNameText;
 CEGUI::Window* m_pFameTitleText;
 std::wstring m_TextA0;
 std::wstring m_DamageDescription;
 std::wstring m_TextB0;
 std::wstring m_ArmorDescription;
 CEGUI::Window* m_pLevelText;
 CEGUI::Window* m_pFameLevelText;
 CEGUI::Window* m_AttributeTexts[4];
 CEGUI::Window* m_DamageTexts[3];
 CEGUI::Window* m_pArmorText;
 CEGUI::Window* m_pManaText;
 CEGUI::Window* m_pHealthText;
 CEGUI::Window* m_pExperienceText;
 CEGUI::Window* m_pFameText;
 CEGUI::Window* m_pPointsText;
 CEGUI::Window* m_ResistanceTexts[4];
 CEGUI::Window* m_pPointsContainer;
 CEGUI::Window* m_SpendButtons[4];
 CEGUI::Window* m_ReclaimButtons[4];
 CGenericModel* m_pModel;
 CResourceManager* m_pResourceManager;
 float m_fScreenEdge;
 char m_Data1B4[12];
 int m_InvestedPoints[4];
};
#endif
