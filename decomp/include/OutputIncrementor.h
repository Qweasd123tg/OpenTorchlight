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
};

#endif
