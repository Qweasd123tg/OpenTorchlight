#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>
#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "iLevelUpdate.h"
#include "iMenuListener.h"

class CQuestController : public CEditorBaseObject, public iMenuListener, public iLevelUpdate
{
public:
    virtual ~CQuestController();
    virtual void menuEventOccured(void*, EMENU_TYPE, EMENU_EVENT);
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    void questHasBeenAccepted(bool);
    void questHasBeenAbandoned();
    void questHasBeenCompleted(bool);
    void setQuestComplete(bool);
    void setQuestAccepted(bool);
    void interactWithUnit();
    void initQuestController();
    void setUnitInteractWith(std::wstring);
    CQuestController(CResourceManager*);

    // fields
    CResourceManager* m_pResourceManager;
    long long m_iUnknown70;
    CRunicCore* m_pRunicCore;
    int m_iUnknown80;
    unsigned char m_gap84[0x4] __attribute__((aligned(4)));
    void* m_pCategory;
    std::wstring m_sUnitInteractWith;
    CRunicCore* m_pRunicCore_98;
    int m_iUnknownA0;
    unsigned char m_gapA4[0x4] __attribute__((aligned(4)));
    void* m_pQuest;
    bool m_bUnknownB0;
    bool m_bBroadcastEventsOnLoad;
    bool m_bUnknownB2;
    bool m_bPlayerGetsDisabled;
    int m_UnknownB4;
};

#endif
