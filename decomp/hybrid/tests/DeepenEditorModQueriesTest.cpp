#include <cstring>
#include <string>
#include <map>
#include <stdint.h>
#include "AutoTest.h"
#define private public
#include "ModFileFilter.h"
#include "Mod.h"
#include "FileSystem.h"
#undef private
#define QUERY(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
QUERY(std::wstring,oldPath,newPath,(void*,const std::wstring&,std::string&,CFileInfo&),"_ZN14CModFileFilter11getFilePathERKSbIwSt11char_traitsIwESaIwEERSsR9CFileInfo")
QUERY(void,oldEnabledNames,newEnabledNames,(void*,TArrayList<std::wstring>*),"_ZN14CModFileFilter18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
QUERY(void,oldModNames,newModNames,(void*,TArrayList<std::wstring>*),"_ZN14CModFileFilter11getModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
#undef QUERY
namespace {
struct Case{unsigned mode,seed;};
void text(autotest::Capture&o,const std::wstring&s){unsigned n=s.size();o.add(&n,4);if(n)o.add(s.data(),n*4);}
void narrow(autotest::Capture&o,const std::string&s){unsigned n=s.size();o.add(&n,4);if(n)o.add(s.data(),n);}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);uint64_t filterSpace[(sizeof(CModFileFilter)+7)/8],modSpace[5][(sizeof(CMod)+7)/8];std::memset(filterSpace,0xa5,sizeof(filterSpace));std::memset(modSpace,0x5a,sizeof(modSpace));CModFileFilter*self=reinterpret_cast<CModFileFilter*>(filterSpace);TArrayList<CMod*>*mods=new(&self->m_Mods)TArrayList<CMod*>(2);
 const wchar_t* names[]={L"",L"A",L"AA",L"Ж"};
 for(unsigned i=0;i<5;++i){CMod*m=reinterpret_cast<CMod*>(modSpace[i]);new(&m->m_sUnknown10)std::string(i&1?"ODD":"EVEN");new(&m->m_mapModFiles)std::map<std::wstring,std::wstring>;new(&m->m_sUnknown48)std::string(i&1?"ODD GROUP":"EVEN GROUP");new(&m->m_wUnknown50)std::wstring(names[(i+c.seed/3)%4]);new(&m->m_wUnknown58)std::wstring;new(&m->m_wUnknown60)std::wstring;new(&m->m_wUnknown68)std::wstring;m->m_bUnknown70=((c.seed>>(i%5))&1)!=0;m->m_iUnknown74=(i+c.seed/7)%4==0?-1:static_cast<int>(i);if((i+c.seed)%3)m->m_mapModFiles[names[(i+c.seed/11)%4]]=names[(i+c.seed/13)%4];if(i<c.seed%6)mods->add(m);}
 if((c.seed&32)&&mods->size())mods->m_nCapacity=1;
 if(c.mode==0){std::wstring query=names[(c.seed/5)%4],expected;std::string group="unchanged group",expectedGroup=group;CFileInfo info;info.m_sModName="unchanged mod";std::string expectedMod=info.m_sModName;
  for(unsigned i=0;i<mods->size();++i){CMod*m=(*mods)[i];std::map<std::wstring,std::wstring>::const_iterator found=m->m_mapModFiles.find(query);if(m->m_iUnknown74>=0&&m->m_bUnknown70&&found!=m->m_mapModFiles.end()&&!found->second.empty()){expected=found->second;expectedGroup=m->m_sUnknown48;expectedMod=m->m_sUnknown10;break;}}
  typedef std::wstring(*Fn)(void*,const std::wstring&,std::string&,CFileInfo&);Fn fn=ours?newPath:oldPath;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self,query,group,info);out.callCompleted=1;text(out,result);narrow(out,group);narrow(out,info.m_sModName);narrow(out,info.m_sResourceName);text(out,info.m_sPath);out.add(&info.m_eFormat,sizeof(info.m_eFormat));out.add(&info.m_eLocation,sizeof(info.m_eLocation));narrow(out,info.m_sResourceGroup);out.add(&info.m_bExists,1);
  if(result!=expected||group!=expectedGroup||info.m_sModName!=expectedMod)out.issue=autotest::Capture::InvalidReport;}
 else{TArrayList<std::wstring> result((c.seed%3)+1);unsigned prefix=c.seed%3;for(unsigned i=0;i<prefix;++i)result.add(L"prefix");std::vector<std::wstring> expected(prefix,L"prefix");for(unsigned i=0;i<mods->size();++i)if(c.mode==2||(*mods)[i]->m_bUnknown70)expected.push_back((*mods)[i]->m_wUnknown50);
  void(*fn)(void*,TArrayList<std::wstring>*)=c.mode==1?(ours?newEnabledNames:oldEnabledNames):(ours?newModNames:oldModNames);if(!autotest::beginInvocation(out,fn))return;fn(self,&result);out.callCompleted=1;unsigned n=result.size();out.add(&n,4);if(n!=expected.size())out.issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<n;++i){text(out,result[i]);if(i>=expected.size()||result[i]!=expected[i])out.issue=autotest::Capture::InvalidReport;}}
 mods->~TArrayList();for(unsigned i=0;i<5;++i){CMod*m=reinterpret_cast<CMod*>(modSpace[i]);typedef std::map<std::wstring,std::wstring>Map;m->m_mapModFiles.~Map();m->m_sUnknown10.~basic_string();m->m_sUnknown48.~basic_string();m->m_wUnknown50.~basic_string();m->m_wUnknown58.~basic_string();m->m_wUnknown60.~basic_string();m->m_wUnknown68.~basic_string();}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<120;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    mod query mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(deepen_editor_mod_old_path){return run(host,0,"deepen_editor_mod_old_path",(uintptr_t)&oldPath);}
TL_TEST(deepen_editor_mod_old_enabled_names){return run(host,1,"deepen_editor_mod_old_enabled_names",(uintptr_t)&oldEnabledNames);}
TL_TEST(deepen_editor_mod_old_all_names){return run(host,2,"deepen_editor_mod_old_all_names",(uintptr_t)&oldModNames);}
