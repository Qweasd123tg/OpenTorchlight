#ifndef LINUXUTILS_H
#define LINUXUTILS_H

#include <string>

// Partial: declarations from LinuxUtils.cpp used by recovered TUs.
unsigned int GetTickCount();
short GetAsyncKeyState(unsigned int key);

namespace LinuxUtils
{
    std::wstring GetHomeDir();
    int GetPhysicalRAMSize();
    int GetCPUFrequency();
}

#endif
