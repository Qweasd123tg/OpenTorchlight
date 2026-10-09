#include <cstring>
#include <new>
#include <string>
#include <OgreVector3.h>
#include "GameUI.h"
#include "Settings.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldKeys,(CGameUI*),"_ZN7CGameUI16handleKeyPressesEv")
extern "C" void newKeys(CGameUI*) __asm__("_ZN7CGameUI16handleKeyPressesEv");
extern "C" bool inventoryFlag __asm__("_ZL16gToggleInventory");
extern "C" bool statsFlag __asm__("_ZL12gToggleStats");
extern "C" bool petFlag __asm__("_ZL10gTogglePet");
extern "C" char removeLinked[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
TL_FUNCTION(f_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(f_integer,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(f_pressed,"_ZN11CKeyManager10keyPressedEj")
TL_FUNCTION(f_held,"_ZN11CKeyManager7keyHeldEj")
TL_FUNCTION(f_capture,"_ZN7CGameUI19captureProcessInputEv")
TL_FUNCTION(f_consoleToggle,"_ZN7CGameUI13toggleConsoleEv")
TL_FUNCTION(f_visible,"_ZN8CConsole10getVisibleEv")
TL_FUNCTION(f_inventory,"_ZN7CGameUI15toggleInventoryEv")
TL_FUNCTION(f_weapons,"_ZN10CCharacter18hasWeaponsInOffSetEv")
TL_FUNCTION(f_weaponToggle,"_ZN14CInventoryMenu15toggleWeaponSetEv")
TL_FUNCTION(f_skill,"_ZN7CGameUI11toggleSkillEv")
TL_FUNCTION(f_journal,"_ZN7CGameUI13toggleJournalEv")
TL_FUNCTION(f_quest,"_ZN7CGameUI11toggleQuestEv")
TL_FUNCTION(f_stats,"_ZN7CGameUI11toggleStatsEv")
TL_FUNCTION(f_pet,"_ZN7CGameUI9togglePetEv")
TL_FUNCTION(f_swap,"_ZN10CCharacter10swapSkillsEv")
TL_FUNCTION(f_automap,"_ZN6CLevel13toggleAutomapEv")
TL_FUNCTION(f_zoom,"_ZN6CLevel11zoomAutomapEf")
TL_FUNCTION(f_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(f_room,"_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(f_clipboard,"_ZN9UTILITIES16SetClipBoardTextESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(f_path,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(f_mkdir,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(f_string,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(f_sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(f_cycle,"_ZN10CCharacter10cycleSkillEi")
namespace {
struct Case {unsigned mask,flags,variant;};
unsigned long long memory[20][1024];void* menuTable[16];void* renderTable[64];
autotest::Capture* cap;const Case* c;unsigned masterCalls;bool consoleVisible;
std::wstring folder;
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void* obj(unsigned i){return memory[i];}
void n(int x){cap->add(&x,sizeof(x));}void f(float x){cap->add(&x,sizeof(x));}
void ptr(const void* p){if(!p){n(-1);return;}uintptr_t v=reinterpret_cast<uintptr_t>(p)-reinterpret_cast<uintptr_t>(memory);if(v>=sizeof(memory)){cap->issue=autotest::Capture::UnsupportedPointer;n(-2);return;}n(v);}
void e(int id,void* p){n(id);ptr(p);}
void wide(const std::wstring& x){n(x.size());cap->add(x.data(),x.size()*sizeof(wchar_t));}
void* master(){n(1);n(masterCalls++);return obj((c->variant&1)?(masterCalls%2?8:9):8);}
int integer(void* p,unsigned key){e(2,p);n(key);if(key==1)return (c->variant%3==0)?0:(c->variant%3==1?-1:101);return key+100;}
bool pressed(void* p,unsigned key){e(3,p);n(key);if(key==0x90)return c->mask&(1U<<20);if(key==0x78)return c->mask&(1U<<21);return key>=100&&key<120&&(c->mask&(1U<<(key-100)));}
bool held(void* p,unsigned key){e(4,p);n(key);return (c->flags&(key==0x10?2:1))!=0;}
void capture(void* p){e(5,p);n(at<bool>(p,0x12fb));n(at<int>(p,0x1674));n(at<int>(p,0x1678));n(at<int>(p,0x167c));at<bool>(p,0x1670)=true;}
void consoleToggle(void* p){e(6,p);if(c->flags&4)consoleVisible=!consoleVisible;}
bool visible(void* p){e(7,p);return consoleVisible;}
void inventory(void* p){e(8,p);n(inventoryFlag);}
bool weapons(void* p){e(9,p);return c->flags&8;}
bool open(void* p){e(10,p);return c->flags&16;}
void weaponToggle(void* p){e(11,p);}
void skill(void* p){e(12,p);}void journal(void* p){e(13,p);}void quest(void* p){e(14,p);}
void stats(void* p){e(15,p);n(statsFlag);}void pet(void* p){e(16,p);n(petFlag);}
void swap(void* p){e(17,p);}
void remove(void* p,void* child){e(18,p);ptr(child);at<void*>(child,0xb0)=0;}
void automap(void* p){e(19,p);}void zoom(void* p,float x){e(20,p);f(x);}
Ogre::Vector3 position(void* p,bool absolute){e(21,p);n(absolute);return Ogre::Vector3(1.25f,-3.5f,8.0f);}
void* room(void* p,const Ogre::Vector3& v){e(22,p);f(v.x);f(v.y);f(v.z);return c->flags&32?obj(12):0;}
void clipboard(std::wstring text){n(23);wide(text);}
std::wstring path(){n(24);return c->variant&1?L"/tmp/test/":L"/home/test/";}
bool mkdir(const std::wstring& p){n(25);wide(p);return c->variant&1;}
const std::wstring& string(void* p,unsigned key){e(26,p);n(key);return folder;}
std::string screenshot(void* p,const std::string& prefix,const std::string& suffix){e(27,p);n(prefix.size());cap->add(prefix.data(),prefix.size());n(suffix.size());cap->add(suffix.data(),suffix.size());return "fake-result.png";}
void sound(void* p,int sample,void* node,float a,float b,bool flag){e(28,p);n(sample);ptr(node);f(a);f(b);n(flag);if(c->variant&1)at<void*>(obj(0),0x38)=obj(2);}
void cycle(void* p,int direction){e(29,p);n(direction);}
void side(const Case& value,bool ours,autotest::Capture& out){
 c=&value;cap=&out;masterCalls=0;consoleVisible=c->flags&64;
 std::memset(memory,0xa5,sizeof(memory));
 at<void*>(obj(0),0x38)=obj(1);at<void*>(obj(0),0x40)=c->flags&128?0:obj(3);
 at<void*>(obj(0),0x78)=obj(4);at<void*>(obj(0),0x1308)=c->flags&256?0:obj(5);
 at<void*>(obj(0),0x1690)=obj(6);at<void*>(obj(0),0x4d8)=c->flags&512?0:obj(7);
 at<void*>(obj(0),0x4c0)=obj(10);at<void*>(obj(10),0x348)=obj(11);at<void*>(obj(11),0xb0)=c->flags&1024?obj(13):0;
 at<void*>(obj(0),0x16a8)=obj(14);at<void*>(obj(1),0x58)=obj(15);at<void*>(obj(2),0x58)=obj(16);
 at<void*>(obj(8),0x90)=obj(17);at<void*>(obj(9),0x90)=obj(18);
 at<void*>(obj(8),0xb0)=at<void*>(obj(9),0xb0)=c->flags&2048?0:obj(19);
 menuTable[4]=reinterpret_cast<void*>(&open);at<void*>(obj(7),0)=menuTable;
 renderTable[35]=reinterpret_cast<void*>(&screenshot);at<void*>(obj(19),0)=renderTable;
 at<int>(obj(3),0x1a4)=c->variant? -17:41;at<int>(obj(3),0x228)=c->variant?(-2147483647-1):2147483647;
 at<bool>(obj(0),0x1999)=c->flags&4096;at<bool>(obj(0),0x12fb)=true;at<bool>(obj(0),0x1670)=false;
 at<int>(obj(0),0x1674)=71;at<int>(obj(0),0x1678)=-18;at<int>(obj(0),0x167c)=99;
 inventoryFlag=c->flags&8192;statsFlag=c->flags&16384;petFlag=c->flags&32768;
 folder=c->variant&1?L"screens/":L"shots/";
 new(&at<std::wstring>(obj(12),0x168))std::wstring(c->variant&1?L"room_\x03a9_\x1f600":L"room.alpha");
 KSETTINGS_KEYMAP_CONSOLE_HOLD=1;
 KSETTINGS_KEYMAP_CONSOLE_PRESS=2;
 KSETTINGS_KEYMAP_INVENTORY=3;
 KSETTINGS_KEYMAP_WEAPONSET=4;
 KSETTINGS_KEYMAP_SKILLS=5;
 KSETTINGS_KEYMAP_JOURNAL=6;
 KSETTINGS_KEYMAP_QUESTS=7;
 KSETTINGS_KEYMAP_STATS=8;
 KSETTINGS_KEYMAP_PET=9;
 KSETTINGS_KEYMAP_SWAPSKILLS=10;
 KSETTINGS_KEYMAP_AUTOMAP=11;
 KSETTINGS_KEYMAP_AUTOMAPZOOMOUT=12;
 KSETTINGS_KEYMAP_AUTOMAPZOOMIN=13;
 KSETTINGS_KEYMAP_CYCLESKILLDOWN=14;
 KSETTINGS_KEYMAP_CYCLESKILLUP=15;
 KSETTINGS_S_PATH_SCREENSHOTS=99;
 detour::Set patches;
 TL_REDIRECT(patches,f_master,master);
 TL_REDIRECT(patches,f_integer,integer);
 TL_REDIRECT(patches,f_pressed,pressed);
 TL_REDIRECT(patches,f_held,held);
 TL_REDIRECT(patches,f_capture,capture);
 TL_REDIRECT(patches,f_consoleToggle,consoleToggle);
 TL_REDIRECT(patches,f_visible,visible);
 TL_REDIRECT(patches,f_inventory,inventory);
 TL_REDIRECT(patches,f_weapons,weapons);
 TL_REDIRECT(patches,f_weaponToggle,weaponToggle);
 TL_REDIRECT(patches,f_skill,skill);
 TL_REDIRECT(patches,f_journal,journal);
 TL_REDIRECT(patches,f_quest,quest);
 TL_REDIRECT(patches,f_stats,stats);
 TL_REDIRECT(patches,f_pet,pet);
 TL_REDIRECT(patches,f_swap,swap);
 TL_REDIRECT(patches,f_automap,automap);
 TL_REDIRECT(patches,f_zoom,zoom);
 TL_REDIRECT(patches,f_position,position);
 TL_REDIRECT(patches,f_room,room);
 TL_REDIRECT(patches,f_clipboard,clipboard);
 TL_REDIRECT(patches,f_path,path);
 TL_REDIRECT(patches,f_mkdir,mkdir);
 TL_REDIRECT(patches,f_string,string);
 TL_REDIRECT(patches,f_sound,sound);
 TL_REDIRECT(patches,f_cycle,cycle);
 patches.redirect(removeLinked,removeLinked,&remove);
 if(patches.failed()){out.issue=autotest::Capture::UnsupportedPointer;return;}
 CGameUI* ui=reinterpret_cast<CGameUI*>(obj(0));
 if(ours)autotest::invoke(out,&newKeys,ui);else autotest::invoke(out,&oldKeys,ui);
 out.add(obj(0),0x1a08);ptr(at<void*>(obj(11),0xb0));n(inventoryFlag);n(statsFlag);n(petFlag);
 at<std::wstring>(obj(12),0x168).~basic_string();
}
void a(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),false,o);}void b(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(gameui_keyboard_dispatch_differential){
 autotest::Coverage coverage("gameui_keyboard_dispatch_differential",reinterpret_cast<uintptr_t>(&oldKeys));
 for(unsigned i=0;i<256;++i){
  Case c={i<24?(1U<<i):((i*2654435761U)&0x3fffff),i<24?0U:((i*40503U)&65535),i%6};
  if(i>=240){c.mask=0x3fffff;c.flags=(1U<<(i-240))|3;c.variant=i%6;}
  autotest::Outcome l,r;autotest::runChild(a,&c,l);autotest::runChild(b,&c,r);
  int diff=coverage.observe(host,l,r);
  if(diff||l.childStatus||r.childStatus||!l.capture.callCompleted||!r.capture.callCompleted){coverage.report(host);host->log("    keyboard case=%u mask=%x flags=%x variant=%u exits=%d/%d sizes=%lu/%lu\n",i,c.mask,c.flags,c.variant,l.childStatus,r.childStatus,(unsigned long)l.capture.length,(unsigned long)r.capture.length);return 1;}
 }
 coverage.report(host);return 0;
}
