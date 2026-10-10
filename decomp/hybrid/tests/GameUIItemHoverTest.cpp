// Original-ASM differential fixtures. Every allocated byte (including redzones)
// is snapshotted losslessly; run-length encoding only reduces sentinel runs.
#include <climits>
#include <cstring>
#include "MenuItemClickState.h"
#include "EquipmentRef.h"
#include "SDL.h"
#include "AutoTest.h"
#include "Detour.h"
#define ENTRY(N,P,S) TL_ORIGINAL(void,old##N,P,S) extern "C" void new##N P __asm__(S);
ENTRY(Clear,(CGameUI*),"_ZN7CGameUI19clearMenuMouseOversEv")
ENTRY(Activate,(CGameUI*,int,bool),"_ZN7CGameUI16activateItemSlotEib")
ENTRY(Cursor,(CGameUI*),"_ZN7CGameUI20updateHardwareCursorEv")
ENTRY(DeleteItem,(CGameUI*,CItem*),"_ZN7CGameUI16notifyOfDeletionEP5CItem")
ENTRY(Hover,(CGameUI*,CItem*,bool),"_ZN7CGameUI16setMouseOverItemEP5CItemb")
ENTRY(DeleteActor,(CGameUI*,CCharacter*),"_ZN7CGameUI16notifyOfDeletionEP10CCharacter")
#undef ENTRY
TL_FUNCTION(equipmentFn,"_ZN10CInventory18getEquipmentOfGuidEx")
TL_FUNCTION(addSafeFn,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(removeSafeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(enchantFn,"_ZN12CEnchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(combineFn,"_ZN12CCombineMenu9setPlayerEP10CCharacter")
TL_FUNCTION(stashFn,"_ZN10CStashMenu9setPlayerEP10CCharacter")
extern "C" char showCursorFn[] __asm__("SDL_ShowCursor");
extern "C" char setCursorFn[] __asm__("SDL_SetCursor");
namespace {
enum Target { Clear,Activate,Cursor,DeleteItem,Hover,DeleteActor,Composition };
enum Call { Equipment=1,ShowCursor,SetCursor,RemoveSafe,AddSafe,GetOwner,SetOwner,Enchant,Combine,Stash,LastCall };
struct Failure { unsigned call; explicit Failure(unsigned x):call(x){} };
struct Case {
 Target target;unsigned seed,mask,oldItem,newItem,actor,alias,mutationAt,mutation,mutationNth,fault,faultNth,repeat,registry;
 int slot,refSlot,cursor;long long guid;bool flag,hit,drag;
 Case(Target t):target(t),seed(0),mask(0x7ff),oldItem(1),newItem(2),actor(1),alias(0),mutationAt(0),mutation(0),mutationNth(1),fault(0),faultNth(1),repeat(1),registry(0),slot(3),refSlot(29),cursor(0),guid(0x1234567887654321LL),flag(true),hit(true),drag(false){}
};
struct Block{unsigned char* p;unsigned bytes;};
struct Registry{void* object;void* refs[16];unsigned count;};
Block blocks[80];unsigned blockCount,calls[LastCall],step;Registry regs[8];unsigned regCount;
const Case* c;autotest::Capture* cap;bool mutated,ours;void* activeRef;
CGameUI* ui;void* actors[3];void* items[3];void* menus[2][6];void* tips[3];void* inventories[2];void* equipmentRefs[2];
void** cursorArrays[2];void* cursors[10];void* witnesses[12];void* vtable[13];
const unsigned menuOffsets[]={0x4d8,0x4f0,0x4f8,0x500,0x508,0x4e8};
const unsigned hoverOffsets[]={0x1020,0x3438,0xf0,0x190,0x3408,0x1370};
const unsigned actorOrder[]={1,2,3,5,0,4};
const long long values[]={0LL,-1LL,-999LL,0x1234567887654321LL,(-9223372036854775807LL-1LL),9223372036854775807LL};
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void require(bool b){if(!b)_exit(90);}
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void n(unsigned x){cap->add(&x,4);}void i(int x){cap->add(&x,4);}void w(long long x){cap->add(&x,8);}void ptr(const void* p){cap->addPointer(p);}
void* object(unsigned bytes){if(blockCount>=80)_exit(81);if(bytes>=0x10000)_exit(82);unsigned char* p=(unsigned char*)autotest::allocate(bytes+32);if(!p)_exit(83);std::memset(p,0xd3,16);std::memset(p+16,0xa5,bytes);std::memset(p+16+bytes,0x6c,16);blocks[blockCount].p=p;blocks[blockCount++].bytes=bytes;return p+16;}
Registry& reg(void* p){for(unsigned j=0;j<regCount;++j)if(regs[j].object==p)return regs[j];if(regCount>=8)_exit(84);Registry& r=regs[regCount++];r.object=p;r.count=0;std::memset(r.refs,0,sizeof(r.refs));return r;}
unsigned registerRef(void* p,void* r){Registry& x=reg(p);if(x.count>=16)_exit(85);x.refs[x.count]=r;return x.count++;}
void unregisterRef(void* p,void* r,unsigned index){Registry& x=reg(p);if(index==UINT_MAX)return;if(index>=x.count)_exit(86);if(x.refs[index]!=r)_exit(87);x.refs[index]=x.refs[--x.count];x.refs[x.count]=0;if(index<x.count)at<unsigned>(x.refs[index],8)=index;}
void bind(void* r,void* p){void* old=at<void*>(r,0);if(old==p)return;if(old)unregisterRef(old,r,at<unsigned>(r,8));at<void*>(r,0)=0;if(p)at<unsigned>(r,8)=registerRef(p,r);at<void*>(r,0)=p;}
void* item(unsigned id){require(id<4);return id?items[id-1]:0;}void* actor(unsigned id){require(id<4);return id?actors[id-1]:0;}
void safeInit(void* r,void* p){at<void*>(r,0)=0;at<unsigned>(r,8)=UINT_MAX;bind(r,p);}
void registrySnapshot(){n(regCount);for(unsigned j=0;j<regCount;++j){Registry& r=regs[j];ptr(r.object);n(r.count);for(unsigned k=0;k<16;++k)ptr(r.refs[k]);}}
void state(){ptr(at<void*>(ui,0x38));for(unsigned off=0x48;off<=0x68;off+=16){ptr(at<void*>(ui,off));n(at<unsigned>(ui,off+8));}ptr(at<void*>(ui,0xb8));i(at<int>(ui,0x12fc));i(at<int>(ui,0x1678));i(at<int>(ui,0x167c));ptr(at<void*>(ui,0x19f0));for(unsigned j=0;j<6;++j){void* p=at<void*>(ui,menuOffsets[j]);ptr(p);ptr(at<void*>(p,hoverOffsets[j]));ptr(at<void*>(p,0x30));}for(unsigned j=0;j<3;++j){void* p=at<void*>(ui,0x4a0+j*8);ptr(p);w(at<long long>(p,0x10));}registrySnapshot();}
void begin(unsigned call,void* self){require(call<LastCall&&calls[call]!=UINT_MAX);++calls[call];n(call);n(calls[call]);n(step);ptr(self);state();}
void mutation(unsigned call){if(!mutated&&c->mutationAt==call&&calls[call]==c->mutationNth){mutated=true;
 switch(c->mutation){
 case 1:for(unsigned j=0;j<6;++j)at<void*>(ui,menuOffsets[j])=menus[1][j];for(unsigned j=0;j<3;++j)at<void*>(ui,0x4a0+j*8)=tips[(j+1)%3];break;
 case 2:at<int>(ui,0x12fc)=c->refSlot;at<void*>(ui,0x19f0)=cursorArrays[1];at<void*>(ui,0xb8)=items[2];break;
 case 3:at<void*>(ui,0x38)=actors[1];at<int>(equipmentRefs[0],0x18)=c->refSlot^0x12345678;at<int>(ui,0x1678)=INT_MIN;at<int>(ui,0x167c)=INT_MAX;break;
 case 4:if(activeRef!=(char*)ui+0x48)bind((char*)ui+0x48,actors[2]);if(activeRef!=(char*)ui+0x58)bind((char*)ui+0x58,actors[2]);break;
 case 5:for(unsigned j=0;j<6;++j)at<void*>(at<void*>(ui,menuOffsets[j]),0x30)=actor(c->actor);at<void*>(at<void*>(ui,0x4f8),0x60)=actor(c->actor);at<void*>(at<void*>(ui,0x500),0x90)=actor(c->actor);at<void*>(at<void*>(ui,0x508),0x58)=actor(c->actor);break;
 case 6:for(unsigned j=0;j<6;++j)at<void*>(at<void*>(ui,menuOffsets[j]),0x30)=actors[2];at<void*>(at<void*>(ui,0x4f8),0x60)=actors[2];at<void*>(at<void*>(ui,0x500),0x90)=actors[2];at<void*>(at<void*>(ui,0x508),0x58)=actors[2];break;
 }
 }
 if(c->fault==call&&calls[call]==c->faultNth)throw Failure(call);
}
void* equipment(void* p,long long guid){begin(Equipment,p);w(guid);mutation(Equipment);return c->hit?equipmentRefs[0]:0;}
int showCursor(int enabled){begin(ShowCursor,0);i(enabled);mutation(ShowCursor);return c->refSlot;}
void setCursor(void* p){begin(SetCursor,p);mutation(SetCursor);}
unsigned addSafe(void* p,void* r){begin(AddSafe,p);ptr(r);ptr(at<void*>(r,0));n(at<unsigned>(r,8));mutation(AddSafe);return registerRef(p,r);}
void removeSafe(void* p,void* r,unsigned index){begin(RemoveSafe,p);ptr(r);n(index);ptr(at<void*>(r,0));if(c->fault==RemoveSafe&&calls[RemoveSafe]==c->faultNth)throw Failure(RemoveSafe);unregisterRef(p,r,index);activeRef=r;mutation(RemoveSafe);activeRef=0;}
void* getOwner(void* p){begin(GetOwner,p);void* result=at<void*>(p,0x30);ptr(result);mutation(GetOwner);return result;}
void setOwner(void* p,void* owner){begin(SetOwner,p);ptr(owner);at<void*>(p,0x30)=owner;mutation(SetOwner);}
void player(unsigned call,void* p,void* owner,unsigned offset){begin(call,p);ptr(owner);at<void*>(p,offset)=owner;mutation(call);}
void enchant(void* p,void* v){player(Enchant,p,v,0x60);}void combine(void* p,void* v){player(Combine,p,v,0x90);}void stash(void* p,void* v){player(Stash,p,v,0x58);}
void forbidden(){_exit(91);}
void redirects(detour::Set& d){TL_REDIRECT(d,equipmentFn,&equipment);TL_REDIRECT(d,addSafeFn,&addSafe);TL_REDIRECT(d,removeSafeFn,&removeSafe);TL_REDIRECT(d,enchantFn,&enchant);TL_REDIRECT(d,combineFn,&combine);TL_REDIRECT(d,stashFn,&stash);d.redirect(showCursorFn,showCursorFn,&showCursor);d.redirect(setCursorFn,setCursorFn,&setCursor);}
void initialize(){
 autotest::g_arenaUsed=0;blockCount=regCount=0;mutated=false;activeRef=0;std::memset(calls,0,sizeof(calls));std::memset(regs,0,sizeof(regs));
 ui=(CGameUI*)object(sizeof(CGameUI));for(unsigned j=0;j<3;++j){actors[j]=object(sizeof(CPlayer));items[j]=object(sizeof(CEquipment));tips[j]=object(sizeof(CEquipmentTooltip));at<long long>(tips[j],0x10)=values[(c->seed+j)%6];}
 const unsigned sizes[]={sizeof(CInventoryMenu),sizeof(CMerchantMenu),sizeof(CEnchantMenu),sizeof(CCombineMenu),sizeof(CStashMenu),sizeof(CPetMenu)};
 for(unsigned j=0;j<13;++j)vtable[j]=(void*)&forbidden;vtable[2]=(void*)&getOwner;vtable[7]=(void*)&setOwner;
 for(unsigned k=0;k<2;++k)for(unsigned j=0;j<6;++j){menus[k][j]=object(sizes[j]);at<void**>(menus[k][j],0)=vtable;at<void*>(menus[k][j],hoverOffsets[j])=c->mask&(1u<<j)?items[(j+c->seed)%3]:0;at<void*>(menus[k][j],0x30)=c->mask&(1u<<j)?actor(c->actor):actors[2];}
 for(unsigned k=0;k<2;++k){at<void*>(menus[k][2],0x60)=c->mask&64?actor(c->actor):actors[2];at<void*>(menus[k][3],0x90)=c->mask&128?actor(c->actor):actors[2];at<void*>(menus[k][4],0x58)=c->mask&256?actor(c->actor):actors[2];inventories[k]=object(sizeof(CInventory));equipmentRefs[k]=object(sizeof(CEquipmentRef));at<int>(equipmentRefs[k],0x18)=c->refSlot;cursorArrays[k]=(void**)object(5*sizeof(void*));}
 for(unsigned j=0;j<10;++j){cursors[j]=object(16);cursorArrays[j/5][j%5]=c->alias==3?cursors[0]:cursors[j];}
 for(unsigned j=0;j<3;++j){at<void*>(actors[j],0x490)=inventories[j%2];for(unsigned k=0;k<10;++k)at<long long>(actors[j],0x900+k*8)=values[(k+j+c->seed)%6];}
 at<long long>(actors[0],0x900+c->slot*8)=c->guid;at<void*>(ui,0x38)=actors[0];at<void*>(ui,0xb8)=c->drag?items[0]:0;at<int>(ui,0x12fc)=c->cursor;at<int>(ui,0x1678)=INT_MIN+137;at<int>(ui,0x167c)=INT_MAX-137;
 at<void*>(ui,0x19f0)=cursorArrays[0];at<void*>(ui,0x19f8)=cursorArrays[0]+5;at<void*>(ui,0x1a00)=cursorArrays[0]+5;
 for(unsigned j=0;j<6;++j)at<void*>(ui,menuOffsets[j])=menus[0][j];for(unsigned j=0;j<3;++j)at<void*>(ui,0x4a0+j*8)=tips[c->alias==1?0:c->alias==2?2-j:j];
 // Witness registrations before and after the tested references exercise swap-last
 // index repair. The model has no silent table truncation or wrapping counter.
 for(unsigned j=0;j<12;++j){witnesses[j]=object(16);safeInit(witnesses[j],j<6?item(1+j%3):actor(1+j%3));}
 safeInit((char*)ui+0x48,c->mask&512?actor(c->actor):actors[2]);safeInit((char*)ui+0x58,c->mask&1024?actor(c->actor):actors[2]);safeInit((char*)ui+0x68,item(c->oldItem));
 for(unsigned j=0;j<6;++j)bind(witnesses[j],j<3?actor(1+j%3):item(1+j%3));
 if(c->registry&&item(c->oldItem)){void* r=(char*)ui+0x68;unregisterRef(at<void*>(r,0),r,at<unsigned>(r,8));at<unsigned>(r,8)=UINT_MAX;}
}
void snapshot(){
 n(blockCount);for(unsigned j=0;j<blockCount;++j){Block& b=blocks[j];for(unsigned k=0;k<16;++k)if(b.p[k]!=0xd3||b.p[16+b.bytes+k]!=0x6c)invalid();n(b.bytes);unsigned end=b.bytes+32;for(unsigned k=0;k<end;){unsigned count=1;while(k+count<end&&b.p[k+count]==b.p[k])++count;n(count);cap->add(b.p+k,1);k+=count;}n(0);}
 registrySnapshot();for(unsigned j=1;j<LastCall;++j)n(calls[j]);n(mutated);
}
uint64_t originalTarget(Target t){switch(t){case Clear:return (uintptr_t)oldClear;case Activate:return (uintptr_t)oldActivate;case Cursor:return (uintptr_t)oldCursor;case DeleteItem:return (uintptr_t)oldDeleteItem;case DeleteActor:return (uintptr_t)oldDeleteActor;default:return (uintptr_t)oldHover;}}
void callTarget(Target t,autotest::Capture& invocation){switch(t){case Clear:autotest::invoke(invocation,ours?newClear:oldClear,ui);break;case Activate:autotest::invoke(invocation,ours?newActivate:oldActivate,ui,c->slot,c->flag);break;case Cursor:autotest::invoke(invocation,ours?newCursor:oldCursor,ui);break;case DeleteItem:autotest::invoke(invocation,ours?newDeleteItem:oldDeleteItem,ui,(CItem*)item(c->newItem));break;case DeleteActor:autotest::invoke(invocation,ours?newDeleteActor:oldDeleteActor,ui,(CCharacter*)actor(c->actor));break;default:autotest::invoke(invocation,ours?newHover:oldHover,ui,(CItem*)item(c->newItem),c->flag);}}
void side(void* context,autotest::Capture& out,bool candidate){c=(const Case*)context;cap=&out;ours=candidate;initialize();detour::Set d;redirects(d);if(d.failed()){out.issue=autotest::Capture::UnsupportedPointer;return;}
 const Target sequence[]={Hover,DeleteItem,Clear,Cursor,Activate,DeleteActor};unsigned count=c->target==Composition?6:c->repeat;
 for(step=0;step<count;++step){autotest::Capture invocation;invocation.reset();cap=&invocation;n(step);bool caught=false;try{callTarget(c->target==Composition?sequence[step]:c->target,invocation);}catch(const Failure& e){caught=true;n(e.call);if(e.call!=c->fault)invalid();}catch(...){invalid();}n(caught);if(caught!=(c->fault!=0))invalid();snapshot();cap=&out;if(!step){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}else if(invocation.callStarted!=1||invocation.callCompleted!=1)invalid();if(invocation.issue)out.issue=invocation.issue;out.add(invocation.data,invocation.length);}
}
void before(void* p,autotest::Capture& out){side(p,out,false);}void after(void* p,autotest::Capture& out){side(p,out,true);}
bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& value,unsigned& count){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);++count;int status=coverage.observe(host,a,b);if(!status&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callCompleted==1&&b.capture.callCompleted==1&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length))return true;size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    item-hover #%u target=%u seed=%u mask=%u old/new=%u/%u actor=%u alias=%u slot=%d ref=%d cursor=%d mutation=%u/%u/%u fault=%u/%u exits=%d/%d valid=%u/%u issues=%u/%u completed=%u/%u bytes=%lu/%lu first=%lu\n",count,unsigned(value.target),value.seed,value.mask,value.oldItem,value.newItem,value.actor,value.alias,value.slot,value.refSlot,value.cursor,value.mutationAt,value.mutation,value.mutationNth,value.fault,value.faultNth,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);coverage.report(host);return false;}
bool exceptionPair(const tlhybrid_host* host,Case& value){autotest::Outcome a,b;autotest::runChild(before,&value,a);autotest::runChild(after,&value,b);bool okay=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&a.capture.callCompleted==0&&b.capture.callCompleted==0&&a.capture.callTarget==originalTarget(value.target)&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(!okay)host->log("    item-hover exception target=%u boundary=%u nth=%u exits=%d/%d valid=%u/%u issue=%u/%u complete=%u/%u\n",unsigned(value.target),value.fault,value.faultNth,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted);return okay;}
int finish(const tlhybrid_host* host,autotest::Coverage& cv,unsigned count){cv.report(host);return count<20||cv.completed!=count||cv.different||cv.missing;}
} // namespace

TL_TEST(gameui_item_hover_clear){autotest::Coverage cv("gameui_item_hover_clear",originalTarget(Clear));unsigned count=0;for(unsigned mask=0;mask<64;++mask)for(unsigned alias=0;alias<3;++alias){Case v(Clear);v.mask=mask;v.alias=alias;v.seed=mask%6;v.repeat=mask%5==0?2:1;if(!pair(host,cv,v,count))return 1;}return finish(host,cv,count);}
TL_TEST(gameui_item_hover_activate){autotest::Coverage cv("gameui_item_hover_activate",originalTarget(Activate));unsigned count=0;const int slots[]={0,1,9};const int refs[]={INT_MIN,-1,0,1,INT_MAX};for(unsigned slot=0;slot<3;++slot)for(unsigned guid=0;guid<6;++guid)for(unsigned bits=0;bits<4;++bits)for(unsigned ref=0;ref<5;++ref){Case v(Activate);v.slot=slots[slot];v.guid=values[guid];v.hit=bits&1;v.flag=bits&2;v.refSlot=refs[ref];v.repeat=ref==2?2:1;if(!pair(host,cv,v,count))return 1;}for(unsigned ref=0;ref<5;++ref){Case v(Activate);v.mutationAt=Equipment;v.mutation=3;v.refSlot=refs[ref];if(!pair(host,cv,v,count))return 1;}if(finish(host,cv,count))return 1;Case v(Activate);v.fault=Equipment;if(!exceptionPair(host,v))return 1;host->log("    item-hover activate exceptions: 1 matched, excluded from completed receipts\n");return 0;}
TL_TEST(gameui_item_hover_cursor){autotest::Coverage cv("gameui_item_hover_cursor",originalTarget(Cursor));unsigned count=0;const int states[]={INT_MIN,-1,0,1,2,3,4,5,INT_MAX};for(unsigned j=0;j<9;++j)for(unsigned bits=0;bits<4;++bits){Case v(Cursor);v.cursor=states[j];v.drag=bits&1;v.alias=bits&2?3:0;v.repeat=2;if(!pair(host,cv,v,count))return 1;}for(unsigned j=0;j<9;++j){Case v(Cursor);v.cursor=states[(j+3)%9];v.refSlot=states[j];v.mutationAt=ShowCursor;v.mutation=2;if(!pair(host,cv,v,count))return 1;}if(finish(host,cv,count))return 1;for(unsigned j=ShowCursor;j<=SetCursor;++j){Case v(Cursor);v.fault=j;if(!exceptionPair(host,v))return 1;}host->log("    item-hover cursor exceptions: 2 matched, excluded from completed receipts\n");return 0;}
TL_TEST(gameui_item_hover_delete_item){autotest::Coverage cv("gameui_item_hover_delete_item",originalTarget(DeleteItem));unsigned count=0;for(unsigned old=0;old<4;++old)for(unsigned next=0;next<4;++next)for(unsigned mask=0;mask<64;mask+=7){Case v(DeleteItem);v.oldItem=old;v.newItem=next;v.mask=mask;v.alias=mask%3;v.repeat=2;v.registry=mask&1;if(!pair(host,cv,v,count))return 1;}for(unsigned mutation=1;mutation<=4;mutation+=3){Case v(DeleteItem);v.newItem=1;v.mutationAt=RemoveSafe;v.mutation=mutation;if(!pair(host,cv,v,count))return 1;}if(finish(host,cv,count))return 1;Case v(DeleteItem);v.newItem=1;v.fault=RemoveSafe;if(!exceptionPair(host,v))return 1;host->log("    item-hover item deletion exceptions: 1 matched, excluded from completed receipts\n");return 0;}
TL_TEST(gameui_item_hover_set){autotest::Coverage cv("gameui_item_hover_set",originalTarget(Hover));unsigned count=0;for(unsigned old=0;old<4;++old)for(unsigned next=0;next<4;++next)for(unsigned bits=0;bits<4;++bits)for(unsigned alias=0;alias<3;++alias){Case v(Hover);v.oldItem=old;v.newItem=next;v.flag=bits&1;v.registry=bits&2;v.alias=alias;v.seed=(old+next)%6;v.repeat=2;if(!pair(host,cv,v,count))return 1;}for(unsigned call=RemoveSafe;call<=AddSafe;++call)for(unsigned mutation=1;mutation<=4;mutation+=3){Case v(Hover);v.mutationAt=call;v.mutation=mutation;if(!pair(host,cv,v,count))return 1;}if(finish(host,cv,count))return 1;for(unsigned call=RemoveSafe;call<=AddSafe;++call){Case v(Hover);v.fault=call;if(!exceptionPair(host,v))return 1;}host->log("    item-hover set exceptions: 2 matched, excluded from completed receipts\n");return 0;}
TL_TEST(gameui_item_hover_delete_actor){autotest::Coverage cv("gameui_item_hover_delete_actor",originalTarget(DeleteActor));unsigned count=0;for(unsigned mask=0;mask<2048;mask+=17)for(unsigned actor=0;actor<3;++actor){Case v(DeleteActor);v.mask=mask;v.actor=actor;v.seed=mask%6;v.repeat=2;if(!pair(host,cv,v,count))return 1;}for(unsigned bit=0;bit<11;++bit){Case v(DeleteActor);v.mask=1u<<bit;if(!pair(host,cv,v,count))return 1;v.mask=0x7ff^(1u<<bit);if(!pair(host,cv,v,count))return 1;}const unsigned boundaries[]={GetOwner,SetOwner,Enchant,Combine,Stash,RemoveSafe};for(unsigned j=0;j<6;++j)for(unsigned mutation=1;mutation<=6;++mutation)if(mutation==1||mutation>=4){Case v(DeleteActor);v.mutationAt=boundaries[j];v.mutation=mutation;if(!pair(host,cv,v,count))return 1;}for(unsigned nth=1;nth<=6;++nth)for(unsigned mutation=1;mutation<=6;++mutation)if(mutation==1||mutation>=4){Case v(DeleteActor);v.mutationAt=GetOwner;v.mutationNth=nth;v.mutation=mutation;if(!pair(host,cv,v,count))return 1;v.mutationAt=SetOwner;if(!pair(host,cv,v,count))return 1;}if(finish(host,cv,count))return 1;unsigned exceptions=0;for(unsigned j=0;j<6;++j){unsigned total=boundaries[j]==GetOwner||boundaries[j]==SetOwner?6:boundaries[j]==RemoveSafe?2:1;for(unsigned nth=1;nth<=total;++nth){Case v(DeleteActor);v.fault=boundaries[j];v.faultNth=nth;if(!exceptionPair(host,v))return 1;++exceptions;}}host->log("    item-hover actor deletion exceptions: %u matched, excluded from completed receipts\n",exceptions);return 0;}
TL_TEST(gameui_item_hover_composition){autotest::Coverage cv("gameui_item_hover_composition",originalTarget(Composition));unsigned count=0;for(unsigned seed=0;seed<6;++seed)for(unsigned bits=0;bits<8;++bits){Case v(Composition);v.seed=seed;v.guid=values[seed];v.flag=bits&1;v.drag=bits&2;v.hit=bits&4;v.newItem=bits%4;v.cursor=int(seed)-1;v.mask=bits*293;v.alias=seed%3;if(!pair(host,cv,v,count))return 1;}return finish(host,cv,count);}
