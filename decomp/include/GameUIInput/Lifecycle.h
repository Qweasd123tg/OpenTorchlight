#ifndef OTL_GAMEUI_INPUT_LIFECYCLE_H
#define OTL_GAMEUI_INPUT_LIFECYCLE_H
#include "State.h"
namespace gameui_input_detail {
struct CloseAllFrontWindow { char prefix[0x138]; CEGUI::Window* window; };
inline __attribute__((always_inline)) void clearDrag(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    ui.draggedItem.setObject(NULL);
    ui.dragOwner.setObject(NULL);
    ui.dragSlot=-1;
    self->updateHardwareCursor();
}
inline __attribute__((always_inline)) void detachDragIcon(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    CEGUI::Window* icon=ui.draggedItem.getObject()->m_pIconWindow;
    if(ui.dragWindow==icon->getParent())ui.dragWindow->removeChildWindow(icon);
}
inline __attribute__((always_inline)) void processPlayerState(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    gameui_create_detail::MenuState& menus=*reinterpret_cast<gameui_create_detail::MenuState*>(self);
    if(!ui.player || ui.player->getEnabled())self->handleKeyPresses();
    if(ui.player) {
        if(!ui.player->alive()) {
            self->closeAll();
            if(ui.draggedItem.getObject()) {
                self->returnDraggedItem();
                detachDragIcon(self);
                clearDrag(self);
            }
            return;
        }
        if(ui.player && !ui.player->getEnabled())return;
    }
    // ab68f7 loads +0x540: the cinematic dropdown, not modal at +0x548.
    CCinematicMenu* cinematic=menus.cinematic;
    if(cinematic && (cinematic->m_bUnknown30 || !cinematic->m_bUnknown31))return;
    if(ui.player && !ui.player->getEnabled())return;
    if(static_cast<unsigned char>(self->getUIIsInCinematic()))return;
    unsigned closeKey=settings(self)->GetInt(KSETTINGS_KEYMAP_CLOSEALL);
    if(keys(self).keyPressed(closeKey)) {
        self->unPause();
        if(self->eitherCoveredPartial())self->closeAll();
        else if(!self->modalDialogOpenPartial()) {
            self->closeAll();
            ui.inventoryMenu->setOpen(true);
            menus.stats->setOpen(true);
            reinterpret_cast<CloseAllFrontWindow*>(self)->window->moveToFront();
        }
    }
    unsigned pauseKey=settings(self)->GetInt(KSETTINGS_KEYMAP_PAUSE);
    if(keys(self).keyPressed(pauseKey))self->togglePause();
}
inline __attribute__((always_inline)) void processWorldClick(CGameUI* self,bool& result) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    if(!input(self).mouseThrough || !mouse(self).buttonPressed(MOUSE_LEFT))return;
    bool acted=false;
    if(ui.targetedItem.getObject()) {
        self->setCursorState(static_cast<ECursorState>(0));
        clearTargetPointers(self);
        acted=true;
    }
    if(ui.selectedSkill!=-1) {
        self->setCursorState(static_cast<ECursorState>(0));
        ui.selectedSkill=-1;
        acted=true;
    }
    if(ui.draggedItem.getObject()) {
        CCharacter* owner=ui.dragOwner.getObject();
        bool owned=ui.player==owner;
        if(!owned)owned=ui.petMenu->getOwner()==owner;
        if(owned) {
            if(ui.draggedItem.getObject()->ISA(UNITTYPES::QUESTITEM))self->returnDraggedItem();
            else {
                Ogre::Vector3 position;
                if(ui.petMenu->getOwner()==ui.dragOwner.getObject())
                    position=ui.petMenu->getOwner()->getPosition(true);
                else position=ui.player->getPosition(true);
                ui.level->addItem(ui.draggedItem.getObject(),position,true);
                detachDragIcon(self);
            }
            clearDrag(self);
            result=false;
            return;
        }
    }
    if(!acted && self->bothCoveredPartial())self->closeAll();
}
}
#endif
