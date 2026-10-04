#include "EmptyStrings.h"
#include "SkipCutsceneDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "SkipCutscene.h"

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

void CSkipCutsceneDescriptor::update(float param_1)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        if (m_Objects[i] != NULL) {
            static_cast<CSkipCutscene *>(m_Objects[i])->update(param_1);
        }
    }
}

void CSkipCutsceneDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int eventType, CEditorBaseObject*)
{
    CSkipCutscene* skipCutscene = dynamic_cast<CSkipCutscene*>(object);

    if (skipCutscene != NULL) {
        if (eventType == 2) {
            skipCutscene->setEnabled(true);
            return;
        }

        if (eventType == 3) {
            skipCutscene->setEnabled(false);
            return;
        }
    }
}

CEditorBaseObject* CSkipCutsceneDescriptor::CreateObject(CEditorScene* scene)
{
    return new CSkipCutscene(scene->getResourceManager());
}
