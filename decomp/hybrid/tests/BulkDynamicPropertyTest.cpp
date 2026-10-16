#include <cstring>
#include <stdint.h>
#include <new>
#include <string>
#include <vector>
#include <map>
#include "AutoTest.h"
#include "SafePointer.h"
#define private public
#include "DynamicPropertyFile.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oCtor,nCtor,(CDynamicPropertyFile*,std::wstring,std::wstring,std::wstring),"_ZN20CDynamicPropertyFileC1ESbIwSt11char_traitsIwESaIwEES3_S3_")
DECL(void,oDtor,nDtor,(CDynamicPropertyFile*),"_ZN20CDynamicPropertyFileD1Ev")
DECL(unsigned,oFloat,nFloat,(CDynamicPropertyFile*,const std::wstring&,float),"_ZN20CDynamicPropertyFile8SetFloatERKSbIwSt11char_traitsIwESaIwEEf")
DECL(unsigned,oInt,nInt,(CDynamicPropertyFile*,const std::wstring&,int),"_ZN20CDynamicPropertyFile6SetIntERKSbIwSt11char_traitsIwESaIwEEi")
DECL(unsigned,oString,nString,(CDynamicPropertyFile*,const std::wstring&,const std::wstring&),"_ZN20CDynamicPropertyFile9SetStringERKSbIwSt11char_traitsIwESaIwEES5_")
DECL(void,oSetting,nSetting,(CDynamicPropertyFile*,const std::wstring&,const std::wstring&),"_ZN20CDynamicPropertyFile10SetSettingERKSbIwSt11char_traitsIwESaIwEES5_")
#undef DECL
namespace {
struct Case { unsigned mode,seed; };
autotest::Capture* capture;unsigned callbacks;
void callback(unsigned index){++callbacks;capture->add(&index,4);}
void number(unsigned n){capture->add(&n,4);}
void state(CDynamicPropertyFile* self){
 capture->addText(self->m_directory);capture->addText(self->m_file);capture->addText(self->m_secondaryFile);capture->addText(self->m_missingString);
 number(self->m_intValues.size());for(unsigned i=0;i<self->m_intValues.size();++i)capture->add(&self->m_intValues[i],4);
 number(self->m_floatValues.size());for(unsigned i=0;i<self->m_floatValues.size();++i)capture->add(&self->m_floatValues[i],4);
 number(self->m_stringValues.size());for(unsigned i=0;i<self->m_stringValues.size();++i)capture->addText(self->m_stringValues[i]);
 std::map<std::wstring,unsigned>* maps[]={&self->m_intIndices,&self->m_floatIndices,&self->m_stringIndices};
 for(unsigned m=0;m<3;++m){number(maps[m]->size());for(std::map<std::wstring,unsigned>::iterator j=maps[m]->begin();j!=maps[m]->end();++j){capture->addText(j->first);number(j->second);}}
 number(self->m_nonLocalVariables.size());for(unsigned i=0;i<self->m_nonLocalVariables.size();++i)capture->addText(self->m_nonLocalVariables[i]);
 capture->add(self->m_Unrecovered130,1);capture->add(self->m_Unrecovered130+4,4);
}
// Pinned GCC 4.4 wstring COW representation: ASM decrements its int at data-8.
int references(const std::wstring& text){int value;std::memcpy(&value,reinterpret_cast<const char*>(text.c_str())-8,4);return value;}
void side(void* raw,autotest::Capture& out,bool ours){
 const Case& c=*static_cast<Case*>(raw);capture=&out;callbacks=0;
 uint64_t memory[(sizeof(CDynamicPropertyFile)+7)/8];std::memset(memory,0xa5,sizeof(memory));
 CDynamicPropertyFile* self=reinterpret_cast<CDynamicPropertyFile*>(memory);
 std::wstring dir=c.seed%3?std::wstring(30+c.seed,L'd'):L"",file=c.seed%2?L"Ж/settings.ini":L"",section=L"extra";
 if(c.mode==0){typedef void(*Fn)(CDynamicPropertyFile*,std::wstring,std::wstring,std::wstring);Fn fn=ours?nCtor:oCtor;if(!autotest::beginInvocation(out,fn))return;fn(self,dir,file,section);out.callCompleted=1;state(self);if(self->m_Unrecovered130[1]!=0xa5||self->m_Unrecovered130[2]!=0xa5||self->m_Unrecovered130[3]!=0xa5)out.issue=autotest::Capture::InvalidReport;oDtor(self);return;}
 oCtor(self,dir,file,section);
 std::wstring names[]={L"",L"a",L"A",L"aa",L"Ж",L"missing"};
 if(c.seed&16){self->m_intValues.reserve(16);self->m_floatValues.reserve(16);self->m_stringValues.reserve(16);}
 for(unsigned i=0;i<c.seed%6;++i){self->m_intValues.push_back(int(i)-3);self->m_floatValues.push_back(i-0.5f);self->m_stringValues.push_back(names[(i+2)%6]);self->m_intIndices[names[i]]=i;self->m_floatIndices[names[i]]=i;self->m_stringIndices[names[i]]=i;self->m_nonLocalVariables.push_back(names[i]);}
 self->m_callbacks.resize(8);for(unsigned i=0;i<8;++i)self->m_callbacks[i].push_back(&callback);
 if(c.mode==1){
    // Keep the owned buffers above glibc's small-allocation caches: omitting
    // any numeric vector or callback-array destruction must change this delta.
    if(c.seed&1)self->m_intValues.resize(4096+c.seed,123);
    if(c.seed&2)self->m_floatValues.resize(4096+c.seed,1.25f);
    size_t minimumRelease=0;
    if(self->m_intValues.capacity()>=4096)minimumRelease+=self->m_intValues.capacity()*sizeof(int);
    if(self->m_floatValues.capacity()>=4096)minimumRelease+=self->m_floatValues.capacity()*sizeof(float);
    for(unsigned i=0;i<self->m_callbacks.size();++i){
        if((i+c.seed)%3)self->m_callbacks[i].resize(2048+i+c.seed,&callback);
        if(self->m_callbacks[i].capacity()>=2048)
            minimumRelease+=self->m_callbacks[i].capacity()*sizeof(CDynamicPropertyFile::StatChangeCallback);
    }
    TSafePointer<CDynamicPropertyFile> reference;reference.setObject(self);
    int before=references(dir);
    typedef void(*Fn)(CDynamicPropertyFile*);Fn fn=ours?nDtor:oDtor;
    if(!autotest::beginInvocation(out,fn))return;
    long long heapBefore=static_cast<unsigned>(mallinfo().uordblks);
    fn(self);
    long long heapAfter=static_cast<unsigned>(mallinfo().uordblks);
    out.callCompleted=1;
    long long released=heapBefore-heapAfter;
    out.add(&released,sizeof(released));out.add(&minimumRelease,sizeof(minimumRelease));
    if(released<static_cast<long long>(minimumRelease)||callbacks!=0)
        out.issue=autotest::Capture::InvalidReport;
    number(reference.getObject()==NULL);int after=references(dir);
    out.add(&before,4);out.add(&after,4);
    if(reference.getObject()!=NULL||(dir.size()&&after!=before-1))out.issue=autotest::Capture::InvalidReport;
    for(unsigned i=0;i<6;++i){int refs=references(names[i]);out.add(&refs,4);}
    return;
 }
 unsigned bits[]={0,0x80000000,0x3f800000,0x7fc12345,0x7f800000,0xff800000};
 for(unsigned i=0;i<4;++i){std::wstring name=names[((c.seed/3)+(i%2))%6];unsigned result=0;
 if(c.mode==2){float value;std::memcpy(&value,&bits[(c.seed+i)%6],4);typedef unsigned(*Fn)(CDynamicPropertyFile*,const std::wstring&,float);Fn fn=ours?nFloat:oFloat;if(!i&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,value);}
 else if(c.mode==3){typedef unsigned(*Fn)(CDynamicPropertyFile*,const std::wstring&,int);Fn fn=ours?nInt:oInt;if(!i&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,int(c.seed*i)-123);}
 else if(c.mode==4){typedef unsigned(*Fn)(CDynamicPropertyFile*,const std::wstring&,const std::wstring&);Fn fn=ours?nString:oString;if(!i&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,names[(c.seed+i)%6]);}
 else {self->m_intIndices.clear();self->m_floatIndices.clear();self->m_stringIndices.clear();unsigned count=self->m_intValues.size();for(unsigned j=0;j<count;++j){if(j%3==0)self->m_intIndices[names[j]]=j;else if(j%3==1)self->m_floatIndices[names[j]]=j;else self->m_stringIndices[names[j]]=j;}std::wstring values[]={L"-123",L"0",L"1.25",L"nonsense",L"2147483647",L" 8 "};typedef void(*Fn)(CDynamicPropertyFile*,const std::wstring&,const std::wstring&);Fn fn=ours?nSetting:oSetting;if(!i&&!autotest::beginInvocation(out,fn))return;fn(self,name,values[(c.seed+i)%6]);}
 number(result);}
 out.callCompleted=1;number(callbacks);state(self);oDtor(self);
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,unsigned mode,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<120;++seed){Case c={mode,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    dynamic mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(bulk_dynamic_ctor,0,oCtor)
TEST(bulk_dynamic_dtor,1,oDtor)
TEST(bulk_dynamic_float_name,2,oFloat)
TEST(bulk_dynamic_int_name,3,oInt)
TEST(bulk_dynamic_string_name,4,oString)
TEST(bulk_dynamic_setting,5,oSetting)
