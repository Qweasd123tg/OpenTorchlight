#include "LinuxUtils.h"
#include <cstring>
extern long MouseX __asm__("_ZL6MouseX");
extern long MouseY __asm__("_ZL6MouseY");
extern bool keyStates[256] __asm__("_ZL9keyStates") __attribute__((aligned(32)));

void UpdateCursorPos(long x, long y)
{
    MouseX=x;
    MouseY=y;
}

int GetCursorPos(POINT* point)
{
    point->x=MouseX;
    point->y=MouseY;
    return 0;
}

int SetCursorPos(int x, int y)
{
    return 0;
}

void UpdateKeyState(unsigned int key, bool pressed)
{
    keyStates[key]=pressed;
}

short GetAsyncKeyState(unsigned int key)
{
    return keyStates[key] ? static_cast<short>(0x8000) : 0;
}

short GetKeyState(unsigned int key)
{
    return keyStates[key] ? static_cast<short>(0x8000) : 0;
}

void ClearKeyState()
{
    std::memset(keyStates,0,sizeof(keyStates));
}

#include "WinMouseAndKeys.h"

unsigned int LinuxMapVirtual2Scancode(unsigned int key)
{
    return virt2scanMap[key];
}
