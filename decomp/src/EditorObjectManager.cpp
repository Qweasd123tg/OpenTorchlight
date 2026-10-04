#include "EmptyStrings.h"
#include "GameVariables.h"
#include "EditorObjectManager.h"



CEditorObjectManager::~CEditorObjectManager()
{
    if (m_pObjectControl != NULL)
    {
        delete m_pObjectControl;
        m_pObjectControl = NULL;
    }
}
