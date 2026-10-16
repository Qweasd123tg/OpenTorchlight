#include "SmallMassCompare.h"
#include <OgreMemoryAllocatorConfig.h>
#include <new>
#include <new>
TL_ORIGINAL(void, oldRefresh, (void*,const std::string&), "_ZN14CModFileFilter10refreshModERKSs")
extern "C" void newRefresh(void*,const std::string&) __asm__("_ZN14CModFileFilter10refreshModERKSs");
TL_ORIGINAL(void, oldRefreshAll, (void*), "_ZN14CModFileFilter14refreshAllModsEv")
extern "C" void newRefreshAll(void*) __asm__("_ZN14CModFileFilter14refreshAllModsEv");
TL_ORIGINAL(void, oldAdd, (void*,const std::wstring&), "_ZN14CModFileFilter9addNewModERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void newAdd(void*,const std::wstring&) __asm__("_ZN14CModFileFilter9addNewModERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, oldCheat, (void*), "_ZN13CAchievements5cheatEv")
extern "C" void newCheat(void*) __asm__("_ZN13CAchievements5cheatEv");
TL_ORIGINAL(void, oldComplete, (void*,void*), "_ZN13CAchievements22setAchievementCompleteEP12CAchievement")
extern "C" void newComplete(void*,void*) __asm__("_ZN13CAchievements22setAchievementCompleteEP12CAchievement");
TL_ORIGINAL(std::wstring, oldStatus, (void*), "_ZN13CAchievements20getAchievementStatusEv")
extern "C" std::wstring newStatus(void*) __asm__("_ZN13CAchievements20getAchievementStatusEv");
TL_FUNCTION(reload,"_ZN4CMod14reloadModFilesEv")
TL_FUNCTION(save,"_ZN14CModFileFilter11saveModFileEb")
TL_FUNCTION(modCtor,"_ZN4CModC1ERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(cheat,"_ZN12CAchievement5cheatEv")
TL_FUNCTION(progress,"_ZN12CAchievement21getStatCompleteStringEv")
namespace {
using namespace smallmass;
void* created;
void reloadMod(void* p){event(1,p);}
void saveMods(void* p,bool flag){event(2,p);number(flag);}
void modConstruct(void* p,const std::wstring& name,int priority){number(3);text(name);number(priority);created=p;}
void cheatOne(void* p){event(4,p);field<bool>(p,0x20)=true;}
std::wstring stat(void* p){event(5,p);return field<bool>(p,0x20)?L"1/1":L"0/1";}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;created=0;
 void* self=object(0xa0);void* members[8];unsigned count=c.index%5;unsigned capacity=(c.index/5)%2?count:count+2;
 for(unsigned i=0;i<8;++i){members[i]=object(0x78);new(static_cast<char*>(members[i])+0x48)std::string((i+c.index)%3?"mod":"target");field<int>(members[i],0x74)=int((c.index+i)%7)-3;new(static_cast<char*>(members[i])+0x18)std::string(i&1?"Second":"First");field<bool>(members[i],0x20)=(c.index+i)&1;}
 void** data=capacity?new void*[capacity]:0;for(unsigned i=0;i<capacity;++i)data[i]=members[i];
 detour::Set d;TL_REDIRECT(d,reload,&reloadMod);TL_REDIRECT(d,save,&saveMods);TL_REDIRECT(d,modCtor,&modConstruct);TL_REDIRECT(d,cheat,&cheatOne);TL_REDIRECT(d,progress,&stat);if(d.failed())_exit(41);
 if(c.op<3){
  list(self,0x18,data,count,capacity);
  if(c.op==0){std::string name(c.index&1?"target":"missing");autotest::invoke(out,ours?newRefresh:oldRefresh,self,name);}
  else if(c.op==1)autotest::invoke(out,ours?newRefreshAll:oldRefreshAll,self);
  else {std::wstring name(c.index&1?L"newmod":L"");autotest::invoke(out,ours?newAdd:oldAdd,self,name);number(field<unsigned>(self,0x20));number(field<unsigned>(self,0x24));void** after=field<void**>(self,0x18);for(unsigned i=0;i<field<unsigned>(self,0x20);++i){if(after[i]==created)number(999);else pointer(after[i]);}delete[] after;if(created)Ogre::NedAllocImpl::deallocBytes(created);}
 }else if(c.op==3){list(self,0x30,data,count,capacity);autotest::invoke(out,ours?newCheat:oldCheat,self);for(unsigned i=0;i<count;++i)number(field<bool>(members[i],0x20));}
 else if(c.op==4){list(self,0x18,data,count,capacity);void* achievement=c.index&1?members[7]:0;autotest::invoke(out,ours?newComplete:oldComplete,self,achievement);number(field<unsigned>(self,0x20));number(field<unsigned>(self,0x24));void** after=field<void**>(self,0x18);for(unsigned i=0;i<field<unsigned>(self,0x20);++i)pointer(after[i]);delete[] after;}
 else {list(self,0x30,data,count,capacity);autotest::invoke(out,ours?newStatus:oldStatus,self);}
 if(c.op!=2&&c.op!=4)delete[] data;
 for(unsigned i=0;i<8;++i){field<std::string>(members[i],0x48).~basic_string();field<std::string>(members[i],0x18).~basic_string();}
 out.addHeapInUse();
}
}
TL_TEST(services_mod_refresh){return smallmass::run(host,0,"ServicesModRefresh",0xc83ab0,execute,48);}
TL_TEST(services_mod_refresh_all){return smallmass::run(host,1,"ServicesModRefreshAll",0xc84440,execute,48);}
TL_TEST(services_mod_add){return smallmass::run(host,2,"ServicesModAdd",0xc83b40,execute,64);}
TL_TEST(services_achievement_cheat){return smallmass::run(host,3,"ServicesAchievementCheat",0xebfac0,execute,48);}
TL_TEST(services_achievement_complete){return smallmass::run(host,4,"ServicesAchievementComplete",0xec7850,execute,64);}
TL_TEST(services_achievement_status){return smallmass::run(host,5,"ServicesAchievementStatus",0xec71d0,execute,48);}
