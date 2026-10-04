#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "LinuxUtils.h"
#include "RunicCore.h"

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
