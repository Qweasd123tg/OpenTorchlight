#ifndef GAMEUI_H
#define GAMEUI_H
#include <string>
#include <vector>
class CCinematicMenu;
class CConsole;
class CDialogMenu;
class CDieMenu;
class CDropdownMenu;
class CDynamicPropertyFile;
class CInventoryMenu;
class CJournalMenu;
class CMenuManager;
class CModalMenu;
class COptionsMenu;
class CPetMenu;
class CQuestDialogMenu;
class CQuestMenu;
class CSettingsMenu;
class CSkillFoldout;
class CSkillMenu;
class CStatsMenu;
class CTipMenu;
class CWaypointMenu;

#include "GameEnums.h"
#include "RunicCore.h"

enum ELayoutFunction { LAYOUT_FUNCTION_EXIT_GAME = 0 };

// Partial: size 0x1a08 is the allocation at 0x5790e2. Complete vtable shape.
// onClick returns bool through the original CEGUI callback (consumed as AL).
namespace CEGUI { class Image; class Window; class EventArgs; class colour; }
class CGameClient;
class CLevel;
class CSubMenu;
class CItem;
namespace Ogre { class RenderWindow; class Vector3; class Matrix4; }
class CTextEvent;
class CCharacter;
class CEquipment;
class CEquipmentTooltip;
class iMenuListener;

class CGameUI : public CRunicCore
{
public:
    bool processInput(CGameClient*,void*,float,bool);
    void notifyOfDeletion(CItem*);
    void notifyOfDeletion(CCharacter*);
    void mouseEvent(unsigned int,unsigned int);
    void keyEvent(unsigned int,unsigned int,long);
    void setWindowActive(bool);

    void clearGameStateRequest();
    bool getDieMenuIsOpen();
    bool questDialogOpen();
    bool isCinematicMenuOpen();
    void hideModalDialogs();
    bool tipMenuOpen();
    bool modalDialogOpen();
    bool leftCovered();
    bool rightCovered();
    bool bothCovered();
    void toggleStatFill();
    CEquipment* getMouseOverItem();
    void flushProcessInput();
    void refreshQuestMenu();
    void closeCinematicMenu();
    void clickLeft();
    bool handle_MouseOut(const CEGUI::EventArgs& event);
    void removeMenuListener(EMENU_TYPE type, iMenuListener* listener);
    float scaledX(float value);
    bool getConsoleIsOpen();
    void setRightButtonPressed();
    void flushInput();
    void setActiveMenu(EMenu menu);
    void reloadMenuCharacters();
    bool handle_ToggleOptions(const CEGUI::EventArgs& event);
    void toggleSettings();
    bool handle_ToggleQuest(const CEGUI::EventArgs& event);
    bool handle_ToggleJournal(const CEGUI::EventArgs& event);
    bool handle_ToggleSkill(const CEGUI::EventArgs& event);
    bool handle_ToggleInventory(const CEGUI::EventArgs& event);
    void toggleOptions();
    void toggleDeath();
    void toggleWaypointMenu();
    void toggleDialog();
    float leftScreenEdge();
    float rightScreenEdge();
    bool handle_TogglePet(const CEGUI::EventArgs& event);
    bool handle_ToggleStats(const CEGUI::EventArgs& event);
    bool handle_ToggleMap(const CEGUI::EventArgs& event);
    CGameClient* getGameClient() { return m_gameClient; }
    void requestSetGameState(EGameState, EMenu);
    bool processIngameInput(void*,float,bool);
    bool bothCoveredPartial();
    bool eitherCoveredPartial();
    bool modalDialogOpenPartial();
    void captureProcessInput();
    void handleKeyPresses();
    void toggleConsole();
    void toggleInventory();
    void toggleJournal();
    void togglePet();
    void toggleQuest();
    void toggleSkill();
    void toggleStats();

    void togglePause();
    void unPause();
    void useItem(CLevel&,CEquipment*);
    void performItemUse(CLevel&,CEquipment*,CCharacter*,CCharacter*,CCharacter*);
    void showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*);
    float getWindowWidth();
    float getWindowHeight();
    void updateIngameUI(float, CGameClient*, Ogre::RenderWindow*);
    void convertToScreenScale(CEGUI::Window*, bool);
    void mapToFunctions(CEGUI::Window*);
    void statsChanged();
    virtual ~CGameUI();
    bool create();
    bool handle_MouseThrough(const CEGUI::EventArgs&);
    bool handle_onClick(const CEGUI::EventArgs&);
    bool handle_ToggleItemNames(const CEGUI::EventArgs&);
    bool handle_MouseOver(const CEGUI::EventArgs&);
    bool handle_ClickThrough(const CEGUI::EventArgs&);
    bool handle_SkillSelectMouseOver(const CEGUI::EventArgs&);
    bool handle_SkillSelectMouseOut(const CEGUI::EventArgs&);
    bool handle_SkillSelectClick(const CEGUI::EventArgs&);
    bool handle_SkillMouseOver(const CEGUI::EventArgs&);
    bool handle_SkillMouseOut(const CEGUI::EventArgs&);
    bool handle_SkillClick(const CEGUI::EventArgs&);
    float getAspectRatio();
    void mapEventHandlers(CEGUI::Window*);
    void toggleFPS();
    void updateSlots();
    bool menuItemClick(CCharacter*, CSubMenu*, int, bool);
    void returnDraggedItem();
    void setCursorState(ECursorState);
    void setMouseOverItem(CItem*, bool);
    void updateHardwareCursor();
    virtual bool onClick(ELayoutFunction);
    static CGameUI* getSingleton();
    CCharacter* getCharacter() { return m_pCharacter; }
    void queueTip(EContextTip tip);
    float scaledY(float value);
    const CEGUI::Image* getImageFromImageSet(const unsigned char* name);
    void clearMenuMouseOvers();
    void openModalDialog(std::wstring,std::wstring,bool);
    void closeLeft();
    void closeRight();
    void closeMenus();
    void closeAll();
    void setInteractiveMenuVisible(bool visible);
    int getUIIsInCinematic();
    void returnTextEventObject(CTextEvent* event);
    Ogre::Vector3 getScreenPosition(const Ogre::Vector3*, const Ogre::Vector3*, Ogre::Matrix4);
    void hideTextEvents();
    void updateTextEvents(float, Ogre::Vector3&, Ogre::Matrix4&, bool);
    void addTextEvent(const Ogre::Vector3&, const std::string&, float, float, CEGUI::colour, CEGUI::colour);
    // Pointer return verified at original 0xa9bff5; parameters from its mangled name.
    CTextEvent* getTextEventObject(const Ogre::Vector3&, const std::string&, float, float, CEGUI::colour, CEGUI::colour, bool);
    void addMenuListener(EMENU_TYPE menu, iMenuListener* listener);
    void setCinematicOpen(std::wstring cinematic);
private:
    friend class CDieMenu;
    friend class COptionsMenu;
    friend class CContinueGameMenu;
    friend class CDifficultyMenu;
    friend class CMainMenu;
    friend class CNewGameMenu;
    friend class CWaypointMenu;
    unsigned char m_gap10[0x28];
    CCharacter* m_pCharacter;
    CLevel* m_level;
    unsigned char m_gap48[0x20];
    CEquipment* m_mouseOverItem;
    unsigned char m_gap70[0x8];
    CDynamicPropertyFile* m_settings;
    unsigned char m_gap80[0x60];
    CEGUI::Window* m_statsWindow;
    unsigned char m_gapE8[0x50];
    CEGUI::Window* m_topWindow;
    unsigned char m_gap140[0x330];
    CEGUI::Window* m_rootWindow;
    unsigned char m_gap478[0x48];
    CSkillFoldout* m_foldout;
    unsigned char m_gap4C8[0x10];
    CInventoryMenu* m_statsMenu;
    CStatsMenu* m_characterStatsMenu;
    CPetMenu* m_inventoryMenu;
    unsigned char m_gap4F0[0x20];
    COptionsMenu* m_optionsMenu;
    CSettingsMenu* m_dialogMenu;
    CDieMenu* m_dieMenu;
    CWaypointMenu* m_waypointMenu;
    CDialogMenu* m_dropdown530;
    CQuestDialogMenu* m_questDialogMenu;
    CCinematicMenu* m_cinematicMenu;
    CModalMenu* m_dropdown548;
    CTipMenu* m_tipMenu;
    CSkillMenu* m_skillsMenu;
    CJournalMenu* m_journalMenu;
    CQuestMenu* m_questMenu;
    unsigned char m_gap570[0x18];
    CMenuManager* m_menuManager;
    unsigned char m_gap590[0xd68];
    bool m_displayStats;
    bool m_bExitButtonPressed;
    unsigned char m_gap12FA;
    bool m_mouseThrough;
    ECursorState m_cursorState;
    unsigned char m_gap1300[0x341];
    bool m_itemHovered;
    bool m_foldoutItemHovered;
    bool m_skillHovered;
    unsigned char m_gap1644[0x14];
    long long m_foldoutItemGuid;
    bool m_foldoutSkillHovered;
    unsigned char m_gap1661[0x7];
    long long m_foldoutSkillGuid;
    unsigned char m_gap1670[0x4];
    int m_leftSlot;
    int m_rightSlot;
    int m_pendingRightSlot;
    float m_usableWidthRatio; // +0x1680
    float m_cachedWindowWidth; // +0x1684
    float m_cachedWindowHeight; // +0x1688
    unsigned char m_gap168C[4];
    CConsole* m_console;
    unsigned char m_gap1698[0x30];
    int m_cachedPetMode; // +0x16c8
    unsigned char m_gap16CC[0x1914-0x16cc];
    EGameState m_requestedGameState;
    EMenu m_requestedMenu;
    unsigned char m_gap191C[4];
    CGameClient* m_gameClient;
    unsigned char m_gap1928[8];
    std::vector<CSubMenu*> m_submenus;
    std::vector<CDropdownMenu*> m_dropdowns;
    unsigned char m_gap1960[0x39];
    bool m_paused;
    unsigned char m_gap199A[0x6e];
};
#endif
