#ifndef SETTINGS_H
#define SETTINGS_H

#include "CmdLineParser.h"
#include "DynamicPropertyFile.h"

// Property indices registered by CSettings.
extern unsigned int KSETTINGS_S_ZIP_LOADING;
extern unsigned int KSETTINGS_ZIP_COUNT;
extern unsigned int KSETTINGS_DEBUG_LOGIC;
extern unsigned int KSETTINGS_YRATIO;
extern unsigned int KSETTINGS_DISPLAY_STATS;
extern unsigned int KSETTINGS_KEYMAP_SHOWITEMS;
extern unsigned int KSETTINGS_KEYMAP_SWAPSKILLS;
extern unsigned int KSETTINGS_TOGGLE_ITEM_NAME;


// Partial: declarations from Settings.cpp used by recovered TUs; only the
// leading field is recovered.
class CSettings : public CDynamicPropertyFile
{
public:
    virtual ~CSettings();

    CCmdLineParser* m_pCmdLineParser;
};

#endif
