#include <cstring>
#include <string>
#include <map>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "ModFileFilter.h"
#include "Mod.h"
#include "FileUtilities.h"
#undef private
TL_ORIGINAL(void,mfOld,(CModFileFilter*,const std::wstring&,TArrayList<std::wstring>&,std::wstring,bool),"_ZN14CModFileFilter8getFilesERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_b")
extern "C" void mfNew(CModFileFilter*,const std::wstring&,TArrayList<std::wstring>&,std::wstring,bool) __asm__("_ZN14CModFileFilter8getFilesERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_b");
TL_FUNCTION(mfList,"_ZN10FILESYSTEM11GetFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_")
TL_FUNCTION(mfRecursive,"_ZN10FILESYSTEM20GetFileListRecursiveERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES5_")
namespace {
struct Case{unsigned seed;bool recursive;};autotest::Capture*cap;unsigned seed,calls;bool recurse;CModFileFilter*owner;std::wstring dir,pattern;std::vector<std::wstring> expected;
void n(unsigned x){cap->add(&x,4);}void bad(){cap->issue=autotest::Capture::InvalidReport;}
void enumerate(const std::wstring&path,TArrayList<std::wstring>&result,const std::wstring&pat,bool recursive){unsigned index=99;for(unsigned i=0;i<owner->m_Mods.size();++i){CMod*m=owner->m_Mods[i];if(m->m_wUnknown68+dir==path){index=i;break;}}if(index==99||pat!=pattern||recursive!=recurse){bad();return;}CMod*m=owner->m_Mods[index];if(m->m_iUnknown74<0||!m->m_bUnknown70)bad();++calls;n(index);cap->addText(path);cap->addText(pat);n(recursive);n(result.size());for(unsigned i=0;i<(seed+index)%6;++i){std::wstring relative=dir+(i%3==0?L"same.dat":i%3==1?L"Ж/one.dat":L"two.bin");result.add(m->m_wUnknown68+relative);if(std::find(expected.begin(),expected.end(),relative)==expected.end())expected.push_back(relative);}}
void list(const std::wstring&p,TArrayList<std::wstring>&r,std::wstring pat){enumerate(p,r,pat,false);}void recursive(const std::wstring&p,TArrayList<std::wstring>&r,const std::wstring&pat){enumerate(p,r,pat,true);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;recurse=c.recursive;cap=&out;calls=0;expected.clear();uint64_t space[(sizeof(CModFileFilter)+7)/8],modSpace[5][(sizeof(CMod)+7)/8];std::memset(space,0,sizeof(space));std::memset(modSpace,0,sizeof(modSpace));CModFileFilter*self=reinterpret_cast<CModFileFilter*>(space);owner=self;new(self)CRunicCore;new(&self->m_sModsFile)std::wstring;new(&self->m_Mods)TArrayList<CMod*>(2);
 for(unsigned i=0;i<5;++i){CMod*m=reinterpret_cast<CMod*>(modSpace[i]);new(m)CRunicCore;new(&m->m_sUnknown10)std::string;new(&m->m_mapModFiles)std::map<std::wstring,std::wstring>;new(&m->m_sUnknown48)std::string;new(&m->m_wUnknown50)std::wstring;new(&m->m_wUnknown58)std::wstring;new(&m->m_wUnknown60)std::wstring;wchar_t prefix[24];std::swprintf(prefix,24,L"/mod%u/",i);new(&m->m_wUnknown68)std::wstring(prefix);m->m_iUnknown74=(seed+i)%4==0?-1:i;m->m_bUnknown70=(seed>>(i%5))&1;m->m_bUnknown71=false;m->m_mapModFiles[L"sentinel"]=L"unchanged";if(i<seed%6)self->m_Mods.add(m);}
 TArrayList<std::wstring> files(1+seed%3);dir=seed%3==0?L"":seed%3==1?L"media/":L"Ж/";pattern=seed&1?L"*.dat":L"*.*";for(unsigned i=0;i<seed%4;++i){files.add(i%2?L"prefix":dir+L"same.dat");expected.push_back(files[i]);}
 {detour::Set patches;TL_REDIRECT(patches,mfList,&list);TL_REDIRECT(patches,mfRecursive,&recursive);if(patches.failed()){bad();return;}
 typedef void(*Fn)(CModFileFilter*,const std::wstring&,TArrayList<std::wstring>&,std::wstring,bool);Fn fn=ours?mfNew:mfOld;const std::wstring&input=(seed&16)&&files.size()?files[0]:dir;dir=input;if(!autotest::beginInvocation(out,fn))return;fn(self,input,files,pattern,recurse);out.callCompleted=1;}
 n(calls);n(files.size());if(files.size()!=expected.size())bad();for(unsigned i=0;i<files.size();++i){cap->addText(files[i]);if(i>=expected.size()||files[i]!=expected[i])bad();}for(unsigned i=0;i<5;++i){CMod*m=reinterpret_cast<CMod*>(modSpace[i]);if(m->m_mapModFiles.size()!=1||m->m_mapModFiles[L"sentinel"]!=L"unchanged")bad();typedef std::map<std::wstring,std::wstring>Map;m->m_mapModFiles.~Map();m->m_sUnknown10.~basic_string();m->m_sUnknown48.~basic_string();m->m_wUnknown50.~basic_string();m->m_wUnknown58.~basic_string();m->m_wUnknown60.~basic_string();m->m_wUnknown68.~basic_string();m->CRunicCore::~CRunicCore();}self->m_Mods.~TArrayList();self->m_sModsFile.~basic_string();self->CRunicCore::~CRunicCore();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(deepen_editor_mod_files){autotest::Coverage coverage("deepen_editor_mod_files",(uintptr_t)&mfOld);for(unsigned r=0;r<2;++r)for(unsigned s=0;s<120;++s){Case c={s,r!=0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    mod files recursive%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",r,s,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
