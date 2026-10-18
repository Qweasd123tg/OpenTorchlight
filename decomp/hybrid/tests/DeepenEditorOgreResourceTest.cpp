#include <cstring>
#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "DataGroup.h"
#include "DataValue.h"
#include "TRepository.h"
#include "TimerStatics.h"
#include "OgreReader.h"
#undef private
#include "OgreResourceFile.h"
#define TARGET(old,newer,symbol) TL_ORIGINAL(void,old,(COgreResourceFile*,COgreReader*,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*),symbol) extern "C" void newer(COgreResourceFile*,COgreReader*,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*) __asm__(symbol);
TARGET(deOldValues,deNewValues,"_ZN17COgreResourceFile14LoadDataValuesEP11COgreReaderP10CDataGroupRSt3mapIjjSt4lessIjESaISt4pairIKjjEEEjP13CTimerStatics")
TARGET(deOldLoad,deNewLoad,"_ZN17COgreResourceFile4LoadEP11COgreReaderP10CDataGroupRSt3mapIjjSt4lessIjESaISt4pairIKjjEEEjP13CTimerStatics")
#undef TARGET
TL_ORIGINAL(void,deCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,deDestroy,(CDataGroup*),"_ZN10CDataGroupD1Ev")
extern "C" char deTime_linked[] __asm__("_ZN4Ogre5Timer15getMicrosecondsEv");
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* capture;unsigned seed,ticks;Ogre::Timer* timer;
void number(unsigned x){capture->add(&x,4);}
unsigned long microseconds(Ogre::Timer* p){if(p!=timer)capture->issue=autotest::Capture::InvalidReport;return (seed&4?0x100000000ul:0ul)+unsigned(seed*173+ ++ticks*1009);}
void word(std::ostream& f,unsigned x){f.write(reinterpret_cast<const char*>(&x),4);}
void values(std::ostream& f,unsigned n,unsigned salt){word(f,n);for(unsigned i=0;i<n;++i){word(f,10+(i+salt)%7);unsigned type=(i+salt)%10;word(f,type);if(type==3||type==7){long long x=(salt&1)?-0x1234567890LL:0x1122334455667788LL;f.write(reinterpret_cast<const char*>(&x),8);}else word(f,type==5||type==8?10+(i+1)%7:0x80000000u+salt+i);}}
void tree(std::ostream& f,unsigned salt,unsigned depth){word(f,10+salt%7);values(f,salt%5,salt);word(f,depth?salt%3:0);for(unsigned i=0;depth&&i<salt%3;++i)tree(f,salt+i+1,depth-1);}
void repository(TRepository<std::wstring>& r){number(r.m_iNextID);number(r.m_Values.size());for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){number(i->first);capture->addText(i->second);}number(r.m_RefCounts.size());for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){number(i->first);capture->add(&i->second,2);}}
void group(CDataGroup* p){number(p->m_iNameID);number(p->m_b58);number(p->m_DataValues.m_nGrowBy);number(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i){CDataValue* v=p->m_DataValues[i];number(v->m_iNameID);number(v->m_eType);capture->add(&v->m_Value,8);}number(p->m_DataGroups.m_nGrowBy);number(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)group(p->m_DataGroups[i]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);capture=&out;seed=c.seed;ticks=0;TRepository<std::wstring> r(L"");uint64_t parentMemory[(sizeof(CDataGroup)+7)/8],memory[(sizeof(CDataGroup)+7)/8];CDataGroup* parent=reinterpret_cast<CDataGroup*>(parentMemory);CDataGroup*self=reinterpret_cast<CDataGroup*>(memory);deCtor(parent,L"parent",NULL,2,2,NULL);deCtor(self,L"root",parent,2,2,&r);COgreResourceFile style;CTimerStatics timing;timer=&timing.m_timer;timing.m_times.setGrowBy(1+seed%3);for(unsigned i=0;i<seed%4;++i)timing.m_times.add(seed*17+i);std::map<unsigned,unsigned> names;
 for(unsigned i=0;i<5;++i){wchar_t text[24];std::swprintf(text,24,L"name%u",i);r.m_Values[i+1]=text;r.m_IDs[text]=i+1;r.m_RefCounts[i+1]=5;names[10+i]=i+1;}r.m_iNextID=6;
 std::ostringstream bytes(std::ios::binary);if(c.mode==0)values(bytes,seed%11,seed);else tree(bytes,seed,2);std::string data=bytes.str();COgreReader input;input.m_pData=new char[data.size()];std::memcpy(input.m_pData,data.data(),data.size());input.m_iSize=data.size();input.m_iPosition=0;
 detour::Set d;d.redirect(reinterpret_cast<char*>(0x555928),deTime_linked,&microseconds);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}CTimerStatics*stats=seed&1?&timing:NULL;
 typedef void(*Fn)(COgreResourceFile*,COgreReader*,CDataGroup*,std::map<unsigned,unsigned>&,unsigned,CTimerStatics*);Fn fn=c.mode==0?(ours?deNewValues:deOldValues):(ours?deNewLoad:deOldLoad);if(!autotest::beginInvocation(out,fn))return;fn(&style,&input,self,names,seed%3,stats);out.callCompleted=1;
 if(input.m_iPosition!=input.m_iSize)out.issue=autotest::Capture::InvalidReport;
 number(input.m_iPosition);number(ticks);number(names.size());for(std::map<unsigned,unsigned>::iterator i=names.begin();i!=names.end();++i){number(i->first);number(i->second);}number(timing.m_times.size());number(timing.m_times.m_nCapacity);number(timing.m_times.m_nGrowBy);for(unsigned i=0;i<timing.m_times.size();++i)number(timing.m_times[i]);number(timing.m_statistics.size());for(std::map<std::wstring,std::pair<unsigned,unsigned> >::iterator i=timing.m_statistics.begin();i!=timing.m_statistics.end();++i){out.addText(i->first);number(i->second.first);number(i->second.second);}
 group(self);repository(r);deDestroy(self);deDestroy(parent);repository(r);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<60;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    ogre load op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_ogre_values){return run(host,0,"deepen_editor_ogre_values",(uintptr_t)&deOldValues);}
TL_TEST(deepen_editor_ogre_load){return run(host,1,"deepen_editor_ogre_load",(uintptr_t)&deOldLoad);}
