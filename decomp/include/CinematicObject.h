#ifndef CINEMATICOBJECT_H
#define CINEMATICOBJECT_H

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>

#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "iLevelUpdate.h"
#include "iMenuListener.h"

class CCinematicObject : public CEditorBaseObject,
                        public iMenuListener,
                        public iLevelUpdate
{
public:
    virtual ~CCinematicObject();

    virtual void menuEventOccured(void* pTarget,
                                  EMENU_TYPE eMenuType,
                                  EMENU_EVENT eMenuEvent);

    virtual long long updateLevelObject(float fTime,
                                         Ogre::Camera* pCamera,
                                         const Ogre::Vector3& vPosition);

    CCinematicObject(CResourceManager* pResourceManager);

    void play();

    std::wstring m_sCinematicName;
    CResourceManager* m_pResourceManager;
    EMENU_EVENT m_eMenuEvent;
};

#endif
