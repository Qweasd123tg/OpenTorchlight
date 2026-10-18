#include <string>
#include <vector>
#include <map>
#include <new>
#include <stdint.h>
#define private public
#define protected public
#include "Effect.h"
#include "Character.h"
#include "Item.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Affix.h"
#include "Skill.h"
#include "ResourceManager.h"
#include "Graph.h"
#include "GraphManager.h"
#include "ParticlePreloader.h"
#include "Particle.h"
#include "StringTranslate.h"
#include "SkillParser.h"
#include "UnitResourceList.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "UnitThemes.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
#include "StringUtilities.h"
TL_ORIGINAL(float, oldEffectCalc, (CEffect*,CEffect::ECALCULATETYPES), "_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
extern "C" float newEffectCalc(CEffect*,CEffect::ECALCULATETYPES) __asm__("_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE");
TL_ORIGINAL(void, oldEffectOwner, (CEffect*,CBaseUnit*,bool), "_ZN7CEffect8setOwnerEP9CBaseUnitb")
extern "C" void newEffectOwner(CEffect*,CBaseUnit*,bool) __asm__("_ZN7CEffect8setOwnerEP9CBaseUnitb");
TL_ORIGINAL(void, oldEffectSkill, (CEffect*,CSkill*), "_ZN7CEffect13setSkillOwnerEP6CSkill")
extern "C" void newEffectSkill(CEffect*,CSkill*) __asm__("_ZN7CEffect13setSkillOwnerEP6CSkill");
TL_ORIGINAL(void, oldEffectAffix, (CEffect*,CAffix*), "_ZN7CEffect13setAffixOwnerEP6CAffix")
extern "C" void newEffectAffix(CEffect*,CAffix*) __asm__("_ZN7CEffect13setAffixOwnerEP6CAffix");
TL_ORIGINAL(void, oldEffectClone, (CEffect*,const CEffect*), "_ZN7CEffect5cloneEPKS_")
extern "C" void newEffectClone(CEffect*,const CEffect*) __asm__("_ZN7CEffect5cloneEPKS_");
TL_ORIGINAL(void, oldEffectCtor, (CEffect*,EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool), "_ZN7CEffectC1E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb")
extern "C" void newEffectCtor(CEffect*,EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool) __asm__("_ZN7CEffectC1E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb");
TL_ORIGINAL(void, oldEffectCopy, (CEffect*,const CEffect*), "_ZN7CEffectC1EPKS_")
extern "C" void newEffectCopy(CEffect*,const CEffect*) __asm__("_ZN7CEffectC1EPKS_");
TL_ORIGINAL(CEffectDisplayValues, oldEffectVisual, (CEffect*,unsigned int,bool), "_ZN7CEffect25getVisualCalculatedValuesEjb")
extern "C" CEffectDisplayValues newEffectVisual(CEffect*,unsigned int,bool) __asm__("_ZN7CEffect25getVisualCalculatedValuesEjb");
TL_ORIGINAL(void, oldEffectGraphs, (CEffect*,std::wstring), "_ZN7CEffect9setGraphsESbIwSt11char_traitsIwESaIwEE")
extern "C" void newEffectGraphs(CEffect*,std::wstring) __asm__("_ZN7CEffect9setGraphsESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, oldEffectFX, (CEffect*,const std::wstring&), "_ZN7CEffect5setFXERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void newEffectFX(CEffect*,const std::wstring&) __asm__("_ZN7CEffect5setFXERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, oldEffectDtor, (CEffect*), "_ZN7CEffectD1Ev")
extern "C" void newEffectDtor(CEffect*) __asm__("_ZN7CEffectD1Ev");
TL_FUNCTION(effectRng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(effectGraph,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(effectGraphSingleton,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(effectGetGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(effectParticleSingleton,"_ZN18CParticlePreloader12getSingletonEv")
TL_FUNCTION(effectPreload,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(std::wstring, oldEffectDisplay, (CEffect*,CEffectDisplayValues&), "_ZN7CEffect15getDisplayStatsER20CEffectDisplayValues")
extern "C" std::wstring newEffectDisplay(CEffect*,CEffectDisplayValues&) __asm__("_ZN7CEffect15getDisplayStatsER20CEffectDisplayValues");
TL_ORIGINAL(std::wstring, oldEffectLevelDisplay, (CEffect*,unsigned int,bool), "_ZN7CEffect15getDisplayStatsEjb")
extern "C" std::wstring newEffectLevelDisplay(CEffect*,unsigned int,bool) __asm__("_ZN7CEffect15getDisplayStatsEjb");
TL_ORIGINAL(std::wstring, oldEffectDamageName, (CEffect*,EDAMAGE_TYPES), "_ZN7CEffect26getDamageTypeDisplayStringE13EDAMAGE_TYPES")
extern "C" std::wstring newEffectDamageName(CEffect*,EDAMAGE_TYPES) __asm__("_ZN7CEffect26getDamageTypeDisplayStringE13EDAMAGE_TYPES");
TL_FUNCTION(effectTranslateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(effectTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(effectSkillParserSingleton,"_ZN12CSkillParser12getSingletonEv")
TL_FUNCTION(effectSkillData,"_ZN12CSkillParser12getSkillDataERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(effectMasterResources,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(effectUnitData,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_ORIGINAL(void, oldEffectDataCtor, (CEffect*,CDataGroup*,CBaseUnit*), "_ZN7CEffectC1EP10CDataGroupP9CBaseUnit")
extern "C" void newEffectDataCtor(CEffect*,CDataGroup*,CBaseUnit*) __asm__("_ZN7CEffectC1EP10CDataGroupP9CBaseUnit");
TL_FUNCTION(effectThemesSingleton,"_ZN11CUnitThemes12getSingletonEv")
namespace {
struct Case { unsigned mode,index; };
struct State {
    autotest::Capture* out;Case c; bool armed;
    CEffect *effect,*source; CCharacter* character; CItem* item; CEquipment* equipment; CSkill* skill;
    CResourceManager *resourceA,*resourceB;CAffix* affix; CGraph* graph; CDataGroup* data; CUnitThemes* themes; CUnitTheme* theme;
};
State* active;
void num(unsigned int n){if(active->armed)active->out->add(&n,4);}
void fp(float n){if(active->armed)active->out->add(&n,4);}
void text(const std::wstring& v){num(v.size());if(active->armed)active->out->add(v.data(),v.size()*sizeof(wchar_t));}
unsigned id(const void* p){if(!p)return 0;if(p==active->character)return 1;if(p==active->item)return 2;if(p==active->equipment)return 3;if(p==active->skill)return 4;if(p==active->resourceA)return 5;if(p==active->resourceB)return 6;if(p==active->affix)return 7;if(p==active->graph)return 8;if(p==active->effect)return 9;if(p==active->source)return 10;if(p==active->theme)return 11;return 99;}
float rng(float lo,float hi){num(100);fp(lo);fp(hi);return active->c.index%3==0?lo:active->c.index%3==1?hi:(lo+hi)*0.5f;}
float graph(const CGraph* p,float level,unsigned int line){num(101);num(id(p));fp(level);num(line);return (active->c.index&1)?-17.5f:31.25f;}
CGraphManager* graphSingleton(){num(102);return reinterpret_cast<CGraphManager*>(active->resourceB);}
CGraph* getGraph(CGraphManager*,const std::wstring& name){num(103);text(name);return (active->c.index&4)?NULL:active->graph;}
CParticlePreloader* particleSingleton(){num(104);return reinterpret_cast<CParticlePreloader*>(active->resourceA);}
void preload(CParticlePreloader*,std::wstring name){num(105);text(name);}
CStringTranslate* translateSingleton(){num(106);return reinterpret_cast<CStringTranslate*>(active->resourceA);}
std::wstring translate(CStringTranslate*,const wchar_t* name){num(107);text(name);return std::wstring(L"translated-")+name;}
CSkillParser* parserSingleton(){num(108);return reinterpret_cast<CSkillParser*>(active->resourceA);}
CDataGroup* skillData(CSkillParser*,const std::wstring& name){num(109);text(name);return active->c.index&32?NULL:active->data;}
CUnitResourceList* masterResources(CResourceManager* resources){num(110);num(id(resources));return reinterpret_cast<CUnitResourceList*>(active->resourceB);}
CDataGroup* unitData(CUnitResourceList*,const std::wstring& type,const std::wstring& name){num(111);text(type);text(name);return active->c.index&32?NULL:active->data;}
CUnitThemes* themesSingleton(){num(113);return active->themes;}
void particleDrop(CParticle*){num(112);num(active->effect->m_pAffixOwner==NULL);}
void base(CRunicCore* p,uintptr_t vtable){new(p) CRunicCore();*reinterpret_cast<void***>(p)=reinterpret_cast<void**>(vtable);}
void snapshot(CEffect* e){
    num(e->m_iLevel);num(e->m_eDamageType);fp(e->m_fRemainingDuration);num(e->m_eType);num(e->m_activation);fp(e->m_fValue24);num(e->m_bFlag28);num(e->m_value2C);
    num(e->m_flag30);num(e->m_flag31);num(e->m_padding32);num(e->m_flag33);num(e->m_bDead);num(e->m_showStats);num(e->m_useOwnerLevel);num(e->m_flag37);
    fp(e->m_value38);num(e->m_value3C);num(e->m_value40);num(e->m_value44);
    num(id(e->m_Owner.getObject()));num(e->m_Owner.m_nIndex);num(id(e->m_sourceCharacter.getObject()));num(e->m_sourceCharacter.m_nIndex);num(id(e->m_pSkillOwner.getObject()));num(e->m_pSkillOwner.m_nIndex);
    text(e->m_name78);text(e->m_sName);text(e->m_name88);text(e->m_name90);text(e->m_particleName);
    fp(e->m_direction.x);fp(e->m_direction.y);fp(e->m_direction.z);num(id(e->m_pAffixOwner));fp(e->m_fValueC0);
    for(unsigned i=0;i<4;++i){fp(e->m_values[i]);num(id(e->m_graphs[i]));}
    num(e->m_statModifiers.m_nCount);num(e->m_statModifiers.m_nCapacity);num(e->m_statModifiers.m_nGrowBy);
    num(e->m_statModifierValues.m_nCount);num(e->m_statModifierValues.m_nCapacity);num(e->m_statModifierValues.m_nGrowBy);
    for(unsigned i=0;i<e->m_statModifiers.size();++i){num(e->m_statModifiers[i]);fp(e->m_statModifierValues[i]);}
    num(id(e->m_resources));num(id(e->m_pUnitTheme));
}
void configure(CEffect* e,unsigned seed){
    static const float samples[]={-11.5f,0,7.25f,25,100,-3.125f};
    static const unsigned levels[]={0,1,17,1000,1001,static_cast<unsigned>(-1)};
    e->m_iLevel=levels[seed%6];e->m_eType=static_cast<EEFFECT_TYPE>((seed*17)%145);e->m_activation=static_cast<EEFFECT_ACTIVATION>(seed%3);
    e->m_fValue24=seed%4==0?-900.0f:seed%4==1?-1000.0f:seed%4==2?12.5f:0;
    e->m_fRemainingDuration=4.25f;e->m_fValueC0=-14.0f;e->m_eDamageType=static_cast<EDAMAGE_TYPES>(seed%8);
    e->m_values[0]=samples[seed%6];e->m_values[1]=samples[(seed/3)%6];e->m_values[2]=3.5f;e->m_values[3]=8.75f;
    e->m_graphs[0]=seed&1?active->graph:NULL;e->m_graphs[1]=active->graph;e->m_flag37=seed&2;e->m_useOwnerLevel=seed&4;e->m_showStats=!(seed&8);
    e->m_bFlag28=seed&16;e->m_flag30=seed&32;e->m_flag31=seed&64;e->m_flag33=seed&128;e->m_padding32=3;
    e->m_name78=L"first";e->m_sName=L"named";e->m_name88=L"third";e->m_name90=L"last";e->m_particleName=L"particles/ember";
    e->m_value2C=-7;e->m_value3C=48;e->m_value40=15;e->m_value44=9;e->m_value38=0.625f;e->m_direction=Ogre::Vector3(0.5f,-1,2);
    if(seed&8)e->m_Owner.setObject(active->item);
    if(seed&16)e->m_Owner.setObject(active->character);
    if(seed&32)e->m_Owner.setObject(active->equipment);
    if(seed&64)e->m_sourceCharacter.setObject(active->character);
    if(seed&128)e->m_pSkillOwner.setObject(active->skill);
    unsigned count=(seed/5)%8;
    for(unsigned i=0;i<count;++i){e->m_statModifiers.add(static_cast<EEFFECT_STAT_MODIFIERS>((seed+i)%8));e->m_statModifierValues.add((i&1)?-0.125f:0.375f);}
}
void side(Case& c,bool ours,autotest::Capture& out){
    autotest::g_arenaUsed=0;State s;active=&s;s.out=&out;s.c=c;s.armed=false;
    new(reinterpret_cast<void*>(0x1476068)) std::wstring;
    s.resourceA=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.resourceB=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));
    s.resourceA->m_pLevel=c.index&1?reinterpret_cast<CLevel*>(s.resourceB):NULL;
    s.character=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));base(s.character,0xfcdd70);
    s.character->m_iUnitLevel=c.index%5==0?1001:c.index%5==1?static_cast<unsigned>(-1):c.index%5==2?0:23;
    s.character->m_pResourceManager=s.resourceA;s.character->m_iMeleeStat=47;s.character->m_rangedStat=83;s.character->m_defenseStat=19;s.character->m_magicStat=-7;
    s.item=static_cast<CItem*>(autotest::allocate(sizeof(CItem)));base(s.item,0xfd1ad0);s.item->m_pResourceManager=s.resourceB;s.item->m_iUnitLevel=59;
    s.equipment=static_cast<CEquipment*>(autotest::allocate(sizeof(CEquipment)));base(s.equipment,0xfd0cf0);
    CInventory* inv=static_cast<CInventory*>(autotest::allocate(sizeof(CInventory)));inv->m_pPositionableObject=c.index&2?s.character:NULL;s.equipment->m_pInventory=inv;
    s.skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));base(s.skill,0xff4c50);s.skill->m_pOwner=c.index&2?static_cast<CBaseUnit*>(s.character):static_cast<CBaseUnit*>(s.item);s.skill->m_resources=s.resourceB;
    s.affix=static_cast<CAffix*>(autotest::allocate(sizeof(CAffix)));s.affix->m_uiLevel=c.index%5==0?1001:c.index%5==1?static_cast<unsigned>(-1):19;
    s.graph=static_cast<CGraph*>(autotest::allocate(sizeof(CGraph)));
    s.effect=static_cast<CEffect*>(autotest::allocate(sizeof(CEffect)));s.source=static_cast<CEffect*>(autotest::allocate(sizeof(CEffect)));
    oldEffectCtor(s.source,static_cast<EEFFECT_TYPE>(7),true,EFFECT_ACTIVATION_DYNAMIC,1.0f,2.0f,3.0f,false);configure(s.source,c.index);
    if(c.mode!=5&&c.mode!=6&&c.mode!=14){oldEffectCtor(s.effect,static_cast<EEFFECT_TYPE>(6),false,EFFECT_ACTIVATION_DYNAMIC,0,0,1,false);configure(s.effect,c.index+17);}
    if(c.mode>=10){
        uintptr_t emptyAddresses[]={0x14dd9c8,0x14dd9d8,0x14dda88,0x152f138};
        for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(emptyAddresses[i])) std::wstring;
        std::wstring empty;s.data=new CDataGroup(L"UNIT",NULL,8,8,new TRepository<std::wstring>(empty));
        if(!(c.index&64))s.data->AddDataValue(L"DISPLAYNAME",L"Visible Name",false);
    }
    if(c.mode==10||c.mode==11){
        s.effect->m_eType=static_cast<EEFFECT_TYPE>(c.index%145);
        unsigned variant=c.index/145;
        s.effect->m_showStats=!(variant&8);s.effect->m_fValue24=variant%4==0?-900.0f:variant%4==1?-1000.0f:1.25f;
        s.effect->m_resources=s.resourceA;s.effect->m_eDamageType=static_cast<EDAMAGE_TYPES>((c.index/7)%9);
        const wchar_t* message=variant&4?L"":L"[VALUE] /[VALUE1]/[MINVAL]/[VALUE2]/[MAXVAL] \\n [NAME] [VALUE3AND4] [DMGTYPE] [DURATION]";
        new(&gEFFECT_TYPE_DESCRIPTIONS_GOOD[s.effect->m_eType]) std::wstring(std::wstring(L"GOOD ")+message);
        new(&gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[s.effect->m_eType]) std::wstring(std::wstring(L"GOOD_OT ")+message);
        new(&gEFFECT_TYPE_DESCRIPTIONS_BAD[s.effect->m_eType]) std::wstring(std::wstring(L"BAD ")+message);
        new(&gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[s.effect->m_eType]) std::wstring(std::wstring(L"BAD_OT ")+message);
        gEFFECT_TYPE_MAX_VALUES[s.effect->m_eType]=(variant&1)?-100:100;gEFFECT_TYPE_BONUS[s.effect->m_eType]=variant&2?2:0;
    }
    if(c.mode==14){
        unsigned variant=c.index/145;unsigned type=c.index%145;
        s.themes=static_cast<CUnitThemes*>(autotest::allocate(sizeof(CUnitThemes)));new(&s.themes->m_Themes) TArrayList<CUnitTheme*>;
        s.theme=static_cast<CUnitTheme*>(autotest::allocate(sizeof(CUnitTheme)));new(&s.theme->m_sName) std::wstring(L"EMBER");s.themes->m_Themes.add(s.theme);
        for(unsigned i=0;i<145;++i){new(&gEFFECT_TYPE_NAMES[i]) std::wstring(L"EFFECT"+STRINGS::GetValueAsWString(i));for(unsigned j=0;j<4;++j){new(&gEFFECT_TYPE_PROPERTY_TAGS[i][j]) std::wstring(L"TAG"+STRINGS::GetValueAsWString(j));new(&gEFFECT_TYPE_GRAPHS[i][j]) std::wstring((variant&2)?L"DEFAULT_GRAPH":L"");}}
        const wchar_t* activations[]={L"PASSIVE",L"DYNAMIC",L"TRANSFER"};for(unsigned i=0;i<3;++i)new(reinterpret_cast<std::wstring*>(0x1476e10)+i) std::wstring(activations[i]);
        const wchar_t* damages[]={L"Physical",L"Magical",L"Fire",L"Ice",L"Electric",L"Poison",L"All"};for(unsigned i=0;i<7;++i)new(reinterpret_cast<std::wstring*>(0x1476640)+i) std::wstring(damages[i]);
        const wchar_t* modifiers[]={L"MELEE",L"RANGED",L"DEFENSE",L"MAGIC",L"LEVEL",L"OWNERLEVEL"};for(unsigned i=0;i<6;++i)new(reinterpret_cast<std::wstring*>(0x1476e40)+i) std::wstring(modifiers[i]);
        s.data->AddDataValue(L"TYPE",variant&4?std::wstring(L"unknown"):gEFFECT_TYPE_NAMES[type],false);
        s.data->AddDataValue(L"ACTIVATION",activations[c.index%3],false);
        const wchar_t* durations[]={L"",L"ALWAYS",L"INSTANT",L"0",L"-1.25",L"2.75",L"-0",L"20"};s.data->AddDataValue(L"DURATION",durations[c.index%8],false);
        if(c.index&1)s.data->AddDataValue(L"UNITTHEME",L"ember",false);
        if(c.index&2)s.data->AddDataValue(L"SAVE",true);if(c.index&4)s.data->AddDataValue(L"USEOWNERLEVEL",true);if(c.index&8)s.data->AddDataValue(L"EXCLUSIVE",true);
        s.data->AddDataValue(L"NAME",L"test name",false);s.data->AddDataValue(L"LINK_NAME",L"lower link",false);
        s.data->AddDataValue(L"LEVEL",c.index%3==0?-1:c.index%3==1?1001:37);
        if(c.index&16)s.data->AddDataValue(L"PARTICLE_FX",L"media/test/a",false);
        if(c.index&32)s.data->AddDataValue(L"NOGRAPH",true);if(c.index&64)s.data->AddDataValue(L"GRAPHOVERRIDE",L"override_graph",false);
        for(unsigned i=0;i<4;++i){if((c.index+i)%3==0)s.data->AddDataValue(gEFFECT_TYPE_PROPERTY_TAGS[type][i],(i&1)?-17.5f:4.25f);else if((c.index+i)%3==1)s.data->AddDataValue(L"VALUE"+(i?STRINGS::GetValueAsWString(i+1):L""),i==1?0.0f:-7.125f);}
        s.data->AddDataValue(L"DAMAGE_TYPE",damages[c.index%7],false);
        const wchar_t* names[]={L"",L"MELEE",L"ranged,magic,defense",L"UNKNOWN,LEVEL,OWNERLEVEL",L"MELEE,RANGED,DEFENSE,MAGIC,LEVEL,OWNERLEVEL,MELEE,INVALID,LEVEL"};
        const wchar_t* amounts[]={L"",L"25",L"-12.5,37.5",L"0,100,-50,12.5,75,200,15,5,18"};
        s.data->AddDataValue(L"STATMODIFYNAME",names[c.index%5],false);s.data->AddDataValue(L"STATMODIFYPERCENT",amounts[(c.index/5)%4],false);
    }
    s.armed=true;
    if(c.mode==0){typedef float(*F)(CEffect*,CEffect::ECALCULATETYPES);F fn=ours?newEffectCalc:oldEffectCalc;if(!autotest::beginInvocation(out,fn))return;fp(fn(s.effect,static_cast<CEffect::ECALCULATETYPES>(c.index%5)));out.callCompleted=1;}
    if(c.mode==1){typedef void(*F)(CEffect*,CBaseUnit*,bool);F fn=ours?newEffectOwner:oldEffectOwner;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,c.index%4==0?NULL:c.index%4==1?s.item:c.index%4==2?static_cast<CBaseUnit*>(s.character):static_cast<CBaseUnit*>(s.equipment),c.index&4);out.callCompleted=1;}
    if(c.mode==2){typedef void(*F)(CEffect*,CSkill*);F fn=ours?newEffectSkill:oldEffectSkill;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,c.index&1?s.skill:NULL);out.callCompleted=1;}
    if(c.mode==3){typedef void(*F)(CEffect*,CAffix*);F fn=ours?newEffectAffix:oldEffectAffix;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,c.index&1?s.affix:NULL);out.callCompleted=1;}
    if(c.mode==4){typedef void(*F)(CEffect*,const CEffect*);F fn=ours?newEffectClone:oldEffectClone;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,s.source);out.callCompleted=1;}
    if(c.mode==5){typedef void(*F)(CEffect*,EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool);F fn=ours?newEffectCtor:oldEffectCtor;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,static_cast<EEFFECT_TYPE>(c.index%145),c.index&1,static_cast<EEFFECT_ACTIVATION>(c.index%3),c.index%3==0?-900.0f:1.25f,-17.5f,0.75f,c.index&2);out.callCompleted=1;}
    if(c.mode==6){typedef void(*F)(CEffect*,const CEffect*);F fn=ours?newEffectCopy:oldEffectCopy;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,s.source);out.callCompleted=1;}
    if(c.mode==7){typedef CEffectDisplayValues(*F)(CEffect*,unsigned,bool);F fn=ours?newEffectVisual:oldEffectVisual;if(!autotest::beginInvocation(out,fn))return;{CEffectDisplayValues v=fn(s.effect,c.index%4==0?static_cast<unsigned>(-1):c.index%4==1?s.effect->m_iLevel:c.index%4==2?1001:31,c.index&4);out.callCompleted=1;fp(v.m_duration);fp(v.m_minimum);fp(v.m_maximum);fp(v.m_secondaryMinimum);fp(v.m_secondaryMaximum);fp(v.m_value24);num(v.m_scaled);num(v.m_effectType);num(id(v.m_effect));}}
    if(c.mode==8){
        for(unsigned i=0;i<4;++i)new(&gEFFECT_TYPE_GRAPHS[s.effect->m_eType][i]) std::wstring(c.index&8?L"default-graph":L"");
        typedef void(*F)(CEffect*,std::wstring);F fn=ours?newEffectGraphs:oldEffectGraphs;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,c.index&16?L"replacement":L"");out.callCompleted=1;
    }
    if(c.mode==9){static const wchar_t* names[]={L"",L"A",L"x/y",L"a\\b",L"Particles",L"/",L"\\",L"media/particle/a"};typedef void(*F)(CEffect*,const std::wstring&);F fn=ours?newEffectFX:oldEffectFX;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,names[c.index%8]);out.callCompleted=1;}
    if(c.mode==14){typedef void(*F)(CEffect*,CDataGroup*,CBaseUnit*);F fn=ours?newEffectDataCtor:oldEffectDataCtor;if(!autotest::beginInvocation(out,fn))return;fn(s.effect,s.data,c.index%3==0?NULL:c.index%3==1?static_cast<CBaseUnit*>(s.item):static_cast<CBaseUnit*>(s.character));out.callCompleted=1;}
    if(c.mode==10){
        CEffectDisplayValues v;v.m_duration=(c.index/145)%3==0?0.0f:(c.index/145)%3==1?2.25f:-1.5f;v.m_minimum=(c.index&1)?-12.25f:3.125f;v.m_maximum=(c.index&2)?0.0f:(c.index&4)?-7.75f:19.125f;v.m_secondaryMinimum=1.25f;v.m_secondaryMaximum=11.5f;
        typedef std::wstring(*F)(CEffect*,CEffectDisplayValues&);F fn=ours?newEffectDisplay:oldEffectDisplay;if(!autotest::beginInvocation(out,fn))return;text(fn(s.effect,v));out.callCompleted=1;
    }
    if(c.mode==11){typedef std::wstring(*F)(CEffect*,unsigned,bool);F fn=ours?newEffectLevelDisplay:oldEffectLevelDisplay;if(!autotest::beginInvocation(out,fn))return;text(fn(s.effect,c.index&1?static_cast<unsigned>(-1):11,c.index&2));out.callCompleted=1;}
    if(c.mode==12){typedef std::wstring(*F)(CEffect*,EDAMAGE_TYPES);F fn=ours?newEffectDamageName:oldEffectDamageName;if(!autotest::beginInvocation(out,fn))return;for(unsigned i=0;i<2;++i)text(fn(s.effect,static_cast<EDAMAGE_TYPES>(c.index%10)));out.callCompleted=1;}
    if(c.mode==13){
        new(&s.affix->m_Effects) TArrayList<CEffect*>;s.affix->m_Effects.add(s.effect);s.affix->m_Effects.add(s.source);
        s.effect->m_pAffixOwner=c.index&1?s.affix:NULL;
        if(c.index&2){CParticle* p=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));void** vt=static_cast<void**>(autotest::allocate(16));vt[1]=reinterpret_cast<void*>(&particleDrop);*reinterpret_cast<void***>(p)=vt;s.effect->m_particle=p;}
        int count=g_iTotalCountOfObjects;typedef void(*F)(CEffect*);F fn=ours?newEffectDtor:oldEffectDtor;if(!autotest::beginInvocation(out,fn))return;fn(s.effect);out.callCompleted=1;num(g_iTotalCountOfObjects-count);num(s.affix->m_Effects.size());for(unsigned i=0;i<s.affix->m_Effects.size();++i)num(id(s.affix->m_Effects[i]));s.affix->m_Effects.~TArrayList();
    }else snapshot(s.effect);
    // Owner destruction must invalidate both registered safe pointers.
    s.character->CRunicCore::~CRunicCore();num(id(s.effect->m_Owner.getObject()));num(id(s.effect->m_sourceCharacter.getObject()));num(s.effect->m_Owner.m_nIndex);num(s.effect->m_sourceCharacter.m_nIndex);
    s.armed=false;if(c.mode!=13){s.effect->m_pAffixOwner=NULL;oldEffectDtor(s.effect);}s.source->m_pAffixOwner=NULL;oldEffectDtor(s.source);
    if(c.mode==14){s.theme->m_sName.~basic_string();s.themes->m_Themes.~TArrayList();}
    if(c.mode>=10)delete s.data;
    s.item->CRunicCore::~CRunicCore();s.equipment->CRunicCore::~CRunicCore();s.skill->CRunicCore::~CRunicCore();
}
void before(void* c,autotest::Capture& o){side(*static_cast<Case*>(c),false,o);}void after(void* c,autotest::Capture& o){side(*static_cast<Case*>(c),true,o);}
int run(const tlhybrid_host* host,unsigned mode,const char* name,uintptr_t address,unsigned count){
    detour::Set hooks;TL_REDIRECT(hooks,effectRng,&rng);TL_REDIRECT(hooks,effectGraph,&graph);TL_REDIRECT(hooks,effectGraphSingleton,&graphSingleton);TL_REDIRECT(hooks,effectGetGraph,&getGraph);TL_REDIRECT(hooks,effectParticleSingleton,&particleSingleton);TL_REDIRECT(hooks,effectPreload,&preload);TL_REDIRECT(hooks,effectThemesSingleton,&themesSingleton);TL_REDIRECT(hooks,effectTranslateSingleton,&translateSingleton);TL_REDIRECT(hooks,effectTranslate,&translate);TL_REDIRECT(hooks,effectSkillParserSingleton,&parserSingleton);TL_REDIRECT(hooks,effectSkillData,&skillData);TL_REDIRECT(hooks,effectMasterResources,&masterResources);TL_REDIRECT(hooks,effectUnitData,&unitData);if(hooks.failed())return 1;
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log(" effect mode%u seed%u exits%d/%d issues%u/%u\n",mode,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
}
TL_TEST(all_effect_calculate){return run(host,0,"all_effect_calculate",0x7dc9f0,512);}
TL_TEST(all_effect_owner){return run(host,1,"all_effect_owner",0x7dd040,256);}
TL_TEST(all_effect_skill_owner){return run(host,2,"all_effect_skill_owner",0x7dd1b0,256);}
TL_TEST(all_effect_affix_owner){return run(host,3,"all_effect_affix_owner",0x7ddc80,256);}
TL_TEST(all_effect_clone){return run(host,4,"all_effect_clone",0x7dd250,256);}
TL_TEST(all_effect_ctor){return run(host,5,"all_effect_ctor",0x7dd6f0,145);}
TL_TEST(all_effect_copy){return run(host,6,"all_effect_copy",0x7dd900,256);}
TL_TEST(all_effect_visual){return run(host,7,"all_effect_visual",0x7ddac0,512);}
TL_TEST(all_effect_graphs){return run(host,8,"all_effect_graphs",0x7de7f0,64);}
TL_TEST(all_effect_fx){return run(host,9,"all_effect_fx",0x7decb0,8);}

TL_TEST(all_effect_display){return run(host,10,"all_effect_display",0x7dedb0,2320);}
TL_TEST(all_effect_level_display){return run(host,11,"all_effect_level_display",0x7e1180,580);}
TL_TEST(all_effect_damage_name){return run(host,12,"all_effect_damage_name",0x7d6020,10);}
TL_TEST(all_effect_destructor){return run(host,13,"all_effect_destructor",0x7de960,32);}

TL_TEST(all_effect_data_ctor){return run(host,14,"all_effect_data_ctor",0x7e1200,1160);}
