#include <string>
#include <cstring>
#include "AutoTest.h"
TL_ORIGINAL(std::string, originalCStringPlus, (const char*,const std::string&), "_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_")
TL_ORIGINAL(std::string, originalStringPlus, (const std::string&,const std::string&), "_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_S8_")
extern "C" std::string restoredCStringPlus(const char*,const std::string&) __asm__("_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_");
extern "C" std::string restoredStringPlus(const std::string&,const std::string&) __asm__("_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_S8_");
namespace {
struct Case {unsigned a,b,reserve,kind;};
std::string make(unsigned kind){if(kind==0)return std::string();if(kind==1)return std::string("x");if(kind==2)return std::string("alpha beta");if(kind==3)return std::string("a\0b",3);if(kind==4)return std::string(63,'q');return std::string(4097,'z');}
void side(const Case& c,bool ours,autotest::Capture& out){std::string a=make(c.a),b=make(c.b);if(c.reserve){a.reserve(8192);b.reserve(8192);}std::string sharedA=a,sharedB=b;
 if(c.kind==0){if(ours)autotest::invoke(out,&restoredCStringPlus,a.c_str(),b);else autotest::invoke(out,&originalCStringPlus,a.c_str(),b);}
 else {if(ours)autotest::invoke(out,&restoredStringPlus,a,b);else autotest::invoke(out,&originalStringPlus,a,b);}
 out.addText(a);out.addText(b);out.addText(sharedA);out.addText(sharedB);
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(narrow_string_plus_production){
 autotest::Coverage first("narrow_string_plus_production",(uint64_t)(uintptr_t)&originalCStringPlus),second("narrow_string_plus_production",(uint64_t)(uintptr_t)&originalStringPlus);int failures=0;
 for(unsigned k=0;k<2;++k)for(unsigned i=0;i<6;++i)for(unsigned j=0;j<6;++j)for(unsigned reserve=0;reserve<2;++reserve){Case c={i,j,reserve,k};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=(k?second:first).observe(host,x,y);bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;if(!ok){++failures;host->log("    narrow plus %u input %u/%u reserve %u: status %d/%d bytes %lu/%lu\n",k,i,j,reserve,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);}}
 first.report(host);second.report(host);return failures;
}
