#include <cstring>
#include <new>
#include <vector>
#include <string>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "ItemSaveState.h"
#include "Effect.h"
#include "EffectManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentSave,(CEquipment*,CItemSaveState&,int,bool),"_ZN10CEquipment13fillSaveStateER14CItemSaveStateib")
TL_FUNCTION(svCopy,"_ZN7CEffectC1EPKS_")
TL_FUNCTION(svOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
TL_FUNCTION(svSkill,"_ZN7CEffect13setSkillOwnerEP6CSkill")
TL_FUNCTION(svSelf,"_ZN10CEquipment13fillSaveStateER14CItemSaveStateib")
TL_FUNCTION(svBase,"_ZN5CItem13fillSaveStateER14CItemSaveStateib")
TL_FUNCTION(svIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(svName,"_ZN10CEquipment15getFullItemNameEb")
TL_FUNCTION(svElements,"_ZN10CEquipment22createElementalDamagesEv")
TL_FUNCTION(svClear,"_ZN14CEffectManager20clearOutAffixEffectsEv")
TL_FUNCTION(svRestore,"_ZN14CEffectManager21addAffixEffectsBackInEv")
extern "C" void* saveEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void tracedoriginalEquipmentSave(CEquipment*,CItemSaveState&,int,bool) __asm__("_ZN10CEquipment13fillSaveStateER14CItemSaveStateib");
typedef void (*SaveInvocation)(CEquipment*,CItemSaveState&,int,bool);
namespace {
typedef char state_size[sizeof(CItemSaveState)==0x180?1:-1];
typedef char state_effects[__builtin_offsetof(CItemSaveState,m_Effects)==0xe0?1:-1];
typedef char state_sockets[__builtin_offsetof(CItemSaveState,m_SocketedItems)==0x128?1:-1];
typedef char effect_value[__builtin_offsetof(CEffect,m_fValueC0)==0xc0?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,kind,graph,effects,elements,flags,mode;};
struct World;World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
TArrayList<CEffect*>* lists(CEffectManager* p){return reinterpret_cast<TArrayList<CEffect*>*>(p->m_EffectData10+0x18);}
struct World{
 Raw<CEquipment> items[4];Raw<CEffectManager> managers[2];void* tables[4][110];std::vector<CEffect*> sources;bool enabled[4];unsigned kind[4],calls[4];bool changed;
 World(bool ours):changed(false){for(unsigned m=0;m<2;++m)for(unsigned a=0;a<4;++a)new(lists(managers[m].get())+a)TArrayList<CEffect*>;
 for(unsigned i=0;i<4;++i){CEquipment* p=items[i].get();std::memcpy(tables[i],saveEquipmentTable+2,sizeof(tables[i]));tables[i][82]=ours?svSelf_linked:svSelf_original;void** t=tables[i];std::memcpy(p,&t,sizeof(t));new(&p->m_sPrefix)std::wstring(L"old prefix");new(&p->m_sSuffix)std::wstring(L"old suffix");new(&p->m_SocketedEquipment)TArrayList<CEquipment*>;new(&p->m_ElementalDamageTypes)std::vector<EDAMAGE_TYPES>;new(&p->m_ElementalDamageBonuses)std::vector<int>;enabled[i]=(input->flags&1)!=0;kind[i]=(input->kind+i)%4;calls[i]=0;p->m_iUnknown28C=-30+i;p->m_iUnknown238=7+i;p->m_iUnknown344=81+i;p->m_iSocketCount=2+i;p->m_iUnknown33C=110+i;p->m_iUnknown340=210+i;p->m_bUnknown348=(input->flags&2)!=0;p->m_bUnknown25C=(input->flags&4)!=0;p->m_pEffectManager=input->effects?managers[i%2].get():NULL;}
 for(unsigned m=0;m<2;++m)for(unsigned a=0;a<4;++a)for(unsigned j=0;j<(a==3?1:(input->effects+a)%4);++j){CEffect* e=new CEffect(static_cast<EEFFECT_TYPE>(0),false,static_cast<EEFFECT_ACTIVATION>(a%3),3.0f,3.0f,1.0f,false);e->m_sName=L"effect";e->m_sName+=wchar_t(L'A'+m*12+a*4+j);e->m_fValueC0=17.25f+m*100+a*10+j;sources.push_back(e);lists(managers[m].get())[a].add(e);}
 if(input->graph){items[0].get()->m_SocketedEquipment.add(items[1].get());if(input->graph>=2)items[0].get()->m_SocketedEquipment.add(items[2].get());if(input->graph>=3)items[1].get()->m_SocketedEquipment.add(items[3].get());}
 }
 ~World(){for(unsigned i=0;i<sources.size();++i)delete sources[i];for(unsigned m=0;m<2;++m)for(unsigned a=0;a<4;++a)lists(managers[m].get())[a].~TArrayList<CEffect*>();for(unsigned i=0;i<4;++i){CEquipment* p=items[i].get();typedef std::wstring Text;p->m_sPrefix.~Text();p->m_sSuffix.~Text();p->m_SocketedEquipment.~TArrayList<CEquipment*>();p->m_ElementalDamageTypes.~vector<EDAMAGE_TYPES>();p->m_ElementalDamageBonuses.~vector<int>();}}
 unsigned id(CEquipment* p){for(unsigned i=0;i<4;++i)if(p==items[i].get())return i;_exit(51);return 9;}
};
bool enabled(CEquipment* p){unsigned i=world->id(p);number(10);number(i);return world->enabled[i];}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){unsigned i=world->id(static_cast<CEquipment*>(p));number(11);number(i);number(t);return t==UNITTYPES::SOCKETABLE?(world->kind[i]&1)!=0:t==UNITTYPES::RANDOMMAGIC_SOCKETABLE?(world->kind[i]&2)!=0:false;}
void base(CItem* item,CItemSaveState& state,int index,bool flag){unsigned i=world->id(static_cast<CEquipment*>(item));number(12);number(i);number(index);number(flag);state.m_iIndex=index;state.m_bSaveFlag5C=flag;state.m_bEnabled=(input->flags&8)!=0;state.m_sItemName=L"base";state.m_iOriginalGuid=123400+i;++world->calls[i];if(input->mode==1)world->kind[i]^=3;if(input->mode==2){CEquipment* p=world->items[i].get();p->m_pEffectManager=world->managers[1].get();p->m_iUnknown238+=3;}if(input->mode==3&&i==1&&world->calls[i]==1)world->items[0].get()->m_SocketedEquipment.add(world->items[3].get());}
std::wstring fullname(CEquipment* p,bool flag){unsigned i=world->id(p);number(13);number(i);number(flag);p->m_sPrefix=L"cached prefix";p->m_sPrefix+=wchar_t(L'A'+i);p->m_sSuffix=flag?L"cached suffix":L"wrong";return L"discarded full name";}
void elements(CEquipment* p){unsigned i=world->id(p);number(14);number(i);p->m_ElementalDamageTypes.clear();p->m_ElementalDamageBonuses.clear();for(unsigned j=0;j<input->elements;++j){p->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(j+1));p->m_ElementalDamageBonuses.push_back(-11+int(i*10+j*7));}}
void clear(CEffectManager* p){number(15);number(p==world->managers[1].get());}
void restore(CEffectManager* p){number(16);number(p==world->managers[1].get());}
detour::Set ownerPatch,skillPatch,copyPatch;CEffect* activeClone;const CEffect* cloneSource;
void copy(CEffect* target,const CEffect* source){activeClone=NULL;copyPatch.restore();reinterpret_cast<void(*)(CEffect*,const CEffect*)>(svCopy_original)(target,source);TL_REDIRECT(copyPatch,svCopy,&copy);activeClone=target;cloneSource=source;}
void callback(CEffect* effect){if(effect!=activeClone||world->changed||input->mode<4)return;world->changed=true;for(unsigned m=0;m<2;++m)for(unsigned a=0;a<3;++a){TArrayList<CEffect*>& list=lists(world->managers[m].get())[a];for(unsigned j=0;j<list.size();++j)if(list[j]==cloneSource){if(input->mode==4)list[j]->m_fValueC0+=73.5f;if(input->mode==5)list.add(lists(world->managers[m].get())[3][0]);if(input->mode==6)world->items[0].get()->m_pEffectManager=world->managers[1-m].get();if(input->mode==7)list[j]=lists(world->managers[m].get())[3][0];return;}}}

void owner(CEffect* effect,CBaseUnit* unit,bool recalculate){number(17);number(unit==NULL);number(recalculate);ownerPatch.restore();reinterpret_cast<void(*)(CEffect*,CBaseUnit*,bool)>(svOwner_original)(effect,unit,recalculate);TL_REDIRECT(ownerPatch,svOwner,&owner);}
void skill(CEffect* effect,CSkill* unit){number(18);number(unit==NULL);skillPatch.restore();reinterpret_cast<void(*)(CEffect*,CSkill*)>(svSkill_original)(effect,unit);TL_REDIRECT(skillPatch,svSkill,&skill);callback(effect);}
void snapshot(const CItemSaveState& s,unsigned depth=0){if(depth>4)_exit(52);text(s.m_sItemName);text(s.m_sStateString18);text(s.m_sStateString20);number(s.m_iOriginalGuid);number(s.m_iIndex);number(s.m_bSaveFlag5C);number(s.m_bEnabled);number(s.m_iStateValue28);number(s.m_iStackSize);number(s.m_iStateValue6C);number(s.m_iSocketCount);number(s.m_bIdentified);number(s.m_iBaseDamage);number(s.m_iBaseArmor);for(unsigned a=0;a<3;++a){number(s.m_Effects[a].size());for(unsigned j=0;j<s.m_Effects[a].size();++j){CEffect* e=s.m_Effects[a][j];text(e->m_sName);number(e->m_eType);real(e->m_fValueC0);void* owner;std::memcpy(&owner,reinterpret_cast<char*>(e)+0x48,8);number(owner==NULL);std::memcpy(&owner,reinterpret_cast<char*>(e)+0x68,8);number(owner==NULL);}}number(s.m_SocketedItems.size());for(unsigned j=0;j<s.m_SocketedItems.size();++j)snapshot(*s.m_SocketedItems[j],depth+1);number(s.m_DamageTypes.size());for(unsigned j=0;j<s.m_DamageTypes.size();++j)number(s.m_DamageTypes[j]);number(s.m_DamageBonuses.size());for(unsigned j=0;j<s.m_DamageBonuses.size();++j)number(s.m_DamageBonuses[j]);}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w(ours);world=&w;CItemSaveState saved;saved.m_DamageTypes.push_back(static_cast<EDAMAGE_TYPES>(9));saved.m_DamageBonuses.push_back(999);for(unsigned i=0;i<4;++i)w.tables[i][9]=reinterpret_cast<void*>(&enabled);detour::Set patches;TL_REDIRECT(patches,svIsa,&isa);TL_REDIRECT(patches,svBase,&base);TL_REDIRECT(patches,svName,&fullname);TL_REDIRECT(patches,svElements,&elements);TL_REDIRECT(patches,svClear,&clear);TL_REDIRECT(patches,svRestore,&restore);activeClone=NULL;cloneSource=NULL;TL_REDIRECT(copyPatch,svCopy,&copy);TL_REDIRECT(ownerPatch,svOwner,&owner);TL_REDIRECT(skillPatch,svSkill,&skill);if(copyPatch.failed()||patches.failed()||ownerPatch.failed()||skillPatch.failed())_exit(42);for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke<SaveInvocation,CEquipment*,CItemSaveState&,int,bool>(out,ours?&tracedoriginalEquipmentSave:&originalEquipmentSave,w.items[0].get(),saved,int(c.id%5)-2,(c.id&1)!=0);}else{if(ours)w.items[0].get()->fillSaveState(saved,int(c.id%5)-2,(c.id&1)!=0);else originalEquipmentSave(w.items[0].get(),saved,int(c.id%5)-2,(c.id&1)!=0);}snapshot(saved);for(unsigned i=0;i<4;++i){number(w.calls[i]);text(w.items[i].get()->m_sPrefix);text(w.items[i].get()->m_sSuffix);}}copyPatch.restore();ownerPatch.restore();skillPatch.restore();patches.restore();}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_save_differential){
autotest::Coverage coverage0("equipment_save_differential",(uint64_t)(uintptr_t)&originalEquipmentSave);
int failures=0;for(unsigned n=0;n<5120;++n){Case c={n,n%4,(n/4)%4,(n/16)%4,(n/64)%4,(n/256)%16,0};if(n>=4096){unsigned j=n-4096;c.kind=j%4;c.graph=1+(j/4)%3;c.effects=(j/16)%4;c.elements=(j/64)%4;c.flags=(j/4)%16;c.mode=1+(j/128)%3;}if(n>=4608){unsigned j=n-4608;c.graph=0;c.effects=1+j%3;c.mode=4+j/128;c.flags=j%16;c.kind=j%4;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    save case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    equipment save: 5120 cases, two calls per side\n");{coverage0.report(host);return failures;}}
