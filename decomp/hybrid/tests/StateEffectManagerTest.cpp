#include <cstring>
#include <string>
#include <vector>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "EffectManager.h"
#include "Effect.h"
#include "Affix.h"
#include "DataGroup.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oClear,nClear,(void*),"_ZN14CEffectManager20clearOutDescriptionsEv")
DECL(void,oRecalc,nRecalc,(void*),"_ZN14CEffectManager18recalculateEffectsEv")
DECL(void,oAffClear,nAffClear,(void*),"_ZN14CEffectManager20clearOutAffixEffectsEv")
DECL(void,oAffBack,nAffBack,(void*),"_ZN14CEffectManager21addAffixEffectsBackInEv")
DECL(void,oUnsaved,nUnsaved,(void*),"_ZN14CEffectManager21removeNonSavedEffectsEv")
DECL(void,oClones,nClones,(void*,void*,TArrayList<CEffect*>*),"_ZN14CEffectManager12cloneEffectsEP9CBaseUnitP10TArrayListIP7CEffectE")
DECL(void*,oAdd,nAdd,(void*,void*,unsigned,void*,float),"_ZN14CEffectManager8addAffixEP6CAffixjP9CBaseUnitf")
DECL(bool,oDelete,nDelete,(void*,void*),"_ZN14CEffectManager11deleteAffixEP6CAffix")
DECL(bool,oDeleteName,nDeleteName,(void*,const std::wstring&),"_ZN14CEffectManager11deleteAffixERKSbIwSt11char_traitsIwESaIwEE")
DECL(void,oUpdate,nUpdate,(void*,float),"_ZN14CEffectManager13updateAffixesEf")
DECL(bool,oRemove,nRemove,(void*,void*,bool),"_ZN14CEffectManager12removeEffectEP7CEffectb")
DECL(unsigned,oCreate,nCreate,(void*,void*,bool),"_ZN14CEffectManager13createEffectsEP10CDataGroupb")
DECL(void*,oClone,nClone,(void*,void*,void*),"_ZN14CEffectManager11cloneEffectEP9CBaseUnitP7CEffect")
#undef DECL
TL_FUNCTION(effectMaximum,"_ZN7CEffect20getMaxCaculatedValueEv")
TL_FUNCTION(affixClear,"_ZN6CAffix21clearEffectsFromOwnerEv")
TL_FUNCTION(affixBack,"_ZN6CAffix25addEffectsToEffectManagerEP14CEffectManager")
TL_FUNCTION(effectCalculate,"_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(effectDead,"_ZN14CEffectManager17deleteDeadEffectsEv")
TL_FUNCTION(affixLevel,"_ZN6CAffix8setLevelEj")
TL_FUNCTION(affixOwner,"_ZN6CAffix8setOwnerEP9CBaseUnit")
TL_FUNCTION(affixDuration,"_ZN6CAffix19updateAffixDurationEf")
TL_FUNCTION(singleClone,"_ZN14CEffectManager11cloneEffectEP9CBaseUnitP7CEffect")
TL_FUNCTION(groupName,"_ZN10CDataGroup12GetGroupNameEv")
TL_FUNCTION(groupMatches,"_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
TL_FUNCTION(singleCreate,"_ZN14CEffectManager12createEffectEP10CDataGroupb")
TL_FUNCTION(effectCopy,"_ZN7CEffectC1EPKS_")
TL_FUNCTION(effectOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
TL_FUNCTION(effectAdd,"_ZN14CEffectManager12addNewEffectEP7CEffect")
TL_FUNCTION(effectActivate,"_ZN9CBaseUnit14activateEffectEP7CEffect")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;void*manager;void*source;void*made;void*objects[10];unsigned seed;std::wstring group;
int id(void*p){if(!p)return -1;for(int i=0;i<10;++i)if(objects[i]==p)return i;if(p==made)return 10;return -2;}
void event(unsigned kind,void*p){int identity=id(p);cap->add(&kind,4);cap->add(&identity,4);}
void maxValue(void*p){event(1,p);}void clearAffix(void*p){event(2,p);}void back(void*p,void*self){event(3,p);if(self!=manager)cap->issue=autotest::Capture::InvalidReport;}
void calculate(void*self){event(4,self);if(self!=manager)cap->issue=autotest::Capture::InvalidReport;}
void dead(void*self){event(5,self);if(self!=manager)cap->issue=autotest::Capture::InvalidReport;}
void level(void*p,unsigned v){event(6,p);cap->add(&v,4);}void owner(void*p,void*s){event(7,p);if(s!=source)cap->issue=autotest::Capture::InvalidReport;}
void destroy(void*p){event(8,p);}bool duration(void*p,float value){event(9,p);cap->add(&value,4);return ((id(p)+seed)%3)!=0;}
void*clone(void*self,void*s,void*e){event(10,e);if(self!=manager||s!=source)cap->issue=autotest::Capture::InvalidReport;return e;}
const std::wstring&name(void*){return group;}
unsigned matches(void*,const std::wstring&n,std::vector<CDataGroup*>*out){unsigned marker=11;cap->add(&marker,4);if(n!=L"EFFECT")cap->issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<seed%5;++i)out->push_back(reinterpret_cast<CDataGroup*>(objects[i]));return out->size();}
void create(void*self,void*p,bool flag){event(12,p);cap->add(&flag,1);if(self!=manager)cap->issue=autotest::Capture::InvalidReport;}
void copy(void*p,const void*s){made=p;event(13,const_cast<void*>(s));std::memset(p,0,sizeof(CEffect));}
void setEffectOwner(void*p,void*s,bool flag){event(14,p);cap->add(&flag,1);if(s!=source)cap->issue=autotest::Capture::InvalidReport;}
void*add(void*self,void*p){event(15,p);if(self!=manager)cap->issue=autotest::Capture::InvalidReport;return p;}
void activate(void*s,void*p){event(16,p);if(s!=source)cap->issue=autotest::Capture::InvalidReport;}
void text(autotest::Capture&o,const std::wstring&s){unsigned n=s.size();o.add(&n,4);if(n)o.add(s.data(),4*n);}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;made=NULL;
 uint64_t storage[(sizeof(CEffectManager)+7)/8],affixes[5][(sizeof(CAffix)+7)/8],effects[5][(sizeof(CEffect)+7)/8],unit[64];std::memset(storage,0xa5,sizeof(storage));std::memset(affixes,0x5a,sizeof(affixes));std::memset(effects,0x3c,sizeof(effects));CEffectManager*self=reinterpret_cast<CEffectManager*>(storage);manager=self;source=(seed&1)?unit:NULL;
 void*vt[2]={reinterpret_cast<void*>(&destroy),reinterpret_cast<void*>(&destroy)};
 const wchar_t*names[]={L"",L"A",L"AA",L"Ж"};float values[]={-900.0f,-1000.0f,-1.0f,0.0f,2.5f};
 for(unsigned i=0;i<5;++i){CAffix*a=reinterpret_cast<CAffix*>(affixes[i]);objects[5+i]=a;*reinterpret_cast<void***>(a)=vt;new(&a->m_sDisplayName)std::wstring(names[(i+seed/3)%4]);a->m_pEffectManager=seed&8?self:NULL;a->m_fDuration=-4.0f-i;CEffect*e=reinterpret_cast<CEffect*>(effects[i]);objects[i]=e;*reinterpret_cast<void***>(e)=vt;e->m_activation=static_cast<EEFFECT_ACTIVATION>((i+seed)%3);e->m_flag33=(seed+i)%2;e->m_bDead=false;e->m_fValue24=values[(i+seed/4)%5];e->m_fRemainingDuration=-3.0f-i;e->m_pAffixOwner=seed&4?reinterpret_cast<CAffix*>(objects[5]):NULL;}
 TArrayList<CAffix*>&as=self->getAffixes();new(&as)TArrayList<CAffix*>(1+(seed%3));for(unsigned i=0;i<seed%6;++i)as.add(static_cast<CAffix*>(objects[5+i]));
 for(unsigned g=0;g<3;++g){TArrayList<CEffect*>&ls=self->getActiveEffects(g);new(&ls)TArrayList<CEffect*>(2);for(unsigned i=0;i<5;++i)if(i<seed%6&&static_cast<CEffect*>(objects[i])->m_activation==g)ls.add(static_cast<CEffect*>(objects[i]));if(c.mode<6&&(seed&16)&&ls.m_nCount)ls.m_nCapacity=(seed/8)%2;}
 if(c.mode<6&&(seed&16)&&as.m_nCount)as.m_nCapacity=(seed/8)%2;
 new(&self->m_EffectString2E0)std::wstring(names[(seed/2)%4]);new(&self->m_EffectString2E8)std::wstring(L"second");new(&self->m_EffectString2F0)std::wstring(L"third");self->getOwnerReference().m_pObject=static_cast<CBaseUnit*>(source);self->getOwnerReference().m_nIndex=0;
 detour::Set patches;TL_REDIRECT(patches,effectMaximum,&maxValue);TL_REDIRECT(patches,affixClear,&clearAffix);TL_REDIRECT(patches,affixBack,&back);TL_REDIRECT(patches,effectCalculate,&calculate);TL_REDIRECT(patches,effectDead,&dead);TL_REDIRECT(patches,affixLevel,&level);TL_REDIRECT(patches,affixOwner,&owner);TL_REDIRECT(patches,affixDuration,&duration);
 if(c.mode==5)TL_REDIRECT(patches,singleClone,&clone);
 if(c.mode==11){TL_REDIRECT(patches,groupName,&name);TL_REDIRECT(patches,groupMatches,&matches);TL_REDIRECT(patches,singleCreate,&create);}
 if(c.mode==12){TL_REDIRECT(patches,effectCopy,&copy);TL_REDIRECT(patches,effectOwner,&setEffectOwner);TL_REDIRECT(patches,effectAdd,&add);TL_REDIRECT(patches,effectActivate,&activate);}
 if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode<5){void(*old[])(void*)={oClear,oRecalc,oAffClear,oAffBack,oUnsaved};void(*now[])(void*)={nClear,nRecalc,nAffClear,nAffBack,nUnsaved};void(*fn)(void*)=ours?now[c.mode]:old[c.mode];if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;}
 else if(c.mode==5){TArrayList<CEffect*>list(2);for(unsigned i=0;i<seed%6;++i)list.add(static_cast<CEffect*>(objects[i]));if((seed&16)&&list.m_nCount)list.m_nCapacity=(seed/8)%2;void(*fn)(void*,void*,TArrayList<CEffect*>*)=ours?nClones:oClones;if(!autotest::beginInvocation(out,fn))return;fn(self,source,seed%7==0?NULL:&list);out.callCompleted=1;}
 else if(c.mode==6){void*(*fn)(void*,void*,unsigned,void*,float)=ours?nAdd:oAdd;if(!autotest::beginInvocation(out,fn))return;void*target=seed%5==0?NULL:objects[9];float scale=values[(seed/3)%5];void*r=fn(self,target,seed&8?unsigned(-1):seed,source,scale);out.callCompleted=1;int identity=id(r);out.add(&identity,4);if(r!=target)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==7){bool(*fn)(void*,void*)=ours?nDelete:oDelete;if(!autotest::beginInvocation(out,fn))return;bool value=fn(self,objects[5+seed%5]);out.callCompleted=1;out.add(&value,1);}
 else if(c.mode==8){bool(*fn)(void*,const std::wstring&)=ours?nDeleteName:oDeleteName;std::wstring query=names[(seed/5)%4];if(!autotest::beginInvocation(out,fn))return;bool value=fn(self,query);out.callCompleted=1;out.add(&value,1);}
 else if(c.mode==9){void(*fn)(void*,float)=ours?nUpdate:oUpdate;if(!autotest::beginInvocation(out,fn))return;fn(self,values[(seed/5)%5]);out.callCompleted=1;}
 else if(c.mode==10){bool(*fn)(void*,void*,bool)=ours?nRemove:oRemove;if(!autotest::beginInvocation(out,fn))return;bool value=fn(self,objects[seed%5],(seed&1)!=0);out.callCompleted=1;out.add(&value,1);}
 else if(c.mode==11){group=seed&1?L"EFFECT":L"GROUP";unsigned(*fn)(void*,void*,bool)=ours?nCreate:oCreate;if(!autotest::beginInvocation(out,fn))return;unsigned value=fn(self,seed%7==0?NULL:objects[0],(seed&2)!=0);out.callCompleted=1;out.add(&value,4);unsigned wanted=seed%7==0?0:seed&1?1:seed%5;if(value!=wanted)out.issue=autotest::Capture::InvalidReport;}
 else{void*(*fn)(void*,void*,void*)=ours?nClone:oClone;if(!autotest::beginInvocation(out,fn))return;void*r=fn(self,source,objects[0]);out.callCompleted=1;int identity=id(r);out.add(&identity,4);if(r!=made&&r!=objects[0])out.issue=autotest::Capture::InvalidReport;if(made)CEffect::operator delete(made);}
 text(out,self->m_EffectString2E0);text(out,self->m_EffectString2E8);text(out,self->m_EffectString2F0);
 unsigned n=as.size();out.add(&n,4);for(unsigned i=0;i<n;++i){int identity=id(as.m_pData[i]);out.add(&identity,4);}for(unsigned g=0;g<3;++g){TArrayList<CEffect*>&ls=self->getActiveEffects(g);n=ls.size();out.add(&n,4);for(unsigned i=0;i<n;++i){int identity=id(ls.m_pData[i]);out.add(&identity,4);}ls.~TArrayList();}
 for(unsigned i=0;i<5;++i){CEffect*e=static_cast<CEffect*>(objects[i]);out.add(&e->m_fRemainingDuration,4);out.add(&e->m_bDead,1);CAffix*a=static_cast<CAffix*>(objects[5+i]);out.add(&a->m_fDuration,4);a->m_sDisplayName.~basic_string();}as.~TArrayList();self->m_EffectString2E0.~basic_string();self->m_EffectString2E8.~basic_string();self->m_EffectString2F0.~basic_string();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    manager state mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_effect_clear,0,oClear)
TEST(state_effect_recalculate,1,oRecalc)
TEST(state_effect_clear_affixes,2,oAffClear)
TEST(state_effect_restore_affixes,3,oAffBack)
TEST(state_effect_remove_unsaved,4,oUnsaved)
TEST(state_effect_clone_list,5,oClones)
TEST(state_effect_add_affix,6,oAdd)
TEST(state_effect_delete_affix_ptr,7,oDelete)
TEST(state_effect_delete_affix_name,8,oDeleteName)
TEST(state_effect_update_affixes,9,oUpdate)
TEST(state_effect_remove_ptr,10,oRemove)
TEST(state_effect_create_groups,11,oCreate)
TEST(state_effect_clone_one,12,oClone)
