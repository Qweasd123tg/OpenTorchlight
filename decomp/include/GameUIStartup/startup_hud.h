// CGameUI::create phase, aa0677..aa15a8.
#ifndef OTL_GAMEUI_STARTUP_HUD_H
#define OTL_GAMEUI_STARTUP_HUD_H
#include "startup_imagesets.h"
#include <elements/CEGUIRadioButton.h>
namespace gameui_create_detail {
struct HUDState {
    char gap0[0xe8];
    CEGUI::Window* targetName;
    CEGUI::Window* targetDescription;
    CEGUI::Window* targetLevel;
    CEGUI::Window* levelName;
    CEGUI::Window* merchantTip;
    CEGUI::Window* largeMessage;
    CEGUI::Window* smallMessage;
    CEGUI::Window* targetHealth;
    CEGUI::Window* targetBar;
    CEGUI::Window* playButton;
    CEGUI::Window* bottom;
    CEGUI::Window* health;
    CEGUI::Window* healthOver;
    CEGUI::Window* healthSub;
    CEGUI::Window* mana;
    CEGUI::Window* manaOver;
    CEGUI::Window* manaSub;
    CEGUI::Window* pet;
    CEGUI::Window* petHealthOver;
    CEGUI::Window* petHealth;
    char gap188[0x8];
    CEGUI::Window* petMana;
    CEGUI::Window* petManaOver;
    char gap1a0[0x8];
    CEGUI::Window* fleeing;
    CEGUI::Window* petName;
    CEGUI::Window* aggressive;
    CEGUI::Window* defensive;
    CEGUI::Window* passive;
    CEGUI::Window* experience;
    CEGUI::Window* experienceOver;
    CEGUI::Window* statsUp;
    CEGUI::Window* skillUp;
    CEGUI::Window* mapPlus;
    CEGUI::Window* mapMinus;
};
typedef char hud_targetName[__builtin_offsetof(HUDState,targetName)==0xe8?1:-1];
typedef char hud_targetDescription[__builtin_offsetof(HUDState,targetDescription)==0xf0?1:-1];
typedef char hud_targetLevel[__builtin_offsetof(HUDState,targetLevel)==0xf8?1:-1];
typedef char hud_levelName[__builtin_offsetof(HUDState,levelName)==0x100?1:-1];
typedef char hud_merchantTip[__builtin_offsetof(HUDState,merchantTip)==0x108?1:-1];
typedef char hud_largeMessage[__builtin_offsetof(HUDState,largeMessage)==0x110?1:-1];
typedef char hud_smallMessage[__builtin_offsetof(HUDState,smallMessage)==0x118?1:-1];
typedef char hud_targetHealth[__builtin_offsetof(HUDState,targetHealth)==0x120?1:-1];
typedef char hud_targetBar[__builtin_offsetof(HUDState,targetBar)==0x128?1:-1];
typedef char hud_playButton[__builtin_offsetof(HUDState,playButton)==0x130?1:-1];
typedef char hud_bottom[__builtin_offsetof(HUDState,bottom)==0x138?1:-1];
typedef char hud_health[__builtin_offsetof(HUDState,health)==0x140?1:-1];
typedef char hud_healthOver[__builtin_offsetof(HUDState,healthOver)==0x148?1:-1];
typedef char hud_healthSub[__builtin_offsetof(HUDState,healthSub)==0x150?1:-1];
typedef char hud_mana[__builtin_offsetof(HUDState,mana)==0x158?1:-1];
typedef char hud_manaOver[__builtin_offsetof(HUDState,manaOver)==0x160?1:-1];
typedef char hud_manaSub[__builtin_offsetof(HUDState,manaSub)==0x168?1:-1];
typedef char hud_pet[__builtin_offsetof(HUDState,pet)==0x170?1:-1];
typedef char hud_petHealthOver[__builtin_offsetof(HUDState,petHealthOver)==0x178?1:-1];
typedef char hud_petHealth[__builtin_offsetof(HUDState,petHealth)==0x180?1:-1];
typedef char hud_petMana[__builtin_offsetof(HUDState,petMana)==0x190?1:-1];
typedef char hud_petManaOver[__builtin_offsetof(HUDState,petManaOver)==0x198?1:-1];
typedef char hud_fleeing[__builtin_offsetof(HUDState,fleeing)==0x1a8?1:-1];
typedef char hud_petName[__builtin_offsetof(HUDState,petName)==0x1b0?1:-1];
typedef char hud_aggressive[__builtin_offsetof(HUDState,aggressive)==0x1b8?1:-1];
typedef char hud_defensive[__builtin_offsetof(HUDState,defensive)==0x1c0?1:-1];
typedef char hud_passive[__builtin_offsetof(HUDState,passive)==0x1c8?1:-1];
typedef char hud_experience[__builtin_offsetof(HUDState,experience)==0x1d0?1:-1];
typedef char hud_experienceOver[__builtin_offsetof(HUDState,experienceOver)==0x1d8?1:-1];
typedef char hud_statsUp[__builtin_offsetof(HUDState,statsUp)==0x1e0?1:-1];
typedef char hud_skillUp[__builtin_offsetof(HUDState,skillUp)==0x1e8?1:-1];
typedef char hud_mapPlus[__builtin_offsetof(HUDState,mapPlus)==0x1f0?1:-1];
typedef char hud_mapMinus[__builtin_offsetof(HUDState,mapMinus)==0x1f8?1:-1];
struct HUDGeometry {
    char prefix[0x16cc];
    CEGUI::UVector2 healthPosition, manaPosition, experiencePosition, petHealthPosition, petManaPosition;
    CEGUI::UVector2 healthSize, manaSize, experienceSize, petHealthSize, petManaSize;
    CEGUI::UVector2 targetSize, targetPosition;
    char gap178C[0x199c-0x178c];
    CEGUI::Rect blockers[5];
};
typedef char geometry_healthPosition[__builtin_offsetof(HUDGeometry,healthPosition)==0x16cc?1:-1];
typedef char geometry_manaPosition[__builtin_offsetof(HUDGeometry,manaPosition)==0x16dc?1:-1];
typedef char geometry_experiencePosition[__builtin_offsetof(HUDGeometry,experiencePosition)==0x16ec?1:-1];
typedef char geometry_petHealthPosition[__builtin_offsetof(HUDGeometry,petHealthPosition)==0x16fc?1:-1];
typedef char geometry_petManaPosition[__builtin_offsetof(HUDGeometry,petManaPosition)==0x170c?1:-1];
typedef char geometry_healthSize[__builtin_offsetof(HUDGeometry,healthSize)==0x171c?1:-1];
typedef char geometry_manaSize[__builtin_offsetof(HUDGeometry,manaSize)==0x172c?1:-1];
typedef char geometry_experienceSize[__builtin_offsetof(HUDGeometry,experienceSize)==0x173c?1:-1];
typedef char geometry_petHealthSize[__builtin_offsetof(HUDGeometry,petHealthSize)==0x174c?1:-1];
typedef char geometry_petManaSize[__builtin_offsetof(HUDGeometry,petManaSize)==0x175c?1:-1];
typedef char geometry_targetSize[__builtin_offsetof(HUDGeometry,targetSize)==0x176c?1:-1];
typedef char geometry_targetPosition[__builtin_offsetof(HUDGeometry,targetPosition)==0x177c?1:-1];
typedef char geometry_blockers[__builtin_offsetof(HUDGeometry,blockers)==0x199c?1:-1];
inline __attribute__((always_inline)) void loadLayout(CEGUI::Window*& destination,CFileInfo& info,const wchar_t* path) {
    {
        std::wstring name(path);
        CFileSystem::getSingleton()->getFileInfo(name,info,false,true,false);
    }
    CEGUI::String name(info.m_sResourceName);
    destination=CEGUI::WindowManager::getSingleton().loadWindowLayout(name,true);
}
inline __attribute__((always_inline)) void bindChild(CEGUI::Window*& destination,CEGUI::Window*& root,const char* text) {
    CEGUI::String name(text);
    destination=root->recursiveChildSearch(name);
}
inline __attribute__((always_inline)) void geometry(CEGUI::Window*& window,CEGUI::UVector2& position,CEGUI::UVector2& size) {
    position=window->getPosition();
    size=window->getSize();
}
inline __attribute__((always_inline)) void createHUD(CGameUI* self,PrefixState& ui,SheetState& sheets,HUDState& hud,HUDGeometry& geom,CFileInfo& info) {
    loadLayout(hud.bottom,info,L"media/ui/bottomhud.layout");
    self->convertToScreenScale(hud.bottom,false);
    self->mapToFunctions(hud.bottom);
    self->mapEventHandlers(hud.bottom);
    bindChild(hud.playButton,hud.bottom,"PlayButton");
    hud.bottom->removeChildWindow(hud.playButton);
    const char* blockers[]={"LeftPaneBlocker","RightPaneBlocker","PetHudBlocker","BottomHudBlocker","BottomHudBlocker2"};
    for(unsigned i=0;i<5;++i) {
        CEGUI::Window* window;
        {CEGUI::String name(blockers[i]);window=hud.bottom->recursiveChildSearch(name);}
        geom.blockers[i]=window->getPixelRect();
    }
    bindChild(hud.health,hud.bottom,"PlayerHealthBar");
    hud.health->setTooltip(ui.system->getDefaultTooltip());
    geometry(hud.health,geom.healthPosition,geom.healthSize);
    bindChild(hud.healthSub,hud.bottom,"PlayerHealthBarSub");
    bindChild(hud.healthOver,hud.bottom,"PlayerHealthBarMouseover");
    hud.healthOver->setTooltip(ui.system->getDefaultTooltip());
    bindChild(hud.mana,hud.bottom,"PlayerManaBar");
    hud.mana->setTooltip(ui.system->getDefaultTooltip());
    bindChild(hud.manaSub,hud.bottom,"PlayerManaBarSub");
    geometry(hud.mana,geom.manaPosition,geom.manaSize);
    bindChild(hud.manaOver,hud.bottom,"PlayerManaBarMouseover");
    hud.manaOver->setTooltip(ui.system->getDefaultTooltip());
    bindChild(hud.experience,hud.bottom,"ExperienceBar");
    bindChild(hud.experienceOver,hud.bottom,"ExperienceBarMouseover");
    hud.experienceOver->setTooltip(ui.system->getDefaultTooltip());
    geometry(hud.experience,geom.experiencePosition,geom.experienceSize);
    bindChild(hud.statsUp,hud.bottom,"StatsUp");
    bindChild(hud.skillUp,hud.bottom,"SkillUp");
    bindChild(hud.mapPlus,hud.bottom,"AutomapPlus");
    hud.mapPlus->setWantsMultiClickEvents(false);
    bindChild(hud.mapMinus,hud.bottom,"AutomapMinus");
    hud.mapMinus->setWantsMultiClickEvents(false);
    sheets.ingame->addChildWindow(hud.bottom);
    loadLayout(hud.pet,info,L"media/ui/pethud.layout");
    self->convertToScreenScale(hud.pet,false);
    self->mapToFunctions(hud.pet);
    self->mapEventHandlers(hud.pet);
    sheets.ingame->addChildWindow(hud.pet);
    bindChild(hud.aggressive,hud.pet,"PetAggressive");
    bindChild(hud.passive,hud.pet,"PetPassive");
    bindChild(hud.defensive,hud.pet,"PetDefensive");
    if(hud.aggressive)static_cast<CEGUI::RadioButton*>(hud.aggressive)->setSelected(true);
    bindChild(hud.fleeing,hud.pet,"FleeingText");
    hud.fleeing->setVisible(false);
    bindChild(hud.petName,hud.pet,"PetName");
    bindChild(hud.petHealth,hud.pet,"PetHealthBar");
    geometry(hud.petHealth,geom.petHealthPosition,geom.petHealthSize);
    bindChild(hud.petHealthOver,hud.pet,"PetHealthBarMouseover");
    hud.petHealthOver->setTooltip(ui.system->getDefaultTooltip());
    bindChild(hud.petMana,hud.pet,"PetManaBar");
    bindChild(hud.petManaOver,hud.pet,"PetManaBarMouseover");
    // Original repeats the HEALTH mouseover assignment after finding mana.
    hud.petHealthOver->setTooltip(ui.system->getDefaultTooltip());
    geometry(hud.petMana,geom.petManaPosition,geom.petManaSize);
    bindChild(hud.merchantTip,hud.bottom,"MerchantTip");
    bindChild(hud.levelName,hud.bottom,"LevelName");
    bindChild(hud.largeMessage,hud.bottom,"LargeMessageText");
    bindChild(hud.smallMessage,hud.bottom,"SmallMessageText");
    hud.levelName->setVisible(false);
    hud.merchantTip->setVisible(false);
    hud.largeMessage->setVisible(false);
    hud.smallMessage->setVisible(false);
    bindChild(hud.targetHealth,hud.bottom,"TargetHealth");
    hud.targetHealth->setVisible(false);
    geom.targetPosition=hud.targetHealth->getPosition();
    bindChild(hud.targetBar,hud.bottom,"TargetHealthBar");
    geom.targetSize=hud.targetBar->getSize();
    bindChild(hud.targetName,hud.bottom,"TargetName");
    bindChild(hud.targetLevel,hud.bottom,"TargetLevel");
    bindChild(hud.targetDescription,hud.bottom,"TargetDescription");
    hud.targetName->setVisible(false);
    hud.targetLevel->setVisible(false);
    hud.targetDescription->setVisible(false);
}
}
#endif
