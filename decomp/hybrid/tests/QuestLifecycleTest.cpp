// Independent CQuest slice-A lifetime oracle, GCC 4.4 COW ABI / C++98.
// Original parser/reset/save/load are NOT accepted by this fixture. All owned
// children below have genuine original constructors, vtables and destructors.
// No world/resource doubles, fabricated child vtables, or suppressed frees.
// Original D1 LSDA 11dc909: unregister d1a447..d1a44c -> d1b380;
// d1a49e..d1aef6 -> d1b2f4; base destruction and Resume have no cleanup.
// Constructor cleanup probes and real allocator failures are separate from
// completed-call coverage. No deallocator or string destructor throws.
#include <cstddef>
#include <cstring>
#include <new>
#include <string>
#include <dlfcn.h>
#include "Quest.h"
#include "AutoTest.h"
#include "Detour.h"

#define QL_PAIR(N,A,S) TL_ORIGINAL(void,qlOld##N,A,S) extern "C" void qlNew##N A __asm__(S);
QL_PAIR(C1,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
QL_PAIR(C2,(void*,void*,void*),"_ZN6CQuestC2EP16CResourceManagerP13CQuestManager")
QL_PAIR(D1,(void*),"_ZN6CQuestD1Ev")
QL_PAIR(D2,(void*),"_ZN6CQuestD2Ev")
QL_PAIR(D0,(void*),"_ZN6CQuestD0Ev")
#undef QL_PAIR
TL_ORIGINAL(void,qlDialogCtor,(void*,void*),"_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void,qlRewardCtor,(void*,void*),"_ZN13CQuestRewardsC1EP6CQuest")
TL_ORIGINAL(void,qlUnitCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qlControllerCtor,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
TL_ORIGINAL(void,qlControllerDtor,(void*),"_ZN16CQuestControllerD1Ev")
TL_FUNCTION(qlUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qlGuid,"_ZN9UTILITIES16createUniqueGuidEv")
TL_ORIGINAL(void,qlCoreCtor,(void*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(unsigned,qlAddSafe,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qlReqCtor,"_ZN18CQuestRequirementsC1EP6CQuest")
TL_FUNCTION(qlCoreDtor,"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(qlRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qlDialogD0,"_ZN12CQuestDialogD0Ev")
TL_FUNCTION(qlDialogD1,"_ZN12CQuestDialogD1Ev")
TL_FUNCTION(qlRewardD0,"_ZN13CQuestRewardsD0Ev")
TL_FUNCTION(qlRewardD1,"_ZN13CQuestRewardsD1Ev")
TL_FUNCTION(qlUnitD0,"_ZN14CQuestUnitDataD0Ev")
TL_FUNCTION(qlUnitD1,"_ZN14CQuestUnitDataD1Ev")
TL_FUNCTION(qlReqD0,"_ZN18CQuestRequirementsD0Ev")
TL_FUNCTION(qlReqD1,"_ZN18CQuestRequirementsD1Ev")
extern "C" char qlAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qlFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qlArrayNew[] __asm__("_Znam");
extern "C" char qlArrayDelete[] __asm__("_ZdaPv");
extern "C" char qlScalarNew[] __asm__("_Znwm");
extern "C" char qlScalarDelete[] __asm__("_ZdlPv");
extern "C" char qlCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qlRepDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char qlStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
namespace quest_lifetime {
typedef std::wstring Wide;
typedef TArrayList<void*> Pointers;
typedef TArrayList<Wide> Strings;
typedef TArrayList<bool> Flags;
typedef char ABI[sizeof(CQuest)==0x218 && sizeof(Wide)==8 && sizeof(Pointers)==24?1:-1];
template<class T>T& at(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
struct Stop { unsigned site; explicit Stop(unsigned s):site(s){} };
// kind=0 constructor, 1 teardown. alias=C1/C2 or D1/D2/D0/virtual D0.
// text=0 normal empty source; 1 shared, 2 leaked source boundary.
// faults=1..4 copy boundary; 11..14 real new failure within leaked copy;
// 20 requirements outer allocation; 21..23 nested Ogre allocation;
// 24..26 nested new[]; 40 real listener unregister boundary.
struct Case {unsigned kind,alias,shape,text,fault,constructor;};
struct Block {void* p;unsigned id,allocator,frees,bases,deletes;};
struct Weak {void* p;unsigned index,pad;};
struct StringWitness {Wide* keeper;void* rep;unsigned id,freed;};
static const Case* cs;static autotest::Capture* cap;static const tlhybrid_host* context;
static void *owner,*resource,*manager,*requirements,*controller;
static Weak witness,listenerWitness;static void* listener;
static Block blocks[256];static unsigned blockCount;
static StringWitness strings[160];static unsigned stringCount;
static unsigned errors,events[2048],eventCount,baseCalls,copyCalls,copySuccess;
static unsigned faultHits,ogreCalls,arrayCalls,reqBaseCalls,outerFrees;
static unsigned expectedChildren,expectedUnits,expectedGroups,childCalls,unitCalls,groupFrees,virtualCalls;
static bool virtualCandidate;static detour::Set* virtualPatch;
static bool tracking,constructing,insideCopy,reqActive;
static unsigned copyStage;
static Wide* source;static Wide* ctorKeep[4];
static void* forwardedRep;
static detour::Set *allocPatch,*freePatch,*arrayNewPatch,*arrayDeletePatch,*scalarNewPatch,*scalarDeletePatch;
static detour::Set *copyPatch,*corePatch,*reqPatch,*safePatch,*repPatch,*stringPatch;
static detour::Set *dialogPatch,*rewardPatch,*unitPatch,*requirementsPatch;
static void number(unsigned n){cap->add(&n,sizeof(n));}
static void need(bool yes,unsigned site){if(!yes){++errors;number(0xf3000000u+site);}}
static void event(unsigned e){need(eventCount<2048,1);if(eventCount<2048)events[eventCount++]=e;number(e);}
static void* raw(unsigned bytes){void* p=autotest::allocate(bytes);if(!p)_exit(71);return p;}
static int refs(const Wide& s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);}
static void* rep(const Wide& s){return const_cast<char*>(reinterpret_cast<const char*>(s.c_str())-24);}
static Block* block(void* p){Block* found=0;for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p){found=&blocks[i];if(!found->frees)return found;}return found;}
static void remember(void* p,unsigned id,unsigned allocator){
 if(!p)return;need((!block(p)||block(p)->frees)&&blockCount<256,2);if(blockCount<256){Block& b=blocks[blockCount++];b.p=p;b.id=id;b.allocator=allocator;b.frees=b.bases=b.deletes=0;}
}
static void* ogre(unsigned size){return reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qlAlloc)(size,0,0,0);}
static void freeOgre(void* p){reinterpret_cast<void(*)(void*)>(qlFree)(p);}
static void init(){
 errors=eventCount=blockCount=stringCount=baseCalls=copyCalls=copySuccess=faultHits=ogreCalls=arrayCalls=reqBaseCalls=outerFrees=0;
 expectedChildren=expectedUnits=expectedGroups=childCalls=unitCalls=groupFrees=virtualCalls=0;tracking=constructing=insideCopy=reqActive=false;copyStage=0;requirements=controller=listener=forwardedRep=0;
 std::memset(ctorKeep,0,sizeof(ctorKeep));std::memset(&witness,0,sizeof(witness));std::memset(&listenerWitness,0,sizeof(listenerWitness));
 autotest::g_arenaUsed=0;
 const uintptr_t cells[]={0x14f9fe8,0x151d408,0x14fb488,0x14ff1a8,0x151c128,0x151ab48};
 for(unsigned i=0;i<6;++i)new(reinterpret_cast<void*>(cells[i]))Wide();
 *reinterpret_cast<unsigned*>(0x1500730)=17;
 resource=raw(16);manager=raw(16);
 if(!cs->kind){if(cs->constructor&1)resource=0;if(cs->constructor&2)manager=0;}
 source=new(raw(sizeof(Wide)))Wide(cs->text?L"Quest lifetime \u03a9 \u732b source":L"");
 if(cs->text==2)(*source)[0]=source->c_str()[0];
 owner=ogre(0x218);std::memset(owner,cs->shape&1?0xa5:0x5a,0x218);
}
static bool mapped(uintptr_t a,uintptr_t b){return a==b||(context->comparison_pair&&context->comparison_pair(a,b));}
static void vtable(bool candidate){
 uintptr_t* v=at<uintptr_t*>(owner,0);need(v&&reinterpret_cast<std::ptrdiff_t*>(v)[-2]==0,3);
 if(v){uintptr_t* old=reinterpret_cast<uintptr_t*>(0xff7170);for(unsigned i=0;i<2;++i)need(candidate?mapped(old[i],v[i]):old[i]==v[i],4+i);
  need(reinterpret_cast<const char* const*>(v[-1])[1]!=0,6);}
}
static void aliveStrings(unsigned site){
 for(unsigned i=0;i<stringCount;++i)if(strings[i].keeper&&(!cs->fault||strings[i].id<100))need(refs(*strings[i].keeper)==0,site+i);
}
static void core(void* self){
 if(tracking){
  if(self==owner){++baseCalls;event(9000);need(!at<long long>(owner,0x10),7);
   for(unsigned i=0;i<4;++i)if(ctorKeep[i])need(refs(*ctorKeep[i])==(cs->text==1?static_cast<int>(copySuccess):0),8+i);
   if(!constructing){aliveStrings(100);need(at<void*>(owner,0x1d0)==(cs->fault?manager:0),261);}
   if(!constructing&&!cs->fault){need(childCalls==expectedChildren,12);need(groupFrees==expectedGroups,13);}
   if(!constructing)need(witness.p==owner,14);
  }else if(constructing&&self==requirements){++reqBaseCalls;event(9010);}
  else {Block* b=block(self);if(b){++b->bases;event(10000+b->id);need(b->bases==1,15);}}
 }
 corePatch->restore();reinterpret_cast<void(*)(void*)>(qlCoreDtor_original)(self);TL_REDIRECT(*corePatch,qlCoreDtor,&core);need(!corePatch->failed(),16);
 if(tracking&&self==owner&&!constructing)need(!witness.p&&witness.index==~0u,17);
}
static void reqCtor(void* self,void* q){
 if(tracking&&constructing){requirements=self;reqActive=true;event(9020);need(q==owner&&!at<void*>(owner,0x1e0),18);need(at<unsigned>(owner,0x108)==10&&at<unsigned>(owner,0x120)==10,250);}
 reqPatch->restore();
 try{reinterpret_cast<void(*)(void*,void*)>(qlReqCtor_original)(self,q);}
 catch(...){TL_REDIRECT(*reqPatch,qlReqCtor,&reqCtor);reqActive=false;throw;}
 TL_REDIRECT(*reqPatch,qlReqCtor,&reqCtor);reqActive=false;need(!reqPatch->failed(),19);
}
static void* allocate(size_t n,const char* file,int line,const char* fn){
 if(tracking&&constructing){++ogreCalls;event(1100+ogreCalls);
  unsigned target=ogreCalls==1?20:19+ogreCalls;
  if(cs->fault==target){++faultHits;throw Stop(target);}}
 allocPatch->restore();void* p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qlAlloc)(n,file,line,fn);
 allocPatch->redirect(qlAlloc,qlAlloc,&allocate);need(!allocPatch->failed(),20);
 if(tracking&&constructing)remember(p,400+ogreCalls,1);
 return p;
}
static void released(void* p,unsigned allocator){
 if(!tracking)return;Block* b=block(p);if(!b)return;
 ++b->frees;event(20000+b->id);need(b->frees==1&&b->allocator==allocator,21);
 if(b->id==1){++outerFrees;need(baseCalls==1&&(!witness.p),22);}
 if(!constructing&&b->id>=200&&b->id<230){++groupFrees;need(unitCalls==expectedUnits,23);}
 if(!constructing&&b->id==90)need(!at<void*>(p,0)&&at<unsigned>(p,8)==~0u,24);
}
static void release(void* p){released(p,1);freePatch->restore();reinterpret_cast<void(*)(void*)>(qlFree)(p);freePatch->redirect(qlFree,qlFree,&release);need(!freePatch->failed(),25);}
static void* arrayNew(size_t n){
 if(tracking&&constructing&&reqActive){++arrayCalls;event(1200+arrayCalls);if(cs->fault==23+arrayCalls){++faultHits;throw Stop(cs->fault);}}
 arrayNewPatch->restore();void* p=reinterpret_cast<void*(*)(size_t)>(qlArrayNew)(n);arrayNewPatch->redirect(qlArrayNew,qlArrayNew,&arrayNew);need(!arrayNewPatch->failed(),26);
 if(tracking&&constructing&&reqActive)remember(p,410+arrayCalls,2);
 return p;
}
static void arrayDelete(void* p){released(p,2);arrayDeletePatch->restore();reinterpret_cast<void(*)(void*)>(qlArrayDelete)(p);arrayDeletePatch->redirect(qlArrayDelete,qlArrayDelete,&arrayDelete);need(!arrayDeletePatch->failed(),27);}
static void* scalarNew(size_t n){
 if(tracking&&constructing&&insideCopy&&cs->fault==10+copyStage){++faultHits;throw Stop(cs->fault);}
 scalarNewPatch->restore();void* p=reinterpret_cast<void*(*)(size_t)>(qlScalarNew)(n);scalarNewPatch->redirect(qlScalarNew,qlScalarNew,&scalarNew);need(!scalarNewPatch->failed(),28);return p;
}
static void scalarDelete(void* p){released(p,3);scalarDeletePatch->restore();reinterpret_cast<void(*)(void*)>(qlScalarDelete)(p);scalarDeletePatch->redirect(qlScalarDelete,qlScalarDelete,&scalarDelete);need(!scalarDeletePatch->failed(),29);}
static void requireRelocation(bool valid){if(!valid){std::fprintf(stderr,"    Quest lifetime library allocation relocation unavailable\n");_exit(71);}}
struct WideAllocationRelocation {uintptr_t base;void** slot;bool found;};
static int findWideAllocation(struct dl_phdr_info* info,size_t,void* raw){
 WideAllocationRelocation* wanted=static_cast<WideAllocationRelocation*>(raw);if(info->dlpi_addr!=wanted->base)return 0;
 const ElfW(Dyn)* dynamic=0;
 for(unsigned i=0;i<info->dlpi_phnum;++i)if(info->dlpi_phdr[i].p_type==PT_DYNAMIC)dynamic=reinterpret_cast<const ElfW(Dyn)*>(info->dlpi_addr+info->dlpi_phdr[i].p_vaddr);
 requireRelocation(dynamic!=0);uintptr_t strings=0,symbols=0,relocations=0;size_t bytes=0;unsigned kind=0;
 for(const ElfW(Dyn)* d=dynamic;d->d_tag!=DT_NULL;++d){
  if(d->d_tag==DT_STRTAB)strings=d->d_un.d_ptr;if(d->d_tag==DT_SYMTAB)symbols=d->d_un.d_ptr;
  if(d->d_tag==DT_JMPREL)relocations=d->d_un.d_ptr;if(d->d_tag==DT_PLTRELSZ)bytes=d->d_un.d_val;if(d->d_tag==DT_PLTREL)kind=d->d_un.d_val;
 }
 requireRelocation(strings&&symbols&&relocations&&kind==DT_RELA&&bytes%sizeof(ElfW(Rela))==0);
 if(strings<wanted->base)strings+=wanted->base;if(symbols<wanted->base)symbols+=wanted->base;if(relocations<wanted->base)relocations+=wanted->base;
 const ElfW(Sym)* sym=reinterpret_cast<const ElfW(Sym)*>(symbols);const ElfW(Rela)* rel=reinterpret_cast<const ElfW(Rela)*>(relocations);
 for(unsigned i=0;i<bytes/sizeof(*rel);++i){const char* symbol=reinterpret_cast<const char*>(strings)+sym[ELF64_R_SYM(rel[i].r_info)].st_name;
  if(!std::strcmp(symbol,"_Znwm")){requireRelocation(ELF64_R_TYPE(rel[i].r_info)==R_X86_64_JUMP_SLOT&&!wanted->found);wanted->slot=reinterpret_cast<void**>(wanted->base+rel[i].r_offset);wanted->found=true;}}
 return 1;
}
static void* failWideAllocation(size_t size){
 need(insideCopy&&cs->fault==10+copyStage&&cs->text==2,73);need(refs(*source)<0,74);
 need(size>=24+(source->size()+1)*sizeof(wchar_t),75);++faultHits;throw Stop(cs->fault);
}
class WideAllocationFault {
 void* handle;void** slot;void* saved;void* page;size_t pageSize;int protection;
 WideAllocationFault(const WideAllocationFault&);WideAllocationFault& operator=(const WideAllocationFault&);
public:
 WideAllocationFault():handle(0),slot(0),saved(0),page(0),pageSize(0),protection(0){
  void* constructor=dlsym(RTLD_DEFAULT,"_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");Dl_info identity;
  requireRelocation(constructor&&dladdr(constructor,&identity)&&identity.dli_fname&&std::strstr(identity.dli_fname,"libstdc++")&&identity.dli_saddr==constructor);
  handle=dlopen(identity.dli_fname,RTLD_LAZY|RTLD_NOLOAD);requireRelocation(handle!=0);void* allocator=dlsym(handle,"_Znwm");requireRelocation(allocator!=0);
  WideAllocationRelocation relocation={reinterpret_cast<uintptr_t>(identity.dli_fbase),0,false};dl_iterate_phdr(&findWideAllocation,&relocation);
  requireRelocation(relocation.found&&relocation.slot);slot=relocation.slot;saved=*slot;
  if(saved!=allocator){
   Dl_info lazy;requireRelocation(dladdr(saved,&lazy)&&lazy.dli_fbase==identity.dli_fbase);const unsigned char* stub=static_cast<const unsigned char*>(saved);
   requireRelocation(stub[0]==0x68&&stub[5]==0xe9&&stub[-6]==0xff&&stub[-5]==0x25);int32_t offset;std::memcpy(&offset,stub-4,4);requireRelocation(reinterpret_cast<const void*>(stub+offset)==slot);
  }
  pageSize=static_cast<size_t>(sysconf(_SC_PAGESIZE));requireRelocation(pageSize&&!(pageSize&(pageSize-1)));
  uintptr_t address=reinterpret_cast<uintptr_t>(slot);page=reinterpret_cast<void*>(address&~(pageSize-1));requireRelocation(address+sizeof(void*)<=reinterpret_cast<uintptr_t>(page)+pageSize);
  FILE* maps=std::fopen("/proc/self/maps","r");requireRelocation(maps!=0);char line[512];bool found=false;
  while(std::fgets(line,sizeof(line),maps)){unsigned long lo,hi;char perms[5];
   if(std::sscanf(line,"%lx-%lx %4s",&lo,&hi,perms)==3&&lo<=address&&address+sizeof(void*)<=hi){protection=(perms[0]=='r'?PROT_READ:0)|(perms[1]=='w'?PROT_WRITE:0)|(perms[2]=='x'?PROT_EXEC:0);found=true;break;}}
  std::fclose(maps);requireRelocation(found&&(protection&PROT_READ));requireRelocation(!mprotect(page,pageSize,protection|PROT_WRITE));
  *slot=reinterpret_cast<void*>(&failWideAllocation);requireRelocation(!mprotect(page,pageSize,protection));
 }
 ~WideAllocationFault(){requireRelocation(!mprotect(page,pageSize,protection|PROT_WRITE));*slot=saved;requireRelocation(!mprotect(page,pageSize,protection));requireRelocation(*slot==saved);requireRelocation(!dlclose(handle));}
};

static void copy(Wide* dst,const Wide& src){
 unsigned stage=0;for(unsigned i=0;i<4;++i)if(dst==reinterpret_cast<Wide*>(static_cast<char*>(owner)+0x30+8*i))stage=i+1;
 bool observed=tracking&&constructing&&stage;
 if(observed){++copyCalls;copyStage=stage;event(1300+stage);need(copyCalls==stage,30);
  need(!at<long long>(owner,0x10)&&!at<int>(owner,0x18)&&at<int>(owner,0x1c)==-1&&!at<int>(owner,0x20),31);
  if(cs->fault==stage){++faultHits;throw Stop(stage);}}
 copyPatch->restore();insideCopy=observed;
 try{
  if(observed&&cs->fault==10+stage){WideAllocationFault allocation;reinterpret_cast<void(*)(Wide*,const Wide&)>(qlCopy)(dst,*source);}
  else reinterpret_cast<void(*)(Wide*,const Wide&)>(qlCopy)(dst,observed&&cs->text?*source:src);
 }
 catch(...){insideCopy=false;copyPatch->redirect(qlCopy,qlCopy,&copy);throw;}
 insideCopy=false;
 if(observed){++copySuccess;if(!dst->empty())ctorKeep[stage-1]=new(raw(sizeof(Wide)))Wide(*dst);}
 copyPatch->redirect(qlCopy,qlCopy,&copy);need(!copyPatch->failed(),32);
}
static void releaseRep(void* p){
 if(!tracking||constructing)return;
 for(unsigned i=0;i<stringCount;++i)if(!strings[i].keeper&&strings[i].rep==p){++strings[i].freed;event(40000+strings[i].id);need(strings[i].freed==1,33);}
}
static void repDestroy(void* p,const void* a){
 bool observe=p!=forwardedRep;repPatch->restore();reinterpret_cast<void(*)(void*,const void*)>(qlRepDestroy)(p,a);
 if(observe)releaseRep(p);repPatch->redirect(qlRepDestroy,qlRepDestroy,&repDestroy);need(!repPatch->failed(),34);
}
static void stringDtor(Wide* s){
 void* p=rep(*s);void* previous=forwardedRep;forwardedRep=p;
 // Only unique tracked reps are observed here. Shared keepers prove ref drops.
 stringPatch->restore();reinterpret_cast<void(*)(Wide*)>(qlStringDtor)(s);releaseRep(p);
 stringPatch->redirect(qlStringDtor,qlStringDtor,&stringDtor);forwardedRep=previous;need(!stringPatch->failed(),35);
}
static void child(void* p,unsigned family){
 if(tracking){Block* b=block(p);need(b!=0,36);if(b){++b->deletes;++childCalls;event(30000+b->id);need(b->deletes==1,37);}
  if(family==2)++unitCalls;}
}
static void dialog(void* p){child(p,0);dialogPatch->restore();reinterpret_cast<void(*)(void*)>(qlDialogD0_original)(p);TL_REDIRECT(*dialogPatch,qlDialogD0,&dialog);}
static void reward(void* p){child(p,1);rewardPatch->restore();reinterpret_cast<void(*)(void*)>(qlRewardD0_original)(p);TL_REDIRECT(*rewardPatch,qlRewardD0,&reward);}
static void unit(void* p){child(p,2);unitPatch->restore();reinterpret_cast<void(*)(void*)>(qlUnitD0_original)(p);TL_REDIRECT(*unitPatch,qlUnitD0,&unit);}
static void reqDelete(void* p){child(p,3);requirementsPatch->restore();reinterpret_cast<void(*)(void*)>(qlReqD0_original)(p);TL_REDIRECT(*requirementsPatch,qlReqD0,&reqDelete);}
static void removeSafe(void* p,void* w,unsigned index){
 if(tracking&&!constructing&&w==listener){event(8000);need(p==controller&&index==at<unsigned>(listener,8),38);
  if(cs->fault==40){++faultHits;throw Stop(40);}}
 safePatch->restore();reinterpret_cast<void(*)(void*,void*,unsigned)>(qlRemoveSafe_original)(p,w,index);TL_REDIRECT(*safePatch,qlRemoveSafe,&removeSafe);need(!safePatch->failed(),39);
}
static void pinOriginal(detour::Set& s,char* original,char* linked){if(linked!=original)s.redirect(linked,linked,original);}
static void* noUI(){return 0;}
static unsigned long long stableGuid(){return 0x8765432112345678ULL;}
struct Hooks {
 detour::Set a,f,an,ad,sn,sd,c,b,r,s,rp,st,dg,rw,u,rq,pins,environment;
 Hooks(){allocPatch=&a;freePatch=&f;arrayNewPatch=&an;arrayDeletePatch=&ad;scalarNewPatch=&sn;scalarDeletePatch=&sd;copyPatch=&c;corePatch=&b;reqPatch=&r;safePatch=&s;repPatch=&rp;stringPatch=&st;dialogPatch=&dg;rewardPatch=&rw;unitPatch=&u;requirementsPatch=&rq;
  a.redirect(qlAlloc,qlAlloc,&allocate);f.redirect(qlFree,qlFree,&release);an.redirect(qlArrayNew,qlArrayNew,&arrayNew);ad.redirect(qlArrayDelete,qlArrayDelete,&arrayDelete);sn.redirect(qlScalarNew,qlScalarNew,&scalarNew);sd.redirect(qlScalarDelete,qlScalarDelete,&scalarDelete);c.redirect(qlCopy,qlCopy,&copy);
  TL_REDIRECT(b,qlCoreDtor,&core);TL_REDIRECT(r,qlReqCtor,&reqCtor);TL_REDIRECT(s,qlRemoveSafe,&removeSafe);
  rp.redirect(qlRepDestroy,qlRepDestroy,&repDestroy);st.redirect(qlStringDtor,qlStringDtor,&stringDtor);
  TL_REDIRECT(dg,qlDialogD0,&dialog);TL_REDIRECT(rw,qlRewardD0,&reward);TL_REDIRECT(u,qlUnitD0,&unit);TL_REDIRECT(rq,qlReqD0,&reqDelete);
  TL_REDIRECT(environment,qlUI,&noUI);TL_REDIRECT(environment,qlGuid,&stableGuid);
  pinOriginal(pins,qlDialogD1_original,qlDialogD1_linked);pinOriginal(pins,qlRewardD1_original,qlRewardD1_linked);pinOriginal(pins,qlUnitD1_original,qlUnitD1_linked);pinOriginal(pins,qlReqD1_original,qlReqD1_linked);
 }
 bool failed(){return a.failed()||f.failed()||an.failed()||ad.failed()||sn.failed()||sd.failed()||c.failed()||b.failed()||r.failed()||s.failed()||rp.failed()||st.failed()||dg.failed()||rw.failed()||u.failed()||rq.failed()||pins.failed()||environment.failed();}
};
static void definedState(bool candidate){
 vtable(candidate);need(!at<void*>(owner,8)&&!at<long long>(owner,0x10)&&!at<int>(owner,0x18)&&at<int>(owner,0x1c)==-1&&!at<int>(owner,0x20),40);
 for(unsigned o=0x24;o<0x2c;++o)need(at<unsigned char>(owner,o)==(o==0x29),41+o);
 unsigned poison=cs->shape&1?0xa5:0x5a;for(unsigned o=0x2e;o<0x30;++o)need(at<unsigned char>(owner,o)==poison,252);for(unsigned o=0x211;o<0x218;++o)need(at<unsigned char>(owner,o)==poison,253);need(at<unsigned char>(owner,0x2c)==poison&&at<unsigned char>(owner,0x2d)==poison&&at<unsigned char>(owner,0x208)==poison,42);
 for(unsigned o=0x30;o<=0x58;o+=8){Wide& s=at<Wide>(owner,o);need(s==(o<=0x48&&cs->text?*source:Wide()),43+o);cap->addText(s);}
 const unsigned offsets[]={0x60,0x78,0x90,0xa8,0xc8,0xe0,0xf8,0x110,0x130,0x148,0x160,0x178,0x190,0x1b0,0x1f0};
 for(unsigned i=0;i<15;++i){unsigned o=offsets[i];for(unsigned j=20;j<24;++j)need(at<unsigned char>(owner,o+j)==poison,251);need(!at<void*>(owner,o)&&!at<unsigned>(owner,o+8)&&!at<unsigned>(owner,o+12)&&at<unsigned>(owner,o+16)==(o>=0x130&&o<=0x1b0?1u:10u),60+i);}
 need(!at<void*>(owner,0xc0)&&!at<void*>(owner,0x128),75);
 need(at<int>(owner,0x1a8)==1&&at<int>(owner,0x1ac)==1&&at<long long>(owner,0x1c8)==-1,76);
 need(at<void*>(owner,0x1d0)==manager&&at<void*>(owner,0x1d8)==resource&&!at<long long>(owner,0x1e8),77);
 need(!at<unsigned char>(owner,0x209)&&!at<unsigned char>(owner,0x20a)&&!at<unsigned char>(owner,0x20b)&&at<int>(owner,0x20c)==1&&!at<unsigned char>(owner,0x210),78);
 void* r=at<void*>(owner,0x1e0);need(r&&r==requirements,79);
 if(r){need(at<void*>(r,0x18)==owner&&!at<void*>(r,0x10)&&at<unsigned>(r,0x40)==3,80);need(at<uintptr_t>(r,0)==0xffdfd0,81);}
}
static void construct(void* p,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(p);cap=&out;init();Hooks hooks;if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 constructing=tracking=true;
 typedef void(*Fn)(void*,void*,void*);Fn fn=candidate?(cs->alias?&qlNewC2:&qlNewC1):(cs->alias?&qlOldC2:&qlOldC1);
 need(reinterpret_cast<uintptr_t>(&qlOldC1)==reinterpret_cast<uintptr_t>(&qlOldC2),82);
 if(!autotest::beginInvocation(out,fn))return;bool caught=false;
 try{fn(owner,resource,manager);out.callCompleted=1;}catch(const Stop& x){caught=true;need(x.site==cs->fault,83);}
 need(caught==(cs->fault!=0)&&faultHits==(cs->fault?1u:0u),84);
 if(!caught){definedState(candidate);need(copyCalls==4&&copySuccess==4&&ogreCalls==4&&arrayCalls==3,85);}
 if(caught){need(baseCalls==1,86);need(reqBaseCalls==(cs->fault>=21?1u:0u),87);
  for(unsigned i=0;i<4;++i)if(ctorKeep[i])need(refs(*ctorKeep[i])==(cs->text==1?static_cast<int>(copySuccess):0),88+i);
  // Original requirements failure destroys members but intentionally leaves
  // already-created pointed-to nested wrappers alive. Check outer separately.
  Block* outer=0;for(unsigned i=0;i<blockCount;++i)if(blocks[i].id==401)outer=&blocks[i];
  if(cs->fault>=21){need(outer&&outer->frees==1,92);for(unsigned i=0;i<blockCount;++i)if(blocks[i].allocator==1&&blocks[i].id>401)need(blocks[i].frees==0,254);}
  if(cs->fault>=20)need(!at<void*>(owner,0x1e0),93);
 }else{
  tracking=false;qlOldD1(owner);
  for(unsigned i=0;i<4;++i)if(ctorKeep[i])need(refs(*ctorKeep[i])==(cs->text==1?static_cast<int>(copySuccess):0),94+i);
 }
 tracking=false;freeOgre(owner);for(unsigned i=0;i<4;++i)if(ctorKeep[i])ctorKeep[i]->~Wide();source->~Wide();
 need(!hooks.failed(),98);number(0x514c4946);number(errors);
}
static void ctorOld(void* p,autotest::Capture& out){construct(p,out,false);}static void ctorNew(void* p,autotest::Capture& out){construct(p,out,true);}
static void watchString(Wide& value,unsigned id){
 need(stringCount<160,200);if(stringCount>=160)return;
 StringWitness& w=strings[stringCount++];w.id=id;w.freed=0;
 // Every tracked string is nonempty, including embedded NUL and long values.
 Wide text(1,wchar_t(L'A'+id%23));text+=L" lifetime \u03a9";
 if(cs->text){text.append(97+id%13,L'x');text[7]=0;}
 value.assign(text.c_str(),text.size());w.rep=rep(value);
 w.keeper=(cs->text&&id%2)?0:new(raw(sizeof(Wide)))Wide(value);
 need(refs(value)==(w.keeper?1:0),201);
}
static void watchBuffer(void* list,unsigned id,bool wide=false){
 void* p=at<void*>(list,0);if(p)remember(wide?static_cast<char*>(p)-8:p,id,2);
}
static void stringsIn(Strings& list,unsigned id,unsigned count){
 for(unsigned i=0;i<count;++i)list.add(Wide());
 // Also populate one live capacity-only element. delete[] must destroy the
 // complete constructed array, even beyond the logical count.
 unsigned capacity=at<unsigned>(&list,12);Wide* data=at<Wide*>(&list,0);
 for(unsigned i=0;i<count;++i)watchString(data[i],id+i);
 if(capacity>count)watchString(data[capacity-1],id+count);
}
static void* makeDialog(unsigned id){
 void* p=ogre(0xa8);qlDialogCtor(p,owner);need(at<uintptr_t>(p,0)==0xff7410,202);remember(p,id,1);++expectedChildren;
 watchString(at<Wide>(p,0x60),100+id);return p;
}
static void* makeUnit(unsigned id){
 void* p=ogre(0xc8);qlUnitCtor(p,owner);need(at<uintptr_t>(p,0)==0xff7df0,203);remember(p,id,1);++expectedChildren;
 watchString(at<Wide>(p,0x68),200+id);return p;
}
static void graph(bool candidate){
 if(candidate&&cs->constructor)qlNewC1(owner,resource,manager);else qlOldC1(owner,resource,manager);
 requirements=at<void*>(owner,0x1e0);remember(owner,1,1);remember(requirements,12,1);expectedChildren=1;
 // Real base registry invalidates a live external observer only at the end.
 witness.p=owner;witness.index=qlAddSafe(owner,&witness);
 remember(at<void*>(owner,8),280,1);watchBuffer(at<void*>(owner,8),380);
 if(!cs->shape)return;
 at<long long>(owner,0x10)=0x12345678;
 for(unsigned i=0;i<6;++i)watchString(at<Wide>(owner,0x30+i*8),1+i);
 const unsigned stringOffsets[]={0xc8,0xe0,0x1f0};
 for(unsigned i=0;i<3;++i){Strings& s=at<Strings>(owner,stringOffsets[i]);stringsIn(s,20+i*16,cs->shape==2?11:2);watchBuffer(&s,350+i,true);}
 // Original producer writes byte flags at +f8/+110, paired with the names
 // at +c8/+e0. These are genuine bool arrays, never unit-pointer aliases.
 for(unsigned f=0;f<2;++f){
  Flags& flags=at<Flags>(owner,0xf8+f*24);
  unsigned count=at<Strings>(owner,0xc8+f*24).size();
  for(unsigned i=0;i<count;++i)flags.add(((i+f)&1)!=0);
  unsigned capacity=at<unsigned>(&flags,12);bool* data=at<bool*>(&flags,0);
  if(capacity>count)data[capacity-1]=true;
  need(flags.size()==count&&capacity>=count&&at<unsigned>(&flags,16)==10,262);
  for(unsigned i=0;i<count;++i)need(data[i]==(((i+f)&1)!=0),263);
  if(capacity>count)need(data[capacity-1],264);
  watchBuffer(&flags,330+f);
 }
 if(cs->shape==3)return; // Strings and requirements only: all optional owned categories absent.
 void* rewards=ogre(0x78);qlRewardCtor(rewards,owner);need(at<uintptr_t>(rewards,0)==0xff7a90,204);at<void*>(owner,0x128)=rewards;remember(rewards,10,1);++expectedChildren;
 at<void*>(owner,0xc0)=makeDialog(11);
 const unsigned dialogOffsets[]={0xa8,0x60,0x78,0x90};
 for(unsigned f=0;f<(cs->shape==4?0u:4u);++f){Pointers& list=at<Pointers>(owner,dialogOffsets[f]);unsigned count=cs->shape==2?11:2;
  for(unsigned i=0;i<count;++i)list.add(makeDialog(20+f*16+i));list.add(0);watchBuffer(&list,300+f);
 }
 // Requirements owns three genuine constructor-created nested string lists.
 Pointers& required=at<Pointers>(requirements,0x38);need(required.size()==3,205);watchBuffer(&required,360);
 watchString(at<Wide>(requirements,0x30),600);
 for(unsigned i=0;i<3;++i){void* p=required[i];remember(p,250+i,1);Strings& s=*static_cast<Strings*>(p);stringsIn(s,610+i*8,2);watchBuffer(p,361+i,true);}
 if(cs->shape==4)return; // Rewards/primary/requirements only, no dialog/unit families.
 // Child pass order: +178,+160,+190. Wrapper-free order: +160,+190,+178.
 const unsigned families[]={0x178,0x160,0x190};
 for(unsigned f=0;f<3;++f){Pointers& outer=at<Pointers>(owner,families[f]);
  for(unsigned g=0;g<2;++g){Pointers* list=new Pointers(2);++expectedGroups;remember(list,200+f*10+g,1);outer.add(list);
   if(!g){for(unsigned i=0;i<2;++i){void* unit=makeUnit(100+f*10+i);++expectedUnits;list->add(unit);}list->add(0);watchBuffer(list,320+f);}
   // Original reset selects +130 from +178, and +148 from +190.
   // Each selection includes the populated and the empty original-owned group.
   if(f==0)at<Pointers>(owner,0x130).add(list);
   if(f==2)at<Pointers>(owner,0x148).add(list);
  }
  watchBuffer(&outer,310+f);
 }
 watchBuffer(static_cast<char*>(owner)+0x130,332);watchBuffer(static_cast<char*>(owner)+0x148,333);
 for(unsigned i=0;i<2;++i){need(at<Pointers>(owner,0x130)[i]==at<Pointers>(owner,0x178)[i],265);need(at<Pointers>(owner,0x148)[i]==at<Pointers>(owner,0x190)[i],266);}
 need(at<Pointers>(owner,0x130).size()==2&&at<Pointers>(owner,0x148).size()==2,267);
 controller=ogre(0xb8);qlControllerCtor(controller,resource);
 listener=ogre(16);at<void*>(listener,0)=controller;at<unsigned>(listener,8)=qlAddSafe(controller,listener);
 remember(listener,90,1);at<Pointers>(owner,0x1b0).add(listener);at<Pointers>(owner,0x1b0).add(0);watchBuffer(static_cast<char*>(owner)+0x1b0,390);
}
static unsigned eventPosition(unsigned value){for(unsigned i=0;i<eventCount;++i)if(events[i]==value)return i;return ~0u;}
static void ordered(unsigned a,unsigned b,unsigned site){unsigned x=eventPosition(a),y=eventPosition(b);need(x!=~0u&&y!=~0u&&x<y,site);}
static void normalOracle(){
 need(baseCalls==1&&!witness.p&&witness.index==~0u,210);
 need(childCalls==expectedChildren,211);
 for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];if(b.id!=1)need(b.frees==1,212);
  bool ownedObject=b.id==10||b.id==11||b.id==12||(b.id>=20&&b.id<84)||(b.id>=100&&b.id<130);
  if(ownedObject)need(b.bases==1&&b.deletes==1,213);
 }
 for(unsigned i=0;i<stringCount;++i){StringWitness& w=strings[i];if(w.keeper)need(refs(*w.keeper)==0,214);else need(w.freed==1,215);}
 if(cs->shape==4){ordered(30010,30011,255);ordered(30011,30012,256);}
 if(cs->shape==1||cs->shape==2){
  ordered(8000,20090,240);ordered(20090,20390,241);ordered(20390,30010,242);
  ordered(30010,30011,216);ordered(30011,30012,217);ordered(30012,30020,218);
  ordered(30020,30036,219);ordered(30036,30052,220);ordered(30052,30068,221);
  ordered(30068,30100,222);ordered(30101,30110,223);ordered(30111,30120,224);
  ordered(30121,20210,225);ordered(20211,20220,226);ordered(20221,20200,227);
  ordered(20201,20332,228);ordered(20332,20333,229);ordered(20333,20352,230);
  ordered(20352,20331,231);ordered(20331,20330,232);ordered(20330,20351,233);ordered(20351,20350,234);
  ordered(20350,9000,235);
 }
}
static void virtualDelete(void* p){
 ++virtualCalls;event(9500);need(p==owner,257);
 virtualPatch->restore();
 typedef void(*Fn)(void*);Fn target=virtualCandidate?&qlNewD0:&qlOldD0;
 need(!virtualCandidate||(target!=&qlOldD0&&context->comparison_pair&&context->comparison_pair(0xd1b5c0,reinterpret_cast<uintptr_t>(target))),258);
 target(p);
}
static void destroy(void* p,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(p);cap=&out;init();Hooks hooks;if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 graph(candidate);vtable(candidate&&cs->constructor);
 typedef void(*Fn)(void*);Fn fn=candidate?(cs->alias==1?&qlNewD2:cs->alias>=2?&qlNewD0:&qlNewD1):(cs->alias==1?&qlOldD2:cs->alias>=2?&qlOldD0:&qlOldD1);
 detour::Set virtualRoute;virtualPatch=&virtualRoute;virtualCandidate=candidate;
 if(cs->alias==3){
  // Virtual dispatch must actually use the side's constructed vtable. Force
  // candidate C1 in this case, rather than transplanting a vptr.
  fn=reinterpret_cast<Fn>(at<uintptr_t*>(owner,0)[1]);
  need(reinterpret_cast<uintptr_t>(fn)==0xd1b5c0,236);
  // The selftest retains original vtable slots; locally reproduce the verified
  // production hook and keep this as supplemental dispatch evidence only.
  virtualRoute.redirect(reinterpret_cast<char*>(fn),reinterpret_cast<char*>(fn),&virtualDelete);
  need(!virtualRoute.failed(),259);
 }
 need(reinterpret_cast<uintptr_t>(&qlOldD1)==reinterpret_cast<uintptr_t>(&qlOldD2),237);
 tracking=true;constructing=false;if(!autotest::beginInvocation(out,fn))return;
 bool caught=false;try{fn(owner);out.callCompleted=1;}catch(const Stop& e){caught=true;need(e.site==cs->fault,243);}
 need(caught==(cs->fault!=0)&&faultHits==(cs->fault?1u:0u),244);
 if(!caught){normalOracle();need(outerFrees==(cs->alias>=2?1u:0u),238);}
 else{
  need(baseCalls==1&&!witness.p&&witness.index==~0u&&childCalls==0&&groupFrees==0&&outerFrees==0,245);
  for(unsigned i=0;i<blockCount;++i){Block& b=blocks[i];bool freed=b.allocator==2&&b.id>=300&&b.id<400;
   // Only the quest's own automatic members and base registry are cleaned.
   if(b.id==320||b.id==321||b.id==322||b.id==360||b.id==361||b.id==362||b.id==363)freed=false;
   if(b.id==280)freed=true;
   need(b.frees==(freed?1u:0u),246);
  }
  for(unsigned i=0;i<stringCount;++i){StringWitness& w=strings[i];bool gone=w.id<100;if(w.keeper)need(refs(*w.keeper)==(gone?0:1),247);else need(w.freed==(gone?1u:0u),248);}
 }
 need(!hooks.failed(),239);need(virtualCalls==(cs->alias==3?1u:0u),260);
 tracking=false;if(cs->alias<2||caught)freeOgre(owner);
 if(controller){qlControllerDtor(controller);freeOgre(controller);}
 for(unsigned i=0;i<stringCount;++i)if(strings[i].keeper)strings[i].keeper->~Wide();source->~Wide();
 number(0x514c4946);number(errors);
}
static void dtorOld(void* p,autotest::Capture& out){destroy(p,out,false);}static void dtorNew(void* p,autotest::Capture& out){destroy(p,out,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x514c4946&&!tail[1];}
static bool compare(const tlhybrid_host* host,autotest::Coverage& cv,autotest::Body oldBody,autotest::Body newBody,Case& c){
 context=host;autotest::Outcome a,b;autotest::runChild(oldBody,&c,a);autotest::runChild(newBody,&c,b);
 bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault){if(c.kind&&c.alias==3){ok=ok&&a.capture.callStarted&&b.capture.callStarted&&a.capture.callCompleted&&b.capture.callCompleted&&a.capture.callTarget==0xd1b5c0&&b.capture.callTarget==0xd1b5c0;}else if(cv.observe(host,a,b))ok=false;}
 else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==cv.original&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok){host->log("tlhybrid: Quest lifetime kind=%u alias=%u shape=%u text=%u fault=%u ctor=%u status=%d/%d good=%u/%u length=%lu/%lu\n",c.kind,c.alias,c.shape,c.text,c.fault,c.constructor,a.childStatus,b.childStatus,good(a),good(b),(unsigned long)a.capture.length,(unsigned long)b.capture.length);
  for(unsigned side=0;side<2;++side){const autotest::Capture& z=side?b.capture:a.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned w;std::memcpy(&w,z.data+i,4);if((w&0xff000000u)==0xf3000000u)host->log("tlhybrid: Quest lifetime side=%u oracle=%u word=%lu\n",side,w-0xf3000000u,(unsigned long)i/4);}}
 }
 return ok;
}
}
TL_TEST(quest_constructor_lifetime){using namespace quest_lifetime;autotest::Coverage cv("quest_constructor_lifetime",0xd16280);
 for(unsigned a=0;a<2;++a)for(unsigned shape=0;shape<2;++shape)for(unsigned text=0;text<3;++text)for(unsigned identity=0;identity<4;++identity){Case c={0,a,shape,text,0,identity};if(!compare(host,cv,ctorOld,ctorNew,c)){cv.report(host);return 1;}}
 cv.report(host);return cv.completed!=48||cv.different||cv.missing;
}
TL_TEST(quest_constructor_unwind){using namespace quest_lifetime;autotest::Coverage cv("quest constructor expected unwind excluded",0xd16280);
 for(unsigned a=0;a<2;++a){for(unsigned f=1;f<=4;++f){Case c={0,a,1,2,f,0};if(!compare(host,cv,ctorOld,ctorNew,c))return 1;}
  for(unsigned f=11;f<=14;++f){Case c={0,a,1,2,f,0};if(!compare(host,cv,ctorOld,ctorNew,c))return 1;}
  for(unsigned f=20;f<=26;++f){Case c={0,a,1,2,f,0};if(!compare(host,cv,ctorOld,ctorNew,c))return 1;}}
 host->log("tlhybrid: Quest C1/C2: 8 copy-boundary probes, 8 real leaked-COW allocation failures, 14 real requirements allocation failures; no completed-call credit\n");return 0;
}
TL_TEST(quest_destructor_owned_lifetime){using namespace quest_lifetime;autotest::Coverage complete("quest_destructor_owned_lifetime",0xd1a390),deleting("quest_deleting_lifetime",0xd1b5c0);
 for(unsigned a=0;a<4;++a)for(unsigned shape=0;shape<5;++shape)for(unsigned text=0;text<2;++text){Case c={1,a,shape,text,0,a==3?1u:0u};autotest::Coverage& cv=a>=2?deleting:complete;if(!compare(host,cv,dtorOld,dtorNew,c)){complete.report(host);deleting.report(host);return 1;}}
 // Additional complete-destruction integration on candidate-constructed graph.
 for(unsigned a=0;a<2;++a){Case c={1,a,2,1,0,1};if(!compare(host,complete,dtorOld,dtorNew,c)){complete.report(host);deleting.report(host);return 1;}}
 host->log("tlhybrid: Quest virtual deletion: 10 supplemental actual-vtable dispatch pairs with verified local production routing, excluded from direct-address coverage\n");
 complete.report(host);deleting.report(host);return complete.completed!=22||deleting.completed!=10||complete.different||complete.missing||deleting.different||deleting.missing;
}

TL_TEST(quest_destructor_unwind){using namespace quest_lifetime;autotest::Coverage cv("quest destructor expected unwind excluded",0xd1a390);
 for(unsigned a=0;a<2;++a)for(unsigned text=0;text<2;++text){Case c={1,a,2,text,40,1};if(!compare(host,cv,dtorOld,dtorNew,c))return 1;}
 host->log("tlhybrid: Quest D1/D2: 4 LSDA-reachable listener-unregister boundary unwinds; untouched raw pointees preserved; no completed-call credit\n");return 0;
}
