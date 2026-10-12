// Direct actual-definition pairs. Expected results come from explicit sorted
// key tables, callback boundary assertions, and byte-preservation checks.
#include <map>
#include <string>
#include <cstdlib>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, qrOldReset, (void*,bool), "_ZN13CQuestManager17resetQuestManagerEb")
extern "C" void qrNewReset(void*,bool) __asm__("_ZN13CQuestManager17resetQuestManagerEb");
TL_ORIGINAL(void, qrOldNames, (void*,void*), "_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
extern "C" void qrNewNames(void*,void*) __asm__("_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE");
TL_FUNCTION(qrReinitialize,"_ZN6CQuest17reinitializeQuestEbb")
extern "C" char qrArrayNew[] __asm__("_Znam");
extern "C" char qrArrayDelete[] __asm__("_ZdaPv");
extern "C" char qrCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qrAssign[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_");
namespace qr {
typedef std::map<std::wstring,void*> Quests;
typedef std::map<std::wstring,bool> Complete;
typedef char MapABI[sizeof(Quests)==48&&sizeof(Complete)==48&&sizeof(std::wstring)==8?1:-1];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>((char*)p+off);}
struct Stop {};
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x265e700u&&!tail[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,autotest::Body a,autotest::Body b,void* c,bool fault){
 autotest::Outcome x,y;autotest::runChild(a,c,x);autotest::runChild(b,c,y);
 bool ok=good(x)&&good(y)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(!fault){if(cv.observe(host,x,y))ok=false;}else ok=ok&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==cv.original&&host&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget);
 if(!ok)host->log(" reset/names pair status=%d/%d oracle=%u/%u issue=%u/%u\n",x.childStatus,y.childStatus,good(x),good(y),x.capture.issue,y.capture.issue);return ok;
}
}
namespace qr_reset {
using namespace qr;
struct Case {unsigned shape,flag,mode,fault;};
const Case* cs;autotest::Capture* cap;unsigned errors,calls,deletes,nq,nc;unsigned char* owner;Quests* quests;Complete* complete;void** rawList;void* objects[8];void* expected[8];unsigned expectedCalls;std::wstring keys[8];unsigned char before[0xd0];
void need(bool x){if(!x)++errors;}void n(unsigned x){cap->add(&x,4);}
void released(void* p){++deletes;n(0xdee1);need(p==rawList);need(at<void*>(owner,0x18)==rawList);need(at<unsigned>(owner,0x20)==0&&at<unsigned>(owner,0x24)==0);need(at<unsigned>(owner,0x28)==7);
 unsigned i=0;for(Complete::iterator it=complete->begin();it!=complete->end();++it,++i)need(it->second==((i&1)==0));
 for(unsigned j=0;j<4;++j)need(rawList[j]==objects[3-j]);
 if(cs->mode==4)complete->insert(Complete::value_type(L"z after allocation callback",true));
 std::free(p);
}
void reset(void* self,bool a,bool b){n(0xca11);unsigned id=99;for(unsigned j=0;j<8;++j)if(self==objects[j])id=j;n(id);n(a);n(b);need(calls<expectedCalls&&self==expected[calls]);need(a==(cs->flag!=0)&&!b);need(!at<void*>(owner,0x18)&&!at<unsigned>(owner,0x20)&&!at<unsigned>(owner,0x24));
 for(Complete::iterator it=complete->begin();it!=complete->end();++it)need(it->second==(calls>0&&cs->mode==3&&it==complete->begin()));
 ++calls;if(calls==1){
  if(cs->mode==1&&nq>1)(*quests)[keys[1]]=objects[7];
  if(cs->mode==2){quests->insert(Quests::value_type(L"\uffff appended",objects[6]));}
  if(cs->mode==3&&!complete->empty())complete->begin()->second=true;
  if(cs->fault)throw Stop();
 }
}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;errors=calls=deletes=0;autotest::g_arenaUsed=0;owner=(unsigned char*)autotest::allocate(0xf0);std::memset(owner,0x9d,0xf0);owner+=16;quests=new(owner+0x40)Quests;complete=new(owner+0x70)Complete;
 for(unsigned i=0;i<8;++i)objects[i]=autotest::allocate(16);
 nq=cs->shape==0?0:cs->shape==1?1:cs->shape==2?3:5;nc=cs->shape==0?3:cs->shape==1?0:cs->shape==2?1:5;
 const wchar_t* names[]={L"",L"A",L"Quest",L"\u041a\u0432\u0435\u0441\u0442",L"\u4efb\u52a1"};
 for(unsigned i=0;i<nq;++i){keys[i]=names[i];expected[i]=objects[i];}
 // Deliberately seed a non-sorted shape: callback order is key order.
 const unsigned order[]={3,1,4,0,2};for(unsigned j=0;j<5;++j){unsigned i=order[j];if(i<nq)quests->insert(Quests::value_type(keys[i],objects[i]));}
 for(unsigned i=0;i<nc;++i)complete->insert(Complete::value_type(std::wstring(1,wchar_t(L'a'+i)),(i&1)==0));
 rawList=cs->shape==1?0:(void**)std::malloc(4*sizeof(void*));if(rawList)for(unsigned i=0;i<4;++i)rawList[i]=objects[3-i];
 at<void*>(owner,0x18)=rawList;at<unsigned>(owner,0x20)=cs->shape==0?0:3;at<unsigned>(owner,0x24)=rawList?4:0;at<unsigned>(owner,0x28)=7;
 expectedCalls=nq;if(cs->mode==1&&nq>1)expected[1]=objects[7];if(cs->mode==2&&nq)expected[expectedCalls++]=objects[6];if(cs->fault)expectedCalls=1;
 std::memcpy(before,owner,0xd0);typedef void(*Fn)(void*,bool);Fn fn=candidate?&qrNewReset:&qrOldReset;bool caught=false;
 {detour::Set callbacks,deallocation;TL_REDIRECT(callbacks,qrReinitialize,&reset);deallocation.redirect(qrArrayDelete,qrArrayDelete,&released);if(callbacks.failed()||deallocation.failed()){out.issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(out,fn))return;try{fn(owner,cs->flag!=0);out.callCompleted=1;}catch(const Stop&){caught=true;}}
 need(caught==(cs->fault!=0));need(calls==expectedCalls);need(deletes==(rawList?1u:0u));need(quests->size()==nq+(cs->mode==2&&nq?1:0));need(complete->size()==nc+(cs->mode==4&&rawList?1:0));
 for(Complete::iterator it=complete->begin();it!=complete->end();++it){bool want=cs->mode==3&&nq&&it==complete->begin();need(it->second==want);out.addText(it->first);n(it->second);}
 for(unsigned i=0;i<nq;++i){Quests::iterator it=quests->find(keys[i]);need(it!=quests->end()&&it->second==(cs->mode==1&&i==1?objects[7]:objects[i]));}
 unsigned char actual[0xd0];std::memcpy(actual,owner,0xd0);std::memset(actual+0x40,0,96);std::memset(before+0x40,0,96);at<void*>(before,0x18)=0;at<unsigned>(before,0x20)=at<unsigned>(before,0x24)=0;need(!std::memcmp(actual,before,0xd0));for(unsigned i=0;i<16;++i)need(owner[-16+(int)i]==0x9d&&owner[0xd0+i]==0x9d);
 n(calls);n(deletes);n(caught);n(0x265e700u);n(errors);quests->~Quests();complete->~Complete();
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(questmanager_reset_all){using namespace qr_reset;autotest::Coverage cv("questmanager_reset_all",0xd26560);unsigned count=0;for(unsigned shape=0;shape<4;++shape)for(unsigned flag=0;flag<2;++flag)for(unsigned mode=0;mode<5;++mode){Case c={shape,flag,mode,0};if(!qr::pair(host,cv,a,b,&c,false)){host->log(" reset-all shape=%u flag=%u mode=%u\n",shape,flag,mode);cv.report(host);return 1;}++count;}cv.report(host);return cv.completed!=count||cv.different||cv.missing;}
TL_TEST(questmanager_reset_all_exceptions){using namespace qr_reset;autotest::Coverage cv("reset-all unwind excluded",0xd26560);for(unsigned flag=0;flag<2;++flag){Case c={3,flag,0,1};if(!qr::pair(host,cv,a,b,&c,true))return 1;}host->log(" reset-all: 2 expected callback unwinds, no completed coverage\n");return 0;}
namespace qr_names {
using namespace qr;
struct Array {std::wstring* data;unsigned count,capacity,grow,pad;};
typedef char ArrayABI[sizeof(Array)==24?1:-1];
struct Case {unsigned shape,layout,variant,repeat,fault;};
const Case* cs;autotest::Capture* cap;unsigned errors,copies,allocations,deletions,oldAssignments,nq,initialCount,initialCapacity,expectedCount,expectedCapacity,currentPass;unsigned char* owner;Quests* quests;Array* list;std::wstring expected[64],keyValues[8];const std::wstring* mapKeys[8];int initialRefs[8];std::wstring* oldData;unsigned oldCap;bool shifted;detour::Set *copyPatch,*assignPatch;void* allocationsRaw[32];unsigned liveAllocations;
int refs(const std::wstring& s){return *(const int*)((const char*)s.c_str()-8);}
void need(bool x){if(!x)++errors;}void n(unsigned x){cap->add(&x,4);}
void keyRefs(){for(unsigned i=0;i<nq;++i){if(mapKeys[i]->empty())continue;unsigned shares=0;for(unsigned j=0;j<list->count;++j)if(list->data[j].c_str()==mapKeys[i]->c_str())++shares;need(refs(*mapKeys[i])==initialRefs[i]+(initialRefs[i]<0?0:shares));}}
void copy(std::wstring* dst,const std::wstring& src){unsigned id=99;for(unsigned i=0;i<nq;++i)if(&src==mapKeys[i])id=i;
 if(id!=99){keyRefs();need(id==copies%nq);++copies;n(0xc0f1);n(id);if(cs->fault==2)throw Stop();}
 copyPatch->restore();reinterpret_cast<void(*)(std::wstring*,const std::wstring&)>(qrCopy)(dst,src);copyPatch->redirect(qrCopy,qrCopy,&copy);need(!copyPatch->failed());
}
std::wstring& assign(std::wstring* dst,const std::wstring& src){if(oldData){uintptr_t p=(uintptr_t)&src,b=(uintptr_t)oldData;if(p>=b&&p<b+8*oldCap){unsigned index=(p-b)/8;need(index==oldAssignments);++oldAssignments;n(0xa551);n(index);}}
 assignPatch->restore();std::wstring& result=reinterpret_cast<std::wstring&(*)(std::wstring*,const std::wstring&)>(qrAssign)(dst,src);assignPatch->redirect(qrAssign,qrAssign,&assign);need(!assignPatch->failed());return result;
}
void* allocate(size_t bytes){++allocations;n(0xa110);n(bytes);unsigned next=list->data?list->capacity+list->grow:list->grow;need(bytes==8+8*next);if(!list->data)need(list->capacity==list->grow);
 if(cs->fault==1)throw std::bad_alloc();oldData=list->data;oldCap=list->capacity;oldAssignments=0;
 if(cs->layout==4&&!shifted&&oldData){shifted=true;list->count=1;}
 void* p=std::malloc(bytes);if(!p)throw std::bad_alloc();need(liveAllocations<32);if(liveAllocations>=32)_exit(71);allocationsRaw[liveAllocations++]=p;return p;
}
void release(void* p){++deletions;n(0xdee1);need(oldData&&(char*)p==(char*)oldData-8);need(list->data==oldData&&list->capacity==oldCap);need(oldAssignments==oldCap);oldData=0;oldCap=0;std::free(p);}
std::wstring key(unsigned i){switch(i){case 0:return L"";case 1:return L"A";case 2:{const wchar_t a[]={L'A',0,L'Z'};return std::wstring(a,3);}case 3:return L"Quest long shared name";case 4:return std::wstring(140,L'z');case 5:return L"\u041a\u0432\u0435\u0441\u0442";default:return L"\u4efb\u52a1";}}
void model(){expectedCount=initialCount;expectedCapacity=initialCapacity;for(unsigned i=0;i<initialCapacity;++i)expected[i].assign(list->data[i].c_str(),list->data[i].size());bool changed=false;for(unsigned pass=0;pass<cs->repeat;++pass)for(unsigned i=0;i<nq;++i){if(expectedCount>=expectedCapacity){if(cs->layout==4&&!changed&&expectedCapacity){expectedCount=1;changed=true;}expectedCapacity=expectedCapacity?expectedCapacity+list->grow:list->grow;}expected[expectedCount++].assign(keyValues[i].c_str(),keyValues[i].size());}}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;errors=copies=allocations=deletions=oldAssignments=liveAllocations=0;shifted=false;oldData=0;oldCap=0;autotest::g_arenaUsed=0;
 owner=(unsigned char*)autotest::allocate(0xf0);std::memset(owner,0x91,0xf0);owner+=16;quests=new(owner+0x40)Quests;
 nq=cs->fault?6:cs->shape==0?0:cs->shape==1?1:cs->shape==2?3:7;
 for(unsigned i=0;i<nq;++i)keyValues[i]=key(i+(cs->fault?1:0));
 const unsigned order[]={3,1,5,0,6,2,4};for(unsigned j=0;j<7;++j){unsigned i=order[j];if(i<nq)quests->insert(Quests::value_type(keyValues[i],(cs->variant&1)?0:autotest::allocate(16)));}
 for(unsigned i=0;i<nq;++i){mapKeys[i]=&quests->find(keyValues[i])->first;if(cs->variant&&mapKeys[i]->size()){std::wstring& s=const_cast<std::wstring&>(*mapKeys[i]);s[0]=s[0];}initialRefs[i]=refs(*mapKeys[i]);}
 unsigned char* arrayStorage=(unsigned char*)autotest::allocate(56);std::memset(arrayStorage,0x7a,56);list=(Array*)(arrayStorage+16);list->data=0;list->count=0;list->capacity=0;list->grow=cs->layout==0?1:3;list->pad=0x76543210;
 if(cs->layout>=2){list->capacity=4;list->count=cs->layout==2?1:4;list->data=new std::wstring[4];for(unsigned i=0;i<4;++i){const wchar_t text[]={L'p',wchar_t(L'0'+i),0,L'x'};list->data[i].assign(text,4);if(cs->variant)(list->data[i])[0]=L'p';}}
 initialCount=list->count;initialCapacity=list->capacity;for(unsigned i=0;i<64;++i)expected[i].clear();model();unsigned char ownerBefore[0xd0];std::memcpy(ownerBefore,owner,0xd0);
 typedef void(*Fn)(void*,void*);Fn fn=candidate?&qrNewNames:&qrOldNames;unsigned caught=0;
 {detour::Set allocators,copyRedirect,assignRedirect;copyPatch=&copyRedirect;assignPatch=&assignRedirect;allocators.redirect(qrArrayNew,qrArrayNew,&allocate);allocators.redirect(qrArrayDelete,qrArrayDelete,&release);copyRedirect.redirect(qrCopy,qrCopy,&copy);assignRedirect.redirect(qrAssign,qrAssign,&assign);if(allocators.failed()||copyRedirect.failed()||assignRedirect.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(!autotest::beginInvocation(out,fn))return;try{for(currentPass=0;currentPass<cs->repeat;++currentPass)fn(owner,list);out.callCompleted=1;}catch(const std::bad_alloc&){caught=1;}catch(const Stop&){caught=2;}}
 need(caught==cs->fault);need(!std::memcmp(ownerBefore,owner,0xd0));need(quests->size()==nq);need(list->grow==(cs->layout==0?1u:3u)&&list->pad==0x76543210);for(unsigned i=0;i<16;++i)need(arrayStorage[i]==0x7a&&arrayStorage[40+i]==0x7a&&owner[-16+(int)i]==0x91&&owner[0xd0+i]==0x91);
 if(caught){need(copies==1);need(list->count==initialCount);need(list->capacity==(caught==1&&!initialCapacity?list->grow:initialCapacity));need(allocations==(caught==1?1u:0u));need(!deletions);}
 else {need(copies==nq*cs->repeat);need(list->count==expectedCount&&list->capacity==expectedCapacity);for(unsigned i=0;i<list->capacity&&i<64;++i){need(list->data[i]==expected[i]);out.addText(list->data[i]);}}
 keyRefs();for(unsigned i=0;i<nq;++i){need(*mapKeys[i]==keyValues[i]);out.addText(*mapKeys[i]);n(refs(*mapKeys[i])-initialRefs[i]);}
 n(copies);n(allocations);n(deletions);n(list->count);n(list->capacity);n(shifted);n(caught);n(0x265e700u);n(errors);delete[] list->data;quests->~Quests();
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(questmanager_names){using namespace qr_names;autotest::Coverage cv("questmanager_names",0xd2e700);unsigned count=0;for(unsigned shape=0;shape<4;++shape)for(unsigned layout=0;layout<5;++layout)for(unsigned variant=0;variant<2;++variant)for(unsigned repeat=1;repeat<=2;++repeat){Case c={shape,layout,variant,repeat,0};if(!qr::pair(host,cv,a,b,&c,false)){host->log(" names shape=%u layout=%u variant=%u repeat=%u\n",shape,layout,variant,repeat);cv.report(host);return 1;}++count;}cv.report(host);return cv.completed!=count||cv.different||cv.missing;}
TL_TEST(questmanager_names_exceptions){using namespace qr_names;autotest::Coverage cv("names unwind excluded",0xd2e700);unsigned count=0;for(unsigned layout=0;layout<4;++layout){if(layout==2)continue;for(unsigned variant=0;variant<2;++variant)for(unsigned fault=1;fault<=2;++fault){Case c={3,layout,variant,1,fault};if(!qr::pair(host,cv,a,b,&c,true)){host->log(" names unwind layout=%u variant=%u fault=%u\n",layout,variant,fault);return 1;}++count;}}host->log(" names: %u expected copy/allocation unwinds, no completed coverage\n",count);return 0;}
