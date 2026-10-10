// Headless original/recovered witnesses. Bool returns intentionally retain
// unrelated high RAX bits; short and uint32 boundaries are poisoned likewise.
#include <climits>
#include <cstring>
#include <CEGUI.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"
#define TARGET(R,N,A,S) TL_ORIGINAL(R, original##N, A, S) \
 extern "C" R candidate##N A __asm__(S);
TARGET(bool, Menu, (CGameUI*,void*,float,bool), "_ZN7CGameUI16processMenuInputEPvfb")
TARGET(void, Mouse, (CGameUI*,unsigned,unsigned), "_ZN7CGameUI10mouseEventEjj")
TARGET(void, Key, (CGameUI*,unsigned,unsigned,long), "_ZN7CGameUI8keyEventEjjl")
TARGET(void, MenuUI, (CGameUI*,float,CGameClient*,Ogre::RenderWindow*), "_ZN7CGameUI12updateMenuUIEfP11CGameClientPN4Ogre12RenderWindowE")
TARGET(bool, Input, (CGameUI*,CGameClient*,void*,float,bool), "_ZN7CGameUI12processInputEP11CGameClientPvfb")
TARGET(void, Update, (CGameUI*,float,CGameClient*,Ogre::RenderWindow*), "_ZN7CGameUI6updateEfP11CGameClientPN4Ogre12RenderWindowE")
#undef TARGET
TL_FUNCTION(mouseUpdateFn,"_ZN13CMouseManager6updateEPv")
TL_FUNCTION(mouseEventFn,"_ZN13CMouseManager10mouseEventEjj")
TL_FUNCTION(menuInputFn,"_ZN12CMenuManager12processInputEPvfb")
TL_FUNCTION(keyEventFn,"_ZN11CKeyManager8keyEventEjj")
TL_FUNCTION(consoleKeyFn,"_ZN8CConsole8keyEventEjjl")
TL_FUNCTION(asyncFn,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(scanFn,"_Z24LinuxMapVirtual2Scancodej")
TL_FUNCTION(pressedFn,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(heldFn,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(menuUpdateFn,"_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(processMenuFn,"_ZN7CGameUI16processMenuInputEPvfb")
TL_FUNCTION(processIngameFn,"_ZN7CGameUI18processIngameInputEPvfb")
TL_FUNCTION(updateMenuFn,"_ZN7CGameUI12updateMenuUIEfP11CGameClientPN4Ogre12RenderWindowE")
TL_FUNCTION(updateIngameFn,"_ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE")
#define SDK(N,S) extern "C" char N[] __asm__(S)
SDK(singletonFn,"_ZN5CEGUI6System12getSingletonEv");
SDK(positionFn,"_ZN5CEGUI6System19injectMousePositionEff");
SDK(pulseFn,"_ZN5CEGUI6System15injectTimePulseEf");
SDK(downFn,"_ZN5CEGUI6System21injectMouseButtonDownENS_11MouseButtonE");
SDK(upFn,"_ZN5CEGUI6System19injectMouseButtonUpENS_11MouseButtonE");
SDK(charFn,"_ZN5CEGUI6System10injectCharEj");
SDK(keyDownFn,"_ZN5CEGUI6System13injectKeyDownEj");
SDK(keyUpFn,"_ZN5CEGUI6System11injectKeyUpEj");
SDK(visibleFn,"_ZNK5CEGUI6Window9isVisibleEb");
SDK(tipWidthFn,"_ZNK5CEGUI6Window8getWidthEv");
SDK(tipHeightFn,"_ZNK5CEGUI6Window9getHeightEv");
SDK(setPositionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
SDK(cleanFn,"_ZN5CEGUI13WindowManager13cleanDeadPoolEv");
#undef SDK
extern "C" void* windowSingleton __asm__("_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE");
namespace {
enum Target {Menu,Mouse,Key,MenuUI,Input,Update};
enum Boundary {MouseUpdate=1,Singleton,Position,Pulse,MenuInput,MouseDown,MouseUp,
 MouseForward,KeyForward,ConsoleKey,Async,Scan,Char,KeyDown,KeyUp,DialogUpdate,
 WrongSlot,Pressed,Held,Visible,Width,Height,TipWidth,TipHeight,SetPosition,
 MenuUpdate,ProcessMenu,ProcessIngame,UpdateMenu,UpdateIngame,Clean,Last};
enum Mutation {None,MouseChangesCoordinates,MouseChangesManager,SingletonChangesCoordinates,
 PositionChangesManager,PulseChangesManager,KeyChangesConsole,ConsoleChangesConsole,
 ButtonChangesManager,VisibleChangesTooltip,WidthChangesTooltip,HeightChangesCoordinates,
 TipWidthChangesCoordinates,TipHeightChangesCoordinates,PositionChangesUpdateManager,
 UpdateChangesSingleton,ProcessChangesState,LastMutation};
struct Case {
 Target target; unsigned event,value,scan,elapsed,buttons,mutation,fault,repeat,geometry;
 int state,asyncValue; long text,x,y; bool enabled,result,manager,console,visible,gate30,gate31,real;
 Case(Target t):target(t),event(0),value(0),scan(0x87654321u),elapsed(0x3e000000u),buttons(0),
 mutation(0),fault(0),repeat(1),geometry(0),state(0),asyncValue(0),text(0x12345678abcdef01L),
 x(300),y(200),enabled(true),result(false),manager(true),console(true),visible(true),gate30(false),gate31(true),real(false){}
};
struct Failure {unsigned boundary; explicit Failure(unsigned b):boundary(b){}};
struct Block {unsigned char* p;unsigned size;};
struct Pointer {void* p;unsigned offset;};
Block blocks[40];Pointer pointers[60];unsigned blockCount,pointerCount,calls[Last],step,changed;
const Case* cs;autotest::Capture* cap;void* ui;void* clients[2];void* systems[2];void* managers[2];
void* consoles[2];void* dialogs[2];void* windows[2];void* deadPools[2];void* handle;void* render;
void** table;CEGUI::UDim dimensions[2];CEGUI::UVector2 positions[2];bool ours;
void dialogUpdate(void*,float);void wrongSlot(void*,float);
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(unsigned v){cap->add(&v,4);}void wide(long v){cap->add(&v,sizeof(v));}void scalar(float f){cap->add(&f,4);}
float floatBits(unsigned bits){float value;std::memcpy(&value,&bits,4);return value;}
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void* object(unsigned size){if(blockCount==40||size>0x4000)_exit(70);unsigned char* p=(unsigned char*)autotest::allocate(size+32);if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,size);std::memset(p+16+size,0x6c,16);blocks[blockCount].p=p;blocks[blockCount++].size=size;return p+16;}
void pfield(void* p,unsigned offset,void* value){if(pointerCount==60)_exit(72);at<void*>(p,offset)=value;pointers[pointerCount].p=p;pointers[pointerCount++].offset=offset;}
uintptr_t token(const void* p){if(!p)return 0;for(unsigned i=0;i<blockCount;++i){uintptr_t start=(uintptr_t)(blocks[i].p+16),v=(uintptr_t)p;if(v>=start&&v-start<blocks[i].size)return 0x10000u+(uintptr_t(i)<<16)+v-start;}if(p==(void*)&dialogUpdate)return 100;if(p==(void*)&wrongSlot)return 101;cap->issue=autotest::Capture::UnsupportedPointer;return 0;}
void ptr(const void* p){uintptr_t t=token(p);cap->add(&t,sizeof(t));}
void trace(unsigned b,const void* p){n(b);n(step);++calls[b];ptr(p);n(at<bool>(ui,0x1670));n(at<unsigned>(clients[0],0x38d0));wide(at<long>(ui,0x12d0));wide(at<long>(ui,0x12d8));ptr(at<void*>(ui,0x588));ptr(at<void*>(ui,0x1690));ptr(at<void*>(ui,0x430));ptr(at<void*>(systems[0],0x238));ptr(windowSingleton);}
void effect(unsigned b){
 if(!changed){unsigned m=cs->mutation;
  if(m==MouseChangesCoordinates&&b==MouseUpdate){at<long>(ui,0x12d0)=16777217L;at<long>(ui,0x12d8)=-16777219L;changed=1;}
  if(m==MouseChangesManager&&b==MouseUpdate){at<void*>(ui,0x588)=cs->manager?0:managers[1];changed=1;}
  if(m==SingletonChangesCoordinates&&b==Singleton){at<long>(ui,0x12d0)=-4567;at<long>(ui,0x12d8)=8910;changed=1;}
  if((m==PositionChangesManager&&b==Position)||(m==PulseChangesManager&&b==Pulse)){at<void*>(ui,0x588)=cs->manager?0:managers[1];changed=1;}
  if(m==KeyChangesConsole&&b==KeyForward){at<void*>(ui,0x1690)=cs->console?0:consoles[1];changed=1;}
  if(m==ConsoleChangesConsole&&b==ConsoleKey){at<void*>(ui,0x1690)=consoles[1];changed=1;}
  if(m==ButtonChangesManager&&(b==Pressed||b==Held)){at<void*>(ui,0x588)=managers[1];changed=1;}
  if((m==VisibleChangesTooltip&&b==Visible)||(m==WidthChangesTooltip&&b==Width)){at<void*>(systems[0],0x238)=windows[1];at<void*>(ui,0x430)=systems[1];changed=1;}
  if((m==HeightChangesCoordinates&&b==Height)||(m==TipWidthChangesCoordinates&&b==TipWidth)||(m==TipHeightChangesCoordinates&&b==TipHeight)){at<long>(ui,0x12d0)=777;at<long>(ui,0x12d8)=-555;changed=1;}
  if(m==PositionChangesUpdateManager&&b==SetPosition){at<void*>(ui,0x588)=managers[1];changed=1;}
  if(m==UpdateChangesSingleton&&(b==UpdateMenu||b==UpdateIngame||b==MenuUpdate||b==DialogUpdate)){windowSingleton=deadPools[1];at<bool>(ui,0x1670)=true;changed=1;}
  if(m==ProcessChangesState&&(b==ProcessMenu||b==ProcessIngame)){at<unsigned>(clients[0],0x38d0)=1-at<unsigned>(clients[0],0x38d0);changed=1;}
 }
 if(cs->fault==b)throw Failure(b);
}
unsigned long long boolean(bool b){return 0x91abcdeffedcba00ULL|unsigned(b);}
void mouseUpdate(void* self,void* h){trace(MouseUpdate,self);ptr(h);effect(MouseUpdate);}
void* singleton(){trace(Singleton,systems[calls[Singleton]%2]);effect(Singleton);return systems[(calls[Singleton]-1)%2];}
unsigned long long injectPosition(void* self,float x,float y){trace(Position,self);scalar(x);scalar(y);effect(Position);return boolean(cs->result);}
unsigned long long pulse(void* self,float elapsed){trace(Pulse,self);scalar(elapsed);effect(Pulse);return boolean(cs->result);}
unsigned long long menuInput(void* self,void* h,float elapsed,bool enabled){trace(MenuInput,self);ptr(h);scalar(elapsed);n(enabled);at<unsigned>(self,0x18)^=cs->value+step;effect(MenuInput);return boolean(cs->result^(step&1));}
unsigned long long mouseDown(void* self,unsigned b){trace(MouseDown,self);n(b);effect(MouseDown);return boolean(cs->result);}
unsigned long long mouseUp(void* self,unsigned b){trace(MouseUp,self);n(b);effect(MouseUp);return boolean(cs->result);}
void mouseForward(void* self,unsigned e,unsigned v){trace(MouseForward,self);n(e);n(v);at<unsigned>(self,0x10)^=e;at<unsigned>(self,0x14)^=v;effect(MouseForward);}
void keyForward(void* self,unsigned e,unsigned v){trace(KeyForward,self);n(e);n(v);at<unsigned>(self,0x10)^=e;at<unsigned>(self,0x14)^=v;effect(KeyForward);}
void consoleKey(void* self,unsigned e,unsigned v,long text){trace(ConsoleKey,self);n(e);n(v);wide(text);at<long>(self,0x18)^=text;effect(ConsoleKey);}
unsigned long long async(unsigned key){trace(Async,ui);n(key);effect(Async);return 0x91abcdeffedc0000ULL|static_cast<unsigned short>(cs->asyncValue);}
unsigned long long scan(unsigned key){trace(Scan,ui);n(key);effect(Scan);return 0x91abcdef00000000ULL|cs->scan;}
unsigned long long character(void* self,unsigned c){trace(Char,self);n(c);effect(Char);return boolean(cs->result);}
unsigned long long keyDown(void* self,unsigned c){trace(KeyDown,self);n(c);effect(KeyDown);return boolean(cs->result);}
unsigned long long keyUp(void* self,unsigned c){trace(KeyUp,self);n(c);effect(KeyUp);return boolean(cs->result);}
void dialogUpdate(void* self,float elapsed){trace(DialogUpdate,self);scalar(elapsed);at<unsigned>(self,0x38)^=cs->value;effect(DialogUpdate);}
void wrongSlot(void* self,float elapsed){trace(WrongSlot,self);scalar(elapsed);effect(WrongSlot);}
unsigned long long pressed(void* self,unsigned b){trace(Pressed,self);n(b);effect(Pressed);return boolean((cs->buttons&(b?1:2))!=0);}
unsigned long long held(void* self,unsigned b){trace(Held,self);n(b);effect(Held);return boolean((cs->buttons&(b?4:8))!=0);}
unsigned long long visible(void* self,bool local){trace(Visible,self);n(local);effect(Visible);return boolean(cs->visible);}
float width(void* self){trace(Width,self);effect(Width);return cs->geometry==11?floatBits(0x7fc12345):cs->geometry==12?floatBits(0x80000000):1024.0f;}
float height(void* self){trace(Height,self);effect(Height);return floatBits(0x7fc54321);}
// GCC 4.4 SDK UDim is nontrivial and returned through an explicit result slot.
void tipWidth(CEGUI::UDim* result,void* self){trace(TipWidth,self);cap->add(&dimensions[0],sizeof(CEGUI::UDim));effect(TipWidth);std::memcpy(result,&dimensions[0],sizeof(CEGUI::UDim));}
void tipHeight(CEGUI::UDim* result,void* self){trace(TipHeight,self);cap->add(&dimensions[1],sizeof(CEGUI::UDim));effect(TipHeight);std::memcpy(result,&dimensions[1],sizeof(CEGUI::UDim));}
void setPosition(void* self,const CEGUI::UVector2& p){trace(SetPosition,self);cap->add(&p,sizeof(p));unsigned i=self==windows[1];std::memcpy(&positions[i],&p,sizeof(p));effect(SetPosition);}
void menuUpdate(void* self,float elapsed,void* client,void* window){trace(MenuUpdate,self);scalar(elapsed);ptr(client);ptr(window);at<unsigned>(self,0x18)^=cs->value;effect(MenuUpdate);}
unsigned long long processMenu(void* self,void* h,float elapsed,bool enabled){trace(ProcessMenu,self);ptr(h);scalar(elapsed);n(enabled);effect(ProcessMenu);return boolean(cs->result^(step&1));}
unsigned long long processIngame(void* self,void* h,float elapsed,bool enabled){trace(ProcessIngame,self);ptr(h);scalar(elapsed);n(enabled);effect(ProcessIngame);return boolean(cs->result^(step&1));}
void updateMenu(void* self,float elapsed,void* client,void* window){trace(UpdateMenu,self);scalar(elapsed);ptr(client);ptr(window);effect(UpdateMenu);}
void updateIngame(void* self,float elapsed,void* client,void* window){trace(UpdateIngame,self);scalar(elapsed);ptr(client);ptr(window);effect(UpdateIngame);}
void clean(void* self){trace(Clean,self);at<unsigned>(self,0x18)^=0x98765432u;effect(Clean);}
void initialize(){autotest::g_arenaUsed=0;blockCount=pointerCount=step=changed=0;std::memset(calls,0,sizeof(calls));ui=object(sizeof(CGameUI));
 for(unsigned i=0;i<2;++i){clients[i]=object(0x38d8);systems[i]=object(0x300);managers[i]=object(0x40);consoles[i]=object(0x40);dialogs[i]=object(0x60);windows[i]=object(sizeof(CEGUI::Window));deadPools[i]=object(0x40);}
 handle=object(0x20);render=object(0x20);table=(void**)object(8*sizeof(void*));
 for(unsigned i=0;i<8;++i)pfield(table,i*sizeof(void*),(void*)(i==3?&dialogUpdate:&wrongSlot));
 for(unsigned i=0;i<2;++i){pfield(dialogs[i],0,table);at<bool>(dialogs[i],0x30)=cs->gate30;at<bool>(dialogs[i],0x31)=cs->gate31;at<unsigned>(clients[i],0x38d0)=i?0x76543210u:cs->state;pfield(systems[i],0x238,windows[i]);}
 pfield(ui,0x588,cs->manager?managers[0]:0);pfield(ui,0x1690,cs->console?consoles[0]:0);pfield(ui,0x430,systems[0]);pfield(ui,0x518,dialogs[0]);pfield(ui,0x1920,clients[1]);
 at<long>(ui,0x12d0)=cs->x;at<long>(ui,0x12d8)=cs->y;at<bool>(ui,0x1670)=cs->enabled;windowSingleton=deadPools[0];
 static const unsigned scaleBits[]={0,0x80000000u,0x3effffffu,0x3f000000u,0x3f000001u,0xbeffffffu,0xbf000000u,0xbf000001u,0x3fc00000u,0xbfc00000u,0x4b7fffffu,0xcb7fffffu,0x3f800000u};
 dimensions[0]=CEGUI::UDim(floatBits(scaleBits[cs->geometry%13]),cs->geometry==9?floatBits(0x7fc43210):74.0f);
 dimensions[1]=CEGUI::UDim(floatBits(scaleBits[(cs->geometry+3)%13]),cs->geometry==10?floatBits(0x80000000):24.0f);
 std::memset(positions,0x3d,sizeof(positions));
}
void redirect(detour::Set& d){
 TL_REDIRECT(d,mouseUpdateFn,&mouseUpdate);TL_REDIRECT(d,mouseEventFn,&mouseForward);TL_REDIRECT(d,menuInputFn,&menuInput);
 TL_REDIRECT(d,keyEventFn,&keyForward);TL_REDIRECT(d,consoleKeyFn,&consoleKey);TL_REDIRECT(d,asyncFn,&async);TL_REDIRECT(d,scanFn,&scan);
 TL_REDIRECT(d,pressedFn,&pressed);TL_REDIRECT(d,heldFn,&held);TL_REDIRECT(d,menuUpdateFn,&menuUpdate);TL_REDIRECT(d,widthFn,&width);TL_REDIRECT(d,heightFn,&height);
 TL_REDIRECT(d,processIngameFn,&processIngame);TL_REDIRECT(d,updateIngameFn,&updateIngame);
 if(cs->target==Input&&!cs->real)TL_REDIRECT(d,processMenuFn,&processMenu);
 if(cs->target==Update&&!cs->real)TL_REDIRECT(d,updateMenuFn,&updateMenu);
 d.redirect(singletonFn,singletonFn,&singleton);d.redirect(positionFn,positionFn,&injectPosition);d.redirect(pulseFn,pulseFn,&pulse);
 d.redirect(downFn,downFn,&mouseDown);d.redirect(upFn,upFn,&mouseUp);d.redirect(charFn,charFn,&character);
 d.redirect(keyDownFn,keyDownFn,&keyDown);d.redirect(keyUpFn,keyUpFn,&keyUp);d.redirect(visibleFn,visibleFn,&visible);
 d.redirect(tipWidthFn,tipWidthFn,&tipWidth);d.redirect(tipHeightFn,tipHeightFn,&tipHeight);d.redirect(setPositionFn,setPositionFn,&setPosition);d.redirect(cleanFn,cleanFn,&clean);
}
void snapshot(){n(blockCount);unsigned char bytes[0x4000];for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];for(unsigned j=0;j<16;++j)if(b.p[j]!=0xd3||b.p[16+b.size+j]!=0x6c)invalid();std::memcpy(bytes,b.p+16,b.size);for(unsigned j=0;j<pointerCount;++j)if(pointers[j].p==b.p+16){uintptr_t t=token(at<void*>(b.p+16,pointers[j].offset));std::memcpy(bytes+pointers[j].offset,&t,sizeof(t));}n(b.size);cap->add(bytes,b.size);cap->add(b.p,16);cap->add(b.p+16+b.size,16);}cap->add(dimensions,sizeof(dimensions));cap->add(positions,sizeof(positions));ptr(windowSingleton);for(unsigned i=0;i<Last;++i)n(calls[i]);n(changed);}
uint64_t originalAddress(Target t){switch(t){case Menu:return (uint64_t)(uintptr_t)&originalMenu;case Mouse:return (uint64_t)(uintptr_t)&originalMouse;case Key:return (uint64_t)(uintptr_t)&originalKey;case MenuUI:return (uint64_t)(uintptr_t)&originalMenuUI;case Input:return (uint64_t)(uintptr_t)&originalInput;case Update:return (uint64_t)(uintptr_t)&originalUpdate;}return 0;}
void side(void* context,autotest::Capture& out,bool candidate){cs=(Case*)context;ours=candidate;cap=&out;initialize();detour::Set d;redirect(d);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}autotest::Capture invocation;
 for(step=0;step<cs->repeat;++step){invocation.reset();cap=&invocation;n(step);n(cs->target);bool caught=false;
  if(step&&cs->target==Input)at<unsigned>(clients[0],0x38d0)=(cs->state+step)%3;
  if(step&&cs->target==Update)at<unsigned>(clients[0],0x38d0)=(cs->state+step)%3;
  try {CGameUI* p=(CGameUI*)ui;CGameClient* c=(CGameClient*)clients[0];Ogre::RenderWindow* r=(Ogre::RenderWindow*)render;float elapsed=floatBits(cs->elapsed);
   switch(cs->target){
    case Menu:autotest::invoke(invocation,ours?&candidateMenu:&originalMenu,p,handle,elapsed,cs->enabled);break;
    case Mouse:autotest::invoke(invocation,ours?&candidateMouse:&originalMouse,p,cs->event,cs->value);break;
    case Key:autotest::invoke(invocation,ours?&candidateKey:&originalKey,p,cs->event,cs->value,cs->text);break;
    case MenuUI:autotest::invoke(invocation,ours?&candidateMenuUI:&originalMenuUI,p,elapsed,c,r);break;
    case Input:autotest::invoke(invocation,ours?&candidateInput:&originalInput,p,c,handle,elapsed,cs->enabled);break;
    case Update:autotest::invoke(invocation,ours?&candidateUpdate:&originalUpdate,p,elapsed,c,r);break;
   }
  }catch(const Failure& e){caught=true;n(e.boundary);if(e.boundary!=cs->fault)invalid();}catch(...){invalid();}
  n(caught);if(caught!=(cs->fault!=0))invalid();snapshot();cap=&out;
  if(!step){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}
  else {if(invocation.callStarted!=1||invocation.callCompleted!=1)invalid();out.callCompleted=out.callCompleted&&invocation.callCompleted;}
  if(invocation.issue)out.issue=invocation.issue;out.add(invocation.data,invocation.length);
 }
}
void oldSide(void* c,autotest::Capture& out){side(c,out,false);}void newSide(void* c,autotest::Capture& out){side(c,out,true);}
bool equal(const autotest::Outcome& a,const autotest::Outcome& b){return a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
void diagnostic(const tlhybrid_host* host,const Case& c,const autotest::Outcome& a,const autotest::Outcome& b,unsigned count){size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    dispatch #%u target=%u event=%x value=%x state=%d mutation=%u geometry=%u gate=%u/%u buttons=%u visible=%u manager=%u console=%u result=%u repeat=%u real=%u fault=%u exits=%d/%d valid=%u/%u issues=%u/%u complete=%u/%u bytes=%lu/%lu first=%lu\n",count,unsigned(c.target),c.event,c.value,c.state,c.mutation,c.geometry,unsigned(c.gate30),unsigned(c.gate31),c.buttons,unsigned(c.visible),unsigned(c.manager),unsigned(c.console),unsigned(c.result),c.repeat,unsigned(c.real),c.fault,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);}
bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& count){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++count;int receipt=coverage.observe(host,a,b);if(!receipt&&equal(a,b)&&a.capture.callCompleted==1&&b.capture.callCompleted==1)return true;diagnostic(host,c,a,b,count);coverage.report(host);return false;}
bool exceptionPair(const tlhybrid_host* host,Case& c){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);if(equal(a,b)&&a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==originalAddress(c.target)&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget))return true;diagnostic(host,c,a,b,0);return false;}
int finish(const tlhybrid_host* host,autotest::Coverage& coverage,unsigned count,unsigned expected){coverage.report(host);return count!=expected||coverage.completed!=expected||coverage.completed<20||coverage.different||coverage.missing;}
const unsigned times[]={0,0x80000000u,0x3f000001u,0xbf000001u,0x7f800000u,0xff800000u,0x7fc12345u,0x00000001u};
}
TL_TEST(gameui_dispatch_menu_input){autotest::Coverage coverage("gameui_dispatch_menu_input",originalAddress(Menu));unsigned count=0;
 for(unsigned i=0;i<8;++i)for(unsigned bits=0;bits<8;++bits){Case c(Menu);c.elapsed=times[i];c.enabled=bits&1;c.result=bits&2;c.manager=bits&4;c.x=i&1?LONG_MIN:LONG_MAX;c.y=i&2?16777217:-16777217;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned m=MouseChangesCoordinates;m<=PulseChangesManager;++m)for(unsigned present=0;present<2;++present){Case c(Menu);c.mutation=m;c.manager=present;c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,74);}
TL_TEST(gameui_dispatch_mouse_event){autotest::Coverage coverage("gameui_dispatch_mouse_event",originalAddress(Mouse));unsigned count=0;
 const unsigned events[]={0,0x1ff,0x200,0x201,0x202,0x203,0x204,0x205,0x206,0x207,0x208,0x20a,0xffffffffu,0x80000201u};
 for(unsigned i=0;i<14;++i)for(unsigned bits=0;bits<4;++bits){Case c(Mouse);c.event=events[i];c.value=bits==0?0:bits==1?UINT_MAX:bits==2?0x80000000u:0x76543210u;c.result=bits&1;c.repeat=bits==3?3:1;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,56);}
TL_TEST(gameui_dispatch_key_event){autotest::Coverage coverage("gameui_dispatch_key_event",originalAddress(Key));unsigned count=0;
 const unsigned events[]={0,0xff,0x100,0x101,0x102,0x103,0x104,0x105,0x106,UINT_MAX,0x80000100u};
 const unsigned values[]={0,0x7e,0x1007e,UINT_MAX,0x80000001u};
 for(unsigned i=0;i<11;++i)for(unsigned j=0;j<5;++j)for(unsigned present=0;present<2;++present){Case c(Key);c.event=events[i];c.value=values[j];c.console=present;c.text=present?LONG_MIN:LONG_MAX;c.scan=values[(j+2)%5];c.asyncValue=j&1?-32768:32767;c.result=present;if(!pair(host,coverage,c,count))return 1;}
 const int keys[]={0,1,127,128,255,256,32767,-1,-32768};
 for(unsigned i=0;i<9;++i)for(unsigned j=0;j<2;++j){Case c(Key);c.event=0x102;c.value=j?0x7e:0x7f;c.asyncValue=keys[i];if(!pair(host,coverage,c,count))return 1;}
 for(unsigned m=KeyChangesConsole;m<=ConsoleChangesConsole;++m)for(unsigned present=0;present<2;++present){Case c(Key);c.event=0x104;c.value=UINT_MAX;c.mutation=m;c.console=present;c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,132);}
TL_TEST(gameui_dispatch_menu_ui){autotest::Coverage coverage("gameui_dispatch_menu_ui",originalAddress(MenuUI));unsigned count=0;
 for(unsigned gate=0;gate<4;++gate)for(unsigned i=0;i<8;++i){Case c(MenuUI);c.gate30=gate&1;c.gate31=gate&2;c.elapsed=times[i];c.buttons=i;c.value=i*1234567u;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned buttons=0;buttons<16;++buttons)for(unsigned visible=0;visible<2;++visible){Case c(MenuUI);c.buttons=buttons;c.visible=visible;c.result=visible;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned geometry=0;geometry<13;++geometry)for(unsigned loc=0;loc<6;++loc){Case c(MenuUI);c.geometry=geometry;const long xs[]={0,923,924,925,LONG_MIN,LONG_MAX};const long ys[]={-1,49,50,51,LONG_MIN,LONG_MAX};c.x=xs[loc];c.y=ys[loc];c.elapsed=times[loc];if(!pair(host,coverage,c,count))return 1;}
 for(unsigned m=ButtonChangesManager;m<=PositionChangesUpdateManager;++m){Case c(MenuUI);c.mutation=m;c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,149);}
TL_TEST(gameui_dispatch_process_input){autotest::Coverage coverage("gameui_dispatch_process_input",originalAddress(Input));unsigned count=0;const int states[]={0,1,2,-1,INT_MIN,INT_MAX};
 for(unsigned i=0;i<6;++i)for(unsigned j=0;j<8;++j){Case c(Input);c.state=states[i];c.elapsed=times[j];c.enabled=j&1;c.result=j&2;c.mutation=ProcessChangesState;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned j=0;j<8;++j){Case c(Input);c.real=true;c.repeat=3;c.manager=j&1;c.result=j&2;c.elapsed=times[j];c.mutation=PulseChangesManager;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,56);}
TL_TEST(gameui_dispatch_update){autotest::Coverage coverage("gameui_dispatch_update",originalAddress(Update));unsigned count=0;const int states[]={0,1,2,-1,INT_MIN,INT_MAX};
 for(unsigned i=0;i<6;++i)for(unsigned j=0;j<8;++j){Case c(Update);c.state=states[i];c.elapsed=times[j];c.enabled=j&1;c.mutation=UpdateChangesSingleton;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned j=0;j<8;++j){Case c(Update);c.real=true;c.repeat=3;c.elapsed=times[j];c.gate30=j&1;c.gate31=j&2;c.buttons=j/2;c.mutation=UpdateChangesSingleton;if(!pair(host,coverage,c,count))return 1;}
 return finish(host,coverage,count,56);}
TL_TEST(gameui_dispatch_exceptions){
 const unsigned menu[]={MouseUpdate,Singleton,Position,Pulse,MenuInput};for(unsigned i=0;i<5;++i){Case c(Menu);c.fault=menu[i];if(!exceptionPair(host,c))return 1;}
 const unsigned mouse[]={Singleton,MouseDown,MouseForward};for(unsigned i=0;i<3;++i){Case c(Mouse);c.event=0x201;c.fault=mouse[i];if(!exceptionPair(host,c))return 1;}
 const unsigned key[]={KeyForward,ConsoleKey,Async,Singleton,Char,Scan,KeyDown,KeyUp};for(unsigned i=0;i<8;++i){Case c(Key);c.event=i<5?0x102:i==7?0x101:0x100;c.fault=key[i];if(!exceptionPair(host,c))return 1;}
 const unsigned update[]={DialogUpdate,Pressed,Held,Visible,Width,Height,TipWidth,TipHeight,SetPosition,MenuUpdate};for(unsigned i=0;i<10;++i){Case c(MenuUI);c.gate30=i==0;c.fault=update[i];if(!exceptionPair(host,c))return 1;}
 for(unsigned i=0;i<2;++i){Case c(Input);c.state=i;c.fault=i?ProcessIngame:ProcessMenu;if(!exceptionPair(host,c))return 1;}
 for(unsigned i=0;i<3;++i){Case c(Update);c.state=i;c.fault=i==0?UpdateMenu:i==1?UpdateIngame:Clean;if(!exceptionPair(host,c))return 1;}
 host->log("    31 exception witnesses passed, excluded from normal coverage\n");return 0;}
