#include "ParticleEmitterWrapperDescriptor.h"

void CParticleEmitterWrapperDescriptor::deleteNotification()
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
        DescriptorObjectBeingDeleted(m_Objects[i]);
}

CParticleEmitterWrapperDescriptor::~CParticleEmitterWrapperDescriptor()
{
}

#include "ParticleEmitterWrapper.h"
#include <map>
#include <string>
#include "ParticleEmitterWrapperDescriptorNames.h"
#include "ParticleEmitterWrapper.h"

bool CParticleEmitterWrapperDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    static_cast<CParticleEmitterWrapper*>(object)->destroyEmitter();
    return true;
}

void CParticleEmitterWrapperDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CParticleEmitterWrapper* target = dynamic_cast<CParticleEmitterWrapper*>(object);
        if (target)
        {
            switch (event)
            {
            case 2: target->setVisible(true); target->setEnabled(true); break;
            case 3: target->setEnabled(false); break;
            }
            CPositionableObjectDescriptor::InputLogicEvent(object, event, initiator);
        }
    }
}

std::wstring CParticleEmitterWrapperDescriptor::GetEmitterTypeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 4)
        return gEMITTER_TYPES[0];
    return gEMITTER_TYPES[index];
}

unsigned int CParticleEmitterWrapperDescriptor::GetEmitterTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 5; ++index)
    {
        if (value == gEMITTER_TYPES[index])
            return index;
    }
    return 0;
}

CEditorBaseObject* CParticleEmitterWrapperDescriptor::CreateObject(CEditorScene* scene)
{
    return new CParticleEmitterWrapper(scene->getResourceManager());
}

CParticleEmitterWrapperDescriptor::CParticleEmitterWrapperDescriptor()
    : CPositionableObjectDescriptor(L"Emitter", L"Emitters will release anything from images to meshes depending on the renderer.", L"EMITTER", true, false, false, false, false)
{
    m_iFlags |= DESCRIPTOR_FLAG_CHILDREN;
    m_iFlags &= ~DESCRIPTOR_FLAG_100;
    m_ParentFilters.add(std::wstring(L"PARTICLE"));
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddPropertyWithInterpreterFunctions(L"TYPE", L"TYPE OF EMITTER", L"Different types of emitters.", (void*)Set_setEmitterType, (void*)Get_getEmitterType, GetEmitterTypeIDByString, GetEmitterTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"MOVEMENT", L"DIRECTION", L"This is the direction the particles will be released at.", (void*)Set_setParticleDirection, (void*)Get_getParticleDirection, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"DIMENSIONS", L"FIXED", L"Fixed sized for particle( uses Width ).", (void*)Set_setUnifiedScale, (void*)Get_getUnifiedScale, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"DIMENSIONS", L"SCALE ON LAUNCH", L"After the particle has it's with and height it'll be scaled.", (void*)Set_setDynPropScaleOnLaunch, (void*)Get_getDynPropScaleOnLaunch, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"DIMENSIONS", L"WIDTH", L"Width of the particles.", (void*)Set_setDynPropWidth, (void*)Get_getDynPropWidth, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"DIMENSIONS", L"HEIGHT", L"Height of the particles.", (void*)Set_setDynPropHeight, (void*)Get_getDynPropHeight, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"DIMENSIONS", L"DEPTH", L"The depth of render.", (void*)Set_setDynPropDepth, (void*)Get_getDynPropDepth, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"MOVEMENT", L"ANGLE", L"Angle at which to release the particles around the direction.", (void*)Set_setDynPropAngleOfRelease, (void*)Get_getDynPropAngleOfRelease, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"MOVEMENT", L"VELOCITY", L"The velocity of the emitter.", (void*)Set_setDynPropVelocity, (void*)Get_getDynPropVelocity, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"PROPERTIES", L"MASS", L"The mass of the particles released.", (void*)Set_setDynPropMass, (void*)Get_getDynPropMass, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"PROPERTIES", L"KEEP LOCAL", L"Keeps the particle local to the emitter ( if the particle say moves for instance ).", (void*)Set_setKeepLocal, (void*)Get_getKeepLocal, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the emitter enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NO EXPIRATION", L"Particles don't expire", (void*)Set_setDynPropNonExpiring, (void*)Get_getDynPropNonExpiring, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"EMISSION", L"DELAY FIRST", L"If true the delay occurs first", (void*)Set_setDelayOccursFirst, (void*)Get_getDelayOccursFirst, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"EMISSION", L"DELAY", L"Once the emit duration has been reached it dealys for X amount and starts over.", (void*)Set_setDynPropRepeatRate, (void*)Get_getDynPropRepeatRate, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"EMISSION", L"PARTICLE LIFE", L"Once a particle is released the life span of it. Using a dynamic property will use the emitter's Duration.", (void*)Set_setDynPropTimeToLive, (void*)Get_getDynPropTimeToLive, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"EMISSION", L"EMIT DURATION", L"The duration over time the emitter releases it's particles. NOTE - if you use a dynamic property such as a range it'll base the duration off the parent particle system.", (void*)Set_setDynPropDuration, (void*)Get_getDynPropDuration, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"EMISSION", L"EMIT RATE", L"This is the rate at which the elements being emitted are released. This is based off the duration of the emitter.", (void*)Set_setDynPropEmissionRate, (void*)Get_getDynPropEmissionRate, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"EMISSION", L"NUM LOOPS", L"-1 means it loops forever. 0 means just once and any number above 0 means it loops down till the counter reaches zero.", (void*)Set_setNumberOfLoops, (void*)Get_getNumberOfLoops, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"EMISSION", L"RELEASE OVER DISTANCE", L"If true the emitter will release over distance of 1 unit. L", (void*)Set_setEmitOverDistance, (void*)Get_getEmitOverDistance, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"EMISSION", L"CHANCE TO EMIT", L"The chance to emit per loop.", (void*)Set_setDynPropChanceOfRelease, (void*)Get_getDynPropChanceOfRelease, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"LINE EMITTER", L"MIN INCREMENT", L"The min increment of the particles to release in.", (void*)Set_setMinLineIncrement, (void*)Get_getMinLineIncrement, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"LINE EMITTER", L"MAX INCREMENT", L"The max increment of the particles to release in.", (void*)Set_setMaxLineIncrement, (void*)Get_getMaxLineIncrement, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"LINE EMITTER", L"MAX DEVIATION", L"The max deviation allowed on the line.", (void*)Set_setMaxLineDeviation, (void*)Get_getMaxLineDeviation, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"LINE EMITTER", L"END POSITION", L"The end position of the line.", (void*)Set_setPositionEnd, (void*)Get_getPositionEnd, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"BOX EMITTER", L"WIDTH", L"The width off the box.", (void*)Set_setBoxWidth, (void*)Get_getBoxWidth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"BOX EMITTER", L"HEIGHT", L"The height of the box.", (void*)Set_setBoxHeight, (void*)Get_getBoxHeight, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"BOX EMITTER", L"DEPTH", L"The depth of the box.", (void*)Set_setBoxDepth, (void*)Get_getBoxDepth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SPHERE EMITTER", L"RADIUS", L"The radius of the emitter when using a sphere or circle.", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"CIRCLE EMITTER", L"MIN RADIUS", L"The min radius of the emitter when using a sphere or circle.", (void*)Set_setMinRadius, (void*)Get_getMinRadius, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"CIRCLE EMITTER", L"MAX RADIUS", L"The max radius of the emitter when using a sphere or circle.", (void*)Set_setMaxRadius, (void*)Get_getMaxRadius, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"CIRCLE EMITTER", L"STEP", L"The particle step around the angle specified.", (void*)Set_setCircleStep, (void*)Get_getCircleStep, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"CIRCLE EMITTER", L"FIXED", L"fixed radius. Will us the max radius", (void*)Set_setCircleFixedSize, (void*)Get_getCircleFixedSize, VARIABLE_TYPE_BOOL, 0);
}
