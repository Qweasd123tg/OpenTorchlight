// Original-vs-recovered calculation with real graph setters, effect/attack
// constructors, inherent-damage insertion, strings and allocation. External
// data, curves, random draws and effect ownership use identical controlled spies.
#include <cstring>
#include <new>
#include <map>
#include <Ogre.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Equipment.h"
#include "AttackDescription.h"
#include "Effect.h"
#include "DataGroup.h"
#include "GraphManager.h"
#undef private
#undef protected
TL_ORIGINAL(void, originalEquipmentCombatStats, (CEquipment*,bool), "_ZN10CEquipment20calculateCombatStatsEb")
TL_FUNCTION(ecIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ecInt,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(ecFloat,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(ecText,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(ecRandomInt,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(ecRandomFloat,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(ecGraphManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(ecGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ecGraphValue,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(ecAddEffect,"_ZN9CBaseUnit12addNewEffectEP7CEffect")
TL_FUNCTION(ecDestroyText,"_ZN5CItem15destroyItemTextEv")
namespace {
#define EC_AT(F,O) typedef char checked_##F[__builtin_offsetof(CAttackDescription,F)==O?1:-1]
EC_AT(m_sAnimationName,0x10);EC_AT(m_bUnknown18,0x18);EC_AT(m_DamageMaximums,0x24);EC_AT(m_DamageMinimums,0x40);
EC_AT(m_fRange,0x68);EC_AT(m_fStrikeRange,0x6c);EC_AT(m_fAttackSpeed,0x70);EC_AT(m_iToHit,0x74);EC_AT(m_iUnknown78,0x78);
#undef EC_AT
typedef char attack_size[sizeof(CAttackDescription)==0x80?1:-1];
typedef char effect_size[sizeof(CEffect)==0x138?1:-1];
struct Case {unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* object;
std::wstring missile,graphName;std::vector<CEffect*>* ownedEffects;
unsigned long long service[4];CAttackDescription* oldAttack[2];
unsigned profile(){return input->seed/11;}
void number(int n){capture->add(&n,sizeof(n));}
void real(float n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
void narrow(const std::string& s){number(s.size());capture->add(s.data(),s.size());}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){
    number(1);number(p==object);number(t);unsigned leaf=input->seed%11;
    static const int types[]={8,36,110,116,90,98,105,61,13,0,8};
    return static_cast<int>(t)==types[leaf] || (t==UNITTYPES::WEAPON&&leaf<8) || (t==UNITTYPES::ARMOR&&leaf==10);
}
int dataInt(CDataGroup* p,const std::wstring& key,int fallback){
    number(2);number(p==reinterpret_cast<CDataGroup*>(&service[1]));text(key);number(fallback);
    static const int damage[]={0,1,5,17,30};static const int scale[]={0,50,100,125,200};
    static const int elemental[]={-5,0,1,25,100,150};static const int physical[]={-2,-1,0,1,25,100,150};
    unsigned n=profile();
    if(key==L"MINDAMAGE")return damage[n%5];
    if(key==L"MAXDAMAGE")return damage[(n+n/5)%5];
    if(key==L"TOHIT")return static_cast<int>(n%7)-2;
    if(key==L"SPEED")return static_cast<int>(n%8)*25-25;
    if(key==L"RARITY_AMR_MOD")return scale[n%5];
    if(key==L"SPECIAL_AMR_MOD")return scale[(n+1)%5];
    if(key==L"RARITY_DMG_MOD")return scale[(n+2)%5];
    if(key==L"SPEED_DMG_MOD")return scale[(n+3)%5];
    if(key==L"ARMOR")return n%3 ? static_cast<int>(n%21) : 0;
    if(key==L"ARMORMIN")return damage[(n+1)%5];
    if(key==L"ARMORMAX")return damage[(n+3)%5];
    if(key==L"ARMOR_PHYSICAL"||key==L"DAMAGE_PHYSICAL")return physical[n%7];
    static const wchar_t* const armorKeys[]={L"ARMOR_ELECTRIC",L"ARMOR_FIRE",L"ARMOR_ICE",L"ARMOR_POISON"};
    static const wchar_t* const damageKeys[]={L"DAMAGE_ELECTRIC",L"DAMAGE_FIRE",L"DAMAGE_ICE",L"DAMAGE_POISON"};
    for(unsigned i=0;i<4;++i)if(key==armorKeys[i]||key==damageKeys[i]){
        if(input->mode==1)object->m_iUnknown338+=13;
        if(input->mode==4)object->m_pDataGroup=reinterpret_cast<CDataGroup*>(&service[1]);
        return elemental[(n+i)%6];
    }
    _exit(61);return fallback;
}
float dataFloat(CDataGroup*,const std::wstring& key,float fallback){number(3);text(key);real(fallback);return profile()%4 ? fallback+static_cast<int>(profile()%5)*0.125f-0.25f : fallback;}
const std::wstring& dataText(CDataGroup*,const std::wstring& key,const std::wstring& fallback){number(4);text(key);text(fallback);return missile;}
int randomInt(int lo,int hi){number(5);number(lo);number(hi);if(input->mode==2)object->m_iUnknown28C=3;return lo+(hi-lo)/3;}
float randomFloat(float lo,float hi){number(6);real(lo);real(hi);return lo+(hi-lo)*0.375f;}
CGraphManager* graphManager(){number(7);return reinterpret_cast<CGraphManager*>(&service[0]);}
CGraph* graph(CGraphManager*,const std::wstring& name){number(8);text(name);graphName=name;return reinterpret_cast<CGraph*>(&service[2]);}
float graphValue(const CGraph* p,float x,unsigned line){number(9);number(p==reinterpret_cast<CGraph*>(&service[2]));real(x);number(line);if(input->mode==5)object->m_iUnknown28C+=1;return (graphName==L"BASE_WEAPON_DAMAGE"?12.0f:7.0f)+x*0.5f;}
CEffect* addEffect(CBaseUnit* p,CEffect* e){
    number(10);number(p==object);const char* b=reinterpret_cast<const char*>(e);
    number(*reinterpret_cast<const int*>(b+0x1c));number(*reinterpret_cast<const int*>(b+0x20));
    real(*reinterpret_cast<const float*>(b+0x24));number(b[0x30]);number(b[0x37]);real(*reinterpret_cast<const float*>(b+0x38));
    real(*reinterpret_cast<const float*>(b+0xc4));
    ownedEffects->push_back(e);if(input->mode==1)object->m_iUnknown338+=17;return e;
}
void destroyText(CItem* p){
    number(11);number(p==object);number(object->m_InherentElementalDamage.size());
    for(unsigned i=0;i<object->m_InherentElementalDamage.size();++i)number(object->m_InherentElementalDamage[i]);
    if(input->mode==3)object->m_iMaximumDamage=77;
}
void deleteOld(CAttackDescription* p){number(12);number(p==oldAttack[0]?0:p==oldAttack[1]?1:-1);}
void attackState(CAttackDescription* p){
    number(p!=0);if(!p)return;
    if(p==oldAttack[0]||p==oldAttack[1]){number(p==oldAttack[0]?0:1);return;}
    number(2);narrow(p->m_sAnimationName);number(p->m_bUnknown18);
    for(int i=0;i<7;++i){number(p->m_DamageMaximums[i]);number(p->m_DamageMinimums[i]);}
    capture->add(p->m_AttackData5C,sizeof(p->m_AttackData5C));real(p->m_fRange);real(p->m_fStrikeRange);real(p->m_fAttackSpeed);number(p->m_iToHit);number(p->m_iUnknown78);
}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);
    unsigned long long oldStorage[2][sizeof(CAttackDescription)/8];std::memset(oldStorage,0,sizeof(oldStorage));
    void* oldVtable[2]={reinterpret_cast<void*>(&deleteOld),reinterpret_cast<void*>(&deleteOld)};
    for(int i=0;i<2;++i){oldAttack[i]=reinterpret_cast<CAttackDescription*>(oldStorage[i]);*reinterpret_cast<void***>(oldAttack[i])=oldVtable;}
    object->m_pAttackDescription=profile()%4&1?oldAttack[0]:0;object->m_pAttackDescriptionOverride=profile()%4&2?oldAttack[1]:0;
    object->m_pDataGroup=reinterpret_cast<CDataGroup*>(&service[0]);object->m_iUnknown274=profile()%12;
    object->m_iUnknown28C=static_cast<int>(profile()%8)-1;object->m_iUnknown33C=901;object->m_iUnknown340=902;
    new(&object->m_sUnknown400) std::wstring(L"old");missile=profile()%3?L"missiles/Fire_\x416":L"";
    typedef std::vector<int> Ints; typedef std::vector<EDAMAGE_TYPES> DamageTypes;new(&object->m_ElementalDamageTypes) DamageTypes();new(&object->m_ElementalDamageBonuses) Ints();new(&object->m_InherentElementalDamage) Ints();
    for(unsigned i=0;i<profile()%5;++i){object->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((i*2)%7));object->m_ElementalDamageBonuses.push_back(70+i);object->m_InherentElementalDamage.push_back(80+i);}
    std::vector<CEffect*> effects;ownedEffects=&effects;int beforeCount=g_iTotalCountOfObjects;
    detour::Set patches;TL_REDIRECT(patches,ecIsa,&isa);TL_REDIRECT(patches,ecInt,&dataInt);TL_REDIRECT(patches,ecFloat,&dataFloat);TL_REDIRECT(patches,ecText,&dataText);TL_REDIRECT(patches,ecRandomInt,&randomInt);TL_REDIRECT(patches,ecRandomFloat,&randomFloat);TL_REDIRECT(patches,ecGraphManager,&graphManager);TL_REDIRECT(patches,ecGraph,&graph);TL_REDIRECT(patches,ecGraphValue,&graphValue);TL_REDIRECT(patches,ecAddEffect,&addEffect);TL_REDIRECT(patches,ecDestroyText,&destroyText);
    if(patches.failed())_exit(42);
    for(int repeat=0;repeat<2;++repeat){
        bool skip=(c.seed/22)%2!=0;if(ours)object->calculateCombatStats(skip);else originalEquipmentCombatStats(object,skip);
        number(100+repeat);number(object->m_iMinimumDamage);number(object->m_iMaximumDamage);number(object->m_iUnknown338);number(object->m_iUnknown33C);number(object->m_iUnknown340);number(object->m_iUnknown28C);text(object->m_sUnknown400);real(object->m_fUnknown408);
        number(object->m_ElementalDamageTypes.size());for(unsigned i=0;i<object->m_ElementalDamageTypes.size();++i){number(object->m_ElementalDamageTypes[i]);number(object->m_ElementalDamageBonuses[i]);number(object->m_InherentElementalDamage[i]);}
        attackState(object->m_pAttackDescription);attackState(object->m_pAttackDescriptionOverride);number(effects.size());number(g_iTotalCountOfObjects-beforeCount);
    }
    for(unsigned i=0;i<effects.size();++i)delete effects[i];
    if(object->m_pAttackDescription && object->m_pAttackDescription!=oldAttack[0] && object->m_pAttackDescription!=oldAttack[1])delete object->m_pAttackDescription;
    if(object->m_pAttackDescriptionOverride && object->m_pAttackDescriptionOverride!=oldAttack[0] && object->m_pAttackDescriptionOverride!=oldAttack[1])delete object->m_pAttackDescriptionOverride;
    number(g_iTotalCountOfObjects-beforeCount);patches.restore();typedef std::wstring Text;object->m_sUnknown400.~Text();object->m_ElementalDamageTypes.~DamageTypes();object->m_ElementalDamageBonuses.~Ints();object->m_InherentElementalDamage.~Ints();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_combat_stats_differential){
    int failures=0;
    for(unsigned n=0;n<1122;++n){
        Case c={n<792?n:((n-792)%66)+66,n<792?0u:1+(n-792)/66};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    combat %u mode %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
        TL_CHECK(failures,ok);
    }
    host->log("    equipment combat stats: 1122 cases, two calls per side\n");return failures;
}
