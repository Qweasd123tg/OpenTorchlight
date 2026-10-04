#include "EmptyStrings.h"
#include "MouseHandler.h"

struct SDL_Window;
extern "C" SDL_Window* SDL_GetWindowFromID(unsigned int id);
extern "C" unsigned int SDL_GetWindowFlags(SDL_Window* window);

CMouseHandler::CMouseHandler(void* window) : CRunicCore(), m_pWindow(window) {}
CMouseHandler::~CMouseHandler() {}

POINT CMouseHandler::MousePosition()
{
    POINT point;
    GetCursorPos(&point);
    return point;
}

bool CMouseHandler::MouseIsInWindow()
{
    SDL_Window* window = SDL_GetWindowFromID(static_cast<unsigned int>(reinterpret_cast<unsigned long>(m_pWindow)));
    return (SDL_GetWindowFlags(window) & 0x200) != 0;
}

bool CMouseHandler::MouseCenterButtonDown()
{
    return (GetAsyncKeyState(4) & 0x8000) != 0;
}

bool CMouseHandler::MouseRightButtonDown()
{
    return (GetAsyncKeyState(2) & 0x8000) != 0;
}

bool CMouseHandler::MouseLeftButtonDown()
{
    return (GetAsyncKeyState(1) & 0x8000) != 0;
}
