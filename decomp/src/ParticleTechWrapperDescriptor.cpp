#include "EditorScene.h"
#include "ParticleTechWrapper.h"
#include "ParticleTechWrapperDescriptor.h"

void CParticleTechWrapperDescriptor::update(float value)
{
}

void CParticleTechWrapperDescriptor::descriptorSceneActivated(CEditorScene* value)
{
}

void CParticleTechWrapperDescriptor::descriptorSceneDeactivated(CEditorScene* value)
{
}

CEditorBaseObject* CParticleTechWrapperDescriptor::CreateObject(CEditorScene* scene)
{
    return new CParticleTechWrapper(scene->getResourceManager());
}

CParticleTechWrapperDescriptor::~CParticleTechWrapperDescriptor()
{
}

#include <map>
#include <string>
#include "ParticleTechWrapperDescriptorNames.h"

void CParticleTechWrapperDescriptor::DescriptorObjectHasBeenInited(CEditorBaseObject* object)
{
    static_cast<CParticleTechWrapper*>(object)->createTextureMaterial();
}

std::wstring CParticleTechWrapperDescriptor::GetParticleRenderStyleStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 3)
        return gPARTICLE_MATERIAL_TYPES[0];
    return gPARTICLE_MATERIAL_TYPES[index];
}

std::wstring CParticleTechWrapperDescriptor::GetBillboardOriginTypeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 8)
        return gPARTICLE_BILLBOARD_ORIGIN_POSITIONS[0];
    return gPARTICLE_BILLBOARD_ORIGIN_POSITIONS[index];
}

std::wstring CParticleTechWrapperDescriptor::GetBillboardRotationTypeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 1)
        return gPARTICLE_BILLBOARD_ROTATION_TYPES[0];
    return gPARTICLE_BILLBOARD_ROTATION_TYPES[index];
}

std::wstring CParticleTechWrapperDescriptor::GetParticleRenderStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 12)
        return gPARTICLE_RENDER_TYPE_NAMES[0];
    return gPARTICLE_RENDER_TYPE_NAMES[index];
}

unsigned int CParticleTechWrapperDescriptor::GetParticleRenderStyleIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 4; ++index)
    {
        if (value == gPARTICLE_MATERIAL_TYPES[index])
            return index;
    }
    return 0;
}

unsigned int CParticleTechWrapperDescriptor::GetBillboardOriginTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 9; ++index)
    {
        if (value == gPARTICLE_BILLBOARD_ORIGIN_POSITIONS[index])
            return index;
    }
    return 0;
}

unsigned int CParticleTechWrapperDescriptor::GetParticleRenderIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 13; ++index)
    {
        if (value == gPARTICLE_RENDER_TYPE_NAMES[index])
            return index;
    }
    return 0;
}

unsigned int CParticleTechWrapperDescriptor::GetBillboardRotationTypeIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    if (value == gPARTICLE_BILLBOARD_ROTATION_TYPES[0]) return 0;
    if (value == gPARTICLE_BILLBOARD_ROTATION_TYPES[1]) return 1;
    return 0;
}

#include "StringUtilities.h"

std::wstring CParticleTechWrapperDescriptor::GetSortIndexStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    if (index >= 5) index = 0;
    return STRINGS::GetValueAsWString(index);
}

unsigned int CParticleTechWrapperDescriptor::GetSortIndexIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    unsigned int index = STRINGS::GetInt(value);
    return index >= 5 ? 0 : index;
}
