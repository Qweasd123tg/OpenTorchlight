#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

// Game globals by symbol, promoted from the generated headers as recovered code needs
// them; types from Hungarian prefixes or sizes until a TU defines them.

#include <string>

extern int KSETTINGS_KEYMAP_ZOOMIN;
extern int KSETTINGS_KEYMAP_ZOOMOUT;
extern int KSETTINGS_RES_HEIGHT;
extern int KSETTINGS_RES_WIDTH;
static unsigned char gANIMATIONPLAYER_TYPE_NAMES[32];
static unsigned char gCAMERA_TYPE_NAMES[16];
static unsigned char gGAMESTATE_NAMES[56];
static unsigned char gINTERACTABLE_TYPE_NAMES[32];
static unsigned char gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES[16];
static unsigned char gPARTICLE_COLLISION_TYPE[24];
static unsigned char gPARTICLE_INTERSECTION_TYPE[24];
static unsigned char gPROPERTY_NODE_TYPE_NAMES[128];
static unsigned char gQUEST_REQUIREMENTS[24];
static unsigned char gRANDOMGROUP_NAMES[24];
static unsigned char gRESOURCE_GROUP_NAMES[32];
static unsigned char g_DescriptorController[96];
static unsigned char g_LayoutToCloneOrControl[48];
static unsigned char g_MeshFilesByIndex[48];
static long g_MissilePreloader;
static long g_SkillParser;
static bool g_bCachParticles;
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
extern long m_pMasterResourceManager;

#endif
