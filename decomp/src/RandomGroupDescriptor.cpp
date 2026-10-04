#include "EmptyStrings.h"
#include "RandomGroupDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "RandomGroup.h"
#include "UnitResourceList.h"
#include "TArrayList.h"

CRandomGroupDescriptor::CRandomGroupDescriptor()
    : CPositionableObjectDescriptor(L"Group", L"Group for organizing random selections for levels", L"folder", true, false, false, false, false)
{
    AddProperty(L"PROPERTIES", L"VISIBLE", L"The group will set all the children visible or not.", (void*)Set_setVisible, (void*)Get_getVisible, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"DYNAMIC", L"if the group is dynamic it will position children as well as set them visible..", (void*)Set_setIsDynamicGroup, (void*)Get_getIsDynamicGroup, VARIABLE_TYPE_BOOL, 0);
    m_iFlags |= 0x1020;
    AddOutputLogic(OUTPUT_EVENT_ON_VISIBLE);
    AddOutputLogic(OUTPUT_EVENT_ON_INVISIBLE);
    AddInputLogic(INPUT_EVENT_SHOW);
    AddInputLogic(INPUT_EVENT_HIDE);
    AddProperty(L"WEIGHT OR RAND AS CHILD", L"RANDOMIZATION", L"When placed into a group, and the group has the random choice of 'weight' selected it'll use this value as the weight of the object for it's random choice.", (void*)Set_SetRandomWeight, (void*)Get_GetRandomWeight, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"CHILD RANDOMIZATION", L"NUMBER", L"Put the number of objects you want to pick when doing a random chance or by weight. NOTE it won't pick an item twice.", (void*)Set_SetNumberOfPicks, (void*)Get_GetNumberOfPicks, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddPropertyWithInterpreterFunctions(L"CHILD RANDOMIZATION", L"CHOICE", L"When adding children this will choose what type of choices this group will make when loading the level.", (void*)Set_SetRandomType, (void*)Get_GetRandomType, GetRandomGroupTypeIDByString, GetRandomGroupTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"DIFFICULTY MODE", L"If the difficulty mode is set, this group and it's children will only appear in that mode.", (void*)Set_setDifficulty, (void*)Get_getDifficulty, getDifficultyIDByString, setDifficultyStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"DUNGEON", L"This group and it's children will not appear unless it's in this dungeon.", (void*)Set_setDungeonForGroup, (void*)Get_getDungeonForGroup, getDungeonIDByString, getDungeonStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"CLASS", L"Specifying a class will almost make this group show.", (void*)Set_setPlayerClassName, (void*)Get_getPlayerClassName, getPlayerClassIDByString, getPlayerClassStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"ACTIVE OR COMPLETE", L"Group will only show if quest is active or complete.", (void*)Set_setQuestHasToBeActiveOrComplete, (void*)Get_getQuestHasToBeActiveOrComplete, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"COMPLETE", L"Group will only show if quest is complete.", (void*)Set_setQuestHasToBeComplete, (void*)Get_getQuestHasToBeComplete, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"NOT COMPLETE", L"Group will show if quest is NOT complete.", (void*)Set_setQuestNotComplete, (void*)Get_getQuestNotComplete, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"ACTIVE", L"Group will only show if quest is active.", (void*)Set_setQuestHasToBeActive, (void*)Get_getQuestHasToBeActive, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"NOT ACTIVE OR COMPLETE", L"Group will only show if quest is NOT active or complete.", (void*)Set_setQuestCannotBeActiveOrComplete, (void*)Get_getQuestCannotBeActiveOrComplete, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
}

CRandomGroupDescriptor::~CRandomGroupDescriptor()
{
}

unsigned int CRandomGroupDescriptor::getDungeonIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return 0;
}

std::wstring CRandomGroupDescriptor::setDifficultyStringByID(
    CEditorScene* scene,
    CEditorBaseObject* object,
    unsigned int index,
    void* userData)
{
    switch (index)
    {
    case 0:
        return L"EASY";
    case 1:
        return L"NORMAL";
    case 2:
        return L"HARD";
    case 3:
        return L"VERY HARD";
    default:
        return EMPTY_WSTRING;
    }
}

std::wstring CRandomGroupDescriptor::getPlayerClassStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    if (index != 0) {
        unsigned int position = index - 1;
        TArrayList<std::wstring>* playerClassNames =
            reinterpret_cast<TArrayList<std::wstring>*>(
                CUnitResourceList::getSingleton()->getPlayerClassNames());

        if (position >= playerClassNames->size())
            return EMPTY_WSTRING;

        return (*playerClassNames)[position];
    }

    return EMPTY_WSTRING;
}

void CRandomGroupDescriptor::InputLogicEvent(CEditorBaseObject* object,
                                                unsigned int event,
                                                CEditorBaseObject* param)
{
    CRandomGroup* randomGroup = dynamic_cast<CRandomGroup*>(object);
    if (randomGroup != 0) {
        if (event == 0) {
            randomGroup->setVisible(true);
        } else if (event == 1) {
            randomGroup->setVisible(false);
        }
    }
}

void CRandomGroupDescriptor::descriptorSceneLoaded(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        if (m_Objects[i] != NULL) {
            CRandomGroup* randomGroup =
                dynamic_cast<CRandomGroup*>(m_Objects[i]);

            if (randomGroup != NULL &&
                !scene->getResourceManager()->getEditorIsRunning() &&
                randomGroup->m_bIsDynamicGroup) {
                randomGroup->calculateChildren();
            }
        }
    }
}

CEditorBaseObject* CRandomGroupDescriptor::CreateObject(CEditorScene* scene)
{
    return new CRandomGroup(scene->getResourceManager());
}

unsigned int CRandomGroupDescriptor::GetRandomGroupTypeIDByString(
    CEditorScene*,
    CEditorBaseObject*,
    const std::wstring& value,
    void*)
{
    const std::wstring* names =
        reinterpret_cast<const std::wstring*>(gRANDOMGROUP_NAMES);

    for (unsigned int i = 0; i < 3; ++i)
    {
        if (value == names[i])
            return i;
    }

    return 0;
}
