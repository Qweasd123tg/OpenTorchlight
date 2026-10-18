#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void*,aeOldGenericFactory,(void*,void*),"_ZN23CGenericModelDescriptor12CreateObjectEP12CEditorScene")
extern "C" void* aeNewGenericFactory(void*,void*) __asm__("_ZN23CGenericModelDescriptor12CreateObjectEP12CEditorScene");
TL_FUNCTION(aeGenericCtor,"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b")
extern "C" char aeAllocate[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char aeRelease[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
struct Case{unsigned seed;};autotest::Capture* output;void* resource;uint64_t storage[128];unsigned seed;struct Failure{};
void number(unsigned n){output->add(&n,4);}void check(bool ok){number(ok);if(!ok)output->issue=autotest::Capture::InvalidReport;}
void* allocate(size_t size,const char* file,int line,const char* function){number(1);output->add(&size,sizeof(size));number(!file);number(line);number(!function);std::memset(storage,seed|0x40,sizeof(storage));return storage;}
void release(void*p){number(2);check(p==storage);}
void ctor(void*p,void*res,void*manager,std::wstring mesh,std::wstring material,bool flag){number(3);check(p==storage);check(res==resource);number(!manager);output->addText(mesh);output->addText(material);number(flag);static_cast<unsigned char*>(p)[0x200]=seed;if(seed&0x100)throw Failure();}
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;output=&out;uint64_t desc[64]={0},scene[64]={0},res[8]={0};resource=seed&1?res:NULL;std::memcpy(reinterpret_cast<char*>(scene)+0x68,&resource,8);
 detour::Set d;TL_REDIRECT(d,aeGenericCtor,&ctor);d.redirect(aeAllocate,aeAllocate,&allocate);d.redirect(aeRelease,aeRelease,&release);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void*(*Fn)(void*,void*);Fn fn=ours?aeNewGenericFactory:aeOldGenericFactory;if(!autotest::beginInvocation(out,fn))return;
 try{void*result=fn(desc,scene);out.callCompleted=1;check(result==storage);out.add(storage,sizeof(storage));}catch(const Failure&){number(4);}
}
void old(void*p,autotest::Capture&c){side(p,c,false);}void newer(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_editor_generic_factory)
{
 autotest::Coverage coverage("advance_editor_generic_factory",(uint64_t)(uintptr_t)aeOldGenericFactory);
 for(unsigned seed=0;seed<32;++seed){Case c={seed};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);if(coverage.observe(host,a,b)){coverage.report(host);return 1;}}coverage.report(host);return 0;
}
TL_TEST(advance_editor_generic_factory_cleanup)
{
 for(unsigned seed=0;seed<8;++seed){Case c={seed|0x100};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);
  if(!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||a.capture.issue||b.capture.issue||!a.capture.callStarted||!b.capture.callStarted||a.capture.callCompleted||b.capture.callCompleted||a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length))return 1;
 }host->log("    Generic model factory: 8 matching expected constructor unwinds, excluded from normal coverage\n");return 0;
}
