#ifndef SDL_H
#define SDL_H

// Partial: the SDL 1.3 declarations the game uses. SDL is a library, it is
// linked, not recovered.

typedef unsigned char Uint8;
typedef unsigned int Uint32;

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
    SDL_RWops* SDL_RWFromFile(const char* file,const char* mode);
    SDL_Surface* SDL_LoadBMP_RW(SDL_RWops* source,int freeSource);
    SDL_Cursor* SDL_CreateColorCursor(SDL_Surface* surface,int hotX,int hotY);
    void SDL_FreeSurface(SDL_Surface* surface);
    SDL_Window* SDL_GetWindowFromID(Uint32 id);
    Uint32 SDL_GetWindowFlags(SDL_Window* window);
}

#endif
