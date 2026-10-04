#ifndef CINEMATICOBJECT_H
#define CINEMATICOBJECT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>
#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "iLevelUpdate.h"
#include "iMenuListener.h"

class CCinematicObject : public CEditorBaseObject, public iMenuListener, public iLevelUpdate
{
public:
    virtual ~CCinematicObject();
    virtual void menuEventOccured(void*, EMENU_TYPE, EMENU_EVENT);
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    CCinematicObject(CResourceManager*);
    void play();

    // fields
    std::wstring m_sUnknown68;
    CResourceManager* m_pResourceManager;
    int m_Unknown78;
};

#endif
