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

public:
    // Inline accessors behind the descriptors' property functions.
    void setLoopForever(bool value) { m_bRepeatForever = value; }
    bool getLoopForever() const { return m_bRepeatForever; }
    int getLoopCount() const { return m_iRepeatCount; }
    float getMaxTimer() const { return m_fMaxTime; }
    float getTimer() const { return m_fMinTime; }
    bool getEnabled() const { return m_bEnabled; }
};

#endif
