#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "RunicCore.h"
#include "LinuxUtils.h"

class CMouseHandler : public CRunicCore
{
public:
    CMouseHandler(void* window);
    virtual ~CMouseHandler();
    POINT MousePosition();
    bool MouseIsInWindow();
    bool MouseCenterButtonDown();
    bool MouseRightButtonDown();
    bool MouseLeftButtonDown();
private:
    void* m_pWindow;
};

#endif
