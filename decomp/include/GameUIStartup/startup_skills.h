// CGameUI::create phase, aa15a9..aa3116 plus aa40b4..aa433d.
// Source of branches/constants: original ASM.
#ifndef OTL_GAMEUI_STARTUP_SKILLS_H
#define OTL_GAMEUI_STARTUP_SKILLS_H
#include "startup_hud.h"
#include "Constants.h"
#include "Settings.h"
#include "GameUIStartupData.h"
#include <CEGUIPropertyHelper.h>
namespace gameui_create_detail {
struct SkillStartupState {
    char prefix[0xe0];
    CEGUI::Window* information;
    char gape8[0x200-0xe8];
    CEGUI::Window* magnify;
    CEGUI::Window* attack;
    CEGUI::Window* right;
    CEGUI::Window* rightText;
    CEGUI::Window* attackText;
    char gap228[0x238-0x228];
    CEGUI::Window* alternate;
    CEGUI::Window* alternateText;
    char gap248[0x260-0x248];
    CEGUI::Window* buttons[10];
    CEGUI::Window* icons[10];
    CEGUI::Window* labels[10];
    CEGUI::Window* hotkeys[10];
    CEGUI::Window* swapHotkey;
    CEGUI::Window* itemHotkey;
    char gap3B0[0x4c8-0x3b0];
    float slotWidth,slotHeight;
    char gap4D0[0x1318-0x4d0];
    CEGUI::Window* glow;
    long long slotIndices[100];
};
#define STARTUP_SKILL_OFFSET(NAME,OFFSET) typedef char startup_skill_##NAME[__builtin_offsetof(SkillStartupState,NAME)==OFFSET?1:-1]
STARTUP_SKILL_OFFSET(information,0xe0);STARTUP_SKILL_OFFSET(magnify,0x200);
STARTUP_SKILL_OFFSET(attack,0x208);STARTUP_SKILL_OFFSET(right,0x210);
STARTUP_SKILL_OFFSET(rightText,0x218);STARTUP_SKILL_OFFSET(attackText,0x220);
STARTUP_SKILL_OFFSET(alternate,0x238);STARTUP_SKILL_OFFSET(alternateText,0x240);
STARTUP_SKILL_OFFSET(buttons,0x260);STARTUP_SKILL_OFFSET(icons,0x2b0);
STARTUP_SKILL_OFFSET(labels,0x300);STARTUP_SKILL_OFFSET(hotkeys,0x350);
STARTUP_SKILL_OFFSET(swapHotkey,0x3a0);STARTUP_SKILL_OFFSET(itemHotkey,0x3a8);
STARTUP_SKILL_OFFSET(slotWidth,0x4c8);STARTUP_SKILL_OFFSET(slotHeight,0x4cc);
STARTUP_SKILL_OFFSET(glow,0x1318);STARTUP_SKILL_OFFSET(slotIndices,0x1320);
#undef STARTUP_SKILL_OFFSET
inline __attribute__((always_inline)) void createUnique(CEGUI::Window*& destination,const char* typeName) {
    CEGUI::String prefix("");
    std::string seed("gui_");
    std::string generated=STRINGS::uniqueName(seed);
    CEGUI::String name(generated);
    CEGUI::String type(reinterpret_cast<const CEGUI::utf8*>(typeName));
    destination=CEGUI::WindowManager::getSingleton().createWindow(type,name,prefix);
}
inline __attribute__((always_inline)) void subscribeSkill(CGameUI* self,CEGUI::Window*& window) {
    window->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::Event::Subscriber(&CGameUI::handle_SkillMouseOver,self));
    window->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::Event::Subscriber(&CGameUI::handle_SkillMouseOver,self));
    window->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::Event::Subscriber(&CGameUI::handle_SkillMouseOut,self));
    window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::Event::Subscriber(&CGameUI::handle_SkillClick,self));
}
inline __attribute__((always_inline)) void noRiseOrMulti(CEGUI::Window*& window) {
    window->setRiseOnClickEnabled(false);
    window->setWantsMultiClickEvents(false);
}
inline __attribute__((always_inline)) void keyText(CEGUI::Window*& window,PrefixState& ui,unsigned setting) {
    int key=ui.settings->GetInt(setting);
    std::string bytes=STRINGS::StringConvertToUTF8(KCharacterNames[key]);
    CEGUI::String text(reinterpret_cast<const CEGUI::utf8*>(bytes.c_str()));
    window->setText(text);
}
inline __attribute__((always_inline)) CEGUI::Window* numberedChild(CEGUI::Window*& root,const char* prefix,unsigned number) {
    std::string digits=STRINGS::GetValueAsString(number);
    std::string bytes=prefix+digits;
    CEGUI::String name(bytes);
    return root->recursiveChildSearch(name);
}
inline __attribute__((always_inline)) void createSkillWidgets(CGameUI* self,PrefixState& ui,HUDState& hud,ImagesetState& images,SkillStartupState& slots) {
    if(!slots.information) {
        createUnique(slots.information,"GuiLook/StaticText");
        slots.information->setSize(CEGUI::UVector2(CEGUI::UDim(0.f,500.f),CEGUI::UDim(0.f,450.f)));
        {CEGUI::String text(reinterpret_cast<const CEGUI::utf8*>(""));slots.information->setText(text);}
        {CEGUI::String value("TopAligned");CEGUI::String key("VertFormatting");slots.information->setProperty(key,value);}
        slots.information->setMutedState(true);
        slots.information->setRiseOnClickEnabled(false);
        slots.information->setMousePassThroughEnabled(true);
    }
    createUnique(slots.glow,"GuiLook/StaticImage");
    slots.glow->setMutedState(true);
    slots.glow->setMousePassThroughEnabled(true);
    slots.glow->setRiseOnClickEnabled(false);
    {
        CEGUI::String name("slotglow");
        CEGUI::String value=CEGUI::PropertyHelper::imageToString(&images.uiIcons->getImage(name));
        CEGUI::String key("Image");slots.glow->setProperty(key,value);
    }
    for(int i=0;i<100;++i)slots.slotIndices[i]=i;
    bindChild(slots.magnify,hud.bottom,"MagnifyButton");
    int showNames=ui.settings->GetInt(KSETTINGS_TOGGLE_ITEM_NAME);
    static_cast<CEGUI::RadioButton*>(slots.magnify)->setSelected(showNames==1);
    bindChild(slots.attack,hud.bottom,"PlayerSkillLeft");
    {
        CEGUI::String value=CEGUI::PropertyHelper::imageToString(self->getImageFromImageSet(reinterpret_cast<const unsigned char*>("skill_attack")));
        CEGUI::String key("Image");slots.attack->setProperty(key,value);
    }
    slots.attack->setID(100);
    noRiseOrMulti(slots.attack);
    slots.attack->setTooltip(ui.system->getDefaultTooltip());
    subscribeSkill(self,slots.attack);
    bindChild(slots.attackText,hud.bottom,"SkillLeftText");noRiseOrMulti(slots.attackText);
    bindChild(slots.right,hud.bottom,"PlayerSkillRight");noRiseOrMulti(slots.right);
    slots.right->setTooltip(ui.system->getDefaultTooltip());subscribeSkill(self,slots.right);
    slots.right->setID(101);
    bindChild(slots.rightText,hud.bottom,"SkillRightText");noRiseOrMulti(slots.rightText);
    bindChild(slots.alternate,hud.bottom,"PlayerSkillAlternate");noRiseOrMulti(slots.alternate);
    slots.alternate->setTooltip(ui.system->getDefaultTooltip());subscribeSkill(self,slots.alternate);
    slots.alternate->setID(102);
    bindChild(slots.alternateText,hud.bottom,"SkillRightAlternateText");noRiseOrMulti(slots.alternateText);
    bindChild(slots.swapHotkey,hud.bottom,"TabHotkey");keyText(slots.swapHotkey,ui,KSETTINGS_KEYMAP_SWAPSKILLS);
    bindChild(slots.itemHotkey,hud.bottom,"AltHotkey");keyText(slots.itemHotkey,ui,KSETTINGS_KEYMAP_SHOWITEMS);
    for(unsigned i=0;i<10;++i) {
        slots.hotkeys[i]=numberedChild(hud.bottom,"SkillHotkey",i+1);
        keyText(slots.hotkeys[i],ui,KSkillSlotsKeys[i]);
        slots.labels[i]=numberedChild(hud.bottom,"SkillText",i+1);
        noRiseOrMulti(slots.labels[i]);
        CEGUI::Window* button=numberedChild(hud.bottom,"SkillSlot",i+1);
        noRiseOrMulti(button);
        button->setTooltip(ui.system->getDefaultTooltip());
        button->setID(0);
        subscribeSkill(self,button);
        button->setID(i);
        slots.buttons[i]=button;
        CEGUI::Window* icon;
        createUnique(icon,"GuiLook/StaticImage");
        noRiseOrMulti(icon);
        icon->setMousePassThroughEnabled(true);
        icon->setSize(slots.buttons[i]->getSize());
        slots.buttons[i]->addChildWindow(icon);
        slots.icons[i]=icon;
        if(i==0) {
            slots.slotWidth=icon->getWidth().asAbsolute(1.f);
            slots.slotHeight=icon->getHeight().asAbsolute(1.f);
        }
    }
}
}
#endif
