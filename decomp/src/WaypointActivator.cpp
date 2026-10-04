#include "EmptyStrings.h"
#include "WaypointActivator.h"
#include "PositionableObject.h"
#include "ResourceManager.h"

void CWaypointActivator::createEntity()
{
}

CWaypointActivator::CWaypointActivator(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_emptyWString(EMPTY_WSTRING),
      m_pResourceManager(resourceManager)
{
}

CWaypointActivator::~CWaypointActivator()
{
}
