#include <stdint.h>
#include <cstring>
#include <new>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "SafePointer.h"
#define private public
#include "TRepository.h"
#include "DataValue.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oName,nName,(CDataValue*,const wchar_t*,TRepository<std::wstring>*),"_ZN10CDataValueC1EPKwP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
DECL(void,oUnion,nUnion,(CDataValue*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES,TRepository<std::wstring>*),"_ZN10CDataValueC1Ej14UNIONDATA64BITNS_15EDATAVALUETYPESEP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
DECL(void,oCopyCtor,nCopyCtor,(CDataValue*,CDataValue*,TRepository<std::wstring>*),"_ZN10CDataValueC1EPS_P11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
DECL(void,oConvert,nConvert,(CDataValue*,const std::wstring&,std::wstring&),"_ZN10CDataValue16SetValueByStringERKSbIwSt11char_traitsIwESaIwEERS3_")
TL_ORIGINAL(void,oDestroy,(CDataValue*),"_ZN10CDataValueD1Ev")
#undef DECL
namespace {
struct Case{unsigned mode,seed;};
void repository(TRepository<std::wstring>& r,autotest::Capture& out){unsigned n=r.m_iNextID;out.add(&n,4);n=r.m_Values.size();out.add(&n,4);for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){out.add(&i->first,4);out.addText(i->second);}n=r.m_IDs.size();out.add(&n,4);for(std::map<std::wstring,unsigned>::iterator i=r.m_IDs.begin();i!=r.m_IDs.end();++i){out.addText(i->first);out.add(&i->second,4);}n=r.m_RefCounts.size();out.add(&n,4);for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){out.add(&i->first,4);out.add(&i->second,2);}}
void state(CDataValue* self,autotest::Capture& out,TRepository<std::wstring>* r){out.add(&self->m_bStringValue,1);out.add(&self->m_Value,8);out.add(&self->m_iNameID,4);unsigned repo=self->m_pRepository==r?1:self->m_pRepository?2:0;out.add(&repo,4);out.add(&self->m_eType,4);out.addText(self->GetDataValueName());}
void setup(TRepository<std::wstring>& r,unsigned seed){std::wstring names[]={L"",L"name",L"Ж",L"value",L"<default>"};for(unsigned i=0;i<seed%6&&i<5;++i){r.m_Values[i]=names[i];r.m_IDs[names[i]]=i;if(seed&4)r.m_RefCounts[i]=(seed&8)?65535:3;}r.m_iNextID=5;}
void side(void* raw,autotest::Capture& out,bool ours){const Case& c=*static_cast<Case*>(raw);TRepository<std::wstring> r(L"<default>"),sourceRepo(L"<default>");setup(r,c.seed);setup(sourceRepo,c.seed+2);uint64_t memory[(sizeof(CDataValue)+7)/8],sourceMemory[(sizeof(CDataValue)+7)/8];std::memset(memory,0xa5,sizeof(memory));std::memset(sourceMemory,0xa5,sizeof(sourceMemory));CDataValue*self=reinterpret_cast<CDataValue*>(memory),*source=reinterpret_cast<CDataValue*>(sourceMemory);std::wstring names[]={L"",L"name",L"Ж",std::wstring(40+c.seed,L'n'),L"<default>"};std::wstring types[]={L"INTEGER",L"INTEGER64",L"FLOAT",L"DOUBLE",L"UNSIGNED INT",L"BOOL",L"TRANSLATE",L"DIALOG",L"STRING",L"UNKNOWN"};std::wstring values[]={L"0",L"-1",L"1.25",L"true",L"FALSE",L"9223372036854775807",L"Ж",L""};bool sourceAlive=false;
 if(c.mode==0){typedef void(*Fn)(CDataValue*,const wchar_t*,TRepository<std::wstring>*);Fn fn=ours?nName:oName;if(!autotest::beginInvocation(out,fn))return;fn(self,names[c.seed%5].c_str(),c.seed%7?&r:NULL);}
 else if(c.mode==1){UNIONDATA64BIT value;value.signed64=(c.seed%4==0)?-1:(c.seed/3)%7;unsigned id=(c.seed%4==0)?unsigned(-1):c.seed%7;CDataValue::EDATAVALUETYPES type=static_cast<CDataValue::EDATAVALUETYPES>(c.seed%10);TRepository<std::wstring>* repo=(id==unsigned(-1)&&c.seed%3==0)?NULL:&r;typedef void(*Fn)(CDataValue*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES,TRepository<std::wstring>*);Fn fn=ours?nUnion:oUnion;if(!autotest::beginInvocation(out,fn))return;fn(self,id,value,type,repo);}
 else if(c.mode==2){oName(source,names[c.seed%5].c_str(),&sourceRepo);sourceAlive=true;std::wstring value=values[c.seed%8];oConvert(source,types[c.seed%10],value);typedef void(*Fn)(CDataValue*,CDataValue*,TRepository<std::wstring>*);Fn fn=ours?nCopyCtor:oCopyCtor;if(!autotest::beginInvocation(out,fn))return;fn(self,c.seed%7?source:NULL,&r);}
 else{oName(self,names[c.seed%5].c_str(),&r);if(c.seed&8){std::wstring initial=L"initial";oConvert(self,L"STRING",initial);}std::wstring value=values[(c.seed/3)%8];typedef void(*Fn)(CDataValue*,const std::wstring&,std::wstring&);Fn fn=ours?nConvert:oConvert;if(!autotest::beginInvocation(out,fn))return;fn(self,types[c.seed%10],value);out.addText(value);}
 out.callCompleted=1;state(self,out,&r);repository(r,out);if(sourceAlive){state(source,out,&sourceRepo);repository(sourceRepo,out);}TSafePointer<CDataValue> ref;ref.setObject(self);oDestroy(self);unsigned invalidated=ref.getObject()==NULL;out.add(&invalidated,4);if(!invalidated)out.issue=autotest::Capture::InvalidReport;repository(r,out);if(sourceAlive)oDestroy(source);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*n,uintptr_t addr){autotest::Coverage coverage(n,addr);for(unsigned seed=0;seed<160;++seed){Case c={mode,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    data value mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(bulk_data_value_name_ctor,0,oName)
TEST(bulk_data_value_union_ctor,1,oUnion)
TEST(bulk_data_value_copy_ctor,2,oCopyCtor)
TEST(bulk_data_value_from_string,3,oConvert)
