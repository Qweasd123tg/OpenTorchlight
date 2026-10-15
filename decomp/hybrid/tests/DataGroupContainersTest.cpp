#include <cstring>
#include <string>
#include <vector>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "DataGroup.h"

TL_ORIGINAL(void*, oldFindValue, (void*, const std::wstring&), "_ZN10CDataGroup18GetDataValueByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(unsigned, oldMatching, (void*, const std::wstring&, std::vector<void*>*), "_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
TL_ORIGINAL(bool, oldSetWide, (void*, const std::wstring&, const wchar_t*, bool), "_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_ORIGINAL(bool, oldSetString, (void*, const std::wstring&, const std::wstring&, bool), "_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(void*, oldAdd64, (void*, const std::wstring&, long long), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEx")
TL_ORIGINAL(void*, oldAdd32, (void*, const std::wstring&, int), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
extern "C" void* newFindValue(void*, const std::wstring&) __asm__("_ZN10CDataGroup18GetDataValueByNameERKSbIwSt11char_traitsIwESaIwEE");
extern "C" unsigned newMatching(void*, const std::wstring&, std::vector<void*>*) __asm__("_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE");
extern "C" bool newSetWide(void*, const std::wstring&, const wchar_t*, bool) __asm__("_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb");
extern "C" bool newSetString(void*, const std::wstring&, const std::wstring&, bool) __asm__("_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEES5_b");
extern "C" void* newAdd64(void*, const std::wstring&, long long) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEx");
extern "C" void* newAdd32(void*, const std::wstring&, int) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi");
TL_FUNCTION(valueName, "_ZN10CDataValue16GetDataValueNameEv")
TL_FUNCTION(groupName, "_ZN10CDataGroup12GetGroupNameEv")
TL_FUNCTION(findValue, "_ZN10CDataGroup18GetDataValueByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(setText, "_ZN10CDataValue14SetValueStringEPKw")
TL_FUNCTION(translateText, "_ZN10CDataValue19SetValueIsTranslateEv")
TL_FUNCTION(addWide, "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_FUNCTION(addString, "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
extern "C" char allocateValue[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeValue[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
TL_FUNCTION(constructValue, "_ZN10CDataValueC1EPKwP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(set64, "_ZN10CDataValue13SetValueInt64Ex")
TL_FUNCTION(set32, "_ZN10CDataValue13SetValueInt32Ei")
namespace {
typedef char GroupSize[(sizeof(CDataGroup) == 0x60) ? 1 : -1];
struct Case { unsigned operation, seed; };
autotest::Capture* output;
uint64_t buffers[5][12];
void* receiver; void* repository;
std::wstring names[4], query, text;
unsigned calls, frees, seed, operation;
long long scalar;
void number(unsigned n) { output->add(&n, sizeof(n)); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
void recordString(const std::wstring& s) { number(s.size()); output->add(s.data(), s.size()*sizeof(wchar_t)); }
template<class T> void put(void* p, unsigned offset, const T& v) { std::memcpy(static_cast<char*>(p)+offset, &v, sizeof(v)); }
template<class T> T get(void* p, unsigned offset) { T v; std::memcpy(&v, static_cast<char*>(p)+offset, sizeof(v)); return v; }
unsigned identity(void* p) { if (!p) return 0; for (unsigned i=0;i<5;++i) if(p==buffers[i]) return i+1; invalid(); return 99; }
const std::wstring& nameOf(void* p) { unsigned id=identity(p); number(10+id); ++calls; if(id<1||id>4) { invalid(); return query; } return names[id-1]; }
void* find(void* p, const std::wstring& name) { number(1); recordString(name); if(p!=receiver||name!=query||calls++!=0)invalid(); return seed&1 ? buffers[0] : 0; }
void set(void* p, const wchar_t* value) { number(2); recordString(value); if(p!=buffers[0]||text!=value||calls++!=1)invalid(); reinterpret_cast<unsigned char*>(p)[0x10]^=0x55; }
void translate(void* p) { number(3); if(p!=buffers[0]||calls++!=2)invalid(); reinterpret_cast<unsigned char*>(p)[0x11]^=0x33; }
void* addW(void* p,const std::wstring& name,const wchar_t* value,bool tr) { number(4);recordString(name);recordString(value);number(tr);if(p!=receiver||name!=query||text!=value||tr!=bool(seed&2)||calls++!=1)invalid();reinterpret_cast<unsigned char*>(p)[0x58]=1;return buffers[1]; }
void* addS(void* p,const std::wstring& name,const std::wstring& value,bool tr) { return addW(p,name,value.c_str(),tr); }
void* allocate(unsigned long size,const char* file,int line,const char* fn) { number(5);number(size);if(size!=0x38||file||line||fn||calls++!=0)invalid();return buffers[4]; }
void release(void* p) { number(6);number(identity(p));if(p!=buffers[4])invalid();++frees; }
void construct(void* p,const wchar_t* name,void* repo) { number(7);recordString(name);if(p!=buffers[4]||query!=name||repo!=repository||calls++!=1)invalid();if(seed&8)throw 23;std::memset(p,0x69,0x38); }
void scalar64(void* p,long long value) { number(8);output->add(&value,sizeof(value));if(p!=buffers[4]||value!=scalar||calls++!=2)invalid();put(p,0x18,value); }
void scalar32(void* p,int value) { number(9);output->add(&value,sizeof(value));if(p!=buffers[4]||value!=int(scalar)||calls++!=2)invalid();put(p,0x18,value); }
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);output=&out;seed=c.seed;operation=c.operation;calls=frees=0;
    uint64_t group[12];std::memset(group,0xa5,sizeof(group));std::memset(buffers,0x3c,sizeof(buffers));receiver=group;repository=buffers[3];
    query=seed%4==0?L"":seed%4==1?L"hit":seed%4==2?L"мир":L"missing";
    text=seed&4?L"текст / value":L"";
    names[0]=L"";names[1]=L"hit";names[2]=L"мир";names[3]=L"hit";
    void* data[4]={buffers[0],buffers[1],buffers[2],buffers[3]};
    unsigned count=(seed/4)%5,capacity=seed&16?1u:4u,grow=2;
    put(group,0x20,static_cast<void*>(data));put(group,0x28,count);put(group,0x2c,capacity);put(group,0x30,grow);
    put(group,0x38,static_cast<void*>(data));put(group,0x40,count);put(group,0x44,capacity);put(group,0x48,grow);
    put(group,0x18,repository);
    detour::Set patches;
    if(operation==0) TL_REDIRECT(patches,valueName,&nameOf);
    else if(operation==1) TL_REDIRECT(patches,groupName,&nameOf);
    else if(operation<4) { TL_REDIRECT(patches,findValue,&find);TL_REDIRECT(patches,setText,&set);TL_REDIRECT(patches,translateText,&translate);if(operation==2)TL_REDIRECT(patches,addWide,&addW);else TL_REDIRECT(patches,addString,&addS); }
    else { patches.redirect(allocateValue,allocateValue,&allocate);patches.redirect(freeValue,freeValue,&release);TL_REDIRECT(patches,constructValue,&construct);TL_REDIRECT(patches,set64,&scalar64);TL_REDIRECT(patches,set32,&scalar32); }
    if(patches.failed()){invalid();return;}
    if(operation==0) {
        typedef void*(*Fn)(void*,const std::wstring&);Fn fn=ours?newFindValue:oldFindValue;
        if(!autotest::beginInvocation(out,fn))return;void* result=fn(group,query);out.callCompleted=1;number(identity(result));
        void* wanted=0;for(unsigned i=0;i<count;++i){unsigned index=i<capacity?i:0;if(names[index]==query){wanted=data[index];break;}}if(result!=wanted)invalid();
    } else if(operation==1) {
        std::vector<void*> groups;if(seed&1)groups.reserve(8);if(seed&2)groups.push_back(buffers[3]);
        std::vector<void*> initialGroups=groups;std::vector<void*> expected=groups;for(unsigned i=0;i<count;++i){unsigned index=i<capacity?i:0;if(names[index]==query)expected.push_back(data[index]);}
        typedef unsigned(*Fn)(void*,const std::wstring&,std::vector<void*>*);Fn fn=ours?newMatching:oldMatching;
        std::vector<void*>* arg=seed%7==0?0:&groups;
        if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(group,query,arg);out.callCompleted=1;
        if(result!=(arg?expected.size():0)||groups!=(arg?expected:initialGroups))invalid();
        number(result);number(groups.size());for(unsigned i=0;i<groups.size();++i)number(identity(groups[i]));
    } else if(operation<4) {
        bool result;
        if(operation==2){typedef bool(*Fn)(void*,const std::wstring&,const wchar_t*,bool);Fn fn=ours?newSetWide:oldSetWide;if(!autotest::beginInvocation(out,fn))return;result=fn(group,query,text.c_str(),seed&2);}
        else{typedef bool(*Fn)(void*,const std::wstring&,const std::wstring&,bool);Fn fn=ours?newSetString:oldSetString;if(!autotest::beginInvocation(out,fn))return;result=fn(group,query,text,seed&2);}
        out.callCompleted=1;number(result);if(result!=!(seed&1)||calls!=(seed&1?2u+bool(seed&2):2u))invalid();
    } else {
        // Real TArrayList growth: empty, spare capacity, and a full allocation.
        unsigned shape=seed%3;count=shape==0?0u:2u;capacity=shape==1?4u:count;
        void** initial=shape==0?0:new void*[capacity];for(unsigned i=0;i<capacity;++i)initial[i]=data[i%4];
        put(group,0x20,static_cast<void*>(initial));put(group,0x28,count);put(group,0x2c,capacity);
        scalar=seed&4 ? -0x11223344556677LL : 0x1234567887654321LL;
        void* result=0;int exception=0;
        if(operation==4){typedef void*(*Fn)(void*,const std::wstring&,long long);Fn fn=ours?newAdd64:oldAdd64;if(!autotest::beginInvocation(out,fn))return;try{result=fn(group,query,scalar);}catch(int code){exception=code;}}
        else{typedef void*(*Fn)(void*,const std::wstring&,int);Fn fn=ours?newAdd32:oldAdd32;if(!autotest::beginInvocation(out,fn))return;try{result=fn(group,query,int(scalar));}catch(int code){exception=code;}}
        out.callCompleted=1;number(identity(result));out.add(&exception,sizeof(exception));number(frees);
        void** finalData=get<void**>(group,0x20);unsigned finalCount=get<unsigned>(group,0x28);
        if(exception!=(seed&8?23:0)||frees!=unsigned(bool(seed&8))||calls!=(seed&8?2u:3u)||
           result!=(seed&8?0:buffers[4])||finalCount!=count+unsigned(!(seed&8))||reinterpret_cast<unsigned char*>(group)[0x58]!=1)invalid();
        if(seed&8){if(finalData!=initial||get<unsigned>(group,0x2c)!=capacity)invalid();}
        else{for(unsigned i=0;i<count;++i)if(finalData[i]!=data[i%4])invalid();if(finalData[count]!=buffers[4])invalid();}
        if(shape==1)for(unsigned i=finalCount;i<capacity;++i)if(finalData[i]!=data[i%4])invalid();
        number(finalCount);for(unsigned i=0;i<finalCount;++i)number(identity(finalData[i]));
    }
    number(calls);recordString(query);recordString(text);
    if(get<void*>(group,0x18)!=repository)invalid();
    if(operation<4&&get<void*>(group,0x20)!=data)invalid();if(get<void*>(group,0x38)!=data)invalid();
    for(unsigned i=0;i<4;++i)if(data[i]!=buffers[i])invalid();
    put(group,0x20,static_cast<void*>(0));put(group,0x38,static_cast<void*>(0));put(group,0x18,static_cast<void*>(0));
    out.add(group,sizeof(group));out.add(buffers,sizeof(buffers));
}
void original(void* c,autotest::Capture& out){side(c,out,false);}void candidate(void* c,autotest::Capture& out){side(c,out,true);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
    autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<40;++seed){Case c={operation,seed};autotest::Outcome before,after;autotest::runChild(original,&c,before);autotest::runChild(candidate,&c,after);if(coverage.observe(host,before,after)){host->log("    data group operation %u seed %u exits %d/%d\n",operation,seed,before.childStatus,after.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;
}
}
TL_TEST(data_group_find_value){return run(host,0,"data_group_find_value",reinterpret_cast<uintptr_t>(&oldFindValue));}
TL_TEST(data_group_matching_groups){return run(host,1,"data_group_matching_groups",reinterpret_cast<uintptr_t>(&oldMatching));}
TL_TEST(data_group_set_wide){return run(host,2,"data_group_set_wide",reinterpret_cast<uintptr_t>(&oldSetWide));}
TL_TEST(data_group_set_string){return run(host,3,"data_group_set_string",reinterpret_cast<uintptr_t>(&oldSetString));}
TL_TEST(data_group_add_int64){return run(host,4,"data_group_add_int64",reinterpret_cast<uintptr_t>(&oldAdd64));}
TL_TEST(data_group_add_int32){return run(host,5,"data_group_add_int32",reinterpret_cast<uintptr_t>(&oldAdd32));}
