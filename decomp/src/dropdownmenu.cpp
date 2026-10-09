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
