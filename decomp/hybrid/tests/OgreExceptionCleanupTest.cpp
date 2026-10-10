#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
// Deallocation collaborators record terminal requests and retain storage for
// complete post-destruction observation; they do not claim physical freeing.
// Independent ownership assertions are applied to the original; candidate
// violations remain completed differences in the captured observations.
// Opaque owner deliberately avoids including OgreException.h: this fixture must
// never emit the inline destructors whose production copies it is verifying.
#define DTOR(N,S) TL_ORIGINAL(void,old##N,(void*),S) extern "C" void new##N(void*) __asm__(S);
DTOR(Delete,"_ZN4Ogre9ExceptionD0Ev")
DTOR(Complete,"_ZN4Ogre9ExceptionD1Ev")
DTOR(Base,"_ZN4Ogre9ExceptionD2Ev")
#undef DTOR
extern "C" char repDestroyFn[] __asm__("_ZNSs4_Rep10_M_destroyERKSaIcE");
extern "C" char deleteFn[] __asm__("_ZdlPv");
extern "C" char base1Fn[] __asm__("_ZNSt9exceptionD1Ev");
extern "C" char base2Fn[] __asm__("_ZNSt9exceptionD2Ev");
extern "C" char ogreVtable[] __asm__("_ZTVN4Ogre9ExceptionE");
extern "C" char baseVtable[] __asm__("_ZTVSt9exception");
namespace {
struct Case { unsigned kind,mode,mask,length; };
struct Rep { char* data; unsigned frees; size_t capacity; int before; };
Rep reps[5];unsigned count,baseCalls,outerFrees,serial;autotest::Capture* cap;void* owner;char* guarded;
std::string* retained;unsigned kind;const void* emptyData;
template<class T>T& at(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
void n(unsigned x){cap->add(&x,sizeof(x));}
void require(bool ok){if(!ok)cap->issue=autotest::Capture::InvalidReport;}
unsigned repIndex(const void* p){for(unsigned i=0;i<count;++i)if(p==reps[i].data||p==reps[i].data-24)return i+1;return 0;}
void pointer(const void* p){if(p==owner)n(100);else if(p==ogreVtable+16)n(101);else if(p==baseVtable+16)n(102);else {unsigned i=repIndex(p);n(i);require(i!=0);}}
void state(){
 cap->add(guarded,16);cap->add(guarded+80,16);pointer(at<void*>(owner,0));cap->add(static_cast<char*>(owner)+8,16);
 for(unsigned i=0;i<5;++i){const void* data=at<void*>(owner,24+i*8);unsigned id=repIndex(data);n(id);if(!id)require(data==emptyData);}
 for(unsigned i=0;i<count;++i){n(i);cap->add(reps[i].data-24,24);cap->add(reps[i].data,reps[i].capacity+1);n(reps[i].frees);}
 for(unsigned i=0;i<5;++i){const std::string& s=retained[i];n(repIndex(s.data()));cap->addText(s);}
}
void release(void* p){n(1);n(++serial);pointer(p);if(p==owner)++outerFrees;else{unsigned id=repIndex(p);require(id!=0);if(id)++reps[id-1].frees;}state();}
void destroyRep(void* p,const void*){n(4);n(++serial);pointer(p);unsigned id=repIndex(p);require(id!=0);if(id)++reps[id-1].frees;state();}
void baseDestructor(void* p){n(2);n(++serial);pointer(p);require(p==owner);++baseCalls;state();at<void*>(p,0)=baseVtable+16;}
void setup(const Case& c){count=baseCalls=outerFrees=serial=0;kind=c.kind;guarded=static_cast<char*>(autotest::allocate(96));memset(guarded,0xa7,96);owner=guarded+16;at<void*>(owner,0)=ogreVtable+16;at<long>(owner,8)=-91827364L;at<int>(owner,16)=37;
 retained=static_cast<std::string*>(autotest::allocate(5*sizeof(std::string)));for(unsigned i=0;i<5;++i)::new(retained+i)std::string();emptyData=retained[0].data();
 for(unsigned i=0;i<5;++i){std::string* s=&at<std::string>(owner,24+i*8);::new(s)std::string();if(c.mask&(1u<<i)){char bytes[128];unsigned length=c.length+i*3+1;memset(bytes,char('A'+i),length);if(length>4)bytes[3]='\0';*s=std::string(bytes,length);}}
 if(c.mode==1||c.mode==2){at<std::string>(owner,24)=std::string(c.length+7,'S');for(unsigned i=1;i<5;++i)at<std::string>(owner,24+i*8)=at<std::string>(owner,24);if(c.mode==2)retained[0]=at<std::string>(owner,24);}
 if(c.mode==3){for(unsigned i=0;i<5;++i)if(c.mask&(1u<<i))retained[i]=at<std::string>(owner,24+i*8);}
 if(c.mode==4){for(unsigned i=0;i<5;++i){std::string& s=at<std::string>(owner,24+i*8);if(!s.empty())s[0]=char('a'+i);}}
 for(unsigned i=0;i<5;++i){std::string& s=at<std::string>(owner,24+i*8);if(s.empty()||repIndex(s.data()))continue;Rep& r=reps[count++];r.data=const_cast<char*>(s.data());r.frees=0;r.capacity=s.capacity();r.before=*reinterpret_cast<int*>(r.data-8);for(size_t j=s.size()+1;j<=r.capacity;++j)r.data[j]=char(0x59);}
}
typedef void(*Fn)(void*);
Fn function(unsigned k,bool candidate){if(k==0)return candidate?newDelete:oldDelete;if(k==1)return candidate?newComplete:oldComplete;return candidate?newBase:oldBase;}
void side(void* p,autotest::Capture& out,bool candidate){const Case& c=*static_cast<Case*>(p);cap=&out;setup(c);state();detour::Set d;d.redirect(repDestroyFn,repDestroyFn,&destroyRep);d.redirect(deleteFn,deleteFn,&release);d.redirect(base1Fn,base1Fn,&baseDestructor);if(base1Fn!=base2Fn)d.redirect(base2Fn,base2Fn,&baseDestructor);require(!d.failed());Fn fn=function(c.kind,candidate);require(autotest::beginInvocation(out,fn));fn(owner);out.callCompleted=1;n(3);state();n(baseCalls);n(outerFrees);
 if(!candidate)require(baseCalls==1&&outerFrees==(c.kind==0?1u:0u));
 for(unsigned r=0;r<count;++r){unsigned own=0,keep=0;for(unsigned i=0;i<5;++i){if(at<void*>(owner,24+i*8)==reps[r].data)++own;if(retained[i].data()==reps[r].data)++keep;}if(!candidate)require(reps[r].frees==(keep?0u:1u));int after=*reinterpret_cast<int*>(reps[r].data-8);int expected=reps[r].before-static_cast<int>(own);if(!candidate)require(after==expected);}
}
void originalSide(void* p,autotest::Capture& o){side(p,o,false);}void candidateSide(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,const char* name,unsigned kind){autotest::Coverage coverage(name,reinterpret_cast<uint64_t>(function(kind,false)));unsigned index=0;
 for(unsigned mode=0;mode<5;++mode)for(unsigned mask=0;mask<32;++mask){if((mode==1||mode==2)&&mask!=31)continue;Case c={kind,mode,mask,(mask%3==0?0u:mask%3==1?7u:96u)};autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);if(coverage.observe(host,a,b)){host->log("    cleanup case %u mode%u mask%u status%d/%d issue%u/%u bytes%u/%u\n",index,mode,mask,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned)a.capture.length,(unsigned)b.capture.length);coverage.report(host);return 1;}++index;}
 coverage.report(host);return coverage.completed!=98;
}
}
TL_TEST(gameui_ogre_exception_delete){return run(host,"gameui_ogre_exception_delete",0);}
TL_TEST(gameui_ogre_exception_complete){return run(host,"gameui_ogre_exception_complete",1);}
TL_TEST(gameui_ogre_exception_base){return run(host,"gameui_ogre_exception_base",2);}
