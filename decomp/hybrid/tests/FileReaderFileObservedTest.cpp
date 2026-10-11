
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <unistd.h>
#include <OgreLogManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include <OgreDataStream.h>
#include "AutoTest.h"
#include "Detour.h"
#include "FileReader.h"
#include "FileSystem.h"
TL_ORIGINAL(bool,originalReadFile,(CFileReader*,const std::wstring&),"_ZN11CFileReader8ReadFileERKSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidateReadFile(CFileReader*,const std::wstring&) __asm__("_ZN11CFileReader8ReadFileERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(targetSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(targetInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(targetStream,"_ZN11CFileSystem13getDataStreamER9CFileInfo")
namespace {
struct ReaderView{std::wstring filename;wchar_t*buffer;unsigned length,position,characterSize;};
struct Case{unsigned seed;};Case*input;autotest::Capture*output;Ogre::DataStreamPtr selectedStream;void*fileSystems[2];unsigned singletonCalls;std::wstring fileNames[7];
void event(unsigned k,void*p){output->add(&k,4);output->add(&p,8);}
void* singleton(){++singletonCalls;void*p=input->seed%4==0?NULL:fileSystems[singletonCalls%2];event(1,p);return p;}
void info(void*p,const std::wstring&name,CFileInfo&value,bool a,bool b,bool c){event(2,p);output->addText(name);output->add(&a,1);output->add(&b,1);output->add(&c,1);output->addText(value.m_sModName);output->addText(value.m_sResourceName);output->addText(value.m_sPath);output->add(&value.m_eFormat,4);output->add(&value.m_eLocation,4);output->addText(value.m_sResourceGroup);output->add(&value.m_bExists,1);value.m_sPath=L"resolved";value.m_sResourceName="memory";value.m_eLocation=FILE_LOCATION_RESOURCE_GROUP;}
Ogre::DataStreamPtr stream(void*p,CFileInfo&value){event(3,p);output->addText(value.m_sPath);output->addText(value.m_sResourceName);output->add(&value.m_eLocation,4);return input->seed%4==1?Ogre::DataStreamPtr():selectedStream;}
struct Logs:Ogre::LogListener {std::vector<std::string>text;std::vector<int>level;std::vector<unsigned char>mask;virtual void messageLogged(const Ogre::String&s,Ogre::LogMessageLevel l,bool m,const Ogre::String&){text.push_back(s);level.push_back(l);mask.push_back(m);}};
void side(void*p,autotest::Capture&out,bool ours){Case&c=*static_cast<Case*>(p);input=&c;output=&out;singletonCalls=0;unsigned long long fs[2][8]={{0}};fileSystems[0]=fs[0];fileSystems[1]=fs[1];
 Ogre::LogManager logs;Ogre::Log*log=logs.createLog("reader-file-test",true,false,true);Logs captured;log->addListener(&captured);
 unsigned short data[48];for(unsigned i=0;i<48;++i)data[i]=static_cast<unsigned short>(0x41+(i+c.seed)%24);const unsigned short first[]={0xfeff,0,0xd83d,0xfffe,0x41,0xd800,0xffff,0xdc00};data[0]=first[(c.seed/4)%8];data[1]=c.seed&16?0xde00:0x41;data[47]=0;
 const unsigned sizes[]={0,1,2,3,4,6,17,24,64,95,96};unsigned bytes=sizes[(c.seed/32)%11];selectedStream=Ogre::DataStreamPtr(new Ogre::MemoryDataStream(data,bytes,false));
 CFileReader reader;ReaderView&view=*reinterpret_cast<ReaderView*>(&reader);view.filename=L"previous name";view.length=(c.seed/3)%7+1;view.position=(c.seed/11)%view.length;view.characterSize=2+(c.seed%2)*2;view.buffer=OGRE_ALLOC_T(wchar_t,view.length,Ogre::MEMCATEGORY_GENERAL);for(unsigned i=0;i<view.length;++i)view.buffer[i]=0x31+i;
 detour::Set patches;TL_REDIRECT(patches,targetSingleton,&singleton);TL_REDIRECT(patches,targetInfo,&info);TL_REDIRECT(patches,targetStream,&stream);if(patches.failed())_exit(41);bool(*fn)(CFileReader*,const std::wstring&)=ours?candidateReadFile:originalReadFile;if(!autotest::beginInvocation(out,fn))return;bool ret=fn(&reader,fileNames[(c.seed/4)%7]);out.callCompleted=1;out.add(&ret,1);out.addText(view.filename);out.add(&view.length,4);out.add(&view.position,4);out.add(&view.characterSize,4);bool has=view.buffer!=NULL;out.add(&has,1);if(view.length>256)_exit(42);if(has)out.add(view.buffer,view.length*sizeof(wchar_t));unsigned n=captured.text.size();out.add(&n,4);for(unsigned i=0;i<n;++i){out.addText(captured.text[i]);out.add(&captured.level[i],4);out.add(&captured.mask[i],1);}out.add(fs,sizeof(fs));out.add(data,sizeof(data));size_t pos=selectedStream->tell();out.add(&pos,sizeof(pos));out.add(&singletonCalls,4);out.addHeapInUse();log->removeListener(&captured);
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void recovered(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(reader_file_observed){char directory[]="/tmp/opencode-reader-next-XXXXXX";if(!mkdtemp(directory))return 1;const unsigned char prefixes[][4]={{0xff,0xfe,0x41,0},{0xff,0xfe,0,0},{0,0,0xfe,0xff},{0xef,0xbb,0xbf,0x41},{0xfe,0xff,0,0x41},{0x41,0x42,0x43,0x44}};for(unsigned i=0;i<7;++i){char name[256];snprintf(name,sizeof(name),"%s/file%u.dat",directory,i);fileNames[i]=std::wstring(name,name+strlen(name));if(i<6){FILE*f=fopen(name,"wb");if(!f)return 1;unsigned char bytes[96];for(unsigned j=0;j<96;++j)bytes[j]=j%2?0:0x41+(j%20);std::memcpy(bytes,prefixes[i],4);fwrite(bytes,1,sizeof(bytes),f);fclose(f);}}
 autotest::Coverage coverage("reader_file_observed",(uint64_t)(uintptr_t)originalReadFile);int failed=0;for(unsigned n=0;n<704;++n){Case c={n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    reader file %u status %d/%d first %lu bytes %lu/%lu\n",n,a.status,b.status,(unsigned long)at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failed=1;break;}}coverage.report(host);for(unsigned i=0;i<6;++i){std::string path(fileNames[i].begin(),fileNames[i].end());unlink(path.c_str());}rmdir(directory);return failed;}
