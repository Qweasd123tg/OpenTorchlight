// d2ec10. Independent framing/stdio oracle; the controlled Quest boundary is
// explicitly separate from the real original Quest/tmpfile integration below.
// UTF conversion always forwards to the original implementation. Expected
// exceptions are checked separately and never receive completed-call credit.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include <dlfcn.h>
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void,qpsOldSave,(void*,FILE*),"_ZN13CQuestManager4saveEP8_IO_FILE")
extern "C" void qpsNewSave(void*,FILE*) __asm__("_ZN13CQuestManager4saveEP8_IO_FILE");
TL_FUNCTION(qpsQuestSave,"_ZN6CQuest4saveEP8_IO_FILE")
TL_FUNCTION(qpsConvert,"_Z12UTF32ToUTF16RKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,qpsQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qpsQuestDtor,(void*),"_ZN6CQuestD1Ev")
extern "C" char qpsWrite[] __asm__("fwrite");
extern "C" char qpsTell[] __asm__("ftell");
extern "C" char qpsSeek[] __asm__("fseek");
extern "C" char qpsCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qpsRepDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char qpsStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
extern "C" char qpsNew[] __asm__("_Znwm");
extern "C" char qpsDelete[] __asm__("_ZdlPv");

namespace qps {
typedef std::wstring Wide;
typedef std::basic_string<unsigned short> Utf16;
typedef std::map<Wide,void*> Quests;
typedef std::map<Wide,bool> Completed;
typedef char WideABI[sizeof(Wide)==8?1:-1];
typedef char MapABI[sizeof(Quests)==48&&sizeof(Completed)==48?1:-1];
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
struct Stop {unsigned site;explicit Stop(unsigned s):site(s){}};
// scenario: 0 empty, 1 completion-map/key/name roles, 2 text,
// 3 placeholder replaces slot, 4 length-write replaces slot/name,
// 5 count-header grows, 6 Quest shrinks, 7 Quest grows,
// 8 Quest republishes buffer, 9 capacity fallback, 10 signed count,
// 11 pre-existing EOF, 12 unsigned/truncated sparse offsets,
// 13 count-header empties, 14 lifetimes, 15 completed short I/O,
// 16 active short I/O, 17 ftell error, 18 fseek error. offset selects
// the first/second prescribed failure in17/18. text: empty, BMP, NUL, scalar, scalar+BMP,
// 65536 wchar, 1024 BMP, 512 supplementary scalars.
// faults: 1 real leaked-wide-copy allocation, 2 UTF allocation, 3 name-length write,
// 4 name-data write, 5 Quest after partial payload, 6 post-Quest tell,
// 7 backpatch seek, 8 backpatch write. Never throw from final EOF seek.
struct Case {unsigned scenario,text,leaked,fault,offset;};
enum {Write=1,Tell=2,Seek=3,Quest=4};
enum {Ordinary=0,ActiveLength=3,ActiveData=4,QuestPayload=5,EndTell=6,PatchSeek=7,PatchWrite=8};
struct Event {
 unsigned kind,tag; unsigned long long position,a,b; size_t length,taken;
 unsigned char bytes[4096];
};
struct Cell {unsigned long long offset;unsigned char value;};
struct Image {
 Cell cells[8192];unsigned count;unsigned long long position,end;
 void clear(unsigned long long p,unsigned long long e){count=0;position=p;end=e;}
 void put(const unsigned char* bytes,size_t n){
  for(size_t j=0;j<n;++j){unsigned k=0;for(;k<count;++k)if(cells[k].offset==position+j)break;
   if(k==count){if(count==8192)_exit(72);cells[count++].offset=position+j;}cells[k].value=bytes[j];}
  position+=n;if(position>end)end=position;
 }
};
struct Life {
 void* wideRep;void* utfRep;unsigned id;bool wideOwned,utfOwned;
 unsigned wideFrees,utfFrees,wideOrder,utfOrder;
};
static const Case* cs;static autotest::Capture* cap;
static void* owner;static void* quests[3];static void** list;static void** alternate;
static Quests* map;static Completed* completed;static FILE* stream;
static Event expected[128];static unsigned expectedCount,eventIndex,errors,firstError,writes,questCalls,copies,conversions;
static unsigned faultHits,releaseOrder,lifeCount,conversionAllocations;
static unsigned tellCalls,seekCalls,tellFailures,seekFailures;
static bool stopped,inConversion,inWideCopy,activePhase;
static Image planned,actual;
static Life lives[8];static int initialRefs[3];
static Wide originalNames[3],expectedNames[8];static unsigned expectedIds[8],expectedRecords;
static unsigned char encoded[4096];static unsigned encodedLength,declaredLength;
static unsigned expectedFinalCount,expectedInitialCount,expectedFinalCapacity;
static unsigned long long initialPosition,initialEnd;
static unsigned char ownerBefore[0xd0],questBefore[3][0x218];
static detour::Set *copyPatch,*convertPatch,*newPatch,*deletePatch,*widePatch,*stringPatch;
static void* forwardedWideRep;

static void n(unsigned v){cap->add(&v,sizeof(v));}
static void q(unsigned long long v){cap->add(&v,sizeof(v));}
static void need(bool v,unsigned code){if(!v){if(!errors)firstError=code;++errors;n(0xf0000000u+code);}}
static int refs(const Wide& s){return *reinterpret_cast<const int*>((const char*)s.c_str()-8);}
static void fail(unsigned site){++faultHits;throw Stop(site);}
static void le(unsigned char* p,unsigned long long value,unsigned width){for(unsigned i=0;i<width;++i)p[i]=(unsigned char)(value>>(8*i));}
static unsigned identity(void* p){for(unsigned i=0;i<3;++i)if(p==quests[i])return i;need(false,1);return 99;}
static Wide& name(unsigned i){return at<Wide>(quests[i],0x50);}
static void scalarBytes(unsigned char* p,unsigned value,unsigned width){le(p,value,width);}
static Event* next(unsigned kind,unsigned tag){
 if(stopped)return 0;if(expectedCount==128)_exit(72);
 Event* e=&expected[expectedCount++];std::memset(e,0,sizeof(*e));e->kind=kind;e->tag=tag;e->position=planned.position;return e;
}
static void expectWrite(const unsigned char* p,size_t size,size_t count,unsigned tag=Ordinary,size_t take=~size_t(0)){
 Event* e=next(Write,tag);if(!e)return;e->a=size;e->b=count;e->length=size*count;
 if(e->length>sizeof(e->bytes))_exit(72);if(e->length)std::memcpy(e->bytes,p,e->length);
 e->taken=take==~size_t(0)?e->length:take;
 if(cs->fault==tag&&tag!=Ordinary&&tag!=QuestPayload){stopped=true;e->taken=0;return;}
 planned.put(p,e->taken);
}
static void expectScalar(unsigned value,unsigned width,unsigned tag=Ordinary){unsigned char p[8];scalarBytes(p,value,width);expectWrite(p,width,1,tag);}
static void expectTell(unsigned tag=Ordinary){
 Event* e=next(Tell,tag);if(!e)return;
 bool fails=cs->scenario==17&&(cs->offset==0?tag==Ordinary:tag==EndTell);
 e->a=fails?~0ULL:planned.position;if(cs->fault==tag&&tag!=Ordinary)stopped=true;
}
static void expectSeek(unsigned long long offset,int origin,unsigned tag=Ordinary){
 Event* e=next(Seek,tag);if(!e)return;e->a=offset;e->b=origin;
 if(cs->fault==tag&&tag!=Ordinary){stopped=true;return;}
 if(cs->scenario==18&&(cs->offset==0?tag==PatchSeek:origin==SEEK_END)){e->taken=1;return;}
 planned.position=origin==SEEK_SET?offset:origin==SEEK_END?planned.end+offset:planned.position+offset;
}
static void encode(unsigned text){
 encodedLength=declaredLength=0;std::memset(encoded,0,sizeof(encoded));
 if(text==0)return;
 if(text==1){declaredLength=3;const unsigned units[]={0x41,0x416,0x4efb};for(unsigned i=0;i<3;++i)le(encoded+2*i,units[i],2);encodedLength=6;}
 if(text==2){declaredLength=3;le(encoded,0x41,2);le(encoded+2,0,2);le(encoded+4,0x42,2);encodedLength=6;}
 if(text==3){declaredLength=1;le(encoded,0xd83d,2);encodedLength=2;}
 if(text==4){declaredLength=2;le(encoded,0xd83d,2);le(encoded+2,0xde00,2);encodedLength=4;}
 // Original converter has only a 1024-unit scratch buffer. A 65536-wchar
 // input fails conversion, returns empty, and these methods request ZERO
 // bytes. No over-capacity nonzero-length memory read is authorized here.
 if(text==5)return;
 if(text==6){declaredLength=1024;encodedLength=2048;for(unsigned i=0;i<1024;++i)le(encoded+2*i,0x51,2);}
 if(text==7){declaredLength=512;encodedLength=1024;for(unsigned i=0;i<256;++i){le(encoded+4*i,0xd83d,2);le(encoded+4*i+2,0xde00,2);}}
}
static Wide textValue(unsigned text){
 if(text==0)return Wide();if(text==1)return Wide(L"A\u0416\u4efb");
 if(text==2){const wchar_t s[]={L'A',0,L'B'};return Wide(s,3);}
 if(text==3)return Wide(1,wchar_t(0x1f600));
 if(text==4){const wchar_t s[]={wchar_t(0x1f600),L'A'};return Wide(s,2);}
 if(text==5)return Wide(65536,L'Q');if(text==6)return Wide(1024,L'Q');
 return Wide(512,wchar_t(0x1f600));
}
static void addRecord(unsigned id,const Wide& value){
 if(expectedRecords==8)_exit(72);expectedIds[expectedRecords]=id;
 expectedNames[expectedRecords].assign(value.c_str(),value.size());++expectedRecords;
}
static void record(unsigned index,bool useEncoded){
 unsigned id=expectedIds[index];unsigned char simple[8];const unsigned char* bytes=encoded;
 unsigned length=declaredLength,dataLength=encodedLength;
 if(!useEncoded){length=expectedNames[index].size();dataLength=length*2;
  if(dataLength>sizeof(simple))_exit(72);for(unsigned i=0;i<length;++i)le(simple+2*i,expectedNames[index].c_str()[i],2);bytes=simple;}
 unsigned long long start=cs->scenario==17&&cs->offset==0?~0ULL:planned.position;expectTell();expectScalar((unsigned)start,4);
 if(cs->fault==1){stopped=true;return;} // copy construction has not committed
 expectScalar(length,2,ActiveLength);
 if(cs->fault==2){stopped=true;return;} // original converter allocation fails
 expectWrite(bytes,2*length,1,ActiveData,cs->scenario==16?2:dataLength);
 Event* e=next(Quest,Ordinary);if(e)e->a=id;
 unsigned char payload[]={0xa0,(unsigned char)(0x30+id),0x5c};
 expectWrite(payload,1,3,QuestPayload);
 if(cs->fault==5){stopped=true;return;}
 unsigned long long end=cs->scenario==17&&cs->offset==1?~0ULL:planned.position;expectTell(EndTell);
 expectSeek((unsigned)start,SEEK_SET,PatchSeek);expectScalar((unsigned)end,4,PatchWrite);expectSeek(0,SEEK_END);
}
static void setup(){
 errors=firstError=expectedCount=eventIndex=writes=questCalls=copies=conversions=faultHits=releaseOrder=lifeCount=conversionAllocations=expectedRecords=0;
 tellCalls=seekCalls=tellFailures=seekFailures=0;
 stopped=inConversion=inWideCopy=activePhase=false;forwardedWideRep=0;std::memset(lives,0,sizeof(lives));autotest::g_arenaUsed=0;
 owner=autotest::allocate(0xd0);list=(void**)autotest::allocate(3*sizeof(void*));alternate=(void**)autotest::allocate(3*sizeof(void*));
 stream=reinterpret_cast<FILE*>(autotest::allocate(16));map=new((char*)owner+0x40)Quests;completed=new((char*)owner+0x70)Completed;
 for(unsigned i=0;i<3;++i){quests[i]=autotest::allocate(0x218);new((char*)quests[i]+0x50)Wide(i==0?L"A":i==1?L"B":L"C");list[i]=quests[i];alternate[i]=quests[i];}
 alternate[1]=quests[2];expectedInitialCount=1;expectedFinalCount=1;expectedFinalCapacity=3;
 initialPosition=cs->scenario==12?(cs->offset==0?0x80000010ULL:cs->offset==1?0x100000010ULL:0xfffffff0ULL):cs->offset?7:0;
 if(cs->scenario==17||cs->scenario==18)initialPosition=7;
 initialEnd=cs->scenario==11||(cs->scenario==18&&cs->offset==1)?100:initialPosition;
 encode(cs->text);
 switch(cs->scenario){
 case 0:expectedInitialCount=expectedFinalCount=0;break;
 case 1:
  name(0)=L"hidden";name(1)=L"done";name(2)=L"done";
  (*map)[L"C"]=quests[2];(*map)[L"A"]=quests[0];(*map)[L"B"]=quests[1];
  (*completed)[L"hidden"]=false;(*completed)[L"done"]=true;(*completed)[L"A"]=true;(*completed)[L"orphan"]=true;
  // Every map-key lookup also exists, so a key/name semantic mutant remains
  // defined and produces a completed, observably different invocation.
  (*completed)[L"B"]=false;(*completed)[L"C"]=false;
  expectedInitialCount=expectedFinalCount=0;break;
 case 2:case 15:case 16:
  name(0)=textValue(cs->text);
  if(cs->scenario!=16){(*map)[textValue(cs->text)]=quests[1];name(1)=L"done";(*completed)[L"done"]=true;}
  if(cs->scenario==15)expectedInitialCount=expectedFinalCount=0;
  else addRecord(0,name(0));break;
 case 3:addRecord(1,name(1));break;
 case 4:addRecord(0,name(0));break;
 case 5:case 7:expectedFinalCount=2;addRecord(0,name(0));addRecord(1,name(1));break;
 case 6:expectedInitialCount=2;addRecord(0,name(0));break;
 case 8:expectedInitialCount=expectedFinalCount=2;addRecord(0,name(0));addRecord(2,name(2));break;
 case 9:expectedInitialCount=expectedFinalCount=2;expectedFinalCapacity=0;addRecord(0,name(0));addRecord(0,name(0));break;
 case 10:expectedInitialCount=expectedFinalCount=0x80000000u;break;
 case 11:expectedInitialCount=expectedFinalCount=2;addRecord(0,name(0));addRecord(1,name(1));break;
 case 13:expectedFinalCount=0;break;
 case 14:name(0)=L"LIFE";addRecord(0,name(0));break;
 default:addRecord(0,name(0));break;
 }
 at<void**>(owner,0x18)=list;at<unsigned>(owner,0x20)=expectedInitialCount;at<unsigned>(owner,0x24)=expectedFinalCapacity;at<unsigned>(owner,0x28)=11;
 if(cs->leaked&&!name(0).empty())name(0)[0]=name(0).c_str()[0];
 for(unsigned i=0;i<3;++i){originalNames[i].assign(name(i).c_str(),name(i).size());initialRefs[i]=refs(name(i));}
 planned.clear(initialPosition,initialEnd);actual.clear(initialPosition,initialEnd);
 if(cs->scenario==1){
  expectScalar(3,4);const unsigned char b[]={0x42,0},c[]={0x43,0};
  expectScalar(1,2);expectWrite(b,2,1);expectScalar(1,2);expectWrite(c,2,1);
 }else if(cs->scenario==2||cs->scenario==15){
  expectScalar(1,4);expectScalar(declaredLength,2);expectWrite(encoded,2,declaredLength,Ordinary,cs->scenario==15?2:encodedLength);
 }else expectScalar(0,4);
 expectScalar(expectedInitialCount,4);
 for(unsigned i=0;i<expectedRecords;++i)record(i,cs->scenario==2||cs->scenario==16);
 std::memcpy(ownerBefore,owner,sizeof(ownerBefore));for(unsigned i=0;i<3;++i)std::memcpy(questBefore[i],quests[i],sizeof(questBefore[i]));
}
static const Event* observed(unsigned kind,unsigned long long a,unsigned long long b,const void* data=0,size_t length=0){
 const Event* e=eventIndex<expectedCount?&expected[eventIndex]:0;
 n(kind);q(actual.position);q(a);q(b);n(length);if(length<=4096)cap->add(data,length);else need(false,2);
 need(e!=0,3);if(e){need(e->kind==kind,4);need(e->position==actual.position,5);need(e->a==a&&e->b==b,6);
  if(kind==Write)need(e->length==length&&length<=4096&&(!length||!std::memcmp(e->bytes,data,length)),7);}
 ++eventIndex;return e;
}
static size_t write(const void* data,size_t size,size_t count,FILE* f){
 need(f==stream,8);size_t length=size*count;
 if(size&&length/size!=count){need(false,9);return 0;}
 if(length>4096){need(false,10);return 0;}
 const Event* e=observed(Write,size,count,data,length);++writes;
 unsigned tag=e?e->tag:Ordinary;
 if(cs->fault==tag&&tag!=Ordinary&&tag!=QuestPayload)fail(tag);
 size_t taken=length;
 // Short writes are scripted by the concrete call's role. A partial element
 // moves the stream but is not counted as a completed fwrite element.
 if((cs->scenario==15&&writes==3)||(cs->scenario==16&&tag==ActiveData))taken=length<2?length:2;
 actual.put(static_cast<const unsigned char*>(data),taken);
 size_t result=size?taken/size:0;q(result);q(taken);
 if(cs->scenario==3&&writes==3)list[0]=quests[1];
 if(cs->scenario==4&&tag==ActiveLength){list[0]=quests[1];name(0)=L"X";}
 if((cs->scenario==5||cs->scenario==13)&&writes==2)at<unsigned>(owner,0x20)=expectedFinalCount;
 return result;
}
static long tell(FILE* f){
 need(f==stream,11);++tellCalls;
 bool failed=cs->scenario==17&&tellCalls==cs->offset+1;
 long result=failed?-1L:static_cast<long>(actual.position);const Event* e=observed(Tell,(unsigned long long)result,0);
 if(cs->fault==6&&e&&e->tag==EndTell)fail(6);
 if(failed){++tellFailures;errno=EIO;}n(failed?errno:0);return result;
}
static int seek(FILE* f,long offset,int origin){
 need(f==stream,12);++seekCalls;const Event* e=observed(Seek,(unsigned long long)offset,origin);
 if(cs->fault==7&&e&&e->tag==PatchSeek)fail(7);
 bool failed=cs->scenario==18&&seekCalls==cs->offset+1;
 if(failed){++seekFailures;errno=EIO;need(e&&e->taken==1,78);n(~0u);n(errno);return -1;}
 need(!e||e->taken==0,79);n(0);n(0);
 if(offset<0){need(false,13);return -1;}
 if(origin==SEEK_SET)actual.position=offset;else if(origin==SEEK_END)actual.position=actual.end+offset;
 else if(origin==SEEK_CUR)actual.position+=offset;else {need(false,14);return -1;}return 0;
}
static void questSave(void* self,FILE* f){
 unsigned id=identity(self);need(f==stream,15);observed(Quest,id,0);need(questCalls<expectedRecords&&id==expectedIds[questCalls],16);++questCalls;
 unsigned char payload[]={0xa0,(unsigned char)(0x30+id),0x5c};write(payload,1,3,f);
 if(cs->fault==5)fail(5);
 if(questCalls==1){
  if(cs->scenario==6||cs->scenario==7)at<unsigned>(owner,0x20)=expectedFinalCount;
  if(cs->scenario==8)at<void**>(owner,0x18)=alternate;
 }
}
// The real libstdc++ COW clone allocates through its own _Znwm JUMP_SLOT,
// which the game's PLT detour cannot see. This is the checked library-private
// GOT technique used by GameUILoadingVisibleTest, scoped to one actual copy.
static void requireRelocation(bool valid){if(!valid){std::fprintf(stderr,"    QPS library allocation relocation unavailable\n");_exit(71);}}
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
 need(inWideCopy&&cs->fault==1&&cs->leaked,73);need(refs(name(0))<0,74);
 need(size>=24+(name(0).size()+1)*sizeof(wchar_t),75);++faultHits;throw std::bad_alloc();
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
static void copy(Wide* destination,const Wide& source){
 unsigned id=99;for(unsigned i=0;i<3;++i)if(&source==&name(i))id=i;
 need(id!=99,17);need(copies<expectedRecords&&id==expectedIds[copies],18);
 n(0xc001);n(id);inWideCopy=true;copyPatch->restore();
 try{
  if(cs->fault==1){need(refs(source)<0,76);WideAllocationFault allocation;reinterpret_cast<void(*)(Wide*,const Wide&)>(qpsCopy)(destination,source);}
  else reinterpret_cast<void(*)(Wide*,const Wide&)>(qpsCopy)(destination,source);
 }
 catch(...){inWideCopy=false;copyPatch->redirect(qpsCopy,qpsCopy,&copy);throw;}
 inWideCopy=false;
 copyPatch->redirect(qpsCopy,qpsCopy,&copy);need(!copyPatch->failed(),19);
 need(copies<8,20);if(copies>=8)_exit(72);Life& life=lives[copies];
 life.id=id;life.wideRep=(void*)((const char*)destination->c_str()-24);life.wideOwned=!destination->empty()&&(initialRefs[id]<0||cs->scenario==4);
 need(*destination==expectedNames[copies],21);
 if(!destination->empty())need(refs(source)==(initialRefs[id]<0?-1:initialRefs[id]+1),22);
 ++copies;lifeCount=copies;activePhase=true;
}
static void* allocate(size_t size){
 if(inWideCopy&&cs->fault==1){need(cs->leaked!=0,59);++faultHits;throw std::bad_alloc();}
 if(inConversion){++conversionAllocations;if(cs->fault==2){++faultHits;throw std::bad_alloc();}}
 newPatch->restore();void* p=0;
 try{p=reinterpret_cast<void*(*)(size_t)>(qpsNew)(size);}catch(...){newPatch->redirect(qpsNew,qpsNew,&allocate);throw;}
 newPatch->redirect(qpsNew,qpsNew,&allocate);need(!newPatch->failed(),23);return p;
}
static void release(void* p){
 for(unsigned i=0;i<lifeCount;++i){Life& life=lives[i];
  if(p==life.utfRep&&life.utfOwned&&!life.utfFrees){++life.utfFrees;life.utfOrder=++releaseOrder;n(0xd016);n(i);}
  if(p!=forwardedWideRep&&p==life.wideRep&&life.wideOwned&&!life.wideFrees){++life.wideFrees;life.wideOrder=++releaseOrder;n(0xd032);n(i);}
 }
 deletePatch->restore();reinterpret_cast<void(*)(void*)>(qpsDelete)(p);deletePatch->redirect(qpsDelete,qpsDelete,&release);need(!deletePatch->failed(),24);
}
static void destroyWide(void* rep,const std::allocator<wchar_t>& allocator){
 // A shared-library _M_destroy can call its own operator-delete binding,
 // bypassing the game's PLT. Observe and forward that real boundary too.
 void* previous=forwardedWideRep;forwardedWideRep=rep;widePatch->restore();
 reinterpret_cast<void(*)(void*,const std::allocator<wchar_t>&)>(qpsRepDestroy)(rep,allocator);
 widePatch->redirect(qpsRepDestroy,qpsRepDestroy,&destroyWide);forwardedWideRep=previous;need(!widePatch->failed(),51);
 for(unsigned i=0;i<lifeCount;++i){Life& life=lives[i];if(rep==life.wideRep&&life.wideOwned&&!life.wideFrees){++life.wideFrees;life.wideOrder=++releaseOrder;n(0xd032);n(i);}}
}
static void destroyString(Wide* value){
 // EH calls D1 rather than the normal inlined _M_destroy path. Its internal
 // library destruction can bypass both game PLTs, so forward D1 itself and
 // observe release only when this pre-call representation has one owner.
 void* rep=(void*)((const char*)value->c_str()-24);bool releases=!value->empty()&&refs(*value)<=0;
 void* previous=forwardedWideRep;forwardedWideRep=rep;stringPatch->restore();
 reinterpret_cast<void(*)(Wide*)>(qpsStringDtor)(value);
 stringPatch->redirect(qpsStringDtor,qpsStringDtor,&destroyString);forwardedWideRep=previous;need(!stringPatch->failed(),77);
 if(releases)for(unsigned i=0;i<lifeCount;++i){Life& life=lives[i];if(rep==life.wideRep&&life.wideOwned&&!life.wideFrees){++life.wideFrees;life.wideOrder=++releaseOrder;n(0xd032);n(i);}}
}
static void convert(Utf16* destination,const Wide& source){
 ++conversions;n(0xc016);q(source.size());
 if(activePhase){need(copies>0&&source==expectedNames[copies-1],25);}
 convertPatch->restore();inConversion=true;
 try{reinterpret_cast<void(*)(Utf16*,const Wide&)>(qpsConvert_original)(destination,source);}
 catch(...){inConversion=false;TL_REDIRECT(*convertPatch,qpsConvert,&convert);throw;}
 inConversion=false;TL_REDIRECT(*convertPatch,qpsConvert,&convert);need(!convertPatch->failed(),26);
 // Directly inspect the original helper's sret, without manufacturing a
 // replacement string or adding a wrapper's extra return-value lifetime.
 if(cs->scenario==2||cs->scenario==15||cs->scenario==16){
  size_t want=cs->text==3?2:cs->text==4?3:cs->text==5?0:cs->text==7?1024:source.size();
  need(destination->size()==want,27);
 }
 if(activePhase){Life& life=lives[copies-1];life.utfRep=(void*)((const char*)destination->c_str()-24);life.utfOwned=!destination->empty();}
}
static void imageCheck(){
 need(actual.position==planned.position,28);need(actual.end==planned.end,29);need(actual.count==planned.count,30);
 for(unsigned i=0;i<planned.count;++i){unsigned k=0;for(;k<actual.count;++k)if(actual.cells[k].offset==planned.cells[i].offset)break;
  need(k<actual.count&&actual.cells[k].value==planned.cells[i].value,31);}
 q(actual.position);q(actual.end);n(actual.count);
}
static void verify(bool caught){
 need(eventIndex==expectedCount,32);imageCheck();need(caught==(cs->fault!=0),33);need(faultHits==(cs->fault?1u:0u),34);
 unsigned wantCopies=cs->fault==1?0:expectedRecords;need(copies==wantCopies,35);
 unsigned wantQuest=cs->fault&&cs->fault<5?0:expectedRecords;need(questCalls==wantQuest,36);
 unsigned wantConversions=cs->scenario==1?2:cs->scenario==2||cs->scenario==15?1:0;
 wantConversions+=cs->fault==1||cs->fault==3?0:expectedRecords;need(conversions==wantConversions,52);
 if(cs->fault==2)need(conversionAllocations==1,53);
 need(tellFailures==(cs->scenario==17?1u:0u),80);need(seekFailures==(cs->scenario==18?1u:0u),81);
 for(unsigned i=0;i<lifeCount;++i){const Life& life=lives[i];
  need(life.wideFrees==(life.wideOwned?1u:0u),37);need(life.utfFrees==(life.utfOwned?1u:0u),38);
  if(life.wideOwned&&life.utfOwned)need(life.utfOrder<life.wideOrder,39);
  n(life.wideOwned);n(life.utfOwned);n(life.wideFrees);n(life.utfFrees);n(life.wideOrder);n(life.utfOrder);
 }
 need(at<unsigned>(owner,0x20)==expectedFinalCount,40);need(at<unsigned>(owner,0x24)==expectedFinalCapacity,41);need(at<unsigned>(owner,0x28)==11,42);
 need(at<void**>(owner,0x18)==(cs->scenario==8?alternate:list),43);
 need(list[0]==quests[cs->scenario==3||cs->scenario==4?1:0],44);
 need(list[1]==quests[1]&&list[2]==quests[2]&&alternate[0]==quests[0]&&alternate[1]==quests[2]&&alternate[2]==quests[2],54);
 at<void**>(ownerBefore,0x18)=cs->scenario==8?alternate:list;at<unsigned>(ownerBefore,0x20)=expectedFinalCount;
 need(!std::memcmp(owner,ownerBefore,sizeof(ownerBefore)),55);
 for(unsigned i=0;i<3;++i){need(name(i)==(cs->scenario==4&&i==0?Wide(L"X"):originalNames[i]),45);
  if(!(cs->scenario==4&&i==0))need(refs(name(i))==initialRefs[i],46);
  if(cs->scenario==4&&i==0)std::memcpy(questBefore[i]+0x50,(char*)quests[i]+0x50,sizeof(Wide));
  need(!std::memcmp(quests[i],questBefore[i],sizeof(questBefore[i])),56);}
 if(cs->scenario==1){need(map->size()==3&&completed->size()==6,47);need(!completed->find(L"hidden")->second&&completed->find(L"done")->second&&completed->find(L"A")->second&&completed->find(L"orphan")->second&&!completed->find(L"B")->second&&!completed->find(L"C")->second,48);}
 else if(cs->scenario==2||cs->scenario==15){need(map->size()==1&&completed->size()==1&&completed->find(L"done")->second,57);}
 else need(map->empty()&&completed->empty(),58);
 n(copies);n(conversions);n(conversionAllocations);n(questCalls);n(faultHits);n(caught);n(at<unsigned>(owner,0x20));n(tellFailures);n(seekFailures);n(firstError);n(0x51505346);n(errors);
}
static void side(void* p,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(p);cap=&out;setup();
 detour::Set io,quest,copier,converter,allocator,deallocator,wideDestroy,stringDestroy;copyPatch=&copier;convertPatch=&converter;newPatch=&allocator;deletePatch=&deallocator;widePatch=&wideDestroy;stringPatch=&stringDestroy;
 io.redirect(qpsWrite,qpsWrite,&write);io.redirect(qpsTell,qpsTell,&tell);io.redirect(qpsSeek,qpsSeek,&seek);
 TL_REDIRECT(quest,qpsQuestSave,&questSave);copier.redirect(qpsCopy,qpsCopy,&copy);TL_REDIRECT(converter,qpsConvert,&convert);
 allocator.redirect(qpsNew,qpsNew,&allocate);deallocator.redirect(qpsDelete,qpsDelete,&release);
 wideDestroy.redirect(qpsRepDestroy,qpsRepDestroy,&destroyWide);
 stringDestroy.redirect(qpsStringDtor,qpsStringDtor,&destroyString);
 if(io.failed()||quest.failed()||copier.failed()||converter.failed()||allocator.failed()||deallocator.failed()||wideDestroy.failed()||stringDestroy.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*,FILE*);Fn fn=candidate?&qpsNewSave:&qpsOldSave;
 bool caught=false;if(!autotest::beginInvocation(out,fn))return;
 try{fn(owner,stream);out.callCompleted=1;}catch(const Stop& s){caught=true;need(s.site==cs->fault,49);}catch(const std::bad_alloc&){caught=true;need(cs->fault==1||cs->fault==2,50);}
 // Oracle inspection must not itself call our construction observer.
 io.restore();quest.restore();copier.restore();converter.restore();allocator.restore();deallocator.restore();wideDestroy.restore();stringDestroy.restore();
 verify(caught);map->~Quests();completed->~Completed();for(unsigned i=0;i<3;++i)name(i).~Wide();
}
static void original(void* p,autotest::Capture& o){side(p,o,false);}
static void candidate(void* p,autotest::Capture& o){side(p,o,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x51505346&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,autotest::Body a=original,autotest::Body b=candidate){
 autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
 bool ok=good(x)&&good(y)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(!c.fault){if(coverage.observe(host,x,y))ok=false;}
 else ok=ok&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==0xd2ec10&&host->comparison_pair&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget);
 if(!ok){unsigned first[2]={~0u,~0u};if(x.capture.length>=12)std::memcpy(first,x.capture.data+x.capture.length-12,4);if(y.capture.length>=12)std::memcpy(first+1,y.capture.data+y.capture.length-12,4);
  host->log("    quest save scenario=%u text=%u leaked=%u fault=%u offset=%u status=%d/%d issue=%u/%u valid=%u/%u first=%u/%u\n",c.scenario,c.text,c.leaked,c.fault,c.offset,x.childStatus,y.childStatus,x.capture.issue,y.capture.issue,good(x),good(y),first[0],first[1]);
  for(unsigned side=0;side<2;++side){const autotest::Capture& z=side?y.capture:x.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned code;std::memcpy(&code,z.data+i,4);if((code&0xffff0000u)==0xf0000000u)host->log("    save side=%u oracle=%u at=%lu\n",side,code-0xf0000000u,(unsigned long)i);}}}
 return ok;
}

// Separate production boundary: genuine original CQuest construction/save/D1,
// real stdio and original UTF helpers; empty collections are constructor state.
// This does NOT stand in for CGameClient::saveCharacter consumer coverage.
static void realQuest(void* p,autotest::Capture& out,bool replacement){
 cs=static_cast<Case*>(p);cap=&out;errors=firstError=0;autotest::g_arenaUsed=0;
 void* manager=autotest::allocate(0xd0);void* quest=autotest::allocate(0x218);
 Quests* qm=new((char*)manager+0x40)Quests;Completed* cm=new((char*)manager+0x70)Completed;
 // Self-tests precede game TU static constructors. These original empty
 // string cells are read by Quest/QuestRequirements construction. Establish
 // their real string lifetime in this child, then restore the prior bytes.
 const uintptr_t globals[]={0x14f9fe8,0x14fb488};unsigned char savedGlobals[2][sizeof(Wide)];
 for(unsigned i=0;i<2;++i){std::memcpy(savedGlobals[i],reinterpret_cast<void*>(globals[i]),sizeof(Wide));new(reinterpret_cast<void*>(globals[i]))Wide();}
 std::memset(quest,0xa5,0x218);
 qpsQuestCtor(quest,0,0);Wide& title=at<Wide>(quest,0x50);title=cs->text?Wide(L"A\u0416"):Wide(L"Q");
 const unsigned values[]={0x11223344u,0x89abcdefu,0x02030405u};const unsigned offsets[]={0x1c,0x20,0x20c};
 for(unsigned i=0;i<3;++i)at<unsigned>(quest,offsets[i])=values[i];
 const unsigned counts[]={0x68,0x80,0x98,0xb0,0x138,0x150,0x168};for(unsigned i=0;i<7;++i)need(at<unsigned>(quest,counts[i])==0,60);
 need(at<void*>(quest,0x1e8)==0,61);
 void** active=(void**)autotest::allocate(sizeof(void*));active[0]=quest;
 at<void**>(manager,0x18)=active;at<unsigned>(manager,0x20)=1;at<unsigned>(manager,0x24)=1;at<unsigned>(manager,0x28)=10;
 FILE* f=std::tmpfile();if(!f){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned char before[128],expectedBytes[128],got[128];std::memset(before,0x6d,sizeof(before));std::memcpy(expectedBytes,before,sizeof(before));
 unsigned start=cs->offset?7:0,recordStart=start+8,nameLength=title.size(),end=recordStart+6+2*nameLength+48;
 unsigned expectedEnd=cs->offset?128:end;
 if(cs->offset)need(std::fwrite(before,1,sizeof(before),f)==sizeof(before),62);
 need(!std::fseek(f,start,SEEK_SET),63);
 le(expectedBytes+start,0,4);le(expectedBytes+start+4,1,4);le(expectedBytes+recordStart,end,4);le(expectedBytes+recordStart+4,nameLength,2);
 for(unsigned i=0;i<nameLength;++i)le(expectedBytes+recordStart+6+2*i,title.c_str()[i],2);
 unsigned payload=recordStart+6+2*nameLength;le(expectedBytes+payload,~0ULL,8);
 for(unsigned i=0;i<3;++i)le(expectedBytes+payload+8+4*i,values[i],4);std::memset(expectedBytes+payload+20,0,28);
 typedef void(*Fn)(void*,FILE*);Fn fn=replacement?&qpsNewSave:&qpsOldSave;
 if(!autotest::beginInvocation(out,fn)){std::fclose(f);return;}fn(manager,f);out.callCompleted=1;
 need(std::ftell(f)==long(expectedEnd),64);need(!std::ferror(f),65);need(!std::fseek(f,0,SEEK_SET),66);
 size_t amount=std::fread(got,1,sizeof(got),f);need(amount==expectedEnd,67);need(amount<=sizeof(got)&&!std::memcmp(got,expectedBytes,amount),68);
 out.add(got,amount);n(amount);need(!std::fclose(f),69);
 for(unsigned i=0;i<3;++i)need(at<unsigned>(quest,offsets[i])==values[i],70);
 for(unsigned i=0;i<7;++i)need(at<unsigned>(quest,counts[i])==0,71);
 need(at<void**>(manager,0x18)==active&&at<unsigned>(manager,0x20)==1&&active[0]==quest,72);
 qpsQuestDtor(quest);qm->~Quests();cm->~Completed();
 for(unsigned i=0;i<2;++i){reinterpret_cast<Wide*>(globals[i])->~Wide();std::memcpy(reinterpret_cast<void*>(globals[i]),savedGlobals[i],sizeof(Wide));}
 n(firstError);n(0x51505346);n(errors);
}
static void realOriginal(void* p,autotest::Capture& o){realQuest(p,o,false);}
static void realCandidate(void* p,autotest::Capture& o){realQuest(p,o,true);}
}

TL_TEST(questmanager_persistence_save_protocol){
 using namespace qps;autotest::Coverage coverage("questmanager_persistence_save_protocol",0xd2ec10);unsigned count=0;
 for(unsigned scenario=0;scenario<=14;++scenario){if(scenario==2||scenario==12||scenario==14)continue;Case c={scenario,0,0,0,1};if(!pair(host,coverage,c)){coverage.report(host);return 1;}++count;}
 for(unsigned text=0;text<8;++text){Case c={2,text,0,0,0};if(!pair(host,coverage,c)){coverage.report(host);return 1;}++count;}
 for(unsigned offset=0;offset<3;++offset){Case c={12,0,0,0,offset};if(!pair(host,coverage,c)){coverage.report(host);return 1;}++count;}
 for(unsigned leaked=0;leaked<2;++leaked){Case c={14,0,leaked,0,0};if(!pair(host,coverage,c)){coverage.report(host);return 1;}++count;}
 coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
TL_TEST(questmanager_persistence_save_short_io){
 using namespace qps;autotest::Coverage coverage("questmanager_persistence_save_short_io",0xd2ec10);
 for(unsigned scenario=15;scenario<=16;++scenario){Case c={scenario,1,0,0,0};if(!pair(host,coverage,c)){coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=2||coverage.different||coverage.missing;
}
TL_TEST(questmanager_persistence_save_unwind){
 using namespace qps;autotest::Coverage coverage("save expected unwinds excluded",0xd2ec10);unsigned count=0;
 for(unsigned fault=1;fault<=8;++fault)for(unsigned leaked=0;leaked<2;++leaked){if(fault==1&&!leaked)continue;Case c={14,0,leaked,fault,0};if(!pair(host,coverage,c))return 1;++count;}
 host->log("    quest save: %u expected LSDA-qualified unwinds, no completed-call credit\n",count);return 0;
}
TL_TEST(questmanager_persistence_save_stdio_errors){
 using namespace qps;autotest::Coverage coverage("questmanager_persistence_save_stdio_errors",0xd2ec10);
 for(unsigned scenario=17;scenario<=18;++scenario)for(unsigned operation=0;operation<2;++operation){Case c={scenario,0,0,0,operation};if(!pair(host,coverage,c)){coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=4||coverage.different||coverage.missing;
}
TL_TEST(questmanager_persistence_save_original_quest){
 using namespace qps;autotest::Coverage coverage("questmanager_persistence_save_original_quest",0xd2ec10);
 for(unsigned text=0;text<2;++text)for(unsigned offset=0;offset<2;++offset){Case c={0,text,0,0,offset};if(!pair(host,coverage,c,realOriginal,realCandidate)){coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=4||coverage.different||coverage.missing;
}
