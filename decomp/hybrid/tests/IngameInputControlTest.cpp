// Controlled full-entry tests for input arbitration and lifecycle branches.
// Inventory/skill payload branches have a separate matrix; this is not full acceptance.
#include <cstring>
#include <vector>
#include <new>
#include "GameUI.h"
#include <OgreVector3.h>
#include <CEGUI.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,oldInput,(CGameUI*,void*,float,bool),"_ZN7CGameUI18processIngameInputEPvfb")
extern "C" bool newInput(CGameUI*,void*,float,bool) __asm__("_ZN7CGameUI18processIngameInputEPvfb");
TL_FUNCTION(captureFn,"_ZN7CGameUI19captureProcessInputEv")
TL_FUNCTION(updateFn,"_ZN13CMouseManager6updateEPv")
TL_FUNCTION(buttonFn,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(handleFn,"_ZN7CGameUI16handleKeyPressesEv")
TL_FUNCTION(aliveFn,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(cinematicFn,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(keyFn,"_ZN11CKeyManager10keyPressedEj")
TL_FUNCTION(unpauseFn,"_ZN7CGameUI7unPauseEv")
TL_FUNCTION(eitherFn,"_ZN7CGameUI20eitherCoveredPartialEv")
TL_FUNCTION(bothFn,"_ZN7CGameUI18bothCoveredPartialEv")
TL_FUNCTION(modalFn,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(closeFn,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(pauseFn,"_ZN7CGameUI11togglePauseEv")
TL_FUNCTION(clickFn,"_ZN7CGameUI13menuItemClickEP10CCharacterP8CSubMenuib")
TL_FUNCTION(slotFn,"_ZN10CInventory18getEquipmentInSlotEj")
extern "C" char singletonFn[] __asm__("_ZN5CEGUI6System12getSingletonEv");
extern "C" char positionFn[] __asm__("_ZN5CEGUI6System19injectMousePositionEff");
extern "C" char pulseFn[] __asm__("_ZN5CEGUI6System15injectTimePulseEf");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
TL_FUNCTION(skillLookupFn,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(skillLevelFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(skillNameFn,"_ZN6CSkill7getNameEv")
TL_FUNCTION(activeFn,"_ZN10CCharacter14setActiveSkillEP6CSkillb")
TL_FUNCTION(leftNameFn,"_ZN10CCharacter18setLeftSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(rightMapFn,"_ZN7CPlayer22setMappedFunctionSkillEjx")
TL_FUNCTION(leftMapFn,"_ZN7CPlayer26setLeftMappedFunctionSkillEjx")
TL_FUNCTION(foldoutFn,"_ZN13CSkillFoldout11showFoldoutEP9CBaseUnitffbb")
TL_FUNCTION(skillTooltipFn,"_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
extern "C" char moveFn[] __asm__("_ZN5CEGUI6System15injectMouseMoveEff");
TL_FUNCTION(unitIsFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(equipFn,"_ZN10CInventory35equipEquipmentIntoFirstFreeLocationEP10CEquipment")
TL_FUNCTION(comparisonFn,"_ZN10CInventory18getComparisonItemsEP10CEquipmentPS1_S2_")
TL_FUNCTION(removeItemFn,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(pickupFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(useFn,"_ZN7CGameUI7useItemER6CLevelP10CEquipment")
TL_FUNCTION(behindFn,"_ZN10CCharacter15setRenderBehindEb")
TL_FUNCTION(dropSoundFn,"_ZN10CEquipment13playDropSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(queueFn,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(actorPositionFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(addItemFn,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(returnDraggedFn,"_ZN7CGameUI17returnDraggedItemEv")
TL_FUNCTION(cursorFn,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(hardwareFn,"_ZN7CGameUI20updateHardwareCursorEv")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(removeSafeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(addSafeFn,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
extern "C" char windowPositionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
TL_FUNCTION(equipmentTooltipFn,"_ZN7CGameUI20showEquipmentTooltipEP10CCharacterP10CEquipmentP17CEquipmentTooltipS5_S5_")
TL_FUNCTION(equipmentGuidFn,"_ZN10CInventory18getEquipmentOfGuidEx")
namespace {
struct Case {unsigned scenario,variant;};
unsigned long long storage[64][5120];
const wchar_t* borrowedName;
void* itemTable[128];unsigned equipCalls,pickupCalls,scaleCalls,dispatchCalls;
void* menuTable[16];void* actorTable[16];void* fishTable[8];void* dropdownTable[8];
autotest::Capture* cap;const Case* input;unsigned enabledCalls,keyCalls;bool opened[64];
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void* obj(unsigned i){return storage[i];}
int id(const void* p){if(!p)return -1;uintptr_t off=reinterpret_cast<uintptr_t>(p)-reinterpret_cast<uintptr_t>(storage);if(off>=sizeof(storage)){cap->issue=autotest::Capture::UnsupportedPointer;return -2;}return off/sizeof(storage[0]);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void ptr(const void* p){n(id(p));if(id(p)>=0)n(static_cast<const char*>(p)-static_cast<const char*>(obj(id(p))));}
void event(int e,void* p){n(e);ptr(p);}
void capture(void* p){event(1,p);at<bool>(p,0x1670)=input->scenario==1;}
void update(void* p,void* window){event(2,p);ptr(window);if(input->variant&1){at<long long>(obj(0),0x12d0)+=7;at<long long>(obj(0),0x12d8)-=3;}}
bool button(void* p,int b){event(3,p);n(b);return (input->scenario==64&&b==1) || input->scenario==2 || (input->scenario==3 && b==0) || (input->scenario>=40&&input->scenario<=45&&b==(input->scenario==44?1:0));}
void* singleton(){n(4);return obj(30);}
bool position(void* p,float x,float y){event(5,p);f(x);f(y);return true;}
bool pulse(void* p,float dt){event(6,p);f(dt);return true;}
void remove(void* p,void* child){event(7,p);ptr(child);if(at<void*>(child,0xb0)==p)at<void*>(child,0xb0)=NULL;}
bool enabled(void* p){event(8,p);n(enabledCalls);unsigned masks[]={7,0,1,3,5,6,2,4};return ((input->scenario==0?masks[input->variant]:7)& (1U<<enabledCalls++))!=0;}
void handle(void* p){event(9,p);}
bool alive(void* p){event(10,p);return input->scenario!=4&&input->scenario!=65;}
unsigned cinematic(void* p){event(11,p);return input->scenario==5?0x101:0x100;}
int settings(void* p,unsigned key){event(12,p);n(key);return 100+keyCalls;}
bool key(void* p,unsigned code){event(13,p);n(code);unsigned k=keyCalls++;if(input->scenario>=18&&k>=2){unsigned masks[]={4095,1,2048,1365,2730,0,65,1026};return (masks[input->variant]&(1U<<((k-2)%12)))!=0;}return (input->scenario==6 && k==0)||(input->scenario==7&&k==1)||input->scenario==8;}
void unpause(void* p){event(14,p);at<bool>(p,0x1999)=false;}
bool either(void* p){event(15,p);return input->variant&1;}
bool both(void* p){event(16,p);return input->variant&2;}
bool modal(void* p){event(17,p);return input->variant&2;}
void close(void* p){event(18,p);for(unsigned i=4;i<16;++i)opened[i]=false;}
void pause(void* p){event(19,p);at<bool>(p,0x1999)=!at<bool>(p,0x1999);}
void front(void* p){event(20,p);}
bool open(void* p){event(21,p);return opened[id(p)];}
void setOpen(void* p,bool value){event(22,p);n(value);opened[id(p)]=value;}
void layout(void* p){event(23,p);}
void* owner(void* p){event(24,p);return obj(id(p)==6?2:id(p)==7?3:id(p)==10?16:1);}
bool click(void* p,void* who,void* menu,int slot,bool incoming){event(25,p);ptr(who);ptr(menu);n(slot);n(incoming);return (input->variant&4)==0;}
void* slot(void* p,unsigned index){event(26,p);n(index);return input->scenario>=30&&input->scenario<=39?obj(41):NULL;}
bool process(void* p,void* window,float dt,bool enabled){event(27,p);ptr(window);f(dt);n(enabled);
 if(input->scenario>=61){std::vector<void*>& menus=at<std::vector<void*> >(obj(0),0x1930);std::vector<void*>& drops=at<std::vector<void*> >(obj(0),0x1948);n(dispatchCalls++);
  if(id(p)==14){drops.push_back(obj(15));menus.push_back(obj(4));}
  if(id(p)==15&&dispatchCalls==2){if(input->scenario==61)drops.push_back(obj(15));if(input->scenario==62)drops.clear();menus.push_back(obj(6));}
  if(id(p)==4&&input->scenario==63)menus.clear();
 }
 return (input->variant&(1U<<(id(p)%3)))==0;}
unsigned long long dropdown(void* p,void* window,float dt,bool enabled){bool result=process(p,window,dt,enabled);return 0x123400+(result?1:0);}
void wide(long long x){cap->add(&x,8);}
void* skillLookup(void* p,long long guid){event(40,p);wide(guid);return guid==101?obj(44):guid==102?obj(45):NULL;}
void skillLevel(void* p){event(41,p);}
const std::wstring& skillName(void* p){event(42,p);return *reinterpret_cast<std::wstring*>(obj(48));}
void active(void* p,void* skill,bool flag){event(43,p);ptr(skill);n(flag);}
void leftName(void* p,std::wstring name){event(44,p);cap->addText(name);if(input->scenario==71||input->scenario==72){borrowedName=name.c_str();int refs;std::memcpy(&refs,reinterpret_cast<const char*>(borrowedName)-8,4);n(refs);throw 711;}}
void rightMap(void* p,unsigned index,long long guid){event(45,p);n(index);wide(guid);at<long long>(p,0x950+index*8)=guid;}
void leftMap(void* p,unsigned index,long long guid){event(46,p);n(index);wide(guid);at<long long>(p,0x9b0+index*8)=guid;}
void foldout(void* p,void* who,float x,float y,bool a,bool b){event(47,p);ptr(who);f(x);f(y);n(a);n(b);at<void*>(obj(31),0xb0)=obj(35);}
void skillTooltip(void* p,void* who,void* skill,float x,float y){event(48,p);ptr(who);ptr(skill);f(x);f(y);at<void*>(obj(32),0xb0)=obj(35);}
void sound(void* p,int sample,void* scene,float x,float y,bool loop){event(49,p);n(sample);ptr(scene);f(x);f(y);n(loop);}
bool move(void* p,float x,float y){event(50,p);f(x);f(y);return true;}
bool unitIs(void* p,int tag){event(60,p);n(tag);if(input->scenario>=46&&input->scenario<=60){const int tags[]={8,13,39,999};return tag==tags[input->variant%4];}if(input->scenario==30||input->scenario==31)return tag==((input->variant&1)?32:1);if(input->scenario==36||input->scenario==37)return tag==10;return input->scenario==42&&tag==103;}
bool equip(void* p,void* item){event(61,p);ptr(item);n(equipCalls);bool result=input->scenario==32||input->scenario==33||(equipCalls>0&&(input->variant&4));++equipCalls;return result;}
bool canEquip(void* p,void* who,bool flag){event(62,p);ptr(who);n(flag);return input->scenario!=34&&input->scenario!=35;}
void comparison(void* p,void* item,void** first,void** second){event(63,p);ptr(item);*first=(input->variant&1)?obj(42):NULL;*second=(input->variant&2)?obj(49):NULL;}
void removeItem(void* p,void* item){event(64,p);ptr(item);}
void* pickup(void* p,void* item,bool flag){event(65,p);ptr(item);n(flag);n(pickupCalls++);return (input->variant&4)?NULL:item;}
void use(void* p,void* level,void* item){event(66,p);ptr(level);ptr(item);}
void behind(void* p,bool flag){event(67,p);n(flag);}
void dropSound(void* p,void* scene){event(68,p);ptr(scene);}
void queue(void* p,int sample,float x,float y){event(69,p);n(sample);f(x);f(y);}
Ogre::Vector3 actorPosition(void* p,bool flag){event(70,p);n(flag);return Ogre::Vector3(float(id(p)),2.5f,-3.25f);}
void addItem(void* p,void* item,const Ogre::Vector3& v,bool flag){event(71,p);ptr(item);f(v.x);f(v.y);f(v.z);n(flag);}
void drop(void* p){event(72,p);}
void returnDragged(void* p){event(73,p);}
void cursor(void* p,int state){event(74,p);n(state);}
void hardware(void* p){event(75,p);}
float scaled(void* p,float x){event(76,p);f(x);if((input->variant&4)&&scaleCalls++==0)at<long long>(p,0x12d0)+=37;return x*.75f;}
void windowPosition(void* p,const CEGUI::UVector2& v){event(77,p);cap->add(&v,sizeof(v));}
void removeSafe(void* p,void* ref,unsigned index){event(78,p);ptr(ref);n(index);}
unsigned addSafe(void* p,void* ref){event(79,p);ptr(ref);return 13;}
void equipmentTooltip(void* p,void* who,void* item,void* tooltip,void* a,void* b){event(80,p);ptr(who);ptr(item);ptr(tooltip);ptr(a);ptr(b);at<long long>(tooltip,0x10)=at<long long>(item,0x10);at<void*>(at<void*>(tooltip,0x20),0xb0)=obj(35);}
void* equipmentGuid(void* p,long long guid){event(81,p);wide(guid);return input->variant==7?NULL:obj(55);}
void setup(const Case& c,autotest::Capture& out){
 cap=&out;input=&c;std::memset(storage,0,sizeof(storage));std::memset(opened,0,sizeof(opened));enabledCalls=keyCalls=equipCalls=pickupCalls=scaleCalls=dispatchCalls=0;
 std::memset(menuTable,0,sizeof(menuTable));menuTable[2]=(void*)&owner;menuTable[4]=(void*)&open;menuTable[8]=(void*)&setOpen;menuTable[9]=(void*)&layout;menuTable[12]=(void*)&process;
 actorTable[9]=(void*)&enabled;fishTable[4]=(void*)&process;dropdownTable[2]=(void*)&dropdown;
 for(unsigned i=1;i<4;++i){at<void*>(obj(i),0)=actorTable;at<void*>(obj(i),0x490)=obj(17+i);}
 const unsigned menuOffsets[]={0x4d8,0x4e0,0x4e8,0x4f0,0x4f8,0x500,0x508,0x558,0x568,0x538};
 for(unsigned i=0;i<10;++i){at<void*>(obj(0),menuOffsets[i])=obj(4+i);at<void*>(obj(4+i),0)=menuTable;}
 at<void*>(obj(0),0x38)=obj(1);at<void*>(obj(0),0x78)=obj(21);at<long long>(obj(0),0xb0)=-1;
 at<void*>(obj(0),0x578)=obj(14);at<void*>(obj(14),0)=fishTable;
 at<void*>(obj(0),0x4c0)=obj(22);at<void*>(obj(22),0x348)=obj(31);
 at<void*>(obj(0),0x4b8)=obj(23);at<void*>(obj(23),0x30)=obj(32);
 at<void*>(obj(0),0x1318)=obj(33);at<void*>(obj(0),0x138)=obj(34);
 for(unsigned i=0;i<3;++i){at<void*>(obj(0),0x4a0+8*i)=obj(24+i);at<void*>(obj(24+i),0x18)=obj(35);at<void*>(obj(24+i),0x20)=obj(36+i);}
 for(unsigned i=31;i<=38;++i)at<void*>(obj(i),0xb0)=(c.variant&4)?obj(35):NULL;
 at<bool>(obj(0),0x1998)=c.variant&1;at<bool>(obj(0),0x1999)=c.variant&2;at<bool>(obj(0),0x12fb)=c.scenario==3;
 at<bool>(obj(0),0x1640)=c.variant&2;
 at<long long>(obj(0),0x12d0)=(c.variant&1)?(1LL<<33)+17:-77;
 at<long long>(obj(0),0x12d8)=(c.variant&2)?-(1LL<<33)+19:81;
 const unsigned slots[]={0x1674,0x1678,0x167c};for(unsigned i=0;i<3;++i)at<int>(obj(0),slots[i])=-1;
 const unsigned clickOffsets[]={0x78,0x98,0x3428,0xe8,0x188,0x33f8};const unsigned clickIDs[]={4,6,7,8,9,10};
 for(unsigned i=0;i<6;++i)for(unsigned k=0;k<(i==2||i==5?3:2);++k)at<int>(obj(clickIDs[i]),clickOffsets[i]+4*k)=-1;
 if(c.scenario==9)at<int>(obj(0),0x1674)=27;
 if(c.scenario==10)at<int>(obj(0),0x1678)=28;
 if(c.scenario==11)at<int>(obj(0),0x167c)=29;
 if(c.scenario==12){for(unsigned i=4;i<=10;++i)opened[i]=true;at<int>(obj(4),0x78)=30;at<int>(obj(8),0xe8)=31;at<int>(obj(9),0x188)=32;}
 if(c.scenario==13){opened[6]=opened[7]=opened[10]=true;at<int>(obj(7),0x3428)=33;at<int>(obj(10),0x33f8)=34;}
 if(c.scenario==14){opened[7]=opened[10]=true;at<int>(obj(7),0x3430)=35;at<int>(obj(10),0x3400)=36;}
 if(c.scenario==15){opened[6]=true;at<int>(obj(6),0x9c)=37;}
 if(c.scenario==16){at<void*>(obj(0),0x540)=obj(27);at<bool>(obj(27),0x30)=c.variant&1;at<bool>(obj(27),0x31)=c.variant&2;}
 if((c.scenario>=18&&c.scenario<30)||c.scenario>=70){
  at<void*>(obj(1),0x1c8)=c.scenario==29?NULL:obj(43);at<void*>(obj(1),0x58)=obj(47);at<void*>(obj(0),0x16a8)=obj(46);
  at<bool>(obj(22),0xcb0)=c.variant&1;at<bool>(obj(22),0xcb1)=c.variant&2;
  new(obj(48)) std::wstring(c.variant==1?L"":c.variant==2?L"Skill Ω中文":L"TEST_SKILL_NAME_with_long_tail");
  for(unsigned i=0;i<12;++i){at<long long>(obj(1),0x950+8*i)=c.scenario==18?101:404;at<long long>(obj(1),0x9b0+8*i)=(c.scenario==19||c.scenario==71)?102:(c.scenario==20||c.scenario==72)?-999:404;}
  at<bool>(obj(44),0x6d)=true;at<unsigned>(obj(44),0xe0)=1;
  if(c.scenario==22||c.scenario==23||c.scenario==28){at<long long>(obj(11),0x40)=c.scenario==23?-999:101;
   if(c.scenario==28){at<unsigned>(obj(44),0xe0)=c.variant&1;at<bool>(obj(44),0x6b)=c.variant&2;at<bool>(obj(44),0x6d)=c.variant&4;at<int>(obj(44),0x60)=c.variant==7?4:0;}}
  if(c.scenario==24||c.scenario==26||c.scenario==27||c.scenario==29){at<bool>(obj(0),0x1643)=true;at<long long>(obj(0),0x1648)=c.scenario==27?404:101;at<void*>(obj(31),0xb0)=NULL;}
  if(c.scenario==25||c.scenario==26){at<bool>(obj(0),0x1660)=true;at<long long>(obj(0),0x1668)=c.scenario==26?102:101;at<void*>(obj(31),0xb0)=obj(35);}
 }
 if(c.scenario>=30){
  at<void*>(obj(0),0x40)=obj(52);at<void*>(obj(0),0x16a8)=obj(46);
  at<void*>(obj(1),0x58)=obj(47);at<void*>(obj(2),0x58)=obj(53);
  at<void*>(obj(1),0x298)=(c.variant&2)?obj(54):NULL;
  itemTable[0x2f8/8]=(void*)&canEquip;itemTable[0x360/8]=(void*)&drop;
  const unsigned ids[]={41,42,49};for(unsigned i=0;i<3;++i)at<void*>(obj(ids[i]),0)=itemTable;
  if(c.scenario<=39){if(c.scenario&1){opened[6]=true;at<int>(obj(6),0x9c)=17;if(c.variant&2)at<int>(obj(2),0x330)=42;}else at<int>(obj(0),0x1678)=17;}
  if(c.scenario>=38&&c.scenario<=43){at<void*>(obj(0),0xb8)=obj(41);at<unsigned>(obj(0),0xc0)=7;at<void*>(obj(0),0xc8)=obj(c.scenario==41?2:c.scenario==43?3:1);at<unsigned>(obj(0),0xd0)=9;at<int>(obj(0),0xd8)=17;at<void*>(obj(41),0x2c8)=obj(50);at<void*>(obj(0),0x498)=obj(51);at<void*>(obj(50),0xb0)=(c.variant&1)?obj(51):obj(35);}
  if(c.scenario>=40&&c.scenario<=45)at<bool>(obj(0),0x12fb)=c.scenario!=44;
  if(c.scenario==44||c.scenario==45){at<void*>(obj(0),0x80)=obj(41);at<unsigned>(obj(0),0x88)=3;at<void*>(obj(0),0x90)=obj(2);at<unsigned>(obj(0),0x98)=4;at<void*>(obj(0),0xa0)=obj(1);at<unsigned>(obj(0),0xa8)=5;at<long long>(obj(0),0xb0)=123456789LL;}
 }
 if(c.scenario>=46&&c.scenario<=60){
  for(unsigned i=1;i<=3;++i)at<long long>(obj(i),0x10)=100+i;
  at<long long>(obj(16),0x10)=116;
  at<long long>(obj(41),0x10)=200;at<long long>(obj(42),0x10)=201;at<long long>(obj(49),0x10)=202;
  for(unsigned i=36;i<=38;++i)at<void*>(obj(i),0xb0)=(c.variant&4)?obj(39):obj(35);
  unsigned ids[]={4,7,6,8,9,12,13};unsigned offsets[]={0x1020,0x3438,0x1370,0xf0,0x190,0x170,0x1e0};
  unsigned index=c.scenario==46?0:c.scenario==47||c.scenario==59?1:c.scenario>=49&&c.scenario<=53?c.scenario-47:99;
  if(index<7){for(unsigned i=index;i<7;++i)at<void*>(obj(ids[i]),offsets[i])=obj(i==index?41:49);}
  at<void*>(obj(8),0x60)=obj(3);at<void*>(obj(9),0x90)=obj(16);
  if(c.scenario==47||c.scenario==59){at<long long>(obj(41),0x18)=c.scenario==59?999:103;opened[7]=true;}
  if(c.scenario==48){opened[7]=opened[10]=true;at<void*>(obj(7),0x3438)=obj(49);at<void*>(obj(10),0x3408)=obj(41);at<long long>(obj(41),0x18)=116;}
  if(c.scenario==59){std::vector<void*>* pets=new(static_cast<char*>(obj(1))+0x648) std::vector<void*>;if(c.variant&1)pets->push_back(obj(2));}
  if(c.scenario>=54&&c.scenario<=57){at<bool>(obj(0),0x1641)=c.scenario!=55;at<bool>(obj(0),0x1642)=c.scenario==55;at<long long>(obj(0),0x1650)=12345;at<long long>(obj(0),0x1658)=54321;at<void*>(obj(31),0xb0)=c.scenario==55||c.scenario==56?obj(35):NULL;at<void*>(obj(55),0x10)=c.scenario==57?NULL:obj(41);}
  if(c.scenario==58){at<void*>(obj(4),0x1020)=obj(49);at<void*>(obj(0),0xb8)=obj(41);at<void*>(obj(0),0xc8)=obj(1);at<void*>(obj(41),0x2c8)=obj(50);}
  if(c.scenario==60)at<void*>(obj(4),0x1020)=obj(41);
 }
 if(c.scenario==64||c.scenario==65||c.scenario==66){
  at<void*>(obj(0),0xb8)=obj(41);at<unsigned>(obj(0),0xc0)=7;at<void*>(obj(0),0xc8)=c.scenario==66?NULL:obj(1);at<unsigned>(obj(0),0xd0)=9;at<int>(obj(0),0xd8)=17;at<void*>(obj(41),0x2c8)=obj(50);at<void*>(obj(0),0x498)=obj(51);at<void*>(obj(50),0xb0)=(c.variant&1)?obj(51):obj(35);
  if(c.scenario==64){opened[6]=true;at<int>(obj(6),0x9c)=77;}
 }
 if(c.scenario==67||c.scenario==68||c.scenario==69){opened[6]=opened[7]=opened[10]=true;at<int>(obj(0),0x1678)=78;at<int>(obj(6),0x9c)=79;if(c.scenario!=69)at<int>(obj(7),0x3428)=80;at<int>(obj(7),0x3430)=81;if(c.scenario==67)at<int>(obj(0),0x1674)=82;}
 if(c.scenario==70){at<bool>(obj(0),0x1660)=true;at<long long>(obj(0),0x1668)=101;at<void*>(obj(31),0xb0)=NULL;}
 if(c.scenario>=73&&c.scenario<=76){at<long long>(obj(11),0x40)=101;at<unsigned>(obj(44),0xe0)=c.scenario==73?0:1;at<bool>(obj(44),0x6b)=c.scenario==74;at<bool>(obj(44),0x6d)=c.scenario!=75;at<int>(obj(44),0x60)=c.scenario==76?4:0;}
 // Deliberately different modal flags: original key gating reads cinematic +0x540.
 at<void*>(obj(0),0x548)=obj(28);at<bool>(obj(28),0x30)=!(c.variant&1);at<bool>(obj(28),0x31)=!(c.variant&2);
 std::vector<void*>* menus=new(static_cast<char*>(obj(0))+0x1930) std::vector<void*>;
 std::vector<void*>* dropdowns=new(static_cast<char*>(obj(0))+0x1948) std::vector<void*>;
 if(c.scenario>=61)at<void*>(obj(15),0)=dropdownTable;
 if(c.scenario==17){menus->push_back(obj(4));menus->push_back(obj(6));at<void*>(obj(15),0)=dropdownTable;dropdowns->push_back(obj(15));dropdowns->push_back(obj(15));}
}
void snapshot(){n(900);n(at<bool>(obj(0),0x1998));n(at<bool>(obj(0),0x1999));n(at<bool>(obj(0),0x1670));n(at<bool>(obj(0),0x12fb));for(unsigned i=0;i<3;++i)n(at<int>(obj(0),0x1674+4*i));for(unsigned i=4;i<16;++i)n(opened[i]);for(unsigned i=31;i<=38;++i)ptr(at<void*>(obj(i),0xb0));n(enabledCalls);n(keyCalls);n(dispatchCalls);n(equipCalls);n(pickupCalls);if(input->scenario>=30){ptr(at<void*>(obj(0),0xb8));ptr(at<void*>(obj(0),0xc8));n(at<int>(obj(0),0xd8));for(unsigned o=0x80;o<=0xa0;o+=0x10){ptr(at<void*>(obj(0),o));n(at<unsigned>(obj(0),o+8));}wide(at<long long>(obj(0),0xb0));ptr(at<void*>(obj(50),0xb0));for(unsigned i=24;i<=26;++i)wide(at<long long>(obj(i),0x10));}if(input->scenario>=18)for(unsigned i=0;i<24;++i)wide(at<long long>(obj(1),0x950+8*i));}
void side(const Case& c,bool ours,autotest::Capture& out){
 setup(c,out);detour::Set d;detour::Set skills;detour::Set items;
 TL_REDIRECT(d,captureFn,&capture);TL_REDIRECT(d,updateFn,&update);TL_REDIRECT(d,buttonFn,&button);TL_REDIRECT(d,handleFn,&handle);TL_REDIRECT(d,aliveFn,&alive);TL_REDIRECT(d,cinematicFn,&cinematic);TL_REDIRECT(d,settingsFn,&settings);TL_REDIRECT(d,keyFn,&key);TL_REDIRECT(d,unpauseFn,&unpause);TL_REDIRECT(d,eitherFn,&either);TL_REDIRECT(d,bothFn,&both);TL_REDIRECT(d,modalFn,&modal);TL_REDIRECT(d,closeFn,&close);TL_REDIRECT(d,pauseFn,&pause);TL_REDIRECT(d,clickFn,&click);TL_REDIRECT(d,slotFn,&slot);
 d.redirect(singletonFn,singletonFn,&singleton);d.redirect(positionFn,positionFn,&position);d.redirect(pulseFn,pulseFn,&pulse);d.redirect(removeFn,removeFn,&remove);d.redirect(frontFn,frontFn,&front);
 TL_REDIRECT(skills,skillLookupFn,&skillLookup);TL_REDIRECT(skills,skillLevelFn,&skillLevel);TL_REDIRECT(skills,skillNameFn,&skillName);TL_REDIRECT(skills,activeFn,&active);TL_REDIRECT(skills,leftNameFn,&leftName);TL_REDIRECT(skills,rightMapFn,&rightMap);TL_REDIRECT(skills,leftMapFn,&leftMap);TL_REDIRECT(skills,foldoutFn,&foldout);TL_REDIRECT(skills,skillTooltipFn,&skillTooltip);TL_REDIRECT(skills,soundFn,&sound);skills.redirect(moveFn,moveFn,&move);
 TL_REDIRECT(items,unitIsFn,&unitIs);TL_REDIRECT(items,equipFn,&equip);TL_REDIRECT(items,comparisonFn,&comparison);TL_REDIRECT(items,removeItemFn,&removeItem);TL_REDIRECT(items,pickupFn,&pickup);TL_REDIRECT(items,useFn,&use);TL_REDIRECT(items,behindFn,&behind);TL_REDIRECT(items,dropSoundFn,&dropSound);TL_REDIRECT(items,queueFn,&queue);TL_REDIRECT(items,actorPositionFn,&actorPosition);TL_REDIRECT(items,addItemFn,&addItem);TL_REDIRECT(items,returnDraggedFn,&returnDragged);TL_REDIRECT(items,cursorFn,&cursor);TL_REDIRECT(items,hardwareFn,&hardware);TL_REDIRECT(items,scaledFn,&scaled);TL_REDIRECT(items,removeSafeFn,&removeSafe);TL_REDIRECT(items,addSafeFn,&addSafe);items.redirect(windowPositionFn,windowPositionFn,&windowPosition);
 TL_REDIRECT(items,equipmentTooltipFn,&equipmentTooltip);TL_REDIRECT(items,equipmentGuidFn,&equipmentGuid);
 if(d.failed()||skills.failed()||items.failed())_exit(60);
 const unsigned elapsedBits[]={0,0x80000000U,0x3e000000U,0x3f800000U,0xbf800000U,0x7f800000U,0xff800000U,0x7fc12345U};
 float elapsed;std::memcpy(&elapsed,&elapsedBits[c.variant],4);
 for(unsigned frame=0;frame<2;++frame){
  n(901);n(frame);enabledCalls=keyCalls=0;
  if(!frame){
   if(ours)autotest::invoke(out,&newInput,reinterpret_cast<CGameUI*>(obj(0)),obj(40),elapsed,true);
   else autotest::invoke(out,&oldInput,reinterpret_cast<CGameUI*>(obj(0)),obj(40),elapsed,true);
  }else{bool result=ours?newInput(reinterpret_cast<CGameUI*>(obj(0)),obj(40),0.0f,true):oldInput(reinterpret_cast<CGameUI*>(obj(0)),obj(40),0.0f,true);n(result);}
  snapshot();
 }
}
// An expected exception is recorded separately, never relabelled a normal
// completed invocation. GCC 4.4's COW wstring _Rep refcount is eight bytes
// before data; the fixture/global source string keeps that data alive.
void exceptionSide(void* p,bool ours,autotest::Capture& out){
 borrowedName=NULL;bool caught=false;
 try{side(*static_cast<Case*>(p),ours,out);}catch(int value){caught=value==711;n(902);n(value);}catch(...){n(903);}
 if(!caught||!borrowedName)_exit(67);
 int refs;std::memcpy(&refs,reinterpret_cast<const char*>(borrowedName)-8,4);n(904);n(refs);n(at<bool>(obj(0),0x1998));
}
void exceptionA(void* p,autotest::Capture& out){exceptionSide(p,false,out);}
void exceptionB(void* p,autotest::Capture& out){exceptionSide(p,true,out);}
void a(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void b(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(ingame_input_control_differential){
 autotest::Coverage coverage("ingame_input_control_differential",reinterpret_cast<uintptr_t>(&oldInput));unsigned count=0;
 for(unsigned scenario=0;scenario<77;++scenario)for(unsigned variant=0;variant<8;++variant){if(scenario==71||scenario==72)continue;Case c={scenario,variant};autotest::Outcome left,right;autotest::runChild(a,&c,left);autotest::runChild(b,&c,right);++count;int difference=coverage.observe(host,left,right);
 if(difference||left.childStatus||right.childStatus||!left.reportValid||!right.reportValid||!left.capture.callCompleted||!right.capture.callCompleted){coverage.report(host);host->log("    control scenario=%u variant=%u exits=%d/%d lengths=%lu/%lu\n",scenario,variant,left.childStatus,right.childStatus,(unsigned long)left.capture.length,(unsigned long)right.capture.length);size_t off=0;while(off<left.capture.length&&off<right.capture.length&&left.capture.data[off]==right.capture.data[off])++off;host->log("    first byte %lu\n",(unsigned long)off);for(size_t i=off/4>6?off/4-6:0;i<off/4+20;++i){unsigned l=0,r=0;if(i*4+4<=left.capture.length)std::memcpy(&l,left.capture.data+i*4,4);if(i*4+4<=right.capture.length)std::memcpy(&r,right.capture.data+i*4,4);host->log("    word %lu: %u/%u\n",(unsigned long)i,l,r);}return 1;}}
 coverage.report(host);host->log("    processIngameInput control: %u two-frame cases (partial coverage only)\n",count);return 0;
}

TL_TEST(ingame_input_exception_cleanup){
 unsigned count=0;
 for(unsigned scenario=71;scenario<=72;++scenario)for(unsigned variant=0;variant<8;++variant){
  if(variant==5)continue;Case c={scenario,variant};autotest::Outcome left,right;
  autotest::runChild(exceptionA,&c,left);autotest::runChild(exceptionB,&c,right);++count;
  bool completedException=left.childStatus==0&&right.childStatus==0&&left.reportValid&&right.reportValid&&left.capture.issue==autotest::Capture::Complete&&right.capture.issue==autotest::Capture::Complete&&left.capture.callStarted==1&&right.capture.callStarted==1&&left.capture.callCompleted==0&&right.capture.callCompleted==0&&left.capture.callTarget==reinterpret_cast<uintptr_t>(&oldInput)&&host->comparison_pair(left.capture.callTarget,right.capture.callTarget);
  if(!completedException||left.capture.length!=right.capture.length||std::memcmp(left.capture.data,right.capture.data,left.capture.length)){
   host->log("    exception scenario=%u variant=%u exits=%d/%d lengths=%lu/%lu\n",scenario,variant,left.childStatus,right.childStatus,(unsigned long)left.capture.length,(unsigned long)right.capture.length);return 1;
  }
 }
 host->log("    processIngameInput: %u expected-exception cleanup comparisons; not normal-call coverage\n",count);return 0;
}
