#include "DropdownMenu.h"
#include "iMenuListener.h"


CDropdownMenu::~CDropdownMenu()
{
    if (m_pGenericModel)
    {
        delete m_pGenericModel;
        m_pGenericModel = NULL;
    }
    if (m_pSoundBank)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    m_menuListeners.clear();
    m_pendingMenuListeners.clear();
}

template TArrayList<iMenuListener*>::~TArrayList();

bool CDropdownMenu::processInput(void*, float, bool capture)
{
    if (capture && m_bUnknown32) {
        setOpen(false);
        m_bUnknown32 = false;
        return false;
    }
    return true;
}
