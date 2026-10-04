// Compare the original UI description with the reconstruction. Collaborators
// are controlled spies; real STL formatting, affix selection and UTF strings.
#include <cstring>
#include <limits>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include <Ogre.h>
#include <map>
#define private public
#define protected public
#include "Equipment.h"
#include "AttackDescription.h"
#include "EffectManager.h"
#include "Affix.h"
#include "Level.h"
#include "StringTranslate.h"
#undef private
#undef protected
TL_ORIGINAL(std::wstring, originalEquipmentDescription, (CEquipment*,bool,bool), "_ZN10CEquipment23getEquipmentDescriptionEbb")
TL_FUNCTION(edIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(edTranslation,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(edTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(edTranslateRef,"_ZN16CStringTranslate18getTranslateStringERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(edAttackSpeed,"_ZN10CEquipment20getAttackSpeedStringE12EWeaponSpeed")
TL_FUNCTION(edBuy,"_ZN10CEquipment8buyPriceEv")
TL_FUNCTION(edSell,"_ZN10CEquipment9sellPriceEv")
TL_FUNCTION(edEffects,"_ZN10CEquipment19getEquipmentEffectsEv")
TL_FUNCTION(edPlayer,"_ZN6CLevel9getPlayerEv")
TL_FUNCTION(edRequirement,"_ZN10CEquipment19getLevelRequirementEP10CCharacter")
namespace {
typedef char description_size[sizeof(CEquipment)==0x438?1:-1];
typedef char prefix_offset[__builtin_offsetof(CEquipment,m_sPrefix)==0x2e0?1:-1];
typedef char suffix_offset[__builtin_offsetof(CEquipment,m_sSuffix)==0x2e8?1:-1];
typedef char affix_prefix_offset[__builtin_offsetof(CAffix,m_sPrefix)==0x58?1:-1];
typedef char affix_suffix_offset[__builtin_offsetof(CAffix,m_sSuffix)==0x60?1:-1];
typedef char affix_rank_offset[__builtin_offsetof(CAffix,m_iRank)==0x74?1:-1];
struct Case {unsigned seed, mode;};
const Case* input; autotest::Capture* capture; CEquipment* object;
std::wstring itemName,translatedRef;
CLevel* levelObject; CCharacter* playerObject;
unsigned long long service;
void number(int n) {capture->add(&n,sizeof(n));}
void text(const std::wstring& s) {number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t) {
    number(1);number(p==object);number(t);
    unsigned category=input->seed%9,quality=(input->seed/9)%4;
    switch(t) {
    case UNITTYPES::WEAPON:return category<4;
    case UNITTYPES::SWORD:return category==1;
    case UNITTYPES::BOW:return category==2;
    case UNITTYPES::AXE:return category==3;
    case UNITTYPES::ARMOR:return category==4;
    case UNITTYPES::TRINKET:return category==5;
    case UNITTYPES::POTION:return category==6;
    case UNITTYPES::SCROLL:return category==7;
    case UNITTYPES::UNIQUE:return quality==1;
    case UNITTYPES::MAGIC:return quality==2;
    default:return false;
    }
}
CStringTranslate* translator() {number(2);return reinterpret_cast<CStringTranslate*>(&service);}
std::wstring translate(CStringTranslate*,const wchar_t* s) {
    number(3);text(s);
    if(input->mode==2) return L"";
    if(input->mode==3 && object->m_InherentElementalDamage.size()) object->m_InherentElementalDamage[0]+=1;
    return input->seed%3 ? std::wstring(L"T:")+s : std::wstring(s);
}
const std::wstring& translateRef(CStringTranslate*,const std::wstring& s) {number(4);text(s);translatedRef=L"R:"+s;return translatedRef;}
const std::wstring& name(CEquipment* p) {number(5);number(p==object);if(input->mode==1)object->m_bUnknown348=!object->m_bUnknown348;return itemName;}
bool magical(CEquipment* p) {number(6);number(p==object);return (input->seed/9)%4==3;}
float effect(CEquipment* p,EEFFECT_TYPE t,float value,EDAMAGE_TYPES d) {
    number(7);number(p==object);number(t);number(d);capture->add(&value,sizeof(value));
    static const float percent[]={0,1,-1,12.5f,-12.5f,99.9f};
    static const float flat[]={0,0.1f,-0.1f,2.2f,-2.2f,7};
    if(input->mode==4) object->m_iUnknown338+=3;
    return static_cast<int>(t)==0x17 ? percent[(input->seed/9)%6] : flat[(input->seed/18)%6];
}
std::wstring speed(CEquipment* p,EWeaponSpeed s) {number(8);number(p==object);number(s);if(input->mode==5)object->m_bUnknown348=!object->m_bUnknown348;return std::wstring(1,L'A'+static_cast<int>(s));}
int buy(CEquipment* p) {number(9);number(p==object);return static_cast<int>(input->seed)-150;}
int sell(CEquipment* p) {number(10);number(p==object);return 75-static_cast<int>(input->seed);}
std::wstring effects(CEquipment* p) {number(11);number(p==object);switch(input->seed%5){case 0:return L"";case 1:return input->seed%10==1 ? L"x" : L"effect";case 2:return L"effect\n\n";case 3:return L"\n\n";default:return L"\x416\U0001f525\n";}}
CCharacter* player(CLevel* p) {number(12);number(p==levelObject);return playerObject;}
int requirement(CEquipment* p,CCharacter* c) {number(13);number(p==object);number(c==playerObject);return static_cast<int>(input->seed%13)-1;}
void side(const Case& c,bool ours,autotest::Capture& out) {
    input=&c;capture=&out;
    unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);
    void* vtable[128];std::memset(vtable,0,sizeof(vtable));vtable[74]=reinterpret_cast<void*>(&effect);vtable[84]=reinterpret_cast<void*>(&name);vtable[86]=reinterpret_cast<void*>(&magical);*reinterpret_cast<void***>(object)=vtable;
    itemName=c.seed%7==0 ? L"" : c.seed%7==1 ? L"Item\n\n" : L"Item\x416\U0001f525";
    new(&object->m_sPrefix) std::wstring(c.seed%3 ? L"cachedPrefix" : L"");
    new(&object->m_sSuffix) std::wstring(c.seed%4 ? L"cachedSuffix" : L"");
    object->m_bUnknown348=((c.seed/36)%2)!=0;
    unsigned long long managerStorage[(sizeof(CEffectManager)+7)/8];std::memset(managerStorage,0,sizeof(managerStorage));
    CEffectManager* manager=reinterpret_cast<CEffectManager*>(managerStorage);
    TArrayList<CAffix*>* list=new(reinterpret_cast<char*>(manager)+0x10) TArrayList<CAffix*>(2);
    unsigned long long affixStorage[5][(sizeof(CAffix)+7)/8];std::memset(affixStorage,0,sizeof(affixStorage));
    static const int ranks[]={10,0,5,-1,11};
    for(unsigned i=0;i<5;++i) {
        CAffix* a=reinterpret_cast<CAffix*>(affixStorage[i]);a->m_iRank=c.mode==7 ? 5 : ranks[(c.seed/72+i)%5];
        std::wstring prefix=c.seed%6==i ? L"" : std::wstring(1,L'P'+i);
        std::wstring suffix=c.seed%5==i ? L"" : std::wstring(1,L'a'+i);
        if(c.mode==6){prefix=std::wstring(L"P\0ignored",9);suffix=std::wstring(L"\0ignored",8);}
        new(&a->m_sPrefix) std::wstring(prefix);new(&a->m_sSuffix) std::wstring(suffix);
        if(i<c.seed%6)list->add(a);
    }
    object->m_pEffectManager=c.seed%7 ? manager : 0;
    unsigned long long attackStorage[2][sizeof(CAttackDescription)/8];std::memset(attackStorage,0,sizeof(attackStorage));
    CAttackDescription* a=reinterpret_cast<CAttackDescription*>(attackStorage[0]);CAttackDescription* b=reinterpret_cast<CAttackDescription*>(attackStorage[1]);
    static const float speeds[]={-1,0,0.799f,0.8f,0.9f,1.1f,1.3f,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
    a->m_fAttackSpeed=speeds[(c.seed/9)%10];b->m_fAttackSpeed=speeds[(c.seed/9+3)%10];
    object->m_pAttackDescription=a;object->m_pAttackDescriptionOverride=c.seed%4 ? 0 : b;
    static const int damage[]={0,1,3,-2,7,2147483647};
    object->m_iMinimumDamage=damage[(c.seed/9)%6];object->m_iMaximumDamage=c.seed%3 ? object->m_iMinimumDamage : damage[(c.seed/9+2)%6];
    object->m_iUnknown338=static_cast<int>(c.seed%29)-7;
    typedef std::vector<int> Ints; typedef std::vector<EDAMAGE_TYPES> DamageTypes;new(&object->m_ElementalDamageTypes) DamageTypes();new(&object->m_ElementalDamageBonuses) Ints();new(&object->m_InherentElementalDamage) Ints();
    for(unsigned i=0;i<c.seed%4;++i) {object->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((c.seed+i)%7));object->m_ElementalDamageBonuses.push_back(88);object->m_InherentElementalDamage.push_back(damage[(c.seed+i)%5]);}
    new(&object->m_SocketedEquipment) TArrayList<CEquipment*>(1);object->m_iSocketCount=c.seed%4;
    for(unsigned i=0;i<(c.seed/4)%5;++i)object->m_SocketedEquipment.add(object);
    unsigned long long resources[(sizeof(CResourceManager)+7)/8];std::memset(resources,0,sizeof(resources));
    CResourceManager* rm=reinterpret_cast<CResourceManager*>(resources);levelObject=reinterpret_cast<CLevel*>(&service);playerObject=c.seed%3 ? reinterpret_cast<CCharacter*>(&service) : 0;rm->m_pLevel=levelObject;object->m_pResourceManager=rm;object->m_iUnknown278=c.seed%3 ? 2 : 0;
    detour::Set patches;TL_REDIRECT(patches,edIsa,&isa);TL_REDIRECT(patches,edTranslation,&translator);TL_REDIRECT(patches,edTranslate,&translate);TL_REDIRECT(patches,edTranslateRef,&translateRef);TL_REDIRECT(patches,edAttackSpeed,&speed);TL_REDIRECT(patches,edBuy,&buy);TL_REDIRECT(patches,edSell,&sell);TL_REDIRECT(patches,edEffects,&effects);TL_REDIRECT(patches,edPlayer,&player);TL_REDIRECT(patches,edRequirement,&requirement);
    if(patches.failed())_exit(42);
    for(int repeat=0;repeat<2;++repeat) {
        bool buyFlag=(c.seed&1)!=0,sellFlag=(c.seed&2)!=0;
        std::wstring result=ours ? object->getEquipmentDescription(buyFlag,sellFlag) : originalEquipmentDescription(object,buyFlag,sellFlag);
        number(100+repeat);text(result);text(object->m_sPrefix);text(object->m_sSuffix);number(object->m_bUnknown348);number(object->m_iUnknown338);
    }
    patches.restore();typedef std::wstring Text;object->m_sPrefix.~Text();object->m_sSuffix.~Text();
    for(int i=0;i<5;++i){CAffix* a=reinterpret_cast<CAffix*>(affixStorage[i]);a->m_sPrefix.~Text();a->m_sSuffix.~Text();}
    list->~TArrayList<CAffix*>();object->m_ElementalDamageTypes.~DamageTypes();object->m_ElementalDamageBonuses.~Ints();object->m_InherentElementalDamage.~Ints();object->m_SocketedEquipment.~TArrayList<CEquipment*>();
}
void original(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c) {side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_description_differential) {
    int failures=0;
    for(unsigned n=0;n<1224;++n) {
        Case c={n<720 ? n : 36+(n-720)%72,n<720 ? 0u : 1+(n-720)/72};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    description %u mode %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
        TL_CHECK(failures,ok);
    }
    host->log("    equipment description: 1224 cases, two calls per side\n");return failures;
}
