#include "AutoTest.h"
#include "LinuxUtils.h"
TL_ORIGINAL(unsigned int,scanOriginal,(unsigned int),"_Z24LinuxMapVirtual2Scancodej")
extern "C" unsigned int scanCandidate(unsigned int) __asm__("_Z24LinuxMapVirtual2Scancodej");
namespace {void side(void*p,autotest::Capture&out,bool ours){unsigned key=*static_cast<unsigned*>(p);unsigned(*fn)(unsigned)=ours?scanCandidate:scanOriginal;if(autotest::beginInvocation(out,fn)){unsigned r=fn(key);out.callCompleted=1;out.add(&r,sizeof(r));}}void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}}
TL_TEST(complete_win_mouse_scan_map){autotest::Stats stats={0,0,0};int failures=0;autotest::Coverage coverage("complete_win_mouse_scan_map",reinterpret_cast<uintptr_t>(&scanOriginal));for(unsigned key=0;key<223;++key){bool ok=autotest::compareCase(original,candidate,&key,stats,host,"complete_win_mouse_scan_map",key,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=223);}
