#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include "RunicCore.h"
#include "LinuxUtils.h"

enum EMouseButton { MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_MIDDLE = 2 };

class CMouseManager : public CRunicCore
{
public:
    CMouseManager();
    virtual ~CMouseManager();
    void mouseEvent(unsigned int event, unsigned int value);
    bool buttonPressed(EMouseButton button);
    bool buttonHeld(EMouseButton button);
    bool buttonDoubleClick(EMouseButton button);
    POINT* virtualMousePosition(float width, float height, float virtualWidth, float virtualHeight);
    void capture();
    void flushAll();
    void flush();
    void update(void* window);
private:
    unsigned char m_Pressed[3];
    unsigned char m_Held[3];
    unsigned char m_DoubleClick[3];
    unsigned char m_PendingPressed[3];
    unsigned char m_PendingHeld[3];
    unsigned char m_PendingDoubleClick[3];
    POINT m_Position;
    POINT m_VirtualPosition;
    int m_iWheelDelta;
    int m_iPendingWheelDelta;
};

#endif
