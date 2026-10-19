#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "LinuxUtils.h"
TL_ORIGINAL(int, systemsCPU, (), "_ZN10LinuxUtils15GetCPUFrequencyEv")
extern "C" int newCPU() __asm__("_ZN10LinuxUtils15GetCPUFrequencyEv");
extern "C" int statImport(int,const char*,struct stat*) __asm__("__xstat");
extern "C" std::filebuf* fileOpenImport(std::filebuf*,const char*,std::ios_base::openmode) __asm__("_ZNSt13basic_filebufIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode");
namespace {
struct Case { unsigned exists, content; };
const Case* current;
autotest::Capture* capture;
detour::Set* openPatch;
char filename[80];
int statRoute(int version,const char* path,struct stat* data) {
    unsigned ok=!std::strcmp(path,"/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
    capture->add(&ok,sizeof(ok));capture->add(&version,sizeof(version));
    if(!ok){capture->issue=autotest::Capture::InvalidReport;return -1;}
    std::memset(data,0,sizeof(*data));return current->exists?0:-1;
}
std::filebuf* route(std::filebuf* self,const char* path,std::ios_base::openmode mode) {
    unsigned id=!std::strcmp(path,"/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq")?1:!std::strcmp(path,"/proc/cpuinfo")?2:0;
    capture->add(&id,sizeof(id));capture->add(&mode,sizeof(mode));
    if(!id)capture->issue=autotest::Capture::InvalidReport;
    openPatch->restore();
    std::filebuf* result=fileOpenImport(self,id?filename:path,mode);
    openPatch->redirect(reinterpret_cast<char*>(&fileOpenImport),reinterpret_cast<char*>(&fileOpenImport),&route);
    return result;
}
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);current=&c;capture=&out;
    const char* content[]={"3200000\n","1999999\n","0\n","-1234567\n","1234","","nonsense\n","cpu MHz\t: 2876.250\n","cpu MHz : 1799\nother\n","999999999999999999999\n"};
    std::strcpy(filename,"/tmp/otl-cpu-XXXXXX");int fd=mkstemp(filename);
    if(fd<0){out.issue=autotest::Capture::InvalidReport;return;}
    unsigned size=std::strlen(content[c.content]);
    if(write(fd,content[c.content],size)!=size){out.issue=autotest::Capture::InvalidReport;close(fd);unlink(filename);return;}
    close(fd);
    detour::Set statPatch,files;openPatch=&files;
    statPatch.redirect(reinterpret_cast<char*>(&statImport),reinterpret_cast<char*>(&statImport),&statRoute);files.redirect(reinterpret_cast<char*>(&fileOpenImport),reinterpret_cast<char*>(&fileOpenImport),&route);
    if(statPatch.failed()||files.failed()){out.issue=autotest::Capture::InvalidReport;unlink(filename);return;}
    int(*fn)()=ours?newCPU:systemsCPU;
    if(autotest::beginInvocation(out,fn)){int value=fn();out.callCompleted=1;out.add(&value,sizeof(value));}
    files.restore();statPatch.restore();unlink(filename);
}
void original(void* raw,autotest::Capture& out){side(raw,out,false);}
void candidate(void* raw,autotest::Capture& out){side(raw,out,true);}
}
TL_TEST(complete_linux_cpu_frequency) {
    autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;
    autotest::Coverage coverage("complete_linux_cpu_frequency",reinterpret_cast<uintptr_t>(&systemsCPU));
    for(unsigned e=0;e<2;++e)for(unsigned i=0;i<10;++i){Case c={e,i};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_linux_cpu_frequency",cases++,&coverage);TL_CHECK(failures,ok);}
    coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
