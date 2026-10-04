#ifndef LOGIC_TRIGGER_H
#define LOGIC_TRIGGER_H

#include "PositionableObject.h"
class CEditorScene;

class CLogicTrigger : public CPositionableObject
{
public:
    CLogicTrigger(CResourceManager* resourceManager);
    virtual ~CLogicTrigger();
    virtual void setEnabled(bool enabled) { m_bTriggerEnabled = enabled; }
    virtual bool getEnabled() { return m_bTriggerEnabled; }
    virtual void TriggerReset();
    virtual void updateTrigger(float elapsed, CEditorScene* scene) = 0;
    void TriggerActivated(CEditorBaseObject* object);
    void TriggerDeactivated(CEditorBaseObject* object);
    bool canUpdate();

private:
    bool m_bActive;
    bool m_bHasActivated;
    bool m_bHasDeactivated;
    bool m_bTriggerEnabled;
};
#endif
