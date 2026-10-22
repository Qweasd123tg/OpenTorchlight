#include "DescriptorController.h"
#include "DescriptorRegistry.h"
#include "DescriptorControllerState.h"
#include "DescriptorProp.h"
#include "EditorBaseObject.h"
#include "AlignDescriptor.h"
#include "AnimationPlayerDescriptor.h"
#include "BoxColliderDescriptor.h"
#include "CameraControllerDescriptor.h"
#include "CameraShakeDescriptor.h"
#include "CinematicDescriptor.h"
#include "ColorAffectorDescriptor.h"
#include "CounterDescriptor.h"
#include "DamageShapeDescriptor.h"
#include "DungeonObjectDescriptor.h"
#include "EditorButtonDescriptor.h"
#include "EditorImageDescriptor.h"
#include "GameStateControllerDescriptor.h"
#include "GenericModelDescriptor.h"
#include "GeometryRotateDescriptor.h"
#include "GravityAffectorDescriptor.h"
#include "ItemDescriptor.h"
#include "JetAffectorDescriptor.h"
#include "LayoutDescriptor.h"
#include "LightDescriptor.h"
#include "LineAffectorDescriptor.h"
#include "LinearForceAffectorDescriptor.h"
#include "LogicGroupDescriptor.h"
#include "LogicTimerDescriptor.h"
#include "MissileDescriptor.h"
#include "MoneyTakerDescriptor.h"
#include "MonsterDescriptor.h"
#include "MusicObjectDescriptor.h"
#include "OutputIncrementorDescriptor.h"
#include "ParticleEmitterWrapperDescriptor.h"
#include "ParticleTechWrapperDescriptor.h"
#include "PathControllerDescriptor.h"
#include "PathNodeDescriptor.h"
#include "PlaneColliderDescriptor.h"
#include "PropertyNodeDescriptor.h"
#include "PuzzleRandomizerDescriptor.h"
#include "QuestControllerDescriptor.h"
#include "RandomChoiceDescriptor.h"
#include "RandomGroupDescriptor.h"
#include "RoomPieceDescriptor.h"
#include "ScaleAffectorDescriptor.h"
#include "SineForceAffectorDescriptor.h"
#include "SkillControllerDescriptor.h"
#include "SkipCutsceneDescriptor.h"
#include "SoundObjectDescriptor.h"
#include "SphereColliderDescriptor.h"
#include "TeleportDescriptor.h"
#include "TextureAnimateDescriptor.h"
#include "TextureRotateDescriptor.h"
#include "TimelineDescriptor.h"
#include "TriggerBoxDescriptor.h"
#include "TriggerSphereDescriptor.h"
#include "UnitSpawnerDescriptor.h"
#include "UnitTriggerDescriptor.h"
#include "VortexAffectorDescriptor.h"
#include "WarperDescriptor.h"
#include "WaypointActivatorDescriptor.h"

CDescriptorController::~CDescriptorController()
{
    for (std::map<std::wstring, TArrayList<CDescriptorProp*>*>::iterator i = m_Properties.begin();
         i != m_Properties.end(); ++i) {
        i->second->deleteAll();
        if (i->second) {
            delete i->second;
            i->second = NULL;
        }
    }
    m_Properties.clear();
    for (std::map<std::wstring, TArrayList<CDescriptorProp*>*>::iterator i = m_DefaultProperties.begin();
         i != m_DefaultProperties.end(); ++i) {
        i->second->deleteAll();
        if (i->second) {
            delete i->second;
            i->second = NULL;
        }
    }
    m_DefaultProperties.clear();
    if (g_CachedObjects.size()) {
        for (std::map<std::wstring, TArrayList<CEditorBaseObject*>*>::iterator i = g_CachedObjects.begin();
             i != g_CachedObjects.end(); ++i) {
            i->second->deleteAll();
            if (i->second) {
                delete i->second;
                i->second = NULL;
            }
        }
        g_CachedObjects.clear();
    }
}

static void* Set_CWaypointActivatorDescriptorParam1()
{
    CWaypointActivatorDescriptor* descriptor = new CWaypointActivatorDescriptor(L"Waypoint Activator", L"Activates waypoint for this level", L"waypointactivator");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Waypoint Activator");
    return descriptor;
}

static void* Set_CDungeonObjectDescriptorParam1()
{
    CDungeonObjectDescriptor* descriptor = new CDungeonObjectDescriptor(L"Dungeon Object", L"Performs operations on a dungeon", L"warper");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Dungeon Object");
    return descriptor;
}

static void* Set_CMoneyTakerDescriptorParam1()
{
    CMoneyTakerDescriptor* descriptor = new CMoneyTakerDescriptor(L"Money Taker", L"Attempts to take the set amount of money from the player", L"money");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Money Taker");
    return descriptor;
}

static void* Set_CCinematicDescriptorParam1()
{
    CCinematicDescriptor* descriptor = new CCinematicDescriptor(L"Cinematic", L"Controls playing a cinematic", L"cinematic");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Cinematic");
    return descriptor;
}

static void* Set_CDamageShapeDescriptorParam1()
{
    CDamageShapeDescriptor* descriptor = new CDamageShapeDescriptor();
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Damage Shape");
    return descriptor;
}

static void* Set_CSkipCutsceneDescriptorParam1()
{
    CSkipCutsceneDescriptor* descriptor = new CSkipCutsceneDescriptor(L"Skip Cutscene", L"watches the esc key to skip cut scene", L"skipcutscene");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Skip Cutscene");
    return descriptor;
}

static void* Set_CAnimationPlayerDescriptorParam1()
{
    CAnimationPlayerDescriptor* descriptor = new CAnimationPlayerDescriptor(L"Animation Controller", L"Animation Controller", L"clapperboard");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Animation Controller");
    return descriptor;
}

static void* Set_CPathNodeDescriptorParam1()
{
    CPathNodeDescriptor* descriptor = new CPathNodeDescriptor(L"Path Node", L"Path Node", L"effectpercent");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Path Node");
    return descriptor;
}

static void* Set_CPathControllerDescriptorParam1()
{
    CPathControllerDescriptor* descriptor = new CPathControllerDescriptor(L"Pathing", L"Pathing", L"pathing");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Pathing");
    return descriptor;
}

static void* Set_CSkillControllerDescriptorParam1()
{
    CSkillControllerDescriptor* descriptor = new CSkillControllerDescriptor(L"Skill Controller", L"Skill controller", L"skill");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Skill Controller");
    return descriptor;
}

static void* Set_CQuestControllerDescriptorParam1()
{
    CQuestControllerDescriptor* descriptor = new CQuestControllerDescriptor(L"Quest Controller", L"Quest controller", L"exclamation");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Quest Controller");
    return descriptor;
}

static void* Set_CGameStateControllerDescriptorParam1()
{
    CGameStateControllerDescriptor* descriptor = new CGameStateControllerDescriptor(L"Game State Controller", L"Game state controller", L"gear");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Game State Controller");
    return descriptor;
}

static void* Set_CRandomGroupDescriptorParam1()
{
    CRandomGroupDescriptor* descriptor = new CRandomGroupDescriptor();
    descriptor->setMenuCategory(L"");
    descriptor->setDescriptorName(L"Group");
    return descriptor;
}

static void* Set_CMissileDescriptorParam1()
{
    CMissileDescriptor* descriptor = new CMissileDescriptor();
    descriptor->setMenuCategory(L"Missiles");
    descriptor->setDescriptorName(L"Missile");
    return descriptor;
}

static void* Set_CMusicObjectDescriptorParam1()
{
    CMusicObjectDescriptor* descriptor = new CMusicObjectDescriptor(L"Music Object", L"Stores a music track that can be triggered", L"sound");
    descriptor->setMenuCategory(L"Sounds");
    descriptor->setDescriptorName(L"Music");
    return descriptor;
}

static void* Set_CSoundObjectDescriptorParam1()
{
    CSoundObjectDescriptor* descriptor = new CSoundObjectDescriptor();
    descriptor->setMenuCategory(L"Sounds");
    descriptor->setDescriptorName(L"Sound");
    return descriptor;
}

static void* Set_CLightDescriptorParam1()
{
    CLightDescriptor* descriptor = new CLightDescriptor();
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Light");
    return descriptor;
}

static void* Set_CRoomPieceDescriptorParam1()
{
    CRoomPieceDescriptor* descriptor = new CRoomPieceDescriptor();
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Room Piece");
    return descriptor;
}

static void* Set_CGenericModelDescriptorParam1()
{
    CGenericModelDescriptor* descriptor = new CGenericModelDescriptor();
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Generic Model");
    return descriptor;
}

static void* Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2()
{
    CLayoutDescriptor* descriptor = new CLayoutDescriptor(L"Layout Link Trigger", static_cast<ELAYOUT_TYPES>(3));
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Layout Link Trigger");
    return descriptor;
}

static void* Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2()
{
    CLayoutDescriptor* descriptor = new CLayoutDescriptor(L"Layout Link Timeline", static_cast<ELAYOUT_TYPES>(2));
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Layout Link Timeline");
    return descriptor;
}

static void* Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2()
{
    CLayoutDescriptor* descriptor = new CLayoutDescriptor(L"Layout Link Particle", static_cast<ELAYOUT_TYPES>(1));
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Layout Link Particle");
    return descriptor;
}

static void* Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2()
{
    CLayoutDescriptor* descriptor = new CLayoutDescriptor(L"Layout Link", static_cast<ELAYOUT_TYPES>(0));
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Layout Link");
    return descriptor;
}

static void* Set_CUnitSpawnerDescriptorParam1()
{
    CUnitSpawnerDescriptor* descriptor = new CUnitSpawnerDescriptor();
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Unit Spawner");
    return descriptor;
}

static void* Set_CUnitTriggerDescriptorParam1()
{
    CUnitTriggerDescriptor* descriptor = new CUnitTriggerDescriptor(L"Unit Trigger", L"Trigger for logic", L"chest");
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Unit Trigger");
    return descriptor;
}

static void* Set_CItemDescriptorParam1()
{
    CItemDescriptor* descriptor = new CItemDescriptor(L"Item", L"Item in the level", L"remove");
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Item");
    return descriptor;
}

static void* Set_CMonsterDescriptorParam1()
{
    CMonsterDescriptor* descriptor = new CMonsterDescriptor(L"Monster", L"Monster in the level", L"monster");
    descriptor->setMenuCategory(L"Building Blocks");
    descriptor->setDescriptorName(L"Monster");
    return descriptor;
}

static void* Set_CCameraControllerDescriptorParam1()
{
    CCameraControllerDescriptor* descriptor = new CCameraControllerDescriptor(L"Camera Controller", L"Interactive Object", L"camera");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Camera Controller");
    return descriptor;
}

static void* Set_CPuzzleRandomizerDescriptorParam1()
{
    CPuzzleRandomizerDescriptor* descriptor = new CPuzzleRandomizerDescriptor(L"Puzzle Input", L"Puzzle Counter", L"die");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Puzzle Input");
    return descriptor;
}

static void* Set_CPropertyNodeDescriptorParam1()
{
    CPropertyNodeDescriptor* descriptor = new CPropertyNodeDescriptor();
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Property Node");
    return descriptor;
}

static void* Set_CCameraShakeDescriptorParam1()
{
    CCameraShakeDescriptor* descriptor = new CCameraShakeDescriptor();
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Camera Shake");
    return descriptor;
}

static void* Set_COutputIncrementorDescriptorParam1()
{
    COutputIncrementorDescriptor* descriptor = new COutputIncrementorDescriptor(L"Output Incrementor", L"Increments output", L"outputcounter");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Output Incrementor");
    return descriptor;
}

static void* Set_CLogicTimerDescriptorParam1()
{
    CLogicTimerDescriptor* descriptor = new CLogicTimerDescriptor(L"Timer", L"Timer ticks down when enabled", L"clock");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Timer");
    return descriptor;
}

static void* Set_CTeleportDescriptorParam1()
{
    CTeleportDescriptor* descriptor = new CTeleportDescriptor(L"Teleport", L"Teleports player inside level", L"teleport");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Teleport");
    return descriptor;
}

static void* Set_CWarperDescriptorParam1()
{
    CWarperDescriptor* descriptor = new CWarperDescriptor(L"Warper", L"Warps player to another level", L"warper");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Warper");
    return descriptor;
}

static void* Set_CRandomChoiceDescriptorParam1()
{
    CRandomChoiceDescriptor* descriptor = new CRandomChoiceDescriptor(L"Random Choice", L"Random choice of outputs", L"question");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Random Choice");
    return descriptor;
}

static void* Set_CCounterDescriptorParam1()
{
    CCounterDescriptor* descriptor = new CCounterDescriptor(L"Counter", L"Counts up and then broadcasts emitters", L"counter");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Counter");
    return descriptor;
}

static void* Set_CTriggerBoxDescriptorParam1()
{
    CTriggerBoxDescriptor* descriptor = new CTriggerBoxDescriptor(L"Player Box Trigger", L"Trigger for logic", L"boxtrigger");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Player Box Trigger");
    return descriptor;
}

static void* Set_CTriggerSphereDescriptorParam1()
{
    CTriggerSphereDescriptor* descriptor = new CTriggerSphereDescriptor(L"Player Sphere Trigger", L"Trigger for logic", L"playersphere");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Player Sphere Trigger");
    return descriptor;
}

static void* Set_CLogicGroupDescriptorParam1()
{
    CLogicGroupDescriptor* descriptor = new CLogicGroupDescriptor(L"Logic Group", L"Double click to bring up logic group", L"logicgroup");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Logic Group");
    return descriptor;
}

static void* Set_CTimelineDescriptorParam1()
{
    CTimelineDescriptor* descriptor = new CTimelineDescriptor(L"Timeline", L"Double click to bring up timeline", L"timeline");
    descriptor->setMenuCategory(L"Logic");
    descriptor->setDescriptorName(L"Timeline");
    return descriptor;
}

static void* Set_CSphereColliderDescriptorParam1()
{
    CSphereColliderDescriptor* descriptor = new CSphereColliderDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Sphere Collision");
    return descriptor;
}

static void* Set_CPlaneColliderDescriptorParam1()
{
    CPlaneColliderDescriptor* descriptor = new CPlaneColliderDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Plane Collision");
    return descriptor;
}

static void* Set_CBoxColliderDescriptorParam1()
{
    CBoxColliderDescriptor* descriptor = new CBoxColliderDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Box Collision");
    return descriptor;
}

static void* Set_CColorAffectorDescriptorParam1()
{
    CColorAffectorDescriptor* descriptor = new CColorAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Color");
    return descriptor;
}

static void* Set_CTextureAnimateDescriptorParam1()
{
    CTextureAnimateDescriptor* descriptor = new CTextureAnimateDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Texture Animation");
    return descriptor;
}

static void* Set_CTextureRotateDescriptorParam1()
{
    CTextureRotateDescriptor* descriptor = new CTextureRotateDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Texture Rotate");
    return descriptor;
}

static void* Set_CGeometryRotateDescriptorParam1()
{
    CGeometryRotateDescriptor* descriptor = new CGeometryRotateDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Geometry Rotator");
    return descriptor;
}

static void* Set_CJetAffectorDescriptorParam1()
{
    CJetAffectorDescriptor* descriptor = new CJetAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Jet");
    return descriptor;
}

static void* Set_CScaleAffectorDescriptorParam1()
{
    CScaleAffectorDescriptor* descriptor = new CScaleAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Scale");
    return descriptor;
}

static void* Set_CGravityAffectorDescriptorParam1()
{
    CGravityAffectorDescriptor* descriptor = new CGravityAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Gravity Well");
    return descriptor;
}

static void* Set_CVortexAffectorDescriptorParam1()
{
    CVortexAffectorDescriptor* descriptor = new CVortexAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Vortext");
    return descriptor;
}

static void* Set_CSineForceAffectorDescriptorParam1()
{
    CSineForceAffectorDescriptor* descriptor = new CSineForceAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Sine Force");
    return descriptor;
}

static void* Set_CLinearForceAffectorDescriptorParam1()
{
    CLinearForceAffectorDescriptor* descriptor = new CLinearForceAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Linear Force");
    return descriptor;
}

static void* Set_CLineAffectorDescriptorParam1()
{
    CLineAffectorDescriptor* descriptor = new CLineAffectorDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Line");
    return descriptor;
}

static void* Set_CAlignDescriptorParam1()
{
    CAlignDescriptor* descriptor = new CAlignDescriptor();
    descriptor->setMenuCategory(L"Affectors");
    descriptor->setDescriptorName(L"Align");
    return descriptor;
}

static void* Set_CParticleEmitterWrapperDescriptorParam1()
{
    CParticleEmitterWrapperDescriptor* descriptor = new CParticleEmitterWrapperDescriptor();
    descriptor->setMenuCategory(L"");
    descriptor->setDescriptorName(L"Emitter");
    return descriptor;
}

static void* Set_CParticleTechWrapperDescriptorParam1()
{
    CParticleTechWrapperDescriptor* descriptor = new CParticleTechWrapperDescriptor();
    descriptor->setMenuCategory(L"Particles");
    descriptor->setDescriptorName(L"Particle");
    return descriptor;
}

static void* Set_CEditorButtonDescriptorParam1()
{
    CEditorButtonDescriptor* descriptor = new CEditorButtonDescriptor();
    descriptor->setMenuCategory(L"UI");
    descriptor->setDescriptorName(L"Button");
    return descriptor;
}

static void* Set_CEditorImageDescriptorParam1()
{
    CEditorImageDescriptor* descriptor = new CEditorImageDescriptor();
    descriptor->setMenuCategory(L"UI");
    descriptor->setDescriptorName(L"Image");
    return descriptor;
}

void CDescriptorController::addDescriptorFunction(const wchar_t* name, void* (*factory)())
{
    g_Descriptors[name] = factory;
    g_DescriptorNameOrder.push_back(name);
}

CDescriptorController::CDescriptorController()
{
    addDescriptorFunction(L"Group", Set_CRandomGroupDescriptorParam1);
    addDescriptorFunction(L"Monster", Set_CMonsterDescriptorParam1);
    addDescriptorFunction(L"Item", Set_CItemDescriptorParam1);
    addDescriptorFunction(L"Unit Trigger", Set_CUnitTriggerDescriptorParam1);
    addDescriptorFunction(L"Unit Spawner", Set_CUnitSpawnerDescriptorParam1);
    addDescriptorFunction(L"Layout Link", Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2);
    addDescriptorFunction(L"Layout Link Particle", Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2);
    addDescriptorFunction(L"Layout Link Timeline", Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2);
    addDescriptorFunction(L"Layout Link Trigger", Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2);
    addDescriptorFunction(L"Generic Model", Set_CGenericModelDescriptorParam1);
    addDescriptorFunction(L"Room Piece", Set_CRoomPieceDescriptorParam1);
    addDescriptorFunction(L"Light", Set_CLightDescriptorParam1);
    addDescriptorFunction(L"Sound", Set_CSoundObjectDescriptorParam1);
    addDescriptorFunction(L"Music", Set_CMusicObjectDescriptorParam1);
    addDescriptorFunction(L"Missile", Set_CMissileDescriptorParam1);
    addDescriptorFunction(L"Image", Set_CEditorImageDescriptorParam1);
    addDescriptorFunction(L"Button", Set_CEditorButtonDescriptorParam1);
    addDescriptorFunction(L"Particle", Set_CParticleTechWrapperDescriptorParam1);
    addDescriptorFunction(L"Emitter", Set_CParticleEmitterWrapperDescriptorParam1);
    addDescriptorFunction(L"Align", Set_CAlignDescriptorParam1);
    addDescriptorFunction(L"Line", Set_CLineAffectorDescriptorParam1);
    addDescriptorFunction(L"Linear Force", Set_CLinearForceAffectorDescriptorParam1);
    addDescriptorFunction(L"Sine Force", Set_CSineForceAffectorDescriptorParam1);
    addDescriptorFunction(L"Vortext", Set_CVortexAffectorDescriptorParam1);
    addDescriptorFunction(L"Gravity Well", Set_CGravityAffectorDescriptorParam1);
    addDescriptorFunction(L"Scale", Set_CScaleAffectorDescriptorParam1);
    addDescriptorFunction(L"Jet", Set_CJetAffectorDescriptorParam1);
    addDescriptorFunction(L"Geometry Rotator", Set_CGeometryRotateDescriptorParam1);
    addDescriptorFunction(L"Texture Rotate", Set_CTextureRotateDescriptorParam1);
    addDescriptorFunction(L"Texture Animation", Set_CTextureAnimateDescriptorParam1);
    addDescriptorFunction(L"Color", Set_CColorAffectorDescriptorParam1);
    addDescriptorFunction(L"Box Collision", Set_CBoxColliderDescriptorParam1);
    addDescriptorFunction(L"Plane Collision", Set_CPlaneColliderDescriptorParam1);
    addDescriptorFunction(L"Sphere Collision", Set_CSphereColliderDescriptorParam1);
    addDescriptorFunction(L"Timeline", Set_CTimelineDescriptorParam1);
    addDescriptorFunction(L"Logic Group", Set_CLogicGroupDescriptorParam1);
    addDescriptorFunction(L"Player Sphere Trigger", Set_CTriggerSphereDescriptorParam1);
    addDescriptorFunction(L"Player Box Trigger", Set_CTriggerBoxDescriptorParam1);
    addDescriptorFunction(L"Counter", Set_CCounterDescriptorParam1);
    addDescriptorFunction(L"Random Choice", Set_CRandomChoiceDescriptorParam1);
    addDescriptorFunction(L"Warper", Set_CWarperDescriptorParam1);
    addDescriptorFunction(L"Teleport", Set_CTeleportDescriptorParam1);
    addDescriptorFunction(L"Timer", Set_CLogicTimerDescriptorParam1);
    addDescriptorFunction(L"Output Incrementor", Set_COutputIncrementorDescriptorParam1);
    addDescriptorFunction(L"Camera Shake", Set_CCameraShakeDescriptorParam1);
    addDescriptorFunction(L"Property Node", Set_CPropertyNodeDescriptorParam1);
    addDescriptorFunction(L"Puzzle Input", Set_CPuzzleRandomizerDescriptorParam1);
    addDescriptorFunction(L"Camera Controller", Set_CCameraControllerDescriptorParam1);
    addDescriptorFunction(L"Game State Controller", Set_CGameStateControllerDescriptorParam1);
    addDescriptorFunction(L"Quest Controller", Set_CQuestControllerDescriptorParam1);
    addDescriptorFunction(L"Skill Controller", Set_CSkillControllerDescriptorParam1);
    addDescriptorFunction(L"Pathing", Set_CPathControllerDescriptorParam1);
    addDescriptorFunction(L"Path Node", Set_CPathNodeDescriptorParam1);
    addDescriptorFunction(L"Animation Controller", Set_CAnimationPlayerDescriptorParam1);
    addDescriptorFunction(L"Skip Cutscene", Set_CSkipCutsceneDescriptorParam1);
    addDescriptorFunction(L"Damage Shape", Set_CDamageShapeDescriptorParam1);
    addDescriptorFunction(L"Cinematic", Set_CCinematicDescriptorParam1);
    addDescriptorFunction(L"Money Taker", Set_CMoneyTakerDescriptorParam1);
    addDescriptorFunction(L"Dungeon Object", Set_CDungeonObjectDescriptorParam1);
    addDescriptorFunction(L"Waypoint Activator", Set_CWaypointActivatorDescriptorParam1);
}

#include "DescriptorProp.h"

CDescriptor* CDescriptorController::getNewDescriptorByName(const std::wstring& name)
{
    DescriptorFactoryMap::iterator factory = g_Descriptors.find(name);
    if (factory == g_Descriptors.end())
        return NULL;
    CDescriptor* descriptor = static_cast<CDescriptor*>(factory->second());
    for (unsigned int i = 0; i < g_DescriptorNameOrder.size(); ++i) {
        if (g_DescriptorNameOrder[i] == name) {
            descriptor->m_iID = i;
            break;
        }
    }
    return descriptor;
}

CDescriptor* CDescriptorController::getNewDescriptorByCreatedIndex(unsigned int index)
{
    if (index < g_DescriptorNameOrder.size())
        return getNewDescriptorByName(g_DescriptorNameOrder[index]);
    return NULL;
}

CDescriptorProp* CDescriptorController::getDescriptorPropertyByName(
    CDescriptor* descriptor, const std::wstring& name, bool defaults)
{
    if (!descriptor)
        return NULL;
    std::map<std::wstring, TArrayList<CDescriptorProp*>*>& properties = defaults
        ? g_DescriptorController.m_DefaultProperties : g_DescriptorController.m_Properties;
    std::map<std::wstring, TArrayList<CDescriptorProp*>*>::iterator found = properties.find(descriptor->m_sName);
    if (found == properties.end() || !found->second)
        return NULL;
    TArrayList<CDescriptorProp*>* list = found->second;
    for (unsigned int i = 0; i < list->size(); ++i)
        if ((*list)[i]->m_sName == name)
            return (*list)[i];
    return NULL;
}

long long CDescriptorController::getDescriptionVersion()
{
    if (g_DescriptionVersion == 0) {
        unsigned int shift = 0;
        for (unsigned int i = 0; i < g_DescriptorNameOrder.size(); ++i) {
            CDescriptor* descriptor = getNewDescriptorByName(g_DescriptorNameOrder[i]);
            long long value = descriptor->getUniqueNumericValueRepresentation();
            g_DescriptionVersion += (value << shift) + (value >> (64 - shift));
            delete descriptor;
            shift += 3;
            if (shift >= 64) shift -= 64;
        }
        g_DescriptionVersion += 18;
    }
    return g_DescriptionVersion;
}

CEditorBaseObject* CDescriptorController::getCachedObject(const std::wstring& name)
{
    std::map<std::wstring, TArrayList<CEditorBaseObject*>*>::iterator it = g_CachedObjects.find(name);
    if (it == g_CachedObjects.end()) return NULL;
    TArrayList<CEditorBaseObject*>* objects = it->second;
    if (objects->size() == 0) return NULL;
    CEditorBaseObject* object = (*objects)[0];
    objects->removeAt(0);
    return object;
}

void CDescriptorController::addDescriptorProperty(CDescriptor* descriptor,
    CDescriptorProp* property, bool defaults)
{
    if (!descriptor) return;
    std::map<std::wstring, TArrayList<CDescriptorProp*>*>& properties = defaults
        ? g_DescriptorController.m_DefaultProperties : g_DescriptorController.m_Properties;
    if (properties.find(descriptor->m_sName) == properties.end())
        properties[descriptor->m_sName] = new TArrayList<CDescriptorProp*>(20);
    properties[descriptor->m_sName]->add(property);
}

void CDescriptorController::returnCarchedObject(const std::wstring& name, CEditorBaseObject* object)
{
    if (!object) return;
    if (g_CachedObjects.find(name) == g_CachedObjects.end())
        g_CachedObjects[name] = new TArrayList<CEditorBaseObject*>(1000);
    g_CachedObjects[name]->add(object);
    object->removedFromSceneAndAddedToCache();
}
