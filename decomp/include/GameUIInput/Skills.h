#ifndef OTL_GAMEUI_INPUT_SKILLS_H
#define OTL_GAMEUI_INPUT_SKILLS_H
#include "State.h"
#include "GameUIInputData.h"
namespace gameui_input_detail {
inline __attribute__((always_inline)) CEGUI::Window* skillTooltipRoot(CGameUI* self) {
    return reinterpret_cast<TooltipState*>(skillWindows(self).tooltip)->root;
}
inline __attribute__((always_inline)) bool functionKeyPressed(CGameUI* self,unsigned index) {
    unsigned key=settings(self)->GetInt(KSkillSlotsFunctionKeys[index]);
    return keys(self).keyPressed(key);
}
inline __attribute__((always_inline)) void assignFunctionKey(CGameUI* self,unsigned index,long long guid) {
    CSkillFoldout* menu=skillWindows(self).foldout;
    bool left=foldout(menu).root->getParent() && foldout(menu).leftMapping;
    if(left)menu_item_click_detail::state(self).player->setLeftMappedFunctionSkill(index,guid);
    else menu_item_click_detail::state(self).player->setMappedFunctionSkill(index,guid);
}
inline __attribute__((always_inline)) void reopenFoldout(CGameUI* self) {
    CSkillFoldout* menu=skillWindows(self).foldout;
    bool flag=foldout(menu).flagCB0;
    bool left=foldout(menu).leftMapping;
    menu->showFoldout(menu_item_click_detail::state(self).player,-1.0f,-1.0f,flag,left);
}
inline __attribute__((always_inline)) bool mapSkillMenuHover(CGameUI* self) {
    gameui_create_detail::MenuState& menus=*reinterpret_cast<gameui_create_detail::MenuState*>(self);
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    long long guid=reinterpret_cast<SkillMenuHover*>(menus.skill)->guid;
    CSkillManager* manager=skills(ui.player);
    if(!guid || !manager)return false;
    CSkill* skill=manager->getSkillByGuid(guid);
    bool eligible=false;
    if(skill) {
        skill->calculateEffectiveSkillLevel();
        SkillEligibility& value=*reinterpret_cast<SkillEligibility*>(skill);
        eligible=value.effectiveLevel && !value.executedByProperty && value.enabled && value.activation!=4;
    }
    if(!eligible && guid!=-999)return false;
    bool mapped=false;
    for(unsigned i=0;i<12;++i) {
        if(!functionKeyPressed(self,i))continue;
        assignFunctionKey(self,i,guid);
        CEGUI::Window* root=foldout(skillWindows(self).foldout).root;
        if(root->getParent()) {
            root->getParent()->removeChildWindow(root);
            reopenFoldout(self);
            detachFromActualParent(skillTooltipRoot(self));
        }
        menus.skill->updateLayout();
        CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);
        mapped=true;
    }
    return mapped;
}
inline __attribute__((always_inline)) void mapFoldoutHover(CGameUI* self,long long guid) {
    gameui_create_detail::MenuState& menus=*reinterpret_cast<gameui_create_detail::MenuState*>(self);
    for(unsigned i=0;i<12;++i) {
        if(!functionKeyPressed(self,i))continue;
        assignFunctionKey(self,i,guid);
        detachFromActualParent(foldout(skillWindows(self).foldout).root);
        // Unlike the skill-menu branch, this reopens an unparented foldout too.
        reopenFoldout(self);
        detachFromActualParent(skillTooltipRoot(self));
        if(menus.skill->open())menus.skill->updateLayout();
        CEGUI::System::getSingleton().injectMouseMove(1.0f,0.0f);
    }
}
inline __attribute__((always_inline)) void activateFunctionKeys(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    CSkillManager* manager=skills(ui.player);
    if(!manager)return;
    for(unsigned i=0;i<12;++i) {
        if(!functionKeyPressed(self,i))continue;
        long long right=reinterpret_cast<SkillMappings*>(ui.player)->right[i];
        CSkill* skill=manager->getSkillByGuid(right);
        if(skill)ui.player->setActiveSkill(skill,true);
        else {
            long long left=reinterpret_cast<SkillMappings*>(ui.player)->left[i];
            if(left==-999)ui.player->setLeftSkillByName(EMPTY_WSTRING);
            else {
                skill=manager->getSkillByGuid(left);
                if(!skill)continue;
                const std::wstring& name=skill->getName();
                ui.player->setLeftSkillByName(name);
            }
        }
        ui.soundBank->playSample(30,ui.player->getSceneNode(),0.0f,0.0f,false);
    }
}
inline __attribute__((always_inline)) void updateSkillTooltip(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    InputState& state=input(self);
    long long guid;
    if(state.skillHovered && ui.player && !foldout(skillWindows(self).foldout).root->getParent())
        guid=state.hoveredSkillGuid;
    else if(state.foldoutSkillHovered && ui.player && foldout(skillWindows(self).foldout).root->getParent())
        guid=state.foldoutSkillGuid;
    else {detachFromActualParent(skillTooltipRoot(self));return;}
    CSkillManager* manager=skills(ui.player);
    if(!manager)return;
    CSkill* skill=manager->getSkillByGuid(guid);
    if(!skill)return;
    float x=float(ui.mouseX),y=float(ui.mouseY);
    skillWindows(self).tooltip->showTooltip(ui.player,skill,x,y);
}
inline __attribute__((always_inline)) void processSkillKeys(CGameUI* self) {
    menu_item_click_detail::UIState& ui=menu_item_click_detail::state(self);
    InputState& state=input(self);
    bool mapped=mapSkillMenuHover(self);
    if((state.skillHovered || state.foldoutSkillHovered) && ui.player) {
        long long guid=state.foldoutSkillHovered?state.foldoutSkillGuid:state.hoveredSkillGuid;
        CSkillManager* manager=skills(ui.player);
        if(manager) {
            CSkill* skill=manager->getSkillByGuid(guid);
            if((skill || guid==-999) && state.foldoutSkillHovered)mapFoldoutHover(self,guid);
        }
    } else if(!mapped)activateFunctionKeys(self);
    updateSkillTooltip(self);
}
}
#endif
