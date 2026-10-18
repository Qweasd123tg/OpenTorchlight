#include <cstring>
#include <cstdio>
#include <string>
#include <map>
#include <fstream>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "DataGroup.h"
#include "DataValue.h"
#include "TRepository.h"
#include "TimerStatics.h"
#undef private
#include "BinaryStyle.h"
#define TARGET(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
TARGET(void,cbOldValues,cbNewValues,(CBinaryStyle*,std::ifstream&,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*),"_ZN12CBinaryStyle14LoadDataValuesERSt14basic_ifstreamIcSt11char_traitsIcEEP10CDataGroupRSt3mapIjjSt4lessIjESaISt4pairIKjjEEEjP13CTimerStatics")
TARGET(void,cbOldLoad,cbNewLoad,(CBinaryStyle*,std::ifstream&,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*),"_ZN12CBinaryStyle4LoadERSt14basic_ifstreamIcSt11char_traitsIcEEP10CDataGroupRSt3mapIjjSt4lessIjESaISt4pairIKjjEEEjP13CTimerStatics")
TARGET(int,cbOldSave,cbNewSave,(CBinaryStyle*,const std::wstring&,CDataGroup*),"_ZN12CBinaryStyle19SaveDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
TL_ORIGINAL(void,cbCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,cbDestroy,(CDataGroup*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(CDataValue*,cbAdd,(CDataGroup*,const std::wstring&,int),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_ORIGINAL(CDataValue*,cbAddText,(CDataGroup*,const std::wstring&,const wchar_t*,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_ORIGINAL(CDataGroup*,cbAddGroup,(CDataGroup*,const std::wstring&),"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char cbTime_linked[] __asm__("_ZN4Ogre5Timer15getMicrosecondsEv");
#undef TARGET
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* capture;unsigned seed,ticks;Ogre::Timer* timer;
void number(unsigned x){capture->add(&x,4);}
unsigned long microseconds(Ogre::Timer* p){if(p!=timer)capture->issue=autotest::Capture::InvalidReport;return (seed&4?0x100000000ul:0ul)+unsigned(seed*173+ ++ticks*1009);}
void word(std::ofstream& f,unsigned x){f.write(reinterpret_cast<const char*>(&x),4);}
void values(std::ofstream& f,unsigned n,unsigned salt){word(f,n);const unsigned types[]={0,1,2,3,4,5,6,7,8,9};for(unsigned i=0;i<n;++i){word(f,10+(i+salt)%7);unsigned type=types[(i+salt)%10];word(f,type);if(type==3||type==7){long long x=(salt&1)?-0x1234567890LL:0x1122334455667788LL;f.write(reinterpret_cast<const char*>(&x),8);}else word(f,type==5||type==8?10+(i+1)%7:0x80000000u+salt+i);}}
void tree(std::ofstream& f,unsigned salt,unsigned depth){word(f,10+salt%7);values(f,salt%4,salt);word(f,depth?salt%3:0);for(unsigned i=0;depth&&i<salt%3;++i)tree(f,salt+i+1,depth-1);}
void repository(TRepository<std::wstring>& r){number(r.m_iNextID);number(r.m_Values.size());for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){number(i->first);capture->addText(i->second);}number(r.m_RefCounts.size());for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){number(i->first);capture->add(&i->second,2);}}
void group(CDataGroup* p){number(p->m_iNameID);number(p->m_b58);number(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i){CDataValue* v=p->m_DataValues[i];number(v->m_iNameID);number(v->m_eType);capture->add(&v->m_Value,8);}number(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)group(p->m_DataGroups[i]);}
void side(void* raw,autotest::Capture& out,bool ours){Case c=*static_cast<Case*>(raw);capture=&out;seed=c.seed;ticks=0;char name[128];std::sprintf(name,"/tmp/otl-continuation-binary-%ld.dat",static_cast<long>(getpid()));std::string path(name);std::wstring wide(path.begin(),path.end());TRepository<std::wstring> r(L"");uint64_t parentMemory[(sizeof(CDataGroup)+7)/8],memory[(sizeof(CDataGroup)+7)/8];CDataGroup* parent=reinterpret_cast<CDataGroup*>(parentMemory);CDataGroup* self=reinterpret_cast<CDataGroup*>(memory);cbCtor(parent,L"parent",NULL,2,2,NULL);cbCtor(self,L"root",parent,2,2,&r);CBinaryStyle style;CTimerStatics timing;timer=&timing.m_timer;timing.m_times.setGrowBy(1+seed%3);for(unsigned i=0;i<seed%4;++i)timing.m_times.add(seed*17+i);std::map<unsigned,unsigned> names;
 for(unsigned i=0;i<5;++i){wchar_t text[24];std::swprintf(text,24,L"name%u",i);r.m_Values[i+1]=text;r.m_IDs[text]=i+1;r.m_RefCounts[i+1]=5;names[10+i]=i+1;}r.m_iNextID=6;
 if(c.mode<2){std::ofstream file(path.c_str(),std::ios::binary);if(c.mode==0)values(file,seed%5,seed);else tree(file,seed,2);file.close();std::ifstream input(path.c_str(),std::ios::binary);detour::Set d;d.redirect(reinterpret_cast<char*>(0x555928),cbTime_linked,&microseconds);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}CTimerStatics* stats=seed&1?&timing:NULL;
  typedef void(*Fn)(CBinaryStyle*,std::ifstream&,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*);Fn fn=c.mode==0?(ours?cbNewValues:cbOldValues):(ours?cbNewLoad:cbOldLoad);if(!autotest::beginInvocation(out,fn))return;fn(&style,input,self,names,seed%3,stats);out.callCompleted=1;number(static_cast<unsigned>(input.tellg()));number(input.rdstate());number(ticks);number(names.size());for(std::map<unsigned,unsigned>::iterator i=names.begin();i!=names.end();++i){number(i->first);number(i->second);}number(timing.m_times.size());number(timing.m_times.m_nCapacity);number(timing.m_times.m_nGrowBy);for(unsigned i=0;i<timing.m_times.size();++i)number(timing.m_times[i]);number(timing.m_statistics.size());for(std::map<std::wstring,std::pair<unsigned,unsigned> >::iterator i=timing.m_statistics.begin();i!=timing.m_statistics.end();++i){out.addText(i->first);number(i->second.first);number(i->second.second);}
 }else{for(unsigned i=0;i<seed%5;++i){if(i&1)cbAddText(self,i&2?L"Ж":L"text",i&2?L"Unicode Ж":L"",seed&2);else cbAdd(self,L"number",seed*23+i);}if(seed&4){CDataGroup* child=cbAddGroup(self,L"child");cbAddText(child,L"leaf",L"value",true);}if(seed%4==0)wide=L"";if(seed%4==1)wide=L"/tmp/otl-missing-continuation-directory/sub/file.dat";CDataGroup* argument=seed%7?self:NULL;typedef int(*Fn)(CBinaryStyle*,const std::wstring&,CDataGroup*);Fn fn=ours?cbNewSave:cbOldSave;if(!autotest::beginInvocation(out,fn))return;int result=fn(&style,wide,argument);out.callCompleted=1;out.add(&result,4);std::ifstream saved(path.c_str(),std::ios::binary);std::string bytes((std::istreambuf_iterator<char>(saved)),std::istreambuf_iterator<char>());number(bytes.size());out.add(bytes.data(),bytes.size());if(result&&(!argument||wide.empty()||bytes.size()<12))out.issue=autotest::Capture::InvalidReport;}
 group(self);repository(r);cbDestroy(self);cbDestroy(parent);std::remove(path.c_str());
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<40;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    binary op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(continuation_binary_values){return run(host,0,"continuation_binary_values",(uintptr_t)&cbOldValues);}
TL_TEST(continuation_binary_load){return run(host,1,"continuation_binary_load",(uintptr_t)&cbOldLoad);}
TL_TEST(continuation_binary_save){return run(host,2,"continuation_binary_save",(uintptr_t)&cbOldSave);}
