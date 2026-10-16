#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "TRepository.h"
#include "DataValue.h"
#include "DataGroup.h"
#undef private
#define QUERY(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
QUERY(const std::wstring&,oldValueName,newValueName,(void*),"_ZN10CDataValue16GetDataValueNameEv")
QUERY(const std::wstring&,oldString,newString,(void*,bool),"_ZN10CDataValue14GetValueStringEb")
QUERY(std::wstring,oldAsString,newAsString,(void*),"_ZN10CDataValue16GetValueAsStringEv")
QUERY(const std::wstring&,oldGroupName,newGroupName,(void*),"_ZN10CDataGroup12GetGroupNameEv")
QUERY(unsigned,oldMatching,newMatching,(void*,const std::wstring&,std::vector<CDataValue*>*),"_ZN10CDataGroup25GetDataValuesMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIP10CDataValueSaIS8_EE")
#undef QUERY
TL_FUNCTION(translationSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translationLookup,"_ZN16CStringTranslate18getTranslateStringERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* capture;bool translatorPresent;uint64_t translator[12];std::wstring* translated;
void text(autotest::Capture&o,const std::wstring&s){unsigned n=s.size();o.add(&n,4);if(n)o.add(s.data(),n*4);}
void* singleton(){unsigned marker=71;capture->add(&marker,4);return translatorPresent?translator:NULL;}
const std::wstring& translate(void*self,const std::wstring&s){unsigned marker=72;capture->add(&marker,4);text(*capture,s);if(self!=translator)capture->issue=autotest::Capture::InvalidReport;return *translated;}
void fill(CDataValue*value,TRepository<std::wstring>*repository,unsigned seed){std::memset(value,0x5a,sizeof(CDataValue));value->m_bStringValue=(seed&4)!=0;value->m_pRepository=seed&8?repository:NULL;const unsigned ids[]={0,1,3,5,~0u};value->m_iNameID=ids[seed%5];value->m_eType=static_cast<CDataValue::EDATAVALUETYPES>(seed%11);value->m_Value.unsigned32=ids[(seed/5)%5];}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);capture=&out;
 TRepository<std::wstring> repository(std::wstring(L"repository default"));if(c.seed&16){repository.m_Values[1]=L"A";repository.m_Values[3]=L"";repository.m_Values[5]=L"Ж";}
 uint64_t valueSpace[8][(sizeof(CDataValue)+7)/8],groupSpace[(sizeof(CDataGroup)+7)/8];CDataValue*value=reinterpret_cast<CDataValue*>(valueSpace[0]);fill(value,&repository,c.seed);
 std::wstring translatedValue=L"translated value";translated=&translatedValue;translatorPresent=(c.seed&32)!=0;
 detour::Set patches;TL_REDIRECT(patches,translationSingleton,&singleton);TL_REDIRECT(patches,translationLookup,&translate);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode==0){const std::wstring&(*fn)(void*)=ours?newValueName:oldValueName;if(!autotest::beginInvocation(out,fn))return;const std::wstring&result=fn(value);out.callCompleted=1;text(out,result);std::wstring expected;
  if(value->m_pRepository&&value->m_iNameID!=~0u){std::map<unsigned,std::wstring>::const_iterator i=repository.m_Values.find(value->m_iNameID);expected=i==repository.m_Values.end()?repository.m_DefaultValue:i->second;}if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==1){const std::wstring&(*fn)(void*,bool)=ours?newString:oldString;if(!autotest::beginInvocation(out,fn))return;const std::wstring&result=fn(value,(c.seed&1)!=0);out.callCompleted=1;text(out,result);std::wstring expected;
  if((value->m_eType==5||value->m_eType==8)&&value->m_pRepository&&value->m_bStringValue){std::map<unsigned,std::wstring>::const_iterator i=repository.m_Values.find(value->m_Value.unsigned32);expected=i==repository.m_Values.end()?repository.m_DefaultValue:i->second;if(value->m_Value.unsigned32==~0u)expected=repository.m_DefaultValue;if((c.seed&1)&&value->m_eType==8&&translatorPresent)expected=translatedValue;}if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==2){const uint64_t bits[]={0,1,0xffffffffULL,0x80000000ULL,0xffffffffffffffffULL,0x7fffffffffffffffULL,0x3ff8000000000000ULL,0x7ff0000000000000ULL};value->m_Value.signed64=bits[(c.seed/11)%8];if(value->m_eType==5||value->m_eType==8)value->m_Value.unsigned32=(c.seed/11)%6;if(value->m_eType==6)value->m_Value.boolean=(c.seed&1)!=0;
  std::wstring(*fn)(void*)=ours?newAsString:oldAsString;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(value);out.callCompleted=1;text(out,result);}
 else if(c.mode==3){std::memset(groupSpace,0xa5,sizeof(groupSpace));CDataGroup*group=reinterpret_cast<CDataGroup*>(groupSpace);group->m_pRepository=value->m_pRepository;group->m_iNameID=value->m_iNameID;
  const std::wstring&(*fn)(void*)=ours?newGroupName:oldGroupName;if(!autotest::beginInvocation(out,fn))return;const std::wstring&result=fn(group);out.callCompleted=1;text(out,result);std::wstring expected;
  if(group->m_pRepository){std::map<unsigned,std::wstring>::const_iterator i=repository.m_Values.find(group->m_iNameID);expected=(group->m_iNameID==-1||i==repository.m_Values.end())?repository.m_DefaultValue:i->second;}if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else{std::memset(groupSpace,0xa5,sizeof(groupSpace));CDataGroup*group=reinterpret_cast<CDataGroup*>(groupSpace);TArrayList<CDataValue*>*values=new(&group->m_DataValues)TArrayList<CDataValue*>(2);
  for(unsigned i=0;i<c.seed%8;++i){CDataValue*v=reinterpret_cast<CDataValue*>(valueSpace[i]);fill(v,&repository,c.seed+i);values->add(v);}if(c.seed&64&&values->size())values->m_nCapacity=1;
  const wchar_t*names[]={L"",L"A",L"Ж",L"repository default",L"missing"};std::wstring query=names[(c.seed/8)%5];std::vector<CDataValue*> result,expected;if(c.seed&1){result.push_back(value);expected.push_back(value);}
  for(unsigned i=0;i<values->size();++i){CDataValue*v=(*values)[i];std::wstring name;if(v->m_pRepository&&v->m_iNameID!=~0u){std::map<unsigned,std::wstring>::iterator found=repository.m_Values.find(v->m_iNameID);name=found==repository.m_Values.end()?repository.m_DefaultValue:found->second;}if(name==query)expected.push_back(v);}
  unsigned(*fn)(void*,const std::wstring&,std::vector<CDataValue*>*)=ours?newMatching:oldMatching;if(!autotest::beginInvocation(out,fn))return;unsigned count=fn(group,query,c.seed%7==0?NULL:&result);out.callCompleted=1;out.add(&count,4);
  if(c.seed%7==0){if(count!=0)out.issue=autotest::Capture::InvalidReport;}else if(count!=expected.size()||result!=expected)out.issue=autotest::Capture::InvalidReport;
  for(unsigned i=0;i<result.size();++i){unsigned id=(reinterpret_cast<uintptr_t>(result[i])-reinterpret_cast<uintptr_t>(&valueSpace[0][0]))/sizeof(valueSpace[0]);out.add(&id,4);}values->~TArrayList();}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<176;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    data query mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(resource_data_value_name){return run(host,0,"resource_data_value_name",(uintptr_t)&oldValueName);}
TL_TEST(resource_data_value_string){return run(host,1,"resource_data_value_string",(uintptr_t)&oldString);}
TL_TEST(resource_data_value_format){return run(host,2,"resource_data_value_format",(uintptr_t)&oldAsString);}
TL_TEST(resource_data_group_name){return run(host,3,"resource_data_group_name",(uintptr_t)&oldGroupName);}
TL_TEST(resource_data_group_matching){return run(host,4,"resource_data_group_matching",(uintptr_t)&oldMatching);}
