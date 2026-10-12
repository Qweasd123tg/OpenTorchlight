// Differential closure of the twelve residual CGameUI adapters.
// Deliberately no CGameUI/CEGUI/client constructor or destructor on raw owners.
#include <climits>
#include <cstring>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "Detour.h"
#define ENTRY(R,N,A,S) TL_ORIGINAL(R,old##N,A,S) extern "C" R new##N A __asm__(S);
ENTRY(void*,Singleton,(),"_ZN7CGameUI12getSingletonEv")
ENTRY(void,Level,(void*,void*),"_ZN7CGameUI8setLevelEP6CLevel")
ENTRY(bool,Cinematic,(void*),"_ZN7CGameUI18getUIIsInCinematicEv")
ENTRY(bool,Tooltip,(void*),"_ZN7CGameUI23equipmentTooltipVisibleEv")
ENTRY(void,Listener,(void*,int,void*),"_ZN7CGameUI15addMenuListenerE10EMENU_TYPEP13iMenuListener")
ENTRY(void*,NPC,(void*),"_ZN7CGameUI17getQuestDialogNPCEv")
ENTRY(const Ogre::Vector3&,Camera,(void*),"_ZN7CGameUI26getQuestDialogCameraOffsetEv")
ENTRY(void,Hide,(void*),"_ZN7CGameUI6hideUIEv")
ENTRY(void,Show,(void*),"_ZN7CGameUI6showUIEv")
ENTRY(void,Active,(void*,bool),"_ZN7CGameUI15setWindowActiveEb")
ENTRY(bool,Load,(void*),"_ZN7CGameUI7canLoadEv")
ENTRY(bool,Continue,(void*),"_ZN7CGameUI11canContinueEv")
#undef ENTRY
TL_FUNCTION(cameraFn,"_ZN16CQuestDialogMenu15getCameraOffsetEv")
TL_FUNCTION(keyFn,"_ZN11CKeyManager8flushAllEv")
TL_FUNCTION(mouseFn,"_ZN13CMouseManager8flushAllEv")
TL_FUNCTION(activeFn,"_ZN12CMenuManager15setWindowActiveEb")
TL_FUNCTION(loadFn,"_ZN12CMenuManager7canLoadEv")
TL_FUNCTION(continueFn,"_ZN12CMenuManager11canContinueEv")
extern "C" char rendererFn[] __asm__("_ZN5CEGUI17OgreCEGUIRenderer21setTargetSceneManagerEPN4Ogre12SceneManagerE");
namespace {
enum Target { Singleton,Level,Cinematic,Tooltip,Listener,NPC,Camera,Hide,Show,Active,Load,Continue };
const unsigned addresses[]={0xa828e0,0xa82f20,0xa83580,0xa83650,0xa83740,0xa837e0,0xa83800,0xa84c00,0xa84c10,0xa84ca0,0xa84d20,0xa84d30};
const char* names[]={"gameui_adapter_singleton","gameui_adapter_level","gameui_adapter_cinematic","gameui_adapter_tooltip","gameui_adapter_listener","gameui_adapter_npc","gameui_adapter_camera","gameui_adapter_hide","gameui_adapter_show","gameui_adapter_active","gameui_adapter_load","gameui_adapter_continue"};
struct Case { Target target; unsigned bits,mutation; int value,users; Case(Target t):target(t),bits(0),mutation(0),value(0),users(0){} };
struct Block { unsigned char* p; unsigned size; } blocks[32];
unsigned blockCount,callbackCount,semanticErrors; void *ui,*inventory,*pet,*quest,*cinema,*window,*tooltip,*renderer,*scene,*manager[3],*safe[2],*cell[2],*client[2],*player[2],*token;
void* playerTable[10];void* menuTable[6];
Ogre::Vector3* vectorResult; autotest::Capture* cap; const Case* c;
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void number(unsigned n){cap->add(&n,sizeof(n));}
void pointer(const void* p){cap->add(&p,sizeof(p));} // Explicit identity: arena, fixed ELF constant, or known callback table only.
void infrastructureFailure(){cap->issue=autotest::Capture::InvalidReport;}
void semanticFailure(){++semanticErrors;}
bool oracleGood(const autotest::Capture& o){unsigned footer[2];if(o.length<sizeof(footer))return false;std::memcpy(footer,o.data+o.length-sizeof(footer),sizeof(footer));return footer[0]==0xadac105eu&&footer[1]==0;}
void* raw(unsigned n){unsigned char* p=(unsigned char*)autotest::allocate(n+32);if(!p||blockCount==32)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,n);std::memset(p+16+n,0x6c,16);blocks[blockCount].p=p;blocks[blockCount++].size=n;return p+16;}
void event(unsigned n,void* self){number(n);pointer(self);++callbackCount;}
bool playerReady(void* self){if(self!=player[0])semanticFailure();event(1,self);switch(c->mutation){case 1:at<void*>(ui,0x1308)=safe[1];break;case 2:at<void*>(cell[0],0)=client[1];break;case 3:at<void*>(client[0],0x58)=player[1];break;case 4:at<int>(ui,0x178c)=1;break;case 5:at<int>(ui,0x178c)=-1;break;}return (c->bits&128)==0;}
bool wrongPlayer(void* self){event(0xf001,self);semanticFailure();return false;}
void wrongMenu(void* self,void* arg){event(0xf002,self);pointer(arg);semanticFailure();}
void listen(void* self,void* p){event(2,self);pointer(p);at<void*>(self,0x80)=p;}
const Ogre::Vector3& camera(void* self){event(3,self);return *vectorResult;}
void render(void* self,void* target){event(4,self);pointer(target);}
void keys(void* self){event(5,self);at<unsigned>(self,8)=0x13572468;if(c->mutation==1)at<void*>(ui,0x588)=manager[1];if(c->mutation==2)at<void*>(ui,0x588)=0;}
void mouse(void* self){event(6,self);pointer(at<void*>(ui,0x588));at<unsigned>(self,8)=0xabcdef01;if(c->mutation==3)at<void*>(ui,0x588)=manager[2];if(c->mutation==4)at<void*>(ui,0x588)=0;if(c->mutation==5)at<void*>(ui,0x588)=manager[1];}
void active(void* self,bool value){event(7,self);number(value);}
bool load(void* self){event(8,self);return c->bits&1;}
bool cont(void* self){event(9,self);return c->bits&1;}
void initialize(){autotest::g_arenaUsed=0;blockCount=callbackCount=semanticErrors=0;
 ui=raw(0x1a08);inventory=raw(0x1030);pet=raw(0x1380);quest=raw(0x180);cinema=raw(0x180);window=raw(0x400);tooltip=raw(0x98);renderer=raw(0x40);scene=raw(0x40);token=raw(0x40);
 for(unsigned i=0;i<3;++i)manager[i]=raw(0x80);
 for(unsigned i=0;i<2;++i){safe[i]=raw(0x38);cell[i]=raw(8);client[i]=raw(0x3910);player[i]=raw(0x760);at<void*>(safe[i],0x28)=cell[i];at<unsigned>(safe[i],0x30)=1;at<void*>(cell[i],0)=client[i];at<void*>(client[i],0x58)=player[i];at<unsigned char>(client[i],0x10bc)=0;at<int>(client[i],0x390c)=0;at<void*>(player[i],0)=playerTable;at<void*>(player[i],0x750)=i?token:0;at<unsigned char>(player[i],0x264)=i?1:0;}
 for(unsigned i=0;i<10;++i)playerTable[i]=(void*)&wrongPlayer;playerTable[9]=(void*)&playerReady;
 for(unsigned i=0;i<6;++i)menuTable[i]=(void*)&wrongMenu;menuTable[5]=(void*)&listen;
 at<void*>(quest,0)=menuTable;at<void*>(cinema,0)=menuTable;
 at<void*>(ui,0x4d8)=inventory;at<void*>(ui,0x4e8)=pet;at<void*>(ui,0x538)=quest;at<void*>(ui,0x540)=cinema;at<void*>(ui,0x4a0)=tooltip;at<void*>(tooltip,0x20)=window;at<void*>(window,0xb0)=0;
 at<void*>(ui,0x428)=renderer;at<void*>(ui,0x18)=scene;at<void*>(ui,0x588)=manager[0];at<void*>(ui,0x1308)=safe[0];at<int>(ui,0x178c)=c->users;
 at<unsigned char>(cinema,0x30)=0;at<unsigned char>(cinema,0x31)=1;at<void*>(quest,0xc0)=token;
 vectorResult=new(autotest::allocate(sizeof(Ogre::Vector3))) Ogre::Vector3(1.25f,-9.5f,300.0f);
 if(c->target==Cinematic){unsigned b=c->bits;if(b&1)at<unsigned>(safe[0],0x30)=0;if(b&2)at<void*>(cell[0],0)=0;if(b&4)at<void*>(client[0],0x58)=0;if(b&8)at<unsigned char>(client[0],0x10bc)=1;at<int>(client[0],0x390c)=b&16?1:c->value;if(b&32)at<unsigned char>(cinema,0x30)=1;if(b&64)at<unsigned char>(cinema,0x31)=0;if(b&256)at<void*>(player[0],0x750)=token;if(b&512)at<unsigned char>(player[0],0x264)=1;if(b&1024)at<void*>(ui,0x540)=0;}
 if(c->target==Tooltip){std::memset(window,c->bits&4?1:0,0x400);if(c->bits&1)at<void*>(ui,0x4a0)=0;at<void*>(window,0xb0)=c->bits&2?token:0;}
 if(c->target==NPC||c->target==Camera){if(c->bits&1)at<void*>(ui,0x538)=0;if(c->bits&2)at<void*>(quest,0xc0)=0;}
 if(c->target==Active||c->target==Load||c->target==Continue)if(c->bits&2)at<void*>(ui,0x588)=0;
 if(c->target==Show&&c->bits&1)at<void*>(ui,0x18)=0;
 if(c->target==Listener&&(c->bits&2)&&(c->value==0||c->value==1))at<void*>(ui,c->value==0?0x540:0x538)=0;
 if(c->target==Listener&&(c->value!=0&&c->value!=1)){at<void*>(ui,0x538)=0;at<void*>(ui,0x540)=0;}
}
void side(void* context,autotest::Capture& out,bool candidate){c=(Case*)context;cap=&out;initialize();detour::Set d;
 TL_REDIRECT(d,cameraFn,&camera);TL_REDIRECT(d,keyFn,&keys);TL_REDIRECT(d,mouseFn,&mouse);TL_REDIRECT(d,activeFn,&active);TL_REDIRECT(d,loadFn,&load);TL_REDIRECT(d,continueFn,&cont);d.redirect(rendererFn,rendererFn,&render);if(d.failed()){infrastructureFailure();return;}
 switch(c->target){
 case Singleton:{void* expected=c->bits&1?ui:0;*reinterpret_cast<void**>(0x14b9c68)=expected;typedef void*(*Fn)();Fn fn=candidate?&newSingleton:&oldSingleton;if(!autotest::beginInvocation(out,fn))return;void* result=fn();out.callCompleted=1;pointer(result);if(result!=expected)semanticFailure();pointer(*reinterpret_cast<void**>(0x14b9c68));break;}
 case Level:autotest::invoke(out,candidate?&newLevel:&oldLevel,ui,c->bits&1?token:(void*)0);break;
 case Cinematic:{
  unsigned b=c->bits;bool expected=c->users>0;unsigned callbacks=0;
  if(!(b&7)) {
   if((b&8)||(b&16)||c->value==1||(!(b&1024)&&((b&32)||(b&64))))expected=true;
   else {callbacks=1;if(b&128)expected=true;
    else {bool path=(c->mutation>=1&&c->mutation<=3)||((b&256)&&(b&512));int users=c->mutation==4?1:c->mutation==5?-1:c->users;expected=path||users>0;}}
  }
  typedef bool(*Fn)(void*);Fn fn=candidate?&newCinematic:&oldCinematic;
  if(!autotest::beginInvocation(out,fn))return;bool result=fn(ui);out.callCompleted=1;number(result);
  if(result!=expected||callbackCount!=callbacks)semanticFailure();break;
 }
 case Tooltip:autotest::invoke(out,candidate?&newTooltip:&oldTooltip,ui);break;
 case Listener:autotest::invoke(out,candidate?&newListener:&oldListener,ui,c->value,c->bits&1?(c->bits&4?scene:token):(void*)0);break;
 case NPC:{typedef void*(*Fn)(void*);Fn fn=candidate?&newNPC:&oldNPC;if(!autotest::beginInvocation(out,fn))return;void* result=fn(ui);out.callCompleted=1;pointer(result);if(result!=(c->bits&3?(void*)0:token))semanticFailure();break;}
 case Camera:{typedef const Ogre::Vector3&(*Fn)(void*);Fn fn=candidate?&newCamera:&oldCamera;if(!autotest::beginInvocation(out,fn))return;const Ogre::Vector3& result=fn(ui);out.callCompleted=1;pointer(&result);if(&result!=(c->bits&1?reinterpret_cast<const Ogre::Vector3*>(0x14241ac):vectorResult))semanticFailure();else out.add(&result,sizeof(result));break;}
 case Hide:autotest::invoke(out,candidate?&newHide:&oldHide,ui);break;
 case Show:autotest::invoke(out,candidate?&newShow:&oldShow,ui);break;
 case Active:autotest::invoke(out,candidate?&newActive:&oldActive,ui,c->value!=0);break;
 case Load:autotest::invoke(out,candidate?&newLoad:&oldLoad,ui);break;
 case Continue:autotest::invoke(out,candidate?&newContinue:&oldContinue,ui);break;
 }
 number(callbackCount);for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];for(unsigned j=0;j<16;++j)if(b.p[j]!=0xd3||b.p[16+b.size+j]!=0x6c)semanticFailure();out.add(b.p,b.size+32);}number(0xadac105eu);number(semanticErrors);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
bool pair(const tlhybrid_host* host,autotest::Coverage& cov,Case& c,unsigned& count){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++count;int compared=cov.observe(host,a,b);if(compared||!oracleGood(a.capture)||!oracleGood(b.capture)){host->log(" adapter=%u bits=%x value=%d users=%d mutation=%u\n",unsigned(c.target),c.bits,c.value,c.users,c.mutation);cov.report(host);return false;}return true;}
int run(const tlhybrid_host* host,Target target){autotest::Coverage cov(names[target],addresses[target]);unsigned count=0;
 if(target==Cinematic){const int users[]={INT_MIN,-2,-1,0,1,2,INT_MAX};unsigned masks[64],n=0;masks[n++]=0;for(unsigned a=0;a<7;++a){masks[n++]=1u<<a;for(unsigned b=a+1;b<7;++b)masks[n++]=(1u<<a)|(1u<<b);}for(unsigned b=0;b<8;++b)masks[n++]=(b&1?128:0)|(b&2?256:0)|(b&4?512:0);masks[n++]=1024;masks[n++]=1024|128;masks[n++]=1024|256|512;for(unsigned i=0;i<7;++i)for(unsigned j=0;j<n;++j){Case c(target);c.users=users[i];c.bits=masks[j];if(!pair(host,cov,c,count))return 1;}const int states[]={INT_MIN,-1,2,INT_MAX};for(unsigned s=0;s<4;++s){Case c(target);c.value=states[s];if(!pair(host,cov,c,count))return 1;}for(unsigned m=1;m<=5;++m)for(unsigned b=0;b<8;++b){Case c(target);c.mutation=m;c.bits=(b&1?256:0)|(b&2?512:0)|(b&4?128:0);if(!pair(host,cov,c,count))return 1;}}
 else if(target==Listener){const int values[]={INT_MIN,-2,-1,0,1,2,3,INT_MAX};for(unsigned i=0;i<8;++i)for(unsigned b=0;b<2;++b){Case c(target);c.value=values[i];c.bits=b;if(!pair(host,cov,c,count))return 1;}const unsigned extra[]={2,3,5,7};for(int menu=0;menu<2;++menu)for(unsigned i=0;i<4;++i){Case c(target);c.value=menu;c.bits=extra[i];if(!pair(host,cov,c,count))return 1;}}
 else if(target==Active){for(unsigned b=0;b<4;++b)for(unsigned m=0;m<6;++m){Case c(target);c.bits=b&2;c.value=b&1;c.mutation=m;if(!pair(host,cov,c,count))return 1;}}
 else {unsigned total=target==Tooltip?8:target==NPC||target==Camera||target==Load||target==Continue?4:2;for(unsigned b=0;b<total;++b){Case c(target);c.bits=b;if(!pair(host,cov,c,count))return 1;}}
 cov.report(host);return cov.completed!=count||!count||cov.different||cov.missing;
}
}
TL_TEST(gameui_adapter_singleton){return run(host,Singleton);}
TL_TEST(gameui_adapter_level){return run(host,Level);}
TL_TEST(gameui_adapter_cinematic){return run(host,Cinematic);}
TL_TEST(gameui_adapter_tooltip){return run(host,Tooltip);}
TL_TEST(gameui_adapter_listener){return run(host,Listener);}
TL_TEST(gameui_adapter_npc){return run(host,NPC);}
TL_TEST(gameui_adapter_camera){return run(host,Camera);}
TL_TEST(gameui_adapter_hide){return run(host,Hide);}
TL_TEST(gameui_adapter_show){return run(host,Show);}
TL_TEST(gameui_adapter_active){return run(host,Active);}
TL_TEST(gameui_adapter_load){return run(host,Load);}
TL_TEST(gameui_adapter_continue){return run(host,Continue);}
