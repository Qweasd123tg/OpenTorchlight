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
#include "KeyManager.h"
#include "MouseManager.h"
class CMerchantMenu;
class CEnchantMenu;
class CCombineMenu;
class CStashMenu;
class CSettings;
class CResourceManager;
class CSoundBank;
class CSoundManager;
class CSkillTooltip;
class CInteractiveMenu;
class CFishingMenu;
struct SDL_Cursor;
namespace CEGUI { class OgreCEGUIRenderer; class System; }
namespace gameui_create_detail { struct TextEventList; }
struct CGameUILayoutAudit;

enum ELayoutFunction { LAYOUT_FUNCTION_EXIT_GAME = 0 };

// Partial: size 0x1a08 is the allocation at 0x5790e2. Complete vtable shape.
// onClick returns bool through the original CEGUI callback (consumed as AL).
namespace CEGUI { class Combobox; class Imageset; class Image; class Window; class EventArgs; class colour; }
class CGameClient;
class CLevel;
class CSubMenu;
class CItem;
namespace Ogre { class RenderWindow; class Camera; class SceneManager; class Vector3; class Matrix4; }
class CTextEvent;
class CCharacter;
class CPlayer;
class CBaseUnit;
class CQuest;
class CEquipment;
class CEquipmentTooltip;
class iMenuListener;

class CGameUI : public CRunicCore
{
public:
    CGameUI(CSettings&, CGameClient&, void*, Ogre::RenderWindow*, Ogre::Camera*, Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CResourceManager*);
    bool processInput(CGameClient*,void*,float,bool);
    bool processMenuInput(void*, float, bool);
    void updateMenuUI(float, CGameClient*, Ogre::RenderWindow*);
    void update(float, CGameClient*, Ogre::RenderWindow*);
    void notifyOfDeletion(CItem*);
    void notifyOfDeletion(CCharacter*);
    void mouseEvent(unsigned int,unsigned int);
    void keyEvent(unsigned int,unsigned int,long);
    void setWindowActive(bool);

    void cleanupReferences();
    void setLoadingVisible(bool);
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
    void activateItemSlot(int, bool);
    bool handle_MouseOut(const CEGUI::EventArgs& event);
    void removeMenuListener(EMENU_TYPE type, iMenuListener* listener);
    float scaledX(float value);
    bool getConsoleIsOpen();
    void setRightButtonPressed();
    void flushInput();
    void setActiveMenu(EMenu menu);
    void reloadMenuCharacters();
    bool handle_ToggleOptions(const CEGUI::EventArgs& event);
    bool canLoad();
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
    bool mouseOverPanel(int x, int y);
    void sizeComboList(CEGUI::Combobox*);
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
    void setPlayer(CCharacter*);
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
    void addImageSet(CEGUI::Imageset* imageset);
    CEGUI::Imageset* getImageSetForIcon(const unsigned char* name);
    const CEGUI::Image* getImageFromImageSet(const unsigned char* name);
    void clearMenuMouseOvers();
    void setSmallText(std::wstring text, float duration);
    void setBigText(std::wstring text, float duration);
    void forceInteractiveDialog(CPlayer*, CBaseUnit*, CQuest*);
    void openModalDialog(std::wstring,std::wstring,bool);
    void closeLeft();
    void closeRight();
    void closeMenus();
    void closeAll();
    void setInteractiveMenuVisible(bool visible);
    void setIngameUIVisible(bool visible);
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
    friend class CDropdownMenu;
    friend class CDieMenu;
    friend class COptionsMenu;
    friend class CContinueGameMenu;
    friend class CDifficultyMenu;
    friend class CMainMenu;
    friend class CNewGameMenu;
    friend class CWaypointMenu;
    friend struct CGameUILayoutAudit;
    Ogre::Camera* m_camera; // +0x10
    Ogre::SceneManager* m_mainScene; // +0x18
    Ogre::SceneManager* m_inventoryScene; // +0x20
    Ogre::SceneManager* m_petScene; // +0x28
    CSoundManager* m_soundManager; // +0x30, MasterResourceManager::m_pSoundManager at +0x98
    CCharacter* m_pCharacter;
    CLevel* m_level;
    TSafePointer<CCharacter> m_hoveredCharacter; // +0x48
    TSafePointer<CCharacter> m_selectedCharacter; // +0x58
    TSafePointer<CItem> m_mouseOverItem; // +0x68
    CDynamicPropertyFile* m_settings;
    TSafePointer<CEquipment> m_targetedItem; // +0x80
    TSafePointer<CCharacter> m_reference90;
    TSafePointer<CCharacter> m_referenceA0;
    long long m_guidB0;
    TSafePointer<CEquipment> m_draggedItem; // +0xb8
    TSafePointer<CCharacter> m_dragOwner; // +0xc8
    unsigned char m_gapD8[8];
    CEGUI::Window* m_statsWindow;
    CEGUI::Window* m_targetName; // +0xe8
    CEGUI::Window* m_targetDescription; // +0xf0
    CEGUI::Window* m_targetLevel; // +0xf8
    unsigned char m_gap100[0x20];
    CEGUI::Window* m_targetHealth; // +0x120
    CEGUI::Window* m_targetBar; // +0x128
    unsigned char m_gap130[0x8];
    CEGUI::Window* m_topWindow;
    CEGUI::Window* m_healthWindow; // +0x140
    unsigned char m_gap148[0x10];
    CEGUI::Window* m_manaWindow; // +0x158
    unsigned char m_gap160[0x10];
    CEGUI::Window* m_petWindow; // +0x170
    unsigned char m_gap178[0x8];
    CEGUI::Window* m_petHealthWindow; // +0x180
    unsigned char m_gap188[0x8];
    CEGUI::Window* m_petManaWindow; // +0x190
    unsigned char m_gap198[0x38];
    CEGUI::Window* m_experienceWindow; // +0x1d0
    unsigned char m_gap1D8[0x50];
    long long m_leftGuid; // +0x228
    unsigned long long m_word230; // Stored as one 64-bit zero; semantic role remains unconfirmed.
    unsigned char m_gap238[0x20];
    unsigned long long m_word258; // Stored as one 64-bit zero; semantic role remains unconfirmed.
    unsigned char m_gap260[0x1c8];
    CEGUI::OgreCEGUIRenderer* m_renderer; // +0x428
    CEGUI::System* m_ceguiSystem; // +0x430
    CEGUI::Imageset* m_guiLook; // +0x438
    TArrayList<std::wstring> m_itemIconFiles; // +0x440, growBy=25
    TArrayList<CEGUI::Imageset*> m_itemImagesets; // +0x458, growBy=5
    CEGUI::Window* m_rootWindow;
    unsigned char m_gap478[0x4a0-0x478];
    CEquipmentTooltip* m_equipmentTooltip;
    CEquipmentTooltip* m_compareFirst;
    CEquipmentTooltip* m_compareSecond;
    CSkillTooltip* m_skillTooltip;
    CSkillFoldout* m_foldout;
    unsigned char m_gap4C8[8];
    Ogre::RenderWindow* m_renderWindow; // +0x4d0
    CInventoryMenu* m_statsMenu;
    CStatsMenu* m_characterStatsMenu;
    CPetMenu* m_inventoryMenu;
    CMerchantMenu* m_merchantMenu; // +0x4f0
    CEnchantMenu* m_enchantMenu; // +0x4f8
    CCombineMenu* m_combineMenu; // +0x500
    CStashMenu* m_stashMenu; // +0x508
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
    CInteractiveMenu* m_interactiveMenu;
    CFishingMenu* m_fishingMenu;
    CEGUI::Imageset* m_statsImageset;
    CMenuManager* m_menuManager;
    CKeyManager m_keys; // +0x590, sizeof=0xd18
    CMouseManager m_mouse; // +0x12a8, sizeof=0x50
    bool m_displayStats;
    bool m_bExitButtonPressed;
    unsigned char m_gap12FA;
    bool m_mouseThrough;
    ECursorState m_cursorState;
    void* m_window; // +0x1300
    CResourceManager* m_resources; // +0x1308
    unsigned char m_gap1310[0x330];
    bool m_labelHovered; // +0x1640
    bool m_itemHovered;
    bool m_foldoutItemHovered;
    bool m_skillHovered;
    unsigned char m_gap1644[0x4];
    long long m_hoveredSkillGuid; // +0x1648
    long long m_hoveredItemGuid; // +0x1650
    long long m_foldoutItemGuid;
    bool m_foldoutSkillHovered;
    unsigned char m_gap1661[0x7];
    long long m_foldoutSkillGuid;
    bool m_inputCaptured; // +0x1670
    unsigned char m_gap1671[0x3];
    int m_leftSlot;
    int m_rightSlot;
    int m_pendingRightSlot;
    float m_usableWidthRatio; // +0x1680
    float m_cachedWindowWidth; // +0x1684
    float m_cachedWindowHeight; // +0x1688
    unsigned char m_gap168C[4];
    CConsole* m_console;
    gameui_create_detail::TextEventList* m_freeEvents;
    gameui_create_detail::TextEventList* m_activeEvents;
    CSoundBank* m_soundBank;
    std::wstring m_name16B0;
    std::wstring m_name16B8;
    std::wstring m_text16C0;
    int m_cachedPetMode; // +0x16c8
    unsigned char m_gap16CC[0xc0];
    int m_interactiveMenuUsers; // +0x178c
    int m_slotIndices[97]; // +0x1790
    EGameState m_requestedGameState;
    EMenu m_requestedMenu;
    unsigned char m_gap191C[4];
    CGameClient* m_gameClient;
    int m_returnToTownOption; // +0x1928
    unsigned char m_gap192C[4];
    std::vector<CSubMenu*> m_submenus;
    std::vector<CDropdownMenu*> m_dropdowns;
    std::vector<EContextTip> m_queuedTips; // +0x1960
    std::wstring m_smallText; // +0x1978
    float m_smallDuration; // +0x1980
    float m_smallElapsed; // +0x1984
    std::wstring m_bigText; // +0x1988
    float m_bigDuration; // +0x1990
    float m_bigElapsed; // +0x1994
    unsigned char m_gap1998;
    bool m_paused;
    unsigned char m_gap199A[0x19f0-0x199a];
    std::vector<SDL_Cursor*> m_cursors;
};
struct CGameUILayoutAudit {
#define UI_OFFSET(F,O) typedef char offset_##F[__builtin_offsetof(CGameUI,F)==O?1:-1]
UI_OFFSET(m_camera,0x10);
UI_OFFSET(m_mainScene,0x18);
UI_OFFSET(m_inventoryScene,0x20);
UI_OFFSET(m_petScene,0x28);
UI_OFFSET(m_soundManager,0x30);
UI_OFFSET(m_pCharacter,0x38);
UI_OFFSET(m_level,0x40);
UI_OFFSET(m_hoveredCharacter,0x48);
UI_OFFSET(m_selectedCharacter,0x58);
UI_OFFSET(m_mouseOverItem,0x68);
UI_OFFSET(m_settings,0x78);
UI_OFFSET(m_targetedItem,0x80);
UI_OFFSET(m_reference90,0x90);
UI_OFFSET(m_referenceA0,0xa0);
UI_OFFSET(m_guidB0,0xb0);
UI_OFFSET(m_draggedItem,0xb8);
UI_OFFSET(m_dragOwner,0xc8);
UI_OFFSET(m_statsWindow,0xe0);
UI_OFFSET(m_topWindow,0x138);
UI_OFFSET(m_renderer,0x428);
UI_OFFSET(m_ceguiSystem,0x430);
UI_OFFSET(m_guiLook,0x438);
UI_OFFSET(m_itemIconFiles,0x440);
UI_OFFSET(m_itemImagesets,0x458);
UI_OFFSET(m_rootWindow,0x470);
UI_OFFSET(m_equipmentTooltip,0x4a0);
UI_OFFSET(m_compareFirst,0x4a8);
UI_OFFSET(m_compareSecond,0x4b0);
UI_OFFSET(m_skillTooltip,0x4b8);
UI_OFFSET(m_foldout,0x4c0);
UI_OFFSET(m_renderWindow,0x4d0);
UI_OFFSET(m_statsMenu,0x4d8);
UI_OFFSET(m_characterStatsMenu,0x4e0);
UI_OFFSET(m_inventoryMenu,0x4e8);
UI_OFFSET(m_optionsMenu,0x510);
UI_OFFSET(m_interactiveMenu,0x570);
UI_OFFSET(m_fishingMenu,0x578);
UI_OFFSET(m_statsImageset,0x580);
UI_OFFSET(m_menuManager,0x588);
UI_OFFSET(m_keys,0x590);
UI_OFFSET(m_mouse,0x12a8);
UI_OFFSET(m_displayStats,0x12f8);
UI_OFFSET(m_cursorState,0x12fc);
UI_OFFSET(m_window,0x1300);
UI_OFFSET(m_resources,0x1308);
UI_OFFSET(m_itemHovered,0x1641);
UI_OFFSET(m_foldoutItemGuid,0x1658);
UI_OFFSET(m_leftSlot,0x1674);
UI_OFFSET(m_console,0x1690);
UI_OFFSET(m_freeEvents,0x1698);
UI_OFFSET(m_activeEvents,0x16a0);
UI_OFFSET(m_soundBank,0x16a8);
UI_OFFSET(m_name16B0,0x16b0);
UI_OFFSET(m_name16B8,0x16b8);
UI_OFFSET(m_text16C0,0x16c0);
UI_OFFSET(m_cachedPetMode,0x16c8);
UI_OFFSET(m_requestedGameState,0x1914);
UI_OFFSET(m_gameClient,0x1920);
UI_OFFSET(m_returnToTownOption,0x1928);
UI_OFFSET(m_submenus,0x1930);
UI_OFFSET(m_dropdowns,0x1948);
UI_OFFSET(m_queuedTips,0x1960);
UI_OFFSET(m_smallText,0x1978);
UI_OFFSET(m_bigText,0x1988);
UI_OFFSET(m_paused,0x1999);
UI_OFFSET(m_cursors,0x19f0);
UI_OFFSET(m_targetName,0xe8);
UI_OFFSET(m_targetDescription,0xf0);
UI_OFFSET(m_targetLevel,0xf8);
UI_OFFSET(m_targetHealth,0x120);
UI_OFFSET(m_targetBar,0x128);
UI_OFFSET(m_healthWindow,0x140);
UI_OFFSET(m_manaWindow,0x158);
UI_OFFSET(m_petWindow,0x170);
UI_OFFSET(m_petHealthWindow,0x180);
UI_OFFSET(m_petManaWindow,0x190);
UI_OFFSET(m_experienceWindow,0x1d0);
UI_OFFSET(m_leftGuid,0x228);
UI_OFFSET(m_word230,0x230);
UI_OFFSET(m_word258,0x258);
UI_OFFSET(m_merchantMenu,0x4f0);
UI_OFFSET(m_enchantMenu,0x4f8);
UI_OFFSET(m_combineMenu,0x500);
UI_OFFSET(m_stashMenu,0x508);
UI_OFFSET(m_labelHovered,0x1640);
UI_OFFSET(m_hoveredSkillGuid,0x1648);
UI_OFFSET(m_hoveredItemGuid,0x1650);
UI_OFFSET(m_inputCaptured,0x1670);
UI_OFFSET(m_interactiveMenuUsers,0x178c);
UI_OFFSET(m_slotIndices,0x1790);
#undef UI_OFFSET
};
typedef char gameui_lifetime_size[sizeof(CGameUI)==0x1a08?1:-1];
typedef char gameui_mouse_size[sizeof(CMouseManager)==0x50?1:-1];
typedef char gameui_wstring_size[sizeof(std::wstring)==8?1:-1];

#endif
