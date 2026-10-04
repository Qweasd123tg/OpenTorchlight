#include "EmptyStrings.h"
#include "CameraControllerDescriptor.h"
#include "GameVariables.h"
#include "CameraController.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "StringUtilities.h"

CCameraControllerDescriptor::CCameraControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, false)
{
    AddProperty(L"CAMERA CONTROL", L"PAN TIME", L"The amount of time the camera takes to pan to target.", (void*)Set_setCameraPanTime, (void*)Get_getCameraPanTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"CAMERA CONTROL", L"EASE IN DISTANCE PCT", L"The percent of distance before the the ease in kicks on. Use a number between 0-1", (void*)Set_setCameraEaseInDistancePCT, (void*)Get_getCameraEaseInDistancePCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"CAMERA CONTROL", L"EASE IN PCT", L"When the ease in distance is reached it will use a given pct of the final distance. Use a number between 0-1", (void*)Set_setCameraEaseInPCT, (void*)Get_getCameraEaseInPCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PAUSE TIMER", L"TIME", L"The amount of time to pause at the end of the camera. NOTE the camera stop event won't fire till timer is done.", (void*)Set_setCameraPauseTimer, (void*)Get_getCameraPauseTimer, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"RESETS AT END", L"If true the camera will give control back to the player at the end of it's movement and pausing.", (void*)Set_setRestoreCameraStateAfterMoving, (void*)Get_getRestoreCameraStateAfterMoving, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"FOLLOW UNIT", L"If true after the camera pans and pauses it will begin to follow the unit till it is told to stop", (void*)Set_setFollowUnit, (void*)Get_getFollowUnit, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"TYPE", L"The type of camera. if unit it will pan over to a unit. If it's a position it'll pan over to the position of the camera controller", (void*)Set_setCameraType, (void*)Get_getCameraType, getTypeIDByString, getTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"UNIT", L"The unit to interact with.", (void*)Set_setUnitInteractWith, (void*)Get_getUnitInteractWith, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddInputLogic(INPUT_EVENT_START_CAMERA);
    AddInputLogic(INPUT_EVENT_CAMERA_OFF);
    AddOutputLogic(OUTPUT_EVENT_CAMERA_MOVING);
    AddOutputLogic(OUTPUT_EVENT_CAMERA_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_CAMERA_PAUSING);
    AddOutputLogic(OUTPUT_EVENT_CAMERA_CONTROL_RESTORED);
}

CCameraControllerDescriptor::~CCameraControllerDescriptor()
{
}

unsigned int CCameraControllerDescriptor::GetResourceIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*)
{
    return 0;
}

std::wstring CCameraControllerDescriptor::GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData)
{
    if (index == 0)
        return L"MONSTERS";

    return L"ITEMS";
}

unsigned int CCameraControllerDescriptor::getTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return STRINGS::getStringIndex(value, reinterpret_cast<const std::wstring*>(&gCAMERA_TYPE_NAMES), 2, 0, false);
}

unsigned int CCameraControllerDescriptor::GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >& value, void* userData)
{
    return value == L"ITEMS";
}

void CCameraControllerDescriptor::update(float param_1)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CCameraController* controller =
            dynamic_cast<CCameraController*>(m_Objects[i]);

        if (controller != 0)
            controller->update(param_1);
    }
}

void CCameraControllerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int eventType, CEditorBaseObject* source)
{
    if (object != NULL) {
        CCameraController* controller = dynamic_cast<CCameraController*>(object);

        if (controller != NULL) {
            if (eventType == 0x33) {
                controller->startCamera();
                controller->update(0.0f);
                return;
            }

            if (eventType == 0x34) {
                controller->stopCamera();
                return;
            }
        }
    }
}

CEditorBaseObject* CCameraControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CCameraController(scene->getResourceManager());
}
