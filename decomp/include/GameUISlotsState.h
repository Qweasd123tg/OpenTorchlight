#ifndef OTL_GAMEUI_SLOTS_STATE_H
#define OTL_GAMEUI_SLOTS_STATE_H
#include "GameUI.h"
#include "Character.h"
#include "Inventory.h"
#include "Skill.h"
#include "SkillManager.h"
#include "ResourceManager.h"
#include "DataGroup.h"
#include "StringUtilities.h"
#include "StringTranslate.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "EmptyStrings.h"
#include <CEGUI.h>
#include <cmath>
namespace gameui_slots_detail {
struct UIState {
    char gap0[56];
    CCharacter* player;
    char gap40[456];
    CEGUI::Window* attackIcon;
    CEGUI::Window* leftIcon;
    CEGUI::Window* leftCooldown;
    CEGUI::Window* attackCooldown;
    long long leftGuid;
    char gap230[8];
    CEGUI::Window* rightIcon;
    CEGUI::Window* rightCooldown;
    long long rightGuid;
    long long attackGuid;
    char gap258[8];
    CEGUI::Window* buttons[10];
    CEGUI::Window* icons[10];
    CEGUI::Window* labels[10];
    char gap350[96];
    long long itemGuids[10];
    int counts[10];
    char gap428[160];
    float slotWidth;
    float slotHeight;
    char gap4d0[3640];
    CResourceManager* resources;
    char gap1310[16];
    long long skillGuids[10];
    char gap1370[688];
    long long emptyGuid;
    long long primaryUserGuids[3];
};
typedef char check_UIState_player[__builtin_offsetof(UIState,player)==0x38?1:-1];
typedef char check_UIState_attackIcon[__builtin_offsetof(UIState,attackIcon)==0x208?1:-1];
typedef char check_UIState_leftIcon[__builtin_offsetof(UIState,leftIcon)==0x210?1:-1];
typedef char check_UIState_leftCooldown[__builtin_offsetof(UIState,leftCooldown)==0x218?1:-1];
typedef char check_UIState_attackCooldown[__builtin_offsetof(UIState,attackCooldown)==0x220?1:-1];
typedef char check_UIState_leftGuid[__builtin_offsetof(UIState,leftGuid)==0x228?1:-1];
typedef char check_UIState_rightIcon[__builtin_offsetof(UIState,rightIcon)==0x238?1:-1];
typedef char check_UIState_rightCooldown[__builtin_offsetof(UIState,rightCooldown)==0x240?1:-1];
typedef char check_UIState_rightGuid[__builtin_offsetof(UIState,rightGuid)==0x248?1:-1];
typedef char check_UIState_attackGuid[__builtin_offsetof(UIState,attackGuid)==0x250?1:-1];
typedef char check_UIState_buttons[__builtin_offsetof(UIState,buttons)==0x260?1:-1];
typedef char check_UIState_icons[__builtin_offsetof(UIState,icons)==0x2b0?1:-1];
typedef char check_UIState_labels[__builtin_offsetof(UIState,labels)==0x300?1:-1];
typedef char check_UIState_itemGuids[__builtin_offsetof(UIState,itemGuids)==0x3b0?1:-1];
typedef char check_UIState_counts[__builtin_offsetof(UIState,counts)==0x400?1:-1];
typedef char check_UIState_slotWidth[__builtin_offsetof(UIState,slotWidth)==0x4c8?1:-1];
typedef char check_UIState_slotHeight[__builtin_offsetof(UIState,slotHeight)==0x4cc?1:-1];
typedef char check_UIState_resources[__builtin_offsetof(UIState,resources)==0x1308?1:-1];
typedef char check_UIState_skillGuids[__builtin_offsetof(UIState,skillGuids)==0x1320?1:-1];
typedef char check_UIState_emptyGuid[__builtin_offsetof(UIState,emptyGuid)==0x1620?1:-1];
typedef char check_UIState_primaryUserGuids[__builtin_offsetof(UIState,primaryUserGuids)==0x1628?1:-1];
struct ActorState {
    char gap0[456];
    CSkillManager* skills;
    char gap1d0[480];
    long long primarySkills[3];
    char gap3c8[200];
    CInventory* inventory;
    char gap498[1048];
    long long hotkeySkills[10];
    long long hotkeyItems[10];
};
typedef char check_ActorState_skills[__builtin_offsetof(ActorState,skills)==0x1c8?1:-1];
typedef char check_ActorState_primarySkills[__builtin_offsetof(ActorState,primarySkills)==0x3b0?1:-1];
typedef char check_ActorState_inventory[__builtin_offsetof(ActorState,inventory)==0x490?1:-1];
typedef char check_ActorState_hotkeySkills[__builtin_offsetof(ActorState,hotkeySkills)==0x8b0?1:-1];
typedef char check_ActorState_hotkeyItems[__builtin_offsetof(ActorState,hotkeyItems)==0x900?1:-1];
inline __attribute__((always_inline)) UIState& state(CGameUI* ui) { return *reinterpret_cast<UIState*>(ui); }
inline __attribute__((always_inline)) ActorState& actor(CCharacter* player) { return *reinterpret_cast<ActorState*>(player); }
inline __attribute__((always_inline)) CEGUI::String utf8(const std::string& bytes) {
    return CEGUI::String(reinterpret_cast<const unsigned char*>(bytes.c_str()));
}
inline __attribute__((always_inline)) void clearText(CEGUI::Window*& window) { window->setText(utf8("")); }
inline __attribute__((always_inline)) void image(CEGUI::Window*& window,const CEGUI::Image* value) {
    window->setProperty("Image",CEGUI::PropertyHelper::imageToString(value));
}
inline __attribute__((always_inline)) void tint(CEGUI::Window*& window,float value) {
    // Four independent conversions preserve the original evaluation count.
    window->setProperty("ImageColours",
        "tl:" + CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1.0f)) +
        "tr:" + CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1.0f)) +
        "bl:" + CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1.0f)) +
        "br:" + CEGUI::PropertyHelper::colourToString(CEGUI::colour(value,value,value,1.0f)));
}
inline __attribute__((always_inline)) void primary(CGameUI* self,UIState& ui,int index,CEGUI::Window*& icon,
                    CEGUI::Window*& cooldown,long long& cachedGuid) {
    if(cachedGuid!=actor(ui.player).primarySkills[index]) {
        cachedGuid=actor(ui.player).primarySkills[index];
        CSkill* skill=actor(ui.player).skills ?
            actor(ui.player).skills->getSkillByGuid(actor(ui.player).primarySkills[index]) : NULL;
        if(skill && !skill->getSkillIcon().empty()) {
            image(icon,self->getImageFromImageSet(reinterpret_cast<const unsigned char*>(
                STRINGS::StringConvertToNarrow(skill->getSkillIcon().c_str()).c_str())));
            ui.primaryUserGuids[index]=cachedGuid;
            icon->setUserData(&ui.primaryUserGuids[index]);
        } else {
            if(index==2) image(icon,self->getImageFromImageSet(reinterpret_cast<const unsigned char*>("skill_attack")));
            else icon->setProperty("Image","");
            icon->setUserData(&ui.emptyGuid);
        }
        // The first icon refresh clears the second button's cooldown label.
        if(index==0)clearText(ui.rightCooldown);
    }
    if(actor(ui.player).primarySkills[index]!=-1) {
        std::string value="";
        CSkill* skill=actor(ui.player).skills ?
            actor(ui.player).skills->getSkillByGuid(actor(ui.player).primarySkills[index]) : NULL;
        if(skill) {
            int seconds=static_cast<int>(ceilf(actor(ui.player).skills->getSkillCoolingTime(skill)));
            if(seconds>0)value=STRINGS::StringConvertToUTF8(STRINGS::GetValueAsWString(seconds));
        }
        if(cooldown->getText()!=value)cooldown->setText(utf8(value));
    } else if(cooldown->getText()!="")clearText(cooldown);
}
}
#endif
