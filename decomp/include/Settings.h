#ifndef SETTINGS_H
#define SETTINGS_H

#include "CmdLineParser.h"
#include "DynamicPropertyFile.h"

// Property indices registered by CSettings.
extern unsigned int KSETTINGS_S_ZIP_LOADING;
extern unsigned int KSETTINGS_ZIP_COUNT;

// Partial: declarations from Settings.cpp used by recovered TUs; only the
// leading field is recovered.
class CSettings : public CDynamicPropertyFile
{
public:
    virtual ~CSettings();

    CCmdLineParser* m_pCmdLineParser;
};

#endif
