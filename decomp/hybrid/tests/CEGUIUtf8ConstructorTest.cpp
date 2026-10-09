#include <string>
#include <cstring>
#include <new>
#define private public
#define protected public
#include <CEGUIString.h>
#undef private
#undef protected
#include "AutoTest.h"
TL_ORIGINAL(void,originalUtf8Ctor,(CEGUI::String*,const unsigned char*),"_ZN5CEGUI6StringC1EPKh")
extern "C" void candidateUtf8Ctor(CEGUI::String*,const unsigned char*) __asm__("_ZN5CEGUI6StringC1EPKh");
namespace {
struct Utf8CtorCase { unsigned count, profile; };
void utf8CtorSide(const Utf8CtorCase& c,bool ours,autotest::Capture& out){
 const char* units[]={"A","xy","\xc2\xa9","\xce\xa9","\xe4\xb8\xad","\xd0\x96","A\xce\xa9\xe4\xb8\xad","z"};
 std::string input;for(unsigned i=0;i<c.count;++i)input+=units[c.profile];
 if(c.profile==7){input+='\0';input+="ignored-after-nul";}
 // Defined padding protects the input boundary even when investigating the old decoder.
 const size_t logical=input.size();input.append(16,'\0');
 unsigned long long memory[(sizeof(CEGUI::String)+7)/8];std::memset(memory,0xa5,sizeof(memory));
 CEGUI::String* value=reinterpret_cast<CEGUI::String*>(memory);
 const unsigned char* bytes=reinterpret_cast<const unsigned char*>(input.c_str());
 if(ours)autotest::invoke(out,&candidateUtf8Ctor,value,bytes);
 else autotest::invoke(out,&originalUtf8Ctor,value,bytes);
 size_t length=value->length();out.add(&length,sizeof(length));
 for(size_t i=0;i<length;++i){CEGUI::utf32 item=(*value)[i];out.add(&item,sizeof(item));}
 bool quick=value->d_buffer==value->d_quickbuff;out.add(&quick,sizeof(quick));
 out.add(&value->d_reserve,sizeof(value->d_reserve));
 bool encoded=value->d_encodedbuff!=NULL;out.add(&encoded,sizeof(encoded));
 out.add(&value->d_encodedbufflen,sizeof(value->d_encodedbufflen));
 const char* rendered=value->c_str();out.addText(std::string(rendered));
 out.add(&logical,sizeof(logical));
 value->~String();
}
void originalUtf8Side(void* p,autotest::Capture& out){utf8CtorSide(*static_cast<Utf8CtorCase*>(p),false,out);}
void candidateUtf8Side(void* p,autotest::Capture& out){utf8CtorSide(*static_cast<Utf8CtorCase*>(p),true,out);}
}
TL_TEST(cegui_utf8_constructor_differential){
 autotest::Coverage coverage("cegui_utf8_constructor_differential",reinterpret_cast<uintptr_t>(&originalUtf8Ctor));
 const unsigned sizes[]={0,1,2,15,31,32,33,64,127,512};unsigned total=0;
 for(unsigned i=0;i<10;++i)for(unsigned profile=0;profile<8;++profile){
  Utf8CtorCase c={sizes[i],profile};autotest::Outcome a,b;
  autotest::runChild(originalUtf8Side,&c,a);autotest::runChild(candidateUtf8Side,&c,b);
  int difference=coverage.observe(host,a,b);++total;
  if(difference||a.childStatus||b.childStatus||!a.reportValid||!b.reportValid||!a.capture.callCompleted||!b.capture.callCompleted){
   coverage.report(host);host->log("    UTF8 ctor count %u profile %u differs, exits %d/%d\n",c.count,c.profile,a.childStatus,b.childStatus);return 1;
  }
 }
 coverage.report(host);host->log("    UTF8 constructor: %u completed ASCII/BMP/buffer-boundary comparisons\n",total);return 0;
}
