#ifndef LINUXUTILS_H
#define LINUXUTILS_H

#include <string>
#include <cstdio>
struct SDL_Window;
int MessageBoxA(void*, const char*, const char*, int);
int MessageBox(void*, const wchar_t*, const wchar_t*, int);
// FLTK fl_ask.H: shared label pointer used by MessageBoxA.
extern const char* fl_ok;

// Partial: declarations from LinuxUtils.cpp used by recovered TUs.
struct POINT
{
    long x;
    long y;
};

unsigned int GetTickCount();
int _wfopen_s(FILE**, const wchar_t*, const wchar_t*);
int SetCurrentDirectory(std::wstring);
int GetCursorPos(POINT* point);
short GetAsyncKeyState(unsigned int key);
// Original 0xf632a0 returns 32 bits consumed by CEGUI as an unsigned scan code.
// The original return type spelling/signedness is not encoded by its symbol.
unsigned int LinuxMapVirtual2Scancode(unsigned int key);

namespace LinuxUtils
{
    void* GetSDLWindowHandle(SDL_Window*);
    void crash_handler(int);
    void Init();
    extern std::wstring gameDataPath __asm__("_ZN10LinuxUtilsL12gameDataPathE");
    extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");
    extern std::wstring gameTempPath __asm__("_ZN10LinuxUtilsL12gameTempPathE");
    int GetIntLine(const std::string& path, const std::string& key);
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
