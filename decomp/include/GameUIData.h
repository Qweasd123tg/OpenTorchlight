#ifndef GAMEUIDATA_H
#define GAMEUIDATA_H
class CGameUI;
// Original TU-local singleton pointer, gameui.cpp, 0x14b9c68.
// Preserve original per-call loads across reentrant collaborators.
static CGameUI* volatile g_pGameUI;
#endif
