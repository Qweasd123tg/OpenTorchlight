#include "SmallMassCompare.h"
#include "TRepository.h"
#include <map>

TL_ORIGINAL(void, nameOriginal, (void*,std::wstring&), "_ZN10CDataValue16SetDataValueNameERSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, stringOriginal, (void*,const wchar_t*), "_ZN10CDataValue14SetValueStringEPKw")
extern "C" void nameCandidate(void*,std::wstring&) __asm__("_ZN10CDataValue16SetDataValueNameERSbIwSt11char_traitsIwESaIwEE");
extern "C" void stringCandidate(void*,const wchar_t*) __asm__("_ZN10CDataValue14SetValueStringEPKw");

namespace {
using namespace smallmass;
typedef TRepository<std::wstring> Repo;
typedef std::map<unsigned,std::wstring> Values;
typedef std::map<std::wstring,unsigned> IDs;
typedef std::map<unsigned,unsigned short> Counts;
void execute(Case& c,bool ours,autotest::Capture& out) {
    output=&out;input=&c;autotest::g_arenaUsed=0;
    Repo repository(L"default");
    Values& values=field<Values>(&repository,8);
    IDs& ids=field<IDs>(&repository,0x38);
    Counts& counts=field<Counts>(&repository,0x68);
    unsigned mode=c.index%16;
    field<unsigned>(&repository,0)=10;
    if(mode!=1) {
        values[0]=L"zero";values[1]=mode==8?L"default":L"old";values[2]=L"retained";
        for(Values::iterator i=values.begin();i!=values.end();++i) {
            ids[i->second]=i->first;counts[i->first]=2;
        }
        counts[1]=mode==4?1:mode==6?0:mode==12?65535:2;
        if(mode==7)counts.erase(1);
        if(mode==9)ids.erase(values[1]);
        if(mode==10)values.erase(1);
        if(mode==11)ids[L"old"]=5;
    }
    unsigned oldID=mode==2?~0u:mode==3?0:mode==13?0x80000000u:mode==14?99:1;
    unsigned char* self=static_cast<unsigned char*>(object(0x38));
    std::memset(self,0x3a,0x38);
    field<bool>(self,0x10)=(c.index&1)!=0;
    field<unsigned>(self,0x18)=oldID;
    field<unsigned>(self,0x20)=oldID;
    field<Repo*>(self,0x28)=mode==0?NULL:&repository;
    static const unsigned types[]={1,5,8,0xffffffff};
    field<unsigned>(self,0x30)=types[(c.index/16)%4];
    static const wchar_t* texts[]={L"",L"new",L"old",L"default",L"Ж string"};
    std::wstring incoming=texts[(c.index/4)%5];
    const wchar_t* pointer=incoming.c_str();
    std::wstring* name=&incoming;
    if(c.index&64) {
        Values::iterator i=values.find(1);
        if(i!=values.end()) {pointer=i->second.c_str();name=&i->second;}
    }
    if(c.op==0)autotest::invoke<void (*)(void*,std::wstring&),void*,std::wstring&>(
        out,ours?nameCandidate:nameOriginal,self,*name);
    else autotest::invoke(out,ours?stringCandidate:stringOriginal,self,c.index%7?pointer:NULL);
    out.add(self,0x38);
    number(field<unsigned>(&repository,0));
    number(values.size());
    for(Values::iterator i=values.begin();i!=values.end();++i){number(i->first);text(i->second);}
    number(ids.size());
    for(IDs::iterator i=ids.begin();i!=ids.end();++i){text(i->first);number(i->second);}
    number(counts.size());
    for(Counts::iterator i=counts.begin();i!=counts.end();++i){number(i->first);number(i->second);}
    text(incoming);
}
}
TL_TEST(advance_data_name){return smallmass::run(host,0,"advance_data_name",(uintptr_t)nameOriginal,execute,192);}
TL_TEST(advance_data_string){return smallmass::run(host,1,"advance_data_string",(uintptr_t)stringOriginal,execute,192);}
