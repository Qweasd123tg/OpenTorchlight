#include <cstring>
#include <map>
#include <new>
#define private public
#define protected public
#include "CombineMenu.h"
#include "Equipment.h"
#include "Inventory.h"
#undef private
#undef protected
#include "AutoTest.h"
TL_ORIGINAL(void, originalTrack,(CCombineMenu*,CEquipment*,bool),"_ZN12CCombineMenu17itemUpdatedInMenuEP10CEquipmentb")
extern "C" void candidateTrack(CCombineMenu*,CEquipment*,bool) __asm__("_ZN12CCombineMenu17itemUpdatedInMenuEP10CEquipmentb");
namespace {
typedef std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> > Locations;
struct Case {unsigned mask,index,location;};
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;unsigned long long mm[(sizeof(CCombineMenu)+23)/8],em[5][(sizeof(CEquipment)+7)/8]={0},im[2][(sizeof(CInventory)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));CCombineMenu* menu=(CCombineMenu*)mm;new(&menu->m_OriginalItemLocations) Locations;CEquipment* items[5];CInventory* inventories[2]={(CInventory*)im[0],(CInventory*)im[1]};const int locations[]={-1,0,1,18,19,2147483647,(-2147483647-1)};
 for(unsigned i=0;i<5;++i){items[i]=(CEquipment*)em[i];items[i]->m_pInventory=c.mask&4?inventories[i%2]:0;items[i]->m_iUnknown298=locations[(c.location+i)%7];if(c.mask&(8u<<i))menu->m_OriginalItemLocations[items[i]]=std::make_pair(inventories[(i+1)%2],(EEQUIP_LOCATIONS)locations[(i+c.location+2)%7]);}
 g_bDontTrackItemEquipAndUnEquip=c.mask&1;
 if(ours)autotest::invoke(out,&candidateTrack,menu,items[c.index],bool(c.mask&2));else autotest::invoke(out,&originalTrack,menu,items[c.index],bool(c.mask&2));
 unsigned size=menu->m_OriginalItemLocations.size();out.add(&size,4);
 for(unsigned i=0;i<5;++i){Locations::iterator it=menu->m_OriginalItemLocations.find(items[i]);int present=it!=menu->m_OriginalItemLocations.end();out.add(&present,4);if(present){int inventory=it->second.first==inventories[0]?1:it->second.first==inventories[1]?2:it->second.first==0?0:99;out.add(&inventory,4);out.add(&it->second.second,4);}}
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));std::memset(snapshot+0x18,0,sizeof(Locations));out.add(snapshot,sizeof(snapshot));out.add(&g_bDontTrackItemEquipAndUnEquip,1);menu->m_OriginalItemLocations.~Locations();
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(combinemenu_item_tracking){autotest::Coverage coverage("combinemenu_item_tracking",(uint64_t)(uintptr_t)&originalTrack);for(unsigned mask=0;mask<256;++mask)for(unsigned index=0;index<5;++index)for(unsigned location=0;location<7;++location){Case c={mask,index,location};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    tracking mismatch %u/%u/%u exits %d/%d\n",mask,index,location,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
