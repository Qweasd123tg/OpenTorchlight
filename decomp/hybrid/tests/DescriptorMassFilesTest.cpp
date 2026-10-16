#include <string>
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massFilesOld,(void*,void*,unsigned,void*),"_ZN16CLightDescriptor17GetFileStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massFilesNew(void*,void*,unsigned,void*) __asm__("_ZN16CLightDescriptor17GetFileStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_FUNCTION(massFileSystemSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(massFileSystemList,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
namespace {
struct Case{unsigned count,index;};Case* input;autotest::Capture* capture;unsigned calls,singletons;unsigned char marker;
void invalid(){capture->issue=autotest::Capture::InvalidReport;}
void* singleton(){++singletons;return &marker;}
unsigned files(void* p,const std::wstring& directory,TArrayList<std::wstring>& result,std::wstring pattern,bool a,bool b,bool c,bool d){
 ++calls;if(p!=&marker||directory!=L"media/lights/"||pattern!=L"*.mesh"||!a||!b||c||d||result.size()!=0)invalid();
 const wchar_t* names[]={L"first.mesh",L"spot.mesh",L"third.mesh"};for(unsigned i=0;i<input->count;++i)result.add(names[i]);capture->addText(directory);capture->addText(pattern);return input->count;
}
void side(Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;calls=singletons=0;detour::Set d;TL_REDIRECT(d,massFileSystemSingleton,&singleton);TL_REDIRECT(d,massFileSystemList,&files);if(d.failed()){invalid();return;}typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massFilesNew:massFilesOld;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,0,c.index,0);std::wstring first=fn(0,0,0,0);out.callCompleted=1;out.addText(result);out.addText(first);out.add(&calls,4);out.add(&singletons,4);if(calls!=(c.count?1u:2u)||singletons!=calls)invalid();const wchar_t* names[]={L"first.mesh",L"spot.mesh",L"third.mesh"};if(result!=(c.index<c.count?std::wstring(names[c.index]):std::wstring()))invalid();if(first!=(c.count?std::wstring(names[0]):std::wstring()))invalid();}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(mass_descriptor_5f8b80){autotest::Coverage cov("mass_descriptor_5f8b80",reinterpret_cast<uintptr_t>(&massFilesOld));const unsigned indices[]={0,1,2,3,9,0xffffffffu};for(unsigned count=0;count<4;++count)for(unsigned i=0;i<6;++i){Case c={count,indices[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" massfiles count%u index%u exits%d/%d issues%u/%u\n",count,c.index,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
