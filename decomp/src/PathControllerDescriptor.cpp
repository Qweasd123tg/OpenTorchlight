#include "EmptyStrings.h"
#include "PathControllerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "PathController.h"

CPathControllerDescriptor::CPathControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, false)
{
    AddProperty(L"PATHING POINTS", L"POINTS", L"The list of points for the pathing", (void*)Set_setArrayOfVectors, (void*)Get_getArrayOfVectors, VARIABLE_TYPE_FLOAT, 32768);
    AddProperty(L"PATHING POINTS", L"NUMBER OF POINTS", L"The number of points", (void*)Set_setNumberOfPathPoints, (void*)Get_getNumberOfPathPoints, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"SHOW", L"Will hide all the path nodes in the editor", (void*)Set_setVisible, (void*)Get_getVisible, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ENABLE ON START", L"Will enable the unit on start", (void*)Set_setEnableUnitOnStart, (void*)Get_getEnableUnitOnStart, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ENABLED", L"If a unit is selected to path and is enabled the unit will use this path.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"PATH NAME", L"The name of the path", (void*)Set_setPathName, (void*)Get_getPathName, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"PROPERTIES", L"RUN", L"If true the unit runs on the path", (void*)Set_setUnitRunsOnPath, (void*)Get_getUnitRunsOnPath, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"PATH TO PLAYER", L"Path's to player.", (void*)Set_setWalkToPlayer, (void*)Get_getWalkToPlayer, VARIABLE_TYPE_BOOL, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"UNIT PATHING", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"UNIT PATHING", L"UNIT", L"The unit to make path.", (void*)Set_setUnitInteractWith, (void*)Get_getUnitInteractWith, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_END_OF_PATH_REACHED);
}

CPathControllerDescriptor::~CPathControllerDescriptor()
{
}

unsigned int CPathControllerDescriptor::GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return 0;
}

std::wstring CPathControllerDescriptor::GetGroupStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    const std::wstring *names = reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES);

    if (index == 0)
        return names[1];
    if (index == 2)
        return L"PLAYER";
    return names[0];
}

void CPathControllerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    if (object != 0)
    {
        CPathController* controller = dynamic_cast<CPathController*>(object);
        if (controller != 0)
        {
            if (event == 2)
            {
                controller->setVisible(true);
                return;
            }
            if (event == 3)
            {
                controller->setVisible(false);
                return;
            }
        }
    }
}

void CPathControllerDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CPathController* controller =
            dynamic_cast<CPathController*>(m_Objects[i]);

        if (controller && !scene->getResourceManager()->getEditorIsRunning()) {
            controller->initPathController();
        }
    }
}

void CPathControllerDescriptor::DescriptorObjectCreatedInEditor(CEditorBaseObject* object)
{
    CPathController* pathController = dynamic_cast<CPathController*>(object);
    if (pathController != NULL)
    {
        pathController->initObjectInEditor();
    }
}

CEditorBaseObject* CPathControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CPathController(scene->getResourceManager());
}
