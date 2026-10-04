#include "EmptyStrings.h"
#include "SkillControllerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "SkillController.h"

CSkillControllerDescriptor::CSkillControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, false)
{
    AddProperty(L"PROPERTIES", L"LEARN ON START", L"if true the unit will learn the skill on start if it doesn't already know it.", (void*)Set_setSkillLearnOnStart, (void*)Get_getSkillLearnOnStart, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"UNLEARN ON STOP", L"will make the unit unlearn the skill when the skill stops.", (void*)Set_setSkillUnlearnOnStop, (void*)Get_getSkillUnlearnOnStop, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"FORCE STOP", L"forces the skill to stop.", (void*)Set_setForceStop, (void*)Get_getForceStop, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"TARGET PLAYER", L"forces the skill to target the player.", (void*)Set_setPlayerAsTarget, (void*)Get_getPlayerAsTarget, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"USE UNIT TARGET", L"Skill will target the unit's target.", (void*)Set_setUseUnitTarget, (void*)Get_getUseUnitTarget, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"SKILL LEVEL", L"If the skill is being fired by an Item you can specify the level of the skill.", (void*)Set_setLevelOfSkill, (void*)Get_getLevelOfSkill, VARIABLE_TYPE_BOOL, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"UNIT", L"The unit to interact with.", (void*)Set_setUnitInteractWith, (void*)Get_getUnitInteractWith, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddPropertyWithInterpreterFunctions(L"SKILL", L"SKILL", L"The skill that will be referanced.", (void*)Set_setSkillName, (void*)Get_getSkillName, getSkillIDByString, getSkillStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddInputLogic(INPUT_EVENT_START_SKILL);
    AddInputLogic(INPUT_EVENT_STOP_SKILL);
    AddInputLogic(INPUT_EVENT_LEARN_SKILL);
    AddInputLogic(INPUT_EVENT_UNLEARN_SKILL);
    AddOutputLogic(OUTPUT_EVENT_SKILL_STARTED);
    AddOutputLogic(OUTPUT_EVENT_SKILL_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_SKILL_LEARNED);
    AddOutputLogic(OUTPUT_EVENT_SKILL_UNLEARNED);
}

CSkillControllerDescriptor::~CSkillControllerDescriptor()
{
}

unsigned int CSkillControllerDescriptor::GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return 0;
}

void CSkillControllerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* param)
{
    CSkillController* skill = dynamic_cast<CSkillController*>(object);
    if (skill)
    {
        switch (event)
        {
        case 0x39:
            skill->startSkill();
            break;
        case 0x3a:
            skill->stopSkill();
            break;
        case 0x3b:
            skill->learnSkill();
            break;
        case 0x3c:
            skill->unlearnSkill();
            break;
        }
    }
}

void CSkillControllerDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CSkillController* controller =
            dynamic_cast<CSkillController*>(m_Objects[i]);

        if (controller != 0 &&
            !scene->getResourceManager()->getEditorIsRunning())
        {
            controller->initSkillController();
        }
    }
}

void CSkillControllerDescriptor::update(float param_1)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CSkillController *object = (CSkillController *)m_Objects[i];

        if (object != NULL && !object->m_pResourceManager->getEditorIsRunning())
            object->update(param_1);
    }
}

CEditorBaseObject* CSkillControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CSkillController(scene->getResourceManager());
}
