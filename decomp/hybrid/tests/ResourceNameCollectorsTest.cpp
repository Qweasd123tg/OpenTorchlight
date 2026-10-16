#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "TArrayList.h"
TL_ORIGINAL(void, oldAffixNames, (void*, TArrayList<std::wstring>&), "_ZN19CEffectGroupManager13getAffixNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
extern "C" void newAffixNames(void*, TArrayList<std::wstring>&) __asm__("_ZN19CEffectGroupManager13getAffixNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE");
TL_ORIGINAL(void,oldHierarchyNames,(void*,TArrayList<std::wstring>*),"_ZN10CHierarchy12getTypeNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
extern "C" void newHierarchyNames(void*,TArrayList<std::wstring>*) __asm__("_ZN10CHierarchy12getTypeNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE");
TL_ORIGINAL(std::wstring,oldCommandString,(void*,const std::wstring&,std::wstring),"_ZN14CCmdLineParser14GetStringParamERKSbIwSt11char_traitsIwESaIwEES3_")
extern "C" std::wstring newCommandString(void*,const std::wstring&,std::wstring) __asm__("_ZN14CCmdLineParser14GetStringParamERKSbIwSt11char_traitsIwESaIwEES3_");
namespace {
struct Case {unsigned count, prefix, grow, order, mode;};
TL_ORIGINAL(void, oldSetNames, (void*, TArrayList<std::wstring>&), "_ZN5CSets11getSetNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
extern "C" void newSetNames(void*, TArrayList<std::wstring>&) __asm__("_ZN5CSets11getSetNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE");
TL_ORIGINAL(void, oldMissileNames, (void*, TArrayList<std::wstring>&), "_ZN17CMissilePreloader15getMissileNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
extern "C" void newMissileNames(void*, TArrayList<std::wstring>&) __asm__("_ZN17CMissilePreloader15getMissileNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE");
struct AffixNamesInput {uint64_t base[3]; std::map<std::wstring, void*> names; uint64_t guard[3];};
void text(autotest::Capture& out, const std::wstring& value) {
    size_t n=value.size(); out.add(&n,sizeof(n)); if(n)out.add(value.data(),n*sizeof(wchar_t));
}
template<class Value, unsigned Prefix> struct NamesInput {uint64_t base[Prefix];std::map<std::wstring,Value> names;uint64_t guard[3];};
template<class Value,unsigned Prefix> void collect(void* p, autotest::Capture& out, bool ours) {
    const Case& c=*static_cast<Case*>(p); NamesInput<Value,Prefix> input;
    std::memset(input.base,0x5a,sizeof(input.base)); std::memset(input.guard,0xa5,sizeof(input.guard));
    for(unsigned i=0;i<c.count;++i){unsigned key=c.order?c.count-i-1:i;
        std::wstring name(key%3==0?L"Ж_LONG_AFFIX_":key%3==1?L"B_":L"ä_");
        name+=wchar_t(L'A'+key); input.names[name]=Value();
    }
    TArrayList<std::wstring> result(c.grow);
    for(unsigned i=0;i<c.prefix;++i) result.add(L"preserved prefix");
    typedef void(*Fn)(void*,TArrayList<std::wstring>&);Fn fn=c.mode==1?(ours?newSetNames:oldSetNames):c.mode==2?(ours?newMissileNames:oldMissileNames):(ours?newAffixNames:oldAffixNames);
    if(c.mode==3){void(*hierarchyFn)(void*,TArrayList<std::wstring>*)=ours?newHierarchyNames:oldHierarchyNames;if(!autotest::beginInvocation(out,hierarchyFn))return;hierarchyFn(&input,&result);}
    else {if(!autotest::beginInvocation(out,fn))return;fn(&input,result);}out.callCompleted=1;
    unsigned count=result.size();out.add(&count,4);
    for(unsigned i=0;i<count;++i)text(out,result[i]);
    if(count!=c.prefix+input.names.size())out.issue=autotest::Capture::InvalidReport;
    for(unsigned i=0;i<c.prefix;++i)if(result[i]!=L"preserved prefix")out.issue=autotest::Capture::InvalidReport;
    unsigned n=c.prefix;
    for(typename std::map<std::wstring,Value>::const_iterator i=input.names.begin();i!=input.names.end();++i,++n){
        if(n>=count||result[n]!=i->first||i->second!=Value())out.issue=autotest::Capture::InvalidReport;
        text(out,i->first);
    }
    out.add(input.base,sizeof(input.base));out.add(input.guard,sizeof(input.guard));
}
void side(void* p,autotest::Capture& out,bool ours){Case& c=*static_cast<Case*>(p);if(c.mode==1)collect<unsigned,6>(p,out,ours);else if(c.mode==3)collect<unsigned,8>(p,out,ours);else collect<void*,3>(p,out,ours);}
void before(void* p,autotest::Capture& out){side(p,out,false);}
void after(void* p,autotest::Capture& out){side(p,out,true);}
}
namespace {
int runNames(const tlhybrid_host* host,unsigned mode,const char* name,uintptr_t address) {
    autotest::Coverage coverage(name,address);
    const unsigned sizes[]={0,1,2,5,9,17}, grows[]={1,2,7};
    for(unsigned n=0;n<108;++n){Case c={sizes[n%6],(n/6)%3,grows[(n/18)%3],n/54,mode};autotest::Outcome a,b;
        autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        if(coverage.observe(host,a,b)){host->log("    name collector mode %u case %u exits %d/%d\n",mode,n,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(resource_affix_name_collector){return runNames(host,0,"resource_affix_name_collector",(uintptr_t)&oldAffixNames);}
TL_TEST(resource_set_name_collector){return runNames(host,1,"resource_set_name_collector",(uintptr_t)&oldSetNames);}
TL_TEST(resource_missile_name_collector){return runNames(host,2,"resource_missile_name_collector",(uintptr_t)&oldMissileNames);}

TL_TEST(resource_hierarchy_name_collector){return runNames(host,3,"resource_hierarchy_name_collector",(uintptr_t)&oldHierarchyNames);}
namespace {
struct CommandInput {uint64_t base[2];std::map<std::wstring,std::vector<std::wstring> > parameters;uint64_t guard[2];};
void commandSide(void* raw,autotest::Capture& out,bool ours){
    unsigned n=*static_cast<unsigned*>(raw);CommandInput input;std::memset(input.base,0x5a,sizeof(input.base));std::memset(input.guard,0xa5,sizeof(input.guard));
    const wchar_t* keys[]={L"",L"A",L"AA",L"Ж"};
    for(unsigned i=0;i<n%5;++i){std::vector<std::wstring>& values=input.parameters[keys[i]];for(unsigned j=0;j<(n/5+i)%4;++j)values.push_back(keys[(i+j+1)%4]);}
    std::map<std::wstring,std::vector<std::wstring> > before=input.parameters;
    std::wstring query=keys[(n/7)%4],fallback=keys[(n/13)%4],expected=fallback;
    std::map<std::wstring,std::vector<std::wstring> >::const_iterator found=before.find(query);
    if(found!=before.end()&&!found->second.empty())expected=found->second[0];
    typedef std::wstring(*Fn)(void*,const std::wstring&,std::wstring);Fn fn=ours?newCommandString:oldCommandString;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(&input,query,fallback);out.callCompleted=1;
    text(out,result);if(result!=expected||input.parameters!=before)out.issue=autotest::Capture::InvalidReport;out.add(input.base,sizeof(input.base));out.add(input.guard,sizeof(input.guard));
}
void oldCommand(void*p,autotest::Capture&o){commandSide(p,o,false);}void newCommand(void*p,autotest::Capture&o){commandSide(p,o,true);}
}
TL_TEST(resource_command_string){autotest::Coverage coverage("resource_command_string",(uintptr_t)&oldCommandString);for(unsigned n=0;n<120;++n){autotest::Outcome a,b;autotest::runChild(oldCommand,&n,a);autotest::runChild(newCommand,&n,b);if(coverage.observe(host,a,b)){host->log("    command string seed %u issue %u/%u\n",n,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return 0;}
