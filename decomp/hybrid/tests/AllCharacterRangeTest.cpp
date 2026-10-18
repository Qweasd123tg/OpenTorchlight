#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Character.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "GameGlobals.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldCharacterActiveRange,(CCharacter*,const Ogre::Vector3&),"_ZN10CCharacter20calculateActiveRangeERKN4Ogre7Vector3E")
extern "C" void newCharacterActiveRange(CCharacter*,const Ogre::Vector3&) __asm__("_ZN10CCharacter20calculateActiveRangeERKN4Ogre7Vector3E");
TL_FUNCTION(crange_editor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(crange_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(crange_globals,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(crange_effect,"_ZN10CCharacter30getEffectValueWithoutInventoryE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(crange_shadows,"_ZN9CBaseUnit15getCastsShadowsEv")
TL_FUNCTION(crange_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(crange_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
namespace {
struct Case{unsigned index;};
struct State{Case c;autotest::Capture*out;CCharacter*self,*master;CResourceManager*resources;CGameGlobals*globals;CMasterResourceManager*manager;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}
bool bit(unsigned n){return (hash(n)&7)==0;}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void ev(unsigned n){num(n);}
bool editor(CResourceManager*p){ev(1);num(p==active->resources);return bit(1);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){ev(2);num(p==active->self?1:2);num(t);return bit(p==active->self?2:3);}
CGameGlobals*globals(){ev(3);return active->globals;}
float effect(CCharacter*,EEFFECT_TYPE t,EDAMAGE_TYPES d){ev(4);num(t);num(d);const float values[]={0,-100,-50,25,100,500,std::numeric_limits<float>::quiet_NaN()};return values[hash(4)%7];}
bool shadows(CBaseUnit*){ev(5);return !bit(5);}
CMasterResourceManager*manager(){ev(6);return active->manager;}
int settings(CDynamicPropertyFile*p,unsigned n){ev(7);num(p!=NULL);num(n);return int(hash(7)%3)-1;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;
 s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.master=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));
 s.globals=static_cast<CGameGlobals*>(autotest::allocate(sizeof(CGameGlobals)));s.globals->m_fUnitShadowRange=10;s.globals->m_fUnitNearRange=24;s.globals->m_fIndoorUnitActiveRange=16;s.globals->m_fOutdoorUnitActiveRange=30;
 s.manager=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.manager->m_pSettings=static_cast<CSettings*>(autotest::allocate(sizeof(CSettings)));KSETTINGS_SHADOWS_ENABLED=55;
 CLevel*level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));CLevelTemplateData*data=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));
 s.self->m_pResourceManager=bit(9)?NULL:s.resources;s.resources->m_pLevel=bit(10)?NULL:level;level->m_pLevelTemplateData=bit(11)?NULL:data;data->m_bUnitLightFade=bit(12);data->m_sightRangeModifier=float(int(hash(13)%5)-2)*25;
 CSkill*skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));skill->m_animationID=bit(14)?-1:10;skill->m_interruptible=bit(15);s.self->m_activeSkill=bit(16)?NULL:skill;s.self->m_skillLooping=bit(17);s.self->m_skillTime=bit(18)?1:0;
 CSkillManager*sm=static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager)));new(&sm->m_UpdatingSkills)TArrayList<CSkill*>;if(bit(19))sm->m_UpdatingSkills.add(skill);s.self->m_pSkillManager=bit(20)?NULL:sm;
 s.self->m_pMaster=bit(21)?s.master:NULL;s.master->m_bInActiveRange=bit(22);s.self->m_alwaysActive=bit(23);s.self->m_eAIState=static_cast<EAIState>(hash(24)%16);s.self->m_aiThinkTier=99;
 s.self->m_bInActiveRange=bit(25);s.self->m_bInFadeRange=bit(26);s.self->m_castsDynamicShadow=bit(27);s.self->m_vPosition=Ogre::Vector3(7,3,-2);
 const float distances[]={0,9.99f,10,10.01f,14.99f,15,15.01f,19.99f,20,20.01f,24.99f,25,25.01f,29.99f,30,30.01f,100,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};const float heights[]={0,2.99f,3,3.01f,-3,-3.01f,std::numeric_limits<float>::quiet_NaN()};
 Ogre::Vector3 viewer=s.self->m_vPosition+Ogre::Vector3(distances[c.index%19],heights[hash(28)%7],bit(29)?5:0);
 autotest::invoke(out,ours?newCharacterActiveRange:oldCharacterActiveRange,s.self,viewer);
 num(s.self->m_bInActiveRange);num(s.self->m_bInFadeRange);num(s.self->m_castsDynamicShadow);num(s.self->m_aiThinkTier);sm->m_UpdatingSkills.~TArrayList();
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(all_character_active_range){detour::Set hooks;TL_REDIRECT(hooks,crange_editor,&editor);TL_REDIRECT(hooks,crange_isa,&isa);TL_REDIRECT(hooks,crange_globals,&globals);TL_REDIRECT(hooks,crange_effect,&effect);TL_REDIRECT(hooks,crange_shadows,&shadows);TL_REDIRECT(hooks,crange_master,&manager);TL_REDIRECT(hooks,crange_getInt,&settings);if(hooks.failed())return 1;
 autotest::Coverage coverage("all_character_active_range",0x824080);for(unsigned i=0;i<8192;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    character range seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);host->log("    word%u %08x/%08x\n",k,x,y);}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=8192||coverage.different||coverage.missing;}
