#include "AutoTest.h"
#include "GameMainRuntime.h"
#include "MainFileSandbox.h"
#include <cstdio>
#include <stdint.h>
TL_ORIGINAL(bool,archiveCompressOriginal,(std::wstring,std::wstring,std::wstring,bool),"_Z13compressFilesSbIwSt11char_traitsIwESaIwEES2_S2_b")
extern "C" bool archiveCompressCandidate(std::wstring,std::wstring,std::wstring,bool) __asm__("_Z13compressFilesSbIwSt11char_traitsIwESaIwEES2_S2_b");
namespace {
struct Case{unsigned mode,count;};
unsigned get32(const std::string& data,unsigned at){unsigned result=0;for(unsigned i=0;i<4;++i)result|=static_cast<unsigned char>(data[at+i])<<(i*8);return result;}
void archiveCapture(autotest::Capture& out,const std::string& path){
 std::ifstream f(path.c_str(),std::ios::binary);unsigned exists=f.is_open();out.add(&exists,sizeof(exists));if(!exists)return;std::string data((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());unsigned size=data.size();out.add(&size,sizeof(size));if(size<8){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned count=get32(data,4),end=8,payload=0;if(count>1000){out.issue=autotest::Capture::InvalidReport;return;}for(unsigned i=0;i<count;++i){if(end+24>size){out.issue=autotest::Capture::InvalidReport;return;}payload+=get32(data,end+4);unsigned chars=get32(data,end+20);end+=24+chars*2;if(end>size){out.issue=autotest::Capture::InvalidReport;return;}}
 if(payload>size-end){out.issue=autotest::Capture::InvalidReport;return;}
 // Native writes a contiguous header/payload prefix, then exports an unwritten
 // allocation tail. Compare every written byte and the complete file length.
 if(end+payload<=65536)out.add(data.data(),end+payload);else{uint64_t hash=14695981039346656037ULL;for(unsigned i=0;i<end+payload;++i)hash=(hash^static_cast<unsigned char>(data[i]))*1099511628211ULL;out.add(&hash,sizeof(hash));}
}
void side(void* raw,autotest::Capture& out,bool ours){Case c=*static_cast<Case*>(raw);mainfiles::Sandbox s;std::string input=s.save+"input/";mkdir(input.c_str(),0700);mainfiles::put(input+"ignored.txt","ignored");
 for(unsigned i=0;i<c.count;++i){char n[40];std::sprintf(n,"slot_%02u.bin",i);std::string name=i==1?"данные.bin":n;unsigned length=(c.mode==5&&i==0)?3000010u:i*47u;std::string data(length,'\0');uint32_t seed=123+i;for(unsigned j=0;j<length;++j){seed=seed*1664525u+1013904223u;data[j]=seed>>24;}mainfiles::put(input+name,data);mainfiles::stamp(input+name,1700000000+i);}
 std::string output=s.base+"archive.bin";if(c.mode==2)output=s.base+"missing/archive.bin";if(c.mode==3)mkdir(output.c_str(),0700);if(c.mode==4)mainfiles::clear(input);
 bool(*fn)(std::wstring,std::wstring,std::wstring,bool)=ours?archiveCompressCandidate:archiveCompressOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(UTF8ToUTF32(input),c.mode==6?L"*.none":L"*.bin",UTF8ToUTF32(output),c.mode==1);out.callCompleted=1;out.add(&r,sizeof(r));}
 struct stat st;if(!stat(output.c_str(),&st)&&S_ISREG(st.st_mode))archiveCapture(out,output);else{unsigned absent=0;out.add(&absent,sizeof(absent));}mainfiles::capture(out,s.base,".runicgames");
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_compress_files){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_compress_files",reinterpret_cast<uintptr_t>(&archiveCompressOriginal));const unsigned counts[]={0,1,2,9,10,11,24};for(unsigned mode=0;mode<7;++mode)for(unsigned i=0;i<7;++i){if(mode==5&&i>2)continue;Case c={mode,counts[i]};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_compress_files",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
