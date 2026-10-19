#include "AutoTest.h"
#include "tests/Detour.h"
#include "GameMainRuntime.h"
#include "MainFileSandbox.h"
#include <stdint.h>
#include <cstring>
#include <cstdio>
typedef unsigned char Bytef;typedef unsigned long uLongf;extern "C" int compress(Bytef*,uLongf*,const Bytef*,unsigned long);
TL_ORIGINAL(bool,archiveUncompressOriginal,(std::wstring,std::wstring,bool),"_Z15uncompressFilesSbIwSt11char_traitsIwESaIwEES2_b")
extern "C" bool archiveUncompressCandidate(std::wstring,std::wstring,bool) __asm__("_Z15uncompressFilesSbIwSt11char_traitsIwESaIwEES2_b");
TL_FUNCTION(archiveMessage,"_Z10MessageBoxPvPKwS1_i")
TL_FUNCTION(archiveSetTime,"_ZN10FILESYSTEM11setFileTimeERKSbIwSt11char_traitsIwESaIwEExxx")
namespace {
struct Case {unsigned mode,count,flags;};autotest::Capture* cap;const Case* current;std::wstring directory;
void word(unsigned x){cap->add(&x,sizeof(x));}
int question(void* owner,const wchar_t* text,const wchar_t* title,int flags){word(owner!=NULL);cap->addText(std::wstring(text));cap->addText(std::wstring(title));word(flags);return current->flags&4?1:0;}
void setTime(const std::wstring& path,long long modified,long long access,long long created){cap->addText(path.substr(directory.size()));cap->add(&modified,sizeof(modified));cap->add(&access,sizeof(access));cap->add(&created,sizeof(created));}
void u32(std::vector<char>& b,unsigned at,unsigned x){for(unsigned j=0;j<4;++j)b[at+j]=x>>(j*8);}
void i64(std::vector<char>& b,unsigned at,long long x){for(unsigned j=0;j<8;++j)b[at+j]=static_cast<unsigned long long>(x)>>(j*8);}
void side(void* raw,autotest::Capture& out,bool ours) {
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;mainfiles::Sandbox s;std::string dest=s.save+"out/";if(c.mode!=7)mkdir(dest.c_str(),0700);directory=UTF8ToUTF32(dest);
 std::vector<std::string> payloads,names;std::vector<std::vector<char> > zipped;unsigned header=8;
 for(unsigned i=0;i<c.count;++i){char n[50];std::sprintf(n,"slot%u.bin",i);names.push_back(n);if(i==1)names[i]="你.bin";std::string data(i*37+17,'\0');for(unsigned j=0;j<data.size();++j)data[j]=(j*3+i)%251;payloads.push_back(data);uLongf size=data.size()+64;std::vector<char> z(size);if(compress(reinterpret_cast<Bytef*>(&z[0]),&size,reinterpret_cast<const Bytef*>(data.data()),data.size()))_exit(66);z.resize(size);if(c.mode==5)z[0]^=0xff;if(c.mode==6)z.resize(size/2);zipped.push_back(z);header+=24+UTF8ToUTF32(names[i]).size()*2;
  if(c.mode>=1&&c.mode<=4){mainfiles::put(dest+names[i],"local:"+names[i]);mainfiles::stamp(dest+names[i],1700000000);}
  if(c.mode==8)mkdir((dest+names[i]).c_str(),0700);
 }
 std::vector<char> data(header);u32(data,0,c.mode==9?9:1);u32(data,4,c.count);unsigned pos=8,offset=header;
 for(unsigned i=0;i<c.count;++i){std::wstring name=UTF8ToUTF32(names[i]);u32(data,pos,offset);u32(data,pos+4,zipped[i].size());u32(data,pos+8,c.mode==10?payloads[i].size()/2:payloads[i].size());long long timestamp=c.mode==2?1700000000LL:c.mode==3?1700000010LL:1699999990LL;i64(data,pos+12,timestamp);u32(data,pos+20,name.size());pos+=24;for(unsigned j=0;j<name.size();++j){data[pos++]=name[j];data[pos++]=name[j]>>8;}data.insert(data.end(),zipped[i].begin(),zipped[i].end());offset+=zipped[i].size();}
 std::string archive=s.base+"backup.zip";if(c.mode!=11)mainfiles::put(archive,std::string(&data[0],data.size()));g_bFileCheckDone=c.flags&1;g_bUseLocalFile=c.flags&2;
 detour::Set d;TL_REDIRECT(d,archiveMessage,&question);TL_REDIRECT(d,archiveSetTime,&setTime);if(d.failed())_exit(64);
 bool(*fn)(std::wstring,std::wstring,bool)=ours?archiveUncompressCandidate:archiveUncompressOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(UTF8ToUTF32(archive),directory,c.flags&8);out.callCompleted=1;word(r);}word(g_bFileCheckDone);word(g_bUseLocalFile);mainfiles::capture(out,s.base,".runicgames");d.restore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_uncompress_files) {
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_uncompress_files",reinterpret_cast<uintptr_t>(&archiveUncompressOriginal));
 const unsigned counts[]={0,1,2,11};for(unsigned mode=0;mode<12;++mode)for(unsigned i=0;i<4;++i)for(unsigned flags=0;flags<(mode>=1&&mode<=4?16u:1u);++flags){Case c={mode,counts[i],flags};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_uncompress_files",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
