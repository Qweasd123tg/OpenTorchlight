#ifndef CONSOLE_H
#define CONSOLE_H

#include <CEGUIWindow.h>
#include <string>
#include "RunicCore.h"

// The RTTI base and two destructor vtable slots are present in the original.
// Unrecovered regions remain opaque; container/window types below are named
// by calls in CConsole's original functions.
class CGameUI; class CResourceManager;
class CConsole : public CRunicCore
{
public:
    void keyEvent(unsigned int event, unsigned int key, long text);

    CConsole(CGameUI*, CResourceManager*, CEGUI::Window*);

    virtual ~CConsole();
    bool getVisible();
    void setVisible(bool);
    bool handleClose(const CEGUI::EventArgs&);
    std::wstring getHistoryText();

    unsigned char m_unknown10[8];
    CEGUI::Window* m_window;
    CEGUI::Window* m_inputWindow;
    CEGUI::Window* m_historyWindow;
    unsigned char m_unknown30[8];
    TArrayList<std::wstring> m_history;
    unsigned char m_unknown50[32];
};

#endif
