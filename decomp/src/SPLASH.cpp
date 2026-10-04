#include "EmptyStrings.h"
#include <cstring>
#include <iostream>
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "Splash.h"
#include "StringUtilities.h"
#include "GameNamespaces.h"

extern "C"
{
    struct SDL_RWops;
    struct SDL_Surface;

    struct SDL_RendererInfo
    {
        const char* name;
        unsigned int flags;
        unsigned int num_texture_formats;
        unsigned int texture_formats[16];
        int max_texture_width;
        int max_texture_height;
    };

    SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, unsigned int flags);
    void SDL_DestroyWindow(SDL_Window* window);
    void SDL_SetWindowPosition(SDL_Window* window, int x, int y);
    void SDL_ShowWindow(SDL_Window* window);
    void SDL_HideWindow(SDL_Window* window);
    int SDL_GetNumRenderDrivers();
    int SDL_GetRenderDriverInfo(int index, SDL_RendererInfo* info);
    SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, unsigned int flags);
    int SDL_GetRendererInfo(SDL_Renderer* renderer, SDL_RendererInfo* info);
    void SDL_DestroyRenderer(SDL_Renderer* renderer);
    int SDL_RenderClear(SDL_Renderer* renderer);
    int SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const void* srcrect, const void* dstrect);
    void SDL_RenderPresent(SDL_Renderer* renderer);
    SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
    void SDL_DestroyTexture(SDL_Texture* texture);
    SDL_RWops* SDL_RWFromFile(const char* file, const char* mode);
    SDL_Surface* SDL_LoadBMP_RW(SDL_RWops* src, int freesrc);
    void SDL_FreeSurface(SDL_Surface* surface);
}

namespace LinuxUtils
{
    void GetDesktopResolution(int& width, int& height);
}

static const int SDL_WINDOWPOS_CENTERED = 0x2fff0000;
static const unsigned int SDL_WINDOW_HIDDEN = 0x8;
static const unsigned int SDL_WINDOW_BORDERLESS = 0x10;

CSplash::CSplash()
    : m_pWindow(NULL),
      m_pRenderer(NULL),
      m_pTexture(NULL),
      m_iWidth(400),
      m_iHeight(315)
{
}

void CSplash::findCenterForWindow(int width, int height, int& x, int& y)
{
    y = 0;
    x = 0;
}

void CSplash::Hide()
{
    SDL_HideWindow(m_pWindow);
    m_bVisible = false;
}

void CSplash::Show()
{
    int width = m_iWidth;
    int height = m_iHeight;
    int desktopWidth;
    int desktopHeight;
    LinuxUtils::GetDesktopResolution(desktopWidth, desktopHeight);
    SDL_SetWindowPosition(m_pWindow, (desktopWidth - width) / 2, (desktopHeight - height) / 2);
    SDL_ShowWindow(m_pWindow);
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
    SDL_RenderPresent(m_pRenderer);
    m_bVisible = true;
}

CSplash::~CSplash()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
}

void CSplash::Init(void* parentWindow, int unused)
{
    m_pWindow = SDL_CreateWindow("Torchlight Loading", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 m_iWidth, m_iHeight, SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
    if (m_pWindow)
    {
        SDL_RendererInfo info;
        int driver = -1;
        int driverCount = SDL_GetNumRenderDrivers();
        for (int i = 0; i < driverCount; ++i)
        {
            SDL_GetRenderDriverInfo(i, &info);
            if (strcmp(info.name, "software") == 0)
            {
                driver = i;
                break;
            }
        }
        m_pRenderer = SDL_CreateRenderer(m_pWindow, driver, 0);
        SDL_GetRendererInfo(m_pRenderer, &info);
        std::string path = STRINGS::StringConvertToUTF8(FILESYSTEM::GetApplicationPath() + L"logo.bmp");
        SDL_Surface* surface = SDL_LoadBMP_RW(SDL_RWFromFile(path.c_str(), "rb"), 1);
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
        SDL_FreeSurface(surface);
    }
    m_bVisible = false;
}
