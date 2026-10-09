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

void CParticleTechWrapperDescriptor::DescriptorObjectHasBeenInited(CEditorBaseObject* object)
{
    static_cast<CParticleTechWrapper*>(object)->createTextureMaterial();
}
