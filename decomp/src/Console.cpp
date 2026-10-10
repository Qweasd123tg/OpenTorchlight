#include "EmptyStrings.h"
#include "Console.h"
#include "StringUtilities.h"
#include "CEGUIWindowManager.h"


bool CConsole::getVisible()
{
    return m_window ? m_window->isVisible(false) : false;
}

bool CConsole::handleClose(const CEGUI::EventArgs&)
{
    setVisible(false);
    return true;
}

std::wstring CConsole::getHistoryText()
{
    std::wstring text = EMPTY_WSTRING;
    if (m_historyWindow)
        text = STRINGS::StringConvertToWide(m_historyWindow->getText().c_str(), 5000);
    return text;
}

CConsole::~CConsole()
{
    CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
    m_window = NULL;
    m_inputWindow = NULL;
}

template TArrayList<std::wstring>::~TArrayList();

void CConsole::keyEvent(unsigned int, unsigned int, long)
{
}
