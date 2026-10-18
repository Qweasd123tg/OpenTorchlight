#include <new>
#include <string>
#include <map>
#include "UnitResourceList.h"
#include "TRepository.h"
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,unitLoadOld,(CUnitResourceList*,ERESOURCE_GROUPS,std::wstring,std::wstring,bool,CDataGroup*),"_ZN17CUnitResourceList8loadFileE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_bP10CDataGroup")
extern "C" void unitLoadNew(CUnitResourceList*,ERESOURCE_GROUPS,std::wstring,std::wstring,bool,CDataGroup*) __asm__("_ZN17CUnitResourceList8loadFileE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_bP10CDataGroup");
TL_FUNCTION(unitLoadParse,"_ZN17CUnitResourceList14parseChildFileERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(unitLoadAdd,"_ZN17CUnitResourceList10addNewItemERKSbIwSt11char_traitsIwESaIwEEP10CDataGroupb")
namespace {
struct Case{unsigned index;};
struct State{autotest::Capture* out;CUnitResourceList* self;CDataGroup* parsed;unsigned index,parseCalls,addCalls;};
State* active;
void number(unsigned x){active->out->add(&x,sizeof(x));}
void text(const std::wstring& s){number(s.size());active->out->add(s.data(),s.size()*sizeof(wchar_t));}
void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
CDataGroup* parse(CUnitResourceList* self,const std::wstring& path,bool create){if(self!=active->self)invalid();number(1);text(path);number(create);++active->parseCalls;return active->parsed;}
void add(CUnitResourceList* self,const std::wstring& name,CDataGroup* data,bool overwrite){if(self!=active->self||data!=active->parsed)invalid();number(2);text(name);number(overwrite);++active->addCalls;}
CDataGroup* group(const wchar_t* name){std::wstring empty;TRepository<std::wstring>* repository=new TRepository<std::wstring>(empty);return new CDataGroup(std::wstring(name),0,4,4,repository);}
void snapshot(CDataGroup* data){
    text(data->GetGroupName());number(data->GetNumberOfDataValues());number(data->GetNumberOfDataGroups());
    const wchar_t* keys[]={L"NAME",L"FILEITEM",L"DATFILE",L"BASEFILE",L"EXTRA"};
    for(unsigned i=0;i<5;++i)text(data->GetDataValue(keys[i],L"<missing>"));
    number(data->GetDataValue(L"RESOURCEGROUP",999u));number(data->GetDataValue(L"DONTCREATE",false));
}
void side(Case& c,bool ours,autotest::Capture& out){
    State s;active=&s;s.out=&out;s.index=c.index;s.parseCalls=s.addCalls=0;
    const unsigned emptyCells[]={0x14dd9c8,0x14dd9d8,0x14dda88,0x152f138};
    for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(emptyCells[i]))std::wstring();
    const wchar_t* groupNames[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};
    for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(0x152f160+8*i))std::wstring(groupNames[i]);
    CUnitResourceList self;s.self=&self;
    unsigned shape=c.index%8;
    s.parsed=shape==0?0:group(L"INPUT");
    if(s.parsed){
        if(shape!=1)s.parsed->AddDataValue(L"NAME",shape==2?L"":shape==3?L"MiXeD":L"Лесник",false);
        s.parsed->SetDataValue(L"DONTCREATE",bool(shape==4));
        s.parsed->AddDataValue(L"FILEITEM",L"old.dat",false);
        s.parsed->AddDataValue(L"DATFILE",L"old/path.dat",false);
        s.parsed->AddDataValue(L"BASEFILE",L"base/template.dat",false);
        s.parsed->AddDataValue(L"RESOURCEGROUP",99u);
        s.parsed->AddDataValue(L"EXTRA",L"preserved",false);
    }
    CDataGroup* parent=(c.index&8)?group(L"PARENT"):0;
    if(parent){CDataGroup* prior=parent->AddDataGroup(L"EXISTING");prior->AddDataValue(L"EXTRA",L"before",false);}
    const wchar_t* paths[]={L"media/units/MiXeD.DAT",L"plain.dat",L"media/Лесник.dat",L"folder/"};
    std::wstring path(paths[(c.index/16)%4]),resourceName=(c.index&64)?L"customЖ":L"ITEMS";
    typedef void(*Fn)(CUnitResourceList*,ERESOURCE_GROUPS,std::wstring,std::wstring,bool,CDataGroup*);
    Fn fn=ours?unitLoadNew:unitLoadOld;
    if(!autotest::beginInvocation(out,fn))return;
    fn(&self,static_cast<ERESOURCE_GROUPS>((c.index/32)%4),resourceName,path,(c.index&128)!=0,parent);out.callCompleted=1;
    number(s.parseCalls);number(s.addCalls);number(self.m_loadedDataGroups.size());
    for(unsigned i=0;i<self.m_loadedDataGroups.size();++i)snapshot(self.m_loadedDataGroups[i]);
    if(parent){snapshot(parent);for(unsigned i=0;i<parent->GetNumberOfDataGroups();++i)snapshot(parent->GetDataGroup(i));delete parent;}
}
void before(void* c,autotest::Capture& out){side(*static_cast<Case*>(c),false,out);}
void after(void* c,autotest::Capture& out){side(*static_cast<Case*>(c),true,out);}
}
TL_TEST(unit_resource_load_file){
    detour::Set hooks;TL_REDIRECT(hooks,unitLoadParse,&parse);TL_REDIRECT(hooks,unitLoadAdd,&add);if(hooks.failed())return 1;
    autotest::Coverage coverage("unit_resource_load_file",0xe7eb00);
    for(unsigned i=0;i<256;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log(" unit load case%u status%d/%d\n",i,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=256||coverage.different||coverage.missing;
}
