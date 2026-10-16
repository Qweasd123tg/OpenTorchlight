#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <utime.h>
#include <unistd.h>
#include "AutoTest.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(unsigned char,oByte,nByte,(FILE*),"_ZN10FILESYSTEM8ReadByteEP8_IO_FILE")
DECL(std::string,oRead,nRead,(FILE*),"_ZN10FILESYSTEM10ReadStringEP8_IO_FILE")
DECL(std::wstring,oWide,nWide,(FILE*),"_ZN10FILESYSTEM11ReadWStringEP8_IO_FILE")
DECL(std::wstring,oRemove,nRemove,(const std::wstring&),"_ZN10FILESYSTEM14RemoveFileNameERKSbIwSt11char_traitsIwESaIwEE")
DECL(bool,oOlder,nOlder,(const std::wstring&,const std::wstring&),"_ZN10FILESYSTEM11FileIsOlderERKSbIwSt11char_traitsIwESaIwEES5_")
DECL(void,oList,nList,(const std::wstring&,TArrayList<std::wstring>&,std::wstring),"_ZN10FILESYSTEM11GetFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_")
DECL(void,oSorted,nSorted,(const std::wstring&,TArrayList<std::wstring>&,std::wstring),"_ZN10FILESYSTEM17GetFileListSortedERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_")
#undef DECL
namespace{
struct Case{unsigned mode,seed;};
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);
 if(c.mode<3){FILE*file=tmpfile();if(!file){out.issue=autotest::Capture::InvalidReport;return;}
  if(c.mode==0){unsigned char bytes[16];for(unsigned i=0;i<16;++i)bytes[i]=(c.seed*33+i*17)&255;unsigned length=c.seed%17;fwrite(bytes,1,length,file);rewind(file);unsigned steps=c.seed%20+1;typedef unsigned char(*Fn)(FILE*);Fn fn=ours?nByte:oByte;if(!autotest::beginInvocation(out,fn))return;for(unsigned i=0;i<steps;++i){unsigned char result=fn(file);out.add(&result,1);}}
  else if(c.mode==1){for(unsigned i=0;i<c.seed%20;++i){unsigned char v=((c.seed+i*31)%255)+1;fwrite(&v,1,1,file);}unsigned char zero=0;fwrite(&zero,1,1,file);unsigned char tail=9;fwrite(&tail,1,1,file);rewind(file);typedef std::string(*Fn)(FILE*);Fn fn=ours?nRead:oRead;if(!autotest::beginInvocation(out,fn))return;out.addText(fn(file));}
  else{for(unsigned i=0;i<c.seed%20;++i){unsigned short v=(c.seed+i)%5==0?0xd834:(c.seed+i)%5==1?0xdd1e:(c.seed+i)%5==2?0xffff:0x0416+i;fwrite(&v,2,1,file);}unsigned short zero=0;fwrite(&zero,2,1,file);unsigned short tail=12;fwrite(&tail,2,1,file);rewind(file);typedef std::wstring(*Fn)(FILE*);Fn fn=ours?nWide:oWide;if(!autotest::beginInvocation(out,fn))return;out.addText(fn(file));}
  out.callCompleted=1;long position=ftell(file);int eof=feof(file),error=ferror(file);out.add(&position,sizeof(position));out.add(&eof,4);out.add(&error,4);fclose(file);return;
 }
 if(c.mode==3){std::wstring paths[]={L"",L"file",L"dir/file",L"dir/",L"/",L"a\\b\\file",L"a/b\\file",L"a\\b/file",L"Ж/путь/имя",std::wstring(L"a\0/b",4),L"a//b",L"a/../x"};typedef std::wstring(*Fn)(const std::wstring&);Fn fn=ours?nRemove:oRemove;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(paths[c.seed%12]);out.callCompleted=1;out.addText(result);return;}
 char pattern[]="/tmp/otl-storage-files-XXXXXX";char*directory=mkdtemp(pattern);if(!directory){out.issue=autotest::Capture::InvalidReport;return;}std::string root(directory);std::wstring wideRoot=STRINGS::StringConvertUTF8ToWide(root);std::string names[]={"a.dat","b.dat","c.txt",".hidden","Ж.dat","tie.dat"};for(unsigned i=0;i<6;++i){std::string path=root+"/"+names[i];FILE*file=fopen(path.c_str(),"wb");if(!file){out.issue=autotest::Capture::InvalidReport;return;}fputs("contents",file);fclose(file);struct utimbuf times;times.actime=100000+i;times.modtime=100000+((i+c.seed)%3)*100;utime(path.c_str(),&times);}mkdir((root+"/sub.dat").c_str(),0700);
 if(c.mode==4){std::wstring first=wideRoot+L"/"+STRINGS::StringConvertUTF8ToWide(names[c.seed%6]);std::wstring second=wideRoot+L"/"+STRINGS::StringConvertUTF8ToWide(names[(c.seed/3)%6]);if(c.seed&8)first+=L".missing";if(c.seed&16)second+=L".missing";typedef bool(*Fn)(const std::wstring&,const std::wstring&);Fn fn=ours?nOlder:oOlder;if(!autotest::beginInvocation(out,fn))return;bool result=fn(first,second);out.callCompleted=1;out.add(&result,1);}
 else{std::wstring path=wideRoot;if(c.seed&1)path+=L"/";if(c.seed%11==0)path+=L"missing/";std::wstring filters[]={L"*",L"*.dat",L"a*",L"none*",L"",L"*.*"};TArrayList<std::wstring> files((c.seed%3)+1);if(c.seed&2)files.add(wideRoot+L"/c.txt");if(c.seed&4)files.add(wideRoot+L"/a.dat");typedef void(*Fn)(const std::wstring&,TArrayList<std::wstring>&,std::wstring);Fn fn=c.mode==5?(ours?nList:oList):(ours?nSorted:oSorted);if(!autotest::beginInvocation(out,fn))return;fn(path,files,filters[(c.seed/3)%6]);out.callCompleted=1;unsigned size=files.size();out.add(&size,4);for(unsigned i=0;i<size;++i){std::wstring value=files[i];if(value.find(wideRoot)==0)value=value.substr(wideRoot.size());out.addText(value);}}
 for(unsigned i=0;i<6;++i)unlink((root+"/"+names[i]).c_str());rmdir((root+"/sub.dat").c_str());rmdir(root.c_str());
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*n,uintptr_t a){autotest::Coverage coverage(n,a);for(unsigned seed=0;seed<120;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(candidate,&c,y);if(coverage.observe(h,x,y)){h->log("    file mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(bulk_files_byte,0,oByte)
TEST(bulk_files_read_string,1,oRead)
TEST(bulk_files_read_wide,2,oWide)
TEST(bulk_files_remove_name,3,oRemove)
TEST(bulk_files_older,4,oOlder)
TEST(bulk_files_list,5,oList)
TEST(bulk_files_sorted,6,oSorted)
