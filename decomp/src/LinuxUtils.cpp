#include <fstream>
#include <cstdlib>
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















int LinuxUtils::GetIntLine(const std::string& path, const std::string& key)
{
    std::ifstream file(path.c_str());
    std::string line;
    while (std::getline(file, line).good()) {
        if (line.compare(0, key.length(), key) == 0) {
            std::string::size_type first = line.find_first_of("0123456789");
            if (first != std::string::npos) {
                std::string::size_type end = line.find_first_not_of("0123456789", first);
                return std::atoi(line.substr(first, end - first).c_str());
            }
        }
    }
    return 0;
}

int LinuxUtils::GetPhysicalRAMSize()
{
    return GetIntLine("/proc/meminfo", "MemTotal") * 1024;
}

#include <sys/stat.h>
extern std::string UTF32ToUTF8(const std::wstring&);

int _wfopen_s(FILE** file, const wchar_t* filename, const wchar_t* mode)
{
    std::string path = UTF32ToUTF8(std::wstring(filename));
    std::string flags = UTF32ToUTF8(std::wstring(mode));
    *file = fopen(path.c_str(), flags.c_str());
    return 0;
}

int LinuxUtils::GetCPUFrequency()
{
    struct stat information;
    if (stat("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", &information) == 0)
    {
        std::ifstream input("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
        std::string line;
        if (std::getline(input, line).good())
            return std::atoi(line.c_str()) / 1000;
    }
    return GetIntLine("/proc/cpuinfo", "cpu MHz");
}


int MessageBox(void*, const wchar_t* text, const wchar_t* title, int type)
{
    std::string message = UTF32ToUTF8(std::wstring(text));
    std::string caption = UTF32ToUTF8(std::wstring(title));
    return MessageBoxA(NULL,message.c_str(),caption.c_str(),type);
}

#include <execinfo.h>
#include <signal.h>
void LinuxUtils::crash_handler(int signal)
{
    void* trace[40];
    int size = backtrace(trace,40);
    fprintf(stderr,"Error: signal: %d\n\n",signal);
    backtrace_symbols_fd(trace,size,2);
    if (signal != SIGTRAP) exit(2);
}

#include "SDL.h"
void* LinuxUtils::GetSDLWindowHandle(SDL_Window* window)
{
    SDL_SysWMinfo info;
    info.version.major=2;
    info.version.minor=0;
    info.version.patch=0;
    SDL_GetWindowWMInfo(window,&info);
    return reinterpret_cast<void*>(info.info.x11.window);
}

#include <FL/Fl.H>
#include <FL/fl_ask.H>
int MessageBoxA(void*,const char* text,const char* title,int type)
{
    Fl::lock();
    fl_message_title(title);
    int result=1;
    switch (type&15) {
    case 0: result=fl_choice("%s",fl_ok,NULL,NULL,text)+1;break;
    case 1: result=fl_choice("%s",fl_ok,"Cancel",NULL,text)+1;break;
    case 5: result=fl_choice("%s","Retry","Cancel",NULL,text)+1;break;
    }
    Fl::wait(0.0);
    Fl::unlock();
    fprintf(stderr,"MessageBox: %s :: %s\n",text,title);
    return result;
}

#include <binreloc.h>
#include <clocale>
extern std::wstring UTF8ToUTF32(const std::string&);

void LinuxUtils::Init()
{
    BrInitError error;
    if (!br_init(&error)) {
        MessageBoxA(NULL,"Could not locate game binary","Initialization Error",0);
        exit(1);
    }
    char* executable = br_find_exe_dir(NULL);
    if (!executable) {
        MessageBoxA(NULL,"Could not locate game binary","Initialization Error",0);
        exit(1);
    }
    gameDataPath = UTF8ToUTF32(std::string(executable));
    if (gameDataPath[gameDataPath.size()-1] != L'/')
        gameDataPath += L"/";
    free(executable);
    if (!setlocale(LC_CTYPE,"")) {
        MessageBoxA(NULL,"Could not set LC_CTYPE locale","Initialization Error",0);
        exit(1);
    }
    char* home = getenv("HOME");
    if (!home) {
        MessageBoxA(NULL,"Could not find home directory.  Is HOME set?","Initialization Error",0);
        exit(1);
    }
    gameHomePath = UTF8ToUTF32(std::string(home));
    if (gameHomePath[gameHomePath.size()-1] != L'/')
        gameHomePath += L"/";
    char* temporary = getenv("TMPDIR");
    gameTempPath = UTF8ToUTF32(std::string(temporary ? temporary : "/tmp"));
    if (gameTempPath[gameTempPath.size()-1] != L'/')
        gameTempPath += L"/";
    signal(SIGSEGV,crash_handler);
    signal(SIGABRT,crash_handler);
    signal(SIGTRAP,crash_handler);
}
