#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>

#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "iLevelUpdate.h"
#include "iMenuListener.h"

class CResourceManager;
class CDataGroup;
class CBaseUnit;
class CQuest;

class CQuestController : public CEditorBaseObject,
                         public iMenuListener,
                         public iLevelUpdate
{
public:
    virtual ~CQuestController();

    virtual void menuEventOccured(void* pData,
                                  EMENU_TYPE menuType,
                                  EMENU_EVENT menuEvent);
    virtual long long updateLevelObject(float fTimeDelta,
                                        Ogre::Camera* pCamera,
                                        const Ogre::Vector3& vPosition);

    void questHasBeenAccepted(bool bIsAccepted);
    void questHasBeenAbandoned();
    void questHasBeenCompleted(bool bIsComplete);
    void setQuestComplete(bool bIsComplete);
    void setQuestAccepted(bool bIsAccepted);

    void interactWithUnit();
    void initQuestController();
    void setUnitInteractWith(const std::wstring& sUnitInteractWith);

    CQuestController(CResourceManager* pResourceManager);

    CResourceManager* m_pResourceManager;
    CDataGroup* m_pDataGroup;
    CBaseUnit* m_pUnit;
    int m_iUnitSafePointer;

    unsigned char m_padding84[4];

    std::wstring m_sCategory;
    std::wstring m_sUnitInteractWith;

    CQuest* m_pQuest;
    int m_iQuestSafePointer;

    unsigned char m_paddingA4[4];

    std::wstring m_sQuestName;
    bool m_bFirstUpdate;
    bool m_bBroadcastEventsOnLoad;
    bool m_bPlayerEnabled;
    bool m_bPlayerGetsDisabled;
    EMENU_EVENT m_eMenuEvent;

public:
    // Inline accessors behind the descriptors' property functions.
    void setPlayerGetsDisabled(bool value) { m_bPlayerGetsDisabled = value; }
    void setBroadcastEventsOnLoad(bool value) { m_bBroadcastEventsOnLoad = value; }
    bool getBroadcastEventsOnLoad() const { return m_bBroadcastEventsOnLoad; }
    bool getPlayerGetsDisabled() const { return m_bPlayerGetsDisabled; }
    void setQuest(const std::wstring& value) { m_sQuestName = value; }
    void setCategory(const std::wstring& value) { m_sCategory = value; }
};

#endif
