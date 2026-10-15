#include "SmallMassCompare.h"
#include <clocale>
#include <climits>
#include <cfloat>
TL_ORIGINAL(std::wstring, old0, (const std::string&), "_ZN7STRINGS19StringConvertToWideERKSs")
extern "C" std::wstring next0(const std::string&) __asm__("_ZN7STRINGS19StringConvertToWideERKSs");
TL_ORIGINAL(std::string, old1, (const std::string&), "_ZN7STRINGS11StringUpperERKSs")
extern "C" std::string next1(const std::string&) __asm__("_ZN7STRINGS11StringUpperERKSs");
TL_ORIGINAL(std::wstring, old2, (const std::wstring&), "_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
extern "C" std::wstring next2(const std::wstring&) __asm__("_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(std::string, old3, (const wchar_t*), "_ZN7STRINGS21StringConvertToNarrowEPKw")
extern "C" std::string next3(const wchar_t*) __asm__("_ZN7STRINGS21StringConvertToNarrowEPKw");
TL_ORIGINAL(std::string, old4, (int), "_ZN7STRINGS16GetValueAsStringEi")
extern "C" std::string next4(int) __asm__("_ZN7STRINGS16GetValueAsStringEi");
TL_ORIGINAL(std::string, old5, (const std::string&), "_ZN7STRINGS10uniqueNameERKSs")
extern "C" std::string next5(const std::string&) __asm__("_ZN7STRINGS10uniqueNameERKSs");
TL_ORIGINAL(std::string, old6, (float), "_ZN7STRINGS16GetValueAsStringEf")
extern "C" std::string next6(float) __asm__("_ZN7STRINGS16GetValueAsStringEf");

extern wchar_t conversionBuffer[5000] __asm__("_ZZN7STRINGS19StringConvertToWideERKSsE4buff");
extern unsigned uniqueCounter __asm__("_ZZN7STRINGS10uniqueNameERKSsE16gUniqueNameValue");
namespace {
void execute(smallmass::Case& c, bool ours, autotest::Capture& out) {
 using namespace smallmass;
 output=&out;
 if(!std::setlocale(LC_CTYPE,c.index&1 ? "C.UTF-8" : "C")) {out.issue=autotest::Capture::InvalidReport;return;}
 std::string narrow;std::wstring wide;
 const unsigned lengths[]={0,1,2,7,64,256,4999};
 unsigned length=lengths[(c.index/2)%7];
 for(unsigned i=0;i<length;++i) {
  narrow+=char((i+c.index/14)%256);
  wide+=wchar_t((i*101+c.index/14)%0x10000);
 }
 if(c.op==0) {
  for(unsigned i=0;i<5000;++i)conversionBuffer[i]=0xabc000+i;
  typedef std::wstring(*Fn)(const std::string&);Fn fn=ours?next0:old0;
  if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(narrow);out.callCompleted=1;
  text(value);text(narrow);out.add(conversionBuffer,sizeof(conversionBuffer));
 } else if(c.op==1) {
  // Match the original signed-char toupper call, using its defined ASCII domain.
  for(unsigned i=0;i<narrow.size();++i)narrow[i]&=0x7f;
  std::string saved=narrow;
  typedef std::string(*Fn)(const std::string&);Fn fn=ours?next1:old1;
  if(!autotest::beginInvocation(out,fn))return;std::string value=fn(narrow);out.callCompleted=1;text(value);text(narrow);text(saved);
 } else if(c.op==2) {
  typedef std::wstring(*Fn)(const std::wstring&);Fn fn=ours?next2:old2;
  if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(wide);out.callCompleted=1;text(value);text(wide);
 } else if(c.op==3) {
  typedef std::string(*Fn)(const wchar_t*);Fn fn=ours?next3:old3;
  if(!autotest::beginInvocation(out,fn))return;std::string value=fn(wide.c_str());out.callCompleted=1;text(value);text(wide);
 } else if(c.op==4) {
  const int integers[]={0,1,-1,INT_MIN,INT_MAX,10,-10,999999,-999999};
  typedef std::string(*Fn)(int);Fn fn=ours?next4:old4;
  if(!autotest::beginInvocation(out,fn))return;std::string value=fn(integers[c.index%9]);out.callCompleted=1;text(value);
 } else if(c.op==5) {
  const unsigned counters[]={0,1,99,0x7fffffffu,0xfffffffeu,0xffffffffu};
  uniqueCounter=counters[c.index%6];
  typedef std::string(*Fn)(const std::string&);Fn fn=ours?next5:old5;
  if(!autotest::beginInvocation(out,fn))return;std::string value=fn(narrow);std::string again=fn(narrow);out.callCompleted=1;
  text(value);text(again);number(uniqueCounter);text(narrow);
 } else {
  const unsigned values[]={0,0x80000000u,0x3f800000,0xbf800000,0x00800000,1,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00000,0xffc12345,0x3eaaaaab,0x4b800001};
  typedef std::string(*Fn)(float);Fn fn=ours?next6:old6;
  if(!autotest::beginInvocation(out,fn))return;std::string value=fn(bits(values[c.index%14]));out.callCompleted=1;text(value);
 }
}
}
TL_TEST(followup_strings_c8daf0) { return smallmass::run(host,0,"followup_strings_c8daf0",(uint64_t)(uintptr_t)old0,execute,84); }
TL_TEST(followup_strings_c8e0e0) { return smallmass::run(host,1,"followup_strings_c8e0e0",(uint64_t)(uintptr_t)old1,execute,84); }
TL_TEST(followup_strings_c8e190) { return smallmass::run(host,2,"followup_strings_c8e190",(uint64_t)(uintptr_t)old2,execute,84); }
TL_TEST(followup_strings_c8e350) { return smallmass::run(host,3,"followup_strings_c8e350",(uint64_t)(uintptr_t)old3,execute,84); }
TL_TEST(followup_strings_c8e810) { return smallmass::run(host,4,"followup_strings_c8e810",(uint64_t)(uintptr_t)old4,execute,28); }
TL_TEST(followup_strings_c8ea50) { return smallmass::run(host,5,"followup_strings_c8ea50",(uint64_t)(uintptr_t)old5,execute,84); }
TL_TEST(followup_strings_c90a30) { return smallmass::run(host,6,"followup_strings_c90a30",(uint64_t)(uintptr_t)old6,execute,28); }
