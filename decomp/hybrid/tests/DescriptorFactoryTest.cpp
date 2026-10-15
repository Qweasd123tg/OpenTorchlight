// Factory bodies execute unchanged; collaborators isolate constructor side effects.
#include <cstring>
#include <new>
#include <string>
#include <stdint.h>
#include "GameEnums.h"
#include "AutoTest.h"
#include "Detour.h"
extern "C" char factoryAllocate[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char factoryRelease[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
TL_ORIGINAL(void*,oldFactory0,(),"_ZL38Set_CWaypointActivatorDescriptorParam1v")
extern "C" void* newFactory0() __asm__("__tlhybrid_local_12__ZL38Set_CWaypointActivatorDescriptorParam1v");
TL_FUNCTION(factoryCtor0,"_ZN28CWaypointActivatorDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory1,(),"_ZL34Set_CDungeonObjectDescriptorParam1v")
extern "C" void* newFactory1() __asm__("__tlhybrid_local_12__ZL34Set_CDungeonObjectDescriptorParam1v");
TL_FUNCTION(factoryCtor1,"_ZN24CDungeonObjectDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory2,(),"_ZL31Set_CMoneyTakerDescriptorParam1v")
extern "C" void* newFactory2() __asm__("__tlhybrid_local_12__ZL31Set_CMoneyTakerDescriptorParam1v");
TL_FUNCTION(factoryCtor2,"_ZN21CMoneyTakerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory3,(),"_ZL30Set_CCinematicDescriptorParam1v")
extern "C" void* newFactory3() __asm__("__tlhybrid_local_12__ZL30Set_CCinematicDescriptorParam1v");
TL_FUNCTION(factoryCtor3,"_ZN20CCinematicDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory4,(),"_ZL32Set_CDamageShapeDescriptorParam1v")
extern "C" void* newFactory4() __asm__("__tlhybrid_local_12__ZL32Set_CDamageShapeDescriptorParam1v");
TL_FUNCTION(factoryCtor4,"_ZN22CDamageShapeDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory5,(),"_ZL33Set_CSkipCutsceneDescriptorParam1v")
extern "C" void* newFactory5() __asm__("__tlhybrid_local_12__ZL33Set_CSkipCutsceneDescriptorParam1v");
TL_FUNCTION(factoryCtor5,"_ZN23CSkipCutsceneDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory6,(),"_ZL36Set_CAnimationPlayerDescriptorParam1v")
extern "C" void* newFactory6() __asm__("__tlhybrid_local_12__ZL36Set_CAnimationPlayerDescriptorParam1v");
TL_FUNCTION(factoryCtor6,"_ZN26CAnimationPlayerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory7,(),"_ZL29Set_CPathNodeDescriptorParam1v")
extern "C" void* newFactory7() __asm__("__tlhybrid_local_12__ZL29Set_CPathNodeDescriptorParam1v");
TL_FUNCTION(factoryCtor7,"_ZN19CPathNodeDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory8,(),"_ZL35Set_CPathControllerDescriptorParam1v")
extern "C" void* newFactory8() __asm__("__tlhybrid_local_12__ZL35Set_CPathControllerDescriptorParam1v");
TL_FUNCTION(factoryCtor8,"_ZN25CPathControllerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory9,(),"_ZL36Set_CSkillControllerDescriptorParam1v")
extern "C" void* newFactory9() __asm__("__tlhybrid_local_12__ZL36Set_CSkillControllerDescriptorParam1v");
TL_FUNCTION(factoryCtor9,"_ZN26CSkillControllerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory10,(),"_ZL36Set_CQuestControllerDescriptorParam1v")
extern "C" void* newFactory10() __asm__("__tlhybrid_local_12__ZL36Set_CQuestControllerDescriptorParam1v");
TL_FUNCTION(factoryCtor10,"_ZN26CQuestControllerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory11,(),"_ZL40Set_CGameStateControllerDescriptorParam1v")
extern "C" void* newFactory11() __asm__("__tlhybrid_local_12__ZL40Set_CGameStateControllerDescriptorParam1v");
TL_FUNCTION(factoryCtor11,"_ZN30CGameStateControllerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory12,(),"_ZL32Set_CRandomGroupDescriptorParam1v")
extern "C" void* newFactory12() __asm__("__tlhybrid_local_12__ZL32Set_CRandomGroupDescriptorParam1v");
TL_FUNCTION(factoryCtor12,"_ZN22CRandomGroupDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory13,(),"_ZL28Set_CMissileDescriptorParam1v")
extern "C" void* newFactory13() __asm__("__tlhybrid_local_12__ZL28Set_CMissileDescriptorParam1v");
TL_FUNCTION(factoryCtor13,"_ZN18CMissileDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory14,(),"_ZL32Set_CMusicObjectDescriptorParam1v")
extern "C" void* newFactory14() __asm__("__tlhybrid_local_12__ZL32Set_CMusicObjectDescriptorParam1v");
TL_FUNCTION(factoryCtor14,"_ZN22CMusicObjectDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory15,(),"_ZL32Set_CSoundObjectDescriptorParam1v")
extern "C" void* newFactory15() __asm__("__tlhybrid_local_12__ZL32Set_CSoundObjectDescriptorParam1v");
TL_FUNCTION(factoryCtor15,"_ZN22CSoundObjectDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory16,(),"_ZL26Set_CLightDescriptorParam1v")
extern "C" void* newFactory16() __asm__("__tlhybrid_local_12__ZL26Set_CLightDescriptorParam1v");
TL_FUNCTION(factoryCtor16,"_ZN16CLightDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory17,(),"_ZL30Set_CRoomPieceDescriptorParam1v")
extern "C" void* newFactory17() __asm__("__tlhybrid_local_12__ZL30Set_CRoomPieceDescriptorParam1v");
TL_FUNCTION(factoryCtor17,"_ZN20CRoomPieceDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory18,(),"_ZL33Set_CGenericModelDescriptorParam1v")
extern "C" void* newFactory18() __asm__("__tlhybrid_local_12__ZL33Set_CGenericModelDescriptorParam1v");
TL_FUNCTION(factoryCtor18,"_ZN23CGenericModelDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory19,(),"_ZL52Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2v")
extern "C" void* newFactory19() __asm__("__tlhybrid_local_12__ZL52Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2v");
TL_FUNCTION(factoryCtor19,"_ZN17CLayoutDescriptorC1ESbIwSt11char_traitsIwESaIwEE13ELAYOUT_TYPES")
TL_ORIGINAL(void*,oldFactory20,(),"_ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2v")
extern "C" void* newFactory20() __asm__("__tlhybrid_local_12__ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2v");
TL_FUNCTION(factoryCtor20,"_ZN17CLayoutDescriptorC1ESbIwSt11char_traitsIwESaIwEE13ELAYOUT_TYPES")
TL_ORIGINAL(void*,oldFactory21,(),"_ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2v")
extern "C" void* newFactory21() __asm__("__tlhybrid_local_12__ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2v");
TL_FUNCTION(factoryCtor21,"_ZN17CLayoutDescriptorC1ESbIwSt11char_traitsIwESaIwEE13ELAYOUT_TYPES")
TL_ORIGINAL(void*,oldFactory22,(),"_ZL46Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2v")
extern "C" void* newFactory22() __asm__("__tlhybrid_local_12__ZL46Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2v");
TL_FUNCTION(factoryCtor22,"_ZN17CLayoutDescriptorC1ESbIwSt11char_traitsIwESaIwEE13ELAYOUT_TYPES")
TL_ORIGINAL(void*,oldFactory23,(),"_ZL32Set_CUnitSpawnerDescriptorParam1v")
extern "C" void* newFactory23() __asm__("__tlhybrid_local_12__ZL32Set_CUnitSpawnerDescriptorParam1v");
TL_FUNCTION(factoryCtor23,"_ZN22CUnitSpawnerDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory24,(),"_ZL32Set_CUnitTriggerDescriptorParam1v")
extern "C" void* newFactory24() __asm__("__tlhybrid_local_12__ZL32Set_CUnitTriggerDescriptorParam1v");
TL_FUNCTION(factoryCtor24,"_ZN22CUnitTriggerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory25,(),"_ZL25Set_CItemDescriptorParam1v")
extern "C" void* newFactory25() __asm__("__tlhybrid_local_12__ZL25Set_CItemDescriptorParam1v");
TL_FUNCTION(factoryCtor25,"_ZN15CItemDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory26,(),"_ZL28Set_CMonsterDescriptorParam1v")
extern "C" void* newFactory26() __asm__("__tlhybrid_local_12__ZL28Set_CMonsterDescriptorParam1v");
TL_FUNCTION(factoryCtor26,"_ZN18CMonsterDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory27,(),"_ZL37Set_CCameraControllerDescriptorParam1v")
extern "C" void* newFactory27() __asm__("__tlhybrid_local_12__ZL37Set_CCameraControllerDescriptorParam1v");
TL_FUNCTION(factoryCtor27,"_ZN27CCameraControllerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory28,(),"_ZL37Set_CPuzzleRandomizerDescriptorParam1v")
extern "C" void* newFactory28() __asm__("__tlhybrid_local_12__ZL37Set_CPuzzleRandomizerDescriptorParam1v");
TL_FUNCTION(factoryCtor28,"_ZN27CPuzzleRandomizerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory29,(),"_ZL33Set_CPropertyNodeDescriptorParam1v")
extern "C" void* newFactory29() __asm__("__tlhybrid_local_12__ZL33Set_CPropertyNodeDescriptorParam1v");
TL_FUNCTION(factoryCtor29,"_ZN23CPropertyNodeDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory30,(),"_ZL32Set_CCameraShakeDescriptorParam1v")
extern "C" void* newFactory30() __asm__("__tlhybrid_local_12__ZL32Set_CCameraShakeDescriptorParam1v");
TL_FUNCTION(factoryCtor30,"_ZN22CCameraShakeDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory31,(),"_ZL38Set_COutputIncrementorDescriptorParam1v")
extern "C" void* newFactory31() __asm__("__tlhybrid_local_12__ZL38Set_COutputIncrementorDescriptorParam1v");
TL_FUNCTION(factoryCtor31,"_ZN28COutputIncrementorDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory32,(),"_ZL31Set_CLogicTimerDescriptorParam1v")
extern "C" void* newFactory32() __asm__("__tlhybrid_local_12__ZL31Set_CLogicTimerDescriptorParam1v");
TL_FUNCTION(factoryCtor32,"_ZN21CLogicTimerDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory33,(),"_ZL29Set_CTeleportDescriptorParam1v")
extern "C" void* newFactory33() __asm__("__tlhybrid_local_12__ZL29Set_CTeleportDescriptorParam1v");
TL_FUNCTION(factoryCtor33,"_ZN19CTeleportDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory34,(),"_ZL27Set_CWarperDescriptorParam1v")
extern "C" void* newFactory34() __asm__("__tlhybrid_local_12__ZL27Set_CWarperDescriptorParam1v");
TL_FUNCTION(factoryCtor34,"_ZN17CWarperDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory35,(),"_ZL33Set_CRandomChoiceDescriptorParam1v")
extern "C" void* newFactory35() __asm__("__tlhybrid_local_12__ZL33Set_CRandomChoiceDescriptorParam1v");
TL_FUNCTION(factoryCtor35,"_ZN23CRandomChoiceDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory36,(),"_ZL28Set_CCounterDescriptorParam1v")
extern "C" void* newFactory36() __asm__("__tlhybrid_local_12__ZL28Set_CCounterDescriptorParam1v");
TL_FUNCTION(factoryCtor36,"_ZN18CCounterDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory37,(),"_ZL31Set_CTriggerBoxDescriptorParam1v")
extern "C" void* newFactory37() __asm__("__tlhybrid_local_12__ZL31Set_CTriggerBoxDescriptorParam1v");
TL_FUNCTION(factoryCtor37,"_ZN21CTriggerBoxDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory38,(),"_ZL34Set_CTriggerSphereDescriptorParam1v")
extern "C" void* newFactory38() __asm__("__tlhybrid_local_12__ZL34Set_CTriggerSphereDescriptorParam1v");
TL_FUNCTION(factoryCtor38,"_ZN24CTriggerSphereDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory39,(),"_ZL31Set_CLogicGroupDescriptorParam1v")
extern "C" void* newFactory39() __asm__("__tlhybrid_local_12__ZL31Set_CLogicGroupDescriptorParam1v");
TL_FUNCTION(factoryCtor39,"_ZN21CLogicGroupDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory40,(),"_ZL29Set_CTimelineDescriptorParam1v")
extern "C" void* newFactory40() __asm__("__tlhybrid_local_12__ZL29Set_CTimelineDescriptorParam1v");
TL_FUNCTION(factoryCtor40,"_ZN19CTimelineDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void*,oldFactory41,(),"_ZL35Set_CSphereColliderDescriptorParam1v")
extern "C" void* newFactory41() __asm__("__tlhybrid_local_12__ZL35Set_CSphereColliderDescriptorParam1v");
TL_FUNCTION(factoryCtor41,"_ZN25CSphereColliderDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory42,(),"_ZL34Set_CPlaneColliderDescriptorParam1v")
extern "C" void* newFactory42() __asm__("__tlhybrid_local_12__ZL34Set_CPlaneColliderDescriptorParam1v");
TL_FUNCTION(factoryCtor42,"_ZN24CPlaneColliderDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory43,(),"_ZL32Set_CBoxColliderDescriptorParam1v")
extern "C" void* newFactory43() __asm__("__tlhybrid_local_12__ZL32Set_CBoxColliderDescriptorParam1v");
TL_FUNCTION(factoryCtor43,"_ZN22CBoxColliderDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory44,(),"_ZL34Set_CColorAffectorDescriptorParam1v")
extern "C" void* newFactory44() __asm__("__tlhybrid_local_12__ZL34Set_CColorAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor44,"_ZN24CColorAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory45,(),"_ZL35Set_CTextureAnimateDescriptorParam1v")
extern "C" void* newFactory45() __asm__("__tlhybrid_local_12__ZL35Set_CTextureAnimateDescriptorParam1v");
TL_FUNCTION(factoryCtor45,"_ZN25CTextureAnimateDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory46,(),"_ZL34Set_CTextureRotateDescriptorParam1v")
extern "C" void* newFactory46() __asm__("__tlhybrid_local_12__ZL34Set_CTextureRotateDescriptorParam1v");
TL_FUNCTION(factoryCtor46,"_ZN24CTextureRotateDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory47,(),"_ZL35Set_CGeometryRotateDescriptorParam1v")
extern "C" void* newFactory47() __asm__("__tlhybrid_local_12__ZL35Set_CGeometryRotateDescriptorParam1v");
TL_FUNCTION(factoryCtor47,"_ZN25CGeometryRotateDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory48,(),"_ZL32Set_CJetAffectorDescriptorParam1v")
extern "C" void* newFactory48() __asm__("__tlhybrid_local_12__ZL32Set_CJetAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor48,"_ZN22CJetAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory49,(),"_ZL34Set_CScaleAffectorDescriptorParam1v")
extern "C" void* newFactory49() __asm__("__tlhybrid_local_12__ZL34Set_CScaleAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor49,"_ZN24CScaleAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory50,(),"_ZL36Set_CGravityAffectorDescriptorParam1v")
extern "C" void* newFactory50() __asm__("__tlhybrid_local_12__ZL36Set_CGravityAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor50,"_ZN26CGravityAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory51,(),"_ZL35Set_CVortexAffectorDescriptorParam1v")
extern "C" void* newFactory51() __asm__("__tlhybrid_local_12__ZL35Set_CVortexAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor51,"_ZN25CVortexAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory52,(),"_ZL38Set_CSineForceAffectorDescriptorParam1v")
extern "C" void* newFactory52() __asm__("__tlhybrid_local_12__ZL38Set_CSineForceAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor52,"_ZN28CSineForceAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory53,(),"_ZL40Set_CLinearForceAffectorDescriptorParam1v")
extern "C" void* newFactory53() __asm__("__tlhybrid_local_12__ZL40Set_CLinearForceAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor53,"_ZN30CLinearForceAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory54,(),"_ZL33Set_CLineAffectorDescriptorParam1v")
extern "C" void* newFactory54() __asm__("__tlhybrid_local_12__ZL33Set_CLineAffectorDescriptorParam1v");
TL_FUNCTION(factoryCtor54,"_ZN23CLineAffectorDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory55,(),"_ZL26Set_CAlignDescriptorParam1v")
extern "C" void* newFactory55() __asm__("__tlhybrid_local_12__ZL26Set_CAlignDescriptorParam1v");
TL_FUNCTION(factoryCtor55,"_ZN16CAlignDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory56,(),"_ZL43Set_CParticleEmitterWrapperDescriptorParam1v")
extern "C" void* newFactory56() __asm__("__tlhybrid_local_12__ZL43Set_CParticleEmitterWrapperDescriptorParam1v");
TL_FUNCTION(factoryCtor56,"_ZN33CParticleEmitterWrapperDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory57,(),"_ZL40Set_CParticleTechWrapperDescriptorParam1v")
extern "C" void* newFactory57() __asm__("__tlhybrid_local_12__ZL40Set_CParticleTechWrapperDescriptorParam1v");
TL_FUNCTION(factoryCtor57,"_ZN30CParticleTechWrapperDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory58,(),"_ZL33Set_CEditorButtonDescriptorParam1v")
extern "C" void* newFactory58() __asm__("__tlhybrid_local_12__ZL33Set_CEditorButtonDescriptorParam1v");
TL_FUNCTION(factoryCtor58,"_ZN23CEditorButtonDescriptorC1Ev")
TL_ORIGINAL(void*,oldFactory59,(),"_ZL32Set_CEditorImageDescriptorParam1v")
extern "C" void* newFactory59() __asm__("__tlhybrid_local_12__ZL32Set_CEditorImageDescriptorParam1v");
TL_FUNCTION(factoryCtor59,"_ZN22CEditorImageDescriptorC1Ev")
namespace {
typedef void* (*Factory)();
struct Spec { Factory original, candidate; char *ctorOriginal,*ctorLinked; unsigned size, signature; const wchar_t *name,*category,*arg0,*arg1,*arg2; ELAYOUT_TYPES type; };
const Spec specs[] = {
 {oldFactory0,newFactory0,factoryCtor0_original,factoryCtor0_linked,368,1,L"Waypoint Activator",L"Logic",L"Waypoint Activator",L"Activates waypoint for this level",L"waypointactivator",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory1,newFactory1,factoryCtor1_original,factoryCtor1_linked,368,1,L"Dungeon Object",L"Logic",L"Dungeon Object",L"Performs operations on a dungeon",L"warper",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory2,newFactory2,factoryCtor2_original,factoryCtor2_linked,368,1,L"Money Taker",L"Logic",L"Money Taker",L"Attempts to take the set amount of money from the player",L"money",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory3,newFactory3,factoryCtor3_original,factoryCtor3_linked,368,1,L"Cinematic",L"Logic",L"Cinematic",L"Controls playing a cinematic",L"cinematic",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory4,newFactory4,factoryCtor4_original,factoryCtor4_linked,368,0,L"Damage Shape",L"Logic",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory5,newFactory5,factoryCtor5_original,factoryCtor5_linked,368,1,L"Skip Cutscene",L"Logic",L"Skip Cutscene",L"watches the esc key to skip cut scene",L"skipcutscene",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory6,newFactory6,factoryCtor6_original,factoryCtor6_linked,368,1,L"Animation Controller",L"Logic",L"Animation Controller",L"Animation Controller",L"clapperboard",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory7,newFactory7,factoryCtor7_original,factoryCtor7_linked,368,1,L"Path Node",L"Logic",L"Path Node",L"Path Node",L"effectpercent",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory8,newFactory8,factoryCtor8_original,factoryCtor8_linked,368,1,L"Pathing",L"Logic",L"Pathing",L"Pathing",L"pathing",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory9,newFactory9,factoryCtor9_original,factoryCtor9_linked,368,1,L"Skill Controller",L"Logic",L"Skill Controller",L"Skill controller",L"skill",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory10,newFactory10,factoryCtor10_original,factoryCtor10_linked,368,1,L"Quest Controller",L"Logic",L"Quest Controller",L"Quest controller",L"exclamation",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory11,newFactory11,factoryCtor11_original,factoryCtor11_linked,368,1,L"Game State Controller",L"Logic",L"Game State Controller",L"Game state controller",L"gear",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory12,newFactory12,factoryCtor12_original,factoryCtor12_linked,368,0,L"Group",L"",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory13,newFactory13,factoryCtor13_original,factoryCtor13_linked,368,0,L"Missile",L"Missiles",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory14,newFactory14,factoryCtor14_original,factoryCtor14_linked,368,1,L"Music",L"Sounds",L"Music Object",L"Stores a music track that can be triggered",L"sound",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory15,newFactory15,factoryCtor15_original,factoryCtor15_linked,368,0,L"Sound",L"Sounds",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory16,newFactory16,factoryCtor16_original,factoryCtor16_linked,368,0,L"Light",L"Building Blocks",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory17,newFactory17,factoryCtor17_original,factoryCtor17_linked,368,0,L"Room Piece",L"Building Blocks",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory18,newFactory18,factoryCtor18_original,factoryCtor18_linked,368,0,L"Generic Model",L"Building Blocks",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory19,newFactory19,factoryCtor19_original,factoryCtor19_linked,376,2,L"Layout Link Trigger",L"Building Blocks",L"Layout Link Trigger",0,0,static_cast<ELAYOUT_TYPES>(3)},
 {oldFactory20,newFactory20,factoryCtor20_original,factoryCtor20_linked,376,2,L"Layout Link Timeline",L"Building Blocks",L"Layout Link Timeline",0,0,static_cast<ELAYOUT_TYPES>(2)},
 {oldFactory21,newFactory21,factoryCtor21_original,factoryCtor21_linked,376,2,L"Layout Link Particle",L"Building Blocks",L"Layout Link Particle",0,0,static_cast<ELAYOUT_TYPES>(1)},
 {oldFactory22,newFactory22,factoryCtor22_original,factoryCtor22_linked,376,2,L"Layout Link",L"Building Blocks",L"Layout Link",0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory23,newFactory23,factoryCtor23_original,factoryCtor23_linked,368,0,L"Unit Spawner",L"Building Blocks",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory24,newFactory24,factoryCtor24_original,factoryCtor24_linked,368,1,L"Unit Trigger",L"Building Blocks",L"Unit Trigger",L"Trigger for logic",L"chest",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory25,newFactory25,factoryCtor25_original,factoryCtor25_linked,368,1,L"Item",L"Building Blocks",L"Item",L"Item in the level",L"remove",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory26,newFactory26,factoryCtor26_original,factoryCtor26_linked,368,1,L"Monster",L"Building Blocks",L"Monster",L"Monster in the level",L"monster",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory27,newFactory27,factoryCtor27_original,factoryCtor27_linked,368,1,L"Camera Controller",L"Logic",L"Camera Controller",L"Interactive Object",L"camera",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory28,newFactory28,factoryCtor28_original,factoryCtor28_linked,368,1,L"Puzzle Input",L"Logic",L"Puzzle Input",L"Puzzle Counter",L"die",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory29,newFactory29,factoryCtor29_original,factoryCtor29_linked,368,0,L"Property Node",L"Logic",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory30,newFactory30,factoryCtor30_original,factoryCtor30_linked,368,0,L"Camera Shake",L"Logic",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory31,newFactory31,factoryCtor31_original,factoryCtor31_linked,368,1,L"Output Incrementor",L"Logic",L"Output Incrementor",L"Increments output",L"outputcounter",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory32,newFactory32,factoryCtor32_original,factoryCtor32_linked,368,1,L"Timer",L"Logic",L"Timer",L"Timer ticks down when enabled",L"clock",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory33,newFactory33,factoryCtor33_original,factoryCtor33_linked,368,1,L"Teleport",L"Logic",L"Teleport",L"Teleports player inside level",L"teleport",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory34,newFactory34,factoryCtor34_original,factoryCtor34_linked,368,1,L"Warper",L"Logic",L"Warper",L"Warps player to another level",L"warper",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory35,newFactory35,factoryCtor35_original,factoryCtor35_linked,368,1,L"Random Choice",L"Logic",L"Random Choice",L"Random choice of outputs",L"question",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory36,newFactory36,factoryCtor36_original,factoryCtor36_linked,368,1,L"Counter",L"Logic",L"Counter",L"Counts up and then broadcasts emitters",L"counter",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory37,newFactory37,factoryCtor37_original,factoryCtor37_linked,368,1,L"Player Box Trigger",L"Logic",L"Player Box Trigger",L"Trigger for logic",L"boxtrigger",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory38,newFactory38,factoryCtor38_original,factoryCtor38_linked,368,1,L"Player Sphere Trigger",L"Logic",L"Player Sphere Trigger",L"Trigger for logic",L"playersphere",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory39,newFactory39,factoryCtor39_original,factoryCtor39_linked,368,1,L"Logic Group",L"Logic",L"Logic Group",L"Double click to bring up logic group",L"logicgroup",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory40,newFactory40,factoryCtor40_original,factoryCtor40_linked,368,1,L"Timeline",L"Logic",L"Timeline",L"Double click to bring up timeline",L"timeline",static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory41,newFactory41,factoryCtor41_original,factoryCtor41_linked,368,0,L"Sphere Collision",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory42,newFactory42,factoryCtor42_original,factoryCtor42_linked,368,0,L"Plane Collision",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory43,newFactory43,factoryCtor43_original,factoryCtor43_linked,368,0,L"Box Collision",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory44,newFactory44,factoryCtor44_original,factoryCtor44_linked,368,0,L"Color",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory45,newFactory45,factoryCtor45_original,factoryCtor45_linked,368,0,L"Texture Animation",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory46,newFactory46,factoryCtor46_original,factoryCtor46_linked,368,0,L"Texture Rotate",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory47,newFactory47,factoryCtor47_original,factoryCtor47_linked,368,0,L"Geometry Rotator",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory48,newFactory48,factoryCtor48_original,factoryCtor48_linked,368,0,L"Jet",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory49,newFactory49,factoryCtor49_original,factoryCtor49_linked,368,0,L"Scale",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory50,newFactory50,factoryCtor50_original,factoryCtor50_linked,368,0,L"Gravity Well",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory51,newFactory51,factoryCtor51_original,factoryCtor51_linked,368,0,L"Vortext",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory52,newFactory52,factoryCtor52_original,factoryCtor52_linked,368,0,L"Sine Force",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory53,newFactory53,factoryCtor53_original,factoryCtor53_linked,368,0,L"Linear Force",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory54,newFactory54,factoryCtor54_original,factoryCtor54_linked,368,0,L"Line",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory55,newFactory55,factoryCtor55_original,factoryCtor55_linked,368,0,L"Align",L"Affectors",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory56,newFactory56,factoryCtor56_original,factoryCtor56_linked,368,0,L"Emitter",L"",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory57,newFactory57,factoryCtor57_original,factoryCtor57_linked,368,0,L"Particle",L"Particles",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory58,newFactory58,factoryCtor58_original,factoryCtor58_linked,368,0,L"Button",L"UI",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
 {oldFactory59,newFactory59,factoryCtor59_original,factoryCtor59_linked,368,0,L"Image",L"UI",0,0,0,static_cast<ELAYOUT_TYPES>(0)},
};
struct Case { unsigned which,pattern,text,fault; };
struct Stop { unsigned stage; explicit Stop(unsigned value):stage(value){} };
const Case* current; const Spec* spec; autotest::Capture* capture;
uint64_t storage[160]; void* object; unsigned allocations,constructors,releases; bool stringsLive;
std::wstring initialName,initialCategory;
void number(unsigned value) { capture->add(&value,sizeof(value)); }
void require(bool value) { if(!value)capture->issue=autotest::Capture::InvalidReport; }
std::wstring* nameSlot() { return reinterpret_cast<std::wstring*>(static_cast<char*>(object)+0x58); }
std::wstring* categorySlot() { return reinterpret_cast<std::wstring*>(static_cast<char*>(object)+0x70); }
void* allocate(size_t bytes,const char* file,int line,const char* function)
{
    ++allocations;number(1);number(bytes);require(bytes==spec->size);require(!file&&!line&&!function);
    if(current->fault==1)throw Stop(1);
    return object;
}
void release(void* p) { ++releases;number(3);require(p==object); }
void construct(void* p)
{
    ++constructors;number(2);require(p==object);require(allocations==1);
    if(current->fault==2)throw Stop(2);
    // ASM + the shared class layout identify the two assigned std::wstring slots.
    new (nameSlot()) std::wstring(initialName);
    new (categorySlot()) std::wstring(initialCategory);
    if(current->text==3) { (*nameSlot())[0]=L'!'; (*categorySlot())[0]=L'?'; }
    stringsLive=true;
}
void noArguments(void* p) { require(spec->signature==0);construct(p); }
void threeArguments(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c)
{
    require(spec->signature==1);require(a&&b&&c);
    if(a&&b&&c) { capture->addText(std::wstring(a));capture->addText(std::wstring(b));capture->addText(std::wstring(c));
        require(std::wstring(a)==spec->arg0&&std::wstring(b)==spec->arg1&&std::wstring(c)==spec->arg2); }
    construct(p);
}
void layoutArguments(void* p,std::wstring name,ELAYOUT_TYPES type)
{
    require(spec->signature==2);capture->addText(name);number(type);require(name==spec->arg0&&type==spec->type);construct(p);
}
void side(void* data,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(data);spec=&specs[current->which];capture=&out;allocations=constructors=releases=0;stringsLive=false;
    static const unsigned char patterns[]={0,1,0x55,0xaa,0xfe,0xff};
    std::memset(storage,patterns[current->pattern],sizeof(storage));object=reinterpret_cast<char*>(storage)+16;
    initialName=current->text==0?L"":current->text==1?L"old name":current->text==2?L"\u03a9\u4e2d":std::wstring(257,L'N');
    initialCategory=current->text==0?L"":current->text==1?L"old category":current->text==2?L"\u0416\u00e9":std::wstring(263,L'C');
    detour::Set d;d.redirect(factoryAllocate,factoryAllocate,&allocate);d.redirect(factoryRelease,factoryRelease,&release);
    if(spec->signature==0)d.redirect(spec->ctorOriginal,spec->ctorLinked,&noArguments);
    else if(spec->signature==1)d.redirect(spec->ctorOriginal,spec->ctorLinked,&threeArguments);
    else d.redirect(spec->ctorOriginal,spec->ctorLinked,&layoutArguments);
    if(d.failed()) { require(false);return; }
    Factory fn=ours?spec->candidate:spec->original;void* result=0;unsigned stopped=0;
    if(!autotest::beginInvocation(out,fn))return;
    try { result=fn();out.callCompleted=1; } catch(const Stop& stop) { stopped=stop.stage; } catch(...) { require(false); }
    number(stopped);number(allocations);number(constructors);number(releases);
    require(allocations==1);require(constructors==(current->fault==1?0u:1u));require(releases==(current->fault==2?1u:0u));require(stopped==current->fault);
    if(!current->fault) {
        require(out.callCompleted==1&&result==object&&stringsLive);
        capture->addText(*nameSlot());capture->addText(*categorySlot());
        require(*nameSlot()==spec->name&&*categorySlot()==spec->category);
    } else require(!out.callCompleted&&!result&&!stringsLive);
    unsigned char snapshot[sizeof(storage)];std::memcpy(snapshot,storage,sizeof(storage));
    if(stringsLive) { std::memset(snapshot+16+0x58,0,sizeof(std::wstring));std::memset(snapshot+16+0x70,0,sizeof(std::wstring)); }
    for(unsigned i=0;i<sizeof(snapshot);++i) {
        bool slot=stringsLive&&((i>=16+0x58&&i<16+0x58+sizeof(std::wstring))||(i>=16+0x70&&i<16+0x70+sizeof(std::wstring)));
        require(snapshot[i]==(slot?0:patterns[current->pattern]));
    }
    capture->add(snapshot,sizeof(snapshot));
    if(stringsLive) { nameSlot()->~basic_string();categorySlot()->~basic_string(); }
}
void before(void* p,autotest::Capture& c) { side(p,c,false); }
void after(void* p,autotest::Capture& c) { side(p,c,true); }
int run(const tlhybrid_host* host,unsigned which,const char* name)
{
    autotest::Coverage coverage(name,reinterpret_cast<uintptr_t>(specs[which].original));
    for(unsigned pattern=0;pattern<6;++pattern)for(unsigned text=0;text<4;++text) {
        Case c={which,pattern,text,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        if(coverage.observe(host,a,b)) { host->log("    factory %u pattern %u text %u status %d/%d issue %u/%u\n",which,pattern,text,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1; }
    }
    coverage.report(host);return coverage.completed==24?0:1;
}
}
TL_TEST(descriptor_factory_5c93e0) { return run(host,0,"descriptor_factory_5c93e0"); }
TL_TEST(descriptor_factory_5c9520) { return run(host,1,"descriptor_factory_5c9520"); }
TL_TEST(descriptor_factory_5c9660) { return run(host,2,"descriptor_factory_5c9660"); }
TL_TEST(descriptor_factory_5c97a0) { return run(host,3,"descriptor_factory_5c97a0"); }
TL_TEST(descriptor_factory_5c98e0) { return run(host,4,"descriptor_factory_5c98e0"); }
TL_TEST(descriptor_factory_5c9a10) { return run(host,5,"descriptor_factory_5c9a10"); }
TL_TEST(descriptor_factory_5c9b50) { return run(host,6,"descriptor_factory_5c9b50"); }
TL_TEST(descriptor_factory_5c9c90) { return run(host,7,"descriptor_factory_5c9c90"); }
TL_TEST(descriptor_factory_5c9dd0) { return run(host,8,"descriptor_factory_5c9dd0"); }
TL_TEST(descriptor_factory_5c9f10) { return run(host,9,"descriptor_factory_5c9f10"); }
TL_TEST(descriptor_factory_5ca050) { return run(host,10,"descriptor_factory_5ca050"); }
TL_TEST(descriptor_factory_5ca190) { return run(host,11,"descriptor_factory_5ca190"); }
TL_TEST(descriptor_factory_5ca2d0) { return run(host,12,"descriptor_factory_5ca2d0"); }
TL_TEST(descriptor_factory_5ca400) { return run(host,13,"descriptor_factory_5ca400"); }
TL_TEST(descriptor_factory_5ca530) { return run(host,14,"descriptor_factory_5ca530"); }
TL_TEST(descriptor_factory_5ca670) { return run(host,15,"descriptor_factory_5ca670"); }
TL_TEST(descriptor_factory_5ca7a0) { return run(host,16,"descriptor_factory_5ca7a0"); }
TL_TEST(descriptor_factory_5ca8d0) { return run(host,17,"descriptor_factory_5ca8d0"); }
TL_TEST(descriptor_factory_5caa00) { return run(host,18,"descriptor_factory_5caa00"); }
TL_TEST(descriptor_factory_5cab30) { return run(host,19,"descriptor_factory_5cab30"); }
TL_TEST(descriptor_factory_5cace0) { return run(host,20,"descriptor_factory_5cace0"); }
TL_TEST(descriptor_factory_5cae90) { return run(host,21,"descriptor_factory_5cae90"); }
TL_TEST(descriptor_factory_5cb040) { return run(host,22,"descriptor_factory_5cb040"); }
TL_TEST(descriptor_factory_5cb1f0) { return run(host,23,"descriptor_factory_5cb1f0"); }
TL_TEST(descriptor_factory_5cb320) { return run(host,24,"descriptor_factory_5cb320"); }
TL_TEST(descriptor_factory_5cb460) { return run(host,25,"descriptor_factory_5cb460"); }
TL_TEST(descriptor_factory_5cb5a0) { return run(host,26,"descriptor_factory_5cb5a0"); }
TL_TEST(descriptor_factory_5cb6e0) { return run(host,27,"descriptor_factory_5cb6e0"); }
TL_TEST(descriptor_factory_5cb820) { return run(host,28,"descriptor_factory_5cb820"); }
TL_TEST(descriptor_factory_5cb960) { return run(host,29,"descriptor_factory_5cb960"); }
TL_TEST(descriptor_factory_5cba90) { return run(host,30,"descriptor_factory_5cba90"); }
TL_TEST(descriptor_factory_5cbbc0) { return run(host,31,"descriptor_factory_5cbbc0"); }
TL_TEST(descriptor_factory_5cbd00) { return run(host,32,"descriptor_factory_5cbd00"); }
TL_TEST(descriptor_factory_5cbe40) { return run(host,33,"descriptor_factory_5cbe40"); }
TL_TEST(descriptor_factory_5cbf80) { return run(host,34,"descriptor_factory_5cbf80"); }
TL_TEST(descriptor_factory_5cc0c0) { return run(host,35,"descriptor_factory_5cc0c0"); }
TL_TEST(descriptor_factory_5cc200) { return run(host,36,"descriptor_factory_5cc200"); }
TL_TEST(descriptor_factory_5cc340) { return run(host,37,"descriptor_factory_5cc340"); }
TL_TEST(descriptor_factory_5cc480) { return run(host,38,"descriptor_factory_5cc480"); }
TL_TEST(descriptor_factory_5cc5c0) { return run(host,39,"descriptor_factory_5cc5c0"); }
TL_TEST(descriptor_factory_5cc700) { return run(host,40,"descriptor_factory_5cc700"); }
TL_TEST(descriptor_factory_5cc840) { return run(host,41,"descriptor_factory_5cc840"); }
TL_TEST(descriptor_factory_5cc970) { return run(host,42,"descriptor_factory_5cc970"); }
TL_TEST(descriptor_factory_5ccaa0) { return run(host,43,"descriptor_factory_5ccaa0"); }
TL_TEST(descriptor_factory_5ccbd0) { return run(host,44,"descriptor_factory_5ccbd0"); }
TL_TEST(descriptor_factory_5ccd00) { return run(host,45,"descriptor_factory_5ccd00"); }
TL_TEST(descriptor_factory_5cce30) { return run(host,46,"descriptor_factory_5cce30"); }
TL_TEST(descriptor_factory_5ccf60) { return run(host,47,"descriptor_factory_5ccf60"); }
TL_TEST(descriptor_factory_5cd090) { return run(host,48,"descriptor_factory_5cd090"); }
TL_TEST(descriptor_factory_5cd1c0) { return run(host,49,"descriptor_factory_5cd1c0"); }
TL_TEST(descriptor_factory_5cd2f0) { return run(host,50,"descriptor_factory_5cd2f0"); }
TL_TEST(descriptor_factory_5cd420) { return run(host,51,"descriptor_factory_5cd420"); }
TL_TEST(descriptor_factory_5cd550) { return run(host,52,"descriptor_factory_5cd550"); }
TL_TEST(descriptor_factory_5cd680) { return run(host,53,"descriptor_factory_5cd680"); }
TL_TEST(descriptor_factory_5cd7b0) { return run(host,54,"descriptor_factory_5cd7b0"); }
TL_TEST(descriptor_factory_5cd8e0) { return run(host,55,"descriptor_factory_5cd8e0"); }
TL_TEST(descriptor_factory_5cda10) { return run(host,56,"descriptor_factory_5cda10"); }
TL_TEST(descriptor_factory_5cdb40) { return run(host,57,"descriptor_factory_5cdb40"); }
TL_TEST(descriptor_factory_5cdc70) { return run(host,58,"descriptor_factory_5cdc70"); }
TL_TEST(descriptor_factory_5cdda0) { return run(host,59,"descriptor_factory_5cdda0"); }
TL_TEST(descriptor_factory_expected_exceptions)
{
    unsigned completed=0;
    for(unsigned which=0;which<60;++which)for(unsigned fault=1;fault<=2;++fault) {
        Case c={which,which%6,which%4,fault};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        if(!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||a.capture.issue||b.capture.issue||!a.capture.callStarted||!b.capture.callStarted||a.capture.callCompleted||b.capture.callCompleted||a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length)) {
            host->log("    factory expected exception %u/%u mismatch status %d/%d issue %u/%u\n",which,fault,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);return 1;
        }
        ++completed;
    }
    host->log("    EXPECTED FACTORY EXCEPTIONS: %u matching unwinds, excluded from normal pair coverage\n",completed);return completed==120?0:1;
}
