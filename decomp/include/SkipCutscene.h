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
};

#endif
