#include <climits>
#include <cstring>
#include <new>
#include <string>
#include <CEGUI.h>
#include "GameUI.h"
#include "Character.h"
#include "Skill.h"
#include "SkillFoldout.h"
#include "AutoTest.h"
#include "Detour.h"

#define CALLBACK(N,S) TL_ORIGINAL(bool, old##N, (CGameUI*,const CEGUI::EventArgs*), S) \
 extern "C" bool new##N(CGameUI*,const CEGUI::EventArgs*) __asm__(S);
CALLBACK(Hover,"_ZN7CGameUI27handle_SkillSelectMouseOverERKN5CEGUI9EventArgsE")
CALLBACK(Select,"_ZN7CGameUI23handle_SkillSelectClickERKN5CEGUI9EventArgsE")
CALLBACK(Click,"_ZN7CGameUI17handle_SkillClickERKN5CEGUI9EventArgsE")
#undef CALLBACK
TL_FUNCTION(unitFn,"_ZN16CResourceManager17getUnitDataByGuidEx")
TL_FUNCTION(guidFn,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(skillFn,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(levelFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(nameFn,"_ZN6CSkill7getNameEv")
TL_FUNCTION(leftFn,"_ZN10CCharacter18setLeftSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(activeFn,"_ZN10CCharacter20setActiveSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(altFn,"_ZN10CCharacter17setAltSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(keyFn,"_ZN11CKeyManager7keyHeldEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(returnFn,"_ZN7CGameUI17returnDraggedItemEv")
TL_FUNCTION(updateFn,"_ZN7CGameUI11updateSlotsEv")
TL_FUNCTION(activateFn,"_ZN7CGameUI16activateItemSlotEib")
TL_FUNCTION(targetFn,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(rightFn,"_ZN11CGameClient10clickRightExbb")
TL_FUNCTION(showFn,"_ZN13CSkillFoldout11showFoldoutEP9CBaseUnitffbb")
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char rectFn[] __asm__("_ZNK5CEGUI6Window12getPixelRectEv");

namespace {
enum Target { Hover, Select, Click };
enum Call { Unit=1, Guid, Skill, Level, Name, Left, Active, Alt, Sound, Key,
            Remove, Isa, Return, Update, Activate, TargetType, Right, Rect, Show };
struct Failure { unsigned call; explicit Failure(unsigned x):call(x){} };
struct Case {
 Target target; unsigned id, flags, mutationAt, mutation, mutationNth, fault, faultNth;
 int slot, mapped, button, level, targetType, foldSlot;
 unsigned guid, name, geometry, owner, followers, targetSequence, repeat;
 bool present, actor, manager, hit, passive, usable, held, parent, dragged, isaItem, isaSpell, itemSlot, skillSlot, handled;
 Case(Target t):target(t),id(999),flags(31),mutationAt(0),mutation(0),mutationNth(1),fault(0),faultNth(1),slot(3),mapped(3),button(0),level(1),targetType(3),foldSlot(19),guid(3),name(2),geometry(0),owner(0),followers(1),targetSequence(0),repeat(1),present(true),actor(true),manager(true),hit(true),passive(false),usable(true),held(false),parent(true),dragged(false),isaItem(true),isaSpell(false),itemSlot(false),skillSlot(true),handled(false) {}
};
struct Block { unsigned char* base; size_t size; };
struct Pointer { void* base; size_t offset; };
Block blocks[48]; Pointer pointers[128]; unsigned blockCount,pointerCount,calls[32],step;
const Case* c; autotest::Capture* cap; bool mutated,ours;
void* ui; void* actors[2]; void* foldouts[2]; void* managers[4]; void* skills[2]; void* items[2]; void* sounds[2]; void* clients[2]; void* data;
void** followers; long long* guids; CEGUI::Window* windows[6];
CEGUI::MouseEventArgs* event; CEGUI::WindowEventArgs* windowEvent; void* vtables[2]; std::wstring names[2];
const unsigned flagOffsets[]={0x1640,0x1641,0x1642,0x1643,0x1660,0x1670};
const long long guidValues[]={0LL,-1LL,-999LL,0x1234567887654321LL,(-9223372036854775807LL-1LL),9223372036854775807LL};
typedef bool (*Handler)(CGameUI*,const CEGUI::EventArgs*);
template<class T>T& at(void* p,size_t o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void n(unsigned x){cap->add(&x,sizeof(x));} void i(int x){cap->add(&x,sizeof(x));} void w(long long x){cap->add(&x,sizeof(x));} void f(float x){cap->add(&x,sizeof(x));}
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void* object(size_t bytes){if(blockCount==48||bytes>0x8000)_exit(70);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(bytes+32));if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,bytes);std::memset(p+16+bytes,0x6c,16);blocks[blockCount].base=p;blocks[blockCount++].size=bytes;return p+16;}
void pf(void* p,size_t off,void* q){if(pointerCount==128)_exit(72);at<void*>(p,off)=q;pointers[pointerCount].base=p;pointers[pointerCount++].offset=off;}
uintptr_t token(const void* p){if(!p)return 0;for(unsigned j=0;j<blockCount;++j){uintptr_t a=(uintptr_t)p,b=(uintptr_t)(blocks[j].base+16);if(a>=b&&a-b<=blocks[j].size)return 0x10000+(uintptr_t(j)<<16)+a-b;}if(p==vtables[0])return 10;if(p==vtables[1])return 11;cap->issue=autotest::Capture::UnsupportedPointer;return 0;}
void ptr(const void* p){uintptr_t x=token(p);cap->add(&x,sizeof(x));}
void str(const std::wstring& s){size_t length=s.size();cap->add(&length,sizeof(length));if(length)cap->add(s.data(),length*sizeof(wchar_t));}
void flags(unsigned value){for(unsigned j=0;j<6;++j)at<bool>(ui,flagOffsets[j])=(value&(1u<<j))!=0;}
void state(){for(unsigned j=0;j<6;++j)n(at<bool>(ui,flagOffsets[j]));w(at<long long>(ui,0x1658));w(at<long long>(ui,0x1668));ptr(at<void*>(ui,0x38));ptr(at<void*>(ui,0x4c0));ptr(at<void*>(ui,0xb8));ptr(at<void*>(ui,0xc8));ptr(at<void*>(ui,0x1308));ptr(at<void*>(ui,0x16a8));ptr(at<void*>(ui,0x1920));ptr(event->window);i(event->button);for(unsigned j=0;j<2;++j){i(at<int>(foldouts[j],0x10));ptr(at<void*>(foldouts[j],0x348));i(at<int>(skills[j],0xe0));n(at<bool>(skills[j],0x6b));n(at<bool>(skills[j],0x6d));w(at<long long>(skills[j],0x150));for(unsigned k=0;k<10;++k){w(at<long long>(actors[j],0x8b0+k*8));w(at<long long>(actors[j],0x900+k*8));}}}
void begin(unsigned call,const void* self){if(call>=32||calls[call]==UINT_MAX)_exit(73);++calls[call];n(call);n(calls[call]);n(step);ptr(self);state();}
void boundary(unsigned call){
 if(!mutated&&c->mutationAt==call&&calls[call]==c->mutationNth){mutated=true;
  switch(c->mutation){
  case 1: at<void*>(ui,0x38)=actors[1];at<void*>(ui,0x4c0)=foldouts[1];at<void*>(ui,0x1308)=managers[3];at<void*>(ui,0x16a8)=sounds[1];at<void*>(ui,0x1920)=clients[1];break;
  case 2: flags(c->flags^63);at<long long>(ui,0x1658)=guidValues[5];at<long long>(ui,0x1668)=guidValues[4];guids[0]=guidValues[4];event->window=windows[1];at<unsigned>(windows[0],0x170)=100;event->button=CEGUI::RightButton;break;
  case 3: at<void*>(ui,0xb8)=items[1];at<void*>(ui,0xc8)=actors[1];at<void*>(ui,0x38)=actors[1];at<void*>(ui,0x4c0)=foldouts[1];break;
  case 4: at<void*>(actors[0],0x1c8)=0;at<void*>(actors[1],0x1c8)=0;at<void*>(ui,0x4c0)=foldouts[1];break;
  case 5: at<void*>(ui,0x38)=0;at<void*>(ui,0x4c0)=foldouts[1];break;
  case 6: at<long long>(actors[0],0x8b0+c->slot*8)=guidValues[4];at<long long>(actors[1],0x8b0+c->slot*8)=guidValues[5];at<void*>(ui,0x38)=actors[1];at<void*>(ui,0x1920)=clients[1];break;
  case 7: at<int>(skills[0],0xe0)=c->level;at<bool>(skills[0],0x6b)=c->passive;at<bool>(skills[0],0x6d)=c->usable;at<long long>(skills[0],0x150)=guidValues[c->guid];break;
  }
 }
 if(c->fault==call&&calls[call]==c->faultNth)throw Failure(call);
}
void* unit(void* self,long long guid){begin(Unit,self);w(guid);boundary(Unit);return c->hit?data:0;}
long long getGuid(void* self,void* group,const std::wstring& key){begin(Guid,self);ptr(group);str(key);boundary(Guid);return guidValues[(c->guid+3)%6];}
void* skill(void* self,long long guid){begin(Skill,self);w(guid);boundary(Skill);return c->hit?skills[0]:0;}
void level(void* self){begin(Level,self);boundary(Level);}
const std::wstring& name(void* self){begin(Name,self);str(names[0]);boundary(Name);return names[0];}
void named(unsigned call,void* self,std::wstring value){begin(call,self);str(value);at<unsigned>(self,0x100)=call;boundary(call);}
void left(void* p,std::wstring s){named(Left,p,s);}void active(void* p,std::wstring s){named(Active,p,s);}void alt(void* p,std::wstring s){named(Alt,p,s);}
void sound(void* self,int sample,void* node,float a,float b,bool flag){begin(Sound,self);i(sample);ptr(node);f(a);f(b);n(flag);at<unsigned>(self,0x10)=sample;boundary(Sound);}
bool key(void* self,unsigned k){begin(Key,self);n(k);boundary(Key);return c->held;}
void remove(CEGUI::Window* self,CEGUI::Window* child){begin(Remove,self);ptr(child);at<void*>(child,0xb0)=0;boundary(Remove);}
bool isa(void* self,int type){begin(Isa,self);i(type);boundary(Isa);return type==1?c->isaItem:c->isaSpell;}
void returned(void* self){begin(Return,self);boundary(Return);at<void*>(ui,0xb8)=0;}
void update(void* self){begin(Update,self);boundary(Update);at<unsigned>(ui,0x1900)=0x12345678;}
void activate(void* self,int slot,bool alt){begin(Activate,self);i(slot);n(alt);boundary(Activate);at<unsigned>(ui,0x1900)=0x87654321;}
int target(void* self){begin(TargetType,self);unsigned nth=calls[TargetType];int value=c->targetType;
 if(c->targetSequence==1){const int seq[]={0,0,9,7};value=seq[(nth-1)%4];}
 if(c->targetSequence==2){const int seq[]={3,0,8};value=seq[(nth-1)%3];}
 if(c->targetSequence==3){const int seq[]={0,0,0,0,0,4,0,0};value=seq[(nth-1)%8];}
 i(value);boundary(TargetType);return value;}
void right(void* self,long long guid,bool untargeted,bool queue){begin(Right,self);w(guid);n(untargeted);n(queue);boundary(Right);at<unsigned>(self,0x10)=0x10203040;}
CEGUI::Rect rect(const CEGUI::Window* self){begin(Rect,self);CEGUI::Rect result;
 static const uint32_t bits[][4]={{0x41280000,0x42140000,0x42910000,0x42bd0000},{0x80000000,0,0x80000001,1},{0x7f7fffff,0xff7fffff,0x00800000,0x80800000},{0x7f800000,0xff800000,0x7fc12345,0x7fc54321},{0x3f000000,0xbe800000,0xc1200000,0x418a0000},{0x00800001,0x007fffff,0x3f800000,0xbf800000}};
 uint32_t value[4];for(unsigned j=0;j<4;++j)value[j]=bits[(c->geometry+calls[Rect]-1)%6][(j+calls[Rect]-1)%4];std::memcpy(&result,value,sizeof(value));cap->add(&result,sizeof(result));f(result.d_top);f(result.d_bottom);f(result.d_left);f(result.d_right);boundary(Rect);return result;}
void show(void* self,void* actor,float x,float y,bool itemsAllowed,bool leftOnly){begin(Show,self);ptr(actor);f(x);f(y);n(itemsAllowed);n(leftOnly);boundary(Show);at<unsigned>(self,0x18)=0x11112222;}
void redirect(detour::Set& d){
 TL_REDIRECT(d,unitFn,&unit);TL_REDIRECT(d,guidFn,&getGuid);TL_REDIRECT(d,skillFn,&skill);TL_REDIRECT(d,levelFn,&level);TL_REDIRECT(d,nameFn,&name);TL_REDIRECT(d,leftFn,&left);TL_REDIRECT(d,activeFn,&active);TL_REDIRECT(d,altFn,&alt);TL_REDIRECT(d,soundFn,&sound);TL_REDIRECT(d,keyFn,&key);TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,returnFn,&returned);TL_REDIRECT(d,updateFn,&update);TL_REDIRECT(d,activateFn,&activate);TL_REDIRECT(d,targetFn,&target);TL_REDIRECT(d,rightFn,&right);TL_REDIRECT(d,showFn,&show);d.redirect(removeFn,removeFn,&remove);d.redirect(rectFn,rectFn,&rect);
}
void initialize(){
 autotest::g_arenaUsed=0;blockCount=pointerCount=0;mutated=false;std::memset(calls,0,sizeof(calls));vtables[0]=vtables[1]=0;
 ui=object(sizeof(CGameUI));
 // Full guarded backing contains every original actor offset and slots 0..102.
 // High integer slot cases take proven no-index paths; no fake domain clamp.
 for(unsigned j=0;j<2;++j){actors[j]=object(0x2000);foldouts[j]=object(sizeof(CSkillFoldout));skills[j]=object(sizeof(CSkill));items[j]=object(0x500);sounds[j]=object(0xd0);clients[j]=object(0x40);}
 for(unsigned j=0;j<4;++j)managers[j]=object(0x80);data=object(0x80);
 for(unsigned j=0;j<6;++j)windows[j]=static_cast<CEGUI::Window*>(object(sizeof(CEGUI::Window)));
 followers=static_cast<void**>(object(8*sizeof(void*)));guids=static_cast<long long*>(object(2*sizeof(long long)));guids[0]=guidValues[c->guid];guids[1]=guidValues[(c->guid+1)%6];
 event=new(object(sizeof(CEGUI::MouseEventArgs)))CEGUI::MouseEventArgs(c->present?windows[0]:0);
 windowEvent=new(object(sizeof(CEGUI::WindowEventArgs)))CEGUI::WindowEventArgs(c->present?windows[0]:0);
 vtables[0]=at<void*>(event,0);vtables[1]=at<void*>(windowEvent,0);pf(event,0,vtables[0]);pf(windowEvent,0,vtables[1]);pf(event,0x10,c->present?windows[0]:0);pf(windowEvent,0x10,c->present?windows[0]:0);
 event->handled=windowEvent->handled=c->handled;event->button=static_cast<CEGUI::MouseButton>(c->button);event->position=CEGUI::Point(-7.25f,8.5f);event->moveDelta=CEGUI::Point(1.5f,-2.25f);event->sysKeys=0xf0e1d2c3;event->wheelChange=-0.5f;event->clickCount=UINT_MAX;
 CEGUI::EventArgs* base=event;CEGUI::EventArgs* baseWindow=windowEvent;
 // Verify SDK polymorphism and the original +0x10/+0x28 offsets; do not forge RTTI.
 if(dynamic_cast<CEGUI::MouseEventArgs*>(base)!=event||dynamic_cast<CEGUI::WindowEventArgs*>(base)!=static_cast<CEGUI::WindowEventArgs*>(event)||dynamic_cast<CEGUI::MouseEventArgs*>(baseWindow)!=0||(char*)&event->window-(char*)event!=0x10||(char*)&event->button-(char*)event!=0x28||sizeof(CEGUI::Rect)!=16)invalid();
 pf(ui,0x38,c->actor?actors[0]:0);pf(ui,0x4c0,foldouts[0]);pf(ui,0xb8,c->dragged?items[0]:0);pf(ui,0xc8,c->owner==0?actors[0]:c->owner==1?actors[1]:c->owner==2?items[1]:0);pf(ui,0x1308,managers[2]);pf(ui,0x16a8,sounds[0]);pf(ui,0x1920,clients[0]);
 for(unsigned j=0;j<10;++j)pf(ui,0x260+j*8,c->mapped==int(j)?windows[0]:windows[1]);
 for(unsigned j=0;j<8;++j)pf(followers,j*8,actors[1]);
 for(unsigned j=0;j<2;++j){pf(actors[j],0x68,managers[j]);pf(actors[j],0x1c8,c->manager?managers[j]:0);pf(actors[j],0x648,followers);pf(actors[j],0x650,followers+c->followers);pf(actors[j],0x658,followers+8);pf(foldouts[j],0x348,windows[2+j]);at<int>(foldouts[j],0x10)=c->target==Select?(j?c->slot==100?101:100:c->slot):c->foldSlot+int(j);at<int>(skills[j],0xe0)=c->level;at<bool>(skills[j],0x6b)=c->passive;at<bool>(skills[j],0x6d)=c->usable;at<long long>(skills[j],0x150)=guidValues[c->guid];at<long long>(items[j],0x1a0)=guidValues[(c->guid+j)%6];
  for(unsigned k=0;k<=102;++k){at<long long>(actors[j],0x8b0+k*8)=guidValues[3];at<long long>(actors[j],0x900+k*8)=guidValues[5];}
  for(unsigned k=0;k<10;++k){at<long long>(actors[j],0x8b0+k*8)=c->skillSlot?guidValues[(c->guid+j)%6]:-1LL;at<long long>(actors[j],0x900+k*8)=c->itemSlot?guidValues[(c->guid+j)%6]:-1LL;}
 }
 if(c->mutationAt==Level&&c->mutation==7){at<int>(skills[0],0xe0)=!c->level;at<bool>(skills[0],0x6b)=!c->passive;at<bool>(skills[0],0x6d)=!c->usable;}
 for(unsigned j=0;j<6;++j){pf(windows[j],0xb0,c->parent?windows[4+(j&1)]:0);pf(windows[j],0x1d8,guids+(j&1));at<unsigned>(windows[j],0x170)=j==0?c->id:102;}
 flags(c->flags);at<long long>(ui,0x1658)=0x1020304050607080LL;at<long long>(ui,0x1668)=0x7060504030201000LL;at<unsigned>(ui,0x1900)=0xfedcba98;
 static const wchar_t* text[]={L"",L"x",L"SKILL_FIREBALL",L"\x041c\x043e\x043b\x043d\x0438\x044f\x4e16\x754c"};names[0]=c->name<4?std::wstring(text[c->name]):std::wstring(4097,L'Z');if(c->name==5)names[0]=std::wstring(L"A\0B\0C",5);names[1]=L"other";
}
void snapshot(){n(blockCount);unsigned char buffer[0x8000];for(unsigned j=0;j<blockCount;++j){Block& b=blocks[j];for(unsigned k=0;k<16;++k)if(b.base[k]!=0xd3||b.base[16+b.size+k]!=0x6c)invalid();std::memcpy(buffer,b.base+16,b.size);for(unsigned k=0;k<pointerCount;++k)if(pointers[k].base==b.base+16){uintptr_t t=token(at<void*>(b.base+16,pointers[k].offset));std::memcpy(buffer+pointers[k].offset,&t,sizeof(t));}n(b.size);cap->add(buffer,b.size);cap->add(b.base,16);cap->add(b.base+16+b.size,16);}for(unsigned j=1;j<=Show;++j)n(calls[j]);n(mutated);str(names[0]);str(names[1]);for(unsigned j=0;j<2;++j){int references;std::memcpy(&references,reinterpret_cast<const char*>(names[j].c_str())-8,sizeof(references));i(references);}}
Handler handler(){if(ours)return c->target==Hover?newHover:c->target==Select?newSelect:newClick;return c->target==Hover?oldHover:c->target==Select?oldSelect:oldClick;}
void side(void* context,autotest::Capture& out,bool candidate){c=static_cast<Case*>(context);cap=&out;ours=candidate;initialize();if(out.issue)return;detour::Set d;redirect(d);if(d.failed()){out.issue=autotest::Capture::UnsupportedPointer;return;}autotest::Capture invocation;
 for(step=0;step<c->repeat;++step){invocation.reset();cap=&invocation;n(step);if(c->fault)cap->addHeapInUse();bool caught=false;const CEGUI::EventArgs* args=(c->target!=Click&&c->handled)?static_cast<CEGUI::EventArgs*>(windowEvent):static_cast<CEGUI::EventArgs*>(event);try{autotest::invoke(invocation,handler(),static_cast<CGameUI*>(ui),args);}catch(const Failure& e){caught=true;n(e.call);if(e.call!=c->fault)invalid();}catch(...){invalid();}n(caught);if(caught!=(c->fault!=0))invalid();if(c->fault)cap->addHeapInUse();snapshot();cap=&out;if(!step){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}else{if(invocation.callStarted!=1||invocation.callCompleted!=1)invalid();out.callCompleted=out.callCompleted&&invocation.callCompleted;}if(invocation.issue)out.issue=invocation.issue;out.add(invocation.data,invocation.length);}
}
void before(void* p,autotest::Capture& o){side(p,o,false);}void after(void* p,autotest::Capture& o){side(p,o,true);}
bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& value,unsigned& count){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);++count;int receipt=coverage.observe(host,a,b);if(!receipt&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callCompleted==1&&b.capture.callCompleted==1&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length))return true;size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    selection #%u target=%u id=%u slot=%d map=%d button=%d level=%d type=%d flags=%u guid=%u mutation=%u/%u/%u fault=%u exits=%d/%d valid=%u/%u issues=%u/%u completed=%u/%u bytes=%lu/%lu first=%lu\n",count,unsigned(value.target),value.id,value.slot,value.mapped,value.button,value.level,value.targetType,value.flags,value.guid,value.mutationAt,value.mutation,value.mutationNth,value.fault,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);coverage.report(host);return false;}
bool exceptionPair(const tlhybrid_host* host,Case& value){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);Handler h=value.target==Hover?oldHover:value.target==Select?oldSelect:oldClick;bool okay=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&a.capture.callCompleted==0&&b.capture.callCompleted==0&&a.capture.callTarget==(uint64_t)(uintptr_t)h&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(!okay)host->log("    selection exception target=%u boundary=%u nth=%u exits=%d/%d valid=%u/%u issue=%u/%u complete=%u/%u\n",unsigned(value.target),value.fault,value.faultNth,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted);return okay;}
int finish(const tlhybrid_host* host,autotest::Coverage& cv,unsigned n){cv.report(host);return n<20||cv.completed!=n||cv.different||cv.missing;}
} // namespace

TL_TEST(gameui_skill_selection_hover){autotest::Coverage cv("gameui_skill_selection_hover",(uint64_t)(uintptr_t)&oldHover);unsigned count=0;
 const unsigned ids[]={0,999,1000,1001,UINT_MAX};
 for(unsigned id=0;id<5;++id)for(unsigned guid=0;guid<6;++guid)for(unsigned bits=0;bits<4;++bits){Case v(Hover);v.id=ids[id];v.guid=guid;v.present=bits!=0;v.hit=bits&1;v.handled=bits&2;v.flags=(id*7+guid*3+bits)%64;if(!pair(host,cv,v,count))return 1;}
 for(unsigned call=Unit;call<=Guid;++call)for(unsigned mutation=1;mutation<=2;++mutation)for(unsigned hit=0;hit<2;++hit){Case v(Hover);v.id=1000;v.mutationAt=call;v.mutation=mutation;v.hit=hit;v.guid=5;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<6;++j){Case v(Hover);v.id=j&1?1000:999;v.guid=j;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned call=Unit;call<=Guid;++call){Case v(Hover);v.id=1000;v.fault=call;if(!exceptionPair(host,v))return 1;}host->log("    selection hover exceptions: 2 matched, excluded from completed receipts\n");return 0;}

TL_TEST(gameui_skill_selection_select){autotest::Coverage cv("gameui_skill_selection_select",(uint64_t)(uintptr_t)&oldSelect);unsigned count=0;
 const int slots[]={0,1,9,100,101,102};const int levels[]={0,1,-1,INT_MIN,INT_MAX};
 for(unsigned slot=0;slot<6;++slot)for(unsigned guid=0;guid<6;++guid)for(unsigned bits=0;bits<4;++bits){Case v(Select);v.slot=slots[slot];v.guid=guid;v.id=bits&1?1000:999;v.parent=bits&2;v.handled=bits&2;v.name=(slot+guid)%6;if(!pair(host,cv,v,count))return 1;}
 for(unsigned lev=0;lev<5;++lev)for(unsigned bits=0;bits<8;++bits){Case v(Select);v.level=levels[lev];v.passive=bits&1;v.usable=bits&2;v.hit=bits&4;v.slot=100+bits%3;v.name=bits%6;if(!pair(host,cv,v,count))return 1;}
 for(unsigned bits=0;bits<16;++bits){Case v(Select);v.present=bits&1;v.actor=bits&2;v.manager=bits&4;v.parent=bits&8;v.slot=INT_MIN;v.level=0;if(!pair(host,cv,v,count))return 1;v.slot=INT_MAX;v.hit=false;if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={Unit,Skill,Level,Name,Left,Active,Alt,Sound,Remove};
 for(unsigned j=0;j<9;++j)for(unsigned mutation=1;mutation<=4;++mutation){Case v(Select);v.slot=j==3||j==4?100:j==5?101:j==6?102:3;v.id=j==0?1000:999;v.mutationAt=boundaries[j];v.mutation=mutation;v.name=4;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<5;++j){Case v(Select);v.slot=100;v.mutationAt=Level;v.mutation=7;v.level=levels[j];v.passive=j&1;v.usable=j&2;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<4;++j){Case v(Select);v.slot=100+j%3;v.guid=j;v.repeat=2;v.name=j+2;if(!pair(host,cv,v,count))return 1;}
 {Case v(Select);v.id=1000;v.mutationAt=Unit;v.mutation=5;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;
 for(unsigned j=0;j<9;++j){Case v(Select);v.slot=j==4?100:j==5?101:j==6?102:100;v.id=j==0?1000:999;v.fault=boundaries[j];v.name=4;if(!exceptionPair(host,v))return 1;}host->log("    selection click exceptions: 9 matched, excluded from completed receipts\n");return 0;}

TL_TEST(gameui_skill_selection_click){autotest::Coverage cv("gameui_skill_selection_click",(uint64_t)(uintptr_t)&oldClick);unsigned count=0;
 const int buttons[]={0,1,2,-1,INT_MIN,INT_MAX};
 for(unsigned mapping=0;mapping<13;++mapping)for(unsigned button=0;button<6;++button)for(unsigned held=0;held<2;++held){Case v(Click);v.mapped=mapping<10?int(mapping):-1;v.slot=mapping<10?int(mapping):int(mapping+90);v.id=mapping<10?UINT_MAX:mapping+90;v.button=buttons[button];v.held=held;v.geometry=(mapping+button)%6;v.parent=button&1;v.flags=(mapping*3+button)%64;if(!pair(host,cv,v,count))return 1;}
 const int types[]={INT_MIN,-1,0,1,3,4,7,8,9,10,11,INT_MAX};
 for(unsigned type=0;type<12;++type)for(unsigned bits=0;bits<8;++bits){Case v(Click);v.button=1;v.targetType=types[type];v.itemSlot=bits&1;v.skillSlot=bits&2;v.hit=bits&4;v.guid=3;if(!pair(host,cv,v,count))return 1;}
 for(unsigned owner=0;owner<4;++owner)for(unsigned bits=0;bits<8;++bits)for(unsigned guid=0;guid<6;++guid){Case v(Click);v.dragged=true;v.owner=owner;v.isaItem=bits&1;v.isaSpell=bits&2;v.followers=bits&4?8:0;v.guid=guid;if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={Key,Remove,Isa,Return,Update,Activate,Skill,TargetType,Right,Rect,Show};
 for(unsigned j=0;j<11;++j)for(unsigned mutation=1;mutation<=3;++mutation){Case v(Click);v.mutationAt=boundaries[j];v.mutation=mutation;v.dragged=j==2||j==3;v.held=j==4;v.button=j>=5&&j<=8?1:0;v.itemSlot=j==5;v.guid=3;v.parent=true;if(!pair(host,cv,v,count))return 1;}
 for(unsigned nth=1;nth<=3;++nth)for(unsigned geom=0;geom<6;++geom){Case v(Click);v.mutationAt=Rect;v.mutation=1;v.mutationNth=nth;v.geometry=geom;if(!pair(host,cv,v,count))return 1;v.mutation=2;if(!pair(host,cv,v,count))return 1;}
 for(unsigned sequence=1;sequence<=3;++sequence)for(unsigned nth=1;nth<=8;++nth){Case v(Click);v.button=1;v.guid=3;v.targetSequence=sequence;v.mutationAt=TargetType;v.mutation=6;v.mutationNth=nth;if(!pair(host,cv,v,count))return 1;}
 const unsigned ids[]={0,99,103,0x7fffffffU,0x80000000U,UINT_MAX};
 for(unsigned j=0;j<6;++j)for(unsigned parent=0;parent<2;++parent){Case v(Click);v.id=ids[j];v.mapped=-1;v.slot=int(ids[j]);v.parent=parent;v.geometry=j;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<6;++j){Case v(Click);v.repeat=2;v.guid=j;v.geometry=j;v.button=j&1;if(!pair(host,cv,v,count))return 1;}
 // Same-selection close, including absent actor on that no-dereference branch.
 for(unsigned slot=0;slot<10;++slot)for(unsigned parent=0;parent<2;++parent){Case v(Click);v.slot=slot;v.mapped=slot;v.foldSlot=slot;v.parent=parent;v.actor=!parent;if(!pair(host,cv,v,count))return 1;}
 // Special buttons reject dragged-item binding even for valid consumables.
 for(unsigned slot=100;slot<=102;++slot)for(unsigned owner=0;owner<4;++owner){Case v(Click);v.id=slot;v.slot=slot;v.mapped=-1;v.dragged=true;v.owner=owner;if(!pair(host,cv,v,count))return 1;}
 // The second ISA callback still uses the cached object; binding rereads the drag.
 for(unsigned nth=1;nth<=2;++nth)for(unsigned mutation=1;mutation<=3;++mutation){Case v(Click);v.dragged=true;v.mutationAt=Isa;v.mutationNth=nth;v.mutation=mutation;if(!pair(host,cv,v,count))return 1;}
 {Case v(Click);v.dragged=true;v.actor=false;v.owner=3;if(!pair(host,cv,v,count))return 1;}
 for(unsigned id=100;id<=102;++id)for(unsigned mapped=0;mapped<10;++mapped){Case v(Click);v.id=id;v.mapped=mapped;v.slot=id;v.button=1;v.itemSlot=true;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;
 for(unsigned j=0;j<11;++j){Case v(Click);v.fault=boundaries[j];v.dragged=j==2||j==3;v.held=j==4;v.button=j>=5&&j<=8?1:0;v.itemSlot=j==5;v.guid=3;if(!exceptionPair(host,v))return 1;}host->log("    skill click exceptions: 11 matched, excluded from completed receipts\n");return 0;}
