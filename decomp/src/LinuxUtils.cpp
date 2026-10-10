#include "LinuxUtils.h"
#include <sys/time.h>
#include <cstring>
// Existing private globals in the original Linux input layer.
namespace LinuxUtils {
extern int desktopWidth __asm__("_ZN10LinuxUtilsL12desktopWidthE");
extern int desktopHeight __asm__("_ZN10LinuxUtilsL13desktopHeightE");
extern std::wstring gameDataPath __asm__("_ZN10LinuxUtilsL12gameDataPathE");
extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");
extern std::wstring gameTempPath __asm__("_ZN10LinuxUtilsL12gameTempPathE");
}
extern long MouseX __asm__("_ZL6MouseX");
extern long MouseY __asm__("_ZL6MouseY");
extern bool keyStates[256] __asm__("_ZL9keyStates") __attribute__((aligned(32)));
#include "LinuxUtils.h"


// Imported source candidates; historical status is not fresh acceptance.
void LinuxUtils::SaveDesktopResolution(int width, int height)
{
    desktopWidth=width;
    desktopHeight=height;
}

void LinuxUtils::GetDesktopResolution(int& width, int& height)
{
    width=desktopWidth;
    height=desktopHeight;
}

std::wstring LinuxUtils::GetHomeDir()
{
    return gameHomePath;
}

std::wstring LinuxUtils::GetTempDir()
{
    return gameTempPath;
}

std::wstring LinuxUtils::GetAppDir()
{
    return gameDataPath;
}

unsigned int GetTickCount()
{
    timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

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
