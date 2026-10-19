#include "AutoTest.h"
#include "tests/Detour.h"
#include <X11/Xlib.h>
#include <cstring>
TL_ORIGINAL(int,fltkLookupOriginal,(XIC,XKeyPressedEvent*,char*,int,KeySym*,Status*),"XUtf8LookupString")
extern "C" int fltkLookupCandidate(XIC,XKeyPressedEvent*,char*,int,KeySym*,Status*) __asm__("XUtf8LookupString");
namespace {
struct Case{unsigned key,length,status,capacity,context,locale;};
const Case*current;autotest::Capture*cap;
void word(unsigned x){cap->add(&x,4);}
int mb(XIC ic,XKeyPressedEvent*event,char*buffer,int size,KeySym*key,Status*status){word(1);word(ic!=NULL);word(event->type);word(size);word(key!=NULL);word(status!=NULL);const KeySym keys[]={0,1,0x7f,0x80,0xff,0x100,0x1a1,0xf000,0xf001,0x01000000,0x01000041,0x0101f642,0x100000001UL};*key=keys[current->key];*status=current->status?current->status:XLookupBoth;unsigned n=current->length;if(*status==XBufferOverflow||int(n)>size){*status=XBufferOverflow;return n;}const unsigned char data[]={0xa4,0xa2,0x8f,0xa1};for(unsigned i=0;i<n;++i)buffer[i]=data[i%4];return n;}
XIM im(XIC ic){word(2);word(ic!=NULL);return current->context==2?NULL:reinterpret_cast<XIM>(0x2220);}
char*locale(XIM input){word(3);word(input==reinterpret_cast<XIM>(0x2220));const char*names[]={NULL,"UTF-8","ja_JP.EUC","zh_CN.EUC","zh_CN","zh_TW","GBK","ko_KR","chinese-t","unknown"};return const_cast<char*>(names[current->locale]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;detour::Set d;d.redirect(reinterpret_cast<char*>(&XmbLookupString),reinterpret_cast<char*>(&XmbLookupString),&mb);d.redirect(reinterpret_cast<char*>(&XIMOfIC),reinterpret_cast<char*>(&XIMOfIC),&im);d.redirect(reinterpret_cast<char*>(&XLocaleOfIM),reinterpret_cast<char*>(&XLocaleOfIM),&locale);if(d.failed())_exit(64);char buffer[160];std::memset(buffer,0xa5,sizeof(buffer));XKeyPressedEvent event;std::memset(&event,0,sizeof(event));event.type=KeyPress;KeySym key=0xdead;Status status=0xa5;int(*fn)(XIC,XKeyPressedEvent*,char*,int,KeySym*,Status*)=ours?fltkLookupCandidate:fltkLookupOriginal;if(autotest::beginInvocation(out,fn)){int r=fn(c.context?reinterpret_cast<XIC>(0x1110):NULL,&event,buffer+16,c.capacity,&key,&status);out.callCompleted=1;out.add(&r,4);}out.add(&key,sizeof(key));out.add(&status,sizeof(status));out.add(buffer,sizeof(buffer));d.restore();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_fltk_source_lookup){int failures=0;autotest::Stats stats={0,0,0};autotest::Coverage coverage("complete_fltk_source_lookup",reinterpret_cast<uintptr_t>(&fltkLookupOriginal));unsigned cases=0;const unsigned sizes[]={0,1,4,5,8,16,128};for(unsigned key=0;key<13;++key)for(unsigned size=0;size<7;++size)for(unsigned length=0;length<4;++length)for(unsigned context=0;context<3;++context){Case c={key,length,length==3?unsigned(-1):XLookupBoth,sizes[size],context,(key+size+length+context)%10};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_fltk_source_lookup",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
