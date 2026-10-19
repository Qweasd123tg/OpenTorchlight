#ifndef TRIGGERUNIT_H
#define TRIGGERUNIT_H

#include "Item.h"
#include "TArrayList.h"

class CLayout;
class CGenericModel;
class CCollisionModel;

enum ETRIGGER_STATES
{
    TRIGGER_STATE_ZERO = 0,
    TRIGGER_STATE_ONE = 1
};

// Field order and owning arrays follow the native C1/D1 and unitInit accesses.
class CTriggerUnit : public CItem
{
public:
    CTriggerUnit(CResourceManager*);
    virtual ~CTriggerUnit();
    virtual void setActiveInLevel(bool);
    virtual void* getUnitModel();
    virtual void* getUnitCollisionModel();
    virtual void unitInit(CDataGroup*, bool);
    virtual void update(Ogre::Camera*, const Ogre::Vector3&, float);
    virtual bool interact(CCharacter*);
    virtual void fillSaveState(CItemSaveState&, int, bool);
    virtual void applySaveState(CItemSaveState&);
    virtual void setVisible(bool, bool);
    void setTriggerState(ETRIGGER_STATES, bool, bool, bool);
    void resetTrigger();
    void spawnTreasureClass(CCharacter*, const std::wstring&, unsigned int);
    bool trigger(CCharacter*);
    void addSoundsToState(ETRIGGER_STATES, const wchar_t*);
    void setUnitModelName(std::wstring);
    void addAnimations();
private:
    CGenericModel* m_unitModel;               // +0x230
    CCollisionModel* m_unitCollisionModel;    // +0x238
    CLayout* m_layout;                       // +0x240
    int m_state;                            // +0x248
    int m_minState;                          // +0x24c
    int m_maxState;                          // +0x250
    int m_cycleMode;                         // +0x254
    int m_cycleDirection;                    // +0x258
    bool m_flag25C;
    bool m_pendingStateEvent;
    std::wstring m_modelName;                // +0x260
    TArrayList<unsigned int> m_animations;   // +0x268
    TArrayList<bool> m_looping;              // +0x280
    TArrayList<unsigned int> m_altAnimations;// +0x298
    TArrayList<CLayout*> m_stateLayouts;     // +0x2b0
    CLayout* m_layout2C8;
    std::wstring m_treasureClass;            // +0x2d0
    int m_minTreasure;
    int m_maxTreasure;
    bool m_flag2E0;
    std::wstring m_requiredItem;             // +0x2e8
    int m_value2F0;
    bool m_flag2F4;
    std::wstring m_requiredQuest;            // +0x2f8
};

#endif
