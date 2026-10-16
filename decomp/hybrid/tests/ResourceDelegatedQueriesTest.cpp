#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "DescriptorManager.h"
#include "SteamStats.h"
TL_ORIGINAL(void*,oldDescriptorByName,(void*,const wchar_t*,bool),"_ZN18CDescriptorManager13GetDescriptorEPKwb")
extern "C" void*newDescriptorByName(void*,const wchar_t*,bool) __asm__("_ZN18CDescriptorManager13GetDescriptorEPKwb");
TL_ORIGINAL(int,oldPlayerStat,(void*,ESTATS),"_ZN11CSteamStats16getPlayerStatIntE6ESTATS")
extern "C" int newPlayerStat(void*,ESTATS) __asm__("_ZN11CSteamStats16getPlayerStatIntE6ESTATS");
TL_FUNCTION(descriptorCreate,"_ZN21CDescriptorController22getNewDescriptorByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(descriptorAdd,"_ZN18CDescriptorManager13AddDescriptorEP11CDescriptor")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*capture;void*created;void*manager;unsigned createCount,addCount;
void*create(const std::wstring&name){++createCount;unsigned marker=90;capture->add(&marker,4);unsigned n=name.size();capture->add(&n,4);if(n)capture->add(name.data(),n*4);return created;}
unsigned add(void*self,void*descriptor){++addCount;unsigned marker=91;capture->add(&marker,4);if(self!=manager||descriptor!=created)capture->issue=autotest::Capture::InvalidReport;return 123;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);capture=&out;
 if(c.mode==0){uint64_t storage[(sizeof(CDescriptorManager)+7)/8],objects[4][32];std::memset(storage,0xa5,sizeof(storage));CDescriptorManager*self=reinterpret_cast<CDescriptorManager*>(storage);manager=self;
  typedef std::map<std::wstring,unsigned>Map;Map*indices=new(&self->m_descriptorIndices)Map;typedef std::vector<CDescriptor*>Vector;Vector*values=new(&self->m_descriptors)Vector;
  const wchar_t*names[]={L"",L"A",L"AA",L"Ж"};for(unsigned i=0;i<c.seed%5;++i){(*indices)[names[i]]=(i+c.seed/7)%5;values->push_back(reinterpret_cast<CDescriptor*>(objects[i]));}
  std::wstring name=names[(c.seed/5)%4];created=c.seed&16?objects[3]:NULL;createCount=addCount=0;Map before=*indices;bool createMissing=(c.seed&1)!=0;
  void*expected=NULL;Map::const_iterator found=indices->find(name);bool missing=found==indices->end();if(found!=indices->end()){if(found->second<values->size())expected=(*values)[found->second];}else if(createMissing)expected=created;
  detour::Set patches;TL_REDIRECT(patches,descriptorCreate,&create);TL_REDIRECT(patches,descriptorAdd,&add);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  void*(*fn)(void*,const wchar_t*,bool)=ours?newDescriptorByName:oldDescriptorByName;if(!autotest::beginInvocation(out,fn))return;void*result=fn(self,name.c_str(),createMissing);out.callCompleted=1;int identity=-1;for(unsigned i=0;i<4;++i)if(result==objects[i])identity=i;out.add(&identity,4);
  bool createExpected=missing&&createMissing;if(result!=expected||createCount!=(createExpected?1u:0u)||addCount!=(createExpected&&created?1u:0u)||*indices!=before)out.issue=autotest::Capture::InvalidReport;values->~Vector();indices->~Map();
 }else{uint64_t statsSpace[(sizeof(CSteamStats)+7)/8],playerSpace[0x900/8];std::memset(statsSpace,0xa5,sizeof(statsSpace));std::memset(playerSpace,0x5a,sizeof(playerSpace));CSteamStats*self=reinterpret_cast<CSteamStats*>(statsSpace);self->m_pPlayer=c.seed&1?reinterpret_cast<CPlayer*>(playerSpace):NULL;
  const int integers[]={0,1,-1,2147483647,(-2147483647-1)},stats[]={0,27,28,29,30,31,-1};int journal=integers[(c.seed/2)%5],gold=integers[(c.seed/10)%5],stat=stats[(c.seed/3)%7];std::memcpy(reinterpret_cast<char*>(playerSpace)+0x7f0,&journal,4);std::memcpy(reinterpret_cast<char*>(playerSpace)+0x444,&gold,4);
  int(*fn)(void*,ESTATS)=ours?newPlayerStat:oldPlayerStat;if(!autotest::beginInvocation(out,fn))return;int result=fn(self,static_cast<ESTATS>(stat));out.callCompleted=1;out.add(&result,4);int expected=self->m_pPlayer?(stat==28?journal:stat==29?gold:-1):-1;if(result!=expected)out.issue=autotest::Capture::InvalidReport;
 }
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<120;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    delegated query mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(resource_descriptor_by_name){return run(host,0,"resource_descriptor_by_name",(uintptr_t)&oldDescriptorByName);}
TL_TEST(resource_player_stat){return run(host,1,"resource_player_stat",(uintptr_t)&oldPlayerStat);}
