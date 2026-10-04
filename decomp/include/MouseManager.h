#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include "LinuxUtils.h"
#include "RunicCore.h"

enum EMouseButton
{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_COUNT
};

// Collects window mouse messages (WM_* codes) between frames; capture()
// publishes them as the state of the current frame.
class CMouseManager : public CRunicCore
{
public:
    CMouseManager();
    virtual ~CMouseManager();

    void mouseEvent(unsigned int message, unsigned int wParam);
    bool buttonPressed(EMouseButton button);
    bool buttonHeld(EMouseButton button);
    bool buttonDoubleClick(EMouseButton button);
    POINT* virtualMousePosition(float screenWidth, float screenHeight, float virtualWidth, float virtualHeight);
    void capture();
    void flushAll();
    void flush();
    void update(void* window);

private:
    unsigned char m_bPressed[MOUSE_BUTTON_COUNT];
    unsigned char m_bHeld[MOUSE_BUTTON_COUNT];
    unsigned char m_bDoubleClick[MOUSE_BUTTON_COUNT];
    unsigned char m_bPendingPressed[MOUSE_BUTTON_COUNT];
    unsigned char m_bDown[MOUSE_BUTTON_COUNT];
    unsigned char m_bPendingDoubleClick[MOUSE_BUTTON_COUNT];
    POINT m_Position;
    POINT m_VirtualPosition;
    int m_iWheel;
    int m_iPendingWheel;
};

#endif
