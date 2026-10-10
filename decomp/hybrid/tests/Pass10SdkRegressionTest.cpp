#include <string>
#include <cstring>
#include <new>
#include <OgreUTFString.h>
#include "AutoTest.h"
TL_ORIGINAL(Ogre::UTFString*, oldAssign, (Ogre::UTFString*, const std::string&), "_ZN4Ogre9UTFString6assignERKSs")
TL_ORIGINAL(void, oldCopy, (Ogre::UTFString*, const Ogre::UTFString&), "_ZN4Ogre9UTFStringC1ERKS0_")
TL_ORIGINAL(void, oldDestroy, (Ogre::UTFString*), "_ZN4Ogre9UTFStringD1Ev")
typedef std::basic_string<unsigned short> ShortString;
TL_ORIGINAL(void, oldShortDestroy, (ShortString*), "_ZNSbItSt11char_traitsItESaItEED1Ev")
extern "C" Ogre::UTFString* newAssign(Ogre::UTFString*, const std::string&) __asm__("_ZN4Ogre9UTFString6assignERKSs");
extern "C" void newCopy(Ogre::UTFString*, const Ogre::UTFString&) __asm__("_ZN4Ogre9UTFStringC1ERKS0_");
extern "C" void newDestroy(Ogre::UTFString*) __asm__("_ZN4Ogre9UTFStringD1Ev");
extern "C" void newShortDestroy(ShortString*) __asm__("_ZNSbItSt11char_traitsItESaItEED1Ev");
namespace {
struct Case { unsigned op, n, count, state, invalid; };
void capture(autotest::Capture& out, const Ogre::UTFString& s) { size_t n=s.size(), c=s.capacity();out.add(&n,sizeof(n));out.add(&c,sizeof(c));out.add(s.data(),(n+1)*sizeof(Ogre::UTFString::code_point)); }
void captureShort(autotest::Capture& out, const ShortString& s) {size_t n=s.size(),c=s.capacity();out.add(&n,sizeof(n));out.add(&c,sizeof(c));out.add(s.data(),(n+1)*sizeof(unsigned short));}
void side(void* raw, autotest::Capture& out, bool ours) {
 Case c=*(Case*)raw;
 const char* good[]={"","ASCII","\xc2\xa9","\xe4\xb8\xad","\xf0\x9f\x98\x80","\xed\xa0\x80","\xf4\x8f\xbf\xbf","\xef\xbf\xbf"};
 const char* bad[]={"\xc2Q","\xe4Q\x80","\xf0\x9fQ\x80","\x80","\xff","\xc0\x80","\xe0\x80\x80","\xf0\x80\x80\x80"};
 std::string input; for(unsigned i=0;i<c.count;++i){input+=c.invalid?bad[c.n]:good[c.n];if(i%2)input.append("a\0b",3);}
 if(c.op==3){
  ShortString* p=new(autotest::allocate(sizeof(ShortString))) ShortString(c.count*17,(unsigned short)(0x1234+c.n));
  if(c.state&1)p->reserve(1024); ShortString shared=*p;if((c.state&2)&&p->size())(*p)[0]=0xd800;
  typedef void(*Fn)(ShortString*);autotest::invoke<Fn,ShortString*>(out,ours?&newShortDestroy:&oldShortDestroy,p);out.addHeapInUse();captureShort(out,shared);return;
 }
 Ogre::UTFString source(input);if(c.state&1)source.reserve(1024);Ogre::UTFString shared=source;
 if((c.state&2)&&source.size())source[0]=0x1234;
 Ogre::UTFString* p=(Ogre::UTFString*)autotest::allocate(sizeof(Ogre::UTFString));
 if(c.op==0){
  new(p) Ogre::UTFString(c.state&1?std::string(257,'Q'):std::string());if(c.state&2)p->reserve(2048);Ogre::UTFString old=*p;
  int error=0;std::string message;typedef Ogre::UTFString*(*Fn)(Ogre::UTFString*,const std::string&);
  try{autotest::invoke<Fn,Ogre::UTFString*,const std::string&>(out,ours?&newAssign:&oldAssign,p,input);}catch(const Ogre::UTFString::invalid_data&e){error=1;message=e.what();}catch(...){_exit(62);}
  out.add(&error,sizeof(error));out.addText(message);capture(out,*p);capture(out,old);out.addText(input);p->~UTFString();return;
 }
 if(c.op==1){
  typedef void(*Fn)(Ogre::UTFString*,const Ogre::UTFString&);autotest::invoke<Fn,Ogre::UTFString*,const Ogre::UTFString&>(out,ours?&newCopy:&oldCopy,p,source);
  capture(out,*p);capture(out,source);if(p->size())(*p)[0]=0x2345;capture(out,*p);capture(out,source);capture(out,shared);p->~UTFString();return;
 }
 new(p) Ogre::UTFString(source);if(c.state&1){p->asUTF8();p->asUTF32();p->asWStr();}if((c.state&2)&&p->size())(*p)[0]=0x3456;
 typedef void(*Fn)(Ogre::UTFString*);autotest::invoke<Fn,Ogre::UTFString*>(out,ours?&newDestroy:&oldDestroy,p);out.addHeapInUse();capture(out,source);capture(out,shared);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uint64_t address){autotest::Coverage cv(name,address);unsigned counts[]={0,1,2,8,80};for(unsigned n=0;n<8;++n)for(unsigned k=0;k<5;++k)for(unsigned state=0;state<4;++state){Case c={op,n,counts[k],state,0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){host->log("    sdk %u/%u/%u/%u\n",op,n,counts[k],state);cv.report(host);return 1;}}cv.report(host);return 0;}
}
TL_TEST(pass10_sdk_assign){return run(host,0,"pass10_sdk_assign",(uint64_t)(uintptr_t)&oldAssign);}
TL_TEST(pass10_sdk_copy){return run(host,1,"pass10_sdk_copy",(uint64_t)(uintptr_t)&oldCopy);}
TL_TEST(pass10_sdk_destroy){return run(host,2,"pass10_sdk_destroy",(uint64_t)(uintptr_t)&oldDestroy);}
TL_TEST(pass10_sdk_short_destroy){return run(host,3,"pass10_sdk_short_destroy",(uint64_t)(uintptr_t)&oldShortDestroy);}
