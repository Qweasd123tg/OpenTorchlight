// Full original recursion is compared with full reconstructed recursion:
// the hybrid self-tests run before replacement hooks are installed.
#include <cstring>
#include <new>
#include <map>
#include <Ogre.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#undef private
#undef protected
TL_ORIGINAL(std::wstring, originalEffectsDescription, (CEquipment*,EEFFECT_ACTIVATION,bool,bool), "_ZN10CEquipment18effectsDescriptionE18EEFFECT_ACTIVATIONbb")
extern "C" std::wstring recoveredEffectsDescription(CEquipment*,EEFFECT_ACTIVATION,bool,bool) __asm__("_ZN10CEquipment18effectsDescriptionE18EEFFECT_ACTIVATIONbb");
TL_FUNCTION(efIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(efTranslator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(efTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(efVisual,"_ZN14CEffectManager20getVisualDescriptionE18EEFFECT_ACTIVATIONjbb")
TL_FUNCTION(efGlobals,"_ZN12CGameGlobals12getSingletonEv")
namespace {
struct Case {unsigned seed,mode,warm,limited;};
const Case* input;autotest::Capture* capture;CEquipment* objects[4];CGameGlobals* globals;
unsigned long long services[4];std::wstring descriptions[4];unsigned visualCalls;bool changed;
void number(int n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
int objectID(const CBaseUnit* p){for(int i=0;i<4;++i)if(p==objects[i])return i;return -1;}
int managerID(const CEffectManager* p){for(int i=0;i<4;++i)if(p==reinterpret_cast<const CEffectManager*>(&services[i]))return i;return -1;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){
    int id=objectID(p);number(1);number(id);number(t);if(id<0)_exit(61);
    if(input->mode==4&&t==UNITTYPES::SOCKETABLE)objects[id]->m_pEffectManager=reinterpret_cast<CEffectManager*>(&services[(id+1)%4]);
    if(t==UNITTYPES::SOCKETABLE)return (input->seed/7+id)%3!=0;
    if(t==UNITTYPES::RANDOMMAGIC_SOCKETABLE)return (input->seed/11+id)%2!=0;
    return false;
}
CStringTranslate* translator(){number(2);return reinterpret_cast<CStringTranslate*>(&services[0]);}
std::wstring translate(CStringTranslate*,const wchar_t* s){
    number(3);text(s);
    if(input->mode==1&&objects[0]->m_ElementalDamageBonuses.size())objects[0]->m_ElementalDamageBonuses[0]=-objects[0]->m_ElementalDamageBonuses[0]+1;
    if(input->mode==2)return L"";
    return input->seed%3?std::wstring(L"T:")+s:std::wstring(s);
}
const std::wstring& visual(CEffectManager* p,EEFFECT_ACTIVATION a,unsigned level,bool show,bool special){
    int id=managerID(p);number(4);number(id);number(a);number(level);number(show);number(special);if(id<0)_exit(62);
    if(++visualCalls>100)_exit(63);
    if(!changed){changed=true;
        if(input->mode==3)objects[0]->m_SocketedEquipment.add(objects[3]);
        if(input->mode==5){objects[0]->m_ElementalDamageTypes.push_back(DAMAGE_FIRE);objects[0]->m_ElementalDamageBonuses.push_back(7);objects[0]->m_InherentElementalDamage.push_back(200);}
    }
    switch((input->seed+id+static_cast<unsigned>(a))%8){
    case 0:descriptions[id]=L"";break;
    case 1:descriptions[id]=L"x";break;
    case 2:descriptions[id]=L"x\n";break;
    case 3:descriptions[id]=L"\n\n";break;
    case 4:descriptions[id]=L"two\nlines\n\n";break;
    case 5:descriptions[id]=L"\x416\U0001f525";break;
    case 6:descriptions[id]=L"|c123456tag|u\n";break;
    default:descriptions[id]=special?L"special":L"regular";break;
    }
    return descriptions[id];
}
CGameGlobals* gameGlobals(){number(5);if(input->mode==7)globals->m_sGlobalsString2B8=L"CHANGED";return globals;}
struct Snapshot {
 std::vector<unsigned char> bytes;
 Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}
 void pointer(size_t offset,uintptr_t value){if(offset+sizeof(value)>bytes.size())_exit(64);std::memcpy(&bytes[offset],&value,sizeof(value));}
 template<class T> void array(size_t offset,const std::vector<T>& v){pointer(offset,0);pointer(offset+8,v.size());pointer(offset+16,v.capacity());number(v.size());for(size_t i=0;i<v.size();++i)number(v[i]);}
 void emit(){capture->add(&bytes[0],bytes.size());}
};
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;visualCalls=0;changed=false;
    unsigned long long storage[4][(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));
    typedef std::vector<EDAMAGE_TYPES> Types;typedef std::vector<int> Ints;
    static const int bonuses[]={-7,0,1,2,77};
    for(unsigned id=0;id<4;++id){
        objects[id]=reinterpret_cast<CEquipment*>(storage[id]);
        new(&objects[id]->m_ElementalDamageTypes)Types();new(&objects[id]->m_ElementalDamageBonuses)Ints();new(&objects[id]->m_InherentElementalDamage)Ints();new(&objects[id]->m_SocketedEquipment)TArrayList<CEquipment*>();
        for(unsigned i=0;i<(c.seed/12+id)%5;++i){objects[id]->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((c.seed+id+i)%7));objects[id]->m_ElementalDamageBonuses.push_back(bonuses[(c.seed/3+id+i)%5]);objects[id]->m_InherentElementalDamage.push_back(99+i);}
        objects[id]->m_pEffectManager=c.seed%7==id?0:reinterpret_cast<CEffectManager*>(&services[id]);
    }
    for(unsigned i=0;i<(c.seed/12)%5;++i)objects[0]->m_SocketedEquipment.add(c.mode==6&&i==3?objects[0]:objects[1+i%3]);
    if(c.limited && c.mode!=3 && objects[0]->m_SocketedEquipment.size()>1)objects[0]->m_SocketedEquipment.m_nCapacity=1;
    unsigned long long globalStorage[(sizeof(CGameGlobals)+7)/8];std::memset(globalStorage,0,sizeof(globalStorage));globals=reinterpret_cast<CGameGlobals*>(globalStorage);new(&globals->m_sGlobalsString2B8)std::wstring(c.seed%5?L"AA00BB":L"");
    detour::Set patches;TL_REDIRECT(patches,efIsa,&isa);TL_REDIRECT(patches,efTranslator,&translator);TL_REDIRECT(patches,efTranslate,&translate);TL_REDIRECT(patches,efVisual,&visual);TL_REDIRECT(patches,efGlobals,&gameGlobals);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<=c.warm;++repeat){
        EEFFECT_ACTIVATION a=static_cast<EEFFECT_ACTIVATION>(c.seed%3);bool embedded=(c.seed/3)%2!=0,socketed=(c.seed/6)%2!=0;
        if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEffectsDescription,objects[0],a,embedded,socketed);else autotest::invoke(out,&originalEffectsDescription,objects[0],a,embedded,socketed);}
        else {std::wstring result=ours?objects[0]->effectsDescription(a,embedded,socketed):originalEffectsDescription(objects[0],a,embedded,socketed);text(result);}
        number(100+repeat);number(visualCalls);number(objects[0]->m_SocketedEquipment.size());
        for(unsigned i=0;i<4;++i){number(managerID(objects[i]->m_pEffectManager));number(objects[i]->m_ElementalDamageTypes.size());for(unsigned j=0;j<objects[i]->m_ElementalDamageTypes.size();++j){number(objects[i]->m_ElementalDamageTypes[j]);number(objects[i]->m_ElementalDamageBonuses[j]);number(objects[i]->m_InherentElementalDamage[j]);}}
    }
    for(unsigned id=0;id<4;++id){
        CEquipment* o=objects[id];Snapshot state(o,sizeof(*o));
        state.pointer(__builtin_offsetof(CEquipment,m_pEffectManager),managerID(o->m_pEffectManager)+2);
        state.array(__builtin_offsetof(CEquipment,m_ElementalDamageTypes),o->m_ElementalDamageTypes);
        state.array(__builtin_offsetof(CEquipment,m_ElementalDamageBonuses),o->m_ElementalDamageBonuses);
        state.array(__builtin_offsetof(CEquipment,m_InherentElementalDamage),o->m_InherentElementalDamage);
        state.pointer(__builtin_offsetof(CEquipment,m_SocketedEquipment),o->m_SocketedEquipment.m_pData?1:0);
        for(unsigned j=0;j<o->m_SocketedEquipment.size();++j)number(objectID(o->m_SocketedEquipment.m_pData[j]));
        state.emit();text(descriptions[id]);
    }
    Snapshot gs(globals,sizeof(*globals));gs.pointer(__builtin_offsetof(CGameGlobals,m_sGlobalsString2B8),1);gs.emit();text(globals->m_sGlobalsString2B8);capture->add(services,sizeof(services));
    patches.restore();typedef std::wstring Text;globals->m_sGlobalsString2B8.~Text();
    for(int i=0;i<4;++i){objects[i]->m_ElementalDamageTypes.~Types();objects[i]->m_ElementalDamageBonuses.~Ints();objects[i]->m_InherentElementalDamage.~Ints();objects[i]->m_SocketedEquipment.~TArrayList<CEquipment*>();}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_effects_description_differential){
    autotest::Coverage coverage("equipment_effects_description_differential",(uint64_t)(uintptr_t)&originalEffectsDescription);unsigned count=0;
    for(unsigned n=0;n<1680;++n)for(unsigned warm=0;warm<2;++warm)for(unsigned limited=0;limited<2;++limited){Case c={n<840?n:120+(n-840)%120,n<840?0u:1+(n-840)/120,warm,limited};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);++count;
        int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    effects description %u mode %u warm %u limited %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,c.warm,c.limited,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    equipment effects description: %u completed cold/warm and capacity cases\n",count);return 0;
}
