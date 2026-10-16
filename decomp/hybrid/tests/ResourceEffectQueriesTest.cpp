#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "AutoTest.h"
#define private public
#include "EffectManager.h"
#include "Effect.h"
#include "Affix.h"
#undef private
#define QUERY(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
QUERY(void*,oldByType,newByType,(void*,EEFFECT_TYPE),"_ZN14CEffectManager9getEffectE12EEFFECT_TYPE")
QUERY(bool,oldFromSkill,newFromSkill,(void*,const CSkill*),"_ZN14CEffectManager18hasEffectFromSkillEPK6CSkill")
QUERY(void,oldAll,newAll,(void*,TArrayList<CEffect*>*),"_ZN14CEffectManager10getEffectsEP10TArrayListIP7CEffectE")
QUERY(void*,oldAffix,newAffix,(void*,const std::wstring&),"_ZN14CEffectManager8getAffixERKSbIwSt11char_traitsIwESaIwEE")
QUERY(bool,oldTypeName,newTypeName,(void*,EEFFECT_TYPE,const std::wstring&),"_ZN14CEffectManager9hasEffectE12EEFFECT_TYPERKSbIwSt11char_traitsIwESaIwEE")
QUERY(void*,oldNameIndex,newNameIndex,(void*,const std::wstring&,unsigned),"_ZN14CEffectManager9getEffectERKSbIwSt11char_traitsIwESaIwEEj")
#undef QUERY
namespace {
struct Case {unsigned mode,seed;};
int id(void* p,void** objects,unsigned n){if(!p)return -1;for(unsigned i=0;i<n;++i)if(p==objects[i])return i;return -2;}
void side(void* raw,autotest::Capture& out,bool ours){
 const Case& c=*static_cast<Case*>(raw);uint64_t managerSpace[(sizeof(CEffectManager)+7)/8],effectSpace[8][(sizeof(CEffect)+7)/8],affixSpace[5][(sizeof(CAffix)+7)/8],skills[3][4];
 std::memset(managerSpace,0xa5,sizeof(managerSpace));std::memset(effectSpace,0x3c,sizeof(effectSpace));std::memset(affixSpace,0x5a,sizeof(affixSpace));
 CEffectManager* manager=reinterpret_cast<CEffectManager*>(managerSpace);void* effects[8];void* affixes[5];
 const wchar_t* names[]={L"",L"A",L"AA",L"Ж"};
 for(unsigned i=0;i<8;++i){CEffect* e=reinterpret_cast<CEffect*>(effectSpace[i]);effects[i]=e;new(&e->m_sName)std::wstring(names[(i+c.seed/7)%4]);e->m_eType=static_cast<EEFFECT_TYPE>((i+c.seed)%4);e->m_pSkillOwner=(i+c.seed)%4==3?NULL:reinterpret_cast<CSkill*>(skills[(i+c.seed)%3]);}
 for(unsigned i=0;i<5;++i){CAffix* a=reinterpret_cast<CAffix*>(affixSpace[i]);affixes[i]=a;new(&a->m_sAffixFileName)std::wstring(names[(i+1+c.seed/11)%4]);new(&a->m_sDisplayName)std::wstring(names[(i+c.seed/11)%4]);}
 TArrayList<CAffix*>* affixList=new(manager->m_EffectData10)TArrayList<CAffix*>(2);
 for(unsigned i=0;i<c.seed%6;++i)affixList->add(static_cast<CAffix*>(affixes[i]));
 TArrayList<CEffect*>* groups[3];for(unsigned g=0;g<3;++g){groups[g]=new(manager->m_EffectData10+0x18+g*0x18)TArrayList<CEffect*>(2);for(unsigned i=0;i<(c.seed+g*3)%7;++i)groups[g]->add(static_cast<CEffect*>(effects[(i+g*2)%8]));}
 // The original indexed accessors deliberately fall back to slot zero when capacity is smaller.
 if(c.seed&16)for(unsigned g=0;g<3;++g)if(groups[g]->m_nCount)groups[g]->m_nCapacity=(c.seed/8)%2;
 if((c.seed&32)&&affixList->m_nCount)affixList->m_nCapacity=(c.seed/8)%2;
 unsigned char before[sizeof(managerSpace)];std::memcpy(before,managerSpace,sizeof(managerSpace));
 std::wstring query=names[(c.seed/3)%4];EEFFECT_TYPE type=static_cast<EEFFECT_TYPE>((c.seed/5)%5);const CSkill* skill=c.seed&1?NULL:reinterpret_cast<CSkill*>(skills[c.seed%3]);unsigned index=(c.seed/13)%5;
 int expected=-1,result=-1;
 if(c.mode==0||c.mode==1||c.mode==4||c.mode==5){for(unsigned g=0;g<2&&expected<0;++g)for(unsigned i=0;i<groups[g]->size();++i){CEffect* e=(*groups[g])[i];bool match=c.mode==0?e->m_eType==type:c.mode==1?e->m_pSkillOwner==skill:c.mode==4?(e->m_eType==type&&e->m_sName==query):e->m_sName==query;if(match){if(c.mode==5&&index){--index;continue;}expected=id(e,effects,8);break;}}}
 if(c.mode==3)for(unsigned i=0;i<affixList->size();++i)if((*affixList)[i]->m_sDisplayName==query){expected=id((*affixList)[i],affixes,5);break;}
 if(c.mode==0){void*(*fn)(void*,EEFFECT_TYPE)=ours?newByType:oldByType;if(!autotest::beginInvocation(out,fn))return;result=id(fn(manager,type),effects,8);out.callCompleted=1;}
 else if(c.mode==1){bool(*fn)(void*,const CSkill*)=ours?newFromSkill:oldFromSkill;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,skill)?1:0;out.callCompleted=1;expected=expected>=0?1:0;}
 else if(c.mode==2){TArrayList<CEffect*> values((c.seed%3)+1);unsigned prefix=c.seed%3;for(unsigned i=0;i<prefix;++i)values.add(static_cast<CEffect*>(effects[7]));void(*fn)(void*,TArrayList<CEffect*>*)=ours?newAll:oldAll;if(!autotest::beginInvocation(out,fn))return;fn(manager,c.seed%9==0?NULL:&values);out.callCompleted=1;unsigned n=values.size();out.add(&n,4);unsigned expectedCount=prefix;
  if(c.seed%9!=0)for(unsigned g=0;g<3;++g)expectedCount+=groups[g]->size();if(n!=expectedCount)out.issue=autotest::Capture::InvalidReport;
  unsigned at=0;for(;at<prefix;++at)if(values[at]!=effects[7])out.issue=autotest::Capture::InvalidReport;
  if(c.seed%9!=0)for(unsigned g=0;g<3;++g)for(unsigned i=0;i<groups[g]->size();++i,++at)if(values[at]!=groups[g]->m_pData[i])out.issue=autotest::Capture::InvalidReport;
  for(unsigned i=0;i<n;++i){int value=id(values[i],effects,8);out.add(&value,4);} }
 else if(c.mode==3){void*(*fn)(void*,const std::wstring&)=ours?newAffix:oldAffix;if(!autotest::beginInvocation(out,fn))return;result=id(fn(manager,query),affixes,5);out.callCompleted=1;}
 else if(c.mode==4){bool(*fn)(void*,EEFFECT_TYPE,const std::wstring&)=ours?newTypeName:oldTypeName;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,type,query)?1:0;out.callCompleted=1;expected=expected>=0?1:0;}
 else{void*(*fn)(void*,const std::wstring&,unsigned)=ours?newNameIndex:oldNameIndex;if(!autotest::beginInvocation(out,fn))return;result=id(fn(manager,query,(c.seed/13)%5),effects,8);out.callCompleted=1;}
 if(c.mode!=2){out.add(&result,4);if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 if(std::memcmp(before,managerSpace,sizeof(managerSpace)))out.issue=autotest::Capture::InvalidReport;
 for(unsigned g=0;g<3;++g){groups[g]->m_nCapacity=groups[g]->m_nCount;groups[g]->~TArrayList();}affixList->~TArrayList();
 for(unsigned i=0;i<8;++i)reinterpret_cast<CEffect*>(effectSpace[i])->m_sName.~basic_string();for(unsigned i=0;i<5;++i){reinterpret_cast<CAffix*>(affixSpace[i])->m_sAffixFileName.~basic_string();reinterpret_cast<CAffix*>(affixSpace[i])->m_sDisplayName.~basic_string();}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<120;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    effect query mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(resource_effect_by_type){return run(host,0,"resource_effect_by_type",(uintptr_t)&oldByType);}
TL_TEST(resource_effect_from_skill){return run(host,1,"resource_effect_from_skill",(uintptr_t)&oldFromSkill);}
TL_TEST(resource_effect_all){return run(host,2,"resource_effect_all",(uintptr_t)&oldAll);}
TL_TEST(resource_effect_affix){return run(host,3,"resource_effect_affix",(uintptr_t)&oldAffix);}
TL_TEST(resource_effect_type_name){return run(host,4,"resource_effect_type_name",(uintptr_t)&oldTypeName);}
TL_TEST(resource_effect_name_index){return run(host,5,"resource_effect_name_index",(uintptr_t)&oldNameIndex);}
