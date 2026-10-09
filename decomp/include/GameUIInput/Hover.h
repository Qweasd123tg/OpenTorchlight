#ifndef OTL_GAMEUI_INPUT_HOVER_H
#define OTL_GAMEUI_INPUT_HOVER_H
#include "State.h"
namespace gameui_input_detail {
template<unsigned Offset> struct HoverOwner { char prefix[Offset]; CCharacter* owner; };
struct PetListState { char prefix[0x648]; std::vector<CCharacter*> pets; };
typedef char check_PetListState_pets[__builtin_offsetof(PetListState,pets)==0x648?1:-1];
template<unsigned Offset,class Menu>
inline __attribute__((always_inline)) CEquipment* hover(Menu* menu) {
    return reinterpret_cast<menu_item_click_detail::HoverState<Offset>*>(menu)->equipment;
}
inline __attribute__((always_inline)) void removeEquipmentTooltip(CEquipmentTooltip* tooltip) {
    if(tooltip->m_pRoot->getParent())tooltip->m_pParent->removeChildWindow(tooltip->m_pRoot);
}
inline __attribute__((always_inline)) CEquipment* hoveredEquipment(CGameUI* self,const Selection& selected,CCharacter*& owner) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    gameui_create_detail::MenuState& menus=*reinterpret_cast<gameui_create_detail::MenuState*>(self);
    CEquipment* item=hover<0x1020>(ui.inventoryMenu);
    if(item){owner=ui.player;return item;}
    item=selected.serviceMenu==ui.merchantMenu?hover<0x3438>(selected.serviceMenu):hover<0x3408>(ui.stashMenu);
    if(item) {
        owner=static_cast<CCharacter*>(selected.serviceMenu->getOwner());
        if(item->getParentGuid()!=owner->getGuid()) {
            std::vector<CCharacter*>& pets=reinterpret_cast<PetListState*>(ui.player)->pets;
            std::size_t count=pets.size();
            // Original tests the low32 count before selecting the first pet.
            if(static_cast<unsigned>(count)) {
                owner=NULL;
                if(count)owner=pets[0];
            }
        }
        return item;
    }
    item=hover<0x1370>(ui.petMenu);
    if(item){owner=static_cast<CCharacter*>(ui.petMenu->getOwner());return item;}
    item=hover<0xf0>(ui.enchantMenu);
    if(item){owner=reinterpret_cast<HoverOwner<0x60>*>(ui.enchantMenu)->owner;return item;}
    item=hover<0x190>(ui.combineMenu);
    if(item){owner=reinterpret_cast<HoverOwner<0x90>*>(ui.combineMenu)->owner;return item;}
    item=hover<0x170>(menus.quest);
    if(item){owner=ui.player;return item;}
    item=hover<0x1e0>(menus.questDialog);
    if(item){owner=ui.player;return item;}
    InputState& state=input(self);
    CEquipmentRef* reference=NULL;
    if(state.itemHovered && ui.player && !foldout(skillWindows(self).foldout).root->getParent())
        reference=inventory(ui.player)->getEquipmentOfGuid(state.hoveredItemGuid);
    else if(state.foldoutItemHovered && ui.player && foldout(skillWindows(self).foldout).root->getParent())
        reference=inventory(ui.player)->getEquipmentOfGuid(state.foldoutItemGuid);
    if(reference) {
        item=static_cast<CEquipment*>(reference->m_pUnknown10);
        owner=ui.player;
    }
    return item;
}
inline __attribute__((always_inline)) void updateEquipmentTooltips(CGameUI* self,const Selection& selected) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    CCharacter* owner=NULL;
    CEquipment* item=hoveredEquipment(self,selected,owner);
    if(!item || ui.draggedItem.getObject()) {
        removeEquipmentTooltip(ui.tooltip);
        removeEquipmentTooltip(ui.comparisonTooltip1);
        removeEquipmentTooltip(ui.comparisonTooltip2);
        return;
    }
    self->showEquipmentTooltip(owner,item,ui.tooltip,NULL,NULL);
    if(ui.player && (item->ISA(UNITTYPES::WEAPON) || item->ISA(UNITTYPES::ARMOR) || item->ISA(UNITTYPES::TRINKET))) {
        CEquipment* first=NULL;
        CEquipment* second=NULL;
        inventory(ui.player)->getComparisonItems(item,&first,&second);
        if(first)self->showEquipmentTooltip(ui.player,first,ui.comparisonTooltip1,ui.tooltip,NULL);
        // Original does not refresh third tooltip when only second exists.
        if(second && first)self->showEquipmentTooltip(ui.player,second,ui.comparisonTooltip2,ui.tooltip,ui.comparisonTooltip1);
        if(!first)removeEquipmentTooltip(ui.comparisonTooltip1);
        if(!second)removeEquipmentTooltip(ui.comparisonTooltip2);
    } else {
        removeEquipmentTooltip(ui.comparisonTooltip1);
        removeEquipmentTooltip(ui.comparisonTooltip2);
    }
}
}
#endif
