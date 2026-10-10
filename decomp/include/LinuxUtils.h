#ifndef LINUXUTILS_H
#define LINUXUTILS_H

#include <string>

// Partial: declarations from LinuxUtils.cpp used by recovered TUs.
struct POINT
{
    long x;
    long y;
};

unsigned int GetTickCount();
int GetCursorPos(POINT* point);
short GetAsyncKeyState(unsigned int key);
// Original 0xf632a0 returns 32 bits consumed by CEGUI as an unsigned scan code.
// The original return type spelling/signedness is not encoded by its symbol.
unsigned int LinuxMapVirtual2Scancode(unsigned int key);

namespace LinuxUtils
{
    std::wstring GetHomeDir();
    int GetPhysicalRAMSize();
    int GetCPUFrequency();
}


// Signatures retained from the supplied pass10 source, verified against the original at import.
namespace LinuxUtils {
void SaveDesktopResolution(int width, int height);
void GetDesktopResolution(int& width, int& height);
std::wstring GetHomeDir();
std::wstring GetTempDir();
std::wstring GetAppDir();
}
unsigned int GetTickCount();
void UpdateCursorPos(long x, long y);
int GetCursorPos(POINT* point);
int SetCursorPos(int x, int y);
void UpdateKeyState(unsigned int key, bool pressed);
short GetAsyncKeyState(unsigned int key);
short GetKeyState(unsigned int key);
void ClearKeyState();
#endif
