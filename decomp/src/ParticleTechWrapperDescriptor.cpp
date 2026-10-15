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
