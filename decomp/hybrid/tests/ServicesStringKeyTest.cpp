#include "SmallMassCompare.h"
#include <queue>
TL_ORIGINAL(unsigned, origWideSize, (const wchar_t*, unsigned), "_ZN7STRINGS22StringSizeOfWCharArrayEPKwj")
extern "C" unsigned mineWideSize(const wchar_t*, unsigned) __asm__("_ZN7STRINGS22StringSizeOfWCharArrayEPKwj");
TL_ORIGINAL(unsigned, origCharSize, (const char*, unsigned), "_ZN7STRINGS21StringSizeOfCharArrayEPKcj")
extern "C" unsigned mineCharSize(const char*, unsigned) __asm__("_ZN7STRINGS21StringSizeOfCharArrayEPKcj");
TL_ORIGINAL(int, origShift, (void*,int,bool), "_ZN11CKeyManager14shiftCharacterEib")
extern "C" int mineShift(void*,int,bool) __asm__("_ZN11CKeyManager14shiftCharacterEib");
TL_ORIGINAL(void, origWideTokens, (std::queue<std::wstring>*,const std::wstring&,const wchar_t*), "_ZN7STRINGS14TokenizeStringEPSt5queueISbIwSt11char_traitsIwESaIwEESt5dequeIS4_SaIS4_EEERKS4_PKw")
extern "C" void mineWideTokens(std::queue<std::wstring>*,const std::wstring&,const wchar_t*) __asm__("_ZN7STRINGS14TokenizeStringEPSt5queueISbIwSt11char_traitsIwESaIwEESt5dequeIS4_SaIS4_EEERKS4_PKw");
TL_ORIGINAL(void, origCharTokens, (std::queue<std::string>*,const std::string&,const char*), "_ZN7STRINGS14TokenizeStringEPSt5queueISsSt5dequeISsSaISsEEERKSsPKc")
extern "C" void mineCharTokens(std::queue<std::string>*,const std::string&,const char*) __asm__("_ZN7STRINGS14TokenizeStringEPSt5queueISsSt5dequeISsSaISsEEERKSsPKc");
namespace {
using namespace smallmass;
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;
 if(c.op<2) {
  wchar_t w[64];char b[64];for(unsigned i=0;i<64;++i) {w[i]=L'X';b[i]='X';}
  unsigned length=(c.index/8)%8;w[length]=0;b[length]=0;unsigned limit=c.index%8;
  if(c.op==0)autotest::invoke(out,ours?mineWideSize:origWideSize,w,limit);
  else autotest::invoke(out,ours?mineCharSize:origCharSize,b,limit);
 } else if(c.op==2) {
  void* self=object(0xd18);autotest::invoke(out,ours?mineShift:origShift,self,int(c.index/2)-20,bool(c.index&1));
 } else {
  const char* values[]={"", "abc", ",", ",,", "a,b", "a,,b,", ",start", "tail,", "a::b::c", "aaXbbXcc", "::", "a:a:a", "abc::xyz,tail"};
  const char* separators[]={",", "::", "X", "no-match"};
  std::string text(values[c.index%13]);std::string sep(separators[(c.index/13)%4]);
  if(c.op==3) {
   std::queue<std::string> tokens;if(c.index&1)tokens.push("existing");
   autotest::invoke(out,ours?mineCharTokens:origCharTokens,&tokens,text,sep.c_str());
   number(tokens.size());while(!tokens.empty()){smallmass::text(tokens.front());tokens.pop();}
  } else {
   std::wstring wide(text.begin(),text.end()),separator(sep.begin(),sep.end());std::queue<std::wstring> tokens;
   if(c.index&1)tokens.push(L"existing");
   autotest::invoke(out,ours?mineWideTokens:origWideTokens,&tokens,wide,separator.c_str());
   number(tokens.size());while(!tokens.empty()){smallmass::text(tokens.front());tokens.pop();}
  }
 }
}
}
TL_TEST(services_wide_size){return smallmass::run(host,0,"services_wide_size",0xc8d720,execute,64);}
TL_TEST(services_char_size){return smallmass::run(host,1,"services_char_size",0xc8d760,execute,64);}
TL_TEST(services_shift_character){return smallmass::run(host,2,"services_shift_character",0x91a6b0,execute,560);}
TL_TEST(services_char_tokens){return smallmass::run(host,3,"services_char_tokens",0xc8f060,execute,104);}
TL_TEST(services_wide_tokens){return smallmass::run(host,4,"services_wide_tokens",0xc8ebb0,execute,104);}
