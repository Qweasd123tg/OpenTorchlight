#ifndef LOGICTIMER_H
#define LOGICTIMER_H

#include "EditorBaseObject.h"
#include "OutputEvents.h"
#include "ResourceManager.h"

// Logic object that fires OUTPUT_EVENT_ACTIVATED after a (random) delay,
// a set number of times or forever.
class CLogicTimer : public CEditorBaseObject
{
public:
    CLogicTimer(CResourceManager* resourceManager);
    virtual ~CLogicTimer();

    void setEnabled(bool enabled);
    void update(float elapsed);
    void resetTimer();

private:
    float m_fMinTime;
    float m_fMaxTime;
    float m_fTimeRemaining;
    int m_iRepeatCount;
    int m_iRepeatsLeft;
    bool m_bEnabled;
    bool m_bRepeatForever;
    CResourceManager* m_pResourceManager;
};

#endif
