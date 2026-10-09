// The original delegates wide-string destruction to libstdc++; the candidate
// inlines it. The adapter below executes that same pinned inline destructor.
// Representation release is intercepted on both paths, preserving allocations
// until the forked child exits so release order and reference counts are visible.
#include <string>
#include <new>
#include <cstring>
#include "FileSystem.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalFileInfoDestructor,(CFileInfo*),"_ZN9CFileInfoD1Ev")
extern "C" void candidateFileInfoDestructor(CFileInfo*) __asm__("_ZN9CFileInfoD1Ev");
extern "C" char narrowRepDestroy[] __asm__("_ZNSs4_Rep10_M_destroyERKSaIcE");
extern "C" char wideRepDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char wideStringDestructor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
namespace fileinfo_dtor_fixture {
struct Case {unsigned modes,profile;};
struct Rep {size_t length,capacity;int refs;};
static Rep* representations[4];static unsigned destroyed[4];static autotest::Capture* capture;
static void number(unsigned v){capture->add(&v,sizeof(v));}
static void release(void* p,const void*){
 for(unsigned i=0;i<4;++i)if(p==representations[i]){number(i);number(++destroyed[i]);return;}
 _exit(61);
}
static void wideAdapter(std::wstring* p){p->~basic_string();}
static void side(const Case& c,bool ours,autotest::Capture& out){
 capture=&out;std::memset(destroyed,0,sizeof(destroyed));
 unsigned long long storage[(sizeof(CFileInfo)+7)/8];std::memset(storage,0xa5,sizeof(storage));
 CFileInfo* value=reinterpret_cast<CFileInfo*>(storage);
 new(&value->m_sModName)std::string();new(&value->m_sResourceName)std::string();
 new(&value->m_sPath)std::wstring();new(&value->m_sResourceGroup)std::string();
 std::string* narrow[]={&value->m_sModName,&value->m_sResourceName,NULL,&value->m_sResourceGroup};
 unsigned long long aliases[4][2];unsigned modes[4];
 for(unsigned i=0;i<4;++i){
  unsigned mode=modes[i]=(c.modes>>(i*2))&3;unsigned length=mode?(c.profile?127+i*17:1+i):0;
  if(i==2){
   value->m_sPath=std::wstring(length,c.profile?L'Ω':L'x');
   if(mode==2)new(aliases[i])std::wstring(value->m_sPath);
   if(mode==3)(void)value->m_sPath.begin();
   representations[i]=reinterpret_cast<Rep*>(const_cast<wchar_t*>(value->m_sPath.c_str()))-1;
  }else{
   *narrow[i]=std::string(length,char('a'+i));
   if(mode==2)new(aliases[i])std::string(*narrow[i]);
   if(mode==3)(void)narrow[i]->begin();
   representations[i]=reinterpret_cast<Rep*>(const_cast<char*>(narrow[i]->c_str()))-1;
  }
  number(mode);number(representations[i]->length);number(representations[i]->capacity);number(representations[i]->refs);
 }
 detour::Set patches;
 patches.redirect(narrowRepDestroy,narrowRepDestroy,&release);
 patches.redirect(wideRepDestroy,wideRepDestroy,&release);
 patches.redirect(wideStringDestructor,wideStringDestructor,&wideAdapter);
 if(patches.failed())_exit(60);
 if(ours)autotest::invoke(out,&candidateFileInfoDestructor,value);
 else autotest::invoke(out,&originalFileInfoDestructor,value);
 patches.restore();
 for(unsigned i=0;i<4;++i){
  number(destroyed[i]);number(representations[i]->length);number(representations[i]->capacity);number(representations[i]->refs);
  unsigned expected=(modes[i]==1||modes[i]==3)?1:0;
  if(destroyed[i]!=expected)_exit(62);
  if(i==2)out.add(static_cast<void*>(representations[i]+1),representations[i]->length*sizeof(wchar_t));
  else out.add(static_cast<void*>(representations[i]+1),representations[i]->length);
 }
 // All string allocations/placement aliases deliberately live until child exit.
}
static void left(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void right(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(fileinfo_destructor_differential){
 using namespace fileinfo_dtor_fixture;
 autotest::Coverage coverage("fileinfo_destructor_differential",reinterpret_cast<uintptr_t>(&originalFileInfoDestructor));
 for(unsigned modes=0;modes<256;++modes)for(unsigned profile=0;profile<2;++profile){
  Case c={modes,profile};autotest::Outcome a,b;autotest::runChild(left,&c,a);autotest::runChild(right,&c,b);
  int diff=coverage.observe(host,a,b);
  if(diff||a.childStatus||b.childStatus||!a.reportValid||!b.reportValid||!a.capture.callCompleted||!b.capture.callCompleted){
   coverage.report(host);host->log("    fileinfo destructor %u/%u differs exits %d/%d\n",modes,profile,a.childStatus,b.childStatus);return 1;
  }
 }
 coverage.report(host);host->log("    FileInfo destructor: 512 empty/unique/shared/leaked representations and release-order comparisons\n");return 0;
}
