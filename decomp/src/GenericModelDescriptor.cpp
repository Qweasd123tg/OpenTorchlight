#include "EmptyStrings.h"
#include "GenericModelDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "GenericModel.h"
#include "StringUtilities.h"

CGenericModelDescriptor::CGenericModelDescriptor()
    : CPositionableObjectDescriptor(L"Generic Model", L"A simple generic model", L"model", true, true, true, true, true)
{
    AddProperty(L"RESOURCES", L"FILE", L" File containing the model", (void*)Set_loadModel, (void*)Get_getModelPath, VARIABLE_TYPE_STRING, 4096);
    AddProperty(L"MUTATORS", L"SCALE X", L"Sets the scale of the model", (void*)Set_setScaleX, (void*)Get_getScaleX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"MUTATORS", L"SCALE Y", L"Sets the scale of the model", (void*)Set_setScaleY, (void*)Get_getScaleY, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"MUTATORS", L"SCALE Z", L"Sets the scale of the model", (void*)Set_setScaleZ, (void*)Get_getScaleZ, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"ANIMATION", L"SPEED", L"Speed of animation", (void*)Set_setAnimationSpeed, (void*)Get_getAnimationSpeed, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"ANIMATION", L"LOOPS", L"Animation will loop", (void*)Set_setAnimationLoop, (void*)Get_getAnimationLoop, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"ANIMATION", L"ANIMATION", L"The animation you want to play.", (void*)Set_setAnimationPlaying, (void*)Get_getAnimationPlaying, GetAnimationIDByString, GetAnimationStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"RENDERING", L"LIGHT MAP", L"Will render the model to the light map", (void*)Set_setRenderToLightMap, (void*)Get_getRenderToLightMap, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TEXTURE", L"TEXTURE OVERRIDE", L"The desired texture override", (void*)Set_setTextureOverride, (void*)Get_getTextureOverridePath, VARIABLE_TYPE_STRING, 8192);
    AddProperty(L"INFO", L"POLY COUNT", L"The ploy count for the loaded mesh (read only)", (void*)Set_setPolyCount, (void*)Get_getPolyCount, VARIABLE_TYPE_INTEGER, 1);
}

CGenericModelDescriptor::~CGenericModelDescriptor()
{
}

void CGenericModelDescriptor::update(float param_1)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        if (m_Objects[i] != NULL) {
            CGenericModel *pModel = dynamic_cast<CGenericModel *>(m_Objects[i]);
            if (pModel != NULL) {
                pModel->updateAnimation(param_1, false);
            }
        }
    }
}

unsigned int CGenericModelDescriptor::GetAnimationIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    std::string converted = STRINGS::StringConvertToNarrow(value.c_str());

    CGenericModel* model = dynamic_cast<CGenericModel*>(object);
    if (model == NULL)
        return 0;

    void* data = *reinterpret_cast<void**>(
        reinterpret_cast<unsigned char*>(model) + 0x1e0);
    if (data == NULL)
        return 0;

    std::vector<std::string>* animations =
        reinterpret_cast<std::vector<std::string>*>(
            reinterpret_cast<unsigned char*>(data) + 0x28);

    for (unsigned int i = 0; i < animations->size(); ++i) {
        if ((*animations)[i] == converted)
            return i;
    }

    return 0;
}
