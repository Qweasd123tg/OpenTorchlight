#include "EmptyStrings.h"
#include "AnimationPlayerDescriptor.h"

CAnimationPlayerDescriptor::CAnimationPlayerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, false, false, false, false, false)
{
    AddProperty(L"PROPERTIES", L"START ON LOAD", L"If true the animation starts on load.", (void*)Set_setStartOnLoad, (void*)Get_getStartOnLoad, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"BLEND TIME", L"The time which the animation will blend.", (void*)Set_setBlendTime, (void*)Get_getBlendTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"BLEND OUT TIME", L"The time which the animation will blend out.", (void*)Set_setBlendOutTime, (void*)Get_getBlendOutTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"DURATION OVERRIDE", L"Forces the animation to play this long.", (void*)Set_setForceDuration, (void*)Get_getForceDuration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"PLAY IDLE", L"When the animation stops it'll blend into an idle.", (void*)Set_setPlayIdle, (void*)Get_getPlayIdle, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"ANIMATION", L"ANIMATION", L"The name of the animation you want the unit to play.", (void*)Set_setAnimationName, (void*)Get_getAnimationName, VARIABLE_TYPE_STRING, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"UNIT", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"UNIT", L"UNIT", L"The unit to make path.", (void*)Set_setUnitString, (void*)Get_getUnitString, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddInputLogic(INPUT_EVENT_PLAY_3);
    AddInputLogic(INPUT_EVENT_PLAY_LOOPING);
    AddInputLogic(INPUT_EVENT_STOP_3);
    AddInputLogic(INPUT_EVENT_STOP_AND_IDLE);
    AddOutputLogic(OUTPUT_EVENT_ANIMATION_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_ANIMATION_PLAYING);
}

CAnimationPlayerDescriptor::~CAnimationPlayerDescriptor()
{
}
