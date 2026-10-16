#include "AutoTest.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(void, oldc75a20, (const std::wstring&, std::vector<std::wstring>&), "_ZN10FILESYSTEM16GetDirectoryListERKSbIwSt11char_traitsIwESaIwEERSt6vectorIS3_SaIS3_EE")
extern "C" void newc75a20(const std::wstring&, std::vector<std::wstring>&) __asm__("_ZN10FILESYSTEM16GetDirectoryListERKSbIwSt11char_traitsIwESaIwEERSt6vectorIS3_SaIS3_EE");
TL_ORIGINAL(std::wstring, oldc75c70, (const std::wstring&, const std::wstring&), "_ZN10FILESYSTEM21FindFullDirectoryNameERKSbIwSt11char_traitsIwESaIwEES5_")
extern "C" std::wstring newc75c70(const std::wstring&, const std::wstring&) __asm__("_ZN10FILESYSTEM21FindFullDirectoryNameERKSbIwSt11char_traitsIwESaIwEES5_");
TL_ORIGINAL(void, oldc75ec0, (const std::wstring&, TArrayList<std::wstring>&, const std::wstring&), "_ZN10FILESYSTEM20GetFileListRecursiveERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES5_")
extern "C" void newc75ec0(const std::wstring&, TArrayList<std::wstring>&, const std::wstring&) __asm__("_ZN10FILESYSTEM20GetFileListRecursiveERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES5_");
TL_ORIGINAL(std::wstring, oldc76190, (const std::wstring&, const std::wstring&, const std::wstring&), "_ZN10FILESYSTEM16FindFullFileNameERKSbIwSt11char_traitsIwESaIwEES5_S5_")
extern "C" std::wstring newc76190(const std::wstring&, const std::wstring&, const std::wstring&) __asm__("_ZN10FILESYSTEM16FindFullFileNameERKSbIwSt11char_traitsIwESaIwEES5_S5_");

namespace {
std::wstring root;
const wchar_t* prefixes[]={L"",L"alpha",L"a",L"beta",L"none",L".",L"alpha.txt",L"gamma",L"nested"};
const wchar_t* extensions[]={L"",L".txt",L".bin",L"txt",L".other",L".missing"};
void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);
    std::wstring path=root;
    if(c.index%4==1)path+=L"alpha/";
    if(c.index%4==2)path+=L"empty/";
    if(c.index%4==3)path+=L"absent/";
    if(c.op==0) {
        std::vector<std::wstring> values;
        if(c.index%2)values.push_back(L"preexisting");
        typedef void(*Fn)(const std::wstring&,std::vector<std::wstring>&);Fn fn=ours?newc75a20:oldc75a20;
        if(!autotest::beginInvocation(out,fn))return;fn(path,values);out.callCompleted=1;
        unsigned n=values.size();out.add(&n,4);for(unsigned i=0;i<n;++i)out.addText(values[i]);
    } else if(c.op==1) {
        std::wstring prefix=prefixes[c.index/4%9];
        typedef std::wstring(*Fn)(const std::wstring&,const std::wstring&);Fn fn=ours?newc75c70:oldc75c70;
        if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(path,prefix);out.callCompleted=1;out.addText(value);
    } else if(c.op==2) {
        TArrayList<std::wstring> values(c.index%3+1);if(c.index%2)values.add(L"preexisting");
        std::wstring pattern=c.index/4%3==0?L"*.*":c.index/4%3==1?L"*.txt":L"*.absent";
        typedef void(*Fn)(const std::wstring&,TArrayList<std::wstring>&,const std::wstring&);Fn fn=ours?newc75ec0:oldc75ec0;
        if(!autotest::beginInvocation(out,fn))return;fn(path,values,pattern);out.callCompleted=1;
        unsigned n=values.size();out.add(&n,4);for(unsigned i=0;i<n;++i)out.addText(values[i]);
    } else {
        std::wstring prefix=prefixes[c.index/4%9],extension=extensions[c.index/9%6];
        typedef std::wstring(*Fn)(const std::wstring&,const std::wstring&,const std::wstring&);Fn fn=ours?newc76190:oldc76190;
        if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(path,prefix,extension);out.callCompleted=1;out.addText(value);
    }
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
int runFile(const tlhybrid_host* host,unsigned op,const char* name,uint64_t address)
{
    char folder[]="/tmp/otl-state-files-XXXXXX";if(!mkdtemp(folder))return 1;
    const char* dirs[]={"alpha","alpha/nested","beta","empty",".hidden"};
    const char* files[]={"alpha.txt","alpha.other","beta.bin","alpha/deep.txt","alpha/nested/final.txt",".hidden/ignored.txt"};
    bool ok=true;
    for(unsigned i=0;i<5;++i){std::string p=std::string(folder)+"/"+dirs[i];if(mkdir(p.c_str(),0700))ok=false;}
    for(unsigned i=0;i<6;++i){std::string p=std::string(folder)+"/"+files[i];FILE*f=fopen(p.c_str(),"wb");if(!f)ok=false;else{fputs("state fixture",f);fclose(f);}}
    root=STRINGS::StringConvertToWide(std::string(folder)+"/");
    int result=ok?runCases(host,op,72,name,address,original,candidate):1;
    for(unsigned i=0;i<6;++i){std::string p=std::string(folder)+"/"+files[i];unlink(p.c_str());}
    for(int i=4;i>=0;--i){std::string p=std::string(folder)+"/"+dirs[i];rmdir(p.c_str());}rmdir(folder);
    return result;
}
}
TL_TEST(state_file_c75a20){return runFile(host,0,"state_file_c75a20",(uint64_t)(uintptr_t)oldc75a20);}
TL_TEST(state_file_c75c70){return runFile(host,1,"state_file_c75c70",(uint64_t)(uintptr_t)oldc75c70);}
TL_TEST(state_file_c75ec0){return runFile(host,2,"state_file_c75ec0",(uint64_t)(uintptr_t)oldc75ec0);}
TL_TEST(state_file_c76190){return runFile(host,3,"state_file_c76190",(uint64_t)(uintptr_t)oldc76190);}
