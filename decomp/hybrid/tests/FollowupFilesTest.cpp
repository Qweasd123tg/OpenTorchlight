#include "SmallMassCompare.h"
#include <cerrno>
#include <new>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
TL_ORIGINAL(std::wstring, oldApplication, (), "_ZN10FILESYSTEM18GetApplicationPathEv")
extern "C" std::wstring nextApplication() __asm__("_ZN10FILESYSTEM18GetApplicationPathEv");
TL_ORIGINAL(std::wstring, oldAbsolute, (const std::wstring&,const std::wstring&), "_ZN10FILESYSTEM20AssembleAbsolutePathERKSbIwSt11char_traitsIwESaIwEES5_")
extern "C" std::wstring nextAbsolute(const std::wstring&,const std::wstring&) __asm__("_ZN10FILESYSTEM20AssembleAbsolutePathERKSbIwSt11char_traitsIwESaIwEES5_");
TL_ORIGINAL(bool, oldExists, (const wchar_t*), "_ZN10FILESYSTEM10FileExistsEPKw")
extern "C" bool nextExists(const wchar_t*) __asm__("_ZN10FILESYSTEM10FileExistsEPKw");
TL_ORIGINAL(long long, oldTime, (const wchar_t*), "_ZN10FILESYSTEM11GetFileTimeEPKw")
extern "C" long long nextTime(const wchar_t*) __asm__("_ZN10FILESYSTEM11GetFileTimeEPKw");
TL_FUNCTION(appDirectory,"_ZN10LinuxUtils9GetAppDirEv")
extern std::wstring applicationCache __asm__("_ZZN10FILESYSTEM18GetApplicationPathEvE12absolutePath");
extern unsigned long long applicationGuard __asm__("_ZGVZN10FILESYSTEM18GetApplicationPathEvE12absolutePath");
namespace {
std::string directory;
unsigned appCalls;
std::wstring appDirectoryValue;
std::wstring appDirectorySpy(){++appCalls;return appDirectoryValue;}
std::wstring applicationCaseValue(unsigned index, bool cached) {
 switch(index) {
 case 0: return cached?L"/cached app/":L"";
 case 1: return L"/";
 case 2: return L"relative/../app";
 case 3: return L"/space path/with trailing /";
 case 4: return L"/\u0438\u0433\u0440\u0430/\u00e9/";
 case 5: {const wchar_t embedded[]={L'/',L'a',0,L'b',L'/'};return std::wstring(embedded,5);}
 case 6: return std::wstring(4096,L'x');
 default: return std::wstring(L"/astral/")+wchar_t(0x1f642)+L"/";
 }
}
void execute(smallmass::Case& c,bool ours,autotest::Capture& out) {
 using namespace smallmass;output=&out;
 if(c.op==0) {
  // Cold, initialized empty, shared cache, and unshared cache each see eight values.
  const unsigned state=c.index/8, variation=c.index%8;
  const std::wstring cached=state>=2?applicationCaseValue(variation,true):std::wstring();
  new(&applicationCache)std::wstring(cached);
  std::wstring alias=state>=2?applicationCache:std::wstring();
  if(state==3)applicationCache[0]=applicationCache[0];
  appDirectoryValue=applicationCaseValue(variation,false);
  applicationGuard=state==0?0:1;appCalls=0;
  detour::Set patches;TL_REDIRECT(patches,appDirectory,&appDirectorySpy);
  if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef std::wstring(*Fn)();Fn fn=ours?nextApplication:oldApplication;
  if(!autotest::beginInvocation(out,fn))return;
  std::wstring value=fn();
  out.callCompleted=1;text(value);text(applicationCache);text(alias);number(unsigned(applicationGuard&1));number(appCalls);
  const std::wstring expected=state>=2?cached:appDirectoryValue;
  if(value!=expected||applicationCache!=cached||alias!=(state>=2?cached:std::wstring())||
     !(applicationGuard&1)||appCalls!=unsigned(state<2))out.issue=autotest::Capture::InvalidReport;
 } else if(c.op==1) {
  const wchar_t* bases[]={L"",L"base/",L"base",L"/base space/",L"C:\\base\\"};
  const wchar_t* paths[]={L"",L"file",L"/absolute",L"//double",L"x/y",L"\\windows",L".",L"../up",L" spaced/thing"};
  std::wstring base=bases[c.index%5],path=paths[(c.index/5)%9];
  typedef std::wstring(*Fn)(const std::wstring&,const std::wstring&);Fn fn=ours?nextAbsolute:oldAbsolute;
  if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(base,path);out.callCompleted=1;text(result);text(base);text(path);
 } else {
  const char* names[]={"/file","/missing","/folder","/alias","/broken","/file/child","/unicod\xc3\xa9"};
  std::string raw=directory+names[c.index%7];std::wstring path;
  // Only the last synthetic UTF-8 filename requires decoding.
  if(c.index%7==6){std::string prefix=directory+"/unicod";path.assign(prefix.begin(),prefix.end());path+=wchar_t(0xe9);}else path.assign(raw.begin(),raw.end());
  if(c.op==2){typedef bool(*Fn)(const wchar_t*);Fn fn=ours?nextExists:oldExists;if(!autotest::beginInvocation(out,fn))return;bool result=fn(path.c_str());out.callCompleted=1;number(result);}
  else{typedef long long(*Fn)(const wchar_t*);Fn fn=ours?nextTime:oldTime;if(!autotest::beginInvocation(out,fn))return;long long result=fn(path.c_str());out.callCompleted=1;out.add(&result,sizeof(result));}
  text(path);
 }
}
int files(const tlhybrid_host* host,unsigned op,const char* name,uint64_t address) {
 char pattern[]="/tmp/otl-followup-files-XXXXXX";char* made=mkdtemp(pattern);if(!made)return 1;directory=made;
 const std::string file=directory+"/file",folder=directory+"/folder",alias=directory+"/alias",broken=directory+"/broken",unicode=directory+"/unicod\xc3\xa9";
 bool setup=mkdir(folder.c_str(),0700)==0;
 FILE* stream=fopen(file.c_str(),"wb");if(stream){fputs("synthetic\n",stream);fclose(stream);}else setup=false;
 stream=fopen(unicode.c_str(),"wb");if(stream){fputs("utf8\n",stream);fclose(stream);}else setup=false;
 setup=symlink("file",alias.c_str())==0&&setup;setup=symlink("missing",broken.c_str())==0&&setup;
 struct utimbuf times;times.actime=123456789;times.modtime=123456789;
 setup=utime(file.c_str(),&times)==0&&utime(unicode.c_str(),&times)==0&&setup;
 int code=setup?smallmass::run(host,op,name,address,execute,28):1;
 unlink(alias.c_str());unlink(broken.c_str());unlink(file.c_str());unlink(unicode.c_str());rmdir(folder.c_str());rmdir(directory.c_str());return code;
}
}
TL_TEST(followup_files_application){return smallmass::run(host,0,"followup_files_application",(uint64_t)(uintptr_t)oldApplication,execute,32);}
TL_TEST(followup_files_absolute){return smallmass::run(host,1,"followup_files_absolute",(uint64_t)(uintptr_t)oldAbsolute,execute,45);}
TL_TEST(followup_files_exists){return files(host,2,"followup_files_exists",(uint64_t)(uintptr_t)oldExists);}
TL_TEST(followup_files_time){return files(host,3,"followup_files_time",(uint64_t)(uintptr_t)oldTime);}
