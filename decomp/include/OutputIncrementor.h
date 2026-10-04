#ifndef OUTPUTINCREMENTOR_H
#define OUTPUTINCREMENTOR_H

#include "EditorBaseObject.h"
#include "OutputEvents.h"
#include "ResourceManager.h"

// Logic object counting its inputs: fires an event per increment and the
// numbered increment events, and resets after reaching its target count.
class COutputIncrementor : public CEditorBaseObject
{
public:
    COutputIncrementor(CResourceManager* resourceManager);
    virtual ~COutputIncrementor();

    void setEnabled(bool enabled);
    void increment();

private:
    unsigned int m_iTarget;
    unsigned int m_iCount;
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
    unsigned int getMaxIncrement() const { return m_iTarget; }
    bool getEnabled() const { return m_bEnabled; }
};

#endif
