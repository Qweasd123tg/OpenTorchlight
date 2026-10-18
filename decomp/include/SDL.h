#ifndef SDL_H
#define SDL_H

// Partial: the SDL 1.3 declarations the game uses. SDL is a library, it is
// linked, not recovered.

typedef unsigned char Uint8;
typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef int Sint32;
enum SDL_bool { SDL_FALSE = 0, SDL_TRUE = 1 };
enum SDL_Keymod { KMOD_NONE = 0 };
#include "SDLEventHandler.h"
// Only the event fields consumed by the original executable are exposed.
// Its pre-release mouse ABI predates the Uint32 which field in released SDL2.
struct SDL_WindowEvent { Uint32 type,timestamp,windowID; Uint8 event,padding1,padding2,padding3; Sint32 data1,data2; };
struct SDL_Keysym { SDL_Scancode scancode; Sint32 sym; Uint16 mod; Uint32 unused; };
struct SDL_KeyboardEvent { Uint32 type,timestamp,windowID; Uint8 state,repeat,padding2,padding3; SDL_Keysym keysym; };
struct SDL_TextInputEvent { Uint32 type,timestamp,windowID; char text[32]; };
struct SDL_MouseMotionEvent { Uint32 type,timestamp,windowID; Uint8 state,padding1,padding2,padding3; Sint32 x,y,xrel,yrel; };
struct SDL_MouseButtonEvent { Uint32 type,timestamp,windowID; Uint8 button,state,padding1,padding2; Sint32 x,y; };
struct SDL_MouseWheelEvent { Uint32 type,timestamp,windowID; Sint32 x,y; };
union SDL_Event { Uint32 type; SDL_WindowEvent window; SDL_KeyboardEvent key; SDL_TextInputEvent text; SDL_MouseMotionEvent motion; SDL_MouseButtonEvent button; SDL_MouseWheelEvent wheel; Uint8 padding[56]; };
struct SDL_DisplayMode { Uint32 format; int w,h,refresh_rate; void* driverdata; };
struct SDL_version { Uint8 major,minor,patch; };
struct SDL_SysWMinfo { SDL_version version; int subsystem; union { struct { void* display; unsigned long window; } x11; void* padding[3]; } info; };

struct SDL_Window;
struct SDL_RWops;
struct SDL_Surface;
struct SDL_Cursor;

enum SDL_WindowFlags
{
    SDL_WINDOW_INPUT_FOCUS = 0x00000200
};

extern "C"
{
    SDL_bool SDL_GetWindowWMInfo(SDL_Window*,SDL_SysWMinfo*);
    SDL_Keymod SDL_GetModState();
    Uint32 SDL_GetWindowID(SDL_Window*);
    void SDL_ShowWindow(SDL_Window*);
    void SDL_GetWindowSize(SDL_Window*,int*,int*);
    void SDL_SetWindowSize(SDL_Window*,int,int);
    int SDL_SetWindowFullscreen(SDL_Window*,Uint32);
    void SDL_SetWindowPosition(SDL_Window*,int,int);
    void SDL_SetWindowGrab(SDL_Window*,SDL_bool);
    int SDL_VideoInit(const char*);
    void SDL_Quit();
    void SDL_VideoQuit();
    int SDL_PollEvent(SDL_Event*);
    int SDL_PushEvent(SDL_Event*);
    const char* SDL_GetError();
    int SDL_GetDesktopDisplayMode(int,SDL_DisplayMode*);
    int SDL_GetNumVideoDisplays();
    int SDL_GetNumDisplayModes(int);
    int SDL_GetDisplayMode(int,int,SDL_DisplayMode*);
    SDL_bool SDL_PixelFormatEnumToMasks(Uint32,int*,Uint32*,Uint32*,Uint32*,Uint32*);
    SDL_RWops* SDL_RWFromFile(const char* file,const char* mode);
    SDL_Surface* SDL_LoadBMP_RW(SDL_RWops* source,int freeSource);
    int SDL_ShowCursor(int toggle);
    void SDL_SetCursor(SDL_Cursor* cursor);
    void SDL_FreeCursor(SDL_Cursor* cursor);
    SDL_Cursor* SDL_CreateColorCursor(SDL_Surface* surface,int hotX,int hotY);
    void SDL_FreeSurface(SDL_Surface* surface);
    SDL_Window* SDL_GetWindowFromID(Uint32 id);
    Uint32 SDL_GetWindowFlags(SDL_Window* window);
}

#endif
