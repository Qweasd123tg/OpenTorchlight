#include "EmptyStrings.h"
#include "CameraShakeDescriptor.h"

CCameraShakeDescriptor::CCameraShakeDescriptor()
    : CBaseObjectDescriptor(L"Camera Shake", L"Does a camera shake", L"shake")
{
    AddInputLogic(INPUT_EVENT_ACTIVATE);
    AddProperty(L"PROPERTIES", L"DIRECTION", L"Direction of the shake.", (void*)Set_setDirection, (void*)Get_getDirection, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"PROPERTIES", L"DURATION", L"Duration of the camera shake.", (void*)Set_setDuration, (void*)Get_getDuration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"MAGNITUDE", L"A magnitude mult to the camera shake.", (void*)Set_setMagnitudeMult, (void*)Get_getMagnitudeMult, VARIABLE_TYPE_FLOAT, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"ORIENTATION TYPE", L"The type of orientation to use for the camera shake.", (void*)Set_setDirectionOrientation, (void*)Get_getDirectionOrientation, getCameraShakeOrientationByString, getCameraShakeOrientationStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"CAMERA SHAKE NAME", L"The name of the camera shake.", (void*)Set_setCameraShakeName, (void*)Get_getCameraShakeName, getCameraShakeNameByString, getCameraShakeNameStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddProperty(L"PROPERTIES", L"FADES", L"Fades with distancce.", (void*)Set_setCameraFallsOffWithDistance, (void*)Get_getCameraFallsOffWithDistance, VARIABLE_TYPE_BOOL, 0);
}

CCameraShakeDescriptor::~CCameraShakeDescriptor()
{
}
