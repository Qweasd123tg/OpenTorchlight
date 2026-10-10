#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#include "GameGlobals.h"
#include "ResourceManager.h"
#include "DataGroup.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentEnchant,(CEquipment*,bool),"_ZN10CEquipment7enchantEb")
TL_FUNCTION(enBool,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(enIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(enGlobals,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(enRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(enInteger,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(enAffixes,"_ZN16CResourceManager20createAffixesForUnitEP9CBaseUnitjj")
TL_FUNCTION(enPrice,"_ZN10CEquipment16recalculatePriceEv")
extern "C" void tracedoriginalEquipmentEnchant(CEquipment*,bool) __asm__("_ZN10CEquipment7enchantEb");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,classification,category,manager,flags,rolls,mode;};
struct World{Raw<CEquipment> item;Raw<CEffectManager> manager;Raw<CResourceManager> resources;Raw<CGameGlobals> globals[2];unsigned randomCalls,integerCalls,globalCalls,affixCalls,priceCalls;unsigned classification,category;World():randomCalls(0),integerCalls(0),globalCalls(0),affixCalls(0),priceCalls(0){}};
World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(10);number(p==world->item.get());number(t);if(t==UNITTYPES::UNIQUE)return (world->classification&1)!=0;if(t==UNITTYPES::MAGIC)return (world->classification&2)!=0;if(t==UNITTYPES::RANDOMMAGIC)return (world->classification&4)!=0;return t==UNITTYPES::WEAPON?world->category==1:t==UNITTYPES::ARMOR?world->category==2:t==UNITTYPES::RING?world->category==3:t==UNITTYPES::RANDOMMAGIC_SOCKETABLE?world->category==4:t==UNITTYPES::NECKLACE?world->category==5:false;}
CGameGlobals* globals(){number(11);unsigned index=input->mode==4?world->globalCalls%2:0;++world->globalCalls;number(index);return world->globals[index].get();}
float random(float minimum,float maximum){number(12);real(minimum);real(maximum);static const float samples[]={0,249.99998f,250,250.00002f,499.99997f,500,749.99994f,750,999.99994f,1000};unsigned idx=(input->rolls+world->randomCalls*3)%10;++world->randomCalls;float value=samples[idx];if(input->mode==5){unsigned bits=0x7fc00000;std::memcpy(&value,&bits,4);}if(input->mode==6&&world->randomCalls==1)world->category=5;real(value);return value;}
int integer(int minimum,int maximum){number(13);number(minimum);number(maximum);++world->integerCalls;return minimum+int(world->integerCalls%3);}
void affixes(CResourceManager* resources,CBaseUnit* unit,unsigned level,unsigned count){number(14);number(resources==world->resources.get());number(unit==world->item.get());number(level);number(count);number(world->item.get()->m_bUnknown348);++world->affixCalls;if(input->mode==1){world->item.get()->m_iUnknown274+=2;unsigned v=1;std::memcpy(world->manager.get()->m_EffectData10+0x20,&v,4);}if(input->mode==2)world->classification^=1;if(input->mode==3)world->item.get()->m_iSocketCount=2;}
void price(CEquipment* p){number(15);number(p==world->item.get());number(p->m_bUnknown348);number(p->m_iSocketCount);++world->priceCalls;}
detour::Set boolPatch;
bool boolean(CDataGroup* data,const std::wstring& key,bool defaultValue){number(16);number(data==world->item.get()->m_pDataGroup);number(key==L"ALWAYS_IDENTIFIED");number(defaultValue);boolPatch.restore();bool result=reinterpret_cast<bool(*)(CDataGroup*,const std::wstring&,bool)>(enBool_original)(data,key,defaultValue);TL_REDIRECT(boolPatch,enBool,&boolean);return result;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.classification=c.classification;w.category=c.category;CEquipment* p=w.item.get();p->m_pEffectManager=c.manager?w.manager.get():NULL;unsigned affixCount=c.manager&1?0:3,passiveCount=c.manager&2?4:0;std::memcpy(w.manager.get()->m_EffectData10+8,&affixCount,4);std::memcpy(w.manager.get()->m_EffectData10+0x20,&passiveCount,4);p->m_bItemFlag20A=(c.flags&1)!=0;p->m_bUnknown348=(c.flags&2)!=0;p->m_iSocketCount=c.flags&4?3:0;p->m_iUnknown274=3+c.id%37;p->m_pResourceManager=c.mode==7?NULL:w.resources.get();w.resources.get()->m_pLevel=c.flags&8?reinterpret_cast<CLevel*>(w.manager.get()):NULL;CDataGroup data(L"ITEM",0,4,4,0);p->m_pDataGroup=&data;if(c.flags&16)data.AddDataValue(L"ALWAYS_IDENTIFIED",true);
 for(unsigned i=0;i<2;++i){CGameGlobals* g=w.globals[i].get();g->m_fRandomEnchantChance=25.0f+i;g->m_fRandomSocketChance=50.0f+i;g->m_fSecondSocketChance=75.0f+i;g->m_iMinRandomEnchantSlots=2+i*10;g->m_iMaxRandomEnchantSlots=5+i*10;g->m_iMinMagicItemSlots=12+i*10;g->m_iMaxMagicItemSlots=15+i*10;g->m_iMinUniqueItemSlots=22+i*10;g->m_iMaxUniqueItemSlots=25+i*10;}
 detour::Set patches;TL_REDIRECT(patches,enIsa,&isa);TL_REDIRECT(patches,enGlobals,&globals);TL_REDIRECT(patches,enRandom,&random);TL_REDIRECT(patches,enInteger,&integer);TL_REDIRECT(patches,enAffixes,&affixes);TL_REDIRECT(patches,enPrice,&price);TL_REDIRECT(boolPatch,enBool,&boolean);if(patches.failed()||boolPatch.failed())_exit(42);for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalEquipmentEnchant:&originalEquipmentEnchant,p,(c.flags&32)!=0);}else{if(ours)p->enchant((c.flags&32)!=0);else originalEquipmentEnchant(p,(c.flags&32)!=0);}number(p->m_bUnknown348);number(p->m_iSocketCount);number(p->m_iUnknown274);number(w.randomCalls);number(w.integerCalls);number(w.globalCalls);number(w.affixCalls);number(w.priceCalls);}boolPatch.restore();}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_enchant_differential){
autotest::Coverage coverage0("equipment_enchant_differential",(uint64_t)(uintptr_t)&originalEquipmentEnchant);
int failures=0;for(unsigned n=0;n<13120;++n){Case c={n,n%8,(n/8)%6,(n/48)%4,(n/192)%64,(n/7)%10,0};if(n>=12288){unsigned j=n-12288;c.classification=j%8;c.category=1+(j/8)%5;c.manager=1+(j/40)%3;c.flags=9+(j%2?32:0);c.mode=1+j/128;}if(n>=13056){c.classification=0;c.category=0;c.flags=n%64;c.mode=7;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    enchant case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    equipment enchant: 13120 cases, two calls per side\n");{coverage0.report(host);return failures;}}
