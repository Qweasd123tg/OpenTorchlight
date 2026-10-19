#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <typeinfo>
TL_ORIGINAL(void,lcOld,(CLevel*,std::wstring,CSettings*,CGameClient*,CResourceManager*,Ogre::SceneManager*,CSoundManager*,int,int),"_ZN6CLevelC1ESbIwSt11char_traitsIwESaIwEEP9CSettingsP11CGameClientP16CResourceManagerPN4Ogre12SceneManagerEP13CSoundManagerii")
extern "C" void lcNew(CLevel*,std::wstring,CSettings*,CGameClient*,CResourceManager*,Ogre::SceneManager*,CSoundManager*,int,int) __asm__("_ZN6CLevelC1ESbIwSt11char_traitsIwESaIwEEP9CSettingsP11CGameClientP16CResourceManagerPN4Ogre12SceneManagerEP13CSoundManagerii");
namespace {
Ogre::SceneManager*scene;CSettings*settings;
void n(autotest::Capture&o,unsigned x){o.add(&x,4);}
void cleanup(CLevel&v){
 delete v.m_activeCharacters;delete v.m_activeItems;delete v.m_pCharacters;delete v.m_items;
 delete v.m_pendingCharacters;delete v.m_pendingItems;delete v.m_characterUpdateListeners;
 finishlevel::endMember(v.m_RoomScenes);finishlevel::endMember(v.m_roomBounds);finishlevel::endMember(v.m_collisionIndices);finishlevel::endMember(v.m_updateObjects);
 finishlevel::endMember(v.m_noSpawnRegions);finishlevel::endMember(v.m_propertyNodesF0);finishlevel::endMember(v.m_propertyNodes108);finishlevel::endMember(v.m_collisionBounds);
 finishlevel::endMember(v.m_chunks);finishlevel::endMember(v.m_formations);finishlevel::endMember(v.m_timer);finishlevel::endMember(v.m_auxiliaryLayouts);finishlevel::endMember(v.m_sDungeonName);
 finishlevel::endMember(v.m_renderableStates);finishlevel::endMember(v.m_unitObservers);finishlevel::endMember(v.m_pendingCharacterUpdateRemovals);
 v.CRunicCore::~CRunicCore();Ogre::NedAllocImpl::deallocBytes(&v);
}
void side(void*raw,autotest::Capture&out,bool ours){
 unsigned seed=*static_cast<unsigned*>(raw);CResourceManager resources(scene);int before=g_iTotalCountOfObjects;
 CLevel*p=static_cast<CLevel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CLevel),0,0,0));std::memset(p,static_cast<unsigned char>(seed*37+5),sizeof(CLevel));
 const wchar_t*names[]={L"",L"MAIN",L"MINE",L"\x041b\x0435\x0441/\x03a9"};std::wstring dungeon=names[seed%4];const int depths[]={-13,0,1,7,93,2147483647,-2147483647,2};
 typedef void(*Fn)(CLevel*,std::wstring,CSettings*,CGameClient*,CResourceManager*,Ogre::SceneManager*,CSoundManager*,int,int);Fn fn=ours?lcNew:lcOld;
 // Native list allocations must be initialized even after allocator reuse.
 void* recycled[64];for(unsigned i=0;i<64;++i){recycled[i]=Ogre::NedAllocImpl::allocBytes(sizeof(TLinkedList<CCharacter*>),0,0,0);std::memset(recycled[i],int(seed*13+0x45),sizeof(TLinkedList<CCharacter*>));}
 for(unsigned i=64;i>0;--i)Ogre::NedAllocImpl::deallocBytes(recycled[i-1]);
 if(!autotest::beginInvocation(out,fn))return;fn(p,dungeon,seed&1?settings:NULL,NULL,&resources,seed&2?scene:NULL,NULL,int(seed)*-173,depths[seed/8%8]);out.callCompleted=1;
 n(out,resources.m_pLevel==p);n(out,g_iTotalCountOfObjects-before);n(out,std::strcmp(typeid(*p).name(),"6CLevel")==0);
 n(out,p->m_activeCharacters&&p->m_activeCharacters->m_pHead==NULL);n(out,p->m_activeItems&&p->m_activeItems->m_pHead==NULL);
 n(out,p->m_pCharacters&&p->m_pCharacters->m_pHead==NULL);n(out,p->m_items&&p->m_items->m_pHead==NULL);
 n(out,p->m_pendingCharacters&&p->m_pendingCharacters->m_pHead==NULL);n(out,p->m_pendingItems&&p->m_pendingItems->m_pHead==NULL);
 n(out,p->m_characterUpdateListeners&&p->m_characterUpdateListeners->m_pHead==NULL);
 n(out,p->m_noSpawnRegions.size());n(out,p->m_noSpawnRegions.capacity());for(unsigned i=0;i<p->m_noSpawnRegions.size();++i)n(out,p->m_noSpawnRegions[i]==NULL);
 n(out,p->m_unitObservers.empty());n(out,p->m_sDungeonName.size());out.add(p->m_sDungeonName.data(),p->m_sDungeonName.size()*sizeof(wchar_t));
 n(out,p->m_timer.getMilliseconds()<10000);n(out,p->m_timer.getMillisecondsCPU()<10000);
 unsigned char bytes[sizeof(CLevel)];std::memcpy(bytes,p,sizeof bytes);
 const unsigned offsets[]={0,8,0x88,0x90,0x98,0xa0,0xc0,0xc8,0xd0,0xd8,0xe0,0xe8,0x280,0x2c0,0x2c8};
 for(unsigned i=0;i<sizeof(offsets)/sizeof(offsets[0]);++i)std::memset(bytes+offsets[i],0,8);
 // The real timer owns wall/CPU clock values; compare its bounded readings above.
 std::memset(bytes+0x240,0,sizeof(Ogre::Timer));out.add(bytes,sizeof bytes);
 TSafePointer<CLevel> weak;weak.setObject(p);cleanup(*p);n(out,weak.getObject()==NULL);n(out,g_iTotalCountOfObjects==before);resources.m_pLevel=NULL;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;settings=CMasterResourceManager::getSingleton()->m_pSettings;autotest::Coverage cov("level_constructor_native",reinterpret_cast<uintptr_t>(&lcOld));for(unsigned i=0;i<64;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(cov.observe(host,a,b)){host->log("    Level C1 seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0,shown=0;j<a.capture.length&&j<b.capture.length&&shown<24;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    byte %u original %02x candidate %02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);++shown;}cov.report(host);return 1;}}cov.report(host);return 0;}
}
TL_TEST(level_constructor_native){return systems_fixture::isolated(&run,host);}
