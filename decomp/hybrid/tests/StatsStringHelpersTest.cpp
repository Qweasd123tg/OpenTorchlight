#include <string>
#include <exception>
#include <cstring>
#include <OgreUTFString.h>
#include "AutoTest.h"
TL_ORIGINAL(size_t,oldVerify,(const std::string&),"_ZN4Ogre9UTFString11_verifyUTF8ERKSs")
extern "C" size_t newVerify(const std::string&) __asm__("_ZN4Ogre9UTFString11_verifyUTF8ERKSs");
TL_ORIGINAL(void,oldMutate,(std::basic_string<unsigned short>*,size_t,size_t,size_t),"_ZNSbItSt11char_traitsItESaItEE9_M_mutateEmmm")
extern "C" void newMutate(std::basic_string<unsigned short>*,size_t,size_t,size_t) __asm__("_ZNSbItSt11char_traitsItESaItEE9_M_mutateEmmm");
namespace {
struct VerifyCase {std::string text;};
void verify(void* p,autotest::Capture& out,bool ours){VerifyCase& c=*(VerifyCase*)p;size_t(*fn)(const std::string&)=ours?newVerify:oldVerify;if(!autotest::beginInvocation(out,fn))return;int kind=0;size_t count=0;std::string error;try{count=fn(c.text);}catch(const Ogre::UTFString::invalid_data& e){kind=1;error=e.what();}catch(const std::exception& e){kind=2;error=e.what();}out.callCompleted=1;out.add(&kind,sizeof(kind));out.add(&count,sizeof(count));out.addText(error);out.addText(c.text);}
void va(void* p,autotest::Capture& o){verify(p,o,false);}void vb(void* p,autotest::Capture& o){verify(p,o,true);}
struct MutateCase {unsigned size,pos,remove,insert,reserve,shared;};
void mutate(void* p,autotest::Capture& out,bool ours){MutateCase c=*(MutateCase*)p;typedef std::basic_string<unsigned short> S;S s;for(unsigned i=0;i<c.size;++i)s.push_back((unsigned short)(i*913+1));if(c.reserve)s.reserve(160);S saved=s;if(!c.shared)saved.clear();if(ours)autotest::invoke(out,&newMutate,&s,size_t(c.pos),size_t(c.remove),size_t(c.insert));else autotest::invoke(out,&oldMutate,&s,size_t(c.pos),size_t(c.remove),size_t(c.insert));
// _M_mutate leaves the inserted span uninitialized; initialize exactly that span.
for(unsigned i=0;i<c.insert;++i)s[c.pos+i]=(unsigned short)(0x8100+i);size_t n=s.size();out.add(&n,sizeof(n));out.add(s.data(),n*sizeof(unsigned short));n=saved.size();out.add(&n,sizeof(n));out.add(saved.data(),n*sizeof(unsigned short));unsigned short end=s.c_str()[s.size()];out.add(&end,sizeof(end));}
void ma(void* p,autotest::Capture& o){mutate(p,o,false);}void mb(void* p,autotest::Capture& o){mutate(p,o,true);}
}
TL_TEST(stats_utf8_verifier_differential){autotest::Coverage cv("stats_utf8_verifier_differential",(uint64_t)(uintptr_t)&oldVerify);const char* pieces[]={"","ASCII","\xc2\xa9","\xe4\xb8\xad","\xf0\x9f\x98\x80","\xf8\x88\x80\x80\x80","\xfc\x84\x80\x80\x80\x80","\xc0\x80","\xe0\x80\x80","\xf0\x80\x80\x80","\xf8\x80\x80\x80\x80","\xfc\x80\x80\x80\x80\x80","\xc2Q","\xe4Q\x80","\xf0\x9fQ\x80","\x80","\xff","\xc1\x81"};for(unsigned i=0;i<sizeof(pieces)/sizeof(*pieces);++i)for(unsigned repeat=1;repeat<=4;++repeat){VerifyCase c;for(unsigned j=0;j<repeat;++j){c.text+="prefix";c.text+=pieces[i];c.text+="suffix";}autotest::Outcome a,b;autotest::runChild(va,&c,a);autotest::runChild(vb,&c,b);if(cv.observe(host,a,b)){host->log("    verifier case %u repeat %u statuses %d/%d\n",i,repeat,a.childStatus,b.childStatus);return 1;}}cv.report(host);return 0;}
TL_TEST(stats_utf16_mutate_differential){autotest::Coverage cv("stats_utf16_mutate_differential",(uint64_t)(uintptr_t)&oldMutate);const unsigned sizes[]={0,1,2,7,32,70};const unsigned adds[]={0,1,2,13,100};for(unsigned z=0;z<6;++z)for(unsigned pos=0;pos<=sizes[z];pos+=(sizes[z]>7?7:1))for(unsigned rem=0;rem<3;++rem)for(unsigned add=0;add<5;++add)for(unsigned reserve=0;reserve<2;++reserve)for(unsigned shared=0;shared<2;++shared){MutateCase c={sizes[z],pos,rem==0?0:rem==1?(sizes[z]-pos)/2:sizes[z]-pos,adds[add],reserve,shared};autotest::Outcome a,b;autotest::runChild(ma,&c,a);autotest::runChild(mb,&c,b);if(cv.observe(host,a,b)){host->log("    mutate size %u pos %u remove %u insert %u reserve %u shared %u status %d/%d bytes %lu/%lu\n",c.size,pos,c.remove,c.insert,reserve,shared,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}}cv.report(host);return 0;}
