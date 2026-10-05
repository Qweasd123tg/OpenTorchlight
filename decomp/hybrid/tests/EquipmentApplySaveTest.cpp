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
#include "ResourceManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentApply,(CEquipment*,CItemSaveState&),"_ZN10CEquipment14applySaveStateER14CItemSaveState")
TL_FUNCTION(apSelf,"_ZN10CEquipment14applySaveStateER14CItemSaveState")
TL_FUNCTION(apBase,"_ZN5CItem14applySaveStateER14CItemSaveState")
TL_FUNCTION(apCreate,"_ZN16CResourceManager10createUnitExibb")
TL_FUNCTION(apContainer,"_ZN10CEquipment16addContainerItemEPS_")
TL_FUNCTION(apEffect,"_ZN9CBaseUnit12addNewEffectEP7CEffect")
TL_FUNCTION(apActivate,"_ZN9CBaseUnit14activateEffectEP7CEffect")
TL_FUNCTION(apCalculate,"_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(apDamage,"_ZN10CEquipment14addDamageBonusE13EDAMAGE_TYPESi")
TL_FUNCTION(apElements,"_ZN10CEquipment22createElementalDamagesEv")
TL_FUNCTION(apPrice,"_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(apRequirements,"_ZN10CEquipment15setRequirementsEv")
extern "C" void* applyEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,graph,effects,damage,base,flags,mode;};
struct World;World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
struct World{
 Raw<CEquipment> items[4];Raw<CEffectManager> managers[4];Raw<CResourceManager> resources;void* tables[4][112];CItemSaveState state;std::vector<CEffect*> effects;CEffect* returned;unsigned effectCalls,creates;bool changed;CItemSaveState* active;
 World(bool ours):returned(NULL),effectCalls(0),creates(0),changed(false),active(NULL){for(unsigned i=0;i<4;++i){CEquipment* p=items[i].get();std::memcpy(tables[i],applyEquipmentTable,sizeof(tables[i]));tables[i][85]=ours?apSelf_linked:apSelf_original;void** t=tables[i]+2;std::memcpy(p,&t,sizeof(t));new(&p->m_sPrefix)std::wstring(L"before prefix");new(&p->m_sSuffix)std::wstring(L"before suffix");new(&p->m_SocketedEquipment)TArrayList<CEquipment*>;new(&p->m_ElementalDamageTypes)std::vector<EDAMAGE_TYPES>;new(&p->m_ElementalDamageBonuses)std::vector<int>;new(&p->m_InherentElementalDamage)std::vector<int>;p->m_pResourceManager=resources.get();p->m_pEffectManager=input->flags&1?managers[i].get():NULL;p->m_iMinimumDamage=17+i;p->m_iMaximumDamage=29+i;p->m_iUnknown340=37+i;p->m_iUnknown338=43+i;p->m_iUnknown33C=59+i;for(unsigned j=0;j<input->damage;++j){p->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(j+1));p->m_ElementalDamageBonuses.push_back(88+j);p->m_InherentElementalDamage.push_back(77+j);}}
 initialize(state,0);for(unsigned i=0;i<input->graph;++i){CItemSaveState* child=new CItemSaveState;initialize(*child,i+1);child->m_iUnitValue60=input->flags&2&&i==0?-1LL:100LL+i;state.m_SocketedItems.push_back(child);}
 for(unsigned a=0;a<3;++a)for(unsigned j=0;j<(input->effects+a)%4;++j){CEffect* e=makeEffect(10+a*4+j);state.m_Effects[a].push_back(e);}returned=makeEffect(99);
 }
 CEffect* makeEffect(unsigned id){CEffect* e=new CEffect(static_cast<EEFFECT_TYPE>(0),false,static_cast<EEFFECT_ACTIVATION>(0),2,2,1,false);e->m_sName=L"effect";e->m_sName+=wchar_t(L'A'+id);e->m_fValueC0=13.5f+id;effects.push_back(e);return e;}
 void initialize(CItemSaveState& s,unsigned i){s.m_sStateString18=L"saved prefix";s.m_sStateString18+=wchar_t(L'A'+i);s.m_sStateString20=L"saved suffix";s.m_sStateString20+=wchar_t(L'A'+i);s.m_iStateValue28=-7+i;s.m_iStackSize=12+i;s.m_iStateValue6C=51+i;s.m_iSocketCount=3+i;s.m_bIdentified=(input->flags&4)!=0;static const int values[]={-1,0,1,137};s.m_iBaseDamage=values[input->base%4];s.m_iBaseArmor=values[(input->base/4)%4];for(unsigned j=0;j<input->damage;++j){s.m_DamageTypes.push_back(static_cast<EDAMAGE_TYPES>(j+2));s.m_DamageBonuses.push_back(int(i*10+j)-9);}}
 ~World(){for(unsigned i=0;i<effects.size();++i)delete effects[i];for(unsigned i=0;i<4;++i){CEquipment* p=items[i].get();typedef std::wstring Text;p->m_sPrefix.~Text();p->m_sSuffix.~Text();p->m_SocketedEquipment.~TArrayList<CEquipment*>();p->m_ElementalDamageTypes.~vector<EDAMAGE_TYPES>();p->m_ElementalDamageBonuses.~vector<int>();p->m_InherentElementalDamage.~vector<int>();}}
 unsigned id(CEquipment* p){for(unsigned i=0;i<4;++i)if(p==items[i].get())return i;_exit(51);return 9;}
};
void base(CItem* p,CItemSaveState& state){unsigned i=world->id(static_cast<CEquipment*>(p));number(10);number(i);world->active=&state;if(input->mode==1){state.m_iStackSize+=2;state.m_iBaseDamage=81;}if(input->mode==2&&i==0)world->items[i].get()->m_pEffectManager=world->managers[i].get();}
CBaseUnit* create(CResourceManager* p,long long guid,int level,bool first,bool second){number(11);number(p==world->resources.get());number(guid);number(level);number(first);number(second);++world->creates;if(input->mode==7&&!world->changed){world->changed=true;CItemSaveState* replacement=new CItemSaveState;world->initialize(*replacement,3);replacement->m_iUnitValue60=guid;delete world->state.m_SocketedItems[0];world->state.m_SocketedItems[0]=replacement;}if(guid<100||guid>102)_exit(52);return world->items[1+guid-100].get();}
void container(CEquipment* p,CEquipment* child){number(12);number(world->id(p));number(world->id(child));p->m_SocketedEquipment.add(child);if(input->mode==3&&!world->changed){world->changed=true;CItemSaveState* extra=new CItemSaveState;world->initialize(*extra,3);extra->m_iUnitValue60=102;world->state.m_SocketedItems.push_back(extra);}}
CEffect* addEffect(CBaseUnit* p,CEffect* effect){number(13);number(world->id(static_cast<CEquipment*>(p)));for(unsigned a=0;a<3;++a)number(world->state.m_Effects[a].size());if(input->mode==8)static_cast<CEquipment*>(p)->m_pEffectManager=world->managers[0].get();text(effect->m_sName);real(effect->m_fValueC0);++world->effectCalls;if(input->mode==4&&!world->changed){world->changed=true;world->state.m_Effects[0].push_back(world->makeEffect(77));}effect->m_fValueC0=-91.0f;if(input->flags&8&&world->effectCalls%2==1)return NULL;return input->flags&16?world->returned:effect;}
void activate(CBaseUnit* p,CEffect* effect){number(14);number(world->id(static_cast<CEquipment*>(p)));text(effect->m_sName);real(effect->m_fValueC0);}
void calculate(CEffectManager* p){unsigned i=0;while(i<4&&p!=world->managers[i].get())++i;number(15);number(i);if(i>=4)_exit(53);if(input->mode==5)world->items[i].get()->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(8));}
void damage(CEquipment* p,EDAMAGE_TYPES type,int amount){number(16);number(world->id(p));number(type);number(amount);number(p->m_ElementalDamageBonuses.size());for(unsigned j=0;j<p->m_ElementalDamageBonuses.size();++j)number(p->m_ElementalDamageBonuses[j]);unsigned i=0;while(i<p->m_ElementalDamageTypes.size()&&p->m_ElementalDamageTypes[i]!=type)++i;if(i==p->m_ElementalDamageTypes.size()){p->m_ElementalDamageTypes.push_back(type);p->m_ElementalDamageBonuses.push_back(amount);}else p->m_ElementalDamageBonuses[i]+=amount;if(input->mode==6&&!world->changed){world->changed=true;world->active->m_DamageTypes.push_back(static_cast<EDAMAGE_TYPES>(9));world->active->m_DamageBonuses.push_back(72);}}
void elements(CEquipment* p){number(17);number(world->id(p));number(p->m_ElementalDamageBonuses.size());}
void price(CEquipment* p){number(18);number(world->id(p));}
void requirements(CEquipment* p){number(19);number(world->id(p));}
void snapshot(World& w){for(unsigned i=0;i<4;++i){CEquipment* p=w.items[i].get();number(p->m_iUnknown28C);number(p->m_iUnknown238);number(p->m_bUnknown348);text(p->m_sPrefix);text(p->m_sSuffix);number(p->m_iUnknown344);number(p->m_iSocketCount);number(p->m_iMinimumDamage);number(p->m_iMaximumDamage);number(p->m_iUnknown340);number(p->m_iUnknown338);number(p->m_iUnknown33C);number(p->m_SocketedEquipment.size());for(unsigned j=0;j<p->m_SocketedEquipment.size();++j)number(w.id(p->m_SocketedEquipment[j]));number(p->m_ElementalDamageTypes.size());for(unsigned j=0;j<p->m_ElementalDamageTypes.size();++j)number(p->m_ElementalDamageTypes[j]);number(p->m_ElementalDamageBonuses.size());for(unsigned j=0;j<p->m_ElementalDamageBonuses.size();++j)number(p->m_ElementalDamageBonuses[j]);}for(unsigned a=0;a<3;++a)number(w.state.m_Effects[a].size());number(w.effectCalls);number(w.creates);for(unsigned i=0;i<w.effects.size();++i)real(w.effects[i]->m_fValueC0);}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w(ours);world=&w;detour::Set patches;TL_REDIRECT(patches,apBase,&base);TL_REDIRECT(patches,apCreate,&create);TL_REDIRECT(patches,apContainer,&container);TL_REDIRECT(patches,apEffect,&addEffect);TL_REDIRECT(patches,apActivate,&activate);TL_REDIRECT(patches,apCalculate,&calculate);TL_REDIRECT(patches,apDamage,&damage);TL_REDIRECT(patches,apElements,&elements);TL_REDIRECT(patches,apPrice,&price);TL_REDIRECT(patches,apRequirements,&requirements);if(patches.failed())_exit(42);for(unsigned repeat=0;repeat<2;++repeat){if(ours)w.items[0].get()->applySaveState(w.state);else originalEquipmentApply(w.items[0].get(),w.state);snapshot(w);}patches.restore();}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_applysave_differential){int failures=0;for(unsigned n=0;n<8960;++n){Case c={n,n%4,(n/4)%4,(n/16)%4,(n/64)%16,(n/256)%32,0};if(n>=8192){unsigned j=n-8192;c.mode=1+(j/64)%6;c.graph=1;c.effects=1;c.damage=2;c.flags=1+j%32;}if(n>=8704){unsigned j=n-8704;c.graph=1;c.effects=1;c.damage=2;c.flags=(j%16)*2;c.mode=7+j/128;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    apply save case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment apply save: 8960 cases, two calls per side\n");return failures;}
