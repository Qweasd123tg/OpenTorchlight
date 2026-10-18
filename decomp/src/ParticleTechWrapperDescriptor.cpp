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

CParticleTechWrapperDescriptor::CParticleTechWrapperDescriptor()
    : CPositionableObjectDescriptor(L"Particle", L"Particle control emitters, affectors, Observers and most importantly what is rendering.", L"particle", true, true, true, true, false)
{
    m_iFlags |= DESCRIPTOR_FLAG_CHILDREN;
    m_ParentFilters.add(std::wstring(L"ALL"));
    m_ParentFilters.add(std::wstring(L"PARTICLE"));
    AddInputLogic(INPUT_EVENT_START_PARTICLE);
    AddInputLogic(INPUT_EVENT_STOP_PARTICLE);
    AddPropertyWithInterpreterFunctions(L"RENDERING", L"RENDER TYPE", L"This is the render type for the particle", (void*)Set_setRenderType, (void*)Get_getRenderType, GetParticleRenderIDByString, GetParticleRenderStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"WORLD SCALES", L"VISUAL SCALE", L"Scales everything that is a visual by scale", (void*)Set_setWorldVisualScale, (void*)Get_getWorldVisualScale, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"WORLD SCALES", L"TIME SCALE", L"Make particle systems go faster", (void*)Set_setWorldScaleTime, (void*)Get_getWorldScaleTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"WORLD SCALES", L"VELOCITY SCALE", L"Make particle and emitter velocities faster or slower", (void*)Set_setWorldScaleVelocity, (void*)Get_getWorldScaleVelocity, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"LIFE TIME", L"Leave 0 to loop.", (void*)Set_setFixedLifeTime, (void*)Get_getFixedLifeTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"WORLD ORIENTATION", L"The particles orientation is always up.", (void*)Set_setAlwaysUp, (void*)Get_getAlwaysUp, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NO CULLING", L"The particle never culls", (void*)Set_setNoCull, (void*)Get_getNoCull, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TECHNIQUE PROPERTIES", L"IS LIGHT", L"Sets the particle so it becomes al ight", (void*)Set_setAsLight, (void*)Get_getIsLight, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TECHNIQUE PROPERTIES", L"VISIBLE", L"Setting the property hides the particles", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TECHNIQUE PROPERTIES", L"SORTS", L"Enabling this will make the particles sort with the geometry", (void*)Set_setSorts, (void*)Get_getSorts, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"TECHNIQUE PROPERTIES", L"SORT INDEX", L"This is the sorting draw index", (void*)Set_setSortIndex, (void*)Get_getSortIndex, GetSortIndexIDByString, GetSortIndexStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"TECHNIQUE PROPERTIES", L"DEPTH BIAS", L"Depth bias toward screen", (void*)Set_setDepthBias, (void*)Get_getDepthBias, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"MAX VALUES ALLOWED", L"VELOCITY", L"Max velocity allowed", (void*)Set_setMaxVelocity, (void*)Get_getMaxVelocity, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"MAX VALUES ALLOWED", L"VISUAL QUOTA", L"This is the max visual particles allowed in the particle system", (void*)Set_setVisualParticleQuota, (void*)Get_getVisualParticleQuota, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"RESOURCES and RENDERING", L"TEXTURE", L"Texture file", (void*)Set_setTexturePath, (void*)Get_getTexturePath, VARIABLE_TYPE_STRING, 1024);
    AddPropertyWithInterpreterFunctions(L"RESOURCES and RENDERING", L"RENDER STYLE", L"This is the style the texture will render at.", (void*)Set_setParticleRenderStyle, (void*)Get_getParticleRenderStyle, GetParticleRenderStyleIDByString, GetParticleRenderStyleStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"RESOURCES and RENDERING", L"MESH", L"Mesh file", (void*)Set_setModelPath, (void*)Get_getModelPath, VARIABLE_TYPE_STRING, 4096);
    AddProperty(L"RESOURCES and RENDERING", L"DEPTH CHECK", L"setting this to false will make it render in front of everything.", (void*)Set_setDepthCheck, (void*)Get_getDepthCheck, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"BILLBOARD PROPERTIES", L"ROTATION TYPE", L"This specifies if you want to rotate the geometry or the texture.", (void*)Set_setBillboardRotationType, (void*)Get_getBillboardRotationType, GetBillboardRotationTypeIDByString, GetBillboardRotationTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"BILLBOARD PROPERTIES", L"ORIGIN", L"This is the origin of the billboard.", (void*)Set_setBillboardOrigin, (void*)Get_getBillboardOrigin, GetBillboardOriginTypeIDByString, GetBillboardOriginTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"RIBBON PROPERTIES", L"LENGTH", L"The length of the ribbon", (void*)Set_setRibbonLength, (void*)Get_getRibbonLength, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"RIBBON PROPERTIES", L"WIDTH", L"The width of the ribbon", (void*)Set_setRibbonWidth, (void*)Get_getRibbonWidth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"RIBBON PROPERTIES", L"SEGMENTS", L"The number of segments in the ribbon", (void*)Set_setRibbonMaxChains, (void*)Get_getRibbonMaxChains, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"RIBBON PROPERTIES", L"FADE ENDS", L"Set ends of ribbon to black and transparent", (void*)Set_setRibbonEndFade, (void*)Get_getRibbonEndFade, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"RIBBON PROPERTIES", L"LOCAL TRAIL", L"Trail stays local to parent system", (void*)Set_setRibbonLocalTrail, (void*)Get_getRibbonLocalTrail, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"UV ANIMATION", L"FRAMES WIDE", L"X frames on flipbook sheet", (void*)Set_setFlipbookWidth, (void*)Get_getFlipbookWidth, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"UV ANIMATION", L"FRAMES HIGH", L"Y frames on flipbook sheet", (void*)Set_setFlipbookHeight, (void*)Get_getFlipbookHeight, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"UV ANIMATION", L"U RATE", L"U scroll rate", (void*)Set_setUScroll, (void*)Get_getUScroll, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"UV ANIMATION", L"V RATE", L"V scroll rate", (void*)Set_setVScroll, (void*)Get_getVScroll, VARIABLE_TYPE_FLOAT, 0);
}

void CParticleTechWrapperDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender)
{
    CParticleTechWrapper* technique = dynamic_cast<CParticleTechWrapper*>(object);
    if (!technique)
        return;
    if (event == 16) {
        if (!technique->getEnabled())
            technique->setActivated(true);
        technique->start();
        object->BroadcastEvent(31);
    } else if (event == 17) {
        technique->stop();
        object->BroadcastEvent(32);
    }
    CPositionableObjectDescriptor::InputLogicEvent(object, event, sender);
}
