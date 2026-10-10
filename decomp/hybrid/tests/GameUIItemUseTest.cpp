// Guarded differential tests for the item-use/drag-return path. Layouts and
// virtual slots reuse the accepted menuItemClick/onClick/spell fixtures.
#include <climits>
#include <cstring>
#include <CEGUI.h>
#include <OgreSceneNode.h>
#include "MenuItemClickState.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalReturn, (CGameUI*), "_ZN7CGameUI17returnDraggedItemEv")
extern "C" void recoveredReturn(CGameUI*) __asm__("_ZN7CGameUI17returnDraggedItemEv");
TL_ORIGINAL(void, originalPerform, (CGameUI*,CLevel*,CEquipment*,CCharacter*,CCharacter*,CCharacter*), "_ZN7CGameUI14performItemUseER6CLevelP10CEquipmentP10CCharacterS5_S5_")
extern "C" void recoveredPerform(CGameUI*,CLevel*,CEquipment*,CCharacter*,CCharacter*,CCharacter*) __asm__("_ZN7CGameUI14performItemUseER6CLevelP10CEquipmentP10CCharacterS5_S5_");
TL_ORIGINAL(void, originalUse, (CGameUI*,CLevel*,CEquipment*), "_ZN7CGameUI7useItemER6CLevelP10CEquipment")
extern "C" void recoveredUse(CGameUI*,CLevel*,CEquipment*) __asm__("_ZN7CGameUI7useItemER6CLevelP10CEquipment");
TL_ORIGINAL(bool, originalClick, (CGameUI*,ELayoutFunction), "_ZN7CGameUI7onClickE15ELayoutFunction")
extern "C" bool recoveredClick(CGameUI*,ELayoutFunction) __asm__("_ZN7CGameUI7onClickE15ELayoutFunction");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dropFn,"_ZN10CEquipment13playDropSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
TL_FUNCTION(pickAtFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
TL_FUNCTION(pickAnyFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(removeFn,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(positionFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(addItemFn,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(addSafeFn,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(removeSafeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(hardwareFn,"_ZN7CGameUI20updateHardwareCursorEv")
TL_FUNCTION(hoverFn,"_ZN7CGameUI16setMouseOverItemEP5CItemb")
TL_FUNCTION(cursorFn,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(canUseFn,"_ZN10CEquipment14canUseOnTargetEP10CCharacterP9CBaseUnit")
TL_FUNCTION(useTargetFn,"_ZN10CEquipment11useOnTargetEP10CCharacterP9CBaseUnit")
TL_FUNCTION(playFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(queueFn,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(keyFn,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(aliveFn,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(performFn,"_ZN7CGameUI14performItemUseER6CLevelP10CEquipmentP10CCharacterS5_S5_")
TL_FUNCTION(usableFn,"_ZN5CItem9isUseableEv")
extern "C" char removeWindowFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
namespace {
using namespace menu_item_click_detail;
typedef char check_ui_size[sizeof(CGameUI)==0x1a08?1:-1];
typedef char check_actor_size[sizeof(CCharacter)==0x778?1:-1];
enum Boundary { Drop=1, Detach, Isa, Shared, PickAt, PickAny, Remove, Position, AddItem,
 AddSafe, RemoveSafe, Destroy, Hardware, Hover, Layout, Cursor, CanUse, UseTarget,
 Play, Queue, Key, Alive, Perform, Usable, Front, LastBoundary };
enum Mutation { None, DropChangesDrag, DetachChangesDrag, IsaChangesOwner,
 PickChangesDragOwner, PickInvalidatesDrag, PositionChangesLevelDrag,
 HardwareChangesMenus, CanUseChangesMode, CanUseChangesPlayer, UseExhausts,
 UseReplenishes, UseChangesDrag, RemoveChangesDrag, HoverChangesMenus,
 DestroyChangesMenus, LayoutChangesPlayer, AliveChangesPlayer, IsaChangesPlayer,
 KeyChangesPlayer, PlayChangesPlayer, PlayClearsSound, AddChangesLaterRefs,
 RemoveChangesLaterRefs, PickChangesInventory, UseChangesInventory,
 HardwareChangesDrag, UsableChangesDrag, UsableChangesPlayer, LastMutation };
struct Case {
 unsigned target, drag, ownerType, failureMask, tags, followers, seed, mutation,
  fault, repeat, ownerRole, userRole, targetRole;
 int slot, mode, stack, count, petState, key;
 bool attached, allowed, live, inventory, actorSound;
 Case(unsigned t=0):target(t),drag(1),ownerType(0),failureMask(0),tags(1),followers(1),
  seed(0),mutation(0),fault(0),repeat(1),ownerRole(2),userRole(3),targetRole(4),
  slot(31),mode(0),stack(2),count(1),petState(40),key(0),attached(true),
  allowed(true),live(true),inventory(true),actorSound(true){}
};
struct Stop {};
struct Block { unsigned char* p; unsigned size; };
struct Registration { void* object; TSafePointer<void*>* refs[16]; unsigned count; };
Block blocks[80];unsigned blockCount;
Registration regs[12];unsigned regCount;
unsigned calls[LastBoundary],changed,deleted[3];
const Case* current;autotest::Capture* capture;
CGameUI* gui;UIState* ui;CPlayer* players[2];CCharacter* actors[5];
CEquipment* items[3];CInventory* inventories[5];CLevel* levels[2];
CInventoryMenu* invMenus[2];CPetMenu* petMenus[2];CSubMenu* otherMenus[4];
CEquipmentTooltip* tips[3];CEGUI::Window* windows[5];CSoundBank* banks[3];
Ogre::SceneNode* nodes[5];CCharacter** followerArrays[2];
CSharedStash* stash;void* itemVtable[2];void* menuVtable[10];
TSafePointer<void*>* witnesses[3];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void number(int n){capture->add(&n,4);}void pointer(const void* p){capture->addPointer(p);}
void scalar(float f){capture->add(&f,4);}
void require(bool b){if(!b)_exit(90);}
void* guarded(unsigned size){require(blockCount<80);unsigned char* p=(unsigned char*)autotest::allocate(size+32);require(p!=0);std::memset(p,0xd3,16);std::memset(p+16,0,size);std::memset(p+16+size,0x6c,16);blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;}
template<class T>T* object(){return reinterpret_cast<T*>(guarded(sizeof(T)));}
void guards(){for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){require(blocks[i].p[int(j)-16]==0xd3);require(blocks[i].p[blocks[i].size+j]==0x6c);}}
void tag(unsigned b,const void* p){number(b);pointer(p);++calls[b];if(current->fault==b)throw Stop();}
Registration& registration(void* object){for(unsigned i=0;i<regCount;++i)if(regs[i].object==object)return regs[i];require(regCount<12);Registration& r=regs[regCount++];r.object=object;r.count=0;return r;}
unsigned registerRef(void* object,TSafePointer<void*>* ref){Registration& r=registration(object);require(r.count<16);r.refs[r.count]=ref;return r.count++;}
void unregisterRef(void* object,TSafePointer<void*>* ref,unsigned index){Registration& r=registration(object);if(index==~0u)return;require(index<r.count&&r.refs[index]==ref);r.refs[index]=r.refs[--r.count];if(index<r.count)r.refs[index]->setIndex(index);}
void bind(void* ref,void* value){void* old=at<void*>(ref,0);if(old==value)return;if(old)unregisterRef(old,(TSafePointer<void*>*)ref,at<unsigned>(ref,8));at<void*>(ref,0)=0;if(value)at<unsigned>(ref,8)=registerRef(value,(TSafePointer<void*>*)ref);at<void*>(ref,0)=value;}
void invalidate(void* object){Registration& r=registration(object);for(unsigned k=0;k<r.count;++k)r.refs[k]->invalidate();r.count=0;}
void swapMenus(){ui->inventoryMenu=invMenus[1];ui->petMenu=petMenus[1];}
void mutate(unsigned boundary){if(changed)return;unsigned m=current->mutation;
 if(m==DropChangesDrag&&boundary==Drop){bind(&ui->draggedItem,items[1]);changed=1;}
 if(m==DetachChangesDrag&&boundary==Detach){bind(&ui->draggedItem,items[1]);changed=1;}
 if(m==IsaChangesOwner&&boundary==Isa){bind(&ui->dragOwner,actors[3]);changed=1;}
 if(m==PickChangesDragOwner&&boundary==PickAt){bind(&ui->draggedItem,items[1]);bind(&ui->dragOwner,actors[3]);changed=1;}
 if(m==PickInvalidatesDrag&&boundary==PickAt){invalidate(ui->draggedItem.getObject());changed=1;}
 if(m==PositionChangesLevelDrag&&boundary==Position){ui->level=levels[1];bind(&ui->draggedItem,items[1]);changed=1;}
 if(m==HardwareChangesMenus&&boundary==Hardware){swapMenus();changed=1;}
 if(m==CanUseChangesMode&&boundary==CanUse){items[0]->m_iUnknown260=1;changed=1;}
 if(m==CanUseChangesPlayer&&boundary==CanUse){ui->player=players[1];ui->soundBank=banks[1];changed=1;}
 if(m==UseExhausts&&boundary==UseTarget){items[0]->m_iUnknown238=1;items[0]->m_iUnknown248=0;changed=1;}
 if(m==UseReplenishes&&boundary==UseTarget){items[0]->m_iUnknown238=2;items[0]->m_iUnknown248=INT_MAX;changed=1;}
 if(m==UseChangesDrag&&boundary==UseTarget){bind(&ui->draggedItem,items[1]);changed=1;}
 if(m==RemoveChangesDrag&&boundary==Remove){bind(&ui->draggedItem,items[0]);changed=1;}
 if(m==HoverChangesMenus&&boundary==Hover){swapMenus();changed=1;}
 if(m==DestroyChangesMenus&&boundary==Destroy){swapMenus();changed=1;}
 if(m==LayoutChangesPlayer&&boundary==Layout){ui->player=players[1];changed=1;}
 if(m==AliveChangesPlayer&&boundary==Alive){ui->player=players[1];changed=1;}
 if(m==IsaChangesPlayer&&boundary==Isa){ui->player=players[1];changed=1;}
 if(m==KeyChangesPlayer&&boundary==Key){ui->player=players[1];changed=1;}
 if(m==PlayChangesPlayer&&boundary==Play){ui->player=players[1];changed=1;}
 if(m==PlayClearsSound&&boundary==Play){actor(ui->player).soundBank=0;changed=1;}
 if(m==AddChangesLaterRefs&&boundary==AddSafe){bind(&ui->targetCharacter,actors[1]);bind(&ui->itemUser,actors[0]);changed=1;}
 if(m==RemoveChangesLaterRefs&&boundary==RemoveSafe){bind(&ui->targetCharacter,actors[1]);bind(&ui->itemUser,actors[0]);changed=1;}
 if(m==PickChangesInventory&&boundary==PickAt){actor(ui->dragOwner.getObject()).inventory=inventories[4];changed=1;}
 if(m==UseChangesInventory&&boundary==UseTarget){items[0]->m_pInventory=inventories[4];changed=1;}
 if(m==HardwareChangesDrag&&boundary==Hardware){bind(&ui->draggedItem,items[1]);bind(&ui->dragOwner,actors[3]);changed=1;}
 if(m==UsableChangesDrag&&boundary==Usable){bind(&ui->draggedItem,items[1]);changed=1;}
 if(m==UsableChangesPlayer&&boundary==Usable){ui->player=players[1];changed=1;}
}
void drop(CEquipment* p,Ogre::SceneNode* n){tag(Drop,p);pointer(n);mutate(Drop);}
void detach(CEGUI::Window* p,CEGUI::Window* child){tag(Detach,p);pointer(child);if(at<CEGUI::Window*>(child,0xb0)==p)at<CEGUI::Window*>(child,0xb0)=0;mutate(Detach);}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){tag(Isa,p);number(type);bool answer=false;for(unsigned i=0;i<3;++i)if(p==items[i])answer=(type==1&&(current->tags&1))||(type==32&&(current->tags&2))||(type==125&&(current->tags&4));if(p==actors[2])answer=unsigned(type)==current->ownerType;if(p==actors[3])answer=type==UNITTYPES::STASH;mutate(Isa);return answer;}
CSharedStash* shared(){tag(Shared,stash);return stash;}
CEquipment* pickAt(CInventory* p,CEquipment* item,int slot,bool allow){tag(PickAt,p);pointer(item);number(slot);number(allow);mutate(PickAt);return current->failureMask&1?0:item;}
CEquipment* pickAny(CInventory* p,CEquipment* item,bool allow){tag(PickAny,p);pointer(item);number(allow);mutate(PickAny);return current->failureMask&2?0:item;}
long long removeEquipment(CInventory* p,CEquipment* item){tag(Remove,p);pointer(item);item->m_pInventory=0;mutate(Remove);return 0;}
Ogre::Vector3 position(CPositionableObject* p,bool absolute){tag(Position,p);number(absolute);mutate(Position);return Ogre::Vector3(-123.75f,.03125f,8192.5f);}
void addItem(CLevel* p,CItem* item,const Ogre::Vector3& pos,bool allow){tag(AddItem,p);pointer(item);scalar(pos.x);scalar(pos.y);scalar(pos.z);number(allow);}
unsigned addSafe(CRunicCore* p,TSafePointer<void*>* ref){tag(AddSafe,p);pointer(ref);pointer(at<void*>(ref,0));number(at<unsigned>(ref,8));unsigned result=registerRef(p,ref);mutate(AddSafe);return result;}
void removeSafe(CRunicCore* p,TSafePointer<void*>* ref,unsigned index){tag(RemoveSafe,p);pointer(ref);number(index);pointer(at<void*>(ref,0));unregisterRef(p,ref,index);mutate(RemoveSafe);}
void destroy(CEquipment* p){tag(Destroy,p);pointer(ui->draggedItem.getObject());number(at<unsigned>(&ui->draggedItem,8));pointer(ui->dragOwner.getObject());number(ui->dragSlot);pointer(at<void*>(ui->inventoryMenu,0x1020));pointer(at<void*>(ui->petMenu,0x1370));for(unsigned i=0;i<3;++i)if(items[i]==p){require(!deleted[i]);deleted[i]=1;}invalidate(p);mutate(Destroy);}
void hardware(CGameUI* p){tag(Hardware,p);pointer(ui->draggedItem.getObject());pointer(ui->dragOwner.getObject());number(ui->dragSlot);number(at<int>(p,0x1678));number(at<int>(p,0x167c));mutate(Hardware);}
void hover(CGameUI* p,CItem* item,bool force){tag(Hover,p);pointer(item);number(force);pointer(ui->draggedItem.getObject());mutate(Hover);}
void layout(CSubMenu* p){tag(Layout,p);pointer(ui->draggedItem.getObject());number(deleted[0]);mutate(Layout);}
void cursor(CGameUI* p,ECursorState state){tag(Cursor,p);number(state);at<int>(p,0x12fc)=state;}
bool canUse(CEquipment* p,CCharacter* user,CBaseUnit* target){tag(CanUse,p);pointer(user);pointer(target);mutate(CanUse);return current->allowed;}
void useTarget(CEquipment* p,CCharacter* user,CBaseUnit* target){tag(UseTarget,p);pointer(user);pointer(target);mutate(UseTarget);}
void play(CSoundBank* p,int sample,Ogre::SceneNode* node,float a,float b,bool flag){tag(Play,p);number(sample);pointer(node);scalar(a);scalar(b);number(flag);mutate(Play);}
void queue(CSoundBank* p,int sample,float a,float b){tag(Queue,p);number(sample);scalar(a);scalar(b);}
short key(unsigned k){tag(Key,0);number(k);mutate(Key);return short(current->key);}
bool alive(CCharacter* p){tag(Alive,p);mutate(Alive);return current->live;}
void perform(CGameUI* p,CLevel* l,CEquipment* e,CCharacter* owner,CCharacter* user,CCharacter* target){tag(Perform,p);pointer(l);pointer(e);pointer(owner);pointer(user);pointer(target);}
bool usable(CItem* p){tag(Usable,p);mutate(Usable);return true;}
void front(CEGUI::Window* p){tag(Front,p);}
void forbidden(){_exit(91);}
void initialize(const Case& c){blockCount=regCount=changed=0;std::memset(calls,0,sizeof(calls));std::memset(deleted,0,sizeof(deleted));std::memset(regs,0,sizeof(regs));
 gui=object<CGameUI>();ui=&state(gui);for(unsigned i=0;i<2;++i){players[i]=object<CPlayer>();actors[i]=players[i];}for(unsigned i=2;i<5;++i)actors[i]=object<CCharacter>();
 for(unsigned i=0;i<5;++i){inventories[i]=object<CInventory>();nodes[i]=object<Ogre::SceneNode>();actor(actors[i]).inventory=inventories[i];at<Ogre::SceneNode*>(actors[i],0x58)=nodes[i];}
 for(unsigned i=0;i<3;++i){items[i]=object<CEquipment>();banks[i]=object<CSoundBank>();tips[i]=object<CEquipmentTooltip>();tips[i]->m_iCachedItemGuid=0x1122334400000000LL+i;witnesses[i]=object<TSafePointer<void*> >();at<unsigned>(witnesses[i],8)=~0u;}
 for(unsigned i=0;i<5;++i)windows[i]=object<CEGUI::Window>();
 for(unsigned i=0;i<2;++i){levels[i]=object<CLevel>();invMenus[i]=object<CInventoryMenu>();petMenus[i]=object<CPetMenu>();followerArrays[i]=(CCharacter**)guarded(2*sizeof(CCharacter*));followerArrays[i][0]=actors[3+i];followerArrays[i][1]=actors[4-i];at<CCharacter**>(players[i],0x648)=followerArrays[i];at<CCharacter**>(players[i],0x650)=followerArrays[i]+c.followers;at<CCharacter**>(players[i],0x658)=followerArrays[i]+2;actor(players[i]).soundBank=c.actorSound?banks[i+1]:0;}
 otherMenus[0]=object<CMerchantMenu>();otherMenus[1]=object<CEnchantMenu>();otherMenus[2]=object<CCombineMenu>();otherMenus[3]=object<CStashMenu>();stash=object<CSharedStash>();stash->m_pInventory=inventories[4];
 for(unsigned i=0;i<2;++i)itemVtable[i]=(void*)&forbidden;itemVtable[1]=(void*)&destroy;for(unsigned i=0;i<10;++i)menuVtable[i]=(void*)&forbidden;menuVtable[9]=(void*)&layout;
 for(unsigned i=0;i<3;++i){at<void**>(items[i],0)=itemVtable;items[i]->m_iUnknown238=c.stack;items[i]->m_iUnknown248=c.count;items[i]->m_iUnknown260=c.mode;items[i]->m_pInventory=c.inventory?inventories[2]:0;items[i]->m_pIconWindow=windows[i];at<CEGUI::Window*>(windows[i],0xb0)=c.attached?windows[3]:windows[4];}
 for(unsigned i=0;i<2;++i){at<void**>(invMenus[i],0)=menuVtable;at<void**>(petMenus[i],0)=menuVtable;at<CEquipment*>(invMenus[i],0x1020)=items[2];at<CEquipment*>(petMenus[i],0x1370)=items[2];}
 const unsigned offsets[]={0x3438,0xf0,0x190,0x3408};for(unsigned i=0;i<4;++i)at<CEquipment*>(otherMenus[i],offsets[i])=items[2];
 ui->player=players[0];ui->level=levels[0];ui->inventoryMenu=invMenus[0];ui->petMenu=petMenus[0];ui->merchantMenu=(CMerchantMenu*)otherMenus[0];ui->enchantMenu=(CEnchantMenu*)otherMenus[1];ui->combineMenu=(CCombineMenu*)otherMenus[2];ui->stashMenu=(CStashMenu*)otherMenus[3];ui->tooltip=tips[0];ui->comparisonTooltip1=tips[1];ui->comparisonTooltip2=tips[2];ui->soundBank=banks[0];ui->rootWindow=windows[4];ui->dragWindow=windows[3];ui->dragSlot=c.slot;at<int>(gui,0x1678)=INT_MIN;at<int>(gui,0x167c)=INT_MAX;at<int>(gui,0x12fc)=17;
 const unsigned refs[]={0x80,0x90,0xa0,0xb8,0xc8};for(unsigned i=0;i<5;++i)at<unsigned>(gui,refs[i]+8)=~0u;
 // Witnesses force nonzero registration indices and swap-removal index repair.
 bind(witnesses[0],items[0]);bind(witnesses[1],actors[2]);bind(witnesses[2],items[0]);
 if(c.seed==1||c.seed==3){bind(&ui->targetedItem,items[1]);bind(&ui->targetCharacter,actors[4]);bind(&ui->itemUser,actors[2]);}
 if(c.seed==2||c.seed==3){bind(&ui->targetedItem,items[0]);if(c.seed==2){bind(&ui->targetCharacter,c.ownerRole<5?actors[c.ownerRole]:0);bind(&ui->itemUser,actors[c.userRole]);}}
 if(c.drag){bind(&ui->draggedItem,items[c.drag-1]);bind(&ui->dragOwner,actors[2]);}
 actor(actors[3]).aiState=c.petState;actor(actors[4]).aiState=c.petState==41?43:c.petState==42?40:c.petState;
}
void redirect(detour::Set& d){
#define R(N,F) TL_REDIRECT(d,N##Fn,&F)
 R(isa,isa);R(drop,drop);R(shared,shared);R(pickAt,pickAt);R(pickAny,pickAny);R(remove,removeEquipment);R(position,position);R(addItem,addItem);R(addSafe,addSafe);R(removeSafe,removeSafe);R(hardware,hardware);R(hover,hover);R(cursor,cursor);R(canUse,canUse);R(useTarget,useTarget);R(play,play);R(queue,queue);R(key,key);R(alive,alive);R(usable,usable);
 if(current->target==2)R(perform,perform);
#undef R
 d.redirect(removeWindowFn,removeWindowFn,&detach);d.redirect(frontFn,frontFn,&front);
}
// All payload bytes are initialized, and all object and vtable identities are
// stable across the forked pair, as in the accepted onClick regression fixture.
void snapshot(){guards();number(blockCount);for(unsigned i=0;i<blockCount;++i){number(blocks[i].size);capture->add(blocks[i].p,blocks[i].size);}number(regCount);for(unsigned i=0;i<regCount;++i){pointer(regs[i].object);number(regs[i].count);for(unsigned j=0;j<regs[i].count;++j)pointer(regs[i].refs[j]);}for(unsigned i=1;i<LastBoundary;++i)number(calls[i]);for(unsigned i=0;i<3;++i)number(deleted[i]);number(changed);}
void side(void* data,autotest::Capture& out,bool ours){const Case& c=*(Case*)data;current=&c;capture=&out;initialize(c);detour::Set d;redirect(d);require(!d.failed());
 autotest::Capture invocation;
 for(unsigned iteration=0;iteration<c.repeat;++iteration){invocation.reset();capture=&invocation;number(iteration);bool threw=false;try{
  if(c.target==0)autotest::invoke(invocation,ours?&recoveredReturn:&originalReturn,gui);
  else if(c.target==1)autotest::invoke(invocation,ours?&recoveredPerform:&originalPerform,gui,levels[1],items[0],c.ownerRole<5?actors[c.ownerRole]:0,actors[c.userRole],actors[c.targetRole]);
  else if(c.target==2||c.target==3)autotest::invoke(invocation,ours?&recoveredUse:&originalUse,gui,levels[1],items[0]);
  else autotest::invoke(invocation,ours?&recoveredClick:&originalClick,gui,static_cast<ELayoutFunction>(68));
 }catch(const Stop&){threw=true;}catch(...){_exit(92);}number(threw);guards();capture=&out;
 if(iteration==0){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}else{require(out.callTarget==invocation.callTarget&&invocation.callStarted);out.callCompleted=out.callCompleted&&invocation.callCompleted;}
 if(invocation.issue)out.issue=invocation.issue;out.add(invocation.data,invocation.length);}
 capture=&out;snapshot();
}
void a(void* p,autotest::Capture& out){side(p,out,false);}void b(void* p,autotest::Capture& out){side(p,out,true);}
int compare(const tlhybrid_host* host,autotest::Coverage& coverage,Case c,unsigned& total){autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++total;int d=coverage.observe(host,x,y);if(d||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus){size_t n=0;while(n<x.capture.length&&n<y.capture.length&&x.capture.data[n]==y.capture.data[n])++n;host->log("    item path %u case %u drag %u owner %u fail %u mode %d stack %d count %d tags %u followers %u state %d key %d seed %u mutation %u exits %d/%d completed %u/%u lengths %lu/%lu first %lu\n",c.target,total,c.drag,c.ownerType,c.failureMask,c.mode,c.stack,c.count,c.tags,c.followers,c.petState,c.key,c.seed,c.mutation,x.childStatus,y.childStatus,x.capture.callCompleted,y.capture.callCompleted,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)n);coverage.report(host);return 1;}return 0;}
}
TL_TEST(gameui_item_return_dragged){autotest::Coverage cov("gameui_item_return_dragged",(uintptr_t)&originalReturn);unsigned total=0;const unsigned owners[]={0,41,128,170};const int slots[]={INT_MIN,-1,0,INT_MAX};for(unsigned owner=0;owner<4;++owner)for(unsigned fail=0;fail<3;++fail)for(unsigned attached=0;attached<2;++attached)for(unsigned slot=0;slot<4;++slot){Case c;c.ownerType=owners[owner];c.failureMask=fail==2?3:fail;c.attached=attached;c.slot=slots[slot];if(compare(host,cov,c,total))return 1;}
 for(unsigned seed=0;seed<4;++seed){Case c;c.drag=0;c.seed=seed;if(compare(host,cov,c,total))return 1;c.drag=1;c.repeat=2;if(compare(host,cov,c,total))return 1;}
 const unsigned mutations[]={DropChangesDrag,DetachChangesDrag,IsaChangesOwner,PickChangesDragOwner,PickInvalidatesDrag,PositionChangesLevelDrag,HardwareChangesMenus,PickChangesInventory,HardwareChangesDrag};for(unsigned i=0;i<sizeof(mutations)/sizeof(*mutations);++i){Case c;c.mutation=mutations[i];if(c.mutation==PositionChangesLevelDrag)c.failureMask=3;else if(c.mutation==PickChangesDragOwner||c.mutation==PickChangesInventory)c.failureMask=1;if(compare(host,cov,c,total))return 1;}
 cov.report(host);host->log("    returnDraggedItem: %u completed pairs\n",total);return 0;}
TL_TEST(gameui_item_perform_use){autotest::Coverage cov("gameui_item_perform_use",(uintptr_t)&originalPerform);unsigned total=0;const int stacks[]={INT_MIN,-1,0,1,2,INT_MAX};const int counts[]={INT_MIN,-10000,-9999,-9998,-1,0,1,INT_MAX};for(unsigned stack=0;stack<6;++stack)for(unsigned count=0;count<8;++count)for(unsigned drag=0;drag<3;++drag){Case c(1);c.stack=stacks[stack];c.count=counts[count];c.drag=drag;c.inventory=(stack+count+drag)%2;c.seed=stack%4;if(compare(host,cov,c,total))return 1;}
 const int modes[]={INT_MIN,-1,0,1,2,INT_MAX};for(unsigned mode=0;mode<6;++mode)for(unsigned seed=0;seed<4;++seed)for(unsigned allowed=0;allowed<2;++allowed){Case c(1);c.mode=modes[mode];c.seed=seed;c.allowed=allowed;if(compare(host,cov,c,total))return 1;}
 for(unsigned role=0;role<6;++role){Case c(1);c.mode=1;c.ownerRole=role;c.userRole=(role+1)%5;c.targetRole=(role+2)%5;c.seed=1;if(compare(host,cov,c,total))return 1;}
 const unsigned mutations[]={HardwareChangesMenus,CanUseChangesMode,CanUseChangesPlayer,UseExhausts,UseReplenishes,UseChangesDrag,RemoveChangesDrag,HoverChangesMenus,DestroyChangesMenus,LayoutChangesPlayer,AddChangesLaterRefs,RemoveChangesLaterRefs,UseChangesInventory,HardwareChangesDrag};for(unsigned i=0;i<sizeof(mutations)/sizeof(*mutations);++i){Case c(1);c.stack=1;c.count=0;c.seed=1;c.mutation=mutations[i];if(c.mutation==CanUseChangesPlayer)c.allowed=false;if(c.mutation==UseExhausts){c.stack=INT_MAX;c.count=INT_MAX;}if(c.mutation==RemoveChangesDrag)c.drag=2;if(c.mutation==AddChangesLaterRefs||c.mutation==RemoveChangesLaterRefs)c.mode=1;if(compare(host,cov,c,total))return 1;}
 cov.report(host);host->log("    performItemUse: %u completed pairs\n",total);return 0;}
TL_TEST(gameui_item_use_routing){autotest::Coverage cov("gameui_item_use_routing",(uintptr_t)&originalUse);unsigned total=0;const int keys[]={SHRT_MIN,-1,0,1,SHRT_MAX};const int states[]={INT_MIN,40,41,42,43,INT_MAX};for(unsigned tags=0;tags<8;++tags)for(unsigned key=0;key<5;++key)for(unsigned followers=0;followers<3;++followers){Case c(2);c.tags=tags;c.key=keys[key];c.followers=followers;c.petState=states[(tags+key)%6];c.actorSound=(tags+key)%2;if(compare(host,cov,c,total))return 1;}
 for(unsigned state=0;state<6;++state)for(unsigned sound=0;sound<2;++sound){Case c(2);c.tags=5;c.petState=states[state];c.actorSound=sound;if(compare(host,cov,c,total))return 1;}
 for(unsigned tags=0;tags<8;++tags){Case c(2);c.tags=tags;c.live=false;if(compare(host,cov,c,total))return 1;}
 const unsigned mutations[]={AliveChangesPlayer,IsaChangesPlayer,KeyChangesPlayer,PlayChangesPlayer,PlayClearsSound};for(unsigned i=0;i<5;++i)for(unsigned route=0;route<3;++route){Case c(2);c.mutation=mutations[i];c.key=route?-1:1;c.petState=route==2?41:40;if(compare(host,cov,c,total))return 1;}
 // A short return defines AX only. The pinned compiler leaves these poison
 // bits in EAX, distinguishing signed-short tests from accidental int tests.
 const int poisonedKeys[]={0x00008000,0x12348000,0x1234ffff,-65535,-65536};
 for(unsigned k=0;k<5;++k)for(unsigned route=0;route<3;++route){Case c(2);c.key=poisonedKeys[k];c.followers=route?1:0;c.petState=route==2?41:40;if(compare(host,cov,c,total))return 1;}
 cov.report(host);host->log("    useItem routing: %u completed pairs\n",total);return 0;}
TL_TEST(gameui_item_use_composed){autotest::Coverage cov("gameui_item_use_composed",(uintptr_t)&originalUse);unsigned total=0;if(!host->comparison_pair||!host->comparison_pair((uintptr_t)&originalPerform,(uintptr_t)&recoveredPerform))return 1;
 for(unsigned mode=0;mode<3;++mode)for(unsigned route=0;route<3;++route)for(unsigned exhausted=0;exhausted<2;++exhausted)for(unsigned allowed=0;allowed<2;++allowed){Case c(3);c.mode=mode;c.tags=route==2?5:1;c.key=route==1?-1:0;c.stack=exhausted?1:2;c.count=0;c.allowed=allowed;c.seed=1;if(compare(host,cov,c,total))return 1;}
 const unsigned mutations[]={UseExhausts,UseChangesDrag,HoverChangesMenus,CanUseChangesMode,AliveChangesPlayer,KeyChangesPlayer};for(unsigned i=0;i<6;++i){Case c(3);c.key=-1;c.mutation=mutations[i];c.stack=1;c.count=0;if(compare(host,cov,c,total))return 1;}
 cov.report(host);host->log("    composed useItem to real performItemUse: %u completed pairs\n",total);return 0;}
TL_TEST(gameui_item_click_composed){autotest::Coverage cov("gameui_item_click_composed",(uintptr_t)&originalClick);unsigned total=0;if(!host->comparison_pair||!host->comparison_pair((uintptr_t)&originalPerform,(uintptr_t)&recoveredPerform)||!host->comparison_pair((uintptr_t)&originalReturn,(uintptr_t)&recoveredReturn))return 1;
 for(unsigned mode=0;mode<3;++mode)for(unsigned exhausted=0;exhausted<2;++exhausted)for(unsigned failure=0;failure<3;++failure){Case c(4);c.mode=mode;c.stack=exhausted?1:2;c.count=0;c.failureMask=failure==2?3:failure;if(compare(host,cov,c,total))return 1;}
 const unsigned mutations[]={UseChangesDrag,HardwareChangesMenus,UsableChangesDrag,UsableChangesPlayer};for(unsigned i=0;i<4;++i){Case c(4);c.mutation=mutations[i];if(compare(host,cov,c,total))return 1;}
 cov.report(host);host->log("    composed onClick to real performItemUse and returnDraggedItem: %u completed pairs\n",total);return 0;}
TL_TEST(gameui_item_expected_exceptions){unsigned total=0;const unsigned faults[]={Drop,Detach,PickAt,PickAny,Position,AddItem,Hardware,CanUse,UseTarget,Remove,Hover,Layout,Cursor,Alive,Isa,Key,Play,Queue};for(unsigned i=0;i<sizeof(faults)/sizeof(*faults);++i){Case c;c.fault=faults[i];if(c.fault<=Hardware){c.failureMask=3;}if(c.fault==CanUse||c.fault==UseTarget||c.fault==Remove||c.fault==Hover||c.fault==Layout||c.fault==Cursor){c.target=1;c.stack=1;c.count=0;}if(c.fault==Alive||c.fault==Isa||c.fault==Key||c.fault==Play||c.fault==Queue){c.target=2;c.key=-1;c.petState=41;}
 autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(!x.reportValid||!y.reportValid||x.childStatus||y.childStatus||!x.capture.callStarted||!y.capture.callStarted||x.capture.callCompleted||y.capture.callCompleted||x.capture.issue||y.capture.issue||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length)){host->log("    item exception boundary %u target %u exits %d/%d completed %u/%u lengths %lu/%lu\n",c.fault,c.target,x.childStatus,y.childStatus,x.capture.callCompleted,y.capture.callCompleted,(unsigned long)x.capture.length,(unsigned long)y.capture.length);return 1;}++total;}
 host->log("    EXPECTED ITEM EXCEPTIONS: %u matching unwinds excluded from normal completion coverage\n",total);return 0;}
