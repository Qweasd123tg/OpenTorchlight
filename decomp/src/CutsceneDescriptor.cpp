#include "EmptyStrings.h"
#include "SkipCutsceneDescriptor.h"

CSkipCutsceneDescriptor::CSkipCutsceneDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the counter enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"DISABLE SKILLS", L"If true skills can't execute when skipping a cutscene.", (void*)Set_setSkillsDisabled, (void*)Get_getSkillsDisabled, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_SKIP_CUTSCENE);
}

CSkipCutsceneDescriptor::~CSkipCutsceneDescriptor()
{
}
