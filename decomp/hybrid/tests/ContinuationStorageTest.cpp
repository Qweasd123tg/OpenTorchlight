#include <cstring>
#include <string>
#include <map>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "SafePointer.h"
#define private public
#include "DataGroup.h"
#include "DataValue.h"
#include "TRepository.h"
#undef private
#define TARGET(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
TARGET(CDataValue*,csOldUnion,csNewUnion,(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES),"_ZN10CDataGroup12AddDataValueEj14UNIONDATA64BITN10CDataValue15EDATAVALUETYPESE")
TARGET(CDataValue*,csOldText,csNewText,(CDataGroup*,const std::wstring&,std::wstring,std::wstring),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES3_S3_")
TARGET(CDataValue*,csOldCopy,csNewCopy,(CDataGroup*,CDataValue*,TArrayList<CDataValue*>*),"_ZN10CDataGroup13CopyDataValueEP10CDataValueP10TArrayListIS1_E")
TARGET(void,csOldCopyGroup,csNewCopyGroup,(CDataGroup*,CDataGroup*,bool),"_ZN10CDataGroup13CopyDataGroupEPS_b")
TARGET(void,csOldValueDestroy,csNewValueDestroy,(CDataValue*),"_ZN10CDataValueD1Ev")
TL_ORIGINAL(void,csGroupCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,csGroupDtor,(CDataGroup*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(CDataValue*,csAddInt,(CDataGroup*,const std::wstring&,int),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_ORIGINAL(CDataValue*,csAddString,(CDataGroup*,const std::wstring&,const wchar_t*,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_ORIGINAL(CDataGroup*,csAddGroup,(CDataGroup*,const std::wstring&),"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,csValueCtor,(CDataValue*,const wchar_t*,TRepository<std::wstring>*),"_ZN10CDataValueC1EPKwP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
#undef TARGET
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* capture;
void number(unsigned x){capture->add(&x,4);}
void repository(TRepository<std::wstring>& r){number(r.m_iNextID);number(r.m_Values.size());for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){number(i->first);capture->addText(i->second);}number(r.m_IDs.size());for(std::map<std::wstring,unsigned>::iterator i=r.m_IDs.begin();i!=r.m_IDs.end();++i){capture->addText(i->first);number(i->second);}number(r.m_RefCounts.size());for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){number(i->first);capture->add(&i->second,2);}}
void value(CDataValue* p){number(p->m_bStringValue);number(p->m_iNameID);number(p->m_eType);capture->add(&p->m_Value,8);}
void group(CDataGroup* p){number(p->m_iNameID);number(p->m_b58);number(p->m_b59);number(p->m_DataValues.size());number(p->m_DataValues.m_nCapacity);number(p->m_DataValues.m_nGrowBy);for(unsigned i=0;i<p->m_DataValues.size();++i)value(p->m_DataValues[i]);number(p->m_DataGroups.size());number(p->m_DataGroups.m_nCapacity);number(p->m_DataGroups.m_nGrowBy);for(unsigned i=0;i<p->m_DataGroups.size();++i)group(p->m_DataGroups[i]);}
void side(void* raw,autotest::Capture& out,bool ours){Case c=*static_cast<Case*>(raw);capture=&out;unsigned seed=c.seed;TRepository<std::wstring> r(L"<default>"),sourceRepo(L"<default>");
 if(c.mode==4){uint64_t memory[(sizeof(CDataValue)+7)/8];std::memset(memory,0xa5,sizeof(memory));CDataValue* self=reinterpret_cast<CDataValue*>(memory);csValueCtor(self,L"initial",&r);r.clear();
  const wchar_t* text[]={L"<default>",L"name",L"value",L"Ж"};for(unsigned i=0;i<4;++i){r.m_Values[i]=text[i];r.m_IDs[text[i]]=i;r.m_RefCounts[i]=static_cast<unsigned short>((seed+i)%4==0?0:(seed+i)%4==1?1:(seed+i)%4==2?2:65535);}r.m_iNextID=4;
  self->m_iNameID=seed%6==5?unsigned(-1):seed%6;self->m_Value.unsigned32=(seed/3)%6==5?unsigned(-1):(seed/3)%6;const unsigned types[]={0,5,8,9};self->m_eType=static_cast<CDataValue::EDATAVALUETYPES>(types[(seed/4)%4]);self->m_bStringValue=seed&1;
  if(seed&16)r.m_Values.erase(1);if(seed&32)r.m_IDs.erase(L"value");if(seed%7==0)r.m_RefCounts.erase(3);if(seed%11==0)self->m_pRepository=NULL;
  TSafePointer<CDataValue> reference;reference.setObject(self);unsigned constructed=g_iTotalCountOfObjects;typedef void(*Fn)(CDataValue*);Fn fn=ours?csNewValueDestroy:csOldValueDestroy;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;number(reference.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);if(reference.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;value(self);repository(r);return;
 }
 uint64_t parentMemory[(sizeof(CDataGroup)+7)/8],selfMemory[(sizeof(CDataGroup)+7)/8],sourceMemory[(sizeof(CDataGroup)+7)/8];std::memset(parentMemory,0xa5,sizeof(parentMemory));std::memset(selfMemory,0xa5,sizeof(selfMemory));std::memset(sourceMemory,0xa5,sizeof(sourceMemory));CDataGroup* parent=reinterpret_cast<CDataGroup*>(parentMemory);CDataGroup* self=reinterpret_cast<CDataGroup*>(selfMemory);CDataGroup* source=reinterpret_cast<CDataGroup*>(sourceMemory);csGroupCtor(parent,L"parent",NULL,2,2,NULL);csGroupCtor(self,L"destination",parent,1+seed%3,1+seed%2,&r);csGroupCtor(source,L"source",parent,2,2,&sourceRepo);
 const wchar_t* names[]={L"",L"name",L"Ж",L"other"};for(unsigned i=0;i<seed%5;++i){if((seed+i)&1)csAddString(self,names[i%4],i&1?L"text":L"",seed&2);else csAddInt(self,names[i%4],int(seed*13+i));}for(unsigned i=0;i<1+seed%4;++i){if(i&1)csAddInt(source,names[(i+seed)%4],int(seed*19+i));else csAddString(source,names[(i+seed)%4],i&2?L"Ж":L"value",seed&4);}self->m_b58=false;
 CDataValue* result=NULL;
 if(c.mode==0){UNIONDATA64BIT data;data.signed64=seed%6==0?-1:seed%7;unsigned name=seed%5==0?unsigned(-1):seed%7;typedef CDataValue*(*Fn)(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES);Fn fn=ours?csNewUnion:csOldUnion;if(!autotest::beginInvocation(out,fn))return;result=fn(self,name,data,static_cast<CDataValue::EDATAVALUETYPES>(seed%10));}
 else if(c.mode==1){const wchar_t* types[]={L"INTEGER",L"INTEGER64",L"FLOAT",L"DOUBLE",L"UNSIGNED INT",L"BOOL",L"TRANSLATE",L"DIALOG",L"STRING",L"UNKNOWN"};const wchar_t* values[]={L"0",L"-1",L"1.25",L"true",L"FALSE",L"9223372036854775807",L"Ж",L""};typedef CDataValue*(*Fn)(CDataGroup*,const std::wstring&,std::wstring,std::wstring);Fn fn=ours?csNewText:csOldText;if(!autotest::beginInvocation(out,fn))return;result=fn(self,names[seed%4],std::wstring(types[seed%10]),std::wstring(values[(seed/3)%8]));}
 else if(c.mode==2){TArrayList<CDataValue*> available(1+seed%3);for(unsigned i=0;i<self->m_DataValues.size();++i)if((i+seed)%3)available.add(self->m_DataValues[i]);CDataValue* input=seed%7?source->m_DataValues[seed%source->m_DataValues.size()]:NULL;typedef CDataValue*(*Fn)(CDataGroup*,CDataValue*,TArrayList<CDataValue*>*);Fn fn=ours?csNewCopy:csOldCopy;if(!autotest::beginInvocation(out,fn))return;result=fn(self,input,seed%11?&available:NULL);out.callCompleted=1;number(available.size());for(unsigned i=0;i<available.size();++i){int identity=-1;for(unsigned j=0;j<self->m_DataValues.size();++j)if(available[i]==self->m_DataValues[j])identity=j;out.add(&identity,4);}if((!input||seed%11==0)&&(result||self->m_b58))out.issue=autotest::Capture::InvalidReport;}
 else{for(unsigned i=0;i<seed%3;++i){CDataGroup* child=csAddGroup(source,names[i]);csAddInt(child,L"number",seed*13);if(i==1)csAddGroup(child,L"leaf");}typedef void(*Fn)(CDataGroup*,CDataGroup*,bool);Fn fn=ours?csNewCopyGroup:csOldCopyGroup;if(!autotest::beginInvocation(out,fn))return;fn(self,seed%7?source:NULL,seed&1);}
 out.callCompleted=1;int identity=-1;for(unsigned i=0;i<self->m_DataValues.size();++i)if(result==self->m_DataValues[i])identity=i;out.add(&identity,4);group(self);group(source);repository(r);repository(sourceRepo);TSafePointer<CDataGroup> reference;reference.setObject(self);csGroupDtor(self);number(reference.getObject()==NULL);if(reference.getObject())out.issue=autotest::Capture::InvalidReport;csGroupDtor(source);repository(r);repository(sourceRepo);csGroupDtor(parent);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<64;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log(" continuation storage %u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
static int continuation_data_union(const tlhybrid_host* host){return run(host,0,"continuation_data_union",(uintptr_t)&csOldUnion);}
static int continuation_data_text(const tlhybrid_host* host){return run(host,1,"continuation_data_text",(uintptr_t)&csOldText);}
static int continuation_copy_value(const tlhybrid_host* host){return run(host,2,"continuation_copy_value",(uintptr_t)&csOldCopy);}
static int continuation_copy_group(const tlhybrid_host* host){return run(host,3,"continuation_copy_group",(uintptr_t)&csOldCopyGroup);}
TL_TEST(continuation_data_value_lifetime){return run(host,4,"continuation_data_value_lifetime",(uintptr_t)&csOldValueDestroy);}
