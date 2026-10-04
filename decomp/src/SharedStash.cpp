#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SharedStash.h"
#include "Inventory.h"
#include "RunicCore.h"

CSharedStash* CSharedStash::getSingleton()
{
    return (CSharedStash*)g_pSharedStash;
}

CSharedStash::CSharedStash(const wchar_t* stashFileName,
                           const wchar_t* alternateStashFileName)
    : CRunicCore(),
      m_pInventory(NULL),
      m_stashFileName(stashFileName),
      m_alternateStashFileName(alternateStashFileName),
      m_bUseAlternateStash(false)
{
    if (g_pSharedStash == NULL)
    {
        m_pInventory = new CInventory(NULL, 42);
        g_pSharedStash = this;
    }
}

CSharedStash::~CSharedStash()
{
    g_pSharedStash = NULL;

    if (m_pInventory != NULL)
    {
        delete m_pInventory;
        m_pInventory = NULL;
    }
}
