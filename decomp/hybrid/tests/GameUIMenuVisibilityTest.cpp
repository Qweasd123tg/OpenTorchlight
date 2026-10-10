#include <climits>
#include <cstring>
#include "GameUI.h"
#include "Settings.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(bool,oldCovered,(CGameUI*),"_ZN7CGameUI18bothCoveredPartialEv")
extern "C" bool newCovered(CGameUI*) __asm__("_ZN7CGameUI18bothCoveredPartialEv");
#define ONE(N,S) TL_ORIGINAL(void,old##N,(CGameUI*),S) extern "C" void new##N(CGameUI*) __asm__(S);
#define FLAG(N,S) TL_ORIGINAL(void,old##N,(CGameUI*,bool),S) extern "C" void new##N(CGameUI*,bool) __asm__(S);
FLAG(Interactive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
FLAG(Ingame,"_ZN7CGameUI18setIngameUIVisibleEb")
ONE(Pause,"_ZN7CGameUI11togglePauseEv")
ONE(Console,"_ZN7CGameUI13toggleConsoleEv")
ONE(Inventory,"_ZN7CGameUI15toggleInventoryEv")
#undef ONE
#undef FLAG
TL_FUNCTION(automapFn,"_ZN6CLevel17setAutomapVisibleEb")
TL_FUNCTION(closeAllFn,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(unpauseFn,"_ZN7CGameUI7unPauseEv")
TL_FUNCTION(modalFn,"_ZN7CGameUI15modalDialogOpenEv")
TL_FUNCTION(closeRightFn,"_ZN7CGameUI10closeRightEv")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(getIntFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(consoleGetFn,"_ZN8CConsole10getVisibleEv")
TL_FUNCTION(consoleSetFn,"_ZN8CConsole10setVisibleEb")
extern "C" char childFn[] __asm__("_ZNK5CEGUI6Window7isChildEPKS0_");
extern "C" char addFn[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char topFn[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");

namespace {
enum Target { Covered, Interactive, Ingame, Pause, Console, Inventory };
enum Call { Side=1, Partial, Open, SetOpen, InteractiveVisible, Automap,
 IsChild, Add, Remove, Front, Top, Visible, CloseAll, Unpause, Modal,
 CloseRight, Master, GetInt, ConsoleGet, ConsoleSet };
enum Mutation { NoMutation, SwapMenus, SwapWindows, RewriteStates,
 SwapList, EmptyList, GrowList, SwapLevel, SwapConsole, RewriteKey,
 SwapFoldout, SwapTooltips, ClearConsole, AliasMenus };
struct Case {
 Target target; unsigned bits, pattern, length, alias, mutationAt, mutation, mutationNth, fault, faultNth, repeat, partialSequence;
 int counter, setting; bool visible;
 Case(Target t):target(t),bits(31),pattern(0),length(4),alias(0),mutationAt(0),mutation(0),mutationNth(1),fault(0),faultNth(1),repeat(1),partialSequence(0),counter(0),setting(1),visible(true){}
};
struct Failure { unsigned call; explicit Failure(unsigned x):call(x){} };
struct Block { unsigned char* base; unsigned size; };
struct Pointer { void* base; unsigned off; };
Block blocks[72]; Pointer pointers[256]; unsigned blockCount,pointerCount,calls[32],step,events;
void* ui;void* menus[2][6];void* tips[2][3];void* windows[2][5];void* foldouts[2];void* levels[2];void* consoles[2];void* masters[2];void* settings[2];void* interactive[2];void* item;
void** lists[2];void* menuTables[2][16];void* interactiveTable[16];
const unsigned menuOffsets[]={0x4d8,0x4f0,0x4f8,0x500,0x508,0x4e8};
const unsigned hoverOffsets[]={0x1020,0x3438,0xf0,0x190,0x3408,0x1370};
const unsigned menuSizes[]={0x1040,0x3460,0x120,0x1c0,0x3430,0x1390};
const unsigned windowOffsets[]={0x470,0x488,0x498,0x130,0x138};
const Case* c;autotest::Capture* cap;bool mutated,ours;
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void n(unsigned x){cap->add(&x,sizeof(x));}void i(int x){cap->add(&x,sizeof(x));}
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void* object(unsigned size){if(blockCount==72||size>0x4000)_exit(70);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,size);std::memset(p+16+size,0x6c,16);blocks[blockCount].base=p;blocks[blockCount++].size=size;return p+16;}
void pf(void* p,unsigned o,void* value){if(pointerCount==256)_exit(72);at<void*>(p,o)=value;pointers[pointerCount].base=p;pointers[pointerCount++].off=o;}
uintptr_t token(const void* p){if(!p)return 0;for(unsigned j=0;j<blockCount;++j){uintptr_t a=(uintptr_t)p,b=(uintptr_t)(blocks[j].base+16);if(a>=b&&a-b<=blocks[j].size)return 0x10000+(uintptr_t(j)<<16)+a-b;}if(p==menuTables[0])return 10;if(p==menuTables[1])return 11;if(p==interactiveTable)return 12;cap->issue=autotest::Capture::UnsupportedPointer;return 0;}
void ptr(const void* p){uintptr_t x=token(p);cap->add(&x,sizeof(x));}
void state(){i(at<int>(ui,0x178c));n(at<bool>(ui,0x1999));ptr(at<void*>(ui,0x40));ptr(at<void*>(ui,0x1690));for(unsigned k=0;k<5;++k)ptr(at<void*>(ui,windowOffsets[k]));for(unsigned k=0;k<6;++k){ptr(at<void*>(ui,menuOffsets[k]));for(unsigned j=0;j<2;++j){n(at<bool>(menus[j][k],0x38));n(at<bool>(menus[j][k],0x39));ptr(at<void*>(menus[j][k],hoverOffsets[k]));}}ptr(at<void*>(ui,0x1930));ptr(at<void*>(ui,0x1938));}
void begin(unsigned call,const void* self){if(call>=32||calls[call]==UINT_MAX||++events>512)_exit(73);++calls[call];n(call);n(calls[call]);n(step);ptr(self);state();}
void boundary(unsigned call){
 if(!mutated&&c->mutationAt==call&&calls[call]==c->mutationNth){mutated=true;
  switch(c->mutation){
  case SwapMenus:for(unsigned k=0;k<6;++k)at<void*>(ui,menuOffsets[k])=menus[1][k];at<void*>(ui,0x570)=interactive[1];break;
  case SwapWindows:for(unsigned k=0;k<5;++k)at<void*>(ui,windowOffsets[k])=windows[1][k];break;
  case RewriteStates:at<int>(ui,0x178c)=-7;at<bool>(ui,0x1999)=!at<bool>(ui,0x1999);for(unsigned j=0;j<2;++j)for(unsigned k=0;k<6;++k){at<bool>(menus[j][k],0x38)=!at<bool>(menus[j][k],0x38);at<bool>(menus[j][k],0x39)=!at<bool>(menus[j][k],0x39);}break;
  case SwapList:at<void*>(ui,0x1930)=lists[1];at<void*>(ui,0x1938)=lists[1]+c->length;at<void*>(ui,0x1940)=lists[1]+8;break;
  case EmptyList:at<void*>(ui,0x1938)=at<void*>(ui,0x1930);break;
  case GrowList:at<void*>(ui,0x1938)=static_cast<void**>(at<void*>(ui,0x1930))+8;break;
  case SwapLevel:at<void*>(ui,0x40)=levels[1];break;
  case SwapConsole:at<void*>(ui,0x1690)=consoles[1];at<void*>(masters[0],0x90)=settings[1];break;
  case RewriteKey:KSETTINGS_ALLOW_CONSOLE=0x89abcdefU;break;
  case SwapFoldout:at<void*>(ui,0x4c0)=foldouts[1];break;
  case SwapTooltips:for(unsigned k=0;k<3;++k)at<void*>(ui,0x4a0+k*8)=tips[1][k];break;
  case ClearConsole:at<void*>(ui,0x1690)=0;break;
  case AliasMenus:for(unsigned k=0;k<6;++k)at<void*>(ui,menuOffsets[k])=menus[1][1];break;
  }
 }
 if(c->fault==call&&calls[call]==c->faultNth)throw Failure(call);
}
bool side(void* self){begin(Side,self);bool r=at<bool>(self,0x3a);n(r);boundary(Side);return r;}
bool partial(void* self){begin(Partial,self);bool r=at<bool>(self,0x39);if(c->partialSequence==1)r=(calls[Partial]%3)!=1;if(c->partialSequence==2)r=(calls[Partial]%2)!=0;n(r);boundary(Partial);return r;}
bool open(void* self){begin(Open,self);bool r=at<bool>(self,0x38);n(r);boundary(Open);return r;}
void setOpenCommon(void* self,bool value,unsigned table){begin(SetOpen,self);n(value);n(table);at<bool>(self,0x38)=value;at<bool>(self,0x39)=value;boundary(SetOpen);}
void setOpen0(void* self,bool value){setOpenCommon(self,value,0);}void setOpen1(void* self,bool value){setOpenCommon(self,value,1);}
void interactiveVisible(void* self,bool value){begin(InteractiveVisible,self);n(value);at<bool>(self,0x38)=value;boundary(InteractiveVisible);}
void automap(void* self,bool value){begin(Automap,self);n(value);at<bool>(self,0x20)=value;boundary(Automap);}
bool isChild(void* self,const void* child){begin(IsChild,self);ptr(child);bool r=at<void*>(const_cast<void*>(child),0xb0)==self;n(r);boundary(IsChild);return r;}
void add(void* self,void* child){begin(Add,self);ptr(child);at<void*>(child,0xb0)=self;boundary(Add);}
void remove(void* self,void* child){begin(Remove,self);ptr(child);at<void*>(child,0xb0)=0;boundary(Remove);}
void front(void* self){begin(Front,self);at<unsigned>(self,0x200)=calls[Front];boundary(Front);}
void top(void* self,bool value){begin(Top,self);n(value);at<bool>(self,0x204)=value;boundary(Top);}
void visible(void* self,bool value){begin(Visible,self);n(value);at<bool>(self,0x205)=value;boundary(Visible);}
void closeAll(void* self){begin(CloseAll,self);at<unsigned>(self,0x1900)=0x12563478;boundary(CloseAll);}
void unpause(void* self){begin(Unpause,self);at<bool>(self,0x1999)=false;boundary(Unpause);}
bool modal(void* self){begin(Modal,self);bool r=(c->bits&64)!=0;n(r);boundary(Modal);return r;}
void closeRight(void* self){begin(CloseRight,self);at<unsigned>(self,0x1900)=0x87654321;boundary(CloseRight);}
void* master(){begin(Master,masters[0]);boundary(Master);return masters[0];}
int getInt(void* self,unsigned key){begin(GetInt,self);n(key);i(c->setting);boundary(GetInt);return c->setting;}
bool consoleGet(void* self){begin(ConsoleGet,self);bool r=at<bool>(self,0x20);n(r);boundary(ConsoleGet);return r;}
void consoleSet(void* self,bool value){begin(ConsoleSet,self);n(value);if(self)at<bool>(self,0x20)=value;boundary(ConsoleSet);}
void redirect(detour::Set& d){
 TL_REDIRECT(d,automapFn,&automap);TL_REDIRECT(d,closeAllFn,&closeAll);TL_REDIRECT(d,unpauseFn,&unpause);TL_REDIRECT(d,modalFn,&modal);TL_REDIRECT(d,closeRightFn,&closeRight);TL_REDIRECT(d,masterFn,&master);TL_REDIRECT(d,getIntFn,&getInt);TL_REDIRECT(d,consoleGetFn,&consoleGet);TL_REDIRECT(d,consoleSetFn,&consoleSet);
 d.redirect(childFn,childFn,&isChild);d.redirect(addFn,addFn,&add);d.redirect(removeFn,removeFn,&remove);d.redirect(frontFn,frontFn,&front);d.redirect(topFn,topFn,&top);d.redirect(visibleFn,visibleFn,&visible);
 // setIngameUIVisible is deliberately not detoured: original togglePause calls
 // the original body and recovered togglePause calls the selected replacement.
}
void initialize(){
 autotest::g_arenaUsed=0;blockCount=pointerCount=events=0;mutated=false;std::memset(calls,0,sizeof(calls));std::memset(menuTables,0,sizeof(menuTables));std::memset(interactiveTable,0,sizeof(interactiveTable));
 for(unsigned j=0;j<2;++j){menuTables[j][3]=(void*)&side;menuTables[j][4]=(void*)&open;menuTables[j][5]=(void*)&partial;menuTables[j][8]=j?(void*)&setOpen1:(void*)&setOpen0;}interactiveTable[3]=(void*)&interactiveVisible;
 ui=object(sizeof(CGameUI));item=object(0x40);
 for(unsigned j=0;j<2;++j){for(unsigned k=0;k<6;++k)menus[j][k]=object(menuSizes[k]);for(unsigned k=0;k<3;++k)tips[j][k]=object(0x40);for(unsigned k=0;k<5;++k)windows[j][k]=object(0x220);foldouts[j]=object(0x360);levels[j]=object(0x40);consoles[j]=object(0x40);masters[j]=object(0xb0);settings[j]=object(0x40);interactive[j]=object(0x60);lists[j]=static_cast<void**>(object(8*sizeof(void*)));}
 for(unsigned j=0;j<2;++j){
  for(unsigned k=0;k<6;++k){pf(menus[j][k],0,menuTables[j]);pf(menus[j][k],hoverOffsets[k],item);at<bool>(menus[j][k],0x38)=((c->pattern>>(k%4))&1)^j;at<bool>(menus[j][k],0x39)=((c->pattern>>((k+1)%4))&1)^j;at<bool>(menus[j][k],0x3a)=((k+j)&1)!=0;}
  for(unsigned k=0;k<3;++k)at<long long>(tips[j][k],0x10)=j?(-9223372036854775807LL-1LL)+k:9223372036854775807LL-k;
  for(unsigned k=0;k<5;++k){pf(windows[j][k],0xb0,((c->bits>>(k==4?1:k+1))&1)?windows[j][0]:0);at<unsigned>(windows[j][k],0x200)=0;at<bool>(windows[j][k],0x204)=false;at<bool>(windows[j][k],0x205)=false;}
  pf(foldouts[j],0x348,windows[j][4]);pf(masters[j],0x90,settings[j]);pf(interactive[j],0,interactiveTable);at<bool>(interactive[j],0x38)=((c->bits&2)!=0)^j;at<bool>(levels[j],0x20)=((c->bits&4)!=0)^j;at<bool>(consoles[j],0x20)=((c->bits&8)!=0)^j;
  for(unsigned k=0;k<8;++k)pf(lists[j],k*8,menus[j][((c->alias&1)?k/2:k)%6]);
 }
 for(unsigned k=0;k<6;++k)pf(ui,menuOffsets[k],c->alias&2?menus[0][1]:menus[0][k]);for(unsigned k=0;k<3;++k)pf(ui,0x4a0+k*8,c->alias&4?tips[0][0]:tips[0][k]);for(unsigned k=0;k<5;++k)pf(ui,windowOffsets[k],c->alias&8?windows[0][0]:windows[0][k]);
 pf(ui,0x4c0,foldouts[0]);pf(ui,0x570,interactive[0]);pf(ui,0x40,c->bits&1?levels[0]:0);pf(ui,0x1690,c->bits&32?0:consoles[0]);pf(ui,0x1930,lists[0]);pf(ui,0x1938,lists[0]+c->length);pf(ui,0x1940,lists[0]+8);at<int>(ui,0x178c)=c->counter;at<bool>(ui,0x1999)=(c->bits&16)!=0;at<unsigned>(ui,0x1900)=0xabcdef12;KSETTINGS_ALLOW_CONSOLE=0x12345678U;
}
void snapshot(){n(blockCount);unsigned char buffer[0x4000];for(unsigned j=0;j<blockCount;++j){Block& b=blocks[j];for(unsigned k=0;k<16;++k)if(b.base[k]!=0xd3||b.base[16+b.size+k]!=0x6c)invalid();std::memcpy(buffer,b.base+16,b.size);for(unsigned k=0;k<pointerCount;++k)if(pointers[k].base==b.base+16){uintptr_t t=token(at<void*>(b.base+16,pointers[k].off));std::memcpy(buffer+pointers[k].off,&t,sizeof(t));}n(b.size);cap->add(buffer,b.size);cap->add(b.base,16);cap->add(b.base+16+b.size,16);}for(unsigned j=1;j<=ConsoleSet;++j)n(calls[j]);n(mutated);n(KSETTINGS_ALLOW_CONSOLE);}
void invoke(autotest::Capture& out){CGameUI* p=static_cast<CGameUI*>(ui);switch(c->target){case Covered:autotest::invoke(out,ours?newCovered:oldCovered,p);break;case Interactive:autotest::invoke(out,ours?newInteractive:oldInteractive,p,c->visible);break;case Ingame:autotest::invoke(out,ours?newIngame:oldIngame,p,c->visible);break;case Pause:autotest::invoke(out,ours?newPause:oldPause,p);break;case Console:autotest::invoke(out,ours?newConsole:oldConsole,p);break;case Inventory:autotest::invoke(out,ours?newInventory:oldInventory,p);break;}}
uint64_t original(Target t){switch(t){case Covered:return(uint64_t)(uintptr_t)&oldCovered;case Interactive:return(uint64_t)(uintptr_t)&oldInteractive;case Ingame:return(uint64_t)(uintptr_t)&oldIngame;case Pause:return(uint64_t)(uintptr_t)&oldPause;case Console:return(uint64_t)(uintptr_t)&oldConsole;case Inventory:return(uint64_t)(uintptr_t)&oldInventory;}return 0;}
void run(void* context,autotest::Capture& out,bool candidate){c=static_cast<Case*>(context);cap=&out;ours=candidate;initialize();detour::Set d;redirect(d);if(d.failed()){invalid();return;}autotest::Capture invocation;for(step=0;step<c->repeat;++step){invocation.reset();cap=&invocation;n(step);bool caught=false;try{invoke(invocation);}catch(const Failure& e){caught=true;n(e.call);if(e.call!=c->fault)invalid();}catch(...){invalid();}n(caught);if(caught!=(c->fault!=0))invalid();snapshot();cap=&out;if(!step){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}else{if(invocation.callStarted!=1||invocation.callCompleted!=1)invalid();out.callCompleted=out.callCompleted&&invocation.callCompleted;}if(invocation.issue)out.issue=invocation.issue;out.add(invocation.data,invocation.length);}}
void before(void* p,autotest::Capture& o){run(p,o,false);}void after(void* p,autotest::Capture& o){run(p,o,true);}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case& value,unsigned& count){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);++count;int receipt=cv.observe(host,a,b);if(!receipt&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callCompleted==1&&b.capture.callCompleted==1&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length))return true;size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    visibility #%u target=%u bits=%u pattern=%u len=%u alias=%u counter=%d visible=%u setting=%d mutation=%u/%u/%u fault=%u exits=%d/%d valid=%u/%u issues=%u/%u completed=%u/%u bytes=%lu/%lu first=%lu\n",count,unsigned(value.target),value.bits,value.pattern,value.length,value.alias,value.counter,unsigned(value.visible),value.setting,value.mutationAt,value.mutation,value.mutationNth,value.fault,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);cv.report(host);return false;}
bool exceptionPair(const tlhybrid_host* host,Case& value){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);bool good=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&a.capture.callCompleted==0&&b.capture.callCompleted==0&&a.capture.callTarget==original(value.target)&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(!good)host->log("    visibility exception target=%u call=%u nth=%u exits=%d/%d valid=%u/%u issue=%u/%u complete=%u/%u bytes=%lu/%lu\n",unsigned(value.target),value.fault,value.faultNth,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return good;}
int finish(const tlhybrid_host* host,autotest::Coverage& cv,unsigned count){cv.report(host);return count<20||cv.completed!=count||cv.different||cv.missing;}
} // namespace

TL_TEST(gameui_menu_visibility_covered){autotest::Coverage cv("gameui_menu_visibility_covered",original(Covered));unsigned count=0;
 for(unsigned len=0;len<=8;++len)for(unsigned pattern=0;pattern<16;++pattern){Case v(Covered);v.length=len;v.pattern=pattern;v.alias=pattern%2;if(!pair(host,cv,v,count))return 1;}
 const unsigned mutations[]={SwapMenus,SwapList,EmptyList,GrowList,RewriteStates};for(unsigned call=Side;call<=Partial;++call)for(unsigned m=0;m<5;++m)for(unsigned nth=1;nth<=8;++nth){Case v(Covered);v.length=4;v.pattern=15;v.mutationAt=call;v.mutation=mutations[m];v.mutationNth=nth;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<12;++j){Case v(Covered);v.length=8;v.pattern=j;v.partialSequence=j%3;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned call=Side;call<=Partial;++call){Case v(Covered);v.fault=call;v.pattern=15;if(!exceptionPair(host,v))return 1;}host->log("    visibility covered exceptions: 2 matched, excluded\n");return 0;}
TL_TEST(gameui_menu_visibility_interactive){autotest::Coverage cv("gameui_menu_visibility_interactive",original(Interactive));unsigned count=0;const int counts[]={INT_MIN,INT_MIN+1,-3,-2,-1,0,1,2,3,INT_MAX-1,INT_MAX};
 for(unsigned k=0;k<11;++k)for(unsigned bits=0;bits<4;++bits)for(unsigned visible=0;visible<2;++visible){Case v(Interactive);v.counter=counts[k];v.bits=bits;v.visible=visible;if(!pair(host,cv,v,count))return 1;}
 for(unsigned call=InteractiveVisible;call<=Automap;++call)for(unsigned m=1;m<=13;++m)for(unsigned show=0;show<2;++show){Case v(Interactive);v.counter=show?0:1;v.visible=show;v.bits=show?1:3;v.mutationAt=call;v.mutation=m;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<8;++j){Case v(Interactive);v.bits=j;v.counter=j%3;v.visible=j&1;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned call=InteractiveVisible;call<=Automap;++call){Case v(Interactive);v.bits=1;v.fault=call;if(!exceptionPair(host,v))return 1;}host->log("    visibility interactive exceptions: 2 matched, excluded\n");return 0;}
TL_TEST(gameui_menu_visibility_ingame){autotest::Coverage cv("gameui_menu_visibility_ingame",original(Ingame));unsigned count=0;
 for(unsigned bits=0;bits<32;++bits)for(unsigned visible=0;visible<2;++visible){Case v(Ingame);v.bits=bits;v.visible=visible;v.pattern=bits%16;if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={IsChild,Add,Remove,Front,Top};const unsigned changes[]={SwapMenus,SwapWindows,RewriteStates,SwapTooltips,AliasMenus};for(unsigned j=0;j<5;++j)for(unsigned m=0;m<5;++m)for(unsigned nth=1;nth<=2;++nth){Case v(Ingame);v.bits=j==2?31:0;v.visible=j!=2;v.mutationAt=boundaries[j];v.mutation=changes[m];v.mutationNth=nth;if(!pair(host,cv,v,count))return 1;}
 for(unsigned alias=0;alias<16;++alias){Case v(Ingame);v.bits=alias;v.alias=alias;v.visible=alias&1;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned j=0;j<5;++j){Case v(Ingame);v.bits=j==2?31:0;v.visible=j!=2;v.fault=boundaries[j];if(!exceptionPair(host,v))return 1;}host->log("    visibility ingame exceptions: 5 matched, excluded\n");return 0;}
TL_TEST(gameui_menu_visibility_pause){autotest::Coverage cv("gameui_menu_visibility_pause",original(Pause));unsigned count=0;
 for(unsigned bits=0;bits<64;++bits){Case v(Pause);v.bits=bits;v.pattern=bits%16;if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={CloseAll,Automap,IsChild,Add,Remove,Front,Top,Visible};const unsigned changes[]={SwapMenus,SwapWindows,RewriteStates,SwapLevel,SwapTooltips,AliasMenus};for(unsigned j=0;j<8;++j)for(unsigned m=0;m<6;++m)for(unsigned pause=0;pause<2;++pause){Case v(Pause);v.bits=pause?31:1;v.mutationAt=boundaries[j];v.mutation=changes[m];if(!pair(host,cv,v,count))return 1;}
 for(unsigned alias=0;alias<16;++alias){Case v(Pause);v.bits=alias;v.alias=alias;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned j=0;j<8;++j){Case v(Pause);v.bits=(j==3||j==5||j==6)?17:15;v.fault=boundaries[j];if(!exceptionPair(host,v))return 1;}host->log("    visibility pause exceptions: 8 matched, excluded; real selected ingame body composed on both sides\n");return 0;}
TL_TEST(gameui_menu_visibility_console){autotest::Coverage cv("gameui_menu_visibility_console",original(Console));unsigned count=0;const int values[]={INT_MIN,-1,0,1,2,INT_MAX};
 for(unsigned bits=0;bits<64;++bits)for(unsigned k=0;k<6;++k){Case v(Console);v.bits=bits;v.setting=values[k];if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={Remove,Master,GetInt,ConsoleGet,ConsoleSet};const unsigned changes[]={SwapWindows,SwapConsole,RewriteKey,SwapFoldout,ClearConsole};for(unsigned j=0;j<5;++j)for(unsigned m=0;m<5;++m){Case v(Console);v.bits=31;v.mutationAt=boundaries[j];v.mutation=changes[m];if(changes[m]==ClearConsole&&boundaries[j]!=Remove&&boundaries[j]!=ConsoleGet&&boundaries[j]!=ConsoleSet)continue;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<8;++j){Case v(Console);v.bits=j|16;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned j=0;j<5;++j){Case v(Console);v.bits=31;v.fault=boundaries[j];if(!exceptionPair(host,v))return 1;}host->log("    visibility console exceptions: 5 matched, excluded\n");return 0;}
TL_TEST(gameui_menu_visibility_inventory){autotest::Coverage cv("gameui_menu_visibility_inventory",original(Inventory));unsigned count=0;
 for(unsigned pattern=0;pattern<16;++pattern)for(unsigned bits=0;bits<8;++bits){Case v(Inventory);v.pattern=pattern;v.bits=(bits&1?64:0)|(bits&2?16:0)|(bits&4?32:0);if(!pair(host,cv,v,count))return 1;}
 const unsigned boundaries[]={Unpause,Remove,Partial,Open,SetOpen,Modal,CloseRight,Front};const unsigned changes[]={SwapMenus,SwapWindows,RewriteStates,SwapFoldout,SwapTooltips,AliasMenus};for(unsigned j=0;j<8;++j)for(unsigned m=0;m<6;++m)for(unsigned nth=1;nth<=3;++nth){Case v(Inventory);v.pattern=j==5||j==6?0:15;v.bits=31;v.mutationAt=boundaries[j];v.mutation=changes[m];v.mutationNth=nth;if(!pair(host,cv,v,count))return 1;}
 for(unsigned j=0;j<16;++j){Case v(Inventory);v.pattern=j;v.partialSequence=j%3;v.alias=j%4;v.repeat=2;if(!pair(host,cv,v,count))return 1;}
 if(finish(host,cv,count))return 1;for(unsigned j=0;j<8;++j){Case v(Inventory);v.pattern=j==5||j==6?0:15;v.bits=31;v.fault=boundaries[j];if(!exceptionPair(host,v))return 1;}host->log("    visibility inventory exceptions: 8 matched, excluded\n");return 0;}
