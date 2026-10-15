#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "DataGroup.h"
TL_ORIGINAL(void*,old_string,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
extern "C" void* new_string(void*,const std::wstring&,const std::wstring&,bool) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b");
TL_ORIGINAL(void*,old_bool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEb")
extern "C" void* new_bool(void*,const std::wstring&,bool) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEb");
TL_ORIGINAL(void*,old_double,(void*,const std::wstring&,double),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEd")
extern "C" void* new_double(void*,const std::wstring&,double) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEd");
TL_ORIGINAL(void*,old_float,(void*,const std::wstring&,float),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf")
extern "C" void* new_float(void*,const std::wstring&,float) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf");
TL_ORIGINAL(void*,old_uint,(void*,const std::wstring&,unsigned),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEj")
extern "C" void* new_uint(void*,const std::wstring&,unsigned) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEj");
TL_ORIGINAL(void*,old_group,(void*,const std::wstring&),"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* new_group(void*,const std::wstring&) __asm__("_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE");
extern "C" char allocateValue[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeValue[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
TL_FUNCTION(ctorValue,"_ZN10CDataValueC1EPKwP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(ctorGroup,"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(setString,"_ZN10CDataValue14SetValueStringEPKw")
TL_FUNCTION(translate,"_ZN10CDataValue19SetValueIsTranslateEv")
TL_FUNCTION(setBool,"_ZN10CDataValue12SetValueBoolEb")
TL_FUNCTION(setDouble,"_ZN10CDataValue15SetValueFloat64Ed")
TL_FUNCTION(setFloat,"_ZN10CDataValue15SetValueFloat32Ef")
TL_FUNCTION(setUInt,"_ZN10CDataValue14SetValueUInt32Ej")
namespace {
struct Case{unsigned op,seed;};
autotest::Capture* output;uint64_t value[12],previous[4][12];void* receiver;void* repository;std::wstring name,text;unsigned op,seed,calls,frees;void** initial;unsigned count,capacity;
void num(unsigned n){output->add(&n,4);}void invalid(){output->issue=autotest::Capture::InvalidReport;}void str(const std::wstring& s){num(s.size());output->add(s.data(),s.size()*sizeof(wchar_t));}
template<class T>void put(void*p,unsigned offset,const T&v){std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}template<class T>T get(void*p,unsigned offset){T v;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof(v));return v;}
void* allocate(unsigned long size,const char* file,int line,const char* fn){num(1);num(size);if(size!=(op==5?0x60u:0x38u)||file||line||fn||calls++!=0||get<unsigned char>(receiver,0x58)!=1)invalid();return value;}
void release(void*p){num(2);if(p!=value)invalid();++frees;}
void construct(void*p,const wchar_t*n,void*r){num(3);str(n);if(p!=value||name!=n||r!=repository||calls++!=1)invalid();if(seed%8==0)throw 23;std::memset(p,0x69,0x38);}
void group(void*p,const std::wstring&n,void*parent,unsigned values,unsigned groups,void*r){num(4);str(n);num(values);num(groups);if(p!=value||n!=name||parent!=receiver||values!=20||groups!=10||r||calls++!=1)invalid();if(seed%8==0)throw 23;std::memset(p,0x69,0x60);}
void scalar(void*p,const void* bytes,unsigned size){if(p!=value||calls++!=2)invalid();output->add(bytes,size);std::memcpy(static_cast<char*>(p)+0x18,bytes,size);if(seed%8==1)throw 24;}
void setB(void*p,bool v){num(5);scalar(p,&v,sizeof(v));}void setD(void*p,double v){num(6);scalar(p,&v,sizeof(v));}void setF(void*p,float v){num(7);scalar(p,&v,sizeof(v));}void setU(void*p,unsigned v){num(8);scalar(p,&v,sizeof(v));}
void setS(void*p,const wchar_t*v){num(9);str(v);if(text!=v)invalid();unsigned id=0x1234;scalar(p,&id,4);}
void translated(void*p){num(10);if(p!=value||calls++!=3||get<unsigned>(receiver,0x28)!=count+1)invalid();reinterpret_cast<unsigned char*>(p)[0x30]=8;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);op=c.op;seed=c.seed;output=&out;calls=frees=0;uint64_t object[12];std::memset(object,0xa5,sizeof(object));std::memset(value,0x3c,sizeof(value));std::memset(previous,0x52,sizeof(previous));receiver=object;repository=previous[3];name=seed&1?L"NAME/мир":L"";text=seed&2?L"value/строка":L"";put(object,0x18,repository);
 count=seed%3==0?0:2;capacity=seed%3==1?4:count;initial=capacity?new void*[capacity]:0;for(unsigned i=0;i<capacity;++i)initial[i]=previous[i%4];unsigned offset=op==5?0x38:0x20;put(object,offset,static_cast<void*>(initial));put(object,offset+8,count);put(object,offset+12,capacity);unsigned grow=2;put(object,offset+16,grow);
 detour::Set patches;patches.redirect(allocateValue,allocateValue,&allocate);patches.redirect(freeValue,freeValue,&release);TL_REDIRECT(patches,ctorValue,&construct);TL_REDIRECT(patches,ctorGroup,&group);TL_REDIRECT(patches,setString,&setS);TL_REDIRECT(patches,translate,&translated);TL_REDIRECT(patches,setBool,&setB);TL_REDIRECT(patches,setDouble,&setD);TL_REDIRECT(patches,setFloat,&setF);TL_REDIRECT(patches,setUInt,&setU);if(patches.failed()){invalid();return;}
 void*result=0;int exception=0;unsigned bits[]={0,0x80000000,0x3fc00000,0x7fc12345,0x7f800000,0xff800000};float f;unsigned rawbits=bits[(seed/2)%6];std::memcpy(&f,&rawbits,4);double d=seed&4?-3.75:2.5;unsigned u=seed&4?0xffffffffu:0x80000000u;
 if(op==0){typedef void*(*Fn)(void*,const std::wstring&,const std::wstring&,bool);Fn fn=ours?new_string:old_string;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name,text,bool(seed&4));}
 if(op==1){typedef void*(*Fn)(void*,const std::wstring&,bool);Fn fn=ours?new_bool:old_bool;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name,bool(seed&4));}
 if(op==2){typedef void*(*Fn)(void*,const std::wstring&,double);Fn fn=ours?new_double:old_double;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name,d);}
 if(op==3){typedef void*(*Fn)(void*,const std::wstring&,float);Fn fn=ours?new_float:old_float;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name,f);}
 if(op==4){typedef void*(*Fn)(void*,const std::wstring&,unsigned);Fn fn=ours?new_uint:old_uint;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name,u);}
 if(op==5){typedef void*(*Fn)(void*,const std::wstring&);Fn fn=ours?new_group:old_group;if(!autotest::beginInvocation(out,fn))return;result=fn(object,name);}
 out.callCompleted=1;num(calls);num(frees);out.add(&exception,4);num(result==value);unsigned expectedException=seed%8==0?23:op!=5&&seed%8==1?24:0;if(exception!=int(expectedException)||frees!=unsigned(seed%8==0)||result!=(expectedException?0:value))invalid();void**finalData=get<void**>(object,offset);unsigned finalCount=get<unsigned>(object,offset+8);if(finalCount!=count+unsigned(!expectedException))invalid();for(unsigned i=0;i<count;++i)if(finalData[i]!=previous[i%4])invalid();if(!expectedException&&finalData[count]!=value)invalid();if(expectedException&&(finalData!=initial||get<unsigned>(object,offset+12)!=capacity))invalid();num(finalCount);num(get<unsigned>(object,offset+12));if(get<void*>(object,0x18)!=repository)invalid();put(object,offset,static_cast<void*>(0));put(object,0x18,static_cast<void*>(0));out.add(object,sizeof(object));out.add(value,sizeof(value));out.add(previous,sizeof(previous));str(name);str(text);delete[] finalData;
}
void original(void*c,autotest::Capture&out){side(c,out,false);}void candidate(void*c,autotest::Capture&out){side(c,out,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<48;++seed){if(seed%8==0||(op!=5&&seed%8==1))continue;Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    data add op %u seed %u exits %d/%d issues %u/%u\n",op,seed,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(data_group_new_add_string){return run(host,0,"data_group_new_add_string",reinterpret_cast<uintptr_t>(&old_string));}
TL_TEST(data_group_new_add_bool){return run(host,1,"data_group_new_add_bool",reinterpret_cast<uintptr_t>(&old_bool));}
TL_TEST(data_group_new_add_double){return run(host,2,"data_group_new_add_double",reinterpret_cast<uintptr_t>(&old_double));}
TL_TEST(data_group_new_add_float){return run(host,3,"data_group_new_add_float",reinterpret_cast<uintptr_t>(&old_float));}
TL_TEST(data_group_new_add_uint){return run(host,4,"data_group_new_add_uint",reinterpret_cast<uintptr_t>(&old_uint));}
TL_TEST(data_group_new_add_group){return run(host,5,"data_group_new_add_group",reinterpret_cast<uintptr_t>(&old_group));}
