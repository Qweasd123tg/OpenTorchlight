// Original-vs-recovered text generation. External game services are identical
// spies on both sides; strings, numerical formatting and UTF conversion are real.
#include <cstring>
#include <limits>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Equipment.h"
#include "AttackDescription.h"
#include "Set.h"
#include "Sets.h"
#include "Inventory.h"
#include "Affix.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
TL_ORIGINAL(std::wstring, originalEquipmentStats, (CEquipment*), "_ZN10CEquipment17getEquipmentStatsEv")
extern "C" std::wstring recoveredEquipmentStats(CEquipment*) __asm__("_ZN10CEquipment17getEquipmentStatsEv");
TL_FUNCTION(esIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(esTranslation,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(esTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(esSetName,"_ZN10CEquipment6getSetEv")
TL_FUNCTION(esAttackSpeed,"_ZN10CEquipment20getAttackSpeedStringE12EWeaponSpeed")
TL_FUNCTION(esSets,"_ZN5CSets12getSingletonEv")
TL_FUNCTION(esFindSet,"_ZN5CSets6getSetEPKw")
TL_FUNCTION(esSetCount,"_ZN10CInventory11getSetCountEP4CSet")
TL_FUNCTION(esGlobals,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(esAffixStats,"_ZN6CAffix15getDisplayStatsEj")
namespace {
#define ES_SIZE(C,S) typedef char checked_size_##C[sizeof(C)==S?1:-1]
#define ES_AT(C,F,O) typedef char checked_offset_##F[__builtin_offsetof(C,F)==O?1:-1]
ES_SIZE(CItem,0x230); ES_SIZE(CEquipment,0x438); ES_SIZE(CAttackDescription,0x80);
ES_SIZE(CSet,0x30); ES_SIZE(CSetAffix,0x18);
// Matches the first derived fields of original ItemGold and Breakable.
struct ItemTailProbe : CItem { int firstDerivedField; };
ES_AT(ItemTailProbe,firstDerivedField,0x22c);
ES_AT(CEquipment,m_pInventory,0x240);ES_AT(CEquipment,m_pAttackDescription,0x2a0);
ES_AT(CEquipment,m_pAttackDescriptionOverride,0x2a8);
ES_AT(CEquipment,m_ElementalDamageTypes,0x350);ES_AT(CEquipment,m_ElementalDamageBonuses,0x368);
ES_AT(CEquipment,m_InherentElementalDamage,0x380);ES_AT(CEquipment,m_iSocketCount,0x3e0);
ES_AT(CEquipment,m_SocketedEquipment,0x3e8);ES_AT(CAttackDescription,m_fAttackSpeed,0x70);
ES_AT(CSet,m_Affixes,8);ES_AT(CSet,m_sDisplayName,0x28);
ES_AT(CSetAffix,m_iLevel,0x10);ES_AT(CSetAffix,m_iRequiredCount,0x14);
#undef ES_SIZE
#undef ES_AT
struct Case { unsigned seed, mutate; };
const Case* input;
autotest::Capture* capture;
CEquipment* object;
CSet* currentSet;
CSetAffix* bonuses;
CGameGlobals* globals;
unsigned affixCalls, globalsCalls;
bool changed;
unsigned long long service;
void number(int n) {capture->add(&n,sizeof(n));}
void text(const std::wstring& s) {number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t) {number(1);number(p==object);number(t);return (input->seed&1)!=0;}
CStringTranslate* translator() {number(2);return reinterpret_cast<CStringTranslate*>(&service);}
std::wstring translate(CStringTranslate*,const wchar_t* s) {
    number(3);text(s);
    if (std::wstring(s)==L"pieces") return input->seed%3 ? L"pcs" : L"pieces";
    return input->seed%3 ? std::wstring(L"T:")+s : std::wstring(s);
}
std::wstring setName(CEquipment* p) {number(4);number(p==object);return input->seed%5==0 ? L"" : L"TEST_SET";}
std::wstring speed(CEquipment* p,EWeaponSpeed s) {number(5);number(p==object);number(s);return std::wstring(1,L'A'+static_cast<int>(s));}
CSets* sets() {number(6);return reinterpret_cast<CSets*>(&service);}
CSet* findSet(CSets*,const wchar_t* s) {number(7);text(s);return input->seed%7==0 ? 0 : currentSet;}
int equippedCount(CInventory*,CSet* s) {number(8);number(s==currentSet);return static_cast<int>(input->seed%7)-1;}
CGameGlobals* gameGlobals() {number(9);++globalsCalls;return globals;}
std::wstring affixStats(CAffix* p,unsigned level) {
    number(10);number(level);int id=-1;
    for (int i=0;i<4;++i) if(p==reinterpret_cast<CAffix*>(&bonuses[i]))id=i;
    number(id);
    if (++affixCalls>20) _exit(41);
    if (!changed) {
        changed=true;
        if (input->mutate&1) bonuses[id].m_iRequiredCount+=3;
        if (input->mutate&2) currentSet->m_Affixes.add(&bonuses[3]);
        if (input->mutate&4) currentSet->m_Affixes.clear();
        if (input->mutate&8) bonuses[(id+1)%4].m_iLevel+=10;
    }
    switch(input->seed%5) {
    case 0:return L"";
    case 1:return L"bonus";
    case 2:return L"line1\nline2";
    case 3:return L"line1\\nline2\nline3";
    default:return L"\x416\U0001f525 |cABCDEFtext|u";
    }
}
void side(const Case& c,bool ours,autotest::Capture& out) {
    input=&c;capture=&out;affixCalls=0;globalsCalls=0;changed=false;
    unsigned long long self[(sizeof(CEquipment)+7)/8];std::memset(self,0,sizeof(self));
    object=reinterpret_cast<CEquipment*>(self);
    unsigned long long attack0[sizeof(CAttackDescription)/8],attack1[sizeof(CAttackDescription)/8];
    std::memset(attack0,0,sizeof(attack0));std::memset(attack1,0,sizeof(attack1));
    CAttackDescription* a=reinterpret_cast<CAttackDescription*>(attack0);
    CAttackDescription* b=reinterpret_cast<CAttackDescription*>(attack1);
    static const float speeds[]={-1,0,0.799f,0.8f,0.9f,1.1f,1.3f,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
    a->m_fAttackSpeed=speeds[c.seed%10];b->m_fAttackSpeed=speeds[(c.seed+3)%10];
    object->m_pAttackDescription=a;object->m_pAttackDescriptionOverride=c.seed%4==0 ? b : 0;
    static const int damage[]={0,1,2,3,7,-1,2147483647};
    object->m_iMinimumDamage=damage[(c.seed/2)%7];
    object->m_iMaximumDamage=c.seed%3 ? object->m_iMinimumDamage : damage[(c.seed+3)%7];
    object->m_bUnknown348=(c.seed&2)!=0;
    typedef std::vector<int> Ints; typedef std::vector<EDAMAGE_TYPES> DamageTypes;
    new (&object->m_ElementalDamageTypes) DamageTypes();
    new (&object->m_ElementalDamageBonuses) Ints();
    new (&object->m_InherentElementalDamage) Ints();
    for (unsigned i=0;i<c.seed%4;++i) {
        object->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((c.seed+i)%7));
        object->m_ElementalDamageBonuses.push_back(99);
        object->m_InherentElementalDamage.push_back(damage[(c.seed+i)%7]);
    }
    new (&object->m_SocketedEquipment) TArrayList<CEquipment*>(1);
    object->m_iSocketCount=c.seed%4;
    for (unsigned i=0;i<(c.seed/3)%5;++i)object->m_SocketedEquipment.add(object);
    object->m_pInventory=c.seed%3 ? reinterpret_cast<CInventory*>(&service) : 0;
    CSet set; CSetAffix entries[4];currentSet=&set;bonuses=entries;
    set.m_sName=L"TEST_SET";set.m_sDisplayName=c.seed%2 ? L"Set\x416" : L"";
    for(unsigned i=0;i<4;++i) {
        entries[i].m_pAffix=reinterpret_cast<CAffix*>(&entries[i]);entries[i].m_iLevel=i+1;
        entries[i].m_iRequiredCount=static_cast<int>(i*2)-1;
        if(i<c.seed%4)set.m_Affixes.add(&entries[i]);
    }
    unsigned long long globalsStorage[(sizeof(CGameGlobals)+7)/8];std::memset(globalsStorage,0,sizeof(globalsStorage));
    globals=reinterpret_cast<CGameGlobals*>(globalsStorage);
    std::wstring* active=new(reinterpret_cast<char*>(globals)+0x280) std::wstring(L"11AA22");
    std::wstring* inactive=new(reinterpret_cast<char*>(globals)+0x2a8) std::wstring(L"778899");
    detour::Set patches;
    TL_REDIRECT(patches,esIsa,&isa);TL_REDIRECT(patches,esTranslation,&translator);TL_REDIRECT(patches,esTranslate,&translate);
    TL_REDIRECT(patches,esSetName,&setName);TL_REDIRECT(patches,esAttackSpeed,&speed);TL_REDIRECT(patches,esSets,&sets);
    TL_REDIRECT(patches,esFindSet,&findSet);TL_REDIRECT(patches,esSetCount,&equippedCount);TL_REDIRECT(patches,esGlobals,&gameGlobals);TL_REDIRECT(patches,esAffixStats,&affixStats);
    if(patches.failed())_exit(42);
    for(int repeat=0;repeat<2;++repeat) {
        number(100+repeat);
        if(repeat==0) {
            if(ours)autotest::invoke(out,&recoveredEquipmentStats,object);
            else autotest::invoke(out,&originalEquipmentStats,object);
        } else {
            std::wstring result=ours ? object->getEquipmentStats() : originalEquipmentStats(object);
            text(result);
        }
    }
    number(affixCalls);number(globalsCalls);number(set.m_Affixes.size());
    patches.restore();
    typedef std::wstring Text;active->~Text();inactive->~Text();
    object->m_ElementalDamageTypes.~DamageTypes();object->m_ElementalDamageBonuses.~Ints();object->m_InherentElementalDamage.~Ints();
    object->m_SocketedEquipment.~TArrayList<CEquipment*>();
}
void original(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_stats_differential) {
    int failures=0;
    autotest::Coverage coverage("equipment_stats_differential",(uint64_t)(uintptr_t)&originalEquipmentStats);
    for (unsigned seed=0;seed<294;++seed) {
        Case c={seed<210 ? seed : 1+(seed-210)%21, seed<210 ? 0u : 1u<<((seed-210)/21)};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        int observation=coverage.observe(host,a,b);
        bool ok=observation==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    comparison_kind=%d\n",observation);
        if(!ok)host->log("    equipment seed %u: status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);
    }
    coverage.report(host);
    host->log("    equipment stats: 294 cases, two calls per side\n");
    return failures;
}
