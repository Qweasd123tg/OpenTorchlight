// Original 0xa9c3b0. Public entries run normally in separate children.
// Real UTF8 conversion and real CEGUI strings; only observable collaborators
// are redirected. The oracle never calls the recovered reset helper.
#include <cstring>
#include <string>
#include <vector>
#include <new>
#include <dlfcn.h>
#include <CEGUIString.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalLoading, (CGameUI*,bool), "_ZN7CGameUI17setLoadingVisibleEb")
extern "C" void candidateLoading(CGameUI*,bool) __asm__("_ZN7CGameUI17setLoadingVisibleEb");
TL_FUNCTION(managerBoundary,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(globalsBoundary,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(randomBoundary,"_ZN12CGameGlobals12getRandomTipEv")
TL_FUNCTION(contextBoundary,"_ZN12CGameGlobals13getContextTipE11EContextTip")
TL_FUNCTION(convertBoundary,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(std::string, realConvert, (const std::wstring&), "_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
extern "C" bool realGrow(CEGUI::String*,size_t) __asm__("_ZN5CEGUI6String4growEm");
extern "C" char isChildBoundary[] __asm__("_ZNK5CEGUI6Window7isChildEPKS0_");
extern "C" char addBoundary[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char removeBoundary[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char textBoundary[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char rootBoundary[] __asm__("_ZN4Ogre4Root15getSingletonPtrEv");
extern "C" char renderBoundary[] __asm__("_ZN4Ogre4Root14renderOneFrameEv");
extern "C" void realDestructor(CEGUI::String*) __asm__("_ZN5CEGUI6StringD1Ev");

namespace {
enum { UISize=0x1a08, MaxBlocks=40, MaxSize=0x3440 };
// Constructor denotes the common out-of-line grow boundary, not an entry
// constructor hook: the recovered public body inlines the SDK constructor.
enum Tag { InitialManager=1, Membership, Add, Remove, Globals, RandomTip,
           Convert, Constructor, Text, Destructor, PreManager, Root, Render,
           PostManager, ConstructorAllocation };
enum Mutation { MembershipReload=1, AddReload=2, RandomReload=4,
                ConvertReload=8, RootReload=16, RenderReload=32 };
struct Case {
    unsigned gate,text,mutation,fault,repeat,alias,pattern;
    bool show,present,renderResult;
    Case():gate(1),text(1),mutation(0),fault(0),repeat(1),alias(0),pattern(0),
           show(true),present(false),renderResult(true){}
};
struct Block { unsigned char* p; unsigned size; unsigned char expected[MaxSize]; };
struct Injected { unsigned tag; explicit Injected(unsigned t):tag(t){} };
struct State {
    std::wstring tip,sharedTip,wantedTip;
    std::string utf8Witness,wantedUTF8;
    unsigned errors,hits,catches,unwinds,step,total,managerCalls,plan[20],count;
    unsigned iteration,activeFault,nextPost,globalsIndex,ctorAllocations;
    bool present,show,returned,constructed,converted;
    CEGUI::String* temporary;
    State():errors(0),hits(0),catches(0),unwinds(0),step(0),total(0),managerCalls(0),
        count(0),iteration(0),activeFault(0),nextPost(2),globalsIndex(0),ctorAllocations(0),
        present(false),show(false),returned(false),constructed(false),converted(false),temporary(0){}
};
const Case* current; State* state; autotest::Capture* capture;
Block blocks[MaxBlocks]; unsigned blockCount;
void* ui;void* menus[2][6];void* tips[2][3];void* windows[5];void* managers[3];void* globals[2];void* root;
detour::Set* conversionPatch;detour::Set* constructorPatch;detour::Set* destructorPatch;
const unsigned menuSlots[]={0x4d8,0x4f0,0x4f8,0x500,0x508,0x4e8};
const unsigned hoverOffsets[]={0x1020,0x3438,0xf0,0x190,0x3408,0x1370};
const unsigned menuSizes[]={0x1040,0x3440,0x110,0x1b0,0x3420,0x1390};
void require(bool ok){if(!ok)_exit(90);}
void check(bool ok){if(!ok)++state->errors;}
void number(unsigned n){capture->add(&n,sizeof(n));}
void pointer(const void* p){capture->addPointer(p);}
Block& block(void* p){for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p)return blocks[i];require(false);return blocks[0];}
template<class T>T expected(void* p,unsigned offset){T v;std::memcpy(&v,block(p).expected+offset,sizeof(v));return v;}
template<class T>void model(void* p,unsigned offset,T v){Block& b=block(p);require(offset+sizeof(v)<=b.size);std::memcpy(b.expected+offset,&v,sizeof(v));}
template<class T>void change(void* p,unsigned offset,T v){model(p,offset,v);std::memcpy(static_cast<unsigned char*>(p)+offset,&v,sizeof(v));}
void* guarded(unsigned n,unsigned fill){require(blockCount<MaxBlocks&&n<=MaxSize);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(n+32));require(p!=0);
 std::memset(p,0xad,16);std::memset(p+16,fill,n);std::memset(p+16+n,0x5e,16);
 Block& b=blocks[blockCount++];b.p=p+16;b.size=n;std::memcpy(b.expected,b.p,n);return b.p;}
void checkState(){for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];check(!std::memcmp(b.p,b.expected,b.size));
 for(unsigned j=0;j<16;++j)check(b.p[int(j)-16]==0xad&&b.p[b.size+j]==0x5e);}
 check(state->tip==state->wantedTip&&state->sharedTip==state->wantedTip);}
void references(){if(state->tip.empty())return;const std::wstring& s=state->tip;int refs;std::memcpy(&refs,reinterpret_cast<const char*>(s.data())-8,4);
 // All three surviving owners deliberately share one real COW representation.
 check(s.data()==state->sharedTip.data()&&s.data()==state->wantedTip.data());check(refs==2);number(refs);}
void utf8Released(){if(!state->converted||state->utf8Witness.empty())return;int refs;
 std::memcpy(&refs,state->utf8Witness.data()-8,4);check(refs==0);number(refs);}
void modelReset(){for(unsigned i=0;i<6;++i)model(expected<void*>(ui,menuSlots[i]),hoverOffsets[i],static_cast<void*>(0));
 for(unsigned i=0;i<3;++i)model(expected<void*>(ui,0x4a0+8*i),0x10,static_cast<long long>(-1));}
void boundary(unsigned tag){
 // These writes are owed by the tested entry, never performed by the hook.
 if(tag==Add||tag==Remove)modelReset();
 if(tag==Root)model(managers[1],0xc0,static_cast<unsigned char>(1));
 ++state->step;++state->total;number(tag);number(state->step);require(state->step<=20);
 check(state->step<=state->count&&state->plan[state->step-1]==tag);checkState();
}
void fault(unsigned tag){if(state->activeFault==tag){++state->hits;throw Injected(tag);}}
void setMenus(unsigned set){for(unsigned i=0;i<6;++i)change(ui,menuSlots[i],menus[set][current->alias?0:i]);
 for(unsigned i=0;i<3;++i)change(ui,0x4a0+8*i,tips[set][current->alias?0:i]);}
void* manager(){unsigned tag=state->managerCalls==0?InitialManager:state->managerCalls==1?PreManager:PostManager;
 boundary(tag);require(state->managerCalls<3);unsigned i=state->managerCalls==0?0:state->managerCalls==1?1:state->nextPost;
 ++state->managerCalls;number(i);pointer(managers[i]);
 if(tag==PreManager){check(!state->constructed);utf8Released();references();}
 fault(tag);return managers[i];}
bool membership(void* parent,const void* child){boundary(Membership);pointer(parent);pointer(child);
 check(parent==expected<void*>(ui,0x470)&&child==expected<void*>(ui,0x478));
 bool result=state->present;
 if(current->mutation&MembershipReload){change(ui,0x470,windows[1]);change(ui,0x478,windows[3]);setMenus(1);}
 fault(Membership);return result;}
void add(void* parent,void* child){boundary(Add);pointer(parent);pointer(child);
 check(parent==expected<void*>(ui,0x470)&&child==expected<void*>(ui,0x478));check(!state->present);
 if(current->mutation&AddReload){change(ui,0x480,windows[1]);state->globalsIndex=1;}
 fault(Add);state->present=true;}
void remove(void* parent,void* child){boundary(Remove);pointer(parent);pointer(child);
 check(parent==expected<void*>(ui,0x470)&&child==expected<void*>(ui,0x478));check(state->present);
 fault(Remove);state->present=false;}
void* getGlobals(){boundary(Globals);pointer(globals[state->globalsIndex]);fault(Globals);return globals[state->globalsIndex];}
const std::wstring& randomTip(void* self){boundary(RandomTip);pointer(self);check(self==globals[state->globalsIndex]);references();
 if(current->mutation&RandomReload)change(ui,0x480,windows[2]);fault(RandomTip);return state->tip;}
const std::wstring& forbiddenContext(void* self,EContextTip tip){boundary(RandomTip);pointer(self);number(99);number(static_cast<unsigned>(tip));check(false);return state->tip;}
std::string convert(const std::wstring& value){boundary(Convert);check(&value==&state->tip);capture->addText(value);references();
 if(current->mutation&ConvertReload)change(ui,0x480,windows[3]);fault(Convert);
 conversionPatch->restore();require(!conversionPatch->failed());
 // Execute the original conversion, not a fake encoder or a supplied string.
 std::string result=realConvert(value);
 TL_REDIRECT(*conversionPatch,convertBoundary,&convert);require(!conversionPatch->failed());
 check(result==state->wantedUTF8);capture->addText(result);state->utf8Witness=result;state->converted=true;return result;}
void* failConstructorAllocation(size_t n){number(ConstructorAllocation);number(static_cast<unsigned>(n));++state->ctorAllocations;++state->hits;throw std::bad_alloc();}
// Pinned libCEGUIBase.so.1: grow is at 0x105670; its call at +0x68
// targets _Znam@plt (0xbf378), whose jump slot is 0x43e8f8. Those
// addresses document the evidence, not runtime locators. Resolve the owning
// loaded DSO and its unique ELF _Znam relocation before editing one data pointer. This is necessary because the game's _Znam PLT is not
// the library's allocator boundary. No code bytes or global allocator change.
struct AllocationRelocation { uintptr_t base;void** slot;bool found; };
int findAllocationRelocation(struct dl_phdr_info* info,size_t,void* raw){
 AllocationRelocation* wanted=static_cast<AllocationRelocation*>(raw);if(info->dlpi_addr!=wanted->base)return 0;
 const ElfW(Dyn)* dynamic=0;for(unsigned i=0;i<info->dlpi_phnum;++i)if(info->dlpi_phdr[i].p_type==PT_DYNAMIC)
  dynamic=reinterpret_cast<const ElfW(Dyn)*>(info->dlpi_addr+info->dlpi_phdr[i].p_vaddr);
 require(dynamic!=0);uintptr_t strings=0,symbols=0,relocations=0;size_t bytes=0;unsigned kind=0;
 for(const ElfW(Dyn)* d=dynamic;d->d_tag!=DT_NULL;++d){
  if(d->d_tag==DT_STRTAB)strings=d->d_un.d_ptr;
  if(d->d_tag==DT_SYMTAB)symbols=d->d_un.d_ptr;
  if(d->d_tag==DT_JMPREL)relocations=d->d_un.d_ptr;
  if(d->d_tag==DT_PLTRELSZ)bytes=d->d_un.d_val;
  if(d->d_tag==DT_PLTREL)kind=d->d_un.d_val;
 }
 require(strings&&symbols&&relocations&&kind==DT_RELA&&bytes%sizeof(ElfW(Rela))==0);
 // glibc exposes relocated DT pointers; tolerate only the equivalent relative
 // representation when it is below this object's load bias.
 if(strings<wanted->base)strings+=wanted->base;if(symbols<wanted->base)symbols+=wanted->base;if(relocations<wanted->base)relocations+=wanted->base;
 const ElfW(Sym)* sym=reinterpret_cast<const ElfW(Sym)*>(symbols);const ElfW(Rela)* rel=reinterpret_cast<const ElfW(Rela)*>(relocations);
 for(unsigned i=0;i<bytes/sizeof(*rel);++i){const char* name=reinterpret_cast<const char*>(strings)+sym[ELF64_R_SYM(rel[i].r_info)].st_name;
  if(!std::strcmp(name,"_Znam")){require(ELF64_R_TYPE(rel[i].r_info)==R_X86_64_JUMP_SLOT);
   require(!wanted->found);wanted->slot=reinterpret_cast<void**>(wanted->base+rel[i].r_offset);wanted->found=true;}}
 return 1;
}
class GrowAllocationFault {
 void* handle;void** slot;void* saved;void* page;size_t pageSize;int protection;
 GrowAllocationFault(const GrowAllocationFault&);GrowAllocationFault& operator=(const GrowAllocationFault&);
public:
 GrowAllocationFault():handle(0),slot(0),saved(0),page(0),pageSize(0),protection(0){
  handle=dlopen("libCEGUIBase.so.1",RTLD_LAZY|RTLD_NOLOAD);require(handle!=0);
  unsigned char* actualGrow=static_cast<unsigned char*>(dlsym(handle,"_ZN5CEGUI6String4growEm"));
  void* allocator=dlsym(handle,"_Znam");require(actualGrow&&allocator);
  Dl_info identity;require(dladdr(actualGrow,&identity)!=0&&identity.dli_sname&&
   !std::strcmp(identity.dli_sname,"_ZN5CEGUI6String4growEm")&&identity.dli_fname&&std::strstr(identity.dli_fname,"libCEGUIBase"));
  require(identity.dli_saddr==actualGrow);const uintptr_t base=reinterpret_cast<uintptr_t>(identity.dli_fbase);
  AllocationRelocation relocation={base,0,false};dl_iterate_phdr(&findAllocationRelocation,&relocation);require(relocation.found&&relocation.slot);slot=relocation.slot;
  saved=*slot;
  if(saved!=allocator){
   // A lazy PLT slot must point to this object's push/jump resolver stub and
   // the preceding RIP-relative indirect jump must refer to this exact slot.
   // Do not force resolution: preserve the exact prior lazy-binding state.
   Dl_info lazy;require(dladdr(saved,&lazy)!=0&&lazy.dli_fbase==identity.dli_fbase);
   const unsigned char* stub=static_cast<const unsigned char*>(saved);require(stub[0]==0x68&&stub[5]==0xe9&&stub[-6]==0xff&&stub[-5]==0x25);
   int32_t displacement;std::memcpy(&displacement,stub-4,4);require(reinterpret_cast<const void*>(stub+displacement)==slot);
  }
  pageSize=static_cast<size_t>(sysconf(_SC_PAGESIZE));require(pageSize&&!(pageSize&(pageSize-1)));
  const uintptr_t address=reinterpret_cast<uintptr_t>(slot);page=reinterpret_cast<void*>(address&~(pageSize-1));
  require(address+sizeof(void*)<=reinterpret_cast<uintptr_t>(page)+pageSize);
  FILE* maps=std::fopen("/proc/self/maps","r");require(maps!=0);char line[512];bool found=false;
  while(std::fgets(line,sizeof(line),maps)){unsigned long lo,hi;char perms[5];
   if(std::sscanf(line,"%lx-%lx %4s",&lo,&hi,perms)==3&&lo<=address&&address+sizeof(void*)<=hi){
    protection=(perms[0]=='r'?PROT_READ:0)|(perms[1]=='w'?PROT_WRITE:0)|(perms[2]=='x'?PROT_EXEC:0);found=true;break;}}
  std::fclose(maps);require(found&&(protection&PROT_READ));
  require(mprotect(page,pageSize,protection|PROT_WRITE)==0);*slot=reinterpret_cast<void*>(&failConstructorAllocation);
  require(mprotect(page,pageSize,protection)==0);
 }
 ~GrowAllocationFault(){require(mprotect(page,pageSize,protection|PROT_WRITE)==0);*slot=saved;
  require(mprotect(page,pageSize,protection)==0);require(*slot==saved);require(dlclose(handle)==0);}
};
bool grow(CEGUI::String* self,size_t length){boundary(Constructor);check(!state->constructed);check(state->converted);
 const std::wstring& tip=state->tip;unsigned wanted=0;while(wanted<tip.size()&&tip[wanted])++wanted;
 check(length==wanted);number(static_cast<unsigned>(length));
 constructorPatch->restore();require(!constructorPatch->failed());bool result=false;
 try{
  if(state->activeFault==ConstructorAllocation){GrowAllocationFault allocation;result=realGrow(self,length);}
  else result=realGrow(self,length);
 }catch(...){char* site=reinterpret_cast<char*>(&realGrow);constructorPatch->redirect(site,site,&grow);require(!constructorPatch->failed());throw;}
 char* site=reinterpret_cast<char*>(&realGrow);constructorPatch->redirect(site,site,&grow);require(!constructorPatch->failed());
 state->temporary=self;state->constructed=true;return result;}
void text(void* window,const CEGUI::String& value){boundary(Text);pointer(window);check(window==expected<void*>(ui,0x480));
 check(state->constructed&&&value==state->temporary);const std::wstring& tip=state->tip;unsigned length=0;while(length<tip.size()&&tip[length])++length;
 number(value.length());check(value.length()==length);require(value.length()<4096);
 for(unsigned i=0;i<value.length();++i){number(value[i]);check(i<length&&value[i]==static_cast<unsigned>(tip[i]));}
 fault(Text);}
void destroy(CEGUI::String* value){boundary(Destructor);check(state->constructed&&state->temporary==value);
 destructorPatch->restore();require(!destructorPatch->failed());realDestructor(value);
 char* site=reinterpret_cast<char*>(&realDestructor);destructorPatch->redirect(site,site,&destroy);require(!destructorPatch->failed());
 state->constructed=false;state->temporary=0;}
void* getRoot(){boundary(Root);check(!state->constructed);utf8Released();
 if(current->mutation&RootReload)state->nextPost=0;fault(Root);return root;}
bool render(void* self){boundary(Render);pointer(self);check(self==root);check(!state->constructed);utf8Released();
 if(current->mutation&RenderReload)state->nextPost=2;fault(Render);return current->renderResult;}
std::wstring makeTip(unsigned n){switch(n){case 0:return L"";case 1:return L"Loading a new world";case 2:return L"\u0416\u03a9\u4e2d\u2603";
 case 3:return std::wstring(L"A\0B\u4e2d",4);case 4:return std::wstring(767,L'Q')+L"\u4e2d";case 5:return std::wstring(1,L'\0');
 default:return L"[colour] \t\n \u00e9 /tips/world";}}
// Independent BMP encoding oracle; never calls the target converter or SDK.
std::string encode(const std::wstring& s){std::string r;for(unsigned i=0;i<s.size();++i){unsigned v=s[i];require(v<0x10000);
 if(v<0x80)r+=static_cast<char>(v);else if(v<0x800){r+=static_cast<char>(0xc0|(v>>6));r+=static_cast<char>(0x80|(v&63));}
 else{r+=static_cast<char>(0xe0|(v>>12));r+=static_cast<char>(0x80|((v>>6)&63));r+=static_cast<char>(0x80|(v&63));}}return r;}
void setup(){autotest::g_arenaUsed=0;blockCount=0;require(sizeof(std::wstring)==8&&sizeof(CEGUI::String)==0xb0);
 ui=guarded(UISize,current->pattern?0xa5:0x5a);
 for(unsigned s=0;s<2;++s){for(unsigned i=0;i<6;++i)menus[s][i]=guarded(current->alias&&i==0?MaxSize:menuSizes[i],0x30+12*s+i);
 for(unsigned i=0;i<3;++i)tips[s][i]=guarded(0x40,0x81+4*s+i);}
 for(unsigned i=0;i<5;++i)windows[i]=guarded(0x80,0x61+i);
 for(unsigned i=0;i<3;++i){managers[i]=guarded(0x190,0x91+i);change(managers[i],0xc0,static_cast<unsigned char>(0x51+i));change(managers[i],0xc1,static_cast<unsigned char>(i?0:current->gate));}
 for(unsigned i=0;i<2;++i)globals[i]=guarded(0x40,0xb1+i);root=guarded(0x40,0xc3);
 change(ui,0x470,current->gate?windows[0]:static_cast<void*>(0));change(ui,0x478,current->gate?windows[2]:static_cast<void*>(0));
 change(ui,0x480,current->gate?windows[4]:static_cast<void*>(0));setMenus(0);
 if(!current->gate){for(unsigned i=0;i<6;++i)change(ui,menuSlots[i],static_cast<void*>(0));for(unsigned i=0;i<3;++i)change(ui,0x4a0+8*i,static_cast<void*>(0));}
 state->tip=makeTip(current->text);state->sharedTip=state->tip;state->wantedTip=state->tip;state->wantedUTF8=encode(state->tip);state->present=current->present;
}
void push(unsigned tag){require(state->count<20);state->plan[state->count++]=tag;}
void prepare(unsigned iteration,bool recovery){state->iteration=iteration;state->step=state->managerCalls=state->count=0;state->returned=false;
 state->activeFault=recovery?0:current->fault;state->nextPost=2;state->globalsIndex=0;state->converted=false;state->utf8Witness.clear();state->constructed=false;state->temporary=0;
 state->show=current->repeat==4?(iteration<2):current->show;
 // Reseed between calls: a repeated show must preserve nonzero hover state.
 if(iteration&&current->gate){for(unsigned s=0;s<2;++s){for(unsigned i=0;i<6;++i)change(menus[s][current->alias?0:i],hoverOffsets[i],static_cast<unsigned long long>(0xdead0000u+iteration*32+i));
 for(unsigned i=0;i<3;++i)change(tips[s][current->alias?0:i],0x10,static_cast<long long>(700+iteration*4+i));}}
 push(InitialManager);
 if(current->gate){push(Membership);if(state->show&&!state->present){push(Add);push(Globals);push(RandomTip);push(Convert);push(Constructor);push(Text);push(Destructor);}
 else if(!state->show&&state->present)push(Remove);
 if(state->show){push(PreManager);push(Root);push(Render);push(PostManager);}}
 if(state->activeFault){unsigned target=state->activeFault==ConstructorAllocation?Constructor:state->activeFault;unsigned stop=0;
 for(unsigned i=0;i<state->count;++i)if(state->plan[i]==target){stop=i+1;break;}require(stop!=0);state->count=stop;
 if(state->activeFault==Text)push(Destructor);}
 checkState();references();}
struct InvocationWitness{~InvocationWitness(){if(!state->returned)++state->unwinds;}};
void invoke(void(*fn)(CGameUI*,bool),bool recovery){unsigned before=state->catches;bool caught=false;
 try{InvocationWitness witness;fn(static_cast<CGameUI*>(ui),state->show);state->returned=true;}
 catch(const Injected& e){check(e.tag==state->activeFault);++state->catches;caught=true;}
 catch(const std::bad_alloc&){check(state->activeFault==ConstructorAllocation);++state->catches;caught=true;}
 catch(...){_exit(91);}
 check(caught==bool(state->activeFault));check(state->catches==before+unsigned(caught));check(state->step==state->count);
 // A post-provider throw leaves the pre-render flag set. Successful post-fetch
 // clears the freshly returned object, which may differ from the initial one.
 if(!caught&&current->gate&&state->show)model(managers[state->nextPost],0xc0,static_cast<unsigned char>(0));
 checkState();check(!state->constructed);utf8Released();references();number(caught);number(recovery);number(state->present);
}
void snapshot(){checkState();for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];pointer(b.p);number(b.size);capture->add(b.p-16,b.size+32);}
 capture->addText(state->tip);number(state->total);number(state->ctorAllocations);}
void side(void* raw,autotest::Capture& out,bool ours){current=static_cast<Case*>(raw);capture=&out;unsigned trailer[5]={0x4c4f4144u,0,0,0,0};
 {State local;state=&local;setup();detour::Set d,cv,ct,dt;conversionPatch=&cv;constructorPatch=&ct;destructorPatch=&dt;
 TL_REDIRECT(d,managerBoundary,&manager);TL_REDIRECT(d,globalsBoundary,&getGlobals);TL_REDIRECT(d,randomBoundary,&randomTip);TL_REDIRECT(d,contextBoundary,&forbiddenContext);
 d.redirect(isChildBoundary,isChildBoundary,&membership);d.redirect(addBoundary,addBoundary,&add);d.redirect(removeBoundary,removeBoundary,&remove);
 d.redirect(textBoundary,textBoundary,&text);d.redirect(rootBoundary,rootBoundary,&getRoot);d.redirect(renderBoundary,renderBoundary,&render);
 TL_REDIRECT(cv,convertBoundary,&convert);char* growSite=reinterpret_cast<char*>(&realGrow);ct.redirect(growSite,growSite,&grow);
 char* destructorSite=reinterpret_cast<char*>(&realDestructor);dt.redirect(destructorSite,destructorSite,&destroy);
 require(!d.failed()&&!cv.failed()&&!ct.failed()&&!dt.failed());
 void(*fn)(CGameUI*,bool)=ours?&candidateLoading:&originalLoading;require(autotest::beginInvocation(out,fn));
 for(unsigned i=0;i<current->repeat;++i){prepare(i,false);invoke(fn,false);if(current->fault)break;}
 // Reuse retained state after every injected fault; a successful retry is
 // supplemental evidence, never allowed to mark the throwing entry completed.
 if(current->fault){prepare(1,true);invoke(fn,true);}
 else if(!state->catches)out.callCompleted=1;
 snapshot();check(state->ctorAllocations==unsigned(current->fault==ConstructorAllocation));check(state->hits==unsigned(current->fault!=0));check(state->catches==unsigned(current->fault!=0));check(state->unwinds==unsigned(current->fault!=0));
 trailer[1]=state->errors;trailer[2]=state->hits;trailer[3]=state->catches;trailer[4]=state->unwinds;
 dt.restore();ct.restore();cv.restore();d.restore();require(!d.failed()&&!cv.failed()&&!ct.failed()&&!dt.failed());
 }out.addHeapInUse();out.add(trailer,sizeof(trailer));}
void originalSide(void* p,autotest::Capture& out){side(p,out,false);}void candidateSide(void* p,autotest::Capture& out){side(p,out,true);}
bool witness(const autotest::Outcome& o,bool fault){unsigned t[5];if(o.capture.length<sizeof(t))return false;std::memcpy(t,o.capture.data+o.capture.length-sizeof(t),sizeof(t));
 return t[0]==0x4c4f4144u&&!t[1]&&t[2]==unsigned(fault)&&t[3]==unsigned(fault)&&t[4]==unsigned(fault);}
void diagnostic(const tlhybrid_host* host,unsigned i,const Case& c,const autotest::Outcome& a,const autotest::Outcome& b){size_t first=0;
 while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
 unsigned aw[5]={0},bw[5]={0};if(a.capture.length>=sizeof(aw))std::memcpy(aw,a.capture.data+a.capture.length-sizeof(aw),sizeof(aw));if(b.capture.length>=sizeof(bw))std::memcpy(bw,b.capture.data+b.capture.length-sizeof(bw),sizeof(bw));
 host->log("    loading case %u gate %u show/present %u/%u text %u mutation %u fault %u repeat %u: exits %d/%d issues %u/%u completed %u/%u errors %u/%u lengths %u/%u first %u\n",
 i,c.gate,unsigned(c.show),unsigned(c.present),c.text,c.mutation,c.fault,c.repeat,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,
 a.capture.callCompleted,b.capture.callCompleted,aw[1],bw[1],unsigned(a.capture.length),unsigned(b.capture.length),unsigned(first));}
}

TL_TEST(gameui_loading_visible){std::vector<Case> cases,faults;const unsigned gates[]={0,1,2,255};
 for(unsigned g=0;g<4;++g)for(unsigned show=0;show<2;++show)for(unsigned present=0;present<2;++present)for(unsigned result=0;result<2;++result){
 Case c;c.gate=gates[g];c.show=show;c.present=present;c.renderResult=result;c.pattern=result;cases.push_back(c);}
 for(unsigned t=0;t<7;++t)for(unsigned m=0;m<64;++m){Case c;c.text=t;c.mutation=m;c.renderResult=(m&1)!=0;c.pattern=m&1;cases.push_back(c);}
 for(unsigned m=0;m<64;++m)for(unsigned show=0;show<2;++show){Case c;c.mutation=m;c.show=show;c.present=true;c.alias=(m&1);cases.push_back(c);}
 for(unsigned m=0;m<64;++m){Case c;c.mutation=m;c.repeat=4;c.text=m%7;c.alias=(m&1);cases.push_back(c);}
 for(unsigned tag=InitialManager;tag<=PostManager;++tag){if(tag==Constructor||tag==Destructor)continue;
 for(unsigned t=0;t<7;++t){Case c;c.fault=tag;c.text=t;c.mutation=63;c.renderResult=(t&1)!=0;
 if(tag==Remove){c.show=false;c.present=true;}faults.push_back(c);}}
 {Case c;c.text=4;c.fault=ConstructorAllocation;c.mutation=63;faults.push_back(c);}
 const uint64_t address=(uint64_t)(uintptr_t)&originalLoading;autotest::Coverage coverage("gameui_loading_visible",address);
 for(unsigned i=0;i<cases.size();++i){Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
 if(coverage.observe(host,a,b)||!witness(a,false)||!witness(b,false)){diagnostic(host,i,c,a,b);coverage.report(host);return 1;}}
 coverage.report(host);if(coverage.completed!=cases.size())return 1;
 for(unsigned i=0;i<faults.size();++i){Case c=faults[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
 bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&
 !a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==address&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&
 host->comparison_pair(address,b.capture.callTarget)&&witness(a,true)&&witness(b,true)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!ok){diagnostic(host,i,c,a,b);return 1;}}
 host->log("    loading: %u expected exception prefixes plus retained-state retries, excluded from normal acceptance; ASCII/BMP only (known original non-BMP tail quirk)\n",unsigned(faults.size()));return 0;
}
// Parent-run negative controls: cache initial manager for both writes; skip frame
// on repeated show; replace random tip with context tip or query random twice;
// cache root/menu/text before callbacks; clear render flag with an unwind guard.
// Restore the exact candidate and rerun positives after every mutation batch.
