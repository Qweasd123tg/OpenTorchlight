#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "PathController.h"
#include "PathNode.h"
TL_ORIGINAL(void,pathNameNativeCtor,(CPathController*,CResourceManager*),"_ZN15CPathControllerC1EP16CResourceManager")
TL_ORIGINAL(void,pathNameNativeDtor,(CPathController*),"_ZN15CPathControllerD1Ev")
TL_ORIGINAL(void,pathNameOriginal,(CPathController*,const std::wstring&),"_ZN15CPathController11setPathNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void pathNameCandidate(CPathController*,const std::wstring&) __asm__("_ZN15CPathController11setPathNameERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(pathNameText,"_ZN9CPathNode7setTextERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case { unsigned count,name,alias; };
const wchar_t*names[]={L"",L"route",L"\u0422\u0440\u043e\u043f\u0430",L"\U0001f642\u03a9",L"a _ b",L"\ud7ff\ue000\U0010ffff"};
autotest::Capture*cap;CPathNode*identities[9];unsigned count;
// PathName calls one direct collaborator and never reads the node's layout.
// These identities stop at that typed API boundary; no PathNode lifecycle or
// rendering behavior is claimed by this comparison.
void text(CPathNode*node,const std::wstring&value){
    unsigned index=0;while(index<count&&identities[index]!=node)++index;
    cap->add(&index,sizeof index);cap->addText(value);
}
void initWide(uintptr_t address,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),sizeof p);if(!p)new(reinterpret_cast<void*>(address))std::wstring(value);}
void side(void*raw,autotest::Capture&out,bool ours){
    Case c=*static_cast<Case*>(raw);cap=&out;count=c.count;
    initWide(0x1428728);
    initWide(0x1428748,L"MONSTERS");
    void*storage=Ogre::NedAllocImpl::allocBytes(sizeof(CPathController),0,0,0);
    CPathController*path=static_cast<CPathController*>(storage);pathNameNativeCtor(path,NULL);
    unsigned long tokens[9];for(unsigned i=0;i<count;++i){tokens[i]=i;identities[i]=reinterpret_cast<CPathNode*>(&tokens[i]);path->m_pathNodes.add(identities[i]);}
    path->m_pathName=names[c.name];std::wstring input=names[(c.name+1)%6];
    detour::Set boundary;TL_REDIRECT(boundary,pathNameText,&text);if(boundary.failed())_exit(64);
    void(*fn)(CPathController*,const std::wstring&)=ours?pathNameCandidate:pathNameOriginal;
    if(autotest::beginInvocation(out,fn)){fn(path,c.alias?path->m_pathName:input);out.callCompleted=1;}
    out.addText(path->m_pathName);unsigned retained=path->m_pathNodes.size();out.add(&retained,sizeof retained);
    boundary.restore();pathNameNativeDtor(path);Ogre::NedAllocImpl::deallocBytes(path);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;autotest::Stats stats={0,0,0};unsigned cases=0;int failures=0;autotest::Coverage coverage("complete_path_name",reinterpret_cast<uintptr_t>(pathNameOriginal));
    const unsigned counts[]={0,1,3,9};for(unsigned n=0;n<4;++n)for(unsigned name=0;name<6;++name)for(unsigned alias=0;alias<2;++alias){Case c={counts[n],name,alias};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_path_name",cases++,&coverage);TL_CHECK(failures,ok);}
    coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
}
TL_TEST(complete_path_name){return systems_fixture::isolated(&worker,host);}
