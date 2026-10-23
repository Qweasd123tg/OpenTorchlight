#include "AutoTest.h"
#include "tests/Detour.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
TL_ORIGINAL(std::wstring, oldName, (const std::wstring&), "_ZN10FILESYSTEM11GetFileNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" std::wstring newName(const std::wstring&) __asm__("_ZN10FILESYSTEM11GetFileNameERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(std::wstring, oldDirectory, (const std::wstring&), "_ZN10FILESYSTEM12GetDirectoryERKSbIwSt11char_traitsIwESaIwEE")
extern "C" std::wstring newDirectory(const std::wstring&) __asm__("_ZN10FILESYSTEM12GetDirectoryERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool, oldExists, (const std::string&), "_ZN10FILESYSTEM10FileExistsERKSs")
extern "C" bool newExists(const std::string&) __asm__("_ZN10FILESYSTEM10FileExistsERKSs");
TL_ORIGINAL(int, oldIntLine, (const std::string&, const std::string&), "_ZN10LinuxUtils10GetIntLineERKSsS1_")
extern "C" int newIntLine(const std::string&, const std::string&) __asm__("_ZN10LinuxUtils10GetIntLineERKSsS1_");
TL_FUNCTION(replaceWide, "_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
namespace {
struct Case { unsigned operation, index; const char* file; };
autotest::Capture* output;unsigned replacementCalls;
std::wstring replaceForDirectory(std::wstring text,const std::wstring& find,const std::wstring& replacement) {
    ++replacementCalls;output->addText(text);output->addText(find);output->addText(replacement);
    // GetDirectory only composes this call. Empty basenames make the actual
    // replacement loop nonterminating, so expose every argument and propagate
    // a distinctive collaborator result on the entire input family.
    return std::wstring(L"replacement-result:")+text+L"|"+find+L"|"+replacement;
}
const wchar_t* paths[] = {L"", L"a", L"/", L"\\", L"a/b", L"a\\b", L"a/b\\c", L"a\\b/c", L"/a/a", L"a/a/a", L"a//b/", L"a\\\\b\\", L"relative.long/name.ext", L"/a b/\x0438\x043c\x044f", L"../x/../x"};
const char* lines[] = {"", "MemTotal: 1234 kB\n", "MemTotal: 1234 kB", "other: 42\nMemTotal: 5678\n", "MemTotal: none\nMemTotal: 9\n", "MemTotal: -16 kB\n", "MemTotal: 2147483648\n", "MemTotal: 0001024z\n", "MemTotalSuffix: 17\n", " MemTotal: 99\n", "MemTotal: \n", "MemTotal: 12.75\n", "MemTotal: 9223372036854775807\n", "MemTotal: 9223372036854775808\n", "MemTotal: abc34x56\n"};
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c=*static_cast<Case*>(raw);
    if(c.operation<2) {
        std::wstring input(paths[c.index%15]);
        if(c.index>=15) input.insert(input.begin()+input.size()/2, wchar_t(0));
        detour::Set replacements;replacementCalls=0;output=&out;
        if(c.operation==1)TL_REDIRECT(replacements,replaceWide,replaceForDirectory);
        if(replacements.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        typedef std::wstring(*Fn)(const std::wstring&);Fn fn=c.operation==0?(ours?newName:oldName):(ours?newDirectory:oldDirectory);
        if(!autotest::beginInvocation(out,fn))return;
        std::wstring value=fn(input);out.callCompleted=1;out.addText(input);out.addText(value);
        if(c.operation==1){out.add(&replacementCalls,sizeof(replacementCalls));if(replacementCalls!=1)out.issue=autotest::Capture::InvalidReport;}
    } else if(c.operation==2) {
        std::string input=c.index%3==0?c.file:c.index%3==1?std::string(c.file)+"-absent":"";
        typedef bool(*Fn)(const std::string&);Fn fn=ours?newExists:oldExists;
        if(!autotest::beginInvocation(out,fn))return;bool value=fn(input);out.callCompleted=1;out.add(&value,sizeof(value));out.addText(input);
    } else {
        std::string input=c.index<30?c.file:std::string(c.file)+"-absent";
        std::string key=c.index%30<15?"MemTotal":"";
        typedef int(*Fn)(const std::string&,const std::string&);Fn fn=ours?newIntLine:oldIntLine;
        if(!autotest::beginInvocation(out,fn))return;int value=fn(input,key);out.callCompleted=1;out.add(&value,sizeof(value));out.addText(key);
    }
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uint64_t address) {
    autotest::Coverage coverage(name,address);
    char path[]="/tmp/otl-accessor-file-XXXXXX";int fd=mkstemp(path);if(fd<0)return 1;close(fd);
    unsigned count=operation==3?45:30;
    for(unsigned i=0;i<count;++i) {
        if(operation==3){std::ofstream file(path);file<<lines[i%15];}
        Case c={operation,i,path};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)){host->log("    %s case %u original status %d report %u issue %u started %u completed %u; candidate status %d report %u issue %u started %u completed %u\n",name,i,a.childStatus,a.reportValid,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.reportValid,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);unlink(path);coverage.report(host);return 1;}
    }
    unlink(path);coverage.report(host);return 0;
}
}
TL_TEST(preserve_linux_int_line){return run(host,3,"preserve_linux_int_line",(uint64_t)(uintptr_t)oldIntLine);}
