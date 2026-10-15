#include <cstring>
#include <string>
#include <stdint.h>
#define protected public
#include "Descriptor.h"
#undef protected
#include "AutoTest.h"
#include "Detour.h"
#include "DescriptorBulkCallbackIdentity.h"

TL_FUNCTION(bulkBase0,"_ZN21CBaseObjectDescriptorC1EPKwS1_S1_")
TL_FUNCTION(bulkBase1,"_ZN29CPositionableObjectDescriptorC1EPKwS1_S1_bbbbb")
TL_FUNCTION(bulkBase2,"_ZN19CAffectorDescriptorC1EPKwS1_S1_")
TL_FUNCTION(bulkBase3,"_ZN19CColliderDescriptorC1EPKw")
TL_FUNCTION(bulkBase4,"_ZN24CForceAffectorDescriptorC1EPKwS1_S1_")
TL_FUNCTION(bulkBase5,"_ZN18CTriggerDescriptorC1EPKwS1_S1_")
TL_FUNCTION(bulkBase6,"_ZN16CShapeDescriptorC1EPKwS1_S1_bbb")
TL_FUNCTION(bulkBase7,"_ZN11CDescriptorC1Ei")
TL_ORIGINAL(void,bulkOld0,(void*),"_ZN16CAlignDescriptorC1Ev")
extern "C" void bulkNew0(void*) __asm__("_ZN16CAlignDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld1,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN26CAnimationPlayerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew1(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN26CAnimationPlayerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld2,(void*),"_ZN22CBoxColliderDescriptorC1Ev")
extern "C" void bulkNew2(void*) __asm__("_ZN22CBoxColliderDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld3,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN27CCameraControllerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew3(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN27CCameraControllerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld4,(void*),"_ZN22CCameraShakeDescriptorC1Ev")
extern "C" void bulkNew4(void*) __asm__("_ZN22CCameraShakeDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld5,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN20CCinematicDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew5(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN20CCinematicDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld6,(void*,wchar_t const*),"_ZN19CColliderDescriptorC1EPKw")
extern "C" void bulkNew6(void*,wchar_t const*) __asm__("_ZN19CColliderDescriptorC1EPKw");
TL_ORIGINAL(void,bulkOld7,(void*),"_ZN27CCollisionAvoiderDescriptorC1Ev")
extern "C" void bulkNew7(void*) __asm__("_ZN27CCollisionAvoiderDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld8,(void*),"_ZN25CCollisionShapeDescriptorC1Ev")
extern "C" void bulkNew8(void*) __asm__("_ZN25CCollisionShapeDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld9,(void*),"_ZN24CColorAffectorDescriptorC1Ev")
extern "C" void bulkNew9(void*) __asm__("_ZN24CColorAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld10,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN18CCounterDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew10(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN18CCounterDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld11,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN23CSkipCutsceneDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew11(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN23CSkipCutsceneDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld12,(void*),"_ZN22CDamageShapeDescriptorC1Ev")
extern "C" void bulkNew12(void*) __asm__("_ZN22CDamageShapeDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld13,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN24CDungeonObjectDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew13(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN24CDungeonObjectDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld14,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN24CForceAffectorDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew14(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN24CForceAffectorDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld15,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN30CGameStateControllerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew15(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN30CGameStateControllerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld16,(void*),"_ZN23CGenericModelDescriptorC1Ev")
extern "C" void bulkNew16(void*) __asm__("_ZN23CGenericModelDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld17,(void*),"_ZN25CGeometryRotateDescriptorC1Ev")
extern "C" void bulkNew17(void*) __asm__("_ZN25CGeometryRotateDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld18,(void*),"_ZN26CGravityAffectorDescriptorC1Ev")
extern "C" void bulkNew18(void*) __asm__("_ZN26CGravityAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld19,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN22CInteractiveDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew19(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN22CInteractiveDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld20,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN15CItemDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew20(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN15CItemDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld21,(void*),"_ZN22CJetAffectorDescriptorC1Ev")
extern "C" void bulkNew21(void*) __asm__("_ZN22CJetAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld22,(void*),"_ZN16CLightDescriptorC1Ev")
extern "C" void bulkNew22(void*) __asm__("_ZN16CLightDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld23,(void*),"_ZN23CLineAffectorDescriptorC1Ev")
extern "C" void bulkNew23(void*) __asm__("_ZN23CLineAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld24,(void*),"_ZN30CLinearForceAffectorDescriptorC1Ev")
extern "C" void bulkNew24(void*) __asm__("_ZN30CLinearForceAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld25,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN21CLogicTimerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew25(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN21CLogicTimerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld26,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN21CMoneyTakerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew26(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN21CMoneyTakerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld27,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN18CMonsterDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew27(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN18CMonsterDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld28,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN22CMusicObjectDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew28(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN22CMusicObjectDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld29,(void*),"_ZN26CParticleWrapperDescriptorC1Ev")
extern "C" void bulkNew29(void*) __asm__("_ZN26CParticleWrapperDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld30,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN25CPathControllerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew30(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN25CPathControllerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld31,(void*),"_ZN24CPlaneColliderDescriptorC1Ev")
extern "C" void bulkNew31(void*) __asm__("_ZN24CPlaneColliderDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld32,(void*),"_ZN23CPropertyNodeDescriptorC1Ev")
extern "C" void bulkNew32(void*) __asm__("_ZN23CPropertyNodeDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld33,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN27CPuzzleRandomizerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew33(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN27CPuzzleRandomizerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld34,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN26CQuestControllerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew34(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN26CQuestControllerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld35,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN23CRandomChoiceDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew35(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN23CRandomChoiceDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld36,(void*),"_ZN22CRandomGroupDescriptorC1Ev")
extern "C" void bulkNew36(void*) __asm__("_ZN22CRandomGroupDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld37,(void*),"_ZN15CRoomDescriptorC1Ev")
extern "C" void bulkNew37(void*) __asm__("_ZN15CRoomDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld38,(void*),"_ZN20CRoomPieceDescriptorC1Ev")
extern "C" void bulkNew38(void*) __asm__("_ZN20CRoomPieceDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld39,(void*),"_ZN24CScaleAffectorDescriptorC1Ev")
extern "C" void bulkNew39(void*) __asm__("_ZN24CScaleAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld40,(void*),"_ZN28CSineForceAffectorDescriptorC1Ev")
extern "C" void bulkNew40(void*) __asm__("_ZN28CSineForceAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld41,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN26CSkillControllerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew41(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN26CSkillControllerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld42,(void*),"_ZN22CSoundObjectDescriptorC1Ev")
extern "C" void bulkNew42(void*) __asm__("_ZN22CSoundObjectDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld43,(void*),"_ZN25CSphereColliderDescriptorC1Ev")
extern "C" void bulkNew43(void*) __asm__("_ZN25CSphereColliderDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld44,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN19CTeleportDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew44(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN19CTeleportDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld45,(void*),"_ZN25CTextureAnimateDescriptorC1Ev")
extern "C" void bulkNew45(void*) __asm__("_ZN25CTextureAnimateDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld46,(void*),"_ZN24CTextureRotateDescriptorC1Ev")
extern "C" void bulkNew46(void*) __asm__("_ZN24CTextureRotateDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld47,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN21CTriggerBoxDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew47(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN21CTriggerBoxDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld48,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN18CTriggerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew48(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN18CTriggerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld49,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN24CTriggerSphereDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew49(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN24CTriggerSphereDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld50,(void*),"_ZN22CUnitSpawnerDescriptorC1Ev")
extern "C" void bulkNew50(void*) __asm__("_ZN22CUnitSpawnerDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld51,(void*),"_ZN25CVortexAffectorDescriptorC1Ev")
extern "C" void bulkNew51(void*) __asm__("_ZN25CVortexAffectorDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld52,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN17CWarperDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew52(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN17CWarperDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld53,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN21CBaseObjectDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew53(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN21CBaseObjectDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld54,(void*,wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool, bool, bool),"_ZN29CPositionableObjectDescriptorC1EPKwS1_S1_bbbbb")
extern "C" void bulkNew54(void*,wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool, bool, bool) __asm__("_ZN29CPositionableObjectDescriptorC1EPKwS1_S1_bbbbb");
TL_ORIGINAL(void,bulkOld55,(void*,wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool),"_ZN16CShapeDescriptorC1EPKwS1_S1_bbb")
extern "C" void bulkNew55(void*,wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool) __asm__("_ZN16CShapeDescriptorC1EPKwS1_S1_bbb");
TL_ORIGINAL(void,bulkOld56,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN22CUnitTriggerDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew56(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN22CUnitTriggerDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld57,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN19CAffectorDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew57(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN19CAffectorDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld58,(void*),"_ZN33CParticleEmitterWrapperDescriptorC1Ev")
extern "C" void bulkNew58(void*) __asm__("_ZN33CParticleEmitterWrapperDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld59,(void*),"_ZN30CParticleTechWrapperDescriptorC1Ev")
extern "C" void bulkNew59(void*) __asm__("_ZN30CParticleTechWrapperDescriptorC1Ev");
TL_ORIGINAL(void,bulkOld60,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN21CLogicGroupDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew60(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN21CLogicGroupDescriptorC1EPKwS1_S1_");
TL_ORIGINAL(void,bulkOld61,(void*,wchar_t const*, wchar_t const*, wchar_t const*),"_ZN19CTimelineDescriptorC1EPKwS1_S1_")
extern "C" void bulkNew61(void*,wchar_t const*, wchar_t const*, wchar_t const*) __asm__("_ZN19CTimelineDescriptorC1EPKwS1_S1_");
TL_FUNCTION(bulkProperty,"_ZN11CDescriptor11AddPropertyESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_15EVARIABLE_TYPESi")
TL_FUNCTION(bulkInterpreted,"_ZN11CDescriptor35AddPropertyWithInterpreterFunctionsESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_PFjP12CEditorSceneP17CEditorBaseObjectRKS3_S4_EPFS3_S6_S8_jS4_ES4_15EVARIABLE_TYPESi")
TL_FUNCTION(bulkInput,"_ZN11CDescriptor13AddInputLogicE13EINPUT_EVENTS")
TL_FUNCTION(bulkOutput,"_ZN11CDescriptor14AddOutputLogicE14EOUTPUT_EVENTS")
TL_FUNCTION(bulkLink,"_ZN11CDescriptor12LinkPropertyEjj")
TL_FUNCTION(bulkTriggerPorts,"_ZN22CUnitTriggerDescriptor19AddInputsAndOutputsEP11CDescriptor")
namespace {
struct BulkCase { unsigned kind, flags, text, returns, fill, options; };
autotest::Capture* bulkCapture;
const BulkCase* bulkCase;
CDescriptor* bulkDescriptor;
unsigned bulkCalls, bulkBaseCalls;
void number(unsigned value) { bulkCapture->add(&value,sizeof(value)); }
void identity(void* p) { uintptr_t value=bulkCallbackIdentity(p); bulkCapture->add(&value,sizeof(value)); }
unsigned returned() { ++bulkCalls; return bulkCase->returns ? 0xffffffffU-bulkCalls : bulkCalls; }
void baseText(void* p,const wchar_t* name,const wchar_t* group,const wchar_t* description) {
    ++bulkBaseCalls; number(p==bulkDescriptor);
    bulkCapture->addText(std::wstring(name)); bulkCapture->addText(std::wstring(group));
    bulkCapture->addText(std::wstring(description)); bulkDescriptor->m_iFlags=bulkCase->flags;
}
void base0(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c) { number(10);baseText(p,a,b,c); }
void base1(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c,bool d,bool e,bool f,bool g,bool h) {
 number(11);baseText(p,a,b,c);number(d);number(e);number(f);number(g);number(h);
 if(bulkCase->kind>=57 && bulkCase->kind<=59) {
  new (&bulkDescriptor->m_ParentFilters) TArrayList<std::wstring>(bulkCase->returns?3:1);
  for(unsigned i=0;i<bulkCase->fill;++i)bulkDescriptor->m_ParentFilters.add(i?L"initial two":L"initial one");
 }
}
void base2(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c) { number(12);baseText(p,a,b,c); }
void base3(void* p,const wchar_t* a) { number(13);++bulkBaseCalls;number(p==bulkDescriptor);bulkCapture->addText(std::wstring(a));bulkDescriptor->m_iFlags=bulkCase->flags; }
void base4(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c) { number(14);baseText(p,a,b,c); }
void base5(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c) { number(15);baseText(p,a,b,c); }
void base6(void* p,const wchar_t* a,const wchar_t* b,const wchar_t* c,bool d,bool e,bool f) {
 number(16);baseText(p,a,b,c);number(d);number(e);number(f);
}
void base7(void* p,int flags) {
 number(17);++bulkBaseCalls;number(p==bulkDescriptor);number(flags);
 new (&bulkDescriptor->m_sName) std::wstring(L"initial name");
 new (&bulkDescriptor->m_sDescription) std::wstring(L"initial description");
 new (&bulkDescriptor->m_sIcon) std::wstring(L"initial icon");
 new (&bulkDescriptor->m_sMenuCategory) std::wstring(L"initial menu category");
 typedef std::map<std::wstring,unsigned int> IDs;
 typedef std::map<CEditorBaseObject*,TArrayList<CLogicObject*>*> Outputs;
 new (&bulkDescriptor->m_PropertyIDs) IDs();
 new (&bulkDescriptor->m_OutputLogicObjects) Outputs();
 new (&bulkDescriptor->m_Properties) TArrayList<CDescriptorProp*>();
 new (&bulkDescriptor->m_DefaultProperties) TArrayList<CDescriptorProp*>();
 new (&bulkDescriptor->m_Objects) TArrayList<CEditorBaseObject*>();
 new (&bulkDescriptor->m_ParentFilters) TArrayList<std::wstring>();
 new (&bulkDescriptor->m_InputLogicWrappers) TArrayList<CLogicWrapper*>();
 new (&bulkDescriptor->m_OutputLogicWrappers) TArrayList<CLogicWrapper*>();
 bulkDescriptor->m_iFlags=bulkCase->flags;
}
unsigned property(CDescriptor* p,std::wstring category,std::wstring name,std::wstring description,void* setter,void* getter,EVARIABLE_TYPES type,int flags) {
 number(20);number(p==bulkDescriptor);bulkCapture->addText(category);bulkCapture->addText(name);bulkCapture->addText(description);
 identity(setter);identity(getter);number(type);number(flags);number(bulkDescriptor->m_iFlags);return returned();
}
unsigned interpreted(CDescriptor* p,std::wstring category,std::wstring name,std::wstring description,void* setter,void* getter,PropertyStringToIndexFunction from,PropertyIndexToStringFunction to,void* user,EVARIABLE_TYPES type,int flags) {
 number(21);number(p==bulkDescriptor);bulkCapture->addText(category);bulkCapture->addText(name);bulkCapture->addText(description);
 identity(setter);identity(getter);identity((void*)from);identity((void*)to);identity(user);number(type);number(flags);number(bulkDescriptor->m_iFlags);return returned();
}
unsigned addInput(CDescriptor* p,EINPUT_EVENTS event) { number(22);number(p==bulkDescriptor);number(event);number(bulkDescriptor->m_iFlags);return returned(); }
unsigned addOutput(CDescriptor* p,EOUTPUT_EVENTS event) { number(23);number(p==bulkDescriptor);number(event);number(bulkDescriptor->m_iFlags);return returned(); }
void link(CDescriptor* p,unsigned first,unsigned second) { number(24);number(p==bulkDescriptor);number(first);number(second);number(bulkDescriptor->m_iFlags); }
void triggerPorts(CDescriptor* p) { number(25);number(p==bulkDescriptor);number(bulkDescriptor->m_iFlags); }
void side(const BulkCase& c,bool ours,autotest::Capture& output) {
 bulkCapture=&output;bulkCase=&c;bulkCalls=0;bulkBaseCalls=0;
 uint64_t memory[128]; const unsigned char fills[]={0,0x5a,0xff}; memset(memory,fills[c.fill],sizeof(memory));
 bulkDescriptor=(CDescriptor*)memory;
 std::wstring name=c.text==0?L"name":c.text==1?L"":c.text==2?L"\u03a9\u4e2d":std::wstring(200,L'N');
 std::wstring group=L"group"+name,description=L"description"+name;
 detour::Set d;
 TL_REDIRECT(d,bulkProperty,&property);TL_REDIRECT(d,bulkInterpreted,&interpreted);
 TL_REDIRECT(d,bulkInput,&addInput);TL_REDIRECT(d,bulkOutput,&addOutput);TL_REDIRECT(d,bulkLink,&link);
 switch(c.kind) {
 case 0: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 1: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 2: TL_REDIRECT(d,bulkBase3,&base3); break;
 case 3: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 4: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 5: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 6: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 7: TL_REDIRECT(d,bulkBase3,&base3); break;
 case 8: TL_REDIRECT(d,bulkBase6,&base6); break;
 case 9: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 10: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 11: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 12: TL_REDIRECT(d,bulkBase6,&base6); break;
 case 13: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 14: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 15: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 16: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 17: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 18: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 19: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 20: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 21: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 22: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 23: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 24: TL_REDIRECT(d,bulkBase4,&base4); break;
 case 25: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 26: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 27: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 28: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 29: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 30: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 31: TL_REDIRECT(d,bulkBase3,&base3); break;
 case 32: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 33: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 34: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 35: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 36: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 37: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 38: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 39: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 40: TL_REDIRECT(d,bulkBase4,&base4); break;
 case 41: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 42: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 43: TL_REDIRECT(d,bulkBase3,&base3); break;
 case 44: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 45: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 46: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 47: TL_REDIRECT(d,bulkBase5,&base5); break;
 case 48: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 49: TL_REDIRECT(d,bulkBase5,&base5); break;
 case 50: TL_REDIRECT(d,bulkBase6,&base6); break;
 case 51: TL_REDIRECT(d,bulkBase2,&base2); break;
 case 52: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 53: TL_REDIRECT(d,bulkBase7,&base7); break;
 case 54: TL_REDIRECT(d,bulkBase0,&base0); break;
 case 55: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 56: TL_REDIRECT(d,bulkBase1,&base1);TL_REDIRECT(d,bulkTriggerPorts,&triggerPorts); break;
 case 57: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 58: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 59: TL_REDIRECT(d,bulkBase1,&base1); break;
 case 60: TL_REDIRECT(d,bulkBase7,&base7); break;
 case 61: TL_REDIRECT(d,bulkBase7,&base7); break;
 default: _exit(44);
 }
 if(d.failed())_exit(43);
 switch(c.kind) {
 case 0: autotest::invoke(output,ours?&bulkNew0:&bulkOld0,(void*)bulkDescriptor);
 break;
 case 1: autotest::invoke(output,ours?&bulkNew1:&bulkOld1,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 2: autotest::invoke(output,ours?&bulkNew2:&bulkOld2,(void*)bulkDescriptor);
 break;
 case 3: autotest::invoke(output,ours?&bulkNew3:&bulkOld3,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 4: autotest::invoke(output,ours?&bulkNew4:&bulkOld4,(void*)bulkDescriptor);
 break;
 case 5: autotest::invoke(output,ours?&bulkNew5:&bulkOld5,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 6: autotest::invoke(output,ours?&bulkNew6:&bulkOld6,(void*)bulkDescriptor,name.c_str());
 break;
 case 7: autotest::invoke(output,ours?&bulkNew7:&bulkOld7,(void*)bulkDescriptor);
 break;
 case 8: autotest::invoke(output,ours?&bulkNew8:&bulkOld8,(void*)bulkDescriptor);
 break;
 case 9: autotest::invoke(output,ours?&bulkNew9:&bulkOld9,(void*)bulkDescriptor);
 break;
 case 10: autotest::invoke(output,ours?&bulkNew10:&bulkOld10,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 11: autotest::invoke(output,ours?&bulkNew11:&bulkOld11,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 12: autotest::invoke(output,ours?&bulkNew12:&bulkOld12,(void*)bulkDescriptor);
 break;
 case 13: autotest::invoke(output,ours?&bulkNew13:&bulkOld13,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 14: autotest::invoke(output,ours?&bulkNew14:&bulkOld14,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 15: autotest::invoke(output,ours?&bulkNew15:&bulkOld15,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 16: autotest::invoke(output,ours?&bulkNew16:&bulkOld16,(void*)bulkDescriptor);
 break;
 case 17: autotest::invoke(output,ours?&bulkNew17:&bulkOld17,(void*)bulkDescriptor);
 break;
 case 18: autotest::invoke(output,ours?&bulkNew18:&bulkOld18,(void*)bulkDescriptor);
 break;
 case 19: autotest::invoke(output,ours?&bulkNew19:&bulkOld19,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 20: autotest::invoke(output,ours?&bulkNew20:&bulkOld20,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 21: autotest::invoke(output,ours?&bulkNew21:&bulkOld21,(void*)bulkDescriptor);
 break;
 case 22: autotest::invoke(output,ours?&bulkNew22:&bulkOld22,(void*)bulkDescriptor);
 break;
 case 23: autotest::invoke(output,ours?&bulkNew23:&bulkOld23,(void*)bulkDescriptor);
 break;
 case 24: autotest::invoke(output,ours?&bulkNew24:&bulkOld24,(void*)bulkDescriptor);
 break;
 case 25: autotest::invoke(output,ours?&bulkNew25:&bulkOld25,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 26: autotest::invoke(output,ours?&bulkNew26:&bulkOld26,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 27: autotest::invoke(output,ours?&bulkNew27:&bulkOld27,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 28: autotest::invoke(output,ours?&bulkNew28:&bulkOld28,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 29: autotest::invoke(output,ours?&bulkNew29:&bulkOld29,(void*)bulkDescriptor);
 break;
 case 30: autotest::invoke(output,ours?&bulkNew30:&bulkOld30,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 31: autotest::invoke(output,ours?&bulkNew31:&bulkOld31,(void*)bulkDescriptor);
 break;
 case 32: autotest::invoke(output,ours?&bulkNew32:&bulkOld32,(void*)bulkDescriptor);
 break;
 case 33: autotest::invoke(output,ours?&bulkNew33:&bulkOld33,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 34: autotest::invoke(output,ours?&bulkNew34:&bulkOld34,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 35: autotest::invoke(output,ours?&bulkNew35:&bulkOld35,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 36: autotest::invoke(output,ours?&bulkNew36:&bulkOld36,(void*)bulkDescriptor);
 break;
 case 37: autotest::invoke(output,ours?&bulkNew37:&bulkOld37,(void*)bulkDescriptor);
 break;
 case 38: autotest::invoke(output,ours?&bulkNew38:&bulkOld38,(void*)bulkDescriptor);
 break;
 case 39: autotest::invoke(output,ours?&bulkNew39:&bulkOld39,(void*)bulkDescriptor);
 break;
 case 40: autotest::invoke(output,ours?&bulkNew40:&bulkOld40,(void*)bulkDescriptor);
 break;
 case 41: autotest::invoke(output,ours?&bulkNew41:&bulkOld41,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 42: autotest::invoke(output,ours?&bulkNew42:&bulkOld42,(void*)bulkDescriptor);
 break;
 case 43: autotest::invoke(output,ours?&bulkNew43:&bulkOld43,(void*)bulkDescriptor);
 break;
 case 44: autotest::invoke(output,ours?&bulkNew44:&bulkOld44,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 45: autotest::invoke(output,ours?&bulkNew45:&bulkOld45,(void*)bulkDescriptor);
 break;
 case 46: autotest::invoke(output,ours?&bulkNew46:&bulkOld46,(void*)bulkDescriptor);
 break;
 case 47: autotest::invoke(output,ours?&bulkNew47:&bulkOld47,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 48: autotest::invoke(output,ours?&bulkNew48:&bulkOld48,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 49: autotest::invoke(output,ours?&bulkNew49:&bulkOld49,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 50: autotest::invoke(output,ours?&bulkNew50:&bulkOld50,(void*)bulkDescriptor);
 break;
 case 51: autotest::invoke(output,ours?&bulkNew51:&bulkOld51,(void*)bulkDescriptor);
 break;
 case 52: autotest::invoke(output,ours?&bulkNew52:&bulkOld52,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 53: autotest::invoke(output,ours?&bulkNew53:&bulkOld53,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 54: autotest::invoke(output,ours?&bulkNew54:&bulkOld54,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str(),bool(c.options & 1),bool(c.options & 2),bool(c.options & 4),bool(c.options & 8),bool(c.options & 16));
 break;
 case 55: autotest::invoke(output,ours?&bulkNew55:&bulkOld55,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str(),bool(c.options & 1),bool(c.options & 2),bool(c.options & 4));
 break;
 case 56: autotest::invoke(output,ours?&bulkNew56:&bulkOld56,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 57: autotest::invoke(output,ours?&bulkNew57:&bulkOld57,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 58: autotest::invoke(output,ours?&bulkNew58:&bulkOld58,(void*)bulkDescriptor);
 break;
 case 59: autotest::invoke(output,ours?&bulkNew59:&bulkOld59,(void*)bulkDescriptor);
 break;
 case 60: autotest::invoke(output,ours?&bulkNew60:&bulkOld60,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 case 61: autotest::invoke(output,ours?&bulkNew61:&bulkOld61,(void*)bulkDescriptor,name.c_str(),group.c_str(),description.c_str());
 break;
 }
 switch(c.kind) {
case 53:
case 60:
case 61:

  output.addText(bulkDescriptor->m_sName);output.addText(bulkDescriptor->m_sDescription);
  output.addText(bulkDescriptor->m_sIcon);output.addText(bulkDescriptor->m_sMenuCategory);
  // These four typed string fields were compared by full contents, including initial unassigned fields.
  memset(&bulkDescriptor->m_sName,0,sizeof(std::wstring));memset(&bulkDescriptor->m_sDescription,0,sizeof(std::wstring));
  memset(&bulkDescriptor->m_sIcon,0,sizeof(std::wstring));memset(&bulkDescriptor->m_sMenuCategory,0,sizeof(std::wstring));
  break;
 default:break;
 }
 if(c.kind>=57 && c.kind<=59) {
  number(bulkDescriptor->m_ParentFilters.size());
  for(unsigned i=0;i<bulkDescriptor->m_ParentFilters.size();++i)output.addText(bulkDescriptor->m_ParentFilters[i]);
  // Items and all array metadata are compared; only the observed allocation address is omitted.
  memset(&bulkDescriptor->m_ParentFilters,0,sizeof(void*));
 }
 // Hybrid relocation binds class vtables to the original data; compare every byte.
 number(100);number(bulkCalls);number(bulkBaseCalls);output.add(memory,sizeof(memory));
 if(bulkBaseCalls!=1)_exit(45);
}
void original(void* p,autotest::Capture& c) { side(*(BulkCase*)p,false,c); }
void replacement(void* p,autotest::Capture& c) { side(*(BulkCase*)p,true,c); }
int run(const tlhybrid_host* host,unsigned kind,const char* name,uint64_t address,unsigned options) {
 autotest::Coverage coverage(name,address);
 const unsigned flags[]={0,0xffffffffU,0x55555555U,0x4148U};
 unsigned failures=0;
 for(unsigned option=0;option<options;++option)for(unsigned fill=0;fill<3;++fill)for(unsigned f=0;f<4;++f)for(unsigned returns=0;returns<2;++returns) {
  BulkCase c={kind,flags[f],f,returns,fill,option};autotest::Outcome a,b;
  autotest::runChild(original,&c,a);autotest::runChild(replacement,&c,b);
  int pair=coverage.observe(host,a,b);
  if(pair||autotest::incomplete(a)||autotest::incomplete(b)) {
   size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
   host->log("    registration kind %u fill %u flags %x text %u returns %u status %d/%d bytes %lu/%lu first %lu\n",kind,fill,c.flags,f,returns,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);
   if(++failures==1)for(size_t i=first>32?first-32:0;i<first+48&&i+4<=a.capture.length&&i+4<=b.capture.length;i+=4) {
    unsigned x,y;memcpy(&x,a.capture.data+i,4);memcpy(&y,b.capture.data+i,4);host->log("      %lu %x/%x\n",(unsigned long)i,x,y);
   }
  }
 }
 coverage.report(host);return failures?1:0;
}
}

TL_TEST(bulk_registration_AlignDescriptor) {return run(host,0,"bulk_registration_AlignDescriptor",(uint64_t)(uintptr_t)&bulkOld0,1);}
TL_TEST(bulk_registration_AnimationPlayerDescriptor) {return run(host,1,"bulk_registration_AnimationPlayerDescriptor",(uint64_t)(uintptr_t)&bulkOld1,1);}
TL_TEST(bulk_registration_BoxColliderDescriptor) {return run(host,2,"bulk_registration_BoxColliderDescriptor",(uint64_t)(uintptr_t)&bulkOld2,1);}
TL_TEST(bulk_registration_CameraControllerDescriptor) {return run(host,3,"bulk_registration_CameraControllerDescriptor",(uint64_t)(uintptr_t)&bulkOld3,1);}
TL_TEST(bulk_registration_CameraShakeDescriptor) {return run(host,4,"bulk_registration_CameraShakeDescriptor",(uint64_t)(uintptr_t)&bulkOld4,1);}
TL_TEST(bulk_registration_CinematicDescriptor) {return run(host,5,"bulk_registration_CinematicDescriptor",(uint64_t)(uintptr_t)&bulkOld5,1);}
TL_TEST(bulk_registration_ColliderDescriptor) {return run(host,6,"bulk_registration_ColliderDescriptor",(uint64_t)(uintptr_t)&bulkOld6,1);}
TL_TEST(bulk_registration_CollisionAvoiderDescriptor) {return run(host,7,"bulk_registration_CollisionAvoiderDescriptor",(uint64_t)(uintptr_t)&bulkOld7,1);}
TL_TEST(bulk_registration_CollisionShapeDescriptor) {return run(host,8,"bulk_registration_CollisionShapeDescriptor",(uint64_t)(uintptr_t)&bulkOld8,1);}
TL_TEST(bulk_registration_ColorAffectorDescriptor) {return run(host,9,"bulk_registration_ColorAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld9,1);}
TL_TEST(bulk_registration_CounterDescriptor) {return run(host,10,"bulk_registration_CounterDescriptor",(uint64_t)(uintptr_t)&bulkOld10,1);}
TL_TEST(bulk_registration_SkipCutsceneDescriptor) {return run(host,11,"bulk_registration_SkipCutsceneDescriptor",(uint64_t)(uintptr_t)&bulkOld11,1);}
TL_TEST(bulk_registration_DamageShapeDescriptor) {return run(host,12,"bulk_registration_DamageShapeDescriptor",(uint64_t)(uintptr_t)&bulkOld12,1);}
TL_TEST(bulk_registration_DungeonObjectDescriptor) {return run(host,13,"bulk_registration_DungeonObjectDescriptor",(uint64_t)(uintptr_t)&bulkOld13,1);}
TL_TEST(bulk_registration_ForceAffectorDescriptor) {return run(host,14,"bulk_registration_ForceAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld14,1);}
TL_TEST(bulk_registration_GameStateControllerDescriptor) {return run(host,15,"bulk_registration_GameStateControllerDescriptor",(uint64_t)(uintptr_t)&bulkOld15,1);}
TL_TEST(bulk_registration_GenericModelDescriptor) {return run(host,16,"bulk_registration_GenericModelDescriptor",(uint64_t)(uintptr_t)&bulkOld16,1);}
TL_TEST(bulk_registration_GeometryRotateDescriptor) {return run(host,17,"bulk_registration_GeometryRotateDescriptor",(uint64_t)(uintptr_t)&bulkOld17,1);}
TL_TEST(bulk_registration_GravityAffectorDescriptor) {return run(host,18,"bulk_registration_GravityAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld18,1);}
TL_TEST(bulk_registration_InteractiveDescriptor) {return run(host,19,"bulk_registration_InteractiveDescriptor",(uint64_t)(uintptr_t)&bulkOld19,1);}
TL_TEST(bulk_registration_ItemDescriptor) {return run(host,20,"bulk_registration_ItemDescriptor",(uint64_t)(uintptr_t)&bulkOld20,1);}
TL_TEST(bulk_registration_JetAffectorDescriptor) {return run(host,21,"bulk_registration_JetAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld21,1);}
TL_TEST(bulk_registration_LightDescriptor) {return run(host,22,"bulk_registration_LightDescriptor",(uint64_t)(uintptr_t)&bulkOld22,1);}
TL_TEST(bulk_registration_LineAffectorDescriptor) {return run(host,23,"bulk_registration_LineAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld23,1);}
TL_TEST(bulk_registration_LinearForceAffectorDescriptor) {return run(host,24,"bulk_registration_LinearForceAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld24,1);}
TL_TEST(bulk_registration_LogicTimerDescriptor) {return run(host,25,"bulk_registration_LogicTimerDescriptor",(uint64_t)(uintptr_t)&bulkOld25,1);}
TL_TEST(bulk_registration_MoneyTakerDescriptor) {return run(host,26,"bulk_registration_MoneyTakerDescriptor",(uint64_t)(uintptr_t)&bulkOld26,1);}
TL_TEST(bulk_registration_MonsterDescriptor) {return run(host,27,"bulk_registration_MonsterDescriptor",(uint64_t)(uintptr_t)&bulkOld27,1);}
TL_TEST(bulk_registration_MusicObjectDescriptor) {return run(host,28,"bulk_registration_MusicObjectDescriptor",(uint64_t)(uintptr_t)&bulkOld28,1);}
TL_TEST(bulk_registration_ParticleWrapperDescriptor) {return run(host,29,"bulk_registration_ParticleWrapperDescriptor",(uint64_t)(uintptr_t)&bulkOld29,1);}
TL_TEST(bulk_registration_PathControllerDescriptor) {return run(host,30,"bulk_registration_PathControllerDescriptor",(uint64_t)(uintptr_t)&bulkOld30,1);}
TL_TEST(bulk_registration_PlaneColliderDescriptor) {return run(host,31,"bulk_registration_PlaneColliderDescriptor",(uint64_t)(uintptr_t)&bulkOld31,1);}
TL_TEST(bulk_registration_PropertyNodeDescriptor) {return run(host,32,"bulk_registration_PropertyNodeDescriptor",(uint64_t)(uintptr_t)&bulkOld32,1);}
TL_TEST(bulk_registration_PuzzleRandomizerDescriptor) {return run(host,33,"bulk_registration_PuzzleRandomizerDescriptor",(uint64_t)(uintptr_t)&bulkOld33,1);}
TL_TEST(bulk_registration_QuestControllerDescriptor) {return run(host,34,"bulk_registration_QuestControllerDescriptor",(uint64_t)(uintptr_t)&bulkOld34,1);}
TL_TEST(bulk_registration_RandomChoiceDescriptor) {return run(host,35,"bulk_registration_RandomChoiceDescriptor",(uint64_t)(uintptr_t)&bulkOld35,1);}
TL_TEST(bulk_registration_RandomGroupDescriptor) {return run(host,36,"bulk_registration_RandomGroupDescriptor",(uint64_t)(uintptr_t)&bulkOld36,1);}
TL_TEST(bulk_registration_RoomDescriptor) {return run(host,37,"bulk_registration_RoomDescriptor",(uint64_t)(uintptr_t)&bulkOld37,1);}
TL_TEST(bulk_registration_RoomPieceDescriptor) {return run(host,38,"bulk_registration_RoomPieceDescriptor",(uint64_t)(uintptr_t)&bulkOld38,1);}
TL_TEST(bulk_registration_ScaleAffectorDescriptor) {return run(host,39,"bulk_registration_ScaleAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld39,1);}
TL_TEST(bulk_registration_SineForceAffectorDescriptor) {return run(host,40,"bulk_registration_SineForceAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld40,1);}
TL_TEST(bulk_registration_SkillControllerDescriptor) {return run(host,41,"bulk_registration_SkillControllerDescriptor",(uint64_t)(uintptr_t)&bulkOld41,1);}
TL_TEST(bulk_registration_SoundObjectDescriptor) {return run(host,42,"bulk_registration_SoundObjectDescriptor",(uint64_t)(uintptr_t)&bulkOld42,1);}
TL_TEST(bulk_registration_SphereColliderDescriptor) {return run(host,43,"bulk_registration_SphereColliderDescriptor",(uint64_t)(uintptr_t)&bulkOld43,1);}
TL_TEST(bulk_registration_TeleportDescriptor) {return run(host,44,"bulk_registration_TeleportDescriptor",(uint64_t)(uintptr_t)&bulkOld44,1);}
TL_TEST(bulk_registration_TextureAnimateDescriptor) {return run(host,45,"bulk_registration_TextureAnimateDescriptor",(uint64_t)(uintptr_t)&bulkOld45,1);}
TL_TEST(bulk_registration_TextureRotateDescriptor) {return run(host,46,"bulk_registration_TextureRotateDescriptor",(uint64_t)(uintptr_t)&bulkOld46,1);}
TL_TEST(bulk_registration_TriggerBoxDescriptor) {return run(host,47,"bulk_registration_TriggerBoxDescriptor",(uint64_t)(uintptr_t)&bulkOld47,1);}
TL_TEST(bulk_registration_TriggerDescriptor) {return run(host,48,"bulk_registration_TriggerDescriptor",(uint64_t)(uintptr_t)&bulkOld48,1);}
TL_TEST(bulk_registration_TriggerSphereDescriptor) {return run(host,49,"bulk_registration_TriggerSphereDescriptor",(uint64_t)(uintptr_t)&bulkOld49,1);}
TL_TEST(bulk_registration_UnitSpawnerDescriptor) {return run(host,50,"bulk_registration_UnitSpawnerDescriptor",(uint64_t)(uintptr_t)&bulkOld50,1);}
TL_TEST(bulk_registration_VortexAffectorDescriptor) {return run(host,51,"bulk_registration_VortexAffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld51,1);}
TL_TEST(bulk_registration_WarperDescriptor) {return run(host,52,"bulk_registration_WarperDescriptor",(uint64_t)(uintptr_t)&bulkOld52,1);}
TL_TEST(bulk_registration_BaseObjectDescriptor) {return run(host,53,"bulk_registration_BaseObjectDescriptor",(uint64_t)(uintptr_t)&bulkOld53,1);}
TL_TEST(bulk_registration_PositionableObjectDescriptor) {return run(host,54,"bulk_registration_PositionableObjectDescriptor",(uint64_t)(uintptr_t)&bulkOld54,32);}
TL_TEST(bulk_registration_ShapeDescriptor) {return run(host,55,"bulk_registration_ShapeDescriptor",(uint64_t)(uintptr_t)&bulkOld55,8);}
TL_TEST(bulk_registration_UnitTriggerDescriptor) {return run(host,56,"bulk_registration_UnitTriggerDescriptor",(uint64_t)(uintptr_t)&bulkOld56,1);}
TL_TEST(bulk_registration_AffectorDescriptor) {return run(host,57,"bulk_registration_AffectorDescriptor",(uint64_t)(uintptr_t)&bulkOld57,1);}
TL_TEST(bulk_registration_ParticleEmitterWrapperDescriptor) {return run(host,58,"bulk_registration_ParticleEmitterWrapperDescriptor",(uint64_t)(uintptr_t)&bulkOld58,1);}
TL_TEST(bulk_registration_ParticleTechWrapperDescriptor) {return run(host,59,"bulk_registration_ParticleTechWrapperDescriptor",(uint64_t)(uintptr_t)&bulkOld59,1);}
TL_TEST(bulk_registration_LogicGroupDescriptor) {return run(host,60,"bulk_registration_LogicGroupDescriptor",(uint64_t)(uintptr_t)&bulkOld60,1);}
TL_TEST(bulk_registration_TimelineDescriptor) {return run(host,61,"bulk_registration_TimelineDescriptor",(uint64_t)(uintptr_t)&bulkOld61,1);}
TL_TEST(bulk_descriptor_callback_identity) {
 if(bulkCallbackIdentity((void*)bulkCallback0_original)!=(uintptr_t)bulkCallback0_original || bulkCallbackIdentity((void*)bulkCallback0_linked)!=(uintptr_t)bulkCallback0_original)return 1;
 if(bulkCallbackIdentity((void*)bulkCallback1_original)!=(uintptr_t)bulkCallback1_original || bulkCallbackIdentity((void*)bulkCallback1_linked)!=(uintptr_t)bulkCallback1_original)return 2;
 if(bulkCallbackIdentity((void*)bulkCallback2_original)!=(uintptr_t)bulkCallback2_original || bulkCallbackIdentity((void*)bulkCallback2_linked)!=(uintptr_t)bulkCallback2_original)return 3;
 if(bulkCallbackIdentity((void*)bulkCallback3_original)!=(uintptr_t)bulkCallback3_original || bulkCallbackIdentity((void*)bulkCallback3_linked)!=(uintptr_t)bulkCallback3_original)return 4;
 if(bulkCallbackIdentity((void*)bulkCallback4_original)!=(uintptr_t)bulkCallback4_original || bulkCallbackIdentity((void*)bulkCallback4_linked)!=(uintptr_t)bulkCallback4_original)return 5;
 if(bulkCallbackIdentity((void*)bulkCallback5_original)!=(uintptr_t)bulkCallback5_original || bulkCallbackIdentity((void*)bulkCallback5_linked)!=(uintptr_t)bulkCallback5_original)return 6;
 if(bulkCallbackIdentity((void*)bulkCallback6_original)!=(uintptr_t)bulkCallback6_original || bulkCallbackIdentity((void*)bulkCallback6_linked)!=(uintptr_t)bulkCallback6_original)return 7;
 if(bulkCallbackIdentity((void*)bulkCallback7_original)!=(uintptr_t)bulkCallback7_original || bulkCallbackIdentity((void*)bulkCallback7_linked)!=(uintptr_t)bulkCallback7_original)return 8;
 if(bulkCallbackIdentity((void*)bulkCallback8_original)!=(uintptr_t)bulkCallback8_original || bulkCallbackIdentity((void*)bulkCallback8_linked)!=(uintptr_t)bulkCallback8_original)return 9;
 if(bulkCallbackIdentity((void*)bulkCallback9_original)!=(uintptr_t)bulkCallback9_original || bulkCallbackIdentity((void*)bulkCallback9_linked)!=(uintptr_t)bulkCallback9_original)return 10;
 if(bulkCallbackIdentity((void*)bulkCallback10_original)!=(uintptr_t)bulkCallback10_original || bulkCallbackIdentity((void*)bulkCallback10_linked)!=(uintptr_t)bulkCallback10_original)return 11;
 if(bulkCallbackIdentity((void*)bulkCallback11_original)!=(uintptr_t)bulkCallback11_original || bulkCallbackIdentity((void*)bulkCallback11_linked)!=(uintptr_t)bulkCallback11_original)return 12;
 if(bulkCallbackIdentity((void*)bulkCallback12_original)!=(uintptr_t)bulkCallback12_original || bulkCallbackIdentity((void*)bulkCallback12_linked)!=(uintptr_t)bulkCallback12_original)return 13;
 if(bulkCallbackIdentity((void*)bulkCallback13_original)!=(uintptr_t)bulkCallback13_original || bulkCallbackIdentity((void*)bulkCallback13_linked)!=(uintptr_t)bulkCallback13_original)return 14;
 if(bulkCallbackIdentity((void*)bulkCallback14_original)!=(uintptr_t)bulkCallback14_original || bulkCallbackIdentity((void*)bulkCallback14_linked)!=(uintptr_t)bulkCallback14_original)return 15;
 if(bulkCallbackIdentity((void*)bulkCallback15_original)!=(uintptr_t)bulkCallback15_original || bulkCallbackIdentity((void*)bulkCallback15_linked)!=(uintptr_t)bulkCallback15_original)return 16;
 if(bulkCallbackIdentity((void*)bulkCallback16_original)!=(uintptr_t)bulkCallback16_original || bulkCallbackIdentity((void*)bulkCallback16_linked)!=(uintptr_t)bulkCallback16_original)return 17;
 if(bulkCallbackIdentity((void*)bulkCallback17_original)!=(uintptr_t)bulkCallback17_original || bulkCallbackIdentity((void*)bulkCallback17_linked)!=(uintptr_t)bulkCallback17_original)return 18;
 if(bulkCallbackIdentity((void*)bulkCallback18_original)!=(uintptr_t)bulkCallback18_original || bulkCallbackIdentity((void*)bulkCallback18_linked)!=(uintptr_t)bulkCallback18_original)return 19;
 if(bulkCallbackIdentity((void*)bulkCallback19_original)!=(uintptr_t)bulkCallback19_original || bulkCallbackIdentity((void*)bulkCallback19_linked)!=(uintptr_t)bulkCallback19_original)return 20;
 if(bulkCallbackIdentity((void*)bulkCallback20_original)!=(uintptr_t)bulkCallback20_original || bulkCallbackIdentity((void*)bulkCallback20_linked)!=(uintptr_t)bulkCallback20_original)return 21;
 if(bulkCallbackIdentity((void*)bulkCallback21_original)!=(uintptr_t)bulkCallback21_original || bulkCallbackIdentity((void*)bulkCallback21_linked)!=(uintptr_t)bulkCallback21_original)return 22;
 if(bulkCallbackIdentity((void*)bulkCallback22_original)!=(uintptr_t)bulkCallback22_original || bulkCallbackIdentity((void*)bulkCallback22_linked)!=(uintptr_t)bulkCallback22_original)return 23;
 if(bulkCallbackIdentity((void*)bulkCallback23_original)!=(uintptr_t)bulkCallback23_original || bulkCallbackIdentity((void*)bulkCallback23_linked)!=(uintptr_t)bulkCallback23_original)return 24;
 if(bulkCallbackIdentity((void*)bulkCallback24_original)!=(uintptr_t)bulkCallback24_original || bulkCallbackIdentity((void*)bulkCallback24_linked)!=(uintptr_t)bulkCallback24_original)return 25;
 if(bulkCallbackIdentity((void*)bulkCallback25_original)!=(uintptr_t)bulkCallback25_original || bulkCallbackIdentity((void*)bulkCallback25_linked)!=(uintptr_t)bulkCallback25_original)return 26;
 if(bulkCallbackIdentity((void*)bulkCallback26_original)!=(uintptr_t)bulkCallback26_original || bulkCallbackIdentity((void*)bulkCallback26_linked)!=(uintptr_t)bulkCallback26_original)return 27;
 if(bulkCallbackIdentity((void*)bulkCallback27_original)!=(uintptr_t)bulkCallback27_original || bulkCallbackIdentity((void*)bulkCallback27_linked)!=(uintptr_t)bulkCallback27_original)return 28;
 if(bulkCallbackIdentity((void*)bulkCallback28_original)!=(uintptr_t)bulkCallback28_original || bulkCallbackIdentity((void*)bulkCallback28_linked)!=(uintptr_t)bulkCallback28_original)return 29;
 if(bulkCallbackIdentity((void*)bulkCallback29_original)!=(uintptr_t)bulkCallback29_original || bulkCallbackIdentity((void*)bulkCallback29_linked)!=(uintptr_t)bulkCallback29_original)return 30;
 if(bulkCallbackIdentity((void*)bulkCallback30_original)!=(uintptr_t)bulkCallback30_original || bulkCallbackIdentity((void*)bulkCallback30_linked)!=(uintptr_t)bulkCallback30_original)return 31;
 if(bulkCallbackIdentity((void*)bulkCallback31_original)!=(uintptr_t)bulkCallback31_original || bulkCallbackIdentity((void*)bulkCallback31_linked)!=(uintptr_t)bulkCallback31_original)return 32;
 if(bulkCallbackIdentity((void*)bulkCallback32_original)!=(uintptr_t)bulkCallback32_original || bulkCallbackIdentity((void*)bulkCallback32_linked)!=(uintptr_t)bulkCallback32_original)return 33;
 if(bulkCallbackIdentity((void*)bulkCallback33_original)!=(uintptr_t)bulkCallback33_original || bulkCallbackIdentity((void*)bulkCallback33_linked)!=(uintptr_t)bulkCallback33_original)return 34;
 if(bulkCallbackIdentity((void*)bulkCallback34_original)!=(uintptr_t)bulkCallback34_original || bulkCallbackIdentity((void*)bulkCallback34_linked)!=(uintptr_t)bulkCallback34_original)return 35;
 if(bulkCallbackIdentity((void*)bulkCallback35_original)!=(uintptr_t)bulkCallback35_original || bulkCallbackIdentity((void*)bulkCallback35_linked)!=(uintptr_t)bulkCallback35_original)return 36;
 if(bulkCallbackIdentity((void*)bulkCallback36_original)!=(uintptr_t)bulkCallback36_original || bulkCallbackIdentity((void*)bulkCallback36_linked)!=(uintptr_t)bulkCallback36_original)return 37;
 if(bulkCallbackIdentity((void*)bulkCallback37_original)!=(uintptr_t)bulkCallback37_original || bulkCallbackIdentity((void*)bulkCallback37_linked)!=(uintptr_t)bulkCallback37_original)return 38;
 if(bulkCallbackIdentity((void*)bulkCallback38_original)!=(uintptr_t)bulkCallback38_original || bulkCallbackIdentity((void*)bulkCallback38_linked)!=(uintptr_t)bulkCallback38_original)return 39;
 if(bulkCallbackIdentity((void*)bulkCallback39_original)!=(uintptr_t)bulkCallback39_original || bulkCallbackIdentity((void*)bulkCallback39_linked)!=(uintptr_t)bulkCallback39_original)return 40;
 if(bulkCallbackIdentity((void*)bulkCallback40_original)!=(uintptr_t)bulkCallback40_original || bulkCallbackIdentity((void*)bulkCallback40_linked)!=(uintptr_t)bulkCallback40_original)return 41;
 if(bulkCallbackIdentity((void*)bulkCallback41_original)!=(uintptr_t)bulkCallback41_original || bulkCallbackIdentity((void*)bulkCallback41_linked)!=(uintptr_t)bulkCallback41_original)return 42;
 if(bulkCallbackIdentity((void*)bulkCallback42_original)!=(uintptr_t)bulkCallback42_original || bulkCallbackIdentity((void*)bulkCallback42_linked)!=(uintptr_t)bulkCallback42_original)return 43;
 if(bulkCallbackIdentity((void*)bulkCallback43_original)!=(uintptr_t)bulkCallback43_original || bulkCallbackIdentity((void*)bulkCallback43_linked)!=(uintptr_t)bulkCallback43_original)return 44;
 if(bulkCallbackIdentity((void*)bulkCallback44_original)!=(uintptr_t)bulkCallback44_original || bulkCallbackIdentity((void*)bulkCallback44_linked)!=(uintptr_t)bulkCallback44_original)return 45;
 if(bulkCallbackIdentity((void*)bulkCallback45_original)!=(uintptr_t)bulkCallback45_original || bulkCallbackIdentity((void*)bulkCallback45_linked)!=(uintptr_t)bulkCallback45_original)return 46;
 if(bulkCallbackIdentity((void*)bulkCallback46_original)!=(uintptr_t)bulkCallback46_original || bulkCallbackIdentity((void*)bulkCallback46_linked)!=(uintptr_t)bulkCallback46_original)return 47;
 if(bulkCallbackIdentity((void*)bulkCallback47_original)!=(uintptr_t)bulkCallback47_original || bulkCallbackIdentity((void*)bulkCallback47_linked)!=(uintptr_t)bulkCallback47_original)return 48;
 if(bulkCallbackIdentity((void*)bulkCallback48_original)!=(uintptr_t)bulkCallback48_original || bulkCallbackIdentity((void*)bulkCallback48_linked)!=(uintptr_t)bulkCallback48_original)return 49;
 if(bulkCallbackIdentity((void*)bulkCallback49_original)!=(uintptr_t)bulkCallback49_original || bulkCallbackIdentity((void*)bulkCallback49_linked)!=(uintptr_t)bulkCallback49_original)return 50;
 if(bulkCallbackIdentity((void*)bulkCallback50_original)!=(uintptr_t)bulkCallback50_original || bulkCallbackIdentity((void*)bulkCallback50_linked)!=(uintptr_t)bulkCallback50_original)return 51;
 if(bulkCallbackIdentity((void*)bulkCallback51_original)!=(uintptr_t)bulkCallback51_original || bulkCallbackIdentity((void*)bulkCallback51_linked)!=(uintptr_t)bulkCallback51_original)return 52;
 if(bulkCallbackIdentity((void*)bulkCallback52_original)!=(uintptr_t)bulkCallback52_original || bulkCallbackIdentity((void*)bulkCallback52_linked)!=(uintptr_t)bulkCallback52_original)return 53;
 if(bulkCallbackIdentity((void*)bulkCallback53_original)!=(uintptr_t)bulkCallback53_original || bulkCallbackIdentity((void*)bulkCallback53_linked)!=(uintptr_t)bulkCallback53_original)return 54;
 if(bulkCallbackIdentity((void*)bulkCallback54_original)!=(uintptr_t)bulkCallback54_original || bulkCallbackIdentity((void*)bulkCallback54_linked)!=(uintptr_t)bulkCallback54_original)return 55;
 if(bulkCallbackIdentity((void*)bulkCallback55_original)!=(uintptr_t)bulkCallback55_original || bulkCallbackIdentity((void*)bulkCallback55_linked)!=(uintptr_t)bulkCallback55_original)return 56;
 if(bulkCallbackIdentity((void*)bulkCallback56_original)!=(uintptr_t)bulkCallback56_original || bulkCallbackIdentity((void*)bulkCallback56_linked)!=(uintptr_t)bulkCallback56_original)return 57;
 if(bulkCallbackIdentity((void*)bulkCallback57_original)!=(uintptr_t)bulkCallback57_original || bulkCallbackIdentity((void*)bulkCallback57_linked)!=(uintptr_t)bulkCallback57_original)return 58;
 if(bulkCallbackIdentity((void*)bulkCallback58_original)!=(uintptr_t)bulkCallback58_original || bulkCallbackIdentity((void*)bulkCallback58_linked)!=(uintptr_t)bulkCallback58_original)return 59;
 if(bulkCallbackIdentity((void*)bulkCallback59_original)!=(uintptr_t)bulkCallback59_original || bulkCallbackIdentity((void*)bulkCallback59_linked)!=(uintptr_t)bulkCallback59_original)return 60;
 if(bulkCallbackIdentity((void*)bulkCallback60_original)!=(uintptr_t)bulkCallback60_original || bulkCallbackIdentity((void*)bulkCallback60_linked)!=(uintptr_t)bulkCallback60_original)return 61;
 if(bulkCallbackIdentity((void*)bulkCallback61_original)!=(uintptr_t)bulkCallback61_original || bulkCallbackIdentity((void*)bulkCallback61_linked)!=(uintptr_t)bulkCallback61_original)return 62;
 if(bulkCallbackIdentity((void*)bulkCallback62_original)!=(uintptr_t)bulkCallback62_original || bulkCallbackIdentity((void*)bulkCallback62_linked)!=(uintptr_t)bulkCallback62_original)return 63;
 if(bulkCallbackIdentity((void*)bulkCallback63_original)!=(uintptr_t)bulkCallback63_original || bulkCallbackIdentity((void*)bulkCallback63_linked)!=(uintptr_t)bulkCallback63_original)return 64;
 if(bulkCallbackIdentity((void*)bulkCallback64_original)!=(uintptr_t)bulkCallback64_original || bulkCallbackIdentity((void*)bulkCallback64_linked)!=(uintptr_t)bulkCallback64_original)return 65;
 if(bulkCallbackIdentity((void*)bulkCallback65_original)!=(uintptr_t)bulkCallback65_original || bulkCallbackIdentity((void*)bulkCallback65_linked)!=(uintptr_t)bulkCallback65_original)return 66;
 if(bulkCallbackIdentity((void*)bulkCallback66_original)!=(uintptr_t)bulkCallback66_original || bulkCallbackIdentity((void*)bulkCallback66_linked)!=(uintptr_t)bulkCallback66_original)return 67;
 if(bulkCallbackIdentity((void*)bulkCallback67_original)!=(uintptr_t)bulkCallback67_original || bulkCallbackIdentity((void*)bulkCallback67_linked)!=(uintptr_t)bulkCallback67_original)return 68;
 if(bulkCallbackIdentity((void*)bulkCallback68_original)!=(uintptr_t)bulkCallback68_original || bulkCallbackIdentity((void*)bulkCallback68_linked)!=(uintptr_t)bulkCallback68_original)return 69;
 if(bulkCallbackIdentity((void*)bulkCallback69_original)!=(uintptr_t)bulkCallback69_original || bulkCallbackIdentity((void*)bulkCallback69_linked)!=(uintptr_t)bulkCallback69_original)return 70;
 if(bulkCallbackIdentity((void*)bulkCallback70_original)!=(uintptr_t)bulkCallback70_original || bulkCallbackIdentity((void*)bulkCallback70_linked)!=(uintptr_t)bulkCallback70_original)return 71;
 if(bulkCallbackIdentity((void*)bulkCallback71_original)!=(uintptr_t)bulkCallback71_original || bulkCallbackIdentity((void*)bulkCallback71_linked)!=(uintptr_t)bulkCallback71_original)return 72;
 if(bulkCallbackIdentity((void*)bulkCallback72_original)!=(uintptr_t)bulkCallback72_original || bulkCallbackIdentity((void*)bulkCallback72_linked)!=(uintptr_t)bulkCallback72_original)return 73;
 if(bulkCallbackIdentity((void*)bulkCallback73_original)!=(uintptr_t)bulkCallback73_original || bulkCallbackIdentity((void*)bulkCallback73_linked)!=(uintptr_t)bulkCallback73_original)return 74;
 if(bulkCallbackIdentity((void*)bulkCallback74_original)!=(uintptr_t)bulkCallback74_original || bulkCallbackIdentity((void*)bulkCallback74_linked)!=(uintptr_t)bulkCallback74_original)return 75;
 if(bulkCallbackIdentity((void*)bulkCallback75_original)!=(uintptr_t)bulkCallback75_original || bulkCallbackIdentity((void*)bulkCallback75_linked)!=(uintptr_t)bulkCallback75_original)return 76;
 if(bulkCallbackIdentity((void*)bulkCallback76_original)!=(uintptr_t)bulkCallback76_original || bulkCallbackIdentity((void*)bulkCallback76_linked)!=(uintptr_t)bulkCallback76_original)return 77;
 if(bulkCallbackIdentity((void*)bulkCallback77_original)!=(uintptr_t)bulkCallback77_original || bulkCallbackIdentity((void*)bulkCallback77_linked)!=(uintptr_t)bulkCallback77_original)return 78;
 if(bulkCallbackIdentity((void*)bulkCallback78_original)!=(uintptr_t)bulkCallback78_original || bulkCallbackIdentity((void*)bulkCallback78_linked)!=(uintptr_t)bulkCallback78_original)return 79;
 if(bulkCallbackIdentity((void*)bulkCallback79_original)!=(uintptr_t)bulkCallback79_original || bulkCallbackIdentity((void*)bulkCallback79_linked)!=(uintptr_t)bulkCallback79_original)return 80;
 if(bulkCallbackIdentity((void*)bulkCallback80_original)!=(uintptr_t)bulkCallback80_original || bulkCallbackIdentity((void*)bulkCallback80_linked)!=(uintptr_t)bulkCallback80_original)return 81;
 if(bulkCallbackIdentity((void*)bulkCallback81_original)!=(uintptr_t)bulkCallback81_original || bulkCallbackIdentity((void*)bulkCallback81_linked)!=(uintptr_t)bulkCallback81_original)return 82;
 if(bulkCallbackIdentity((void*)bulkCallback82_original)!=(uintptr_t)bulkCallback82_original || bulkCallbackIdentity((void*)bulkCallback82_linked)!=(uintptr_t)bulkCallback82_original)return 83;
 if(bulkCallbackIdentity((void*)bulkCallback83_original)!=(uintptr_t)bulkCallback83_original || bulkCallbackIdentity((void*)bulkCallback83_linked)!=(uintptr_t)bulkCallback83_original)return 84;
 if(bulkCallbackIdentity((void*)bulkCallback84_original)!=(uintptr_t)bulkCallback84_original || bulkCallbackIdentity((void*)bulkCallback84_linked)!=(uintptr_t)bulkCallback84_original)return 85;
 if(bulkCallbackIdentity((void*)bulkCallback85_original)!=(uintptr_t)bulkCallback85_original || bulkCallbackIdentity((void*)bulkCallback85_linked)!=(uintptr_t)bulkCallback85_original)return 86;
 if(bulkCallbackIdentity((void*)bulkCallback86_original)!=(uintptr_t)bulkCallback86_original || bulkCallbackIdentity((void*)bulkCallback86_linked)!=(uintptr_t)bulkCallback86_original)return 87;
 if(bulkCallbackIdentity((void*)bulkCallback87_original)!=(uintptr_t)bulkCallback87_original || bulkCallbackIdentity((void*)bulkCallback87_linked)!=(uintptr_t)bulkCallback87_original)return 88;
 if(bulkCallbackIdentity((void*)bulkCallback88_original)!=(uintptr_t)bulkCallback88_original || bulkCallbackIdentity((void*)bulkCallback88_linked)!=(uintptr_t)bulkCallback88_original)return 89;
 if(bulkCallbackIdentity((void*)bulkCallback89_original)!=(uintptr_t)bulkCallback89_original || bulkCallbackIdentity((void*)bulkCallback89_linked)!=(uintptr_t)bulkCallback89_original)return 90;
 if(bulkCallbackIdentity((void*)bulkCallback90_original)!=(uintptr_t)bulkCallback90_original || bulkCallbackIdentity((void*)bulkCallback90_linked)!=(uintptr_t)bulkCallback90_original)return 91;
 if(bulkCallbackIdentity((void*)bulkCallback91_original)!=(uintptr_t)bulkCallback91_original || bulkCallbackIdentity((void*)bulkCallback91_linked)!=(uintptr_t)bulkCallback91_original)return 92;
 if(bulkCallbackIdentity((void*)bulkCallback92_original)!=(uintptr_t)bulkCallback92_original || bulkCallbackIdentity((void*)bulkCallback92_linked)!=(uintptr_t)bulkCallback92_original)return 93;
 if(bulkCallbackIdentity((void*)bulkCallback93_original)!=(uintptr_t)bulkCallback93_original || bulkCallbackIdentity((void*)bulkCallback93_linked)!=(uintptr_t)bulkCallback93_original)return 94;
 if(bulkCallbackIdentity((void*)bulkCallback94_original)!=(uintptr_t)bulkCallback94_original || bulkCallbackIdentity((void*)bulkCallback94_linked)!=(uintptr_t)bulkCallback94_original)return 95;
 if(bulkCallbackIdentity((void*)bulkCallback95_original)!=(uintptr_t)bulkCallback95_original || bulkCallbackIdentity((void*)bulkCallback95_linked)!=(uintptr_t)bulkCallback95_original)return 96;
 if(bulkCallbackIdentity((void*)bulkCallback96_original)!=(uintptr_t)bulkCallback96_original || bulkCallbackIdentity((void*)bulkCallback96_linked)!=(uintptr_t)bulkCallback96_original)return 97;
 if(bulkCallbackIdentity((void*)bulkCallback97_original)!=(uintptr_t)bulkCallback97_original || bulkCallbackIdentity((void*)bulkCallback97_linked)!=(uintptr_t)bulkCallback97_original)return 98;
 if(bulkCallbackIdentity((void*)bulkCallback98_original)!=(uintptr_t)bulkCallback98_original || bulkCallbackIdentity((void*)bulkCallback98_linked)!=(uintptr_t)bulkCallback98_original)return 99;
 if(bulkCallbackIdentity((void*)bulkCallback99_original)!=(uintptr_t)bulkCallback99_original || bulkCallbackIdentity((void*)bulkCallback99_linked)!=(uintptr_t)bulkCallback99_original)return 100;
 if(bulkCallbackIdentity((void*)bulkCallback100_original)!=(uintptr_t)bulkCallback100_original || bulkCallbackIdentity((void*)bulkCallback100_linked)!=(uintptr_t)bulkCallback100_original)return 101;
 if(bulkCallbackIdentity((void*)bulkCallback101_original)!=(uintptr_t)bulkCallback101_original || bulkCallbackIdentity((void*)bulkCallback101_linked)!=(uintptr_t)bulkCallback101_original)return 102;
 if(bulkCallbackIdentity((void*)bulkCallback102_original)!=(uintptr_t)bulkCallback102_original || bulkCallbackIdentity((void*)bulkCallback102_linked)!=(uintptr_t)bulkCallback102_original)return 103;
 if(bulkCallbackIdentity((void*)bulkCallback103_original)!=(uintptr_t)bulkCallback103_original || bulkCallbackIdentity((void*)bulkCallback103_linked)!=(uintptr_t)bulkCallback103_original)return 104;
 if(bulkCallbackIdentity((void*)bulkCallback104_original)!=(uintptr_t)bulkCallback104_original || bulkCallbackIdentity((void*)bulkCallback104_linked)!=(uintptr_t)bulkCallback104_original)return 105;
 if(bulkCallbackIdentity((void*)bulkCallback105_original)!=(uintptr_t)bulkCallback105_original || bulkCallbackIdentity((void*)bulkCallback105_linked)!=(uintptr_t)bulkCallback105_original)return 106;
 if(bulkCallbackIdentity((void*)bulkCallback106_original)!=(uintptr_t)bulkCallback106_original || bulkCallbackIdentity((void*)bulkCallback106_linked)!=(uintptr_t)bulkCallback106_original)return 107;
 if(bulkCallbackIdentity((void*)bulkCallback107_original)!=(uintptr_t)bulkCallback107_original || bulkCallbackIdentity((void*)bulkCallback107_linked)!=(uintptr_t)bulkCallback107_original)return 108;
 if(bulkCallbackIdentity((void*)bulkCallback108_original)!=(uintptr_t)bulkCallback108_original || bulkCallbackIdentity((void*)bulkCallback108_linked)!=(uintptr_t)bulkCallback108_original)return 109;
 if(bulkCallbackIdentity((void*)bulkCallback109_original)!=(uintptr_t)bulkCallback109_original || bulkCallbackIdentity((void*)bulkCallback109_linked)!=(uintptr_t)bulkCallback109_original)return 110;
 if(bulkCallbackIdentity((void*)bulkCallback110_original)!=(uintptr_t)bulkCallback110_original || bulkCallbackIdentity((void*)bulkCallback110_linked)!=(uintptr_t)bulkCallback110_original)return 111;
 if(bulkCallbackIdentity((void*)bulkCallback111_original)!=(uintptr_t)bulkCallback111_original || bulkCallbackIdentity((void*)bulkCallback111_linked)!=(uintptr_t)bulkCallback111_original)return 112;
 if(bulkCallbackIdentity((void*)bulkCallback112_original)!=(uintptr_t)bulkCallback112_original || bulkCallbackIdentity((void*)bulkCallback112_linked)!=(uintptr_t)bulkCallback112_original)return 113;
 if(bulkCallbackIdentity((void*)bulkCallback113_original)!=(uintptr_t)bulkCallback113_original || bulkCallbackIdentity((void*)bulkCallback113_linked)!=(uintptr_t)bulkCallback113_original)return 114;
 if(bulkCallbackIdentity((void*)bulkCallback114_original)!=(uintptr_t)bulkCallback114_original || bulkCallbackIdentity((void*)bulkCallback114_linked)!=(uintptr_t)bulkCallback114_original)return 115;
 if(bulkCallbackIdentity((void*)bulkCallback115_original)!=(uintptr_t)bulkCallback115_original || bulkCallbackIdentity((void*)bulkCallback115_linked)!=(uintptr_t)bulkCallback115_original)return 116;
 if(bulkCallbackIdentity((void*)bulkCallback116_original)!=(uintptr_t)bulkCallback116_original || bulkCallbackIdentity((void*)bulkCallback116_linked)!=(uintptr_t)bulkCallback116_original)return 117;
 if(bulkCallbackIdentity((void*)bulkCallback117_original)!=(uintptr_t)bulkCallback117_original || bulkCallbackIdentity((void*)bulkCallback117_linked)!=(uintptr_t)bulkCallback117_original)return 118;
 if(bulkCallbackIdentity((void*)bulkCallback118_original)!=(uintptr_t)bulkCallback118_original || bulkCallbackIdentity((void*)bulkCallback118_linked)!=(uintptr_t)bulkCallback118_original)return 119;
 if(bulkCallbackIdentity((void*)bulkCallback119_original)!=(uintptr_t)bulkCallback119_original || bulkCallbackIdentity((void*)bulkCallback119_linked)!=(uintptr_t)bulkCallback119_original)return 120;
 if(bulkCallbackIdentity((void*)bulkCallback120_original)!=(uintptr_t)bulkCallback120_original || bulkCallbackIdentity((void*)bulkCallback120_linked)!=(uintptr_t)bulkCallback120_original)return 121;
 if(bulkCallbackIdentity((void*)bulkCallback121_original)!=(uintptr_t)bulkCallback121_original || bulkCallbackIdentity((void*)bulkCallback121_linked)!=(uintptr_t)bulkCallback121_original)return 122;
 if(bulkCallbackIdentity((void*)bulkCallback122_original)!=(uintptr_t)bulkCallback122_original || bulkCallbackIdentity((void*)bulkCallback122_linked)!=(uintptr_t)bulkCallback122_original)return 123;
 if(bulkCallbackIdentity((void*)bulkCallback123_original)!=(uintptr_t)bulkCallback123_original || bulkCallbackIdentity((void*)bulkCallback123_linked)!=(uintptr_t)bulkCallback123_original)return 124;
 if(bulkCallbackIdentity((void*)bulkCallback124_original)!=(uintptr_t)bulkCallback124_original || bulkCallbackIdentity((void*)bulkCallback124_linked)!=(uintptr_t)bulkCallback124_original)return 125;
 if(bulkCallbackIdentity((void*)bulkCallback125_original)!=(uintptr_t)bulkCallback125_original || bulkCallbackIdentity((void*)bulkCallback125_linked)!=(uintptr_t)bulkCallback125_original)return 126;
 if(bulkCallbackIdentity((void*)bulkCallback126_original)!=(uintptr_t)bulkCallback126_original || bulkCallbackIdentity((void*)bulkCallback126_linked)!=(uintptr_t)bulkCallback126_original)return 127;
 if(bulkCallbackIdentity((void*)bulkCallback127_original)!=(uintptr_t)bulkCallback127_original || bulkCallbackIdentity((void*)bulkCallback127_linked)!=(uintptr_t)bulkCallback127_original)return 128;
 if(bulkCallbackIdentity((void*)bulkCallback128_original)!=(uintptr_t)bulkCallback128_original || bulkCallbackIdentity((void*)bulkCallback128_linked)!=(uintptr_t)bulkCallback128_original)return 129;
 if(bulkCallbackIdentity((void*)bulkCallback129_original)!=(uintptr_t)bulkCallback129_original || bulkCallbackIdentity((void*)bulkCallback129_linked)!=(uintptr_t)bulkCallback129_original)return 130;
 if(bulkCallbackIdentity((void*)bulkCallback130_original)!=(uintptr_t)bulkCallback130_original || bulkCallbackIdentity((void*)bulkCallback130_linked)!=(uintptr_t)bulkCallback130_original)return 131;
 if(bulkCallbackIdentity((void*)bulkCallback131_original)!=(uintptr_t)bulkCallback131_original || bulkCallbackIdentity((void*)bulkCallback131_linked)!=(uintptr_t)bulkCallback131_original)return 132;
 if(bulkCallbackIdentity((void*)bulkCallback132_original)!=(uintptr_t)bulkCallback132_original || bulkCallbackIdentity((void*)bulkCallback132_linked)!=(uintptr_t)bulkCallback132_original)return 133;
 if(bulkCallbackIdentity((void*)bulkCallback133_original)!=(uintptr_t)bulkCallback133_original || bulkCallbackIdentity((void*)bulkCallback133_linked)!=(uintptr_t)bulkCallback133_original)return 134;
 if(bulkCallbackIdentity((void*)bulkCallback134_original)!=(uintptr_t)bulkCallback134_original || bulkCallbackIdentity((void*)bulkCallback134_linked)!=(uintptr_t)bulkCallback134_original)return 135;
 if(bulkCallbackIdentity((void*)bulkCallback135_original)!=(uintptr_t)bulkCallback135_original || bulkCallbackIdentity((void*)bulkCallback135_linked)!=(uintptr_t)bulkCallback135_original)return 136;
 if(bulkCallbackIdentity((void*)bulkCallback136_original)!=(uintptr_t)bulkCallback136_original || bulkCallbackIdentity((void*)bulkCallback136_linked)!=(uintptr_t)bulkCallback136_original)return 137;
 if(bulkCallbackIdentity((void*)bulkCallback137_original)!=(uintptr_t)bulkCallback137_original || bulkCallbackIdentity((void*)bulkCallback137_linked)!=(uintptr_t)bulkCallback137_original)return 138;
 if(bulkCallbackIdentity((void*)bulkCallback138_original)!=(uintptr_t)bulkCallback138_original || bulkCallbackIdentity((void*)bulkCallback138_linked)!=(uintptr_t)bulkCallback138_original)return 139;
 if(bulkCallbackIdentity((void*)bulkCallback139_original)!=(uintptr_t)bulkCallback139_original || bulkCallbackIdentity((void*)bulkCallback139_linked)!=(uintptr_t)bulkCallback139_original)return 140;
 if(bulkCallbackIdentity((void*)bulkCallback140_original)!=(uintptr_t)bulkCallback140_original || bulkCallbackIdentity((void*)bulkCallback140_linked)!=(uintptr_t)bulkCallback140_original)return 141;
 if(bulkCallbackIdentity((void*)bulkCallback141_original)!=(uintptr_t)bulkCallback141_original || bulkCallbackIdentity((void*)bulkCallback141_linked)!=(uintptr_t)bulkCallback141_original)return 142;
 if(bulkCallbackIdentity((void*)bulkCallback142_original)!=(uintptr_t)bulkCallback142_original || bulkCallbackIdentity((void*)bulkCallback142_linked)!=(uintptr_t)bulkCallback142_original)return 143;
 if(bulkCallbackIdentity((void*)bulkCallback143_original)!=(uintptr_t)bulkCallback143_original || bulkCallbackIdentity((void*)bulkCallback143_linked)!=(uintptr_t)bulkCallback143_original)return 144;
 if(bulkCallbackIdentity((void*)bulkCallback144_original)!=(uintptr_t)bulkCallback144_original || bulkCallbackIdentity((void*)bulkCallback144_linked)!=(uintptr_t)bulkCallback144_original)return 145;
 if(bulkCallbackIdentity((void*)bulkCallback145_original)!=(uintptr_t)bulkCallback145_original || bulkCallbackIdentity((void*)bulkCallback145_linked)!=(uintptr_t)bulkCallback145_original)return 146;
 if(bulkCallbackIdentity((void*)bulkCallback146_original)!=(uintptr_t)bulkCallback146_original || bulkCallbackIdentity((void*)bulkCallback146_linked)!=(uintptr_t)bulkCallback146_original)return 147;
 if(bulkCallbackIdentity((void*)bulkCallback147_original)!=(uintptr_t)bulkCallback147_original || bulkCallbackIdentity((void*)bulkCallback147_linked)!=(uintptr_t)bulkCallback147_original)return 148;
 if(bulkCallbackIdentity((void*)bulkCallback148_original)!=(uintptr_t)bulkCallback148_original || bulkCallbackIdentity((void*)bulkCallback148_linked)!=(uintptr_t)bulkCallback148_original)return 149;
 if(bulkCallbackIdentity((void*)bulkCallback149_original)!=(uintptr_t)bulkCallback149_original || bulkCallbackIdentity((void*)bulkCallback149_linked)!=(uintptr_t)bulkCallback149_original)return 150;
 if(bulkCallbackIdentity((void*)bulkCallback150_original)!=(uintptr_t)bulkCallback150_original || bulkCallbackIdentity((void*)bulkCallback150_linked)!=(uintptr_t)bulkCallback150_original)return 151;
 if(bulkCallbackIdentity((void*)bulkCallback151_original)!=(uintptr_t)bulkCallback151_original || bulkCallbackIdentity((void*)bulkCallback151_linked)!=(uintptr_t)bulkCallback151_original)return 152;
 if(bulkCallbackIdentity((void*)bulkCallback152_original)!=(uintptr_t)bulkCallback152_original || bulkCallbackIdentity((void*)bulkCallback152_linked)!=(uintptr_t)bulkCallback152_original)return 153;
 if(bulkCallbackIdentity((void*)bulkCallback153_original)!=(uintptr_t)bulkCallback153_original || bulkCallbackIdentity((void*)bulkCallback153_linked)!=(uintptr_t)bulkCallback153_original)return 154;
 if(bulkCallbackIdentity((void*)bulkCallback154_original)!=(uintptr_t)bulkCallback154_original || bulkCallbackIdentity((void*)bulkCallback154_linked)!=(uintptr_t)bulkCallback154_original)return 155;
 if(bulkCallbackIdentity((void*)bulkCallback155_original)!=(uintptr_t)bulkCallback155_original || bulkCallbackIdentity((void*)bulkCallback155_linked)!=(uintptr_t)bulkCallback155_original)return 156;
 if(bulkCallbackIdentity((void*)bulkCallback156_original)!=(uintptr_t)bulkCallback156_original || bulkCallbackIdentity((void*)bulkCallback156_linked)!=(uintptr_t)bulkCallback156_original)return 157;
 if(bulkCallbackIdentity((void*)bulkCallback157_original)!=(uintptr_t)bulkCallback157_original || bulkCallbackIdentity((void*)bulkCallback157_linked)!=(uintptr_t)bulkCallback157_original)return 158;
 if(bulkCallbackIdentity((void*)bulkCallback158_original)!=(uintptr_t)bulkCallback158_original || bulkCallbackIdentity((void*)bulkCallback158_linked)!=(uintptr_t)bulkCallback158_original)return 159;
 if(bulkCallbackIdentity((void*)bulkCallback159_original)!=(uintptr_t)bulkCallback159_original || bulkCallbackIdentity((void*)bulkCallback159_linked)!=(uintptr_t)bulkCallback159_original)return 160;
 if(bulkCallbackIdentity((void*)bulkCallback160_original)!=(uintptr_t)bulkCallback160_original || bulkCallbackIdentity((void*)bulkCallback160_linked)!=(uintptr_t)bulkCallback160_original)return 161;
 if(bulkCallbackIdentity((void*)bulkCallback161_original)!=(uintptr_t)bulkCallback161_original || bulkCallbackIdentity((void*)bulkCallback161_linked)!=(uintptr_t)bulkCallback161_original)return 162;
 if(bulkCallbackIdentity((void*)bulkCallback162_original)!=(uintptr_t)bulkCallback162_original || bulkCallbackIdentity((void*)bulkCallback162_linked)!=(uintptr_t)bulkCallback162_original)return 163;
 if(bulkCallbackIdentity((void*)bulkCallback163_original)!=(uintptr_t)bulkCallback163_original || bulkCallbackIdentity((void*)bulkCallback163_linked)!=(uintptr_t)bulkCallback163_original)return 164;
 if(bulkCallbackIdentity((void*)bulkCallback164_original)!=(uintptr_t)bulkCallback164_original || bulkCallbackIdentity((void*)bulkCallback164_linked)!=(uintptr_t)bulkCallback164_original)return 165;
 if(bulkCallbackIdentity((void*)bulkCallback165_original)!=(uintptr_t)bulkCallback165_original || bulkCallbackIdentity((void*)bulkCallback165_linked)!=(uintptr_t)bulkCallback165_original)return 166;
 if(bulkCallbackIdentity((void*)bulkCallback166_original)!=(uintptr_t)bulkCallback166_original || bulkCallbackIdentity((void*)bulkCallback166_linked)!=(uintptr_t)bulkCallback166_original)return 167;
 if(bulkCallbackIdentity((void*)bulkCallback167_original)!=(uintptr_t)bulkCallback167_original || bulkCallbackIdentity((void*)bulkCallback167_linked)!=(uintptr_t)bulkCallback167_original)return 168;
 if(bulkCallbackIdentity((void*)bulkCallback168_original)!=(uintptr_t)bulkCallback168_original || bulkCallbackIdentity((void*)bulkCallback168_linked)!=(uintptr_t)bulkCallback168_original)return 169;
 if(bulkCallbackIdentity((void*)bulkCallback169_original)!=(uintptr_t)bulkCallback169_original || bulkCallbackIdentity((void*)bulkCallback169_linked)!=(uintptr_t)bulkCallback169_original)return 170;
 if(bulkCallbackIdentity((void*)bulkCallback170_original)!=(uintptr_t)bulkCallback170_original || bulkCallbackIdentity((void*)bulkCallback170_linked)!=(uintptr_t)bulkCallback170_original)return 171;
 if(bulkCallbackIdentity((void*)bulkCallback171_original)!=(uintptr_t)bulkCallback171_original || bulkCallbackIdentity((void*)bulkCallback171_linked)!=(uintptr_t)bulkCallback171_original)return 172;
 if(bulkCallbackIdentity((void*)bulkCallback172_original)!=(uintptr_t)bulkCallback172_original || bulkCallbackIdentity((void*)bulkCallback172_linked)!=(uintptr_t)bulkCallback172_original)return 173;
 if(bulkCallbackIdentity((void*)bulkCallback173_original)!=(uintptr_t)bulkCallback173_original || bulkCallbackIdentity((void*)bulkCallback173_linked)!=(uintptr_t)bulkCallback173_original)return 174;
 if(bulkCallbackIdentity((void*)bulkCallback174_original)!=(uintptr_t)bulkCallback174_original || bulkCallbackIdentity((void*)bulkCallback174_linked)!=(uintptr_t)bulkCallback174_original)return 175;
 if(bulkCallbackIdentity((void*)bulkCallback175_original)!=(uintptr_t)bulkCallback175_original || bulkCallbackIdentity((void*)bulkCallback175_linked)!=(uintptr_t)bulkCallback175_original)return 176;
 if(bulkCallbackIdentity((void*)bulkCallback176_original)!=(uintptr_t)bulkCallback176_original || bulkCallbackIdentity((void*)bulkCallback176_linked)!=(uintptr_t)bulkCallback176_original)return 177;
 if(bulkCallbackIdentity((void*)bulkCallback177_original)!=(uintptr_t)bulkCallback177_original || bulkCallbackIdentity((void*)bulkCallback177_linked)!=(uintptr_t)bulkCallback177_original)return 178;
 if(bulkCallbackIdentity((void*)bulkCallback178_original)!=(uintptr_t)bulkCallback178_original || bulkCallbackIdentity((void*)bulkCallback178_linked)!=(uintptr_t)bulkCallback178_original)return 179;
 if(bulkCallbackIdentity((void*)bulkCallback179_original)!=(uintptr_t)bulkCallback179_original || bulkCallbackIdentity((void*)bulkCallback179_linked)!=(uintptr_t)bulkCallback179_original)return 180;
 if(bulkCallbackIdentity((void*)bulkCallback180_original)!=(uintptr_t)bulkCallback180_original || bulkCallbackIdentity((void*)bulkCallback180_linked)!=(uintptr_t)bulkCallback180_original)return 181;
 if(bulkCallbackIdentity((void*)bulkCallback181_original)!=(uintptr_t)bulkCallback181_original || bulkCallbackIdentity((void*)bulkCallback181_linked)!=(uintptr_t)bulkCallback181_original)return 182;
 if(bulkCallbackIdentity((void*)bulkCallback182_original)!=(uintptr_t)bulkCallback182_original || bulkCallbackIdentity((void*)bulkCallback182_linked)!=(uintptr_t)bulkCallback182_original)return 183;
 if(bulkCallbackIdentity((void*)bulkCallback183_original)!=(uintptr_t)bulkCallback183_original || bulkCallbackIdentity((void*)bulkCallback183_linked)!=(uintptr_t)bulkCallback183_original)return 184;
 if(bulkCallbackIdentity((void*)bulkCallback184_original)!=(uintptr_t)bulkCallback184_original || bulkCallbackIdentity((void*)bulkCallback184_linked)!=(uintptr_t)bulkCallback184_original)return 185;
 if(bulkCallbackIdentity((void*)bulkCallback185_original)!=(uintptr_t)bulkCallback185_original || bulkCallbackIdentity((void*)bulkCallback185_linked)!=(uintptr_t)bulkCallback185_original)return 186;
 if(bulkCallbackIdentity((void*)bulkCallback186_original)!=(uintptr_t)bulkCallback186_original || bulkCallbackIdentity((void*)bulkCallback186_linked)!=(uintptr_t)bulkCallback186_original)return 187;
 if(bulkCallbackIdentity((void*)bulkCallback187_original)!=(uintptr_t)bulkCallback187_original || bulkCallbackIdentity((void*)bulkCallback187_linked)!=(uintptr_t)bulkCallback187_original)return 188;
 if(bulkCallbackIdentity((void*)bulkCallback188_original)!=(uintptr_t)bulkCallback188_original || bulkCallbackIdentity((void*)bulkCallback188_linked)!=(uintptr_t)bulkCallback188_original)return 189;
 if(bulkCallbackIdentity((void*)bulkCallback189_original)!=(uintptr_t)bulkCallback189_original || bulkCallbackIdentity((void*)bulkCallback189_linked)!=(uintptr_t)bulkCallback189_original)return 190;
 if(bulkCallbackIdentity((void*)bulkCallback190_original)!=(uintptr_t)bulkCallback190_original || bulkCallbackIdentity((void*)bulkCallback190_linked)!=(uintptr_t)bulkCallback190_original)return 191;
 if(bulkCallbackIdentity((void*)bulkCallback191_original)!=(uintptr_t)bulkCallback191_original || bulkCallbackIdentity((void*)bulkCallback191_linked)!=(uintptr_t)bulkCallback191_original)return 192;
 if(bulkCallbackIdentity((void*)bulkCallback192_original)!=(uintptr_t)bulkCallback192_original || bulkCallbackIdentity((void*)bulkCallback192_linked)!=(uintptr_t)bulkCallback192_original)return 193;
 if(bulkCallbackIdentity((void*)bulkCallback193_original)!=(uintptr_t)bulkCallback193_original || bulkCallbackIdentity((void*)bulkCallback193_linked)!=(uintptr_t)bulkCallback193_original)return 194;
 if(bulkCallbackIdentity((void*)bulkCallback194_original)!=(uintptr_t)bulkCallback194_original || bulkCallbackIdentity((void*)bulkCallback194_linked)!=(uintptr_t)bulkCallback194_original)return 195;
 if(bulkCallbackIdentity((void*)bulkCallback195_original)!=(uintptr_t)bulkCallback195_original || bulkCallbackIdentity((void*)bulkCallback195_linked)!=(uintptr_t)bulkCallback195_original)return 196;
 if(bulkCallbackIdentity((void*)bulkCallback196_original)!=(uintptr_t)bulkCallback196_original || bulkCallbackIdentity((void*)bulkCallback196_linked)!=(uintptr_t)bulkCallback196_original)return 197;
 if(bulkCallbackIdentity((void*)bulkCallback197_original)!=(uintptr_t)bulkCallback197_original || bulkCallbackIdentity((void*)bulkCallback197_linked)!=(uintptr_t)bulkCallback197_original)return 198;
 if(bulkCallbackIdentity((void*)bulkCallback198_original)!=(uintptr_t)bulkCallback198_original || bulkCallbackIdentity((void*)bulkCallback198_linked)!=(uintptr_t)bulkCallback198_original)return 199;
 if(bulkCallbackIdentity((void*)bulkCallback199_original)!=(uintptr_t)bulkCallback199_original || bulkCallbackIdentity((void*)bulkCallback199_linked)!=(uintptr_t)bulkCallback199_original)return 200;
 if(bulkCallbackIdentity((void*)bulkCallback200_original)!=(uintptr_t)bulkCallback200_original || bulkCallbackIdentity((void*)bulkCallback200_linked)!=(uintptr_t)bulkCallback200_original)return 201;
 if(bulkCallbackIdentity((void*)bulkCallback201_original)!=(uintptr_t)bulkCallback201_original || bulkCallbackIdentity((void*)bulkCallback201_linked)!=(uintptr_t)bulkCallback201_original)return 202;
 if(bulkCallbackIdentity((void*)bulkCallback202_original)!=(uintptr_t)bulkCallback202_original || bulkCallbackIdentity((void*)bulkCallback202_linked)!=(uintptr_t)bulkCallback202_original)return 203;
 if(bulkCallbackIdentity((void*)bulkCallback203_original)!=(uintptr_t)bulkCallback203_original || bulkCallbackIdentity((void*)bulkCallback203_linked)!=(uintptr_t)bulkCallback203_original)return 204;
 if(bulkCallbackIdentity((void*)bulkCallback204_original)!=(uintptr_t)bulkCallback204_original || bulkCallbackIdentity((void*)bulkCallback204_linked)!=(uintptr_t)bulkCallback204_original)return 205;
 if(bulkCallbackIdentity((void*)bulkCallback205_original)!=(uintptr_t)bulkCallback205_original || bulkCallbackIdentity((void*)bulkCallback205_linked)!=(uintptr_t)bulkCallback205_original)return 206;
 if(bulkCallbackIdentity((void*)bulkCallback206_original)!=(uintptr_t)bulkCallback206_original || bulkCallbackIdentity((void*)bulkCallback206_linked)!=(uintptr_t)bulkCallback206_original)return 207;
 if(bulkCallbackIdentity((void*)bulkCallback207_original)!=(uintptr_t)bulkCallback207_original || bulkCallbackIdentity((void*)bulkCallback207_linked)!=(uintptr_t)bulkCallback207_original)return 208;
 if(bulkCallbackIdentity((void*)bulkCallback208_original)!=(uintptr_t)bulkCallback208_original || bulkCallbackIdentity((void*)bulkCallback208_linked)!=(uintptr_t)bulkCallback208_original)return 209;
 if(bulkCallbackIdentity((void*)bulkCallback209_original)!=(uintptr_t)bulkCallback209_original || bulkCallbackIdentity((void*)bulkCallback209_linked)!=(uintptr_t)bulkCallback209_original)return 210;
 if(bulkCallbackIdentity((void*)bulkCallback210_original)!=(uintptr_t)bulkCallback210_original || bulkCallbackIdentity((void*)bulkCallback210_linked)!=(uintptr_t)bulkCallback210_original)return 211;
 if(bulkCallbackIdentity((void*)bulkCallback211_original)!=(uintptr_t)bulkCallback211_original || bulkCallbackIdentity((void*)bulkCallback211_linked)!=(uintptr_t)bulkCallback211_original)return 212;
 if(bulkCallbackIdentity((void*)bulkCallback212_original)!=(uintptr_t)bulkCallback212_original || bulkCallbackIdentity((void*)bulkCallback212_linked)!=(uintptr_t)bulkCallback212_original)return 213;
 if(bulkCallbackIdentity((void*)bulkCallback213_original)!=(uintptr_t)bulkCallback213_original || bulkCallbackIdentity((void*)bulkCallback213_linked)!=(uintptr_t)bulkCallback213_original)return 214;
 if(bulkCallbackIdentity((void*)bulkCallback214_original)!=(uintptr_t)bulkCallback214_original || bulkCallbackIdentity((void*)bulkCallback214_linked)!=(uintptr_t)bulkCallback214_original)return 215;
 if(bulkCallbackIdentity((void*)bulkCallback215_original)!=(uintptr_t)bulkCallback215_original || bulkCallbackIdentity((void*)bulkCallback215_linked)!=(uintptr_t)bulkCallback215_original)return 216;
 if(bulkCallbackIdentity((void*)bulkCallback216_original)!=(uintptr_t)bulkCallback216_original || bulkCallbackIdentity((void*)bulkCallback216_linked)!=(uintptr_t)bulkCallback216_original)return 217;
 if(bulkCallbackIdentity((void*)bulkCallback217_original)!=(uintptr_t)bulkCallback217_original || bulkCallbackIdentity((void*)bulkCallback217_linked)!=(uintptr_t)bulkCallback217_original)return 218;
 if(bulkCallbackIdentity((void*)bulkCallback218_original)!=(uintptr_t)bulkCallback218_original || bulkCallbackIdentity((void*)bulkCallback218_linked)!=(uintptr_t)bulkCallback218_original)return 219;
 if(bulkCallbackIdentity((void*)bulkCallback219_original)!=(uintptr_t)bulkCallback219_original || bulkCallbackIdentity((void*)bulkCallback219_linked)!=(uintptr_t)bulkCallback219_original)return 220;
 if(bulkCallbackIdentity((void*)bulkCallback220_original)!=(uintptr_t)bulkCallback220_original || bulkCallbackIdentity((void*)bulkCallback220_linked)!=(uintptr_t)bulkCallback220_original)return 221;
 if(bulkCallbackIdentity((void*)bulkCallback221_original)!=(uintptr_t)bulkCallback221_original || bulkCallbackIdentity((void*)bulkCallback221_linked)!=(uintptr_t)bulkCallback221_original)return 222;
 if(bulkCallbackIdentity((void*)bulkCallback222_original)!=(uintptr_t)bulkCallback222_original || bulkCallbackIdentity((void*)bulkCallback222_linked)!=(uintptr_t)bulkCallback222_original)return 223;
 if(bulkCallbackIdentity((void*)bulkCallback223_original)!=(uintptr_t)bulkCallback223_original || bulkCallbackIdentity((void*)bulkCallback223_linked)!=(uintptr_t)bulkCallback223_original)return 224;
 if(bulkCallbackIdentity((void*)bulkCallback224_original)!=(uintptr_t)bulkCallback224_original || bulkCallbackIdentity((void*)bulkCallback224_linked)!=(uintptr_t)bulkCallback224_original)return 225;
 if(bulkCallbackIdentity((void*)bulkCallback225_original)!=(uintptr_t)bulkCallback225_original || bulkCallbackIdentity((void*)bulkCallback225_linked)!=(uintptr_t)bulkCallback225_original)return 226;
 if(bulkCallbackIdentity((void*)bulkCallback226_original)!=(uintptr_t)bulkCallback226_original || bulkCallbackIdentity((void*)bulkCallback226_linked)!=(uintptr_t)bulkCallback226_original)return 227;
 if(bulkCallbackIdentity((void*)bulkCallback227_original)!=(uintptr_t)bulkCallback227_original || bulkCallbackIdentity((void*)bulkCallback227_linked)!=(uintptr_t)bulkCallback227_original)return 228;
 if(bulkCallbackIdentity((void*)bulkCallback228_original)!=(uintptr_t)bulkCallback228_original || bulkCallbackIdentity((void*)bulkCallback228_linked)!=(uintptr_t)bulkCallback228_original)return 229;
 if(bulkCallbackIdentity((void*)bulkCallback229_original)!=(uintptr_t)bulkCallback229_original || bulkCallbackIdentity((void*)bulkCallback229_linked)!=(uintptr_t)bulkCallback229_original)return 230;
 if(bulkCallbackIdentity((void*)bulkCallback230_original)!=(uintptr_t)bulkCallback230_original || bulkCallbackIdentity((void*)bulkCallback230_linked)!=(uintptr_t)bulkCallback230_original)return 231;
 if(bulkCallbackIdentity((void*)bulkCallback231_original)!=(uintptr_t)bulkCallback231_original || bulkCallbackIdentity((void*)bulkCallback231_linked)!=(uintptr_t)bulkCallback231_original)return 232;
 if(bulkCallbackIdentity((void*)bulkCallback232_original)!=(uintptr_t)bulkCallback232_original || bulkCallbackIdentity((void*)bulkCallback232_linked)!=(uintptr_t)bulkCallback232_original)return 233;
 if(bulkCallbackIdentity((void*)bulkCallback233_original)!=(uintptr_t)bulkCallback233_original || bulkCallbackIdentity((void*)bulkCallback233_linked)!=(uintptr_t)bulkCallback233_original)return 234;
 if(bulkCallbackIdentity((void*)bulkCallback234_original)!=(uintptr_t)bulkCallback234_original || bulkCallbackIdentity((void*)bulkCallback234_linked)!=(uintptr_t)bulkCallback234_original)return 235;
 if(bulkCallbackIdentity((void*)bulkCallback235_original)!=(uintptr_t)bulkCallback235_original || bulkCallbackIdentity((void*)bulkCallback235_linked)!=(uintptr_t)bulkCallback235_original)return 236;
 if(bulkCallbackIdentity((void*)bulkCallback236_original)!=(uintptr_t)bulkCallback236_original || bulkCallbackIdentity((void*)bulkCallback236_linked)!=(uintptr_t)bulkCallback236_original)return 237;
 if(bulkCallbackIdentity((void*)bulkCallback237_original)!=(uintptr_t)bulkCallback237_original || bulkCallbackIdentity((void*)bulkCallback237_linked)!=(uintptr_t)bulkCallback237_original)return 238;
 if(bulkCallbackIdentity((void*)bulkCallback238_original)!=(uintptr_t)bulkCallback238_original || bulkCallbackIdentity((void*)bulkCallback238_linked)!=(uintptr_t)bulkCallback238_original)return 239;
 if(bulkCallbackIdentity((void*)bulkCallback239_original)!=(uintptr_t)bulkCallback239_original || bulkCallbackIdentity((void*)bulkCallback239_linked)!=(uintptr_t)bulkCallback239_original)return 240;
 if(bulkCallbackIdentity((void*)bulkCallback240_original)!=(uintptr_t)bulkCallback240_original || bulkCallbackIdentity((void*)bulkCallback240_linked)!=(uintptr_t)bulkCallback240_original)return 241;
 if(bulkCallbackIdentity((void*)bulkCallback241_original)!=(uintptr_t)bulkCallback241_original || bulkCallbackIdentity((void*)bulkCallback241_linked)!=(uintptr_t)bulkCallback241_original)return 242;
 if(bulkCallbackIdentity((void*)bulkCallback242_original)!=(uintptr_t)bulkCallback242_original || bulkCallbackIdentity((void*)bulkCallback242_linked)!=(uintptr_t)bulkCallback242_original)return 243;
 if(bulkCallbackIdentity((void*)bulkCallback243_original)!=(uintptr_t)bulkCallback243_original || bulkCallbackIdentity((void*)bulkCallback243_linked)!=(uintptr_t)bulkCallback243_original)return 244;
 if(bulkCallbackIdentity((void*)bulkCallback244_original)!=(uintptr_t)bulkCallback244_original || bulkCallbackIdentity((void*)bulkCallback244_linked)!=(uintptr_t)bulkCallback244_original)return 245;
 if(bulkCallbackIdentity((void*)bulkCallback245_original)!=(uintptr_t)bulkCallback245_original || bulkCallbackIdentity((void*)bulkCallback245_linked)!=(uintptr_t)bulkCallback245_original)return 246;
 if(bulkCallbackIdentity((void*)bulkCallback246_original)!=(uintptr_t)bulkCallback246_original || bulkCallbackIdentity((void*)bulkCallback246_linked)!=(uintptr_t)bulkCallback246_original)return 247;
 if(bulkCallbackIdentity((void*)bulkCallback247_original)!=(uintptr_t)bulkCallback247_original || bulkCallbackIdentity((void*)bulkCallback247_linked)!=(uintptr_t)bulkCallback247_original)return 248;
 if(bulkCallbackIdentity((void*)bulkCallback248_original)!=(uintptr_t)bulkCallback248_original || bulkCallbackIdentity((void*)bulkCallback248_linked)!=(uintptr_t)bulkCallback248_original)return 249;
 if(bulkCallbackIdentity((void*)bulkCallback249_original)!=(uintptr_t)bulkCallback249_original || bulkCallbackIdentity((void*)bulkCallback249_linked)!=(uintptr_t)bulkCallback249_original)return 250;
 if(bulkCallbackIdentity((void*)bulkCallback250_original)!=(uintptr_t)bulkCallback250_original || bulkCallbackIdentity((void*)bulkCallback250_linked)!=(uintptr_t)bulkCallback250_original)return 251;
 if(bulkCallbackIdentity((void*)bulkCallback251_original)!=(uintptr_t)bulkCallback251_original || bulkCallbackIdentity((void*)bulkCallback251_linked)!=(uintptr_t)bulkCallback251_original)return 252;
 if(bulkCallbackIdentity((void*)bulkCallback252_original)!=(uintptr_t)bulkCallback252_original || bulkCallbackIdentity((void*)bulkCallback252_linked)!=(uintptr_t)bulkCallback252_original)return 253;
 if(bulkCallbackIdentity((void*)bulkCallback253_original)!=(uintptr_t)bulkCallback253_original || bulkCallbackIdentity((void*)bulkCallback253_linked)!=(uintptr_t)bulkCallback253_original)return 254;
 if(bulkCallbackIdentity((void*)bulkCallback254_original)!=(uintptr_t)bulkCallback254_original || bulkCallbackIdentity((void*)bulkCallback254_linked)!=(uintptr_t)bulkCallback254_original)return 255;
 if(bulkCallbackIdentity((void*)bulkCallback255_original)!=(uintptr_t)bulkCallback255_original || bulkCallbackIdentity((void*)bulkCallback255_linked)!=(uintptr_t)bulkCallback255_original)return 256;
 if(bulkCallbackIdentity((void*)bulkCallback256_original)!=(uintptr_t)bulkCallback256_original || bulkCallbackIdentity((void*)bulkCallback256_linked)!=(uintptr_t)bulkCallback256_original)return 257;
 if(bulkCallbackIdentity((void*)bulkCallback257_original)!=(uintptr_t)bulkCallback257_original || bulkCallbackIdentity((void*)bulkCallback257_linked)!=(uintptr_t)bulkCallback257_original)return 258;
 if(bulkCallbackIdentity((void*)bulkCallback258_original)!=(uintptr_t)bulkCallback258_original || bulkCallbackIdentity((void*)bulkCallback258_linked)!=(uintptr_t)bulkCallback258_original)return 259;
 if(bulkCallbackIdentity((void*)bulkCallback259_original)!=(uintptr_t)bulkCallback259_original || bulkCallbackIdentity((void*)bulkCallback259_linked)!=(uintptr_t)bulkCallback259_original)return 260;
 if(bulkCallbackIdentity((void*)bulkCallback260_original)!=(uintptr_t)bulkCallback260_original || bulkCallbackIdentity((void*)bulkCallback260_linked)!=(uintptr_t)bulkCallback260_original)return 261;
 if(bulkCallbackIdentity((void*)bulkCallback261_original)!=(uintptr_t)bulkCallback261_original || bulkCallbackIdentity((void*)bulkCallback261_linked)!=(uintptr_t)bulkCallback261_original)return 262;
 if(bulkCallbackIdentity((void*)bulkCallback262_original)!=(uintptr_t)bulkCallback262_original || bulkCallbackIdentity((void*)bulkCallback262_linked)!=(uintptr_t)bulkCallback262_original)return 263;
 if(bulkCallbackIdentity((void*)bulkCallback263_original)!=(uintptr_t)bulkCallback263_original || bulkCallbackIdentity((void*)bulkCallback263_linked)!=(uintptr_t)bulkCallback263_original)return 264;
 if(bulkCallbackIdentity((void*)bulkCallback264_original)!=(uintptr_t)bulkCallback264_original || bulkCallbackIdentity((void*)bulkCallback264_linked)!=(uintptr_t)bulkCallback264_original)return 265;
 if(bulkCallbackIdentity((void*)bulkCallback265_original)!=(uintptr_t)bulkCallback265_original || bulkCallbackIdentity((void*)bulkCallback265_linked)!=(uintptr_t)bulkCallback265_original)return 266;
 if(bulkCallbackIdentity((void*)bulkCallback266_original)!=(uintptr_t)bulkCallback266_original || bulkCallbackIdentity((void*)bulkCallback266_linked)!=(uintptr_t)bulkCallback266_original)return 267;
 if(bulkCallbackIdentity((void*)bulkCallback267_original)!=(uintptr_t)bulkCallback267_original || bulkCallbackIdentity((void*)bulkCallback267_linked)!=(uintptr_t)bulkCallback267_original)return 268;
 if(bulkCallbackIdentity((void*)bulkCallback268_original)!=(uintptr_t)bulkCallback268_original || bulkCallbackIdentity((void*)bulkCallback268_linked)!=(uintptr_t)bulkCallback268_original)return 269;
 if(bulkCallbackIdentity((void*)bulkCallback269_original)!=(uintptr_t)bulkCallback269_original || bulkCallbackIdentity((void*)bulkCallback269_linked)!=(uintptr_t)bulkCallback269_original)return 270;
 if(bulkCallbackIdentity((void*)bulkCallback270_original)!=(uintptr_t)bulkCallback270_original || bulkCallbackIdentity((void*)bulkCallback270_linked)!=(uintptr_t)bulkCallback270_original)return 271;
 if(bulkCallbackIdentity((void*)bulkCallback271_original)!=(uintptr_t)bulkCallback271_original || bulkCallbackIdentity((void*)bulkCallback271_linked)!=(uintptr_t)bulkCallback271_original)return 272;
 if(bulkCallbackIdentity((void*)bulkCallback272_original)!=(uintptr_t)bulkCallback272_original || bulkCallbackIdentity((void*)bulkCallback272_linked)!=(uintptr_t)bulkCallback272_original)return 273;
 if(bulkCallbackIdentity((void*)bulkCallback273_original)!=(uintptr_t)bulkCallback273_original || bulkCallbackIdentity((void*)bulkCallback273_linked)!=(uintptr_t)bulkCallback273_original)return 274;
 if(bulkCallbackIdentity((void*)bulkCallback274_original)!=(uintptr_t)bulkCallback274_original || bulkCallbackIdentity((void*)bulkCallback274_linked)!=(uintptr_t)bulkCallback274_original)return 275;
 if(bulkCallbackIdentity((void*)bulkCallback275_original)!=(uintptr_t)bulkCallback275_original || bulkCallbackIdentity((void*)bulkCallback275_linked)!=(uintptr_t)bulkCallback275_original)return 276;
 if(bulkCallbackIdentity((void*)bulkCallback276_original)!=(uintptr_t)bulkCallback276_original || bulkCallbackIdentity((void*)bulkCallback276_linked)!=(uintptr_t)bulkCallback276_original)return 277;
 if(bulkCallbackIdentity((void*)bulkCallback277_original)!=(uintptr_t)bulkCallback277_original || bulkCallbackIdentity((void*)bulkCallback277_linked)!=(uintptr_t)bulkCallback277_original)return 278;
 if(bulkCallbackIdentity((void*)bulkCallback278_original)!=(uintptr_t)bulkCallback278_original || bulkCallbackIdentity((void*)bulkCallback278_linked)!=(uintptr_t)bulkCallback278_original)return 279;
 if(bulkCallbackIdentity((void*)bulkCallback279_original)!=(uintptr_t)bulkCallback279_original || bulkCallbackIdentity((void*)bulkCallback279_linked)!=(uintptr_t)bulkCallback279_original)return 280;
 if(bulkCallbackIdentity((void*)bulkCallback280_original)!=(uintptr_t)bulkCallback280_original || bulkCallbackIdentity((void*)bulkCallback280_linked)!=(uintptr_t)bulkCallback280_original)return 281;
 if(bulkCallbackIdentity((void*)bulkCallback281_original)!=(uintptr_t)bulkCallback281_original || bulkCallbackIdentity((void*)bulkCallback281_linked)!=(uintptr_t)bulkCallback281_original)return 282;
 if(bulkCallbackIdentity((void*)bulkCallback282_original)!=(uintptr_t)bulkCallback282_original || bulkCallbackIdentity((void*)bulkCallback282_linked)!=(uintptr_t)bulkCallback282_original)return 283;
 if(bulkCallbackIdentity((void*)bulkCallback283_original)!=(uintptr_t)bulkCallback283_original || bulkCallbackIdentity((void*)bulkCallback283_linked)!=(uintptr_t)bulkCallback283_original)return 284;
 if(bulkCallbackIdentity((void*)bulkCallback284_original)!=(uintptr_t)bulkCallback284_original || bulkCallbackIdentity((void*)bulkCallback284_linked)!=(uintptr_t)bulkCallback284_original)return 285;
 if(bulkCallbackIdentity((void*)bulkCallback285_original)!=(uintptr_t)bulkCallback285_original || bulkCallbackIdentity((void*)bulkCallback285_linked)!=(uintptr_t)bulkCallback285_original)return 286;
 if(bulkCallbackIdentity((void*)bulkCallback286_original)!=(uintptr_t)bulkCallback286_original || bulkCallbackIdentity((void*)bulkCallback286_linked)!=(uintptr_t)bulkCallback286_original)return 287;
 if(bulkCallbackIdentity((void*)bulkCallback287_original)!=(uintptr_t)bulkCallback287_original || bulkCallbackIdentity((void*)bulkCallback287_linked)!=(uintptr_t)bulkCallback287_original)return 288;
 if(bulkCallbackIdentity((void*)bulkCallback288_original)!=(uintptr_t)bulkCallback288_original || bulkCallbackIdentity((void*)bulkCallback288_linked)!=(uintptr_t)bulkCallback288_original)return 289;
 if(bulkCallbackIdentity((void*)bulkCallback289_original)!=(uintptr_t)bulkCallback289_original || bulkCallbackIdentity((void*)bulkCallback289_linked)!=(uintptr_t)bulkCallback289_original)return 290;
 if(bulkCallbackIdentity((void*)bulkCallback290_original)!=(uintptr_t)bulkCallback290_original || bulkCallbackIdentity((void*)bulkCallback290_linked)!=(uintptr_t)bulkCallback290_original)return 291;
 if(bulkCallbackIdentity((void*)bulkCallback291_original)!=(uintptr_t)bulkCallback291_original || bulkCallbackIdentity((void*)bulkCallback291_linked)!=(uintptr_t)bulkCallback291_original)return 292;
 if(bulkCallbackIdentity((void*)bulkCallback292_original)!=(uintptr_t)bulkCallback292_original || bulkCallbackIdentity((void*)bulkCallback292_linked)!=(uintptr_t)bulkCallback292_original)return 293;
 if(bulkCallbackIdentity((void*)bulkCallback293_original)!=(uintptr_t)bulkCallback293_original || bulkCallbackIdentity((void*)bulkCallback293_linked)!=(uintptr_t)bulkCallback293_original)return 294;
 if(bulkCallbackIdentity((void*)bulkCallback294_original)!=(uintptr_t)bulkCallback294_original || bulkCallbackIdentity((void*)bulkCallback294_linked)!=(uintptr_t)bulkCallback294_original)return 295;
 if(bulkCallbackIdentity((void*)bulkCallback295_original)!=(uintptr_t)bulkCallback295_original || bulkCallbackIdentity((void*)bulkCallback295_linked)!=(uintptr_t)bulkCallback295_original)return 296;
 if(bulkCallbackIdentity((void*)bulkCallback296_original)!=(uintptr_t)bulkCallback296_original || bulkCallbackIdentity((void*)bulkCallback296_linked)!=(uintptr_t)bulkCallback296_original)return 297;
 if(bulkCallbackIdentity((void*)bulkCallback297_original)!=(uintptr_t)bulkCallback297_original || bulkCallbackIdentity((void*)bulkCallback297_linked)!=(uintptr_t)bulkCallback297_original)return 298;
 if(bulkCallbackIdentity((void*)bulkCallback298_original)!=(uintptr_t)bulkCallback298_original || bulkCallbackIdentity((void*)bulkCallback298_linked)!=(uintptr_t)bulkCallback298_original)return 299;
 if(bulkCallbackIdentity((void*)bulkCallback299_original)!=(uintptr_t)bulkCallback299_original || bulkCallbackIdentity((void*)bulkCallback299_linked)!=(uintptr_t)bulkCallback299_original)return 300;
 if(bulkCallbackIdentity((void*)bulkCallback300_original)!=(uintptr_t)bulkCallback300_original || bulkCallbackIdentity((void*)bulkCallback300_linked)!=(uintptr_t)bulkCallback300_original)return 301;
 if(bulkCallbackIdentity((void*)bulkCallback301_original)!=(uintptr_t)bulkCallback301_original || bulkCallbackIdentity((void*)bulkCallback301_linked)!=(uintptr_t)bulkCallback301_original)return 302;
 if(bulkCallbackIdentity((void*)bulkCallback302_original)!=(uintptr_t)bulkCallback302_original || bulkCallbackIdentity((void*)bulkCallback302_linked)!=(uintptr_t)bulkCallback302_original)return 303;
 if(bulkCallbackIdentity((void*)bulkCallback303_original)!=(uintptr_t)bulkCallback303_original || bulkCallbackIdentity((void*)bulkCallback303_linked)!=(uintptr_t)bulkCallback303_original)return 304;
 if(bulkCallbackIdentity((void*)bulkCallback304_original)!=(uintptr_t)bulkCallback304_original || bulkCallbackIdentity((void*)bulkCallback304_linked)!=(uintptr_t)bulkCallback304_original)return 305;
 if(bulkCallbackIdentity((void*)bulkCallback305_original)!=(uintptr_t)bulkCallback305_original || bulkCallbackIdentity((void*)bulkCallback305_linked)!=(uintptr_t)bulkCallback305_original)return 306;
 if(bulkCallbackIdentity((void*)bulkCallback306_original)!=(uintptr_t)bulkCallback306_original || bulkCallbackIdentity((void*)bulkCallback306_linked)!=(uintptr_t)bulkCallback306_original)return 307;
 if(bulkCallbackIdentity((void*)bulkCallback307_original)!=(uintptr_t)bulkCallback307_original || bulkCallbackIdentity((void*)bulkCallback307_linked)!=(uintptr_t)bulkCallback307_original)return 308;
 if(bulkCallbackIdentity((void*)bulkCallback308_original)!=(uintptr_t)bulkCallback308_original || bulkCallbackIdentity((void*)bulkCallback308_linked)!=(uintptr_t)bulkCallback308_original)return 309;
 if(bulkCallbackIdentity((void*)bulkCallback309_original)!=(uintptr_t)bulkCallback309_original || bulkCallbackIdentity((void*)bulkCallback309_linked)!=(uintptr_t)bulkCallback309_original)return 310;
 if(bulkCallbackIdentity((void*)bulkCallback310_original)!=(uintptr_t)bulkCallback310_original || bulkCallbackIdentity((void*)bulkCallback310_linked)!=(uintptr_t)bulkCallback310_original)return 311;
 if(bulkCallbackIdentity((void*)bulkCallback311_original)!=(uintptr_t)bulkCallback311_original || bulkCallbackIdentity((void*)bulkCallback311_linked)!=(uintptr_t)bulkCallback311_original)return 312;
 if(bulkCallbackIdentity((void*)bulkCallback312_original)!=(uintptr_t)bulkCallback312_original || bulkCallbackIdentity((void*)bulkCallback312_linked)!=(uintptr_t)bulkCallback312_original)return 313;
 if(bulkCallbackIdentity((void*)bulkCallback313_original)!=(uintptr_t)bulkCallback313_original || bulkCallbackIdentity((void*)bulkCallback313_linked)!=(uintptr_t)bulkCallback313_original)return 314;
 if(bulkCallbackIdentity((void*)bulkCallback314_original)!=(uintptr_t)bulkCallback314_original || bulkCallbackIdentity((void*)bulkCallback314_linked)!=(uintptr_t)bulkCallback314_original)return 315;
 if(bulkCallbackIdentity((void*)bulkCallback315_original)!=(uintptr_t)bulkCallback315_original || bulkCallbackIdentity((void*)bulkCallback315_linked)!=(uintptr_t)bulkCallback315_original)return 316;
 if(bulkCallbackIdentity((void*)bulkCallback316_original)!=(uintptr_t)bulkCallback316_original || bulkCallbackIdentity((void*)bulkCallback316_linked)!=(uintptr_t)bulkCallback316_original)return 317;
 if(bulkCallbackIdentity((void*)bulkCallback317_original)!=(uintptr_t)bulkCallback317_original || bulkCallbackIdentity((void*)bulkCallback317_linked)!=(uintptr_t)bulkCallback317_original)return 318;
 if(bulkCallbackIdentity((void*)bulkCallback318_original)!=(uintptr_t)bulkCallback318_original || bulkCallbackIdentity((void*)bulkCallback318_linked)!=(uintptr_t)bulkCallback318_original)return 319;
 if(bulkCallbackIdentity((void*)bulkCallback319_original)!=(uintptr_t)bulkCallback319_original || bulkCallbackIdentity((void*)bulkCallback319_linked)!=(uintptr_t)bulkCallback319_original)return 320;
 if(bulkCallbackIdentity((void*)bulkCallback320_original)!=(uintptr_t)bulkCallback320_original || bulkCallbackIdentity((void*)bulkCallback320_linked)!=(uintptr_t)bulkCallback320_original)return 321;
 if(bulkCallbackIdentity((void*)bulkCallback321_original)!=(uintptr_t)bulkCallback321_original || bulkCallbackIdentity((void*)bulkCallback321_linked)!=(uintptr_t)bulkCallback321_original)return 322;
 if(bulkCallbackIdentity((void*)bulkCallback322_original)!=(uintptr_t)bulkCallback322_original || bulkCallbackIdentity((void*)bulkCallback322_linked)!=(uintptr_t)bulkCallback322_original)return 323;
 if(bulkCallbackIdentity((void*)bulkCallback323_original)!=(uintptr_t)bulkCallback323_original || bulkCallbackIdentity((void*)bulkCallback323_linked)!=(uintptr_t)bulkCallback323_original)return 324;
 if(bulkCallbackIdentity((void*)bulkCallback324_original)!=(uintptr_t)bulkCallback324_original || bulkCallbackIdentity((void*)bulkCallback324_linked)!=(uintptr_t)bulkCallback324_original)return 325;
 if(bulkCallbackIdentity((void*)bulkCallback325_original)!=(uintptr_t)bulkCallback325_original || bulkCallbackIdentity((void*)bulkCallback325_linked)!=(uintptr_t)bulkCallback325_original)return 326;
 if(bulkCallbackIdentity((void*)bulkCallback326_original)!=(uintptr_t)bulkCallback326_original || bulkCallbackIdentity((void*)bulkCallback326_linked)!=(uintptr_t)bulkCallback326_original)return 327;
 if(bulkCallbackIdentity((void*)bulkCallback327_original)!=(uintptr_t)bulkCallback327_original || bulkCallbackIdentity((void*)bulkCallback327_linked)!=(uintptr_t)bulkCallback327_original)return 328;
 if(bulkCallbackIdentity((void*)bulkCallback328_original)!=(uintptr_t)bulkCallback328_original || bulkCallbackIdentity((void*)bulkCallback328_linked)!=(uintptr_t)bulkCallback328_original)return 329;
 if(bulkCallbackIdentity((void*)bulkCallback329_original)!=(uintptr_t)bulkCallback329_original || bulkCallbackIdentity((void*)bulkCallback329_linked)!=(uintptr_t)bulkCallback329_original)return 330;
 if(bulkCallbackIdentity((void*)bulkCallback330_original)!=(uintptr_t)bulkCallback330_original || bulkCallbackIdentity((void*)bulkCallback330_linked)!=(uintptr_t)bulkCallback330_original)return 331;
 if(bulkCallbackIdentity((void*)bulkCallback331_original)!=(uintptr_t)bulkCallback331_original || bulkCallbackIdentity((void*)bulkCallback331_linked)!=(uintptr_t)bulkCallback331_original)return 332;
 if(bulkCallbackIdentity((void*)bulkCallback332_original)!=(uintptr_t)bulkCallback332_original || bulkCallbackIdentity((void*)bulkCallback332_linked)!=(uintptr_t)bulkCallback332_original)return 333;
 if(bulkCallbackIdentity((void*)bulkCallback333_original)!=(uintptr_t)bulkCallback333_original || bulkCallbackIdentity((void*)bulkCallback333_linked)!=(uintptr_t)bulkCallback333_original)return 334;
 if(bulkCallbackIdentity((void*)bulkCallback334_original)!=(uintptr_t)bulkCallback334_original || bulkCallbackIdentity((void*)bulkCallback334_linked)!=(uintptr_t)bulkCallback334_original)return 335;
 if(bulkCallbackIdentity((void*)bulkCallback335_original)!=(uintptr_t)bulkCallback335_original || bulkCallbackIdentity((void*)bulkCallback335_linked)!=(uintptr_t)bulkCallback335_original)return 336;
 if(bulkCallbackIdentity((void*)bulkCallback336_original)!=(uintptr_t)bulkCallback336_original || bulkCallbackIdentity((void*)bulkCallback336_linked)!=(uintptr_t)bulkCallback336_original)return 337;
 if(bulkCallbackIdentity((void*)bulkCallback337_original)!=(uintptr_t)bulkCallback337_original || bulkCallbackIdentity((void*)bulkCallback337_linked)!=(uintptr_t)bulkCallback337_original)return 338;
 if(bulkCallbackIdentity((void*)bulkCallback338_original)!=(uintptr_t)bulkCallback338_original || bulkCallbackIdentity((void*)bulkCallback338_linked)!=(uintptr_t)bulkCallback338_original)return 339;
 if(bulkCallbackIdentity((void*)bulkCallback339_original)!=(uintptr_t)bulkCallback339_original || bulkCallbackIdentity((void*)bulkCallback339_linked)!=(uintptr_t)bulkCallback339_original)return 340;
 if(bulkCallbackIdentity((void*)bulkCallback340_original)!=(uintptr_t)bulkCallback340_original || bulkCallbackIdentity((void*)bulkCallback340_linked)!=(uintptr_t)bulkCallback340_original)return 341;
 if(bulkCallbackIdentity((void*)bulkCallback341_original)!=(uintptr_t)bulkCallback341_original || bulkCallbackIdentity((void*)bulkCallback341_linked)!=(uintptr_t)bulkCallback341_original)return 342;
 if(bulkCallbackIdentity((void*)bulkCallback342_original)!=(uintptr_t)bulkCallback342_original || bulkCallbackIdentity((void*)bulkCallback342_linked)!=(uintptr_t)bulkCallback342_original)return 343;
 if(bulkCallbackIdentity((void*)bulkCallback343_original)!=(uintptr_t)bulkCallback343_original || bulkCallbackIdentity((void*)bulkCallback343_linked)!=(uintptr_t)bulkCallback343_original)return 344;
 if(bulkCallbackIdentity((void*)bulkCallback344_original)!=(uintptr_t)bulkCallback344_original || bulkCallbackIdentity((void*)bulkCallback344_linked)!=(uintptr_t)bulkCallback344_original)return 345;
 if(bulkCallbackIdentity((void*)bulkCallback345_original)!=(uintptr_t)bulkCallback345_original || bulkCallbackIdentity((void*)bulkCallback345_linked)!=(uintptr_t)bulkCallback345_original)return 346;
 if(bulkCallbackIdentity((void*)bulkCallback346_original)!=(uintptr_t)bulkCallback346_original || bulkCallbackIdentity((void*)bulkCallback346_linked)!=(uintptr_t)bulkCallback346_original)return 347;
 if(bulkCallbackIdentity((void*)bulkCallback347_original)!=(uintptr_t)bulkCallback347_original || bulkCallbackIdentity((void*)bulkCallback347_linked)!=(uintptr_t)bulkCallback347_original)return 348;
 if(bulkCallbackIdentity((void*)bulkCallback348_original)!=(uintptr_t)bulkCallback348_original || bulkCallbackIdentity((void*)bulkCallback348_linked)!=(uintptr_t)bulkCallback348_original)return 349;
 if(bulkCallbackIdentity((void*)bulkCallback349_original)!=(uintptr_t)bulkCallback349_original || bulkCallbackIdentity((void*)bulkCallback349_linked)!=(uintptr_t)bulkCallback349_original)return 350;
 if(bulkCallbackIdentity((void*)bulkCallback350_original)!=(uintptr_t)bulkCallback350_original || bulkCallbackIdentity((void*)bulkCallback350_linked)!=(uintptr_t)bulkCallback350_original)return 351;
 if(bulkCallbackIdentity((void*)bulkCallback351_original)!=(uintptr_t)bulkCallback351_original || bulkCallbackIdentity((void*)bulkCallback351_linked)!=(uintptr_t)bulkCallback351_original)return 352;
 if(bulkCallbackIdentity((void*)bulkCallback352_original)!=(uintptr_t)bulkCallback352_original || bulkCallbackIdentity((void*)bulkCallback352_linked)!=(uintptr_t)bulkCallback352_original)return 353;
 if(bulkCallbackIdentity((void*)bulkCallback353_original)!=(uintptr_t)bulkCallback353_original || bulkCallbackIdentity((void*)bulkCallback353_linked)!=(uintptr_t)bulkCallback353_original)return 354;
 if(bulkCallbackIdentity((void*)bulkCallback354_original)!=(uintptr_t)bulkCallback354_original || bulkCallbackIdentity((void*)bulkCallback354_linked)!=(uintptr_t)bulkCallback354_original)return 355;
 if(bulkCallbackIdentity((void*)bulkCallback355_original)!=(uintptr_t)bulkCallback355_original || bulkCallbackIdentity((void*)bulkCallback355_linked)!=(uintptr_t)bulkCallback355_original)return 356;
 if(bulkCallbackIdentity((void*)bulkCallback356_original)!=(uintptr_t)bulkCallback356_original || bulkCallbackIdentity((void*)bulkCallback356_linked)!=(uintptr_t)bulkCallback356_original)return 357;
 if(bulkCallbackIdentity((void*)bulkCallback357_original)!=(uintptr_t)bulkCallback357_original || bulkCallbackIdentity((void*)bulkCallback357_linked)!=(uintptr_t)bulkCallback357_original)return 358;
 if(bulkCallbackIdentity((void*)bulkCallback358_original)!=(uintptr_t)bulkCallback358_original || bulkCallbackIdentity((void*)bulkCallback358_linked)!=(uintptr_t)bulkCallback358_original)return 359;
 if(bulkCallbackIdentity((void*)bulkCallback359_original)!=(uintptr_t)bulkCallback359_original || bulkCallbackIdentity((void*)bulkCallback359_linked)!=(uintptr_t)bulkCallback359_original)return 360;
 if(bulkCallbackIdentity((void*)bulkCallback360_original)!=(uintptr_t)bulkCallback360_original || bulkCallbackIdentity((void*)bulkCallback360_linked)!=(uintptr_t)bulkCallback360_original)return 361;
 if(bulkCallbackIdentity((void*)bulkCallback361_original)!=(uintptr_t)bulkCallback361_original || bulkCallbackIdentity((void*)bulkCallback361_linked)!=(uintptr_t)bulkCallback361_original)return 362;
 if(bulkCallbackIdentity((void*)bulkCallback362_original)!=(uintptr_t)bulkCallback362_original || bulkCallbackIdentity((void*)bulkCallback362_linked)!=(uintptr_t)bulkCallback362_original)return 363;
 if(bulkCallbackIdentity((void*)bulkCallback363_original)!=(uintptr_t)bulkCallback363_original || bulkCallbackIdentity((void*)bulkCallback363_linked)!=(uintptr_t)bulkCallback363_original)return 364;
 if(bulkCallbackIdentity((void*)bulkCallback364_original)!=(uintptr_t)bulkCallback364_original || bulkCallbackIdentity((void*)bulkCallback364_linked)!=(uintptr_t)bulkCallback364_original)return 365;
 if(bulkCallbackIdentity((void*)bulkCallback365_original)!=(uintptr_t)bulkCallback365_original || bulkCallbackIdentity((void*)bulkCallback365_linked)!=(uintptr_t)bulkCallback365_original)return 366;
 if(bulkCallbackIdentity((void*)bulkCallback366_original)!=(uintptr_t)bulkCallback366_original || bulkCallbackIdentity((void*)bulkCallback366_linked)!=(uintptr_t)bulkCallback366_original)return 367;
 if(bulkCallbackIdentity((void*)bulkCallback367_original)!=(uintptr_t)bulkCallback367_original || bulkCallbackIdentity((void*)bulkCallback367_linked)!=(uintptr_t)bulkCallback367_original)return 368;
 if(bulkCallbackIdentity((void*)bulkCallback368_original)!=(uintptr_t)bulkCallback368_original || bulkCallbackIdentity((void*)bulkCallback368_linked)!=(uintptr_t)bulkCallback368_original)return 369;
 if(bulkCallbackIdentity((void*)bulkCallback369_original)!=(uintptr_t)bulkCallback369_original || bulkCallbackIdentity((void*)bulkCallback369_linked)!=(uintptr_t)bulkCallback369_original)return 370;
 if(bulkCallbackIdentity((void*)bulkCallback370_original)!=(uintptr_t)bulkCallback370_original || bulkCallbackIdentity((void*)bulkCallback370_linked)!=(uintptr_t)bulkCallback370_original)return 371;
 if(bulkCallbackIdentity((void*)bulkCallback371_original)!=(uintptr_t)bulkCallback371_original || bulkCallbackIdentity((void*)bulkCallback371_linked)!=(uintptr_t)bulkCallback371_original)return 372;
 if(bulkCallbackIdentity((void*)bulkCallback372_original)!=(uintptr_t)bulkCallback372_original || bulkCallbackIdentity((void*)bulkCallback372_linked)!=(uintptr_t)bulkCallback372_original)return 373;
 if(bulkCallbackIdentity((void*)bulkCallback373_original)!=(uintptr_t)bulkCallback373_original || bulkCallbackIdentity((void*)bulkCallback373_linked)!=(uintptr_t)bulkCallback373_original)return 374;
 if(bulkCallbackIdentity((void*)bulkCallback374_original)!=(uintptr_t)bulkCallback374_original || bulkCallbackIdentity((void*)bulkCallback374_linked)!=(uintptr_t)bulkCallback374_original)return 375;
 if(bulkCallbackIdentity((void*)bulkCallback375_original)!=(uintptr_t)bulkCallback375_original || bulkCallbackIdentity((void*)bulkCallback375_linked)!=(uintptr_t)bulkCallback375_original)return 376;
 if(bulkCallbackIdentity((void*)bulkCallback376_original)!=(uintptr_t)bulkCallback376_original || bulkCallbackIdentity((void*)bulkCallback376_linked)!=(uintptr_t)bulkCallback376_original)return 377;
 if(bulkCallbackIdentity((void*)bulkCallback377_original)!=(uintptr_t)bulkCallback377_original || bulkCallbackIdentity((void*)bulkCallback377_linked)!=(uintptr_t)bulkCallback377_original)return 378;
 if(bulkCallbackIdentity((void*)bulkCallback378_original)!=(uintptr_t)bulkCallback378_original || bulkCallbackIdentity((void*)bulkCallback378_linked)!=(uintptr_t)bulkCallback378_original)return 379;
 if(bulkCallbackIdentity((void*)bulkCallback379_original)!=(uintptr_t)bulkCallback379_original || bulkCallbackIdentity((void*)bulkCallback379_linked)!=(uintptr_t)bulkCallback379_original)return 380;
 if(bulkCallbackIdentity((void*)bulkCallback380_original)!=(uintptr_t)bulkCallback380_original || bulkCallbackIdentity((void*)bulkCallback380_linked)!=(uintptr_t)bulkCallback380_original)return 381;
 if(bulkCallbackIdentity((void*)bulkCallback381_original)!=(uintptr_t)bulkCallback381_original || bulkCallbackIdentity((void*)bulkCallback381_linked)!=(uintptr_t)bulkCallback381_original)return 382;
 if(bulkCallbackIdentity((void*)bulkCallback382_original)!=(uintptr_t)bulkCallback382_original || bulkCallbackIdentity((void*)bulkCallback382_linked)!=(uintptr_t)bulkCallback382_original)return 383;
 if(bulkCallbackIdentity((void*)bulkCallback383_original)!=(uintptr_t)bulkCallback383_original || bulkCallbackIdentity((void*)bulkCallback383_linked)!=(uintptr_t)bulkCallback383_original)return 384;
 if(bulkCallbackIdentity((void*)bulkCallback384_original)!=(uintptr_t)bulkCallback384_original || bulkCallbackIdentity((void*)bulkCallback384_linked)!=(uintptr_t)bulkCallback384_original)return 385;
 if(bulkCallbackIdentity((void*)bulkCallback385_original)!=(uintptr_t)bulkCallback385_original || bulkCallbackIdentity((void*)bulkCallback385_linked)!=(uintptr_t)bulkCallback385_original)return 386;
 if(bulkCallbackIdentity((void*)bulkCallback386_original)!=(uintptr_t)bulkCallback386_original || bulkCallbackIdentity((void*)bulkCallback386_linked)!=(uintptr_t)bulkCallback386_original)return 387;
 if(bulkCallbackIdentity((void*)bulkCallback387_original)!=(uintptr_t)bulkCallback387_original || bulkCallbackIdentity((void*)bulkCallback387_linked)!=(uintptr_t)bulkCallback387_original)return 388;
 if(bulkCallbackIdentity((void*)bulkCallback388_original)!=(uintptr_t)bulkCallback388_original || bulkCallbackIdentity((void*)bulkCallback388_linked)!=(uintptr_t)bulkCallback388_original)return 389;
 if(bulkCallbackIdentity((void*)bulkCallback389_original)!=(uintptr_t)bulkCallback389_original || bulkCallbackIdentity((void*)bulkCallback389_linked)!=(uintptr_t)bulkCallback389_original)return 390;
 if(bulkCallbackIdentity((void*)bulkCallback390_original)!=(uintptr_t)bulkCallback390_original || bulkCallbackIdentity((void*)bulkCallback390_linked)!=(uintptr_t)bulkCallback390_original)return 391;
 if(bulkCallbackIdentity((void*)bulkCallback391_original)!=(uintptr_t)bulkCallback391_original || bulkCallbackIdentity((void*)bulkCallback391_linked)!=(uintptr_t)bulkCallback391_original)return 392;
 if(bulkCallbackIdentity((void*)bulkCallback392_original)!=(uintptr_t)bulkCallback392_original || bulkCallbackIdentity((void*)bulkCallback392_linked)!=(uintptr_t)bulkCallback392_original)return 393;
 if(bulkCallbackIdentity((void*)bulkCallback393_original)!=(uintptr_t)bulkCallback393_original || bulkCallbackIdentity((void*)bulkCallback393_linked)!=(uintptr_t)bulkCallback393_original)return 394;
 if(bulkCallbackIdentity((void*)bulkCallback394_original)!=(uintptr_t)bulkCallback394_original || bulkCallbackIdentity((void*)bulkCallback394_linked)!=(uintptr_t)bulkCallback394_original)return 395;
 if(bulkCallbackIdentity((void*)bulkCallback395_original)!=(uintptr_t)bulkCallback395_original || bulkCallbackIdentity((void*)bulkCallback395_linked)!=(uintptr_t)bulkCallback395_original)return 396;
 if(bulkCallbackIdentity((void*)bulkCallback396_original)!=(uintptr_t)bulkCallback396_original || bulkCallbackIdentity((void*)bulkCallback396_linked)!=(uintptr_t)bulkCallback396_original)return 397;
 if(bulkCallbackIdentity((void*)bulkCallback397_original)!=(uintptr_t)bulkCallback397_original || bulkCallbackIdentity((void*)bulkCallback397_linked)!=(uintptr_t)bulkCallback397_original)return 398;
 if(bulkCallbackIdentity((void*)bulkCallback398_original)!=(uintptr_t)bulkCallback398_original || bulkCallbackIdentity((void*)bulkCallback398_linked)!=(uintptr_t)bulkCallback398_original)return 399;
 if(bulkCallbackIdentity((void*)bulkCallback399_original)!=(uintptr_t)bulkCallback399_original || bulkCallbackIdentity((void*)bulkCallback399_linked)!=(uintptr_t)bulkCallback399_original)return 400;
 if(bulkCallbackIdentity((void*)bulkCallback400_original)!=(uintptr_t)bulkCallback400_original || bulkCallbackIdentity((void*)bulkCallback400_linked)!=(uintptr_t)bulkCallback400_original)return 401;
 if(bulkCallbackIdentity((void*)bulkCallback401_original)!=(uintptr_t)bulkCallback401_original || bulkCallbackIdentity((void*)bulkCallback401_linked)!=(uintptr_t)bulkCallback401_original)return 402;
 if(bulkCallbackIdentity((void*)bulkCallback402_original)!=(uintptr_t)bulkCallback402_original || bulkCallbackIdentity((void*)bulkCallback402_linked)!=(uintptr_t)bulkCallback402_original)return 403;
 if(bulkCallbackIdentity((void*)bulkCallback403_original)!=(uintptr_t)bulkCallback403_original || bulkCallbackIdentity((void*)bulkCallback403_linked)!=(uintptr_t)bulkCallback403_original)return 404;
 if(bulkCallbackIdentity((void*)bulkCallback404_original)!=(uintptr_t)bulkCallback404_original || bulkCallbackIdentity((void*)bulkCallback404_linked)!=(uintptr_t)bulkCallback404_original)return 405;
 if(bulkCallbackIdentity((void*)bulkCallback405_original)!=(uintptr_t)bulkCallback405_original || bulkCallbackIdentity((void*)bulkCallback405_linked)!=(uintptr_t)bulkCallback405_original)return 406;
 if(bulkCallbackIdentity((void*)bulkCallback406_original)!=(uintptr_t)bulkCallback406_original || bulkCallbackIdentity((void*)bulkCallback406_linked)!=(uintptr_t)bulkCallback406_original)return 407;
 if(bulkCallbackIdentity((void*)bulkCallback407_original)!=(uintptr_t)bulkCallback407_original || bulkCallbackIdentity((void*)bulkCallback407_linked)!=(uintptr_t)bulkCallback407_original)return 408;
 if(bulkCallbackIdentity((void*)bulkCallback408_original)!=(uintptr_t)bulkCallback408_original || bulkCallbackIdentity((void*)bulkCallback408_linked)!=(uintptr_t)bulkCallback408_original)return 409;
 if(bulkCallbackIdentity((void*)bulkCallback409_original)!=(uintptr_t)bulkCallback409_original || bulkCallbackIdentity((void*)bulkCallback409_linked)!=(uintptr_t)bulkCallback409_original)return 410;
 if(bulkCallbackIdentity((void*)bulkCallback410_original)!=(uintptr_t)bulkCallback410_original || bulkCallbackIdentity((void*)bulkCallback410_linked)!=(uintptr_t)bulkCallback410_original)return 411;
 if(bulkCallbackIdentity((void*)bulkCallback411_original)!=(uintptr_t)bulkCallback411_original || bulkCallbackIdentity((void*)bulkCallback411_linked)!=(uintptr_t)bulkCallback411_original)return 412;
 if(bulkCallbackIdentity((void*)bulkCallback412_original)!=(uintptr_t)bulkCallback412_original || bulkCallbackIdentity((void*)bulkCallback412_linked)!=(uintptr_t)bulkCallback412_original)return 413;
 if(bulkCallbackIdentity((void*)bulkCallback413_original)!=(uintptr_t)bulkCallback413_original || bulkCallbackIdentity((void*)bulkCallback413_linked)!=(uintptr_t)bulkCallback413_original)return 414;
 if(bulkCallbackIdentity((void*)bulkCallback414_original)!=(uintptr_t)bulkCallback414_original || bulkCallbackIdentity((void*)bulkCallback414_linked)!=(uintptr_t)bulkCallback414_original)return 415;
 if(bulkCallbackIdentity((void*)bulkCallback415_original)!=(uintptr_t)bulkCallback415_original || bulkCallbackIdentity((void*)bulkCallback415_linked)!=(uintptr_t)bulkCallback415_original)return 416;
 if(bulkCallbackIdentity((void*)bulkCallback416_original)!=(uintptr_t)bulkCallback416_original || bulkCallbackIdentity((void*)bulkCallback416_linked)!=(uintptr_t)bulkCallback416_original)return 417;
 if(bulkCallbackIdentity((void*)bulkCallback417_original)!=(uintptr_t)bulkCallback417_original || bulkCallbackIdentity((void*)bulkCallback417_linked)!=(uintptr_t)bulkCallback417_original)return 418;
 if(bulkCallbackIdentity((void*)bulkCallback418_original)!=(uintptr_t)bulkCallback418_original || bulkCallbackIdentity((void*)bulkCallback418_linked)!=(uintptr_t)bulkCallback418_original)return 419;
 if(bulkCallbackIdentity((void*)bulkCallback419_original)!=(uintptr_t)bulkCallback419_original || bulkCallbackIdentity((void*)bulkCallback419_linked)!=(uintptr_t)bulkCallback419_original)return 420;
 if(bulkCallbackIdentity((void*)bulkCallback420_original)!=(uintptr_t)bulkCallback420_original || bulkCallbackIdentity((void*)bulkCallback420_linked)!=(uintptr_t)bulkCallback420_original)return 421;
 if(bulkCallbackIdentity((void*)bulkCallback421_original)!=(uintptr_t)bulkCallback421_original || bulkCallbackIdentity((void*)bulkCallback421_linked)!=(uintptr_t)bulkCallback421_original)return 422;
 if(bulkCallbackIdentity((void*)bulkCallback422_original)!=(uintptr_t)bulkCallback422_original || bulkCallbackIdentity((void*)bulkCallback422_linked)!=(uintptr_t)bulkCallback422_original)return 423;
 if(bulkCallbackIdentity((void*)bulkCallback423_original)!=(uintptr_t)bulkCallback423_original || bulkCallbackIdentity((void*)bulkCallback423_linked)!=(uintptr_t)bulkCallback423_original)return 424;
 if(bulkCallbackIdentity((void*)bulkCallback424_original)!=(uintptr_t)bulkCallback424_original || bulkCallbackIdentity((void*)bulkCallback424_linked)!=(uintptr_t)bulkCallback424_original)return 425;
 if(bulkCallbackIdentity((void*)bulkCallback425_original)!=(uintptr_t)bulkCallback425_original || bulkCallbackIdentity((void*)bulkCallback425_linked)!=(uintptr_t)bulkCallback425_original)return 426;
 if(bulkCallbackIdentity((void*)bulkCallback426_original)!=(uintptr_t)bulkCallback426_original || bulkCallbackIdentity((void*)bulkCallback426_linked)!=(uintptr_t)bulkCallback426_original)return 427;
 if(bulkCallbackIdentity((void*)bulkCallback427_original)!=(uintptr_t)bulkCallback427_original || bulkCallbackIdentity((void*)bulkCallback427_linked)!=(uintptr_t)bulkCallback427_original)return 428;
 if(bulkCallbackIdentity((void*)bulkCallback428_original)!=(uintptr_t)bulkCallback428_original || bulkCallbackIdentity((void*)bulkCallback428_linked)!=(uintptr_t)bulkCallback428_original)return 429;
 if(bulkCallbackIdentity((void*)bulkCallback429_original)!=(uintptr_t)bulkCallback429_original || bulkCallbackIdentity((void*)bulkCallback429_linked)!=(uintptr_t)bulkCallback429_original)return 430;
 if(bulkCallbackIdentity((void*)bulkCallback430_original)!=(uintptr_t)bulkCallback430_original || bulkCallbackIdentity((void*)bulkCallback430_linked)!=(uintptr_t)bulkCallback430_original)return 431;
 if(bulkCallbackIdentity((void*)bulkCallback431_original)!=(uintptr_t)bulkCallback431_original || bulkCallbackIdentity((void*)bulkCallback431_linked)!=(uintptr_t)bulkCallback431_original)return 432;
 if(bulkCallbackIdentity((void*)bulkCallback432_original)!=(uintptr_t)bulkCallback432_original || bulkCallbackIdentity((void*)bulkCallback432_linked)!=(uintptr_t)bulkCallback432_original)return 433;
 if(bulkCallbackIdentity((void*)bulkCallback433_original)!=(uintptr_t)bulkCallback433_original || bulkCallbackIdentity((void*)bulkCallback433_linked)!=(uintptr_t)bulkCallback433_original)return 434;
 if(bulkCallbackIdentity((void*)bulkCallback434_original)!=(uintptr_t)bulkCallback434_original || bulkCallbackIdentity((void*)bulkCallback434_linked)!=(uintptr_t)bulkCallback434_original)return 435;
 if(bulkCallbackIdentity((void*)bulkCallback435_original)!=(uintptr_t)bulkCallback435_original || bulkCallbackIdentity((void*)bulkCallback435_linked)!=(uintptr_t)bulkCallback435_original)return 436;
 if(bulkCallbackIdentity((void*)bulkCallback436_original)!=(uintptr_t)bulkCallback436_original || bulkCallbackIdentity((void*)bulkCallback436_linked)!=(uintptr_t)bulkCallback436_original)return 437;
 if(bulkCallbackIdentity((void*)bulkCallback437_original)!=(uintptr_t)bulkCallback437_original || bulkCallbackIdentity((void*)bulkCallback437_linked)!=(uintptr_t)bulkCallback437_original)return 438;
 if(bulkCallbackIdentity((void*)bulkCallback438_original)!=(uintptr_t)bulkCallback438_original || bulkCallbackIdentity((void*)bulkCallback438_linked)!=(uintptr_t)bulkCallback438_original)return 439;
 if(bulkCallbackIdentity((void*)bulkCallback439_original)!=(uintptr_t)bulkCallback439_original || bulkCallbackIdentity((void*)bulkCallback439_linked)!=(uintptr_t)bulkCallback439_original)return 440;
 if(bulkCallbackIdentity((void*)bulkCallback440_original)!=(uintptr_t)bulkCallback440_original || bulkCallbackIdentity((void*)bulkCallback440_linked)!=(uintptr_t)bulkCallback440_original)return 441;
 if(bulkCallbackIdentity((void*)bulkCallback441_original)!=(uintptr_t)bulkCallback441_original || bulkCallbackIdentity((void*)bulkCallback441_linked)!=(uintptr_t)bulkCallback441_original)return 442;
 if(bulkCallbackIdentity((void*)bulkCallback442_original)!=(uintptr_t)bulkCallback442_original || bulkCallbackIdentity((void*)bulkCallback442_linked)!=(uintptr_t)bulkCallback442_original)return 443;
 if(bulkCallbackIdentity((void*)bulkCallback443_original)!=(uintptr_t)bulkCallback443_original || bulkCallbackIdentity((void*)bulkCallback443_linked)!=(uintptr_t)bulkCallback443_original)return 444;
 if(bulkCallbackIdentity((void*)bulkCallback444_original)!=(uintptr_t)bulkCallback444_original || bulkCallbackIdentity((void*)bulkCallback444_linked)!=(uintptr_t)bulkCallback444_original)return 445;
 if(bulkCallbackIdentity((void*)bulkCallback445_original)!=(uintptr_t)bulkCallback445_original || bulkCallbackIdentity((void*)bulkCallback445_linked)!=(uintptr_t)bulkCallback445_original)return 446;
 if(bulkCallbackIdentity((void*)bulkCallback446_original)!=(uintptr_t)bulkCallback446_original || bulkCallbackIdentity((void*)bulkCallback446_linked)!=(uintptr_t)bulkCallback446_original)return 447;
 if(bulkCallbackIdentity((void*)bulkCallback447_original)!=(uintptr_t)bulkCallback447_original || bulkCallbackIdentity((void*)bulkCallback447_linked)!=(uintptr_t)bulkCallback447_original)return 448;
 if(bulkCallbackIdentity((void*)bulkCallback448_original)!=(uintptr_t)bulkCallback448_original || bulkCallbackIdentity((void*)bulkCallback448_linked)!=(uintptr_t)bulkCallback448_original)return 449;
 if(bulkCallbackIdentity((void*)bulkCallback449_original)!=(uintptr_t)bulkCallback449_original || bulkCallbackIdentity((void*)bulkCallback449_linked)!=(uintptr_t)bulkCallback449_original)return 450;
 if(bulkCallbackIdentity((void*)bulkCallback450_original)!=(uintptr_t)bulkCallback450_original || bulkCallbackIdentity((void*)bulkCallback450_linked)!=(uintptr_t)bulkCallback450_original)return 451;
 if(bulkCallbackIdentity((void*)bulkCallback451_original)!=(uintptr_t)bulkCallback451_original || bulkCallbackIdentity((void*)bulkCallback451_linked)!=(uintptr_t)bulkCallback451_original)return 452;
 if(bulkCallbackIdentity((void*)bulkCallback452_original)!=(uintptr_t)bulkCallback452_original || bulkCallbackIdentity((void*)bulkCallback452_linked)!=(uintptr_t)bulkCallback452_original)return 453;
 if(bulkCallbackIdentity((void*)bulkCallback453_original)!=(uintptr_t)bulkCallback453_original || bulkCallbackIdentity((void*)bulkCallback453_linked)!=(uintptr_t)bulkCallback453_original)return 454;
 if(bulkCallbackIdentity((void*)bulkCallback454_original)!=(uintptr_t)bulkCallback454_original || bulkCallbackIdentity((void*)bulkCallback454_linked)!=(uintptr_t)bulkCallback454_original)return 455;
 if(bulkCallbackIdentity((void*)bulkCallback455_original)!=(uintptr_t)bulkCallback455_original || bulkCallbackIdentity((void*)bulkCallback455_linked)!=(uintptr_t)bulkCallback455_original)return 456;
 if(bulkCallbackIdentity((void*)bulkCallback456_original)!=(uintptr_t)bulkCallback456_original || bulkCallbackIdentity((void*)bulkCallback456_linked)!=(uintptr_t)bulkCallback456_original)return 457;
 if(bulkCallbackIdentity((void*)bulkCallback457_original)!=(uintptr_t)bulkCallback457_original || bulkCallbackIdentity((void*)bulkCallback457_linked)!=(uintptr_t)bulkCallback457_original)return 458;
 if(bulkCallbackIdentity((void*)bulkCallback458_original)!=(uintptr_t)bulkCallback458_original || bulkCallbackIdentity((void*)bulkCallback458_linked)!=(uintptr_t)bulkCallback458_original)return 459;
 if(bulkCallbackIdentity((void*)bulkCallback459_original)!=(uintptr_t)bulkCallback459_original || bulkCallbackIdentity((void*)bulkCallback459_linked)!=(uintptr_t)bulkCallback459_original)return 460;
 if(bulkCallbackIdentity((void*)bulkCallback460_original)!=(uintptr_t)bulkCallback460_original || bulkCallbackIdentity((void*)bulkCallback460_linked)!=(uintptr_t)bulkCallback460_original)return 461;
 if(bulkCallbackIdentity((void*)bulkCallback461_original)!=(uintptr_t)bulkCallback461_original || bulkCallbackIdentity((void*)bulkCallback461_linked)!=(uintptr_t)bulkCallback461_original)return 462;
 if(bulkCallbackIdentity((void*)bulkCallback462_original)!=(uintptr_t)bulkCallback462_original || bulkCallbackIdentity((void*)bulkCallback462_linked)!=(uintptr_t)bulkCallback462_original)return 463;
 if(bulkCallbackIdentity((void*)bulkCallback463_original)!=(uintptr_t)bulkCallback463_original || bulkCallbackIdentity((void*)bulkCallback463_linked)!=(uintptr_t)bulkCallback463_original)return 464;
 if(bulkCallbackIdentity((void*)bulkCallback464_original)!=(uintptr_t)bulkCallback464_original || bulkCallbackIdentity((void*)bulkCallback464_linked)!=(uintptr_t)bulkCallback464_original)return 465;
 if(bulkCallbackIdentity((void*)bulkCallback465_original)!=(uintptr_t)bulkCallback465_original || bulkCallbackIdentity((void*)bulkCallback465_linked)!=(uintptr_t)bulkCallback465_original)return 466;
 if(bulkCallbackIdentity((void*)bulkCallback466_original)!=(uintptr_t)bulkCallback466_original || bulkCallbackIdentity((void*)bulkCallback466_linked)!=(uintptr_t)bulkCallback466_original)return 467;
 if(bulkCallbackIdentity((void*)bulkCallback467_original)!=(uintptr_t)bulkCallback467_original || bulkCallbackIdentity((void*)bulkCallback467_linked)!=(uintptr_t)bulkCallback467_original)return 468;
 if(bulkCallbackIdentity((void*)bulkCallback468_original)!=(uintptr_t)bulkCallback468_original || bulkCallbackIdentity((void*)bulkCallback468_linked)!=(uintptr_t)bulkCallback468_original)return 469;
 if(bulkCallbackIdentity((void*)bulkCallback469_original)!=(uintptr_t)bulkCallback469_original || bulkCallbackIdentity((void*)bulkCallback469_linked)!=(uintptr_t)bulkCallback469_original)return 470;
 if(bulkCallbackIdentity((void*)bulkCallback470_original)!=(uintptr_t)bulkCallback470_original || bulkCallbackIdentity((void*)bulkCallback470_linked)!=(uintptr_t)bulkCallback470_original)return 471;
 if(bulkCallbackIdentity((void*)bulkCallback471_original)!=(uintptr_t)bulkCallback471_original || bulkCallbackIdentity((void*)bulkCallback471_linked)!=(uintptr_t)bulkCallback471_original)return 472;
 if(bulkCallbackIdentity((void*)bulkCallback472_original)!=(uintptr_t)bulkCallback472_original || bulkCallbackIdentity((void*)bulkCallback472_linked)!=(uintptr_t)bulkCallback472_original)return 473;
 if(bulkCallbackIdentity((void*)bulkCallback473_original)!=(uintptr_t)bulkCallback473_original || bulkCallbackIdentity((void*)bulkCallback473_linked)!=(uintptr_t)bulkCallback473_original)return 474;
 if(bulkCallbackIdentity((void*)bulkCallback474_original)!=(uintptr_t)bulkCallback474_original || bulkCallbackIdentity((void*)bulkCallback474_linked)!=(uintptr_t)bulkCallback474_original)return 475;
 if(bulkCallbackIdentity((void*)bulkCallback475_original)!=(uintptr_t)bulkCallback475_original || bulkCallbackIdentity((void*)bulkCallback475_linked)!=(uintptr_t)bulkCallback475_original)return 476;
 if(bulkCallbackIdentity((void*)bulkCallback476_original)!=(uintptr_t)bulkCallback476_original || bulkCallbackIdentity((void*)bulkCallback476_linked)!=(uintptr_t)bulkCallback476_original)return 477;
 if(bulkCallbackIdentity((void*)bulkCallback477_original)!=(uintptr_t)bulkCallback477_original || bulkCallbackIdentity((void*)bulkCallback477_linked)!=(uintptr_t)bulkCallback477_original)return 478;
 if(bulkCallbackIdentity((void*)bulkCallback478_original)!=(uintptr_t)bulkCallback478_original || bulkCallbackIdentity((void*)bulkCallback478_linked)!=(uintptr_t)bulkCallback478_original)return 479;
 if(bulkCallbackIdentity((void*)bulkCallback479_original)!=(uintptr_t)bulkCallback479_original || bulkCallbackIdentity((void*)bulkCallback479_linked)!=(uintptr_t)bulkCallback479_original)return 480;
 if(bulkCallbackIdentity((void*)bulkCallback480_original)!=(uintptr_t)bulkCallback480_original || bulkCallbackIdentity((void*)bulkCallback480_linked)!=(uintptr_t)bulkCallback480_original)return 481;
 if(bulkCallbackIdentity((void*)bulkCallback481_original)!=(uintptr_t)bulkCallback481_original || bulkCallbackIdentity((void*)bulkCallback481_linked)!=(uintptr_t)bulkCallback481_original)return 482;
 if(bulkCallbackIdentity((void*)bulkCallback482_original)!=(uintptr_t)bulkCallback482_original || bulkCallbackIdentity((void*)bulkCallback482_linked)!=(uintptr_t)bulkCallback482_original)return 483;
 if(bulkCallbackIdentity((void*)bulkCallback483_original)!=(uintptr_t)bulkCallback483_original || bulkCallbackIdentity((void*)bulkCallback483_linked)!=(uintptr_t)bulkCallback483_original)return 484;
 if(bulkCallbackIdentity((void*)bulkCallback484_original)!=(uintptr_t)bulkCallback484_original || bulkCallbackIdentity((void*)bulkCallback484_linked)!=(uintptr_t)bulkCallback484_original)return 485;
 if(bulkCallbackIdentity((void*)bulkCallback485_original)!=(uintptr_t)bulkCallback485_original || bulkCallbackIdentity((void*)bulkCallback485_linked)!=(uintptr_t)bulkCallback485_original)return 486;
 if(bulkCallbackIdentity((void*)bulkCallback486_original)!=(uintptr_t)bulkCallback486_original || bulkCallbackIdentity((void*)bulkCallback486_linked)!=(uintptr_t)bulkCallback486_original)return 487;
 if(bulkCallbackIdentity((void*)bulkCallback487_original)!=(uintptr_t)bulkCallback487_original || bulkCallbackIdentity((void*)bulkCallback487_linked)!=(uintptr_t)bulkCallback487_original)return 488;
 if(bulkCallbackIdentity((void*)bulkCallback488_original)!=(uintptr_t)bulkCallback488_original || bulkCallbackIdentity((void*)bulkCallback488_linked)!=(uintptr_t)bulkCallback488_original)return 489;
 if(bulkCallbackIdentity((void*)bulkCallback489_original)!=(uintptr_t)bulkCallback489_original || bulkCallbackIdentity((void*)bulkCallback489_linked)!=(uintptr_t)bulkCallback489_original)return 490;
 if(bulkCallbackIdentity((void*)bulkCallback490_original)!=(uintptr_t)bulkCallback490_original || bulkCallbackIdentity((void*)bulkCallback490_linked)!=(uintptr_t)bulkCallback490_original)return 491;
 if(bulkCallbackIdentity((void*)bulkCallback491_original)!=(uintptr_t)bulkCallback491_original || bulkCallbackIdentity((void*)bulkCallback491_linked)!=(uintptr_t)bulkCallback491_original)return 492;
 if(bulkCallbackIdentity((void*)bulkCallback492_original)!=(uintptr_t)bulkCallback492_original || bulkCallbackIdentity((void*)bulkCallback492_linked)!=(uintptr_t)bulkCallback492_original)return 493;
 if(bulkCallbackIdentity((void*)bulkCallback493_original)!=(uintptr_t)bulkCallback493_original || bulkCallbackIdentity((void*)bulkCallback493_linked)!=(uintptr_t)bulkCallback493_original)return 494;
 if(bulkCallbackIdentity((void*)bulkCallback494_original)!=(uintptr_t)bulkCallback494_original || bulkCallbackIdentity((void*)bulkCallback494_linked)!=(uintptr_t)bulkCallback494_original)return 495;
 if(bulkCallbackIdentity((void*)bulkCallback495_original)!=(uintptr_t)bulkCallback495_original || bulkCallbackIdentity((void*)bulkCallback495_linked)!=(uintptr_t)bulkCallback495_original)return 496;
 if(bulkCallbackIdentity((void*)bulkCallback496_original)!=(uintptr_t)bulkCallback496_original || bulkCallbackIdentity((void*)bulkCallback496_linked)!=(uintptr_t)bulkCallback496_original)return 497;
 if(bulkCallbackIdentity((void*)bulkCallback497_original)!=(uintptr_t)bulkCallback497_original || bulkCallbackIdentity((void*)bulkCallback497_linked)!=(uintptr_t)bulkCallback497_original)return 498;
 if(bulkCallbackIdentity((void*)bulkCallback498_original)!=(uintptr_t)bulkCallback498_original || bulkCallbackIdentity((void*)bulkCallback498_linked)!=(uintptr_t)bulkCallback498_original)return 499;
 if(bulkCallbackIdentity((void*)bulkCallback499_original)!=(uintptr_t)bulkCallback499_original || bulkCallbackIdentity((void*)bulkCallback499_linked)!=(uintptr_t)bulkCallback499_original)return 500;
 if(bulkCallbackIdentity((void*)bulkCallback500_original)!=(uintptr_t)bulkCallback500_original || bulkCallbackIdentity((void*)bulkCallback500_linked)!=(uintptr_t)bulkCallback500_original)return 501;
 if(bulkCallbackIdentity((void*)bulkCallback501_original)!=(uintptr_t)bulkCallback501_original || bulkCallbackIdentity((void*)bulkCallback501_linked)!=(uintptr_t)bulkCallback501_original)return 502;
 if(bulkCallbackIdentity((void*)bulkCallback502_original)!=(uintptr_t)bulkCallback502_original || bulkCallbackIdentity((void*)bulkCallback502_linked)!=(uintptr_t)bulkCallback502_original)return 503;
 if(bulkCallbackIdentity((void*)bulkCallback503_original)!=(uintptr_t)bulkCallback503_original || bulkCallbackIdentity((void*)bulkCallback503_linked)!=(uintptr_t)bulkCallback503_original)return 504;
 if(bulkCallbackIdentity((void*)bulkCallback504_original)!=(uintptr_t)bulkCallback504_original || bulkCallbackIdentity((void*)bulkCallback504_linked)!=(uintptr_t)bulkCallback504_original)return 505;
 if(bulkCallbackIdentity((void*)bulkCallback505_original)!=(uintptr_t)bulkCallback505_original || bulkCallbackIdentity((void*)bulkCallback505_linked)!=(uintptr_t)bulkCallback505_original)return 506;
 if(bulkCallbackIdentity((void*)bulkCallback506_original)!=(uintptr_t)bulkCallback506_original || bulkCallbackIdentity((void*)bulkCallback506_linked)!=(uintptr_t)bulkCallback506_original)return 507;
 if(bulkCallbackIdentity((void*)bulkCallback507_original)!=(uintptr_t)bulkCallback507_original || bulkCallbackIdentity((void*)bulkCallback507_linked)!=(uintptr_t)bulkCallback507_original)return 508;
 if(bulkCallbackIdentity((void*)bulkCallback508_original)!=(uintptr_t)bulkCallback508_original || bulkCallbackIdentity((void*)bulkCallback508_linked)!=(uintptr_t)bulkCallback508_original)return 509;
 if(bulkCallbackIdentity((void*)bulkCallback509_original)!=(uintptr_t)bulkCallback509_original || bulkCallbackIdentity((void*)bulkCallback509_linked)!=(uintptr_t)bulkCallback509_original)return 510;
 if(bulkCallbackIdentity((void*)bulkCallback510_original)!=(uintptr_t)bulkCallback510_original || bulkCallbackIdentity((void*)bulkCallback510_linked)!=(uintptr_t)bulkCallback510_original)return 511;
 if(bulkCallbackIdentity((void*)bulkCallback511_original)!=(uintptr_t)bulkCallback511_original || bulkCallbackIdentity((void*)bulkCallback511_linked)!=(uintptr_t)bulkCallback511_original)return 512;
 if(bulkCallbackIdentity((void*)bulkCallback512_original)!=(uintptr_t)bulkCallback512_original || bulkCallbackIdentity((void*)bulkCallback512_linked)!=(uintptr_t)bulkCallback512_original)return 513;
 if(bulkCallbackIdentity((void*)bulkCallback513_original)!=(uintptr_t)bulkCallback513_original || bulkCallbackIdentity((void*)bulkCallback513_linked)!=(uintptr_t)bulkCallback513_original)return 514;
 if(bulkCallbackIdentity((void*)bulkCallback514_original)!=(uintptr_t)bulkCallback514_original || bulkCallbackIdentity((void*)bulkCallback514_linked)!=(uintptr_t)bulkCallback514_original)return 515;
 if(bulkCallbackIdentity((void*)bulkCallback515_original)!=(uintptr_t)bulkCallback515_original || bulkCallbackIdentity((void*)bulkCallback515_linked)!=(uintptr_t)bulkCallback515_original)return 516;
 if(bulkCallbackIdentity((void*)bulkCallback516_original)!=(uintptr_t)bulkCallback516_original || bulkCallbackIdentity((void*)bulkCallback516_linked)!=(uintptr_t)bulkCallback516_original)return 517;
 if(bulkCallbackIdentity((void*)bulkCallback517_original)!=(uintptr_t)bulkCallback517_original || bulkCallbackIdentity((void*)bulkCallback517_linked)!=(uintptr_t)bulkCallback517_original)return 518;
 if(bulkCallbackIdentity((void*)bulkCallback518_original)!=(uintptr_t)bulkCallback518_original || bulkCallbackIdentity((void*)bulkCallback518_linked)!=(uintptr_t)bulkCallback518_original)return 519;
 if(bulkCallbackIdentity((void*)bulkCallback519_original)!=(uintptr_t)bulkCallback519_original || bulkCallbackIdentity((void*)bulkCallback519_linked)!=(uintptr_t)bulkCallback519_original)return 520;
 if(bulkCallbackIdentity((void*)bulkCallback520_original)!=(uintptr_t)bulkCallback520_original || bulkCallbackIdentity((void*)bulkCallback520_linked)!=(uintptr_t)bulkCallback520_original)return 521;
 if(bulkCallbackIdentity((void*)bulkCallback521_original)!=(uintptr_t)bulkCallback521_original || bulkCallbackIdentity((void*)bulkCallback521_linked)!=(uintptr_t)bulkCallback521_original)return 522;
 if(bulkCallbackIdentity((void*)bulkCallback522_original)!=(uintptr_t)bulkCallback522_original || bulkCallbackIdentity((void*)bulkCallback522_linked)!=(uintptr_t)bulkCallback522_original)return 523;
 if(bulkCallbackIdentity((void*)bulkCallback523_original)!=(uintptr_t)bulkCallback523_original || bulkCallbackIdentity((void*)bulkCallback523_linked)!=(uintptr_t)bulkCallback523_original)return 524;
 if(bulkCallbackIdentity((void*)bulkCallback524_original)!=(uintptr_t)bulkCallback524_original || bulkCallbackIdentity((void*)bulkCallback524_linked)!=(uintptr_t)bulkCallback524_original)return 525;
 if(bulkCallbackIdentity((void*)bulkCallback525_original)!=(uintptr_t)bulkCallback525_original || bulkCallbackIdentity((void*)bulkCallback525_linked)!=(uintptr_t)bulkCallback525_original)return 526;
 if(bulkCallbackIdentity((void*)bulkCallback526_original)!=(uintptr_t)bulkCallback526_original || bulkCallbackIdentity((void*)bulkCallback526_linked)!=(uintptr_t)bulkCallback526_original)return 527;
 if(bulkCallbackIdentity((void*)bulkCallback527_original)!=(uintptr_t)bulkCallback527_original || bulkCallbackIdentity((void*)bulkCallback527_linked)!=(uintptr_t)bulkCallback527_original)return 528;
 if(bulkCallbackIdentity((void*)bulkCallback528_original)!=(uintptr_t)bulkCallback528_original || bulkCallbackIdentity((void*)bulkCallback528_linked)!=(uintptr_t)bulkCallback528_original)return 529;
 if(bulkCallbackIdentity((void*)bulkCallback529_original)!=(uintptr_t)bulkCallback529_original || bulkCallbackIdentity((void*)bulkCallback529_linked)!=(uintptr_t)bulkCallback529_original)return 530;
 if(bulkCallbackIdentity((void*)bulkCallback530_original)!=(uintptr_t)bulkCallback530_original || bulkCallbackIdentity((void*)bulkCallback530_linked)!=(uintptr_t)bulkCallback530_original)return 531;
 if(bulkCallbackIdentity((void*)bulkCallback531_original)!=(uintptr_t)bulkCallback531_original || bulkCallbackIdentity((void*)bulkCallback531_linked)!=(uintptr_t)bulkCallback531_original)return 532;
 if(bulkCallbackIdentity((void*)bulkCallback532_original)!=(uintptr_t)bulkCallback532_original || bulkCallbackIdentity((void*)bulkCallback532_linked)!=(uintptr_t)bulkCallback532_original)return 533;
 if(bulkCallbackIdentity((void*)bulkCallback533_original)!=(uintptr_t)bulkCallback533_original || bulkCallbackIdentity((void*)bulkCallback533_linked)!=(uintptr_t)bulkCallback533_original)return 534;
 if(bulkCallbackIdentity((void*)bulkCallback534_original)!=(uintptr_t)bulkCallback534_original || bulkCallbackIdentity((void*)bulkCallback534_linked)!=(uintptr_t)bulkCallback534_original)return 535;
 if(bulkCallbackIdentity((void*)bulkCallback535_original)!=(uintptr_t)bulkCallback535_original || bulkCallbackIdentity((void*)bulkCallback535_linked)!=(uintptr_t)bulkCallback535_original)return 536;
 if(bulkCallbackIdentity((void*)bulkCallback536_original)!=(uintptr_t)bulkCallback536_original || bulkCallbackIdentity((void*)bulkCallback536_linked)!=(uintptr_t)bulkCallback536_original)return 537;
 if(bulkCallbackIdentity((void*)bulkCallback537_original)!=(uintptr_t)bulkCallback537_original || bulkCallbackIdentity((void*)bulkCallback537_linked)!=(uintptr_t)bulkCallback537_original)return 538;
 if(bulkCallbackIdentity((void*)bulkCallback538_original)!=(uintptr_t)bulkCallback538_original || bulkCallbackIdentity((void*)bulkCallback538_linked)!=(uintptr_t)bulkCallback538_original)return 539;
 if(bulkCallbackIdentity((void*)bulkCallback539_original)!=(uintptr_t)bulkCallback539_original || bulkCallbackIdentity((void*)bulkCallback539_linked)!=(uintptr_t)bulkCallback539_original)return 540;
 if(bulkCallbackIdentity((void*)bulkCallback540_original)!=(uintptr_t)bulkCallback540_original || bulkCallbackIdentity((void*)bulkCallback540_linked)!=(uintptr_t)bulkCallback540_original)return 541;
 if(bulkCallbackIdentity((void*)bulkCallback541_original)!=(uintptr_t)bulkCallback541_original || bulkCallbackIdentity((void*)bulkCallback541_linked)!=(uintptr_t)bulkCallback541_original)return 542;
 if(bulkCallbackIdentity((void*)bulkCallback542_original)!=(uintptr_t)bulkCallback542_original || bulkCallbackIdentity((void*)bulkCallback542_linked)!=(uintptr_t)bulkCallback542_original)return 543;
 if(bulkCallbackIdentity((void*)bulkCallback543_original)!=(uintptr_t)bulkCallback543_original || bulkCallbackIdentity((void*)bulkCallback543_linked)!=(uintptr_t)bulkCallback543_original)return 544;
 if(bulkCallbackIdentity((void*)bulkCallback544_original)!=(uintptr_t)bulkCallback544_original || bulkCallbackIdentity((void*)bulkCallback544_linked)!=(uintptr_t)bulkCallback544_original)return 545;
 if(bulkCallbackIdentity((void*)bulkCallback545_original)!=(uintptr_t)bulkCallback545_original || bulkCallbackIdentity((void*)bulkCallback545_linked)!=(uintptr_t)bulkCallback545_original)return 546;
 if(bulkCallbackIdentity((void*)bulkCallback546_original)!=(uintptr_t)bulkCallback546_original || bulkCallbackIdentity((void*)bulkCallback546_linked)!=(uintptr_t)bulkCallback546_original)return 547;
 if(bulkCallbackIdentity((void*)bulkCallback547_original)!=(uintptr_t)bulkCallback547_original || bulkCallbackIdentity((void*)bulkCallback547_linked)!=(uintptr_t)bulkCallback547_original)return 548;
 if(bulkCallbackIdentity((void*)bulkCallback548_original)!=(uintptr_t)bulkCallback548_original || bulkCallbackIdentity((void*)bulkCallback548_linked)!=(uintptr_t)bulkCallback548_original)return 549;
 if(bulkCallbackIdentity((void*)bulkCallback549_original)!=(uintptr_t)bulkCallback549_original || bulkCallbackIdentity((void*)bulkCallback549_linked)!=(uintptr_t)bulkCallback549_original)return 550;
 if(bulkCallbackIdentity((void*)bulkCallback550_original)!=(uintptr_t)bulkCallback550_original || bulkCallbackIdentity((void*)bulkCallback550_linked)!=(uintptr_t)bulkCallback550_original)return 551;
 if(bulkCallbackIdentity((void*)bulkCallback551_original)!=(uintptr_t)bulkCallback551_original || bulkCallbackIdentity((void*)bulkCallback551_linked)!=(uintptr_t)bulkCallback551_original)return 552;
 if(bulkCallbackIdentity((void*)bulkCallback552_original)!=(uintptr_t)bulkCallback552_original || bulkCallbackIdentity((void*)bulkCallback552_linked)!=(uintptr_t)bulkCallback552_original)return 553;
 if(bulkCallbackIdentity((void*)bulkCallback553_original)!=(uintptr_t)bulkCallback553_original || bulkCallbackIdentity((void*)bulkCallback553_linked)!=(uintptr_t)bulkCallback553_original)return 554;
 if(bulkCallbackIdentity((void*)bulkCallback554_original)!=(uintptr_t)bulkCallback554_original || bulkCallbackIdentity((void*)bulkCallback554_linked)!=(uintptr_t)bulkCallback554_original)return 555;
 if(bulkCallbackIdentity((void*)bulkCallback555_original)!=(uintptr_t)bulkCallback555_original || bulkCallbackIdentity((void*)bulkCallback555_linked)!=(uintptr_t)bulkCallback555_original)return 556;
 if(bulkCallbackIdentity((void*)bulkCallback556_original)!=(uintptr_t)bulkCallback556_original || bulkCallbackIdentity((void*)bulkCallback556_linked)!=(uintptr_t)bulkCallback556_original)return 557;
 if(bulkCallbackIdentity((void*)bulkCallback557_original)!=(uintptr_t)bulkCallback557_original || bulkCallbackIdentity((void*)bulkCallback557_linked)!=(uintptr_t)bulkCallback557_original)return 558;
 if(bulkCallbackIdentity((void*)bulkCallback558_original)!=(uintptr_t)bulkCallback558_original || bulkCallbackIdentity((void*)bulkCallback558_linked)!=(uintptr_t)bulkCallback558_original)return 559;
 if(bulkCallbackIdentity((void*)bulkCallback559_original)!=(uintptr_t)bulkCallback559_original || bulkCallbackIdentity((void*)bulkCallback559_linked)!=(uintptr_t)bulkCallback559_original)return 560;
 if(bulkCallbackIdentity((void*)bulkCallback560_original)!=(uintptr_t)bulkCallback560_original || bulkCallbackIdentity((void*)bulkCallback560_linked)!=(uintptr_t)bulkCallback560_original)return 561;
 if(bulkCallbackIdentity((void*)bulkCallback561_original)!=(uintptr_t)bulkCallback561_original || bulkCallbackIdentity((void*)bulkCallback561_linked)!=(uintptr_t)bulkCallback561_original)return 562;
 if(bulkCallbackIdentity((void*)bulkCallback562_original)!=(uintptr_t)bulkCallback562_original || bulkCallbackIdentity((void*)bulkCallback562_linked)!=(uintptr_t)bulkCallback562_original)return 563;
 if(bulkCallbackIdentity((void*)bulkCallback563_original)!=(uintptr_t)bulkCallback563_original || bulkCallbackIdentity((void*)bulkCallback563_linked)!=(uintptr_t)bulkCallback563_original)return 564;
 if(bulkCallbackIdentity((void*)bulkCallback564_original)!=(uintptr_t)bulkCallback564_original || bulkCallbackIdentity((void*)bulkCallback564_linked)!=(uintptr_t)bulkCallback564_original)return 565;
 if(bulkCallbackIdentity((void*)bulkCallback565_original)!=(uintptr_t)bulkCallback565_original || bulkCallbackIdentity((void*)bulkCallback565_linked)!=(uintptr_t)bulkCallback565_original)return 566;
 if(bulkCallbackIdentity((void*)bulkCallback566_original)!=(uintptr_t)bulkCallback566_original || bulkCallbackIdentity((void*)bulkCallback566_linked)!=(uintptr_t)bulkCallback566_original)return 567;
 if(bulkCallbackIdentity((void*)bulkCallback567_original)!=(uintptr_t)bulkCallback567_original || bulkCallbackIdentity((void*)bulkCallback567_linked)!=(uintptr_t)bulkCallback567_original)return 568;
 if(bulkCallbackIdentity((void*)bulkCallback568_original)!=(uintptr_t)bulkCallback568_original || bulkCallbackIdentity((void*)bulkCallback568_linked)!=(uintptr_t)bulkCallback568_original)return 569;
 if(bulkCallbackIdentity((void*)bulkCallback569_original)!=(uintptr_t)bulkCallback569_original || bulkCallbackIdentity((void*)bulkCallback569_linked)!=(uintptr_t)bulkCallback569_original)return 570;
 if(bulkCallbackIdentity((void*)bulkCallback570_original)!=(uintptr_t)bulkCallback570_original || bulkCallbackIdentity((void*)bulkCallback570_linked)!=(uintptr_t)bulkCallback570_original)return 571;
 if(bulkCallbackIdentity((void*)bulkCallback571_original)!=(uintptr_t)bulkCallback571_original || bulkCallbackIdentity((void*)bulkCallback571_linked)!=(uintptr_t)bulkCallback571_original)return 572;
 if(bulkCallbackIdentity((void*)bulkCallback572_original)!=(uintptr_t)bulkCallback572_original || bulkCallbackIdentity((void*)bulkCallback572_linked)!=(uintptr_t)bulkCallback572_original)return 573;
 if(bulkCallbackIdentity((void*)bulkCallback573_original)!=(uintptr_t)bulkCallback573_original || bulkCallbackIdentity((void*)bulkCallback573_linked)!=(uintptr_t)bulkCallback573_original)return 574;
 if(bulkCallbackIdentity((void*)bulkCallback574_original)!=(uintptr_t)bulkCallback574_original || bulkCallbackIdentity((void*)bulkCallback574_linked)!=(uintptr_t)bulkCallback574_original)return 575;
 if(bulkCallbackIdentity((void*)bulkCallback575_original)!=(uintptr_t)bulkCallback575_original || bulkCallbackIdentity((void*)bulkCallback575_linked)!=(uintptr_t)bulkCallback575_original)return 576;
 if(bulkCallbackIdentity((void*)bulkCallback576_original)!=(uintptr_t)bulkCallback576_original || bulkCallbackIdentity((void*)bulkCallback576_linked)!=(uintptr_t)bulkCallback576_original)return 577;
 if(bulkCallbackIdentity((void*)bulkCallback577_original)!=(uintptr_t)bulkCallback577_original || bulkCallbackIdentity((void*)bulkCallback577_linked)!=(uintptr_t)bulkCallback577_original)return 578;
 if(bulkCallbackIdentity((void*)bulkCallback578_original)!=(uintptr_t)bulkCallback578_original || bulkCallbackIdentity((void*)bulkCallback578_linked)!=(uintptr_t)bulkCallback578_original)return 579;
 if(bulkCallbackIdentity((void*)bulkCallback579_original)!=(uintptr_t)bulkCallback579_original || bulkCallbackIdentity((void*)bulkCallback579_linked)!=(uintptr_t)bulkCallback579_original)return 580;
 if(bulkCallbackIdentity((void*)bulkCallback580_original)!=(uintptr_t)bulkCallback580_original || bulkCallbackIdentity((void*)bulkCallback580_linked)!=(uintptr_t)bulkCallback580_original)return 581;
 if(bulkCallbackIdentity((void*)bulkCallback581_original)!=(uintptr_t)bulkCallback581_original || bulkCallbackIdentity((void*)bulkCallback581_linked)!=(uintptr_t)bulkCallback581_original)return 582;
 if(bulkCallbackIdentity((void*)bulkCallback582_original)!=(uintptr_t)bulkCallback582_original || bulkCallbackIdentity((void*)bulkCallback582_linked)!=(uintptr_t)bulkCallback582_original)return 583;
 if(bulkCallbackIdentity((void*)bulkCallback583_original)!=(uintptr_t)bulkCallback583_original || bulkCallbackIdentity((void*)bulkCallback583_linked)!=(uintptr_t)bulkCallback583_original)return 584;
 if(bulkCallbackIdentity((void*)bulkCallback584_original)!=(uintptr_t)bulkCallback584_original || bulkCallbackIdentity((void*)bulkCallback584_linked)!=(uintptr_t)bulkCallback584_original)return 585;
 if(bulkCallbackIdentity((void*)bulkCallback585_original)!=(uintptr_t)bulkCallback585_original || bulkCallbackIdentity((void*)bulkCallback585_linked)!=(uintptr_t)bulkCallback585_original)return 586;
 if(bulkCallbackIdentity((void*)bulkCallback586_original)!=(uintptr_t)bulkCallback586_original || bulkCallbackIdentity((void*)bulkCallback586_linked)!=(uintptr_t)bulkCallback586_original)return 587;
 if(bulkCallbackIdentity((void*)bulkCallback587_original)!=(uintptr_t)bulkCallback587_original || bulkCallbackIdentity((void*)bulkCallback587_linked)!=(uintptr_t)bulkCallback587_original)return 588;
 if(bulkCallbackIdentity((void*)bulkCallback588_original)!=(uintptr_t)bulkCallback588_original || bulkCallbackIdentity((void*)bulkCallback588_linked)!=(uintptr_t)bulkCallback588_original)return 589;
 if(bulkCallbackIdentity((void*)bulkCallback589_original)!=(uintptr_t)bulkCallback589_original || bulkCallbackIdentity((void*)bulkCallback589_linked)!=(uintptr_t)bulkCallback589_original)return 590;
 if(bulkCallbackIdentity((void*)bulkCallback590_original)!=(uintptr_t)bulkCallback590_original || bulkCallbackIdentity((void*)bulkCallback590_linked)!=(uintptr_t)bulkCallback590_original)return 591;
 if(bulkCallbackIdentity((void*)bulkCallback591_original)!=(uintptr_t)bulkCallback591_original || bulkCallbackIdentity((void*)bulkCallback591_linked)!=(uintptr_t)bulkCallback591_original)return 592;
 if(bulkCallbackIdentity((void*)bulkCallback592_original)!=(uintptr_t)bulkCallback592_original || bulkCallbackIdentity((void*)bulkCallback592_linked)!=(uintptr_t)bulkCallback592_original)return 593;
 if(bulkCallbackIdentity((void*)bulkCallback593_original)!=(uintptr_t)bulkCallback593_original || bulkCallbackIdentity((void*)bulkCallback593_linked)!=(uintptr_t)bulkCallback593_original)return 594;
 if(bulkCallbackIdentity((void*)bulkCallback594_original)!=(uintptr_t)bulkCallback594_original || bulkCallbackIdentity((void*)bulkCallback594_linked)!=(uintptr_t)bulkCallback594_original)return 595;
 if(bulkCallbackIdentity((void*)bulkCallback595_original)!=(uintptr_t)bulkCallback595_original || bulkCallbackIdentity((void*)bulkCallback595_linked)!=(uintptr_t)bulkCallback595_original)return 596;
 if(bulkCallbackIdentity((void*)bulkCallback596_original)!=(uintptr_t)bulkCallback596_original || bulkCallbackIdentity((void*)bulkCallback596_linked)!=(uintptr_t)bulkCallback596_original)return 597;
 if(bulkCallbackIdentity((void*)bulkCallback597_original)!=(uintptr_t)bulkCallback597_original || bulkCallbackIdentity((void*)bulkCallback597_linked)!=(uintptr_t)bulkCallback597_original)return 598;
 if(bulkCallbackIdentity((void*)bulkCallback598_original)!=(uintptr_t)bulkCallback598_original || bulkCallbackIdentity((void*)bulkCallback598_linked)!=(uintptr_t)bulkCallback598_original)return 599;
 if(bulkCallbackIdentity((void*)bulkCallback599_original)!=(uintptr_t)bulkCallback599_original || bulkCallbackIdentity((void*)bulkCallback599_linked)!=(uintptr_t)bulkCallback599_original)return 600;
 if(bulkCallbackIdentity((void*)bulkCallback600_original)!=(uintptr_t)bulkCallback600_original || bulkCallbackIdentity((void*)bulkCallback600_linked)!=(uintptr_t)bulkCallback600_original)return 601;
 if(bulkCallbackIdentity((void*)bulkCallback601_original)!=(uintptr_t)bulkCallback601_original || bulkCallbackIdentity((void*)bulkCallback601_linked)!=(uintptr_t)bulkCallback601_original)return 602;
 if(bulkCallbackIdentity((void*)bulkCallback602_original)!=(uintptr_t)bulkCallback602_original || bulkCallbackIdentity((void*)bulkCallback602_linked)!=(uintptr_t)bulkCallback602_original)return 603;
 if(bulkCallbackIdentity((void*)bulkCallback603_original)!=(uintptr_t)bulkCallback603_original || bulkCallbackIdentity((void*)bulkCallback603_linked)!=(uintptr_t)bulkCallback603_original)return 604;
 if(bulkCallbackIdentity((void*)bulkCallback604_original)!=(uintptr_t)bulkCallback604_original || bulkCallbackIdentity((void*)bulkCallback604_linked)!=(uintptr_t)bulkCallback604_original)return 605;
 if(bulkCallbackIdentity((void*)bulkCallback605_original)!=(uintptr_t)bulkCallback605_original || bulkCallbackIdentity((void*)bulkCallback605_linked)!=(uintptr_t)bulkCallback605_original)return 606;
 if(bulkCallbackIdentity((void*)bulkCallback606_original)!=(uintptr_t)bulkCallback606_original || bulkCallbackIdentity((void*)bulkCallback606_linked)!=(uintptr_t)bulkCallback606_original)return 607;
 if(bulkCallbackIdentity((void*)bulkCallback607_original)!=(uintptr_t)bulkCallback607_original || bulkCallbackIdentity((void*)bulkCallback607_linked)!=(uintptr_t)bulkCallback607_original)return 608;
 if(bulkCallbackIdentity((void*)bulkCallback608_original)!=(uintptr_t)bulkCallback608_original || bulkCallbackIdentity((void*)bulkCallback608_linked)!=(uintptr_t)bulkCallback608_original)return 609;
 if(bulkCallbackIdentity((void*)bulkCallback609_original)!=(uintptr_t)bulkCallback609_original || bulkCallbackIdentity((void*)bulkCallback609_linked)!=(uintptr_t)bulkCallback609_original)return 610;
 if(bulkCallbackIdentity((void*)bulkCallback610_original)!=(uintptr_t)bulkCallback610_original || bulkCallbackIdentity((void*)bulkCallback610_linked)!=(uintptr_t)bulkCallback610_original)return 611;
 if(bulkCallbackIdentity((void*)bulkCallback611_original)!=(uintptr_t)bulkCallback611_original || bulkCallbackIdentity((void*)bulkCallback611_linked)!=(uintptr_t)bulkCallback611_original)return 612;
 if(bulkCallbackIdentity((void*)bulkCallback612_original)!=(uintptr_t)bulkCallback612_original || bulkCallbackIdentity((void*)bulkCallback612_linked)!=(uintptr_t)bulkCallback612_original)return 613;
 if(bulkCallbackIdentity((void*)bulkCallback613_original)!=(uintptr_t)bulkCallback613_original || bulkCallbackIdentity((void*)bulkCallback613_linked)!=(uintptr_t)bulkCallback613_original)return 614;
 if(bulkCallbackIdentity((void*)bulkCallback614_original)!=(uintptr_t)bulkCallback614_original || bulkCallbackIdentity((void*)bulkCallback614_linked)!=(uintptr_t)bulkCallback614_original)return 615;
 if(bulkCallbackIdentity((void*)bulkCallback615_original)!=(uintptr_t)bulkCallback615_original || bulkCallbackIdentity((void*)bulkCallback615_linked)!=(uintptr_t)bulkCallback615_original)return 616;
 if(bulkCallbackIdentity((void*)bulkCallback616_original)!=(uintptr_t)bulkCallback616_original || bulkCallbackIdentity((void*)bulkCallback616_linked)!=(uintptr_t)bulkCallback616_original)return 617;
 if(bulkCallbackIdentity((void*)bulkCallback617_original)!=(uintptr_t)bulkCallback617_original || bulkCallbackIdentity((void*)bulkCallback617_linked)!=(uintptr_t)bulkCallback617_original)return 618;
 if(bulkCallbackIdentity((void*)bulkCallback618_original)!=(uintptr_t)bulkCallback618_original || bulkCallbackIdentity((void*)bulkCallback618_linked)!=(uintptr_t)bulkCallback618_original)return 619;
 if(bulkCallbackIdentity((void*)bulkCallback619_original)!=(uintptr_t)bulkCallback619_original || bulkCallbackIdentity((void*)bulkCallback619_linked)!=(uintptr_t)bulkCallback619_original)return 620;
 if(bulkCallbackIdentity((void*)bulkCallback620_original)!=(uintptr_t)bulkCallback620_original || bulkCallbackIdentity((void*)bulkCallback620_linked)!=(uintptr_t)bulkCallback620_original)return 621;
 if(bulkCallbackIdentity((void*)bulkCallback621_original)!=(uintptr_t)bulkCallback621_original || bulkCallbackIdentity((void*)bulkCallback621_linked)!=(uintptr_t)bulkCallback621_original)return 622;
 if(bulkCallbackIdentity((void*)bulkCallback622_original)!=(uintptr_t)bulkCallback622_original || bulkCallbackIdentity((void*)bulkCallback622_linked)!=(uintptr_t)bulkCallback622_original)return 623;
 if(bulkCallbackIdentity((void*)bulkCallback623_original)!=(uintptr_t)bulkCallback623_original || bulkCallbackIdentity((void*)bulkCallback623_linked)!=(uintptr_t)bulkCallback623_original)return 624;
 if(bulkCallbackIdentity((void*)bulkCallback624_original)!=(uintptr_t)bulkCallback624_original || bulkCallbackIdentity((void*)bulkCallback624_linked)!=(uintptr_t)bulkCallback624_original)return 625;
 if(bulkCallbackIdentity((void*)bulkCallback625_original)!=(uintptr_t)bulkCallback625_original || bulkCallbackIdentity((void*)bulkCallback625_linked)!=(uintptr_t)bulkCallback625_original)return 626;
 if(bulkCallbackIdentity((void*)bulkCallback626_original)!=(uintptr_t)bulkCallback626_original || bulkCallbackIdentity((void*)bulkCallback626_linked)!=(uintptr_t)bulkCallback626_original)return 627;
 if(bulkCallbackIdentity((void*)bulkCallback627_original)!=(uintptr_t)bulkCallback627_original || bulkCallbackIdentity((void*)bulkCallback627_linked)!=(uintptr_t)bulkCallback627_original)return 628;
 if(bulkCallbackIdentity((void*)bulkCallback628_original)!=(uintptr_t)bulkCallback628_original || bulkCallbackIdentity((void*)bulkCallback628_linked)!=(uintptr_t)bulkCallback628_original)return 629;
 if(bulkCallbackIdentity((void*)bulkCallback629_original)!=(uintptr_t)bulkCallback629_original || bulkCallbackIdentity((void*)bulkCallback629_linked)!=(uintptr_t)bulkCallback629_original)return 630;
 if(bulkCallbackIdentity((void*)bulkCallback630_original)!=(uintptr_t)bulkCallback630_original || bulkCallbackIdentity((void*)bulkCallback630_linked)!=(uintptr_t)bulkCallback630_original)return 631;
 if(bulkCallbackIdentity((void*)bulkCallback631_original)!=(uintptr_t)bulkCallback631_original || bulkCallbackIdentity((void*)bulkCallback631_linked)!=(uintptr_t)bulkCallback631_original)return 632;
 if(bulkCallbackIdentity((void*)bulkCallback632_original)!=(uintptr_t)bulkCallback632_original || bulkCallbackIdentity((void*)bulkCallback632_linked)!=(uintptr_t)bulkCallback632_original)return 633;
 if(bulkCallbackIdentity((void*)bulkCallback633_original)!=(uintptr_t)bulkCallback633_original || bulkCallbackIdentity((void*)bulkCallback633_linked)!=(uintptr_t)bulkCallback633_original)return 634;
 if(bulkCallbackIdentity((void*)bulkCallback634_original)!=(uintptr_t)bulkCallback634_original || bulkCallbackIdentity((void*)bulkCallback634_linked)!=(uintptr_t)bulkCallback634_original)return 635;
 if(bulkCallbackIdentity((void*)bulkCallback635_original)!=(uintptr_t)bulkCallback635_original || bulkCallbackIdentity((void*)bulkCallback635_linked)!=(uintptr_t)bulkCallback635_original)return 636;
 if(bulkCallbackIdentity((void*)bulkCallback636_original)!=(uintptr_t)bulkCallback636_original || bulkCallbackIdentity((void*)bulkCallback636_linked)!=(uintptr_t)bulkCallback636_original)return 637;
 if(bulkCallbackIdentity((void*)bulkCallback637_original)!=(uintptr_t)bulkCallback637_original || bulkCallbackIdentity((void*)bulkCallback637_linked)!=(uintptr_t)bulkCallback637_original)return 638;
 if(bulkCallbackIdentity((void*)bulkCallback638_original)!=(uintptr_t)bulkCallback638_original || bulkCallbackIdentity((void*)bulkCallback638_linked)!=(uintptr_t)bulkCallback638_original)return 639;
 if(bulkCallbackIdentity((void*)bulkCallback639_original)!=(uintptr_t)bulkCallback639_original || bulkCallbackIdentity((void*)bulkCallback639_linked)!=(uintptr_t)bulkCallback639_original)return 640;
 if(bulkCallbackIdentity((void*)bulkCallback640_original)!=(uintptr_t)bulkCallback640_original || bulkCallbackIdentity((void*)bulkCallback640_linked)!=(uintptr_t)bulkCallback640_original)return 641;
 if(bulkCallbackIdentity((void*)bulkCallback641_original)!=(uintptr_t)bulkCallback641_original || bulkCallbackIdentity((void*)bulkCallback641_linked)!=(uintptr_t)bulkCallback641_original)return 642;
 if(bulkCallbackIdentity((void*)bulkCallback642_original)!=(uintptr_t)bulkCallback642_original || bulkCallbackIdentity((void*)bulkCallback642_linked)!=(uintptr_t)bulkCallback642_original)return 643;
 if(bulkCallbackIdentity((void*)bulkCallback643_original)!=(uintptr_t)bulkCallback643_original || bulkCallbackIdentity((void*)bulkCallback643_linked)!=(uintptr_t)bulkCallback643_original)return 644;
 if(bulkCallbackIdentity((void*)bulkCallback644_original)!=(uintptr_t)bulkCallback644_original || bulkCallbackIdentity((void*)bulkCallback644_linked)!=(uintptr_t)bulkCallback644_original)return 645;
 if(bulkCallbackIdentity((void*)bulkCallback645_original)!=(uintptr_t)bulkCallback645_original || bulkCallbackIdentity((void*)bulkCallback645_linked)!=(uintptr_t)bulkCallback645_original)return 646;
 if(bulkCallbackIdentity((void*)bulkCallback646_original)!=(uintptr_t)bulkCallback646_original || bulkCallbackIdentity((void*)bulkCallback646_linked)!=(uintptr_t)bulkCallback646_original)return 647;
 if(bulkCallbackIdentity((void*)bulkCallback647_original)!=(uintptr_t)bulkCallback647_original || bulkCallbackIdentity((void*)bulkCallback647_linked)!=(uintptr_t)bulkCallback647_original)return 648;
 if(bulkCallbackIdentity((void*)bulkCallback648_original)!=(uintptr_t)bulkCallback648_original || bulkCallbackIdentity((void*)bulkCallback648_linked)!=(uintptr_t)bulkCallback648_original)return 649;
 if(bulkCallbackIdentity((void*)bulkCallback649_original)!=(uintptr_t)bulkCallback649_original || bulkCallbackIdentity((void*)bulkCallback649_linked)!=(uintptr_t)bulkCallback649_original)return 650;
 if(bulkCallbackIdentity((void*)bulkCallback650_original)!=(uintptr_t)bulkCallback650_original || bulkCallbackIdentity((void*)bulkCallback650_linked)!=(uintptr_t)bulkCallback650_original)return 651;
 if(bulkCallbackIdentity((void*)bulkCallback651_original)!=(uintptr_t)bulkCallback651_original || bulkCallbackIdentity((void*)bulkCallback651_linked)!=(uintptr_t)bulkCallback651_original)return 652;
 if(bulkCallbackIdentity((void*)bulkCallback652_original)!=(uintptr_t)bulkCallback652_original || bulkCallbackIdentity((void*)bulkCallback652_linked)!=(uintptr_t)bulkCallback652_original)return 653;
 if(bulkCallbackIdentity((void*)bulkCallback653_original)!=(uintptr_t)bulkCallback653_original || bulkCallbackIdentity((void*)bulkCallback653_linked)!=(uintptr_t)bulkCallback653_original)return 654;
 if(bulkCallbackIdentity((void*)bulkCallback654_original)!=(uintptr_t)bulkCallback654_original || bulkCallbackIdentity((void*)bulkCallback654_linked)!=(uintptr_t)bulkCallback654_original)return 655;
 if(bulkCallbackIdentity((void*)bulkCallback655_original)!=(uintptr_t)bulkCallback655_original || bulkCallbackIdentity((void*)bulkCallback655_linked)!=(uintptr_t)bulkCallback655_original)return 656;
 if(bulkCallbackIdentity((void*)bulkCallback656_original)!=(uintptr_t)bulkCallback656_original || bulkCallbackIdentity((void*)bulkCallback656_linked)!=(uintptr_t)bulkCallback656_original)return 657;
 if(bulkCallbackIdentity((void*)bulkCallback657_original)!=(uintptr_t)bulkCallback657_original || bulkCallbackIdentity((void*)bulkCallback657_linked)!=(uintptr_t)bulkCallback657_original)return 658;
 if(bulkCallbackIdentity((void*)bulkCallback658_original)!=(uintptr_t)bulkCallback658_original || bulkCallbackIdentity((void*)bulkCallback658_linked)!=(uintptr_t)bulkCallback658_original)return 659;
 if(bulkCallbackIdentity((void*)bulkCallback659_original)!=(uintptr_t)bulkCallback659_original || bulkCallbackIdentity((void*)bulkCallback659_linked)!=(uintptr_t)bulkCallback659_original)return 660;
 if(bulkCallbackIdentity((void*)bulkCallback660_original)!=(uintptr_t)bulkCallback660_original || bulkCallbackIdentity((void*)bulkCallback660_linked)!=(uintptr_t)bulkCallback660_original)return 661;
 if(bulkCallbackIdentity((void*)bulkCallback661_original)!=(uintptr_t)bulkCallback661_original || bulkCallbackIdentity((void*)bulkCallback661_linked)!=(uintptr_t)bulkCallback661_original)return 662;
 if(bulkCallbackIdentity((void*)bulkCallback662_original)!=(uintptr_t)bulkCallback662_original || bulkCallbackIdentity((void*)bulkCallback662_linked)!=(uintptr_t)bulkCallback662_original)return 663;
 if(bulkCallbackIdentity((void*)bulkCallback663_original)!=(uintptr_t)bulkCallback663_original || bulkCallbackIdentity((void*)bulkCallback663_linked)!=(uintptr_t)bulkCallback663_original)return 664;
 if(bulkCallbackIdentity((void*)bulkCallback664_original)!=(uintptr_t)bulkCallback664_original || bulkCallbackIdentity((void*)bulkCallback664_linked)!=(uintptr_t)bulkCallback664_original)return 665;
 if(bulkCallbackIdentity((void*)bulkCallback665_original)!=(uintptr_t)bulkCallback665_original || bulkCallbackIdentity((void*)bulkCallback665_linked)!=(uintptr_t)bulkCallback665_original)return 666;
 if(bulkCallbackIdentity((void*)bulkCallback666_original)!=(uintptr_t)bulkCallback666_original || bulkCallbackIdentity((void*)bulkCallback666_linked)!=(uintptr_t)bulkCallback666_original)return 667;
 if(bulkCallbackIdentity((void*)bulkCallback667_original)!=(uintptr_t)bulkCallback667_original || bulkCallbackIdentity((void*)bulkCallback667_linked)!=(uintptr_t)bulkCallback667_original)return 668;
 if(bulkCallbackIdentity((void*)bulkCallback668_original)!=(uintptr_t)bulkCallback668_original || bulkCallbackIdentity((void*)bulkCallback668_linked)!=(uintptr_t)bulkCallback668_original)return 669;
 if(bulkCallbackIdentity((void*)bulkCallback669_original)!=(uintptr_t)bulkCallback669_original || bulkCallbackIdentity((void*)bulkCallback669_linked)!=(uintptr_t)bulkCallback669_original)return 670;
 if(bulkCallbackIdentity((void*)bulkCallback670_original)!=(uintptr_t)bulkCallback670_original || bulkCallbackIdentity((void*)bulkCallback670_linked)!=(uintptr_t)bulkCallback670_original)return 671;
 if(bulkCallbackIdentity((void*)bulkCallback671_original)!=(uintptr_t)bulkCallback671_original || bulkCallbackIdentity((void*)bulkCallback671_linked)!=(uintptr_t)bulkCallback671_original)return 672;
 if(bulkCallbackIdentity((void*)bulkCallback672_original)!=(uintptr_t)bulkCallback672_original || bulkCallbackIdentity((void*)bulkCallback672_linked)!=(uintptr_t)bulkCallback672_original)return 673;
 if(bulkCallbackIdentity((void*)bulkCallback673_original)!=(uintptr_t)bulkCallback673_original || bulkCallbackIdentity((void*)bulkCallback673_linked)!=(uintptr_t)bulkCallback673_original)return 674;
 if(bulkCallbackIdentity((void*)bulkCallback674_original)!=(uintptr_t)bulkCallback674_original || bulkCallbackIdentity((void*)bulkCallback674_linked)!=(uintptr_t)bulkCallback674_original)return 675;
 if(bulkCallbackIdentity((void*)bulkCallback675_original)!=(uintptr_t)bulkCallback675_original || bulkCallbackIdentity((void*)bulkCallback675_linked)!=(uintptr_t)bulkCallback675_original)return 676;
 if(bulkCallbackIdentity((void*)bulkCallback676_original)!=(uintptr_t)bulkCallback676_original || bulkCallbackIdentity((void*)bulkCallback676_linked)!=(uintptr_t)bulkCallback676_original)return 677;
 if(bulkCallbackIdentity((void*)bulkCallback677_original)!=(uintptr_t)bulkCallback677_original || bulkCallbackIdentity((void*)bulkCallback677_linked)!=(uintptr_t)bulkCallback677_original)return 678;
 if(bulkCallbackIdentity((void*)bulkCallback678_original)!=(uintptr_t)bulkCallback678_original || bulkCallbackIdentity((void*)bulkCallback678_linked)!=(uintptr_t)bulkCallback678_original)return 679;
 if(bulkCallbackIdentity((void*)bulkCallback679_original)!=(uintptr_t)bulkCallback679_original || bulkCallbackIdentity((void*)bulkCallback679_linked)!=(uintptr_t)bulkCallback679_original)return 680;
 if(bulkCallbackIdentity((void*)bulkCallback680_original)!=(uintptr_t)bulkCallback680_original || bulkCallbackIdentity((void*)bulkCallback680_linked)!=(uintptr_t)bulkCallback680_original)return 681;
 if(bulkCallbackIdentity((void*)bulkCallback681_original)!=(uintptr_t)bulkCallback681_original || bulkCallbackIdentity((void*)bulkCallback681_linked)!=(uintptr_t)bulkCallback681_original)return 682;
 if(bulkCallbackIdentity((void*)bulkCallback682_original)!=(uintptr_t)bulkCallback682_original || bulkCallbackIdentity((void*)bulkCallback682_linked)!=(uintptr_t)bulkCallback682_original)return 683;
 if(bulkCallbackIdentity((void*)bulkCallback683_original)!=(uintptr_t)bulkCallback683_original || bulkCallbackIdentity((void*)bulkCallback683_linked)!=(uintptr_t)bulkCallback683_original)return 684;
 if(bulkCallbackIdentity((void*)bulkCallback684_original)!=(uintptr_t)bulkCallback684_original || bulkCallbackIdentity((void*)bulkCallback684_linked)!=(uintptr_t)bulkCallback684_original)return 685;
 if(bulkCallbackIdentity((void*)bulkCallback685_original)!=(uintptr_t)bulkCallback685_original || bulkCallbackIdentity((void*)bulkCallback685_linked)!=(uintptr_t)bulkCallback685_original)return 686;
 if(bulkCallbackIdentity((void*)bulkCallback686_original)!=(uintptr_t)bulkCallback686_original || bulkCallbackIdentity((void*)bulkCallback686_linked)!=(uintptr_t)bulkCallback686_original)return 687;
 if(bulkCallbackIdentity((void*)bulkCallback687_original)!=(uintptr_t)bulkCallback687_original || bulkCallbackIdentity((void*)bulkCallback687_linked)!=(uintptr_t)bulkCallback687_original)return 688;
 if(bulkCallbackIdentity((void*)bulkCallback688_original)!=(uintptr_t)bulkCallback688_original || bulkCallbackIdentity((void*)bulkCallback688_linked)!=(uintptr_t)bulkCallback688_original)return 689;
 if(bulkCallbackIdentity((void*)bulkCallback689_original)!=(uintptr_t)bulkCallback689_original || bulkCallbackIdentity((void*)bulkCallback689_linked)!=(uintptr_t)bulkCallback689_original)return 690;
 if(bulkCallbackIdentity((void*)bulkCallback690_original)!=(uintptr_t)bulkCallback690_original || bulkCallbackIdentity((void*)bulkCallback690_linked)!=(uintptr_t)bulkCallback690_original)return 691;
 if(bulkCallbackIdentity((void*)bulkCallback691_original)!=(uintptr_t)bulkCallback691_original || bulkCallbackIdentity((void*)bulkCallback691_linked)!=(uintptr_t)bulkCallback691_original)return 692;
 if(bulkCallbackIdentity((void*)bulkCallback692_original)!=(uintptr_t)bulkCallback692_original || bulkCallbackIdentity((void*)bulkCallback692_linked)!=(uintptr_t)bulkCallback692_original)return 693;
 if(bulkCallbackIdentity((void*)bulkCallback693_original)!=(uintptr_t)bulkCallback693_original || bulkCallbackIdentity((void*)bulkCallback693_linked)!=(uintptr_t)bulkCallback693_original)return 694;
 if(bulkCallbackIdentity((void*)bulkCallback694_original)!=(uintptr_t)bulkCallback694_original || bulkCallbackIdentity((void*)bulkCallback694_linked)!=(uintptr_t)bulkCallback694_original)return 695;
 if(bulkCallbackIdentity((void*)bulkCallback695_original)!=(uintptr_t)bulkCallback695_original || bulkCallbackIdentity((void*)bulkCallback695_linked)!=(uintptr_t)bulkCallback695_original)return 696;
 if(bulkCallbackIdentity((void*)bulkCallback696_original)!=(uintptr_t)bulkCallback696_original || bulkCallbackIdentity((void*)bulkCallback696_linked)!=(uintptr_t)bulkCallback696_original)return 697;
 if(bulkCallbackIdentity((void*)bulkCallback697_original)!=(uintptr_t)bulkCallback697_original || bulkCallbackIdentity((void*)bulkCallback697_linked)!=(uintptr_t)bulkCallback697_original)return 698;
 if(bulkCallbackIdentity((void*)bulkCallback698_original)!=(uintptr_t)bulkCallback698_original || bulkCallbackIdentity((void*)bulkCallback698_linked)!=(uintptr_t)bulkCallback698_original)return 699;
 if(bulkCallbackIdentity((void*)bulkCallback699_original)!=(uintptr_t)bulkCallback699_original || bulkCallbackIdentity((void*)bulkCallback699_linked)!=(uintptr_t)bulkCallback699_original)return 700;
 if(bulkCallbackIdentity((void*)bulkCallback700_original)!=(uintptr_t)bulkCallback700_original || bulkCallbackIdentity((void*)bulkCallback700_linked)!=(uintptr_t)bulkCallback700_original)return 701;
 if(bulkCallbackIdentity((void*)bulkCallback701_original)!=(uintptr_t)bulkCallback701_original || bulkCallbackIdentity((void*)bulkCallback701_linked)!=(uintptr_t)bulkCallback701_original)return 702;
 if(bulkCallbackIdentity((void*)bulkCallback702_original)!=(uintptr_t)bulkCallback702_original || bulkCallbackIdentity((void*)bulkCallback702_linked)!=(uintptr_t)bulkCallback702_original)return 703;
 if(bulkCallbackIdentity((void*)bulkCallback703_original)!=(uintptr_t)bulkCallback703_original || bulkCallbackIdentity((void*)bulkCallback703_linked)!=(uintptr_t)bulkCallback703_original)return 704;
 if(bulkCallbackIdentity((void*)bulkCallback704_original)!=(uintptr_t)bulkCallback704_original || bulkCallbackIdentity((void*)bulkCallback704_linked)!=(uintptr_t)bulkCallback704_original)return 705;
 if(bulkCallbackIdentity((void*)bulkCallback705_original)!=(uintptr_t)bulkCallback705_original || bulkCallbackIdentity((void*)bulkCallback705_linked)!=(uintptr_t)bulkCallback705_original)return 706;
 if(bulkCallbackIdentity((void*)bulkCallback706_original)!=(uintptr_t)bulkCallback706_original || bulkCallbackIdentity((void*)bulkCallback706_linked)!=(uintptr_t)bulkCallback706_original)return 707;
 if(bulkCallbackIdentity((void*)bulkCallback707_original)!=(uintptr_t)bulkCallback707_original || bulkCallbackIdentity((void*)bulkCallback707_linked)!=(uintptr_t)bulkCallback707_original)return 708;
 if(bulkCallbackIdentity((void*)bulkCallback708_original)!=(uintptr_t)bulkCallback708_original || bulkCallbackIdentity((void*)bulkCallback708_linked)!=(uintptr_t)bulkCallback708_original)return 709;
 if(bulkCallbackIdentity((void*)bulkCallback709_original)!=(uintptr_t)bulkCallback709_original || bulkCallbackIdentity((void*)bulkCallback709_linked)!=(uintptr_t)bulkCallback709_original)return 710;
 if(bulkCallbackIdentity((void*)bulkCallback710_original)!=(uintptr_t)bulkCallback710_original || bulkCallbackIdentity((void*)bulkCallback710_linked)!=(uintptr_t)bulkCallback710_original)return 711;
 if(bulkCallbackIdentity((void*)bulkCallback711_original)!=(uintptr_t)bulkCallback711_original || bulkCallbackIdentity((void*)bulkCallback711_linked)!=(uintptr_t)bulkCallback711_original)return 712;
 if(bulkCallbackIdentity((void*)bulkCallback712_original)!=(uintptr_t)bulkCallback712_original || bulkCallbackIdentity((void*)bulkCallback712_linked)!=(uintptr_t)bulkCallback712_original)return 713;
 if(bulkCallbackIdentity((void*)bulkCallback713_original)!=(uintptr_t)bulkCallback713_original || bulkCallbackIdentity((void*)bulkCallback713_linked)!=(uintptr_t)bulkCallback713_original)return 714;
 if(bulkCallbackIdentity((void*)bulkCallback714_original)!=(uintptr_t)bulkCallback714_original || bulkCallbackIdentity((void*)bulkCallback714_linked)!=(uintptr_t)bulkCallback714_original)return 715;
 if(bulkCallbackIdentity((void*)bulkCallback715_original)!=(uintptr_t)bulkCallback715_original || bulkCallbackIdentity((void*)bulkCallback715_linked)!=(uintptr_t)bulkCallback715_original)return 716;
 if(bulkCallbackIdentity((void*)bulkCallback716_original)!=(uintptr_t)bulkCallback716_original || bulkCallbackIdentity((void*)bulkCallback716_linked)!=(uintptr_t)bulkCallback716_original)return 717;
 if(bulkCallbackIdentity((void*)bulkCallback717_original)!=(uintptr_t)bulkCallback717_original || bulkCallbackIdentity((void*)bulkCallback717_linked)!=(uintptr_t)bulkCallback717_original)return 718;
 if(bulkCallbackIdentity((void*)bulkCallback718_original)!=(uintptr_t)bulkCallback718_original || bulkCallbackIdentity((void*)bulkCallback718_linked)!=(uintptr_t)bulkCallback718_original)return 719;
 if(bulkCallbackIdentity((void*)bulkCallback719_original)!=(uintptr_t)bulkCallback719_original || bulkCallbackIdentity((void*)bulkCallback719_linked)!=(uintptr_t)bulkCallback719_original)return 720;
 if(bulkCallbackIdentity((void*)bulkCallback720_original)!=(uintptr_t)bulkCallback720_original || bulkCallbackIdentity((void*)bulkCallback720_linked)!=(uintptr_t)bulkCallback720_original)return 721;
 if(bulkCallbackIdentity((void*)bulkCallback721_original)!=(uintptr_t)bulkCallback721_original || bulkCallbackIdentity((void*)bulkCallback721_linked)!=(uintptr_t)bulkCallback721_original)return 722;
 if(bulkCallbackIdentity((void*)bulkCallback722_original)!=(uintptr_t)bulkCallback722_original || bulkCallbackIdentity((void*)bulkCallback722_linked)!=(uintptr_t)bulkCallback722_original)return 723;
 if(bulkCallbackIdentity((void*)bulkCallback723_original)!=(uintptr_t)bulkCallback723_original || bulkCallbackIdentity((void*)bulkCallback723_linked)!=(uintptr_t)bulkCallback723_original)return 724;
 if(bulkCallbackIdentity((void*)bulkCallback724_original)!=(uintptr_t)bulkCallback724_original || bulkCallbackIdentity((void*)bulkCallback724_linked)!=(uintptr_t)bulkCallback724_original)return 725;
 if(bulkCallbackIdentity((void*)bulkCallback725_original)!=(uintptr_t)bulkCallback725_original || bulkCallbackIdentity((void*)bulkCallback725_linked)!=(uintptr_t)bulkCallback725_original)return 726;
 if(bulkCallbackIdentity((void*)bulkCallback726_original)!=(uintptr_t)bulkCallback726_original || bulkCallbackIdentity((void*)bulkCallback726_linked)!=(uintptr_t)bulkCallback726_original)return 727;
 if(bulkCallbackIdentity((void*)bulkCallback727_original)!=(uintptr_t)bulkCallback727_original || bulkCallbackIdentity((void*)bulkCallback727_linked)!=(uintptr_t)bulkCallback727_original)return 728;
 if(bulkCallbackIdentity((void*)bulkCallback728_original)!=(uintptr_t)bulkCallback728_original || bulkCallbackIdentity((void*)bulkCallback728_linked)!=(uintptr_t)bulkCallback728_original)return 729;
 if(bulkCallbackIdentity((void*)bulkCallback729_original)!=(uintptr_t)bulkCallback729_original || bulkCallbackIdentity((void*)bulkCallback729_linked)!=(uintptr_t)bulkCallback729_original)return 730;
 if(bulkCallbackIdentity((void*)bulkCallback730_original)!=(uintptr_t)bulkCallback730_original || bulkCallbackIdentity((void*)bulkCallback730_linked)!=(uintptr_t)bulkCallback730_original)return 731;
 if(bulkCallbackIdentity((void*)bulkCallback731_original)!=(uintptr_t)bulkCallback731_original || bulkCallbackIdentity((void*)bulkCallback731_linked)!=(uintptr_t)bulkCallback731_original)return 732;
 if(bulkCallbackIdentity((void*)bulkCallback732_original)!=(uintptr_t)bulkCallback732_original || bulkCallbackIdentity((void*)bulkCallback732_linked)!=(uintptr_t)bulkCallback732_original)return 733;
 if(bulkCallbackIdentity((void*)bulkCallback733_original)!=(uintptr_t)bulkCallback733_original || bulkCallbackIdentity((void*)bulkCallback733_linked)!=(uintptr_t)bulkCallback733_original)return 734;
 if(bulkCallbackIdentity((void*)bulkCallback734_original)!=(uintptr_t)bulkCallback734_original || bulkCallbackIdentity((void*)bulkCallback734_linked)!=(uintptr_t)bulkCallback734_original)return 735;
 if(bulkCallbackIdentity((void*)bulkCallback735_original)!=(uintptr_t)bulkCallback735_original || bulkCallbackIdentity((void*)bulkCallback735_linked)!=(uintptr_t)bulkCallback735_original)return 736;
 if(bulkCallbackIdentity((void*)bulkCallback736_original)!=(uintptr_t)bulkCallback736_original || bulkCallbackIdentity((void*)bulkCallback736_linked)!=(uintptr_t)bulkCallback736_original)return 737;
 if(bulkCallbackIdentity((void*)bulkCallback737_original)!=(uintptr_t)bulkCallback737_original || bulkCallbackIdentity((void*)bulkCallback737_linked)!=(uintptr_t)bulkCallback737_original)return 738;
 if(bulkCallbackIdentity((void*)bulkCallback738_original)!=(uintptr_t)bulkCallback738_original || bulkCallbackIdentity((void*)bulkCallback738_linked)!=(uintptr_t)bulkCallback738_original)return 739;
 if(bulkCallbackIdentity((void*)bulkCallback739_original)!=(uintptr_t)bulkCallback739_original || bulkCallbackIdentity((void*)bulkCallback739_linked)!=(uintptr_t)bulkCallback739_original)return 740;
 if(bulkCallbackIdentity((void*)bulkCallback740_original)!=(uintptr_t)bulkCallback740_original || bulkCallbackIdentity((void*)bulkCallback740_linked)!=(uintptr_t)bulkCallback740_original)return 741;
 if(bulkCallbackIdentity((void*)bulkCallback741_original)!=(uintptr_t)bulkCallback741_original || bulkCallbackIdentity((void*)bulkCallback741_linked)!=(uintptr_t)bulkCallback741_original)return 742;
 if(bulkCallbackIdentity((void*)bulkCallback742_original)!=(uintptr_t)bulkCallback742_original || bulkCallbackIdentity((void*)bulkCallback742_linked)!=(uintptr_t)bulkCallback742_original)return 743;
 if(bulkCallbackIdentity((void*)bulkCallback743_original)!=(uintptr_t)bulkCallback743_original || bulkCallbackIdentity((void*)bulkCallback743_linked)!=(uintptr_t)bulkCallback743_original)return 744;
 if(bulkCallbackIdentity((void*)bulkCallback744_original)!=(uintptr_t)bulkCallback744_original || bulkCallbackIdentity((void*)bulkCallback744_linked)!=(uintptr_t)bulkCallback744_original)return 745;
 if(bulkCallbackIdentity((void*)bulkCallback745_original)!=(uintptr_t)bulkCallback745_original || bulkCallbackIdentity((void*)bulkCallback745_linked)!=(uintptr_t)bulkCallback745_original)return 746;
 if(bulkCallbackIdentity((void*)bulkCallback746_original)!=(uintptr_t)bulkCallback746_original || bulkCallbackIdentity((void*)bulkCallback746_linked)!=(uintptr_t)bulkCallback746_original)return 747;
 if(bulkCallbackIdentity((void*)bulkCallback747_original)!=(uintptr_t)bulkCallback747_original || bulkCallbackIdentity((void*)bulkCallback747_linked)!=(uintptr_t)bulkCallback747_original)return 748;
 if(bulkCallbackIdentity((void*)bulkCallback748_original)!=(uintptr_t)bulkCallback748_original || bulkCallbackIdentity((void*)bulkCallback748_linked)!=(uintptr_t)bulkCallback748_original)return 749;
 if(bulkCallbackIdentity((void*)bulkCallback749_original)!=(uintptr_t)bulkCallback749_original || bulkCallbackIdentity((void*)bulkCallback749_linked)!=(uintptr_t)bulkCallback749_original)return 750;
 if(bulkCallbackIdentity((void*)bulkCallback750_original)!=(uintptr_t)bulkCallback750_original || bulkCallbackIdentity((void*)bulkCallback750_linked)!=(uintptr_t)bulkCallback750_original)return 751;
 if(bulkCallbackIdentity((void*)bulkCallback751_original)!=(uintptr_t)bulkCallback751_original || bulkCallbackIdentity((void*)bulkCallback751_linked)!=(uintptr_t)bulkCallback751_original)return 752;
 if(bulkCallbackIdentity((void*)bulkCallback752_original)!=(uintptr_t)bulkCallback752_original || bulkCallbackIdentity((void*)bulkCallback752_linked)!=(uintptr_t)bulkCallback752_original)return 753;
 if(bulkCallbackIdentity((void*)bulkCallback753_original)!=(uintptr_t)bulkCallback753_original || bulkCallbackIdentity((void*)bulkCallback753_linked)!=(uintptr_t)bulkCallback753_original)return 754;
 if(bulkCallbackIdentity((void*)bulkCallback754_original)!=(uintptr_t)bulkCallback754_original || bulkCallbackIdentity((void*)bulkCallback754_linked)!=(uintptr_t)bulkCallback754_original)return 755;
 if(bulkCallbackIdentity((void*)bulkCallback755_original)!=(uintptr_t)bulkCallback755_original || bulkCallbackIdentity((void*)bulkCallback755_linked)!=(uintptr_t)bulkCallback755_original)return 756;
 if(bulkCallbackIdentity((void*)bulkCallback756_original)!=(uintptr_t)bulkCallback756_original || bulkCallbackIdentity((void*)bulkCallback756_linked)!=(uintptr_t)bulkCallback756_original)return 757;
 if(bulkCallbackIdentity((void*)bulkCallback757_original)!=(uintptr_t)bulkCallback757_original || bulkCallbackIdentity((void*)bulkCallback757_linked)!=(uintptr_t)bulkCallback757_original)return 758;
 if(bulkCallbackIdentity((void*)bulkCallback758_original)!=(uintptr_t)bulkCallback758_original || bulkCallbackIdentity((void*)bulkCallback758_linked)!=(uintptr_t)bulkCallback758_original)return 759;
 if(bulkCallbackIdentity((void*)bulkCallback759_original)!=(uintptr_t)bulkCallback759_original || bulkCallbackIdentity((void*)bulkCallback759_linked)!=(uintptr_t)bulkCallback759_original)return 760;
 if(bulkCallbackIdentity((void*)bulkCallback760_original)!=(uintptr_t)bulkCallback760_original || bulkCallbackIdentity((void*)bulkCallback760_linked)!=(uintptr_t)bulkCallback760_original)return 761;
 if(bulkCallbackIdentity((void*)bulkCallback761_original)!=(uintptr_t)bulkCallback761_original || bulkCallbackIdentity((void*)bulkCallback761_linked)!=(uintptr_t)bulkCallback761_original)return 762;
 if(bulkCallbackIdentity((void*)bulkCallback762_original)!=(uintptr_t)bulkCallback762_original || bulkCallbackIdentity((void*)bulkCallback762_linked)!=(uintptr_t)bulkCallback762_original)return 763;
 if(bulkCallbackIdentity((void*)bulkCallback763_original)!=(uintptr_t)bulkCallback763_original || bulkCallbackIdentity((void*)bulkCallback763_linked)!=(uintptr_t)bulkCallback763_original)return 764;
 if(bulkCallbackIdentity((void*)bulkCallback764_original)!=(uintptr_t)bulkCallback764_original || bulkCallbackIdentity((void*)bulkCallback764_linked)!=(uintptr_t)bulkCallback764_original)return 765;
 if(bulkCallbackIdentity((void*)bulkCallback765_original)!=(uintptr_t)bulkCallback765_original || bulkCallbackIdentity((void*)bulkCallback765_linked)!=(uintptr_t)bulkCallback765_original)return 766;
 if(bulkCallbackIdentity((void*)bulkCallback766_original)!=(uintptr_t)bulkCallback766_original || bulkCallbackIdentity((void*)bulkCallback766_linked)!=(uintptr_t)bulkCallback766_original)return 767;
 if(bulkCallbackIdentity((void*)bulkCallback767_original)!=(uintptr_t)bulkCallback767_original || bulkCallbackIdentity((void*)bulkCallback767_linked)!=(uintptr_t)bulkCallback767_original)return 768;
 if(bulkCallbackIdentity((void*)bulkCallback768_original)!=(uintptr_t)bulkCallback768_original || bulkCallbackIdentity((void*)bulkCallback768_linked)!=(uintptr_t)bulkCallback768_original)return 769;
 if(bulkCallbackIdentity((void*)bulkCallback769_original)!=(uintptr_t)bulkCallback769_original || bulkCallbackIdentity((void*)bulkCallback769_linked)!=(uintptr_t)bulkCallback769_original)return 770;
 if(bulkCallbackIdentity((void*)bulkCallback770_original)!=(uintptr_t)bulkCallback770_original || bulkCallbackIdentity((void*)bulkCallback770_linked)!=(uintptr_t)bulkCallback770_original)return 771;
 if(bulkCallbackIdentity((void*)bulkCallback771_original)!=(uintptr_t)bulkCallback771_original || bulkCallbackIdentity((void*)bulkCallback771_linked)!=(uintptr_t)bulkCallback771_original)return 772;
 if(bulkCallbackIdentity((void*)bulkCallback772_original)!=(uintptr_t)bulkCallback772_original || bulkCallbackIdentity((void*)bulkCallback772_linked)!=(uintptr_t)bulkCallback772_original)return 773;
 if(bulkCallbackIdentity((void*)bulkCallback773_original)!=(uintptr_t)bulkCallback773_original || bulkCallbackIdentity((void*)bulkCallback773_linked)!=(uintptr_t)bulkCallback773_original)return 774;
 if(bulkCallbackIdentity((void*)bulkCallback774_original)!=(uintptr_t)bulkCallback774_original || bulkCallbackIdentity((void*)bulkCallback774_linked)!=(uintptr_t)bulkCallback774_original)return 775;
 if(bulkCallbackIdentity((void*)bulkCallback775_original)!=(uintptr_t)bulkCallback775_original || bulkCallbackIdentity((void*)bulkCallback775_linked)!=(uintptr_t)bulkCallback775_original)return 776;
 if(bulkCallbackIdentity((void*)bulkCallback776_original)!=(uintptr_t)bulkCallback776_original || bulkCallbackIdentity((void*)bulkCallback776_linked)!=(uintptr_t)bulkCallback776_original)return 777;
 if(bulkCallbackIdentity((void*)bulkCallback777_original)!=(uintptr_t)bulkCallback777_original || bulkCallbackIdentity((void*)bulkCallback777_linked)!=(uintptr_t)bulkCallback777_original)return 778;
 if(bulkCallbackIdentity((void*)bulkCallback778_original)!=(uintptr_t)bulkCallback778_original || bulkCallbackIdentity((void*)bulkCallback778_linked)!=(uintptr_t)bulkCallback778_original)return 779;
 if(bulkCallbackIdentity((void*)bulkCallback779_original)!=(uintptr_t)bulkCallback779_original || bulkCallbackIdentity((void*)bulkCallback779_linked)!=(uintptr_t)bulkCallback779_original)return 780;
 if(bulkCallbackIdentity((void*)bulkCallback780_original)!=(uintptr_t)bulkCallback780_original || bulkCallbackIdentity((void*)bulkCallback780_linked)!=(uintptr_t)bulkCallback780_original)return 781;
 if(bulkCallbackIdentity((void*)bulkCallback781_original)!=(uintptr_t)bulkCallback781_original || bulkCallbackIdentity((void*)bulkCallback781_linked)!=(uintptr_t)bulkCallback781_original)return 782;
 if(bulkCallbackIdentity((void*)bulkCallback782_original)!=(uintptr_t)bulkCallback782_original || bulkCallbackIdentity((void*)bulkCallback782_linked)!=(uintptr_t)bulkCallback782_original)return 783;
 if(bulkCallbackIdentity((void*)bulkCallback783_original)!=(uintptr_t)bulkCallback783_original || bulkCallbackIdentity((void*)bulkCallback783_linked)!=(uintptr_t)bulkCallback783_original)return 784;
 if(bulkCallbackIdentity((void*)bulkCallback784_original)!=(uintptr_t)bulkCallback784_original || bulkCallbackIdentity((void*)bulkCallback784_linked)!=(uintptr_t)bulkCallback784_original)return 785;
 if(bulkCallbackIdentity((void*)bulkCallback785_original)!=(uintptr_t)bulkCallback785_original || bulkCallbackIdentity((void*)bulkCallback785_linked)!=(uintptr_t)bulkCallback785_original)return 786;
 if(bulkCallbackIdentity((void*)bulkCallback786_original)!=(uintptr_t)bulkCallback786_original || bulkCallbackIdentity((void*)bulkCallback786_linked)!=(uintptr_t)bulkCallback786_original)return 787;
 if(bulkCallbackIdentity((void*)bulkCallback787_original)!=(uintptr_t)bulkCallback787_original || bulkCallbackIdentity((void*)bulkCallback787_linked)!=(uintptr_t)bulkCallback787_original)return 788;
 if(bulkCallbackIdentity((void*)bulkCallback788_original)!=(uintptr_t)bulkCallback788_original || bulkCallbackIdentity((void*)bulkCallback788_linked)!=(uintptr_t)bulkCallback788_original)return 789;
 if(bulkCallbackIdentity((void*)bulkCallback789_original)!=(uintptr_t)bulkCallback789_original || bulkCallbackIdentity((void*)bulkCallback789_linked)!=(uintptr_t)bulkCallback789_original)return 790;
 if(bulkCallbackIdentity((void*)bulkCallback790_original)!=(uintptr_t)bulkCallback790_original || bulkCallbackIdentity((void*)bulkCallback790_linked)!=(uintptr_t)bulkCallback790_original)return 791;
 if(bulkCallbackIdentity((void*)bulkCallback791_original)!=(uintptr_t)bulkCallback791_original || bulkCallbackIdentity((void*)bulkCallback791_linked)!=(uintptr_t)bulkCallback791_original)return 792;
 if(bulkCallbackIdentity((void*)bulkCallback792_original)!=(uintptr_t)bulkCallback792_original || bulkCallbackIdentity((void*)bulkCallback792_linked)!=(uintptr_t)bulkCallback792_original)return 793;
 if(bulkCallbackIdentity((void*)bulkCallback793_original)!=(uintptr_t)bulkCallback793_original || bulkCallbackIdentity((void*)bulkCallback793_linked)!=(uintptr_t)bulkCallback793_original)return 794;
 if(bulkCallbackIdentity((void*)bulkCallback794_original)!=(uintptr_t)bulkCallback794_original || bulkCallbackIdentity((void*)bulkCallback794_linked)!=(uintptr_t)bulkCallback794_original)return 795;
 if(bulkCallbackIdentity((void*)bulkCallback795_original)!=(uintptr_t)bulkCallback795_original || bulkCallbackIdentity((void*)bulkCallback795_linked)!=(uintptr_t)bulkCallback795_original)return 796;
 if(bulkCallbackIdentity((void*)bulkCallback796_original)!=(uintptr_t)bulkCallback796_original || bulkCallbackIdentity((void*)bulkCallback796_linked)!=(uintptr_t)bulkCallback796_original)return 797;
 if(bulkCallbackIdentity((void*)bulkCallback797_original)!=(uintptr_t)bulkCallback797_original || bulkCallbackIdentity((void*)bulkCallback797_linked)!=(uintptr_t)bulkCallback797_original)return 798;
 if(bulkCallbackIdentity((void*)bulkCallback798_original)!=(uintptr_t)bulkCallback798_original || bulkCallbackIdentity((void*)bulkCallback798_linked)!=(uintptr_t)bulkCallback798_original)return 799;
 if(bulkCallbackIdentity((void*)bulkCallback799_original)!=(uintptr_t)bulkCallback799_original || bulkCallbackIdentity((void*)bulkCallback799_linked)!=(uintptr_t)bulkCallback799_original)return 800;
 if(bulkCallbackIdentity((void*)bulkCallback800_original)!=(uintptr_t)bulkCallback800_original || bulkCallbackIdentity((void*)bulkCallback800_linked)!=(uintptr_t)bulkCallback800_original)return 801;
 if(bulkCallbackIdentity((void*)bulkCallback801_original)!=(uintptr_t)bulkCallback801_original || bulkCallbackIdentity((void*)bulkCallback801_linked)!=(uintptr_t)bulkCallback801_original)return 802;
 if(bulkCallbackIdentity((void*)bulkCallback802_original)!=(uintptr_t)bulkCallback802_original || bulkCallbackIdentity((void*)bulkCallback802_linked)!=(uintptr_t)bulkCallback802_original)return 803;
 if(bulkCallbackIdentity((void*)bulkCallback803_original)!=(uintptr_t)bulkCallback803_original || bulkCallbackIdentity((void*)bulkCallback803_linked)!=(uintptr_t)bulkCallback803_original)return 804;
 if(bulkCallbackIdentity((void*)bulkCallback804_original)!=(uintptr_t)bulkCallback804_original || bulkCallbackIdentity((void*)bulkCallback804_linked)!=(uintptr_t)bulkCallback804_original)return 805;
 if(bulkCallbackIdentity((void*)bulkCallback805_original)!=(uintptr_t)bulkCallback805_original || bulkCallbackIdentity((void*)bulkCallback805_linked)!=(uintptr_t)bulkCallback805_original)return 806;
 if(bulkCallbackIdentity((void*)bulkCallback806_original)!=(uintptr_t)bulkCallback806_original || bulkCallbackIdentity((void*)bulkCallback806_linked)!=(uintptr_t)bulkCallback806_original)return 807;
 if(bulkCallbackIdentity((void*)bulkCallback807_original)!=(uintptr_t)bulkCallback807_original || bulkCallbackIdentity((void*)bulkCallback807_linked)!=(uintptr_t)bulkCallback807_original)return 808;
 if(bulkCallbackIdentity((void*)bulkCallback808_original)!=(uintptr_t)bulkCallback808_original || bulkCallbackIdentity((void*)bulkCallback808_linked)!=(uintptr_t)bulkCallback808_original)return 809;
 if(bulkCallbackIdentity((void*)bulkCallback809_original)!=(uintptr_t)bulkCallback809_original || bulkCallbackIdentity((void*)bulkCallback809_linked)!=(uintptr_t)bulkCallback809_original)return 810;

 int unknown=0;
 if(bulkCallbackIdentity(&unknown)!=(uintptr_t)&unknown || bulkCallbackIdentity(0)!=0)return 9001;
 if(bulkCallbackIdentity((void*)0x12345)!=(uintptr_t)0x12345)return 9002;
 if(bulkCallbackIdentity((void*)bulkCallback0_original)==bulkCallbackIdentity((void*)bulkCallback1_original))return 9003;
 return 0;
}

