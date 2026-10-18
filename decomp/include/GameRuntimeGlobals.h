#ifndef GAME_RUNTIME_GLOBALS_H
#define GAME_RUNTIME_GLOBALS_H
class CGame; class CSplash;
extern CSplash m_gSplash;
static int gLastWidth; // 0x14263c0
static int GResizeWidth; // 0x14263cc
static int GResizeHeight; // 0x14263d0
static int gLastHeight; // 0x14263c4
static bool GRecreateUI; // 0x14263d4
static int gLastFullscreen; // 0x14263c8
static int gFailWidth; // 0x14263d8
static int gFailHeight; // 0x14263dc
static bool GResizing; // 0x14263e0
static int g_ResetFrames; // 0x14263e4
static float gfLastTimeElapsed; // 0x14263e8
static int g_Frames; // 0x14263f8
static bool gUseSplash; // 0x14210a4
static CGame* g_pGame; // 0x1426410
static bool gFirstRun; // 0x1426408

#endif
