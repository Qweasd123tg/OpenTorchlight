#ifndef WAYPOINTACTIVATOR_H
#define WAYPOINTACTIVATOR_H

#include <string>

#include "PositionableObject.h"
#include "ResourceManager.h"

class CWaypointActivator : public CPositionableObject
{
public:
    virtual ~CWaypointActivator();

    void createEntity();
    CWaypointActivator(CResourceManager* pResourceManager);
    void activate();

    std::wstring m_emptyWString;
    CResourceManager* m_pResourceManager;
};

#endif
