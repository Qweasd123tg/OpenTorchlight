#ifndef LINUXUTILS_H
#define LINUXUTILS_H

#include <string>

struct POINT
{
    long x;
    long y;
};
int GetCursorPos(POINT* point);

// Partial: declarations from LinuxUtils.cpp used by recovered TUs.
struct POINT
{
    long x;
    long y;
};

unsigned int GetTickCount();
int GetCursorPos(POINT* point);
short GetAsyncKeyState(unsigned int key);

namespace LinuxUtils
{
    std::wstring GetHomeDir();
    int GetPhysicalRAMSize();
    int GetCPUFrequency();
}

#endif
