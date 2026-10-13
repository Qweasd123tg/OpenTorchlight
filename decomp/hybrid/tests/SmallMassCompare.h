#ifndef SMALL_MASS_COMPARE_H
#define SMALL_MASS_COMPARE_H
#include "AutoTest.h"
#include "Detour.h"
#include <OgreVector3.h>
#include <string>

namespace smallmass {
struct Case { unsigned op, index; };
static autotest::Capture* output;
static Case* input;
template<class T> static T& field(void* p, unsigned offset) { return *reinterpret_cast<T*>(static_cast<char*>(p)+offset); }
static inline void* object(unsigned size) { void* p=autotest::allocate(size); if(!p) _exit(40); return p; }
static inline void number(unsigned v) { output->add(&v,sizeof(v)); }
static inline void floating(float v) { output->add(&v,sizeof(v)); }
static inline void pointer(const void* p) { output->add(&p,sizeof(p)); }
static inline void event(unsigned id,const void* p) { number(id);pointer(p); }
static inline void vector(const Ogre::Vector3& v) { output->add(&v,sizeof(v)); }
static inline void text(const std::string& v) { number(v.size());output->add(v.data(),v.size()); }
static inline void text(const std::wstring& v) { number(v.size());output->add(v.data(),v.size()*sizeof(wchar_t)); }
static inline float bits(unsigned v) { float f;std::memcpy(&f,&v,4);return f; }
static inline void list(void* p,unsigned offset,void* data,unsigned count,unsigned capacity) {
 field<void*>(p,offset)=data;field<unsigned>(p,offset+8)=count;
 field<unsigned>(p,offset+12)=capacity;field<unsigned>(p,offset+16)=10;
}
typedef void (*Side)(Case&,bool,autotest::Capture&);
static Side side;
static inline void original(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),false,out); }
static inline void recovered(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),true,out); }
static inline int run(const tlhybrid_host* host,unsigned op,const char* name,uint64_t address,Side implementation,unsigned count=192) {
 side=implementation;autotest::Coverage coverage(name,address);
 for(unsigned i=0;i<count;++i) {
  Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
  autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)) {
   host->log("    %s case %u status %d/%d child %d/%d bytes %lu/%lu\n",name,i,a.status,b.status,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
   unsigned at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
   host->log("    first difference %u, calls 0x%llx / 0x%llx, started %u/%u, completed %u/%u\n",at,(unsigned long long)a.capture.callTarget,(unsigned long long)b.capture.callTarget,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);
   for(unsigned j=at;j<at+32&&j<a.capture.length&&j<b.capture.length;++j) host->log("    byte %u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);
   coverage.report(host);return 1;
  }
 }
 coverage.report(host);return 0;
}
}
#endif
