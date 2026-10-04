#ifndef SKIPCUTSCENE_H
#define SKIPCUTSCENE_H

#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CSkipCutscene : public CEditorBaseObject
{
public:
    virtual ~CSkipCutscene();

    void setEnabled(bool bEnabled);
    CSkipCutscene(CResourceManager* pResourceManager);
    float update(float fDeltaTime);

    bool m_bEnabled;
    bool m_bSkipRequested;
    bool m_bSkillsDisabled;
    unsigned char m_abPadding[5];
    CResourceManager* m_pResourceManager;

public:
    // Inline accessors behind the descriptors' property functions.
    void setSkillsDisabled(bool value) { m_bSkillsDisabled = value; }
    bool getSkillsDisabled() const { return m_bSkillsDisabled; }
    bool getEnabled() const { return m_bEnabled; }
};

#endif
