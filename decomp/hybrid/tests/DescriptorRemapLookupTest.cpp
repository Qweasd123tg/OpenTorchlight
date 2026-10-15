#include <cstring>
#include <map>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "DescriptorLoadConfiguration.h"
TL_ORIGINAL(long long,oldRemap,(CDescriptorLoadConfiguration*,long long),"_ZN28CDescriptorLoadConfiguration13getRemappedIDEx")
extern "C" long long newRemap(CDescriptorLoadConfiguration*,long long) __asm__("_ZN28CDescriptorLoadConfiguration13getRemappedIDEx");
namespace {
struct Case{unsigned shape,index;};
void side(void* raw,autotest::Capture& out,bool ours){const Case& c=*static_cast<Case*>(raw);uint64_t storage[(sizeof(CDescriptorLoadConfiguration)+7)/8];std::memset(storage,0xa5,sizeof(storage));CDescriptorLoadConfiguration* self=reinterpret_cast<CDescriptorLoadConfiguration*>(storage);typedef std::map<long long,long long> Map;Map* map=new(&self->m_Remaps)Map;
 const long long keys[]={(-9223372036854775807LL-1),-10000000000LL,-7,-1,0,1,7,10000000000LL,9223372036854775807LL};
 for(unsigned i=0;i<c.shape;++i)(*map)[keys[i]]=keys[8-i];unsigned char before[sizeof(storage)];std::memcpy(before,storage,sizeof(storage));long long query=c.index<9?keys[c.index]:keys[c.index-9]+(c.index==17?-1:1);
 typedef long long(*Fn)(CDescriptorLoadConfiguration*,long long);Fn fn=ours?newRemap:oldRemap;if(!autotest::beginInvocation(out,fn))return;long long result=fn(self,query);out.callCompleted=1;
 Map::const_iterator found=map->find(query);long long expected=query==-1||found==map->end()?-1:found->second;bool unchanged=std::memcmp(before,storage,sizeof(storage))==0;if(result!=expected||!unchanged)out.issue=autotest::Capture::InvalidReport;
 out.add(&result,sizeof(result));out.add(&unchanged,sizeof(unchanged));for(Map::const_iterator it=map->begin();it!=map->end();++it){out.add(&it->first,sizeof(it->first));out.add(&it->second,sizeof(it->second));}map->~Map();
}
void original(void* c,autotest::Capture& out){side(c,out,false);}void candidate(void* c,autotest::Capture& out){side(c,out,true);}
}
TL_TEST(descriptor_remap_lookup){autotest::Coverage coverage("descriptor_remap_lookup",reinterpret_cast<uintptr_t>(&oldRemap));for(unsigned shape=0;shape<=9;++shape)for(unsigned index=0;index<18;++index){Case c={shape,index};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    remap shape %u index %u exits %d/%d\n",shape,index,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
