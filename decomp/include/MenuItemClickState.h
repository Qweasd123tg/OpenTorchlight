// Private candidate field views for the original 0xa8f780 entry.
// These do not own or construct the objects they describe.
#ifndef OTL_MENU_ITEM_CLICK_STATE_H
#define OTL_MENU_ITEM_CLICK_STATE_H
#include "GameUI.h"
#include "Character.h"
#include "Equipment.h"
#include "SafePointer.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include "PetMenu.h"
#include "MerchantMenu.h"
#include "EnchantMenu.h"
#include "CombineMenu.h"
#include "StashMenu.h"
#include "EquipmentTooltip.h"
#include "ResourceManager.h"
#include "SoundBank.h"
#include "Player.h"
#include "SharedStash.h"
#include "Level.h"
#include "Achievements.h"
#include "Achievement.h"
#include "LinuxUtils.h"
#include <CEGUIWindow.h>
#include <CEGUISystem.h>
namespace menu_item_click_detail {
struct UIState {
    char prefix[0x38];
    CPlayer* player;
    CLevel* level;
    char gap48[0x80-0x48];
    TSafePointer<CEquipment> targetedItem;
    TSafePointer<CCharacter> targetCharacter;
    TSafePointer<CCharacter> itemUser;
    long long selectedSkill;
    TSafePointer<CEquipment> draggedItem;
    TSafePointer<CCharacter> dragOwner;
    int dragSlot;
    char gapDC[0x488-0xdc];
    CEGUI::Window* rootWindow;
    char gap490[8];
    CEGUI::Window* dragWindow;
    CEquipmentTooltip* tooltip;
    CEquipmentTooltip* comparisonTooltip1;
    CEquipmentTooltip* comparisonTooltip2;
    char gap4B8[0x4d8-0x4b8];
    CInventoryMenu* inventoryMenu;
    void* statsMenu;
    CPetMenu* petMenu;
    CMerchantMenu* merchantMenu;
    CEnchantMenu* enchantMenu;
    CCombineMenu* combineMenu;
    CStashMenu* stashMenu;
    char gap510[0x12d0-0x510];
    long long mouseX;
    long long mouseY;
    char gap12E0[0x1308-0x12e0];
    CResourceManager* resourceManager;
    char gap1310[0x16a8-0x1310];
    CSoundBank* soundBank;
};
struct ActorState {
    char prefix[0x298];
    CSoundBank* soundBank;
    char gap2A0[0x330-0x2a0];
    int aiState;
    char gap334[0x490-0x334];
    CInventory* inventory;
};
struct UnitIdentity { char prefix[0x1a0]; long long guid; };
template<unsigned Offset> struct HoverState { char prefix[Offset]; CEquipment* equipment; };
inline UIState& state(CGameUI* ui) { return *reinterpret_cast<UIState*>(ui); }
inline ActorState& actor(CCharacter* unit) { return *reinterpret_cast<ActorState*>(unit); }
inline long long guid(CEquipment* item) { return reinterpret_cast<UnitIdentity*>(item)->guid; }
template<unsigned Offset, class T> inline void clearHover(T* menu) {
    reinterpret_cast<HoverState<Offset>*>(menu)->equipment = NULL;
}
inline void clearHoverAndTooltips(UIState& ui) {
    clearHover<0x1020>(ui.inventoryMenu);
    clearHover<0x3438>(ui.merchantMenu);
    clearHover<0xf0>(ui.enchantMenu);
    clearHover<0x190>(ui.combineMenu);
    clearHover<0x3408>(ui.stashMenu);
    clearHover<0x1370>(ui.petMenu);
    ui.tooltip->m_iCachedItemGuid = -1;
    ui.comparisonTooltip1->m_iCachedItemGuid = -1;
    ui.comparisonTooltip2->m_iCachedItemGuid = -1;
}
typedef char check_ui_player[__builtin_offsetof(UIState,player)==56?1:-1];
typedef char check_ui_level[__builtin_offsetof(UIState,level)==64?1:-1];
typedef char check_ui_targetedItem[__builtin_offsetof(UIState,targetedItem)==128?1:-1];
typedef char check_ui_targetCharacter[__builtin_offsetof(UIState,targetCharacter)==144?1:-1];
typedef char check_ui_itemUser[__builtin_offsetof(UIState,itemUser)==160?1:-1];
typedef char check_ui_selectedSkill[__builtin_offsetof(UIState,selectedSkill)==176?1:-1];
typedef char check_ui_draggedItem[__builtin_offsetof(UIState,draggedItem)==184?1:-1];
typedef char check_ui_dragOwner[__builtin_offsetof(UIState,dragOwner)==200?1:-1];
typedef char check_ui_dragSlot[__builtin_offsetof(UIState,dragSlot)==216?1:-1];
typedef char check_ui_rootWindow[__builtin_offsetof(UIState,rootWindow)==1160?1:-1];
typedef char check_ui_dragWindow[__builtin_offsetof(UIState,dragWindow)==1176?1:-1];
typedef char check_ui_tooltip[__builtin_offsetof(UIState,tooltip)==1184?1:-1];
typedef char check_ui_comparisonTooltip1[__builtin_offsetof(UIState,comparisonTooltip1)==1192?1:-1];
typedef char check_ui_comparisonTooltip2[__builtin_offsetof(UIState,comparisonTooltip2)==1200?1:-1];
typedef char check_ui_inventoryMenu[__builtin_offsetof(UIState,inventoryMenu)==1240?1:-1];
typedef char check_ui_petMenu[__builtin_offsetof(UIState,petMenu)==1256?1:-1];
typedef char check_ui_merchantMenu[__builtin_offsetof(UIState,merchantMenu)==1264?1:-1];
typedef char check_ui_enchantMenu[__builtin_offsetof(UIState,enchantMenu)==1272?1:-1];
typedef char check_ui_combineMenu[__builtin_offsetof(UIState,combineMenu)==1280?1:-1];
typedef char check_ui_stashMenu[__builtin_offsetof(UIState,stashMenu)==1288?1:-1];
typedef char check_ui_mouseX[__builtin_offsetof(UIState,mouseX)==4816?1:-1];
typedef char check_ui_mouseY[__builtin_offsetof(UIState,mouseY)==4824?1:-1];
typedef char check_ui_resourceManager[__builtin_offsetof(UIState,resourceManager)==4872?1:-1];
typedef char check_ui_soundBank[__builtin_offsetof(UIState,soundBank)==5800?1:-1];
typedef char check_actor_soundBank[__builtin_offsetof(ActorState,soundBank)==664?1:-1];
typedef char check_actor_aiState[__builtin_offsetof(ActorState,aiState)==816?1:-1];
typedef char check_actor_inventory[__builtin_offsetof(ActorState,inventory)==1168?1:-1];
typedef char check_safe_pointer_size[sizeof(TSafePointer<CEquipment>)==16?1:-1];
typedef char check_guid[__builtin_offsetof(UnitIdentity,guid)==0x1a0?1:-1];
}
#endif
