#ifndef SKIPCUTSCENE_H
#define SKIPCUTSCENE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CSkipCutscene : public CEditorBaseObject
{
public:
    virtual ~CSkipCutscene();
    void setEnabled(bool);
    CSkipCutscene(CResourceManager*);
    float update(float);

    // fields
    bool m_bEnabled;
    bool m_bUnknown59;
    bool m_bSkillsDisabled;
    unsigned char m_gap5B[0x5];
    CResourceManager* m_pResourceManager;
};

#endif
