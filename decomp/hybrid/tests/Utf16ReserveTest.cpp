// Compare the actual linked UTF-16 reserve helper, including COW sharing.
#include <string>
#include <cstring>
#include "AutoTest.h"
typedef std::basic_string<unsigned short> Text;
TL_ORIGINAL(void,originalReserve,(Text*,size_t),"_ZNSbItSt11char_traitsItESaItEE7reserveEm")
extern "C" void candidateReserve(Text*,size_t) __asm__("_ZNSbItSt11char_traitsItESaItEE7reserveEm");
namespace {
struct Case {unsigned length,capacity,request,shared,pattern;};
void record(autotest::Capture& out,const Text& s){size_t n=s.size(),c=s.capacity();out.add(&n,sizeof(n));out.add(&c,sizeof(c));out.add(s.data(),(n+1)*sizeof(unsigned short));int refs;std::memcpy(&refs,reinterpret_cast<const char*>(s.data())-8,4);out.add(&refs,4);}
void side(void* p,autotest::Capture& out,bool ours){Case c=*(Case*)p;Text s;for(unsigned i=0;i<c.length;++i)s.push_back(c.pattern?static_cast<unsigned short>(i*257u):static_cast<unsigned short>(i%3?65:0));s.reserve(c.capacity);Text copy;if(c.shared)copy=s;record(out,s);record(out,copy);if(ours)autotest::invoke(out,&candidateReserve,&s,size_t(c.request));else autotest::invoke(out,&originalReserve,&s,size_t(c.request));record(out,s);record(out,copy);bool same=s.data()==copy.data();out.add(&same,sizeof(same));if(!s.empty())s[0]=0x1234;record(out,s);record(out,copy);}
void a(void* p,autotest::Capture& out){side(p,out,false);}void b(void* p,autotest::Capture& out){side(p,out,true);}
}
TL_TEST(utf16_reserve_differential){autotest::Coverage coverage("utf16_reserve_differential",(uint64_t)(uintptr_t)&originalReserve);const unsigned lengths[]={0,1,2,15,16,31,64,255},capacities[]={0,1,16,64,256},requests[]={0,1,2,15,16,31,64,255,256,512};for(unsigned l=0;l<8;++l)for(unsigned c=0;c<5;++c)for(unsigned r=0;r<10;++r)for(unsigned share=0;share<2;++share)for(unsigned pattern=0;pattern<2;++pattern){Case x={lengths[l],capacities[c],requests[r],share,pattern};autotest::Outcome u,v;autotest::runChild(a,&x,u);autotest::runChild(b,&x,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    reserve mismatch %u/%u/%u/%u/%u exits %d/%d\n",l,c,r,share,pattern,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
