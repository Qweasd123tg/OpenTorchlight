#include "EmptyStrings.h"
#include "GameNamespaces.h"
#include "SkipCutscene.h"
#include "ResourceManager.h"

void CSkipCutscene::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (enabled)
    {
        BroadcastEvent(6);
        m_bSkipRequested = false;
    }
    else
    {
        BroadcastEvent(7);
    }
}

CSkipCutscene::~CSkipCutscene()
{
}

CSkipCutscene::CSkipCutscene(CResourceManager* resourceManager)
    : m_bEnabled(false), m_bSkipRequested(false), m_bSkillsDisabled(false),
      m_pResourceManager(resourceManager)
{
}
