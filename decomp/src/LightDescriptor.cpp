#include "FileSystem.h"
#include "EmptyStrings.h"
#include "LightDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Light.h"
#include "LightDescriptorNames.h"

CLightDescriptor::CLightDescriptor()
    : CPositionableObjectDescriptor(L"Light", L"A light for the level", L"LIGHT", true, false, false, false, true)
{
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"FILE", L"The file to use.", (void*)Set_setBitmapFile, (void*)Get_getBitmapFile, GetFileIDByString, GetFileStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddProperty(L"BRIGHTNESS", L"BRIGHTNESS", L"Makes the light bright or not", (void*)Set_setLightDensity, (void*)Get_getLightDensity, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"SCALE", L"SCALE X", L"Scale of the light in the X direction", (void*)Set_setScaleX, (void*)Get_getScaleX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SCALE", L"SCALE Z", L"Scale of the light in the Z direction", (void*)Set_setScaleZ, (void*)Get_getScaleZ, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"ROTATION ANGLE", L"ANGLE", L"The angle to rotate the light by", (void*)Set_setRotation, (void*)Get_getRotation, VARIABLE_TYPE_FLOAT, 0);
}

CLightDescriptor::~CLightDescriptor()
{
}

unsigned int CLightDescriptor::GetFileIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return 0;
}

void CLightDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CLight* light = dynamic_cast<CLight*>(m_Objects[i]);
        if (light != NULL) {
            light->updateLightDensity(true);
        }
    }
}

CEditorBaseObject* CLightDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLight(scene->getResourceManager());
}

std::wstring CLightDescriptor::GetLightStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 2)
        return gLIGHT_RENDER_NAMES[0];
    return gLIGHT_RENDER_NAMES[index];
}

int CLightDescriptor::GetLightIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    for (int index = 0; index < 3; ++index) {
        if (value == gLIGHT_RENDER_NAMES[index])
            return index;
    }
    return 0;
}

std::wstring CLightDescriptor::GetFileStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    if (g_FileList.size() == 0)
        CFileSystem::getSingleton()->getFileList(L"media/lights/", g_FileList, L"*.mesh", true, true, false, false);
    if (index < g_FileList.size())
        return g_FileList[index];
    return EMPTY_WSTRING;
}
