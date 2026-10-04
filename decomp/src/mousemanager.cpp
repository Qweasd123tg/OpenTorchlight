#include "EmptyStrings.h"
#include "MouseManager.h"
#include <cstring>

CMouseManager::CMouseManager() : CRunicCore(), m_iWheelDelta(0), m_iPendingWheelDelta(0)
{
    flushAll();
}
CMouseManager::~CMouseManager() {}

void CMouseManager::mouseEvent(unsigned int event, unsigned int value)
{
    switch (event)
    {
    case 0x201:
        if (!m_PendingHeld[0]) m_PendingPressed[0] = 1;
        m_PendingHeld[0] = 1;
        break;
    case 0x202: m_PendingHeld[0] = 0; break;
    case 0x203: m_PendingDoubleClick[0] = 1; break;
    case 0x204:
        if (!m_PendingHeld[1]) m_PendingPressed[1] = 1;
        m_PendingHeld[1] = 1;
        break;
    case 0x205: m_PendingHeld[1] = 0; break;
    case 0x206: m_PendingDoubleClick[1] = 1; break;
    case 0x207:
        if (!m_PendingHeld[2]) m_PendingPressed[2] = 1;
        m_PendingHeld[2] = 1;
        break;
    case 0x208: m_PendingHeld[2] = 0; break;
    case 0x20a: m_iPendingWheelDelta += static_cast<int>(value) >> 16; break;
    }
}

bool CMouseManager::buttonPressed(EMouseButton button) { return m_Pressed[button] == 1; }
bool CMouseManager::buttonHeld(EMouseButton button) { return m_Held[button] == 1 || m_Pressed[button] == 1; }
bool CMouseManager::buttonDoubleClick(EMouseButton button) { return m_DoubleClick[button] == 1; }

POINT* CMouseManager::virtualMousePosition(float width, float height, float virtualWidth, float virtualHeight)
{
    m_VirtualPosition.x = static_cast<int>(static_cast<float>(m_Position.x) * (virtualWidth / width));
    m_VirtualPosition.y = static_cast<int>(static_cast<float>(m_Position.y) * (virtualHeight / height));
    return &m_VirtualPosition;
}

void CMouseManager::capture()
{
    std::memcpy(m_Held,m_PendingHeld,3);
    std::memcpy(m_Pressed,m_PendingPressed,3);
    std::memcpy(m_DoubleClick,m_PendingDoubleClick,3);
    std::memset(m_PendingPressed,0,3);
    std::memset(m_PendingDoubleClick,0,3);
    m_iWheelDelta = m_iPendingWheelDelta;
    m_iPendingWheelDelta = 0;
}

void CMouseManager::flushAll()
{
    m_iPendingWheelDelta = 0;
    std::memset(m_PendingHeld,0,3);
    std::memset(m_PendingPressed,0,3);
    std::memset(m_PendingDoubleClick,0,3);
}

void CMouseManager::flush()
{
    m_iPendingWheelDelta = 0;
    std::memset(m_PendingPressed,0,3);
    std::memset(m_PendingDoubleClick,0,3);
}

void CMouseManager::update(void*) { GetCursorPos(&m_Position); }
