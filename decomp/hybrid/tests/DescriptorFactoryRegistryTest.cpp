#include <string>
#include <map>
#define private public
#include "DescriptorController.h"
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalControllerCtor,(CDescriptorController*),"_ZN21CDescriptorControllerC1Ev")
extern "C" void candidateControllerCtor(CDescriptorController*) __asm__("_ZN21CDescriptorControllerC1Ev");
TL_FUNCTION(registerDescriptor,"_ZN21CDescriptorController21addDescriptorFunctionEPKwPFPvvE")
TL_ORIGINAL(void*,registryOld0,(),"_ZL38Set_CWaypointActivatorDescriptorParam1v")
extern "C" void* registryNew0() __asm__("__tlhybrid_local_12__ZL38Set_CWaypointActivatorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld1,(),"_ZL34Set_CDungeonObjectDescriptorParam1v")
extern "C" void* registryNew1() __asm__("__tlhybrid_local_12__ZL34Set_CDungeonObjectDescriptorParam1v");
TL_ORIGINAL(void*,registryOld2,(),"_ZL31Set_CMoneyTakerDescriptorParam1v")
extern "C" void* registryNew2() __asm__("__tlhybrid_local_12__ZL31Set_CMoneyTakerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld3,(),"_ZL30Set_CCinematicDescriptorParam1v")
extern "C" void* registryNew3() __asm__("__tlhybrid_local_12__ZL30Set_CCinematicDescriptorParam1v");
TL_ORIGINAL(void*,registryOld4,(),"_ZL32Set_CDamageShapeDescriptorParam1v")
extern "C" void* registryNew4() __asm__("__tlhybrid_local_12__ZL32Set_CDamageShapeDescriptorParam1v");
TL_ORIGINAL(void*,registryOld5,(),"_ZL33Set_CSkipCutsceneDescriptorParam1v")
extern "C" void* registryNew5() __asm__("__tlhybrid_local_12__ZL33Set_CSkipCutsceneDescriptorParam1v");
TL_ORIGINAL(void*,registryOld6,(),"_ZL36Set_CAnimationPlayerDescriptorParam1v")
extern "C" void* registryNew6() __asm__("__tlhybrid_local_12__ZL36Set_CAnimationPlayerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld7,(),"_ZL29Set_CPathNodeDescriptorParam1v")
extern "C" void* registryNew7() __asm__("__tlhybrid_local_12__ZL29Set_CPathNodeDescriptorParam1v");
TL_ORIGINAL(void*,registryOld8,(),"_ZL35Set_CPathControllerDescriptorParam1v")
extern "C" void* registryNew8() __asm__("__tlhybrid_local_12__ZL35Set_CPathControllerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld9,(),"_ZL36Set_CSkillControllerDescriptorParam1v")
extern "C" void* registryNew9() __asm__("__tlhybrid_local_12__ZL36Set_CSkillControllerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld10,(),"_ZL36Set_CQuestControllerDescriptorParam1v")
extern "C" void* registryNew10() __asm__("__tlhybrid_local_12__ZL36Set_CQuestControllerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld11,(),"_ZL40Set_CGameStateControllerDescriptorParam1v")
extern "C" void* registryNew11() __asm__("__tlhybrid_local_12__ZL40Set_CGameStateControllerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld12,(),"_ZL32Set_CRandomGroupDescriptorParam1v")
extern "C" void* registryNew12() __asm__("__tlhybrid_local_12__ZL32Set_CRandomGroupDescriptorParam1v");
TL_ORIGINAL(void*,registryOld13,(),"_ZL28Set_CMissileDescriptorParam1v")
extern "C" void* registryNew13() __asm__("__tlhybrid_local_12__ZL28Set_CMissileDescriptorParam1v");
TL_ORIGINAL(void*,registryOld14,(),"_ZL32Set_CMusicObjectDescriptorParam1v")
extern "C" void* registryNew14() __asm__("__tlhybrid_local_12__ZL32Set_CMusicObjectDescriptorParam1v");
TL_ORIGINAL(void*,registryOld15,(),"_ZL32Set_CSoundObjectDescriptorParam1v")
extern "C" void* registryNew15() __asm__("__tlhybrid_local_12__ZL32Set_CSoundObjectDescriptorParam1v");
TL_ORIGINAL(void*,registryOld16,(),"_ZL26Set_CLightDescriptorParam1v")
extern "C" void* registryNew16() __asm__("__tlhybrid_local_12__ZL26Set_CLightDescriptorParam1v");
TL_ORIGINAL(void*,registryOld17,(),"_ZL30Set_CRoomPieceDescriptorParam1v")
extern "C" void* registryNew17() __asm__("__tlhybrid_local_12__ZL30Set_CRoomPieceDescriptorParam1v");
TL_ORIGINAL(void*,registryOld18,(),"_ZL33Set_CGenericModelDescriptorParam1v")
extern "C" void* registryNew18() __asm__("__tlhybrid_local_12__ZL33Set_CGenericModelDescriptorParam1v");
TL_ORIGINAL(void*,registryOld19,(),"_ZL52Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2v")
extern "C" void* registryNew19() __asm__("__tlhybrid_local_12__ZL52Set_CLayoutDescriptorKLAYOUT_TYPE_UNIT_TRIGGERParam2v");
TL_ORIGINAL(void*,registryOld20,(),"_ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2v")
extern "C" void* registryNew20() __asm__("__tlhybrid_local_12__ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_TIMELINEParam2v");
TL_ORIGINAL(void*,registryOld21,(),"_ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2v")
extern "C" void* registryNew21() __asm__("__tlhybrid_local_12__ZL48Set_CLayoutDescriptorKLAYOUT_TYPE_PARTICLEParam2v");
TL_ORIGINAL(void*,registryOld22,(),"_ZL46Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2v")
extern "C" void* registryNew22() __asm__("__tlhybrid_local_12__ZL46Set_CLayoutDescriptorKLAYOUT_TYPE_NORMALParam2v");
TL_ORIGINAL(void*,registryOld23,(),"_ZL32Set_CUnitSpawnerDescriptorParam1v")
extern "C" void* registryNew23() __asm__("__tlhybrid_local_12__ZL32Set_CUnitSpawnerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld24,(),"_ZL32Set_CUnitTriggerDescriptorParam1v")
extern "C" void* registryNew24() __asm__("__tlhybrid_local_12__ZL32Set_CUnitTriggerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld25,(),"_ZL25Set_CItemDescriptorParam1v")
extern "C" void* registryNew25() __asm__("__tlhybrid_local_12__ZL25Set_CItemDescriptorParam1v");
TL_ORIGINAL(void*,registryOld26,(),"_ZL28Set_CMonsterDescriptorParam1v")
extern "C" void* registryNew26() __asm__("__tlhybrid_local_12__ZL28Set_CMonsterDescriptorParam1v");
TL_ORIGINAL(void*,registryOld27,(),"_ZL37Set_CCameraControllerDescriptorParam1v")
extern "C" void* registryNew27() __asm__("__tlhybrid_local_12__ZL37Set_CCameraControllerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld28,(),"_ZL37Set_CPuzzleRandomizerDescriptorParam1v")
extern "C" void* registryNew28() __asm__("__tlhybrid_local_12__ZL37Set_CPuzzleRandomizerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld29,(),"_ZL33Set_CPropertyNodeDescriptorParam1v")
extern "C" void* registryNew29() __asm__("__tlhybrid_local_12__ZL33Set_CPropertyNodeDescriptorParam1v");
TL_ORIGINAL(void*,registryOld30,(),"_ZL32Set_CCameraShakeDescriptorParam1v")
extern "C" void* registryNew30() __asm__("__tlhybrid_local_12__ZL32Set_CCameraShakeDescriptorParam1v");
TL_ORIGINAL(void*,registryOld31,(),"_ZL38Set_COutputIncrementorDescriptorParam1v")
extern "C" void* registryNew31() __asm__("__tlhybrid_local_12__ZL38Set_COutputIncrementorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld32,(),"_ZL31Set_CLogicTimerDescriptorParam1v")
extern "C" void* registryNew32() __asm__("__tlhybrid_local_12__ZL31Set_CLogicTimerDescriptorParam1v");
TL_ORIGINAL(void*,registryOld33,(),"_ZL29Set_CTeleportDescriptorParam1v")
extern "C" void* registryNew33() __asm__("__tlhybrid_local_12__ZL29Set_CTeleportDescriptorParam1v");
TL_ORIGINAL(void*,registryOld34,(),"_ZL27Set_CWarperDescriptorParam1v")
extern "C" void* registryNew34() __asm__("__tlhybrid_local_12__ZL27Set_CWarperDescriptorParam1v");
TL_ORIGINAL(void*,registryOld35,(),"_ZL33Set_CRandomChoiceDescriptorParam1v")
extern "C" void* registryNew35() __asm__("__tlhybrid_local_12__ZL33Set_CRandomChoiceDescriptorParam1v");
TL_ORIGINAL(void*,registryOld36,(),"_ZL28Set_CCounterDescriptorParam1v")
extern "C" void* registryNew36() __asm__("__tlhybrid_local_12__ZL28Set_CCounterDescriptorParam1v");
TL_ORIGINAL(void*,registryOld37,(),"_ZL31Set_CTriggerBoxDescriptorParam1v")
extern "C" void* registryNew37() __asm__("__tlhybrid_local_12__ZL31Set_CTriggerBoxDescriptorParam1v");
TL_ORIGINAL(void*,registryOld38,(),"_ZL34Set_CTriggerSphereDescriptorParam1v")
extern "C" void* registryNew38() __asm__("__tlhybrid_local_12__ZL34Set_CTriggerSphereDescriptorParam1v");
TL_ORIGINAL(void*,registryOld39,(),"_ZL31Set_CLogicGroupDescriptorParam1v")
extern "C" void* registryNew39() __asm__("__tlhybrid_local_12__ZL31Set_CLogicGroupDescriptorParam1v");
TL_ORIGINAL(void*,registryOld40,(),"_ZL29Set_CTimelineDescriptorParam1v")
extern "C" void* registryNew40() __asm__("__tlhybrid_local_12__ZL29Set_CTimelineDescriptorParam1v");
TL_ORIGINAL(void*,registryOld41,(),"_ZL35Set_CSphereColliderDescriptorParam1v")
extern "C" void* registryNew41() __asm__("__tlhybrid_local_12__ZL35Set_CSphereColliderDescriptorParam1v");
TL_ORIGINAL(void*,registryOld42,(),"_ZL34Set_CPlaneColliderDescriptorParam1v")
extern "C" void* registryNew42() __asm__("__tlhybrid_local_12__ZL34Set_CPlaneColliderDescriptorParam1v");
TL_ORIGINAL(void*,registryOld43,(),"_ZL32Set_CBoxColliderDescriptorParam1v")
extern "C" void* registryNew43() __asm__("__tlhybrid_local_12__ZL32Set_CBoxColliderDescriptorParam1v");
TL_ORIGINAL(void*,registryOld44,(),"_ZL34Set_CColorAffectorDescriptorParam1v")
extern "C" void* registryNew44() __asm__("__tlhybrid_local_12__ZL34Set_CColorAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld45,(),"_ZL35Set_CTextureAnimateDescriptorParam1v")
extern "C" void* registryNew45() __asm__("__tlhybrid_local_12__ZL35Set_CTextureAnimateDescriptorParam1v");
TL_ORIGINAL(void*,registryOld46,(),"_ZL34Set_CTextureRotateDescriptorParam1v")
extern "C" void* registryNew46() __asm__("__tlhybrid_local_12__ZL34Set_CTextureRotateDescriptorParam1v");
TL_ORIGINAL(void*,registryOld47,(),"_ZL35Set_CGeometryRotateDescriptorParam1v")
extern "C" void* registryNew47() __asm__("__tlhybrid_local_12__ZL35Set_CGeometryRotateDescriptorParam1v");
TL_ORIGINAL(void*,registryOld48,(),"_ZL32Set_CJetAffectorDescriptorParam1v")
extern "C" void* registryNew48() __asm__("__tlhybrid_local_12__ZL32Set_CJetAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld49,(),"_ZL34Set_CScaleAffectorDescriptorParam1v")
extern "C" void* registryNew49() __asm__("__tlhybrid_local_12__ZL34Set_CScaleAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld50,(),"_ZL36Set_CGravityAffectorDescriptorParam1v")
extern "C" void* registryNew50() __asm__("__tlhybrid_local_12__ZL36Set_CGravityAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld51,(),"_ZL35Set_CVortexAffectorDescriptorParam1v")
extern "C" void* registryNew51() __asm__("__tlhybrid_local_12__ZL35Set_CVortexAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld52,(),"_ZL38Set_CSineForceAffectorDescriptorParam1v")
extern "C" void* registryNew52() __asm__("__tlhybrid_local_12__ZL38Set_CSineForceAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld53,(),"_ZL40Set_CLinearForceAffectorDescriptorParam1v")
extern "C" void* registryNew53() __asm__("__tlhybrid_local_12__ZL40Set_CLinearForceAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld54,(),"_ZL33Set_CLineAffectorDescriptorParam1v")
extern "C" void* registryNew54() __asm__("__tlhybrid_local_12__ZL33Set_CLineAffectorDescriptorParam1v");
TL_ORIGINAL(void*,registryOld55,(),"_ZL26Set_CAlignDescriptorParam1v")
extern "C" void* registryNew55() __asm__("__tlhybrid_local_12__ZL26Set_CAlignDescriptorParam1v");
TL_ORIGINAL(void*,registryOld56,(),"_ZL43Set_CParticleEmitterWrapperDescriptorParam1v")
extern "C" void* registryNew56() __asm__("__tlhybrid_local_12__ZL43Set_CParticleEmitterWrapperDescriptorParam1v");
TL_ORIGINAL(void*,registryOld57,(),"_ZL40Set_CParticleTechWrapperDescriptorParam1v")
extern "C" void* registryNew57() __asm__("__tlhybrid_local_12__ZL40Set_CParticleTechWrapperDescriptorParam1v");
TL_ORIGINAL(void*,registryOld58,(),"_ZL33Set_CEditorButtonDescriptorParam1v")
extern "C" void* registryNew58() __asm__("__tlhybrid_local_12__ZL33Set_CEditorButtonDescriptorParam1v");
TL_ORIGINAL(void*,registryOld59,(),"_ZL32Set_CEditorImageDescriptorParam1v")
extern "C" void* registryNew59() __asm__("__tlhybrid_local_12__ZL32Set_CEditorImageDescriptorParam1v");
namespace {
typedef void*(*Factory)();
struct Entry {const wchar_t* name;Factory original,candidate;};
const Entry expected[] = {
 {L"Group",registryOld12,registryNew12},
 {L"Monster",registryOld26,registryNew26},
 {L"Item",registryOld25,registryNew25},
 {L"Unit Trigger",registryOld24,registryNew24},
 {L"Unit Spawner",registryOld23,registryNew23},
 {L"Layout Link",registryOld22,registryNew22},
 {L"Layout Link Particle",registryOld21,registryNew21},
 {L"Layout Link Timeline",registryOld20,registryNew20},
 {L"Layout Link Trigger",registryOld19,registryNew19},
 {L"Generic Model",registryOld18,registryNew18},
 {L"Room Piece",registryOld17,registryNew17},
 {L"Light",registryOld16,registryNew16},
 {L"Sound",registryOld15,registryNew15},
 {L"Music",registryOld14,registryNew14},
 {L"Missile",registryOld13,registryNew13},
 {L"Image",registryOld59,registryNew59},
 {L"Button",registryOld58,registryNew58},
 {L"Particle",registryOld57,registryNew57},
 {L"Emitter",registryOld56,registryNew56},
 {L"Align",registryOld55,registryNew55},
 {L"Line",registryOld54,registryNew54},
 {L"Linear Force",registryOld53,registryNew53},
 {L"Sine Force",registryOld52,registryNew52},
 {L"Vortext",registryOld51,registryNew51},
 {L"Gravity Well",registryOld50,registryNew50},
 {L"Scale",registryOld49,registryNew49},
 {L"Jet",registryOld48,registryNew48},
 {L"Geometry Rotator",registryOld47,registryNew47},
 {L"Texture Rotate",registryOld46,registryNew46},
 {L"Texture Animation",registryOld45,registryNew45},
 {L"Color",registryOld44,registryNew44},
 {L"Box Collision",registryOld43,registryNew43},
 {L"Plane Collision",registryOld42,registryNew42},
 {L"Sphere Collision",registryOld41,registryNew41},
 {L"Timeline",registryOld40,registryNew40},
 {L"Logic Group",registryOld39,registryNew39},
 {L"Player Sphere Trigger",registryOld38,registryNew38},
 {L"Player Box Trigger",registryOld37,registryNew37},
 {L"Counter",registryOld36,registryNew36},
 {L"Random Choice",registryOld35,registryNew35},
 {L"Warper",registryOld34,registryNew34},
 {L"Teleport",registryOld33,registryNew33},
 {L"Timer",registryOld32,registryNew32},
 {L"Output Incrementor",registryOld31,registryNew31},
 {L"Camera Shake",registryOld30,registryNew30},
 {L"Property Node",registryOld29,registryNew29},
 {L"Puzzle Input",registryOld28,registryNew28},
 {L"Camera Controller",registryOld27,registryNew27},
 {L"Game State Controller",registryOld11,registryNew11},
 {L"Quest Controller",registryOld10,registryNew10},
 {L"Skill Controller",registryOld9,registryNew9},
 {L"Pathing",registryOld8,registryNew8},
 {L"Path Node",registryOld7,registryNew7},
 {L"Animation Controller",registryOld6,registryNew6},
 {L"Skip Cutscene",registryOld5,registryNew5},
 {L"Damage Shape",registryOld4,registryNew4},
 {L"Cinematic",registryOld3,registryNew3},
 {L"Money Taker",registryOld2,registryNew2},
 {L"Dungeon Object",registryOld1,registryNew1},
 {L"Waypoint Activator",registryOld0,registryNew0},
};
struct Case {unsigned pattern,mutation;};
const Case* current;autotest::Capture* capture;CDescriptorController* self;unsigned calls;
typedef std::map<std::wstring,TArrayList<CDescriptorProp*>*> Cache;
void n(unsigned value) {capture->add(&value,sizeof(value));}
void need(bool value) {if(!value)capture->issue=autotest::Capture::InvalidReport;}
void registration(const wchar_t* name,Factory factory)
{
    need(calls<60&&name);if(calls>=60||!name)return;
    const Entry& entry=expected[calls];capture->addText(std::wstring(name));
    need(std::wstring(name)==entry.name);need(factory==entry.original||factory==entry.candidate);
    n(calls);n(factory==entry.original||factory==entry.candidate);
    if(current->mutation&&calls==(current->mutation==1?0u:current->mutation==2?30u:59u)) {
        self->m_Properties[L"cache retained across registration"]=0;
        self->m_DefaultProperties[L"defaults retained across registration"]=0;
    }
    ++calls;
}
void side(void* p,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(p);capture=&out;calls=0;uint64_t storage[16];
    static const unsigned char fill[]={0,1,0x55,0xaa,0xfe,0xff};std::memset(storage,fill[current->pattern],sizeof(storage));self=reinterpret_cast<CDescriptorController*>(storage+2);
    detour::Set d;TL_REDIRECT(d,registerDescriptor,&registration);if(d.failed()){need(false);return;}
    autotest::invoke(out,ours?&candidateControllerCtor:&originalControllerCtor,self);
    need(calls==60);n(calls);n(self->m_Properties.size());n(self->m_DefaultProperties.size());
    need(self->m_Properties.size()==(current->mutation?1u:0u));need(self->m_DefaultProperties.size()==(current->mutation?1u:0u));
    for(Cache::const_iterator i=self->m_Properties.begin();i!=self->m_Properties.end();++i){capture->addText(i->first);need(i->second==0);}
    for(Cache::const_iterator i=self->m_DefaultProperties.begin();i!=self->m_DefaultProperties.end();++i){capture->addText(i->first);need(i->second==0);}
    unsigned char* raw=reinterpret_cast<unsigned char*>(storage);for(unsigned i=0;i<16;++i)need(raw[i]==fill[current->pattern]);for(unsigned i=112;i<sizeof(storage);++i)need(raw[i]==fill[current->pattern]);
    self->m_DefaultProperties.~Cache();self->m_Properties.~Cache();
}
void before(void* p,autotest::Capture& c){side(p,c,false);}void after(void* p,autotest::Capture& c){side(p,c,true);}
}
TL_TEST(descriptor_controller_registration)
{
    autotest::Coverage coverage("descriptor_controller_registration",reinterpret_cast<uintptr_t>(&originalControllerCtor));
    for(unsigned pattern=0;pattern<6;++pattern)for(unsigned mutation=0;mutation<4;++mutation){Case c={pattern,mutation};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    controller registration %u/%u status %d/%d issue %u/%u\n",pattern,mutation,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed==24?0:1;
}
