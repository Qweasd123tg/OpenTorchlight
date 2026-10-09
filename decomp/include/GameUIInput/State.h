#ifndef OTL_GAMEUI_INPUT_STATE_H
#define OTL_GAMEUI_INPUT_STATE_H
#include "MenuItemClickState.h"
#include "GameUIStartup/startup_menus.h"
#include "SkillMenu.h"
#include "SkillFoldout.h"
#include "SkillTooltip.h"
#include "MouseManager.h"
#include "KeyManager.h"
#include "GameVariables.h"
#include "Skill.h"
#include "SkillManager.h"
#include "EmptyStrings.h"
#include <CEGUI.h>
namespace gameui_input_detail {
// Non-owning layout views. Never construct these over original objects.
struct SettingsState { char prefix[0x78]; CDynamicPropertyFile* settings; };
struct InputState {
    char prefix[0x12fb];
    bool mouseThrough;
    char gap12fc[0x1318-0x12fc];
    CEGUI::Window* hoveredLabel;
    char gap1320[0x1640-0x1320];
    bool labelHovered;
    bool itemHovered;
    bool foldoutItemHovered;
    bool skillHovered;
    char gap1644[4];
    long long hoveredSkillGuid;
    long long hoveredItemGuid;
    long long foldoutItemGuid;
    bool foldoutSkillHovered;
    char gap1661[7];
    long long foldoutSkillGuid;
    bool inputCaptured;
    char gap1671[3];
    int leftSlot;
    int rightSlot;
    int pendingRightSlot;
    char gap1680[0x1930-0x1680];
    std::vector<CSubMenu*> submenus;
    std::vector<CDropdownMenu*> dropdowns;
    char gap1960[0x1998-0x1960];
    bool consumeNextInput;
    bool paused;
};
struct SkillWindows { char prefix[0x4b8]; CSkillTooltip* tooltip; CSkillFoldout* foldout; };
struct FoldoutState {
    char prefix[0x348]; CEGUI::Window* root;
    char gap350[0xcb0-0x350]; bool flagCB0; bool leftMapping;
};
struct TooltipState { char prefix[0x30]; CEGUI::Window* root; };
struct InventoryClicks { char prefix[0x78]; int left; int right; };
struct PetClicks { char prefix[0x98]; int left; int right; };
struct EnchantClicks { char prefix[0xe8]; int left; int right; };
struct CombineClicks { char prefix[0x188]; int left; int right; };
struct ServiceClicks { char prefix[0x3428]; int petLeft; int petRight; int item; };
struct StashClicks { char prefix[0x33f8]; int petLeft; int petRight; int item; };
struct ActorSkills { char prefix[0x1c8]; CSkillManager* skills; };
struct SkillMappings { char prefix[0x950]; long long right[12]; long long left[12]; };
struct SkillMenuHover { char prefix[0x40]; long long guid; };
struct SkillEligibility {
    char prefix[0x60]; int activation;
    char gap64[7]; bool executedByProperty; char gap6c; bool enabled;
    char gap6e[0xe0-0x6e]; unsigned effectiveLevel;
};
#define OTL_INPUT_OFFSET(T,F,O) typedef char check_##T##_##F[__builtin_offsetof(T,F)==O?1:-1]
OTL_INPUT_OFFSET(SettingsState,settings,0x78);
OTL_INPUT_OFFSET(InputState,mouseThrough,0x12fb);
OTL_INPUT_OFFSET(InputState,hoveredLabel,0x1318);
OTL_INPUT_OFFSET(InputState,labelHovered,0x1640);
OTL_INPUT_OFFSET(InputState,hoveredSkillGuid,0x1648);
OTL_INPUT_OFFSET(InputState,foldoutSkillHovered,0x1660);
OTL_INPUT_OFFSET(InputState,foldoutSkillGuid,0x1668);
OTL_INPUT_OFFSET(InputState,inputCaptured,0x1670);
OTL_INPUT_OFFSET(InputState,leftSlot,0x1674);
OTL_INPUT_OFFSET(InputState,pendingRightSlot,0x167c);
OTL_INPUT_OFFSET(InputState,submenus,0x1930);
OTL_INPUT_OFFSET(InputState,dropdowns,0x1948);
OTL_INPUT_OFFSET(InputState,consumeNextInput,0x1998);
OTL_INPUT_OFFSET(SkillWindows,foldout,0x4c0);
OTL_INPUT_OFFSET(FoldoutState,root,0x348);
OTL_INPUT_OFFSET(FoldoutState,leftMapping,0xcb1);
OTL_INPUT_OFFSET(SkillMappings,left,0x9b0);
OTL_INPUT_OFFSET(SkillEligibility,executedByProperty,0x6b);
OTL_INPUT_OFFSET(SkillEligibility,enabled,0x6d);
OTL_INPUT_OFFSET(SkillEligibility,effectiveLevel,0xe0);
#undef OTL_INPUT_OFFSET
inline __attribute__((always_inline)) InputState& input(CGameUI* ui) { return *reinterpret_cast<InputState*>(ui); }
inline __attribute__((always_inline)) FoldoutState& foldout(CSkillFoldout* menu) { return *reinterpret_cast<FoldoutState*>(menu); }
inline __attribute__((always_inline)) CMouseManager& mouse(CGameUI* ui) { return *reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(ui)+0x12a8); }
inline __attribute__((always_inline)) CKeyManager& keys(CGameUI* ui) { return *reinterpret_cast<CKeyManager*>(reinterpret_cast<char*>(ui)+0x590); }
inline __attribute__((always_inline)) CDynamicPropertyFile* settings(CGameUI* ui) { return reinterpret_cast<SettingsState*>(ui)->settings; }
inline __attribute__((always_inline)) CSkillManager* skills(CCharacter* actor) { return reinterpret_cast<ActorSkills*>(actor)->skills; }
inline __attribute__((always_inline)) SkillWindows& skillWindows(CGameUI* ui) { return *reinterpret_cast<SkillWindows*>(ui); }
inline __attribute__((always_inline)) void detachFromActualParent(CEGUI::Window* window) {
    if (window->getParent()) window->getParent()->removeChildWindow(window);
}
inline __attribute__((always_inline)) bool finish(CGameUI* self,bool result) {
    InputState& state=input(self);
    state.mouseThrough=false;
    state.leftSlot=-1;state.rightSlot=-1;state.pendingRightSlot=-1;
    return result;
}
inline __attribute__((always_inline)) void clearTargetPointers(CGameUI* self) {
    // Original order is item, user, target. Preserve the safe-pointer indices.
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    ui.targetedItem.setObject(NULL);
    ui.itemUser.setObject(NULL);
    ui.targetCharacter.setObject(NULL);
}
inline __attribute__((always_inline)) void captureAndPosition(CGameUI* self,void* window,float elapsed,bool& result) {
    self->captureProcessInput();
    InputState& state=input(self);
    if(state.inputCaptured)result=false;
    state.inputCaptured=false;
    if(foldout(skillWindows(self).foldout).root->getParent() && state.foldoutSkillHovered)result=false;
    mouse(self).update(window);
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    float mouseY=float(ui.mouseY);
    float mouseX=float(ui.mouseX);
    CEGUI::System::getSingleton().injectMousePosition(mouseX,mouseY);
    CEGUI::System::getSingleton().injectTimePulse(elapsed);
    if(mouse(self).buttonPressed(MOUSE_RIGHT)||mouse(self).buttonPressed(MOUSE_LEFT)){
        if(!state.foldoutSkillHovered&&!state.skillHovered&&!state.itemHovered)
            detachFromActualParent(foldout(skillWindows(self).foldout).root);
    }
    if(mouse(self).buttonPressed(MOUSE_RIGHT) && (ui.targetedItem.getObject() || ui.selectedSkill!=-1)){
        self->setCursorState(static_cast<ECursorState>(0));
        clearTargetPointers(self);
    }
    if(ui.draggedItem.getObject()){
        float y=float(ui.mouseY);
        y-=self->scaledY(48.0f);
        float x=float(ui.mouseX);
        x-=self->scaledY(32.0f);
        ui.draggedItem.getObject()->m_pIconWindow->setPosition(
            CEGUI::UVector2(CEGUI::UDim(0.0f,x),CEGUI::UDim(0.0f,y)));
    }
}
inline __attribute__((always_inline)) CCharacter* equipOwner(CGameUI* self,CCharacter* captured,bool playerPath) {
    return playerPath?menu_item_click_detail::state(self).player:captured;
}
inline __attribute__((always_inline)) CInventory* inventory(CCharacter* actor) {
    return menu_item_click_detail::actor(actor).inventory;
}
inline __attribute__((always_inline)) void equipRejected(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    ui.soundBank->playSample(24,ui.player->getSceneNode(),0.0f,0.0f,false);
    CSoundBank* actorSounds=menu_item_click_detail::actor(ui.player).soundBank;
    if(actorSounds)actorSounds->queueGlobalSample(49,0.0f,0.1f);
}
inline __attribute__((always_inline)) void recoverReplacedItem(CGameUI* self,CCharacter* captured,bool playerPath,
                                CEquipment*& item,bool second) {
    // Keep the pointer by reference: the original reloads the out-parameter
    // after collaborators that may retain its address.
    CCharacter* owner=equipOwner(self,captured,playerPath);
    if(inventory(owner)->pickupEquipment(item,true)) {
        CCharacter* soundOwner=second?equipOwner(self,captured,playerPath):
            menu_item_click_detail::state(self).player;
        item->playDropSound(soundOwner->getSceneNode());
    } else {
        Ogre::Vector3 position=equipOwner(self,captured,playerPath)->getPosition(true);
        menu_item_click_detail::state(self).level->addItem(item,position,true);
        item->drop();
    }
}
inline __attribute__((always_inline)) void quickUseOrEquip(CGameUI* self,CCharacter* captured,int slot,
                            bool playerPath,bool& result) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    CEquipment* item=inventory(equipOwner(self,captured,playerPath))->getEquipmentInSlot(slot);
    if(!item)return;
    if(ui.draggedItem.getObject()) {
        if(playerPath)result=false;
        return;
    }
    bool use=false;
    if(playerPath || menu_item_click_detail::actor(captured).aiState!=42)
        use=item->isUseable();
    if(use) {
        self->useItem(*ui.level,item);
        if(playerPath)result=false;
        menu_item_click_detail::clearHoverAndTooltips(ui);
        return;
    }
    if(inventory(equipOwner(self,captured,playerPath))->equipEquipmentIntoFirstFreeLocation(item)) {
        equipOwner(self,captured,playerPath)->setRenderBehind(true);
        item->playDropSound(ui.player->getSceneNode());
        if(playerPath)result=false;
        menu_item_click_detail::clearHoverAndTooltips(ui);
        return;
    }
    if(!item->canEquip(equipOwner(self,captured,playerPath),true)) {
        if(playerPath){equipRejected(self);result=false;}
        return;
    }
    CEquipment* first=NULL;
    CEquipment* second=NULL;
    inventory(equipOwner(self,captured,playerPath))->getComparisonItems(item,&first,&second);
    if(item->ISA(static_cast<UNITTYPES::EUNITTYPES>(10)) && second)
        inventory(equipOwner(self,captured,playerPath))->removeEquipment(second);
    bool equipped=false;
    if(first) {
        inventory(equipOwner(self,captured,playerPath))->removeEquipment(first);
        if(inventory(equipOwner(self,captured,playerPath))->equipEquipmentIntoFirstFreeLocation(item)) {
            equipped=true;
            equipOwner(self,captured,playerPath)->setRenderBehind(true);
            item->playDropSound(ui.player->getSceneNode());
        }
        recoverReplacedItem(self,captured,playerPath,first,false);
    }
    if(item->ISA(static_cast<UNITTYPES::EUNITTYPES>(10)) && second)
        recoverReplacedItem(self,captured,playerPath,second,true);
    if(playerPath) {
        if(!equipped)equipRejected(self);
        result=false;
    }
    menu_item_click_detail::clearHoverAndTooltips(ui);
    CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);
}
struct Selection {
    CSubMenu* serviceMenu;
    CCharacter* serviceOwner;
    CCharacter* petOwner;
    int serviceSlot;
    int petLeft;
    int petRight;
};
template<class Menu,class Clicks>
inline __attribute__((always_inline)) void mergePlayerClicks(Menu*& menu,InputState& state) {
    if(menu->open()) {
        if(state.leftSlot==-1)state.leftSlot=reinterpret_cast<Clicks*>(menu)->left;
        if(state.rightSlot==-1)state.rightSlot=reinterpret_cast<Clicks*>(menu)->right;
    }
}
inline __attribute__((always_inline)) Selection collectClicks(CGameUI* self,bool& result) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    InputState& state=input(self);
    if(state.rightSlot!=-1)result=false;
    if(state.pendingRightSlot!=-1 && state.rightSlot==-1) {
        state.rightSlot=state.pendingRightSlot;
        state.pendingRightSlot=-1;
    }
    mergePlayerClicks<CInventoryMenu,InventoryClicks>(ui.inventoryMenu,state);
    mergePlayerClicks<CEnchantMenu,EnchantClicks>(ui.enchantMenu,state);
    mergePlayerClicks<CCombineMenu,CombineClicks>(ui.combineMenu,state);
    Selection selected={ui.merchantMenu,NULL,NULL,-1,-1,-1};
    if(selected.serviceMenu->open()) {
        selected.serviceSlot=reinterpret_cast<ServiceClicks*>(ui.merchantMenu)->item;
        selected.serviceOwner=static_cast<CCharacter*>(ui.merchantMenu->getOwner());
        selected.serviceMenu=ui.merchantMenu;
        selected.petRight=reinterpret_cast<ServiceClicks*>(selected.serviceMenu)->petRight;
        selected.petLeft=reinterpret_cast<ServiceClicks*>(selected.serviceMenu)->petLeft;
        selected.petOwner=static_cast<CCharacter*>(ui.petMenu->getOwner());
    }
    if(ui.stashMenu->open()) {
        if(selected.serviceSlot==-1)selected.serviceSlot=reinterpret_cast<StashClicks*>(ui.stashMenu)->item;
        selected.serviceOwner=static_cast<CCharacter*>(ui.stashMenu->getOwner());
        selected.serviceMenu=ui.stashMenu;
        if(selected.petLeft==-1)selected.petLeft=reinterpret_cast<StashClicks*>(selected.serviceMenu)->petLeft;
        if(selected.petRight==-1)selected.petRight=reinterpret_cast<StashClicks*>(selected.serviceMenu)->petRight;
        selected.petOwner=static_cast<CCharacter*>(ui.petMenu->getOwner());
    }
    if(ui.petMenu->open()) {
        if(selected.petLeft==-1)selected.petLeft=reinterpret_cast<PetClicks*>(ui.petMenu)->left;
        if(selected.petRight==-1)selected.petRight=reinterpret_cast<PetClicks*>(ui.petMenu)->right;
        selected.petOwner=static_cast<CCharacter*>(ui.petMenu->getOwner());
    }
    return selected;
}
inline __attribute__((always_inline)) void processClicks(CGameUI* self,Selection& selected,bool& result) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    InputState& state=input(self);
    bool sameClosedOwner=false;
    if(!selected.serviceMenu->open() && ui.draggedItem.getObject())
        sameClosedOwner=selected.serviceOwner==ui.dragOwner.getObject();
    if((mouse(self).buttonPressed(MOUSE_RIGHT) && ui.draggedItem.getObject()) || sameClosedOwner) {
        self->returnDraggedItem();result=false;selected.petRight=-1;
    }
    if(state.leftSlot!=-1) {
        if(!self->menuItemClick(ui.player,ui.inventoryMenu,state.leftSlot,result))result=false;
    } else if(selected.petLeft!=-1) {
        if(!self->menuItemClick(selected.petOwner,ui.petMenu,selected.petLeft,result))result=false;
        if(ui.merchantMenu->open())ui.merchantMenu->updateLayout();
        if(ui.stashMenu->open())ui.stashMenu->updateLayout();
    } else if(selected.petRight!=-1) {
        quickUseOrEquip(self,selected.petOwner,selected.petRight,false,result);
    } else if(state.rightSlot!=-1) {
        quickUseOrEquip(self,NULL,state.rightSlot,true,result);
    } else if(selected.serviceOwner && selected.serviceSlot!=-1) {
        if(!self->menuItemClick(selected.serviceOwner,selected.serviceMenu,selected.serviceSlot,result))result=false;
    }
}
inline __attribute__((always_inline)) void dispatchMenus(CGameUI* self,void* window,float elapsed,bool enabled,bool& result) {
    gameui_create_detail::MenuState& menus=*reinterpret_cast<gameui_create_detail::MenuState*>(self);
    InputState& state=input(self);
    if(!menus.fishing->processInput(window,elapsed,enabled))result=false;
    for(unsigned int i=0;i<state.dropdowns.size();++i) {
        // Caller uses AL, regardless of the current placeholder return type.
        unsigned char accepted=static_cast<unsigned char>(state.dropdowns[i]->processInput(window,elapsed,enabled));
        if(!accepted)result=false;
    }
    for(unsigned int i=0;i<state.submenus.size();++i)
        if(!state.submenus[i]->processInput(window,elapsed,enabled))result=false;
}
}
#endif
