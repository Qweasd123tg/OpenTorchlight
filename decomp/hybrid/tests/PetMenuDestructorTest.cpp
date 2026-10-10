#include <cstring>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "PetMenu.h"
#include "GenericModel.h"
#include "SoundBank.h"
#include "SkillTooltip.h"
#include "Character.h"
#include "Inventory.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalDtor,(CPetMenu*),"_ZN8CPetMenuD1Ev")
TL_ORIGINAL(void,originalDelete,(CPetMenu*),"_ZN8CPetMenuD0Ev")
extern "C" void candidateDtor(CPetMenu*) __asm__("_ZN8CPetMenuD1Ev");
extern "C" void candidateDelete(CPetMenu*) __asm__("_ZN8CPetMenuD0Ev");
TL_FUNCTION(coreFn,"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(removeFn,"_ZN10CInventory14removeListenerEP18iInventoryListener")
TL_FUNCTION(layoutFn,"_ZN8CPetMenu12updateLayoutEv")
extern "C" char stringDtorFn[] __asm__("_ZN5CEGUI6StringD1Ev");
extern "C" char arrayFreeFn[] __asm__("_ZdaPv");
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
struct Stop{};struct Case {unsigned mask,pattern;bool replace,deleting;unsigned fault;};
const Case* cs;autotest::Capture* cap;CPetMenu* menu;void* objects[4];unsigned destroyed[4],coreCalls,freeCalls,arrayCalls,stringCalls,deleteCalls;void* arrayPointer;CCharacter* actor;CInventory* inventory;void* scene;void* camera;
void n(int value){cap->add(&value,4);}int id(void* p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==objects[i])return i+1;return 99;}
void remove(CInventory* p,iInventoryListener* listener){n(5);n(p==inventory);n(listener==static_cast<iInventoryListener*>(menu));n(menu->m_pCharacter==actor);if(cs->fault==1)throw Stop();}
void layout(CPetMenu* p){n(6);n(p==menu);n(menu->m_pCharacter==0);if(cs->fault==2)throw Stop();if(cs->replace)menu->m_pPetModel=(CGenericModel*)objects[3];}
void destroyCamera(void* p,void* c){n(7);n(p==scene);n(c==camera);if(cs->fault==3)throw Stop();if(cs->replace)menu->m_pWardrobeCamera=(Ogre::Camera*)objects[3];}
void destroy(void* p){unsigned i=id(p)-1;n(1);n(i);if(i>=4)_exit(64);++destroyed[i];n(id(menu->m_pPetModel));n(id(menu->m_pSoundBank));n(id(menu->m_pSkillTooltip));if(cs->fault==3+(++deleteCalls))throw Stop();if(cs->replace&&(i==0||i==3))menu->m_pSoundBank=(CSoundBank*)objects[3];}
void core(CRunicCore* p){n(2);n(p==static_cast<CRunicCore*>(menu));++coreCalls;n(id(menu->m_pPetModel));n(id(menu->m_pSoundBank));n(id(menu->m_pSkillTooltip));}
void stringDtor(CEGUI::String* p){ptrdiff_t off=(char*)p-(char*)menu;n(8);n(off);n(p->length());for(size_t i=0;i<p->length();++i)n((*p)[i]);++stringCalls;}
void arrayRelease(void* p){n(4);n(p==arrayPointer);++arrayCalls;}
void release(void* p){n(3);n(p==menu);++freeCalls;}
void ptr(unsigned char* bytes,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(bytes+offset,&v,sizeof(v));}
CEGUI::String* stringAt(unsigned i){if(i<82)return &menu->m_DefaultSlotImages[i];if(i<164)return &menu->m_DefaultSlotTooltips[i-82];if(i<167)return &menu->m_TabUnselectedImages[i-164];return &menu->m_TabSelectedImages[i-167];}
void side(const Case& c,bool ours,autotest::Capture& out){unsigned long long mem[(sizeof(CPetMenu)+16+7)/8],fake[4][4],am[(sizeof(CCharacter)+7)/8]={0},im[(sizeof(CInventory)+7)/8]={0},sm[8]={0},cm[8]={0};void* table[2]={0,(void*)&destroy};std::memset(mem,c.replace?0x5a:0xa5,sizeof(mem));std::memset(fake,0x67,sizeof(fake));for(unsigned i=0;i<4;++i){objects[i]=fake[i];*(void***)objects[i]=table;destroyed[i]=0;}menu=(CPetMenu*)mem;cs=&c;cap=&out;coreCalls=freeCalls=arrayCalls=stringCalls=deleteCalls=0;actor=(CCharacter*)am;inventory=(CInventory*)im;actor->m_pInventory=c.mask&16?inventory:0;menu->m_pCharacter=c.mask&8?actor:0;scene=sm;camera=cm;void* sv[57]={0};sv[56]=(void*)&destroyCamera;*(void***)scene=sv;menu->m_pWardrobeSceneManager=(Ogre::SceneManager*)scene;menu->m_pWardrobeCamera=c.mask&32?(Ogre::Camera*)camera:0;
 menu->m_pPetModel=c.mask&1?(CGenericModel*)objects[0]:0;menu->m_pSoundBank=c.mask&2?(CSoundBank*)objects[1]:0;menu->m_pSkillTooltip=c.mask&4?(CSkillTooltip*)objects[2]:0;
 new(&menu->m_UnknownList70)TArrayList<unsigned char>(3);if(c.pattern){menu->m_UnknownList70.add(0);if(c.pattern>1)menu->m_UnknownList70.add(255);if(c.pattern>2)menu->m_UnknownList70.add(127);}std::memcpy(&arrayPointer,&menu->m_UnknownList70,sizeof(arrayPointer));
 for(unsigned i=0;i<170;++i)new(stringAt(i))CEGUI::String(c.pattern==0?"":c.pattern==1?"short":c.pattern==2?"long-value-long-value-long-value-long-value":"unicode-placeholder");
 detour::Set d;TL_REDIRECT(d,coreFn,&core);TL_REDIRECT(d,removeFn,&remove);TL_REDIRECT(d,layoutFn,&layout);d.redirect(freeFn,freeFn,&release);d.redirect(arrayFreeFn,arrayFreeFn,&arrayRelease);d.redirect(stringDtorFn,stringDtorFn,&stringDtor);if(d.failed())_exit(65);
 bool threw=false;try{if(ours)autotest::invoke(out,c.deleting?&candidateDelete:&candidateDtor,menu);else autotest::invoke(out,c.deleting?&originalDelete:&originalDtor,menu);}catch(const Stop&){threw=true;}catch(...){_exit(66);}
 n(threw);n(coreCalls);n(freeCalls);n(arrayCalls);n(stringCalls);for(unsigned i=0;i<4;++i)n(destroyed[i]);unsigned char snapshot[sizeof(mem)];std::memcpy(snapshot,menu,sizeof(snapshot));ptr(snapshot,0x91a0,id(menu->m_pPetModel));ptr(snapshot,0x91b8,id(menu->m_pSoundBank));ptr(snapshot,0x91f0,id(menu->m_pSkillTooltip));ptr(snapshot,0x58,menu->m_pCharacter==actor?1:menu->m_pCharacter==0?0:99);ptr(snapshot,0x9168,menu->m_pWardrobeSceneManager==scene);ptr(snapshot,0x9170,menu->m_pWardrobeCamera==camera?1:menu->m_pWardrobeCamera==0?0:99);
 void* remaining;std::memcpy(&remaining,&menu->m_UnknownList70,sizeof(remaining));if(remaining==arrayPointer)ptr(snapshot,0x70,arrayPointer?1:0);else if(!remaining)ptr(snapshot,0x70,0);
 for(unsigned i=0;i<170;++i){CEGUI::String* q=stringAt(i);if(q->d_reserve>32)ptr(snapshot,(char*)q-(char*)menu+0xa8,i+1);}
 cap->add(snapshot,sizeof(snapshot));}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
int normal(const tlhybrid_host* host,bool deleting,const char* name){autotest::Coverage coverage(name,(uint64_t)(uintptr_t)(deleting?&originalDelete:&originalDtor));for(unsigned mask=0;mask<64;++mask)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change){Case c={mask,pattern,bool(change),deleting,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    pet dtor mismatch %u/%u/%u exits %d/%d first %lu lengths %lu/%lu\n",mask,pattern,change,u.childStatus,v.childStatus,(unsigned long)f,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(petmenu_destructor_differential){return normal(host,false,"petmenu_destructor_differential");}
TL_TEST(petmenu_deleting_destructor_differential){return normal(host,true,"petmenu_deleting_destructor_differential");}
TL_TEST(petmenu_destructor_expected_exceptions){unsigned total=0;for(unsigned fault=1;fault<=6;++fault)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change){Case c={63,pattern,bool(change),false,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    pet dtor unwind mismatch %u/%u/%u exits %d/%d lengths %lu/%lu\n",fault,pattern,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}host->log("    EXPECTED DESTRUCTOR EXCEPTIONS: %u matching unwinds, excluded from normal completion coverage\n",total);return 0;}
