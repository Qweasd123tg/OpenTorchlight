#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long,oldRead64,(void*,void*),"_ZN17COgreResourceFile12Get64BitDataEP11COgreReader")
extern "C" long long newRead64(void*,void*) __asm__("_ZN17COgreResourceFile12Get64BitDataEP11COgreReader");
TL_FUNCTION(readData,"_ZN11COgreReader4readEPvj")
namespace {struct Case{unsigned seed;};autotest::Capture*output;void*expected;unsigned seed,calls;uint64_t payload;
void read(void*p,void*buffer,unsigned size){++calls;output->add(&size,4);uint64_t before;std::memcpy(&before,buffer,8);output->add(&before,8);if(p!=expected||size!=8||before)output->issue=autotest::Capture::InvalidReport;std::memcpy(buffer,&payload,seed%9);if(seed&16)throw 23;}
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;output=&out;calls=0;uint64_t reader[4],object[2];std::memset(reader,0xa5,sizeof(reader));std::memset(object,0x3c,sizeof(object));expected=reader;payload=seed&1?0xfedcba9876543210ULL:0x123456789abcdefULL;detour::Set patches;TL_REDIRECT(patches,readData,&read);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef long long(*Fn)(void*,void*);Fn fn=ours?newRead64:oldRead64;if(!autotest::beginInvocation(out,fn))return;long long result=0;int exception=0;result=fn(object,reader);out.callCompleted=1;if(calls!=1||exception!=(seed&16?23:0))out.issue=autotest::Capture::InvalidReport;out.add(&calls,4);out.add(&exception,4);out.add(&result,8);out.add(reader,sizeof(reader));out.add(object,sizeof(object));}
void original(void*c,autotest::Capture&out){side(c,out,false);}void candidate(void*c,autotest::Capture&out){side(c,out,true);}}
TL_TEST(ogre_resource_int64_read){autotest::Coverage coverage("ogre_resource_int64_read",reinterpret_cast<uintptr_t>(&oldRead64));for(unsigned seed=0;seed<36;++seed){if(seed&16)continue;Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    int64 read seed %u exits %d/%d\n",seed,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
