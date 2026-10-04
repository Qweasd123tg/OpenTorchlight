#include "EmptyStrings.h"
#include "MouseManager.h"

#include <string.h>

CMouseManager::CMouseManager()
{
    m_iWheel = 0;
    m_iPendingWheel = 0;
    flushAll();
}

enum
{
    WM_LBUTTONDOWN = 0x201,
    WM_LBUTTONUP = 0x202,
    WM_LBUTTONDBLCLK = 0x203,
    WM_RBUTTONDOWN = 0x204,
    WM_RBUTTONUP = 0x205,
    WM_RBUTTONDBLCLK = 0x206,
    WM_MBUTTONDOWN = 0x207,
    WM_MBUTTONUP = 0x208,
    WM_MOUSEWHEEL = 0x20a
};

void CMouseManager::mouseEvent(unsigned int message, unsigned int wParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (!m_bDown[MOUSE_BUTTON_LEFT])
            m_bPendingPressed[MOUSE_BUTTON_LEFT] = true;
        m_bDown[MOUSE_BUTTON_LEFT] = true;
        break;
    case WM_LBUTTONUP:
        m_bDown[MOUSE_BUTTON_LEFT] = false;
        break;
    case WM_LBUTTONDBLCLK:
        m_bPendingDoubleClick[MOUSE_BUTTON_LEFT] = true;
        break;
    case WM_RBUTTONDOWN:
        if (!m_bDown[MOUSE_BUTTON_RIGHT])
            m_bPendingPressed[MOUSE_BUTTON_RIGHT] = true;
        m_bDown[MOUSE_BUTTON_RIGHT] = true;
        break;
    case WM_RBUTTONUP:
        m_bDown[MOUSE_BUTTON_RIGHT] = false;
        break;
    case WM_RBUTTONDBLCLK:
        m_bPendingDoubleClick[MOUSE_BUTTON_RIGHT] = true;
        break;
    case WM_MBUTTONDOWN:
        if (!m_bDown[MOUSE_BUTTON_MIDDLE])
            m_bPendingPressed[MOUSE_BUTTON_MIDDLE] = true;
        m_bDown[MOUSE_BUTTON_MIDDLE] = true;
        break;
    case WM_MBUTTONUP:
        m_bDown[MOUSE_BUTTON_MIDDLE] = false;
        break;
    case WM_MOUSEWHEEL:
        m_iPendingWheel += (int)wParam >> 16;
        break;
    }
}

bool CMouseManager::buttonPressed(EMouseButton button)
{
    return m_bPressed[button] == 1;
}

bool CMouseManager::buttonHeld(EMouseButton button)
{
    return m_bHeld[button] == 1 || m_bPressed[button] == 1;
}

bool CMouseManager::buttonDoubleClick(EMouseButton button)
{
    return m_bDoubleClick[button] == 1;
}

POINT* CMouseManager::virtualMousePosition(float screenWidth, float screenHeight, float virtualWidth, float virtualHeight)
{
    m_VirtualPosition.x = (int)(m_Position.x * (virtualWidth / screenWidth));
    m_VirtualPosition.y = (int)(m_Position.y * (virtualHeight / screenHeight));
    return &m_VirtualPosition;
}

void CMouseManager::capture()
{
    memcpy(m_bHeld, m_bDown, sizeof(m_bHeld));
    memcpy(m_bPressed, m_bPendingPressed, sizeof(m_bPressed));
    memcpy(m_bDoubleClick, m_bPendingDoubleClick, sizeof(m_bDoubleClick));
    memset(m_bPendingPressed, 0, sizeof(m_bPendingPressed));
    memset(m_bPendingDoubleClick, 0, sizeof(m_bPendingDoubleClick));
    m_iWheel = m_iPendingWheel;
    m_iPendingWheel = 0;
}

void CMouseManager::flushAll()
{
    m_iPendingWheel = 0;
    memset(m_bDown, 0, sizeof(m_bDown));
    memset(m_bPendingPressed, 0, sizeof(m_bPendingPressed));
    memset(m_bPendingDoubleClick, 0, sizeof(m_bPendingDoubleClick));
}

void CMouseManager::flush()
{
    m_iPendingWheel = 0;
    memset(m_bPendingPressed, 0, sizeof(m_bPendingPressed));
    memset(m_bPendingDoubleClick, 0, sizeof(m_bPendingDoubleClick));
}

void CMouseManager::update(void* window)
{
    GetCursorPos(&m_Position);
}

CMouseManager::~CMouseManager()
{
}

