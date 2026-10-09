// CGameUI::create phase, aa3117..aa3ac8.
#ifndef OTL_GAMEUI_STARTUP_MENUS_H
#define OTL_GAMEUI_STARTUP_MENUS_H
#include "startup_skills.h"
#include "InventoryMenu.h"
#include "SkillMenu.h"
#include "JournalMenu.h"
#include "QuestMenu.h"
#include "MerchantMenu.h"
#include "EnchantMenu.h"
#include "CombineMenu.h"
#include "StashMenu.h"
#include "StatsMenu.h"
#include "PetMenu.h"
#include "OptionsMenu.h"
#include "SettingsMenu.h"
#include "DieMenu.h"
#include "WaypointMenu.h"
#include "DialogMenu.h"
#include "QuestDialogMenu.h"
#include "CinematicMenu.h"
#include "ModalMenu.h"
#include "TipMenu.h"
#include "InteractiveMenu.h"
#include "FishingMenu.h"
namespace gameui_create_detail {
struct SceneState {
    char prefix[0x10];
    Ogre::Camera* camera;
    Ogre::SceneManager* mainScene;
    Ogre::SceneManager* inventoryScene;
    Ogre::SceneManager* petScene;
};
typedef char scene_inventory[__builtin_offsetof(SceneState,inventoryScene)==0x20?1:-1];
typedef char scene_pet[__builtin_offsetof(SceneState,petScene)==0x28?1:-1];
struct MenuState {
    char gap0[0x4d8];
    CInventoryMenu* inventory;
    CStatsMenu* stats;
    CPetMenu* pet;
    CMerchantMenu* merchant;
    CEnchantMenu* enchant;
    CCombineMenu* combine;
    CStashMenu* stash;
    COptionsMenu* options;
    CSettingsMenu* settings;
    CDieMenu* die;
    CWaypointMenu* waypoint;
    CDialogMenu* dialog;
    CQuestDialogMenu* questDialog;
    CCinematicMenu* cinematic;
    CModalMenu* modal;
    CTipMenu* tip;
    CSkillMenu* skill;
    CJournalMenu* journal;
    CQuestMenu* quest;
    CInteractiveMenu* interactive;
    CFishingMenu* fishing;
    char gap580[0x1308-0x580];
    CResourceManager* resources;
    char gap1310[0x1930-0x1310];
    std::vector<CSubMenu*> submenus;
    std::vector<CDropdownMenu*> dropdowns;
};
typedef char menu_inventory[__builtin_offsetof(MenuState,inventory)==0x4d8?1:-1];
typedef char menu_skill[__builtin_offsetof(MenuState,skill)==0x558?1:-1];
typedef char menu_journal[__builtin_offsetof(MenuState,journal)==0x560?1:-1];
typedef char menu_quest[__builtin_offsetof(MenuState,quest)==0x568?1:-1];
typedef char menu_merchant[__builtin_offsetof(MenuState,merchant)==0x4f0?1:-1];
typedef char menu_enchant[__builtin_offsetof(MenuState,enchant)==0x4f8?1:-1];
typedef char menu_combine[__builtin_offsetof(MenuState,combine)==0x500?1:-1];
typedef char menu_stash[__builtin_offsetof(MenuState,stash)==0x508?1:-1];
typedef char menu_stats[__builtin_offsetof(MenuState,stats)==0x4e0?1:-1];
typedef char menu_pet[__builtin_offsetof(MenuState,pet)==0x4e8?1:-1];
typedef char menu_options[__builtin_offsetof(MenuState,options)==0x510?1:-1];
typedef char menu_settings[__builtin_offsetof(MenuState,settings)==0x518?1:-1];
typedef char menu_die[__builtin_offsetof(MenuState,die)==0x520?1:-1];
typedef char menu_waypoint[__builtin_offsetof(MenuState,waypoint)==0x528?1:-1];
typedef char menu_dialog[__builtin_offsetof(MenuState,dialog)==0x530?1:-1];
typedef char menu_questDialog[__builtin_offsetof(MenuState,questDialog)==0x538?1:-1];
typedef char menu_cinematic[__builtin_offsetof(MenuState,cinematic)==0x540?1:-1];
typedef char menu_modal[__builtin_offsetof(MenuState,modal)==0x548?1:-1];
typedef char menu_tip[__builtin_offsetof(MenuState,tip)==0x550?1:-1];
typedef char menu_interactive[__builtin_offsetof(MenuState,interactive)==0x570?1:-1];
typedef char menu_fishing[__builtin_offsetof(MenuState,fishing)==0x578?1:-1];
typedef char menu_resources[__builtin_offsetof(MenuState,resources)==0x1308?1:-1];
typedef char menu_submenus[__builtin_offsetof(MenuState,submenus)==0x1930?1:-1];
typedef char menu_dropdowns[__builtin_offsetof(MenuState,dropdowns)==0x1948?1:-1];
inline __attribute__((always_inline)) void createMenus(CGameUI* self,PrefixState& ui,SceneState& scenes,SheetState& sheets,MenuState& menus) {
    {
        CInventoryMenu* created=new CInventoryMenu(*self,*ui.settings,ui.renderWindow,ui.scene,scenes.inventoryScene,sheets.ingame,menus.resources);
        menus.inventory=created;
        menus.submenus.push_back(created);
    }
    {
        CSkillMenu* created=new CSkillMenu(*self,*ui.settings,ui.renderWindow,ui.scene,scenes.inventoryScene,sheets.ingame,menus.resources);
        menus.skill=created;
        menus.submenus.push_back(created);
    }
    {
        CJournalMenu* created=new CJournalMenu(*self,*ui.settings,ui.renderWindow,ui.scene,scenes.inventoryScene,sheets.ingame,menus.resources);
        menus.journal=created;
        menus.submenus.push_back(created);
    }
    {
        CQuestMenu* created=new CQuestMenu(*self,*ui.settings,ui.renderWindow,ui.scene,scenes.inventoryScene,sheets.ingame,menus.resources);
        menus.quest=created;
        menus.submenus.push_back(created);
    }
    {
        CMerchantMenu* created=new CMerchantMenu(*self,*ui.settings,ui.renderWindow,ui.scene,sheets.ingame,menus.resources);
        menus.merchant=created;
        menus.submenus.push_back(created);
    }
    {
        CEnchantMenu* created=new CEnchantMenu(*self,*ui.settings,ui.renderWindow,ui.scene,sheets.ingame,menus.resources);
        menus.enchant=created;
        menus.submenus.push_back(created);
    }
    {
        CCombineMenu* created=new CCombineMenu(*self,*ui.settings,ui.renderWindow,ui.scene,sheets.ingame,menus.resources);
        menus.combine=created;
        menus.submenus.push_back(created);
    }
    {
        CStashMenu* created=new CStashMenu(*self,*ui.settings,ui.renderWindow,ui.scene,sheets.ingame,menus.resources);
        menus.stash=created;
        menus.submenus.push_back(created);
    }
    {
        CStatsMenu* created=new CStatsMenu(*self,*ui.settings,ui.renderWindow,ui.scene,sheets.ingame,menus.resources);
        menus.stats=created;
        menus.submenus.push_back(created);
    }
    {
        CPetMenu* created=new CPetMenu(*self,*ui.settings,ui.renderWindow,ui.scene,scenes.petScene,sheets.ingame,menus.resources);
        menus.pet=created;
        menus.submenus.push_back(created);
    }
    {
        COptionsMenu* created=new COptionsMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.options=created;
        menus.dropdowns.push_back(created);
    }
    {
        CSettingsMenu* created=new CSettingsMenu(*self,*ui.settings,ui.scene,sheets.sheet,menus.resources);
        menus.settings=created;
        menus.dropdowns.push_back(created);
    }
    {
        CDieMenu* created=new CDieMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.die=created;
        menus.dropdowns.push_back(created);
    }
    {
        CWaypointMenu* created=new CWaypointMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.waypoint=created;
        menus.dropdowns.push_back(created);
    }
    {
        CDialogMenu* created=new CDialogMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.dialog=created;
        menus.dropdowns.push_back(created);
    }
    {
        CQuestDialogMenu* created=new CQuestDialogMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.questDialog=created;
        menus.dropdowns.push_back(created);
    }
    {
        CCinematicMenu* created=new CCinematicMenu(*self,*ui.settings,ui.scene,sheets.sheet,menus.resources);
        menus.cinematic=created;
        menus.dropdowns.push_back(created);
    }
    {
        CModalMenu* created=new CModalMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.modal=created;
        menus.dropdowns.push_back(created);
    }
    {
        CTipMenu* created=new CTipMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.tip=created;
        menus.dropdowns.push_back(created);
    }
    {
        CInteractiveMenu* created=new CInteractiveMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.interactive=created;
    }
    {
        CFishingMenu* created=new CFishingMenu(*self,*ui.settings,ui.scene,sheets.ingame,menus.resources);
        menus.fishing=created;
    }
    self->setInteractiveMenuVisible(false);
}
}
#endif
