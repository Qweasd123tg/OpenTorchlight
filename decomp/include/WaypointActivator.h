#ifndef WAYPOINTACTIVATOR_H
#define WAYPOINTACTIVATOR_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "PositionableObject.h"
#include "ResourceManager.h"

class CWaypointActivator : public CPositionableObject
{
public:
    virtual ~CWaypointActivator();
    void createEntity();
    CWaypointActivator(CResourceManager*);
    void activate();

    // fields
    void* m_pUnknown100;
    CResourceManager* m_pResourceManager;
};

#endif
