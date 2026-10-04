#include "EmptyStrings.h"
#include "MouseHandler.h"

#include <SDL.h>

CMouseHandler::CMouseHandler(void* window)
    : m_pWindow(window)
{
}

POINT CMouseHandler::MousePosition()
{
    POINT position;
    GetCursorPos(&position);
    return position;
}

bool CMouseHandler::MouseIsInWindow()
{
    return (SDL_GetWindowFlags(SDL_GetWindowFromID((Uint32)(size_t)m_pWindow)) & SDL_WINDOW_INPUT_FOCUS) != 0;
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

CMouseHandler::~CMouseHandler()
{
}
