#include <cstring>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "StashMenu.h"
#include "GenericModel.h"
#include "Settings.h"
#include "GameVariables.h"
#include <OgreBone.h>
#include <OgreSkeletonInstance.h>
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalUpdate,(CStashMenu*,float),"_ZN10CStashMenu6updateEf")
extern "C" void candidateUpdate(CStashMenu*,float) __asm__("_ZN10CStashMenu6updateEf");
TL_FUNCTION(settingFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(animationFn,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(positionFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(scaleFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(playingFn,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(queuedFn,"_ZNK13CGenericModel15animationQueuedERKSs")
extern "C" char entityFn[] __asm__("_ZN4Ogre6Entity16_updateAnimationEv");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char setPositionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
namespace {
struct Stop{};struct Case{unsigned mask,geometry,mutation,fault;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CGenericModel* models[2];Ogre::Entity* entities[2];Ogre::SkeletonInstance* skeletons[2];Ogre::Bone* bones[2];CSettings* settings[2];CGameUI* ui[2];CEGUI::Window* windows[6];Ogre::Vector3 offsets[2];unsigned events,scales;
void n(int x){cap->add(&x,4);}int id(void* p,void* a,void* b){return !p?0:p==a?1:p==b?2:99;}int wid(CEGUI::Window* p){if(!p)return 0;for(unsigned i=0;i<6;++i)if(p==windows[i])return i+1;return 99;}
void event(int x){n(x);if(++events==cs->fault)throw Stop();}
int setting(CDynamicPropertyFile* p,unsigned key){event(1);n(id(p,settings[0],settings[1]));n(key);if(cs->mutation)menu->m_pDynamicPropertyFile=settings[1];return key==KSETTINGS_RES_WIDTH?(cs->geometry%2?-1920:1024):(cs->geometry%2?0:768);}
void animation(CGenericModel* p,float elapsed,bool force){event(2);n(id(p,models[0],models[1]));cap->add(&elapsed,4);n(force);if(cs->mutation==3)menu->m_pUnknown90=models[1];}
void entity(Ogre::Entity* p){event(3);n(id(p,entities[0],entities[1]));if(cs->mutation==4)menu->m_pUnknown90=models[1];}
Ogre::Bone* bone(Ogre::SkeletonInstance* p,const std::string& name){event(4);n(id(p,skeletons[0],skeletons[1]));cap->addText(name);if(cs->mutation==5)menu->m_pUnknown90=models[1];return bones[p==skeletons[1]?1:0];}
Ogre::Vector3 position(CPositionableObject* p,bool absolute){event(5);n(id(p,models[0],models[1]));n(absolute);return Ogre::Vector3(17.25f,-9.5f,4.25f);}
const Ogre::Vector3& derived(const Ogre::Bone* p){event(6);n(id((void*)p,bones[0],bones[1]));return offsets[p==bones[1]?1:0];}
float scale(CGameUI* p,float value){event(7);n(id(p,ui[0],ui[1]));cap->add(&value,4);++scales;if(cs->mutation==6){menu->m_pGameUI=ui[1];offsets[0].y=999;}return value*(p==ui[0]?1.25f:-0.5f);}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& value){event(8);n(wid(p));cap->add(&value,sizeof(value));}
void visible(CEGUI::Window* p,bool value){event(9);n(wid(p));n(value);if(cs->mutation==1)menu->m_pUnknown38=windows[4];if(cs->mutation==2&&(cs->mask&4))menu->m_bOpenPartial=true;}
bool playing(const CGenericModel* p,const std::string& name){event(10);n(id((void*)p,models[0],models[1]));cap->addText(name);if(cs->mutation==7&&menu->m_pUnknown90)menu->m_pUnknown90=models[1];return cs->mask&8;}
bool queued(const CGenericModel* p,const std::string& name){event(11);n(id((void*)p,models[0],models[1]));cap->addText(name);return cs->mask&16;}
void modelVisible(CGenericModel* p,bool value){event(12);n(id(p,models[0],models[1]));n(value);}
void remove(CEGUI::Window* p,CEGUI::Window* q){event(13);n(wid(p));n(wid(q));}
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}void ptr(unsigned char* p,unsigned off,uintptr_t value){std::memcpy(p+off,&value,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;events=scales=0;unsigned long long mm[(sizeof(CStashMenu)+23)/8],modelMem[2][(sizeof(CGenericModel)+7)/8]={0},entityMem[2][8]={0},skeletonMem[2][8]={0},boneMem[2][8]={0},setMem[2][8]={0},uiMem[2][8]={0},wm[6][8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CStashMenu*)mm;void* modelVT[12]={0};modelVT[10]=(void*)&modelVisible;void* skeletonVT[64]={0};skeletonVT[0x1b0/8]=(void*)&bone;void* boneVT[80]={0};boneVT[0x200/8]=(void*)&derived;const float values[]={0.0f,17.25f,-9.5f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};for(unsigned i=0;i<2;++i){models[i]=(CGenericModel*)modelMem[i];entities[i]=(Ogre::Entity*)entityMem[i];skeletons[i]=(Ogre::SkeletonInstance*)skeletonMem[i];bones[i]=(Ogre::Bone*)boneMem[i];settings[i]=(CSettings*)setMem[i];ui[i]=(CGameUI*)uiMem[i];*(void***)models[i]=modelVT;*(void***)skeletons[i]=skeletonVT;*(void***)bones[i]=boneVT;at<Ogre::Entity*>(models[i],0x60)=entities[i];at<Ogre::SkeletonInstance*>(models[i],0x130)=skeletons[i];offsets[i]=Ogre::Vector3(values[c.geometry],values[(c.geometry+i)%6],float(i));}for(unsigned i=0;i<6;++i)windows[i]=(CEGUI::Window*)wm[i];menu->m_bOpenPartial=c.mask&1;menu->m_bUnknown61=c.mask&2;menu->m_pUnknown90=models[0];menu->m_pDynamicPropertyFile=settings[0];menu->m_pGameUI=ui[0];menu->m_pUnknown30=windows[0];menu->m_pUnknown38=windows[1];menu->m_pUnknown18=windows[2];menu->m_pUnknown20=windows[3];menu->m_pUnknown28=windows[4];menu->m_pUnknown40=windows[5];menu->m_pHoverObject=(CEquipment*)models[1];
 detour::Set d;TL_REDIRECT(d,settingFn,&setting);TL_REDIRECT(d,animationFn,&animation);TL_REDIRECT(d,positionFn,&position);TL_REDIRECT(d,scaleFn,&scale);TL_REDIRECT(d,playingFn,&playing);TL_REDIRECT(d,queuedFn,&queued);d.redirect(entityFn,entityFn,&entity);d.redirect(visibleFn,visibleFn,&visible);d.redirect(setPositionFn,setPositionFn,&setPosition);d.redirect(removeFn,removeFn,&remove);if(d.failed())_exit(60);bool threw=false;try{if(ours)autotest::invoke(out,&candidateUpdate,menu,values[(c.geometry+1)%6]);else autotest::invoke(out,&originalUpdate,menu,values[(c.geometry+1)%6]);}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(events);n(scales);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x68,id(menu->m_pDynamicPropertyFile,settings[0],settings[1]));ptr(snapshot,0x70,id(menu->m_pGameUI,ui[0],ui[1]));ptr(snapshot,0x90,id(menu->m_pUnknown90,models[0],models[1]));ptr(snapshot,0x3408,menu->m_pHoverObject?menu->m_pHoverObject==(CEquipment*)models[1]?1:99:0);ptr(snapshot,0x30,wid(menu->m_pUnknown30));ptr(snapshot,0x38,wid(menu->m_pUnknown38));ptr(snapshot,0x18,wid(menu->m_pUnknown18));ptr(snapshot,0x20,wid(menu->m_pUnknown20));ptr(snapshot,0x28,wid(menu->m_pUnknown28));ptr(snapshot,0x40,wid(menu->m_pUnknown40));out.add(snapshot,sizeof(snapshot));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(stashmenu_update){autotest::Coverage coverage("stashmenu_update",(uint64_t)(uintptr_t)&originalUpdate);for(unsigned mask=0;mask<32;++mask)for(unsigned geometry=0;geometry<6;++geometry)for(unsigned mutation=0;mutation<8;++mutation){Case c={mask,geometry,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    stash update mismatch %u/%u/%u exits %d/%d first %lu\n",mask,geometry,mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(stashmenu_update_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=26;++fault)for(unsigned mutation=0;mutation<8;++mutation){Case c={4,1,mutation,fault};if(mutation==2&&fault>22)continue;autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash update unwind mismatch %u/%u exits %d/%d\n",fault,mutation,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED UPDATE EXCEPTIONS: %u matching unwinds, not normal coverage\n",count);return 0;}
