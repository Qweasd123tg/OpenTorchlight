// Manager framing/lifetime tests, independently hand-encoded below. These keep
// original ReadWString and accepted reset/getQuestByName bodies. Controlled Quest
// boundaries isolate the manager; this is NOT original Quest/GameClient coverage.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <new>
#include <stdint.h>
#include <dlfcn.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, qplOld, (void*,FILE*,unsigned,void*), "_ZN13CQuestManager4loadEP8_IO_FILEjP16CResourceManager")
extern "C" void qplNew(void*,FILE*,unsigned,void*) __asm__("_ZN13CQuestManager4loadEP8_IO_FILEjP16CResourceManager");
TL_FUNCTION(qplQuestLoad,"_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
TL_FUNCTION(qplReinitialize,"_ZN6CQuest17reinitializeQuestEbb")
TL_FUNCTION(qplRandom,"_ZN6CQuest23getQuestHasRandomPiecesEv")
TL_ORIGINAL(long long,qplName,(void*,const std::wstring&),"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(char,qplComplete,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char qplFread[] __asm__("fread");
extern "C" char qplFseek[] __asm__("fseek");
extern "C" char qplArrayNew[] __asm__("_Znam");
extern "C" char qplArrayDelete[] __asm__("_ZdaPv");
extern "C" char qplScalarNew[] __asm__("_Znwm");
extern "C" char qplScalarDelete[] __asm__("_ZdlPv");
extern "C" char qplWideCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");
extern "C" char qplWideCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
namespace qpl {
typedef std::map<std::wstring,void*> Names;
typedef std::map<std::wstring,bool> Complete;
struct List { void** data; unsigned count,capacity,grow,pad; };
typedef char ABI[(sizeof(Names)==48&&sizeof(Complete)==48&&sizeof(List)==24&&sizeof(std::wstring)==8)?1:-1];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>((char*)p+off);}
enum Scenario { Empty, RawNames, SkipRecords, Growth, NegativeActive, ReentrantGrowth, Spare, UnsignedSeek, ShortHeader, Compatibility };
enum Fault { NoFault, ResetThrow, LoadThrow, NullArrayThrow, ExistingArrayThrow, RandomThrow, ReinitThrow, CompatThrow, FirstCtorThrow, SecondCtorThrow, PairCopyThrow, NodeNewThrow };
struct Case { unsigned scenario,version,mode,fault; };
struct Stop {};
struct Event { unsigned kind; uint64_t a,b,c,d,e; };
struct Allocation { void* p; size_t bytes; bool live; };
const Case* cs; autotest::Capture* cap;
unsigned errors,firstErrorLine,eventIndex,eventCount,readCalls,resetCalls,loadCalls,randomCalls,trueResets,arrayCalls,arrayDeletes,ctorCalls,copyCalls,scalarCount;
unsigned expectedResetCalls,expectedLoadCalls,expectedRandomCalls,expectedTrueResets,expectedArrayCalls,expectedArrayDeletes,expectedCtorCalls,expectedCopyCalls;
unsigned expectedCount,expectedCapacity,expectedPosition,expectedCaught,expectedSlots[16],expectedLoaded[8],expectedAccepted[8],expectedReset[8];
unsigned loaded[8],randomValue[8],reset[8],payloadAccepted[16],payloadRandom[16],loadIds[16],loadCursor;
unsigned char bytes[4096]; unsigned byteCount; Event events[256]; Allocation scalar[512];
void* owner; void* object[8]; void* resource; List* list; Names* names; Complete* complete; FILE* file;
std::wstring keys[8]; bool hasKey[8],completionKey[8],expectedComplete[8]; bool tracking,initialArrayLive,growthMutation,failScalarAllocation,candidateSide;
void** initialArray; void** oldGrowth; unsigned oldGrowthCapacity; void** newestArray;
detour::Set *readPatch,*seekPatch,*ctorPatch,*copyPatch;
void check(bool b,unsigned line){if(!b){if(!errors)firstErrorLine=line;if(errors<8)std::fprintf(stderr,"    QPL %s scenario=%u version=%u mode=%u fault=%u line=%u event=%u live=%u\n",candidateSide?"candidate":"original",cs->scenario,cs->version,cs->mode,cs->fault,line,eventIndex,scalarCount);++errors;}}
#define need(b) check((b),__LINE__)
void n(unsigned x){cap->add(&x,4);}
unsigned id(void* p){if(!p)return 99;for(unsigned i=0;i<8;++i)if(p==object[i])return i;need(false);return 98;}
unsigned position(){long p=std::ftell(file);need(p>=0);return (unsigned)p;}
void expect(unsigned k,uint64_t a=0,uint64_t b=0,uint64_t c=0,uint64_t d=0,uint64_t e=0){if(eventCount==256)_exit(71);Event& x=events[eventCount++];x.kind=k;x.a=a;x.b=b;x.c=c;x.d=d;x.e=e;}
void event(unsigned k,uint64_t a=0,uint64_t b=0,uint64_t c=0,uint64_t d=0,uint64_t e=0){need(eventIndex<eventCount);if(eventIndex<eventCount){const Event& x=events[eventIndex];bool same=x.kind==k&&x.a==a&&x.b==b&&x.c==c&&x.d==d&&x.e==e;if(!same&&errors<8)std::fprintf(stderr,"    QPL event actual %u %llu %llu %llu %llu %llu expected %u %llu %llu %llu %llu %llu\n",k,(unsigned long long)a,(unsigned long long)b,(unsigned long long)c,(unsigned long long)d,(unsigned long long)e,x.kind,(unsigned long long)x.a,(unsigned long long)x.b,(unsigned long long)x.c,(unsigned long long)x.d,(unsigned long long)x.e);need(same);}++eventIndex;n(k);cap->add(&a,8);cap->add(&b,8);cap->add(&c,8);cap->add(&d,8);cap->add(&e,8);}
void u16(unsigned v){if(byteCount+2>sizeof(bytes))_exit(71);bytes[byteCount++]=(unsigned char)v;bytes[byteCount++]=(unsigned char)(v>>8);}
void u32(unsigned v){u16(v);u16(v>>16);}
void expectRead(unsigned size,unsigned count,unsigned at,unsigned result){expect(1,size,count,result,at,at+size*result);}
void header(unsigned completed,unsigned active){unsigned p=byteCount;u32(completed);expectRead(4,1,p,1);if(!completed){p=byteCount;u32(active);expectRead(4,1,p,1);}}
void nameBytes(const std::wstring& s){unsigned p=byteCount;u16(s.size());expectRead(2,1,p,1);for(unsigned i=0;i<s.size();++i){p=byteCount;u16((unsigned)s[i]);expectRead(2,1,p,1);}}
void completedName(const std::wstring& s){nameBytes(s);}
// Each record supplies its own independent expected capacity/count rather than
// consulting the implementation's list/add path or serializing with save().
void record(unsigned who,const std::wstring& key,unsigned accepted,unsigned random,
            unsigned after,unsigned capacity,unsigned allocateBytes,unsigned savedEnd=0xffffffffu){
 if(savedEnd==0xffffffffu)savedEnd=byteCount+9+2*key.size();
 unsigned p=byteCount;u32(savedEnd);expectRead(4,1,p,1);nameBytes(key);
 unsigned before=expectedCount,oldcap=expectedCapacity;
 expect(4,who,cs->version,before,oldcap,byteCount);++expectedLoadCalls;
 loadIds[loadCursor]=who;payloadAccepted[loadCursor]=accepted;payloadRandom[loadCursor++]=random;
 p=byteCount;bytes[byteCount++]=(unsigned char)who;bytes[byteCount++]=(unsigned char)accepted;bytes[byteCount++]=(unsigned char)random;expectRead(1,3,p,3);
 ++expectedLoaded[who];expectedAccepted[who]=accepted;
 if(cs->fault==LoadThrow&&expectedLoadCalls==2){expectedCaught=1;expectedPosition=byteCount;return;}
 if(cs->scenario==Spare&&expectedLoadCalls==1){before=1;oldcap=4;expectedCount=1;expectedCapacity=4;expectedSlots[0]=7;for(unsigned i=1;i<4;++i)expectedSlots[i]=7;}
 if(allocateBytes){unsigned observedCap=oldcap?oldcap:capacity;expect(5,allocateBytes,before,observedCap,oldcap!=0,0);++expectedArrayCalls;
  if((cs->fault==NullArrayThrow&&!oldcap)||(cs->fault==ExistingArrayThrow&&oldcap)){expectedCaught=2;expectedCapacity=observedCap;expectedPosition=byteCount;return;}
  if(oldcap){if(cs->scenario==ReentrantGrowth){before=1;expectedCount=1;}expect(6,1,before,oldcap,0,0);++expectedArrayDeletes;}
  for(unsigned i=oldcap;i<capacity;++i)expectedSlots[i]=7;
 }
 expectedSlots[before]=who;expectedCount=after;expectedCapacity=capacity;
 if(!accepted){expect(7,who,after,capacity,0,0);++expectedRandomCalls;
  if(cs->mode==1){expectedAccepted[who]=1;}
  if(cs->fault==RandomThrow&&expectedRandomCalls==1){expectedCaught=1;expectedPosition=byteCount;return;}
  if(random){expect(8,who,after,capacity,expectedAccepted[who],byteCount);++expectedTrueResets;++expectedReset[who];expectedAccepted[who]=0;
   if(cs->fault==ReinitThrow){expectedCaught=1;expectedPosition=byteCount;return;}
  }
 }
 expectedPosition=byteCount;
}
void skipped(const std::wstring& key,unsigned payload,unsigned end){unsigned p=byteCount;u32(end);expectRead(4,1,p,1);nameBytes(key);unsigned start=byteCount;for(unsigned i=0;i<payload;++i)bytes[byteCount++]=(unsigned char)(0xe0+i);expect(2,end,SEEK_SET,0,start,end);expectedPosition=end;}
unsigned liveScalars(){unsigned n=0;for(unsigned i=0;i<scalarCount;++i)if(scalar[i].live)++n;return n;}
void* scalarNew(size_t bytes){if(tracking&&failScalarAllocation)throw std::bad_alloc();if(tracking&&cs->fault==NodeNewThrow&&ctorCalls==2&&copyCalls==1&&bytes==48)throw std::bad_alloc();void* p=std::malloc(bytes?bytes:1);if(!p)throw std::bad_alloc();if(tracking){if(scalarCount==512)_exit(71);Allocation& a=scalar[scalarCount++];a.p=p;a.bytes=bytes;a.live=true;}return p;}
void scalarDelete(void* p){if(!p)return;for(unsigned i=scalarCount;i;--i)if(scalar[i-1].p==p&&scalar[i-1].live){scalar[i-1].live=false;break;}std::free(p);}
void* arrayNew(size_t bytes){++arrayCalls;event(5,bytes,list->count,list->capacity,list->data!=0,0);oldGrowth=list->data;oldGrowthCapacity=list->capacity;
 if((cs->fault==NullArrayThrow&&!list->data)||(cs->fault==ExistingArrayThrow&&list->data))throw std::bad_alloc();
 if(cs->scenario==ReentrantGrowth&&list->data){list->count=1;growthMutation=true;}
 void* p=std::malloc(bytes?bytes:1);if(!p)throw std::bad_alloc();newestArray=(void**)p;for(unsigned i=0;i<bytes/8;++i)newestArray[i]=object[7];return p;
}
void arrayDelete(void* p){if(!p)return;++arrayDeletes;if(p==initialArray&&initialArrayLive){event(6,0,list->count,list->capacity,0,0);need(!list->count&&!list->capacity&&list->data==p);initialArrayLive=false;}
 else {event(6,1,list->count,list->capacity,0,0);need(p==oldGrowth&&list->data==p&&list->capacity==oldGrowthCapacity);for(unsigned i=0;i<oldGrowthCapacity;++i)need(newestArray[i]==oldGrowth[i]);}
 std::free(p);
}
size_t read(void* dst,size_t size,size_t count,FILE* f){need(f==file);if(readCalls++==0){need(resetCalls==expectedResetCalls&&!initialArrayLive);if(cs->scenario==SkipRecords||(cs->scenario==Compatibility&&cs->mode/2==2))(*names)[keys[cs->scenario==SkipRecords?2:6]]=0;}
 unsigned p=position();readPatch->restore();size_t result=std::fread(dst,size,count,f);readPatch->redirect(qplFread,qplFread,&read);need(!readPatch->failed());event(1,size,count,result,p,position());return result;
}
int seek(FILE* f,long offset,int origin){need(f==file);unsigned p=position();seekPatch->restore();int result=std::fseek(f,offset,origin);seekPatch->redirect(qplFseek,qplFseek,&seek);need(!seekPatch->failed());event(2,(uint64_t)offset,origin,(unsigned)result,p,position());return result;}
void reinitialize(void* self,bool full,bool other){unsigned who=id(self);need(!other);if(!full){event(3,who,list->count,list->capacity,position(),0);need(!list->data&&!list->count&&!list->capacity);for(Complete::iterator i=complete->begin();i!=complete->end();++i)need(!i->second);++resetCalls;at<unsigned char>(self,0x26)=0;++reset[who];if(cs->fault==ResetThrow&&resetCalls==1)throw Stop();return;}
 event(8,who,list->count,list->capacity,at<unsigned char>(self,0x26),position());++trueResets;++reset[who];at<unsigned char>(self,0x26)=0;
 if(cs->scenario==Compatibility){need(who==6);need(liveScalars()==0);if(cs->fault==CompatThrow)throw Stop();}
 else {need(list->count&&list->data[list->count-1]==self);if(cs->fault==ReinitThrow)throw Stop();}
}
void questLoad(void* self,FILE* f,void* r,unsigned version){unsigned who=id(self);event(4,who,version,list->count,list->capacity,position());need(f==file&&r==resource&&version==cs->version);need(loadCalls<loadCursor&&loadIds[loadCalls]==who);need(liveScalars()==(keys[who].empty()?0u:1u));unsigned char payload[3]={0xff,0xff,0xff};need(std::fread(payload,1,3,f)==3);need(payload[0]==who&&payload[1]==payloadAccepted[loadCalls]&&payload[2]==payloadRandom[loadCalls]);++loadCalls;++loaded[who];at<unsigned char>(self,0x26)=payload[1];randomValue[who]=payload[2];
 if(cs->scenario==Spare&&loadCalls==1){need(!list->data&&!list->count&&!list->capacity);list->data=(void**)std::malloc(32);for(unsigned i=0;i<4;++i)list->data[i]=object[7];list->count=1;list->capacity=4;}
 if(cs->fault==LoadThrow&&loadCalls==2)throw Stop();
}
long long random(void* self){unsigned who=id(self);event(7,who,list->count,list->capacity,at<unsigned char>(self,0x26),0);need(list->count&&list->data[list->count-1]==self);++randomCalls;if(cs->mode==1)at<unsigned char>(self,0x26)=1;if(cs->fault==RandomThrow)throw Stop();return randomValue[who]?1:0;}
void wideCtor(std::wstring* dst,const wchar_t* src,const std::allocator<wchar_t>& alloc){
 need(src&&std::wcscmp(src,L"COMPLETEGAME")==0);++ctorCalls;
 failScalarAllocation=(cs->fault==FirstCtorThrow&&ctorCalls==1)||(cs->fault==SecondCtorThrow&&ctorCalls==2);
 ctorPatch->restore();try{reinterpret_cast<void(*)(std::wstring*,const wchar_t*,const std::allocator<wchar_t>&)>(qplWideCtor)(dst,src,alloc);}
 catch(...){failScalarAllocation=false;throw;}failScalarAllocation=false;
 // This destination is the manager's nonconst second lookup local. Nonconst
 // access gives it a legitimate leaked COW representation, so the upcoming
 // pair-key copy must clone and can genuinely fail its allocator.
 if(cs->fault==PairCopyThrow&&ctorCalls==2)(*dst)[0]=L'C';
 ctorPatch->redirect(qplWideCtor,qplWideCtor,&wideCtor);need(!ctorPatch->failed());
}
void wideCopy(std::wstring* dst,const std::wstring& src){
 bool compat=ctorCalls==2&&src==L"COMPLETEGAME";if(compat){++copyCalls;if(cs->fault==PairCopyThrow&&copyCalls==1){need(*(const int*)((const char*)src.c_str()-8)<0);failScalarAllocation=true;}}
 copyPatch->restore();try{reinterpret_cast<void(*)(std::wstring*,const std::wstring&)>(qplWideCopy)(dst,src);}catch(...){failScalarAllocation=false;throw;}failScalarAllocation=false;
 copyPatch->redirect(qplWideCopy,qplWideCopy,&wideCopy);need(!copyPatch->failed());
}
// The game PLT does not observe libstdc++'s internal COW allocator calls.
// Follow GameUILoadingVisibleTest's checked DSO-relocation technique, preserving
// both original GOT values (including lazy state) and page protections.
void require(bool value){if(!value){std::fprintf(stderr,"    QPL library relocation setup failed\n");_exit(71);}}
struct ScalarRelocations {uintptr_t base;void** slots[2];unsigned found[2];};
int findScalarRelocations(struct dl_phdr_info* info,size_t,void* raw){
 ScalarRelocations* wanted=static_cast<ScalarRelocations*>(raw);if(info->dlpi_addr!=wanted->base)return 0;
 const ElfW(Dyn)* dynamic=0;for(unsigned i=0;i<info->dlpi_phnum;++i)if(info->dlpi_phdr[i].p_type==PT_DYNAMIC)dynamic=reinterpret_cast<const ElfW(Dyn)*>(info->dlpi_addr+info->dlpi_phdr[i].p_vaddr);
 require(dynamic!=0);uintptr_t strings=0,symbols=0,relocations=0;size_t bytes=0;unsigned kind=0;
 for(const ElfW(Dyn)* d=dynamic;d->d_tag!=DT_NULL;++d){if(d->d_tag==DT_STRTAB)strings=d->d_un.d_ptr;if(d->d_tag==DT_SYMTAB)symbols=d->d_un.d_ptr;if(d->d_tag==DT_JMPREL)relocations=d->d_un.d_ptr;if(d->d_tag==DT_PLTRELSZ)bytes=d->d_un.d_val;if(d->d_tag==DT_PLTREL)kind=d->d_un.d_val;}
 require(strings&&symbols&&relocations&&kind==DT_RELA&&bytes%sizeof(ElfW(Rela))==0);
 if(strings<wanted->base)strings+=wanted->base;if(symbols<wanted->base)symbols+=wanted->base;if(relocations<wanted->base)relocations+=wanted->base;
 const ElfW(Sym)* sym=reinterpret_cast<const ElfW(Sym)*>(symbols);const ElfW(Rela)* rel=reinterpret_cast<const ElfW(Rela)*>(relocations);
 for(unsigned i=0;i<bytes/sizeof(*rel);++i){const char* name=reinterpret_cast<const char*>(strings)+sym[ELF64_R_SYM(rel[i].r_info)].st_name;int index=!std::strcmp(name,"_Znwm")?0:!std::strcmp(name,"_ZdlPv")?1:-1;
  if(index>=0){require(ELF64_R_TYPE(rel[i].r_info)==R_X86_64_JUMP_SLOT);require(!wanted->found[index]);wanted->slots[index]=reinterpret_cast<void**>(wanted->base+rel[i].r_offset);++wanted->found[index];}}
 return 1;
}
class LibraryScalars {
 void* handle;void** slots[2];void* saved[2];void* pages[2];int protections[2];size_t pageSize;
 LibraryScalars(const LibraryScalars&);LibraryScalars& operator=(const LibraryScalars&);
public:
 LibraryScalars():handle(0),pageSize(0){
  const char* constructor="_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_";void* actual=dlsym(RTLD_DEFAULT,constructor);Dl_info identity;
  require(actual&&dladdr(actual,&identity)&&identity.dli_fname&&std::strstr(identity.dli_fname,"libstdc++")&&identity.dli_saddr==actual);
  handle=dlopen(identity.dli_fname,RTLD_LAZY|RTLD_NOLOAD);require(handle!=0);
  ScalarRelocations relocation={reinterpret_cast<uintptr_t>(identity.dli_fbase),{0,0},{0,0}};dl_iterate_phdr(&findScalarRelocations,&relocation);
  pageSize=static_cast<size_t>(sysconf(_SC_PAGESIZE));require(pageSize&&!(pageSize&(pageSize-1)));
  const char* symbols[]={"_Znwm","_ZdlPv"};void* callbacks[]={reinterpret_cast<void*>(&scalarNew),reinterpret_cast<void*>(&scalarDelete)};
  for(unsigned i=0;i<2;++i){require(relocation.found[i]==1&&relocation.slots[i]);slots[i]=relocation.slots[i];saved[i]=*slots[i];void* actualAllocator=dlsym(handle,symbols[i]);require(actualAllocator!=0);
   if(saved[i]!=actualAllocator){Dl_info lazy;require(dladdr(saved[i],&lazy)&&lazy.dli_fbase==identity.dli_fbase);const unsigned char* stub=static_cast<const unsigned char*>(saved[i]);require(stub[0]==0x68&&stub[5]==0xe9&&stub[-6]==0xff&&stub[-5]==0x25);int32_t offset;std::memcpy(&offset,stub-4,4);require(reinterpret_cast<const void*>(stub+offset)==slots[i]);}
   uintptr_t address=reinterpret_cast<uintptr_t>(slots[i]);pages[i]=reinterpret_cast<void*>(address&~(pageSize-1));require(address+sizeof(void*)<=reinterpret_cast<uintptr_t>(pages[i])+pageSize);
   FILE* maps=std::fopen("/proc/self/maps","r");require(maps!=0);char line[512];bool found=false;protections[i]=0;
   while(std::fgets(line,sizeof(line),maps)){unsigned long lo,hi;char perms[5];if(std::sscanf(line,"%lx-%lx %4s",&lo,&hi,perms)==3&&lo<=address&&address+sizeof(void*)<=hi){protections[i]=(perms[0]=='r'?PROT_READ:0)|(perms[1]=='w'?PROT_WRITE:0)|(perms[2]=='x'?PROT_EXEC:0);found=true;break;}}
   std::fclose(maps);require(found&&(protections[i]&PROT_READ));require(mprotect(pages[i],pageSize,protections[i]|PROT_WRITE)==0);*slots[i]=callbacks[i];require(mprotect(pages[i],pageSize,protections[i])==0);
  }
 }
 ~LibraryScalars(){for(unsigned i=2;i;--i){unsigned j=i-1;require(mprotect(pages[j],pageSize,protections[j]|PROT_WRITE)==0);*slots[j]=saved[j];require(mprotect(pages[j],pageSize,protections[j])==0);require(*slots[j]==saved[j]);}require(dlclose(handle)==0);}
};
int keyRefs[8]; unsigned char ownerBefore[0xd0];
int refs(const std::wstring& s){return *(const int*)((const char*)s.c_str()-8);}
void setup(){
 errors=firstErrorLine=eventIndex=eventCount=readCalls=resetCalls=loadCalls=randomCalls=trueResets=arrayCalls=arrayDeletes=ctorCalls=copyCalls=scalarCount=0;
 expectedResetCalls=expectedLoadCalls=expectedRandomCalls=expectedTrueResets=expectedArrayCalls=expectedArrayDeletes=expectedCtorCalls=expectedCopyCalls=0;
 expectedCount=expectedCapacity=expectedPosition=expectedCaught=byteCount=loadCursor=0;tracking=false;growthMutation=false;failScalarAllocation=false;initialArrayLive=true;oldGrowth=newestArray=0;
 std::memset(loaded,0,sizeof(loaded));std::memset(reset,0,sizeof(reset));std::memset(randomValue,0,sizeof(randomValue));
 std::memset(expectedLoaded,0,sizeof(expectedLoaded));std::memset(expectedAccepted,0,sizeof(expectedAccepted));std::memset(expectedReset,0,sizeof(expectedReset));
 std::memset(hasKey,0,sizeof(hasKey));std::memset(completionKey,0,sizeof(completionKey));std::memset(expectedComplete,0,sizeof(expectedComplete));
 for(unsigned i=0;i<16;++i)expectedSlots[i]=7;
 keys[0]=L"A";keys[1]=L"B";keys[2]=L"C";const wchar_t nul[]={L'N',0,L'X'};keys[3].assign(nul,3);
 const wchar_t raw16[]={wchar_t(0xd83d),wchar_t(0xde00)};keys[4].assign(raw16,2);keys[5]=L"";keys[6]=L"COMPLETEGAME";keys[7].assign(1,wchar_t(0x1f600));
 if(cs->scenario==RawNames){for(unsigned i=0;i<8;++i)hasKey[i]=completionKey[i]=i!=6;}
 else if(cs->scenario==Compatibility){hasKey[0]=true;hasKey[6]=cs->mode/2!=0;completionKey[6]=(cs->mode%2)!=0;}
 else if(cs->scenario!=Empty&&cs->scenario!=ShortHeader&&cs->scenario!=UnsignedSeek){hasKey[0]=hasKey[1]=hasKey[2]=true;completionKey[0]=completionKey[1]=completionKey[2]=true;}
 autotest::g_arenaUsed=0;unsigned char* raw=(unsigned char*)autotest::allocate(0xf0);std::memset(raw,0xa7,0xf0);owner=raw+16;
 resource=autotest::allocate(32);for(unsigned i=0;i<8;++i){object[i]=autotest::allocate(0x70);std::memset(object[i],0x6d,0x70);new((char*)object[i]+0x50)std::wstring(keys[i]);at<unsigned char>(object[i],0x26)=1;expectedAccepted[i]=1;}
 names=new((char*)owner+0x40)Names;complete=new((char*)owner+0x70)Complete;list=(List*)((char*)owner+0x18);
 // Scrambled insertion order, independent expected reset order below.
 const unsigned insertOrder[]={4,2,7,1,6,3,0,5};for(unsigned j=0;j<8;++j){unsigned i=insertOrder[j];if(hasKey[i])names->insert(Names::value_type(keys[i],object[i]));if(completionKey[i])complete->insert(Complete::value_type(keys[i],true));}
 complete->insert(Complete::value_type(L"unrelated completion",true));
 list->grow=cs->scenario==Growth?2:3;list->pad=0xfedc3210;list->count=2;list->capacity=3;initialArray=(void**)std::malloc(24);for(unsigned i=0;i<3;++i)initialArray[i]=object[7-i];list->data=initialArray;
 expect(6,0,0,0,0,0);expectedArrayDeletes=1;
 const unsigned resetOrder[]={5,0,1,2,6,3,4,7};for(unsigned j=0;j<8;++j){unsigned i=resetOrder[j];if(hasKey[i]){expect(3,i,0,0,0,0);++expectedResetCalls;++expectedReset[i];expectedAccepted[i]=0;if(cs->fault==ResetThrow){expectedCaught=1;break;}}}
 if(!expectedCaught){
 switch(cs->scenario){
 case Empty:header(0,0);expectedPosition=8;break;
 case RawNames:
  header(6,0);completedName(keys[0]);completedName(L"absent completion");completedName(keys[3]);completedName(keys[4]);completedName(keys[5]);completedName(keys[1]);
  expectedComplete[0]=expectedComplete[1]=expectedComplete[3]=expectedComplete[4]=expectedComplete[5]=true;
  {unsigned p=byteCount;u32(5);expectRead(4,1,p,1);}
  record(4,keys[4],1,0,1,3,24);record(3,keys[3],1,0,2,3,0);record(5,keys[5],1,0,3,3,0);record(0,keys[0],1,0,4,6,48);record(1,keys[1],1,0,5,6,0);break;
 case SkipRecords:{
  header(0,4);std::wstring missing=L"missing";unsigned end=byteCount+6+2*missing.size()+3;skipped(missing,3,end);
  end=byteCount+6+2*keys[2].size()+4;skipped(keys[2],4,end);
  unsigned first=byteCount;record(0,keys[0],1,0,1,3,24,0);record(1,keys[1],1,0,2,3,0,0);
  // A valid alternate B frame makes a forced-end-seek mutant complete with
  // different state, rather than relying on a crash/uninitialized read.
  unsigned alternate=byteCount;for(unsigned i=0;i<4;++i)bytes[first+i]=(unsigned char)(alternate>>(8*i));
  u32(alternate+11);u16(1);u16('B');bytes[byteCount++]=1;bytes[byteCount++]=0;bytes[byteCount++]=1;
  break;}
 case Growth:
  header(0,7);record(0,keys[0],1,1,1,2,16);if(expectedCaught)break;
  record(1,keys[1],0,0,2,2,0);if(expectedCaught)break;
  record(0,keys[0],0,1,3,4,32);if(expectedCaught)break;
  record(2,keys[2],1,0,4,4,0);record(1,keys[1],0,1,5,6,48);record(0,keys[0],1,0,6,6,0);record(2,keys[2],0,0,7,8,64);break;
 case NegativeActive:header(0,0xffffffffu);expectedPosition=8;break;
 case ReentrantGrowth:header(0,4);record(0,keys[0],1,0,1,3,24);record(1,keys[1],1,0,2,3,0);record(2,keys[2],1,0,3,3,0);record(0,keys[0],1,0,2,6,48);break;
 case Spare:header(0,2);record(0,keys[0],1,0,2,4,0);record(1,keys[1],1,0,3,4,0);break;
 case UnsignedSeek:header(0,1);skipped(L"absent",0,0x80000020u);break;
 case ShortHeader:
  // Only end/length reads are short; both locals have defined zero defaults.
  // Active count is fully supplied. No short raw16 unit is ever consumed.
  header(0,1);expectRead(4,1,8,0);expectRead(2,1,8,0);expect(2,0,SEEK_SET,0,8,0);expectedPosition=0;break;
 case Compatibility:
  header(1,0);completedName(keys[6]);expectedComplete[6]=completionKey[6];
  {unsigned p=byteCount;u32(1);expectRead(4,1,p,1);}
  record(0,keys[0],1,0,1,3,24);
  if(cs->version<=20){expectedCtorCalls=1;if(cs->fault==FirstCtorThrow){expectedCaught=2;break;}
   if(cs->mode/2==1){expect(8,6,1,3,0,byteCount);++expectedTrueResets;++expectedReset[6];expectedAccepted[6]=0;
    if(cs->fault==CompatThrow){expectedCaught=1;break;}
    expectedCtorCalls=2;if(cs->fault==SecondCtorThrow){expectedCaught=2;break;}
    if(!completionKey[6]){expectedCopyCalls=1;if(cs->fault==PairCopyThrow||cs->fault==NodeNewThrow){expectedCaught=2;break;}expectedCopyCalls=2;completionKey[6]=true;}
    expectedComplete[6]=false;
   }
  }
  break;
 }
 }
 // Random throw cases use one rejected random quest, after the first append.
 // Their completed input count stays fully initialized even though unwinding
 // deliberately prevents later records from being consumed.
 for(unsigned i=0;i<8;++i)keyRefs[i]=refs(keys[i]);
 std::memcpy(ownerBefore,owner,sizeof(ownerBefore));file=std::tmpfile();if(!file)_exit(71);if(byteCount&&std::fwrite(bytes,1,byteCount,file)!=byteCount)_exit(71);std::rewind(file);
}
void snapshot(unsigned caught){
 if(errors)std::fprintf(stderr,"    QPL final %s caught=%u/%u events=%u/%u reset=%u/%u load=%u/%u random=%u/%u full=%u/%u array=%u/%u delete=%u/%u ctor=%u/%u copy=%u/%u scalarLive=%u count/cap=%u/%u expected=%u/%u pos=%u/%u\n",candidateSide?"candidate":"original",caught,expectedCaught,eventIndex,eventCount,resetCalls,expectedResetCalls,loadCalls,expectedLoadCalls,randomCalls,expectedRandomCalls,trueResets,expectedTrueResets,arrayCalls,expectedArrayCalls,arrayDeletes,expectedArrayDeletes,ctorCalls,expectedCtorCalls,copyCalls,expectedCopyCalls,liveScalars(),list->count,list->capacity,expectedCount,expectedCapacity,position(),expectedPosition);
 need(caught==expectedCaught);need(eventIndex==eventCount);need(resetCalls==expectedResetCalls&&loadCalls==expectedLoadCalls&&randomCalls==expectedRandomCalls&&trueResets==expectedTrueResets);
 need(arrayCalls==expectedArrayCalls&&arrayDeletes==expectedArrayDeletes&&ctorCalls==expectedCtorCalls&&copyCalls==expectedCopyCalls);
 need(list->count==expectedCount&&list->capacity==expectedCapacity&&list->grow==(cs->scenario==Growth?2u:3u)&&list->pad==0xfedc3210);
 need(position()==expectedPosition);need(!std::ferror(file));need(!std::feof(file));need(!initialArrayLive);
 if(list->data){for(unsigned i=0;i<list->capacity&&i<16;++i){need(list->data[i]==object[expectedSlots[i]]);n(id(list->data[i]));}}
 else need(!list->count&&(list->capacity==0||cs->fault==NullArrayThrow));
 unsigned nc=1;for(unsigned i=0;i<8;++i)if(completionKey[i])++nc;need(complete->size()==nc);need(complete->find(L"unrelated completion")!=complete->end()&&!complete->find(L"unrelated completion")->second);
 for(unsigned i=0;i<8;++i){Complete::iterator it=complete->find(keys[i]);need((it!=complete->end())==completionKey[i]);if(it!=complete->end()){need(it->second==expectedComplete[i]);cap->addText(it->first);n(it->second);}
  // Actual accepted lookup consumers observe the loaded maps, no proxy wrapper.
  void* wanted=hasKey[i]?object[i]:0;if((cs->scenario==SkipRecords&&i==2)||(cs->scenario==Compatibility&&cs->mode/2==2&&i==6))wanted=0;
  need(qplName(owner,keys[i])==reinterpret_cast<long long>(wanted));need((unsigned char)qplComplete(owner,keys[i])==(completionKey[i]&&expectedComplete[i]?1u:0u));
  need(loaded[i]==expectedLoaded[i]&&reset[i]==expectedReset[i]&&at<unsigned char>(object[i],0x26)==expectedAccepted[i]);need(refs(keys[i])==keyRefs[i]);n(loaded[i]);n(reset[i]);n(at<unsigned char>(object[i],0x26));
 }
 need(complete->find(L"absent completion")==complete->end());
 bool inserted=cs->scenario==Compatibility&&cs->version<=20&&cs->mode==2&&!caught;
 need(liveScalars()==(inserted?2u:0u));
 unsigned char actual[0xd0];std::memcpy(actual,owner,sizeof(actual));std::memset(actual+0x18,0,16);std::memset(ownerBefore+0x18,0,16);std::memset(actual+0x40,0,96);std::memset(ownerBefore+0x40,0,96);need(!std::memcmp(actual,ownerBefore,sizeof(actual)));
 for(unsigned i=0;i<16;++i)need(((unsigned char*)owner)[-16+(int)i]==0xa7&&((unsigned char*)owner)[0xd0+i]==0xa7);
 n(caught);n(eventIndex);n(list->count);n(list->capacity);n(position());n(liveScalars());n(growthMutation);n(firstErrorLine);n(0xd2f8a011u);n(errors);
}
void side(void* raw,autotest::Capture& out,bool candidate){cs=(Case*)raw;cap=&out;candidateSide=candidate;setup();unsigned caught=0;typedef void(*Fn)(void*,FILE*,unsigned,void*);Fn fn=candidate?&qplNew:&qplOld;
 {
  LibraryScalars libraryScalars;
  detour::Set boundaries,arrays,scalars,reads,seeks,ctors,copies;readPatch=&reads;seekPatch=&seeks;ctorPatch=&ctors;copyPatch=&copies;
  TL_REDIRECT(boundaries,qplQuestLoad,&questLoad);TL_REDIRECT(boundaries,qplReinitialize,&reinitialize);TL_REDIRECT(boundaries,qplRandom,&random);
  arrays.redirect(qplArrayNew,qplArrayNew,&arrayNew);arrays.redirect(qplArrayDelete,qplArrayDelete,&arrayDelete);
  scalars.redirect(qplScalarNew,qplScalarNew,&scalarNew);scalars.redirect(qplScalarDelete,qplScalarDelete,&scalarDelete);
  reads.redirect(qplFread,qplFread,&read);seeks.redirect(qplFseek,qplFseek,&seek);ctors.redirect(qplWideCtor,qplWideCtor,&wideCtor);copies.redirect(qplWideCopy,qplWideCopy,&wideCopy);
  if(boundaries.failed()||arrays.failed()||scalars.failed()||reads.failed()||seeks.failed()||ctors.failed()||copies.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  tracking=true;if(!autotest::beginInvocation(out,fn))return;
  try{fn(owner,file,cs->version,resource);out.callCompleted=1;}catch(const Stop&){caught=1;}catch(const std::bad_alloc&){caught=2;}catch(...){caught=3;}
  tracking=false;
 }
 snapshot(caught);std::fclose(file);delete[] list->data;names->~Names();complete->~Complete();for(unsigned i=0;i<8;++i)at<std::wstring>(object[i],0x50).~basic_string();
}
void original(void* p,autotest::Capture& o){side(p,o,false);}void replacement(void* p,autotest::Capture& o){side(p,o,true);}
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0xd2f8a011u&&!tail[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(replacement,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(c.fault){ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd2f8a0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);}
 else if(cv.observe(host,a,b))ok=false;
 if(!ok){unsigned first[3]={0,0,0},second[3]={0,0,0};if(a.capture.length>=12)std::memcpy(first,a.capture.data+a.capture.length-12,12);if(b.capture.length>=12)std::memcpy(second,b.capture.data+b.capture.length-12,12);std::fprintf(stderr,"    QPL pair scenario=%u version=%u mode=%u fault=%u original line/errors=%u/%u candidate=%u/%u\n",c.scenario,c.version,c.mode,c.fault,first[0],first[2],second[0],second[2]);host->log("    persistence oracle first-line/errors=%u/%u,%u/%u\n",first[0],first[2],second[0],second[2]);host->log("    persistence load scenario=%u version=%u mode=%u fault=%u status=%d/%d oracle=%u/%u issue=%u/%u\n",c.scenario,c.version,c.mode,c.fault,a.childStatus,b.childStatus,good(a),good(b),a.capture.issue,b.capture.issue);}
 return ok;
}
}
TL_TEST(questmanager_persistence_load){using namespace qpl;autotest::Coverage cv("questmanager_persistence_load",0xd2f8a0);unsigned completed=0;for(unsigned s=Empty;s<Compatibility;++s){Case c={s,21,0,NoFault};if(!pair(host,cv,c)){cv.report(host);return 1;}++completed;}Case mutation={Growth,21,1,NoFault};if(!pair(host,cv,mutation)){cv.report(host);return 1;}++completed;cv.report(host);return cv.completed!=completed||cv.different||cv.missing;}
TL_TEST(questmanager_persistence_compatibility){using namespace qpl;autotest::Coverage cv("questmanager_persistence_compatibility",0xd2f8a0);const unsigned versions[]={19,20,21,0xffffffffu};unsigned completed=0;for(unsigned v=0;v<4;++v)for(unsigned mode=0;mode<6;++mode){Case c={Compatibility,versions[v],mode,NoFault};if(!pair(host,cv,c)){cv.report(host);return 1;}++completed;}cv.report(host);return cv.completed!=completed||cv.different||cv.missing;}
TL_TEST(questmanager_persistence_load_exceptions){using namespace qpl;autotest::Coverage cv("persistence load expected unwinds excluded",0xd2f8a0);
 const Case cases[]={{Growth,21,0,ResetThrow},{Growth,21,0,LoadThrow},{Growth,21,0,NullArrayThrow},{Growth,21,0,ExistingArrayThrow},{Growth,21,0,RandomThrow},{Growth,21,0,ReinitThrow},{Compatibility,20,2,CompatThrow},{Compatibility,20,2,FirstCtorThrow},{Compatibility,20,2,SecondCtorThrow},{Compatibility,20,2,PairCopyThrow},{Compatibility,20,2,NodeNewThrow}};
 for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i)if(!pair(host,cv,cases[i]))return 1;
 host->log("    persistence load: %u LSDA-reachable expected unwinds; no completed coverage credited\n",unsigned(sizeof(cases)/sizeof(cases[0])));return 0;}
