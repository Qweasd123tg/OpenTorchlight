#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "InventoryMenu.h"
#include "Character.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalToggle,(CInventoryMenu*),"_ZN14CInventoryMenu15toggleWeaponSetEv")
TL_ORIGINAL(bool,originalClose,(CInventoryMenu*,const CEGUI::EventArgs*),"_ZN14CInventoryMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
extern "C" void candidateToggle(CInventoryMenu*) __asm__("_ZN14CInventoryMenu15toggleWeaponSetEv");
extern "C" bool candidateClose(CInventoryMenu*,const CEGUI::EventArgs*) __asm__("_ZN14CInventoryMenu18handle_CloseButtonERKN5CEGUI9EventArgsE");
TL_FUNCTION(aliveFn,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(attackFn,"_ZN10CCharacter21performingAttackLooseEv")
TL_FUNCTION(skillFn,"_ZN10CCharacter20performingSkillLooseEv")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(removeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" char selectedFn[] __asm__("_ZN5CEGUI8Checkbox11setSelectedEb");
namespace {
struct Case {unsigned mask,mutation,button;bool close;};const Case* cs;autotest::Capture* cap;CInventoryMenu* menu;CCharacter* actor[2];CEGUI::Checkbox* checkbox;CSoundBank* bank;unsigned char* client;CRunicCore* objects[4];unsigned calls;
void n(int v){cap->add(&v,4);}int actorId(CCharacter* p){return p==actor[0]?1:p==actor[1]?2:0;}
void mutate(){if(cs->mutation)menu->m_pCharacter=actor[(++calls)&1];if(cs->mutation==2)menu->m_bCloseRequested=!menu->m_bCloseRequested;}
bool alive(CCharacter* p){n(1);n(actorId(p));mutate();return cs->mask&2;}
bool attack(CCharacter* p){n(2);n(actorId(p));mutate();return cs->mask&4;}
bool skill(CCharacter* p){n(3);n(actorId(p));mutate();return cs->mask&8;}
void selected(CEGUI::Checkbox* p,bool v){n(4);n(p==checkbox);n(v);*reinterpret_cast<bool*>(reinterpret_cast<char*>(p)+0x732)=v;mutate();}
void sound(CSoundBank* p,int index,Ogre::SceneNode* node,float a,float b,bool f){n(5);n(p==bank);n(index);n(node==0);cap->add(&a,4);cap->add(&b,4);n(f);mutate();}
void remove(CRunicCore* p,TSafePointer<void*>* ref,unsigned index){n(6);int id=0;for(unsigned i=0;i<4;++i)if(p==objects[i])id=i+1;n(id);n((unsigned char*)ref-client);n(index);if(cs->mutation){menu->m_bCloseRequested=false;unsigned next=((unsigned char*)ref-client)==0x1f8?2:((unsigned char*)ref-client)==0x1e8?0:((unsigned char*)ref-client)==0x1c8?1:3;CRunicCore* q=objects[(next+1)%4];std::memcpy(client+0x1c8+16*next,&q,8);}}
void ptr(unsigned char* b,size_t o,uintptr_t p){std::memcpy(b+o,&p,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;calls=0;unsigned long long mm[(sizeof(CInventoryMenu)+23)/8],am[2][(sizeof(CCharacter)+7)/8]={0},cm[(sizeof(CEGUI::Checkbox)+7)/8]={0},um[(sizeof(CGameUI)+7)/8]={0},clientMemory[0x240/8]={0},om[4][8]={0},bm[16]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CInventoryMenu*)mm;actor[0]=(CCharacter*)am[0];actor[1]=(CCharacter*)am[1];checkbox=(CEGUI::Checkbox*)cm;bank=(CSoundBank*)bm;client=(unsigned char*)clientMemory;menu->m_pCharacter=c.mask&1?actor[0]:0;menu->m_pWeaponSwitchWindow=checkbox;menu->m_pSoundBank=bank;menu->m_pGameUI=(CGameUI*)um;menu->m_bCloseRequested=c.mask&32;*reinterpret_cast<bool*>(reinterpret_cast<char*>(checkbox)+0x732)=c.mask&16;ptr((unsigned char*)um,0x1920,(uintptr_t)client);
 for(unsigned i=0;i<4;++i){objects[i]=(CRunicCore*)om[i];ptr(client,0x1c8+16*i,c.mask&(1u<<i)?(uintptr_t)objects[i]:0);unsigned index=0xabcdef00u+i;std::memcpy(client+0x1d0+16*i,&index,4);}
 CEGUI::MouseEventArgs event(0);event.button=(CEGUI::MouseButton)c.button;detour::Set d;TL_REDIRECT(d,aliveFn,&alive);TL_REDIRECT(d,attackFn,&attack);TL_REDIRECT(d,skillFn,&skill);TL_REDIRECT(d,soundFn,&sound);TL_REDIRECT(d,removeFn,&remove);d.redirect(selectedFn,selectedFn,&selected);if(d.failed())_exit(61);
 if(c.close){if(ours)autotest::invoke(out,&candidateClose,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalClose,menu,static_cast<const CEGUI::EventArgs*>(&event));}else {if(ours)autotest::invoke(out,&candidateToggle,menu);else autotest::invoke(out,&originalToggle,menu);}
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x50,actorId(menu->m_pCharacter));ptr(snapshot,0x70,1);ptr(snapshot,0x9188,2);ptr(snapshot,0x9198,3);cap->add(snapshot,sizeof(snapshot));n(*reinterpret_cast<bool*>(reinterpret_cast<char*>(checkbox)+0x732));n(calls);for(unsigned i=0;i<4;++i){CRunicCore* q;std::memcpy(&q,client+0x1c8+16*i,8);int id=0;for(unsigned j=0;j<4;++j)if(q==objects[j])id=j+1;ptr(client,0x1c8+16*i,id);}cap->add(client,sizeof(clientMemory));
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,bool close){autotest::Coverage coverage(close?"inventorymenu_close":"inventorymenu_weapon_toggle",close?(uint64_t)(uintptr_t)&originalClose:(uint64_t)(uintptr_t)&originalToggle);for(unsigned mask=0;mask<64;++mask)for(unsigned mutation=0;mutation<3;++mutation)for(unsigned button=0;button<(close?4u:1u);++button){Case c={mask,mutation,button,close};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    action mismatch %u/%u/%u close %d exits %d/%d\n",mask,mutation,button,close,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(inventorymenu_weapon_toggle){return run(host,false);}
TL_TEST(inventorymenu_close){return run(host,true);}
