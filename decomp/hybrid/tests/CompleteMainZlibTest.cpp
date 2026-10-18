#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdint.h>
#include <OgreMemoryAllocatorConfig.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "GameMainRuntime.h"
typedef unsigned char Bytef;typedef unsigned long uLongf;
extern "C" int compress(Bytef*,uLongf*,const Bytef*,unsigned long);
extern "C" int uncompress(Bytef*,uLongf*,const Bytef*,unsigned long);
TL_ORIGINAL(bool,zlibUncompressOriginal,(std::wstring,unsigned int,unsigned int,unsigned int,char*),"_Z22uncompressFileInMemorySbIwSt11char_traitsIwESaIwEEjjjPc")
extern "C" bool zlibUncompressCandidate(std::wstring,unsigned int,unsigned int,unsigned int,char*) __asm__("_Z22uncompressFileInMemorySbIwSt11char_traitsIwESaIwEEjjjPc");
TL_ORIGINAL(CompressedFileBuffer,zlibCompressOriginal,(std::wstring,unsigned int&),"_Z12compressFileSbIwSt11char_traitsIwESaIwEERj")
extern "C" CompressedFileBuffer zlibCompressCandidate(std::wstring,unsigned int&) __asm__("_Z12compressFileSbIwSt11char_traitsIwESaIwEERj");
extern std::wstring UTF8ToUTF32(const std::string&);
namespace {
struct Case{unsigned mode,size,offset;};const Case*current;autotest::Capture*cap;
void word(unsigned x){cap->add(&x,sizeof(x));}
int failureCompress(Bytef*,uLongf* size,const Bytef* src,unsigned long n){word(*size);word(n);if(n)cap->add(src,n);return current->mode==4?-4:-5;}
void side(void*raw,autotest::Capture&out,bool ours,bool encode){
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;char folder[]="/tmp/otl-zlib-XXXXXX";if(!mkdtemp(folder))_exit(65);
 std::string path=std::string(folder)+"/"+(c.mode==1?"missing/":"")+"данные.bin";std::wstring wpath;wpath=UTF8ToUTF32(path);
 std::vector<char> input(c.size);for(unsigned i=0;i<c.size;++i)input[i]=static_cast<char>((i*i+17*i)%251);detour::Set patch;
 if(encode){
  if(c.mode!=2){std::ofstream f(path.c_str(),std::ios::binary);if(c.size)f.write(&input[0],c.size);}
  if(c.mode==4||c.mode==5)patch.redirect(reinterpret_cast<char*>(&compress),reinterpret_cast<char*>(&compress),&failureCompress);
  if(patch.failed())_exit(64);unsigned size=0x12345678;CompressedFileBuffer(*fn)(std::wstring,unsigned int&)=ours?zlibCompressCandidate:zlibCompressOriginal;
  if(autotest::beginInvocation(out,fn)){CompressedFileBuffer r=fn(wpath,size);out.callCompleted=1;word(size);word(r.data!=NULL);word(r.size);if(r.data){if(r.size)out.add(r.data,r.size);Ogre::NedAllocImpl::deallocBytes(r.data);}}
 }else{
  uLongf n=c.size+c.size/4+64;std::vector<char> zipped(c.offset+n);unsigned char empty=0;if(compress(reinterpret_cast<Bytef*>(&zipped[c.offset]),&n,c.size?reinterpret_cast<Bytef*>(&input[0]):&empty,c.size)!=0)_exit(66);
  if(c.mode==2)zipped[c.offset]^=0xff;if(c.mode==3&&n)n/=2;unsigned capacity=c.mode==4?c.size/2:c.size;
  bool(*fn)(std::wstring,unsigned int,unsigned int,unsigned int,char*)=ours?zlibUncompressCandidate:zlibUncompressOriginal;
  if(autotest::beginInvocation(out,fn)){bool r=fn(wpath,c.offset,n,capacity,&zipped[0]);out.callCompleted=1;word(r);}
  std::ifstream f(path.c_str(),std::ios::binary);word(f.is_open());std::string output((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());word(output.size());if(!output.empty())out.add(output.data(),output.size());
 }
 patch.restore();unlink(path.c_str());rmdir(folder);
}
void originalU(void*p,autotest::Capture&o){side(p,o,false,false);}void candidateU(void*p,autotest::Capture&o){side(p,o,true,false);}
void originalC(void*p,autotest::Capture&o){side(p,o,false,true);}void candidateC(void*p,autotest::Capture&o){side(p,o,true,true);}
int run(const tlhybrid_host*host,bool encode){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;const char*label=encode?"complete_main_compress_file":"complete_main_uncompress_memory";autotest::Coverage coverage(label,reinterpret_cast<uintptr_t>(encode?reinterpret_cast<void*>(&zlibCompressOriginal):reinterpret_cast<void*>(&zlibUncompressOriginal)));
 const unsigned sizes[]={0,1,31,4097};for(unsigned mode=0;mode<(encode?6u:5u);++mode)for(unsigned n=0;n<4;++n)for(unsigned off=0;off<(encode?1u:2u);++off){Case c={mode,sizes[n],off?17u:0u};bool ok=autotest::compareCase(encode?originalC:originalU,encode?candidateC:candidateU,&c,stats,host,label,cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
}
TL_TEST(complete_main_uncompress_memory){return run(host,false);}
TL_TEST(complete_main_compress_file){return run(host,true);}
