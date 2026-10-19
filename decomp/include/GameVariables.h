#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

// Game globals by symbol, promoted from the generated headers as recovered code needs
// them; types from Hungarian prefixes or sizes until a TU defines them.

#include <string>
#include "TArrayList.h"
#include "SettingsVariables.h"

// One-byte TU-local switches from the original gameui.cpp BSS symbols.
static bool gToggleInventory;
static bool gTogglePet;
static bool gToggleStats;

extern int KSETTINGS_KEYMAP_CLOSEALL;
extern int KSETTINGS_KEYMAP_PAUSE;
extern int KSETTINGS_KEYMAP_ZOOMIN;
extern int KSETTINGS_KEYMAP_ZOOMOUT;
static std::wstring gANIMATIONPLAYER_TYPE_NAMES[4] = {
    L"PLAYER", L"MONSTERS", L"UNITTYPE", L"PROP"
};
static std::wstring gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES[2] = {
    L"Average", L"Add"
};
static std::wstring gPARTICLE_INTERSECTION_TYPE[3] = {
    L"Fast", L"Box", L""
};
static std::wstring gQUEST_REQUIREMENTS[3] = {
    L"QUESTSCOMPLETE", L"QUESTSNOTCOMPLETE", L"QUESTSACTIVE"
};
static std::wstring g_QUEST_TAG_DIALOG_ITEM_NAMES[2] = {
    L"GIVEITEM", L"TAKEITEM"
};
static std::wstring gRESOURCE_GROUP_NAMES[4] = {
    L"ITEMS", L"MONSTERS", L"PLAYERS", L"PROPS"
};
static TArrayList<std::wstring> g_FileList(10);
static TArrayList<std::wstring> g_SkillNames(5);
static unsigned char g_LayoutToCloneOrControl[48];
static unsigned char g_MeshFilesByIndex[48];
static long g_MissilePreloader;
static long g_SkillParser;
static bool g_bCachParticles;
extern bool gbWasVisible; // original one-byte global used by level.cpp
extern bool g_bWasRestarted;
extern unsigned char g_hRestartingFile[4];
static void* g_pCameraControl;
static void* g_pCinematics;
static void* g_pDungeonManager;
static void* g_pGameSpeed;
extern void* g_pQuestManager;
static void* g_pRandomNames;
static void* g_pRecipes;
static void* g_pSets;
static void* g_pSharedStash;
static void* g_pUnitThemes;
static unsigned char g_strStatDefines[744];
static int m_gQuestUnitDataID;
extern long m_gRoomPieceInformation;
extern long m_gStatsObject;
class CMasterResourceManager;
extern CMasterResourceManager* m_pMasterResourceManager;

#endif
