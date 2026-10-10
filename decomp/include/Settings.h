#ifndef SETTINGS_H
#define SETTINGS_H

#include "CmdLineParser.h"
#include "DynamicPropertyFile.h"
#include "TArrayList.h"

// Property indices registered by CSettings.
extern unsigned int KSETTINGS_SOUNDMUTE;
extern unsigned int KSETTINGS_MUSICMUTE;
extern unsigned int KSETTINGS_DESTROY_MONSTERS_AFTER_DEATH;
extern unsigned int KSETTINGS_SHOW_TIPS;
extern unsigned int KSETTINGS_KEYMAP_AUTOMAP;
extern unsigned int KSETTINGS_KEYMAP_AUTOMAPZOOMIN;
extern unsigned int KSETTINGS_KEYMAP_AUTOMAPZOOMOUT;
extern unsigned int KSETTINGS_KEYMAP_CONSOLE_HOLD;
extern unsigned int KSETTINGS_KEYMAP_CONSOLE_PRESS;
extern unsigned int KSETTINGS_KEYMAP_CYCLESKILLDOWN;
extern unsigned int KSETTINGS_KEYMAP_CYCLESKILLUP;
extern unsigned int KSETTINGS_KEYMAP_INVENTORY;
extern unsigned int KSETTINGS_KEYMAP_JOURNAL;
extern unsigned int KSETTINGS_KEYMAP_PET;
extern unsigned int KSETTINGS_KEYMAP_QUESTS;
extern unsigned int KSETTINGS_KEYMAP_SKILLS;
extern unsigned int KSETTINGS_KEYMAP_STATS;
extern unsigned int KSETTINGS_KEYMAP_WEAPONSET;
extern unsigned int KSETTINGS_S_PATH_SCREENSHOTS;

extern unsigned int KSETTINGS_S_ZIP_LOADING;
extern unsigned int KSETTINGS_ZIP_COUNT;
extern unsigned int KSETTINGS_DEBUG_LOGIC;
extern unsigned int KSETTINGS_YRATIO;
extern unsigned int KSETTINGS_DISPLAY_STATS;
extern unsigned int KSETTINGS_KEYMAP_SHOWITEMS;
extern unsigned int KSETTINGS_KEYMAP_SWAPSKILLS;
extern unsigned int KSETTINGS_TOGGLE_ITEM_NAME;

// The empty user destructor retains the array cookie observed in CSettings::~CSettings.
struct CSettingsResolution
{
    int width;
    int height;
    bool flag8; // +0x8
    bool flag9; // +0x9
    bool flagA; // +0xa
    CSettingsResolution() : width(0), height(0), flag8(false), flag9(false), flagA(false) {}
    ~CSettingsResolution() {}
};
// Partial: resolution records begin at 0x148 after the parser pointer.
class CSettings : public CDynamicPropertyFile
{
public:
    void addResolutionCombo(int width, int height, bool flag8, bool flagA, bool flag9);

    void findClosestResolution(int width,int height,int& resultWidth,int& resultHeight);

    virtual ~CSettings();

    CCmdLineParser* m_pCmdLineParser;
    TArrayList<CSettingsResolution> m_resolutions;
};

extern unsigned int KSETTINGS_AMBIENT_LIGHT_RED;
extern unsigned int KSETTINGS_AMBIENT_LIGHT_GREEN;
extern unsigned int KSETTINGS_AMBIENT_LIGHT_BLUE;
extern unsigned int KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED;
extern unsigned int KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN;
extern unsigned int KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE;
extern unsigned int KSETTINGS_DIRECTIONAL_LIGHT_RED;
extern unsigned int KSETTINGS_DIRECTIONAL_LIGHT_GREEN;
extern unsigned int KSETTINGS_DIRECTIONAL_LIGHT_BLUE;
extern unsigned int KSETTINGS_F_DIRECTIONAL_INTENSITY;
extern int KSETTINGS_RES_WIDTH;
extern int KSETTINGS_RES_HEIGHT;
extern unsigned int KSETTINGS_WIN_WIDTH;
extern unsigned int KSETTINGS_WIN_HEIGHT;
extern unsigned int KSETTINGS_XRATIO;
#endif
