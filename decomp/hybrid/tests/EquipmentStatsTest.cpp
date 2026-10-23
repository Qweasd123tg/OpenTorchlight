// Original-vs-recovered text generation. External game services are identical
// spies on both sides; strings, numerical formatting and UTF conversion are real.
#include <cstring>
#include <limits>
#include <new>
#include "AutoTest.h"
#include "tests/Detour.h"
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "AttackDescription.h"
#include "Set.h"
#include "Sets.h"
#include "Inventory.h"
#include "Affix.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#undef protected
#undef private
#include "ResourceManager.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(std::wstring, originalEquipmentStats, (CEquipment*), "_ZN10CEquipment17getEquipmentStatsEv")
extern "C" std::wstring recoveredEquipmentStats(CEquipment*) __asm__("_ZN10CEquipment17getEquipmentStatsEv");
TL_ORIGINAL(void,statsEquipmentCtor,(CEquipment*,CResourceManager*),"_ZN10CEquipmentC1EP16CResourceManager")
TL_ORIGINAL(void,statsEquipmentDtor,(CEquipment*),"_ZN10CEquipmentD1Ev")
TL_FUNCTION(esParse,"_ZN6CAffix15parseAffixGroupEv")
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
struct Case { unsigned seed, mutate, negative; };
const Case* input;
autotest::Capture* capture;
CEquipment* object;
CSet* currentSet;
CSetAffix* bonuses;
CGameGlobals* globals;
unsigned affixCalls, globalsCalls;
bool changed;
CResourceManager* resources;CStringTranslate* translatorOwner;CSets* setsOwner;CInventory* inventory;
void noParse(CAffix*){}
CEquipment* makeEquipment(){CEquipment*p=static_cast<CEquipment*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEquipment),0,0,0));statsEquipmentCtor(p,resources);return p;}
void destroyEquipment(CEquipment*p){statsEquipmentDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
void number(int n) {capture->add(&n,sizeof(n));}
void text(const std::wstring& s) {number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t) {number(1);number(p==object);number(t);return (input->seed&1)!=0;}
CStringTranslate* translator() {number(2);return translatorOwner;}
std::wstring translate(CStringTranslate*,const wchar_t* s) {
    number(3);text(s);
    if (std::wstring(s)==L"pieces") return input->seed%3 ? L"pcs" : L"pieces";
    return input->seed%3 ? std::wstring(L"T:")+s : std::wstring(s);
}
std::wstring setName(CEquipment* p) {number(4);number(p==object);return input->seed%5==0 ? L"" : L"TEST_SET";}
std::wstring speed(CEquipment* p,EWeaponSpeed s) {number(5);number(p==object);number(s);return std::wstring(1,L'A'+static_cast<int>(s));}
CSets* sets() {number(6);return setsOwner;}
CSet* findSet(CSets*,const wchar_t* s) {number(7);text(s);return input->seed%7==0 ? 0 : currentSet;}
int equippedCount(CInventory*,CSet* s) {number(8);number(s==currentSet);return static_cast<int>(input->seed%7)-1;}
CGameGlobals* gameGlobals() {number(9);++globalsCalls;return globals;}
std::wstring affixStats(CAffix* p,unsigned level) {
    number(10);number(level);int id=-1;
    for (int i=0;i<4;++i) if(p==bonuses[i].m_pAffix)id=i;
    number(id);if(id<0)std::abort();
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
    CEquipment* allocated=makeEquipment();object=allocated;
    TSafePointer<CEquipment> witness;witness.setObject(object);
    CAttackDescription attack0("fixture-attack",false,1,2,0,0,0,1),attack1("fixture-override",false,1,2,0,0,0,1);
    CAttackDescription* a=&attack0;CAttackDescription* b=&attack1;
    static const float speeds[]={-1,0,0.799f,0.8f,0.9f,1.1f,1.3f,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
    a->m_fAttackSpeed=speeds[c.seed%10];b->m_fAttackSpeed=speeds[(c.seed+3)%10];
    object->m_pAttackDescription=a;object->m_pAttackDescriptionOverride=c.seed%4==0 ? b : 0;
    static const int damage[]={0,1,2,3,7,-1,2147483647};
    object->m_iMinimumDamage=damage[(c.seed/2)%7];
    object->m_iMaximumDamage=c.seed%3 ? object->m_iMinimumDamage : damage[(c.seed+3)%7];
    object->m_bUnknown348=(c.seed&2)!=0;
    typedef std::vector<int> Ints; typedef std::vector<EDAMAGE_TYPES> DamageTypes;
    for (unsigned i=0;i<c.seed%4;++i) {
        object->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((c.seed+i)%7));
        object->m_ElementalDamageBonuses.push_back(99);
        object->m_InherentElementalDamage.push_back(damage[(c.seed+i)%7]);
    }
    object->m_iSocketCount=c.seed%4;
    CEquipment* sockets[4]={NULL,NULL,NULL,NULL};for (unsigned i=0;i<(c.seed/3)%5;++i){sockets[i]=makeEquipment();object->m_SocketedEquipment.add(sockets[i]);}
    object->m_pInventory=c.seed%3 ? inventory : 0;
    CSet set; CSetAffix entries[4];currentSet=&set;bonuses=entries;
    set.m_sName=L"TEST_SET";set.m_sDisplayName=c.seed%2 ? L"Set\x416" : L"";
    {detour::Set construction;TL_REDIRECT(construction,esParse,&noParse);if(construction.failed())std::abort();
    for(unsigned i=0;i<4;++i) {
        entries[i].m_pAffix=new CAffix(L"fixture-stat-affix");entries[i].m_iLevel=i+1;
        entries[i].m_iRequiredCount=static_cast<int>(i*2)-1;
        if(i<c.seed%4)set.m_Affixes.add(&entries[i]);
    }
    }
    globals=CGameGlobals::getSingleton();if(!globals)std::abort();
    globals->m_sSetColor=L"11AA22";globals->m_sSetColorUnselected=L"778899";
    detour::Set patches;
    TL_REDIRECT(patches,esIsa,&isa);TL_REDIRECT(patches,esTranslation,&translator);TL_REDIRECT(patches,esTranslate,&translate);
    TL_REDIRECT(patches,esSetName,&setName);TL_REDIRECT(patches,esAttackSpeed,&speed);TL_REDIRECT(patches,esSets,&sets);
    TL_REDIRECT(patches,esFindSet,&findSet);TL_REDIRECT(patches,esSetCount,&equippedCount);TL_REDIRECT(patches,esGlobals,&gameGlobals);TL_REDIRECT(patches,esAffixStats,&affixStats);
    if(patches.failed())_exit(42);
    for(int repeat=0;repeat<2;++repeat) {
        number(100+repeat);if(repeat==1&&ours&&c.negative)object->m_iSocketCount^=1;
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
    // Restore actual ownership: set list borrows the stack records, while
    // each record owns its real native affix. Socket children and attacks are
    // independently owned by this fixture, never self-owned/fabricated actors.
    set.m_Affixes.clear();object->m_SocketedEquipment.clear();
    object->m_pInventory=NULL;object->m_pAttackDescription=NULL;object->m_pAttackDescriptionOverride=NULL;
    for(unsigned i=0;i<4;++i)if(sockets[i])destroyEquipment(sockets[i]);
    destroyEquipment(allocated);number(witness.getObject()==NULL);if(witness.getObject())std::abort();

}
void original(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),true,c);}
}
int statsWorker(const tlhybrid_host* host) {
    nativegame::Services* services=new nativegame::Services;if(!services->ready())return 1;resources=new CResourceManager(services->scene);translatorOwner=new CStringTranslate(L"/fixture-no-translation-file");setsOwner=new CSets(L"/fixture-no-sets/",NULL);inventory=new CInventory(NULL,16);
    int failures=0;
    autotest::Coverage coverage("equipment_stats_differential",(uint64_t)(uintptr_t)&originalEquipmentStats);
    for (unsigned seed=0;seed<294;++seed) {
        Case c={seed<210 ? seed : 1+(seed-210)%21, seed<210 ? 0u : 1u<<((seed-210)/21),0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        int observation=coverage.observe(host,a,b);
        bool ok=observation==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    comparison_kind=%d\n",observation);
        if(!ok)host->log("    equipment seed %u: status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);
    }
    coverage.report(host);
    host->log("    equipment stats: 294 cases, two calls per side\n");
    Case control={43,0,1};autotest::Outcome a,b;autotest::runChild(original,&control,a,2000,10000);autotest::runChild(recovered,&control,b,2000,10000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);
    host->log("    equipment stats negative detected%u completed%u\n",unsigned(detected),unsigned(completed));
    return failures+(!detected||!completed)+(coverage.completed!=294);
}
TL_TEST(equipment_stats_differential){return systems_fixture::isolated(statsWorker,host,180);}
