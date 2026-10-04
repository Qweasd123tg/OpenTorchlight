#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

// Game globals by symbol, promoted from the generated headers as recovered code needs
// them; types from Hungarian prefixes or sizes until a TU defines them.

#include <string>

static unsigned char gANIMATIONPLAYER_TYPE_NAMES[32];
static unsigned char gRESOURCE_GROUP_NAMES[32];
extern bool g_bWasRestarted;
extern unsigned char g_hRestartingFile[4];
extern void* g_pQuestManager;
static unsigned char g_strStatDefines[744];
static int m_gQuestUnitDataID;
extern long m_pMasterResourceManager;

#endif
