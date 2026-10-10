#ifndef GAMEUI_CALL_BOUNDARIES_H
#define GAMEUI_CALL_BOUNDARIES_H
class CGameUI;
// Preserve the original out-of-line calls inside flattened recovered UI phases.
extern float gameuiBoundaryWidth(CGameUI*) __asm__("_ZN7CGameUI14getWindowWidthEv");
extern float gameuiBoundaryHeight(CGameUI*) __asm__("_ZN7CGameUI15getWindowHeightEv");
extern float gameuiBoundaryScaledY(CGameUI*, float) __asm__("_ZN7CGameUI7scaledYEf");
#include "GameEnums.h"
extern void gameuiBoundaryCursor(CGameUI*, ECursorState) __asm__("_ZN7CGameUI14setCursorStateE12ECursorState");
extern void gameuiBoundaryCloseLeft(CGameUI*) __asm__("_ZN7CGameUI9closeLeftEv");
extern void gameuiBoundaryCloseRight(CGameUI*) __asm__("_ZN7CGameUI10closeRightEv");
#endif
