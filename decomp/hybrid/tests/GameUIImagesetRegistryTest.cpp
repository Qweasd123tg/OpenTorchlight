// Three original entry points, real CEGUI UTF-8 strings and image maps.
// Only allocation and the external getImage boundary are selectively detoured.
#include <cstring>
#include <new>
#include <map>
#include <vector>
#include <CEGUIImageset.h>
#include <CEGUIImage.h>
#include "GameUI.h"
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalAdd, (CGameUI*,CEGUI::Imageset*), "_ZN7CGameUI11addImageSetEPN5CEGUI8ImagesetE")
TL_ORIGINAL(CEGUI::Imageset*, originalSet, (CGameUI*,const unsigned char*), "_ZN7CGameUI18getImageSetForIconEPKh")
TL_ORIGINAL(const CEGUI::Image*, originalImage, (CGameUI*,const unsigned char*), "_ZN7CGameUI20getImageFromImageSetEPKh")
TL_ORIGINAL(void, originalUTF8, (CEGUI::String*,const unsigned char*), "_ZN5CEGUI6StringC1EPKh")
extern "C" void recoveredAdd(CGameUI*,CEGUI::Imageset*) __asm__("_ZN7CGameUI11addImageSetEPN5CEGUI8ImagesetE");
extern "C" CEGUI::Imageset* recoveredSet(CGameUI*,const unsigned char*) __asm__("_ZN7CGameUI18getImageSetForIconEPKh");
extern "C" const CEGUI::Image* recoveredImage(CGameUI*,const unsigned char*) __asm__("_ZN7CGameUI20getImageFromImageSetEPKh");
extern "C" char arrayAllocate[] __asm__("_Znam");
extern "C" char arrayRelease[] __asm__("_ZdaPv");
extern "C" char libraryImage[] __asm__("_ZNK5CEGUI8Imageset8getImageERKNS_6StringE");

namespace {
typedef std::map<CEGUI::String,CEGUI::Image,CEGUI::String::FastLessCompare> Registry;
struct Array { CEGUI::Imageset** data;unsigned count,capacity,grow; };
struct Case { unsigned op,count,capacity,grow,query,mask,mode,mutation,steps,noiseMode;bool nullArgument,fault;
 Case(unsigned o=0):op(o),count(0),capacity(0),grow(2),query(0),mask(0),mode(0),mutation(0),steps(1),noiseMode(1),nullArgument(false),fault(false){} };
struct Stop {};
const char* queries[]={"", "alpha", "Alpha", "same", "aa", "bb", "skill_attack_abcdefghijklmnopqrstuvwxyz0123456789", "\xc3\xa9" "p" "\xc3\xa9" "e", "\xe7\x81\xab\xe7\x82\x8e", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaD"};
const unsigned queryCount=sizeof(queries)/sizeof(queries[0]);
const char* noise[]={"z", "zz", "aaa", "aaaaz", "aaaba", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB"};
const Case* current;autotest::Capture* capture;CGameUI* ui;Array* array;
CEGUI::Imageset* sets[5];Registry* maps[5];unsigned calls,allocations,releases;CEGUI::Imageset** priorData;
unsigned char* uiBytes;unsigned char* allocationsRaw[12];unsigned allocationSize[12],allocationCount;
void require(bool condition){if(!condition)_exit(90);}
void number(unsigned n){capture->add(&n,sizeof(n));}
void pointer(const void* p){capture->addPointer(p);}
void text(const CEGUI::String& s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void* guarded(unsigned n){require(allocationCount<12);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(n+32));require(p!=0);std::memset(p,0xa7,16);std::memset(p+16+n,0x5d,16);allocationsRaw[allocationCount]=p;allocationSize[allocationCount++]=n;return p+16;}
unsigned setIndex(const CEGUI::Imageset* s){for(unsigned i=0;i<5;++i)if(sets[i]==s)return i;_exit(91);return 0;}
void insert(unsigned i,const char* name){CEGUI::String key(reinterpret_cast<const unsigned char*>(name));CEGUI::Image value(sets[i],key,CEGUI::Rect(i+1,i+2,i+12,i+16),CEGUI::Point(i+.25f,i+.5f),1.f,1.f);maps[i]->insert(std::make_pair(key,value));}
void* allocateArray(size_t n){number(1);number(n);++allocations;require(n<=128);if(current->fault)throw Stop();
 if(current->mutation==1)array->count=1;
 if(current->mutation==2){priorData=array->data;array->data=static_cast<CEGUI::Imageset**>(guarded(8*sizeof(void*)));for(unsigned i=0;i<8;++i)array->data[i]=sets[(i+2)%5];}
 if(current->mutation==3)array->capacity=1;
 return guarded(n);
}
void releaseArray(void* p){number(2);pointer(p);++releases;require(p==array->data);for(unsigned i=0;i<array->capacity;++i)pointer(array->data[i]);}
const CEGUI::Image* getImage(const CEGUI::Imageset* s,const CEGUI::String& name){number(3);unsigned index=setIndex(s);number(index);text(name);++calls;
 if(current->mode==2)throw Stop();
 if((current->mode==1||current->mode==3)&&calls==1){if(current->mode==3)array->count=1;return 0;}
 Registry::const_iterator it=maps[index]->find(name);require(it!=maps[index]->end());return &it->second;
}
void setup(const Case& c){allocationCount=calls=allocations=releases=0;priorData=0;
 uiBytes=static_cast<unsigned char*>(guarded(sizeof(CGameUI)));std::memset(uiBytes,0x6a,sizeof(CGameUI));ui=reinterpret_cast<CGameUI*>(uiBytes);array=reinterpret_cast<Array*>(uiBytes+0x458);
 for(unsigned i=0;i<5;++i){sets[i]=static_cast<CEGUI::Imageset*>(autotest::allocate(sizeof(CEGUI::Imageset)));require(sets[i]!=0);new(sets[i])CEGUI::String(reinterpret_cast<const unsigned char*>("fixture"));maps[i]=new(reinterpret_cast<char*>(sets[i])+sizeof(CEGUI::String))Registry;
  if(c.op){if(c.noiseMode==2)insert(i,c.query==1?"Alpha":"alpha");if(c.noiseMode==1)for(unsigned k=0;k<sizeof(noise)/sizeof(noise[0]);++k)insert(i,noise[(k+i)%7]);if(c.mask&(1u<<i))insert(i,queries[c.query]);}
 }
 array->count=c.count;array->capacity=c.capacity;array->grow=c.grow;array->data=0;
 if(c.capacity){array->data=static_cast<CEGUI::Imageset**>(guarded(c.capacity*sizeof(void*)));for(unsigned i=0;i<c.capacity;++i)array->data[i]=sets[i%5];}
}
void imageIdentity(const CEGUI::Image* result){if(!result){number(0);return;}for(unsigned i=0;i<5;++i){unsigned k=0;for(Registry::const_iterator it=maps[i]->begin();it!=maps[i]->end();++it,++k)if(&it->second==result){number(1+i);number(k);text(it->first);float values[]={result->getWidth(),result->getHeight(),result->getOffsetX(),result->getOffsetY()};capture->add(values,sizeof(values));return;}}_exit(92);}
void snapshot(){number(array->count);number(array->capacity);number(array->grow);pointer(array->data);if(array->data)for(unsigned i=0;i<array->capacity;++i)pointer(array->data[i]);capture->add(uiBytes+0x46c,4);number(calls);number(allocations);number(releases);
 capture->add(uiBytes,0x458);capture->add(uiBytes+0x470,sizeof(CGameUI)-0x470);
 for(unsigned i=0;i<allocationCount;++i){capture->add(allocationsRaw[i],16);capture->add(allocationsRaw[i]+16+allocationSize[i],16);}
 for(unsigned i=0;i<5;++i){number(maps[i]->size());for(Registry::const_iterator it=maps[i]->begin();it!=maps[i]->end();++it)text(it->first);}
}
void side(void* raw,autotest::Capture& out,bool ours){current=static_cast<Case*>(raw);capture=&out;setup(*current);bool threw=false;
 {detour::Set d;if(!current->op){d.redirect(arrayAllocate,arrayAllocate,&allocateArray);d.redirect(arrayRelease,arrayRelease,&releaseArray);}if(current->op==2&&current->mode)d.redirect(libraryImage,libraryImage,&getImage);require(!d.failed());
  try {if(current->op==0){void(*fn)(CGameUI*,CEGUI::Imageset*)=ours?&recoveredAdd:&originalAdd;require(autotest::beginInvocation(out,fn));for(unsigned i=0;i<current->steps;++i)fn(ui,current->nullArgument?0:sets[(i+3)%5]);}
   else if(current->op==1){CEGUI::Imageset*(*fn)(CGameUI*,const unsigned char*)=ours?&recoveredSet:&originalSet;require(autotest::beginInvocation(out,fn));CEGUI::Imageset* result=fn(ui,current->nullArgument?0:reinterpret_cast<const unsigned char*>(queries[current->query]));pointer(result);}
   else {const CEGUI::Image*(*fn)(CGameUI*,const unsigned char*)=ours?&recoveredImage:&originalImage;require(autotest::beginInvocation(out,fn));const CEGUI::Image* result=fn(ui,current->nullArgument?0:reinterpret_cast<const unsigned char*>(queries[current->query]));imageIdentity(result);}
   out.callCompleted=1;
  }catch(const Stop&){threw=true;}catch(...){_exit(93);}
  require(threw==(current->fault||current->mode==2));number(threw);snapshot();
 }
 for(unsigned i=0;i<5;++i){maps[i]->~Registry();reinterpret_cast<CEGUI::String*>(sets[i])->~String();}
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void recovered(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,const char* name,unsigned op,const std::vector<Case>& cases,const std::vector<Case>& faults){uint64_t address=op==0?(uint64_t)(uintptr_t)&originalAdd:op==1?(uint64_t)(uintptr_t)&originalSet:(uint64_t)(uintptr_t)&originalImage;autotest::Coverage coverage(name,address);
 for(unsigned i=0;i<cases.size();++i){Case c=cases[i];autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    imageset op %u case %u statuses %d/%d first %lu lengths %lu/%lu\n",op,i,a.status,b.status,(unsigned long)first,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);if(coverage.completed!=cases.size())return 1;
 for(unsigned i=0;i<faults.size();++i){Case c=faults[i];autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==address&&host->comparison_pair(address,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(!ok){host->log("    imageset op %u expected unwind %u failed\n",op,i);return 1;}}
 host->log("    imageset op %u expected unwinds %u (separate from normal coverage)\n",op,(unsigned)faults.size());return 0;
}
bool fourByteBoundary(const tlhybrid_host* host){
 // The pinned original miscounts a four-byte UTF-8 scalar: length 3 but
 // only two decoded codepoints. The third retains caller storage bytes.
 // Such a key is not a deterministic lookup input; do not "fix" the SDK.
 union Storage {long double align;unsigned char bytes[sizeof(CEGUI::String)];} a,b;
 std::memset(a.bytes,0x11,sizeof(a.bytes));std::memset(b.bytes,0x22,sizeof(b.bytes));
 CEGUI::String* first=reinterpret_cast<CEGUI::String*>(a.bytes);CEGUI::String* second=reinterpret_cast<CEGUI::String*>(b.bytes);
 const unsigned char key[]={0xe7,0x81,0xab,0xf0,0x9f,0x94,0xa5,0};originalUTF8(first,key);originalUTF8(second,key);
 bool ok=first->length()==3&&second->length()==3&&(*first)[0]==0x706b&&(*first)[1]==0x1f525&&(*first)[2]==0x11111111u&&(*second)[2]==0x22222222u;
 host->log("    original four-byte UTF-8 boundary: lengths %lu/%lu retained words %08x/%08x\n",(unsigned long)first->length(),(unsigned long)second->length(),(*first)[2],(*second)[2]);
 first->~String();second->~String();return ok;
}
void lookupCases(unsigned op,std::vector<Case>& cases){for(unsigned q=0;q<queryCount;++q)for(unsigned mask=0;mask<16;++mask){Case c(op);c.count=(q+mask)%5;c.capacity=c.count;c.query=q;c.mask=mask;cases.push_back(c);}for(unsigned q=0;q<queryCount;++q){Case c(op);c.count=c.capacity=4;c.query=q;c.mask=15;cases.push_back(c);c.mask=0;cases.push_back(c);}for(unsigned q=0;q<queryCount;++q){Case c(op);c.count=c.capacity=4;c.query=q;c.noiseMode=0;c.mask=0;cases.push_back(c);c.mask=8;cases.push_back(c);c.capacity=1;cases.push_back(c);c.mask=1;cases.push_back(c);}
 for(unsigned q=1;q<=2;++q){Case c(op);c.count=c.capacity=4;c.query=q;c.noiseMode=2;c.mask=0;cases.push_back(c);c.mask=4;cases.push_back(c);}
 Case empty(op);empty.nullArgument=true;cases.push_back(empty);}
}
TL_TEST(gameui_imageset_registry_add){std::vector<Case> cases,faults;for(unsigned capacity=0;capacity<=5;++capacity)for(unsigned count=0;count<=capacity;++count)for(unsigned nullValue=0;nullValue<2;++nullValue){Case c;c.capacity=capacity;c.count=count;c.grow=capacity%3+1;c.nullArgument=nullValue!=0;c.steps=3;cases.push_back(c);}for(unsigned mutation=1;mutation<=3;++mutation){Case c;c.count=c.capacity=3;c.grow=3;c.mutation=mutation;cases.push_back(c);}for(unsigned full=0;full<2;++full){Case c;c.count=c.capacity=full?3:0;c.grow=2;c.fault=true;faults.push_back(c);}return run(host,"gameui_imageset_registry_add",0,cases,faults);}
TL_TEST(gameui_imageset_registry_select){std::vector<Case> cases,faults;lookupCases(1,cases);return run(host,"gameui_imageset_registry_select",1,cases,faults);}
TL_TEST(gameui_imageset_registry_image){if(!fourByteBoundary(host))return 1;std::vector<Case> cases,faults;lookupCases(2,cases);for(unsigned mode=1;mode<=3;++mode)for(unsigned q=0;q<queryCount;++q){Case c(2);c.count=c.capacity=4;c.query=q;c.mask=15;c.mode=mode;if(mode==2)faults.push_back(c);else cases.push_back(c);}return run(host,"gameui_imageset_registry_image",2,cases,faults);}
