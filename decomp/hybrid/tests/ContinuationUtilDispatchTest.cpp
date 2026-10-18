#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "KeyManager.h"
TL_ORIGINAL(void,cuOldKey,(CKeyManager*,unsigned,unsigned),"_ZN11CKeyManager8keyEventEjj")
extern "C" void cuNewKey(CKeyManager*,unsigned,unsigned) __asm__("_ZN11CKeyManager8keyEventEjj");
TL_ORIGINAL(bool,cuOldDirectory,(const std::wstring&),"_ZN10FILESYSTEM20CreateLocalDirectoryERKSbIwSt11char_traitsIwESaIwEE")
extern "C" bool cuNewDirectory(const std::wstring&) __asm__("_ZN10FILESYSTEM20CreateLocalDirectoryERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,cuOldLayout,(void*,void*,unsigned,void*),"_ZN17CLayoutDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
extern "C" void cuNewLayout(void*,void*,unsigned,void*) __asm__("_ZN17CLayoutDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_");
extern "C" char cuKeyboard_linked[] __asm__("SDL_GetKeyboardState");
TL_FUNCTION(cuMkdir,"_Z15CreateDirectoryPKwPv")
TL_FUNCTION(cuLastError,"_Z12GetLastErrorv")
TL_FUNCTION(cuEnabled,"_ZN12CEditorScene10setEnabledEb")
TL_FUNCTION(cuVisible,"_ZN7CLayout10setVisibleEb")
TL_FUNCTION(cuBroadcast,"_ZN17CEditorBaseObject14BroadcastEventEj")
TL_FUNCTION(cuBaseInput,"_ZN29CPositionableObjectDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_FUNCTION(cuProcess,"_ZN7CLayout13processInputsEjP17CEditorBaseObject")
TL_FUNCTION(cuStart,"_ZN7CLayout5startEv")
TL_FUNCTION(cuStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(cuBack,"_ZN7CLayout14startBackwardsEv")
TL_FUNCTION(cuPause,"_ZN7CLayout5pauseEv")
extern "C" char cuLayoutTable[] __asm__("_ZTV7CLayout");
extern "C" char cuBaseTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case {unsigned mode,seed;};autotest::Capture* out;unsigned seed,calls;void* receiver;void* descriptor;void* sender;void* node;
unsigned char keyboard[128];
void number(unsigned x){out->add(&x,4);}
void identity(void* p,void* expected){number(p==expected);if(p!=expected)out->issue=autotest::Capture::InvalidReport;}
const unsigned char* keys(int* count){number(1);number(count==NULL);if(count)out->issue=autotest::Capture::InvalidReport;return keyboard;}
int directory(const wchar_t* path,void* security){number(2);out->addText(std::wstring(path));number(security==NULL);if(security)out->issue=autotest::Capture::InvalidReport;return ++calls==(seed/7)%5?0:1;}
long lastError(){number(3);return seed&1?17:13;}
void enabled(void* p,bool value){number(4);identity(p,receiver);number(value);}
void visible(void* p,bool value){number(5);identity(p,receiver);number(value);}
void broadcast(void* p,unsigned event){number(6);identity(p,receiver);number(event);}
void base(void* p,void* object,unsigned event,void* from){number(7);identity(p,descriptor);identity(object,receiver);identity(from,sender);number(event);}
bool process(void* p,unsigned event,void* from){number(8);identity(p,receiver);identity(from,sender);number(event);return seed&1;}
void start(void* p){number(9);identity(p,receiver);}
void stop(void* p,bool immediately){number(10);identity(p,receiver);number(immediately);}
void backwards(void* p){number(11);identity(p,receiver);}
void pause(void* p){number(12);identity(p,receiver);}
void nodeVisible(void* p,bool value,bool cascade){number(13);identity(p,node);number(value);number(cascade);}
void side(void* raw,autotest::Capture& capture,bool ours){Case c=*static_cast<Case*>(raw);out=&capture;seed=c.seed;calls=0;
 if(c.mode==0){uint64_t storage[(sizeof(CKeyManager)+7)/8];unsigned char before[sizeof(storage)];for(unsigned i=0;i<sizeof(storage);++i)reinterpret_cast<unsigned char*>(storage)[i]=static_cast<unsigned char>(i*29+seed*17);std::memcpy(before,storage,sizeof(storage));std::memset(keyboard,0,sizeof(keyboard));keyboard[0x39]=seed%3?0:0x80;
  const unsigned events[]={0x100,0x101,0x104,0x105,0,0x102,0xffffffffu,0xff};unsigned event=events[seed%8],key=(seed/8)%4?((seed*71)%510):0;detour::Set d;d.redirect(reinterpret_cast<char*>(0x5563a8),cuKeyboard_linked,&keys);if(d.failed()){capture.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CKeyManager*,unsigned,unsigned);Fn fn=ours?cuNewKey:cuOldKey;if(!autotest::beginInvocation(capture,fn))return;fn(reinterpret_cast<CKeyManager*>(storage),event,key);capture.callCompleted=1;capture.add(storage,sizeof(storage));
  if(event==0x101||event==0x105){if(before[0x911+key])before[0xb11+key]=1;before[0x911+key]=0;}else if(event==0x100||event==0x104){if(!before[0x911+key])before[0x711+key]=1;before[0x911+key]=1;}before[0x10]=keyboard[0x39]!=0;if(std::memcmp(before,storage,sizeof(storage)))capture.issue=autotest::Capture::InvalidReport;
 }else if(c.mode==1){const wchar_t* paths[]={L"",L"a",L"a\\b",L"\\root\\leaf",L"a\\\\b\\",L"/tmp/slashes",L"Ж\\long\\dir"};std::wstring path(paths[seed%7]);detour::Set d;TL_REDIRECT(d,cuMkdir,&directory);TL_REDIRECT(d,cuLastError,&lastError);if(d.failed()){capture.issue=autotest::Capture::InvalidReport;return;}
  typedef bool(*Fn)(const std::wstring&);Fn fn=ours?cuNewDirectory:cuOldDirectory;if(!autotest::beginInvocation(capture,fn))return;bool result=fn(path);capture.callCompleted=1;number(result);number(calls);capture.addText(path);
 }else{uint64_t memory[128]={0},desc[64]={0},from[16]={0},nodeStorage[8]={0};void* table[80]={0};void* layoutTable[82];std::memcpy(layoutTable,cuLayoutTable,sizeof(layoutTable));layoutTable[2+6]=reinterpret_cast<void*>(&broadcast);receiver=memory;descriptor=desc;sender=from;node=nodeStorage;table[0x218/8]=reinterpret_cast<void*>(&nodeVisible);*reinterpret_cast<void**>(nodeStorage)=table;std::memcpy(reinterpret_cast<char*>(memory)+0x58,&node,8);unsigned kind=seed/30%3;*reinterpret_cast<void**>(memory)=kind==2?static_cast<void*>(cuBaseTable+16):static_cast<void*>(layoutTable+2);unsigned event=seed%30;if(event==28)event=0xffffffffu;if(event==29)event=0x80000000u;
  detour::Set d;TL_REDIRECT(d,cuEnabled,&enabled);TL_REDIRECT(d,cuVisible,&visible);TL_REDIRECT(d,cuBroadcast,&broadcast);TL_REDIRECT(d,cuBaseInput,&base);TL_REDIRECT(d,cuProcess,&process);TL_REDIRECT(d,cuStart,&start);TL_REDIRECT(d,cuStop,&stop);TL_REDIRECT(d,cuBack,&backwards);TL_REDIRECT(d,cuPause,&pause);if(d.failed()){capture.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?cuNewLayout:cuOldLayout;if(!autotest::beginInvocation(capture,fn))return;fn(descriptor,kind==1?NULL:receiver,event,sender);capture.callCompleted=1;
 }
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char* name,uintptr_t address,unsigned count){autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    util dispatch %u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(continuation_key_event){return run(host,0,"continuation_key_event",(uintptr_t)&cuOldKey,64);}
TL_TEST(continuation_local_directory){return run(host,1,"continuation_local_directory",(uintptr_t)&cuOldDirectory,70);}
static int continuation_layout_input(const tlhybrid_host* host){return run(host,2,"continuation_layout_input",(uintptr_t)&cuOldLayout,90);}
